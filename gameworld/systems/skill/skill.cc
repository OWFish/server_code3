#include "StdAfx.h"
#include "skill.h"
#include "entity/creature.h"
#include "protos/skill_proto.h"
#include "protos/base_proto.h"
#include "skill_config.h"
#include "status_system.h"
#include "effect/skill_effect_system.h"
#include "creature.h"
#include "role/role_system.h"
#include "move/move_system.h"
#include "role/role.h"
#include "ex-ring/ex_ring_system.h"
#include "skill_system.h"
#include "rank/ranking_system.h"
#include "prestige/prestige_helper.h"
#include "entity/monster/monster.h"
#include "entity/monster/monster_config.h"

const Skill::CalcSkillResultFunc Skill::Handlers[] =
{
	&Skill::CalcSkillResult_NoDamage, //没有伤害
	&Skill::CalcSkillResult_Damage, //正常计算伤害
	&Skill::CalcSkillResult_Heal, //计算结果加血
	&Skill::CalcSkillResult_TogetherHit, //合击技能
	&Skill::CalcSkillResult_FixedDamage, //固定伤害
	&Skill::CalcSkillResult_MultipleDamage, //多段伤害
	&Skill::CalcSkillResult_MultipleSkills, //加特林
};

const Skill::CalcResultFunc Skill::RevHandlers[] =
{
	&Skill::Not, //附加n点伤害
	&Skill::AddDamage, //附加n点伤害
	&Skill::FormulaOne, //按指定公式(1* 玩家属性2 +3)
	&Skill::AddDamageProportion, //附加n点(原本伤害的百份比,参数最大配置为1=100%)伤害
	&Skill::DisregardDef, // 无视防御参数最大配置为1=100%
	&Skill::AddStunPower, // 增加麻痹机率
	&Skill::SetAddBearHurt, //修改玩家放出承伤BUFF技能的系数
	&Skill::AddBuff, //添加BUFF（这里只有技能效果）(参数1：等于1为自己加，等于2为目标加, 参数2=BUFFID)
	&Skill::SetCurBuffInfo, //修改指定BUFF的信息
	&Skill::AddStunBuff, //增加一个麻痹BUFF
};

Skill::Skill()
{

}

Skill::~Skill()
{
}


bool Skill::Init(int id)
{
	conf_ = SkillConfigPool::GetSkillConfig(id);
	if (!conf_)
		return false;
	cd_mtime_ = GetGameEngine()->getTickCount();

	return true;
}

bool Skill::CheckCast(Creature* self, Creature* target, ImbaSkillRevise& rev)
{
	if (!target)
		return false;

	if (!self->GetStatusSystem()->CanAttack() && !conf_->passive.is)
		return false;

	const SkillBase* bConf = &(conf_->base);
	/*if (self->GetType() == EntityType_Role)
	{
		//技能突破
		int breakId = ((Role*)self)->GetSkillBreakSystem()->getConfId(GetId());
		if (breakId > 0)
		{
			const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(breakId);
			if (sbConf)
			{
				bConf = &(sbConf->base);
			}
		}
	}*/

	//检查cd
	static auto ge = GetGameEngine();
	time_t now_t = ge->getTickCount();
	if (now_t < cd_mtime_)
		return false;
	//检查目标类型
	switch (bConf->cast_type)
	{
	case SCTType_Friend:
	case SCTType_MinHpRole:
		if (self->IsEnemy(target))
			return false;
		break;
	case SCTType_Enemy:
		if (!self->IsEnemy(target))
			return false;
		break;
	case SCTType_Self:
		if (self != target)
			return false;
		break;
	default:
		OutputMsg(rmError, "skill cast type is undefined.:%d", bConf->cast_type);
		return false;
	}

	// // 检查距离
	int offset = 0;
	if (target->GetType() == EntityType_Monster)
	{
		offset = ((Monster*)target)->GetConfig()->gsize;
	}
	int dis = GetPixDistance(self->GetPosition(), target->GetPosition(), offset);
	if ((bConf->cast_range + rev.base.cast_range + 0.5) * GRIDSIZE < dis)
		return false;

	return true;
}

bool Skill::Cast(Creature* self, Creature* target)
{
	const SkillBase* bConf = &(conf_->base);
	//OutputMsg(rmError, "---Skill::Cast---- %d", bConf->id);
	ImbaSkillRevise rev;  //不用于合击
	self->GetSkillSystem()->GetImbaSkillReviseCfg(conf_->base.id, rev);
	self->GetSkillSystem()->GetGWSkillReviseCfg(conf_->base.id, rev);
	self->GetSkillSystem()->GetSkillReviseCfg(conf_->base.id, rev);  //所有技能通用修正，暂时用于加特林子弹

	if (!CheckCast(self, target, rev)) return false;

	if (conf_->passive.is == false) { 
		/*改变这个调用位置的时候请注意:
			这个函数会有机率再次触发释放技能(被动技能)
			**需要放到最开始**(再没有更进一步的实现之前)
			原因如下:
			1.OnCastSkill函数中;改变朝向问题等
			**
				触发被动技能时候一定要判断当前释放是否是被动技能
				被动技能不能再触发被动技能条件,否者很容易出现超多
				层级别的递归或在CD为0和概率为100%时无限递归
			**
		*/
		//触发攻击时的被动技能
		self->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_Attack);
	}
	//static auto ge = GetGameEngine();
	//cd_mtime_ = ge->getTickCount() + conf_->cd;
	self->OnCastSkill(conf_->base.id, target);
	// 作用目标选择 affect_range, affect_count 选取目标
	/*static */std::vector<Creature*> results;//去掉静态,因为在被攻击前还是需要释放技能,要之前,策划的坑
	results.clear();
	GetAffectedTargets(self, target, results, rev);

	int affect_count = static_cast<int>( results.size());

	int64_t target_hdl = target ? (int64_t)(target->GetHandle()) : 0; // todo
	Protocol::CastSkillProto msg;
	msg.caster_handle = self->GetHandle();
	msg.id = conf_->base.id;
	msg.target_handle = target_hdl;
	msg.count = affect_count;

	char buff[1024];
	DataPacket pack(buff, sizeof(buff));
	pack.writeBuf(&msg, sizeof(msg));

	bool critflag = false;
	if(conf_->passive.is == false) {
		if (self->GetType() == EntityType_Role || self->GetType() == EntityType_CloneRole) {
			if (conf_->base.calc_type == SkillCalcType_Damage || conf_->base.calc_type == SkillCalcType_Multiple_Damage) {//正常攻击生效部分
				self->SetAttactTimes(self->GetAttactTimes() + 1);//增加攻击次数
			}
			//计算狂爆特戒必定暴击
			unsigned int need_times = self->GetExAttr(ExAttribute::eatAttackTimesCrit);//必定暴击次数
			if (need_times > 0 && self->GetAttactTimes() && (self->GetAttactTimes() % need_times == 0)) {
				self->SendBubbleEffect(KUANGBAO_BUBBLE_TEXT_ID);
				//self->SetAttactTimes(0);//满足条件清空
				critflag = true;
			}
		}
	}

	uint32_t hit_type;
	MarkAttrs_Map &self_mam = self->GetMarkAttrsMap();
	for (int i = 0; i < affect_count; ++i) {
		Creature *affect_target = results[i];
		// 计算作用结果
		hit_type = HitType_None;

		MarkAttrs_Map &tar_mam = affect_target->GetMarkAttrsMap();
		auto selfIt = self_mam.find(affect_target->GetSummitHandle());
		if (selfIt != self_mam.end()) self->SetMarkAttr(&(selfIt->second));
		auto tarIt = tar_mam.find(self->GetSummitHandle());
		if (tarIt != tar_mam.end()) affect_target->SetMarkAttr(&(tarIt->second));

		SKILLRESULTPARAM param;
		param.self = self;
		param.target = affect_target;
		param.skill = this;
		param.index = i;

		if (conf_->passive.is == false) {
			//触发被攻击时的被动技能
			affect_target->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_BeAttack);
		}

		double damage = CalcSkillResult(param, hit_type, rev, critflag);
		self->SetMarkAttr(nullptr);
		affect_target->SetMarkAttr(nullptr);

		//暴击触发被动技能
		if (conf_->passive.is == false) {
			if (hit_type & HitType_Crit) {
				self->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_OnCrit, affect_target);
				self->GetSkillSystem()->SetLastTimeCrit(true);
			} else {
				self->GetSkillSystem()->SetLastTimeCrit(false);
			}
			affect_target->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_AfterAttack, self, &damage, this);
		}

		//扣血
		if (conf_->efftime && damage != 0.0) {//延迟扣血的技能
			DamageArg darg;
			darg.damage = damage;
			darg.skill_cfg = conf_;
			darg.attacker_hdl = self->GetHandle();
			darg.attack_time = _getTickCount() + conf_->efftime;
			darg.hit_type = hit_type;
			affect_target->GetSkillSystem()->AddDamageArg(darg);
		} else { //实时扣血的技能
			affect_target->GetSkillSystem()->DoDamageResult(self, damage, conf_, hit_type);
			if (affect_target->IsDeath()) {
				affect_target->GetSkillSystem()->clear_delay_damage();
			}
		}

		pack << affect_target->GetHandle();

		// 附加技能效果
		if (!affect_target->IsDeath())
		{
			const std::vector<int>* tar_eff = &(conf_->tar_eff);
			if (i > 0) tar_eff = &(conf_->other_tar_eff);
			for (std::size_t i = 0; i < tar_eff->size(); ++i) {
				SKILLRESULTPARAM::buff* buff = NULL;
				const EffectConfig* tmpConf = SkillConfigPool::GetEffectConfig((*tar_eff)[i]);
				if (tmpConf) {
					buff = param.GetBuff(tmpConf->group);
				}
				affect_target->GetSkillEffectSystem()->AddEffect(self, (*tar_eff)[i], 0, buff, self);
			}

			for (auto it : rev.target_eff)
			{
				affect_target->GetSkillEffectSystem()->AddEffect(self, it, -1, nullptr, self);
			}
		}
		if (!self->IsDeath() || conf_->base.calc_type == SkillCalcType_TogetherHit)
		{
			for (std::size_t i = 0; i < conf_->self_eff.size(); ++i)
			{
				SKILLRESULTPARAM::buff* buff = NULL;
				const EffectConfig* tmpConf = SkillConfigPool::GetEffectConfig(conf_->self_eff[i]);
				if (tmpConf)
				{
					buff = param.GetBuff(tmpConf->group);
				}
				if (conf_->base.calc_type == SkillCalcType_TogetherHit)
				{//如果是合击,把其它角色也加上Effect			
					SyncAllRoleAddEffect(self, conf_->self_eff[i], buff);
				}
				else
				{//不是合击,只加给自己
					self->GetSkillEffectSystem()->AddEffect(self, conf_->self_eff[i], 0, buff);
				}
			}
			for (auto it:rev.self_eff)
			{
				SKILLRESULTPARAM::buff* buff = NULL;
				const EffectConfig* tmpConf = SkillConfigPool::GetEffectConfig(it);
				if (tmpConf)
				{
					buff = param.GetBuff(tmpConf->group);
				}
				if (conf_->base.calc_type == SkillCalcType_TogetherHit)
				{//如果是合击,把其它角色也加上Effect			
					SyncAllRoleAddEffect(self, it, buff);
				}
				else
				{//不是合击,只加给自己
					self->GetSkillEffectSystem()->AddEffect(self, it, 0, buff, affect_target);
				}
			}
		}
		// todo位移
		DoRepel(self, affect_target);
	}
	self->GetScene()->SendPacket(&pack, self->GetActor());

	//技能CD
	if (conf_->base.cd - rev.cd < 0) {
		//出现负cd，找策划确认配置
		OutputMsg(rmError, "skill %d cd < 0", conf_->base.id);
#ifdef _MSC_VER
		assert(false);
#endif
	}
	static auto ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	int conf_cd = conf_->base.cd;
	if (conf_->base.calc_type == SkillCalcType_TogetherHit) {
		//合击另外算
		double change_cd = 0.0;
		if ((self->GetType() == EntityType_Role || self->GetType() == EntityType_CloneRole) && conf_->passive.is == false)
			self->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_AfterTogetherHit, nullptr, &change_cd);
		double cd_sub = (double)self->GetExAttr(ExAttribute::eatTogetherHitCdSub) / 10000.0;
		cd_mtime_ = static_cast<int64_t> ( now_t + conf_cd - static_cast<int64_t>(conf_cd * cd_sub) + change_cd );
		SyncAllRoleCDTick(self, cd_mtime_);
	} else {
		cd_mtime_ = now_t + conf_cd - rev.cd;
		if (conf_->sync_cd)
			SyncAllRoleCDTick(self, cd_mtime_);
	}
	return true;
}

Creature* Skill::SelectTarget(Creature* caster)
{
	if (caster == nullptr)
		return nullptr;

	const SkillBase* bConf = &(conf_->base);
	/*if (caster->GetType() == EntityType_Role)
	{
		//技能突破
		int breakId = ((Role*)caster)->GetSkillBreakSystem()->getConfId(GetId());
		if (breakId > 0)
		{
			const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(breakId);
			if (sbConf)
			{
				bConf = &(sbConf->base);
			}
		}
	}*/

	switch (bConf->cast_type)
	{
	case SCTType_Friend:
	{
		Entity* target = caster->GetTarget();
		if (target && target->IsCreature())
		{
			if (!caster->IsEnemy((Creature*)target))
			return (Creature*)target;
		}
		return caster;
		break;
	}
	case SCTType_Enemy:
	{
		Entity *target = caster->GetTarget();
		if (target && target->IsCreature())
		{
			if (caster->IsEnemy((Creature*)target))
				return (Creature*)target;
		}
		return nullptr;
		break;
	}
	case SCTType_Self:
		return caster;
		break;
	case SCTType_MinHpRole:
	{
		if (caster->GetType() != EntityType_Role)
			return caster;
		return ((Role*)caster)->GetSelfMinRole();
	}
	default:
		OutputMsg(rmError, "skill cast type is undefined.:%d", bConf->cast_type);
		return nullptr;
	}
	// // 检查距离
	return nullptr;
}
/*
inline void NotifyHpChangeEx(Creature *self, Creature *caster, double change_hp)
{
	// 只发送给施法者和自己的飘血信息
	Protocol::UpdateHpProto msg;
	msg.handle = self->GetHandle();
	msg.hp = floor(self->GetHp() + change_hp);
	msg.need_display = true; // 设置飘血显示

	Actor *actor = self->GetActor();
	if (actor)
		actor->SendData(msg);
	if (caster)
	{
		Actor *caster_actor = caster->GetActor();
		if (caster_actor && caster_actor != actor)
			caster_actor->SendData(msg);
	}
}
*/
double Skill::CalcSkillResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;

	const SkillBase* bConf = &(conf_->base);
	/*if (self->GetType() == EntityType_Role)
	{
		//技能突破 配置
		int breakId = ((Role*)self)->GetSkillBreakSystem()->getConfId(GetId());
		if (breakId > 0)
		{
			const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(breakId);
			if (sbConf)
			{
				bConf = &(sbConf->base);
			}
		}
	}*/
	if (bConf->calc_type < SkillCalcType_NoDamage || bConf->calc_type >= SkillCalcType_Count)
	{
		return 0.0;
	}
	if (conf_->passive.is == false) {//不是被动技能的时候;才能算受攻击
		if (bConf->calc_type != SkillCalcType_Heal && (target->GetType() == EntityType_Role || target->GetType() == EntityType_CloneRole))
		{//判断目标是否受到多少次攻击直接闪避(闪避特戒)
			unsigned int need_times = target->GetExAttr(ExAttribute::eatBeHitTimesDodge);
			if (need_times > 0 && target->GetBeHitTimes() >= need_times)
			{
				target->SetBeHitTimes(0);
				target->SendBubbleEffect(SHANBI_BUBBLE_TEXT_ID);
				return 0.0;
			}
			else
			{	//增加受攻击次数
				target->SetBeHitTimes(target->GetBeHitTimes() + 1);
			}
		}
	}
	return (this->*Skill::Handlers[bConf->calc_type])(param, hitType, rev, critflag);
	//----------------------------------------------------
}

double Skill::CalcSkillResult_NoDamage(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_None;
	//因为所有符加BUFF的技能都是EntityType_Role的
	/*if (self->GetType() == EntityType_Role)
	{
		//技能突破
		((Role*)self)->GetSkillBreakSystem()->DoResult(param, hitType);
	}*/
	DoResult(param, hitType, rev);
	return 0.0;
}

double Skill::CalcSkillResult_Damage(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	static auto ge = GetGameEngine();
	int64_t now_tick = ge->getTickCount();
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_Hit;

	int rand = wrand(10000);
	int m = __min(target->GetExAttr(ExAttribute::eatMiss) - self->GetExAttr(ExAttribute::eatHit), 4000);
	if (rand < m) {
		hitType += HitType_Dodge;
		target->NotifyFlyHp(self, 0, Skill::HitType_Dodge);
		return 0;
	}
	//判断攻击方和被攻击方是否玩家
	bool selfIsActor = false;
	bool targetIsActor = false;
	if (self->GetType() == EntityType_Actor || self->GetType() == EntityType_Role || self->GetType() == EntityType_CloneRole)
		selfIsActor = true;
	if (target->GetType() == EntityType_Actor || target->GetType() == EntityType_Role || target->GetType() == EntityType_CloneRole)
		targetIsActor = true;
	//计算攻击方职业
	int job = JobType_None;
	if (self->GetType() == EntityType_Role)
		job = ((Role*)self)->GetJob();
	else if (self->GetType() == EntityType_CloneRole)
		job = ((RoleClone*)self)->GetJob();
	//计算守方的职业
	int tjob = JobType_None;
	if (target->GetType() == EntityType_Role)
		tjob = ((Role*)target)->GetJob();
	else if (target->GetType() == EntityType_CloneRole)
		tjob = ((RoleClone*)target)->GetJob();

	//魂骨共鸣
	bool hungu = false;
	if (now_tick > self->GetSkillSystem()->GetHunGuCd() && wrand(10000) < (unsigned int)(self->GetAttr(Attribute::atHunGuPro))) {
		self->GetSkillSystem()->SetHunGuCd(now_tick + static_cast<int64_t>(self->GetAttr(Attribute::atHunGuCd)));
		if (self->GetType() == EntityType_Role) {
			self->SendBubbleEffect(HUNGU_FLOAT_TEXT_ID);
		}
		hungu = true;
	}

	//按攻击职业获取守方用法防或物防
	double job_atk = self->GetAttr(Attribute::atAtk), tjob_def=0.0, single_pen=0.0;
	if (selfIsActor && job) {
		if (job == JobType_Warrior) {
			tjob_def = target->GetAttr(Attribute::atDef);
			single_pen = self->GetAttr(Attribute::atDefPen);
		} else {
			tjob_def = target->GetAttr(Attribute::atRes);
			single_pen = self->GetAttr(Attribute::atResPen);
		}
	} else {
		tjob_def = target->GetAttr(Attribute::atDef);
		single_pen = self->GetAttr(Attribute::atDefPen);
	}

	//新加一个飘字类型 切割传给客户端
	if(self->GetAttr(Attribute::atPenetrate) > 0)
		hitType += HitType_Penet;
	//攻击力 = MAX((攻方攻击-守方防御*（1-攻方无视防御比例）），5%*攻方攻击）
	double penetrate = 1 - (self->GetAttr(Attribute::atPenetrate) + single_pen) / 10000.0;
	if (penetrate > 0 && hungu) penetrate = 0;
	double atk_val = __max(job_atk - tjob_def * penetrate, 0.2*job_atk);
	//定义伤害
	double damage = 0.0;
	//1.(技能系统(攻击力*技能伤害系数+技能附加伤害) + 攻方固定伤害增加 – 守方固定伤害减免）
	auto &args = conf_->args;
	{
		//1.1技能基础系数伤害加成
		//int exBaseSkillArg = 0;
		//if (WARRIOR_COMMON_SKILL == GetId() || MAGE_COMMON_SKILL == GetId() || TAOIST_COMMON_SKILL == GetId()) {
		//	exBaseSkillArg = self->GetExAttr(ExAttribute::eatBaseSkillExArg);
		//}
		//(技能系统(攻击力*技能伤害系数+技能附加伤害)
		damage = floor((args.a + rev.a) * atk_val + args.b + rev.b);
		int skillDamageAdd = self->GetExAttr(ExAttribute::eatAddSkillDamageInc) - target->GetExAttr(ExAttribute::eatSubSkillDamageInc);
		if (skillDamageAdd > 0)
		{
			damage += damage * skillDamageAdd / 10000.0;
		}
		{
			auto m = self->GetMaster();
			if (m  && m->IsCreature() && ((Creature*)m)->GetBattlePet() == self) {
				int deathCount = ((Creature*)m)->getDeathCount();
				damage += damage * deathCount * ((Creature*)m)->GetExAttr(ExAttribute::eatPetAttackInc) / 10000.0;
			} else {
				//神兵加成伤害
				damage = damage * (1 + getWeaponPeakPre(self, target));
			}
		}
		param.damage = damage;
		DoResult(param, hitType, rev);
		damage = param.damage;
		//+ 攻方固定伤害增加 – 守方固定伤害减免
		damage = floor(damage + self->GetExAttr(ExAttribute::eatAdditionalHarm) - target->GetExAttr(ExAttribute::eatReductionHarm));
		//兵魂,攻击有几率额外造成X点伤害（无CD）
		if ((unsigned int)self->GetAttr(Attribute::atAttAddDamPro) > wrand(10000)) {
			self->SendBubbleEffect(ATT_ADD_DAM_TEXT_ID);
			damage += self->GetAttr(Attribute::atAttAddDamVal);
		}
	}
	{//2.（1+对目标伤害加成+攻方对玩家伤害加成|对怪物伤害加成 - 守方对玩家伤害减免|怪物伤害减免）
		double damage_per = 0.0, def_per = 0.0;
		damage_per = damage_per + self->GetAttr(Attribute::atDamageEnhance);//对目标伤害加成
		if (hungu) damage_per = damage_per + self->GetAttr(Attribute::atHunGuHurt);//魂骨伤害加成
		if (selfIsActor) {
			def_per = target->GetAttr(Attribute::atRoleDamageReduction);//守方对玩家伤害减免|怪物伤害减免
		}
		if (targetIsActor) {
			damage_per = damage_per + self->GetAttr(Attribute::atRoleDamageEnhance);//攻方对玩家伤害加成
			//威望的威慑技能
			if (self->GetPrestigeExp() > target->GetPrestigeExp()) {
				damage_per += getPerstigeDam(self);//威慑技能伤害加深万份比
				hitType += HitType_Deter;
			}
		} else {
			damage_per = damage_per + rev.d;//对怪物伤害加成
		}
		//兵魂,对被麻痹的目标额外造成X%伤害提升
		if (target->GetStatusSystem()->CheckStatus(StatusType_Stun) && self->GetAttr(Attribute::atAttMbAddDamPen) > 0.0) {
			self->SendBubbleEffect(ATT_MB_ADD_DAM_TEXT_ID);
			damage_per += self->GetAttr(Attribute::atAttMbAddDamPen);
		}
		//兵魂,对生命低X%的目标伤害永久提升X%（无CD）
		if ((target->GetHp() / target->GetMaxHp()*10000.0) <= self->GetAttr(Attribute::atAttHpLtPenAddDam)) {
			self->SendBubbleEffect(ATT_HP_LT_ADD_DAM_TEXT_ID);
			damage_per += self->GetAttr(Attribute::atAttHpLtAddDamPen);
		}
		//秘籍对伤害的加成
		{
			//狂怒秘籍 INT((m-自身血量百分比)/x)*y
			double hpper = (self->GetHp() / self->GetMaxHp()*10000.0);
			if (hpper <= self->GetExAttr(ExAttribute::eatMiJiKNHpPer)) {
				damage_per += floor((self->GetExAttr(ExAttribute::eatMiJiKNHpPer) - hpper) / self->GetExAttr(ExAttribute::eatMiJiKNHpSubPer) + 1)*self->GetExAttr(ExAttribute::eatMiJiKNDamPer);
			}
			//追魂秘籍
			if (self->GetSkillSystem()->GetLastTimeCrit() && now_tick > self->GetSkillSystem()->GetMiJiZhCd()) {
				self->GetSkillSystem()->SetMiJiZhCd(now_tick + self->GetExAttr(ExAttribute::eatMiJiZHTime));
				damage_per += self->GetExAttr(ExAttribute::eatMiJiZHDamPer);
			}
		}
		unsigned int need_times = static_cast<unsigned int> ( self->GetAttr(Attribute::atHearthCount) );//多少次攻击后触发伤害加成
		if (need_times > 0 && self->GetAttactTimes() && (self->GetAttactTimes() % need_times == 0)) {
			damage_per += self->GetAttr(Attribute::atHearthHurt);
		}
		damage = damage * (1.0 + __max(-5000, damage_per - def_per) / 10000.0);
	}
	{//3.（1+攻方对职业伤害加成率-守方对职业伤害减免率）
		int inc = 0;
		//对指定职业的伤害加成
		switch (tjob)
		{
		case JobType_Warrior:
			inc = self->GetExAttr(ExAttribute::eatAddToWarriorDamageInc);
			break;
		case JobType_Mage:
			inc = self->GetExAttr(ExAttribute::eatAddToMageDamageInc);
			break;
		case JobType_Taoist:
			inc = self->GetExAttr(ExAttribute::eatAddToTaoistDamageInc);
			break;
		default:
			break;
		}
		//对指定职业的伤害减免
		switch (job)
		{
		case JobType_Warrior:
			inc -= target->GetExAttr(ExAttribute::eatSubWarriorDamageInc);
			break;
		case JobType_Mage:
			inc -= target->GetExAttr(ExAttribute::eatSubMageDamageInc);
			break;
		case JobType_Taoist:
			inc -= target->GetExAttr(ExAttribute::eatSubTaoistDamageInc);
			break;
		default:
			break;
		}
		damage = floor(damage * (1 + inc / 10000.0));
	}
	{//4.（1+攻方伤害加成率-守方伤害减免）
		damage -= floor(damage * target->GetAttr(Attribute::atDamageReduction) / 10000.0);
	}

	//群攻的伤害修正 2017年6月26日 15:53:49,策划说要去掉这个功能
	//2017年8月3日 16:02:33,策划说又要加这个功能
	if (param.index > 0) {//只有群攻,在施法第二个以上目标的时候,index才会大于0
		if (targetIsActor) {
			damage = damage * conf_->herd_player_rate / 100;
		} else if (target->IsBoss()) {
			damage = damage * conf_->herd_boss_rate / 100;
		} else {
			damage = damage * conf_->herd_mon_rate / 100;
		}
	}

	{//5.Rnd[95%,105%]
		int rand_val = (int)wrand(11) - 5;
		damage *= (1.0 + rand_val/100.0);
	}
	switch (job)
	{
	case JobType_Warrior:
		damage = floor(damage * (1 + self->GetExAttr(ExAttribute::eatAddWarriorDamageInc) / 10000.0));
		break;
	case JobType_Mage:
		damage = floor(damage * (1 + self->GetExAttr(ExAttribute::eatAddMageDamageInc) / 10000.0));
		break;
	case JobType_Taoist:
		damage = floor(damage * (1 + self->GetExAttr(ExAttribute::eatAddTaoistDamageInc) / 10000.0));
		break;
	default:
		break;
	}
/*保底伤害并没有
	if (self->IsMonster())	// 怪物有保底伤害
	{
		double base_damage = floor(self->GetAttr(Attribute::atAtk) * 0.05);
		if (damage < base_damage)
			damage = base_damage;
	}
*/
	if (now_tick > self->GetSkillSystem()->GetDeathCurseCd() && wrand(10000) < (unsigned int)(self->GetExAttr(ExAttribute::eatGodPowerProbability))) {
		self->GetSkillSystem()->SetDeathCurseCd(now_tick + self->GetExAttr(ExAttribute::eatGodPowerCd));
		self->SendBubbleEffect(SHENLI_BUBBLE_TEXT_ID);
		damage = floor(damage * (1 + self->GetExAttr(ExAttribute::eatGodPowerDamageIncrease) / 10000.0));
	} else if (wrand(10000) < (unsigned int)(self->GetExAttr(ExAttribute::eatDeathCurseProbability))) {
		target->GetSkillEffectSystem()->AddEffect(self, DEATH_CURSE_EFFECT_ID);
		damage = floor(damage * (1 + self->GetExAttr(ExAttribute::eatDeathCurseDamageIncrease) / 10000.0));
	}

	//这个其实成立可能几乎没有
	//if (damage < 0) damage = 0;

	{//幸运一击,无视减免
		if (now_tick > self->GetSkillSystem()->GetMultipleCritCd() && (unsigned int)self->GetExAttr(ExAttribute::eatMultipleCrit) > wrand(10000)) {
			self->GetSkillSystem()->SetMultipleCritCd(now_tick + self->GetExAttr(ExAttribute::eatMultipleCritTime));
			hitType += HitType_Lucky;
			double rate = 1.5 + self->GetExAttr(ExAttribute::eatMultipleCritCoeff) / 10000.0;
			damage = floor(damage * rate);
			damage += (self->GetExAttr(ExAttribute::atMultipleCritHurt));
			self->SendBubbleEffect(MULTIPLE_CRIT_BUBBLE_TEXT_ID);
		}
		// 计算天珠技能是否触发，必定暴击
		if (!critflag) {
			int rnd = self->GetExAttr(ExAttribute::eatAllCrit);
			if ((unsigned int)rnd > wrand(10000)) {
				self->GetSkillEffectSystem()->AddEffect(self, ALLCRIT_SKILL_EFFECT_ID);
				self->SendBubbleEffect(KUANGBAO_BUBBLE_TEXT_ID);
			}
			critflag = self->GetStatusSystem()->CheckStatus(StatusType_AllCrit);
		}
		if (!critflag) {//天珠没触发,计算正常暴击率
			double crit_probability = self->GetAttr(Attribute::atCrit)+rev.crit - target->GetAttr(Attribute::atTough);

			if (crit_probability > 0) {
				int r = wrand(10000);
				if (r < crit_probability) critflag = true;
			}
		}

		//0.5+致命一击伤害率-致命一击伤害抵抗率
		double deadlyPro = 0.0;
		double deadlyDamege = 0.0;
		if (wrand(10000) < (unsigned int)(self->GetAttr(Attribute::atDeadLyPro))) {
			deadlyPro = 0.5 + (self->GetAttr(Attribute::atDeadLyMaster) - target->GetAttr(Attribute::atDeadLyResist)) / 10000.0;
			if (0.2 > deadlyPro) deadlyPro = 0.2;

			//致命一击附加伤害
			deadlyDamege = self->GetAttr(Attribute::atDeadLyHurt) - target->GetAttr(Attribute::atDeadLyHurtResist);
			if (0 > deadlyDamege) deadlyDamege = 0.0;

			hitType += HitType_Deadly;
		}

		//不管如何,只要暴击生效计算暴击伤害
		double critRate = 0.0;
		double critDamege = 0.0;
		if (critflag) {
			//同时触发致命一击和暴击时显示致命一击
			if (0 == (hitType & HitType_Deadly)) hitType += HitType_Crit;

			//对生命低X%的目标暴击时暴击伤害加深(新玉佩)（无CD）
			if ((target->GetHp() / target->GetMaxHp()*10000.0) <= self->GetExAttr(ExAttribute::eatCritHpLt)) {
				critRate += self->GetExAttr(ExAttribute::eatCritHpLtAddDamage);
			}

			// 基础暴击伤害率 + 附加暴击伤害率 + 会心伤害率 - 防守方暴击伤害抵抗率
			critRate = (critRate + (self->GetAttr(Attribute::atCritEnhance) + rev.critDamage + self->GetAttr(Attribute::atHuiXinDamage) - target->GetAttr(Attribute::atCritEnhanceResist))) / 10000.0;

			//保底暴击倍数为0
			if (0 > critRate) critRate = 0.0;

			//暴击附加伤害
			critDamege = self->GetAttr(Attribute::atCritHurt) - target->GetAttr(Attribute::atCritHurtResist);
			if (0 > critDamege) critDamege = 0.0;
		}

		//基础伤害*(1 + （基础暴击伤害率 + 附加暴击伤害率 + 会心伤害率 - 防守方暴击伤害抵抗率） + (0.5 + 致命一击伤害率 - 致命一击伤害抵抗率)）+ 致命一击附加值 + 暴击力（暴击的追加伤害）
		damage = damage + floor(damage * (critRate + deadlyPro)) + deadlyDamege + critDamege;
		}

	//神圣伤害
	damage = damage + self->GetAttr(Attribute::atHolyDamege) * (1 + (self->GetAttr(Attribute::atHolyMaster) - target->GetAttr(Attribute::atHolyResist)) / 10000.0);

	//追命伤害(心法1)
	if ((unsigned int)self->GetAttr(Attribute::atZhuiMingPro) > wrand(10000)) {
		damage += self->GetAttr(Attribute::atZhuiMingVal);
		hitType += HitType_ZhuiMing;
	}
	{//多少次攻击后触发伤害固定值增加(心法3)
		unsigned int need_times = static_cast<unsigned int> ( self->GetAttr(Attribute::atHearthCount) );
		if (need_times > 0 && self->GetAttactTimes() && (self->GetAttactTimes() % need_times == 0)) {
			damage += self->GetAttr(Attribute::atHearthDamege);
			if (self->GetType() == EntityType_Role) {
				self->SendBubbleEffect(XINFA3_FLOAT_TEXT_ID);
			}
		}
	}

	//状态系统对伤害的修正
	target->GetStatusSystem()->OnDamaged(damage);


	if (damage < 0) damage = 0;



	return -damage;
}

double Skill::CalcSkillResult_Heal(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_Hit;
	auto &args = conf_->args;
	double damage = floor(args.a * self->GetAttr(args.attr) + args.b);
	/*if (self->GetType() == EntityType_Role)
	{
		//技能突破
		param.damage = damage;
		((Role*)self)->GetSkillBreakSystem()->DoResult(param, hitType);
		damage = param.damage;
	}*/
	damage = floor(damage);
	return damage;
}

double Skill::CalcSkillResult_TogetherHit(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	if (self->IsMonster()) {
		hitType = HitType_Hit;
	} else {
		hitType = HitType_Together;
	}
	double atk_val = 0.0;//攻击力
	{//（合击攻击-守方防御）
		//合击物攻
		double atk_sum = self->GetAtkSum();
		//守方防御
		double tjob_def = (self->GetAttr(Attribute::atDef) + self->GetAttr(Attribute::atRes)) / 2.0;
		//攻击力
		atk_val = __max((atk_sum - tjob_def), (0.05 * atk_sum));
	}

	//1.技能系统(攻击力*技能伤害系数+技能附加伤害)
	auto &args = conf_->args;
	double damage = floor((args.a + (self->GetExAttr(ExAttribute::eatSkillAddArgA) / 10000.0)) * atk_val + args.b + self->GetExAttr(ExAttribute::eatSkillAddArgB));
	
	//2.(1 + MAX( 60% ,对玩家合击伤害加成|对怪物合击伤害加成 - 守方对合击伤害减免比例）)
	int daminc = 0;
	if (target->GetType() == EntityType_Role || target->GetType() == EntityType_CloneRole) {
		daminc = self->GetExAttr(ExAttribute::eatTogetherHitRoleDamageInc);//对玩家合击伤害加成
	} else if (target->GetType() == EntityType_Monster) {
		daminc = self->GetExAttr(ExAttribute::eatTogetherHitMonDamageInc);//对怪物合击伤害加成
	}
	damage = floor(damage * (1.0 + __max(6000,daminc - target->GetExAttr(ExAttribute::eatTogetherHitFree)) / 10000.0));

	//3.(1-守方对玩家/怪物伤害减免）
	damage = floor(damage * (1.0 - target->GetAttr(Attribute::atRoleDamageReduction) / 10000.0));

	//4.(1-守方伤害减免比率）
	damage = floor(damage * (1.0 - target->GetAttr(Attribute::atDamageReduction) / 10000.0));

	//群攻的伤害修正
	if (param.index > 0) {//只有群攻,在施法第二个以上目标的时候,index才会大于0
		if (target->GetType() != EntityType_Monster) {
			damage = damage * conf_->herd_player_rate / 100;
		} else if (target->IsBoss()) {
			damage = damage * conf_->herd_boss_rate / 100;
		} else {
			damage = damage * conf_->herd_mon_rate / 100;
		}
	}

	{//5.Rnd[95%,105%]
		int rand_val = (int)wrand(11) - 5;
		damage *= (1.0 + rand_val / 100.0);
	}

	//神圣伤害
	damage = damage + self->GetAttr(Attribute::atTogetherHolyDamege) * (1 + (self->GetAttr(Attribute::atTogetherHolyMaster) - target->GetAttr(Attribute::atTogetherHolyResist)) / 10000.0);

	//状态系统对伤害的修正
	target->GetStatusSystem()->OnDamaged(damage);

	if (damage < 0) damage = 0;

	return -damage;
}

double Skill::CalcSkillResult_FixedDamage(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_Hit;

	double damage = floor(self->GetAttr(Attribute::atAtk));
	damage = damage * (1 + getWeaponPeakPre(self, target));
	//target->ChangeHp(0 - damage, self);
	return -damage;
}

double Skill::CalcSkillResult_MultipleDamage(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_Multiple;

	auto &args = conf_->args;
	double c = 0.0;
	double def = target->GetAttr(Attribute::atDef);
	if (target->GetType() != EntityType_Monster) {
		c = args.c;
		if (self->GetJob() == JobType_Mage) {
			def = target->GetAttr(Attribute::atRes);
		}
	}
	
	double atk = __max(self->GetAttr(Attribute::atAtk) - def, 0);
	double damage = floor(args.a * atk + args.b + c * target->GetAttr(Attribute::atHp));

	//威望的威慑技能
	int dam = 0;
	if (self->GetPrestigeExp() > target->GetPrestigeExp() && 0 < target->GetActorId()) {
		dam = getPerstigeDam(self);//威慑技能伤害加深万份比
		hitType += HitType_Deter;
	}

	damage = damage * (1 + getWeaponPeakPre(self, target) + dam/10000.0);
	return -damage;
}

double Skill::CalcSkillResult_MultipleSkills(SKILLRESULTPARAM & param, uint32_t & hitType, ImbaSkillRevise &rev, bool critflag)
{
	Creature* self = param.self;
	Creature* target = param.target;
	if (self == NULL || target == NULL) return 0.0;
	hitType = HitType_None;
	const std::vector<int>& otherSkills = conf_->other_skills;
	for (std::size_t i = 0; i < otherSkills.size(); ++i) {
		self->GetSkillSystem()->UseSkill(otherSkills[i]);
	}
	return 0.0;
}

bool HpCompare(Creature* a, Creature* b)
{
	return a->GetAttr(Attribute::atHp) < b->GetAttr(Attribute::atHp);
}
// todo 如果游戏类型变更，这个要重构
// 问题1：现在主要考虑的是特殊副本会有大量玩家并且匝堆的情况, 不然遍历场景即可
// 问题2：友方的定义，对于role的技能，暂时是己方role，不包括召唤物
void Skill::GetAffectedTargets(Creature* self, Creature* target, std::vector<Creature*> &results, ImbaSkillRevise &rev)
{
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	if (!self || !target) return;

	const SkillBase* bConf = &(conf_->base);
	/*if (self->GetType() == EntityType_Role)
	{
		//技能突破
		int breakId = ((Role*)self)->GetSkillBreakSystem()->getConfId(GetId());
		if (breakId > 0)
		{
			const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(breakId);
			if (sbConf)
			{
				bConf = &(sbConf->base);
			}
		}
	}*/

	int affect_count = bConf->affect_count + rev.base.affect_count;
	int affect_range = bConf->affect_range + rev.base.affect_range;

	if (bConf->target_type == SATType_Friend)
	{
		if (target && !target->IsDeath() && (target == self || !self->IsEnemy(target)))
			results.push_back(target);

		if (affect_count <= 1)
			return;

		// 只选自角色
		if (self->GetType() == EntityType_Role)
		{
			Actor* actor = ((Role*)self)->GetActor();
			if (actor)
			{
				Role* roles[MAX_ROLE] = { NULL };
				Role* tmpRoles[MAX_ROLE] = { NULL };

				int idx = 0;
				actor->GetRoleSystem()->GetRoles(roles);

				for (int i = 0; i < MAX_ROLE; ++i)
				{
					Role* role = roles[i];
					if (role == target)	continue;
					if (role == NULL) break;
					if (role->IsDeath()) continue;
					if (GetGridDistance(role->GetPosition(), target->GetPosition()) < affect_range)
					{
						tmpRoles[idx] = role;
						++idx;
					}
				}
				if (idx > 1)
				{
					std::sort(&(tmpRoles[0]), &(tmpRoles[idx-1]), HpCompare);
				}

				for (int i = 0; i < idx; i++)
				{
					results.push_back(tmpRoles[i]);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
		else if (self->GetType() == EntityType_CloneRole)
		{
			EntityHandle hdl;
			RoleClone* tmpRoleClones[MAX_ROLE] = { NULL };
			int idx = 0;
			for (int i = 0; i < MAX_ROLE; ++i)
			{
				if (((RoleClone*)self)->GetBuddy(i, hdl))
				{
					auto roleClone = em->GetEntity(hdl);
					if (!roleClone) continue;
					if (roleClone->IsDeath()) continue;
					if (roleClone == target) continue;
					if (GetGridDistance(roleClone->GetPosition(), target->GetPosition()) < affect_range)
					{
						tmpRoleClones[idx] = static_cast<RoleClone*>(roleClone);
						++idx;
					}
				}
			}

			if (idx > 1)
			{
				std::sort(&(tmpRoleClones[0]), &(tmpRoleClones[idx - 1]), HpCompare);
			}

			for (int i = 0; i < idx; i++)
			{
				results.push_back(tmpRoleClones[i]);
				if (results.size() >= (std::size_t)affect_count)
					return;
			}
		}
		// 不考虑召唤兽有友方技能的话，怪物只需要从怪物列表里选目标
		else if (self->GetType() == EntityType_Monster)
		{
			auto &monster_list = target->GetScene()->GetMonsterList();
			LinkedNode<EntityHandle>* node;
			ListIterator<EntityHandle> it(monster_list);
			for (node = it.first(); node; node = it.next())
			{
				Monster *mon = (Monster*)em->GetEntity(node->data_);
				if (!mon) continue;
				if (mon == target) continue;
				if (mon->IsDeath()) continue;
				if (mon->GetMonType() == MonsterType_Pet) continue;   //如果是宠物 就排除攻击
				if (mon  && !self->IsEnemy(mon) && self->GetCamp() == mon->GetCamp() &&
					GetGridDistance(target->GetPosition(), mon->GetPosition()) <= affect_range)
				{
					results.push_back(mon);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
	}
	else if (bConf->target_type == SATType_Enemy)
	{
		if (target && self->IsEnemy(target))
			results.push_back(target);

		if (affect_count <= 1)
			return;

		//if (self->GetMaster() && self->GetMaster()->IsCreature())
		//	return GetAffectedTargets((Creature*)self->GetMaster(), target, results);

		if (self->GetType() == EntityType_Role || self->GetType() == EntityType_CloneRole ||(self->GetMaster() && self->GetMaster()->IsCreature()))
		{
			auto &monster_list = target->GetScene()->GetMonsterList();
			LinkedNode<EntityHandle>* node;
			ListIterator<EntityHandle> it(monster_list);
			for (node = it.first(); node; node = it.next())
			{
				Monster *mon = (Monster*)em->GetEntity(node->data_);
				if (mon == target)
					continue;
				if (mon->GetMonType() == MonsterType_Pet) continue;   //如果是宠物 就排除攻击
				if (self->IsEnemy(mon) &&
					GetGridDistance(target->GetPosition(), mon->GetPosition()) <= affect_range)
				{
					results.push_back(mon);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
			auto &role_list = target->GetScene()->GetRoleList();
			ListIterator<EntityHandle> it2(role_list);
			for (node = it2.first(); node; node = it2.next())
			{
				Role *pRole = (Role*)em->GetEntity(node->data_);
				if (pRole == target)
					continue;
				if (self->IsEnemy(pRole) &&
					GetGridDistance(target->GetPosition(), pRole->GetPosition()) <= affect_range )
				{
					//群攻技能挑选范围玩家的时候判断pk模式
					if(self->GetActor() && self->GetActor()->GetBasicData()->field_pk_mode == 0)
						continue;
					if (self->GetActor() && self->GetActor()->GetBasicData()->field_pk_mode == 1 && self->GetActor()->GetBasicData()->guild_id_ > 0 && target->GetActor() && target->GetActor()->GetBasicData()->guild_id_ == self->GetActor()->GetBasicData()->guild_id_)
						continue;
					results.push_back(pRole);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
			auto &clonerole_list = target->GetScene()->GetCloneRoleList();
			ListIterator<EntityHandle> it3(clonerole_list);
			for (node = it3.first(); node; node = it3.next())
			{
				RoleClone *pCloneRole = (RoleClone*)em->GetEntity(node->data_);
				if (!pCloneRole || pCloneRole == target)
					continue;
				if (self->IsEnemy(pCloneRole) &&
					GetGridDistance(target->GetPosition(), pCloneRole->GetPosition()) <= bConf->affect_range)
				{
					results.push_back(pCloneRole);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
		else if (self->GetType() == EntityType_Monster)
		{
			auto &role_list = target->GetScene()->GetRoleList();
			LinkedNode<EntityHandle>* node;
			ListIterator<EntityHandle> it(role_list);
			static EntityMgr *em = GetGameEngine()->GetEntityMgr();
			for (node = it.first(); node; node = it.next())
			{
				Role *role = (Role*)em->GetEntity(node->data_);
				if (role == target)
					continue;
				if (((Monster*)self)->GetMonType() == MonsterType_Pet)
				{
					//宠物宝宝选择攻击对象 要看主人的pk模式
					Role* masterRole = (Role*)em->GetEntity((self)->GetMasterHandle());
					if (masterRole && masterRole->GetActor() && masterRole->GetActor()->GetBasicData()->field_pk_mode == 0)
						continue;
					if (masterRole && masterRole->GetActor() && masterRole->GetActor()->GetBasicData()->field_pk_mode == 1 && masterRole->GetActor()->GetBasicData()->guild_id_ > 0 && role->GetActor() && role->GetActor()->GetBasicData()->guild_id_ == masterRole->GetActor()->GetBasicData()->guild_id_)
						continue;
				}
				if (self->IsEnemy(role) &&
					GetGridDistance(target->GetPosition(), role->GetPosition()) <= affect_range)
				{
					results.push_back(role);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
	}
	else if (bConf->target_type == SATType_Enemy_Self)
	{
		if (target && self->IsEnemy(target))
			results.push_back(target);

		if (affect_count <= 1)
			return;

		//if (self->GetMaster() && self->GetMaster()->IsCreature())
		//	return GetAffectedTargets((Creature*)self->GetMaster(), target, results);

		if (self->GetType() == EntityType_Role || self->GetType() == EntityType_CloneRole || (self->GetMaster() && self->GetMaster()->IsCreature()))
		{
			auto &monster_list = target->GetScene()->GetMonsterList();
			LinkedNode<EntityHandle>* node;
			ListIterator<EntityHandle> it(monster_list);
			for (node = it.first(); node; node = it.next())
			{
				Monster *mon = (Monster*)em->GetEntity(node->data_);
				if (mon == target)
					continue;
				if (mon->GetMonType() == MonsterType_Pet) continue;   //如果是宠物 就排除攻击
				if (self->IsEnemy(mon) &&
					GetGridDistance(self->GetPosition(), mon->GetPosition()) <= affect_range)
				{
					results.push_back(mon);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
			auto &role_list = target->GetScene()->GetRoleList();
			ListIterator<EntityHandle> it2(role_list);
			for (node = it2.first(); node; node = it2.next())
			{
				Role *pRole = (Role*)em->GetEntity(node->data_);
				if (pRole == target)
					continue;
				if (self->IsEnemy(pRole) &&
					GetGridDistance(target->GetPosition(), pRole->GetPosition()) <= affect_range)
				{
					//群攻技能挑选范围玩家的时候判断pk模式
					if (self->GetActor() && self->GetActor()->GetBasicData()->field_pk_mode == 0)
						continue;
					if (self->GetActor() && self->GetActor()->GetBasicData()->field_pk_mode == 1 && self->GetActor()->GetBasicData()->guild_id_ > 0 && target->GetActor() && target->GetActor()->GetBasicData()->guild_id_ == self->GetActor()->GetBasicData()->guild_id_)
						continue;
					results.push_back(pRole);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
			auto &clonerole_list = target->GetScene()->GetCloneRoleList();
			ListIterator<EntityHandle> it3(clonerole_list);
			for (node = it3.first(); node; node = it3.next())
			{
				RoleClone *pCloneRole = (RoleClone*)em->GetEntity(node->data_);
				if (!pCloneRole || pCloneRole == target)
					continue;
				if (self->IsEnemy(pCloneRole) &&
					GetGridDistance(self->GetPosition(), pCloneRole->GetPosition()) <= bConf->affect_range)
				{
					results.push_back(pCloneRole);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
		else if (self->GetType() == EntityType_Monster)
		{
			auto &role_list = target->GetScene()->GetRoleList();
			LinkedNode<EntityHandle>* node;
			ListIterator<EntityHandle> it(role_list);
			static EntityMgr *em = GetGameEngine()->GetEntityMgr();
			for (node = it.first(); node; node = it.next())
			{
				Role *role = (Role*)em->GetEntity(node->data_);
				if (role == target)
					continue;
				if (((Monster*)self)->GetMonType() == MonsterType_Pet)
				{
					//宠物宝宝选择攻击对象 要看主人的pk模式
					Role* masterRole = (Role*)em->GetEntity((self)->GetMasterHandle());
					if (masterRole && masterRole->GetActor() && masterRole->GetActor()->GetBasicData()->field_pk_mode == 0)
						continue;
					if (masterRole && masterRole->GetActor() && masterRole->GetActor()->GetBasicData()->field_pk_mode == 1 && masterRole->GetActor()->GetBasicData()->guild_id_ > 0 && role->GetActor() && role->GetActor()->GetBasicData()->guild_id_ == masterRole->GetActor()->GetBasicData()->guild_id_)
						continue;
				}
				if (self->IsEnemy(role) &&
					GetGridDistance(self->GetPosition(), role->GetPosition()) <= affect_range)
				{
					results.push_back(role);
					if (results.size() >= (std::size_t)affect_count)
						return;
				}
			}
		}
	}
}

void SpecialMove(Creature* caster, Creature* creature, int type, const Point& pos, int fixedDis)
{
	Protocol::EntitySpectialMoveProto msg;
	msg.handle = creature->GetHandle();
	msg.type = type;
	msg.x = pos.x;
	msg.y = pos.y;
	switch (type)
	{
	case MoveSystem::SMT_InstantMove:
		msg.mtime = 0;
		break;
	case MoveSystem::SMT_DashMove:	// 冲锋
	case MoveSystem::SMT_RepelMove: // 被击退
	{
		//double speed = caster->GetAttr(Attribute::atMoveSpeed);
		//int offset = 0;
		//if (creature->GetType() == EntityType_Monster)
		//{
		//	offset = ((Monster*)creature)->GetConfig()->gsize;
		//}
		int dis = GetPixDistance(creature->GetPosition(), pos, 0);
		if (dis < fixedDis)
			dis = fixedDis;
		int mtime = (int)(dis * 1000 / 800);//(1.0 * speed /1000 * GRIDSIZE));
		msg.mtime = mtime;

		Status status;
		status.end_time = GetGameEngine()->getTickCount() + mtime;
		status.type = StatusType_Stun; // 不可操作
		creature->GetStatusSystem()->AddStatus(status);

		status.type = StatusType_Armor; // 不可被位移
		creature->GetStatusSystem()->AddStatus(status);

		break;
	}
	default:
		break;
	}

	creature->GetScene()->SendData(msg);

	//creature->SetPosition(pos);
	creature->ClearMoveLine();
	creature->GetScene()->MoveTo(creature, pos);
	creature->GetMoveSystem()->ClearMoveData();
}

void Skill::DoRepel(Creature* self, Creature* target)
{
	if (conf_->repel_distance > 0)
	{
		if (target && target->GetStatusSystem()->CanControlled())
		{
			const Point &curpos = target->GetPosition();
			const Point &dir = self->GetDirection();

			double hypotenuse = sqrt(dir.x * dir.x + dir.y * dir.y);
			int dis = conf_->repel_distance;
			while (dis > 0)
			{
				double r = dis / hypotenuse;
				Point new_pos((int)(curpos.x + (double)dir.x * r), (int)(curpos.y + (double)dir.y * r));
				if (self->GetScene()->CanMove(new_pos))
				{
					SpecialMove(self, target, MoveSystem::SMT_RepelMove, new_pos, conf_->repel_distance);
					break;
				}
				dis -= GRIDSIZE/2;
			}
		}
	}
	if (conf_->teleport) // 自己也位移 即冲撞技能
	{
		const Point &curpos = self->GetPosition();
		const Point &tarpos = target->GetPosition();
		int offset = 0;
		if (target->GetType() == EntityType_Monster)
		{
			offset = ((Monster*)target)->GetConfig()->gsize;
		}
		int dis = GetPixDistance(curpos, tarpos, offset);
		if (dis > conf_->repel_distance) // 冲到距离1格的位置
		{
			double x = tarpos.x - curpos.x;
			double y = tarpos.y - curpos.y;
			double hypotenuse = sqrt(x*x + y*y);
			double r = (double)conf_->repel_distance / hypotenuse;
			Point new_pos((int)(curpos.x + x * r), (int)(curpos.y + y*r));
			SpecialMove(self, self, MoveSystem::SMT_DashMove, new_pos, conf_->repel_distance);
		}
	}
}

const SkillBase* Skill::GetRealConfig(Creature* caster)
{
	const SkillBase* bConf = &(conf_->base);
	/*if (caster->GetType() == EntityType_Role)
	{
		//技能突破
		int breakId = ((Role*)caster)->GetSkillBreakSystem()->getConfId(GetId());
		if (breakId > 0)
		{
			const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(breakId);
			if (sbConf)
			{
				bConf = &(sbConf->base);
			}
		}
	}*/
	return bConf;
}

void Skill::SyncAllRoleCDTick(Creature * self, int64_t tick)
{
	if (!self) return;
	const SkillBase* conf = GetRealConfig(self);
	if (!conf) return;
	if (EntityType_Role == self->GetType())
	{
		Role* list[MAX_ROLE] = { NULL };
		((Role*)self)->GetActor()->GetRoleSystem()->GetRoles(list);
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			Role* role = list[i];
			if (!role) continue;
			if (conf_->passive.is) role->GetSkillSystem()->SetPassiveSkillCdById(conf->id, tick, conf_->passive.cond);
			else role->GetSkillSystem()->SetSkillCdById(conf->id, tick);
		}
	}
	else if (EntityType_CloneRole == self->GetType())
	{
		static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		EntityHandle hdl;
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			if (((RoleClone*)self)->GetBuddy(i, hdl))
			{
				auto roleClone = em->GetEntity(hdl);
				if (!roleClone) continue;
				if (conf_->passive.is) ((RoleClone*)roleClone)->GetSkillSystem()->SetPassiveSkillCdById(conf->id, tick, conf_->passive.cond);
				else ((RoleClone*)roleClone)->GetSkillSystem()->SetSkillCdById(conf->id, tick);
			}
		}
	}
}

void Skill::SyncAllRoleAddEffect(Creature* self, int eff, SKILLRESULTPARAM::buff* buff)
{
	if (!self) return;
	if (EntityType_Role == self->GetType())
	{
		Role* list[MAX_ROLE] = { NULL };
		((Role*)self)->GetActor()->GetRoleSystem()->GetRoles(list);
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			Role* role = list[i];
			if (!role || role->IsDeath()) continue;
			role->GetSkillEffectSystem()->AddEffect(self, eff, 0, buff);
		}
	}
	else if (EntityType_CloneRole == self->GetType())
	{
		static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		EntityHandle hdl;
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			if (((RoleClone*)self)->GetBuddy(i, hdl))
			{
				auto roleClone = em->GetEntity(hdl);
				if (!roleClone || roleClone->IsDeath()) continue;
				((RoleClone*)roleClone)->GetSkillEffectSystem()->AddEffect(self, eff, 0, buff);
			}
		}
	}
}

void Skill::DoResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev)
{
	if (!param.self || !param.target) return;

	for (auto it:rev.args) {
		(this->*Skill::RevHandlers[it.type])(param, hitType, &(it));
	}
}

void Skill::Not(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
}

void Skill::AddDamage(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.damage += info->vals[0];
}

void Skill::FormulaOne(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.damage += (info->vals[0] * param.self->GetAttr((int)info->vals[1]) + info->vals[2]);
}


void Skill::AddDamageProportion(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.damage += (param.damage * info->vals[0]);
}

void Skill::DisregardDef(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.def_disregard = param.def_disregard + info->vals[0];
}

void Skill::AddStunPower(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.stun_power = param.stun_power + info->vals[0];
	param.stunTime = (double)(param.stun_power + info->vals[1]);
}

void Skill::SetAddBearHurt(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	param.self->GetSkillEffectSystem()->SetAddBearHurt(info->vals[0]);
}

void Skill::AddBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	if (info->vals[0] == 1)
	{
		param.self->GetSkillEffectSystem()->AddEffect(param.self, (int)info->vals[1]);
	}
	else if (info->vals[0] == 2)
	{
		param.target->GetSkillEffectSystem()->AddEffect(param.self, (int)info->vals[1]);
	}
}

void Skill::SetCurBuffInfo(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	tagSkillResultParam::buff buf;
	int id = static_cast<int> ( info->vals[0] );
	param.buffs[id].buff_id = (int)info->vals[0];
	param.buffs[id].buff_time += (int)info->vals[1];
	param.buffs[id].a += info->vals[2];
	param.buffs[id].b += info->vals[3];
	param.buffs[id].c += info->vals[4];
}

void Skill::AddStunBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info)
{
	double stun_power = param.self->GetAttr(Attribute::atStunPower) + info->vals[0];
	double stun_res = param.target->GetAttr(Attribute::atStunRes);
	bool stun = wrand(10000) < (stun_power * (1 - stun_res / 10000.0));
	if (stun)
	{
		param.target->GetSkillEffectSystem()->AddEffect(param.self, (int)info->vals[1]);
	}
}

double Skill::getWeaponPeakPre(Creature * self, Creature * target) {
	if (!self || !target) return 0.0;
	if (target->GetType() == EntityType_Monster) return 0.0;
	if (self->getWeaponPeakLv() <= target->getWeaponPeakLv()) return 0.0;

	int allinc = 0;
	if(self->GetExAttr(ExAttribute::eatWarriorPeakDamageInc)) {
		allinc += self->GetExAttr(ExAttribute::eatWarriorPeakDamageInc) + 100;
	}
	if (self->GetExAttr(ExAttribute::eatMagePeakDamageInc)) {
		allinc += self->GetExAttr(ExAttribute::eatMagePeakDamageInc) + 100;
	}
	if (self->GetExAttr(ExAttribute::eatTaoistPeakDamageInc)) {
		allinc += self->GetExAttr(ExAttribute::eatTaoistPeakDamageInc) + 100;
	}
	return allinc / 10000.0;
}

int Skill::getPerstigeDam(Creature * self) 
{
	if (!self) return 0;
	if (self->GetType() != EntityType_Role && self->GetType() != EntityType_CloneRole) return 0;
	static StaticRankBasic *power_rank = GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->GetRanking(RankingType_Prestige);
	if (!power_rank) return 0;

	int id = self->GetActorId();

	//获取排名
	int rank = power_rank->GetIndexFromId(id);

	return PrestigeHelper::getDeterDam(rank);
}
