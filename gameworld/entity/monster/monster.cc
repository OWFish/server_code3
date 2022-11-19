#include "StdAfx.h"
#include "monster_config.h"
#include "protos/base_proto.h"
#include "ai/config/ai_config.h"
#include "ai/ai_mgr.h"
#include "ai/ai.h"
#include "skill/effect/skill_effect_system.h"
#include "monster_config.h"
#include "actorexring/actor_ex_ring_system.h"


Monster::Monster()
: config_(NULL)
, live_time_(0)
, t500_timer_(500)
{
	SetType(EntityType_Monster);
}

Monster::~Monster()
{

}

bool Monster::Init(int id)
{
	const MonsterConfig* conf = MonsterConfigPool::Get(id);

	if (!conf) return false;
	config_ = conf;
	//SetEntityName(conf->name);

	//todo 属性
	InitBasicAttribute();
	CalcAttributes();

	//todo ai?
	InitAi();

	is_init_ = true;

	return true;
}

void Monster::InitAi()
{

	static AiMgr* aimgr = GetGameEngine()->GetAiMgr();
	ai_ = aimgr->CreateAi(config_->ai, this);
}	

void Monster::InitBasicAttribute()
{
	basic_attrs_cache_.Reset();
	if (!config_) return;

	basic_attrs_cache_[Attribute::atHp] = config_->attrs.hp;
	basic_attrs_cache_[Attribute::atHpMax] = config_->attrs.hp;
	basic_attrs_cache_[Attribute::atMp] = 0;
	basic_attrs_cache_[Attribute::atMpMax] = 0;
	basic_attrs_cache_[Attribute::atAtk] = config_->attrs.atk;
	basic_attrs_cache_[Attribute::atDef] = config_->attrs.def;
	basic_attrs_cache_[Attribute::atRes] = config_->attrs.res;
	basic_attrs_cache_[Attribute::atCrit] = config_->attrs.crit;
	basic_attrs_cache_[Attribute::atTough] = config_->attrs.tough;
	basic_attrs_cache_[Attribute::atMoveSpeed] = config_->attrs.ms;
	basic_attrs_cache_[Attribute::atAttackSpeed] = config_->attrs.as;
	basic_attrs_cache_[Attribute::atStunRes] = config_->attrs.stunRes;
	basic_attrs_cache_[Attribute::atPenetrate] = config_->attrs.penetRate;
	basic_attrs_cache_[Attribute::atCritEnhance] = config_->attrs.critDamage;
}

void Monster::CreateAppearData(DataPacket& appearPack)
{
	Creature::CreateAppearData(appearPack);

	int flamestamp_lv_ = 0;
	int *flamestamp_skill_lv_ = nullptr;
	Entity *master = GetMaster();
	if (config_->type == MonsterType_AexRing && nullptr != master)
	{
		//烈焰印记专用
		if (master->GetType() == EntityType_Actor) {
			flamestamp_skill_lv_ = ((Actor *)master)->GetFlameStampData(flamestamp_lv_);
		} else if (master->GetType() == EntityType_CloneRole) {
			flamestamp_skill_lv_ = ((RoleClone *)master)->GetFlameStampData(flamestamp_lv_);
		}
		
	}

	appearPack << (short)flamestamp_lv_;
	if (nullptr != flamestamp_skill_lv_) {
		appearPack << (char)MAX_FLAMESTAMP_SKILL;
		for (int i = 0; i < MAX_FLAMESTAMP_SKILL; i++) {
			appearPack << (short)flamestamp_skill_lv_[i];
		}
	}
	else {
		appearPack << (char)0;
	}
}

void Monster::CalcAttributes()
{
	static Attribute s_attrs;
	double hp_rate = 1.0;
	//double old_hp = GetHp();
	if (GetMaxHp() > 0) {
		hp_rate = 1.0 * GetHp() / GetMaxHp();
	}

	s_attrs.Reset();
	s_attrs += basic_attrs_cache_;
	// ..
	s_attrs += skill_effect_sys_->GetAttr();
	auto m = GetMaster();
	if (m && m->GetType() == EntityType_Actor)
	{
		int rid = ((Actor*)m)->GetActorExRingSystem()->FindActorExRingMonsterRid(this);
		if (rid >= 0)
		{
			auto attr = (((Actor*)m)->GetActorExRingSystem()->GetMonsterAttr(rid));
			if (attr)
				s_attrs += *attr;
		}
	}
	if (m && m->GetType() == EntityType_CloneRole)
	{
		int rid = ((RoleClone*)m)->HasAexringMon(this);
		if (rid >= 0)
		{
			auto attr = ((RoleClone*)m)->GetAerMonAttr(rid);
			if (attr)
				s_attrs += *attr;
		}
	}
	attrs_.CalcBattleAttribute(s_attrs, JobType_None);

	attrs_.SetHp(floor(GetMaxHp() * hp_rate));
}

void Monster::CalcBattleAttributes()
{
	double old_hp = GetHp();

	static Attribute s_attrs;
	s_attrs.Reset();
	s_attrs += basic_attrs_cache_;
	// ..
	s_attrs += skill_effect_sys_->GetAttr();
	auto m = GetMaster();
	//在线玩家召唤真实的特戒
	if (m && m->GetType() == EntityType_Actor)
	{
		int rid = ((Actor*)m)->GetActorExRingSystem()->FindActorExRingMonsterRid(this);
		if (rid >= 0)
		{
			auto attr = (((Actor*)m)->GetActorExRingSystem()->GetMonsterAttr(rid));
			if (attr)
				s_attrs += *attr;
		}
	}
	//不在线玩家成立的克隆角色召唤出来的特戒
	if (m && m->GetType() == EntityType_CloneRole)
	{
		int rid = ((RoleClone*)m)->HasAexringMon(this);
		if (rid >= 0)
		{
			auto attr = ((RoleClone*)m)->GetAerMonAttr(rid);
			if (attr)
				s_attrs += *attr;
		}
	}
	attrs_.CalcBattleAttribute(s_attrs, JobType_None);

	SetHp(old_hp);
}

void Monster::CalcExAttributes()
{
	ex_attrs_.Reset();
	auto m = GetMaster();
	if (m && m->GetType() == EntityType_Actor)
	{
		int rid = ((Actor*)m)->GetActorExRingSystem()->FindActorExRingMonsterRid(this);
		if (rid >= 0)
		{
			auto attr = (((Actor*)m)->GetActorExRingSystem()->GetMonsterExAttr(rid));
			if (attr)
				ex_attrs_ += *attr;
		}
	}
	if (m && m->GetType() == EntityType_CloneRole)
	{
		int rid = ((RoleClone*)m)->HasAexringMon(this);
		if (rid >= 0)
		{
			auto attr = ((RoleClone*)m)->GetAerMonExAttr(rid);
			if (attr)
				ex_attrs_ += *attr;
		}
	}
	ex_attrs_ += GetSkillEffectSystem()->GetExAttr();
}

void Monster::OnDestroy()
{
	static AiMgr* aimgr = GetGameEngine()->GetAiMgr();
	if (ai_)
		aimgr->DestroyAi(ai_);
	Inherited::OnDestroy();

	Entity *master = GetMaster();
	if (master) {
		if (master->IsCreature() && ((Creature*)master)->GetBattlePet() == this) {
			((Creature*)master)->ClearBattlePet();
		}
		if (master->GetType() == EntityType_Actor) {
			int rid = ((Actor*)master)->GetActorExRingSystem()->FindActorExRingMonsterRid((Monster*)this);
			if (rid >= 0)
				((Actor*)master)->GetActorExRingSystem()->ClearExRingMonster(rid);
		} else if(master->GetType() == EntityType_CloneRole) {
			((RoleClone*)master)->DelAexringMon((Monster*)this);
		}
	}
}

int Monster::GetId()
{
	if (!config_) return 0; return config_->id;
}

Actor* Monster::GetActor()
{
	Entity* master = GetMaster();
	if (master)
		return master->GetActor();
	return NULL;
}

void Monster::OnEntityDeath(EntityHandle killer)
{
	Inherited::OnEntityDeath(killer);
}

void Monster::OnEnterScene()
{
	Creature::OnEnterScene();
}

//被杀死的时候调用的
void Monster::OnKilledByEntity(Entity* killer)
{
}

void Monster::SetLiveTIme(unsigned int nTime)
{
	live_time_ = nTime > 0 ? (GetGameEngine()->getMiniDateTime() + nTime) : 0;
}

void Monster::LogicRun(int64_t nCurrentTime)
{
	if (!is_init_) return;

	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	//static GameEngine* ge = GetGameEngine();

	Inherited::LogicRun(nCurrentTime);

	//if (!t500_timer_.CheckAndSet(nCurrentTime)) return;

}

void Monster::OnChangeHp(double nValue, Creature* attacker, double &ret)
{
	//double old_hp = GetHp();

	//if (old_hp > 0 && nValue < 0)
	//{
		FuBen *fb = GetScene()->GetFuBen();
		if (fb)
			fb->OnMonsterDamage(this, (int)(0-nValue), attacker, ret);
	//}
	Creature::OnChangeHp(nValue, attacker, ret);
}


/*bool Monster::IsEnemy(Creature *target)
{
	// todo
	if (target->GetType() == EntityType_Role)
		return true;
	return false;
}
*/

bool Monster::IsBoss() {
	return config_->type == MonsterType_Boss;
}

int Monster::GetMonType() {
	return config_->type;
}

double Monster::GetAtkSum(void) {
	auto m = GetMaster();
	if (m) {
		if(m->IsCreature()) {
			return ((Creature*)m)->GetAtkSum();
		} else if (m->GetType() == EntityType_Actor) {
			return ((Actor*)m)->GetAtkSum();
		}
	}
	return Creature::GetAtkSum();
}

void Monster::ResetBasicAttr(float rate)
{
	basic_attrs_cache_ *= rate;
	CalcAttributes();

	Scene* pScene = GetScene();
	if (!pScene) return;
	pScene->BroadcastAppear(this);
}
