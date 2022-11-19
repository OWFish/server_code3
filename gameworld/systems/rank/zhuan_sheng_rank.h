#pragma once

struct ActorBasicData;
class StaticRankBasic;

class ZhuanShengRank :
	public StaticRankBasic
{
public:
	ZhuanShengRank(void);
public:
	virtual void UpdateRankCache(DataPacket& cache, const ActorBasicData* data);
public:
	virtual bool Screening(const ActorBasicData* data) { return data->zhuansheng_lv == 0; }
private:
	bool Compare(const ActorBasicData* a, const ActorBasicData* b);
};