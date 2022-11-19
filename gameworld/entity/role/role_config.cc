#include "StdAfx.h"
#include "role_config.h"


std::map<int, RoleAttrConfigs> RoleConfigPool::config_pool_;

RoleAttrConfigs::RoleAttrConfigs()
{
	memset(attr, 0, sizeof(RoleAttrConfig)* 3);
}

RoleAttrConfigs::RoleAttrConfigs(const RoleAttrConfigs& attrs)
{
	memcpy(attr, attrs.attr, sizeof(RoleAttrConfig)* 3);
}

bool RoleConfigPool::Load(GameConfigData* data)
{
	if (!data->openGlobalTable("RoleConfig"))
	{
		OutputMsg(rmError, ("can't open role table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		int lv = 0;
		int job = 0;
		RoleAttrConfigs configs;
		configs.init();
		do {
			for (int i = 0; i < ROLE_JOB_COUNT; ++i)
			{
				if (!data->getFieldIndexTable(i+1))
				{
					OutputMsg(rmError, "open job attr failed. l:%d, j:%d", lv, i);
					return false;
				}
				lv = data->getFieldInt("level");
				job = data->getFieldInt("job");
				assert(job >= 1 && job <= ROLE_JOB_COUNT);
				RoleAttrConfig &config = configs.attr[job-1];
				auto& map_dict = configs.attr_dict[job - 1];
				int ndef = 0;
				config.hp = data->getFieldInt("hp", &ndef);
				config.mp = data->getFieldInt("mp", &ndef);
				config.atk = data->getFieldInt("atk", &ndef);
				config.def = data->getFieldInt("def", &ndef);
				config.res = data->getFieldInt("res", &ndef);
				config.crit = data->getFieldInt("crit", &ndef);
				config.tough = data->getFieldInt("tough", &ndef);
				config.ms = data->getFieldInt("ms", &ndef);
				config.as = data->getFieldInt("as", &ndef);
				config.acrit = data->getFieldInt("acrit", &ndef);

				if (data->fieldTableExists("attr") && data->openFieldTable("attr"))
				{
					if (data->enumTableFirst())
					{
						do 
						{
							map_dict[data->getFieldInt("type", &ndef)] = data->getFieldInt("value", &ndef);
						} while (data->enumTableNext());
					}
					data->closeTable();
				}

				data->closeTable();
			}
			config_pool_[lv] = configs;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------RoleConfig is null");
	}

	data->closeTable();

	return true;
}

const RoleAttrConfig* RoleConfigPool::Get(int level, int job)
{
	if (job <= 0 || job > ROLE_JOB_COUNT)
		return NULL;

	auto it = config_pool_.find(level);
	if (it == config_pool_.end())
		return NULL;
	return &it->second.attr[job-1];
}

const std::unordered_map<int, int>* RoleConfigPool::GetAttrDict(int level, int job)
{
	if (job <= 0 || job > ROLE_JOB_COUNT)
		return nullptr;

	auto it = config_pool_.find(level);
	if (it == config_pool_.end())
		return nullptr;

	return &it->second.attr_dict[job - 1];
}
