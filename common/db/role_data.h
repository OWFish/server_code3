#ifndef _DB_ROLE_DATA_H_
#define _DB_ROLE_DATA_H_

#include "common.h"
#include "common/datalist.h"
#include "common/property_set.h"

#define  MAX_FUWEN 8
#define MAX_WING_PILL 2 //�������������
#define MAX_SKILL_COUNT 8 //��������
#pragma  pack(push,1)
using namespace SrvDef;

//tolua_begin
struct SkillsData
{
	int skill_level[MAX_SKILL_COUNT]; //Ĭ��˳��ļ��ܵȼ�
	int skill_index[MAX_SKILL_COUNT]; //��ѡ����˳���Ӧ���±�
};

struct YuanShenData
{
	bool	slot_filled[6];
};

enum EquipSlotType
{
	EquipSlotType_Weapon = 0,//����
	EquipSlotType_Helmet,//1.ͷ��
	EquipSlotType_Coat,//2.�·�
	EquipSlotType_Necklace,//3.����
	EquipSlotType_Wrist,//4.����
	EquipSlotType_Belt,//5.����
	EquipSlotType_Ring,//6.��ָ
	EquipSlotType_Shoes,//7.Ь��
	EquipSlotType_Dzi,  //8.��ӡ
	EquipSlotType_Hats,  //9.����
	EquipSlotType_Mark,  //10.���
	EquipSlotType_Cloak,  //11.����
	EquipSlotType_Shield,  //12.����
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
	int		strength_lv;	//ǿ���ȼ�
	int		 fuling_lv;		//����ȼ�
	int		 gem_lv;		//��ʯ�ȼ�
	ItemData equip_data;
	int		zhuling_lv;		//ע��ȼ�
	int     soul_lv;		//ħ��ȼ�(1-8��λ��ʾ����ȼ���9-12��ʾħ��ȼ�)
	int		bless_lv;		//ף���ȼ�(����)(��û�õ�)
	int		fuling_exp;		//���龭��
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
	unsigned int ctime;//���ʱ��
	short pill[MAX_WING_PILL];
};

struct WingsEquip
{
	EquipSlotData wing_slot[WingSlotType_Max];
};

//����ϵͳ����
struct JingMaiData
{
	int level;
	int stage;
};

struct SkillsBreakData
{
	int skill_break_level[5];

};

//��������
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

#define HEIRLOOM_TYPE_MAX 8 //����װ�����λ����
//�޸�RoleData�Ļ���Ҫ֪ͨ�ͻ����޸�ͬ��RoleData��Э�飡
struct RoleData
{
	int id;
	int job;
	int sex;
	double power;
	SkillsData skills;
	EquipsData equips_data; //װ��
	ExRingsData ex_rings; //�ؽ�
	WingsData wings;	//���
	JingMaiData jingmai_data;	//����
	LoogsoulData  loogsoul_data; //����

	FuWenData fuwen_data; //ս��
	int heirloom[HEIRLOOM_TYPE_MAX];
	int weapon_soul_id;//��ǰʹ�õı���ID
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

