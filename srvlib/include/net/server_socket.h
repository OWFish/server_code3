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
	HANDLE						accept_thread_;		//���ܿͻ��������߳�
	HANDLE						client_thread_;			//�ͻ���ͨ�����ݴ����߳�
#else
	pthread_t					accept_thread_;
	pthread_t					client_thread_;
#endif
	bool						srv_stoped_;				//�Ƿ�ֹͣ�����߳�
	bool						accept_stoped_;	//���������ӵĹ����߳��Ƿ��Ѿ�ֹͣ�ı��*�����ٽ��������߳�ֹͣ�����ֹͣ���ݹ����߳�

	bool						srv_exit_;	// �����߳̽����ı�־
	bool						accept_exit_;// �����߳̽����ı�־

	char						server_name_[256];	//��������
	char						host_[256];		//����󶨵�ַ
	u_long						addr_;
	int							port_;			//����󶨶˿�

protected:
	QueueList<NetSession*>	session_list_;//�ͻ����б�
	Mutex					session_lock_;		//�ͻ����б���
};

#endif

