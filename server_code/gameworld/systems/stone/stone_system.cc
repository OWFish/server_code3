#include "StdAfx.h"
#include "stone_system.h"
#include "db/actor_db_data.h"


StoneSystem::StoneSystem(Role *role)
: role_(role)
, equip_data_()
{
	attribute_.Reset();
}

StoneSystem::~StoneSystem()
{

}

bool StoneSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	equip_data_ = &data->equips_data;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("stoneAttrInit", &arg, &arg, 0);
	return true;
}

void StoneSystem::Save(RoleData* data)
{

}

void StoneSystem::Destroy()
{
}

void StoneSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void StoneSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void StoneSystem::ClearAttr()
{
	attribute_.Reset();
}


void StoneSystem::SetLevel(int posId, int level)
{
	if (posId < 0 || posId  >=EquipSlotType_Max) return;

	EquipSlotData &pSlotData = equip_data_->slot_data[posId];

	pSlotData.gem_lv = level;
}

std::vector<int> StoneSystem::GetStoneData()
{
	std::vector<int> stoneList;

	for (int pos = EquipSlotType_Weapon; pos < EquipSlotType_Max; ++pos)
	{
		EquipSlotData &pSlotData = equip_data_->slot_data[pos];
		stoneList.push_back(pSlotData.gem_lv);
	}
	return stoneList;
}
