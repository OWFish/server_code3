#include "StdAfx.h"
#include "soul_system.h"
#include "db/actor_db_data.h"


SoulSystem::SoulSystem(Role *role)
: role_(role)
, equip_data_()
{
	attribute_.Reset();
	ex_attribute_.Reset();
}

SoulSystem::~SoulSystem()
{

}

bool SoulSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	equip_data_ = &data->equips_data;
	return true;
}

void SoulSystem::Save(RoleData* data)
{

}

void SoulSystem::Destroy()
{
}

const EquipSlotData* SoulSystem::GetEquipData(int posId)
{
	return &equip_data_->slot_data[posId];
}

void SoulSystem::SetLevel(int posId, int level)
{
	EquipSlotData &pSlotData = equip_data_->slot_data[posId];
	pSlotData.soul_lv = level;
}

