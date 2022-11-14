#include "StdAfx.h"
#include "net_handle_base.h"

#include "entity/entity_mgr.h"
#include "protocol/protos/equip_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "item/item.h"
#include "item/container/equip_bag.h"
#include "wing/wing_system.h"
#include "entity/role/role_system.h"


void OnReqWingEquip(Actor* actor, DataPacketReader& pack)
{
	int64_t uid;
	short roleid;
	short pos;
	pack >> uid >> roleid >> pos;

	Equip* item = (Equip*)actor->GetEquipBag()->GetItem(uid);
	if (item == NULL)
	{
		OutputMsg(rmWarning, "非法请求装备物品，物品不存在.actor:%d", actor->GetActorId());
		return;
	}

	//Role *role = actor->GetRoleSystem()->GetRoleById(roleid);
	//if (role)
		//role->GetWingSystem()->EquipWingItem(item, pos);
}

void NetHandle::ReqWingCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Wing, Protocol::cWingCmd_ReqEquipItem, OnReqWingEquip);
}