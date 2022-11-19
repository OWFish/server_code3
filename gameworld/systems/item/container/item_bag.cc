#include "StdAfx.h"
#include "item_bag.h"
#include "entity/actor/actor.h"
#include "item/item.h"
#include "db/actor_db_data.h"
#include "protos/item_proto.h"


ItemBag::ItemBag(Actor *actor)
	: bag_type_(BagType_Item)
	, actor_(actor)
{
}

ItemBag::~ItemBag()
{
}

bool ItemBag::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;

	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init item.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_ItemBag))
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
		for (size_t i = 0; i  < buf_index_.size(); ++i)
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
		actor_->OnFinishInitStep(Actor::InitFlagType_ItemBag);
		db_buf_.clear();
		buf_index_.clear();
	}
	return true;
}

void ItemBag::NotifyAdd(Item* item, bool showTip)
{
	if (!actor_->IsInited())
		return;
	static Protocol::BagAddItemProto msg;
	msg.bag_type = GetType();
	item->WriteData(&msg.item);
	msg.show_tip = showTip ? 1 : 0;

	actor_->SendData(msg);
}

void ItemBag::NotifyDelete(int64_t uid, int count)
{
	static Protocol::BagDeleteItemProto msg;
	msg.bag_type = GetType();
	msg.uid = uid;

	actor_->SendData(msg);
}

void ItemBag::NotifyUpdate(int64_t uid, int count, bool showTip)
{
	static Protocol::BagUpdateItemProto msg;
	msg.bag_type = GetType();
	msg.uid = uid;
	msg.count = count;
	msg.show_tip = showTip ? 1 : 0;

	actor_->SendData(msg);
}

void ItemBag::OnAddItem(Item *item)
{
	if (!item) return;
	ScriptValueList params;
	params << actor_;
	params << aeGetItem;
	params << item->GetType();
	params << item->GetId();
	actor_->OnEvent(&params);
}

void ItemBag::OnEnterGame()
{
	static Protocol::BagInitProto msg;
	msg.bag_type = GetType();

	int count = (int)Count();
	short index = 0;

	while (index == 0 || count > 0)
	{
		ActorPacket AP;
		DataPacket& sp = actor_->AllocPacket(AP);
		msg.init_index = (uint8_t)index;
		msg.item_count = __min(count, MAX_PACKET_ITEMS_SIZE);
		count -= msg.item_count;
		sp.writeBuf(&msg, sizeof(msg));

		for (int i = 0; i < msg.item_count; ++i)
		{
			(item_list_[i + index * MAX_PACKET_ITEMS_SIZE])->WriteData(sp);
		}
		AP.flush();

		++index;
//#ifdef _MSC_VER
//	OutputMsg(rmTip, "======== send (%d,%d)", 3, 1);
//	OutputMsg(rmTip, "sendItemBag: type:%d, count:%d, index:%d", GetType(), msg.item_count, index);
//#endif
	};
}

void ItemBag::Save(ActorBasicData *data, bool force)
{
	if (!actor_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	if (!force && !need_save_) return;




	db_buf_.resize(item_list_.size() * sizeof(ItemData));
	for (uint32_t i = 0; i < item_list_.size(); i++)
	{
		ItemData* cpy = (ItemData*)&db_buf_[0];
		cpy[i] = item_list_[i]->GetItemData();
	}

	
	if (db_buf_.size() == 0)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveItem));
		pack << (ActorId)actor_->GetActorId() << bag_type_ << (uint32_t)0<<(uint32_t)0<<(uint32_t)0;
		db->flushProtoPacket(pack);
	}
	for (uint32_t i = 0; i < db_buf_.size(); i += PACK_LEN)
	{
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveItem));
		pack << (ActorId)actor_->GetActorId() << bag_type_ << i;

		if ((i + PACK_LEN) >= db_buf_.size())
		{
			pack << (uint32_t)db_buf_.size() - i;
		}
		else
		{
			pack << (uint32_t)PACK_LEN;
		}
		pack << (uint32_t)db_buf_.size();
		
		if ((i + PACK_LEN) > db_buf_.size())
		{
			pack.writeBuf(&db_buf_[i], db_buf_.size() - i);
		}
		else
		{
			pack.writeBuf(&db_buf_[i], PACK_LEN);
		}
		db->flushProtoPacket(pack);
	}
	db_buf_.clear();

/*	OutputMsg(rmTip, "-------------------------------SaveBag:actor:%d, type:%d, count:%d,size:%d",
		actor_->GetActorId(), bag_type_, item_list_.size(), pack.getLength()); */
}


bool ItemBag::AppendItem(int id, int count, const char* log, bool showTip)
{
	int pos = FindItem(id);
	if (pos < 0)
	{
		BaseContainer::AddItem(id, count, showTip);
	}
	else
	{
		Item* item = item_list_[pos];
		int newCount = item->GetCount() + count;
		if (newCount > BaseContainer::MAX_ITEM_COUNT)
			newCount = BaseContainer::MAX_ITEM_COUNT;

		item->SetCount(newCount);
		need_save_ = true;
		NotifyUpdate(item->GetUId(), item->GetCount(), showTip);
	}


	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char id_str[64];
	char count_str[64];
	char level_str[64];
	int level = actor_->GetLevel();

	sprintf(id_str, "%d", id);
	sprintf(count_str, "%d", count);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor_->GetActorId(),
		actor_->GetAccount(),
		level_str,
		"give item",
		id_str,
		count_str,
		"", log, "itembag", "", ""
	);

#ifdef OPENLOGDKMLOG
	static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
	auto conf = ItemConfigPool::GetItemConfig(id);
	//int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType
	if (count > 0 && conf)
	{
		dkmLog.LogAddItem(actor_->GetAccountId(), actor_->GetActorId(), actor_->GetEntityName(), level, actor_->GetPf(), id, count, 0, conf->type, log);
	}
#endif
	return true;
}


bool ItemBag::CostItem(int64_t uid, int count)
{
	return BaseContainer::DeleteItem(uid, count);
}

int ItemBag::FindItem(int id)
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		if (item_list_[i]->GetId() == id)
			return (int)i;
	}
	return -1;
}

int64_t ItemBag::FindItemUid(int id)
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		if (item_list_[i]->GetId() == id)
			return item_list_[i]->GetUId();
	}
	return -1;
}

Item* ItemBag::GetItem(int64_t uid)
{
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		if (item_list_[i]->GetUId() == uid)
			return item_list_[i];
	}
	return NULL;
}

void ItemBag::GMClear()
{
	for (int i = (int)item_list_.size() - 1; i >= 0; --i)
	{
		BaseContainer::DeleteItem(item_list_[i]->GetUId(), item_list_[i]->GetCount());
	}
}
