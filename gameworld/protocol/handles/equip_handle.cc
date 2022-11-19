#include "StdAfx.h"
#include "net_handle_base.h"
#include <vector>

#include "entity/entity_mgr.h"
#include "protocol/protos/equip_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "item/item.h"
#include "item/container/equip_bag.h"
#include "item/equip/equip_system.h"
#include "entity/role/role_system.h"


void OnReqEquip(Actor* actor, DataPacketReader& pack)
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

	Role *role = actor->GetRoleSystem()->GetRoleById(0);
	if (role)
	{
		int equiptype = item->GetEquipType();
		if (equiptype == EquipType_Normal)
		{
			role->GetEquipSystem()->EquipItem(item, pos);
		}
		else if (equiptype == EquipType_God)
		{
			role->GetEquipSystem()->EquipGodItem(item, pos);
		}
		else
		{
			OutputMsg(rmWarning, "非法请求装备，装备类型不存在.ItemID : %d , ItemType : %d ", item->GetId(), equiptype);
		}
	}	
}

void OnTakeOutEquip(Actor* actor, DataPacketReader& pack)
{
	if (!actor) return;
	int equiptype;
	int pos;
	pack >> equiptype >> pos;

	Role *role = actor->GetRoleSystem()->GetRoleById(0);
	if (role)
		role->GetEquipSystem()->TakeOutEquip(equiptype,pos);
}

void OnReqEquipSmelt(Actor* actor, DataPacketReader& pack)
{
	int type;
	int count;
	pack >> type;
	pack >> count;

	if (!actor) return;
	if (count <= 0) return;

	int64_t uid;
	std::vector<int64_t> itemIdList;
	for (int i = 1; i <= count; ++i)
	{
		pack >> uid;
		itemIdList.push_back(uid);
	}

	EquipBag *equipBag = actor->GetEquipBag();
	if (equipBag)
		equipBag->OnEquipSmelt(type, itemIdList);
}

void OnEquipLevelup(Actor* actor, DataPacketReader& pack)
{
	short roleId, slot;
	pack >> roleId >> slot;

	Role *pRole = actor->GetRoleSystem()->GetRoleById(roleId);
	if (!pRole) return;

	pRole->GetEquipSystem()->EquipLevelup(slot);
}

void OnEquipCompose(Actor* actor, DataPacketReader& pack)
{
	short roleId, slot;
	int itemId;
	pack >> roleId >> itemId >> slot;

	Role *pRole = actor->GetRoleSystem()->GetRoleById(roleId);
	if (!pRole) return;

	pRole->GetEquipSystem()->EquipCompose(itemId, slot);
}



void NetHandle::RegEquipCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Equip, Protocol::cEquipCmd_ReqEquipItem, OnReqEquip);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Equip, Protocol::cEquipCmd_ReqEquipSmelt, OnReqEquipSmelt);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Equip, Protocol::cEquipCmd_ReqLevelup, OnEquipLevelup);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Equip, Protocol::cEquipCmd_ReqCompose, OnEquipCompose);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Equip, Protocol::cEquipCmd_ReqTakeOutEquip, OnTakeOutEquip);
}