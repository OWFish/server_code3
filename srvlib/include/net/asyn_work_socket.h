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

	//数据包填充完毕后需要调用flushProtoPacket提交到发送队列
	DataPacket& allocProtoPacket(uint16_t cmd);

	void FlushProtoPacket(DataPacket& packet, const char* fn, int line);

	//发送内部消息
	void PostMsg(UINT uMsg, size_t para1, size_t para2, size_t para3, size_t para4);

	//初始化网络库（调用WSAStartup）,返回0表示成功
	static int InitSocketLib();
	//卸载网络库（调用WSACleanup）
	static void UnintSocketLib();

	void SetDataBuffSize(int size);

protected:
	virtual void OnRecv();

	/**** 以下函数集为子类可能需要覆盖的函数 ****/
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
	time_t					last_msg_t_;			//上次通信的时间
private:
	BaseAllocator			allocator_;
	QueueList<DataPacket*>	net_msg_list_;			// 用于保存网络收到的信息
	Mutex					net_msg_lock_;

	Vector<DataPacket*>		free_back_list_;
	QueueList<DataPacket*>	free_dp_list_;
	Mutex					free_lock_;

	QueueList<APPINTERNALMSG> msg_list_;		//内部消息列表
	Mutex					msg_lock_;			//内部消息列表锁
	size_t					recv_size_;

	DataPacket				data_buff_;
};


#endif

