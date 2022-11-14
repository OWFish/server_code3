#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "power_rank.h"


PowerRank::PowerRank(void):
	StaticRankBasic(RankingType_Power,
		std::bind(&PowerRank::Compare,this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void PowerRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (double)data->total_power;
}

bool PowerRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	return a->total_power > b->total_power;
}
