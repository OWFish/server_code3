#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "warrior_rank.h"


WarriorRank::WarriorRank(void) :
	StaticRankBasic(RankingType_Warrior,
		std::bind(&WarriorRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void WarriorRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (double)data->warrior_power;
}

bool WarriorRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{

	return a->warrior_power > b->warrior_power;
}
