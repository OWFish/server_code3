#pragma once

struct ActorBasicData;
class StaticRankBasic;

class MageRank :
	public StaticRankBasic
{
public:
	MageRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->mage_power == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};