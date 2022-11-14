#include "StdAfx.h"
#include "zhuling_system.h"
#include "db/actor_db_data.h"


ZhulingSystem::ZhulingSystem(Role *role)
: role_(role)
, equip_data_()
{
	attribute_.Reset();
}

ZhulingSystem::~ZhulingSystem()
{

}

bool ZhulingSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	equip_data_ = &data->equips_data;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("zhulingAttrInit", &arg, &arg, 0);

	return true;
}

void ZhulingSystem::Save(RoleData* data)
{

}

void ZhulingSystem::Destroy()
{
}

void ZhulingSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void ZhulingSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void ZhulingSystem::ClearAttr()
{
	attribute_.Reset();
}


void ZhulingSystem::SetLevel(int posId, int level)
{
	EquipSlotData &pSlotData = equip_data_->slot_data[posId];
	pSlotData.zhuling_lv = level;
}

std::vector<int> ZhulingSystem::GetZhulingData()
{
	std::vector<int> zhulingList;

	for (int pos = EquipSlotType_Weapon; pos < EquipSlotType_Max; ++pos)
	{
		EquipSlotData &pSlotData = equip_data_->slot_data[pos];
		zhulingList.push_back(pSlotData.zhuling_lv);
	}
	return zhulingList;
}


