#include "StdAfx.h"

#include "ai_battle.h"
#include "entity/monster/monster.h"
#include "skill/skill_system.h"
#include "script/interface/actor_export_fun.h"

#include "actor/actor.h"
#include "role/role_system.h"
#include "move/move_system.h"



AIBattle::AIBattle(AI* ai_mgr, Creature *mon, const AIEventConfigs *conf, int frame_time)
:AIState(ai_mgr, mon, conf, frame_time)
, last_walk_time_(0)
{
	skill_dis_ = ai_mgr->GetSkillMinDist();
}

AIBattle::~AIBattle()
{

}

void AIBattle::Update(int64_t now_t)
{
	// 检查是否有目标(目标是否死亡,跳出场景)
	//		如果没有了，尝试重新选择目标
	//		仍然没有的话切换back状态 ai_mgr_->ToState(AI::asBack);
	// ***检查目标距离是否超出视野（战斗后变成2倍，会不会好点？）
	// ***		尝试重新选择目标 or 直接返回
	// 检查是否超出追击范围
	//		返回 ai_mgr_->ToState(AI::asBack);

	//如果自己在安全区域就不攻击玩家了 lxl
	if (self_->InSafeArea()) 
	{
		ai_mgr_->ToState(AI::asIdle);
		return;
	}

	Entity* et = self_->GetTarget();

	if (NULL == et) {
		if (ai_mgr_->ReturnHome())
			ai_mgr_->ToState(AI::asBack);
		else
			ai_mgr_->ToState(AI::asIdle);

		last_attack_hdl_ = EntityHandle();
		return;
	}

	if(et->GetType() != EntityType_DropBag) {
		//如果副本结束的时候; 还有非掉落物为目标;直接回到空闲AI寻找掉落物品来捡
		if (!self_->GetFuBen() || !self_->GetFuBen()->IsFb() || self_->GetFuBen()->IsEnd())	{
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asIdle);
			return;
		}
	} 

	//自己和目标都是玩家的时候, 目标死亡了,去打第二个角色
	if (et->GetType() == EntityType_Role && self_->GetType() == EntityType_Role && et->IsDeath()) {
		auto acotr = et->GetActor();
		auto role = acotr->GetLiveByJob();
		auto rs = self_->GetActor()->GetRoleSystem();
		for (int i = 0;i < MAX_ROLE; ++i) {
			auto r = rs->GetRoleById(i);
			if (r && !r->IsDeath()) {
				r->SetTarget(role);
				r->GetAI()->ToState(AI::asBattle);
				if (r->GetBattlePet()) {
					r->GetBattlePet()->SetTarget(role);
					r->GetBattlePet()->GetAI()->ToState(AI::asBattle);
				}
			}
		}
		return;
	}
	
	////如果是玩家要随时更新仇恨列表
	//if(self_->GetType() == EntityType_Role)
	//	ai_mgr_->UpdateHatred();
	//目标和自己不在一个场景里面或者目标已经死了
	if (et->GetPosInfo().scene != self_->GetPosInfo().scene || et->IsDeath() || et->InSafeArea()) {
		if (self_->GetType() == EntityType_Role) {
			//ai_mgr_->ClearHatred();  //打死目标不清空仇恨值
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asIdle);
			return;
			//获取玩家的第一个仇恨列表玩家
			//et = ai_mgr_->GetFirstDamage();
			//self_->SetTarget(et);
			//if (et)
			//	ai_mgr_->ToState(AI::asBattle);
			//else 
			//{
			//	ai_mgr_->ToState(AI::asIdle);
			//	return;
			//}

		} else {
			et = FindOtherEnemy();
			if(!et) {
				self_->SetTarget(NULL);
				ai_mgr_->ToState(AI::asBack);
				return;
			}
		}
	}

	//与目标的距离
	int et_dis = GetDistance(et);

	// 如果有回归, 距离目标太远,正常回归
	if (ai_mgr_->ReturnHome()) {
		//离家的距离
		int home_dis = ::GetPixDistance(self_->GetPosition(), ai_mgr_->GetBackPos(), 0);
		int home_range = ai_mgr_->GetHomeRange() * GRIDSIZE;
		if (home_dis > home_range || et_dis > home_range) {
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asBack);
			return;
		}
	}

	//目标是特殊类型的在这里处理
	if (et->GetType() == EntityType_GatherMonster) {
		if (et_dis <= 1)
		{
			if (self_->GetType() == EntityType_Role)
			{
				GatherMonster* gather = (GatherMonster*)et;
				Role* role = (Role*)self_;
				if (role->GetActor() && role == role->GetActor()->GetLiveByJob()) {
					gather->BeginGather(role->GetActor());
				}
			}
			self_->SetTarget(nullptr);
			//ai_mgr_->ToState(AI::asIdle);
		}
		else if (self_->CanMove())
		{
			if (!IsExistFubenPathLine(et))
			{
				PathToTarget(et->GetPosition(), 1);
			}
		}
		return;
	} else if (et->GetType() == EntityType_DropBag) {
		if (et_dis <= 1)
		{
			if (self_->GetType() == EntityType_Role)
			{
				Role* role = (Role*)self_;
				((DropBag*)et)->GetDrop(role->GetActor());
			}
			self_->SetTarget(nullptr);
			ai_mgr_->ToState(AI::asIdle);
		}
		else if (self_->CanMove())
		{
			if (!IsExistFubenPathLine(et))
			{
				PathToTarget(et->GetPosition(), 1);
			}
		}
		return;
	}

	// 处理ai行为事件
	AIState::Update(now_t);

	// 检测技能相关是否可以攻击目标。 不能攻击时计算出要移动的目的地给移动系统
	if (self_->GetSkillSystem()->CheckPublicCd() && CheckState()) {
		// try attack
		const AiSkill *skill = ai_mgr_->CheckNextSkill(now_t);
		if (skill) { // 有可用技能

			if (skill->dis >= et_dis) {
				self_->ClearMoveLine();
				//在安全区不能打
				if (et->InSafeArea()) {
					if (self_->GetType() == EntityType_Role && self_->GetAI()) {
						self_->GetAI()->setPassivity(true);
						self_->SetTarget(NULL);
						ai_mgr_->ToState(AI::asIdle);
					} else {
						self_->SetTarget(NULL);
						ai_mgr_->ToState(AI::asBack);
					}
				} else {
					if (self_->GetSkillSystem()->AutoUseAISkill() == false)
					{
						int res = Attack(et, skill);
						if (res == SkillUseResult_Err) {
							self_->SetTarget(nullptr);
							ai_mgr_->ToState(AI::asIdle);
						}
					}

				}
			} else if (self_->CanMove()) {
				if (!IsExistFubenPathLine(et))
				{
					PathToTarget(et->GetPosition(), skill->dis-GRIDSIZE/4);
				}
			}
				
		} else {
			if (skill_dis_ < et_dis && self_->CanMove()) {
				if (!IsExistFubenPathLine(et)) {
					PathToTarget(et->GetPosition());
				}
			}
		}
	}
}

int AIBattle::Attack(Entity *tar, const AiSkill *skill) {
	if (!tar) { return SkillUseResult_Err; }
	auto skill_sys = self_->GetSkillSystem();
	if (!skill) { return SkillUseResult_Err;	}
	int res = skill_sys->UseSkill(skill->skill_id, skill->index);
	if (self_->GetType() == EntityType_Role && tar->GetType() == EntityType_Role) {
		auto master = tar->GetActor();
		auto actor = self_->GetActor();
		if (master && actor && last_attack_hdl_ != master->GetHandle()) {
			ActorPacket npack;
			actor->AllocPacket(npack);
			npack << (char)Protocol::CMD_GuildBattle;
			npack << (char)Protocol::sGuildBattleCmd_AttackInfo;
			npack << master->GetHandle();
			npack.flush();
			last_attack_hdl_ = master->GetHandle();
		}
	}

	if(res != SkillUseResult_OK) {
		static GameEngine* ge = GetGameEngine();
		ai_mgr_->OnUseSkill(skill->index, ge->getTickCount() + skill->cd);
	}
	return res;
}

void AIBattle::Reset()
{
	AIState::Reset();
	ai_mgr_->SetBackPos(self_->GetPosition());
}
