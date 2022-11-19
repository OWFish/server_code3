#pragma once

struct ActorBasicData;
class StaticRankBasic;

class WingRank :
	public StaticRankBasic
{
public:
	WingRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->total_wing_power == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};