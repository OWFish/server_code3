#pragma once
#include "attr/attribute.h"
#include "attr/ex_attr.h"

// 秘籍
class Role;


#define MAX_MIJI_LEVEL 9
enum MiJiType
{
	MiJiType_None = 0,
	MiJiType_Hp,
	MiJiType_Atk,
	MiJiType_Def,
	MiJiType_CritRate,
	MiJiType_DamageDec,
	MiJiType_CritEnhance,
	MiJiType_Penetrate,	// 穿透 无视%n防御
	MiJiType_Reflect,
	MiJiType_Pierce,   // 穿刺 无视反伤, 加百分比攻
	MiJiType_Revive,
	MiJiType_DeathCurse,
	MiJiType_Regeneration,
	MiJiType_LuckyMiss,
	MiJiType_KuangLu,//狂怒
	MiJiType_ZhuHun,//追魂
	MiJiType_BuQu,//不屈

	MiJiType_Max,
};

struct MiJiData
{
	int count;
	struct Skill{
		bool enable;
		int param1;
		int param2;
		int param3;
		int power;
	} miji[MAX_MIJI_LEVEL];

	Skill& GetAffectedMiJi();
};

class MiJiSystem
{
public:
	MiJiSystem(Role* role);
	~MiJiSystem();

	bool Init();
	const Attribute& GetBattleAttr() { return attribute_; }
	Attribute* GetAttr() { return &attribute_; }
	ExAttribute* GetExAttr() { return &ex_attribute_; }

	void OnDeath();
	void OnDamage();
	void ChangeMiJi(int grid, int id, bool refresh, int param1, int param2, int param3, int power);
	void Refresh();

private:
	void CalcAttribute();

private:
	MiJiData miji_list_[MiJiType_Max];
	Role* role_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
};
