#ifndef _GAME_SERVER_H_
#define _GAME_SERVER_H_

#if (defined(WIN32) || defined(WINDOWS))
#else
//用于获取本机IP
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#endif
#include <time.h>

using namespace InterSrvComm::GameWorldProto;

class GameEngine;
class GameGateMgr;
class LoginClient;
class DBClient;
class GameConfigData;
class ActorMgr;
class CVSPDefinition;
class LangPack;

/***************************************************************
*游戏服务器类
*最上层的类，负责各个部件的空间
***************************************************************/

class GameServer
{
public:
	GameServer();
	~GameServer();

	//启动逻辑服务器
	bool StartServer();
	//停止逻辑服务器
	void StopServer();

	//获取服务器名称
	inline const char* getServerName() { return srv_name_; }

	//设置服务器的名字
	inline void SetServerName(const char* sName)
	{
		_STRNCPY_A(srv_name_, sName);
#ifdef _MSC_VER
		SetConsoleTitle(srv_name_);
#endif
	}

	unsigned long long getUnixTime();

	/*
	* Comments: 设置服务器的ID
	* int nServerIndex: 服务器的ID
	* Return void:
	*/
	inline void SetServerIndex(int sid) { srv_index_ = sid; }
	//设置服务器的开区时间
	inline void SetServerOpenTime(SecondTime& time) { srv_open_t_ = time; }
	//获取服务器的开区时间
	inline SecondTime& GetServerOpenTime() { return srv_open_t_; }

	//获取网关管理器
	inline GameGateMgr* GetGateManager() { return gate_mgr_; }
	inline LogSender* GetLogClient() { return log_client_; }
	inline int GetServerIndex() { return srv_index_; }
	inline GameEngine* Engine() { return GEngine_; }
	DBClient* GetDbClient(int sid = 0);
	//CenterClient* GetCenterClient() { return center_client_; }

	inline AsyncWorker* GetAsyncWorker() { return async_work_; }
	inline void SetAsyncWorker(AsyncWorker* worker) { async_work_ = worker; }
	inline GameConfigData* GetConfData() { return config_data_; }
	inline ActorMgr* GetActorMgr() { return acotr_mgr_; }

	//inline GameSessionMgr* GetGameSessionMgr() { return game_conn_mgr_; }
	inline WatchThread* GetWatch() { return &watch_thread_; }

	//获取版本以及运营商定义对象
	inline CVSPDefinition& GetVSPDefine() { return vsp_def_; }
	//获取语言包
	inline LangPack& GetLang() { return lang_; }

	void AddDbClient(int sid, const char* ip, int port, bool start);

	// 0：普通服，1：战斗服， 2：主战斗服
	void SetBattleSrvFlag(int flag)
	{
		//assert(is_battle_srv_ == bsCommSrv);
		is_battle_srv_ = flag;
	}

	inline int GetBattleSrvFlag() { return is_battle_srv_; }
	inline bool IsBattleSrv() { return is_battle_srv_ > bsCommSrv && is_battle_srv_ <= bsLianFuSrv; }
	inline bool IsLianFuSrv() { return is_battle_srv_ == bsLianFuSrv; }
	inline bool IsCommonSrv() { return is_battle_srv_ == bsCommSrv; }
	inline bool IsCrossWarSrv() { return is_battle_srv_ >= bsBattleSrv && is_battle_srv_ <= bsMainBattleSrv; }

	void SendMsgToAllGameClient(const void* buff, size_t size, int cmd, int sid, int cross_method = CROSSSERVER_ALL);

	void printAllDbClient();

	void SetWebServer(const char* host, int port)
	{
		_STRNCAT_A(web_host_, host);
		web_port_ = port;
	}
	const char* GetWebServer(int& port)
	{
		port = web_port_;
		return web_host_;
	}

	static size_t MemCounter(size_t s, int idx) { return sac_.counter(s, idx); }
	inline GameConnMgr* GetGameConnMgr() {
		return game_conn_mgr_;
	}
public:
	GameEngine* GEngine_;
	static GameServer* Instance;
	static SimpleAllocCounter		sac_;		// 计算一些不是用内存池分配的内存的数量
private:

	CVSPDefinition			vsp_def_;		//版本以及运营商常量配置定义
	LangPack				lang_;		//语言包
	GameGateMgr*			gate_mgr_;	//网关管理器
	LoginClient*			login_client_;		//会话客户端
	ActorMgr*				acotr_mgr_;		//登陆验证管理器
	AsyncWorker*			async_work_;
	LogSender*				log_client_;		//日志客户端
	CenterClient*			center_client_;
	GameConfigData*			config_data_;  // 配置

	WatchThread				watch_thread_;	// 监控线程

	char					srv_name_[64];	//游戏服务器名称

	char					web_host_[256];
	int						web_port_;

	int						srv_index_;     //server index
	SecondTime				srv_open_t_;   //服务器的开始时间
	bool					started_;		//逻辑服务器是否已经启动

	// 跨服相关
	StaticHashTable<DBClient*, 4096>	dbclient_list_;	// 连接到dbserver的连接，如果是战斗服，则会有多个连接
	//GameSessionMgr*			game_conn_mgr_;	// gameworld连接的管理类
	Vector<DBClientMgr*>	db_client_mgr_; // 连接dbserver的管理器
	GameConnMgr*			game_conn_mgr_;	// gameworld连接的管理类
	int						is_battle_srv_;		// 是否战斗服

public:
	enum WatchID
	{
	    wiGame = 1,
	    wiActorMgr,
	};

	static const int MAX_DB_CLIENT_MGR_COUNT = 2;	// 创建N个线程管理dbclient
};


inline GameEngine* GetGameEngine() { return GameServer::Instance->Engine(); }
inline GameServer* ServerInstance() { return GameServer::Instance; }
//inline GameConfigData* GetConfData() { return GameServer::Instance->GetConfData(); }
inline int64_t GameTickCount() { return GameEngine::game_tick_; }

#define MEMCOUNTER(x, i) GameServer::MemCounter(sizeof(x), i); // i范围0-7
#endif

