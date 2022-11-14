#ifndef _ACHIEVE_DATA_H_
#define _ACHIEVE_DATA_H_

#include "common.h"
#include "skill_data.h"
#include "common/datalist.h"


// 称号的存储的BYTE数量
#define MAX_TITLE_DATA_SIZE	 32
// 成就存储一共占用的字节数目
#define MAX_ACHIEVE_DATA_SIZE            256
// 成就勋章数量上限
#define MAX_MEDALS_COUNT			  256
#pragma once
#pragma pack (push, 1)

//成就的条件
struct ACHIEVECONDITION
{
	uint16_t eventId_;  //成就事件ID
	int  count_;    //事件的数量
};

struct ACHIEVEMEDAL
{
	uint8_t id_;			   //成就勋章的ID
	unsigned int reach_time_;  //获取日期
};

struct AchieveRankData
{
	int medal_cnt; //勋章个数
	ACHIEVEMEDAL medal_list_[MAX_MEDALS_COUNT];

	AchieveRankData() : medal_cnt(0){}
};

#pragma pack(pop)

#endif

