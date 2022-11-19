#include "StdAfx.h"
#include "lf_netmsg_mgr.h"


static NetMsgDealFunc g_net_msg_deal[CMD_MAX_COUNT][SUBCMD_MAX_COUNT] = { 0 };

STATIC_ASSERT(CMD_MAX_COUNT > 255 && SUBCMD_MAX_COUNT > 255)

LFNetmsgMgr::LFNetmsgMgr()
{
	ZeroMemory(g_net_msg_deal, sizeof(g_net_msg_deal));
	/*g_net_msg_deal[enRankingSystemID][cRankData] = (NetMsgDealFunc)&DbRankMgr::SendRankData;
	g_net_msg_deal[enRankingSystemID][cRankUser] = (NetMsgDealFunc)&DbRankMgr::SendRankUser;
	g_net_msg_deal[enRankingSystemID][cRankSelf] = (NetMsgDealFunc)&DbRankMgr::SendRankSelf;
	g_net_msg_deal[enRankingSystemID][cRankTop] = (NetMsgDealFunc)&DbRankMgr::SendRankTop;
	g_net_msg_deal[enRankingSystemID][cMixedRankData] = (NetMsgDealFunc)&DbRankMgr::SendMixedRankData;
	*/
}

LFNetmsgMgr::~LFNetmsgMgr()
{

}


void HandleScriptMsg(ActorId sActorId, DataPacketReader& reader, Actor* srcActor)
{
	uint8_t* buf = (uint8_t*)reader.getMemoryPtr();
	ScriptValueList paramList;
	paramList << (int)buf[0];
	paramList << (int)buf[1];
	paramList << &reader;
	paramList << (int)sActorId;
	paramList << (void*)srcActor;

	static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();

	if (pNpc == NULL) return;

	if (!pNpc->GetScript().Call("OnLFNetmsg", &paramList, &paramList))
	{
		//脚本错误，将以模态对话框的形式呈现给客户端
		const RefString& s = pNpc->GetScript().getLastErrorDesc();
		static GameEngine* ge = GetGameEngine();
		ge->SendTipmsg(sActorId, (const char*)s, ttDialog);
	}
}

void LFNetmsgMgr::RegisterScriptMsg(int sysId, int cmdId)
{
	RegistNetMsgDealFunc(sysId, cmdId, HandleScriptMsg);
}

bool LFNetmsgMgr::ProcessActorNetmsg(ActorId actor_id, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack, Actor* srcActor)
{
	//检查用哪个逻辑处理, 这里不判断sys_id和cmd_id的范围，不会大于255
	if (g_net_msg_deal[sys_id][cmd_id])
	{
		DataPacketReader dp(pack.getOffsetPtr(), pack.getAvaliableLength());
		dp.adjustOffset(2); //去掉协议
		g_net_msg_deal[sys_id][cmd_id](actor_id, dp, srcActor);
		return true;
	}

	return false;
}


int LFNetmsgMgr::RegistNetMsgDealFunc(int sys_id, int cmd_id, NetMsgDealFunc func)
{
	if (sys_id < 0 || sys_id >= CMD_MAX_COUNT || cmd_id < 0 || cmd_id >= SUBCMD_MAX_COUNT)
	{
		return -1;
	}
	g_net_msg_deal[sys_id][cmd_id] = func;

	if (!func)
	{
		OutputMsg(rmTip, " sysid %d, cmd_id %d, func is NULL!", sys_id, cmd_id);
	}
	return 0;
}

int LFNetmsgMgr::UnregistNetMsgDealFunc(int sys_id, int cmd_id)
{
	if (sys_id < 0 || sys_id >= CMD_MAX_COUNT || cmd_id < 0 || cmd_id >= SUBCMD_MAX_COUNT)
	{
		return -1;
	}

	g_net_msg_deal[sys_id][cmd_id] = NULL;

	return 0;
}

