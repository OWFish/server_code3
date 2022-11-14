#pragma once
#include "attr/attribute.h"


struct EquipsData;
struct RoleData;
class Role;
class ZhulingSystem
{
public:
	ZhulingSystem(Role* role);
	~ZhulingSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	void ClearAttr();
	void AddAttr(int type, int value);

	std::vector<int> GetZhulingData();
	const EquipsData* GetEquipsData(){ return equip_data_; }

	//…Ë÷√µ»º∂
	void SetLevel(int posId, int level);

private:
	void CalcAttribute(bool notify);

private:
	Role*	role_;
	EquipsData* equip_data_;
	Attribute attribute_;
};