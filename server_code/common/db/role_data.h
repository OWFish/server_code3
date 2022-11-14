#ifndef _DB_ROLE_DATA_H_
#define _DB_ROLE_DATA_H_

#include "common.h"
#include "common/datalist.h"
#include "common/property_set.h"

#define  MAX_FUWEN 8
#define MAX_WING_PILL 2 //翅膀提升丹种类
#define MAX_SKILL_COUNT 8 //技能数量
#pragma  pack(push,1)
using namespace SrvDef;

//tolua_begin
struct SkillsData
{
	int skill_level[MAX_SKILL_COUNT]; //默认顺序的技能等级
	int skill_index[MAX_SKILL_COUNT]; //自选技能顺序对应的下标
};

struct YuanShenData
{
	bool	slot_filled[6];
};

enum EquipSlotType
{
	EquipSlotType_Weapon = 0,//武器
	EquipSlotType_Helmet,//1.头盔
	EquipSlotType_Coat,//2.衣服
	EquipSlotType_Necklace,//3.项链
	EquipSlotType_Wrist,//4.护腕
	EquipSlotType_Belt,//5.腰带
	EquipSlotType_Ring,//6.戒指
	EquipSlotType_Shoes,//7.鞋子
	EquipSlotType_Dzi,  //8.官印
	EquipSlotType_Hats,  //9.斗笠
	EquipSlotType_Mark,  //10.面甲
	EquipSlotType_Cloak,  //11.披风
	EquipSlotType_Shield,  //12.盾牌
	EquipSlotType_Max,
};

enum WingSlotType
{	
	WingSlotType_Hub = 0,
	WingSlotType_Stone,
	WingSlotType_Feathers,
	WingSlotType_Colorplume,

	WingSlotType_Max,
};

struct EquipSlotData
{
	int		strength_lv;	//强化等级
	int		 fuling_lv;		//附灵等级
	int		 gem_lv;		//宝石等级
	ItemData equip_data;
	int		zhuling_lv;		//注灵等级
	int     soul_lv;		//魔魂等级(1-8部位表示至尊等级，9-12表示魔魂等级)
	int		bless_lv;		//祝福等级(开光)(暂没用到)
	int		fuling_exp;		//附灵经验
};

struct EquipsData
{
	EquipSlotData slot_data[EquipSlotType_Max];
	EquipSlotData god_slot_data[EquipSlotType_Dzi];
};

struct ExRingsData
{
	int ring_level[4];
};

struct WingsData
{
	int level;
	//int star_lv;
	int exp;
	int openStatus;
	unsigned int ctime;//清空时间
	short pill[MAX_WING_PILL];
};

struct WingsEquip
{
	EquipSlotData wing_slot[WingSlotType_Max];
};

//经脉系统数据
struct JingMaiData
{
	int level;
	int stage;
};

struct SkillsBreakData
{
	int skill_break_level[5];

};

//龙魂数据
struct LoogsoulData
{
	int stage;
	int level;
	int exp;
	char act;
};

struct ShieldData
{
	int stage;
	int level;
	int exp;
	char act;
};

struct XueyuData
{
	int stage;
	int level;
	int exp;
	char act;
};

struct FuWenData
{
	ItemData fuwen_slot[MAX_FUWEN];
};

#define HEIRLOOM_TYPE_MAX 8 //传世装备最大部位数量
//修改RoleData的话，要通知客户端修改同步RoleData的协议！
struct RoleData
{
	int id;
	int job;
	int sex;
	double power;
	SkillsData skills;
	EquipsData equips_data; //装备
	ExRingsData ex_rings; //特戒
	WingsData wings;	//翅膀
	JingMaiData jingmai_data;	//经脉
	LoogsoulData  loogsoul_data; //龙魂

	FuWenData fuwen_data; //战纹
	int heirloom[HEIRLOOM_TYPE_MAX];
	int weapon_soul_id;//当前使用的兵魂ID
};

struct RoleDatas
{
	int role_count;
	RoleData roles[3];

	RoleDatas() { memset(this, 0, sizeof(RoleDatas)); }
};

//tolua_end
#pragma  pack(pop)

#endif

