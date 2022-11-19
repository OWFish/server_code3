#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"

#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "zhanling_rank.h"


ZhanLingRank::ZhanLingRank(void) :
	StaticRankBasic(RankingType_ZhanLing,
		std::bind(&ZhanLingRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void ZhanLingRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << (int)data->zhan_ling_stage;
	cache << (int)data->zhan_ling_star;
}

bool ZhanLingRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	//if (a->zhan_ling_stage == b->zhan_ling_stage)
	//{
		return a->zhan_ling_star > b->zhan_ling_star;
	//}
	//else
	//{
	//	return a->zhan_ling_stage > b->zhan_ling_stage;
	//}
}
