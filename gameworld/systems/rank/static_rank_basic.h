#pragma once

#include <functional>
#include "common/system_param_def.h"
struct ActorBasicData;
class BaseAllocator;
class DataPacket;
class Actor;


#define DEFAULT_SEND_SIZE 200
#define RANK_MIN_LEVEL 60

class StaticRankBasic
{
	typedef std::function<bool(const ActorBasicData*, const ActorBasicData* )> compare_t;
public:
	StaticRankBasic(RankingType type, compare_t compare);
	virtual ~StaticRankBasic(void);
	virtual void UpdataRank(void);
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
	virtual void SendData(Actor* actor);
	virtual void UpdataFirstCache(Actor* actor,DataPacket& cache);
	virtual bool Screening(const ActorBasicData* data) { return false;}
	int GetActorRanking(Actor* actor);
	int GetIndexFromId(int id);
	int GetActorIdByRanking(size_t i);
public:
	inline void SetSendSize(size_t s = DEFAULT_SEND_SIZE) { send_size_ = s; }
	inline void SetCcompare(const compare_t& compare) { compare_ = compare;}
	DataPacket* GetFirstCache(void) { return &first_cache_; }
	inline size_t getRankDataSize(void) { return rank_data_.size(); }
	std::vector<ActorBasicData*> GetRankData() { return rank_data_; }
	DataPacket* GetRankCache(size_t min, size_t max);
private:
	void AsyncUpdateFirstCache(Actor* actor);
private:
	compare_t compare_;
	RankingType type_;
	BaseAllocator basic_alloc_;
	DataPacket rank_cache_;
	DataPacket first_cache_;
	DataPacket cache_;
	std::vector<ActorBasicData*> rank_data_;
	std::map<int, size_t> rank_index_actor_id_;
	size_t send_size_ = DEFAULT_SEND_SIZE;
};
