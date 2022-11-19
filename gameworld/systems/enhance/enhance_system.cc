#include "StdAfx.h"
#include "enhance_system.h"
#include "db/actor_db_data.h"


EnhanceSystem::EnhanceSystem(Role *role)
: role_(role)
, Equip_Data_()
{
	attribute_.Reset();
}

EnhanceSystem::~EnhanceSystem()
{

}

bool EnhanceSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	Equip_Data_ = &data->equips_data;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("enhanceAttrInit", &arg, &arg, 0);
	return true;
}

void EnhanceSystem::Save(RoleData* data)
{

}

void EnhanceSystem::Destroy()
{
}

void EnhanceSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void EnhanceSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void EnhanceSystem::ClearAttr()
{
	attribute_.Reset();
}


void EnhanceSystem::SetLevel(int posId, int level)
{
	EquipSlotData &pSlotData = Equip_Data_->slot_data[posId];
	pSlotData.strength_lv = level;
}


