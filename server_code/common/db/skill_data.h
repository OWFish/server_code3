#ifndef _SKILL_DB_DATA_H_
#define _SKILL_DB_DATA_H_

#include "common.h"

/****************************************************************************************
* ����DB��ص�һЩ�ṹ��Ķ���                                               
****************************************************************************************/

//��ҵ�һ��������Ҫ���̵�����
#pragma pack(push, 1)
struct BaseSkillData
{
	uint16_t sid_;				//���ܵ�ID
	unsigned char level_;		//���ܵĵȼ�,���û��ѧϰ����0
	unsigned int  cool_sec_;			 //��ȴʱ��(��λ�룩
	unsigned int  exp_;          //���ܵľ���
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

