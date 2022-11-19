#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"


#include "static_ranking_mgr.h"

StaticRankingMgr::StaticRankingMgr()
	: logic_timer_(1000)
	, next_save_time_(0)
{
	/*
	static BaseAllocator s_base_alloc("rank_packet");
	power_rank_pack_cache_.setAllocator(&s_base_alloc);
	*/
}

StaticRankingMgr::~StaticRankingMgr()
{
	Destroy();
}

void StaticRankingMgr::Destroy()
{
	{
		auto it = rank_map_.begin();
		auto end = rank_map_.end();
		for (; it != end; ++it)
		{
			SafeDelete(it->second);
		}
		rank_map_.clear();
	}


	{
		auto it = dynamic_first_cache_.begin();
		auto end = dynamic_first_cache_.end();
		for (; it != end; ++it)
		{
			SafeDelete(it->second);
		}
		dynamic_first_cache_.clear();
	}
}

bool StaticRankingMgr::Load()
{
	/*
	next_save_time_ = GetGameEngine()->getMiniDateTime();
	next_save_time_ = next_save_time_ / 1800 * 1800 + 1800;

	static BaseAllocator basic_alloc("dynamic ranking first cache ");
	for (size_t i = 0;i < RankingType_Count; ++i)
	{
		if (rank_map_.find((RankingType)i) != rank_map_.end())
		{
			continue;
		}
		dynamic_first_cache_[(RankingType)i] = new DataPacket();
		auto& cache = *dynamic_first_cache_[(RankingType)i];
		cache.setAllocator(&basic_alloc);
		cache << (int)0;
	}
	UpdateRank();

	return true;
	*/
	return false;
}

void StaticRankingMgr::RunOne(int64_t now_t)
{
	/*
	if (!logic_timer_.CheckAndSet(now_t))
		return;

	int second_time = GetGameEngine()->getMiniDateTime();
	if (second_time > next_save_time_)
	{
		next_save_time_ = second_time + 1800;

		UpdateRank();
	}
	*/
	
}

// 回调函数
void getMorshipData(Actor* tar)
{
	/*
	static BaseAllocator baseAlloc("morshipCachePacket");
	static DataPacket cache_packet(&baseAlloc);
	cache_packet.setLength(0);
	auto data = tar->GetBasicData();
	cache_packet << (int)data->actor_id;
	cache_packet << data->actor_name;
	cache_packet << (int)data->total_power;
	cache_packet << (short)data->level;
	cache_packet << (short)data->zhuansheng_lv;
	cache_packet << (short)data->vip_level;
	cache_packet << (short)(tar->GetRoleSystem()->GetRoleCount());
	Role* roles[MAX_ROLE];
	tar->GetRoleSystem()->GetRoles(roles);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = roles[i];
		if (role)
		{
			cache_packet << (uint8_t)role->GetJob();
			cache_packet << (uint8_t)role->GetSex();
			cache_packet << role->GetEquipSystem()->GetEquipId(EquipSlotType_Coat);
			cache_packet << role->GetEquipSystem()->GetEquipId(EquipSlotType_Weapon);
			cache_packet << role->GetWingSystem()->GetWingData()->level;
			cache_packet << role->GetWingSystem()->GetWingData()->openStatus;
		}
	}
	ScriptValueList arg;
	arg << &cache_packet;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("updateMorshipData", &arg, NULL, 0);

	*/
}

// 更新膜拜数据
inline void UpdateMorshipData(int actorId)
{
	//GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorId, getMorshipData);
	//getMorshipData(nullptr, nullptr, nullptr);
}

void StaticRankingMgr::UpdateRank()
{
	/*
	if (!ServerInstance()->IsCommonSrv()) return;
	auto it = rank_map_.begin();
	auto end = rank_map_.end();

	for (; it != end; ++it)
	{
		it->second->UpdataRank();
	}
	*/
	
	/*
	power_rank_.UpdataRank();
	level_rank_.UpdataRank();
	wing_rank_.UpdataRank();
	warrior_rank_.UpdataRank();
	mage_rank_.UpdataRank();
	taoistpriest_rank_.UpdataRank();
	train_rank_.UpdataRank();
	*/
	/*
	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	std::vector<ActorBasicData*> datas = actor_data_mgr->GetDatas();
	power_rank_.clear();
	for (int i = 0; i < datas.size(); ++i)
	{
		if (datas[i]->level < 10) continue;
		RankingData data;
		data.actor_id = datas[i]->actor_id;
		data.ranking_value = datas[i]->total_power;
		power_rank_.push_back(data);
	}

	std::sort(power_rank_.begin(), power_rank_.end(), [](const RankingData& a, const RankingData& b) {return a.ranking_value > b.ranking_value; });
	
	power_rank_index_.clear();
	for (int i = 0; i < power_rank_.size(); ++i)
	{
		power_rank_index_[power_rank_[i].actor_id] = i;
	}

	int rank_size = power_rank_.size();
	if (rank_size > 100) rank_size = 100;
	power_rank_pack_cache_.setLength(0);

	power_rank_pack_cache_ << (uint8_t)Protocol::CMD_Ranking;
	power_rank_pack_cache_ << (uint8_t)Protocol::sRankingCmd_ResRankingData;
	power_rank_pack_cache_ << (short)RankingType_Power;
	power_rank_pack_cache_ << (short)rank_size;
	for (int i = 0; i < rank_size; ++i)
	{
		static const ActorDataMgr* actor_data_mgr = GetGameEngine()->GetActorDataMgr();
		const ActorBasicData* actor_data = actor_data_mgr->GetData(power_rank_[i].actor_id);
		if (actor_data == NULL) {
			OutputMsg(rmError, "GetRankActor failed. aid:%d", power_rank_[i].actor_id);
			power_rank_pack_cache_ << (short)(i);
			power_rank_pack_cache_ << (int)0;
			power_rank_pack_cache_ << "";
			power_rank_pack_cache_ << (short)0;
			power_rank_pack_cache_ << (short)0;
			power_rank_pack_cache_ << (short)0;
			power_rank_pack_cache_ << (int)0;
			power_rank_pack_cache_ << (short)0;
			continue;
		}
		power_rank_pack_cache_ << (short)(i+1);
		power_rank_pack_cache_ << actor_data->actor_id;
		power_rank_pack_cache_ << actor_data->actor_name;
		power_rank_pack_cache_ << (short)actor_data->level;
		power_rank_pack_cache_ << (short)actor_data->zhuansheng_lv;
		power_rank_pack_cache_ << (short)actor_data->vip_level;
		power_rank_pack_cache_ << actor_data->total_power;
		power_rank_pack_cache_ << (short)actor_data->monthcard;
	}

	if (rank_size > 0)
		UpdateMorshipData(power_rank_[0].actor_id);

		*/

}


void StaticRankingMgr::SendRankingDataByType(Actor* actor, RankingType type)
{
	/*
	if (!actor)
	{
		return;
	}
	auto it = rank_map_.find(type);
	if (it != rank_map_.end())
	{
		it->second->SendData(actor);
	}
	*/
	
}

DataPacket* StaticRankingMgr::GetFirstCacheByType(RankingType type)
{
	/*
	{
		auto it = rank_map_.find(type);
		if (it != rank_map_.end())
		{
			//DataPacket* cache = it->second->GetFirstCache();

			return it->second->GetFirstCache();
		}
	}
	{
		auto it = dynamic_first_cache_.find(type);
		if (it != dynamic_first_cache_.end())
		{
			return it->second;
		}
	}
	return nullptr;
	*/
	return nullptr;
}

void StaticRankingMgr::AsyncUpdateDynamicFirstCache(Actor* actor, RankingType type)
{
	/*
	if (dynamic_first_cache_.find(type) == dynamic_first_cache_.end())
	{
		return;
	}
	auto& cache = *dynamic_first_cache_[type];
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
	*/
	
}


void StaticRankingMgr::UpdateDynamicFirstCache(int actor_id, RankingType type)
{
	/*
	if (dynamic_first_cache_.find((RankingType)type) == dynamic_first_cache_.end())
	{
		return;
	}
	*/
	
	//GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, std::bind(
	//	&StaticRankingMgr::AsyncUpdateDynamicFirstCache, this, std::placeholders::_1,
	//	type
	//));
}

StaticRankBasic* StaticRankingMgr::GetRanking(RankingType type)
{
	/*
	auto it = rank_map_.find(type);
	if (it != rank_map_.end())
	{
		return it->second;
	}
	return nullptr;
	*/
	return nullptr;
}