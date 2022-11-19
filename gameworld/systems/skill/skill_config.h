#pragma once

#include "config/game_config_data.h"
#include <map>
#include <vector>


enum SkillCastTargetType	
{
	SCTType_Undefined = 0,
	SCTType_Friend = 1,
	SCTType_Enemy = 2,
	SCTType_Self = 3,
	SCTType_MinHpRole = 4,	// Ѫ�����ټ�����ɫ������������
	SCTType_Max,
};

enum SkillAffectTargetType
{
	SATType_Undefined = 0,
	SATType_Friend = 1,
	SATType_Enemy = 2,
	SATType_Enemy_Self = 3,
	SATType_Max,
};

enum SkillCalcType
{
	SkillCalcType_NoDamage = 0,
	SkillCalcType_Damage = 1,
	SkillCalcType_Heal = 2,
	SkillCalcType_TogetherHit = 3,
	SkillCalcType_Multiple_Damage = 5,
	SkillCalcType_MultipleSkills = 6,
	SkillCalcType_Count,
};

enum SkillDamageType
{
	SkillDamageType_Sacred = 0,
	SkillDamageType_Physical,
	SkillDamageType_Magical,
};

enum EffectOverlayType
{
	EffectOverlayType_Cover = 0,
	EffectOverlayType_Extend,		// 1.ʱ���ӳ�
	EffectOverlayType_Over_Extend,	// 2.���Ӳ��ӳ�ʱ��
	EffectOverlayType_NoCover,		//3.���滻
	EffectOverlayType_Append,      //4.ֱ�ӵ���
};
/*
��������
1 �����˺�{ a = ϵ��, t = ʩ������������, b = ����ֵ }
2 ��Ѫ{ a = ϵ��, t = ʩ������������, b = ����ֵ }
3 ��������{ a = ϵ��, t1 = ʩ������������, b = ����ֵ, t2 = ������������ }
4 ����״̬
5 �ٻ�{ ����1id, ����2id������3id�� }
*/
enum SkillEffectType
{
	SkillEffectType_Damage	= 1,
	SkillEffectType_Heal	= 2,
	SkillEffectType_Attr	= 3,
	SkillEffectType_Status	= 4,
	SkillEffectType_Summon	= 5,
	SkillEffectType_ExAttr  = 6,
	SkillEffectType_EnemyMarkAttr = 7,
};

// ״̬����
enum StatusType
{
	StatusType_Invincibility = 0,	// �޵�(���ɱ����ƣ������˺�)
	StatusType_Stun = 1,		// ����(���ɲ��������ƶ���ʩ������
	StatusType_Shild = 2,		// ����(�ٷֱȵ����˺��������˺�������)
	StatusType_Armor = 3,		// ���壨���ɱ�λ�ƿ��ƣ�λ�ƣ�������
	StatusType_Bind = 4,		// ���������ƶ���
	StatusType_DeathCurse = 5,	// ����(���ܴ�������)
	StatusType_AllCrit = 6,		// �ض�������״̬
	StatusType_HighestHurt = 7, //����˺�
	StatusType_ResStun = 8,		// �ֿ�����(ֻ�ֿ�����)
	StatusType_Frozen = 9,		// ����(���ɲ��������ƶ���ʩ������
	StatusType_Count,
};

// �������Ч��ͨ��״̬����
enum EffectType
{
	EffectType_Palsy = 1,	// ���״̬
};

//�������ܴ�������
enum PassiveSkillCond
{
	PassiveSkillCond_Attack = 0, //����ǰ
	PassiveSkillCond_BeAttack = 1, //������ǰ
	PassiveSkillCond_OnCrit = 2,//�������˵�ʱ��
	PassiveSkillCond_BeCrit = 3,//�����˱���
	PassiveSkillCond_HpPer = 4, //����ֵ����p1
	PassiveSkillCond_KillTar = 5, //��ɱĿ��
	PassiveSkillCond_Death = 6, //����
	PassiveSkillCond_AfterAttack = 7, //���������Ѫǰ
	PassiveSkillCond_AfterTogetherHit = 8, //�ϻ�֮��
	PassiveSkillCond_Count
};

struct SkillBase
{
	SkillBase(void){
		memset(this, 0, sizeof(*this));
	}

	int id;
	float cast_range;
	int cd;
	int cast_type;
	int target_type;
	int affect_range;
	int affect_count;
	int calc_type;
};

struct SkillConfig
{
	SkillConfig(void) {
		passive.is = false;
		args.a = 0.0f;
		args.b = 0.0f;
		args.attr = 0;
	}

	SkillBase base;
	struct  
	{
		int rate;
		int cond;
		int p1;
		int p2;
		int p3;
		int p4;
		bool is;//�Ƿ��Ǳ�������
	} passive;
	struct { 
		float a;
		float b;
		float c;
		short attr;
		//short type;
	} args;
	int herd_mon_rate;
	int herd_boss_rate;
	int herd_player_rate;
	std::vector<int> other_skills;
	std::vector<int> tar_eff;
	std::vector<int> other_tar_eff;
	std::vector<int> self_eff;
	bool teleport;
	int repel_distance;
	bool no_public_cd;
	bool sync_cd;
	int efftime;
	int exp; //����������
};

//����ͻ��,��ʽ�������࣬���������
#define MAX_BREAK_VAL	5

struct SkillBreakConf
{
	//int id;
	//float cast_range;
	//int cd;
	//int cast_type;
	//int target_type;
	//int affect_range;
	//int affect_count;
	//int calc_type;
	SkillBase base;
	struct arg
	{
		int type;
		float vals[MAX_BREAK_VAL];
	};
	std::vector<arg> args;
	std::vector<int> buffs;
	int power;
};


struct EffectConfig
{
	int id;
	bool is_buff;
	int type;
	struct {
		float i;
		float a;
		float b;
		float c;
		float d;
	} args;
	int duration;
	int interval;
	int overlay_type;
	int group;
	std::vector<int> unionBuff;
	std::vector<int> otherBuffs;
	int probability;
	int overMaxCount;
	int delay;
	int skillid;
};

struct ImbaSkillRevise
{
	SkillBase base;//���ܻ�������
	float a;//����a����������ֵ
	int b;//����b����������ֵ
	int cd;//����CD
	int d;//�Թ�����˺�������ֱ���
	int crit;//�����ʼӳ�
	int critDamage; //�����˺�
	std::vector<int> self_eff;
	std::vector<int> target_eff;
	struct arg
	{
		int type;
		float vals[MAX_BREAK_VAL];
	};
	std::vector<arg> args;

	ImbaSkillRevise &operator+=(const ImbaSkillRevise &r) {
		a += r.a;
		b += r.b;
		cd += r.cd;
		d += r.d;
		crit += r.crit;
		critDamage += r.critDamage;
		base.affect_count += r.base.affect_count;
		base.affect_range += r.base.affect_range;
		for (auto  it:r.self_eff) {
			self_eff.push_back(it);
		}
		for (auto it : r.target_eff) {
			target_eff.push_back(it);
		}
		args.clear();
		//args.insert(args.begin(), r.args.begin(), r.args.end());
		for (auto it : r.args) {
			args.push_back(it);
		}
		return *this;
	}
	ImbaSkillRevise() {
		a = 0.0; b = 0; cd = 0; d = 0;
		crit = 0;
		critDamage = 0;
		self_eff.clear();
		target_eff.clear();
		args.clear();
	}
};

struct ImbaSkillReviseCfg
{
	int imba_id;//����ID
	ImbaSkillRevise revise;
};

typedef std::list<ImbaSkillReviseCfg> ImbaSkillReviseCfgList;
typedef std::map<int, ImbaSkillRevise>  GWSkillReviseMap;

class SkillConfigPool
{
public:
	static bool LoadSkill(GameConfigData* data);
	static bool LoadEffect(GameConfigData* data);
	static const SkillConfig* GetSkillConfig(int id);
	static const EffectConfig* GetEffectConfig(int id);
	static float GetSkillCastDistance(int id);
	static int GetSkillCd(int id);
	static bool LoadSkillPowerConfig(GameConfigData* data);
	static int GetSkillPowerPerLevel(int index){ return skill_power_pool[index]; }

	static const SkillBreakConf* GetSkillBreakConfig(int id);

	//��������ͻ������
	static bool LoadSkillBreak(GameConfigData* data);
	static bool LoadOneBreakArgs(GameConfigData* data, SkillBreakConf::arg& info);

	//��ȡ�����Լ�������������
	static bool LoadOneRevise(GameConfigData* data, ImbaSkillRevise &revise);
	static bool LoadImbaSkillRevise(GameConfigData* data);
	static bool LoadGwSkillRevise(GameConfigData* data);
	static bool LoadOneSevArgs(GameConfigData* data, ImbaSkillRevise::arg& info);
	static const ImbaSkillReviseCfgList* GetImbaSkillReviseConfig(int id);
	static const GWSkillReviseMap* GetGWSkillReviseConfig(int id);

private:
	static std::map<int, SkillConfig> skill_config_pool_;
	static std::map<int, EffectConfig> effect_config_pool_;
	static std::map<int, SkillBreakConf> break_conf_pool_; //����ͻ�����ñ�
	static std::map<int, int> skill_power_pool;
	static std::map<int, ImbaSkillReviseCfgList> imba_revise_pool_;//�����Լ��ܵ���������
	static std::map<int, GWSkillReviseMap> gw_revise_pool_;//����Լ��ܵ���������
};


