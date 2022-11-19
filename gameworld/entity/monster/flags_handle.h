#pragma once

#include "gather_monster.h"


class FlagsHandle:
	public GatherMonsterHandle
{
public:
	FlagsHandle(void);
	virtual ~FlagsHandle();
	virtual void Init(void);
	virtual bool BeginGather(Actor* actor);
	virtual void EndGather(bool succeed);
	virtual void OnChangeHp(double& value,Role* role);
	virtual bool CanMove() { return false; };
	virtual void OnWaitTimeTimeOut(void);
	virtual void ReSet(void);
	virtual void LogicRun(int64_t curr_t);
public:
	int shield = 0; //»¤¶Ühp
	bool failure_ = false;
	int64_t failure_wait_tick_ = 0;
};
