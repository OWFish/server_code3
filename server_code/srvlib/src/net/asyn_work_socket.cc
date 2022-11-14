#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include <_ast.h>

#include <net/base_socket.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/asyn_work_socket.h"
#include "server_def.h"

AsynWorkSocket::AsynWorkSocket(const char* name)
	: BaseSocket(), SendPacketPool(name), allocator_("Asyn_WorkSock_Alloc"), net_msg_list_(),free_back_list_(),
		free_dp_list_(), recv_size_(4096),  data_buff_(&allocator_)
{
	last_msg_t_ = 0;
	msg_list_.setLock(&msg_lock_);

	net_msg_list_.setLock(&net_msg_lock_);
	free_dp_list_.setLock(&free_lock_);

	//data_buff_.reserve(10 * 1024 * 1024);
}


AsynWorkSocket::~AsynWorkSocket()
{
	msg_list_.flush();
	msg_list_.clear();

	// 回收所有数据包并释放内存
	net_msg_list_.flush();
	free_dp_list_.flush();
	free_dp_list_.addList(free_back_list_);
	free_dp_list_.addList(net_msg_list_);

	net_msg_list_.clear();
	free_back_list_.clear();

	FILE* fp = fopen("asyn_work.txt", "w");
	char buf[256];

	for (int i = 0; i < free_dp_list_.count(); ++i)
	{
		DataPacket* dp = free_dp_list_[i];
		dp->setLength(0);
		sprintf(buf, "dpsize:%d\n", (int)(dp->getSize()));
		fputs(buf, fp);
		Flush(*dp);	// 提交到发送队列，最后会被释放掉
	}

	sprintf(buf, "total:%d\n", (int)(data_buff_.getSize()));
	fputs(buf, fp);
	fclose(fp);
	free_dp_list_.clear();
}

DataPacket& AsynWorkSocket::allocProtoPacket(uint16_t cmd)
{
#pragma pack(push,4)
	struct CmdHdr
	{
		DATAHEADER hdr;	// 这个也是4字节对齐
		uint16_t cmd;
		uint16_t reserve;	//多余的两个字节，为了字节对齐
	};
#pragma pack(pop)
	STATIC_ASSERT(sizeof(CmdHdr) == sizeof(DATAHEADER) + 4);

	DataPacket& packet = AllocSendPack();

	packet.setLength(sizeof(CmdHdr));

	CmdHdr* pack_hdr = (CmdHdr*)packet.getMemoryPtr();
	pack_hdr->hdr.tag = TAG_VALUE;
	pack_hdr->cmd = cmd;

	const int pos = sizeof(CmdHdr) - sizeof(pack_hdr->reserve);
	packet.setPosition(pos);

	return packet;
}

void AsynWorkSocket::FlushProtoPacket(DataPacket& packet, const char* fn, int line)
{
	DATAHEADER* hdr = (DATAHEADER*)packet.getMemoryPtr();
	
	hdr->len = packet.getLength() - sizeof(*hdr);
	
	if (packet.getLength() > 0xffff)
	{
		OutputMsg(rmError, "%s:send a big packet,size more than 65535,size:%d,function:%s, %d", 
			GetName(), packet.getLength(), fn, line);
	}

	Flush(packet);
}

bool AsynWorkSocket::ReadSocket()
{
	if (!connected())
		return false;

	bool hasrecv = false;
	DataPacket* dp = NULL;
	int end = 0;

	for( ; ;)
	{
		if (!dp)
		{
			if (free_dp_list_.count() <= 0)
			{
				if (free_dp_list_.appendCount() > 0)
				{
					free_dp_list_.flush();
				}
				else
				{
					AllocSendPack(&free_dp_list_, 4, NULL/*, &allocator_*/);
				}
			}

			end = free_dp_list_.count() - 1;
			dp = free_dp_list_[end];
			dp->setLength(0);
		}

		if (dp->getAvaliableBufLen() < recv_size_)
		{
			if (dp->getSize() <= 0) dp->reserve(recv_size_);
			else dp->reserve(__max(dp->getSize(), recv_size_) * 2);	// 每次double增长
		}

		//从套接字读取数据
		int err = recv(dp->getOffsetPtr(), (int)(dp->getAvaliableBufLen()));

		if (err <= 0)
			break;

		dp->adjustOffset(err);
		hasrecv = true;
	}

	if (hasrecv)
	{
		dp->setPosition(0);
		free_dp_list_.trunc(end);
		net_msg_list_.append(dp);
		last_msg_t_ = NOW_T;
	}
	return hasrecv;
}

void AsynWorkSocket::OnRecv()
{
	int count = net_msg_list_.count();

	if (count <= 0) return;

	DataPacket** list = net_msg_list_;

	if (count > 0 && !PreProcess(list[0]))
	{
		free_back_list_.add(list[0]);
		net_msg_list_.remove(0);
		return;
	}
#ifdef _MSC_VER
#pragma message ("其实可以不用这一次的内存copy，不过这样写代码就简单了")
#endif
	static const size_t HDR_SIZE = sizeof(DATAHEADER);
	data_buff_.setPosition(data_buff_.getLength());	// 数据copy到data_buff_

	for (int i = 0; i < count; ++i)
	{
		DataPacket* dp = list[i];

		if (dp->getAvaliableLength() > 0)
		{
			data_buff_.writeBuf(dp->getOffsetPtr(), dp->getAvaliableLength());
		}
	}

	data_buff_.setPosition(0);

	if (count > 0)
	{
		free_back_list_.addList(net_msg_list_);
		net_msg_list_.clear();
	}

	char* buf = data_buff_.getOffsetPtr();
	size_t left_len = data_buff_.getAvaliableLength();
	int tip_flag = 0, last_tip = 0;	// 避免重复输出相同的日志

	while (left_len >= HDR_SIZE)
	{
		DATAHEADER* hdr = (DATAHEADER*)buf;

		if (hdr->tag == TAG_VALUE)
		{
			size_t total = __max(hdr->len + HDR_SIZE, HDR_SIZE);

			if (hdr->len >= sizeof(uint16_t))
			{
				if (total < 0x80000)
				{
					if (left_len < total) break;

					char* tmp_buf = (char*)(hdr + 1);
					uint16_t* cmd = (uint16_t*)tmp_buf;
					tmp_buf += sizeof(uint16_t);
					OnRecv(*cmd, tmp_buf, hdr->len - sizeof(uint16_t));
				}
				else
				{
					tip_flag = 3;
					total = HDR_SIZE;
				}
			}
			else
			{
				tip_flag = 2;
			}

			buf += total;
			left_len -= total;
		}
		else
		{
			++buf;
			--left_len;
			tip_flag = 1;
		}

		if (tip_flag != last_tip)
		{
			last_tip = tip_flag;
			OutputMsg(rmWarning, ("%s droped a packed(not RUNGATECODE):errcode=%d"), 
				GetName(), (__FUNCTION__), tip_flag);
		}
	}

	data_buff_.adjustOffset(buf - data_buff_.getOffsetPtr());

	// 还有剩余数据，移到最前面
	size_t left = 0;

	if ((left = data_buff_.getAvaliableLength()) > 0 && data_buff_.getPosition() > 0)
	{
		memmove(data_buff_.getMemoryPtr(), data_buff_.getOffsetPtr(), left);
	}

	data_buff_.setLength(left);
	data_buff_.setPosition(0);
}

void AsynWorkSocket::SendBuffers()
{
	if (SendToSocket(*this) > 0)
	{
		last_msg_t_ = NOW_T;
	}
}


void AsynWorkSocket::SwapPackets()
{
	// 空闲的包先还回去
	if (free_back_list_.count() > 0)
	{
		free_dp_list_.appendList(free_back_list_);
		free_back_list_.clear();
	}

	if (net_msg_list_.appendCount() > 0)
	{
		net_msg_list_.flush();
	}
}

void AsynWorkSocket::SingleRun()
{
	//接收数据
	if (connected())
		SwapPackets();

	//处理接受到的数据包
	if (connected())
		OnRecv();

	//处理内部消息
	ProcessSysMsg();

	//调用例行函数
	OnRun();

	//发送数据
	if (connected())
	{
		SendBuffers();
	}
}

void AsynWorkSocket::OnRecvSysMsg(UINT, size_t, size_t, size_t, size_t)
{
}

void AsynWorkSocket::ProcessSysMsg()
{
	msg_list_.flush();
	int count = msg_list_.count();

	for (int i = 0; i < count; ++i)
	{
		APPINTERNALMSG& msg = msg_list_[i];
		OnRecvSysMsg(msg.msg_, msg.p1_, msg.p2_, msg.p3_, msg.p4_);
	}

	msg_list_.clear();
}

void AsynWorkSocket::Disconnected()
{
	BaseSocket::Disconnected();

	//断开连接后清空接收到的数据
	net_msg_list_.flush();
	free_dp_list_.flush();
	free_dp_list_.addList(free_back_list_);
	free_dp_list_.addList(net_msg_list_);

	net_msg_list_.clear();
	free_back_list_.clear();

	for (int i = 0; i < free_dp_list_.count(); ++i)
	{
		DataPacket* dp = free_dp_list_[i];
		dp->setLength(0);
	}
}

void AsynWorkSocket::ClearSendBuffers()
{
	ClearSendList();
}

void AsynWorkSocket::OnRun()
{
}

void AsynWorkSocket::PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4)
{
	APPINTERNALMSG msg;
	msg.msg_ = uMsg;
	msg.p1_ = para1;
	msg.p2_ = para2;
	msg.p3_ = para3;
	msg.p4_ = para4;
	msg_list_.append(msg);
}

int AsynWorkSocket::InitSocketLib()
{
#ifdef _MSC_VER
	WSADATA Wsad;

	if (WSAStartup(0x0202, &Wsad))
		return GetLastError();
#endif
	return 0;
}

void AsynWorkSocket::UnintSocketLib()
{
#ifdef _MSC_VER
	WSACleanup();
#endif
}

void AsynWorkSocket::SendKeepAlive()
{
	DataPacket& packet = allocProtoPacket(0);
	flushProtoPacket(packet);
}

void AsynWorkSocket::OnRecv(const UInt16, char*, int)
{

}

void AsynWorkSocket::SetDataBuffSize(int size)
{
	data_buff_.reserve(size);
}


