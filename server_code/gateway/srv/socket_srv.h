#pragma once
class SocketSrv : public thread::BaseThread {
public:
	typedef thread::BaseThread Inherited;
	SocketSrv();
	~SocketSrv();
#ifdef _MSC_VER
	static void STDCALL ServerSocketAcceptThreadRoutine(void* srv);
#else
	static void* ServerSocketAcceptThreadRoutine(void* arg);
#endif
	virtual bool onConnect(SOCKET nSocket, sockaddr_in* pAddrIn) = 0;
	virtual void OnRoutine();
	//单次逻辑处理
	virtual int Run() = 0;
	virtual void OnStart() = 0;
	virtual void OnStop() = 0;

	inline const char* GetServiceName()
	{
		return server_name_;
	}
	inline const char* GetServiceHost()
	{
		return host_;
	}
	inline int GetServicePort()
	{
		return port_;
	}
	inline bool Started()
	{
		return !srv_stoped_;
	}
	void SetServiceName(const char* sName);
	void SetServiceHost(const char* sHost);
	void SetServicePort(const int nPort);
	bool Startup();
	virtual void Stop();

private:
#ifdef _MSC_VER
	HANDLE						accept_thread_;		//接受客户端连接线程
#else
	pthread_t					accept_thread_;
#endif

	bool						srv_stoped_;				//是否停止工作线程
	bool						accept_exit_; //监听线程完整退出

	char						server_name_[256];	//服务名称
	char						host_[256];		//服务绑定地址
	int							port_;			//服务绑定端口
};

