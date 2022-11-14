#ifndef _GAME_GATE_H_
#define _GAME_GATE_H_
/***************************************************************
*                     逻辑服务器网关连接对象
*              实现逻辑服务器中的网关通信以及网关用户管理
***************************************************************/

class GameServer;
class GameGateMgr;

class GameGate :
	public GateSession
{
	friend class GameGateMgr;

public:
	typedef GateSession Inherited;
	enum
	{
	    GameThread = 0,
	    ActorMgrThread,
	    ThreadMax,
	};

	struct ThreadGateMsg
	{
		Vector<DataPacket*>			netmsg_list_;		//临时用来中转数据内容,非线程安全，必须在同个线程访问这个变量
		QueueList<DataPacket*>		free_list_;			//用来存放空闲的数据包
		Mutex						free_lock_;
		Vector<DataPacket*>			free_back_list_;	// 非线程安全，只能在游戏主线程访问,处理完的数据包先集中放这里
		DataPacket*					big_packet_;		// 用于把所有发给用户的包汇集的大包

		bool						gc_;
		int							pack_total_;		// 总共分配的packet个数，用于定期的内存释放
		ThreadGateMsg()
		{
			gc_ = false;
			pack_total_ = 0;
		}
	};

public:
	GameGate();
	virtual ~GameGate();

	inline void AddFreeList(DataPacket* dp, int thread_id)
	{
		ThreadGateMsg& thread_data = msg_thread_[thread_id];
		thread_data.free_back_list_.add(dp);
	}

	inline void AddFreeList(Vector<DataPacket*>& list, int count, int thread_id)
	{
		ThreadGateMsg& thread_data = msg_thread_[thread_id];

		if (count > 0)
		{
			thread_data.free_back_list_.addArray(list, count);
			list.remove(0, count);
			//for (int i = count, pos = 0; i < list.count(); ++i, pos++)
			//{
			//	list[pos] = list[i];
			//}
			//list.trunc(list.count() - count);
		}
		else
		{
			thread_data.free_back_list_.addList(list);
			list.clear();
		}
	}

	void FlushFreeList(int thread_id)
	{
		ThreadGateMsg& thread_data = msg_thread_[thread_id];

		if (thread_data.free_back_list_.count() > 0)
		{
			thread_data.free_list_.appendList(thread_data.free_back_list_);
			thread_data.free_back_list_.clear();
		}
	}

	inline void Flush(DataPacket& packet)
	{
		SendPacketPool::Flush(packet);
	}

	inline DataPacket* GetSendToGatePacket(int thread_id)
	{
		const int AllocOneTime = 2 * 1024 * 1024;
		ThreadGateMsg& thread_data = msg_thread_[thread_id];

		if (thread_data.big_packet_ == NULL)
		{
			// AllocSendPack如果用send_gate_alloc_分配器，
			// 而其他地方调用AllocGateSendPacket函数分配出来的datapack又不是用这个分配器
			// 因此统一不用自定义的分配器
			DataPacket& dp = AllocSendPack(/*&send_gate_alloc_*/);
			dp.reserve(AllocOneTime);
			dp.setAllocSize(1024 * 1024);
			dp.setLength(0);
			thread_data.big_packet_ = &dp;
		}

		return thread_data.big_packet_;
	}

	inline void SendToGate(int thread_id)
	{
		ThreadGateMsg& thread_data = msg_thread_[thread_id];

		if (thread_data.big_packet_ != NULL)
		{
			thread_data.big_packet_->setPosition(0);
			Flush(*(thread_data.big_packet_));
			thread_data.big_packet_ = NULL;
		}
	}

	inline void checkcdcd(DataPacket&)
	{
		//#define RUNTEMPCODE             0XEEFF          //temp部分，也用来校验
		//#define	RUNGATECODE				0xAA55AA55		//网关通信
		//PGATEMSGHDR pHdr;
		//char *buf = pack.getMemoryPtr();
		//char *pend = buf + pack.getLength();
		//while (buf < pend)
		//{
		//	pHdr = (PGATEMSGHDR)buf;
		//	if (pHdr->nDataSize <= 0)
		//	{
		//		//OutputMsg(rmTip, ("checkcdcd %d"), pHdr->nDataSize);
		//		Assert(0);
		//	}
		//	if (pHdr->nDataSize > 0x8000)
		//	{
		//		//OutputMsg(rmTip, ("checkcdcd %d"), pHdr->nDataSize);
		//		Assert(0);
		//	}
		//	Assert(pHdr->nDataSize > 0 && pHdr->nDataSize <= 0x8000 );
		//	Assert( pHdr->dwGateCode == RUNGATECODE);
		//	Assert( pHdr->wTemp == RUNTEMPCODE);
		//	buf += sizeof(*pHdr) + pHdr->nDataSize;
		//}
	}

	// 关闭账户
	bool CloseUserByAccount(int accountId);

	// 释放内存
	void GC();
protected:

	/*** 覆盖父类的逻辑处理函数集 ***/
	void OnOpenUser(GateUser* user);
	void OnCloseUser(GateUser* user, const char* reason);
	void OnRecv(NetId& netid, char* buf, int size);
	void OnRun();

	virtual void OnDisconnected();
	void FlushPackets();
private:
	GameServer*				login_srv_;
	GameGateMgr*			gate_mgr_;

	ThreadGateMsg			msg_thread_[ThreadMax];

//	BaseAllocator			send_gate_alloc_;	// 发送到网关的包的内存分配器
	BaseAllocator			recv_gate_alloc_;	// 从网关接收到的数据的内存分配器
};


#endif


