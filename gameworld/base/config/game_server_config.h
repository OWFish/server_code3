#ifndef _GAME_SERVER_CONFIG_H_
#define _GAME_SERVER_CONFIG_H_

// 用来读取游戏服务器的配置，比如ip，端口等

class GameServer;

class GameServerConfig :
	public GameLuaConfig
{
public:
	typedef GameLuaConfig Inherited;
	static const char ConfigFileName[];	//定义配置文件名称

public:
	GameServerConfig();
	~GameServerConfig();

	//加载并读取服务器服务配置
	bool loadServerConfig(GameServer *game_srv);

protected:
	void showError(const char* err);
	bool throwLoadConfig(GameServer *game_srv);
	//读取服务器服务配置
	bool readServerConfig(GameServer *game_srv);
};

#endif

