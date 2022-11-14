#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_


class NetSession;

class ServerSocket
	: public WorkSocket
{
public:
	typedef WorkSocket	Inherited;
private:
#ifdef _MSC_VER
	static void STDCALL ServerSocketAcceptThreadRoutine(ServerSocket* srv);
	static void STDCALL ServerSocketDataThreadRoutine(ServerSocket* srv);
#else
	static void* ServerSocketAcceptThreadRoutine(void* srv);
	static void* ServerSocketDataThreadRoutine(void* srv);
#endif

protected:
	virtual NetSession* NewSession(SOCKET nSocket, sockaddr_in* pAddrIn) = 0;
	virtual void DestroySession(NetSession* client);
protected:
	virtual void OnServerStart();
	virtual void OnServerStop();
	virtual void OnClientConnect(NetSession* pClientSocke);
protected:
	virtual bool DoStartup();
	virtual void DoStop();
	virtual void ProcessClients();
	virtual void CloseAllClients();
public:
	ServerSocket(const char* name);
	~ServerSocket();

	void SetServiceName(const char* sName);
	void SetServiceHost(const char* sHost);
	void SetServicePort(const int nPort);
	bool Startup();
	void Stop();
	void SingleRun();


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

private:
#ifdef _MSC_VER
	HANDLE						accept_thread_;		//接受客户端连接线程
	HANDLE						client_thread_;			//客户端通信数据处理线程
#else
	pthread_t					accept_thread_;
	pthread_t					client_thread_;
#endif
	bool						srv_stoped_;				//是否停止工作线程
	bool						accept_stoped_;	//接受新连接的工作线程是否已经停止的标记*必须再接受连接线程停止后才能停止数据工作线程

	bool						srv_exit_;	// 真正线程结束的标志
	bool						accept_exit_;// 真正线程结束的标志

	char						server_name_[256];	//服务名称
	char						host_[256];		//服务绑定地址
	u_long						addr_;
	int							port_;			//服务绑定端口

protected:
	QueueList<NetSession*>	session_list_;//客户端列表
	Mutex					session_lock_;		//客户端列表锁
};

#endif

