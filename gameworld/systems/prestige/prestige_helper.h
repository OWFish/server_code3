#pragma once
#include "attr/attribute.h"

#define RANK_SIZE 3

class PrestigeHelper
{
public:
	PrestigeHelper();
	~PrestigeHelper();

	static void setChangeExpTimeInfo();
	static void ChangePrestigeExpData(int tactorId);
	static void LogicRun(int64_t curr_t);

	static bool LoadPrestigeConfig(GameConfigData* data);

	static int getRankLimitexp(void) { return rankLimitexp_; };

	static int getDeterDam(int rank);
private:
	static std::map<uint64_t, ActorId, std::less<uint64_t>> _time_list;
	static int rankLimitexp_;    //上榜经验
	static int normalDeterDam_;    //常规伤害
	static int rankDeterDam_[RANK_SIZE];  //排行榜伤害
};