#include <new>
#include <stdio.h>
#include "os_def.h"
#include <_ast.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include <net/base_socket.h>

#include "share_util.h"
#include "server_def.h"
#include "memory/buffer_allocator.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"

SendPacketPool::SendPacketPool(const char* name) : pack_allocator_(name), base_allocator_(name)
{
	send_idx_ = 0;
	send_list_.setLock(&send_lock_);
	free_list_.setLock(&free_lock_);

	def_alloc_ = &pack_allocator_;

	_STRNCPY_A(pool_name_, name);
	pack_blocked_ = false;
}

SendPacketPool::~SendPacketPool()
{
	FreeAllPackets();
}

void SendPacketPool::FreeAllPackets()
{
	free_list_.lock();

	// test
	/*
	int total = 0;
	size_t alloc_size = 0;

	char fn[64];
	SNPRINTFA(fn, sizeof(fn), "SendPacketPool_%s.txt", pool_name_);
	FILE* fp = fopen(fn, "w");

	if (fp) fputs("======================", fp);

	char buf[256];

	for (int i = all_list_.count() - 1; i > -1; --i)
	{
		DataPacket* dp = all_list_[i].list_;

		for (int j = 0; j < all_list_[i].count_; ++j)
		{
			if (dp->getSize() != 0 && fp)
			{
				sprintf(buf, "datapack size:%d\n", (int)(dp->getSize()));
				fputs(buf, fp);
			}

			alloc_size += dp->getSize();
			dp++;
			total++;
		}
	}

	if (fp)
	{
		sprintf(buf, "all size:%llu\n", (unsigned long long int)alloc_size);
		fputs(buf, fp);
		fputs("===============================", fp);
	}

	if (fp) fclose(fp);
	*/
	// end test

	int del_count = 0;
	size_t alloc_del = 0;

	send_list_.flush();
	DataPacket** pack_list = send_list_;

	for (int i = send_list_.count() - 1; i > -1; --i)
	{
		alloc_del += (*pack_list)->getSize();
		(*pack_list)->~DataPacket();
		pack_list++;
		del_count++;
	}

	send_list_.clear();

	//销毁空闲的数据包
	pack_list = free_list_;

	for (int i = free_list_.count() - 1; i > -1; --i)
	{
		alloc_del += (*pack_list)->getSize();
		(*pack_list)->~DataPacket();
		pack_list++;
		del_count++;
	}

	free_list_.clear();

	//assert(total == del_count);
	//assert(alloc_size == alloc_del);

	//释放所有数据包内存
	for (int i = all_list_.count() - 1; i > -1; --i)
	{
		def_alloc_->FreeBuffer(all_list_[i].list_);
	}

	all_list_.clear();

	free_list_.unlock();

	//让内存管理器释放内存
	//pack_allocator_.CheckFreeBuffers();
}

void SendPacketPool::AllocSendPack(PacketList* p_list, int alloc_count, DataPacket** single, BaseAllocator* allocator)
{
	static const int Max_Count = 512;

	free_list_.lock();
	int count = free_list_.count();

	int give_count = __min(count, alloc_count);

	if (give_count > 0)
	{
		count -= give_count;

		if (p_list) p_list->addArray(&free_list_[count], give_count);

		free_list_.trunc(count);
		alloc_count -= give_count;
	}

	if (single && count > 0)//需要申请单个的话
	{
		count--;
		*single = free_list_[count];
		free_list_.trunc(count);
		single = NULL;//将参数置空，表示不需要申请单个了
	}

	if (single || alloc_count > 0)//仍不足需求数量则继续申请
	{
		//申请数据包对象内存块
		int new_count = __max(Max_Count, alloc_count);

		//如果还需要申请一个单独的数据包，则增加需求数量
		if (single) new_count ++;

		new_count = (new_count + Max_Count) & (~(Max_Count - 1));
		DataPacket* pPacket = (DataPacket*)def_alloc_->AllocBuffer(sizeof(*pPacket) * new_count);
		PackCount pc;
		pc.list_ = pPacket;
		pc.count_ = new_count;
		//讲数据包集的内存块添加到数据内存头列表中
		all_list_.add(pc);

		//如果空闲发送送数据列表的剩余空间不足以放下新申请的数据包，则增长空闲发送数据包列表的保留长度
		if (free_list_.max_size() < count + new_count)
			free_list_.reserve(count + new_count);

		//循环调用构造函数
		BaseAllocator* thisAlloc = allocator ? allocator : def_alloc_;

		for (int i = 0; i < new_count; ++i)
		{
			new(pPacket)DataPacket(thisAlloc);
			free_list_[count] = pPacket;//将数据包保存到空闲发送送数据列表
			pPacket++;
			count++;
		}

		//将剩余申请的数据包拷贝到申请列表中
		if (alloc_count > 0)
		{
			count -= alloc_count;

			if (p_list) p_list->addArray(&free_list_[count], alloc_count);

			free_list_.trunc(count);
		}

		//需要申请一个单独的数据包
		if (single)
		{
			count--;
			*single = free_list_[count];
			free_list_.trunc(count);
		}
	}

	free_list_.unlock();
}

void SendPacketPool::ClearSendList()
{
	free_list_.lock();
	send_list_.flush();
	//情况所有发送队列中数据包的长度
	DataPacket** pack_list = send_list_;

	for (int i = send_list_.count() - 1; i > -1; --i)
	{
		pack_list[i]->setLength(0);
	}

	//将发送队列中的数据包还原到空闲队列中
	free_list_.addArray(send_list_, send_list_.count());
	send_list_.trunc(0);
	//重置发送队列索引为0
	send_idx_ = 0;
	free_list_.unlock();
}

size_t SendPacketPool::SendToSocket(net::BaseSocket& socket)
{
	static int last_send_error = 0;	// 上次send函数出错的错误码
	static int last_pack_len = 0;

	size_t total_send = 0;

	send_list_.flush();

	DataPacket** pack_list = send_list_;
	int count = send_list_.count();

	// 如果数据包积累太多，发出警报
	if (count >= 1024)
	{
		pack_blocked_ = true;
		static time_t next_t = 0;
		time_t now_t = NOW_T;

		if (next_t < now_t)
		{
			OutputMsg(rmError, "too many send packet in SendPacketPool!%d,%s,%d,%d",
			          count, pool_name_, last_send_error, last_pack_len);
			next_t = now_t + 10;	// 10秒输出一次
		}
	}
	else
	{
		pack_blocked_ = false;
	}

	//
	for (; send_idx_ < count; ++send_idx_)
	{
		DataPacket* pack = pack_list[send_idx_];
		int aval_len = (int)pack->getAvaliableLength();

		if (aval_len < 0) aval_len = 0;

		int has_write = 0;

		if (aval_len > 0)
		{
			has_write = socket.send(pack->getOffsetPtr(), aval_len);

			if (has_write <= 0)
			{
				last_send_error = has_write;
				last_pack_len = aval_len;
				break;
			}
		}

		total_send += has_write;

		//该数据包中的数据是否已经发完
		if (has_write >= aval_len)
		{
			pack->setLength(0);
		}
		else
		{
			//调整偏移到下次继续发送的位置
			pack->adjustOffset(has_write);
			break;
		}
	}

	//如果发送队列中的数据已经全部发送完毕，则将数据包全部移动到空闲数据包列表中
	if (send_idx_ >= count)
	{
		send_idx_ = 0;
		free_list_.lock();
		free_list_.addArray(send_list_, send_list_.count());
		send_list_.trunc(0);
		free_list_.unlock();
	}

	return total_send;
}

void SendPacketPool::GC()
{
	free_list_.lock();

	for (int i = free_list_.count() - 1; i > -1; --i)
	{
		DataPacket* dp = free_list_[i];
		dp->empty();
	}

	free_list_.unlock();
}


