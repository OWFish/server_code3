#pragma once
#include "attr/attribute.h"

class Role;
class Item;
class Equip;
class FuWenSystem
{
public:
	FuWenSystem(Role* role);
	~FuWenSystem();

	const static int MAX_FUWEN_POS = 8;
	

	void Destroy();

	bool Init(RoleData* data);

	void Save();

	const Attribute& GetBattleAttr() { return attribute_; }
	void AddAttr(int type, int value);
	void AddExAttr(int type, int value);
	void ClearAttr();


	Attribute* GetAttr() { return &attribute_; }
	ExAttribute& GetExAttr() { return ex_attribute_; }

	void SetEquipFuwen(int posid, int64_t uid);
	void FuwenLevelup(int posid, int itemId);
	const FuWenData* GetFuWenData();
	Item* GetFuWenItemByPos(int posid) const;
private:
	Role*	role_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
	FuWenData* fuwendata_;
	Item* fuwen_[MAX_FUWEN];
	
};

