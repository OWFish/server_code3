#ifndef _RANK_SYSTEM_H_
#define _RANK_SYSTEM_H_


#include "static_ranking_mgr.h"
#include "dynamic_ranking_mgr.h"


class RankingSystem
{
public:
	RankingSystem();
	virtual ~RankingSystem();
	void Destroy();
	void Initialize();
	void RunOne(int64_t now_t);

	void OnReqRankingData(Actor* actor, DataPacketReader& pack);
	DynamicRankingMgr* GetDynamicRankingMgr() { return dynamic_rank_mgr_; }

	StaticRankingMgr* GetStaticRankingMgr(void) { return static_rank_mgr_; }
private:
	StaticRankingMgr *static_rank_mgr_;	//固定间隔更新
	DynamicRankingMgr *dynamic_rank_mgr_; //实时更新
};

#endif