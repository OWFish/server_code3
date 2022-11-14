#pragma once
#include "attr/attribute.h"

#include "role/role_system.h"

class TitleSystem
{
public:
	TitleSystem(Actor* actor);
	~TitleSystem();

	bool Init();
	void Save();

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	Attribute* GetAttr() { return &attribute_; }

	void OnTimeCheck(int64_t curr_t);
	void setRoleTitle(int roleId, int tId);
	int getRoleTitle(int roleId);

//private:
//	void CalcAttribute();

private:
	Actor*	actor_;
	Attribute attribute_;
	int roleTitle[MAX_ROLE];
};