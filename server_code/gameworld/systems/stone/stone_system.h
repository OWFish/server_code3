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

	//…Ë÷√µ»º∂
	void SetLevel(int posId, int level);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
};