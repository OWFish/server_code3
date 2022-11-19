#pragma once




struct ActorBasicData;
class StaticRankBasic;

class PowerRank:
	public StaticRankBasic
{
public:
	PowerRank(void);
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
	virtual bool Screening(const ActorBasicData* data) { return data->level < RANK_MIN_LEVEL; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};