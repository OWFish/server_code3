#include "StdAfx.h"
#include "monster_config.h"


std::map<int, MonsterConfig> MonsterConfigPool::config_pool_;
GameLuaConfig MonsterConfigPool::lua_reader_;

bool MonsterConfigPool::Load(GameConfigData* gc)
{
	return LoadData(gc);
}

const MonsterConfig* MonsterConfigPool::Get(int id)
{
	auto it = config_pool_.find(id);
	if (it == config_pool_.end())
		return nullptr;
	return &it->second;
}


bool MonsterConfigPool::LoadData(GameLuaConfig* data)
{
	if (!data->openGlobalTable("MonstersConfig"))
	{
		OutputMsg(rmError, ("can't open MonstersConfig table"));
		return false;
	}

	if (data->enumTableFirst())
	{
		//int nIdx = 0;
		do {
			MonsterConfig conf;
			int ndef = 0;
			double ddef = 0.0;
			//bool valid = false;
			string::AnsiString r;

			conf.id = data->getFieldInt("id");
			//OutputMsg(rmTip, "------------------------------conf.fbid: %d", conf.fbid); // test config load
			//conf.skill = data->getFieldInt("skill");
			conf.ai = data->getFieldInt("ai", &ndef);
			conf.type = data->getFieldInt("type", &ndef);
			conf.attrs.hp = data->getFieldNumber("hp", &ddef);
			conf.attrs.atk = data->getFieldNumber("atk", &ddef);
			conf.attrs.def = data->getFieldNumber("def", &ddef);
			conf.attrs.res = data->getFieldNumber("res", &ddef);
			conf.attrs.crit = data->getFieldNumber("crit", &ddef);
			conf.attrs.tough = data->getFieldNumber("tough", &ddef);
			ddef = 1500.0;
			conf.attrs.as = data->getFieldNumber("as", &ddef);
			ddef = 1000.0;
			conf.attrs.ms = data->getFieldNumber("ms", &ddef);
			ddef = 0.0;
			conf.attrs.stunRes = data->getFieldNumber("stunRes", &ddef);
			conf.attrs.penetRate = data->getFieldNumber("penetRate", &ddef);
			conf.attrs.critDamage = data->getFieldNumber("critDamage", &ddef);
			conf.attrs.hit = data->getFieldNumber("hit", &ddef);
			ndef = -1;
			conf.gatherMonsterType = data->getFieldInt("gatherMonsterType", &ndef);
			ndef = 0;
			conf.gatherTime = data->getFieldInt("gatherTime", &ndef);
			conf.shield = data->getFieldInt("shield", &ndef);
			conf.waitGatherTime = data->getFieldInt("waitGatherTime", &ndef);
			conf.gsize = data->getFieldInt("gsize", &ndef);
			config_pool_[conf.id] = conf;
		} while (data->enumTableNext());
	}
	else
	{
		OutputMsg(rmError, "------------------------MonstersConfig is null");
	}

	data->closeTable();

	return true;
}

bool MonsterConfigPool::Reload()
{
	GameLuaConfig* config = &(MonsterConfigPool::lua_reader_);
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

	bool ret = LoadData(config);
	if (!ret)
	{
		OutputMsg(rmError, "load monster config error!");
		return false;
	}
	config->setScript(NULL);
	return ret;
}

