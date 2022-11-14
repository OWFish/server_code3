#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "knighthood_rank.h"


KnighthoodRank::KnighthoodRank(void) :
	StaticRankBasic(RankingType_Knighthood,
		std::bind(&KnighthoodRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void KnighthoodRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->knighthood_lv;
}

bool KnighthoodRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->knighthood_lv == b->knighthood_lv) {
		return a->rank_power > b->rank_power;
	}
	return a->knighthood_lv > b->knighthood_lv;
}
