#include "StdAfx.h"
#include "equip_system.h"
#include "db/actor_db_data.h"
#include "../item_pool.h"
#include "protos/equip_proto.h"
#include "../container/equip_bag.h"


EquipSystem::EquipSystem(Role *role)
: role_(role)
, equip_()
, godequip_()
{
	attribute_.Reset();
}

EquipSystem::~EquipSystem()
{
	for (int i = 0; i < EquipSlotType_Max; ++i)
	{
		SafeDelete(equip_[i]);
	}
	for (int i = 0; i < EquipSlotType_Dzi; ++i)
	{
		SafeDelete(godequip_[i]);
	}
}

bool EquipSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;
	data_ = &data->equips_data;

	for (int i = 0; i < EquipSlotType_Max; ++i)
	{
		ItemData *item_data = &(data->equips_data.slot_data[i].equip_data);
		if (item_data->uid != 0)
		{
			equip_[i] = (Equip*)ItemPool::instance().CreateItem(item_data);
		}

		item_data = &(data->equips_data.god_slot_data[i].equip_data);
		if (item_data->uid != 0)
		{
			godequip_[i] = (Equip*)ItemPool::instance().CreateItem(item_data);
		}
	}
	// 计算属性
	CalcAttribute(false);

	return true;
}

void EquipSystem::Save(RoleData* data)
{
	auto slot_data = data->equips_data.slot_data;
	auto god_slot_data = data->equips_data.god_slot_data;
	for (int i = 0; i < EquipSlotType_Max; ++i)
	{
		Equip* equip = equip_[i];
		if (equip)
			equip->WriteData(&(slot_data[i].equip_data));
		else
			memset(&(slot_data[i].equip_data), 0, sizeof(ItemData));
	}

	for (int i = 0; i < EquipSlotType_Dzi; ++i)
	{
		 Equip*	equip = godequip_[i];
		if (equip)
			equip->WriteData(&(god_slot_data[i].equip_data));
		else
			memset(&(god_slot_data[i].equip_data), 0, sizeof(ItemData));
	}
}

void EquipSystem::Destroy()
{
}

inline int GetSlotType(int slot)
{
	if (slot < 0 || slot > EquipType_Max)
	{
		return -1;
	}
	return (EquipType)slot;
}

bool EquipSystem::EquipItem(Equip *item, short slot)
{
	if (!item) return false;
	if (item->GetType() != ItemType_Equip)
		return false;

	int job = item->GetJobType();
	if (job != 0 && job != role_->GetJob())
		return false;

	int type = GetSlotType(slot);
	if (type != item->GetSubType())
		return false;

	int level = role_->GetActor()->GetLevel();
	int zsLevel = role_->GetActor()->GetBasicData()->zhuansheng_lv;
	if (item->GetLevel() > level ||
		item->GetZhuanShengLevel() > zsLevel)
		return false;

	Equip* old = equip_[slot];
	equip_[slot] = item;
	item->WriteData(&data_->slot_data[slot].equip_data);
	NotifyUpdateEquip(slot, item);

	auto equip_bag = role_->GetActor()->GetEquipBag();
	equip_bag->TakeOutItem(item);
	if (old)
		equip_bag->AddItem(old, true, false);

	OnEquipEvent(slot);

	CalcAttribute(true);


	static LogSender* log_sender = ServerInstance()->GetLogClient();
	auto actor = role_->GetActor();
	char itemid[64];
	char olditem[64];
	char slotstr[64];
	char level_str[64];
	int oldid = 0;
	if (old) oldid = old->GetId();

	sprintf(itemid, "%d", item->GetId());
	sprintf(olditem, "%d", oldid);
	sprintf(level_str, "%d", level);
	sprintf(slotstr, "%d", slot);
	log_sender->LogCounter(actor->GetActorId(),
		actor->GetAccount(),
		level_str,
		"equip",
		itemid,
		olditem,
		slotstr, "change", "", "", ""
	);

	return true;
}

bool EquipSystem::EquipGodItem(Equip *item, short slot)
{

	if (slot < EquipSlotType_Weapon || slot >= EquipSlotType_Dzi)
	{
		return false;
	}

	if (!item) return false;
	if (item->GetType() != ItemType_Equip)
		return false;

	int job = item->GetJobType();
	if (job != 0 && job != role_->GetJob())
		return false;

	int type = GetSlotType(slot);
	if (type != item->GetSubType())
		return false;

	int level = role_->GetActor()->GetLevel();
	int zsLevel = role_->GetActor()->GetBasicData()->zhuansheng_lv;
	if (item->GetLevel() > level ||
		item->GetZhuanShengLevel() > zsLevel)
		return false;

	Equip* old = godequip_[slot];
	godequip_[slot] = item;
	item->WriteData(&data_->god_slot_data[slot].equip_data);
	NotifyUpdateEquip(slot, item);

	auto equip_bag = role_->GetActor()->GetEquipBag();
	equip_bag->TakeOutItem(item);
	if (old)
		equip_bag->AddItem(old, true, false);

	OnEquipEvent(slot);

	CalcAttribute(true);


	static LogSender* log_sender = ServerInstance()->GetLogClient();
	auto actor = role_->GetActor();
	char itemid[64];
	char olditem[64];
	char slotstr[64];
	char level_str[64];
	int oldid = 0;
	if (old) oldid = old->GetId();

	sprintf(itemid, "%d", item->GetId());
	sprintf(olditem, "%d", oldid);
	sprintf(level_str, "%d", level);
	sprintf(slotstr, "%d", slot);
	log_sender->LogCounter(actor->GetActorId(),
		actor->GetAccount(),
		level_str,
		"godequip",
		itemid,
		olditem,
		slotstr, "change", "", "", ""
	);

	return true;
}

bool EquipSystem::TakeOutEquip(int equiptype , int slot) {
	if (slot < EquipType_Weapon || slot >= EquipType_Dzi)
		return false;
	Equip** pEquipList = nullptr;
	if (equiptype == EquipType_Normal)
	{
		pEquipList = equip_;
	}
	else if (equiptype == EquipType_God)
	{
		pEquipList = godequip_;
	}

	if (!pEquipList[slot]) return false;
	auto equip_bag = role_->GetActor()->GetEquipBag();
	if (!equip_bag) return false;

	int id = pEquipList[slot]->GetId();
	equip_bag->AddItem(pEquipList[slot], true, false);
	pEquipList[slot] = NULL;
	if (equiptype == EquipType_Normal)
	{
		memset(&(data_->slot_data[slot].equip_data), 0, sizeof(ItemData));
	}
	else if (equiptype == EquipType_God)
	{
		memset(&(data_->god_slot_data[slot].equip_data), 0, sizeof(ItemData));
	}
	
	NotifyUpdateEquip(slot, NULL, equiptype);

	OnEquipEvent(slot);

	CalcAttribute(true);

	static LogSender* log_sender = ServerInstance()->GetLogClient();
	auto actor = role_->GetActor();
	if (!actor) return false;
	char itemid[64];
	char slotstr[64];
	char level_str[64];

	sprintf(itemid, "%d", id);
	sprintf(slotstr, "%d", slot);
	sprintf(level_str, "%d", actor->GetLevel());
	log_sender->LogCounter(actor->GetActorId(),
		actor->GetAccount(),
		level_str,
		"TakeOutequip",
		itemid,
		"",
		slotstr, "change", "", "", ""
	);

	return true;
}


int EquipSystem::GetEquipId(short slot)
{
	Equip* old = equip_[slot];
	if (!old)
		return 0;
	return old->GetId();
}

int EquipSystem::GetEquipQuality(short slot)
{
	Equip* old = equip_[slot];
	if (!old)
		return 0;
	return old->GetQuality();
}

void EquipSystem::getEquipLevel(short slot, int & level, int & zsLevel)
{
	Equip* old = equip_[slot];
	if (!old)
	{
		level = 0; zsLevel = 0;
		return;
	}
	level = old->GetLevel();
	zsLevel = old->GetZhuanShengLevel();
}

void EquipSystem::NotifyUpdateEquip(int slot, Equip* item, int equiptype)
{
	static Protocol::EquipItemProto msg;
	msg.slot = slot;
	if (item) {
		msg.equiptype = item->GetEquipType();
		item->WriteData(&msg.equip_data);
	} else {
		msg.equiptype = equiptype;
		memset(&msg.equip_data, 0, sizeof(ItemData));
	}
	role_->GetActor()->SendData(msg);
}

void EquipSystem::CalcAttribute(bool notify)
{
	attribute_.Reset();
	ex_attribute_.Reset();
	int power = 0;
	for (int i = 0; i < EquipSlotType_Max; ++i)
	{
		const EquipConfig* equip_config = nullptr;
		Equip* equip = equip_[i];
		if (equip)
		{
			equip->AddAttr(attribute_);
			equip->AddExAttr(ex_attribute_);
			equip_config = equip->GetConfig();
			if (equip_config)
				power += equip_config->ex_power;
		}

		if (i < EquipSlotType_Dzi)
		{
			Equip* egodquip = godequip_[i];
			if (egodquip)
			{
				egodquip->AddAttr(attribute_);
				egodquip->AddExAttr(ex_attribute_);
				equip_config = egodquip->GetConfig();
				if (equip_config)
					power += equip_config->ex_power;
			}
		}
	}

	attribute_.SetExtraPower(power);
	if (notify)
	{
		role_->CalcAttributes();
		role_->CalcExAttributes();
	}
}

void EquipSystem::EquipLevelup(short slot)
{
	//校验位置枚举
	if (slot < 0 || slot >= EquipSlotType_Dzi)
		return;

	//没有装备的位置不能升级
	Equip* oldEquip = godequip_[slot];
	if (!oldEquip)
		return;

	//看看是不是能升级的装备，没有配置的就是不能升级的
	int equipId = oldEquip->GetId();
	const LevelupConfig *config = ItemConfigPool::GetLevelupConfig(equipId);
	if (!config) return;

	//看看新的装备id是否正确，并且限制等级是否超过玩家等级
	auto item_config = ItemConfigPool::GetItemConfig(config->newEquipId);
	if (!item_config)
		return;

	int level = role_->GetActor()->GetLevel();
	int zs_level = role_->GetActor()->GetBasicData()->zhuansheng_lv;
	if (item_config->zs_level * 1000 + item_config->level > zs_level * 1000 + level)
		return;

	//校验材料够不够
	auto item_bag = role_->GetActor()->GetItemBag();
	int count = item_bag->GetCountById(config->itemId);
	if (config->count > count) return;

	//创建新的装备
	Item* newEquip = ItemPool::instance().CreateItem(config->newEquipId, 1);
	if (!newEquip) return;

	//看看策划有没有配错表，配了一些不是装备的道具
	if (newEquip->GetType() != ItemType_Equip)
	{
		delete newEquip;
		return;
	}
		
	//先扣材料
	role_->GetActor()->CostItem(config->itemId, config->count, "equip level up");

	//先删除旧装备
	delete oldEquip;

	//穿上新装备
	godequip_[slot] = (Equip*)newEquip;

	//通知前端
	NotifyUpdateEquip(slot, (Equip*)newEquip);

	OnEquipEvent(slot);

	CalcAttribute(true);

	const ComposeConfig *ccfg = ItemConfigPool::GetComposeConfig(equipId);
	if(ccfg) {
		int notice_id = 0;
		int notice_level = 0;
		if (ccfg->type == CCT_ORANGE) {
			if (item_config->zs_level > 0) {
				notice_id = EN_ORANGE_ZSUP_ID;
				notice_level = item_config->zs_level;
			} else {
				notice_id = EN_ORANGE_LVUP_ID;
				notice_level = item_config->level;
			}
		} else if (ccfg->type == CCT_LEGEND) {
			notice_id = EN_LEGEND_ZSUP_ID;
			notice_level = item_config->zs_level;
		}

		if(notice_id) {
			ScriptValueList arg;
			arg << notice_id;
			arg << role_->GetActor()->GetActorName();
			arg << item_config->name;
			arg << notice_level;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("broadCastNotice", &arg, &arg, 0);
		}
	}
		


	ReqLevelup(1, config->newEquipId);

	static LogSender* log_sender = ServerInstance()->GetLogClient();
	auto actor = role_->GetActor();
	char itemid[64];
	char olditem[64];
	char slotstr[64];
	char level_str[64];

	sprintf(itemid, "%d", config->newEquipId);
	sprintf(olditem, "%d", equipId);
	sprintf(level_str, "%d", level);
	sprintf(slotstr, "%d", slot);
	log_sender->LogCounter(actor->GetActorId(),
		actor->GetAccount(),
		level_str,
		"equip",
		itemid,
		olditem,
		slotstr, "levelup", "", "", ""
	);

}

void EquipSystem::ReqLevelup(int result, int itemId)
{
	static Protocol::EquipLevelupProto msg;
	msg.roleId = (short)role_->GetId();
	msg.result = result;
	msg.itemId = itemId;
	
	role_->GetActor()->SendData(msg);
}

void EquipSystem::EquipCompose(int equipId, short slot)
{
	const ComposeConfig *config = ItemConfigPool::GetComposeConfig(equipId);
	if (!config) return;

	//看看装备id是否正确
	auto item_config = ItemConfigPool::GetItemConfig(equipId);
	if (!item_config)
		return;

	//限制等级是否超过玩家等级
	int level = role_->GetActor()->GetLevel();
	int zs_level = role_->GetActor()->GetBasicData()->zhuansheng_lv;
	if (item_config->zs_level * 1000 + item_config->level > zs_level * 1000 + level)
		return;

	//校验材料够不够
	auto item_bag = role_->GetActor()->GetItemBag();
	int count = item_bag->GetCountById(config->itemId);
	if (config->count > count) return;

	//背包空间够不够
	auto equip_bag = role_->GetActor()->GetEquipBag();
	count = equip_bag->Spaces();
	//if (0 >= count)
	//{
	//	role_->GetActor()->SendTipWithId(1);
	//	return;
	//}

	//创建新的装备
	Item* newEquip = ItemPool::instance().CreateItem(config->equipId, 1);
	if (!newEquip) return;

	//先扣材料
	role_->GetActor()->CostItem(config->itemId, config->count, "equip compose");

	//equip_bag->AddItem(newEquip, true, false);
	equip_bag->AppendItem(newEquip, "equip compose.", false);

	EquipGodItem((Equip*)newEquip, slot);

	ScriptValueList params;
	params << role_->GetActor();
	params << aeOrange;
	params << equipId;
	role_->GetActor()->OnEvent(&params);


	ScriptValueList arg;
	arg << (int)((config->type == CCT_ORANGE)?((item_config->zs_level > 0)? EN_ORANGE_COMPOSE_ZS_ID : EN_ORANGE_COMPOSE_ID):EN_LEGEND_COMPOSE_ID);
	arg << role_->GetActor()->GetActorName();
	arg << item_config->name;
	arg << (int)(item_config->zs_level ? item_config->zs_level : item_config->level);
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("broadCastNotice", &arg, &arg, 0);

	NotifyCompose(1, config->equipId);
}

void EquipSystem::NotifyCompose(int result, int itemId)
{
	static Protocol::EquipComposeProto msg;
	msg.roleId = (short)role_->GetId();
	msg.result = result;
	msg.itemId = itemId;

	role_->GetActor()->SendData(msg);
}

bool EquipSystem::GetEquipAttrBySlot(short slot, Attribute &attribute)
{
	Equip* equip = equip_[slot];
	if (!equip)
		return false;

	equip->AddAttr(attribute);
	return true;
}

bool EquipSystem::GetEquipExAttrBySlot(short slot, ExAttribute &ex_attribute)
{
	Equip* equip = equip_[slot];
	if (!equip)
		return false;

	equip->AddExAttr(ex_attribute);
	return true;
}

void EquipSystem::OnEquipEvent(short slot)
{
	ScriptValueList params;
	params << role_->GetActor();
	params << aeAddEquiment;
	params << role_->GetId();
	params << (int)slot;
	role_->GetActor()->OnEvent(&params);
}





