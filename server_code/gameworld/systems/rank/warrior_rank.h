#pragma once

struct ActorBasicData;
class StaticRankBasic;

class WarriorRank :
	public StaticRankBasic
{
public:
	WarriorRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->warrior_power == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};