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
    rtFightVal = 1, // 战力排行
    rtLevel = 2,	// 等级排行
	rtCharmWeek = 3,// 每周魅力排行
	rtAchieve = 4,	// 成就排行
	rtPet = 5,		// 宠物排行榜
	rtMount = 6,	// 坐骑排行
	rtWing = 7,		// 翅膀排行榜
	rtSpirit = 8,	// 精灵排行
	rtCharm = 9,	// 魅力排行(无用)
    rtRoot = 10,	// 灵根排行(无用）
    rtMax,
};

#pragma pack(push, 1)
struct RankDbItem
{
	ActorId actorId_;
	int	rankId_;	// 排行榜的编号
	int point_;		// 排行的分数（如果是等级排行，这个就是等级，如果是魅力排行，这个就是魅力值)
	int camp_;		// 服务器id
	int level_;		// 等级
	int job_;		// 职业
	int sex_;		// 性别
	int fightVal_;	// 战斗力
	int mount_id_;// 坐骑的阶值，用于客户端取得坐骑的名字
	int spirit_id_;	// 法宝的境界，用于客户端取得法宝的名字，注意，这些字段只有特定的排行榜才有用
	int wing_;		// 翅膀id
	int pet_type_;	// 宠物类型id
	int pet_id_;    // 宠物id
	int qq_vip_;	// qqvip等级
	int weapon_;	// 武器外观
	int model_;		// 衣服外观
	int hair_;		// 头发外观
	int stone_effect_;//宝石特效
	int stage_effect_;//阶级特效
	int wing_model_;//翅膀外观
	int last_rank_;	// 上一次的排名
	int like_;		//点赞次数
	int srvid_;		// 服务器id
	char actorName_[32];	//角色名
	char guild_[32];		//仙宗名
	char petName_[32];		//宠物名

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
	int jingjie_;     //宠物境界
	int nature_;     //宠物性格
	short pet_type_; //宠物外观idx
	short skill_count_; //技能个数
	int skill_list_[MAX_PET_SKILL];	//一个int包含技能id和等级 (低16 技能id 高16 等级)
	StaticDataList<ItemData, MAX_PET_EQUIP> items_;//宠物装备

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
	int property_[NEED_REMEMBER_PROPERTY]; //属性值
	int fight_list_[MAX_FIGHT];		//战斗力值

	RankData()
	{
		memset(property_, (int)0, sizeof(property_));
		memset(fight_list_, (int)-1, sizeof(fight_list_));
	}
};
#pragma pack(pop)


struct ActorRankData
{
	ActorId actorId_;		//角色id
	int dragon_;			//神龙信息(无用)
	int hasMount_;			//是否有坐骑数据
	//MountDataDb mount_data_;//坐骑数据
	StaticDataList<ItemData, MAX_USER_EQUIP> items_;//玩家装备
	int hasWing_;			//是否有翅膀数据
	WingRankDbData wing_data_;//翅膀数据
	int hasSpirit_;				//是否有精灵数据
	SpiritRankData spirit_data_; //精灵数据
	AchieveRankData achieve_data_; //成就数据
	RankData rank_data_;		//排行榜杂七杂八数据

	uint8_t rankNum_[rtMax];	// 在每个榜的排名，如果没排上，就是0
	
	ActorRankData() : actorId_(0), dragon_(0), hasMount_(0), hasWing_(0), hasSpirit_(0)
	{
		memset(rankNum_, 0, sizeof(rankNum_));
	}
};

struct ActorRankDataEx
{
	ActorRankData base_;
	char guild_[32];	// 冗余，方便查找
	int mount_id_;	// 坐骑的阶值，用于客户端取得坐骑的名字
	int spirit_id_;		// 法宝的境界，用于客户端取得法宝的名字，注意，这些字段只有特定的排行榜才有用
	int root_;			// 灵根的等级数据
	int wing_;			// 翅膀
	ActorRankDataEx() : mount_id_(0), spirit_id_(0), root_(0), wing_(0)
	{
		guild_[0] = 0;
	}
};



#endif

