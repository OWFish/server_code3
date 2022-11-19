#include "StdAfx.h"
#include "net_handle_base.h"

#include "entity/entity_mgr.h"
#include "protocol/protos/base_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "actor/actor_data_mgr.h"
#include "actor/actor_asyn_mgr.h"
#include "role/role_system.h"
#include "systems/move/move_system.h"
#include "systems/guild/guild_system.h"


void OnReqTime(Actor* actor, DataPacketReader& pack)
{
	static Protocol::SyncTimeProto msg;
	msg.time = GetGameEngine()->getMiniDateTime();
	actor->SendData(msg);
}

void getActorInfo(Actor* tar, int src_id)
{
	ActorPacket AP;
	Actor *src = GetGameEngine()->GetEntityMgr()->GetActorPtrById(src_id);
	if (!src || !src->IsInited() || src->IsImage())
		return;

	DataPacket& pack = src->AllocPacket(AP);

	pack << (uint8_t)Protocol::CMD_Base;
	pack << (uint8_t)Protocol::sBaseCmd_ResActorInfo;
	tar->putActorInfo2Pack(pack);

	AP.flush();
}

void OnReqActorInfo(Actor* actor, DataPacketReader& pack)
{
	int tarid, tarservid;
	int srcid = actor->GetActorId();
	pack >> tarid;
	pack >> tarservid;
	if (tarservid && tarservid != ServerInstance()->GetServerIndex())
	{
		ScriptValueList arg;
		arg << actor;
		arg << tarservid;
		arg << tarid;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("GetOtherSrvActorDetail", &arg, &arg, 1);
		return;
	}
	ActorAsynFunc func = std::bind(getActorInfo, std::placeholders::_1, srcid);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(tarid, func);
}

void OnHeartBeat(Actor* actor, DataPacketReader& pack)
{
}

void OnRecvFubenMoveLine(Actor* actor, DataPacketReader& pack)
{
	if (!actor)
	{
		return;
	}

	int64_t handle = 0;
	pack >> handle;




	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Entity* et = em->GetEntity(handle);
	if (et)
	{
		if (!et->IsCreature())
		{
			return;
		}
		Creature* cte = (Creature*)et;
		cte->ClearMoveLine();
		auto fb = cte->GetFuBen();
		if (!fb || fb->IsEnd()) {
			return;
		}
		int len = 0;
		pack >> len;

		//简单做个限制，防止前端发个无穷大数
		if (len > 64) len = 64;

		for (int i = 0; i < len; ++i)
		{
			int x = 0;
			pack >> x;
			int y = 0;
			pack >> y;
			Point point(x, y);
			//OutputMsg(rmTip, "actor:%d, handle:%ld, OnRecvFubenMoveLine, x:%d,y:%d", actor->GetActorId(), handle, x, y);
			cte->AddMoveLine(point);
		}
		cte->GetMoveSystem()->StartFubenPathToTarget();
	}
}

void OnSetSendPackList(Actor* actor, DataPacketReader& pack) {
	if (!actor) { return; }
	short count = 0;
	pack >> count;
	if (count < 0) {
		actor->ClearPackHideSet();
	} else {
		actor->need_hide_pack_ = true;
		actor->need_pack_list_.clear();
		while (count > 0) {
			int64_t handle = 0;
			pack >> handle;
			if (handle) {
				actor->need_pack_list_.insert(handle);
			}
			--count;
		}
	}
}

void NetHandle::RegBaseCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Base, Protocol::cBaseCmd_ReqTime, OnReqTime);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Base, Protocol::cBaseCmd_GetActorInfo, OnReqActorInfo);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Base, Protocol::cBaseCmd_HeartBeat, OnHeartBeat);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Base, Protocol::cBaseCmd_GetFubenMoveLine, OnRecvFubenMoveLine);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Base, Protocol::cBaseCmd_SetSendPackList, OnSetSendPackList);
}