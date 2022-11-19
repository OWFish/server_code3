#include "StdAfx.h"
#include "kuangsystem.h"
#include "actor/actor.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_data_mgr.h"

void CreateKuangData(Actor* tar, int src_id)
{
	Actor* src = GetGameEngine()->GetEntityMgr()->GetActorPtrById(src_id);
	if (src == NULL || !src->IsInited() || src->IsImage()) return;

	ActorPacket AP;
	DataPacket& pack = src->AllocPacket(AP);
	pack << (uint8_t)Protocol::CMD_Kuang;
	pack << (uint8_t)Protocol::sKuang_UpdateActorData;

	pack << (short)tar->GetLevel();
	pack << (short)tar->GetBasicData()->zhuansheng_lv;
	pack.writeString(tar->GetEntityName());

	if (!tar->CreateCloneData(pack))
		AP.rollBack();
	else {
		pack << int(tar->GetTogeLv());
		pack << int(tar->GetPrestigeExp());
		AP.flush();
	}
}

void KuangHelper::CreateKuangActorData(Actor* actor, int tactorId)
{
	if (actor->IsImage())
		return;

	OutputMsg(rmTip, "CreateKuangActorData tactorId %d", tactorId);

	ActorAsynFunc func = std::bind(CreateKuangData, std::placeholders::_1, actor->GetActorId());
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(tactorId, func);
}
