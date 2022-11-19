#pragma once
#include "attr/attribute.h"

struct RoleData;
class Role;
struct NeiGongData;
class NeigongSystem
{
public:
	NeigongSystem(Creature* self);
	~NeigongSystem();

	bool Init(RoleData* data);
	void Save(RoleData* data);
	void LogicRun(int64_t curr_t);

	void Destroy();
	Attribute* GetNeigongAttr();
	void ClearAttr();
	void AddAttr(int type, int value);

private:
	void CalcAttribute(bool notify);

private:
	Creature*	self_;
	Attribute attribute_;
	int64_t last_time;
};