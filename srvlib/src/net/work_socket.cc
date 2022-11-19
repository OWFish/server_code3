#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include <_ast.h>
#include "os_def.h"

#include <net/base_socket.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "server_def.h"

WorkSocket::WorkSocket(const char* name)
	: BaseSocket(), SendPacketPool(name), allocator_("WorkSock_Alloc"), recv_size_(4096),
	auto_send_(true)
{
	last_msg_t_ = 0;

	proc_pack_ = new DataPacket(&allocator_);
	msg_list_.setLock(&msg_lock_);

	busy_ = false;
}

WorkSocket::~WorkSocket()
{
	delete proc_pack_;

	msg_list_.flush();
	msg_list_.clear();
}

DataPacket& WorkSocket::allocProtoPacket(uint16_t cmd)
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

void WorkSocket::FlushProtoPacket(DataPacket& packet, const char* fn, int line)
{
	DATAHEADER* hdr = (DATAHEADER*)packet.getMemoryPtr();
	//计算并向协议头中写入通信数据长度
	
	hdr->len = packet.getLength() - sizeof(*hdr);
	
	if (packet.getLength() > 0xffff)
	{
		OutputMsg(rmError, "%s:send a big packet,size more than 65535,size:%d,function:%s,%d", 
			GetName(), packet.getLength(), fn, line);
		//hdr->len = 0;
		//packet.setLength(0);
	}
	Flush(packet);
}

int WorkSocket::ReadSocket()
{
	int rsize = 0;
	for( ; ;)
	{
		//增长接收缓冲区大小
		const size_t packsize = proc_pack_->getSize();
		const size_t datalen = proc_pack_->getLength();
		if ((packsize - datalen) < recv_size_ * 2)
		{
			size_t size = packsize;
			size += (recv_size_ * 2);
			proc_pack_->reserve(size);
		}

		//从套接字读取数据
		int err = recv(proc_pack_->getPositionPtr(datalen), (int)recv_size_);

		if (err <= 0)
			break;
		
		SetBusy(true);

		rsize += err;

		proc_pack_->setLength(datalen + err);

		last_msg_t_ = NOW_T;

		if (proc_pack_->getLength() >= 4 * 1024 * 1024)
		{
			break;
		}
	}
	return rsize;
}

void WorkSocket::OnRecv()
{
	// 如果连接已断开则丢弃所有数据
	if (!connected())
	{
		proc_pack_->setLength(0);
		return;
	}

	// 全部数据已经处理完
	if (proc_pack_->getAvaliableLength() <= 0)
	{
		proc_pack_->setLength(0);
		return;
	}

	if (!PreProcess(proc_pack_))
	{
		return;
	}

	ProcessRecvData(proc_pack_);

	// 把尾部未处理的数据移到最前头
	size_t left = proc_pack_->getAvaliableLength();
	if (left > 0)
	{
		memmove(proc_pack_->getMemoryPtr(), proc_pack_->getOffsetPtr(), left);
	}
	proc_pack_->setLength(left);
	proc_pack_->setPosition(0);
}

void WorkSocket::SendBuffers()
{
	if (SendToSocket(*this) > 0)
	{
		last_msg_t_ = NOW_T;
		SetBusy(true);
	}
}

void WorkSocket::OnRecvSysMsg(unsigned int, size_t, size_t, size_t, size_t)
{
}

void WorkSocket::ProcessSysMsg()
{
	msg_list_.flush();
	int count = msg_list_.count();
	if (count > 0) SetBusy(true);

	for (int i = 0; i < count; ++i)
	{
		APPINTERNALMSG& msg = msg_list_[i];
		OnRecvSysMsg(msg.msg_, msg.p1_, msg.p2_, msg.p3_, msg.p4_);
	}

	msg_list_.clear();
}

void WorkSocket::SingleRun()
{
	busy_ = false;

	//接收数据
	if (connected())
	{
		if (ReadSocket())
		{
			//处理接受到的数据包
			OnRecv();
		}
	}

	//处理内部消息
	ProcessSysMsg();

	//调用例行函数
	OnRun();

	//发送数据
	if (auto_send_ && connected())
	{
		SendBuffers();
	}
}

void WorkSocket::Disconnected()
{
	BaseSocket::Disconnected();
	//断开连接后清空接收到的数据
	proc_pack_->setLength(0);
}

void WorkSocket::ClearSendBuffers()
{
	ClearSendList();
}

void WorkSocket::OnRun()
{
}

void WorkSocket::PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4)
{
	APPINTERNALMSG msg;
	msg.msg_ = uMsg;
	msg.p1_ = para1;
	msg.p2_ = para2;
	msg.p3_ = para3;
	msg.p4_ = para4;
	msg_list_.append(msg);
}

int WorkSocket::InitSocketLib()
{
#ifdef _MSC_VER
	WSADATA Wsad;

	if (WSAStartup(0x0202, &Wsad))
		return GetLastError();
#endif
	return 0;
}

void WorkSocket::UnintSocketLib()
{
#ifdef _MSC_VER
	WSACleanup();
#endif
}

void WorkSocket::SendKeepAlive()
{
	DataPacket& packet = allocProtoPacket(0);
	flushProtoPacket(packet);
}

void WorkSocket::OnRecv(const uint16_t, char*, int)
{

}

bool WorkSocket::HasRemainData()
{
	return proc_pack_->getAvaliableLength() > 0;
}

void WorkSocket::ProcessRecvData(DataPacket* data_buf)
{
	const size_t HDR_SIZE = sizeof(DATAHEADER);
	char* buf = data_buf->getOffsetPtr();
	size_t left_len = data_buf->getAvaliableLength();
	int tip_flag = 0, last_tip = 0;	// 避免重复输出相同的日志

	while (left_len >= HDR_SIZE)
	{
		DATAHEADER* hdr = (DATAHEADER*)buf;

		if (hdr->tag == TAG_VALUE)
		{
			size_t total = __max(hdr->len + HDR_SIZE, HDR_SIZE);

			if (hdr->len >= sizeof(uint16_t))
			{
				if (total < MAX_DATA_LEN)
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
			OutputMsg(rmWarning, ("%s:%s droped a packed(not RUNGATECODE):errcode=%d"), 
				GetName(), __FUNCTION__, tip_flag);
		}
	}

	data_buf->adjustOffset(buf - data_buf->getOffsetPtr());
}
