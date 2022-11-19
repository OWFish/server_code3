#ifdef _MSC_VER
#include <Windows.h>  
#include <process.h>  
#else  
#include <pthread.h>  
#endif  
#include "StdAfx.h"
#include "socket_srv.h"


SocketSrv::SocketSrv() {
	srv_stoped_ = true;
	memset(server_name_, 0, sizeof(server_name_));
#ifdef _MSC_VER  
	accept_thread_ = NULL;
#else  
	accept_thread_ = 0;
#endif  
	accept_exit_ = true;
}


SocketSrv::~SocketSrv()
{
#ifdef _MSC_VER  
	if (NULL != accept_thread_)	{
		CloseHandle(accept_thread_);
	}
	accept_thread_ = NULL;
#else  
	accept_thread_ = 0;
#endif  
}
#ifdef _MSC_VER
void STDCALL SocketSrv::ServerSocketAcceptThreadRoutine(void* arg) {
#else
void * SocketSrv::ServerSocketAcceptThreadRoutine(void * arg) {
#endif
	SocketSrv *srv = (SocketSrv*)arg;
	struct sockaddr_in server_addr;
	SOCKET listen_fd_ = 0;
	if ((listen_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
		MSG_ERR("create socket error:%d",errno);
		assert(false);
	}
#ifdef _MSC_VER
	char optval = 1;
#else
	int optval = 1;
#endif
	if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == SOCKET_ERROR) {
		MSG_ERR("setsockopt");
		assert(false);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(srv->GetServicePort());
	server_addr.sin_addr.s_addr = inet_addr(srv->GetServiceHost());
	memset(server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));

	if (::bind(listen_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		MSG_ERR("bind error");
		assert(false);
	}
	if (listen(listen_fd_, 5) == SOCKET_ERROR) {
		MSG_ERR("listen error");
		assert(false);
	}
	socklen_t len = sizeof(sockaddr);
	do {
		sockaddr_in cli_addr;
		SOCKET nSocket = accept(listen_fd_, (sockaddr*)&cli_addr, &len);
		if (srv->Started() && !srv->onConnect(nSocket, &cli_addr)) {
			closesocket(nSocket);
		}
	} while (srv->Started());
	closesocket(listen_fd_);
	srv->accept_exit_ = true;
#ifdef _MSC_VER
	ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

void SocketSrv::SetServiceName(const char * sName)
{
	_STRNCPY_A(server_name_, sName);
}

void SocketSrv::SetServiceHost(const char * sHost)
{
	_STRNCPY_A(host_, sHost);
}

void SocketSrv::SetServicePort(const int nPort) {
	port_ = nPort;
}

bool SocketSrv::Startup() {
	Inherited:Start();
	bool ret = true;
	int err = 0;
	srv_stoped_ = false;
#ifdef _MSC_VER
	accept_thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerSocketAcceptThreadRoutine, this, 0, NULL);
	if (!accept_thread_) {
		err = GetLastError();
		ret = false;
	}
#else

	if (pthread_create(&accept_thread_, NULL, ServerSocketAcceptThreadRoutine, this)) {
		err = errno;
		ret = false;
	}

#endif

	if (!ret)  {
		MSG_ERR("create listen thread error %d", err);
		return false;
	}
	accept_exit_ = false;
	return true;
}

void SocketSrv::Stop() {
	if (srv_stoped_) return;
	MSG_LOG("start");
	srv_stoped_ = true;
//	while (!accept_exit_) {
//		Sleep(1);
//	}
//#ifdef _MSC_VER
//	CloseThread(accept_thread_);
//#endif
	Inherited::Stop();
	MSG_LOG("ok");
}

void SocketSrv::OnRoutine() {
	OnStart();
	while (!terminated()) {
		if (Run() <= 0)
			Sleep(1);
	}
	OnStop();
}
