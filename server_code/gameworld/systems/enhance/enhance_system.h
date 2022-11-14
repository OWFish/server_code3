#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class EnhanceSystem
{
public:
	EnhanceSystem(Role* role);
	~EnhanceSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);

	const EquipsData* GetEquipsData(){ return Equip_Data_; }

	//…Ë÷√µ»º∂
	void SetLevel(int posId, int level);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	EquipsData* Equip_Data_;
	Attribute attribute_;
};