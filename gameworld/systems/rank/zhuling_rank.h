#pragma once

struct ActorBasicData;
class StaticRankBasic;

class ZhulingRank :
	public StaticRankBasic
{
public:
	ZhulingRank(void);
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
	virtual bool Screening(const ActorBasicData* data) { return data->total_zhuling_level == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};