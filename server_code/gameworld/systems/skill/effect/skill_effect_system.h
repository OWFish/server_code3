#pragma once

#include <vector>
#include "../skill_def.h"

struct EffectArg
{
	int bufid;//bufid
	SKILLRESULTPARAM::buff* buf;
	EntityHandle enemy_hdl;//敌人的的handle
	EntityHandle caster_hdl;//的handle
	int64_t attack_time;//攻击时间
	int64_t end_time; //结束时间
	void clear()
	{
		bufid = 0;
		buf = nullptr;
		enemy_hdl = 0;
		caster_hdl = 0;
		attack_time = 0;
		end_time = 0;
	}
};

class SkillEffect;
class Creature;
class SkillEffectSystem
{
public:
	SkillEffectSystem(Creature *self);
	~SkillEffectSystem();

	void Destroy();
	void Clear();
	bool AddEffect(Creature* caster, int id, int64_t time = -1, SKILLRESULTPARAM::buff* buf= nullptr, Creature *enemy = nullptr, bool isSubBuff=false,bool isDelay = true);
	bool HasEffect(int id);
	bool DelEffect(int id);
	void removeUnionBuff(int id);
	void OnRun(int64_t now_t);
	const Attribute& GetAttr() { return attribute_; }
	const ExAttribute& GetExAttr() { return ex_attribute_; }
	void CalcAttributes();
	void CalcExAttributes();
	void CalcMarkAttrs(uint64_t enemy_handle);
	void OnExitScene();
	inline void SetAddBearHurt(float val)
	{
		add_bear_hurt_ = val;
	}
	inline float GetAddBearHurt()
	{
		return add_bear_hurt_;
	}

private:
	void Remove(int index);
private:
	Creature *self_;
	std::vector<SkillEffect*> effect_list_;
	bool on_run_effect_;
	std::map<int, int> effect_group_count_;
	Timer	logic_timer_;
	float add_bear_hurt_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
	std::list<EffectArg> delay_buf_; //延迟buf列表
};