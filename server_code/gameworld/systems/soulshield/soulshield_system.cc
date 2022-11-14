#include "StdAfx.h"
#include "soulshield_system.h"
#include "db/actor_db_data.h"


SoulshieldSystem::SoulshieldSystem(Role *role)
	: role_(role)
{
	attribute_.Reset();
}

SoulshieldSystem::~SoulshieldSystem()
{

}

bool SoulshieldSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	loogsoulData_ = &data->loogsoul_data;
	//shielData_ = &data->shield_data;
	//xueyuData_ = &data->xueyu_data;

	ScriptValueList arg;
	arg << role_->GetActor();
	arg << role_->GetId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("soulShieldAttrInit", &arg, &arg, 0);
	return true;
}

void SoulshieldSystem::Save(RoleData* data)
{

}

void SoulshieldSystem::Destroy()
{
}

void SoulshieldSystem::CalcAttribute(bool notify)
{
	role_->CalcAttributes();
}

void SoulshieldSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void SoulshieldSystem::ClearAttr()
{
	attribute_.Reset();
}

void SoulshieldSystem::SetLevel(int type, int level)
{
	switch (type)
	{
	case ssLoongSoul:
		{
			loogsoulData_->level = level;
			break;
		}
	}

}

void SoulshieldSystem::SetStage(int type, int stage)
{
	switch (type)
	{
	case ssLoongSoul:
	{
		loogsoulData_->stage = stage;
		break;
	}
	}

}

void SoulshieldSystem::SetExp(int type, int exp)
{
	switch (type)
	{
	case ssLoongSoul:
	{
		loogsoulData_->exp = exp;
		break;
	}
	}

}

void SoulshieldSystem::SetAct(int type, int act)
{
	switch (type)
	{
	case ssLoongSoul:
	{
		loogsoulData_->act = act ? 1 : 0;
		break;
	}
	//case ssShield:
	//{
	//	shielData_->act = act ? 1 : 0;
	//	break;
	//}
	//case ssXueyu:
	//{
	//	xueyuData_->act = act ? 1 : 0;
	//	break;
	//}
	}
}

const LoogsoulData* SoulshieldSystem::GetsoulData()
{
	return loogsoulData_;
}
/*
const ShieldData* SoulshieldSystem::GetshielData()
{
	return shielData_;
}

const XueyuData* SoulshieldSystem::GetxueyuData()
{
	return xueyuData_;
}
*/

/*
int SoulshieldSystem::GetLevel(int type)
{
	switch (type)
	{
	case ssLoongSoul:
		{
			return *loongsoul_level;
		}
	case ssShield:
		{
			return *shield_level;
		}
	case ssXueyu:
		{
			return *xueyu_level;
		}
	}
}
*/
