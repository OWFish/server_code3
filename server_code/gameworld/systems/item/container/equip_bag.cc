#include "StdAfx.h"
#include "equip_bag.h"
#include "item/item.h"
#include "protos/equip_proto.h"
#include "protos/item_proto.h"
#include "item/container/bag_config.h"


EquipBag::EquipBag(Actor* actor) :ItemBag(actor)
{
	bag_type_ = BagType_Equip;
}

bool EquipBag::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;
	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on equipbat init.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_EquipBag))
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
		actor_->OnFinishInitStep(Actor::InitFlagType_EquipBag);
		db_buf_.clear();
		buf_index_.clear();
		UpdataCapacity();
	}
	return true;
}

bool EquipBag::OnDecomposeEquip(int64_t uid)
{
	return false;
}

int EquipBag::AppendItem(int id, int count, const char* log, bool showTip)
{
	int i = 0;
	while (count > 0)
	{
		if (Count() >= (uint32_t)capacity_)
			break;
		BaseContainer::AddItem(id, 1, showTip);
		--count;
		++i;
	}

	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char id_str[64];
	char count_str[64];
	char level_str[64];
	char real_get_str[64];
	int level = actor_->GetLevel();

	sprintf(id_str, "%d", id);
	sprintf(count_str, "%d", count);
	sprintf(real_get_str, "%d", i);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor_->GetActorId(),
		actor_->GetAccount(),
		level_str,
		"give item",
		id_str,
		count_str,
		real_get_str, log, "equip_bag", "", ""
	);

#ifdef OPENLOGDKMLOG
	static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
	auto conf = ItemConfigPool::GetItemConfig(id);
	//int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType
	if (i>0 && conf)
	{
		dkmLog.LogAddItem(actor_->GetAccountId(), actor_->GetActorId(), actor_->GetEntityName(), level, actor_->GetPf(), id, i, 0, conf->type, log);
	}
#endif
	return i;
}

int EquipBag::AppendItem(ItemData *data, const char* log, bool showTip)
{
	if (!data) return 0;

	if (Count() < (uint32_t)capacity_)
	{
		BaseContainer::AddItem(data, showTip);
		return 0;
	}
	return 1;
}

int EquipBag::AppendItem(Item* pItem, const char* log, bool showTip)
{
	int real_get = 0;
	if (!pItem) return 0;

	if (pItem)
	{
		if (Count() < (uint32_t)capacity_)
		{
			BaseContainer::AddItem(pItem, true, showTip);
			real_get = 1;
		}
	}

	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char id_str[64];
	char count_str[64];
	char real_get_str[64];
	char level_str[64];
	int level = actor_->GetLevel();

	sprintf(id_str, "%d", pItem->GetId());
	sprintf(count_str, "%d", 1);
	sprintf(real_get_str, "%d", real_get);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor_->GetActorId(),
		actor_->GetAccount(),
		level_str,
		"give item",
		id_str,
		count_str,
		real_get_str, log, "equip_bag", "", ""
	);

#ifdef OPENLOGDKMLOG
	static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
	//int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType
	dkmLog.LogAddItem(actor_->GetAccountId(), actor_->GetActorId(), actor_->GetEntityName(), level, actor_->GetPf(), pItem->GetId(), pItem->GetCount(), 0, pItem->GetType(), log);

#endif
	return real_get;
}

bool EquipBag::IsCanSmelt(int type, int64_t uid)
{

		//检查有没有这个装备
	Item *item = GetItem(uid);
	if (!item) return false;

		//不是装备不能熔炼，后面还有神器和定制装备也不能熔炼的，后面有了再加吧
	if (!item->isEquip()) return false;

		//普通熔炼的话，橙色以上装备不能熔炼
	//if (item->GetQuality() >= Item::QualityType_Orange && type == 0) return false;

	return true;
}

void EquipBag::OnEquipSmelt(int type, std::vector<int64_t> &itemIdList)
{
	bool bSmelt = false;
	int goldNum = 0;
	int smeltCount = 0;
	std::map<int, int> itemList;
	std::map<int, int> currency;
	int count = static_cast<int>( itemIdList.size());

	//获取贵族加成
	/*int precent = 0;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << actor_;
	if (true == luaScript.Call("getSmeltPrecent", &arg, &arg, 1))
	{
		precent = arg[0];
	}*/

	for (int i = 0; i < count; ++i)
	{
		int64_t &itemId = itemIdList[i];

		if (!IsCanSmelt(type, itemId)) continue;
		//检查有没有这个装备
		Item *item = GetItem(itemId);
		if (!item) continue;

		//先记录一些信息，不然后面道具删掉了就拿不到了
		//int level = item->GetLevel();
		//int zsLevel = item->GetZhuanShengLevel();
		int id = item->GetId();
		//int quality = item->GetQuality();
		int itemType = item->GetType();
		//翅膀装备在熔炼时，原等级需要加上一个基础值，与普通装备的熔炼区别开来
		//if (item->GetType() == ItemType_WingEquip)
		//{
		//	level += WING_EQUIP_SMELT_BASE;
		//}
		//else if (item->GetType() == ItemType_TogetherHit) 
		//{
		//	level += TOGETHERHIT_SMELT_BASE;
		//}

		//先删装备，再给奖励
		if (!DeleteItem(itemId, 1)) continue;

		smeltCount++;

		//给奖励
		bSmelt = true;
		const SmeltConfig *smeltConfig = ItemConfigPool::GetSmeltConfig(id);
		if (smeltConfig)
		{
			int curRate = wrand(100);
			bool qualityAdd = false;
			//检查是否能获得更高级装备
			for (std::size_t i = 0; i< smeltConfig->equipRateList.size(); ++i)
			{
				const SmeltEquipRateConfig *config = &(smeltConfig->equipRateList[i]);
				if (curRate < config->rate)
				{
					//品质提升一级对应的装备ID增加100
					int newEquipId = id + 100 * (config->qualityAdd);
					if (ItemConfigPool::GetItemConfig(newEquipId))
					{
						itemList.insert(std::pair<int, int>(newEquipId, 1));
					}

					qualityAdd = true;
					break;
				}
				curRate -= config->rate;
			}

			//获得装备就不能获得金币和强化石奖励
			if (qualityAdd) continue;

			//给金币和强化石奖励
			goldNum = goldNum + smeltConfig->goldNum;// +floor(smeltConfig->goldNum * precent / 100);
			if (smeltConfig->stoneNum) {
				itemList[smeltConfig->stoneId] = itemList[smeltConfig->stoneId] + smeltConfig->stoneNum;
			}
			for (auto it = smeltConfig->currency.begin(); it != smeltConfig->currency.end(); ++it)
			{
				currency[it->first] += it->second;
			}
		}
#ifdef OPENLOGDKMLOG
		static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
		dkmLog.LogCostItem(actor_->GetAccountId(), actor_->GetActorId(), actor_->GetEntityName(), actor_->GetLevel(), actor_->GetPf(), id, 1, 0, itemType, "EquipSmelt");
#endif
	}
	if (goldNum) {
		actor_->ChangeGold(goldNum, "equip smelt");
	}
	for (auto it = currency.begin(); it != currency.end(); ++it)
	{
		actor_->ChangeCurrency(it->first, it->second, "equip smelt");
	}
	for (auto itor = itemList.begin(); itor != itemList.end(); ++itor)
	{
		actor_->GiveItem(itor->first, itor->second, "equip smelt");
	}

	//成功熔炼装备就给个回包
	if (bSmelt)
		ReEquipSmelt(1, goldNum, itemList);

	OnActorSmeltEvent(smeltCount);
}

void EquipBag::OnExpandCapacity(int rows)
{
	if (rows <= 0) return;
	int basic_grid = actor_->GetBasicData()->bag_grid;
	int expanded_rows = (basic_grid - BagConfigPool::GetBaseSize()) / BagConfigPool::GetRowSize();

	int need_yb = 0;
	int temp = rows;
	while (temp > 0)
	{
		auto config = BagConfigPool::GetExpandConfig(++expanded_rows);
		if (config == NULL)
			return;
		need_yb += config->cost;
		--temp;
	};

	if (actor_->GetYuanBao() < need_yb)
		return;
	actor_->ChangeYuanBao(0 - need_yb, "expand bag");
	capacity_ = capacity_ + rows * BagConfigPool::GetRowSize();
	basic_grid = basic_grid + rows * BagConfigPool::GetRowSize();
	actor_->SetBagGrid(basic_grid);

	Protocol::BagUpdateCapacityProto msg;
	msg.grid = basic_grid;
	actor_->SendData(msg);
}

void EquipBag::OnVipLevelUpdate()
{
	UpdataCapacity();
}

void EquipBag::ReEquipSmelt(int result, int goldNum, std::map<int, int> &itemList)
{
	static Protocol::EquipSmeltProto msg;
	msg.result = result;
	msg.goldNum = goldNum;
	msg.itemCount = (int)itemList.size();

	ActorPacket AP;
	DataPacket& sp = actor_->AllocPacket(AP);
	sp.writeBuf(&msg, sizeof(msg));
	for (auto itor = itemList.begin(); itor != itemList.end(); ++itor)
	{
		if (ItemConfigPool::GetItemConfig(itor->first))
		{
			sp << itor->first;
			sp << itor->second;
		}
	}
	AP.flush();
//#ifdef _MSC_VER
//	OutputMsg(rmTip, "======== send (%d,%d)", 4, 2);
//#endif
}

void EquipBag::OnActorSmeltEvent(int smeltCount)
{
	ScriptValueList params;
	params << actor_;
	params << aeSmeltEquip;
	params << smeltCount;
	actor_->OnEvent(&params);
}

void EquipBag::UpdataCapacity(int add,int capacity)
{
	//OutputMsg(rmTip, "====== capacity ===== (%d,%d) ", capacity_, add);
	capacity_ = actor_->GetBasicData()->bag_grid + BagConfigPool::GetVipGrid(actor_->GetVipLevel());
	if (actor_->GetBasicData()->monthcard == 1)
	{ 
		capacity_ += capacity;
	}
	if (actor_->GetBasicData()->privilege_monthcard == 1)
	{
		capacity_ += capacity;
	}
	if (add > 0) {
		int basic_grid = actor_->GetBasicData()->bag_grid;
		basic_grid += add;
		actor_->SetBagGrid(basic_grid);
		Protocol::BagUpdateCapacityProto msg;
		msg.grid = basic_grid;
		actor_->SendData(msg);
	}
	/*
	if (actor_->GetActorVarSystem()->GetIntValue("monthcard.privilege", 0) == 2)	
	{
		capacity_ += PRIVILEGE_EQUIPBAG_GRID;
	}
	*/
}
