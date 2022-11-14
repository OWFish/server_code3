#include "StdAfx.h"
#include "actor/actor_data_mgr.h"

#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"
#include "zhuangban/zhuangban.h"

#include "static_rank_basic.h"


StaticRankBasic::StaticRankBasic(RankingType type, compare_t compare) :
	compare_(compare),
	type_(type),
	basic_alloc_("StaticRankBasic")
{
	rank_cache_.setAllocator(&basic_alloc_);
	first_cache_.setAllocator(&basic_alloc_);
	cache_.setAllocator(&basic_alloc_);
}

StaticRankBasic::~StaticRankBasic(void)
{

}

void StaticRankBasic::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	if (!data)
	{
		return;
	}
	cache << (int)data->actor_id;
	cache << data->actor_name;
	cache << (short)data->level;
	cache << (short)data->zhuansheng_lv;
	cache << (short)data->vip_level;
	cache << (short)data->monthcard;
	cache << data->guild_name_;
}

void StaticRankBasic::UpdataRank(void)
{
	ScriptValueList arg;
	arg << (int)type_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("sRankUpdateBefore", &arg, &arg, 0);

	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	rank_data_.clear();

	auto &data_vec_ = actor_data_mgr->GetDatas();
	rank_data_.assign(data_vec_.begin(), data_vec_.end());
	std::sort(rank_data_.begin(), rank_data_.end(), compare_);

	{
		auto it = rank_data_.begin();
		for (;it != rank_data_.end();)
		{
			if (Screening(*it))
			{
				it = rank_data_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	rank_index_actor_id_.clear();
	for (size_t i = 0;i < rank_data_.size(); ++i)
	{
		auto data = rank_data_[i];
		rank_index_actor_id_[data->actor_id] = i;
	}
	size_t rank_size = 0;
	if (rank_data_.size() > send_size_)
	{
		rank_size = send_size_;
	}
	else
	{
		rank_size = rank_data_.size();
	}
	rank_cache_.setLength(0);
	rank_cache_ << (uint8_t)Protocol::CMD_Ranking;
	rank_cache_ << (uint8_t)Protocol::sRankingCmd_ResRankingData;
	rank_cache_ << (short)type_;
	rank_cache_ << (short)rank_size;
	for (size_t i = 0;i < rank_data_.size() && i < send_size_; ++i)
	{
		auto data = rank_data_[i];
		rank_cache_ << (short)(i + 1);
		UpdateRankCache(rank_cache_, data);
	}
	//first_cache_.setLength(0);
	if (rank_data_.empty())
	{
		first_cache_.setLength(0);
		first_cache_ << (int)0;
	}
	else
	{
		
		//GetGameEngine()->GetActorAsynMgr()->RegActorEv(rank_data_[0]->actor_id, std::bind(
		//	&StaticRankBasic::AsyncUpdateFirstCache,this, std::placeholders::_1));

	}

	arg.clear();
	arg << (int)type_;
	luaScript.Call("staticRankUpdate", &arg, &arg, 0);
}

void StaticRankBasic::SendData(Actor* actor)
{
	if (!actor)
	{
		return;
	}
	auto old_len = rank_cache_.getLength();
	rank_cache_ << GetActorRanking(actor) + 1;

	actor->SendData(rank_cache_);
	rank_cache_.setLength(old_len);


}

int StaticRankBasic::GetActorRanking(Actor* actor)
{
	if (!actor)
	{
		return 0;
	}
	int ret = -1;
	auto it = rank_index_actor_id_.find(actor->GetActorId());
	if (it != rank_index_actor_id_.end())
	{
		ret = (int)(it->second);
	}
	return ret;
}

int StaticRankBasic::GetIndexFromId(int id)
{
	auto it = rank_index_actor_id_.find(id);
	if (it != rank_index_actor_id_.end())
	{
		return (int)(it->second);
	}
	return -1;
}


int StaticRankBasic::GetActorIdByRanking(size_t i)
{
	int ret = 0;

	if (!rank_data_.empty() && i < rank_data_.size())
	{
		return rank_data_[i]->actor_id;
	}
	return ret;
}

void StaticRankBasic::AsyncUpdateFirstCache(Actor* actor)
{
	UpdataFirstCache(actor, first_cache_);
}


void StaticRankBasic::UpdataFirstCache(Actor* actor, DataPacket& cache)
{
	if (!actor)
	{
		return;
	}
	cache.setLength(0);
	auto data = actor->GetBasicData();
	cache << (int)data->actor_id;
	cache << data->actor_name;
	cache << (double)data->total_power;
	cache << (short)data->level;
	cache << (short)data->zhuansheng_lv;
	cache << (short)data->vip_level;
	cache << (short)(actor->GetRoleSystem()->GetRoleCount());
	Role* roles[MAX_ROLE];
	actor->GetRoleSystem()->GetRoles(roles);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = roles[i];
		if (role)
		{
			cache << (uint8_t)role->GetJob();
			cache << (uint8_t)role->GetSex();
			cache << role->GetEquipSystem()->GetEquipId(EquipSlotType_Coat);
			cache << role->GetEquipSystem()->GetEquipId(EquipSlotType_Weapon);
			cache << role->GetWingSystem()->GetWingData()->level;
			cache << role->GetWingSystem()->GetWingData()->openStatus;
			ZhuangBanData * p = role->GetZhuangBanSystem()->GetZhuangBanData();
			cache << (int)p->pos1id;
			cache << (int)p->pos2id;
			cache << (int)p->pos3id;
		}
	}
}


DataPacket* StaticRankBasic::GetRankCache(size_t min, size_t max)
{
	if (min > max)
	{
		return nullptr;
	}
	cache_.setLength(0);
	if ((max - min) > (rank_data_.size() - min))
	{
		cache_ << (short)(rank_data_.size() - min);
	}
	else
	{
		cache_ << (short)(max - min);
	}
	if (min >= rank_data_.size())
	{
		cache_.setLength(0);
		cache_ << (short)0;
	}
	for (size_t i = min; i < rank_data_.size() && i < max; ++i)
	{
		auto data = rank_data_[i];
		cache_ << (short)(i + 1);
		UpdateRankCache(cache_, data);
	}
	return &cache_;
}
