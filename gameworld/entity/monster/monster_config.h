#pragma once

#include "config/game_config_data.h"
#include <map>


struct MonsterAttr
{
	double hp;
	double atk;
	double def;
	double res;
	double crit;
	double tough;
	double as;
	double ms;
	double stunRes;
	double penetRate;
	double critDamage;
	double hit;
};

struct MonsterConfig
{
	int id;
	//int skill;
	int ai;
	int type;
	MonsterAttr attrs;
	int gatherMonsterType;
	int gatherTime;
	int shield;
	int waitGatherTime;
	int gsize;
};

class MonsterConfigPool 
{
public:
	static bool Load(GameConfigData* data);
	static const MonsterConfig* Get(int id);
	static bool LoadData(GameLuaConfig* data);
	static bool Reload();
private:
	static std::map<int, MonsterConfig> config_pool_;
	static GameLuaConfig lua_reader_;
};


