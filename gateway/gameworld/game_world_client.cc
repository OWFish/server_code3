#include "StdAfx.h"
#include "game_world_client.h"

GameWorldClient::GameWorldClient(GateServer* serv, GameClientMgr* gcmgr, const char* name) :
NetClient(name),
serv_(serv),
gcmgr_(gcmgr) {
	SetClientName(name);
	free_.setLock(&lock_);
}


GameWorldClient::~GameWorldClient() {
	free_.flush();

	for (int i = 0; i < free_.count(); i++)
	{
		DataPacket* dp = free_[i];
		dp->setPosition(0);
		Flush(*dp);
	}

	free_.clear();
}

void GameWorldClient::OnRecv(const uint16_t cmd, char * buf, int size) {
	
	switch (cmd) {
	case GW_DATA: {
		NetId net_id = *((NetId*)buf);
		uint8_t nsize = sizeof(NetId);
		//cli->OnGameWorldRecv(buf + nsize, size - nsize);
		DataPacket *dp = AllocPostPacket();
		dp->writeBuf(buf + nsize, size - nsize);
		dp->setPosition(0);
		GateInterMsg msg;
		msg.msg_id_ = gcGWData;
		msg.data_.index_ = net_id.index_;
		msg.data_.packet_ = dp;
		gcmgr_->PostMsg(msg);
		break;
	}
	case GW_CLOSE: {
		NetId net_id = *((NetId*)buf);
		GateInterMsg msg;
		msg.msg_id_ = gcGWClose;
		msg.data_.index_ = net_id.index_;
		gcmgr_->PostMsg(msg);
		break;
	}
	case GW_CHANNEL: {
		OnChannelMsg(buf, size);
		break;
	}
	default:
		MSG_LOG("not handle gameword cmd:%d", cmd);
		break;
	}
}

void GameWorldClient::OnChannelMsg(char* buf, int size) {
	Channel info = *((Channel*)buf);
	switch (info.type) {
	case ccBroadCast: {
		uint8_t nsize = sizeof(Channel);
		DataPacket *dp = AllocPostPacket();
		dp->writeBuf(buf + nsize, size - nsize);
		dp->setPosition(0);
		GateInterMsg msg;
		msg.msg_id_ = gcChBro;
		msg.data_.b_channel_ = info.channelId;
		msg.data_.b_para_ = info.para;
		msg.data_.dp_ = dp;
		gcmgr_->PostMsg(msg);
		break;
	}
	case ccAddUser: {
		GateInterMsg msg;
		msg.msg_id_ = gcChAdd;
		msg.data_.channel_ = info.channelId;
		msg.data_.para_ = info.para;
		msg.data_.idx_ = info.index_;
		gcmgr_->PostMsg(msg);
		break;
	}
	case ccDelUser: {
		GateInterMsg msg;
		msg.msg_id_ = gcChDel;
		msg.data_.channel_ = info.channelId;
		msg.data_.para_ = info.para;
		msg.data_.idx_ = info.index_;
		gcmgr_->PostMsg(msg);
		break;
	}
	default:
		MSG_LOG("not handle channel type:%d", info.type);
		break;
	}
}

int GameWorldClient::GetLocalServerType() {
	return SrvDef::GateServer;
}

const char * GameWorldClient::GetLocalServerName() {
	return gcmgr_->GetServiceName();
}

void GameWorldClient::OnDisconnected() {
	GateInterMsg msg;
	msg.msg_id_ = gcGWDisconn;
	gcmgr_->PostMsg(msg);
}

void GameWorldClient::FreeBackUserDataPacket(DataPacket* pack) {
	free_.append(pack);
}

DataPacket* GameWorldClient::AllocPostPacket()
{
	if (free_.count() <= 0)
	{
		free_.flush();
	}

	if (free_.count() <= 0)
	{
		AllocSendPack(&free_, 512);
	}

	DataPacket* dp = free_.pop();//得到一个空闲的Datapacket
	dp->setLength(0);
	return dp;
}
