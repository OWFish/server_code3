#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include <_ast.h>

#include <net/base_socket.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "os_def.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_client.h"
#include "server_def.h"

NetClient::NetClient(const char* name)
	: Inherited(name)
{
	host_[0] = 0;
	port_ = 0;
	client_name_[0] = 0;
#ifdef _MSC_VER
	handle_ = NULL;
#endif
	stoped_ = true;
	exit_ = true;
	reconn_t_ = 0;
}

NetClient::~NetClient()
{
	Stop();
}

void NetClient::OnRun()
{
	//连接到服务器
	if (!connected())
		ConnectToServer();

	//发送保持连接消息
	if (connected())
	{
		if (NOW_T - last_msg_t_ >= 10 && !IsPackBlocked())
		{
			SendKeepAlive();
		}
	}
}

void NetClient::Connected()
{
	Inherited::Connected();
	OutputMsg(rmTip, ("%s server succ"), client_name_);
	SendRegisteClient();
}

void NetClient::Disconnected()
{
	Inherited::Disconnected();
	OutputMsg(rmWarning, ("%s server disconnect!"), client_name_);
}

void NetClient::SocketError(int errorCode)
{
	Inherited::SocketError(errorCode);
	OutputError(errorCode, ("%s client socket error!"), client_name_);
}

void NetClient::OnWorkThreadStart()
{
}

void NetClient::OnWorkThreadStop()
{
}

void NetClient::SetClientName(const char* sClientName)
{
	_STRNCPY_A(client_name_, sClientName);
}

bool NetClient::ConnectToServer()
{
	//如果已连接则直接返回
	if (connected())
	{
		return true;
	}

	time_t now_t = NOW_T;

	//创建套接字
	if (getSocket() == INVALID_SOCKET)
	{
		SOCKET sock;
		int err = createSocket(&sock);

		if (err)
		{
			OutputError(err, ("create socket fail! %s "), client_name_);
			return false;
		}

		socket_ = sock;
		//调整发送和接收缓冲大小
		err = setSendBufSize(32 * 1024);

		if (err)
		{
			OutputError(err, ("setSendBufSize fail! %s "), client_name_);
			return false;
		}

		err = setRecvBufSize(1024 * 1024);

		if (err)
		{
			OutputError(err, ("setRecvBufSize fail! %s "), client_name_);
			return false;
		}
	}

	if (now_t >= reconn_t_)
	{
		reconn_t_ = now_t + 5;
		int err = connect(addr_, port_, false);

		if (err)
		{
			OutputError(err, ("connect fail! %s ip =%s port=%d"), client_name_, host_, port_);
			return false;
		}

		//调整为非阻塞模式
		err = setBlockMode(false);

		if (err)
		{
			OutputError(err, ("setBlockMode fail! %s "), client_name_);
			return false;
		}

		last_msg_t_ = NOW_T;
		return true;
	}

	return false;
}

void NetClient::SendRegisteClient()
{
	SrvDef::SERVER_REGDATA regData;

	ZeroMemory(&regData, sizeof(regData));
	regData.GameType	= SrvDef::SERVER_REGDATA::GT_ID;
	regData.ServerType	= GetLocalServerType();
	regData.ServerIndex	= GetLocalServerIndex();
	_STRNCPY_A(regData.ServerName, GetLocalServerName());
	send(&regData, sizeof(regData));
}

#ifdef _MSC_VER
void STDCALL NetClient::Work_R(NetClient* ptr)
#else
void* NetClient::Work_R(void* ptr)
#endif
{
	CheckDate();

	NetClient* client = (NetClient*)ptr;

	client->OnWorkThreadStart();

	while (!client->stoped_)
	{
		client->SingleRun();
		if (!client->busy_) client->SleepX();
	}

	if (client->connected())
	{
		client->Close();
	}

	client->OnWorkThreadStop();

	client->exit_ = true;

#ifdef _MSC_VER
	//ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

void NetClient::SetHost(const char* hostName)
{
	_STRNCPY_A(host_, hostName);

	hostent* host = gethostbyname(hostName);

	if (host)
	{
		addr_ = *(u_long*)host->h_addr_list[0];
	}
}

void NetClient::SetPort(const int nPort)
{
	port_ = nPort;
}

bool NetClient::Startup()
{
	bool ret = true;
	int err = 0;

	stoped_ = false;
#ifdef _MSC_VER
	handle_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Work_R, this, 0, &thread_id_);

	if (!handle_)
	{
		err = GetLastError();
		ret = false;
	}
#else
	if (pthread_create(&thread_id_, NULL, Work_R, this))
	{
		err = errno;
		ret = false;
	}
#endif
	if (!ret)
	{
		OutputError(err, ("创建%s通信线程失败"), client_name_);
		return false;
	}
	exit_ = false;
	return true;
}

void NetClient::Stop()
{
	stoped_ = true;
	while (!exit_)
	{
		Sleep(10);
	}
#ifdef _MSC_VER
	CloseThread(handle_);
#endif

	ClearSendBuffers();
}

int NetClient::GetLocalServerIndex()
{
	return 0;
}
