#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include <_ast.h>

#include <x_thread.h>
#include <net/base_socket.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "server_def.h"
#include "net/work_socket.h"
#include "net/net_session.h"
#include "net/server_socket.h"
#include "second_time.h"

ServerSocket::ServerSocket(const char* name)
	: Inherited(name)
{
	server_name_[0] = 0;
	SetServiceHost("0.0.0.0");//默认绑定到所有网卡
	port_ = 0;

	srv_stoped_ = true;
	accept_stoped_ = true;
	srv_exit_ = true;
	accept_exit_ = true;

#ifdef _MSC_VER
	accept_thread_ = NULL;
	client_thread_ = NULL;
#endif

	session_list_.setLock(&session_lock_);
}

ServerSocket::~ServerSocket()
{
	Stop();
}


#ifdef _MSC_VER
void ServerSocket::ServerSocketAcceptThreadRoutine(ServerSocket* ptr)
#else
void* ServerSocket::ServerSocketAcceptThreadRoutine(void* ptr)
#endif
{
	ServerSocket* srv = (ServerSocket*)ptr;

	while (!srv->accept_stoped_)
	{
		SOCKET sock;
		sockaddr_in addr_In;
		int err = srv->accept(&sock, 1000, &addr_In);
		if (srv->accept_stoped_) break;
		//成功
		if (err == 0)
		{
			//创建客户端连接类
			NetSession* client = srv->NewSession(sock, &addr_In);

			//创建连接类失败，则关闭套接字
			if (!client)
			{
				closesocket(sock);
				continue;
			}

			//设置为非阻塞模式
			err = client->setBlockMode(false);

			if (err)
			{
				OutputError(err, ("无法将%s套接字接受的连接设置为非阻塞模式"), srv->server_name_);
				delete client;
				continue;
			}

			//调整接收缓冲区大小
			err = client->setRecvBufSize(32 * 1024);

			if (err)
			{
				//此操作的错误可以忽略
				OutputError(err, ("setRecvBufSize error:%s"), srv->server_name_);
			}

			//调整发送缓冲区大小
			err = client->setSendBufSize(32 * 1024);

			if (err)
			{
				//此操作的错误可以忽略
				OutputError(err, ("setSendBufSize error: %s"), srv->server_name_);
			}

			srv->OnClientConnect(client);

			if (client->connected())
				srv->session_list_.append(client);
			else srv->DestroySession(client);

			continue;
		}

		//超时
		if (err == SOCKET_ERROR - 1)
			continue;

		OutputError(err, "%s错误", __FUNCTION__);
		break;
	}

	srv->accept_exit_ = true;

#ifdef _MSC_VER
	//ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

#ifdef _MSC_VER
void ServerSocket::ServerSocketDataThreadRoutine(ServerSocket* ptr)
#else
void* ServerSocket::ServerSocketDataThreadRoutine(void* ptr)
#endif
{
	CheckDate();

	ServerSocket* srv = (ServerSocket*)ptr;

	srv->OnServerStart();

	while (!srv->srv_stoped_)
	{
		srv->SingleRun();
		if (!srv->busy_) srv->SleepX();
	}

	if (srv->connected())
	{
		srv->Close();
	}

	srv->OnServerStop();
	//关闭所有连接
	srv->CloseAllClients();

	srv->srv_exit_ = true;
#ifdef _MSC_VER
	//ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

void ServerSocket::OnClientConnect(NetSession*)
{

}

bool ServerSocket::DoStartup()
{
	return true;
}

void ServerSocket::DoStop()
{

}

void ServerSocket::OnServerStart()
{

}

void ServerSocket::OnServerStop()
{
}

void ServerSocket::DestroySession(NetSession* client)
{
	delete client;
}

void ServerSocket::ProcessClients()
{
	//循环处理每个客户端连接
	session_list_.flush();
	for (int i = session_list_.count() - 1; i > -1; --i)
	{
		NetSession* cli = session_list_[i];

		// 删除断开的连接
		if (!cli || !cli->connected())
		{
			session_list_.lock();
			session_list_.remove(i);
			session_list_.unlock();
			DestroySession(cli);
			continue;
		}

		// 处理活动的连接
		cli->Run();
		SetBusy(cli->GetBusy());
	}
}

void ServerSocket::CloseAllClients()
{
	session_list_.flush();
	session_list_.lock();

	for (int i = session_list_.count() - 1; i > -1; --i)
	{
		NetSession* client = session_list_[i];

		if (client)
		{
			client->Close();
			DestroySession(client);
		}
	}

	session_list_.clear();
	session_list_.unlock();
}

void ServerSocket::SingleRun()
{
	busy_ = false;

	//处理连接的客户端
	ProcessClients();

	//处理内部消息
	ProcessSysMsg();

	//调用例行函数
	OnRun();
}

void ServerSocket::SetServiceName(const char* sName)
{
	_STRNCPY_A(server_name_, sName);
}

void ServerSocket::SetServiceHost(const char* hostName)
{
	_STRNCPY_A(host_, hostName);

	hostent* host = gethostbyname(hostName);

	if (host)
	{
		addr_ = *(u_long*)host->h_addr_list[0];
	}
}

void ServerSocket::SetServicePort(const int nPort)
{
	port_ = nPort;
}

bool ServerSocket::Startup()
{
	srv_stoped_ = false;

	//创建用于接受连接的套接字
	int err = createSocket(&socket_);

	if (err)
	{
		OutputError(err, ("createSocket error : %s"), server_name_);
		return false;
	}

	//绑定套接字到地址和端口
	err = bind(addr_, port_);

	if (err)
	{
		OutputError(err, ("bind error: %s %s:%d"), server_name_, host_, port_);
		return false;
	}

	//监听
	err = listen();

	if (err)
	{
		OutputError(err, ("无法在%s:%d端口监听%s服务"), host_, port_, server_name_);
		return false;
	}

	//调用启动函数
	if (!DoStartup())
	{
		return false;
	}

	//启动接受连接的线程
	accept_stoped_ = false;
	bool ret = true;
#ifdef _MSC_VER
	accept_thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerSocketAcceptThreadRoutine, this, 0, NULL);
	if (!accept_thread_)
	{
		ret = false;
	}
#else
	if (pthread_create(&accept_thread_, NULL, ServerSocketAcceptThreadRoutine, this))
		ret = false;
#endif
	
	if (!ret)
	{
		OutputError(errno, ("CreateThread error : %s"), server_name_);
		return false;
	}

	accept_exit_ = false;
	ret = true;
#ifdef _MSC_VER
	//启动数据处理线程
	client_thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerSocketDataThreadRoutine, this, 0, NULL);

	if (!client_thread_)
	{
		ret = false;
	}
#else
	if (pthread_create(&client_thread_, NULL, ServerSocketDataThreadRoutine, this))
		ret = false;
#endif
	if (!ret)
	{
		OutputError(errno, ("CreateThread error : %s"), server_name_);
		return false;
	}
	srv_exit_ = false;
	return true;
}

void ServerSocket::Stop()
{
	srv_stoped_ = true;
	accept_stoped_= true;

	// 等待线程的结束，其实用pthread_join也是可以的
	while (!accept_exit_)
	{
		Sleep(10);
	}

	while (!srv_exit_)
	{
		Sleep(10);
	}
#ifdef _MSC_VER
	CloseThread(client_thread_);
	CloseThread(accept_thread_);
#endif

	if (socket_ != INVALID_SOCKET)
		Close();
	DoStop();
}

