#include "StdAfx.h"
#include "fuben_config.h"


std::map<int, FubenConfig> FubenConfigPool::config_pool_;

bool FubenConfigPool::Load(GameConfigData* data)
{
	if (!data->openGlobalTable("InstanceConfig"))
	{
		OutputMsg(rmError, ("can't open Fubens table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			FubenConfig conf;
			int ndef = 0;
			//bool valid = false;
			string::AnsiString r;
			conf.fbid = data->getFieldInt("fbid");
			//OutputMsg(rmTip, "------------------------------conf.fbid: %d", conf.fbid); // test config load
			conf.type = data->getFieldInt("type");
			conf.totalTime = data->getFieldInt("totalTime");
			conf.closeTime = data->getFieldInt("closeTime");
			conf.remainTime = data->getFieldInt("remainTime");
			conf.name = data->getFieldString("name", "");
			conf.desc = data->getFieldString("desc", "");
			conf.showZhanLing = data->getFieldInt("showZhanLing", &ndef);
			conf.findPath = data->getFieldInt("findPath", &ndef);
			conf.pkMode = data->getFieldInt("pkMode");
			if (!data->openFieldTable("scenes"))
			{
				OutputMsg(rmError, " open fuben scenes error!!");
				return false;
			}
			if (data->enumTableFirst())
			{
				do
				{
					int sid = data->getFieldInt(NULL);
					conf.scenes.push_back(sid);

				} while (data->enumTableNext());
			}
			data->closeTable();

			//todo field scenes
			config_pool_[conf.fbid] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------instanceConfig is null");
	}

	data->closeTable();

	return true;
}

const FubenConfig* FubenConfigPool::Get(int id)
{
	auto it = config_pool_.find(id);
	if (it == config_pool_.end())
		return nullptr;
	return &it->second;
}
