#ifndef _GAME_SERVER_H_
#define _GAME_SERVER_H_

#if (defined(WIN32) || defined(WINDOWS))
#else
//���ڻ�ȡ����IP
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
*��Ϸ��������
*���ϲ���࣬������������Ŀռ�
***************************************************************/

class GameServer
{
public:
	GameServer();
	~GameServer();

	//�����߼�������
	bool StartServer();
	//ֹͣ�߼�������
	void StopServer();

	//��ȡ����������
	inline const char* getServerName() { return srv_name_; }

	//���÷�����������
	inline void SetServerName(const char* sName)
	{
		_STRNCPY_A(srv_name_, sName);
#ifdef _MSC_VER
		SetConsoleTitle(srv_name_);
#endif
	}

	unsigned long long getUnixTime();

	/*
	* Comments: ���÷�������ID
	* int nServerIndex: ��������ID
	* Return void:
	*/
	inline void SetServerIndex(int sid) { srv_index_ = sid; }
	//���÷������Ŀ���ʱ��
	inline void SetServerOpenTime(SecondTime& time) { srv_open_t_ = time; }
	//��ȡ�������Ŀ���ʱ��
	inline SecondTime& GetServerOpenTime() { return srv_open_t_; }

	//��ȡ���ع�����
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

	//��ȡ�汾�Լ���Ӫ�̶������
	inline CVSPDefinition& GetVSPDefine() { return vsp_def_; }
	//��ȡ���԰�
	inline LangPack& GetLang() { return lang_; }

	void AddDbClient(int sid, const char* ip, int port, bool start);

	// 0����ͨ����1��ս������ 2����ս����
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
	static SimpleAllocCounter		sac_;		// ����һЩ�������ڴ�ط�����ڴ������
private:

	CVSPDefinition			vsp_def_;		//�汾�Լ���Ӫ�̳������ö���
	LangPack				lang_;		//���԰�
	GameGateMgr*			gate_mgr_;	//���ع�����
	LoginClient*			login_client_;		//�Ự�ͻ���
	ActorMgr*				acotr_mgr_;		//��½��֤������
	AsyncWorker*			async_work_;
	LogSender*				log_client_;		//��־�ͻ���
	CenterClient*			center_client_;
	GameConfigData*			config_data_;  // ����

	WatchThread				watch_thread_;	// ����߳�

	char					srv_name_[64];	//��Ϸ����������

	char					web_host_[256];
	int						web_port_;

	int						srv_index_;     //server index
	SecondTime				srv_open_t_;   //�������Ŀ�ʼʱ��
	bool					started_;		//�߼��������Ƿ��Ѿ�����

	// ������
	StaticHashTable<DBClient*, 4096>	dbclient_list_;	// ���ӵ�dbserver�����ӣ������ս����������ж������
	//GameSessionMgr*			game_conn_mgr_;	// gameworld���ӵĹ�����
	Vector<DBClientMgr*>	db_client_mgr_; // ����dbserver�Ĺ�����
	GameConnMgr*			game_conn_mgr_;	// gameworld���ӵĹ�����
	int						is_battle_srv_;		// �Ƿ�ս����

public:
	enum WatchID
	{
	    wiGame = 1,
	    wiActorMgr,
	};

	static const int MAX_DB_CLIENT_MGR_COUNT = 2;	// ����N���̹߳���dbclient
};


inline GameEngine* GetGameEngine() { return GameServer::Instance->Engine(); }
inline GameServer* ServerInstance() { return GameServer::Instance; }
//inline GameConfigData* GetConfData() { return GameServer::Instance->GetConfData(); }
inline int64_t GameTickCount() { return GameEngine::game_tick_; }

#define MEMCOUNTER(x, i) GameServer::MemCounter(sizeof(x), i); // i��Χ0-7
#endif

