#pragma once
#include <map>

struct AIConditionConfig
{
	int type;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
};
typedef std::vector<AIConditionConfig> AIConditionConfigs;

struct SkillConditionConfig
{
	int type;
	int arg1;
	int arg2;
	int arg3;
	int arg4;
};

struct AIActionConfig
{
	~AIActionConfig(){ /*if (args) SafeDeleteArray(args);*/ }
	int duration;
	int interval;
	//int type;
	//char *args;
	int index;		// action索引  前16位暂时留空，3位表示state序号, 8位表示event序号, 5位表示action序号
};
typedef std::vector<AIActionConfig> AIActionConfigs;

struct AIEventConfig
{
	int delay;
	int lcnt;
	int interval;
	AIConditionConfigs conditions;
	AIActionConfigs	actions;
};
typedef std::vector<AIEventConfig> AIEventConfigs;

struct AiSkill
{
	uint8_t index; //第几个技能
	int skill_id; //技能的ID
	uint16_t first_delay;	// 第一次使用先延迟的时间
	uint16_t cd;			// cd时间
	uint16_t dis;				// x轴攻击距离
	SkillConditionConfig cond;//技能使用条件
};

typedef std::vector<AiSkill> MonsterSkills;
struct AIConfig
{
	int id;
	bool aggressive;		// AI类型： 主动、被动
	bool can_recover;		// 是否回复
	int dead_time;		// 死亡状态持续时间（在回收前处理事件）


	int vision;			// 视野
	int home_range;		// 活动范围 超出后回归	0 -1 不回归
	bool maxDam;

	MonsterSkills		skills;

	AIEventConfigs		born;
	AIEventConfigs		idle;
	AIEventConfigs		battle;
	AIEventConfigs		back;
	AIEventConfigs		dead;
};

class AIConfigPool
{
public:
	static bool Load(GameConfigData* data);
	static const AIConfig* Get(const int nId);
private:
	static std::map<int, AIConfig> config_pool_;
};


