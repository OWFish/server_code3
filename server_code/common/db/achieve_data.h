#ifndef _ACHIEVE_DATA_H_
#define _ACHIEVE_DATA_H_

#include "common.h"
#include "skill_data.h"
#include "common/datalist.h"


// �ƺŵĴ洢��BYTE����
#define MAX_TITLE_DATA_SIZE	 32
// �ɾʹ洢һ��ռ�õ��ֽ���Ŀ
#define MAX_ACHIEVE_DATA_SIZE            256
// �ɾ�ѫ����������
#define MAX_MEDALS_COUNT			  256
#pragma once
#pragma pack (push, 1)

//�ɾ͵�����
struct ACHIEVECONDITION
{
	uint16_t eventId_;  //�ɾ��¼�ID
	int  count_;    //�¼�������
};

struct ACHIEVEMEDAL
{
	uint8_t id_;			   //�ɾ�ѫ�µ�ID
	unsigned int reach_time_;  //��ȡ����
};

struct AchieveRankData
{
	int medal_cnt; //ѫ�¸���
	ACHIEVEMEDAL medal_list_[MAX_MEDALS_COUNT];

	AchieveRankData() : medal_cnt(0){}
};

#pragma pack(pop)

#endif

