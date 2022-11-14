#ifndef _ASYN_CLIENT_SOCKET_H_
#define _ASYN_CLIENT_SOCKET_H_

using namespace tick64;
using namespace container;
using namespace lock;

class AsynClientSocket :
	public AsynWorkSocket
{
public:
	typedef AsynWorkSocket Inherited;

public:
	AsynClientSocket(const char* name);
	virtual ~AsynClientSocket();

	inline const char* GetClientName()
	{
		return client_name_;
	};
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
	bool Startup();
	void Stop();
	//unsigned long GetThreadId()
	//{
	//	return thread_id_;
	//}
protected:
	virtual void OnWorkThreadStart();
	virtual void OnWorkThreadStop();
	virtual int GetLocalServerType() = 0;
	virtual const char* GetLocalServerName() = 0;
	virtual int GetLocalServerIndex();

	void SendRegisteClient();
protected:
	void SetClientName(const char* sClientName);
	bool ConnectToServer();
	void SingleRun();

protected:
	void Connected();
	void Disconnected();
	void SocketError(int errorCode);
private:
#ifdef _MSC_VER
	HANDLE					handle_;				//�����߳̾��
	HANDLE					recv_handle_;
	unsigned long			thread_id_;		//�߳�ID
	unsigned long			recv_thread_id_;		//�߳�ID
	static void STDCALL Work_R(AsynClientSocket* client);
	static void STDCALL Recv_R(AsynClientSocket* client);
#else
	pthread_t				thread_id_;
	pthread_t				recv_thread_id_;
	static void* Work_R(void* client);
	static void* Recv_R(void* client);
#endif
	bool			stoped_;				//�Ƿ���Ϊֹͣ
	bool			recv_stoped_;				//�Ƿ���Ϊֹͣ

	bool			exit_;
	bool			recv_exit_;
	char			host_[256];		//��������ַ
	u_long			addr_;
	int						port_;				//�������˿�
	char					client_name_[256];		//�ͻ�������
	time_t					reconn_t_;		//�������ӷ�������ʱ��
};


#endif

