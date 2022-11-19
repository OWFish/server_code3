#include "StdAfx.h"
#include "netmsg_dispatcher.h"


using namespace Protocol;

static NetMsgHandle s_net_msg_handles[256][256] = { 0 };

void ScriptNetMsgHandle(Actor* actor, DataPacketReader& pack)
{
	static ScriptNpc* gp = GetGameEngine()->GetGlobalNpc();
	ScriptValueList plist;
	uint8_t* buf = (uint8_t*)pack.getMemoryPtr();
	plist << (int)buf[0];
	plist << (int)buf[1];;
	plist << actor;
	plist << &pack;

	bool ret = gp->GetScript().Call("OnNetMsg", &plist, NULL);
	if (!ret)
	{
		//脚本错误，将以模态对话框的形式呈现给客户端
		const RefString& s = gp->GetScript().getLastErrorDesc();
		if (actor) actor->SendTipmsg((const char*)s, ttDialog);
	}
	return;
}

bool NetMsgDispatcher::ProcessNetMsg(Actor* actor, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack)
{
	if (sys_id > 255 || cmd_id > 255) return false;
	if (s_net_msg_handles[sys_id][cmd_id])
	{
		DataPacketReader dp(pack.getOffsetPtr(), pack.getAvaliableLength());
		dp.adjustOffset(2); //去掉协议
		s_net_msg_handles[sys_id][cmd_id](actor, dp);
		return true;
	}

	return false;
}

bool NetMsgDispatcher::RegistNetMsgHandle(int sys_id, int cmd_id, NetMsgHandle func)
{
	if (sys_id < 0 || sys_id > 255 || cmd_id < 0 || cmd_id > 255)
	{
		OutputMsg(rmError, "RegisterNetMsgHandle error. (%d,%d)", sys_id, cmd_id);
		return false;
	}
	s_net_msg_handles[sys_id][cmd_id] = func;

	return true;
}

bool NetMsgDispatcher::RegisterScriptMsg(int sysId, int cmdId)
{
	return RegistNetMsgHandle(sysId, cmdId, ScriptNetMsgHandle);
}
