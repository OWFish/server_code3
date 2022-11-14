#include "StdAfx.h"
#include "actor/actor.h"
#include "actor/tianti.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_data_mgr.h"
#include "role/role.h"
#include "role/role_system.h"
#include "actorexring/actor_ex_ring_system.h"

#include "role/role_clone.h"


#include <math.h>






Tianti::Tianti(void)
{

}



bool Tianti::Init(void)
{

	return true;
}


ActorId Tianti::FindActor(Actor* actor)
{
	if (actor == nullptr)
	{
		return 0;
	}
	
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	luaScript.Call("getTiantiOpenLevel", &arg, &arg, 1);
	int open_level = arg[0];
	auto self_data = actor->GetBasicData();
	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	const std::vector<ActorBasicData*>& datas = actor_data_mgr->GetDatas();

	std::vector<unsigned int> var;
	std::vector<unsigned int> all_var;
	int curr_time = (int)time(nullptr);

	luaScript.Call("getTiantiBeginLevel", &arg, &arg, 1);
	int begin_level = arg[0];
	luaScript.Call("getTiantiBeginShowDan", &arg, &arg, 1);
	int begin_show_dan = arg[0];
	/*
	for (size_t i = 0; i < datas.size(); ++i)
	{
		auto t = datas[i];
		if (t->actor_id == self_data->actor_id)
		{
			continue;
		}

		int level = (t->zhuansheng_lv * 1000) + t->level;
		if (level < open_level)
		{
			continue;
		}
		if (curr_time > t->tianti_week_refres )
		{
			t->tianti_level = begin_level;
			t->tianti_dan = begin_show_dan;
		}
		if (t->tianti_level == 0)
		{
			t->tianti_level = 1;
		}
		if (t->tianti_level != self_data->tianti_level)
		{
			continue;
		}
		if (t->tianti_dan != self_data->tianti_dan)
		{
			continue;
		}
		var.push_back(t->actor_id);
	}
	if (!var.empty())
	{
		return var[wrand(var.size())];
	}
	*/
	
	for (size_t i = 0; i < datas.size(); ++i)
	{
		auto t = datas[i];
		if (t->actor_id == self_data->actor_id)
		{
			continue;
		}
		int level = (t->zhuansheng_lv * 1000) + t->level;
		if (level < open_level)
		{
			continue;
		}
		all_var.push_back(t->actor_id);
		if (curr_time > t->tianti_week_refres)
		{
			t->tianti_level = begin_level;
			t->tianti_dan = begin_show_dan;
		}
		if (t->tianti_level == 0)
		{
			t->tianti_level = 1;
		}
		if (t->tianti_level != self_data->tianti_level)
		{
			continue;
		}
		var.push_back(t->actor_id);
	}

	if (!var.empty())
	{
		return var[wrand(static_cast<unsigned long>( var.size()) )];
	}
	else
	{
		if (!all_var.empty())
		{
			return all_var[wrand(static_cast<unsigned long>( all_var.size()))];
		}
		
	}
	return 0;
}

struct CreateRoldCloneArg
{

	CreateRoldCloneArg() {}
	unsigned int scene;
	ActorId actor_id;
	int x;
	int y;
	int camp;
};

void CreateRoleCloneOffLine(Actor* tar, CreateRoldCloneArg arg)
{
	if (tar == nullptr)
	{
		return;
	}
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	RoleClone* pClone_[MAX_ROLE] = { nullptr };
	EntityHandle cloneHdl[MAX_ROLE];
	Attribute	all_attrs_;
	auto role_system = tar->GetRoleSystem();
	for (int i = 0; i < MAX_ROLE; ++i )
	{
		auto role = role_system->GetRoleById(i);
		if (role)
		{
			all_attrs_ += role->GetAttrs().GetFinalAttrs();
			pClone_[i] = (RoleClone*)em->CreateEntity(EntityType_CloneRole, cloneHdl[i]);
			if (!pClone_[i])
			{

				OutputMsg(rmError, "create role clone error");
				continue;
			}
			int vx = 0, vy = 0;
			if (i != 0) {
				getDir(wrand(8), vx, vy);
			}
			pClone_[i]->LoadFromRole(role, arg.scene, arg.x + vx, arg.y + vy);
		}
	}
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		if (pClone_[i])
		{
			pClone_[i]->SetAllAttrs(all_attrs_);
			//设置同组的角色句柄
			for (int roleId = 0; roleId < MAX_ROLE; ++roleId)
			{
				pClone_[i]->SetBuddy(roleId, cloneHdl[roleId]);
			}
		}
	}
	pClone_[0]->SetCamp(arg.camp);
	auto pCjob = pClone_[0]->GetLiveByJob();
	pCjob->SetLeader();
	tar->GetActorExRingSystem()->CreateCloneExRingMonster(arg.scene, arg.x, arg.y, pCjob);
}

void Tianti::CreateCloneRole(ActorId actor_id, unsigned int scene,int x,int y, int sid, int camp)
{
	if (!sid) {
		static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
		if (!data_mgr->GetData(actor_id)) {
			return;
		}
	}

	CreateRoldCloneArg arg;
	arg.scene = scene;
	arg.actor_id = actor_id;
	arg.x = x;
	arg.y = y;
	arg.camp = camp;

	ActorAsynFunc func = std::bind(CreateRoleCloneOffLine, std::placeholders::_1, arg);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, func, sid);
}

void* Tianti::CreateRobot(RobotData* data, unsigned int scene, int x, int y)
{
	if (!data)
	{
		return NULL;
	}
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	EntityHandle hdl;
	auto *role_clone = (RoleClone*)em->CreateEntity(EntityType_CloneRole, hdl);
	if (role_clone)
	{
		role_clone->LoadFromRobot(data,scene,x,y);
	}
	return role_clone;
}
void Tianti::refreshWeek(void)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	luaScript.Call("getTiantiOpenLevel", &arg, &arg, 1);
	int open_level = arg[0];
	luaScript.Call("getTiantiBeginLevel", &arg, &arg, 1);
	int begin_level = arg[0];
	luaScript.Call("getTiantiBeginShowDan", &arg, &arg, 1);
	int begin_show_dan = arg[0];
	static auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	const std::vector<ActorBasicData*>& datas = actor_data_mgr->GetDatas();
	for (size_t i = 0;i < datas.size(); ++i)
	{
		auto t = datas[i];

		int level = (t->zhuansheng_lv * 1000) + t->level;
		if (level < open_level)
		{
			continue;
		}

		t->tianti_level = begin_level;
		t->tianti_dan = begin_show_dan;
	}


	void* actorList[8192];
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = em->GetOnlineActorPtrList(actorList, 8192);
	for (int i = 0; i < count; ++i)
	{
		Actor* actor = (Actor*)actorList[i];
		arg.clear();
		arg << actor;
		luaScript.Call("tiantiRefreshWeek", &arg, &arg, 0);
	}
}
