#include "stdafx.h"

using namespace SrvDef;

void OnBlockClient(void* ptr)
{
	//if (ptr)
	//{
	//	LoggerServer* srv = (LoggerServer*)ptr;
	//	srv->GetSqlConnection()->Disconnect();
	//}
	LoggerSession* session = (LoggerSession*)ptr;
	printf("onBlock watch_id = %d\n", session->GetWatchId());
	//abort();
}

LoggerSession::LoggerSession(void) : NetSession("LoggerClient")
{
	//watch_id_ = wrand(1000000);
	//WatchThread* watch = GetWatch();
	//if (watch) watch->AddWatch(watch_id_, 120, &OnBlock, this);
}

LoggerSession::LoggerSession(LoggerServer* pSrv, SOCKET nSocket, sockaddr_in* pClientAddr) : NetSession("LoggerClient")
{
	this->srv_ = pSrv;
	this->db_ = pSrv->GetSqlConnection();
	this->SetClientSocket(nSocket, pClientAddr);

	if (pSrv)
	{
		watch_id_ = wrand(1000000);
		WatchThread* watch = pSrv->GetWatch();

		if (watch)
		{
			printf("addWatch %d\n", watch_id_);
			watch->AddWatch(watch_id_, 120000, &OnBlockClient, this);
		}
	}

	report_t_ = 0;
}

LoggerSession::~LoggerSession(void)
{
	if (this->srv_)
	{
		WatchThread* watch = this->srv_->GetWatch();

		if (watch)
		{
			printf("removeWatch %d\n", watch_id_);
			watch->RemoveWatch(watch_id_);
		}
	}
}

bool LoggerSession::OnValidateRegData(const SrvDef::PSERVER_REGDATA regData)
{
	//游戏服和db能够登陆
	return (regData && regData->GameType == SERVER_REGDATA::GT_ID &&
	        regData->ServerType == T_GameServer);
}

void LoggerSession::OnRun()
{
	time_t now_t = NOW_T;

	if (this->srv_)
	{
		if (now_t > report_t_)
		{
			report_t_ = now_t + 30;
			WatchThread* watch = this->srv_->GetWatch();

			if (watch)
			{
				printf("Report watchid %d\n", watch_id_);
				watch->Report(watch_id_);
			}
		}
	}
}

void LoggerSession::OnRecv(const uint16_t cmd, char* buf, int size)
{
	srv_->PostLogPacket(getClientServerIndex(), cmd, buf, size);
}

void LoggerSession::Disconnected()
{
	NetSession::Disconnected();
}

