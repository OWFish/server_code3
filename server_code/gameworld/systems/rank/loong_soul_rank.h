#pragma once

struct ActorBasicData;
class StaticRankBasic;

class LoongSoulRank :
	public StaticRankBasic
{
public:
	LoongSoulRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->total_loongsoul_level == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};