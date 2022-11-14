#pragma once

#include "config/game_config_data.h"
#include <map>
#include <vector>

struct FubenConfig
{
	int fbid;
	int type;
	int totalTime;
	int closeTime;
	int remainTime;
	std::vector<int> scenes;
	std::string name;
	std::string desc;
	int showZhanLing;
	int findPath;
	int pkMode;
};

class FubenConfigPool
{
public:
	static bool Load(GameConfigData* data);
	static const FubenConfig* Get(int id);

private:
	static std::map<int, FubenConfig> config_pool_;
};


