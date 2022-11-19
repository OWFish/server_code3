#include "StdAfx.h"
#include "rank_config.h"

std::unordered_map<int, RankConfig>  RankConfigPool::config_pool_;

bool RankConfigPool::Load(GameConfigData * data)
{
	if (!data->openGlobalTable("OpenRankConfig"))
	{
		OutputMsg(rmError, "can't open OpenRankConfig table");
		return false;
	}

	if (data->enumTableFirst())
	{
		int ranktype = 0;
		static RankConfig temp;
		temp.clear();
		do {
			temp.rank_type = data->getFieldInt("id");
			temp.rank_maxsize = data->getFieldInt("rankmaxsize");
			temp.rank_showsize = data->getFieldInt("rankshowsize");
			temp.rank_name = data->getFieldString("rankname");
			config_pool_.emplace(temp.rank_type, temp);
			temp.clear();
		} while (data->enumTableNext());
	}

	return true;
}

const RankConfig * RankConfigPool::GetRankConfig(int ranktype)
{
	auto ite = config_pool_.find(ranktype);
	if (ite == config_pool_.end())
	{
		return nullptr;
	}

	return &ite->second;
}

const int RankConfigPool::GetRankMaxSize(int ranktype)
{
	auto ite = config_pool_.find(ranktype);
	if (ite == config_pool_.end())
	{
		return -1;
	}
	return ite->second.rank_maxsize;
}

const int RankConfigPool::GetRankShowSize(int ranktype)
{
	auto ite = config_pool_.find(ranktype);
	if (ite == config_pool_.end())
	{
		return -1;
	}
	return ite->second.rank_showsize;
}

const std::string RankConfigPool::GetRankName(int ranktype)
{
	auto ite = config_pool_.find(ranktype);
	if (ite == config_pool_.end())
	{
		return "";
	}
	return ite->second.rank_name;
}

bool RankConfigPool::Reload()
{
	return false;
}
