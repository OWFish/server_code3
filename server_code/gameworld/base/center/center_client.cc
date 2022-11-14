#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace SrvDef;
using namespace InterSrvComm;
using namespace InterSrvComm::CenterProto;


CenterClient::CenterClient(GameServer* srv) : NetClient("CenterClient")
{
	game_server_ = srv;
	SetClientName(("center server"));
	free_.setLock(&lock_);
}

CenterClient::~CenterClient()
{
	free_.flush();

	for (int i = 0; i < free_.count(); i++)
	{
		DataPacket* dp = free_[i];
		dp->setPosition(0);
		Flush(*dp);
	}

	free_.clear();
}


void CenterClient::OnRecv(const uint16_t cmd, char* buf, int size)
{
	if (cmd <= 0) return; //是心跳包

	DataPacket* pack = AllocPostPacket();

	pack->writeBuf(buf, size);

	GameInterMsg msg;
	msg.msg_id_ = SSM_CENTER_DATA;
	msg.data_.cmd_ = cmd;
	msg.data_.packet_ = pack;
	pack->setPosition(0);

	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

int CenterClient::GetLocalServerType()
{
	return T_GameServer;
}

const char* CenterClient::GetLocalServerName()
{
	return game_server_->getServerName();
}

int CenterClient::GetLocalServerIndex()
{
	return serverId_;
}

void CenterClient::OnConnected()
{
		
}


void CenterClient::FreeBackUserDataPacket(DataPacket* pack)
{
	free_.append(pack);
}

DataPacket* CenterClient::AllocPostPacket()
{
	if (free_.count() <= 0)
	{
		free_.flush();
	}

	if (free_.count() <= 0)
	{
		AllocSendPack(&free_, 512);
	}

	DataPacket* dp = free_.pop();	//得到一个空闲的Datapacket
	dp->setLength(0);
	return dp;
}


