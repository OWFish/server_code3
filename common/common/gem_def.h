#ifndef _GEM_DEF_H_
#define _GEM_DEF_H_

#include "common.h"


#define MAX_SPIRIT_SKILL 8
#define MAX_SPIRIT_COUNT 5
#define MAX_SPIRIT_SLOT 8

// �ɻ����
// �ɻ��������
#pragma pack( push, 1 )
struct SoulPropData {
	uint8_t type;	// ����
	uint8_t quality;	// Ʒ��
	uint8_t level;	// �ȼ�
	int expr;	// ����
	uint8_t lock; //�Ƿ��
};

struct SpiritSoul
{
	enum Type { tGem = 0, tHunt = 1 }; // ������������������ɻ�
	int id;	// ϵͳ���ɻ�����ID
	SoulPropData prop_data; // �ɻ�����
};

// ������������
struct GemInfo
{
	int state; // ��������
	int level; // �����ȼ�
	int expr; // ��������
	int score; // ��������
};

struct GemGuard
{
	int type;	//��������
	int level;	//���̵ȼ�
	int expr;	//���̾���

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
	int level_; //���ѵȼ�
	int model_id_; //�������
	int max_slot_cnt_; //������λ
	int spirit_cnt_; //Ԫ�ظ���
	int slot_cnt_[MAX_SPIRIT_COUNT];
	SpiritSoul spirit_[MAX_SPIRIT_COUNT][MAX_SPIRIT_SLOT];
	int skill_cnt_; //���ܸ���
	BaseSkillData skill_list_[MAX_SPIRIT_SKILL];
};

#pragma pack( pop )

#endif



