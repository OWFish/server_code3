#pragma once

struct ActorBasicData;
class StaticRankBasic;

class ZhanLingRank :
	public StaticRankBasic
{
public:
	ZhanLingRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->zhan_ling_stage == 0 && data->zhan_ling_star == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};