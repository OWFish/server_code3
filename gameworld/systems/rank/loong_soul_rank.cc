#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "loong_soul_rank.h"


LoongSoulRank::LoongSoulRank(void) :
	StaticRankBasic(RankingType_LoongSoul,
		std::bind(&LoongSoulRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void LoongSoulRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->total_loongsoul_level;
}

bool LoongSoulRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->total_loongsoul_level == b->total_loongsoul_level) {
		return a->rank_power > b->rank_power;
	}
	return a->total_loongsoul_level > b->total_loongsoul_level;
}
