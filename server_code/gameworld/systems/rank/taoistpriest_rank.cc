#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "taoistpriest_rank.h"


TaoistpriestRank::TaoistpriestRank(void) :
	StaticRankBasic(RankingType_Taoistpriest,
		std::bind(&TaoistpriestRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void TaoistpriestRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (double)data->taoistpriest_power;
}

bool TaoistpriestRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	return a->taoistpriest_power > b->taoistpriest_power;
}
