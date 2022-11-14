#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class FulingSystem
{
public:
	FulingSystem(Role* role);
	~FulingSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();

	const EquipSlotData* GetEquipData(int posId);

	void SetLevelInfo(int posId, int level, int exp);

	Attribute* GetAttr(){ return &attribute_;};
	ExAttribute* GetExAttr() { return &ex_attribute_; };

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
};