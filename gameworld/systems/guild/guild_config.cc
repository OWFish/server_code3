#include "StdAfx.h"
#include "guild_config.h"

std::vector<GuildPosConfig> GuildConfig::pos_counts_;

bool GuildConfig::LoadGuildLevel(GameConfigData * data)
{
	if (!data->openGlobalTable("GuildConfig"))
	{
		OutputMsg(rmError, ("can't open GuildConfig table"));
		return false;
	}

	if (!data->openFieldTable("posCounts"))
	{
		OutputMsg(rmError, ("can't open posCounts table"));
		data->closeTable();
		return false;
	}

	int len = data->getTableLen();
	pos_counts_.resize(len);

	int index = 0;
	if (data->enumTableFirst())
	{
		do {
			GuildPosConfig& levelConfig = pos_counts_[index];
			if (!LoadOneGuildLevel(data, levelConfig))
			{
				data->closeTable();
				data->closeTable();
				return false;
			}
			++index;

		} while (data->enumTableNext());
	}

	data->closeTable();

	data->closeTable();

	return true;
}

GuildPosConfig * GuildConfig::GetLevelConfig(int level)
{
	if (level < 1 || level >(int)pos_counts_.size())
		return nullptr;
	return &pos_counts_[level - 1];
}

bool GuildConfig::LoadOneGuildLevel(GameConfigData * data, GuildPosConfig & levelConfig)
{
	int len = data->getTableLen();
	levelConfig.counts_.resize(len);

	int index = 0;
	if (data->enumTableFirst())
	{
		do {
			levelConfig.counts_[index] = data->getFieldInt(NULL);
			++index;

		} while (data->enumTableNext());
	}

	return true;
}
