#ifndef _GAME_SERVER_CONFIG_H_
#define _GAME_SERVER_CONFIG_H_

// ������ȡ��Ϸ�����������ã�����ip���˿ڵ�

class GameServer;

class GameServerConfig :
	public GameLuaConfig
{
public:
	typedef GameLuaConfig Inherited;
	static const char ConfigFileName[];	//���������ļ�����

public:
	GameServerConfig();
	~GameServerConfig();

	//���ز���ȡ��������������
	bool loadServerConfig(GameServer *game_srv);

protected:
	void showError(const char* err);
	bool throwLoadConfig(GameServer *game_srv);
	//��ȡ��������������
	bool readServerConfig(GameServer *game_srv);
};

#endif

