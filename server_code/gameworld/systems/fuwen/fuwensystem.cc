#include "StdAfx.h"
#include "actor/actor.h"
#include "fuwensystem.h"
#include "db/actor_db_data.h"
#include "item/item_pool.h"
#include "item/item.h"
#include "item/container/item_bag.h"
#include "item/equip/equip.h"
#include "item/container/equip_bag.h"



FuWenSystem::FuWenSystem(Role* role)
	: role_(role)
	, fuwendata_()
	, fuwen_()
{

}

FuWenSystem::~FuWenSystem()
{
	for (int i = 0; i < MAX_FUWEN; ++i)
	{
		SafeDelete(fuwen_[i]);
	}
}



void FuWenSystem::Save()
{

}

void FuWenSystem::Destroy()
{
}

bool FuWenSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;
	fuwendata_ = &data->fuwen_data;

	for (int i = 0; i < MAX_FUWEN; ++i)
	{
		ItemData *item_data = &(fuwendata_->fuwen_slot[i]);
		if (item_data->uid != 0)
		{
			fuwen_[i] = ItemPool::instance().CreateItem(item_data);
		}
	}
	return true;
}

void FuWenSystem::SetEquipFuwen(int posid, int64_t uid)
{
	if (posid < 0  || posid >= MAX_FUWEN)
		return;
	auto actor = role_->GetActor();
	Item* item = (Item*)(actor->GetItemBag()->GetItem(uid));
	if (!item) {
		//Ð¶ÏÂ·ûÎÄ
		Item* old = fuwen_[posid];
		if (old && actor->GiveItem(old->GetId(), 1, "unloadFw", false) > 0){
			SafeDelete(fuwen_[posid]);
			fuwendata_->fuwen_slot[posid].id = 0;
			fuwendata_->fuwen_slot[posid].uid = 0;
			fuwendata_->fuwen_slot[posid].count = 0;
		}
		return;
	}
	if (ItemType_FuWen != item->GetType())
		return;

	Item* old = fuwen_[posid];
	if (old)
	{
		actor->GiveItem(old->GetId(), 1, "equipFw", false);
	}
	else
	{
		Item* newItem = ItemPool::instance().CreateItem(item->GetId(), 1);
		if (!newItem)
			return;
		fuwen_[posid] = newItem;
	}

	item->WriteData((fuwen_[posid]->GetItemDataPtr()));
	item->WriteData(&(fuwendata_->fuwen_slot[posid]));
	auto item_bag = actor->GetItemBag();
	item_bag->CostItem(uid, 1);
}

void FuWenSystem::FuwenLevelup(int posid, int itemId)
{
	if (posid < 0 || posid >= MAX_FUWEN)
		return;

	Item* old = fuwen_[posid];
	if (!old)
		return;

	Item* item = ItemPool::instance().CreateItem(itemId, 1);
	if (!item) return;

	if (item->GetType() != ItemType_FuWen)
	{
		delete item;
		return;
	}

	delete old;
	fuwen_[posid] = item;
	item->WriteData(&(fuwendata_->fuwen_slot[posid]));
}

const FuWenData* FuWenSystem::GetFuWenData()
{
	return fuwendata_;
}

Item* FuWenSystem::GetFuWenItemByPos(int posid) const
{
	if (posid < 0 || posid >= MAX_FUWEN)
		return 0;
	return fuwen_[posid];
}

void FuWenSystem::ClearAttr()
{
	attribute_.Reset();
	ex_attribute_.Reset();
}

void FuWenSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void FuWenSystem::AddExAttr(int type, int value)
{
	ex_attribute_.Add(type,value);
}




