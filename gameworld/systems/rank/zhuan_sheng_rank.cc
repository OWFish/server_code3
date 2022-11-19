#include "StdAfx.h"
#include "actor/actor_data_mgr.h"
#include "ranking_system.h"
#include "protocol/system_cmd_def.h"
#include "role/role_system.h"
#include "item/equip/equip_system.h"
#include "wing/wing_system.h"
#include "actor/actor_asyn_mgr.h"

#include "static_rank_basic.h"

#include "zhuan_sheng_rank.h"


ZhuanShengRank::ZhuanShengRank(void) :
	StaticRankBasic(RankingType_ZhuanSheng,
		std::bind(&ZhuanShengRank::Compare, this,
			std::placeholders::_1,
			std::placeholders::_2
		)
	)
{

}

void ZhuanShengRank::UpdateRankCache(DataPacket& cache, const ActorBasicData* data)
{
	StaticRankBasic::UpdateRankCache(cache, data);
	cache << data->zhuansheng_lv;
}

bool ZhuanShengRank::Compare(const ActorBasicData* a, const ActorBasicData* b)
{
	if (a->zhuansheng_lv == b->zhuansheng_lv) {
		return a->zhuansheng_exp > b->zhuansheng_exp;
	}
	return a->zhuansheng_lv > b->zhuansheng_lv;
}
