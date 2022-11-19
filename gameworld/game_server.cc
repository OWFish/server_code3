#include "StdAfx.h"

SimpleAllocCounter GameServer::sac_("SimpleMemoryCounter");

GameServer::GameServer()
{
	GameServer::Instance = this;

	GEngine_ = NULL;

	srv_name_[0] = 0;
	srv_index_ = 0;
	web_host_[0] = 0;
	web_port_ = 0;

	started_ = false;

	config_data_ = new GameConfigData();
	//创建网关管理器
	gate_mgr_ = new GameGateMgr(this);
	gate_mgr_->Initialize();

	//日志客户端 在外部创建
	log_client_ = new LogSender();
	log_client_->UseBaseAlloc(true);

	center_client_ = new CenterClient(this);
	center_client_->UseBaseAlloc(true);

	//创建逻辑引擎
	GEngine_ = new GameEngine();
	GEngine_->SetGateMgr(gate_mgr_);

	acotr_mgr_ = new ActorMgr(gate_mgr_);

	async_work_ = new AsyncWorker("data/functions/utils/thread/asyncworker.lua");
	async_work_->SetWorkCallBack(&GameEngine::PostMsgToGE);

	GameLog::Init();

	//game_conn_mgr_ = new GameSessionMgr(this);
	game_conn_mgr_ = new GameConnMgr(this);

	for (int i = 0; i < MAX_DB_CLIENT_MGR_COUNT; ++i)
	{
		db_client_mgr_.add(new DBClientMgr());
	}

	is_battle_srv_ = bsCommSrv;

	// 统计内存
	MEMCOUNTER((*config_data_), 1);
	MEMCOUNTER((*gate_mgr_), 2);
	MEMCOUNTER((*log_client_), 3);
	MEMCOUNTER((*center_client_), 4);
	MEMCOUNTER((*GEngine_), 5);
	MEMCOUNTER((*acotr_mgr_), 6);
	MEMCOUNTER((*async_work_), 7);
	MEMCOUNTER((*game_conn_mgr_), 2);
}

GameServer::~GameServer()
{
	//停止服务
	StopServer();

	for (int i = 0; i < db_client_mgr_.count(); ++i)
	{
		DBClientMgr* dbmgr = db_client_mgr_[i];
		SafeDelete(dbmgr);
	}

	//按反向关联顺序销毁对象
	SafeDelete(game_conn_mgr_);
	SafeDelete(async_work_);
	SafeDelete(acotr_mgr_);
	SafeDelete(GEngine_);
	SafeDelete(log_client_);
	SafeDelete(center_client_);
	gate_mgr_->Uninitialize();
	SafeDelete(gate_mgr_);
	SafeDelete(config_data_);
	//SafeDelete(RankingMgr::allocator_);
}

bool GameServer::StartServer()
{
	OutputMsg(rmError, "start server...................");

	started_ = true;

	if (!vsp_def_.LoadDefinitions("data/vspdef.txt"))
	{
		OutputMsg(rmError, "vsp_def load error");
		return false;
	}

	if (!lang_.LoadFromFile(("data/language/langcode.txt")))
	{
		OutputMsg(rmError, "lang_txt load error");
		return false;
	}

	winitseed(0); //初始化随机数

	//GEngine_->GetGlobalVarMgr().Load();

	if (!config_data_->LoadConfig())
	{
		OutputMsg(rmError, "config_data load error");
		return false;
	}


	//启动网关管理器
	if (!gate_mgr_->Startup())
	{
		OutputMsg(rmError, "gate_mgr startup error");
		return false;
	}

	//启动logclient
	if (log_client_)
	{
		if (!log_client_->Startup())
		{
			OutputMsg(rmError, "log_client startup error");
			return false;
		}
	}

	if (center_client_)
	{
		/*if (!center_client_->Startup())
		{
			OutputMsg(rmError, "center_client startup error");
			return false;
		}*/
	}
	
	DBClient* db = ServerInstance()->GetDbClient();
	while (!db || !db->ConnectToServer())
	{
		OutputMsg(rmError, "wait for db client...");
#ifdef  _MSC_VER
		Sleep(1000);
#else
		Sleep(5000);
#endif
		db = ServerInstance()->GetDbClient();
	}
	for (int i = 0; i < db_client_mgr_.count(); ++i)
	{
		DBClientMgr* dbmgr = db_client_mgr_[i];
		if (dbmgr) dbmgr->Start();
	}
	
	if (!GEngine_->StartEngine())
		return false;

	if (!acotr_mgr_->StartActorMgr())
	{
		OutputMsg(rmError, "acotr_mgr startup error");
		return false;
	}

	GEngine_->GameInit();

	async_work_->Start();

	OutputMsg(rmTip, "start server...................[ok]");
	OutputMsg(rmTip, "   _  ___  _  __  ___   _         ");
	OutputMsg(rmTip, "  |_   |  |_| |_|  |   | | |_/    ");
	OutputMsg(rmTip, "   _|  |  | | | \\  |   |_| | \\_     ");
	OutputMsg(rmTip, "                                   ");
	OutputMsg(rmTip, "start server...................[ok]");
	return true;
}

void GameServer::StopServer()
{
	if (!started_)
		return;

	async_work_->Stop();
	acotr_mgr_->Stop();

	//等待并停止逻辑引擎
	GEngine_->StopEngine();

	//停止网关管理器
	gate_mgr_->Stop();

	//等待并停止日志客户端
	if (log_client_)
	{
		log_client_->Stop();
	}

	if (center_client_)
	{
		center_client_->Stop();
	}

	// 关闭跨服的服务器
	game_conn_mgr_->Stop();

	for (int i = 0; i < db_client_mgr_.count(); ++i)
	{
		DBClientMgr* dbmgr = db_client_mgr_[i];
		if (dbmgr) dbmgr->Stop();
	}

	//对未处理的内部消息处理一遍
	GEngine_->ClearAllInterMsg();


	started_ = false;
}

DBClient* GameServer::GetDbClient(int sid)
{
	if (sid == 0)
	{
		sid = GetServerIndex();
	}

	DBClient** data = dbclient_list_.get(sid);
	return data ? *data : NULL;
}

void GameServer::AddDbClient(int sid, const char* ip, int port, bool start)
{
	// 本函数只能在游戏主线程中使用
	DBClient** dbclient = dbclient_list_.get(sid);

	if (dbclient == NULL)
	{
		DBClient* db = new DBClient(this);
		db->UseBaseAlloc(true);
		dbclient_list_.put(sid, db);
		db->SetHost(ip);
		db->SetPort(port);
		db->SetServerId(sid);

		int idx = sid % db_client_mgr_.count();
		GameInterMsg msg;
		msg.msg_id_ = DBClientMgr::dbmAdd;
		msg.data_.ptr_ = db;
		db_client_mgr_[idx]->PostMsg(msg);
	}
	else
	{
		OutputMsg(rmError, "dbclient has in list %d,ip:%s,port:%d", sid, (*dbclient)->GetHost(), (*dbclient)->GetPort());
	}
}

unsigned long long GameServer::getUnixTime()
{
	unsigned long long ftime = 0;
#if (defined(WIN32) || defined(WINDOWS))
	ftime = NOW_T * 1000;
#elif __MACH__
	ftime = 0;
#else
	struct timespec unixTime;
	clock_gettime(CLOCK_REALTIME, &unixTime);
	ftime = unixTime.tv_sec * 1000 + (int)unixTime.tv_nsec / 1000 / 1000;
#endif
	return ftime;
}

void GameServer::SendMsgToAllGameClient(const void* buff, size_t size, int cmd, int sid, int cross_method)
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();

	static BaseAllocator alloc("SendMsgToAllGameClient"); // 要用线程安全的分配器

	if (ServerInstance()->IsCommonSrv())
	{
#ifndef TEST_CROSS_MEM
		DataPacket* gp = new DataPacket(&alloc);
#else
		DataPacket* gp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
		new(gp)DataPacket(&alloc);
#endif
		gp->writeBuf(buff, size);

		GameInterMsg msg;
		msg.msg_id_ = ActorMgr::imBroadCast;
		msg.data_.packet_ = gp;
		msg.data_.cmd_ = cmd;
		msg.data_.dbsid_ = sid;
		mgr->PostMsg(msg);
	}

	if (ServerInstance()->IsBattleSrv()) {
		static GameConnMgr* mgr = ServerInstance()->GetGameConnMgr();
#ifndef TEST_CROSS_MEM
		DataPacket* gp = new DataPacket(&alloc);
#else
		DataPacket* gp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
		new(gp)DataPacket(&alloc);
#endif
		gp->writeBuf(buff, size);
		mgr->PostMsg(GameConnMgr::gcBroadCast, cmd, (size_t)gp, sid, 0);
	}
}

void GameServer::printAllDbClient()
{
}



