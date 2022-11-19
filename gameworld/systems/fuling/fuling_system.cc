#include "StdAfx.h"
#include "fuling_system.h"
#include "db/actor_db_data.h"


FulingSystem::FulingSystem(Role *role)
: role_(role)
, equip_data_()
{
	attribute_.Reset();
	ex_attribute_.Reset();
}

FulingSystem::~FulingSystem()
{

}

bool FulingSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	equip_data_ = &data->equips_data;
	return true;
}

void FulingSystem::Save(RoleData* data)
{

}

void FulingSystem::Destroy()
{
}

const EquipSlotData* FulingSystem::GetEquipData(int posId)
{
	if (posId < EquipSlotType_Hats || posId  > EquipSlotType_Shield) return nullptr;
	return &equip_data_->slot_data[posId];
}

void FulingSystem::SetLevelInfo(int posId, int level, int exp)
{
	if (posId < EquipSlotType_Hats || posId  > EquipSlotType_Shield) return;

	EquipSlotData &pSlotData = equip_data_->slot_data[posId];

	pSlotData.fuling_lv = level;
	pSlotData.fuling_exp = exp;
}

