#include "StdAfx.h"
#include "skill_break.h"

//#include "entity/creature.h"
//#include "db/role_data.h"

const SkillBreak::CalcResultFunc SkillBreak::Handlers[] =
{
	&SkillBreak::Not, //附加n点伤害
	&SkillBreak::AddDamage, //附加n点伤害
	&SkillBreak::FormulaOne, //按指定公式(1* 玩家属性2 +3)
	&SkillBreak::AddDamageProportion, //附加n点(原本伤害的百份比,参数最大配置为1=100%)伤害
	&SkillBreak::DisregardDef, // 无视防御参数最大配置为1=100%
	&SkillBreak::AddStunPower, // 增加麻痹机率
	&SkillBreak::SetAddBearHurt, //修改玩家放出承伤BUFF技能的系数
	&SkillBreak::AddBuff, //添加BUFF（这里只有技能效果）(参数1：等于1为自己加，等于2为目标加, 参数2=BUFFID)
	&SkillBreak::SetCurBuffInfo, //修改指定BUFF的信息
	&SkillBreak::AddStunBuff, //增加一个麻痹BUFF
};

SkillBreak::SkillBreak(Creature* creature)
: self_(creature),
skillbreak_data_(nullptr)
{
	skillbreak_power_.Reset();
}

SkillBreak::~SkillBreak()
{
}

bool SkillBreak::Init(RoleData* data)
{
	if (data == NULL)
		return false;

	ReloadSkillBreakPower();
	return true;
}

int SkillBreak::calcSkillBreakId(int index,int lv)
{
	Role *role = (Role*)self_;
	int skillbreak_id = 10000 * role->GetJob() + 1000 * index + lv;
	return skillbreak_id;
}

int SkillBreak::getConfId(int skillId)
{
	int idx = ((int)(skillId * 0.001f)) % 10;
	int lvl = GetSkillBreakLevel(idx - 1);
	if (lvl <= 0) return 0;
	return ((int)(skillId * 0.001)) * 1000 + lvl;
}

void SkillBreak::Save(RoleData* data)
{

}

void SkillBreak::UpgradeSkillBreakLevel(int index)
{
	if (index < 0 || index >= SkillBreak::MAX_SKILLBREAK_MAX)
		return;
	skillbreak_data_->skill_break_level[index]++;
	UpdateSkillBreakPower(index);
}

void SkillBreak::UpdateSkillBreakPower(int index)
{
	if (index < 0 || index >= SkillBreak::MAX_SKILLBREAK_MAX)
		return;
	if (self_->GetType() != EntityType_Role)
		return;

	int lv = GetSkillBreakLevel(index);
	if (lv <= 0) return;

	int skillbreak_id = 0;
	const SkillBreakConf* sbConf = nullptr;

	int skill_power = static_cast<int> ( skillbreak_power_.GetExtraPower() );

	if (lv - 1 >= 1)
	{
		skillbreak_id = calcSkillBreakId(index + 1, lv - 1);
		sbConf = SkillConfigPool::GetSkillBreakConfig(skillbreak_id);
		if (sbConf == nullptr) return;
		skill_power -= sbConf->power;
	}

	skillbreak_id = calcSkillBreakId(index+1,lv);
	sbConf = SkillConfigPool::GetSkillBreakConfig(skillbreak_id);
	if (sbConf == nullptr) return;
	skill_power += sbConf->power;

	skillbreak_power_.SetExtraPower(skill_power);

	Role *role = (Role*)self_;
	role->CalcAttributes();
}

void SkillBreak::ReloadSkillBreakPower()
{
	if (self_->GetType() != EntityType_Role)
		return;

	int lv = 0;
	int skill_power = 0;
	int skillbreak_id = 0;
	const SkillBreakConf* sbConf = nullptr;
	for (int index = 0; index < MAX_SKILLBREAK_MAX; ++index)
	{
		//更新战力
		lv = GetSkillBreakLevel(index);
		if (lv <= 0) continue;
		
		skillbreak_id = calcSkillBreakId(index + 1, lv);
		sbConf = SkillConfigPool::GetSkillBreakConfig(skillbreak_id);
		if (sbConf == nullptr) return;
		skill_power += sbConf->power;
	}
	skillbreak_power_.SetExtraPower(skill_power);
	Role *role = (Role*)self_;
	role->CalcAttributes();
}

int SkillBreak::GetSkillBreakLevel(int index)
{
	if (index < 0 || index >= SkillBreak::MAX_SKILLBREAK_MAX)
		return 0;

	return skillbreak_data_->skill_break_level[index];
}

void SkillBreak::DoResult(SKILLRESULTPARAM & param, uint8_t& hitType)
{

	if (!param.self || !param.target || !param.skill) return;

	int id = getConfId(param.skill->GetId());
	const SkillBreakConf* sbConf = SkillConfigPool::GetSkillBreakConfig(id);
	if (sbConf == nullptr) return;
	for (size_t i = 0; i < sbConf->args.size(); i++)
	{
		(this->*SkillBreak::Handlers[sbConf->args[i].type])(param, hitType, &(sbConf->args[i]));
	}
}

void SkillBreak::Not(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
}

void SkillBreak::AddDamage(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.damage += info->vals[0];
}

void SkillBreak::FormulaOne(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.damage += (info->vals[0] * param.self->GetAttr((int)info->vals[1]) + info->vals[2]);
}


void SkillBreak::AddDamageProportion(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.damage += (param.damage * info->vals[0]);
}

void SkillBreak::DisregardDef(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.def_disregard = param.def_disregard + info->vals[0];
}

void SkillBreak::AddStunPower(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.stun_power = param.stun_power + info->vals[0];
	param.stunTime = (double)(param.stun_power + info->vals[1]);
}

void SkillBreak::SetAddBearHurt(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	param.self->GetSkillEffectSystem()->SetAddBearHurt(info->vals[0]);
}

void SkillBreak::AddBuff(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
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

void SkillBreak::SetCurBuffInfo(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	tagSkillResultParam::buff buf;

	buf.buff_id = (int)info->vals[0];
	buf.buff_time = (int)info->vals[1];
	buf.a = info->vals[2];
	buf.b = info->vals[3];
	buf.c = info->vals[4];
	param.buffs[buf.buff_id] = buf;
}

void SkillBreak::AddStunBuff(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info)
{
	double stun_power = param.self->GetAttr(Attribute::atStunPower) + info->vals[0];
	double stun_res = param.target->GetAttr(Attribute::atStunRes);
	bool stun = wrand(10000) < (stun_power * (1 - stun_res / 10000.0));
	if (stun)
	{
		param.target->GetSkillEffectSystem()->AddEffect(param.self, (int)info->vals[1]);
	}
}