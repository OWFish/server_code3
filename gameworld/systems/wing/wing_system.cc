#include "StdAfx.h"
#include "wing_system.h"
#include "db/actor_db_data.h"
#include "item/item_pool.h"
#include "item/container/equip_bag.h"
#include "protos/wing_proto.h"

WingSystem::WingSystem(Role *role)
: role_(role)
, wingData_()
//, wing_equip_()
{
	attribute_.Reset();
	temp_attribute_.Reset();
}

WingSystem::~WingSystem()
{
	//for (int i = 0; i < WingSlotType_Max; ++i)
	//{
	//	SafeDelete(wing_equip_[i]);
	//}
	}

bool WingSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	wingData_  = &data->wings;
	//wing_equip_data = &data->wingequips_data;

	/*for (int i = 0; i < WingSlotType_Max; ++i)
	{
		ItemData* item_data = &(wing_equip_data->wing_slot[i].equip_data);
		if (item_data->uid != 0)
		{
			wing_equip_[i] = (Equip*)ItemPool::instance().CreateItem(item_data);
		}
	}*/
	return true;
	}
	/*
void WingSystem::Save(RoleData* data)
{
	auto wingdata = data->wingequips_data;
	for (int i = 0; i < WingSlotType_Max; ++i)
	{
		Equip* equip = wing_equip_[i];
		if (equip)
			equip->WriteData(&(wingdata.wing_slot[i].equip_data));
		else
			memset(&(wingdata.wing_slot[i].equip_data), 0, sizeof(ItemData));
	}
}
*/
void WingSystem::Destroy()
{
}

void WingSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void WingSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void WingSystem::AddTempAttr(int type, int value)
{
	temp_attribute_.Add((Attribute::AttributeType)type, value);
}

void WingSystem::ClearAttr()
{
	attribute_.Reset();
	temp_attribute_.Reset();
}

const WingsData* WingSystem::GetWingData()
{
	return wingData_;
}

void WingSystem::SetLevel(int level)
{
	wingData_->level = level;
}

void WingSystem::SetExp(int exp)
{
	wingData_->exp = exp;
}

void WingSystem::SetStar(int star)
{

	//wingData_->star_lv = star;
}

void WingSystem::SetOpenStatus(int status)
{
	wingData_->openStatus = status;
}

void WingSystem::setWingCTime(unsigned int ctime)
{
	wingData_->ctime = ctime;
	//WingInfoSync();
}

void WingSystem::setWingPill(int idx, int count)
{
	if (idx < 0 || idx >= MAX_WING_PILL) return;
	wingData_->pill[idx] = count;
}

int WingSystem::GetWingSlotType(int slot)
{
	switch (slot)
	{
	case WingSlotType_Hub:
		return EquipType_Hub;
	case WingSlotType_Stone:
		return EquipType_Stone;
	case WingSlotType_Feathers:
		return EquipType_Feathers;
	case WingSlotType_Colorplume:
		return EquipType_Colorplume;
	default:
		return -1;
	}
}

void WingSystem::NotifyUpdateWingEquip(int slot, Equip* item)
{
	static Protocol::WingItemProto msg;
	msg.role_id = role_->GetId();
	msg.slot = slot;
	item->WriteData(&msg.equip_data);
	role_->GetActor()->SendData(msg);
}
/*
bool WingSystem::EquipWingItem(Equip *item, short slot)
{
	if (!item) return false;
	if (item->GetType() != ItemType_WingEquip)
		return false;

	int job = item->GetJobType();
	if (job != 0 && job != role_->GetJob())
		return false;

	int type = GetWingSlotType(slot);
	if (type != item->GetSubType())
		return false;

	if (item->GetLevel() > wingData_->level)
		return false;

	Equip* old = wing_equip_[slot];
	wing_equip_[slot] = item;
	item->WriteData(&wing_equip_data->wing_slot[slot].equip_data);
	NotifyUpdateWingEquip(slot, item);

	EquipBag* equip_bag = role_->GetActor()->GetEquipBag();
	equip_bag->TakeOutItem(item);
	if (old)
		equip_bag->AddItem(old, true, false);

	callUpdateAttr();
	return true;
}

void WingSystem::AddWingEquipAttr()
{
	for (int i = 0; i < WingSlotType_Max; ++i)
	{
		Equip* equip = wing_equip_[i];
		if(!equip)
			continue;

		equip->AddAttr(attribute_);
	}
}
*/
void WingSystem::WingInfoSync()
{
	if (!wingData_) return;
	static Protocol::WingInfoProto msg;
	msg.role_id = role_->GetId();
	msg.wing_data = *wingData_;
	//msg.wing_equip = *wing_equip_data;
	role_->GetActor()->SendData(msg);
}

void WingSystem::On1sTick(int64_t curr_t)
{
	if (!wingData_) return;
	static GameEngine* ge = GetGameEngine();
	unsigned int now = ge->getMiniDateTime();
	if (wingData_->ctime > 0 && wingData_->ctime <= now)
	{
		wingData_->exp = 0;
		wingData_->ctime = 0;
		callUpdateAttr();
		WingInfoSync();
		//发送祝福值清零邮件
		ScriptValueList arg;
		arg << role_->GetActor();
		arg << role_->GetJob();
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("sendWingCTimeOver", &arg, &arg, 0);
	}
}

void WingSystem::callUpdateAttr(void) {
	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("updateWingAttr", &arg, &arg, 0);
}
