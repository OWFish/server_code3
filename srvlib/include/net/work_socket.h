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
	const static size_t MAX_DATA_LEN = 32 * 1024 * 1024;	// 每个网络数据包加上包头的最大长度
public:
	WorkSocket(const char* name);
	virtual ~WorkSocket();
	virtual void SingleRun();

	//数据包填充完毕后需要调用flushProtoPacket提交到发送队列
	DataPacket& allocProtoPacket(uint16_t cmd);

	void FlushProtoPacket(DataPacket& packet, const char* fn, int line);

	//发送内部消息
	void PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4);

	//初始化网络库（调用WSAStartup）,返回0表示成功
	static int InitSocketLib();
	//卸载网络库（调用WSACleanup）
	static void UnintSocketLib();

	// 是否有未处理的数据
	bool HasRemainData();
	// 是否自动发送数据包
	void SetAutoSend(bool flag)
	{
		auto_send_ = flag;
	}
	
	// 发送数据
	void SendBuffers();

	// 线程在每一次loop是否空转
	inline bool GetBusy()
	{
		return busy_;
	}
protected:
	virtual void OnRecv();

	/**** 以下函数集为子类可能需要覆盖的函数 ****/
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
	time_t					last_msg_t_;		//上次通信的时间
	QueueList<APPINTERNALMSG> msg_list_;		//内部消息列表
	bool					busy_;
private:
	DataPacket*				proc_pack_;
	BaseAllocator			allocator_;

	Mutex					msg_lock_;		//内部消息列表锁
	size_t					recv_size_;
	bool					auto_send_;
};


#endif

