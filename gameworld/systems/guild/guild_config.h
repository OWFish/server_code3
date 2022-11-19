#pragma once
#include <vector>
#include "config/game_config_data.h"

struct GuildPosConfig
{
	std::vector<int> counts_;
};

class GuildConfig
{
public:
	static bool LoadGuildLevel(GameConfigData* data);
	static GuildPosConfig* GetLevelConfig(int level);

private:
	static bool LoadOneGuildLevel(GameConfigData* data, GuildPosConfig& levelConfig);

private:
	static std::vector<GuildPosConfig> pos_counts_;
};