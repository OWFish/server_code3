#pragma once

#include "skill_config.h"
#include "db/skill_data.h"
#include "skill_def.h"

#define MABI_SKILL_EFFECT_ID 51001  //麻痹
#define DEATH_CURSE_EFFECT_ID 52001  //死咒
#define ALLCRIT_SKILL_EFFECT_ID 53001 //天珠技能
#define GOD_BLESS_EFFECT_ID 58001 //神佑
#define CURSE_SKILL_EFFECT_ID 80003 //传世装备诅咒,加上等级,这里占用 80004到80007

//冒泡效果ID
#define MABI_BUBBLE_TEXT_ID 1 //麻痹戒指
#define HUTI_BUBBLE_TEXT_ID 2 //护体特戒
#define SHENLI_BUBBLE_TEXT_ID 3 //神力特戒
#define SHANBI_BUBBLE_TEXT_ID 4 //闪避特戒
#define ZHILIAO_BUBBLE_TEXT_ID 5 //治疗特戒
#define KUANGBAO_BUBBLE_TEXT_ID 6 //狂爆特戒
#define FUHUO_BUBBLE_TEXT_ID 7 //复活特戒
#define CURSE_BUBBLE_TEXT_ID 13 //传世装备诅咒
#define VAMIRE_BUBBLE_TEXT_ID 14 //传世装备吸血
#define ATT_ADD_DAM_TEXT_ID 15 //兵魂攻击增加伤害
#define BE_ATT_ADD_HP_TEXT_ID 16 //兵魂被攻击加血
#define ATT_MB_ADD_DAM_TEXT_ID 17 //兵魂攻击麻痹伤害提升
#define HP_LT_ADD_BUFF_TEXT_ID 18 //兵魂生命低加回血buff
#define ATT_HP_LT_ADD_DAM_TEXT_ID 19 //兵魂攻击生命低加伤害
#define ATT_PER_DAM_TEXT_ID 20 //兵魂攻击打出的血+额外伤害
#define MULTIPLE_CRIT_BUBBLE_TEXT_ID 21 //多重暴击
#define RESIST_BUBBLE_TEXT_ID 22 //特戒的复活
#define MJBQ_HP_LT_ADD_BUFF_TEXT_ID 23 //秘籍不屈生命低加buff
#define HUNGU_FLOAT_TEXT_ID 24  //魂骨6件套特效
#define XINFA3_FLOAT_TEXT_ID 25  //心法3特效

//特定吸血技能
#define VamirePro_SKILL_ID 12 //断空斩
#define Pet_Passive_Skill_ID      36000 //宠物被动技能

class Skill
{
public:
	enum HitType
	{
		HitType_None = 0,	// 不显示
		HitType_Hit = 1,	// 命中
		HitType_Crit = 2,	// 暴击
		HitType_Dodge = 4,	// 闪避
		HitType_Lucky = 8,	// 幸运一击
		HitType_Together = 16,//合击
		HitType_ExDam = 32,//额外伤害
		HitType_Deter = 64,//玉佩的威慑
		HitType_Multiple = 128,//多段伤害
		HitType_ZhuiMing = 256,//追命伤害
		HitType_Deadly = 512,//致命一击
		HitType_Rdamage = 1024,//反伤
		HitType_Penet = 2048,//切割
		HitType_Poisoning = 4096,//中毒
		HitType_Bleed = 8192 ,//出血
	};

public:
	friend SkillSystem;
	~Skill();

	bool Init(int id);
	int GetId() { return conf_->base.id; }
	const SkillConfig* GetConfig() { return conf_; }
	bool CheckCast(Creature* self, Creature* target, ImbaSkillRevise& rev);
	bool Cast(Creature* self, Creature* target);
	Creature* SelectTarget(Creature* caster);	// 选择施法目标
	bool IsNoPublicCD() { return conf_->no_public_cd; };
	const SkillBase* GetRealConfig(Creature* caster);
private:
	Skill();
	typedef  double (Skill::*CalcSkillResultFunc)(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag);
	typedef  void (Skill::*CalcResultFunc)(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);

	double CalcSkillResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_NoDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_Damage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_Heal(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_TogetherHit(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_FixedDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_MultipleDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_MultipleSkills(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);

	void DoResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev);
	void Not(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddDamage(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void FormulaOne(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddDamageProportion(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void DisregardDef(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddStunPower(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void SetAddBearHurt(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void SetCurBuffInfo(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddStunBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);

	void GetAffectedTargets(Creature* self, Creature* target, std::vector<Creature*> &results, ImbaSkillRevise &rev);
	void DoRepel(Creature* self, Creature* target);
	void SyncAllRoleCDTick(Creature* self, int64_t tick);
	void SyncAllRoleAddEffect(Creature* self, int eff, SKILLRESULTPARAM::buff* buff);

	double getWeaponPeakPre(Creature * self, Creature * target);
	int getPerstigeDam(Creature * self);

private:
	const SkillConfig* conf_;
	int64_t cd_mtime_;
	static const CalcSkillResultFunc Handlers[];
	static const CalcResultFunc RevHandlers[];
};