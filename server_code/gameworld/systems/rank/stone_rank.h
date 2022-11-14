#pragma once

struct ActorBasicData;
class StaticRankBasic;

class StoneRank :
	public StaticRankBasic
{
public:
	StoneRank(void);
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
	virtual bool Screening(const ActorBasicData* data) { return data->total_stone_level == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};