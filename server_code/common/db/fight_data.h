#ifndef _DB_FIGHT_H_
#define _DB_FIGHT_H_

#include "common.h"
#include "skill_data.h"
#include "common/datalist.h"


#define MAX_DB_SKILL 16
#define MAX_FIGHT_DATA 1000
#define FIGHT_PER_PAGE 15
#define MAX_FIGHT_LOG	50

#pragma pack(push, 1)
struct FightDBData
{
	ActorId aid_;
	ACTORNAME name_;
	int serverid_; 
	int sex_;
	int job_;
	int fight_value_;
	int gid_;	// 所在帮派的ID
	int weapon_;	//武器外观
	int wing_;		//翅膀外观
	int props_[P_MAX_CREATURE];	//一般生物属性集合
	int hair_;
	int sprite_;	//精灵
	int social_;	//帮派职位
	int guild_level_; //帮派排名
	//以下全部添加到props下
	
	//int level_;
	//int icon_;
	//int model_;
	//int max_hp_;
	//int max_mp_;
	//int speed_;
	//int out_attack_;
	//int out_defence_;
	//int in_attack_;
	//int in_defence_;
	//int all_attack_;
	//int sub_def_;
	//int baoji_;
	//int shanbi_;
	//int hit_rate_;
	//int attack_append_;
	//float hp_renew_;
	//float mp_renew_;
	//int attack_speed_;
	//int in_attack_damage_add_;
	//int out_attack_damage_add_;
	//int lilian_;		// 这期获得的历练(无用)

	int skill_cnt_;	// 技能数量
	BaseSkillData skills_[MAX_DB_SKILL]; // 技能列表(角色技能)

	int other_skill_cnt_;	//其他系统技能数量
	BaseSkillData other_skills_[MAX_DB_SKILL]; //其他系统的技能列表, 不包含被动技能(只加属性)

	int nIndex;		//当前排名
	int prev_index; // 上次的排名，用于显示趋势，每天凌晨记录

	int attack_type_;	// 攻击类型

	int init_data_;	// 初始数据

	FightDBData()
	{
		wing_ = 0;
		hair_ = 0;
		sprite_ = 0;
		skill_cnt_ = 0;
		other_skill_cnt_ = 0;
		attack_type_ = 1;
		weapon_ = 0;
		social_ = 0;
		guild_level_ = 0;
		memset(props_, 0, sizeof(props_));
		prev_index = 1000000;
	}

	// 获取排名趋势
	int GetTrend()
	{
		if (nIndex > prev_index)
			return 0;
		else if (nIndex < prev_index)
			return 2;

		return 1;
	}
};

// 对战玩家的数据
struct FightActorData
{
	ActorId id_;
	int rank_;		// 对战后排名
	int serverid_;
	int sex_;
	int job_;
	int level_;
	ACTORNAME name_;
};

// 竞技场对战记录
struct FightLogData
{
	unsigned int time_;	// 时间
	FightActorData aid1_; // 挑战玩家
	FightActorData aid2_; // 被挑战玩家
	int result_;	// 挑战结果
};

// 个人对战记录
struct FightLog
{
	int date_;
	int type_;
	int result_;
	int rank_;		// 对战后排名
	int enemyid_;
	int encamp_;
	int ensex_;
	int enjob_;
	int enlevel_;
	ACTORNAME enname_;
};


// 宠物技能信息
struct FightPetSkill
{
	int skillId_;	// 技能id
	int level_;
};

struct FightPetData
{
	int title_;			//
	int mid_;			// 怪物ID
	int level_;
	//int name_rgb_;
};

#pragma pack(pop)

#endif

