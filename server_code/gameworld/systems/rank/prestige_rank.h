#pragma once

struct ActorBasicData;
class StaticRankBasic;

class PrestigeRank :
	public StaticRankBasic
{
public:
	PrestigeRank(void);
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
	virtual bool Screening(const ActorBasicData* data);
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};