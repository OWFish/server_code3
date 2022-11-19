#ifndef _GAME_GATE_H_
#define _GAME_GATE_H_
/***************************************************************
*                     �߼��������������Ӷ���
*              ʵ���߼��������е�����ͨ���Լ������û�����
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
		Vector<DataPacket*>			netmsg_list_;		//��ʱ������ת��������,���̰߳�ȫ��������ͬ���̷߳����������
		QueueList<DataPacket*>		free_list_;			//������ſ��е����ݰ�
		Mutex						free_lock_;
		Vector<DataPacket*>			free_back_list_;	// ���̰߳�ȫ��ֻ������Ϸ���̷߳���,����������ݰ��ȼ��з�����
		DataPacket*					big_packet_;		// ���ڰ����з����û��İ��㼯�Ĵ��

		bool						gc_;
		int							pack_total_;		// �ܹ������packet���������ڶ��ڵ��ڴ��ͷ�
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
			// AllocSendPack�����send_gate_alloc_��������
			// �������ط�����AllocGateSendPacket�������������datapack�ֲ��������������
			// ���ͳһ�����Զ���ķ�����
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
		//#define RUNTEMPCODE             0XEEFF          //temp���֣�Ҳ����У��
		//#define	RUNGATECODE				0xAA55AA55		//����ͨ��
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

	// �ر��˻�
	bool CloseUserByAccount(int accountId);

	// �ͷ��ڴ�
	void GC();
protected:

	/*** ���Ǹ�����߼��������� ***/
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

//	BaseAllocator			send_gate_alloc_;	// ���͵����صİ����ڴ������
	BaseAllocator			recv_gate_alloc_;	// �����ؽ��յ������ݵ��ڴ������
};


#endif


