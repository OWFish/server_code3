#include "StdAfx.h"
#include "neigong_system.h"
#include "db/actor_db_data.h"
#include "neigong_config.h"


NeigongSystem::NeigongSystem(Creature *self)
: self_(self)
, last_time(0)
{
	attribute_.Reset();
}

NeigongSystem::~NeigongSystem()
{

}

bool NeigongSystem::Init(RoleData* data)
{
	if (data == NULL)
		return false;

//	ScriptValueList arg;
//	arg << role_->GetActor();
//	arg << role_->GetId();
//	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
//	luaScript.Call("neiGongAttrInit", &arg, &arg, 0);
	return true;
}

void NeigongSystem::Save(RoleData* data)
{
}

void NeigongSystem::LogicRun(int64_t curr_t)
{
	//if (true == role_->IsBattle()) return;
	//if (self_->GetType() != EntityType_Role && self_->GetType() != EntityType_CloneRole) return;
	switch (self_->GetType()) //获取一次实体类型
	{
	case EntityType_Role: //玩家
	{
		Actor* actor = ((Role*)self_)->GetActor();
		if (actor && actor->IsImage()) return; //排除镜像
		break;
	}
	case EntityType_CloneRole://天梯克隆人
		break;
	default://其余类型不恢复内功
		return;
	}

	if (last_time < curr_t)
	{
		last_time = curr_t + NeigongConfig::GetIntervalTime();
		double np = self_->GetAttr(Attribute::atNeiGong);
		double maxNp = self_->GetAttr(Attribute::atNeiGongMax);
		if (np < maxNp) 
		{
			int value = 0;

			if (NeigongConfig::GetPrecent())
				value += static_cast<int>( NeigongConfig::GetPrecent() / 100.0 * maxNp);

			value += static_cast<int>( self_->GetAttr(Attribute::atNeiGongRestore));

			self_->ChangeNp(value);
		}
	}
}

void NeigongSystem::Destroy()
{
}

Attribute* NeigongSystem::GetNeigongAttr()
{
	return &attribute_;
}

void NeigongSystem::CalcAttribute(bool notify)
{
	self_->CalcAttributes();
}

void NeigongSystem::AddAttr(int type, int value)
{
	attribute_.Add((Attribute::AttributeType)type, value);
}

void NeigongSystem::ClearAttr()
{
	attribute_.Reset();
}
