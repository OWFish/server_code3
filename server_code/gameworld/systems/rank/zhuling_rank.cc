#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "zhuling/zhuling_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "zhuling_rank.h"


ZhulingRank::ZhulingRank(void) :
	StaticRankBasic(RankingType_Zhuling,
		std::bind(&ZhulingRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{
	
}

void ZhulingRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->total_zhuling_level;
}

bool ZhulingRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->total_zhuling_level == b->total_zhuling_level) {
		return a->rank_power > b->rank_power;
	}
	return a->total_zhuling_level > b->total_zhuling_level;
}
