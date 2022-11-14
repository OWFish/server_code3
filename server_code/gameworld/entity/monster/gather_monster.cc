#include "StdAfx.h"
#include "monster_config.h"
#include "actor/actor.h"
#include "gather_monster.h"
#include "flags_handle.h"
#include "role/role_system.h"
#include "skill/status_system.h"
#include "fb_gather_handle.h"

GatherMonster::GatherMonster(void)
{
	SetType(EntityType_GatherMonster);
}

GatherMonster::~GatherMonster()
{
	SafeDelete(gather_monster_handle_);
}

void GatherMonster::CreateAppearData(DataPacket& appearPack)
{
	Creature::CreateAppearData(appearPack);
}

void GatherMonster::BeginGather(Actor* actor)
{
	if (!actor || gather_actor_  || !gather_monster_handle_) {
		return;
	}
	auto now_t =  ServerInstance()->Engine()->getTickCount();
	if(now_t <= wait_gather_time_) {
		OutputMsg(rmNormal, " 等待采集时间不足 %ld", (wait_gather_time_ - now_t) / 1000);
		return;
	}
	gather_actor_ = actor;
	gather_time_ = conf_->gatherTime * 1000;
	gather_time_ += now_t;
	gather_actor_->SetCurrGatherMonster(this);
	if (!gather_monster_handle_->BeginGather(actor))
	{
		OutputMsg(rmNormal, " %d 采集条件 %d", actor->GetActorId(), GetId());
		gather_actor_->SetCurrGatherMonster(nullptr);
		gather_actor_ = nullptr;

		return;
	}
	OutputMsg(rmNormal, " %d 开始采集 %d", gather_actor_->GetActorId(), GetId());
}

void GatherMonster::EndGather(bool succeed)
{
	if (gather_actor_ == nullptr) {
		return;
	}

	if (succeed == false) {
		OutputMsg(rmNormal, " %d  采集 %d  失败", gather_actor_->GetActorId(), GetId());
	} else {
		OutputMsg(rmNormal, " %d 采集 %d 成功", gather_actor_->GetActorId(), GetId());
	}

	if (gather_monster_handle_)	{
		gather_monster_handle_->EndGather(succeed);
	}
	ClearGatherActor();
	ReSet();

	if (GetGatherMonsterType() == FLAGS) {
		wait_gather_time_ = ServerInstance()->Engine()->getTickCount();
	}

}


int GatherMonster::GetId(void)
{
	return id_;
}

bool GatherMonster::Init(int id)
{
	MonsterConfig* conf = (MonsterConfig*)MonsterConfigPool::Get(id);
	if (!conf)
	{
		OutputMsg(rmError, " inti GatherMonster not config %d ", id);
		return false;
	}
	if (gather_monster_handle_)
	{
		OutputMsg(rmError, " 重复初始化 ");
		return false;
	}
	conf_ = conf;
	ReSet();
	return true;
}

GatherMonsterHandle* GatherMonster::CreateHadnle(GatherMonsterType type)
{

	GatherMonsterHandle* ret = nullptr;
	switch (type)
	{
	case FLAGS:
		ret = new FlagsHandle();
		break;
	case FBGATHER:
		ret = new FbGatherHandle();
		break;
	default:
		OutputMsg(rmError, " %d 没有这种类型的 hadnle ", type);
		break;
	}
	if (ret)
	{
		ret->SetGatherMonster(this);
		ret->Init();
	}
	return ret;
}

void GatherMonster::LogicRun(int64_t curr_t)
{
	curr_t = ServerInstance()->Engine()->getTickCount();
	Creature::LogicRun(curr_t);
	if (gather_actor_ && gather_time_ <= curr_t) {
		EndGather(true);
	}

	if(gather_monster_handle_ && !is_call_time_out_ && wait_gather_time_ <= ServerInstance()->Engine()->getTickCount())	{
		gather_monster_handle_->OnWaitTimeTimeOut();
		OutputMsg(rmNormal, " 等待采集时间超时 ");
		is_call_time_out_ = true;
	}

	if (gather_monster_handle_)
	{
		gather_monster_handle_->LogicRun(curr_t);
	}

}

GatherMonsterType GatherMonster::GetGatherMonsterType(void)
{
	if (conf_ == nullptr)
	{
		OutputMsg(rmError, "没有这初始化");
		return GATHER_MONSTER_TYPE_MAX;
	}
	else
	{
		return (GatherMonsterType)conf_->gatherMonsterType;
	}
}

void GatherMonster::OnChangeHp(double& value,Role* role)
{
	if(!gather_actor_) {
		return;
	}
	gather_monster_handle_->OnChangeHp(value,role);

}

bool GatherMonster::CanMove()
{
	if (!gather_actor_) {
		return true;
	}
	return gather_monster_handle_->CanMove();
}

void GatherMonster::OnAddStatus(int status)
{
	if (!gather_actor_) {
		return;
	}
	
	if (GatherMonsterType::FBGATHER == GetGatherMonsterType()) {
		if(status == StatusType_Stun || status == StatusType_Bind || status == StatusType_Frozen)
			EndGather(false);
	}
}

void GatherMonster::ReSet(void)
{
	EndGather(false);
	if(conf_)
	{

		if (is_call_time_out_ == false)
		{
			wait_gather_time_ = conf_->waitGatherTime * 1000;
			wait_gather_time_ += ServerInstance()->Engine()->getTickCount();
		}	
		id_ = conf_->id;
		if (gather_monster_handle_)
		{
			gather_monster_handle_->ReSet();
		}
		else
		{
			gather_monster_handle_ = CreateHadnle(GetGatherMonsterType());
		}
	}
}



void GatherMonster::ClearGatherActor()
{
	if (gather_actor_ == nullptr)
	{
		return;
	}
	gather_actor_->SetCurrGatherMonster(nullptr);
	gather_actor_ = nullptr;
}

