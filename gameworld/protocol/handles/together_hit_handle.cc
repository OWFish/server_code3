#include "StdAfx.h"
#include "net_handle_base.h"

#include "entity/entity_mgr.h"
#include "protocol/protos/equip_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "item/item.h"
#include "item/container/equip_bag.h"
#include "togetherhit/together_hit_system.h"
#include "entity/role/role_system.h"


void OnReqTogetherHitEquip(Actor* actor, DataPacketReader& pack)
{
	int64_t uid;
	short pos;
	pack >> uid >> pos;

	Equip* item = (Equip*)actor->GetEquipBag()->GetItem(uid);
	if (item == NULL)
	{
		OutputMsg(rmWarning, "非法请求装备物品，物品不存在.actor:%d", actor->GetActorId());
		return;
	}

	actor->GetTogetherHitSystem()->EquipTogetherHitItem(item, pos);
}

void NetHandle::ReqTogetherHitCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Skill, Protocol::cSkillCmd_TogetherHitEquipItem, OnReqTogetherHitEquip);
}