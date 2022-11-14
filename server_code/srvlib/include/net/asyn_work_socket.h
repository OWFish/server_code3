#ifndef _ASYN_WORK_SOCKET_H_
#define _ASYN_WORK_SOCKET_H_

#define flushProtoPacket(x) FlushProtoPacket(x, __FUNCTION__, __LINE__)

using namespace tick64;
using namespace container;
using namespace lock;
using namespace net;

class AsynWorkSocket : 
	public BaseSocket,
	public SendPacketPool
{
public:
	AsynWorkSocket(const char* name);
	virtual ~AsynWorkSocket();

	//���ݰ������Ϻ���Ҫ����flushProtoPacket�ύ�����Ͷ���
	DataPacket& allocProtoPacket(uint16_t cmd);

	void FlushProtoPacket(DataPacket& packet, const char* fn, int line);

	//�����ڲ���Ϣ
	void PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4);

	//��ʼ������⣨����WSAStartup��,����0��ʾ�ɹ�
	static int InitSocketLib();
	//ж������⣨����WSACleanup��
	static void UnintSocketLib();

	void SetDataBuffSize(int size);

protected:
	virtual void OnRecv();

	/**** ���º�����Ϊ���������Ҫ���ǵĺ��� ****/
	virtual bool PreProcess(DataPacketReader*) { return true; }

	virtual void OnRecvSysMsg(UINT uMsg, size_t uParam1, size_t uParam2, size_t uParam3, size_t uParam4);
	virtual void OnRun();
	virtual void SingleRun();
	virtual void OnRecv(const UInt16 cmd, char* buf, int size);
protected:
	void ProcessSysMsg();
	void SwapPackets();
	void ClearSendBuffers();
	bool ReadSocket();
	void SendBuffers();
	inline int GetMsgCount(){ return msg_list_.count(); }
	void Disconnected();
	void SendKeepAlive();
	void SetRecvSize(int size) { recv_size_ = size; }
protected:
	time_t					last_msg_t_;			//�ϴ�ͨ�ŵ�ʱ��
private:
	BaseAllocator			allocator_;
	QueueList<DataPacket*>	net_msg_list_;			// ���ڱ��������յ�����Ϣ
	Mutex					net_msg_lock_;

	Vector<DataPacket*>		free_back_list_;
	QueueList<DataPacket*>	free_dp_list_;
	Mutex					free_lock_;

	QueueList<APPINTERNALMSG> msg_list_;		//�ڲ���Ϣ�б�
	Mutex					msg_lock_;			//�ڲ���Ϣ�б���
	size_t					recv_size_;

	DataPacket				data_buff_;
};


#endif

