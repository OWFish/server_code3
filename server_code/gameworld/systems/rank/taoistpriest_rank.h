#pragma once

struct ActorBasicData;
class StaticRankBasic;

class TaoistpriestRank :
	public StaticRankBasic
{
public:
	TaoistpriestRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->taoistpriest_power == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};