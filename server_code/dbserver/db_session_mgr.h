#ifndef _DB_CLIENT_MGR_H_
#define _DB_CLIENT_MGR_H_
#ifndef _MSC_VER
#include <pthread.h>
#endif
class DBServer;
class DBSession;
class DBTables;

class DBSessionMgr
	: public ServerSocket
{
public:
	typedef ServerSocket Inherited;

	enum RankMsg
	{
	    rmRefeshRank = 2000,	// 更新排行榜数据
	    rmNewServer = 2001,
	    rmCloseServer = 2002,
		//rmReloadScript = 2003,	// 重新读入脚本
		rmWaitForLogin = 2004,		// 等待登陆
		rmSetCacheSaveTime = 2005,	// 随机设置缓存下次存储时间
	};
	struct RankInterMsg
	{
		int msg_;
		int param1_;
	};

public:
	DBSessionMgr(DBServer* db_srv);
	~DBSessionMgr();

	inline DBServer* GetDBServer()
	{
		return db_srv_;
	}

	// 检查逻辑服务器是否已经连接上来
	bool GetGameReady(int srv_id);

	WatchThread* GetWatch() { return &watch_thread_; }
	DBDataCache* GetCache() { return &cache_; }
	void LockCache(){cache_lock_.Lock();}
	void UnLockCache(){cache_lock_.Unlock();}
	// 判断是否跨服战期间
	bool IsBattleTime();
	
	void SetRankRefresh(bool flag);
	bool GetRankRefresh(){return rank_refresh_;}

protected:
	//覆盖创建连接对象的函数
	NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);
	//覆盖销毁一个已经建立的客户端对象
	void DestroySession(NetSession* client);
	//覆盖父类处理客户端连接的函数
	void ProcessClients();
	//覆盖分派内部消息处理的函数
	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);
	//覆盖当客户端连接处理线程停止前调用函数
	void OnServerStart();
	void OnServerStop();
	//覆盖父类例行执行函数
	void SingleRun();
	//覆盖父类调用例行RUN的函数
	void OnRun();
private:
	bool ConnectSQL();
	//处理已经关闭的数据客户端对象
	void ProcessClosedClients();
	//判断是否所有数据数据均已处理完毕以便安全的停止服务
	bool AllDataProcessed();
	//强制释放所有客户端连接占用的内存（销毁连接对象）
	void FreeAllClient();
//#ifdef _MSC_VER
//	static void STDCALL RankThread(DBSessionMgr* ptr);
//#else
//	static void* RankThread(void* ptr);
//#endif
//	static void RankThread2(DBSessionMgr* server);
private:
	static			DBServer*					db_srv_;
	SQLConnection				sql_;
	time_t						next_conn_db_t_;//下次重新连接数据的时间
	Vector<DBSession*>			close_list_;	//已经关闭的数据客户端列表
	time_t						next_delete_t_;//下次从数据库中删除作废数据的时间
	time_t						next_day_delete_t_;//每天清除数据
	time_t                      next_dmp_t_;     //下次dmp的时间
	time_t						next_ping_t_;

	// 排行榜相关
	SQLConnection				rank_sql_;
	bool						rank_runing_;	//是否停止工作线程
	bool						rank_free_;
	bool						rank_refresh_;	//是否刷新排行榜
#ifdef _MSC_VER	
	HANDLE						rank_hdl_;
#else
	pthread_t					rank_hdl_;
#endif

	WatchThread					watch_thread_;	// 监控线程

// 缓存相关
	DBDataCache					cache_;			// 角色缓存数据
	Mutex						cache_lock_;

public:
	static bool					s_checkValid;					// 是否启用检查数据有效性
};

#endif

