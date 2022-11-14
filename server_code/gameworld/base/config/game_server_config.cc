#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include <iostream>
const char GameServerConfig::ConfigFileName[] = ("GameWorld.txt");

GameServerConfig::GameServerConfig()
	: Inherited()
{

}

GameServerConfig::~GameServerConfig()
{

}

void GameServerConfig::showError(const char* err)
{
	SetErrDesc(err);
	RefString s = ("[Config Error]");
	s += err;
	throw s;
}

bool GameServerConfig::loadServerConfig(GameServer* game_srv)
{
	
	bool boResult = false;
	OutputMsg(rmTip, ("loading server config"));

	try
	{
		boResult = throwLoadConfig(game_srv);
	}
	catch (RefString& s)
	{
		OutputMsg(rmError, (const char*)s);
	}
	catch (...)
	{
		OutputMsg(rmError, ("unexpected error on load - read ServerConfig "));
	}

	OutputMsg(rmTip, ("load server config complete"));
	return boResult;
}

bool GameServerConfig::throwLoadConfig(GameServer* game_srv)
{
	stream::MemoryStream ms(NULL);
	
	if (ms.loadFromFile(ConfigFileName) <= 0)
	{
		showErrorFormat(("unable to load from %s"), ConfigFileName);
		return false;
	}

	if (!setScript((char*)ms.getMemory()))
		return false;
	
	return readServerConfig(game_srv);
}

bool GameServerConfig::readServerConfig(GameServer* game_srv)
{
	
	if (!openGlobalTable("GameServer"))
		return false;

	if (!FDOP::FileExists("./runtime/"))
	{
		FDOP::DeepCreateDirectory("./runtime/");
	}

	const char* str = NULL;
	char server_name[64]; //

	//服务器名字和index
	getFieldStringBuffer("ServerName", server_name, ArrayCount(server_name)); //name

	SystemTime st; //服务器的开启时间
	GetSystemTime(st);
	//const char* sName = getFieldString("ServerOpenTime", "", &IsValid);
	int st_ok = false;
	FILE* fp = fopen("./runtime/opentime.txt", "r");

	if (fp)
	{
		char content[256];
		memset(content, 0, sizeof(content));
		fgets(content, 256, fp);

		if (strlen(content) > 10)
		{
			sscanf(content, "%d-%d-%d %d:%d:%d", &st.year_, &st.mon_, &st.mday_, &st.hour_, &st.min_, &st.sec_);
			OutputMsg(rmError, "open server time is : %d-%d-%d %d:%d:%d", st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_);
			st_ok = true;
		}

		fclose(fp);
	}

	if (!st_ok)
	{
		FILE* fp = fopen("./runtime/opentime.txt", "w");

		if (fp)
		{
			char content[256];
			memset(content, 0, sizeof(content));
			SNPRINTFA(content, sizeof(content), "%d-%d-%d %d:%d:%d", st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_);
			OutputMsg(rmError, "open server time is : %d-%d-%d %d:%d:%d", st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_);
			fputs(content, fp);
			fclose(fp);
		}
	}

	SecondTime start_t;
	start_t.encode(st);

	int val = getFieldInt("ServerIndex"); //serverindex
	int server_id = val;

	if (game_srv)
	{
		game_srv->SetServerIndex(val);
		game_srv->SetServerName(server_name);
		game_srv->SetServerOpenTime(start_t); //设置开区时间

		BOOL IsValid = TRUE;
		const char* webHost = getFieldString("WebHost", "", &IsValid);
		char szHost[256];

		if (IsValid && webHost != NULL)
		{
			_STRNCPY_A(szHost, webHost);
		}
		else
		{
			_STRNCPY_A(szHost, "localhost");
		}

		int def = 8080;
		int port = getFieldInt("WebPort", &def);
		game_srv->SetWebServer(webHost, port);
	}

	if (openFieldTable("SQL"))
	{
		char			db_host[128];			//数据库地址
		int				port;					//数据库端口
		char			db_name[128];			//数据库名称
		char			db_user[128];			//数据库用户名
		char			db_pw[128];		//数据库用户密码

		getFieldStringBuffer(("Host"), db_host, sizeof(db_host));
		port = getFieldInt("Port");
		getFieldStringBuffer(("DBName"), db_name, sizeof(db_name));
		getFieldStringBuffer(("DBUser"), db_user, sizeof(db_user));
		//char szTemp[100];
		//getFieldStringBuffer(("DBPass"), szTemp, sizeof(szTemp));
		//DecryptPassword(db_pw, sizeof(db_pw), (const unsigned char*)szTemp, (const unsigned char*)("This_AVC_GAME_fly"));
		getFieldStringBuffer(("DBPass"), db_pw, sizeof(db_pw));
		closeTable();//DB
		ActorMgr* mgr = game_srv->GetActorMgr();
		mgr->SetDbConfig(db_host, port, db_name, db_user, db_pw);
	}
	else
	{
		OutputMsg(rmError, "load db config error!");
		return false;
	}

	if (openFieldTable("GlobalSQL"))
	{
		char			db_host[128];			//数据库地址
		int				port;					//数据库端口
		char			db_name[128];			//数据库名称
		char			db_user[128];			//数据库用户名
		char			db_pw[128];		//数据库用户密码

		getFieldStringBuffer(("Host"), db_host, sizeof(db_host));
		port = getFieldInt("Port");
		getFieldStringBuffer(("DBName"), db_name, sizeof(db_name));
		getFieldStringBuffer(("DBUser"), db_user, sizeof(db_user));
		//char szTemp[100];
		//getFieldStringBuffer(("DBPass"), szTemp, sizeof(szTemp));
		//DecryptPassword(db_pw, sizeof(db_pw), (const unsigned char*)szTemp, (const unsigned char*)("This_AVC_GAME_fly"));
		getFieldStringBuffer(("DBPass"), db_pw, sizeof(db_pw));
		closeTable();//DB
		GameEngine* ge = game_srv->Engine();
		ge->SetDbConfig(db_host, port, db_name, db_user, db_pw);
	}
	else
	{
		OutputMsg(rmError, "load GlobalSQL config error!");
		return false;
	}
	
	if (openFieldTable("Redis"))
	{
		char			db_host[128];			//数据库地址
		int				port;					//数据库端口
		int				db_index;			//数据库索引
		char			db_pw[128];		//数据库用户密码

		getFieldStringBuffer(("Host"), db_host, sizeof(db_host));
		port = getFieldInt("Port");
		db_index = getFieldInt("ServerIndex");
		getFieldStringBuffer(("DBPass"), db_pw, sizeof(db_pw));
		
		GameEngine* ge = game_srv->Engine();
		ge->SetRedisCfg(db_host, port, db_index, db_pw);
		closeTable();
	}

	//网关服务配置
	if (openFieldTable("GateService"))
	{
		str = getFieldString("Address");
		val = getFieldInt("Port");

		if (NULL != str)
		{
			GameGateMgr* gate_mgr = game_srv->GetGateManager();
			gate_mgr->SetServiceHost(str);
			gate_mgr->SetServicePort(val);
		}

		closeTable();
	}
	else
	{
		OutputMsg(rmError, "load GateService config error!");
		return false;
	}

	//日志服务器地址配置
	if (openFieldTable("LogServer"))
	{
		str = getFieldString("Address");
		val = getFieldInt("Port");

		LogSender* log  = game_srv->GetLogClient();

		log->SetHost(str);
		log->SetPort(val);
		log->SetServerIndex(server_id);
		log->SetServerName(server_name);
		log->SetServerType(SrvDef::T_GameServer);

		closeTable();
	}
	else
	{
		OutputMsg(rmError, "load LogServer config error!");
		return false;
	}

	if (openFieldTable("CenterServer"))
	{
		/*str = getFieldString("Address");
		val = getFieldInt("Port");

		CenterClient* cli  = game_srv->GetCenterClient();

		cli->SetHost(str);
		cli->SetPort(val);
		cli->SetServerId(server_id);
		*/
		closeTable();
	}
	else
	{
		OutputMsg(rmError, "load CenterServer config error!");
		return false;
	}

	//数据client配置
	if (openFieldTable("DbServer"))
	{
		str = getFieldString("Address");
		val = getFieldInt("Port");

		//创建数据客户端
		game_srv->AddDbClient(game_srv->GetServerIndex(), str, val, false);
		closeTable();
	}
	else
	{
		OutputMsg(rmError, "load DbServer config error!");
		return false;
	}

	closeTable();
	return true;
}


