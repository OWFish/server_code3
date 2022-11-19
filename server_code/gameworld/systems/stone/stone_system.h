#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class StoneSystem
{
public:
	StoneSystem(Role* role);
	~StoneSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);

	std::vector<int> GetStoneData();

	//设置等级
	void SetLevel(int posId, int level);
	//获取总等级
	int GetTotalLv();

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
};