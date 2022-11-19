#pragma once

#include "config/game_config_data.h"
#include <map>
#include <unordered_map>

#define ROLE_JOB_COUNT 3
struct RoleAttrConfig
{
	int hp;
	int mp;
	int atk;
	int def;
	int res;
	int crit;
	int tough;
	int ms;
	int as;
	int acrit;
};
struct RoleAttrConfigs
{
	RoleAttrConfig attr[ROLE_JOB_COUNT];
	std::vector< std::unordered_map<int32_t, int32_t> > attr_dict;
	
	void init()
	{
		attr_dict.resize(ROLE_JOB_COUNT);
	}

/*---------------------------------------------------------*/
	RoleAttrConfigs();
	RoleAttrConfigs(const RoleAttrConfigs& attrs);
};

class RoleConfigPool
{
public:
	static bool Load(GameConfigData* data);
	static const RoleAttrConfig* Get(int level, int job);
	static const std::unordered_map<int,int>* GetAttrDict(int level, int job);

private:
	static std::map<int, RoleAttrConfigs> config_pool_;
};


