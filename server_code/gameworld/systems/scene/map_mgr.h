#pragma once

#include <map>


class GameMap;
class MapMgr :public Singleton<MapMgr>
{
public:
	friend Singleton<MapMgr>;
	MapMgr();
	~MapMgr();
	GameMap* GetMap(const char* name);
private:
	std::map<std::string, GameMap*> map_list_;
};