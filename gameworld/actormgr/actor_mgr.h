#ifndef _ACTOR_MGR_H_
#define _ACTOR_MGR_H_

#include <map>
#include <string>
#include "actor/tianti_mgr.h"

//这里是定义返回给客户端的错误码，均要小于0,1字节
#define	NOERR					0		//正确
#define	ERR_SQL					-1		//sql错误
#define	ERR_SESS				-2		//用户没登陆
#define ERR_GAMESER				-3		//游戏服务没准备好
#define	ERR_DATASAVE			-4		//角色上一次保存数据是否出现异常
#define ERR_SELACTOR			-5		//客户端选择角色的常规错误
#define ERR_SAMENAME			-6		//角色名称重复
#define ERR_NOUSER				-7		//角色不存在
#define ERR_SEX					-8		//错误的性别
#define ERR_NORANDOMNAME		-9		//随机生成的名字已经分配完
#define ERR_ZY					-10		//客户端上传的角色阵营参数错误
#define ERR_JOB					-11		//客户端上传的角色职业参数错误
#define ERR_NAME				-12		//名称无效，名称中包含非法字符或长度不合法
#define ERR_GUID				-13		//如果玩家是帮主，不能删除该角色，需要玩家退帮
#define ERR_CROSSWAR			-14		//已经登陆到其他服务器
#define ERR_MAXACTOR			-15		//已经超过最大可建角色数量

/** Session服务器操作返回值定义 **/
typedef enum tagSessionServerOPError
{
	enSuccess = 0,	     //操作成功
	enPasswdError = 1,   //密码错误
	enNoAccount = 2,     //没有这个账号
	enIsOnline = 3,      //已经在线
	enServerBusy = 4,    //服务器忙
	enServerClose = 5,   //服务器没有开放
	enSessionServerError = 6 , //session服务器有问题，比如db没有连接好
	enServerNotExisting = 7, //不存在这个服务器
	enFcmLimited = 8 ,     //账户纳入防沉迷
	enBanTime = 9,     //封号时间
} SESSION_SERVER_OPERROR;


using namespace thread;


//#define MAX_ACTOR_CREATE (1 << 19)
#define MAX_ACTOR_CREATE ((1 << 16) - 1) //为了扩展服务器id,缩减最大创角数
#define MAX_SERVER_ID ((1 << 16) -1) //服务器id最大值 

class ActorMgr: public thread::BaseThread
{
public:
	typedef BaseThread Inherited;

	typedef struct tagGameServerRoute
	{
		int		nServerIndex;	//服务器ID
		int		nRouteCount;	//路由地址数量
		struct
		{
			char	sHost[124];	//服务器地址（支持域名）
			int		nPort;		//服务器端口
		}	RouteTable[16];		//路由地址表
	} GAMESERVERROUTE, *PGAMESERVERROUTE;

	enum
	{
	    imReloadScript = 1,	// 重新读入脚本
	    imReloadFilterName = 2,	// 读过滤字库
		imCloseUser = 3,		// 在gameengine中玩家退出
		imAddKey,		// 增加跨服登陆的key
		imGetKeyResp,	// 收到跨服登录key的应答

		imAddOnline,		// 增加在线的玩家数据
		imBatchOnline,		// 批量同步在线玩家数据
		imRemoveOnline,		// 删除在线的玩家

		imAddGameClient,
		imBroadCast,
		imUserChange,

		imDelGameClient,	//断开一个连接的gameclient

		imCloseUserInActorMgr, //在actormgr中玩家退出
		imChangeUserName, //改名
	};
	// 改名方式
	enum
	{
		cnwNormal = 0, // 指定名字
		cnwRandom = 1, // 随机名字, 用于修复玩家名字含特殊字符问题
	};

	struct NameSortItem
	{
		SrvDef::ACTORNAME name_;

		inline bool operator != (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) != 0;
		}
		inline bool operator > (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) > 0;
		}
		inline bool operator < (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) < 0;
		}
	};
	struct ActorSortItem
	{
		int	accountId_;
		NetId netId_;

		inline bool operator !=(const ActorSortItem& data) const
		{
			return accountId_ != data.accountId_;
		}
		inline bool operator >(const ActorSortItem& data) const
		{
			return accountId_ > data.accountId_;
		}
		inline bool operator <(const ActorSortItem& data) const
		{
			return accountId_ < data.accountId_;
		}
	};

	struct CrossUserData
	{
		int serverId_;
		ActorId actorId_;
		int accountId_;
		char account_name_[128];
		int fcm_;			// 已经无用
		bool gm_;
		char key_[64];
		int target_sid_;	// 期望跳转的serverid，这个是用来做验证的
		time_t time_out_;
		//int cross_type_;	// 跳转服务器的类型

		CrossUserData() : serverId_(0), actorId_(0), accountId_(0),
			fcm_(0), gm_(false), target_sid_(0),time_out_(0)
		{
			account_name_[0] = 0;
			key_[0] = 0;
		}
		inline bool operator != (const CrossUserData& data) const
		{
			return actorId_ != data.actorId_;
		}
		inline bool operator > (const CrossUserData& data) const
		{
			return actorId_ > data.actorId_;
		}
		inline bool operator < (const CrossUserData& data) const
		{
			return actorId_ < data.actorId_;
		}
	};

	typedef container::BinaryList<CrossUserData> KeyList;

	struct OnlineUserData
	{
		int serverId_;
		ActorId actorId_;

		OnlineUserData() : serverId_(0), actorId_(0)
		{
		}
		inline bool operator != (const OnlineUserData& data) const
		{
			return actorId_ != data.actorId_;
		}
		inline bool operator > (const OnlineUserData& data) const
		{
			return actorId_ > data.actorId_;
		}
		inline bool operator < (const OnlineUserData& data) const
		{
			return actorId_ < data.actorId_;
		}
	};

	typedef container::BinaryList<OnlineUserData> OnLineList;

	enum
	{
		cUserPw = 1,
		sUserPw = 1,

	    cCreateActor = 2,
	    sCreateActor = 2,

	    cDelete = 3,
	    sDelete = 3,

	    cQueryList = 4,
	    sQueryList = 4,

	    cEnterGame = 5,
	    sEnterGame = 5,

	    cRandName = 6,	//自动生成名字
	    sRandName = 6,

	    cLessJob = 7,		//查询最少人使用的职业
	    sLessJob = 7,

	    cLessCamp = 8,		//查询最少人使用的阵营
	    sLessCamp = 8,

		cCrossKey = 9,		// 跨服登陆验证key
		sCrossKey = 9,		


	};

public:
	bool StartActorMgr();
	virtual void Stop();


	static int GetStrLenUtf8(const char* sName);

	static const char* LowerCaseNameStr(char* sNameStr);
	void PostMsg(GameInterMsg& msg)
	{
		inter_msg_.append(msg);
	}
public:
	ActorMgr(GameGateMgr* gate_mgr);
	virtual ~ActorMgr();

	void ProcessNetMsg(DataPacket& packet, int gate_idx);
	//void FlustFree();

	// 配置
	void SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw);

	// 检查名字的合法性
	bool CheckNameStr(const char* sNameStr);

	SQLConnection* GetDbConn()
	{
		return &sql_;
	}

	void SendToGate(NetId& netid, const char* buf, size_t size);
	bool NameHasUser(const char* name);
	int CreateActor(int accountid, const char* accountname, const char* name, int sex, int job,int headid, ActorId& actor_id, const char* pfid, GateUser* gateuser);
	const char* GetRandomName(int nSex);
	void EnterGame(GateUser* user, ActorId actor_id, const char* pf, const char* pfid, const char* appid, int serverId);

	int ChangeActorName(ActorId actor_id, const char* name, const char* rawName);

	// kicknow表示如果玩家在其他战斗服，是否现在就踢下线
	bool IsLoginBattle(ActorId actorid, bool kickNow = true);

	int IsLogOutBattle(ActorId actorid);

	ActorMgrAlloc& GetAlloc()
	{
		return key_data_alloc_;
	}

	/*AlignAllocator& GetPfAlloc()
	{
		return pf_str_alloc_;
	}*/

	static void GenerateKey(char* buf, int size);

	int LoginOtherSrv(GateUser* user, int sid, ActorId aid, bool newpos = false, unsigned int fbhdl = 0, int sceneid = 0, int x = 0, int y = 0, const char* reason = "");

	bool HasGameClient(int sid);
	void SetupSQLConnection(SQLConnection* sql);
protected:
	void OnRoutine();
	//单次逻辑处理
	void Run();
	void OnStart();
	void OnStop();

	bool ConnectSQL();

private:
	void CheckUserPw(GateUser* user, DataPacket& packet);

	void SendPwResult( int ret, GateUser* user );

	int NameHasUserFromLasts(const char* name);

	bool LoadFilterNames();

	void FreeFilterWords();

	bool LoadNameData();
	bool LoadOldActorNameData();

	

	// 读取跨服战的战斗的名字的列表
	bool LoadCrossWarTeamName();
	// 给本线程发送消息的函数
	void ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);
	int GetOnlinePos(int accountid);

	// 检查跨服的key
	void CheckCrossKey(GateUser* user, DataPacket& pack);
	bool GetCrossKeyData(ActorId aid, CrossUserData& data);
	void AddCrossKey(CrossUserData& data);
	void AddOnline(int serverid, ActorId aid);
	void RemoveOnline(ActorId aid);
	void AddBatchOnline(DataPacket& dp);
	void DealKeyResp(CrossUserData& data, int loginType);
	//void OnRecvGameMsg(int cmd, DataPack& pack, GameClient* gc);
	//void OnRegist(DataPack& pack, GameClient* gc);

	//// 检查是否已经有这个gameworld的连接
	//void HasGameWorld(int sid);

	void ClearGameClient();
	void DelGameClient(int sid);

	bool AddGameClient(const char* ip, int port, int serverId);
	void SendMsgToAllGameClient(int cmd, void* buf, size_t size, int sid);

	GateUser* GetGateUserByActor(ActorId id);

	// 加载允许字符范围列表
	bool LoadAllowWords();
	// 检查是否合法是名字，是则返回true
	bool CheckAllowWord(const char* sName);
	// 解析允许字符
	bool ParseAllowWord(char* sText);
private:
	GameGateMgr*			gate_mgr_;

	SQLConnection			sql_;
	time_t					reconnect_t_;
	time_t					report_t_;
	PFT_MBCS_CHAR			filter_words_;
	Mutex					filter_lock_;	// 字库要加锁，因为有多个线程会访问
	bool					allow_words_[0xffff]; // 允许使用的字符

	RandNameList			def_names_;
	RandNameList			char_names_;

	BinaryList<NameSortItem, 10240>	all_actor_name_;
	BinaryList<ActorSortItem, 4096>	online_list_;

	time_t					next_ping_t_;

	char			db_host_[128];			//数据库地址
	int				db_port_;				//数据库端口
	char			db_name_[128];			//数据库名称
	char			db_user_[128];			//数据库用户名
	char			db_pw_[128];			//数据库用户密码

	static int		actorid_series_;

	// 使用lua脚本功能
	CVSPDefinition	vsp_def_;
	BaseScript		script_;

	QueueList<GameInterMsg>	inter_msg_;		//内部消息列表
	Mutex				inter_msg_lock_;		//内部消息列表锁

	// 跨服
	KeyList				key_list_;
	time_t				check_key_t_;

	ActorMgrAlloc		key_data_alloc_;
	//StrAlloc			pf_str_alloc_;

	OnLineList					battle_online_list_;		// 已经登陆了其他服的玩家列表
	Vector<GameClient*>			game_client_list_;	// 连接战斗服的连接
	//CustomHashTable<ActorId> old_actor_name_;		// 玩家曾经用过的名称的列表
	std::map<std::string, int> old_actor_name_;

	struct ActorNetInfo
	{
		NetId netid;
		ActorNetInfo(){}
		ActorNetInfo(NetId& net_id)
		{
			netid = net_id;
		}
	};
	container::StaticHashTable<ActorNetInfo, 4096 * 2> actor_net_list_; //用于存放玩家的在线信息，比如在哪个服务其上
};

#endif



