#pragma once

#include "config/game_config_data.h"
#include <unordered_map>

struct RankConfig
{
	int rank_type;			//排行榜类型
	int rank_maxsize;		//排行榜人数上限
	int rank_showsize;		//排行榜展示上限
	std::string rank_name;	//排行榜名字
	void clear()
	{
		rank_type = 0;
		rank_maxsize = 0;
		rank_showsize = 0;
		rank_name = "";
	}
};

class RankConfigPool
{
public:
	static bool Load(GameConfigData* data);

	static const RankConfig* GetRankConfig(int ranktype);

	static const int GetRankMaxSize(int ranktype);

	static const int GetRankShowSize(int ranktype);

	static const std::string GetRankName(int ranktype);

	static bool Reload();
private:
	static std::unordered_map<int, RankConfig> config_pool_;

	static GameConfigData lua_reader_;
};


