#pragma once
#include "config/game_config_data.h"

class NeigongConfig
{
public:
	static bool LoadNeigongConfig(GameConfigData* data);
	static int GetIntervalTime();
	inline static int GetPrecent() { return _precent; };

private:
	static int _intervalTime;
	static int _precent;
}; 