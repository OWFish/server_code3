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
	int index;		// action����  ǰ16λ��ʱ���գ�3λ��ʾstate���, 8λ��ʾevent���, 5λ��ʾaction���
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
	uint8_t index; //�ڼ�������
	int skill_id; //���ܵ�ID
	uint16_t first_delay;	// ��һ��ʹ�����ӳٵ�ʱ��
	uint16_t cd;			// cdʱ��
	uint16_t dis;				// x�ṥ������
	SkillConditionConfig cond;//����ʹ������
};

typedef std::vector<AiSkill> MonsterSkills;
struct AIConfig
{
	int id;
	bool aggressive;		// AI���ͣ� ����������
	bool can_recover;		// �Ƿ�ظ�
	int dead_time;		// ����״̬����ʱ�䣨�ڻ���ǰ�����¼���


	int vision;			// ��Ұ
	int home_range;		// ���Χ ������ع�	0 -1 ���ع�
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


