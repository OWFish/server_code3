#pragma once

#include "../skill_def.h"

struct EffectConfig;
class Attribute;
class SkillEffect
{
public:
	// 附加的状态类型定义，与配置类型有区别
	enum StatusType
	{
		stStun			= 0,
		stMagicShield	= 1,
	};
	SkillEffect();
	~SkillEffect();

	bool Init(Creature *self, Creature* caster, int id, const SKILLRESULTPARAM::buff* buf, Creature *enemy);
	void OnTimeCheck(int64_t);
	bool IsInvalid() { return is_invalid_; }
	void OnRemove();
	Attribute* GetAttr() { return attribute_; }
	ExAttribute* GetExAttr() { return ex_attr_; }
	int GetId();
	int GetGroup();
	void SetInvalid() { is_invalid_ = true; }
	void SetEndTime(int64_t time);
	int GetSnapshot() { return snapshot_; }
	int GetAllSnapshot() { return all_snapshot_; }
	void AddCacheSnapshot(int val) { cache_snapshot_ += val; all_snapshot_ += val; }
	void ResetCacheSnapshot() { cache_snapshot_ = 0;}
	void Refresh() { next_effect_time_ = 0; }
	int GetOverlayType();
	uint64_t GetEnemyHandle() { return enemy_handle_; }
	const EffectConfig* GetConfig() { return conf_; }
	Creature *GetCreature() { return self_; }
private:
	void OnEffect();
	bool InitSnapshot(Creature* caster, const SKILLRESULTPARAM::buff* buf);
private:
	const EffectConfig* conf_;
	EntityHandle caster_hdl_;

	Creature *self_;
	int snapshot_;	// 快照
	int cache_snapshot_;//临时数据
	int all_snapshot_;	//叠加数据
	int64_t next_effect_time_;
	int64_t end_time_;
	bool is_invalid_; // 失效标记
	Attribute* attribute_;
	ExAttribute* ex_attr_;
	int pet_add_lvl_;
	double pet_add_atk;
	double pet_penetrate;
	uint64_t enemy_handle_;
};