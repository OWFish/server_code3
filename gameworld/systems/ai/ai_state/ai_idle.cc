#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "ai_idle.h"


AIIdle::AIIdle(AI* ai_mgr, Creature *mon, const AIEventConfigs *config, int frame_time)
:AIState(ai_mgr, mon, config, frame_time)
, aggressive_timer_(600)
{
}

AIIdle::~AIIdle()
{

}

void AIIdle::Update(int64_t now_t)
{
	if (ai_mgr_->Aggressive() && aggressive_timer_.CheckAndSet(now_t)) {
		// 检查周围是否有目标
		if (CheckEnemy()) {
			ai_mgr_->ToState(AI::asBattle);
			return;
		}
	}
	AIState::Update(now_t);

	Entity *master = (Entity*)self_->GetMaster();
	if (master && self_->CanMove()) {
		const Point& mpos = master->GetPosition();
		const Point& spos = self_->GetPosition();
		int size = GRIDSIZE;
		if (abs(mpos.x-spos.x) > size || abs(mpos.y-spos.y) > size)
		{
			PathToMaster(size);
		}
	}
}

void AIIdle::OnAttacked(Creature *enemy)
{
	if(!ai_mgr_->Aggressive()) {
		self_->SetTarget(enemy);
		ai_mgr_->ToState(AI::asBattle);
	}
}

void AIIdle::Reset()
{
	// 检查血量恢复至100%，有可能从战斗中回到该状态。
	static GameEngine* ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	for (std::size_t i = 0; i < events_.size(); ++i)
	{
		events_[i].Reset(now_t, false);	// idle状态要保留部分状态
	}
	state_start_time_ = static_cast<int>(now_t / 1000);

	// 仇恨清零
	if (self_->GetType() != EntityType_Role)
		ai_mgr_->ClearHatred();

}

// todo 这个功能应该独立出来以后放在monster身上，现在这么多状态，判断内容和CanAttack也有重复，以后再扩展肯定会改。
bool CheckAggresive(Creature *mon, Creature *tar)
{
	//if (tar->HasState(esStateDeath))

	//if (!mon->CanSee(tar))
		//return false;

	//if (!mon->CanAttack(tar, &errcode))
	if (!mon->IsEnemy(tar))
		return false;
	if (mon->GetActor() && mon->GetActor() == tar->GetActor())
		return false;
	return true;
}

bool AIIdle::CheckEnemy() {
	//如果在安全区域直接就不用检查了
	if (self_->InSafeArea())
		return false;

	Entity* found = NULL;
	if (self_->GetMaster()) {
		found = self_->GetMaster()->GetTarget();
	}
	//如果目标消失了 就找仇恨列表的面的 没有找到再走正常流程
	if (!found && self_->GetType() == EntityType_Role)
	{
		found = self_->GetAI()->GetFirstDamage();
	}
	if(!found) {
		static VisiHandleList* visibleList = &GameEngine::global_var_->ai_visible_list_;
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();

		visibleList->clear();

		int self_x, self_y;
		self_->GetPosition(self_x, self_y);

		EntityHandle enemy_handle;

		// 视野
		int vision = ai_mgr_->GetVision();
		if (vision <= 0) return false;

		Scene *scene = self_->GetScene();
		if (!scene) return false;
	
		// 视野内对象
		//scene->GetEntityList(self_x, self_y, *visibleList, vision);
		scene->GetEntityListReDrop(*visibleList, self_);
		int cnt = visibleList->count();
		EntityHandle *list = *visibleList;

	
		int min_dist = vision * GRIDSIZE;
		for (int i = 0; i < cnt; ++i)
		{
			Entity *et = em->GetEntity(list[i]);
			if (!et || et == self_)
				continue;
			if ((et->IsCreature() && CheckAggresive(self_, (Creature*)et)) || CheckPickUp(et) ) {
				int dist = GetDistance(et);
				if (dist < min_dist)
				{
					if (self_->GetType() == EntityType_Role && et->GetType() == EntityType_Role)
					{
						int pkMode = self_->GetActor()->GetBasicData()->field_pk_mode;
						//如果pk模式是0 就是和平模式
						if (pkMode)
						{
							//行会模式选中附近玩家
							if (pkMode == 1 && self_->GetActor()->GetBasicData()->guild_id_ == et->GetActor()->GetBasicData()->guild_id_)
							{
								continue;
							}
							found = et;
							min_dist = dist;
							//break;
						}
					}
					else if (self_->GetType() == EntityType_Monster && ((Monster*)self_)->GetMonType() == MonsterType_Pet && et->GetType() == EntityType_Role)
					{
						auto pMaster = self_->GetMaster();
						if (!pMaster)
						{
							continue;
						}

						auto pActor = pMaster->GetActor();
						if (!pActor)
						{
							continue;
						}

						auto pBasicData = pActor->GetBasicData();
						if (!pBasicData)
						{
							continue;
						}

						//玩家宝宝攻击玩家 要判断宝宝主人的攻击模式
						if (pBasicData->field_pk_mode == 0)
						{
							continue;
						}

						if (pBasicData->field_pk_mode == 1 
							&& pBasicData->guild_id_ > 0 
							&& et->GetActor() 
							&& et->GetActor()->GetBasicData()->guild_id_ == pBasicData->guild_id_)
						{
							continue;
						}

						/*
						if (self_->GetMaster() && self_->GetMaster()->GetActor()->GetBasicData()->field_pk_mode == 0)
							continue;
						if (self_->GetMaster() && self_->GetMaster()->GetActor()->GetBasicData()->field_pk_mode == 1 && self_->GetMaster()->GetActor()->GetBasicData()->guild_id_ > 0 && et->GetActor() && et->GetActor()->GetBasicData()->guild_id_ == self_->GetMaster()->GetActor()->GetBasicData()->guild_id_)
							continue;
						*/
						
						found = et;
						min_dist = dist;
						//break;
					}
					else
					{
						found = et;
						min_dist = dist;
						//break;
					}

				}
			}
		}
	}
	if (found)
	{
		if (found->GetType() == EntityType_Role)
		{
			self_->SetTarget(found->GetActor()->GetLiveByJob());
			//self_->SetTarget(found);
		}	
		else
			self_->SetTarget(found);
		ai_mgr_->ToState(AI::asBattle);
		return true;
	}
	return false;
}

bool AIIdle::CheckPickUp(Entity * et)
{
	//是否可捡取的掉落物
	if(self_->GetType() == EntityType_Role && et->GetType() == EntityType_DropBag) {
		if (self_->GetActor()->GetLiveByJob() != self_) return false;//镜头角色才能去掉落
		DropBag* drop = (DropBag*)et;
		if (/*drop->GetFlag() == false && */drop->CanGetDrop(self_->GetActor()))
		{
			if (drop->GetBelongId() == 0 || drop->GetBelongId() == self_->GetActor()->GetActorId()) {
				return true;
			}
		}
	}
	return false;
}
