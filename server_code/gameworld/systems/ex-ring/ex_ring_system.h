#pragma once
#include "attr/attribute.h"


class Role;
struct ExRingsData;
struct RoleData;


// 特戒系统，只做属性保存，逻辑在lua
class ExRingSystem
{
public:
	ExRingSystem(Role* role);
	~ExRingSystem();
	
	bool Init(RoleData* data);
	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	Attribute* GetAttr() { return &attribute_; }
	ExAttribute* GetExAttr() { return &ex_attr_; }
	int GetLevel(int id);
	void SetLevel(int id, int level);
	void Save(RoleData* data){};

private:
	Role*		role_;
	ExRingsData *data_;
	Attribute	attribute_;
	ExAttribute ex_attr_;
};