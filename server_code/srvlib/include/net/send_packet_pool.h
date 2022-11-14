#ifndef _SENDPACK_POOL_H_
#define _SENDPACK_POOL_H_

/************************************************************************
                         网络数据包队列缓冲池

   设计宗旨：
      1、管理网络数据包的发送，按提交数据包的顺序进行发送；
	  2、通过数据包申请和提交的方式免除构造数据包后发送时进行数据包内容拷贝的开销；
	  3、使用内存池（常驻内存）优化内存管理；

   设计原理：
      将网络数据包保存到列表中，发送时循环从列表中逐个发送。会处理发送过程中对一个
   数据包只发送了一部分的情况，这种情况下将在下次发送时继续发送一个数据包未发送完成
   的部分。
      希望发送网络数据包的调用者需调用allocSendPacketList或allocSendPacketList
   函数取得一个或多个数据包对象。申请后的数据包内容已被清空，可直接写入数据。当数据
   包数据写入完成后，调用flushSendPacket或flushSendPacketList函数将数据包提
   交到发送队列中。
      ★调用者申请一个发送数据包对象后必须在队列缓冲池被销毁前提交数据包；
      数据发送者需调用sendToSocket函数将发送队列中的数据包通过socket对象发送，
   在一次sendToSocket的调用中并不一定会将发送队列的数据包全部发送完成，除非socket
   是一个阻塞式的套接字。当一次调用无法发完所有数据包时，则会在下次调用中继续发送后
   续的部分。

   能够最大化提升效率的方式至少有以下两种：
	   1）  在会提交发送数据的线程内部建立一个数据包列表，使用函数
	     AllocSendPacketList一次性申请多个发送数据包，在一定数量的
		 数据包填充完毕后，调用FlushSendPacketList一次性全部提交一个
		 列表中的数据包，这种方法能够提升对发送数据包申请/提交的的效率为
		 申请/提交的“数量”倍以上，将多次的获取锁的操作合并为一次！
		   使用此方法需要注意：提交的发送数据包的队列中，每个数据包的读写
		 偏移量必须为0，FlushSendPacketList函数不会修改提交数据包列表
		 中任何数据包的偏移指针！

	   2）  在一个能够产生多次数据包申请/提交的操作前（逻辑循环最外层的
	     部分）申请一个数据包对象，所有的发送数据全部追加到这个唯一的数
		 据包中，并在操作后提交这个数据包。能够提升对发送数据包申请/提交
		 的效率为向整个数据包中写入的通信数据的次数倍以上。

************************************************************************/

using namespace container;
using namespace net;

class SendPacketPool
{
	typedef Vector<DataPacket*> PacketList;
	struct PackCount
	{
		DataPacket* list_;
		int			count_;
	};
public:
	SendPacketPool(const char* name);
	~SendPacketPool();

	inline DataPacket& AllocSendPack(BaseAllocator* allocator = NULL)
	{
		DataPacket* pack;
		AllocSendPack(NULL, 0, &pack, allocator);
		pack->setLength(0);
		return *pack;
	}

	// 放到发送队列中
	inline void Flush(DataPacket& packet)
	{
		//检查数据包内存是否被破坏
		packet._Assert();

		//如果数据包中被写入了数据则提交到发送队列，否则还原数据包到空闲队列
		if (packet.getLength() > 0)
		{
			//调整数据包偏移为0，才能在发送数据的从数据包头部开始发送
			packet.setPosition(0);
			//将数据包追加到发送队列中
			send_list_.append(&packet);
		}
		else
		{
			free_list_.lock();
			free_list_.add(&packet);
			free_list_.unlock();
		}
	}

	void AllocSendPack(PacketList* p_list, int alloc_count, DataPacket** single = NULL, BaseAllocator* allocator = NULL);

	inline void Flush(PacketList& packetList)
	{
		send_list_.appendArray(packetList, packetList.count());
	}

	void ClearSendList();

	size_t SendToSocket(net::BaseSocket& socket);

	inline size_t GetPacketCount()
	{
		send_list_.flush();
		return send_list_.count() + send_list_.appendCount();
	}

	// 设置默认的内存分配器，不设置默认就是pack_allocator_
	// 注意分配器必须是线程安全
	inline void SetAllocator(BaseAllocator* alloc)
	{
		if (!alloc) return;

		def_alloc_ = alloc;
	}
	inline void UseBaseAlloc(bool flag)
	{
		def_alloc_ = flag ? &base_allocator_ : &pack_allocator_;
	}
	void FreeAllPackets();

	bool IsPackBlocked()
	{
		return pack_blocked_;
	}
	// 定期释放内存
	void GC();

	size_t GetAllocCount()
	{
		return def_alloc_->GetAllocCount();
	}
	const char* GetName()
	{
		return pool_name_;
	}
private:
	BufferAllocator				pack_allocator_;		//内存块管理器
	BaseAllocator				base_allocator_;		//
	BaseAllocator*				def_alloc_;				//
	Mutex						send_lock_;//发送中的数据包队列锁
	Mutex						free_lock_;	//空闲的数据包队列锁
	int							send_idx_;//发送队列中的起始发送位置
	QueueList<DataPacket*>		send_list_;//发送中的数据包队列
	LockList<DataPacket*>		free_list_;	//空闲的数据包队列
	Vector<PackCount>			all_list_;//数据包内存块指针列表

	char						pool_name_[32];

	bool						pack_blocked_;		// 是否有大量包被阻塞了
};

#endif

