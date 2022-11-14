#pragma once

struct ActorBasicData;
class StaticRankBasic;

class TuJianRank :
	public StaticRankBasic
{
public:
	TuJianRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->total_tujian_power == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};