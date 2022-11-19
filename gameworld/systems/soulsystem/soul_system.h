#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class SoulSystem
{
public:
	SoulSystem(Role* role);
	~SoulSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();

	const EquipSlotData* GetEquipData(int posId);

	//…Ë÷√µ»º∂
	void SetLevel(int posId, int level);

	Attribute* GetAttr() { return &attribute_; };
	ExAttribute* GetExAttr() { return &ex_attribute_; };

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
};