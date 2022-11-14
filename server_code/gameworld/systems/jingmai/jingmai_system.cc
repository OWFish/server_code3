#include "StdAfx.h"
#include "jingmai_system.h"
#include "db/actor_db_data.h"


JingmaiSystem::JingmaiSystem(Role *role)
: role_(role)
, jingmai_data_()
{
	attribute_.Reset();
}

JingmaiSystem::~JingmaiSystem()
{

}

bool JingmaiSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	jingmai_data_ = &data->jingmai_data;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("jingmaiAttrInit", &arg, &arg, 0);
	return true;
}

void JingmaiSystem::Save(RoleData* data)
{
	
}

void JingmaiSystem::Destroy()
{
}

void JingmaiSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void JingmaiSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void JingmaiSystem::ClearAttr()
{
	attribute_.Reset();
}

const JingMaiData* JingmaiSystem::GetJingmaiData()
{
	return jingmai_data_;
}

void JingmaiSystem::SetLevel(int level)
{
	jingmai_data_->level = level;
}

void JingmaiSystem::SetStage(int star)
{
	jingmai_data_->stage = star;
}
