#pragma once
#include "attr/attribute.h"
#include "attr/ex_attr.h"

// �ؼ�
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
	MiJiType_Penetrate,	// ��͸ ����%n����
	MiJiType_Reflect,
	MiJiType_Pierce,   // ���� ���ӷ���, �Ӱٷֱȹ�
	MiJiType_Revive,
	MiJiType_DeathCurse,
	MiJiType_Regeneration,
	MiJiType_LuckyMiss,
	MiJiType_KuangLu,//��ŭ
	MiJiType_ZhuHun,//׷��
	MiJiType_BuQu,//����

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
