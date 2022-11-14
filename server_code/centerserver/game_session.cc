#include "stdafx.h"
#include "InterServerComm.h"

using namespace SrvDef;
using namespace InterSrvComm::CenterProto;

GameSession::GameSession(void) : NetSession("GameSession")
{
}

GameSession::GameSession(CenterServer* srv, SOCKET sock, sockaddr_in* addr) : NetSession("CenterServer")
{
	this->srv_ = srv;
	this->SetClientSocket(sock, addr);
}

GameSession::~GameSession(void)
{
}

bool GameSession::OnValidateRegData(const SrvDef::PSERVER_REGDATA regData)
{
	//游戏服和db能够登陆
	bool ret = (regData && regData->GameType == SERVER_REGDATA::GT_ID &&
	            regData->ServerType == T_GameServer);

	if (!ret) return ret;

	int sid = regData->ServerIndex;
	GameSession* cli = srv_->GetGameSession(sid);

	if (cli)
	{
		// 重复的连接？？
		cli->Close();
		srv_->RemoveClientId(sid);
	}

	srv_->AddNewGameSession(sid, this);
	return ret;
}

void GameSession::OnRun()
{

}

void GameSession::OnRecv(const uint16_t cmd, char* buf, int size)
{
	// 转发信息给其他gameworld
	switch (cmd)
	{
	case cwComm:
		{
			srv_->SendToGameworld(getClientServerIndex(), buf, size);
			break;
		}

	case cwActorOnline:
		{
			srv_->HandleActorOnline(getClientServerIndex(), buf, size);
			break;
		}

	case cwActorServer:
		{
			srv_->SendToActorServer(getClientServerIndex(), buf, size);
			break;
		}
	}
}

void GameSession::Disconnected()
{
	int sid = getClientServerIndex();
	GameSession* cli = srv_->GetGameSession(sid);

	if (cli)
	{
		srv_->RemoveClientId(sid);
	}

	NetSession::Disconnected();
}

