#include "StdAfx.h"
#include "bag_config.h"


BagBaseConfig BagConfigPool::base_config_;
std::map<int, BagExpandConfig> BagConfigPool::expand_config_pool_;
std::vector<int> BagConfigPool::vip_grid_config_;


bool BagConfigPool::LoadBase(GameConfigData* data)
{
	if (!data->openGlobalTable("BagBaseConfig"))
	{
		OutputMsg(rmError, ("can't open BagBaseConfig table"));
		return false;
	}

	base_config_.base_size = data->getFieldInt("baseSize");
	base_config_.row_size = data->getFieldInt("rowSize");

	data->closeTable();

	return true;
}

bool BagConfigPool::LoadExpand(GameConfigData* data)
{
	if (!data->openGlobalTable("BagExpandConfig"))
	{
		OutputMsg(rmError, ("can't open BagExpandConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			BagExpandConfig conf;
			//int ndef = 0;

			conf.row = data->getFieldInt("row");
			conf.cost = data->getFieldInt("cost");

			expand_config_pool_[conf.row] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------BagExpandConfig is null");
	}

	data->closeTable();

	return true;
}

bool BagConfigPool::LoadVipGrid(GameConfigData* data)
{
	if (!data->openGlobalTable("VipGridConfig"))
	{
		OutputMsg(rmError, ("can't open VipGridConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			int vip = 0;
			int grid = 0;

			vip = data->getFieldInt("vip");
			grid = data->getFieldInt("grid");

			if ((std::size_t)vip >= vip_grid_config_.size()) vip_grid_config_.resize(1+ vip * 2);
			vip_grid_config_[vip] = grid;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------BagVipGridConfig is null");
	}

	data->closeTable();

	return true;

}

int BagConfigPool::GetBaseSize()
{
	return base_config_.base_size;
}

int BagConfigPool::GetRowSize()
{
	return base_config_.row_size;
}

int BagConfigPool::GetVipGrid(int vip)
{
	if ((std::size_t)vip >= vip_grid_config_.size() || vip < 0) return 0;
	return vip_grid_config_[vip];
}


BagExpandConfig* BagConfigPool::GetExpandConfig(int row)
{
	auto it = expand_config_pool_.find(row);
	if (it == expand_config_pool_.end())
		return NULL;
	return &it->second;
}

