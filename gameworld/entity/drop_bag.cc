#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "item/container/equip_bag.h"
#include "item/item_config.h"

DropBag::DropBag()
{
	type_ = 0;
	id_ = 0;
	count_ = 0;
	//flag_ = false;
	belong_id_ = 0;
	belong_invalid_time_ = 0;
	destroy_time_ = 0;
}

void DropBag::LogicRun(int64_t curr_t)
{
	if (belong_invalid_time_ && belong_invalid_time_ < curr_t)
	{
		belong_invalid_time_ = 0;
		belong_id_ = 0;
	}
	//这里就销毁自己了;尽量放最后面
	if (destroy_time_ < curr_t)
	{
		static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		em->DestroyEntity(GetHandle());
		return;
	}
}

int DropBag::GetId()
{
	return 0;
}

bool DropBag::GetDrop(Actor *actor)
{
	if (!actor) return false;
	if (type_ == AwardType_Numeric) {
		actor->ChangeCurrency(id_, count_, "drop bag");
	} else if (type_ == AwardType_Item) {
		int get_count = actor->GiveItem(id_, count_, "drop bag");
		if (get_count < count_) {
			count_ -= get_count;
			return false;
		}
	}
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	em->DestroyEntity(GetHandle());
	return true;
}

bool DropBag::CanGetDrop(Actor *actor)
{
	if (!actor) return false;
	if (type_ == AwardType_Numeric) return true;
	auto conf = ItemConfigPool::GetItemConfig(id_);
	if (!conf) return false;
	if (!conf->isEquip()) return true;
	return actor->GetEquipBag()->Spaces() >= count_;
}

void DropBag::CreateAppearData(DataPacket& appearPack)
{
	Entity::CreateAppearData(appearPack);
	appearPack << type_ << id_ << count_;
}
