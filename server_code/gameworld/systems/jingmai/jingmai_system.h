#pragma once
#include "attr/attribute.h"


struct RoleData;
class Role;
struct JingMaiData;
class JingmaiSystem
{
public:
	JingmaiSystem(Role* role);
	~JingmaiSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);
	const JingMaiData* GetJingmaiData();

	//设置等级
	void SetLevel(int level);
	//设置经验
	void SetStage(int stage);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	JingMaiData* jingmai_data_;
	Attribute attribute_;
};