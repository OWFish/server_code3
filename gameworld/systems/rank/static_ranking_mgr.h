#pragma once

/*
	��̬���а񣬴���ʵʱ��Ҫ�󲻸ߣ����������ܴ�����а񣬶��ڻ������ݿ�ͨ��ActorBasicData
	���ڴ��д���RoleData�ɿ���ֱ��ͨ��sql��ѯ����ٴ��ݻ��߼�����
*/

// ս�����а����ݽṹ
struct RankingData
{
	int actor_id;
	int ranking_value;	// ���������ֵ ��ʱ��int������Ҫ�ٸ�Ϊ64
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
	std::vector<RankingData> power_rank_;	// ս�����а��¼
	DataPacket power_rank_pack_cache_;		// ս�����а񷢰�����
	std::map<ActorId, int> power_rank_index_; // ս�����а����λ���
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

	//�ر�������Ϊ�ⲿû�취��rank_map_
	std::map<RankingType, DataPacket*> dynamic_first_cache_;
	
};