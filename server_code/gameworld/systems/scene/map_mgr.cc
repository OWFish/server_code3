#include "StdAfx.h"
#include "map_mgr.h"
#include "gameMap/game_map.h"
#include "utils/fdop.h"
#include "share_util.h"


#define MAPFILEEXT ".mmap"


MapMgr::MapMgr()
{
}

MapMgr::~MapMgr()
{
	for (auto it(map_list_.begin()); it != map_list_.end(); ++it)
	{
		SafeDelete(it->second);
	}
}

GameMap* MapMgr::GetMap(const char* name)
{
	if (!name) return NULL;

	auto it = map_list_.find(name);
	if (it != map_list_.end())
		return it->second;


	char map_name[256]; //地图文件的全名
	bool newver = true;
	SNPRINTFA(map_name, sizeof(map_name), "data/map/%s/mdata.txt", name);

	if (!FDOP::FileExists(map_name))
	{
		SNPRINTFA(map_name, sizeof(map_name), "data/map/%s%s", name, MAPFILEEXT);
		newver = false;
	}

	GameMap* map = new GameMap();

	if (!map->LoadFromFile(map_name, newver))
	{
		delete map;
		return NULL;
	}

	map_list_[name] = map;
	return map;
}
