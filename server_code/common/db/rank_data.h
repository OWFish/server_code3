#ifndef _DB_RANK_H_
#define _DB_RANK_H_

#include "container/static_array_list.h"
#include "common/datalist.h"
#include "common/gem_def.h"
#include "item_data.h"
#include "wing_data.h"
#include "achieve_data.h"

using namespace container;

#define MAX_USER_EQUIP 19
#define MAX_PET_SKILL 16
#define MAX_PET_BASE 8
#define MAX_FIGHT 40
#define NEED_REMEMBER_PROPERTY 20
#define MAX_PET_EQUIP 4
enum RankType
{
    rtNone = 0,
    rtFightVal = 1, // ս������
    rtLevel = 2,	// �ȼ�����
	rtCharmWeek = 3,// ÿ����������
	rtAchieve = 4,	// �ɾ�����
	rtPet = 5,		// �������а�
	rtMount = 6,	// ��������
	rtWing = 7,		// ������а�
	rtSpirit = 8,	// ��������
	rtCharm = 9,	// ��������(����)
    rtRoot = 10,	// �������(���ã�
    rtMax,
};

#pragma pack(push, 1)
struct RankDbItem
{
	ActorId actorId_;
	int	rankId_;	// ���а�ı��
	int point_;		// ���еķ���������ǵȼ����У�������ǵȼ���������������У������������ֵ)
	int camp_;		// ������id
	int level_;		// �ȼ�
	int job_;		// ְҵ
	int sex_;		// �Ա�
	int fightVal_;	// ս����
	int mount_id_;// ����Ľ�ֵ�����ڿͻ���ȡ�����������
	int spirit_id_;	// �����ľ��磬���ڿͻ���ȡ�÷��������֣�ע�⣬��Щ�ֶ�ֻ���ض������а������
	int wing_;		// ���id
	int pet_type_;	// ��������id
	int pet_id_;    // ����id
	int qq_vip_;	// qqvip�ȼ�
	int weapon_;	// �������
	int model_;		// �·����
	int hair_;		// ͷ�����
	int stone_effect_;//��ʯ��Ч
	int stage_effect_;//�׼���Ч
	int wing_model_;//������
	int last_rank_;	// ��һ�ε�����
	int like_;		//���޴���
	int srvid_;		// ������id
	char actorName_[32];	//��ɫ��
	char guild_[32];		//������
	char petName_[32];		//������

	static const int MAX_COUNT = 100;

	RankDbItem() : actorId_(0), rankId_(0), point_(0), camp_(0), level_(1), job_(0), sex_(0), fightVal_(0), mount_id_(0),
		spirit_id_(0), wing_(0), pet_type_(0), pet_id_(0), qq_vip_(0), weapon_(0), model_(0), hair_(0), stone_effect_(0), stage_effect_(0), wing_model_(0), last_rank_(0), like_(0), srvid_(0)
	{
		actorName_[0] = 0;
		guild_[0] = 0;
		petName_[0] = 0;
	}
};
#pragma pack(pop)


#pragma pack(push, 1)
struct PetRankDbItem
{
	ActorId actorId_;
	int jingjie_;     //���ﾳ��
	int nature_;     //�����Ը�
	short pet_type_; //�������idx
	short skill_count_; //���ܸ���
	int skill_list_[MAX_PET_SKILL];	//һ��int��������id�͵ȼ� (��16 ����id ��16 �ȼ�)
	StaticDataList<ItemData, MAX_PET_EQUIP> items_;//����װ��

	static const int MAX_COUNT = 100;

	PetRankDbItem() : actorId_(0), jingjie_(0), nature_(0), pet_type_(0), skill_count_(0)
	{
		memset(skill_list_, 0, sizeof(skill_list_));
	}
};
#pragma pack(pop)

typedef StaticArrayList<RankDbItem, RankDbItem::MAX_COUNT> RankList;
typedef StaticArrayList<PetRankDbItem, PetRankDbItem::MAX_COUNT> PetRankList;

typedef StaticHashTable<int, RankDbItem::MAX_COUNT> LastRankList;
typedef StaticDataList<RankList, rtMax> AllRankList;
typedef StaticDataList<LastRankList, rtMax> AllLastRankList;

#pragma pack(push, 1)
struct RankData
{
	int property_[NEED_REMEMBER_PROPERTY]; //����ֵ
	int fight_list_[MAX_FIGHT];		//ս����ֵ

	RankData()
	{
		memset(property_, (int)0, sizeof(property_));
		memset(fight_list_, (int)-1, sizeof(fight_list_));
	}
};
#pragma pack(pop)


struct ActorRankData
{
	ActorId actorId_;		//��ɫid
	int dragon_;			//������Ϣ(����)
	int hasMount_;			//�Ƿ�����������
	//MountDataDb mount_data_;//��������
	StaticDataList<ItemData, MAX_USER_EQUIP> items_;//���װ��
	int hasWing_;			//�Ƿ��г������
	WingRankDbData wing_data_;//�������
	int hasSpirit_;				//�Ƿ��о�������
	SpiritRankData spirit_data_; //��������
	AchieveRankData achieve_data_; //�ɾ�����
	RankData rank_data_;		//���а������Ӱ�����

	uint8_t rankNum_[rtMax];	// ��ÿ��������������û���ϣ�����0
	
	ActorRankData() : actorId_(0), dragon_(0), hasMount_(0), hasWing_(0), hasSpirit_(0)
	{
		memset(rankNum_, 0, sizeof(rankNum_));
	}
};

struct ActorRankDataEx
{
	ActorRankData base_;
	char guild_[32];	// ���࣬�������
	int mount_id_;	// ����Ľ�ֵ�����ڿͻ���ȡ�����������
	int spirit_id_;		// �����ľ��磬���ڿͻ���ȡ�÷��������֣�ע�⣬��Щ�ֶ�ֻ���ض������а������
	int root_;			// ����ĵȼ�����
	int wing_;			// ���
	ActorRankDataEx() : mount_id_(0), spirit_id_(0), root_(0), wing_(0)
	{
		guild_[0] = 0;
	}
};



#endif

