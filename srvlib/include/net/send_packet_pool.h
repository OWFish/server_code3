#ifndef _SENDPACK_POOL_H_
#define _SENDPACK_POOL_H_

/************************************************************************
                         �������ݰ����л����

   �����ּ��
      1�������������ݰ��ķ��ͣ����ύ���ݰ���˳����з��ͣ�
	  2��ͨ�����ݰ�������ύ�ķ�ʽ����������ݰ�����ʱ�������ݰ����ݿ����Ŀ�����
	  3��ʹ���ڴ�أ���פ�ڴ棩�Ż��ڴ����

   ���ԭ��
      ���������ݰ����浽�б��У�����ʱѭ�����б���������͡��ᴦ���͹����ж�һ��
   ���ݰ�ֻ������һ���ֵ��������������½����´η���ʱ��������һ�����ݰ�δ�������
   �Ĳ��֡�
      ϣ�������������ݰ��ĵ����������allocSendPacketList��allocSendPacketList
   ����ȡ��һ���������ݰ��������������ݰ������ѱ���գ���ֱ��д�����ݡ�������
   ������д����ɺ󣬵���flushSendPacket��flushSendPacketList���������ݰ���
   �������Ͷ����С�
      �����������һ���������ݰ����������ڶ��л���ر�����ǰ�ύ���ݰ���
      ���ݷ����������sendToSocket���������Ͷ����е����ݰ�ͨ��socket�����ͣ�
   ��һ��sendToSocket�ĵ����в���һ���Ὣ���Ͷ��е����ݰ�ȫ��������ɣ�����socket
   ��һ������ʽ���׽��֡���һ�ε����޷������������ݰ�ʱ��������´ε����м������ͺ�
   ���Ĳ��֡�

   �ܹ��������Ч�ʵķ�ʽ�������������֣�
	   1��  �ڻ��ύ�������ݵ��߳��ڲ�����һ�����ݰ��б�ʹ�ú���
	     AllocSendPacketListһ�����������������ݰ�����һ��������
		 ���ݰ������Ϻ󣬵���FlushSendPacketListһ����ȫ���ύһ��
		 �б��е����ݰ������ַ����ܹ������Է������ݰ�����/�ύ�ĵ�Ч��Ϊ
		 ����/�ύ�ġ������������ϣ�����εĻ�ȡ���Ĳ����ϲ�Ϊһ�Σ�
		   ʹ�ô˷�����Ҫע�⣺�ύ�ķ������ݰ��Ķ����У�ÿ�����ݰ��Ķ�д
		 ƫ��������Ϊ0��FlushSendPacketList���������޸��ύ���ݰ��б�
		 ���κ����ݰ���ƫ��ָ�룡

	   2��  ��һ���ܹ�����������ݰ�����/�ύ�Ĳ���ǰ���߼�ѭ��������
	     ���֣�����һ�����ݰ��������еķ�������ȫ��׷�ӵ����Ψһ����
		 �ݰ��У����ڲ������ύ������ݰ����ܹ������Է������ݰ�����/�ύ
		 ��Ч��Ϊ���������ݰ���д���ͨ�����ݵĴ��������ϡ�

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

	// �ŵ����Ͷ�����
	inline void Flush(DataPacket& packet)
	{
		//������ݰ��ڴ��Ƿ��ƻ�
		packet._Assert();

		//������ݰ��б�д�����������ύ�����Ͷ��У�����ԭ���ݰ������ж���
		if (packet.getLength() > 0)
		{
			//�������ݰ�ƫ��Ϊ0�������ڷ������ݵĴ����ݰ�ͷ����ʼ����
			packet.setPosition(0);
			//�����ݰ�׷�ӵ����Ͷ�����
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

	// ����Ĭ�ϵ��ڴ��������������Ĭ�Ͼ���pack_allocator_
	// ע��������������̰߳�ȫ
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
	// �����ͷ��ڴ�
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
	BufferAllocator				pack_allocator_;		//�ڴ�������
	BaseAllocator				base_allocator_;		//
	BaseAllocator*				def_alloc_;				//
	Mutex						send_lock_;//�����е����ݰ�������
	Mutex						free_lock_;	//���е����ݰ�������
	int							send_idx_;//���Ͷ����е���ʼ����λ��
	QueueList<DataPacket*>		send_list_;//�����е����ݰ�����
	LockList<DataPacket*>		free_list_;	//���е����ݰ�����
	Vector<PackCount>			all_list_;//���ݰ��ڴ��ָ���б�

	char						pool_name_[32];

	bool						pack_blocked_;		// �Ƿ��д�������������
};

#endif

