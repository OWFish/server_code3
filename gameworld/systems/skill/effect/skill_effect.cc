#include "StdAfx.h"
#include "skill_effect.h"
#include "../skill.h"
#include "../skill_config.h"
#include "../status_system.h"
#include "systems/skill/skill_system.h"
#include "skill_effect_system.h"
#include "creature.h"
#include "attr/attribute.h"
#include "protocol/protos/base_proto.h"


SkillEffect::SkillEffect()
: conf_(NULL)
, caster_hdl_(0)
, snapshot_(0)
, all_snapshot_(0)
, next_effect_time_(0)
, end_time_(0)
, is_invalid_(false)
, attribute_(NULL)
, ex_attr_(NULL)
, pet_add_lvl_(0)
, pet_add_atk(0.0)
, pet_penetrate(0.0)
, enemy_handle_(0)
{
}

SkillEffect::~SkillEffect()
{
	SafeDelete(attribute_);
	SafeDelete(ex_attr_);
}

bool SkillEffect::Init(Creature *self, Creature* caster, int id, const SKILLRESULTPARAM::buff* buf, Creature *enemy)
{
	conf_ = SkillConfigPool::GetEffectConfig(id);
	if (!conf_)
		return false;
	if (self == NULL)
		return false;
	if(caster)
		caster_hdl_ = caster->GetHandle();
	self_ = self;

	//init
	if (buf && buf->buff_time > 0)
	{
		end_time_ = buf->buff_time + GetGameEngine()->getTickCount();
	}
	else
	{
		end_time_ = conf_->duration + GetGameEngine()->getTickCount();
	}
	//next_effect_time_ = GetGameEngine()->getTickCount(); // 等于0表示第一次

	if (!InitSnapshot(caster, buf))
		return false;

	if (nullptr != enemy) {
		enemy_handle_ = enemy->GetSummitHandle();
	}

	return true;
}

void SkillEffect::OnTimeCheck(int64_t now_t)
{
	if (is_invalid_) return;

	if (next_effect_time_ <= now_t)
	{
		OnEffect();
		next_effect_time_ = conf_->interval?(now_t + conf_->interval): LLONG_MAX;
	}

	if (end_time_ <= now_t)
	{
		is_invalid_ = true;
		return;
	}
}

int SkillEffect::GetId()
{
	return conf_->id;
}

int SkillEffect::GetGroup()
{
	return conf_->group;
}
/*
inline void NotifyHpChangeEx(Creature *self, Creature *caster, int change_hp)
{
	// 只发送给施法者和自己的飘血信息
	Protocol::UpdateHpProto msg;
	msg.handle = self->GetHandle();
	msg.hp = self->GetHp() + change_hp;
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
void SkillEffect::OnEffect()
{
	if (self_->IsDeath()) return;
	switch (conf_->type)
	{
	case SkillEffectType_Damage:
	{
			Creature *caster = (Creature*)GetGameEngine()->GetEntityMgr()->GetEntity(caster_hdl_);
			auto tmp = fabs(snapshot_);
			self_->GetStatusSystem()->OnDamaged(tmp, true);
			self_->ChangeHp(-tmp, caster);
			//self_->NotifyFlyHp(caster, -tmp, Skill::HitType_Hit);
			self_->NotifyFlyHp(caster, -tmp, conf_->args.d == 0 ? Skill::HitType_Poisoning : Skill::HitType_Bleed);
			//self_->NotifyHpChangeEx(caster, (int)-tmp);
		break;
	}
	case SkillEffectType_Heal:
	{
		Creature *caster = (Creature*)GetGameEngine()->GetEntityMgr()->GetEntity(caster_hdl_);
		//self_->NotifyHpChangeEx(caster, snapshot_);
		self_->ChangeHp(snapshot_, caster);
		self_->NotifyFlyHp(caster, snapshot_, Skill::HitType_Hit);
		break;
	}
	case SkillEffectType_Attr:
		if (next_effect_time_ == 0)
		{
			if (conf_->args.d == Attribute::atHp)
			{
				//Creature *caster = (Creature*)GetGameEngine()->GetEntityMgr()->GetEntity(caster_hdl_);
				//self_->NotifyHpChangeEx(caster, snapshot_);
				self_->SetHp(self_->GetHp() + snapshot_); // 这个还是会广播，但是只是赋值
			}
			else if (conf_->args.d == Attribute::atHpMax)
			{
				//Creature *caster = (Creature*)GetGameEngine()->GetEntityMgr()->GetEntity(caster_hdl_);

				attribute_ = new Attribute();
				attribute_->Set(Attribute::atHpMax, snapshot_);
				self_->GetSkillEffectSystem()->CalcAttributes();
				self_->SetHp(self_->GetHp() + snapshot_);

				//self_->NotifyHpChangeEx(caster, snapshot_);
				//self_->NotifyAttr(Attribute::atHpMax, self_->GetMaxHp());
			}
			else
			{
				if (conf_->args.d < 0 || conf_->args.d >= Attribute::atCount)
					return;
				attribute_ = new Attribute();
				Attribute::AttributeType at = (Attribute::AttributeType)((int)conf_->args.d);
				attribute_->Set(at, snapshot_);
				self_->GetSkillEffectSystem()->CalcAttributes();
				//self_->NotifyAttr(at, self_->GetAttr(at)); // 目前没必要通知这些属性,除了速度
			}
		}
		break;
	case SkillEffectType_EnemyMarkAttr:
		if (next_effect_time_ == 0)
		{
			if (conf_->args.d < 0 || conf_->args.d >= Attribute::atCount)
				return;
			if (enemy_handle_ != 0) {
				MarkAttrs_Map &mark_map = self_->GetMarkAttrsMap();
				auto it = mark_map.find(enemy_handle_);
				if (it == mark_map.end()) {
					std::map<int, double> tmp;
					tmp[(int)conf_->args.d] = cache_snapshot_;
					mark_map[enemy_handle_] = tmp;
				} else {
					(it->second)[(int)conf_->args.d] += cache_snapshot_;
				}
				cache_snapshot_ = 0;
			}
		}
		break;
	case SkillEffectType_ExAttr:
		if (next_effect_time_ == 0)
		{
			if (conf_->args.d < 0 || conf_->args.d >= ExAttribute::eatCount)
				return;
			ex_attr_ = new ExAttribute();
			ExAttribute::ExAttributeType at = (ExAttribute::ExAttributeType)((int)conf_->args.d);
			ex_attr_->Set(at, snapshot_);
			self_->GetSkillEffectSystem()->CalcExAttributes();
		}
		break;
	case SkillEffectType_Status:
		if (next_effect_time_ == 0)
		{
			Status status;
			status.effect_id = conf_->id;	// 暂时与buff关联, 考虑扩展应做成与buff独立的在args里配的特效id,同时时间也独立配置
			status.end_time = GetGameEngine()->getTickCount() + conf_->duration;
			status.type = int(conf_->args.i);
			int stype = (int)conf_->args.i;
			if (stype == StatusType_Shild)
			{
				status.param.shield_power = snapshot_;
				status.param.decrease_percent = conf_->args.d;
			}
			else if (stype == StatusType_Stun || stype == StatusType_DeathCurse || stype == StatusType_AllCrit || stype == StatusType_Frozen)
			{
				status.end_time = GetGameEngine()->getTickCount() + snapshot_;
			}
			else if(stype == StatusType_HighestHurt)
			{
				status.param.highest_hurt = conf_->args.a;
			}
			self_->GetStatusSystem()->AddStatus(status);
		}
		break;
	case SkillEffectType_Summon:
		{
			// 召唤怪物
			Monster * pMon = self_->SummonBattlePet(int(conf_->args.a) + pet_add_lvl_);
			if (pMon)
			{
				BattleAttribute& bAttr = pMon->GetAttrs();
				bAttr.GMSet(Attribute::atAtk, pMon->GetAttr(Attribute::atAtk) + pet_add_atk);
				bAttr.GMSet(Attribute::atPenetrate, pMon->GetAttr(Attribute::atPenetrate) + pet_penetrate);
				pMon->addCacheAttr(Attribute::atAtk, static_cast<int> ( pet_add_atk));
				pMon->addCacheAttr(Attribute::atPenetrate, static_cast<int> ( pet_penetrate) );
				pMon->GetSkillSystem()->AddPassiveSkill(Pet_Passive_Skill_ID + self_->GetExAttr(ExAttribute::eatPetSkillLevel));
			}
		}
		break;
	default:
		OutputMsg(rmTip, "Unknown skill effect type:%d", conf_->type);
		return;
	}
}

void SkillEffect::OnRemove()
{
	switch (conf_->type)
	{
	case SkillEffectType_Attr:
	{
		SafeDelete(attribute_);
		self_->GetSkillEffectSystem()->CalcAttributes();
		break;
	}
	case SkillEffectType_EnemyMarkAttr:
	{
		self_->GetSkillEffectSystem()->CalcMarkAttrs(enemy_handle_);
		break;
	}
	case SkillEffectType_ExAttr:
	{
		SafeDelete(ex_attr_);
		self_->GetSkillEffectSystem()->CalcExAttributes();
		break;
	}
	case SkillEffectType_Status:
	default:
		break;
	}
}

bool SkillEffect::InitSnapshot(Creature* caster, const SKILLRESULTPARAM::buff* buf)
{
	Creature *tar = caster;
	auto &args = conf_->args;
	switch (conf_->type)
	{
	case SkillEffectType_Damage:
		if (args.i == 1) tar = self_;
		if (tar)
		{
			snapshot_ = 0 - (int)(args.a * tar->GetAttr((int)args.b) + (int)args.c);
			if (buf) {
				snapshot_ += (0 - (int)(buf->a * tar->GetAttr((int)buf->b) + (int)buf->c));
			}
		}
		break;
	case SkillEffectType_Heal:
		if (args.i == 1) tar = self_;
		if (tar)
		{
			snapshot_ = (int)(args.a * tar->GetAttr((int)args.b)) + (int)args.c;
			if (buf) {
				snapshot_ += ((int)(buf->a * tar->GetAttr((int)buf->b)) + (int)buf->c);
			}
			if (0 > snapshot_) snapshot_ = 0;
		}
		break;
	case SkillEffectType_Attr:
	case SkillEffectType_EnemyMarkAttr:
		if (args.i == 1) tar = self_;
		if (tar)
		{
			snapshot_ = (int)(args.a * tar->GetAttr((int)args.b)) + (int)args.c;
			if (buf) {
				snapshot_ += ((int)(buf->a * tar->GetAttr((int)buf->b)) + (int)buf->c);
			}
		}
		break;
	case SkillEffectType_ExAttr:
		if (caster)
		{
			snapshot_ = (int)(args.a * caster->GetAttr((int)args.b)) + (int)args.c;
			if (buf)
			{
				snapshot_ += ((int)(buf->a * caster->GetAttr((int)buf->b)) + (int)buf->c);
			}
		}
		break;
	case SkillEffectType_Status:
		if (caster)
		{
			if ((int)args.i == StatusType_Shild)
			{
				float val = caster->GetSkillEffectSystem()->GetAddBearHurt();
				snapshot_ = (int)((args.a + val) * caster->GetAttr((int)args.b)) + (int)args.c;
				caster->GetSkillEffectSystem()->SetAddBearHurt(0.0f);
			}
			if ((int)args.i == StatusType_Stun)
				snapshot_ = (int)args.d == 0 ? conf_->duration : (int)caster->GetAttr(Attribute::atStunTime);
			if ((int)args.i == StatusType_Frozen)
				snapshot_ = conf_->duration;
			if ((int)args.i == StatusType_DeathCurse)
				snapshot_ = (int)args.d == 0 ? conf_->duration : caster->GetExAttr(ExAttribute::eatDeathCurseTime);
			if ((int)args.i == StatusType_AllCrit)
				snapshot_ = (int)args.d == 0 ? conf_->duration : caster->GetExAttr(ExAttribute::eatAllCritTime);
		}
		break;
	case SkillEffectType_Summon:
		if (buf && caster)
		{
			pet_add_lvl_ = (int)buf->a;
			pet_add_atk = buf->b * caster->GetAttr(Attribute::atAtk);
			pet_penetrate = (int)buf->c;
		}
		break;
	default:
		return true;
	}
	all_snapshot_ = snapshot_;
	cache_snapshot_ = snapshot_;
	return true;
}

void SkillEffect::SetEndTime(int64_t time)
{
	end_time_ = time + GetGameEngine()->getTickCount();
}

int SkillEffect::GetOverlayType()
{
	if (conf_)
	{
		return conf_->overlay_type;
	}
	return 0;
}