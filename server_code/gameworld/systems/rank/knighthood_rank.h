#pragma once

struct ActorBasicData;
class StaticRankBasic;

class KnighthoodRank :
	public StaticRankBasic
{
public:
	KnighthoodRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->knighthood_lv == 0 || data->level < RANK_MIN_LEVEL; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};