#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class BlessSystem
{
public:
	BlessSystem(Role* role);
	~BlessSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	Attribute* GetAttr() { return &attribute_; }

	std::vector<int> GetBlessData();

	//…Ë÷√µ»º∂
	void SetLevel(int posId, int level);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
};