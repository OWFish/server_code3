#include "StdAfx.h"
#include "bless_system.h"
#include "db/actor_db_data.h"


BlessSystem::BlessSystem(Role *role)
	: role_(role)
	, equip_data_()
{
	attribute_.Reset();
}

BlessSystem::~BlessSystem()
{

}

bool BlessSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	equip_data_ = &data->equips_data;

	return true;
}

void BlessSystem::Save(RoleData* data)
{

}

void BlessSystem::Destroy()
{
}

void BlessSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void BlessSystem::SetLevel(int posId, int level)
{
	//EquipSlotData &pSlotData = equip_data_->slot_data[posId];
	//pSlotData.tupo_lv = level;
}

std::vector<int> BlessSystem::GetBlessData()
{
	std::vector<int> blessList;

	for (int pos = EquipSlotType_Weapon; pos < EquipSlotType_Max; ++pos)
	{
		EquipSlotData &pSlotData = equip_data_->slot_data[pos];
		blessList.push_back(pSlotData.bless_lv);
	}
	return blessList;
}


