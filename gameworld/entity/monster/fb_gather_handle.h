#pragma once

#include "gather_monster.h"


class FbGatherHandle:
	public GatherMonsterHandle
{
public:
	FbGatherHandle(void);
	virtual ~FbGatherHandle();
	virtual void Init(void);
	virtual bool BeginGather(Actor* actor);
	virtual void EndGather(bool succeed);
	virtual void OnChangeHp(double& value, Role* role);
	virtual bool CanMove() { return true; };
	virtual void OnWaitTimeTimeOut(void);
	virtual void ReSet(void);
	virtual void LogicRun(int64_t curr_t);
};
