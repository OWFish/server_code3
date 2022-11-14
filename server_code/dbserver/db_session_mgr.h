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
	    rmRefeshRank = 2000,	// �������а�����
	    rmNewServer = 2001,
	    rmCloseServer = 2002,
		//rmReloadScript = 2003,	// ���¶���ű�
		rmWaitForLogin = 2004,		// �ȴ���½
		rmSetCacheSaveTime = 2005,	// ������û����´δ洢ʱ��
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

	// ����߼��������Ƿ��Ѿ���������
	bool GetGameReady(int srv_id);

	WatchThread* GetWatch() { return &watch_thread_; }
	DBDataCache* GetCache() { return &cache_; }
	void LockCache(){cache_lock_.Lock();}
	void UnLockCache(){cache_lock_.Unlock();}
	// �ж��Ƿ���ս�ڼ�
	bool IsBattleTime();
	
	void SetRankRefresh(bool flag);
	bool GetRankRefresh(){return rank_refresh_;}

protected:
	//���Ǵ������Ӷ���ĺ���
	NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);
	//��������һ���Ѿ������Ŀͻ��˶���
	void DestroySession(NetSession* client);
	//���Ǹ��ദ��ͻ������ӵĺ���
	void ProcessClients();
	//���Ƿ����ڲ���Ϣ����ĺ���
	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);
	//���ǵ��ͻ������Ӵ����߳�ֹͣǰ���ú���
	void OnServerStart();
	void OnServerStop();
	//���Ǹ�������ִ�к���
	void SingleRun();
	//���Ǹ����������RUN�ĺ���
	void OnRun();
private:
	bool ConnectSQL();
	//�����Ѿ��رյ����ݿͻ��˶���
	void ProcessClosedClients();
	//�ж��Ƿ������������ݾ��Ѵ�������Ա㰲ȫ��ֹͣ����
	bool AllDataProcessed();
	//ǿ���ͷ����пͻ�������ռ�õ��ڴ棨�������Ӷ���
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
	time_t						next_conn_db_t_;//�´������������ݵ�ʱ��
	Vector<DBSession*>			close_list_;	//�Ѿ��رյ����ݿͻ����б�
	time_t						next_delete_t_;//�´δ����ݿ���ɾ���������ݵ�ʱ��
	time_t						next_day_delete_t_;//ÿ���������
	time_t                      next_dmp_t_;     //�´�dmp��ʱ��
	time_t						next_ping_t_;

	// ���а����
	SQLConnection				rank_sql_;
	bool						rank_runing_;	//�Ƿ�ֹͣ�����߳�
	bool						rank_free_;
	bool						rank_refresh_;	//�Ƿ�ˢ�����а�
#ifdef _MSC_VER	
	HANDLE						rank_hdl_;
#else
	pthread_t					rank_hdl_;
#endif

	WatchThread					watch_thread_;	// ����߳�

// �������
	DBDataCache					cache_;			// ��ɫ��������
	Mutex						cache_lock_;

public:
	static bool					s_checkValid;					// �Ƿ����ü��������Ч��
};

#endif

