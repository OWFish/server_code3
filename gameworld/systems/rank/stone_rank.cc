#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "stone_rank.h"


StoneRank::StoneRank(void) :
	StaticRankBasic(RankingType_Stone,
		std::bind(&StoneRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{
	
}

void StoneRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->total_stone_level;
}

bool StoneRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->total_stone_level == b->total_stone_level) {
		return a->rank_power > b->rank_power;
	}
	return a->total_stone_level > b->total_stone_level;
}
