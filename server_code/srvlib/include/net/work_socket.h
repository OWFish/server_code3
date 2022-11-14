#ifndef _WORK_SOCKET_H_
#define _WORK_SOCKET_H_

#include "os_def.h"
#define flushProtoPacket(x) FlushProtoPacket(x, __FILE__, __LINE__)
using namespace tick64;
using namespace container;
using namespace lock;
using namespace net;

class WorkSocket :
	public BaseSocket,
	public SendPacketPool
{
public:
	const static size_t MAX_DATA_LEN = 32 * 1024 * 1024;	// ÿ���������ݰ����ϰ�ͷ����󳤶�
public:
	WorkSocket(const char* name);
	virtual ~WorkSocket();
	virtual void SingleRun();

	//���ݰ������Ϻ���Ҫ����flushProtoPacket�ύ�����Ͷ���
	DataPacket& allocProtoPacket(uint16_t cmd);

	void FlushProtoPacket(DataPacket& packet, const char* fn, int line);

	//�����ڲ���Ϣ
	void PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4);

	//��ʼ������⣨����WSAStartup��,����0��ʾ�ɹ�
	static int InitSocketLib();
	//ж������⣨����WSACleanup��
	static void UnintSocketLib();

	// �Ƿ���δ���������
	bool HasRemainData();
	// �Ƿ��Զ��������ݰ�
	void SetAutoSend(bool flag)
	{
		auto_send_ = flag;
	}
	
	// ��������
	void SendBuffers();

	// �߳���ÿһ��loop�Ƿ��ת
	inline bool GetBusy()
	{
		return busy_;
	}
protected:
	virtual void OnRecv();

	/**** ���º�����Ϊ���������Ҫ���ǵĺ��� ****/
	virtual bool PreProcess(DataPacketReader*)
	{
		return true;
	}

	virtual void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);
	virtual void OnRun();
	virtual void OnRecv(const UInt16 cmd, char* buf, int size);

	void ProcessRecvData(DataPacket* data_buf);

protected:
	void ProcessSysMsg();
	void ClearSendBuffers();
	int ReadSocket();
	inline int GetMsgCount()
	{
		return msg_list_.count();
	}
	void Disconnected();
	void SendKeepAlive();
	void SetRecvSize(int size)
	{
		recv_size_ = size;
	}
	inline void SleepX()
	{
		Sleep(1);
	}
	inline void SetBusy(bool busy)
	{
		busy_ = busy_ || busy;
	}

protected:
	time_t					last_msg_t_;		//�ϴ�ͨ�ŵ�ʱ��
	QueueList<APPINTERNALMSG> msg_list_;		//�ڲ���Ϣ�б�
	bool					busy_;
private:
	DataPacket*				proc_pack_;
	BaseAllocator			allocator_;

	Mutex					msg_lock_;		//�ڲ���Ϣ�б���
	size_t					recv_size_;
	bool					auto_send_;
};


#endif

