#ifndef _WING_H_
#define _WING_H_

#include "common.h"
#include "skill_data.h"
#include "common/datalist.h"


#define MAX_WING_SKILL 8 //��Ӧwingsystem��MAX_SKILL
#define MAX_WING_EQUIP 4

#pragma pack(push, 1)
struct WingSkill : public BaseSkillData
{
	int64_t guid_;
};

struct WingRankData
{
	int skill_grid_; //���ܿո�
	int skill_cnt_;	//���ܸ���
	BaseSkillData skill_list_[MAX_WING_SKILL];
};

struct WingRankDbData
{
	WingRankData data_;
	StaticDataList<ItemData, MAX_WING_EQUIP> equip_;
};
#pragma pack(pop)

#endif