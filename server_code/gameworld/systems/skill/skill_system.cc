#include "StdAfx.h"
#include "skill_system.h"
#include "skill.h"
#include "entity/creature.h"
#include "db/role_data.h"
#include "entity/role/role_system.h"
#include "systems/imba/imbasystem.h"
#include "systems/godweapon/godweaponsystem.h"
#include "status_system.h"
#include "ai/ai.h"

SkillSystem::SkillSystem(Creature* creature)
	: self_(creature)
	, public_cd_(GetGameEngine()->getTickCount())
	, max_delay_time_(0)
	, multiple_crit_cd_(0)//幸运一击的CD
	, attack_add_hp_cd_(0)//治疗特戒攻击补血的CD
	, stun_cd_(0)//麻痹cd
	, vampire_cd(0) //传世装备吸血cd
	, curse_cd(0)	//传世装备诅咒cd
	, death_curse_cd(0)//死咒触发CD(冷却时间)
	, hp_lt_add_buff_cd(0)//生命低于(万分比例)时,触发生命恢复buff的CD
	, hungu_cd(0)
	, mijizh_cd(0)//秘籍追魂CD
	, mijibq_cd(0)
	, last_time_crit(false)//上一次攻击是否暴击
{
	delay_damage_.clear();
	skill_rev_.clear();
}

SkillSystem::~SkillSystem()
{
	for (auto skill : skill_list_)
		SafeDelete(skill);
	for (int i = 0; i < PassiveSkillCond_Count; ++i)
	{
		for (auto skill : passive_skill_list_[i])
			SafeDelete(skill);
	}
	delay_damage_.clear();
	skill_rev_.clear();
}

int SkillSystem::GetRoleSkillId(int job, int index, int level)
{
	return (index + 1) * 1000 + job * 10000 + level;
}

bool SkillSystem::Init(RoleData *data)
{
	// 专门初始化role的
	int skill_power = 0;
	for (int i = 0; i < MAX_SKILL_COUNT; ++i)
	{
		int level = data->skills.skill_level[i];
		if (level > 0)
		{
			int id = GetRoleSkillId(data->job, i, level);
			AddSkill(id);

			skill_power += level*SkillConfigPool::GetSkillPowerPerLevel(i);
		}
	}
	skill_power_.Reset();
	skill_power_.SetExtraPower(skill_power);
	return true;
}

void SkillSystem::Save(RoleData *data)
{
	
}

bool SkillSystem::OnUpgradeSkill(int index)
{
	return true;
}

bool SkillSystem::CheckPublicCd()
{
	time_t now_t = GetGameEngine()->getTickCount();
	if (public_cd_ > now_t) // 纯服务端计算，不需要设置误差范围了
		return false;

	return true;
}

bool SkillSystem::OnCastSkill(int id, Entity* target)
{
	if (self_->IsDeath())
	{
		OutputMsg(rmWarning, "invalid cast skill role is dead. actor:%d", self_->GetMaster()->GetId());
		return false;
	}

	static auto ge = GetGameEngine();
	Skill* skill = FindSkill(id);
	if (!skill) {
		OutputMsg(rmWarning, "skill not found, id:%d", id);
		return false;
	}

	if (target && !target->IsCreature()) {
		OutputMsg(rmWarning, "skill target error.%p", target);
		return false;
	}
	if (!CheckPublicCd())
	{
		OutputMsg(rmWarning, "skill public cd. p:%lld, now:%lld", public_cd_, ge->getTickCount());
		return false;
	}

	skill->Cast(self_, (Creature*)target);
	public_cd_ = ge->getTickCount() +  1000000 / (int64_t)self_->GetAttr(Attribute::atAttackSpeed);

	
	return true;
}

bool SkillSystem::FindSkillIsActive(int id)
{
	id = id / 1000;	 // 去掉等级
	for (std::size_t i = 0; i < skill_list_.size(); ++i)
	{
		if (skill_list_[i] && skill_list_[i]->GetId() / 1000 == id)
			return true;
	}

	return false;
}

Skill* SkillSystem::FindSkill(int id)
{
	id = id / 1000;	 // 去掉等级
	for (std::size_t i = 0; i < skill_list_.size(); ++i)
	{
		if (skill_list_[i] && skill_list_[i]->GetId() / 1000 == id)
			return skill_list_[i];
	}
	return NULL;
}

Skill* SkillSystem::FindPassiveSkill(int id, int cond)
{
	if (cond < 0 || cond > PassiveSkillCond_Count) return NULL;
	for (std::size_t i = 0; i < passive_skill_list_[cond].size(); ++i)
	{
		if (passive_skill_list_[cond][i] && passive_skill_list_[cond][i]->GetId() == id)
			return passive_skill_list_[cond][i];
	}
	return NULL;
}

bool SkillSystem::AddSkill(int id)
{
	if (FindSkill(id))
		return false;

	Skill *skill = new Skill();
	if (!skill->Init(id))
	{
		delete skill;
		return false;
	}

	skill_list_.push_back(skill);
	return true;
}

bool SkillSystem::DelSkill(int id)
{
	for (std::size_t i = 0; i < skill_list_.size(); ++i)
	{
		if (skill_list_[i]->GetId() == id)
		{
			SafeDelete(skill_list_[i]);
			skill_list_[i] = skill_list_[skill_list_.size() - 1];
			skill_list_.pop_back();
			return true;
		}
	}
	return false;
}

bool SkillSystem::AddAISkill(int id)
{
	if (AddSkill(id) == false)
		return false;
	int len = aiSkillList.size();
	for (int i =0;i< len;++i)
	{
		if (aiSkillList[i] == id)
		{
			return false;
		}
	}
	aiSkillList.push_back(id);
	return true;
}

bool SkillSystem::DelAISkill(int id)
{
	if (DelSkill(id) == false)
		return false;
	std::vector<int>::iterator it = aiSkillList.begin();
	for (; it != aiSkillList.end(); ++it)
	{
		if (*it == id)
		{
			aiSkillList.erase(it);
			return true;
		}
	}

	return false;
}
bool SkillSystem::DelAllAISkill()
{
	std::vector<int>::iterator it = aiSkillList.begin();
	for (; it != aiSkillList.end(); ++it)
	{
		DelSkill(*it);
	}
	aiSkillList.clear();
	return false;
}
bool SkillSystem::DelSkillById(int id)
{
	for (std::size_t i = 0; i < skill_list_.size(); ++i)
	{
		if (skill_list_[i]->GetId() / 1000 == id)
		{
			SafeDelete(skill_list_[i]);
			skill_list_[i] = skill_list_[skill_list_.size() - 1];
			skill_list_.pop_back();
			return true;
		}
	}
	return false;
}

void SkillSystem::DelAllSkill(void) {
	for (std::size_t i = 0; i < skill_list_.size(); ++i) {
		SafeDelete(skill_list_[i]);
	}
	skill_list_.clear();
}

bool SkillSystem::AddPassiveSkill(int id)
{
	const SkillConfig *conf_ = SkillConfigPool::GetSkillConfig(id);
	if (!conf_) return false;
	if (conf_->passive.cond < 0 || conf_->passive.cond > PassiveSkillCond_Count) 
		return false;

	if (FindPassiveSkill(id, conf_->passive.cond))
		return false;
	
	Skill *skill = new Skill();
	if (!skill->Init(id))
	{
		delete skill;
		return false;
	}

	passive_skill_list_[conf_->passive.cond].push_back(skill);
	return true;
}

bool SkillSystem::DelPassiveSkill(int id)
{
	const SkillConfig *conf_ = SkillConfigPool::GetSkillConfig(id);
	if (!conf_) return false;
	if (conf_->passive.cond < 0 || conf_->passive.cond > PassiveSkillCond_Count)
		return false;
	auto &skill_list = passive_skill_list_[conf_->passive.cond];
	for (std::size_t i = 0; i < skill_list.size(); ++i)
	{
		if (skill_list[i]->GetId() == id)
		{
			SafeDelete(skill_list[i]);
			skill_list[i] = skill_list[skill_list.size() - 1];
			skill_list.pop_back();
			return true;
		}
	}
	return false;
}

bool SkillSystem::DelPassiveSkillById(int id)
{
	for (int i = PassiveSkillCond_Attack; i < PassiveSkillCond_Count; i++)
	{
		auto &skill_list = passive_skill_list_[i];
		for (std::size_t i = 0; i < skill_list.size(); ++i)
		{
			if (skill_list[i]->GetId()/1000 == id)
			{
				SafeDelete(skill_list[i]);
				skill_list[i] = skill_list[skill_list.size() - 1];
				skill_list.pop_back();
				return true;
			}
		}
	}
	return false;
}

void SkillSystem::OnPassiveEvent(int cond, Creature *target, double *val, Skill *inSkill)
{
 	auto &skill_list = passive_skill_list_[cond];
	for (std::size_t i = 0; i < skill_list.size(); ++i)
	{
		Skill* skill = skill_list[i];
		if (!skill) continue;
		if (!target) target = skill->SelectTarget(self_);
		if (!target) continue;
		auto &pc = skill->GetConfig()->passive;

		switch (cond)
		{
		case PassiveSkillCond_HpPer:  //生命值低于多少时
			if (self_->GetHp() / self_->GetMaxHp()*10000.0 <= pc.p1) break;
			continue;
		case PassiveSkillCond_KillTar:  //击杀对方
			if (pc.p1 == EntityType_Actor) {
				if (target->GetType() == EntityType_Actor || target->GetType() == EntityType_Role || target->GetType() == EntityType_CloneRole) {
					break;
				}
			}
			continue;
		//case PassiveSkillCond_Death:
		//	if (pc.p1 == JobType_None || pc.p1 == self_->GetJob())
		//		break;
		//	continue;
		}

		//判断概率
		if (wrand(10000) > (unsigned int)pc.rate) {
			continue;
		}
		
		if (PassiveSkillCond_AfterAttack == cond)
		{
			if (pc.p1 == 1)  //被攻击后伤害转移，先写死1类型吧，以后有其他需求再改
			{
				if (self_->GetJob() == pc.p2 || (inSkill && inSkill->GetConfig() && inSkill->GetConfig()->base.calc_type == SkillCalcType_TogetherHit)) {
					//伤害转移只能转移给别人，检查是不是配错表了
					//合击伤害也不能转移
					continue;
				}
				if (EntityType_Role == self_->GetType())
				{
					Role* list[MAX_ROLE] = { NULL };
					((Role*)self_)->GetActor()->GetRoleSystem()->GetRoles(list);
					for (int i = 0; i < MAX_ROLE; ++i)
					{
						Role* role = list[i];
						if (!role) continue;
						if (role->GetJob() == pc.p2 && val && role->GetHp() / role->GetMaxHp() > pc.p3 / 10000.0) {
							role->ChangeHp((*val)*pc.p4/10000.0, target);
							*val *= (1 - pc.p4 / 10000.0);
							break;
						}
					}
				}
				else if (EntityType_CloneRole == self_->GetType())
				{
					static EntityMgr *em = GetGameEngine()->GetEntityMgr();
					EntityHandle hdl;
					RoleClone *roleClone = nullptr;
					for (int i = 0; i < MAX_ROLE; ++i)
					{
						if (((RoleClone*)self_)->GetBuddy(i, hdl))
						{
							roleClone = static_cast<RoleClone*>(em->GetEntity(hdl));
							if (!roleClone) continue;
							if (roleClone->GetJob() == pc.p2 && val && roleClone->GetHp() / roleClone->GetMaxHp() > pc.p3 / 10000.0) {
								roleClone->ChangeHp((*val)*pc.p4 / 10000.0, target);
								*val *= (1 - pc.p4 / 10000.0);
								break;
							}
						}
					}
				}
			}
		}
		else if (PassiveSkillCond_AfterTogetherHit == cond && val)
		{
			*val -= pc.p1;
		}

		//释放技能
		skill->Cast(self_, target);
	}
}

bool SkillSystem::UpgradeSkill(int index, int level)
{
	if (self_->GetType() != EntityType_Role)
		return false;
	Role *role = (Role*)self_;

	int cur_level = role->GetSkillLevel(index);
	int id = GetRoleSkillId(role->GetJob(), index, cur_level);

	DelSkill(id);
	if (level == 0) level = cur_level + 1;
	id = GetRoleSkillId(role->GetJob(), index, level);

	if (!AddSkill(id))
		return false;

	role->SetSkillLevel(index, level);

	UpdateSkillPower();
	return true;
}

void SkillSystem::UpdateSkillPower()
{
	if (self_->GetType() != EntityType_Role)
		return;
	Role *role = (Role*)self_;

	int skill_power = 0;
	for (int index = 0; index < MAX_SKILL_INDEX; ++index)
	{
		int cur_level = role->GetSkillLevel(index);
		int power_per_level = SkillConfigPool::GetSkillPowerPerLevel(index);

		skill_power += cur_level*power_per_level;
	}
	skill_power_.SetExtraPower(skill_power);

	role->CalcAttributes();
}

int64_t SkillSystem::GetSkillLaveCD(int id)
{
	Skill *skill = FindSkill(id);
	if (!skill)
		return 0;
	static auto ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	int64_t left_time = skill->cd_mtime_ - now_t;
	return (left_time > 0)?left_time:0;
}

void SkillSystem::SetSkillCdById(int id, int64_t cd_mtime_)
{
	Skill *skill = FindSkill(id);
	if (!skill)
		return ;
	skill->cd_mtime_ = cd_mtime_;
}

void SkillSystem::SetPassiveSkillCdById(int id, int64_t cd_mtime_, int cond)
{
	Skill *skill = FindPassiveSkill(id, cond);
	if (!skill)
		return;
	skill->cd_mtime_ = cd_mtime_;
}

int SkillSystem::UseSkill(int id, int index)
{
	//OutputMsg(rmError, "-----UseSkill----- %d;%d", id, index);
	Skill *skill = FindSkill(id);
	// 这里为玩家ai特殊返回释放成功，占用一次逻辑时间跳过不存在的技能，否则要为技能是否学习写很多判断接口
	if (!skill)
	{
		static Skill s_skill;
		skill = &s_skill;
		if (!skill->Init(id))
		{
			return SkillUseResult_NotSkill;
		}
	}

	Creature* target = skill->SelectTarget(self_);

	if (!target) return SkillUseResult_Fail;

	time_t now_t = GetGameEngine()->getTickCount();
	if (!skill->IsNoPublicCD() && public_cd_ > now_t + 100) {
		//OutputMsg(rmWarning, "skill public cd. p:%lld, now:%lld", public_cd_, now_t);
		return SkillUseResult_Fail;
	}

	if (!skill->Cast(self_, (Creature*)target)) {
		//OutputMsg(rmWarning, "skill check cast failed");
		return SkillUseResult_Fail;
	}

	double AttrValue = self_->GetAttr(Attribute::atAttackSpeed);
	if (AttrValue <= 0)
	{
		return SkillUseResult_Fail;
	}

	public_cd_ = now_t + 1000000 / (int64_t)self_->GetAttr(Attribute::atAttackSpeed);
	if(self_->GetAI()) {
		if (index >= 0) self_->GetAI()->OnUseSkill(index, skill->cd_mtime_);
	}

	//增加技能熟练度
	const SkillConfig *conf_ = skill->GetConfig();
	if (conf_ && self_->GetType() == EntityType_Role)
	{
		ScriptValueList arg;
		arg << self_->GetActor();
		arg << ((Role*)self_)->GetId(); //角色ID
		arg << id;		   //技能ID
		arg << index;      //第几个技能
		arg << conf_->exp; //技能熟练度
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("OnChangeSkillExp", &arg, &arg, 0);

		((Role*)self_)->SetAILastUseSkill(index);
	}

	return SkillUseResult_OK;
}
bool SkillSystem::AutoUseAISkill()
{

	int len = aiSkillList.size();
	for (int i =0;i < len;++i)
	{
		Skill *skill = FindSkill(aiSkillList[i]);
		if (skill)
		{
			if (UseSkill(aiSkillList[i]) == SkillUseResult_OK)
			{
				time_t now_t = GetGameEngine()->getTickCount();
				SetSkillCdById(aiSkillList[i], now_t + skill->GetConfig()->base.cd);
				return true;
			}

		}
	}
	return false;
}
void SkillSystem::DoDamageResult(Creature *attacker, double &damage, const SkillConfig* cfg, uint32_t hit_type) {
	if (damage == 0.0 || !attacker) return;
	if (self_->GetType() == EntityType_Monster && ((Monster*)self_)->GetMonType() == MonsterType_AexRing) return;
	if (cfg->base.calc_type != SkillCalcType_TogetherHit) {
		if (attacker->IsDeath()) return;
	} else {
		Actor* actor = attacker->GetActor();
		if (!actor || actor->IsDeath()) {
			return;
		}
	}

	bool selfIsActor = false;
	bool attackerIsActor = false;
	if (self_->GetType() == EntityType_Actor || self_->GetType() == EntityType_Role || self_->GetType() == EntityType_CloneRole)
		selfIsActor = true;
	if (attacker->GetType() == EntityType_Actor || attacker->GetType() == EntityType_Role || attacker->GetType() == EntityType_CloneRole)
		attackerIsActor = true;

	MarkAttrs_Map &self_mam = self_->GetMarkAttrsMap();
	MarkAttrs_Map &tar_mam = attacker->GetMarkAttrsMap();
	auto selfIt = self_mam.find(attacker->GetSummitHandle());
	if (selfIt != self_mam.end()) self_->SetMarkAttr(&(selfIt->second));
	auto tarIt = tar_mam.find(self_->GetSummitHandle());
	if (tarIt != tar_mam.end()) attacker->SetMarkAttr(&(tarIt->second));

	static auto ge = GetGameEngine();
	int64_t now_tick = ge->getTickCount();
	if (cfg->base.calc_type == SkillCalcType_Damage || cfg->base.calc_type == SkillCalcType_TogetherHit || cfg->base.calc_type == SkillCalcType_Multiple_Damage) {
		// 护身戒指
		if (self_->HasHuShenShield() && damage < 0.0) {
			double mp = self_->GetAttr(Attribute::atMp);
			if (mp > (0 - damage)) {
				self_->ChangeMp(damage, attacker);
				damage = 0.0;
			}
			else {
				damage += mp;
				self_->ChangeMp(0 - mp, attacker);
			}
		}
	}
	//正常攻击生效部分
	if (cfg->base.calc_type == SkillCalcType_Damage || cfg->base.calc_type == SkillCalcType_Multiple_Damage) {
		//护身内功
		double np = self_->GetAttr(Attribute::atNeiGong);
		if (np)
		{
			double precent = self_->GetAttr(Attribute::atNeiGongDamageAbsorb);
			double absorbDamage = (0 - damage) * precent / 10000.0;
			if (np > absorbDamage)
			{
				damage += absorbDamage;
				self_->ChangeNp(0 - absorbDamage, attacker);
			}
			else
			{
				damage += np;
				self_->ChangeNp(0 - np, attacker);
			}
		}
		// 麻痹戒指(通用)
		if (attacker && now_tick > attacker->GetSkillSystem()->GetStunCd()) {
			double stun_power = attacker->GetAttr(Attribute::atStunPower);
			double stun_res = self_->GetAttr(Attribute::atStunRes);
			bool stun = wrand(10000) < (stun_power * (1 - stun_res / 10000.0));
			if (stun)
			{
				attacker->GetSkillSystem()->SetStunCd(attacker->GetExAttr(ExAttribute::eatStunTime) + now_tick);
				attacker->SendBubbleEffect(MABI_BUBBLE_TEXT_ID);
				self_->GetSkillEffectSystem()->AddEffect(attacker, MABI_SKILL_EFFECT_ID);
			}
		}
	}

	damage = floor(damage);//取整
	if (cfg->base.calc_type == SkillCalcType_Multiple_Damage) {
		double perdge = -damage; damage = 0.0;//临时存储伤害,用于重新计算真实伤害
		double once_dam = perdge / cfg->args.attr;//单次伤害
		for (int i = 1; i <= cfg->args.attr; ++i) {
			double cur_dam = perdge;
			if (cfg->args.attr != i) {
				int r = (wrand(11) - 5);
				cur_dam = once_dam + once_dam * r/100.0;
			}
			//状态系统对伤害的修正
			self_->GetStatusSystem()->OnDamaged(cur_dam);
			perdge -= cur_dam; damage -= cur_dam;
			self_->NotifyFlyHp(attacker, -cur_dam, hit_type);//飘血
		}
	} else {
		self_->NotifyFlyHp(attacker, damage, hit_type);//飘血
	}
	self_->ChangeHp(damage, attacker);//扣血

	//正常攻击生效部分
	if (cfg->base.calc_type == SkillCalcType_Damage || cfg->base.calc_type == SkillCalcType_Multiple_Damage) {
		if (attacker) {
			//命中时追加当前伤害50%的额外伤害
			if (wrand(10000) < attacker->GetAttr(Attribute::atAttPerDamPan)) {
				double exdam = floor(damage * 0.3);
				self_->ChangeHp(exdam, attacker);
				self_->NotifyFlyHp(attacker, exdam, Skill::HitType_ExDam);
				attacker->SendBubbleEffect(ATT_PER_DAM_TEXT_ID);
			}
			//攻击时候;一定概率自己补血,治疗特戒
			if (now_tick > attacker->GetSkillSystem()->GetAttackAddHpCd() && (int)wrand(10000) < attacker->GetExAttr(ExAttribute::eatAttackAddHpProbability)) {
				attacker->GetSkillSystem()->SyncAttackAddHpCd(now_tick + attacker->GetExAttr(ExAttribute::eatAttackAddHpTime));
				attacker->SendBubbleEffect(ZHILIAO_BUBBLE_TEXT_ID);
				attacker->ChangeHp((double)attacker->GetExAttr(ExAttribute::eatAttackAddHpValue));//补上指定血量
				attacker->NotifyFlyHp(attacker, (double)attacker->GetExAttr(ExAttribute::eatAttackAddHpValue), Skill::HitType_Hit);//飘血
			}

			//吸血
			if (now_tick > attacker->GetSkillSystem()->GetVampireCd() && (int)wrand(10000) < attacker->GetAttr(Attribute::atVamirePro)) {
				attacker->GetSkillSystem()->SetVampireCd(now_tick + static_cast<int64_t>( attacker->GetAttr(Attribute::atVamireCd)) );
				double addHp = (double)((0 - damage) * attacker->GetAttr(Attribute::atVamirePen) / 10000.0);
				attacker->ChangeHp(addHp);
				attacker->SendBubbleEffect(VAMIRE_BUBBLE_TEXT_ID);
				attacker->NotifyFlyHp(attacker, addHp, Skill::HitType_Hit);//飘血
			}

			//反吸血(伤自己血)
			{
				double huntHp = damage * attacker->GetAttr(Attribute::atHurtMyself) / 10000.0;
				attacker->ChangeHp(huntHp);
				attacker->NotifyFlyHp(attacker, huntHp, Skill::HitType_Hit);//飘血
			}

			//特定技能吸血
			if (VamirePro_SKILL_ID == cfg->base.id / 1000) {
				double addHp = (double)((0 - damage) * attacker->GetExAttr(ExAttribute::eatSkillVamirePro) / 10000.0);
				attacker->ChangeHp(addHp);
				attacker->NotifyFlyHp(attacker, addHp, Skill::HitType_Hit);//飘血
			}

			//反伤方面的功能
			if (damage < 0.0) {
				int rate = 0;
				//秘籍反伤
				if (attacker->GetExAttr(ExAttribute::eatIgnoreReflect) == 0)
				{
					double rdamage = 0;// 计算反伤
					rate = wrand(10000);
					if (rate < self_->GetExAttr(ExAttribute::eatReflectProbability)) {
						rdamage = floor(damage * (self_->GetExAttr(ExAttribute::eatReflectRate) / 10000.0));
						//OutputMsg(rmTip, "触发反伤:%d", rdamage);
					}
					//反伤生效
					if (rdamage < 0.0 && !self_->IsDeath() && self_->IsEnemy(attacker)) {
						//NotifyHpChangeEx(attacker, self_, 0 - rdamage);
						attacker->ChangeHp(rdamage, self_);
						attacker->NotifyFlyHp(self_, rdamage, Skill::HitType_Hit);//飘血
					}
				}
				//刃甲反伤
				if (selfIsActor && attackerIsActor)  //PVP才生效
				{
					double rdamage = 0;// 计算反伤
					rate = wrand(10000);
					if (rate < self_->GetAttr(Attribute::atBladeMailPro)) {
						rdamage = floor(damage * (self_->GetAttr(Attribute::atBladeMailPer) / 10000.0));
					}
					//反伤生效
					if (rdamage < 0.0 && !self_->IsDeath() && self_->IsEnemy(attacker)) {
						attacker->ChangeHp(rdamage, self_);
						attacker->NotifyFlyHp(self_, rdamage, Skill::HitType_Rdamage);//飘血
					}
				}
				

			}
			//受到攻击时候释放诅咒(传世装备)
			if (!self_->IsDeath() && self_->GetType() == EntityType_Role) {
				int heirloom_coat_lv = ((Role*)self_)->GetData()->heirloom[EquipSlotType_Coat];
				if (heirloom_coat_lv > 0) {
					if (now_tick > self_->GetSkillSystem()->GetCurseCd() && wrand(10000) < self_->GetAttr(Attribute::atCursePro)) {
						self_->GetSkillSystem()->SetCurseCd(now_tick + static_cast<int64_t>( self_->GetAttr(Attribute::atCurseCd)) );
						attacker->GetSkillEffectSystem()->AddEffect(attacker, CURSE_SKILL_EFFECT_ID + heirloom_coat_lv);
						self_->SendBubbleEffect(CURSE_BUBBLE_TEXT_ID);
					}
				}//end if (heirloom_coat_lv > 0)
			}//end if (self->GetType() == EntityType_Role)
		}

		//受到攻击时候加血(生命兵魂)
		if (!self_->IsDeath() && wrand(10000) < self_->GetAttr(Attribute::atBeAttAddHpPro)) {
			double addHp = self_->GetAttr(Attribute::atBeAttAddHpVal);
			self_->ChangeHp(addHp);
			self_->SendBubbleEffect(BE_ATT_ADD_HP_TEXT_ID);
			self_->NotifyFlyHp(self_, addHp, Skill::HitType_Hit);//飘血
		}
	}

	//所有伤害型攻击生效部分
	if (cfg->base.calc_type == SkillCalcType_Damage || cfg->base.calc_type == SkillCalcType_TogetherHit || cfg->base.calc_type == SkillCalcType_Multiple_Damage) {
		//自己受伤给对方加血
		double addHp = self_->GetAttr(Attribute::atAddEnemyHp);
		if (addHp && !attacker->IsDeath()) {
			attacker->ChangeHp(addHp);
			attacker->NotifyFlyHp(attacker, addHp, Skill::HitType_Hit);//飘血
		}
	}

	self_->SetMarkAttr(nullptr);
	attacker->SetMarkAttr(nullptr);
}

void SkillSystem::AddDamageArg(DamageArg &darg) {
	bool notfind = true;
	if (darg.attack_time < max_delay_time_ || delay_damage_.empty()) {
		for (auto it = delay_damage_.begin(); it != delay_damage_.end(); ++it) {
			if (it->attack_time > darg.attack_time) {
				notfind = false;
				delay_damage_.insert(it,darg);
				break;
			}
		}
	}
	if (notfind)
	{
		delay_damage_.push_back(darg);
		max_delay_time_ = darg.attack_time;
	}
}

void SkillSystem::AddSkillRevise(int skillId, ImbaSkillRevise &rev) {
	skill_rev_[skillId] = rev;
}

void SkillSystem::AddSkillReviseSelfBuff(int skillId, int buffId) {
	auto it = skill_rev_.find(skillId);
	if (it != skill_rev_.end()) {
		it->second.self_eff.push_back(buffId);
	}
}

void SkillSystem::AddSkillReviseTarBuff(int skillId, int buffId) {
	auto it = skill_rev_.find(skillId);
	if (it != skill_rev_.end()) {
		it->second.target_eff.push_back(buffId);
	}
}

void SkillSystem::LogicRun(int64_t curr_t) {
	if (!delay_damage_.empty()) {
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		for (auto it = delay_damage_.begin(); it != delay_damage_.end();) {
			if (it->attack_time <= curr_t) {
				Creature *attacker = NULL;
				if (it->attacker_hdl) {
					attacker = (Creature*)em->GetEntity(it->attacker_hdl);
				}
				DoDamageResult(attacker, it->damage, it->skill_cfg, it->hit_type);
				it = delay_damage_.erase(it);
				continue;
			}
			break;
		}
		if (self_->IsDeath()) {
			clear_delay_damage();
		}
		if (delay_damage_.empty()) max_delay_time_ = 0;
	}
}

void SkillSystem::SyncAttackAddHpCd(int64_t cd)
{
	if (!self_) return;
	if (EntityType_Role == self_->GetType())
	{
		Role* list[MAX_ROLE] = { NULL };
		((Role*)self_)->GetActor()->GetRoleSystem()->GetRoles(list);
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			Role* role = list[i];
			if (!role) continue;
			role->GetSkillSystem()->SetAttackAddHpCd(cd);
		}
	}
	else if (EntityType_CloneRole == self_->GetType())
	{
		static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		EntityHandle hdl;
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			if (((RoleClone*)self_)->GetBuddy(i, hdl))
			{
				auto roleClone = em->GetEntity(hdl);
				if (!roleClone) continue;
				((RoleClone*)roleClone)->GetSkillSystem()->SetAttackAddHpCd(cd);
			}
		}
	}
}

void SkillSystem::GetImbaSkillReviseCfg(int skill_id, ImbaSkillRevise &rev)
{
	if (self_->GetType() != EntityType_Role && self_->GetType() != EntityType_CloneRole) return;
	auto list = SkillConfigPool::GetImbaSkillReviseConfig(skill_id / 1000);
	if (!list) return;
	for (auto it : (*list))
	{
		if (self_->GetType() == EntityType_Role)
		{
			if (!((Role*)self_)->GetActor()->GetImbaSystem()->IsActId(it.imba_id)) continue;
		}
		else if (self_->GetType() == EntityType_CloneRole)
		{
			if(!((RoleClone*)self_)->IsActImbaId(it.imba_id)) continue;
		}
		rev += it.revise;
	}
}

void SkillSystem::GetSkillReviseCfg(int skill_id, ImbaSkillRevise &rev)
{
	auto it = skill_rev_.find(skill_id);
	if (it != skill_rev_.end()) {
		rev += it->second;
	}
}

void SkillSystem::GetGWSkillReviseCfg(int skill_id, ImbaSkillRevise &rev)
{
	if (self_->GetType() != EntityType_Role && self_->GetType() != EntityType_CloneRole) return;
	int idx = skill_id / 1000;

	const std::set<int> *list = NULL;
	if (self_->GetType() == EntityType_Role) {
		list = ((Role*)self_)->GetActor()->GetGodWeaponSystem()->getIdList(idx);
	}
	else if (self_->GetType() == EntityType_CloneRole) {
		list = ((RoleClone*)self_)->getWeaponIdList(idx);
	}

	if (!list)  return;
	const GWSkillReviseMap *map = SkillConfigPool::GetGWSkillReviseConfig(idx);
	if (!map) return;

	for (auto it : *list)
	{
		GWSkillReviseMap::const_iterator citer = map->find(it);
		if (citer != map->end())
		{
			rev += (citer->second);
		}
	}
}
