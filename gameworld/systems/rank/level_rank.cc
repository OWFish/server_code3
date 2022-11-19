#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "level_rank.h"


LevelRank::LevelRank(void) :
	StaticRankBasic(RankingType_Level,
		std::bind(&LevelRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void LevelRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
}

bool LevelRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	size_t level_a = a->zhuansheng_lv*1000;
	level_a += a->level;
	size_t level_b = b->zhuansheng_lv * 1000;
	level_b += b->level;
	return level_a > level_b;
}
