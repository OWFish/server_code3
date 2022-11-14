#pragma once
//
//技能突破
//
#include "StdAfx.h"
#include "skill.h"

class SkillBreak
{
public:
	SkillBreak(Creature* creature);
	~SkillBreak();

typedef  void (SkillBreak::*CalcResultFunc)(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	const static int MAX_SKILLBREAK_MAX = 5;

	bool Init(RoleData* data);
	int calcSkillBreakId(int index,int lv);
	void Save(RoleData* data);
	int getConfId(int skillId);

	const Attribute& GetSkillBreakAttr() { return skillbreak_power_; }
	int GetSkillBreakLevel(int index);
	void UpgradeSkillBreakLevel(int index);
	void UpdateSkillBreakPower(int index);

	void ReloadSkillBreakPower();
public:
	void DoResult(SKILLRESULTPARAM & param, uint8_t& hitType);
	void Not(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void AddDamage(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void FormulaOne(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void AddDamageProportion(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void DisregardDef(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void AddStunPower(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void SetAddBearHurt(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void AddBuff(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void SetCurBuffInfo(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);
	void AddStunBuff(SKILLRESULTPARAM & param, uint8_t& hitType, const SkillBreakConf::arg* info);

private:
	Creature* self_;
	SkillsBreakData*  skillbreak_data_;
	Attribute			skillbreak_power_;		//系统战力

protected:
	static const CalcResultFunc Handlers[];

};