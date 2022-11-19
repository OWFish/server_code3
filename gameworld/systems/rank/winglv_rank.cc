#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "winglv_rank.h"


WingLvRank::WingLvRank(void) :
	StaticRankBasic(RankingType_WingLv,
		std::bind(&WingLvRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void WingLvRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << data->total_wing_lv;
}

bool WingLvRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->total_wing_lv == b->total_wing_lv) {
		return a->rank_power > b->rank_power;
	}
	return a->total_wing_lv > b->total_wing_lv;
}
