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
	static int rankLimitexp_;    //�ϰ���
	static int normalDeterDam_;    //�����˺�
	static int rankDeterDam_[RANK_SIZE];  //���а��˺�
};