#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_

#include "server_def.h"

using namespace tick64;
using namespace container;
using namespace lock;

class NetSession : public WorkSocket
{
public:
	typedef WorkSocket Inherited;

public:
	NetSession(const char* name);
	NetSession(SOCKET s, sockaddr_in* client_addr, const char* name);
	virtual ~NetSession();

	//��ȡ�ͻ������ӵ�ַ�Ͷ˿�
	inline sockaddr_in GetRemoteAddrIn()
	{
		return remote_addr_;
	}
	//��ȡ�ͻ�������
	inline const char* GetRemoteHost()
	{
		return remote_host_;
	}
	//��ȡ�ͻ��˶˿�
	inline int GetRemotePort()
	{
		return remote_port_;
	}
	inline bool GetActiveKeepAlive()
	{
		return keep_alive_;
	}
	inline void SetActiveKeepAlive(const bool act)
	{
		keep_alive_ = act;
	}
	inline void Run()
	{
		SingleRun();
	}

	inline bool registed()
	{
		return registed_;
	}
	inline int getClientServerIndex()
	{
		return client_srv_idx_;
	}
	inline const char* getClientName()
	{
		return client_name_;
	}
	inline int getClientType()
	{
		return client_type_;
	}

protected:
	void SetClientSocket(SOCKET sock, sockaddr_in* client_addr);

	/* ��֤�ͻ���ע�������Ƿ���Ч
	 *@return ����true��ʾע��������Ч��������false��ر�����
	 */
	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regdata) = 0;

	void Disconnected();
	virtual bool PreProcess(DataPacketReader* data_buf);
protected:
	sockaddr_in				remote_addr_;		//�ͻ������ӵ�ַ�Ͷ˿�
	char					remote_host_[128];	//�ͻ�������
	int						remote_port_;		//�ͻ��˶˿�
	bool					keep_alive_;//�Ƿ�������ͻ��˷��ͱ����������ݰ�
private:
	bool		registed_;			//�ͻ����Ƿ��Ѿ�ע������
	int			client_srv_idx_;		//�ͻ��˵ķ�����ID
	char		client_name_[40];		//�ͻ���ע��ķ���������
	int			client_type_;	//�ͻ���ע��ķ���������
};


#endif

