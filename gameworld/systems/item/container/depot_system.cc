#include "StdAfx.h"
#include "depot_system.h"
#include "item/item.h"
#include "protos/equip_proto.h"
#include "equip_bag.h"

Depot::Depot(Actor* actor) :ItemBag(actor)
{
	bag_type_ = BagType_Depot;
}

bool Depot::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;

	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init depot.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_Depot))
		return true;
	uint32_t curr_index = 0;
	uint32_t size = 0;
	uint32_t max_size = 0;
	data >> curr_index >> size >> max_size;

	if (max_size != 0)
	{
		if (db_buf_.size() < max_size)
		{
			db_buf_.resize(max_size);
			size_t index_size = 0;
			if (max_size != 0)
			{
				index_size = (size_t)ceil(max_size * 1.0 / PACK_LEN);
			}
			buf_index_.resize(index_size);
		}

		memcpy(&db_buf_[curr_index], data.getOffsetPtr(), data.getAvaliableLength());
		buf_index_[curr_index / PACK_LEN] = true;
	}
	auto check_buf_ok = [&](void)
	{
		for (size_t i = 0; i < buf_index_.size(); ++i)
		{
			if (!buf_index_[i])
				return false;
		}
		return true;
	};
	if (check_buf_ok())
	{
		ItemData* data = (ItemData*)&db_buf_[0];

		size_t item_size = db_buf_.size() / sizeof(*data);
		for (size_t i = 0; i < item_size; ++i)
		{
			AddItem(data + i, false);
		}
		actor_->OnFinishInitStep(Actor::InitFlagType_Depot);
		db_buf_.clear();
		buf_index_.clear();
	}
	return true;
}

void Depot::PickItemToBag(int64_t uid)
{
	Item* pItem = GetItem(uid);
	if (!pItem) return;

	if ((pItem->isEquip()) && actor_->GetEquipBag()->Spaces() <= 0)
		return;

	if (!TakeOutItem(pItem)) return;

	if (pItem->isEquip())
		actor_->GetEquipBag()->AppendItem(pItem, "depot pick up", false);
	else
	{
		actor_->GetItemBag()->AppendItem(pItem->GetId(), pItem->GetCount(), "depot pick up", false);
		delete pItem;
	}
}

void Depot::PickAllItem(int type)
{
	bool isfull = false;
	for (auto itor = item_list_.begin(); itor != item_list_.end();)
	{
		Item* pItem = *itor;
		if (type != pItem->GetBagType()) {
			itor++;
			continue;
		}
			
		if ((pItem->isEquip()) && actor_->GetEquipBag()->Spaces() <= 0)
		{
			itor++;
			isfull = true;
			continue;
		}
			
		itor = item_list_.erase(itor);

		if (pItem->isEquip())
			actor_->GetEquipBag()->AppendItem(pItem, "depot pick up", false);
		else
		{
			actor_->GetItemBag()->AppendItem(pItem->GetId(), pItem->GetCount(), "depot pick up", false);
			delete pItem;
		}
	}
	if (isfull)
		actor_->SendTipWithId(2);

	OnEnterGame();
}

bool Depot::AppendItem(int id, int count, const char* log)
{
	const ItemConfig* pItem = ItemConfigPool::GetItemConfig(id);
	if (!pItem) return false;

	if (pItem->isEquip())
		BaseContainer::AddItem(id, count);
	else
		ItemBag::AppendItem(id, count, log);

	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char id_str[64];
	char count_str[64];
	char level_str[64];
	int level = actor_->GetLevel();

	sprintf(id_str, "%d", id);
	sprintf(count_str, "%d", count);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor_->GetId(),
		actor_->GetAccount(),
		level_str,
		"give item",
		id_str,
		count_str,
		"", log, "depot", "", ""
	);

	return true;
}