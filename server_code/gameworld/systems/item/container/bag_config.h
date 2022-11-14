#pragma once

#include "config/game_config_data.h"
#include <map>
#include <vector>



struct BagBaseConfig
{
	int base_size;
	int row_size;
};

struct BagExpandConfig
{
	int row;
	int cost;
};


class BagConfigPool
{
public:
	static bool LoadBase(GameConfigData* data);
	static bool LoadExpand(GameConfigData* data);
	static bool LoadVipGrid(GameConfigData* data);
	static int GetBaseSize();
	static int GetRowSize();
	static int GetVipGrid(int vip);
	static BagExpandConfig* GetExpandConfig(int row);

private:
	static BagBaseConfig base_config_;
	static std::map<int, BagExpandConfig> expand_config_pool_;
	static std::vector<int> vip_grid_config_;
};


