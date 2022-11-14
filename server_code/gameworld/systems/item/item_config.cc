#include "StdAfx.h"
#include "item_config.h"


std::map<int, ItemConfig> ItemConfigPool::config_pool_;
std::map<int, EquipConfig> ItemConfigPool::equip_config_pool_;
std::map<int, SmeltConfig> ItemConfigPool::equip_smelt_pool;
std::map<int, LevelupConfig> ItemConfigPool::equip_levelup_pool;
std::map<int, ComposeConfig> ItemConfigPool::equip_compose_pool;
std::map<int, std::vector<AttrRangeConfig>> ItemConfigPool::legend_attr_pool;

GameLuaConfig ItemConfigPool::lua_reader_;

bool ItemConfigPool::Load(GameLuaConfig* data)
{
	if (!data->openGlobalTable("ItemConfig"))
	{
		OutputMsg(rmError, ("can't open Items table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			ItemConfig conf;
			memset(&conf, 0, sizeof(ItemConfig));
			int ndef = 0;
			//bool valid = false;

			conf.id = data->getFieldInt("id");
			conf.type = data->getFieldInt("type");
			conf.subtype = data->getFieldInt("subType");
			conf.bagtype = data->getFieldInt("bagType", &ndef);
			conf.quality = data->getFieldInt("quality");
			conf.level = data->getFieldInt("level");
			conf.zs_level = data->getFieldInt("zsLevel", &ndef);
			conf.job = data->getFieldInt("job");
			conf.equiptype = data->getFieldInt("equiptype");
			const char* name = data->getFieldString("name");
			conf.useCond = data->getFieldInt("useCond", &ndef);
			if (nullptr == name)
			{
				OutputMsg(rmError, "ItemName is NULL,ItemId is %d", conf.id);
				return false;
			}
			if (strlen(name) < 32)
				strcpy(conf.name, name);
			// name??

			config_pool_[conf.id] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------ItemConfig is null");
	}

	data->closeTable();

	return true;
}

const ItemConfig* ItemConfigPool::GetItemConfig(int id)
{
	auto it = config_pool_.find(id);
	if (it == config_pool_.end())
		return nullptr;
	return &it->second;
}
/*
inline int MakeSmeltKey(int level, int zsLevel, int quality)
{
	return level * 10 + zsLevel * 10000 + quality;
}
*/
bool ItemConfigPool::LoadEquip(GameLuaConfig* data)
{
	if (!data->openGlobalTable("EquipConfig"))
	{
		OutputMsg(rmError, ("can't open Equip table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			EquipConfig conf;
			memset(&conf, 0, sizeof(EquipConfig));
			int ndef = 0;
			//bool valid = false;

			conf.id = data->getFieldInt("id");
			conf.hp = data->getFieldInt("hp");
			conf.atk = data->getFieldInt("atk", &ndef);
			conf.def = data->getFieldInt("def", &ndef);
			conf.res = data->getFieldInt("res", &ndef);
			conf.crit = data->getFieldInt("crit", &ndef);
			conf.tough = data->getFieldInt("tough", &ndef);
			double ddef = 15.0;
			conf.addrangeHigh = (float)data->getFieldNumber("additionRange", &ddef);
			ddef = 0.0;
			conf.addrangeLow = (float)data->getFieldNumber("additionRangeLow", &ddef);
			conf.ex_power = data->getFieldInt("exPower", &ndef);

			if (data->fieldTableExists("exAttr1") && data->openFieldTable("exAttr1"))
			{
				conf.ex_attr1[0] = data->getFieldInt("type", &ndef);
				conf.ex_attr1[1] = data->getFieldInt("value", &ndef);
				data->closeTable();
			}
			if (data->fieldTableExists("exAttr2") && data->openFieldTable("exAttr2"))
			{
				conf.ex_attr2[0] = data->getFieldInt("type", &ndef);
				conf.ex_attr2[1] = data->getFieldInt("value", &ndef);
				data->closeTable();
			}

			if (data->fieldTableExists("exAttr3") && data->openFieldTable("exAttr3"))
			{
				conf.ex_attr3[0] = data->getFieldInt("type", &ndef);
				conf.ex_attr3[1] = data->getFieldInt("value", &ndef);
				data->closeTable();
			}

			if (data->fieldTableExists("baseAttr1") && data->openFieldTable("baseAttr1"))
			{
				conf.base_attr1[0] = data->getFieldInt("type", &ndef);
				conf.base_attr1[1] = data->getFieldInt("value", &ndef);
				data->closeTable();
			}

			if (data->fieldTableExists("baseAttr2") && data->openFieldTable("baseAttr2"))
			{
				conf.base_attr2[0] = data->getFieldInt("type", &ndef);
				conf.base_attr2[1] = data->getFieldInt("value", &ndef);
				data->closeTable();
			}

			if (data->fieldTableExists("exAttrCount") && data->openFieldTable("exAttrCount"))
			{
				if (data->enumTableFirst())
				{
					do 
					{
						int i = conf.exAttrCountNum++;
						conf.exAttrCount[i][0] = data->getFieldInt("count", &ndef);
						conf.exAttrCount[i][1] = data->getFieldInt("rate", &ndef);
						conf.exAttrCountTotalRate += conf.exAttrCount[i][1];
						if (conf.exAttrCountNum >= EQUIP_ATTR_COUNT) break;
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			if (data->fieldTableExists("exAttr") && data->openFieldTable("exAttr"))
			{
				if (data->enumTableFirst())
				{
					do
					{
						int i = conf.exAttrNum++;
						conf.exAttr[i][0] = data->getFieldInt("type", &ndef);
						conf.exAttr[i][1] = data->getFieldInt("val", &ndef);
						conf.exAttr[i][2] = data->getFieldInt("rate", &ndef);
						conf.exAttrTotalRate += conf.exAttr[i][2];
						if (conf.exAttrNum >= EQUIP_ATTR_COUNT) break;
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			equip_config_pool_[conf.id] = conf;
			LoadSmelt(data, conf.id);
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------EquipConfig is null");
	}

	data->closeTable();

	return true;
}

bool ItemConfigPool::LoadSmelt(GameLuaConfig* data, int id)
{
	SmeltConfig conf;
	int ndef = 0;
	conf.stoneId = data->getFieldInt("stoneId", &ndef);
	conf.stoneNum = data->getFieldInt("stoneNum", &ndef);
	conf.goldNum = data->getFieldInt("moneyNum", &ndef);

	if (data->fieldTableExists("equipRate") && data->openFieldTable("equipRate"))
	{
		if (data->enumTableFirst())
		{
			do
			{
				SmeltEquipRateConfig rateConf;
				rateConf.qualityAdd = data->getFieldInt("qualityAdd");
				rateConf.rate = data->getFieldInt("rate");

				conf.equipRateList.push_back(rateConf);
			} while (data->enumTableNext());
		}
		data->closeTable();
	}
	conf.currency.clear();
	if (data->fieldTableExists("moneyType") && data->openFieldTable("moneyType"))
	{
		if (data->enumTableFirst())
		{
			do
			{
				conf.currency[data->getFieldInt("type")] += data->getFieldInt("count");
			} while (data->enumTableNext());
		}
		data->closeTable();
	}
	if (!conf.isEmpty()) {
		equip_smelt_pool[id] = conf;
	}
	return true;
}

const EquipConfig* ItemConfigPool::GetEquipConfig(int id)
{
	auto it = equip_config_pool_.find(id);
	if (it == equip_config_pool_.end())
		return nullptr;
	return &it->second;
}
/*
bool ItemConfigPool::LoadSmelt(GameLuaConfig* data)
{
	if (!data->openGlobalTable("SmeltConfig"))
	{
		OutputMsg(rmError, ("can't open Smelt table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		do {
			SmeltConfig conf; 
			int ndef = 0;

			conf.level = data->getFieldInt("level");
			conf.quality = data->getFieldInt("quality");
			conf.zsLevel = data->getFieldInt("zsLevel", &ndef);
			conf.stoneId = data->getFieldInt("stoneId");
			conf.stoneNum = data->getFieldInt("stoneNum");
			conf.goldNum = data->getFieldInt("moneyNum");

			if (data->openFieldTable("equipRate"))
			{
				if (data->enumTableFirst())
				{
					do 
					{
						SmeltEquipRateConfig rateConf;
						rateConf.qualityAdd = data->getFieldInt("qualityAdd");
						rateConf.rate = data->getFieldInt("rate");

						conf.equipRateList.push_back(rateConf);
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			conf.currency.clear();
			if (data->fieldTableExists("moneyType") && data->openFieldTable("moneyType"))
			{
				if (data->enumTableFirst())
				{
					do
					{
						conf.currency[data->getFieldInt("type")] += data->getFieldInt("count");
					} while (data->enumTableNext());
				}
				data->closeTable();
			}
			int key = MakeSmeltKey(conf.level, conf.zsLevel, conf.quality);
			equip_smelt_pool[key] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------EquipConfig is null");
	}

	data->closeTable();

	return true;
}
*/
const SmeltConfig* ItemConfigPool::GetSmeltConfig(int key)
{
	//int key = MakeSmeltKey(level, zsLevel, quality);
	if (equip_smelt_pool.find(key) == equip_smelt_pool.end())
		return NULL;

	return &equip_smelt_pool[key];
}

bool ItemConfigPool::LoadLevelup(GameLuaConfig* data)
{
	if (!data->openGlobalTable("LegendLevelupConfig"))
	{
		OutputMsg(rmError, ("can't open LegendLevelupConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			LevelupConfig conf;
			conf.oldEquipId = data->getFieldInt("oldEquipId");
			conf.newEquipId = data->getFieldInt("newEquipId");
			conf.itemId = data->getFieldInt("itemId");
			conf.count = data->getFieldInt("count");

			equip_levelup_pool[conf.oldEquipId] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------LegendLevelupConfig is null");
	}

	data->closeTable();

	return true;
	
}

const LevelupConfig* ItemConfigPool::GetLevelupConfig(int equipId)
{
	if (equip_levelup_pool.find(equipId) == equip_levelup_pool.end())
		return NULL;

	return &equip_levelup_pool[equipId];
}

bool ItemConfigPool::LoadCompose(GameLuaConfig* data)
{
	if (!data->openGlobalTable("LegendComposeConfig"))
	{
		OutputMsg(rmError, ("can't open LegendLevelupConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			ComposeConfig conf;
			conf.equipId= data->getFieldInt("equipId");
			conf.itemId = data->getFieldInt("itemId");
			conf.count = data->getFieldInt("count");
			conf.type = data->getFieldInt("type");

			equip_compose_pool[conf.equipId] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------LegendLevelupConfig is null");
	}

	data->closeTable();

	return true;
}

const ComposeConfig* ItemConfigPool::GetComposeConfig(int equipId)
{
	if (equip_compose_pool.find(equipId) == equip_compose_pool.end())
		return NULL;

	return &equip_compose_pool[equipId];
}

bool ItemConfigPool::LoadLegendAttr(GameLuaConfig* data)
{
	if (!data->openGlobalTable("LegendAttrRateConfig"))
	{
		OutputMsg(rmError, ("can't open LegendAttrRateConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			AttrRangeConfig conf;
			conf.low = data->getFieldInt("low");
			conf.high = data->getFieldInt("high");
			conf.rate = data->getFieldInt("rate");

			int zhuanshenglv = data->getFieldInt("zhuanshenglv");
			int level = data->getFieldInt("level");
			int newlevel = zhuanshenglv * 1000 + level;

			if (legend_attr_pool.find(newlevel) != legend_attr_pool.end())
				legend_attr_pool[newlevel].push_back(conf);
			else
			{
				std::vector<AttrRangeConfig> level_attr;
				level_attr.push_back(conf);

				legend_attr_pool[newlevel] = level_attr;
			}
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------LegendAttrRateConfig is null");
	}

	data->closeTable();

	return true;
}

const std::vector<AttrRangeConfig>* ItemConfigPool::GetLegendAttrConfig(int level)
{
	if (legend_attr_pool.find(level) == legend_attr_pool.end())
		return NULL;

	return &legend_attr_pool[level];
}


bool ItemConfigPool::Reload()
{
	GameLuaConfig* config = &(ItemConfigPool::lua_reader_);
	const char* txt = GameLuaConfig::LoadFromFile(GameConfigData::IncludeFileName, config);
	if (txt == NULL)
	{
		return false;
	}
	if (!config->setScript(txt))
	{
		OutputMsg(rmError, ("syntax error on  %s"), GameConfigData::IncludeFileName);
		return false;
	}
	
	// 以下五项可以只更新其中的一项，另外失败的可能性只有配置表不存在的情况
	// 所以这里不判断返回值，都算加载成功
	Load(config);
	LoadEquip(config);
	//LoadSmelt(config);
	LoadCompose(config);
	LoadLegendAttr(config);

	config->setScript(NULL);
	return true;
}


