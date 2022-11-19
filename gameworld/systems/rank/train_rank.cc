#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "train_rank.h"


TrainRank::TrainRank(void) :
	StaticRankBasic(RankingType_Train,
		std::bind(&TrainRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void TrainRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->train_level;
	cache << (int)data->train_exp;
}

bool TrainRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->train_level != b->train_level)
	{
		return a->train_level > b->train_level;
	}
	return a->train_exp > b->train_exp;
}
