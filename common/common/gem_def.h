#ifndef _GEM_DEF_H_
#define _GEM_DEF_H_

#include "common.h"


#define MAX_SPIRIT_SKILL 8
#define MAX_SPIRIT_COUNT 5
#define MAX_SPIRIT_SLOT 8

// 仙魂对象
// 仙魂项的属性
#pragma pack( push, 1 )
struct SoulPropData {
	uint8_t type;	// 种类
	uint8_t quality;	// 品质
	uint8_t level;	// 等级
	int expr;	// 灵力
	uint8_t lock; //是否绑定
};

struct SpiritSoul
{
	enum Type { tGem = 0, tHunt = 1 }; // 法宝界面或炼魂界面的仙魂
	int id;	// 系统给仙魂分配的ID
	SoulPropData prop_data; // 仙魂属性
};

// 法宝基础属性
struct GemInfo
{
	int state; // 法宝境界
	int level; // 法宝等级
	int expr; // 法宝经验
	int score; // 法宝评分
};

struct GemGuard
{
	int type;	//灵侍类型
	int level;	//灵侍等级
	int expr;	//灵侍经验

	GemGuard()
	{
		type = 0;
		level = 0;
		expr = 0;
	}

	GemGuard(int type, int level = 1, int expr = 0)
	{
		this->type = type;
		this->level = level;
		this->expr = expr;
	}
};

struct SpiritRankData
{
	int level_; //觉醒等级
	int model_id_; //精灵外观
	int max_slot_cnt_; //能量槽位
	int spirit_cnt_; //元素个数
	int slot_cnt_[MAX_SPIRIT_COUNT];
	SpiritSoul spirit_[MAX_SPIRIT_COUNT][MAX_SPIRIT_SLOT];
	int skill_cnt_; //技能个数
	BaseSkillData skill_list_[MAX_SPIRIT_SKILL];
};

#pragma pack( pop )

#endif



