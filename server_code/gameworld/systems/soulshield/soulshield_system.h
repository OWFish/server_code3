#pragma once
#include "attr/attribute.h"


struct RoleData;
class Role;
class SoulshieldSystem
{
public:
	SoulshieldSystem(Role* role);
	~SoulshieldSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);

	//设置等级
	void SetLevel(int type, int level);
	void SetStage(int type, int stage);
	void SetExp(int type, int exp);
	void SetAct(int type, int act);

	//获取龙魂血玉信息
	const LoogsoulData* GetsoulData();
	//const ShieldData* GetshielData();
	//const XueyuData* GetxueyuData();
	//int GetLevel(int type);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	LoogsoulData* loogsoulData_;
	//ShieldData* shielData_;
	//XueyuData* xueyuData_;
	//int* loongsoul_level;
	//int* shield_level;
	//int* xueyu_level;
	Attribute attribute_;
};