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

	//获取客户端连接地址和端口
	inline sockaddr_in GetRemoteAddrIn()
	{
		return remote_addr_;
	}
	//获取客户端名称
	inline const char* GetRemoteHost()
	{
		return remote_host_;
	}
	//获取客户端端口
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

	/* 验证客户端注册数据是否有效
	 *@return 返回true表示注册数据有效并，返回false则关闭连接
	 */
	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regdata) = 0;

	void Disconnected();
	virtual bool PreProcess(DataPacketReader* data_buf);
protected:
	sockaddr_in				remote_addr_;		//客户端连接地址和端口
	char					remote_host_[128];	//客户端名称
	int						remote_port_;		//客户端端口
	bool					keep_alive_;//是否主动向客户端发送保持连接数据包
private:
	bool		registed_;			//客户端是否已经注册连接
	int			client_srv_idx_;		//客户端的服务器ID
	char		client_name_[40];		//客户端注册的服务器名称
	int			client_type_;	//客户端注册的服务器类型
};


#endif

