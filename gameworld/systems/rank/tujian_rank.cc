#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "tujian_rank.h"


TuJianRank::TuJianRank(void) :
	StaticRankBasic(RankingType_TuJianPower,
		std::bind(&TuJianRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void TuJianRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (double)data->total_tujian_power;
}

bool TuJianRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->total_tujian_power == b->total_tujian_power) {
		return a->rank_power > b->rank_power;
	}
	return a->total_tujian_power > b->total_tujian_power;
}
