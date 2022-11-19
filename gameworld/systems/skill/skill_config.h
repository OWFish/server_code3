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
	SCTType_MinHpRole = 4,	// 血量最少己方角色，不包括宠物
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
	EffectOverlayType_Extend,		// 1.时间延长
	EffectOverlayType_Over_Extend,	// 2.叠加并延长时间
	EffectOverlayType_NoCover,		//3.不替换
	EffectOverlayType_Append,      //4.直接叠加
};
/*
补充类型
1 附加伤害{ a = 系数, t = 施法者属性类型, b = 附加值 }
2 加血{ a = 系数, t = 施法者属性类型, b = 附加值 }
3 附加属性{ a = 系数, t1 = 施法者属性类型, b = 附加值, t2 = 附加属性类型 }
4 附加状态
5 召唤{ 怪物1id, 怪物2id，怪物3id… }
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

// 状态类型
enum StatusType
{
	StatusType_Invincibility = 0,	// 无敌(不可被控制，不受伤害)
	StatusType_Stun = 1,		// 昏迷(不可操作，（移动，施法））
	StatusType_Shild = 2,		// 护盾(百分比抵消伤害，抵消伤害有总量)
	StatusType_Armor = 3,		// 霸体（不可被位移控制（位移，定身））
	StatusType_Bind = 4,		// 定身（不可移动）
	StatusType_DeathCurse = 5,	// 死咒(不能触发神佑)
	StatusType_AllCrit = 6,		// 必定暴击的状态
	StatusType_HighestHurt = 7, //最高伤害
	StatusType_ResStun = 8,		// 抵抗昏迷(只抵抗昏迷)
	StatusType_Frozen = 9,		// 冰封(不可操作，（移动，施法））
	StatusType_Count,
};

// 额外的特效表，通过状态附加
enum EffectType
{
	EffectType_Palsy = 1,	// 麻痹状态
};

//被动技能触发条件
enum PassiveSkillCond
{
	PassiveSkillCond_Attack = 0, //攻击前
	PassiveSkillCond_BeAttack = 1, //被攻击前
	PassiveSkillCond_OnCrit = 2,//暴击别人的时候
	PassiveSkillCond_BeCrit = 3,//被别人暴击
	PassiveSkillCond_HpPer = 4, //生命值低于p1
	PassiveSkillCond_KillTar = 5, //击杀目标
	PassiveSkillCond_Death = 6, //死亡
	PassiveSkillCond_AfterAttack = 7, //被攻击后扣血前
	PassiveSkillCond_AfterTogetherHit = 8, //合击之后
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
		bool is;//是否是被动技能
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
	int exp; //技能熟练度
};

//技能突破,公式参数不多，搞个定长的
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
	SkillBase base;//技能基本配置
	float a;//技能a参数的增加值
	int b;//技能b参数的增加值
	int cd;//减少CD
	int d;//对怪物的伤害增加万分比例
	int crit;//暴击率加成
	int critDamage; //暴击伤害
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
	int imba_id;//神器ID
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

	//读出技能突破配置
	static bool LoadSkillBreak(GameConfigData* data);
	static bool LoadOneBreakArgs(GameConfigData* data, SkillBreakConf::arg& info);

	//读取神器对技能修正的配置
	static bool LoadOneRevise(GameConfigData* data, ImbaSkillRevise &revise);
	static bool LoadImbaSkillRevise(GameConfigData* data);
	static bool LoadGwSkillRevise(GameConfigData* data);
	static bool LoadOneSevArgs(GameConfigData* data, ImbaSkillRevise::arg& info);
	static const ImbaSkillReviseCfgList* GetImbaSkillReviseConfig(int id);
	static const GWSkillReviseMap* GetGWSkillReviseConfig(int id);

private:
	static std::map<int, SkillConfig> skill_config_pool_;
	static std::map<int, EffectConfig> effect_config_pool_;
	static std::map<int, SkillBreakConf> break_conf_pool_; //技能突破配置表
	static std::map<int, int> skill_power_pool;
	static std::map<int, ImbaSkillReviseCfgList> imba_revise_pool_;//神器对技能的修正配置
	static std::map<int, GWSkillReviseMap> gw_revise_pool_;//神兵对技能的修正配置
};


