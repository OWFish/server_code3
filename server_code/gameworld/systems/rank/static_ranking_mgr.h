#pragma once

/*
	静态排行榜，处理实时性要求不高，但数据量很大的排行榜，对于基础数据可通过ActorBasicData
	在内存中处理，RoleData可考虑直接通过sql查询获得再传递回逻辑服。
*/

// 战力排行榜数据结构
struct RankingData
{
	int actor_id;
	int ranking_value;	// 参与排序的值 暂时用int，有需要再改为64
};


#include "static_rank_basic.h"



#include <map>


class StaticRankingMgr
{
public:
	StaticRankingMgr();
	~StaticRankingMgr();

	void Destroy();
	bool Load();
	void RunOne(int64_t now_t);
	
public:
	void SendRankingDataByType(Actor* actor, RankingType type);
	DataPacket* GetFirstCacheByType(RankingType type);
	void UpdateDynamicFirstCache(int actor_id, RankingType type);
	StaticRankBasic* GetRanking(RankingType type);
	void UpdateRank();

private:
	void AsyncUpdateDynamicFirstCache(Actor* actor, RankingType type);
private:
	Timer logic_timer_;
	int next_save_time_;
	/*
	std::vector<RankingData> power_rank_;	// 战力排行榜记录
	DataPacket power_rank_pack_cache_;		// 战力排行榜发包缓存
	std::map<ActorId, int> power_rank_index_; // 战力排行榜名次缓存
	*/
	/*
	PowerRank power_rank_;
	LevelRank level_rank_;
	WingRank wing_rank_;
	WarriorRank warrior_rank_;
	MageRank mage_rank_;
	TaoistpriestRank taoistpriest_rank_;
	TrainRank train_rank_;
	*/
	std::map<RankingType, StaticRankBasic*> rank_map_;

	//特别做，因为外部没办法读rank_map_
	std::map<RankingType, DataPacket*> dynamic_first_cache_;
	
};