#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "os_def.h"
#include "lianfu/lf_netmsg_mgr.h"
#include "actor/global_mail_mgr.h"
#include "actor/tianti.h"
#include "../../common/redis/redis_def.h"

class EntityMgr;
struct GlobalVar;
class FuBenMgr;
class AiMgr;
class ActorAsynMgr;
class ActorDataMgr;
class RankingSystem;
class LoginQueue;
class GlobalMailMgr;
class Tianti;
class GuildMgr;
class CRedisConnect;

#define GLOBAL_TIME_FLUCTUATE	20
#define GLOBAL_WEE_HOURS_TIME (22 * 60 * 60)

static const char* loadpvmrankdata = "call loadpvmrankdata()";
static const char* loadpvmchallengerecord = "call loadpvchallengerecord()";

class GameEngine :
	public thread::BaseThread
{
public:
	typedef BaseThread Inherited;
	typedef struct stCampTipData
	{
		void*		m_data;
		size_t		m_nLen;
	} CampTipData;

	typedef struct stCrossServerInfo
	{
		int sid; //服务器id
		int sType; //服务类型
		stCrossServerInfo(int id, int type)
		{
			sid = id;
			sType = type;
		}
	}CrossServerInfo;

	friend class LoginQueue;
public:
	static int64_t			game_tick_;
	//全局功能脚本文件路径
	static const char*		GlobalScriptFile;

	//static const int MAX_SERVER_ID = 65535; //最多的服务器数量public:
	GameEngine();
	~GameEngine();

	//启动逻辑引擎
	bool StartEngine();
	//停止逻辑引擎
	void StopEngine();
	//是否启动完毕
	bool IsStarted() { return started_; }

	/*
	* Comments:提供接口给数据服务器连接调用，当连接上的时候
	* @Return void:
	*/
	void InitComponent()
	{
		//guildMgr_.Load();
		//consignmentMgr_.Load();
		//db_rank_mgr_.Load();
		//miscMgr_.Load();
		//fight_mgr_.Load();
		sysvar_mgr_.Load();
		//dym_item_conf.Load();
		//gamewar_mgr_.Load();
	}

	// 检查每个从数据库加载数据的模块，数据是否加载完全
	inline bool isInitComponentFinished()
	{
		return sysvar_mgr_.isLoad();
		/*return guildMgr_.isLoaded()
		       && consignmentMgr_.isLoaded()
		       && db_rank_mgr_.isLoaded()
		       && miscMgr_.isLoaded()
		       && fight_mgr_.isLoad()
		       && sysvar_mgr_.isLoad()
		       && gamewar_mgr_.isLoaded()
		       && dym_item_conf.isLoad();
			   */
	}

	void ClearAllInterMsg();
	void ClearAllGameRoute();

	inline EntityMgr* GetEntityMgr(void) { return entity_mgr_; }
	inline ActorAsynMgr* GetActorAsynMgr(void) { return actor_asyn_mgr_; }
	inline ActorDataMgr* GetActorDataMgr(void) { return actor_data_mgr_; }
	inline LoginQueue* GetLoginQueue(void) { return login_queue_; }
	inline RankingSystem* GetRankingSystem(void) { return ranking_system_; }
	inline GuildMgr* GetGuildMgr(void) { return guild_mgr_; }
	//inline CampMgr& GetCampMgr() { return camp_mgr_; }
	//inline ConsignmentMgr& GetConsignmentMgr(void) { return consignmentMgr_; }
	inline FuBenMgr* GetFuBenMgr(void) { return fuben_mgr_; }
	inline ScriptNpc* GetReserveNpc() { return globalFuncNpc_rese_; }
	inline ScriptNpc* GetGlobalNpc() { return globalFuncNpc_; }
	//inline RankingMgr& GetRankingMgr() { return rankingMgr_; }
	inline GlobalVarMgr& GetGlobalVarMgr() { return globalVarMgr_; }
	//inline DbRankMgr& GetDbRankMgr() { return db_rank_mgr_; }
	//inline TeamMgr& GetTeamMgr() { return teamMgr_;    //获取队伍管理器 }
	//inline MiscMgr& GetMiscMgr() { return miscMgr_; }
	inline MsgMgr& GetMsgMgr() { return msgMgr_; }
	inline Tianti& GetTianti(void) { return tianti_; }
	//inline DcApiMgr& GetDcApiMgr() { return dcapi_mgr_; }
	inline DKMLogMgr& GetDKMlogMgr() { return dkm_log_mgr_; }
	//inline DymItemConfig& getDymItemConf() { return dym_item_conf; }
	//inline GameWarMgr& GetGameWarMgr() { return gamewar_mgr_; }
	//inline FightMgr& GetFightMgr() { return fight_mgr_; }

	//申请用户物品对象，boGenNewSeries参数用于决定是否分配新的物品系列号
//#ifndef _MEMORY_TRACE_
//	inline ItemData* AllocUserItem(const bool isNew)
//	{
//		ItemData* item = isNew ? item_alloc_.allocItem() : item_alloc_.Alloc();
//		item->sign_data = NULL;
//		return item;
//	}
//	// 销毁用户物品
//	inline void DestroyUserItem(ItemData* item)
//	{
//		if (item->sign_data)
//		{
//			global_var_->sign_data_alloc_.release(item->sign_data);
//			item->sign_data = NULL;
//		}
//
//		item_alloc_.Free(item);
//	}
//#else
//#define AllocUserItem(isNew) _AllocUserItem(isNew, __FILE__, __LINE__)
//#define DestroyUserItem(ptr) _DestroyUserItem(ptr, __FILE__, __LINE__)
//
//	inline ItemData* _AllocUserItem(const bool isNew, const char* fn, int line)
//	{
//		ItemData* item = isNew ? item_alloc_._allocItem(fn, line) : item_alloc_._Alloc(fn, line);
//		//item->sign_data = NULL;
//		return item;
//	}
//
//	// 销毁用户物品
//	inline void _DestroyUserItem(ItemData* item, const char* fn, int line)
//	{
//		item_alloc_._Free(item, fn, line);
//	}
//#endif

//	inline int64_t AllocItemSeries() { return item_alloc_.allocSeries(); }

	/*
	* Comments: 创建脚本事件参数对象
	* Param EntitySCBHandle & handle: SCB句柄
	* @Return ScriptCallbackParam*:
	*/
	ScriptEvent* AllocScriptEvent(SEventHandle& handle);


	/*
	* Comments: 销毁脚本时间参数对象
	* Param EntitySCBHandle & handle:
	* @Return void:
	*/
	void FreeScriptEvent(SEventHandle& handle);


	/*
	* Comments: 获取脚本回调时间对象
	* Param const EntitySCBHandle & handle:
	* @Return ScriptCallbackParam*:
	*/
	ScriptEvent* GetScriptEvent(const SEventHandle& handle);

	//申请定时消息
	/*inline TimeCallMsg* AllocMonsterActionTimeCall()
	{
		return monsterActionCallAlloc_.Alloc();
	}
	//销毁定时消息
	inline void DestroyMonsterActionTimeCall(TimeCallMsg* pMsg)
	{
		monsterActionCallAlloc_.Free(pMsg);
	}*/

	//获取同步的系统逻辑日期和时间
	inline SystemTime& getSysTime() { return cur_sys_time_; }
	//获取同步的系统int64_t
	inline int64_t getTickCount() { return game_tick_; }
	//获取同步的逻辑短日期时间值
	inline unsigned int getMiniDateTime() { return now_sec_; }
	/*
	* Comments: 获取一个随机数，暂时用当前的滴答数量，这个可能还会修改
	* @Return int: 返回一个随机数
	*/
	inline unsigned int GetRandValue() { return wrandvalue(); }

	//返回ai管理器
	inline AiMgr* GetAiMgr() { return ai_mgr_; }

	//返回动作管理器
	//inline ActionMgr& GetActionMgr() { return action_mgr_; }

	// 返回系统变量管理器
	inline SysVarMgr& GetSysVarMgr() { return sysvar_mgr_; }
	//获取给脚本存储的动态数据
	inline CLVariant& GetDyanmicVar() { return dynamicVar_; }

	void SetGateMgr(GameGateMgr* gate_mgr) { gate_mgr_ = gate_mgr; }
	void PostMsg(GameInterMsg& msg);

	// 增加和删除频道的user,type 0 是增加， 1 是删除
	void ChannelUser(int channelId, int para, Actor* actor, int type = 0);
	/*
	* Comments:全局广播
	* Param int channelId:频道id
	* Param int para:附带参数，比如帮派id
	* Param const char * buf:数据内容
	* Param int len:
	* @Returns void:
	*/
	void BroadCast(int channelId, int para, const char* buf, size_t len);

	// 全服广播
	void BroadCast(const char* buff, size_t len);

	// 获取格式化后的数据，保存在buf中
	int FormatTipmsg(char* buf, int size, const char* msg, int tipType);

	/*
	* Comments: 全服发布公告
	* Param char * sTipmsg: tipmsg的指针
	* Param int nTipmsgType: 公告的显示类型，聊天栏，还是弹出框等
	* @Return void:
	*/
	void BroadcastTipmsg(const char* sTipmsg, int level, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:发布阵营的tipmsg
	* Param int nCampId:阵营的id
	* Param char * sTipmsg: 提示的类型
	* Param int nTipmsgType:提示的显示位置
	* @Return void:
	*/
	void BroadcastCampTipmsg(int nCampId, const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);
	/*
	* Comments:发布帮派的tipmsg
	* Param int nCampId:帮派的id
	* Param char * sTipmsg: 提示的类型
	* @Return void:
	*/
	void BroadcastGuildTipmsg(int guild, const char* sTipmsg);
	/*
	* Comments: 通过ID广播tipmsg
	* Param int nTipmsgID: 提示的ID
	* Param int nTipmsgType: 提示的内容
	* @Return void:
	*/
	void BroadcastTipmsgWithID(int nTipmsgID, int nTipmsgType = ttTipmsgWindow);

	// 阵营广播
	void BroadCampTipmsgWithParams(int camp, int tip, int type = ttTipmsgWindow, ...);
	// 帮派广播
	void BroadGuildTipmsgWithParams(int gid, int tip, int type = ttTipmsgWindow, ...);

	/*
	* Comments: 带参数全服广播
	* Param int nTipmsgID: 提示的ID
	* Param int nTipmsgType: 提示的显示类型
	* Param char * sParam1:参数1
	* Param char * sParam2:参数2
	* Param char * sParam3:参数3
	* @Return void:
	*/
	void BroadTipmsgWithParams(int tip, int type = ttTipmsgWindow, ...);

	/*
	* Comments:格式化系统提示的字符串,这个接口可以给外部使用
	* Param int nTipmsgID: 系统提示的ID
	* Param int nTipmsgType: 系统提示的类型
	* Param ...: 可变参数
	* @Return int: 返回数据长度
	*/
	int FormatTipmsg(int nTipmsgID, va_list& args, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments: 同阵营广播
	* Param int nOccupation: 阵营类型
	* Param char * pData: 广播数据
	* Param size_t size: 广播数据长度
	* @Return void:
	*/
	inline void BroadCastCamp(int camp, const char* data, size_t size)
	{
		//if (camp <= zyNone || camp >= zyMax) return;

		//BroadCast(ciChannelCamp, camp, data, size);
	}

	/*
	* Comments: 同帮派广播
	* Param int nOccupation: 阵营类型
	* Param char * pData: 广播数据
	* Param size_t size: 广播数据长度
	* @Return void:
	*/
	/*inline void BroadCastGuild(int guildid, const char* data, size_t size)
	{
		Guild* guild = guildMgr_.FindGuild(guildid);
		if (guild)
			guild->BroadCast(data, size, true);
		else
			BroadCast(ciChannelGuild, guildid, data, size);
	}*/

	/*
	* Comments: 广播阵营提示
	* Param const void * pData1:
	* Param size_t size1:
	* Param const void * pData2:
	* Param size_t size2:
	* Param const void * pData3:
	* Param size_t size3:
	* @Return void:
	* @Remark:
	*/
	inline void BroadCampTipmsg(CampTipData data[3])
	{
		//for (int i = 0; i < zyMax - 1; ++i)
		//{
		//	CampTipData* pData = &data[i];

		//	if (pData->m_data == NULL || pData->m_nLen <= 0) continue;

		//	BroadCast(ciChannelCamp, i + 1, (const char*)pData->m_data, (int)pData->m_nLen);
		//}
	}

	//获取广播数据的指针
	inline char* GetBroadcastDataPtr()
	{
		return broadcastBuff_;
	}

	// 设置某个网络消息是c++处理，还是lua处理，或是关闭系统，如果pid==0，表示sysid下所有都设置为val
	void SetNetMsgRoute(int sysId, int pid, int val);
	// 设置某个db返回消息是c++处理，还是lua处理
	void SetDbRetRoute(int sysid, int cmd, int val);
	// 定期内存释放
	void GC();
	void FreeMsgPack(GameInterMsg& msg);

	//void UpdateCrossGateway(DataPacket& dp);
	void SendActorCrossKey(DataPacket& dp, int sid, int loginType);

	void AddBattleSrv(int sid, int type)
	{
		if (!HasBattleSrv(sid))
		{
			CrossServerInfo info(sid, type);
			cross_server_list_.add(info);
		}
	}

	bool HasBattleSrv(int sid)
	{
		for (int i = 0; i < cross_server_list_.count(); ++i)
		{
			if (cross_server_list_[i].sid == sid)
				return true;
		}

		return false;
	}
	void RemoveBattleSrv(int sid)
	{
		for (int i = 0; i < cross_server_list_.count(); ++i)
		{
			if (cross_server_list_[i].sid == sid)
			{
				cross_server_list_.remove(i);
				return;
			}
		}
	}
	
	int GetSrvByType(int type)
	{
		for (int i = 0; i < cross_server_list_.count(); i++)
		{
			if (cross_server_list_[i].sType == type)
			{
				return cross_server_list_[i].sid;
			}
		}
		return 0;
	}

	void SetSrvType(int sid, int type)
	{
		for (int i = 0; i < cross_server_list_.count(); i++)
		{
			if (cross_server_list_[i].sid == sid)
			{
				cross_server_list_[i].sType = type;
				return;
			}
		}
	}


	// hdl是需要通知的玩家的handle，重刷完npc的脚本后会通知到这个玩家，type：0表示全局npc，1表示测试用的全局npc
	bool PostReloadGlobaNpc(EntityHandle hdl = 0, int type = 0);
	bool ReloadGlobalNpc(EntityHandle hdl = 0, int type = 0);

	/*
	* Comments:屏蔽一个字符
	* Param INOUT char * pInput:输入的字符串
	* @Return int:返回屏蔽了的字符的个数
	*/
	int Filter(char* pInput);

	/*
	* Comments: 一个字符串是否和谐
	* Param char * pInput:字符串指针
	* @Return bool:和谐返回true，否则返回false
	*/
	bool IsStrInvalid(char* pInput);

	bool ReloadFilterDb(); //重新装载屏蔽字符库

	// 单元测试
	void RunAllTests();

	GameRoute* GetGameRoute(int sid, bool create = false);

	inline LianfuMgr& GetLianfuMgr() { return lianfu_mgr_; }

	inline LianfuRank& GetLianfuRank() { return lianfu_rank_; }

	//inline LianfuGuild& GetLianfuGuild() { return lianfu_guild_; }

	LFNetmsgMgr& GetLFNetmsgMgr() { return lf_netmsg_mgr_; }

	inline SQLConnection* GetGlobalSqlConn() { return &global_sql_; }

	inline GlobalMailMgr* GetGlobalMailMgr(){ return &global_mail_mgr_; }
	bool StartOneGameClient(const char* ip, int port, int serverId, int serverType);
	void ResetGameRoute();
	void ResetSingleGameRoute(int sid);

	void GameInit();
protected:
	void OnRoutine();
	//单次逻辑处理
	void LogicRun();
	//检查全服事件刷新时间
	void CheckRefreshTime();

	void MiscRun();


	//逻辑引擎启动函数（由主逻辑线程启动时调用）
	void EngineStarted();
	//逻辑引擎停止函数（由主逻辑线程即将退出前调用）
	void EngineStoped();
private:
	//做全局变量的初始化工作
	void InitStaticVar();
	//释放程序中的全局变量
	void ReleaseStaticVar();

	void SetupSQLConnection(SQLConnection* sql);
private:
	//初始化保留场景 ???
	bool InitReserveScene();
	bool InitStaticFuben();
	//初始化保留NPC
	bool InitReserveNpc();
	bool LoadActorBasicData();
	// 设置线程的亲和度
	void ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);

	void OnAsynWorkerMsg(GameInterMsg& msg);

	void OnCrosswayKey(GameInterMsg& msg);

	//void OnGameSessionGw(GameInterMsg& msg);

	void OnGameSessionReg(GameInterMsg& msg);
	void OnGameClientResp(GameInterMsg& msg);
	void OnCloseActorById(GameInterMsg& msg);

	void OnGatewayDump(GameInterMsg& msg);
	void OnDbServerMsg(GameInterMsg& msg);
	void OnActorLogout(GameInterMsg& msg);
	//void OnActorLogin(GameInterMsg& msg);	//旧版， 走内部消息流程
	void ActorLogin(GateUser* user, int serverId, const char* pf, const char* pfid, const char* appid); //改为走登陆队列流程
	void OnCreateImageActor(GameInterMsg& msg);
	void OnCrossWarMsg(GameInterMsg& msg);
	void OnCenterServerMsg(GameInterMsg& msg);
	void OnRunAllTests(GameInterMsg&);

	void OnCrossServerTtMsg(GameInterMsg& msg);
	void OnChangeUserName(GameInterMsg& msg);
	void OnCrossRelogin(GameInterMsg& msg);
public:
	static CTimeStatisticMgr*		timeStatisticMgr_;     //时间统计组件
	static GlobalVar*				global_var_;
	// 网络消息转发的标志，如果是1表示关闭，0表示c++处理，否则都是lua处理
	char							net_msg_route[256][256];
	// db返回消息处理标志 0表示c++处理，否则都是lua处理
	char							db_ret_route[256][256];

	static void PostMsgToGE(void* cb);	// 给asyncworker回调的函数
	static void AsyncWorkLuaCallback(void* cb);	// asyncworkder执行完后的回调函数

public:
	/*
	* Comments:能够实现参数格式化功能的发送系统提示消息
	* Param const char* sFormat: 消息格式
	* Param int nType:  系统提示显示的类型
	* @Return void:
	*/
	void SendTipmsgWithArgs(ActorId sActorId, const char* fmt, va_list& args, int type);

	// 发送消息给某个玩家，可以在连服的其它服
	void SendTipmsg(ActorId sActorId, const char* sTipmsg, int type = ttTipmsgWindow);

	void SendTipWithId(ActorId sActorId, int msgid, int type = ttTipmsgWindow, ...);

	// 发送检查有效性标识到DBServer
	void SendEnableCheckValid(bool flag);

	void ChangeToOnlineList(DataPacket& pack);
	//根据玩家id 返回该玩家在哪个服务器
	int GetActorInServerId(ActorId aid);

	void SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw);

	bool AddRoutes(int serverid, const char* host, int port);
	bool HasRoute(int serverId);

	void OnAddLoginList(GameInterMsg& msg);

	void SetRedisCfg(const char* host, int port, int db_index, const char* pw);

	std::shared_ptr<CRedisConnect> GetRedis() { return global_redis_; }

private:

	bool				started_;

	SystemTime			cur_sys_time_;			//当前系统日期和时间，每个循环更新一次
	GameGateMgr*		gate_mgr_;
	EntityMgr*			entity_mgr_;
	ActorAsynMgr*		actor_asyn_mgr_;	// 异步回调管理器
	ActorDataMgr*		actor_data_mgr_;	// 玩家数据管理
	LoginQueue*			login_queue_;		// 登陆队列
	RankingSystem*		ranking_system_;		// 排行榜系统
	GuildMgr*			guild_mgr_;			// 公会系统
	//ConsignmentMgr		consignmentMgr_;
	//RankingMgr			rankingMgr_;	//排行榜管理器
	//CampMgr		camp_mgr_;
	GlobalVarMgr		globalVarMgr_;
	//DbRankMgr			db_rank_mgr_;
	//MiscMgr				miscMgr_;
	MsgMgr				msgMgr_;
	//DymItemConfig		dym_item_conf;

	FuBenMgr*			fuben_mgr_;
	SecondTime			now_sec_;		//当前短日期时间
	SecondTime			EventRefreshTime_;	// 用于22点的刷新处理（活动、任务等逻辑）

	//TeamMgr				teamMgr_; //队伍管理器
	//ItemAllocator		item_alloc_;	//用户物品申请器

	//ObjPool<TimeCallMsg> monsterActionCallAlloc_; //怪物动作定时调用

	GameMap				reserveMapData_;//保留场景的地图数据
	Scene*				reserveScene_;//保留场景，用于存放保留NPC
	ScriptNpc*			globalFuncNpc_;	//执行全局的脚本函数
	ScriptNpc*			globalFuncNpc_rese_;

	AiMgr*               ai_mgr_; //ai管理器
	//FightMgr			fight_mgr_; //竞技场管理器

	SysVarMgr			sysvar_mgr_;

	CLVariant			dynamicVar_;		//一个用来给脚本保存全局变量数据的变量，数据不保存db

	QueueList<GameInterMsg>	inter_msg_;		//内部消息列表
	Mutex				inter_msg_lock_;		//内部消息列表锁

	char				broadcastBuff_[4096]; //广播消息用的
	//ActionMgr			action_mgr_;	// 动作管理器

	Timer				engine_report_t_;	// 检查游戏主线程的数据库是否阻塞
	Timer				engine_60s_t_; // 定时执行event计时器
	Timer				engine_5s_t_; // 定时执行event计时器
	Timer				gc_t_;			// 定期释放内存的计时器

	//DcApiMgr			dcapi_mgr_;
	DKMLogMgr			dkm_log_mgr_;
	//GameWarMgr			gamewar_mgr_;
	LianfuMgr			lianfu_mgr_;
	LianfuRank			lianfu_rank_;
	//LianfuGuild			lianfu_guild_;
	LFNetmsgMgr			lf_netmsg_mgr_;	//todo 以后改成连服的那个版本
	// 跨服相关
	// 保存每个连接过来的gameworld的gateway的信息
	container::StaticArrayList<GameRoute*, MAX_SERVER_ID> gateway_routes_;

	Vector<CrossServerInfo, 4>		cross_server_list_;		// 战斗服的id列表
	ScriptEventHdlMgr		se_hdl_mgr_;	// 实体脚本回调事件句柄管理器

	PFT_MBCS_CHAR				filterWords_;		//屏蔽词列表

	char			db_host_[128];			//数据库地址
	int				db_port_;				//数据库端口
	char			db_name_[128];			//数据库名称
	char			db_user_[128];			//数据库用户名
	char			db_pw_[128];			//数据库用户密码

	SQLConnection			global_sql_;

	
	std::shared_ptr<CRedisConnect> global_redis_;

	GlobalMailMgr			global_mail_mgr_; //全服邮件管理器
	Tianti					tianti_;  //天梯

public:
	// 这里出现的基本是调试用的，随时可以删除
	bool				script_5s_timer_;	// 是否触发5s的

	int					gc_actor_cnt_;		// 触发gc的在线人数

	container::StaticHashTable<int, 4096 * 4> actor_online_list_;//玩家在线信息
};

struct ActorIdPacket
{
	Actor* actor_; // 目标玩家的指针
	ActorId actor_id_;
	DataPacket dp_;

	ActorIdPacket();

	DataPacket& AllocIdPacket(ActorId aid, Actor* actor = NULL);
	void flush();

	static const int HEAD_SIZE = sizeof(int) + sizeof(ActorId);
};

#endif

