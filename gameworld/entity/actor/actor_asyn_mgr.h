#pragma once
#include "actor.h"
#include <vector>
#include <functional>


typedef std::function<void(Actor*)> ActorAsynFunc;
typedef std::function<void(void)> TimeOutAsynFunc;

class ActorAsynMgr
{
	struct AsynEv
	{
		ActorId id;
		ActorAsynFunc cb_func;
		TimeOutAsynFunc time_func;
		int end_time;
	};
	struct AsynAL {
		ActorId id;
		int sId;
	};
public:
	ActorAsynMgr();
	~ActorAsynMgr();

	void Destroy();
	void RunOne(int64_t now_t);
	void GameStar();
	void RegActorEv(ActorId tarId, ActorAsynFunc func, int sId = 0, TimeOutAsynFunc time_func = NULL);
	void RegActorScriptEv(ActorId tarId);
	void TriggerAsynEv(Actor* actor);
private:
	void OnTrigger(AsynEv& ev, Actor* actor);
	void RegAsynEv(ActorId tarId, ActorAsynFunc func, int sId = 0, TimeOutAsynFunc time_func = NULL);

private:
	std::vector<AsynEv>  aev_list;
	std::vector<AsynAL>  actor_list;
	Timer logic_timer_;
};
