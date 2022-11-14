#include "StdAfx.h"
#include "status_system.h"
#include "effect/skill_effect_system.h"
#include "creature.h"
#include "protocol/protos/skill_proto.h"


StatusSystem::StatusSystem(Creature *self)
: self_(self)
, frame_timer_(100)
{
	memset(status_list_, 0, sizeof(Status)* StatusType_Count);
}

StatusSystem::~StatusSystem()
{

}


void StatusSystem::AddStatus(Status &status)
{
	if (status.type < 0 || status.type >= StatusType_Count)
	{
		OutputMsg(rmError, "status type error:%d", status.type);
		return;
	}
	if (status.type == StatusType_Stun && CheckStatus(StatusType_ResStun))
		return;

	Status& st = status_list_[status.type];
	if (st.enabled){ // 替换
		if (st.end_time < status.end_time)
			st.end_time = status.end_time;

		if (st.effect_id != status.effect_id)
		{
			DelEffect(st.effect_id);
			AddEffect(status.effect_id);
			st.effect_id = status.effect_id;
		}
	}
	else { // 添加
		st.type = status.type;
		st.end_time = status.end_time;
		memcpy(&st.param, &status.param, sizeof(status.param));
		st.enabled = true;
		st.effect_id = status.effect_id;
		AddEffect(st.effect_id);
	}

	self_->OnAddStatus(status.type);
}

bool StatusSystem::CanMove()
{
	return (!CheckStatus(StatusType_Stun) || CheckStatus(StatusType_ResStun)) &&
		!CheckStatus(StatusType_Bind) && !CheckStatus(StatusType_Frozen);
}

bool StatusSystem::CanAttack()
{
	return (!CheckStatus(StatusType_Stun) || CheckStatus(StatusType_ResStun)) && !CheckStatus(StatusType_Frozen);
}

bool StatusSystem::CanControlled()
{
	return !CheckStatus(StatusType_Invincibility) &&
		!CheckStatus(StatusType_Armor);
}

bool StatusSystem::CanControll()  
{
	return (!CheckStatus(StatusType_Stun) || CheckStatus(StatusType_ResStun)) && !CheckStatus(StatusType_Frozen);
}

bool StatusSystem::CheckStatus(int type)
{
	if (type < 0 || type > StatusType_Count)
		return false;

	if (status_list_[type].enabled)
		return true;
	return false;
}

void StatusSystem::OnRun(int64_t now_t)
{
	if (!frame_timer_.CheckAndSet(now_t))
		return;

	for (int i = 0; i < StatusType_Count; ++i)
	{
		if (status_list_[i].enabled && status_list_[i].end_time < now_t)
		{
			status_list_[i].enabled = false;
			status_list_[i].end_time = 0;
			DelEffect(status_list_[i].effect_id);
			status_list_[i].effect_id = 0;
		}
	}
}

void StatusSystem::OnDamaged(double &damage, bool is_debuff )
{
	
	if (CheckStatus(StatusType_Invincibility))
	{
		damage = 0;
		// todo发消息
		return;
	}
	
	if (!is_debuff && CheckStatus(StatusType_Shild))
	{
		Status &shield = status_list_[StatusType_Shild];

		double damage_dec = floor(damage * shield.param.decrease_percent);
		if (shield.param.shield_power >= damage_dec)
		{
			shield.param.shield_power -= damage_dec;
			damage -= damage_dec;
		}
		else
		{
			damage_dec = shield.param.shield_power;
			damage -= shield.param.shield_power;
			shield.param.shield_power = 0;

			shield.enabled = false;
			shield.end_time = 0;
			DelEffect(shield.effect_id);
		}
		// todo发消息
	}

	// 这一定要放在最后
	if (CheckStatus(StatusType_HighestHurt))
	{
		Status &shield = status_list_[StatusType_HighestHurt];
		if (damage > (int)shield.param.highest_hurt)
		{
			damage = (int)shield.param.highest_hurt;
		}
	}

}


void StatusSystem::AddEffect(int id)
{
	if (id <= 0)
		return;
	Protocol::AddEffectProto msg;	// 添加特效
	msg.target_handle = self_->GetHandle();
	msg.id = id;
	self_->GetScene()->SendData(msg, self_->GetActor());
}

void StatusSystem::DelEffect(int id)
{
	if (id <= 0)
		return;
	Protocol::DelEffectProto msg;	// 删除特效
	msg.target_handle = self_->GetHandle();
	msg.id = id;
	self_->GetScene()->SendData(msg, self_->GetActor());
	self_->GetSkillEffectSystem()->DelEffect(id);
}


void StatusSystem::DelStatus(int type)
{
	Status& st = status_list_[type];
	if (st.enabled)
	{
		DelEffect(st.effect_id);
		st.enabled = false;
	}
}