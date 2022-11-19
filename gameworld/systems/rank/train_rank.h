#pragma once

struct ActorBasicData;
class StaticRankBasic;

class TrainRank :
	public StaticRankBasic
{
public:
	TrainRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->train_level == 0 || data->level < RANK_MIN_LEVEL; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};