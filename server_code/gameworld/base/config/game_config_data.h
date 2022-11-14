#ifndef _GAME_CONFIG_DATA_H_
#define _GAME_CONFIG_DATA_H_


/*******************************************************
*
*					逻辑数据配置提供类
*
   本类实现对游戏逻辑服务器运行中需要的各种游戏配置数据的读取以及管
* 理。例如各个等级的升级需求经验配置，货币上限配置，基础属性配置等。
*******************************************************/

class GameConfigData :
	public GameLuaConfig,
	ConfigLoader<GameConfigData>
{
public:
	typedef GameLuaConfig Inherited;
	GameConfigData();
	~GameConfigData();

	//加载所有基础配置
	bool LoadConfig();
	static const char IncludeFileName[];
protected:
	void showError(const char* err);

private:
	MemoryContainer<char>	alloc_;
};

#endif

