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
	//�����߼�����
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
	HANDLE						accept_thread_;		//���ܿͻ��������߳�
#else
	pthread_t					accept_thread_;
#endif

	bool						srv_stoped_;				//�Ƿ�ֹͣ�����߳�
	bool						accept_exit_; //�����߳������˳�

	char						server_name_[256];	//��������
	char						host_[256];		//����󶨵�ַ
	int							port_;			//����󶨶˿�
};

