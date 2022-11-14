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
	int gid_;	// ���ڰ��ɵ�ID
	int weapon_;	//�������
	int wing_;		//������
	int props_[P_MAX_CREATURE];	//һ���������Լ���
	int hair_;
	int sprite_;	//����
	int social_;	//����ְλ
	int guild_level_; //��������
	//����ȫ����ӵ�props��
	
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
	//int lilian_;		// ���ڻ�õ�����(����)

	int skill_cnt_;	// ��������
	BaseSkillData skills_[MAX_DB_SKILL]; // �����б�(��ɫ����)

	int other_skill_cnt_;	//����ϵͳ��������
	BaseSkillData other_skills_[MAX_DB_SKILL]; //����ϵͳ�ļ����б�, ��������������(ֻ������)

	int nIndex;		//��ǰ����
	int prev_index; // �ϴε�������������ʾ���ƣ�ÿ���賿��¼

	int attack_type_;	// ��������

	int init_data_;	// ��ʼ����

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

	// ��ȡ��������
	int GetTrend()
	{
		if (nIndex > prev_index)
			return 0;
		else if (nIndex < prev_index)
			return 2;

		return 1;
	}
};

// ��ս��ҵ�����
struct FightActorData
{
	ActorId id_;
	int rank_;		// ��ս������
	int serverid_;
	int sex_;
	int job_;
	int level_;
	ACTORNAME name_;
};

// ��������ս��¼
struct FightLogData
{
	unsigned int time_;	// ʱ��
	FightActorData aid1_; // ��ս���
	FightActorData aid2_; // ����ս���
	int result_;	// ��ս���
};

// ���˶�ս��¼
struct FightLog
{
	int date_;
	int type_;
	int result_;
	int rank_;		// ��ս������
	int enemyid_;
	int encamp_;
	int ensex_;
	int enjob_;
	int enlevel_;
	ACTORNAME enname_;
};


// ���＼����Ϣ
struct FightPetSkill
{
	int skillId_;	// ����id
	int level_;
};

struct FightPetData
{
	int title_;			//
	int mid_;			// ����ID
	int level_;
	//int name_rgb_;
};

#pragma pack(pop)

#endif

