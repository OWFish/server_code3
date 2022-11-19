#include "StdAfx.h"
#include "prestige_helper.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_data_mgr.h"
#include "db/actor_db_data.h"

std::map<uint64_t, ActorId, std::less<uint64_t>> PrestigeHelper::_time_list;
int PrestigeHelper::rankLimitexp_ = 0;
int PrestigeHelper::normalDeterDam_ = 0;
int PrestigeHelper::rankDeterDam_[RANK_SIZE] = {0};

void ChangePrestigeExp(Actor* tar)
{
	if (!tar) return;
	ScriptValueList arg;
	arg << tar;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("OnChangePrestigeExp", &arg, &arg, 0);
}

PrestigeHelper::PrestigeHelper()
{
	_time_list.clear();
}

PrestigeHelper::~PrestigeHelper()
{

}

void PrestigeHelper::ChangePrestigeExpData(int tactorId)
{
	ActorAsynFunc func = std::bind(ChangePrestigeExp, std::placeholders::_1);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(tactorId, func);
}

void PrestigeHelper::LogicRun(int64_t curr_t)
{
	for (auto it = _time_list.begin(); it != _time_list.end();)
	{
		if (it->first < (uint64_t)curr_t) {
			ChangePrestigeExpData(it->second);
			it = _time_list.erase(it);
		}
		else
		{
			break;
		}
	}
}

bool PrestigeHelper::LoadPrestigeConfig(GameConfigData* data)
{
	if (!data->openGlobalTable("PrestigeBase"))
	{
		OutputMsg(rmError, ("can't open PrestigeBase table"));
		return false;
	}

	int ndef = 0;
	rankLimitexp_ = data->getFieldInt("rankLimitExp", &ndef);
	normalDeterDam_ = data->getFieldInt("normalDeterDam", &ndef);

	int index = 0;
	if (data->fieldTableExists("rankDeterDam") && data->openFieldTable("rankDeterDam"))
	{
		if (data->enumTableFirst())
		{
			do
			{
				rankDeterDam_[index] = data->getFieldInt(NULL);
				index++;
				if (index > RANK_SIZE - 1) break;
			} while (data->enumTableNext());
		}
	}

	data->closeTable();

	return true;
}

void PrestigeHelper::setChangeExpTimeInfo()
{
	_time_list.clear();

	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	auto &data_vec_ = actor_data_mgr->GetDatas();

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int64_t now_t = GetGameEngine()->getTickCount();
	int index = 0;
	for (auto it = data_vec_.begin(); it != data_vec_.end(); it++)
	{
		if ((*it)->prestige_exp > 0){
			int id = (*it)->actor_id;
			Actor* actor = em->GetActorPtrById(id);
			if (actor && actor->IsInited()){
				ChangePrestigeExp(actor);
			} else{
				_time_list[now_t + (index % 400)*1000] = id;
				index++;
			}
		}
	}
}

int PrestigeHelper::getDeterDam(int rank)
{
	if (rank < 0 || rank > RANK_SIZE - 1) return normalDeterDam_;

	return rankDeterDam_[rank];
}

