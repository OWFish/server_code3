#include "StdAfx.h"
#include "store_system.h"
#include "actor/actor_asyn_mgr.h"
#include "item/item_config.h"
#include "item/container/equip_bag.h"
#include "item/container/item_bag.h"
#include "item/item_pool.h"
#include "item/item.h"
#include "protocol/protos/store_proto.h"

StoreSystem::StoreSystem(Actor* actor)
{
	actor_ = actor;
	need_save_ = false;
	init_finish_ = false;
}

StoreSystem::~StoreSystem()
{

}


bool StoreSystem::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;
	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init store.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_Store))
		return true;

	if (init_finish_) return true;

	int item_count;
	data >> item_count;
	if (data.getAvaliableLength() < item_count * sizeof(StoreItemData))
	{
		OutputMsg(rmError, "Init store item failed. data length is wrong;%d, count:%d",
			data.getAvaliableLength(), item_count);
		return false;
	}

	StoreItemData item_data;
	for (int i = 0; i < item_count; ++i)
	{
		data >> item_data;
		item_list_.push_back(item_data);
	}

	init_finish_ = true;
	actor_->OnFinishInitStep(Actor::InitFlagType_Store);

	return true;
}

void StoreSystem::Save(ActorBasicData* data, bool force)
{
	if (!actor_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	if (!force && !need_save_) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveStore));
	pack << (ActorId)actor_->GetActorId();
	pack << (int)(item_list_.size());

	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		StoreItemData &pItem = item_list_[i];
		pItem.writeData(pack);
	}
	db->flushProtoPacket(pack);
	OutputMsg(rmTip, "-------------------------------SaveStore:actor:%d, type:%d", actor_->GetActorId());

	need_save_ = false;
}

void StoreSystem::OnEnterGame()
{

}

const StoreItemData* StoreSystem::GetStoreItemData(int id)
{
	int count = static_cast<int> ( item_list_.size() );
	for (int i = 0; i < count; ++i)
	{
		if (item_list_[i].id == id)
		{
			return &item_list_[i];
		}
	}
	return NULL;
}

void StoreSystem::GiveStoreItem(int id, int& itemId, int& itemCount)
{
	int count = static_cast<int>( item_list_.size() );
	for (int i = 0; i < count; ++i)
	{
		if (item_list_[i].id == id)
		{
			const ItemConfig *conf = ItemConfigPool::GetItemConfig(item_list_[i].itemData.id);
			if (conf == NULL) return;

			if (conf->isEquip())
			{
				EquipBag* pEquipBag = actor_->GetEquipBag();
				pEquipBag->AppendItem(&item_list_[i].itemData, "store give item");
				itemId = item_list_[i].itemData.id;
				itemCount = 1;
			}
			else
			{
				ItemBag* pItemBag = actor_->GetItemBag();
				pItemBag->AppendItem(item_list_[i].itemData.id, item_list_[i].itemData.count, "store give item");
				itemId = item_list_[i].itemData.id;
				itemCount = item_list_[i].itemData.count;
			}

			auto it = item_list_.begin() + i;
			item_list_.erase(it);

			need_save_ = true;
			break;
		}
	}
}

void StoreSystem::AddStoreItem(int id, int itemId, int count, int currencyType, int currency, int discount)
{
	Item *pItem = ItemPool::instance().CreateItem(itemId, count);
	if (!pItem) return;

	StoreItemData data;
	data.id = id;
	data.currency_type = currencyType;
	data.currency = currency;
	data.discount = discount;
	pItem->WriteData((void *)&data.itemData);
	delete pItem;

	if (item_list_.size() >= maxItemNum)
		return;

	item_list_.push_back(data);

	need_save_ = true;
}

void StoreSystem::StoreDataSync(int refreshCount)
{
	Protocol::StoreDataProto msg;
	msg.refreshCount = refreshCount;
	msg.data_num = static_cast<int>(item_list_.size() );
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << actor_;
	luaScript.Call("getStoreRefreshIntegral", &arg, &arg, 1);
	msg.refresh_integra = arg[0];
	arg.clear();
	arg << actor_;
	luaScript.Call("getStoreRefreshCd", &arg, &arg, 1);
	msg.refresh_cd = arg[0];
	ActorPacket AP;
	DataPacket& sp = actor_->AllocPacket(AP);
	sp.writeBuf(&msg, sizeof(msg));
	for (std::size_t i = 0; i < item_list_.size(); ++i)
	{
		item_list_[i].writeData(sp);
	}
	AP.flush();
//#ifdef _MSC_VER
//	OutputMsg(rmTip, "======== send (%d,%d)", 3, 1);
//#endif
}

void StoreSystem::StoreClearList()
{
	item_list_.clear();
}
