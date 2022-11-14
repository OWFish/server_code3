#include "StdAfx.h"

#include <algorithm>
#include "ai_state/ai_born.h"
#include "ai_state/ai_idle.h"
#include "ai_state/ai_battle.h"
#include "ai_state/ai_back.h"
#include "ai_state/ai_dead.h"
#include "entity/monster/monster.h"
#include "entity/monster/monster_config.h"
#include "skill/skill_system.h"
#include "entity/role/role_system.h"
#include "skill_condition.h"


AI::AI()
//: ai_()
: cur_state_(asBorn)
, ai_conf_(NULL)
//, skill_timer_(150)
, time_check_(100)
, next_skill_index_(-1)
//, skill_cd_()
, back_pos(0,0)
{
	memset(ai_, 0, sizeof(ai_));
	memset(skill_cd_, 0, sizeof(skill_cd_));
}

AI::~AI()
{
	for (int i = 0; i < asMax; ++i)
	{
		if (ai_[i])
			SafeDelete(ai_[i]);
	}
}

bool AI::Init(Creature *self, const AIConfig *conf)
{
	if (!conf) return false;
	if (!self) return false;

	self_ = self;
	ai_conf_ = conf;
	id = conf->id;
	
	ai_[asBorn] = new AIBorn(this, self, &conf->born, 300);
	ai_[asIdle] = new AIIdle(this, self, &conf->idle, 800);
	ai_[asBattle] = new AIBattle(this, self, &conf->battle, 99);
	ai_[asBack] = new AIBack(this, self, &conf->back, 500);
	ai_[asDead] = new AIDead(this, self, &conf->dead, 300);

	for (std::size_t i = 0; i < conf->skills.size(); ++i)
		self->GetSkillSystem()->AddSkill(conf->skills[i].skill_id);

	ToState(asBorn);

	return true;
}

void AI::Update(int64_t now_t)
{
	if (time_check_.CheckAndSet(now_t, true))
	{
		ai_[cur_state_]->Update(now_t);
	}
}

void AI::OnAttacked(Creature *enemy, double damage)
{
	if (enemy == NULL) return;
	//玩家也要仇恨列表  玩家不拿怪物的仇恨
	if (self_->GetType() == EntityType_Role && enemy->GetType() != EntityType_Role) return; //玩家拿仇恨列表没什么意义
#ifdef _MSC_VER 
	if(self_->GetActor() && enemy->GetActor()) assert(self_->GetActor() != enemy->GetActor());
#endif
	EntityHandle hdl = enemy->GetHandle();
	if (ai_conf_->maxDam) {
		Actor *actor = enemy->GetActor();
		if (actor) {
			hdl = actor->GetHandle();
		}
	}

	bool found = false;
	for (std::size_t i = 0; i < damage_list_.size(); ++i)
	{
		if (damage_list_[i].target == hdl){
			damage_list_[i].damage += damage;
			found = true;
			break;
		}
	}
	if (!found){
		DamageInfo info;
		info.target = hdl;
		info.damage = damage;
		damage_list_.push_back(info);
		is_add_damage_list = true;
	}

	ai_[cur_state_]->OnAttacked(enemy);
}

void AI::OnDeath()
{
	ToState(asDead);
	//ClearHatred();
}

void AI::ToState(State s)
{
	cur_state_ = s;
	ai_[cur_state_]->Reset();
}

void AI::OnEnterScene()
{
	ai_[cur_state_]->OnEnterScene();
}

bool AI::Aggressive()
{
	if (ai_conf_)
	{
		auto master = self_->GetMaster();
		if (
			master 
			&& 
			master->IsCreature()
			&& 
			((Creature*)master)->GetBattlePet() == self_
			)
		{
			auto ai = ((Creature*)master)->GetAI();
			if (ai && !ai->passivity_)
			{
				return ai->ai_conf_->aggressive;
			}
		}
		else
		{
			if (!passivity_)
			{
				return ai_conf_->aggressive;
			}
		}
		

		
	}
		
	return false;
}

void AI::setPassivity(bool b)
{
	passivity_ = b;
	if (b && self_->GetBattlePet()) {
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		//em->DestroyEntity(self_->GetBattlePet()->GetHandle(), true);
	}
}

bool AI::getPassivity() {
	return passivity_;
}

bool AI::CanRecover()
{
	if (ai_conf_)
		return ai_conf_->can_recover;
	return false;
}

int AI::GetDeadStateTime()
{
	if (ai_conf_)
		return ai_conf_->dead_time;
	return 0;
}

int AI::GetVision()
{
	if (ai_conf_)
		return ai_conf_->vision;
	return 0;
}

bool AI::ReturnHome()
{
	return GetHomeRange() > 0;
}

int AI::GetHomeRange()
{
	if (ai_conf_)
		return ai_conf_->home_range;
	return 0;
}

const AiSkill* AI::FindRoleNextSkill(int64_t now_t)
{
	auto pRole = (Role*)self_;
	auto pRoleData = pRole->GetData();

	//优先判断临时添加的技能列表
	{
		//std::vector<Skill*> sklList = pRole->GetSkillSystem()->GetSkillList();
		//int sklLengh = sklList.size();
		//for (int i = 0;i < sklLengh;++i)
		//{
		//	if (self_->GetSkillSystem()->GetSkillLaveCD((sklList[i]->GetId())) <= 0)
		//	{
		//		auto pSkillSys = self_->GetSkillSystem();
		//		if (pSkillSys->FindSkillIsActive(skill_id))
		//		{
		//			return &pAISkill;
		//		}
		//		else
		//		{
		//			OutputMsg(rmError, "AISkillFindRoleNextSkill WRONG , Find Skill Not Active,  skill_ID : %d", skill_id);
		//		}
		//	}
		//}


	}


	int next_skill_index = pRole->GetAILastUseSkill()+1; //上一个使用的技能下标
	if (next_skill_index >= MAX_SKILL_COUNT)
	{
		next_skill_index = 0;
	}

	for (int i = next_skill_index; i < 8; ++i)
	{
		if (now_t > skill_cd_[i]) 
		{
			int skill_index = pRoleData->skills.skill_index[i];
			if (i > 0 && skill_index <= 0)
			{
				continue;
			}

			if (skill_index >= ai_conf_->skills.size())
			{
				OutputMsg(rmError, "AISkill Choice Skill WRONG , Can Not Find Skill Index By AIConfig skill_index : %d", skill_index);
				skill_index = 0;
			}

			const AiSkill& pAISkill = ai_conf_->skills[skill_index];		//通过下标获取对应的技能id
			int skill_id = pAISkill.skill_id;
			if (self_->GetSkillSystem()->GetSkillLaveCD(skill_id) <= 0)
			{
				if (SkillCondition::Check(&(pAISkill.cond), self_)) {
					auto pSkillSys = self_->GetSkillSystem();
					if (pSkillSys->FindSkillIsActive(skill_id))
					{
						return &pAISkill;
					}
					else
					{
						OutputMsg(rmError, "AISkillFindRoleNextSkill WRONG , Find Skill Not Active,  skill_ID : %d", skill_id);
					}
					
				}
			}
		}
	}
	
	return  &ai_conf_->skills[0];
}

const AiSkill* AI::CheckNextSkill(int64_t now_t)
{
	//if (skill_timer_.CheckAndSet(now_t))
	//RefreshNextSkill(now_t);
	//return next_skill_index_ != -1;

	if (!ai_conf_) return NULL;

	if (self_->GetType() == EntityType_Role)
	{
		return FindRoleNextSkill( now_t);
	}

	// 查找是否有可用技能
	size_t count = ai_conf_->skills.size();

	for (std::size_t i = 0; i < count && i < MAX_SKILL; ++i) {
		if (now_t > skill_cd_[i]) {
			const AiSkill& conf = ai_conf_->skills[i];
			if (self_->GetSkillSystem()->GetSkillLaveCD(conf.skill_id) <= 0) {
				if (conf.cond.type == 0 || SkillCondition::Check(&(conf.cond), self_)) {
					return &conf;
				}
			}
		}
	}
	return NULL;
}
/*
void AI::RefreshNextSkill(int64_t now_t)
{
	if (!ai_conf_) return;

	next_skill_index_ = -1;

	// 查找是否有可用技能
	size_t count = ai_conf_->skills.size();
	for (std::size_t i = 0; i < count && i < MAX_SKILL; ++i) {
		if (now_t > skill_cd_[i]) {
			const AiSkill& conf = ai_conf_->skills[i];
			if (conf.cond.type == 0 || SkillCondition::Check(&(conf.cond), self_)) {
				next_skill_index_ = i;
				return;
			}
		}
	}
	return;
}

int AI::GetNextSkillDist()
{
	if (next_skill_index_ == -1)
	{
		return 0;
	}

	return ai_conf_->skills[next_skill_index_].dis;
}
*/
int AI::GetSkillMinDist()
{
	int min = 0;
	for (std::size_t i = 0; i < ai_conf_->skills.size(); ++i)
	{
		if (min == 0 || ai_conf_->skills[i].dis < min)
			min = ai_conf_->skills[i].dis;
	}
	return min;
}
/*
const AiSkill* AI::GetNextSkill()
{
	if (next_skill_index_ == -1)
		return NULL;
	return &(ai_conf_->skills[next_skill_index_]);
}
*/
void AI::OnUseSkill(int index, int64_t time)
{
	skill_cd_[index] = time;
}

const Point& AI::GetBackPos()
{
	return back_pos;
}

void AI::SetBackPos(const Point& pos)
{
	back_pos = pos;
}

void AI::ClearHatred()
{
	damage_list_.clear();
	is_add_damage_list = true;
}
void AI::DeleteHatred(EntityHandle hd)
{
	std::vector<AI::DamageInfo>::iterator it = damage_list_.begin();
	for (; it != damage_list_.end(); ++it)
	{
		if (it->target == hd)
		{
			damage_list_.erase(it);
			return;
		}
	}
}
bool AI::UpdateHatred()
{
	bool IsUpdate = is_add_damage_list;
	is_add_damage_list = false;
	//获取玩家的视野范围
	int dest = GetVision();
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	std::vector<AI::DamageInfo>::iterator it = damage_list_.begin();
	for (; it != damage_list_.end();){
		Entity *et = em->GetEntity(it->target);
		//仇恨列表里找到的实体是不是空或不在一个场景
		if (NULL == et || et->GetPosInfo().scene != self_->GetPosInfo().scene)
		{
			if (self_->GetTargetHdl() == it->target)
				self_->SetTarget(NULL);
			it = damage_list_.erase(it);
			IsUpdate = true;

			continue;
		}
		//如果超出了距离 或者角色死亡 玩家进入安全区就清除掉仇恨
		int dis = ::GetPixDistance(self_->GetPosition(), et->GetPosition(),0);
		if ((dest > 0 && dis > dest * GRIDSIZE) || et->IsDeath() || et->InSafeArea())
		{
			if (self_->GetTargetHdl() == it->target)
				self_->SetTarget(NULL);
			it = damage_list_.erase(it);
			IsUpdate = true;
			continue;
		}
		++it;
	}
	return IsUpdate;
}
Entity* AI::GetFirstDamage()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	std::vector<AI::DamageInfo>::iterator it = damage_list_.begin();
	if (it != damage_list_.end()) {
		Entity *et = em->GetEntity(it->target);
		//仇恨列表里找到的实体是不是空或不在一个场景
		if (NULL == et || et->GetPosInfo().scene != self_->GetPosInfo().scene)
		{
			return NULL;
		}
		//如果超出了距离 或者角色死亡就清除掉仇恨
		int dis = ::GetPixDistance(self_->GetPosition(), et->GetPosition(), 0);
		if(dis > GetVision() * GRIDSIZE)
		{
			return NULL;
		}
		//if (et->GetType() == EntityType_Role)
		//	return et->GetActor()->GetRoleSystem()->GetRoleById(0);
		return et;
	}
	return NULL;
}
const AI::HatredList& AI::GetHatred()
{
	std::sort(damage_list_.begin(), damage_list_.end());
	return damage_list_;
}

void AI::PathToTarget(int gx, int gy)
{
	ai_[cur_state_]->PathToTarget(Point(gx, gy));
}

Entity* AI::SetTargetByDamageList(void)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	const AI::HatredList &hatred_list = GetHatred();
	for (std::size_t i = 0; i < hatred_list.size(); ++i) {
		Entity *et = em->GetEntity(hatred_list[i].target);
		//仇恨列表里找到的实体是不是空或不在一个场景
		if (NULL == et || et->GetPosInfo().scene != self_->GetPosInfo().scene) continue;
		//如果是个玩家,这里按战法道来打
		Actor* actor = et->GetActor();
		if (actor) {
			et = actor->GetLiveByJob();
		}
		//仇恨列表里的这个玩家的角色全死光,或者这个实体是死亡状态的
		if (!et || et->IsDeath()) continue;
#ifdef _MSC_VER 
		assert(et->GetType() != EntityType_Actor);
#endif
		self_->SetTarget(et);
		return et;
	}
	return NULL;
}

void AI::ChangeTarget(int type)
{
	if (type == 0) // 按伤害
	{
		SetTargetByDamageList();
	}
}


