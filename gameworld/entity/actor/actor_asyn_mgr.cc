#include "StdAfx.h"
#include "actor_asyn_mgr.h"


ActorAsynMgr::ActorAsynMgr()
	:logic_timer_(1000)
{
	actor_list.clear();
}

ActorAsynMgr::~ActorAsynMgr()
{
}

void ActorAsynMgr::Destroy()
{
	//for (auto ev : aev_list)
	//	SafeDelete(ev.param);
}

void ActorAsynMgr::RunOne(int64_t now_t)
{
	if (!logic_timer_.CheckAndSet(now_t))
		return;

	if (!GetGameEngine()->isInitComponentFinished())
	{
		return;
	}

	int current_time = GetGameEngine()->getMiniDateTime();
	for (auto ev : aev_list)
	{
		if (ev.end_time < current_time)
		{
			OutputMsg(rmError, "actor asyn event is timeout...actor:%d", ev.id);
		}
	}

	int size = static_cast<int>(aev_list.size());
	static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();
	for (int i = size - 1; i >= 0; --i)
	{
		auto &ev = aev_list[i];
		if (ev.end_time < current_time)
		{
			OutputMsg(rmError, "actor asyn event is timeout...actor:%d", ev.id);
			//SafeDelete(ev.param);
			if (ev.time_func) {
				ev.time_func();
			}
			//触发脚本清空事件注册
			ScriptValueList paramList;
			paramList << ev.id;
			pNpc->GetScript().Call("onAsynEventTimeOut", &paramList, &paramList);

			aev_list[i] = aev_list[aev_list.size() - 1];
			aev_list.pop_back();
		}
	}
}

void ActorAsynMgr::RegAsynEv(ActorId tar_id, ActorAsynFunc func, int sId, TimeOutAsynFunc time_func)
{
	if (func == NULL) return;

	static GameServer* srv = ServerInstance();
	//除了普通服外，其他服不能使用镜像
	if (sId == 0) {
		if (!srv->IsCommonSrv()) return;
		sId = srv->GetServerIndex();
	}

	AsynEv ev;
	ev.id = tar_id;
	ev.cb_func = func;
	ev.time_func = time_func;
	ev.end_time = SecondTime::now() + 6000; // 10秒应该很长了, //还不够 // 60也不够, 改6000了
	aev_list.push_back(ev);

	if (!GetGameEngine()->isInitComponentFinished())
	{
		AsynAL al;
		al.id = tar_id;
		al.sId = sId;
		actor_list.push_back(al);
	}
	else
	{
		// 创建镜像玩家
		GameInterMsg msg;
		msg.msg_id_ = SSM_CREATE_ACTOR_IMAGE;
		msg.data_.actor_id = tar_id;
		msg.data_.sId_ = sId;

		static GameEngine* ge = GetGameEngine();
		ge->PostMsg(msg);
	}
}

void ActorAsynMgr::GameStar()
{
	std::vector<AsynAL>::iterator it;
	static GameEngine* ge = GetGameEngine();
	for (it = actor_list.begin(); it != actor_list.end(); it++) {
		GameInterMsg msg;
		msg.msg_id_ = SSM_CREATE_ACTOR_IMAGE;
		msg.data_.actor_id = it->id;
		msg.data_.sId_ = it->sId;

		ge->PostMsg(msg);
	}
	actor_list.clear();
}
void ActorAsynMgr::RegActorEv(ActorId tarId, ActorAsynFunc func, int sId, TimeOutAsynFunc time_func)
{
	Actor *tar = GetGameEngine()->GetEntityMgr()->GetActorPtrById(tarId);
	if (tar && tar->IsInited())
	{
		func(tar);
		//SafeDelete(param);
		// 延长缓存时间
		//if (tar->IsImage())
		//	tar->SetImageEndTime(GetGameEngine()->getMiniDateTime() + IMAGE_ACTOR_CACHE_TIME);
	}
	else
		RegAsynEv(tarId, func, sId, time_func);
}

inline void CallScriptEv(Actor* actor)
{
	// 触发脚本
	ScriptValueList paramList;
	paramList << actor;

	static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();
	pNpc->GetScript().Call("onAsynEvent", &paramList, &paramList);
}

void ActorAsynMgr::RegActorScriptEv(ActorId tarId)
{
	Actor *tar = GetGameEngine()->GetEntityMgr()->GetActorPtrById(tarId);
	if (tar && tar->IsInited())
		CallScriptEv(tar);
	else
		RegAsynEv(tarId, CallScriptEv);
}

void ActorAsynMgr::TriggerAsynEv(Actor* actor)
{
	ActorId aid = actor->GetActorId();
	int size = static_cast<int>(aev_list.size());
	for (int i = size - 1; i >= 0; --i)
	{
		auto &ev = aev_list[i];
		if (ev.id == aid)
		{
			OnTrigger(ev, actor);
			//SafeDelete(ev.param);
			aev_list[i] = aev_list[aev_list.size() - 1];
			aev_list.pop_back();
		}
	}
}

void ActorAsynMgr::OnTrigger(AsynEv& ev, Actor* actor)
{
	ev.cb_func(actor);
	CallScriptEv(actor);
}

