#pragma once
#include "entity/entity.h"
#include "entity/creature.h"


class Actor;
class GatherMonster;

enum GatherMonsterType
{
	FLAGS = 0,
	FBGATHER = 1,
	GATHER_MONSTER_TYPE_MAX
};

//
class GatherMonsterHandle
{
public:
	GatherMonsterHandle(void) {}
	virtual ~GatherMonsterHandle() {}
public:
	virtual void Init(void) {}
	virtual bool BeginGather(Actor* actor) { return false; }
	virtual void EndGather(bool succeed) {}
	virtual void OnChangeHp(double& value,Role* role) {}
	virtual bool CanMove() { return false; };
	virtual void OnWaitTimeTimeOut(void) {} //等待采集时间超时
	virtual void ReSet(void) {}
	virtual void LogicRun(int64_t curr_t) {}
	void SetGatherMonster(GatherMonster* p) { gather_monster_ = p; }
	GatherMonster* GetGatherMonster(void) { return gather_monster_; }



private:
	GatherMonster* gather_monster_ = nullptr;
};

class GatherMonster:
	public Creature
{
public:
	GatherMonster(void);
	virtual ~GatherMonster();
public:
	virtual void CreateAppearData(DataPacket& appearPack);
	virtual void BeginGather(Actor* actor);
	virtual void EndGather(bool succeed);
	virtual void OnChangeHp(double& value,Role* role);
	virtual void OnAddStatus(int status);
	virtual bool CanMove();
	virtual int GetId(void);
	bool Init(int id);
	virtual bool IsDeath(void) { return false; }
	Actor* GetGatherActor(void) { return gather_actor_; }
	virtual void ClearGatherActor();
	virtual void LogicRun(int64_t curr_t);
	MonsterConfig* GetConfig(void) { return conf_; }
	GatherMonsterType GetGatherMonsterType(void);
	int64_t GetWaitGatherTime(void) {return wait_gather_time_;}
	int64_t GetGatherTime(void) { return gather_time_;}
	virtual void ReSet(void);
public:
	virtual void InitBasicAttribute() {}
	virtual void CalcAttributes() {}	
	virtual void CalcBattleAttributes() {} 
private:
	GatherMonsterHandle* CreateHadnle(GatherMonsterType type);
private:
	int id_ = 0;
	Actor* gather_actor_                        = nullptr;
	GatherMonsterHandle* gather_monster_handle_ = nullptr;
	MonsterConfig* conf_                        = nullptr;
	int64_t gather_time_                        = 0; //采集时间(豪秒)
	int64_t wait_gather_time_                   = 0; //等待采集时间(豪秒)
	bool is_call_time_out_                       = false; //是否调用了gather_time_time_out
	
};
