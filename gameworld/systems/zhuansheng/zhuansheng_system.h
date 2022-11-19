#pragma once
#include "attr/attribute.h"


class Actor;
class ZhuanShengSystem
{
public:
	ZhuanShengSystem(Actor* actor);
	~ZhuanShengSystem();

	bool Init();

	void Destroy();
	const Attribute& GetBattleAttr() { return attribute_; }
	Attribute* GetAttr() { return &attribute_; }
	void Save(){};

private:
	Actor*		actor_;
	Attribute	attribute_;
};