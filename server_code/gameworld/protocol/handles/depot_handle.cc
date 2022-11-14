#include "StdAfx.h"
#include "net_handle_base.h"

#include "entity/entity_mgr.h"
#include "protocol/protos/base_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "item/container/depot_system.h"
#include "item/container/equip_bag.h"


void OnDepotPickUp(Actor* actor, DataPacketReader& pack)
{
	double uid;
	pack >> uid;
	if (Depot::OrangeEquip == uid )
		actor->GetDepot()->PickAllItem(Depot::OrangeEquip);
	else if(Depot::FuwenItem == uid)
		actor->GetDepot()->PickAllItem(Depot::FuwenItem);
	else if (Depot::Heirloom == uid)
		actor->GetDepot()->PickAllItem(Depot::Heirloom);
	else
		actor->GetDepot()->PickItemToBag(static_cast<int64_t>(uid));
}

void OnExpandCapacity(Actor* actor, DataPacketReader& pack)
{
	int row;
	pack >> row;
	actor->GetEquipBag()->OnExpandCapacity(row);
}

void NetHandle::ReqDepotCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Bag, Protocol::cBagCmd_DepotPickUp, OnDepotPickUp);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Bag, Protocol::cBagCmd_ReqExpandCapacity, OnExpandCapacity);
}