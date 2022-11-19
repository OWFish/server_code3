#ifndef _SKILL_DB_DATA_H_
#define _SKILL_DB_DATA_H_

#include "common.h"

/****************************************************************************************
* 技能DB相关的一些结构体的定义                                               
****************************************************************************************/

//玩家的一个技能需要存盘的数据
#pragma pack(push, 1)
struct BaseSkillData
{
	uint16_t sid_;				//技能的ID
	unsigned char level_;		//技能的等级,如果没有学习就是0
	unsigned int  cool_sec_;			 //冷却时间(单位秒）
	unsigned int  exp_;          //技能的经验
};

struct PetSkillDb
{
	int skillid_;
	int level_;
	int exp_;
	unsigned int cd_;
	int r1_;
	int r2_;
	int r3_;
	PetSkillDb()
	{
		memset(this, 0, sizeof(*this));
	}
};
#pragma pack(pop)
#endif

