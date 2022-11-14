#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

using namespace tick64;
using namespace container;
using namespace lock;

class NetClient :
	public WorkSocket
{
public:
	typedef WorkSocket Inherited;

public:
	NetClient(const char* name);
	virtual ~NetClient();

	inline const char* GetClientName()
	{
		return client_name_;
	}
	inline const char* GetHost()
	{
		return host_;
	}
	void SetHost(const char* sHost);
	inline int GetPort()
	{
		return port_;
	}
	void SetPort(const int nPort);
	virtual bool Startup();
	virtual void Stop();
#ifdef _MSC_VER
	unsigned long GetThreadId()
#else
	pthread_t GetThreadId()
#endif
	{
		return thread_id_;
	}
protected:
	virtual void OnWorkThreadStart();
	virtual void OnWorkThreadStop();
	virtual int GetLocalServerType() = 0;
	virtual const char* GetLocalServerName() = 0;
	virtual int GetLocalServerIndex();

	void SendRegisteClient();
protected:
	void SetClientName(const char* sClientName);
	virtual bool ConnectToServer();
	virtual void OnRun();
protected:
	void Connected();
	void Disconnected();
	void SocketError(int errorCode);
private:
#ifdef _MSC_VER
	static void STDCALL Work_R(NetClient* ptr);
#else
	static void* Work_R(void* ptr);
#endif
private:
#ifdef _MSC_VER
	HANDLE					handle_;		//工作线程句柄
	unsigned long			thread_id_;		//线程ID
#else
	pthread_t				thread_id_;
#endif
	bool					stoped_;				//是否标记为停止
	bool					exit_;

	char					host_[256];		//服务器地址

protected:
	u_long					addr_;
	int						port_;				//服务器端口
	char					client_name_[256];		//客户端名称
	time_t					reconn_t_;		//重新连接服务器的时间
};


#endif

