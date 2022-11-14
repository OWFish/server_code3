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
#include "net/asyn_work_socket.h"
#include "net/asyn_client_socket.h"
#include "server_def.h"

AsynClientSocket::AsynClientSocket(const char* name)
	: Inherited(name)
{
	host_[0] = 0;
	port_ = 0;
	client_name_[0] = 0;
	reconn_t_ = 0;

#ifdef _MSC_VER
	handle_ = NULL;
	recv_handle_ = NULL;
#endif
	exit_ = true;
	recv_exit_ = true;
	stoped_ = true;
	recv_stoped_ = true;
}

AsynClientSocket::~AsynClientSocket()
{
	Stop();
}

void AsynClientSocket::SingleRun()
{
	//连接到服务器
	if (!connected())
		ConnectToServer();

	Inherited::SingleRun();

	//发送保持连接消息
	if (connected())
	{
		if (NOW_T - last_msg_t_ >= 10)
		{
			SendKeepAlive();
		}
	}
}

void AsynClientSocket::Connected()
{
	Inherited::Connected();
	OutputMsg(rmTip, ("%s connect ok"), client_name_);
	SendRegisteClient();
}

void AsynClientSocket::Disconnected()
{
	Inherited::Disconnected();
	OutputMsg(rmWarning, ("%s disconnected"), client_name_);
}

void AsynClientSocket::SocketError(int errorCode)
{
	Inherited::SocketError(errorCode);
	OutputError(errorCode, ("%s socket error"), client_name_);
}

void AsynClientSocket::OnWorkThreadStart()
{
}

void AsynClientSocket::OnWorkThreadStop()
{
}

void AsynClientSocket::SetClientName(const char* sClientName)
{
	_STRNCPY_A(client_name_, sClientName);
}

bool AsynClientSocket::ConnectToServer()
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
			OutputError(err, ("createSocket fail:%s"), client_name_);
			return false;
		}

		socket_ = sock;
		//调整发送和接收缓冲大小
		err = setSendBufSize(32 * 1024);

		if (err)
		{
			OutputError(err, ("setSendBufSize fail:%s"), client_name_);
			return false;
		}

		err = setRecvBufSize(1024 * 1024);

		if (err)
		{
			OutputError(err, ("setRecvBufSize fail:%s"), client_name_);
			return false;
		}
	}

	if (now_t >= reconn_t_)
	{
		reconn_t_ = now_t + 5;
		int err = connect(addr_, port_, false);

		if (err)
		{
			OutputError(err, ("connect fail:%s"), client_name_);
			return false;
		}

		//调整为非阻塞模式
		err = setBlockMode(false);

		if (err)
		{
			OutputError(err, ("setBlockMode fail:%s"), client_name_);
			return false;
		}

		last_msg_t_ = NOW_T;
		return true;
	}

	return false;
}

void AsynClientSocket::SendRegisteClient()
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
void STDCALL AsynClientSocket::Recv_R(AsynClientSocket* ptr)
#else
void* AsynClientSocket::Recv_R(void* ptr)
#endif
{
	AsynClientSocket* client = (AsynClientSocket*)ptr;

	while (!client->recv_stoped_)
	{
		if (!client->ReadSocket())
			Sleep(1);
	}

	if (client->connected())
	{
		client->Close();
	}

	client->recv_exit_ = true;

#ifdef _MSC_VER
	//ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}


#ifdef _MSC_VER
void STDCALL AsynClientSocket::Work_R(AsynClientSocket* ptr)
#else
void* AsynClientSocket::Work_R(void* ptr)
#endif
{
	AsynClientSocket* client = (AsynClientSocket*)ptr;

	client->OnWorkThreadStart();

	while (!client->stoped_)
	{
		client->SingleRun();

		Sleep(1);
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

void AsynClientSocket::SetHost(const char* hostName)
{
	_STRNCPY_A(host_, hostName);

	hostent* host = gethostbyname(hostName);

	if (host)
	{
		addr_ = *(u_long*)host->h_addr_list[0];
	}
}

void AsynClientSocket::SetPort(const int port)
{
	port_ = port;
}

bool AsynClientSocket::Startup()
{
	stoped_ = false;
	recv_stoped_ = false;

	bool ret = true;
	int err = 0;

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
		OutputError(err, ("%s,AsynClientSocket create work thread fail"), client_name_);
		return ret;
	}

	exit_ = false;

	ret = true;
	recv_stoped_ = false;
#ifdef _MSC_VER
	recv_handle_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Recv_R, this, 0, &recv_thread_id_);

	if (!recv_handle_)
	{
		err = GetLastError();
		ret = false;
	}

#else

	if (pthread_create(&recv_thread_id_, NULL, Recv_R, this))
	{
		err = errno;
		ret = false;
	}

#endif

	if (!ret)
	{
		OutputError(err, ("%s,AsynClientSocket create recv thread fail"), client_name_);
		return false;
	}

	recv_exit_ = false;
	return true;
}

void AsynClientSocket::Stop()
{
	stoped_ = true;
	recv_stoped_ = true;
	while (!recv_exit_)
	{
		Sleep(10);
	}
	while (!exit_)
	{
		Sleep(10);
	}

#ifdef _MSC_VER
	CloseThread(handle_);
#endif
	ClearSendBuffers();

#ifdef _MSC_VER
	CloseThread(recv_handle_);
#endif
}

int AsynClientSocket::GetLocalServerIndex()
{
	return 0;
}
