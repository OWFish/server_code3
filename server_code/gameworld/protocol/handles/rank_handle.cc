#include "StdAfx.h"
#include "net_handle_base.h"
#include "netmsg_dispatcher.h"
#include "rank/ranking_system.h"


void OnReqRankingData(Actor* actor, DataPacketReader& pack)
{
	static RankingSystem* rs = GetGameEngine()->GetRankingSystem();
	return rs->OnReqRankingData(actor, pack);
}


void NetHandle::RegRankingCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Ranking, Protocol::cRankingCmd_ReqRankingData, OnReqRankingData);
}