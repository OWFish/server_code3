#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "prestige/prestige_helper.h"

#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "prestige_rank.h"


PrestigeRank::PrestigeRank(void) :
	StaticRankBasic(RankingType_Prestige,
		std::bind(&PrestigeRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{
	
}

void PrestigeRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->prestige_exp;
}

bool PrestigeRank::Screening(const ActorBasicData* data)
{
	if (data->level < RANK_MIN_LEVEL) return true;
	
	if (data->prestige_exp < PrestigeHelper::getRankLimitexp()) return true;

	return false;
}

bool PrestigeRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->prestige_exp == b->prestige_exp) {
		return a->rank_power > b->rank_power;
	}
	return a->prestige_exp > b->prestige_exp;
}
