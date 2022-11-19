#include "StdAfx.h"

bool DBSessionMgr::s_checkValid = true;

 DBServer* DBSessionMgr::db_srv_ = NULL;
DBSessionMgr::DBSessionMgr(DBServer* db_srv) : Inherited("DBClientMgr")
{
	db_srv_ = db_srv;
	SetServiceName("����");
	next_delete_t_ = 0;
	next_day_delete_t_ = 0;
	sql_.SetMultiThread(true);
	rank_sql_.SetMultiThread(true);
	next_dmp_t_ = 0;
	next_ping_t_ = 0;
	rank_refresh_ = false;

	sql_.SetLog(false);
	rank_sql_.SetLog(false);
#ifdef DB_UTF8
	sql_.SetUtf8(true);
	rank_sql_.SetUtf8(true);
#endif
}

DBSessionMgr::~DBSessionMgr()
{
}

NetSession* DBSessionMgr::NewSession(SOCKET socket, sockaddr_in* addrin)
{
	NetSession* ret = new DBSession(this, &sql_, socket, addrin);
	ret->UseBaseAlloc(true);
	ret->setRecvBufSize(8 * 1024 * 1024);
	ret->setSendBufSize(8 * 1024 * 1024);
	return ret;
}

void DBSessionMgr::DestroySession(NetSession* client)
{
	OutputMsg(rmWarning, "db server close client!");

	DBSession* dc = (DBSession*)client;
	dc->Close();

	LockCache();
	cache_.SaveAllActorDataImmediately(sql_);
	UnLockCache();

	close_list_.add(dc);
}

void DBSessionMgr::ProcessClients()
{
	Inherited::ProcessClients();
	ProcessClosedClients();
}

void DBSessionMgr::OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4)
{
	switch (msg)
	{
	case rmRefeshRank:
		{
			/*
			int sid = (int)p1;
			session_list_.lock();
			for (int i = 0; i < session_list_.count(); ++i)
			{
				DBSession* cli = (DBSession*)session_list_[i];

				if (!cli->IsBattleSrv() && cli->getClientServerIndex() == sid)
				{
					cli->LoadRank();
				}
			}
			session_list_.unlock();
			*/

			break;
		}
	case rmWaitForLogin:
		{
			int sid = (int)p1;
			int actorid = (int)p2;
			session_list_.lock();
			for (int i = 0; i < session_list_.count(); ++i)
			{
				DBSession* cli = (DBSession*)session_list_[i];
				
				if (cli->GetTargetId() == sid && cli->HasWaitFor(actorid))
				{
					cli->RemoveWaitFor(actorid);
					cli->QueryActorFromDB(actorid);
				}
			}
			session_list_.unlock();
			break;
		}
	case rmSetCacheSaveTime:
		{
			int time = (int)p1;
			int actorid = (int)p2;
			this->LockCache();
			cache_.SetNextSaveTime(actorid, time);
			this->UnLockCache();
			break;
		}
	}
}

void DBSessionMgr::OnServerStop()
{
	Inherited::OnServerStop();//���ø���Ĵ������Ա�ر���������

	OutputMsg(rmTip, "wait for process all client data����");
	do
	{
		SingleRun();
		Sleep(10);
	}
	while (!AllDataProcessed());
	//ǿ���ͷ����пͻ�������ռ�õ��ڴ棨�������Ӷ���
	FreeAllClient();
	OutputMsg(rmTip, "wait for process all client data������");

	rank_runing_ = false;
	
	/*while (!rank_free_)
	{
		Sleep(100);
	}*/
#ifdef _MSC_VER
	CloseThread(rank_hdl_);
#endif
	if (DBSession::huge_buf_s != NULL)
	{
		free(DBSession::huge_buf_s);
	}
}

void DBSessionMgr::SingleRun()
{
	_M_DBGFUNC_BEGIN
	//�������ݿ�
	ConnectSQL();

	Inherited::SingleRun();
	_M_DBGFUNC_END
}

void DBSessionMgr::OnRun()
{
	time_t now_t = NOW_T;

	if (sql_.Connected())
	{
		this->LockCache();
		cache_.RunOne(sql_);
		this->UnLockCache();

		if (now_t >= next_delete_t_)
		{
			//DECLARE_TIME_PROF("clear_invalid_db")

			next_delete_t_ = now_t + 360;

			SystemTime dt;
			GetSystemTime(dt);
			if (dt.hour_ >= 8) { //ÿ��8��֮������
				if (!sql_.Exec(sql_realcleanitem))
					sql_.ResetQuery();
				else
					OutputMsg(rmError, "delete items error");

				//ɾ��û�õ��ʼ�
				if (!sql_.Exec(sql_realcleanmail))
					sql_.ResetQuery();
				else
					OutputMsg(rmError, "delete mails error");

				if (!sql_.Exec("delete from roles where actorid=0;"))
					sql_.ResetQuery();
				else
					OutputMsg(rmError, "delete roles error");

				if (!sql_.Exec("delete from guildchat where guildid=0;"))
					sql_.ResetQuery();
				else
					OutputMsg(rmError, "delete guildchat error");
			}
		}
		
// 		if(now_t >= next_day_delete_t_)
// 		{
// 			next_day_delete_t_ = now_t + 3600;
// 			// ��ÿ������賿Ҫ��������Ҫ����
// 			SystemTime dt;
// 			GetSystemTime(dt);
// 			if (dt.hour_ == 0)
// 			{
// 				/*if (!sql_.Exec(deletemailbytick)) // ����Ǿɵ�
// 					sql_.ResetQuery();
// 				else
// 					OutputMsg(rmError, "delete clear day data error");
// 					*/
// 			}
// 		}
	}

	if (sql_.Connected() && now_t >= next_dmp_t_)
	{
#ifdef _MSC_VER
		if (next_dmp_t_)
			TimeProfMgr::getSingleton().dump();
#endif
		next_dmp_t_ = now_t + 300; //5����ִ��һ��dump
	}

#ifdef _MSC_VER
	// ���ִ��sql����϶࣬�򱨾�
	if (sql_.GetErrCnt() >= 10)
	{
		OutputWatchFile("dbserver execute sql too many error!");
		sql_.ClearErrCnt();
	}
#endif

	//if (IsBattleTime())
	//{
	//	DBDataCache::s_nActorCacheSaveInterval = 
	//		60 * SecondTime::SecOfMin * 1000;
	//}
	//else
	//{
	//	DBDataCache::s_nActorCacheSaveInterval = 
	//		60 * SecondTime::SecOfMin * 1000;
	//}
}

bool DBSessionMgr::GetGameReady(int srv_id)
{
	for (int i = session_list_.count() - 1; i > -1; --i)
	{
		DBSession* client = (DBSession*)session_list_[i];

		if (client->registed())
		{
			if (!srv_id || client->getClientServerIndex() == srv_id)
			{
				return true;
			}
		}
	}

	return false;
}

bool DBSessionMgr::ConnectSQL()
{
	time_t now_t = NOW_T;

	if (!sql_.Connected())
	{
		if (now_t >= next_conn_db_t_)
		{
			db_srv_->SetDb(&sql_);

			if (sql_.Connect())
			{
				mysql_options(sql_.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
				return true;
			}

			next_conn_db_t_ = now_t + 5;
			return false;
		}
	}
/*
	if (!rank_sql_.Connected())
	{
		if (now_t >= next_conn_db_t_)
		{
			db_srv_->SetDb(&rank_sql_);

			if (rank_sql_.Connect())
			{
				mysql_options(rank_sql_.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
				return true;
			}

			next_conn_db_t_ = now_t + 5;
			return false;
		}
	}
	*/
	if (now_t >= next_ping_t_)
	{
		int ret = 0;
		if (sql_.Connected())
		{
			ret = sql_.Ping();

			if (ret)
			{
				OutputMsg(rmError, "mysql ping error, errcode=%d", ret);
				sql_.Disconnect();
			}
		}
		/*
		if (rank_sql_.Connected())
		{
			
			//ret = rank_sql_.Ping();

			if (ret)
			{
				OutputMsg(rmError, "rank_sql ping error, errcode=%d", ret);
				rank_sql_.Disconnect();
			}
		}
		*/
		next_ping_t_ = now_t + 20;
	}
	sql_.SetLog(IsBattleTime());
	return true;
}

void DBSessionMgr::ProcessClosedClients()
{
	time_t now_t = NOW_T;

	for (int i = close_list_.count() - 1; i > -1; --i)
	{
		DBSession* client = close_list_[i];
		//���ӱ��رպ���ȻҪ����Run��������Ϊ��������Ҫ���������ݻ��߼�����û�д�����
		client->Run();

		//���ӹر�5���Ӻ����ͷ����Ӷ���
		if (now_t - client->close_t_ >= 300)
		{
			close_list_.remove(i);
			delete client;
		}
	}
}

bool DBSessionMgr::AllDataProcessed()
{
	//�����Ϣ���зǿ��������������
	if (GetMsgCount() > 0)
		return false;

	//�ж����ݿͻ��˵������Ƿ������
	for (int i = session_list_.count() - 1; i > -1; --i)
	{
		DBSession* client = (DBSession*)session_list_[i];

		if (!client->registed())
			continue;

		if (client->HasRemainData())
			return false;
	}

	for (int i = close_list_.count() - 1; i > -1; --i)
	{
		DBSession* client = close_list_[i];

		if (!client->registed())
			continue;

		if (client->HasRemainData())
			return false;
	}

	return true;
}

void DBSessionMgr::FreeAllClient()
{
	//�ر����пͻ���
	CloseAllClients();

	//������������
	for (int i = close_list_.count() - 1; i > -1; --i)
	{
		DBSession* client = close_list_[i];
		delete client;
	}

	close_list_.clear();
}

//void DBSessionMgr::RankThread2(DBSessionMgr* server)
//{
	/*//28�ּ���ˢ�����а�, 28-29�ֶ����а��ڵ���Ҵ���, 30��֪ͨgameworld���а����
	const int MIN1 = 1 * 60;
	const int MIN28 = 28 * 60;
	const int MIN30 = 30 * 60;
	const int MIN60 = 60 * 60;

	Vector<int>	all_client_;
	Vector<int> rank_actorid_list_;
	time_t next_t = NOW_T;
	time_t next_refresh_t = NOW_T;

	time_t nextping_t = NOW_T + 20;
	time_t next_conn_db_t_ = NOW_T + 5;
	SQLConnection& sql = server->rank_sql_;

	while (server->rank_runing_)
	{
		time_t now_t = NOW_T;
		
		if (!sql.Connected())
		{
			if (now_t >= next_conn_db_t_)
			{

				db_srv_->SetDb(&sql);

				if (sql.Connect())
				{
					mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
					continue;
				}

				next_conn_db_t_ = now_t + 5;
				continue;
			}
		}
		
		int ret = 0;
		if(now_t > nextping_t)
		{
			
			ret = sql.Ping();
			if (ret)
			{
				OutputMsg(rmError, "myranksql ping error, errcode=%d", ret);
				sql.Disconnect();
			}
			nextping_t = now_t + 20;
			
			continue;
		}

		//���ж�sql�Ƿ�����
		if (!sql.Connected())
		{
			Sleep(100);
			continue;
		}
		bool runFlag = false;
		// ǿ��ˢ�»���ˢ��ʱ�䵽, �����а����ˢ��
		if (server->GetRankRefresh() || now_t >= next_t)
		{
			// ��ʼˢ�����а�
			all_client_.clear();
			server->session_list_.lock();
			for (int i = 0; i < server->session_list_.count(); ++i)
			{
				DBSession* db = (DBSession*)server->session_list_[i];
				int sid = db->getClientServerIndex();
				if (!db->IsBattleSrv())
					all_client_.add(sid);
			}
			server->session_list_.unlock();

			OutputMsg(rmError, "start update rank...");
			rank_actorid_list_.clear();
			for (int i = 0; i < all_client_.count(); ++i)
			{
				int sid = all_client_[i];

				// ֪ͨ��Ϸ���������ɹ�ˢ��
				int err = sql.Query(saverank, sid);

				if (!err)
				{
					MYSQL_ROW pRow = sql.CurrentRow();
					while (pRow)
					{
						int actorid = 0;
						sscanf(pRow[0], "%d", &actorid);
						rank_actorid_list_.add(actorid);
						pRow = sql.NextRow();
					}
					sql.ResetQuery();
				}
				else
				{
					OutputMsg(rmError, "update rank error!sid=%", sid);
				}
			}
			OutputMsg(rmTip, "end update rank,count=%d ...", all_client_.count());

			// 28, 58��ˢ��һ��
			int minute = now_t % MIN60;

			if (minute < MIN28)
			{
				next_t = (now_t / MIN60) * MIN60 + MIN28;
			}
			else if (minute >= MIN28 && minute < MIN30 + MIN28)
			{
				next_t = (now_t / MIN60) * MIN60 + MIN30 + MIN28;
			}
			else
			{
				next_t = (now_t / MIN60) * MIN60 + MIN60 + MIN28;
			}

			// ��������1����ǿ�Ʊ�������
			for (int i = 0; i < rank_actorid_list_.count(); i++)
			{
				int actorid = rank_actorid_list_[i];
				server->PostMsg(rmSetCacheSaveTime, MIN1, actorid, 0, 0);
			}
			runFlag = true;
		}
		
		if (server->GetRankRefresh() || now_t >= next_refresh_t )
		{
			all_client_.clear();
			server->session_list_.lock();
			for (int i = 0; i < server->session_list_.count(); ++i)
			{
				DBSession* db = (DBSession*)server->session_list_[i];
				int sid = db->getClientServerIndex();
				if (!db->IsBattleSrv())
					all_client_.add(sid);
			}
			server->session_list_.unlock();

			for (int i = 0; i < all_client_.count(); i++)
			{
				int sid = all_client_[i];
				server->PostMsg(rmRefeshRank, sid, 0, 0, 0);
			}
			next_refresh_t = (now_t / MIN30 * MIN30 + MIN30);

			runFlag = true;
			OutputMsg(rmTip, "refreshRank to gameworld ...");
		}

		if (!runFlag)
		{
			Sleep(100);
			continue;
		}
		else
		{
			server->SetRankRefresh(false);
		}
	}

	all_client_.empty();
	rank_actorid_list_.empty();
	server->rank_runing_ = false;//��ǽ������ӵ��߳��Ѿ��˳�
	server->rank_free_ = true;
#ifdef _MSC_VER
	ExitThread(0);//�����߳��˳�����ֵ
#endif
	*/
//}
//
//#ifdef _MSC_VER
//void DBSessionMgr::RankThread(DBSessionMgr* ptr)
//#else
//void* DBSessionMgr::RankThread(void* ptr)
//#endif
//{
//	DBSessionMgr* server = (DBSessionMgr*)ptr;
//
//	_M_DBGFUNC_BEGIN
//	RankThread2(server);
//	_M_DBGFUNC_END
//
//#ifndef _MSC_VER
//	return NULL;
//#endif
//}

void DBSessionMgr::OnServerStart()
{
//	rank_runing_ = true;
//
//	int err = 0;
//
//#ifdef _MSC_VER
//	rank_hdl_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RankThread, this, 0, NULL);
//	if (!rank_hdl_)
//	{
//		err = GetLastError();
//	}
//#else
//	if (pthread_create(&rank_hdl_, NULL, RankThread, this))
//	{
//		err = errno;
//	}
//#endif
//	if (err)
//	{
//		OutputError(err, ("create rank thread fail��"));
//		return;
//	}
//	OutputMsg(rmTip, ("create rank thread succ��"));
//	rank_free_ = false;
}

bool DBSessionMgr::IsBattleTime()
{
	//todo ����汾��return ֮��ֱ��ɾ��
	return false;
	SystemTime st;
	GetSystemTime(st);
	SecondTime now;
	now = now.encode(st);

	SystemTime st_begin = st;
	SystemTime st_end = st;

	st_begin.hour_ = 20;
	st_begin.min_ = 30;
	st_begin.sec_ = 0;
	st_end.hour_ = 21;
	st_end.min_ = 30;
	st_end.sec_ = 0;

	SecondTime sc_st;
	sc_st = sc_st.encode(st_begin);
	SecondTime sc_end;
	sc_end = sc_end.encode(st_end);
	return (now > sc_st && now < sc_end);
}

void DBSessionMgr::SetRankRefresh(bool flag)
{
	rank_refresh_ = flag;
}


