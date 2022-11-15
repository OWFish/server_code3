#include "StdAfx.h"
#include "game_engine.h"
#include "InterServerComm.h"
#include "protocol/handles/net_handle_base.h"
#include "item/item_pool.h"
#include "mail/mail_pool.h"
#include "ai/ai_mgr.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_data_mgr.h"
#include "rank/ranking_system.h"
#include "timedomain/time_domain.h"
#include "actormgr/login_queue.h"
#include "actor/global_mail_mgr.h"
#include "systems/guild/guild.h"
#include "systems/prestige/prestige_helper.h"
#include "actor/tianti_mgr.h"
#include "redis/RedisConnect.h"
#include <iostream>


#ifdef _MSC_VER
//#include "gtest/gtest.h"
#endif

using namespace InterSrvComm::DbServerProto;
using namespace InterSrvComm::GameWorldProto;
using namespace InterSrvComm::CenterProto;

int64_t GameEngine::game_tick_ = _getTickCount();
const char* GameEngine::GlobalScriptFile = ("./data/functions/globalfunction.txt");
CTimeStatisticMgr* GameEngine::timeStatisticMgr_  = NULL;
GlobalVar* GameEngine::global_var_ = NULL;
template <>
EntityList::LinkNodeMgr* EntityList::node_pool_ = NULL;

static BaseAllocator allocActorIdPacket("ActorIdPacket");

GameEngine::GameEngine()
	: Inherited(),
	  //monsterActionCallAlloc_("MonsterActionCallMsg"),
	  engine_report_t_(60 * 1000),engine_60s_t_(60* 1000), engine_5s_t_(5*1000), gc_t_(30 * 60 * 1000),
	  se_hdl_mgr_("ScriptCBHdlMgr")
{
	filterWords_ = NULL;
	entity_mgr_ = new EntityMgr();
	actor_asyn_mgr_ = new ActorAsynMgr();
	actor_data_mgr_ = new ActorDataMgr();
	login_queue_ = new LoginQueue();
	ranking_system_ = new RankingSystem();
	fuben_mgr_ = new FuBenMgr();
	ai_mgr_ = new AiMgr();
	guild_mgr_ = new GuildMgr();
	
	InitStaticVar();

	reserveScene_ = NULL;
	globalFuncNpc_ = NULL;
	globalFuncNpc_rese_ = NULL;

	GetSystemTime(cur_sys_time_);
	//game_tick_ = _getTickCount();
	now_sec_ = now_sec_.encode(cur_sys_time_);
	
	int64_t weehourstimelogin = now_sec_.today() + GLOBAL_WEE_HOURS_TIME;	//当日22点时间

	int rd = wrand(GLOBAL_TIME_FLUCTUATE);
	if (now_sec_.tv >= weehourstimelogin)
	{
		EventRefreshTime_.tv = now_sec_.tomorrow() + rd + GLOBAL_WEE_HOURS_TIME;
	}
	else
	{
		EventRefreshTime_.tv = now_sec_.today() + rd + GLOBAL_WEE_HOURS_TIME;
	}

	inter_msg_.setLock(&inter_msg_lock_);

	memset(net_msg_route, 0, sizeof(net_msg_route));

	started_ = false;

	db_host_[0] = 0;
	db_port_ = 0;
/*
	global_sql_.SetMultiThread(true);
	global_sql_.SetLog(false);

#ifdef DB_UTF8
	global_sql_.SetUtf8(true);
#endif
*/
	Start();

	gc_t_.SetNextHitTimeFromNow(game_tick_, 30 * 60 * 1000);

	script_5s_timer_ = false;

	gc_actor_cnt_ = 1000;

	memset(db_ret_route, 0, sizeof(db_ret_route));
	gateway_routes_.trunc(MAX_SERVER_ID);
	memset(gateway_routes_, 0, sizeof(GameRoute*) * MAX_SERVER_ID);
}

GameEngine::~GameEngine()
{
	//resume();
	BaseThread::Stop();

	ClearAllInterMsg();
	ClearAllGameRoute();

	SafeDelete(timeStatisticMgr_);
	SafeDelete(fuben_mgr_);
	SafeDelete(ai_mgr_);
	SafeDelete(actor_asyn_mgr_);
	SafeDelete(actor_data_mgr_);
	SafeDelete(login_queue_);
	SafeDelete(ranking_system_);
	SafeDelete(guild_mgr_);
	ReleaseStaticVar();
	SafeDelete(entity_mgr_);
}

void GameEngine::ClearAllGameRoute()
{
	for (int i = 0; i < MAX_SERVER_ID; i++)
	{
		GameRoute* r = gateway_routes_[i];
		if (r)
		{
			global_var_->ge_alloc_.FreeBuffer(r);
			gateway_routes_[i] = NULL;
		}
	}
}

void GameEngine::ClearAllInterMsg()
{
	inter_msg_.flush();

	int count = inter_msg_.count();

	for (int i = 0; i < count; ++i)
	{
		GameInterMsg& msg = inter_msg_[i];

		if (msg.msg_id_ == SSM_DB_RET_DATA)
		{
			DBClient* db = ServerInstance()->GetDbClient(msg.data_.dbsid_);

			if (db) db->FreeBackUserDataPacket(msg.data_.packet_);
		}
		else if (msg.msg_id_ == SSM_CENTER_DATA)
		{
			//CenterClient* cli = ServerInstance()->GetCenterClient();

			//if (cli) cli->FreeBackUserDataPacket(msg.data_.packet_);
		}
		else if (msg.msg_id_ == SSM_WORK_THREAD)
		{
			AsyncWorker::CBData* cb = (AsyncWorker::CBData*)msg.data_.ptr_;

			if (cb)
			{
				AsyncWorker::AsyncWorkerAlloc& alloc = cb->worker_->GetAlloc();

				if (cb->params_ && cb->free_func_)
				{
					cb->free_func_(cb);
				}

				alloc.FreeBuffer(cb);
			}
		}
		//else if (msg.msg_id_ == SSM_ACTOR_LOGIN)
		//{
		//	if (msg.data_.pf_)
		//	{
		//		ServerInstance()->GetActorMgr()->GetPfAlloc().FreeBuffer(msg.data_.pf_);
		//	}
		//}
		else
		{
			FreeMsgPack(msg);
		}
	}

	inter_msg_.clear();
}

void GameEngine::FreeMsgPack(GameInterMsg& msg)
{
	if (msg.msg_id_ == SSM_GAMESESSION_GATEWAY ||
	        msg.msg_id_ == SSM_CROSSWAR_KEY ||
	        msg.msg_id_ == SSM_CROSSWAR_MSG ||
			msg.msg_id_ == SSM_CROSSTTMSG_GAME ||
	        msg.msg_id_ == SSM_GAMESESSION_REG)
	{
		DataPacket* dp = msg.data_.packet_;
#ifndef TEST_CROSS_MEM
		delete dp;
#else
		dp->~DataPacket();
		ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		msg.data_.packet_ = NULL;
	}
}

bool GameEngine::StartEngine()
{

	if (!InitReserveNpc())
	{
		OutputMsg(rmError, "StartEngine error: InitReserveNpc");
		return false;
	}
	if (!InitStaticFuben())
	{
		OutputMsg(rmError, "StartEngine error: InitStaticScene");
		return false;
	}
	
	if (!global_mail_mgr_.LoadDbData())
	{
		OutputMsg(rmError, "StartEngine error: initGlobalMailMgr");
		return false;
	}
	if (!LoadActorBasicData())
	{
		OutputMsg(rmError, "StartEngine error: InitStaticScene");
		return false;
	}
	if (!guild_mgr_->LoadDbData())
	{
		OutputMsg(rmError, "StartEngine error: load guild data");
		return false;
	}

	TianTiManger::GetInstance()->NewLoad();

	NetHandle::InitNetHandles();

	time_t next_t = NOW_T + 1;

	while (!isInitComponentFinished())
	{
		ProcessSysMsg();
		time_t now_t = NOW_T;

		if (now_t >= next_t)
		{
			OutputMsg(rmNormal, "wait for data ...");
			next_t = now_t + 1;
		}

		Sleep(1000);
	}

	OutputMsg(rmTip, "StartEngine, load global data finish!!!!!!");

	actor_asyn_mgr_->GameStar();

	WatchThread* watch = ServerInstance()->GetWatch();

	if (watch) watch->AddWatch(GameServer::wiGame, 120000);

	started_ = true;
	return true;
}

void GameEngine::StopEngine()
{
	BaseThread::Stop();
}

void GameEngine::OnRoutine()
{
	while (!started_ && !terminated())
	{
		Sleep(1);
	}

	// 引擎启动
	if (!terminated())
		EngineStarted();

	GetSystemTime(cur_sys_time_);
	SecondTime	last_sec;		//上一次执行时的短日期时间
	unsigned int last_t, now_t;
	last_sec.encode(cur_sys_time_);
	last_t = (unsigned int)last_sec;
	while (!terminated())
	{
		const int64_t MainLoopTimeLimit = 16;
		game_tick_ = _getTickCount();
		int64_t timeOver = game_tick_ + MainLoopTimeLimit;
		
		for (int i = 0; i < 4; ++i)
		{
			// 更新日期和时间
			GetSystemTime(cur_sys_time_);
			now_sec_.encode(cur_sys_time_);
			now_t = (unsigned int)now_sec_;

			if (now_t < last_t || now_t - last_t > 10)
			{
				OutputMsg(rmError, "[BUG]system time error:%d-%d-%d %d:%d:%d",
					cur_sys_time_.year_, cur_sys_time_.mon_, cur_sys_time_.mday_, cur_sys_time_.hour_, cur_sys_time_.min_, cur_sys_time_.sec_);
				continue;
			}

			// 游戏主循环
			LogicRun();

			// 如果处理逻辑后时间超过性能参数中处理逻辑结束的时间，则终止循环
			game_tick_ = _getTickCount();
			last_t = now_t;
			if (game_tick_ >= timeOver) {
#ifndef _MSC_VER
				OutputMsg(rmError, "[BUG]LogicRun timeOver(%d):%d ...", i, game_tick_ - timeOver + MainLoopTimeLimit);
#endif // !_MSC_VER
				break;
			}
		}
		last_t = now_t;

		Sleep(10);
	}

	// 引擎停止
	EngineStoped();
}

void GameEngine::EngineStarted()
{
#ifdef _MSC_VER
	TimeProfMgr::getSingleton();
#endif

	if (!timeStatisticMgr_)	timeStatisticMgr_ = new(CTimeStatisticMgr);

	CTimeSpan::g_mgr = timeStatisticMgr_;

	//item_alloc_.SetServerId(ServerInstance()->GetServerIndex());
	ItemPool::instance().SetServerId(ServerInstance()->GetServerIndex());
	MailPool::instance().SetServerId(ServerInstance()->GetServerIndex());

	ReloadFilterDb();

	//初始化
	entity_mgr_->Initialize();
	ranking_system_->Initialize();
	//miscMgr_.Initialize();
	guild_mgr_->Initialize();
	//camp_mgr_.InitCampBattle();
	//fight_mgr_.Initialize();
	GetSystemTime(cur_sys_time_);
	now_sec_.encode(cur_sys_time_);
	game_tick_ = _getTickCount();
	static GameScript& lua = GetGlobalNpc()->GetScript();
	lua.Call("OnGameStart", NULL, NULL, 0);
}

void GameEngine::EngineStoped()
{
	OutputMsg(rmError, "GameEngine::EngineStoped");

	auto& AllActorDatas = GetEntityMgr()->GetActorMgr();
	EntityPtrList::Iterator it(AllActorDatas.entity_list_);

	//先踢掉所有在线玩家
	for (EntityPtrList::NodeType* node = it.first(); node; node = it.next())
	{
		Entity* entity = *node;
		if (entity && entity->GetType() == EntityType_Actor)
		{
			Actor* actor = (Actor*)entity;
			if (actor)
			{
				if (!actor->IsImage())
				{
					actor->SetKickRelogin(true);
					gate_mgr_->PostCloseUser(actor->GetNetId(), "GameEngine::OnCloseActorById", actor->GetActorId());
				}
				else
				{
					actor->CloseActor("GameEngine::OnCloseActorById");
				}
			}
		}
	}

	//再存库
	for (EntityPtrList::NodeType* node = it.first(); node; node = it.next())
	{
		Entity* entity = *node;
		if (entity && entity->GetType() == EntityType_Actor)
		{
			Actor* actor = (Actor*)entity;
			if (actor)
			{
				if (!actor->IsImage())
				{
					actor->SaveDb(true);
					actor->SetKickRelogin(true);
					gate_mgr_->PostCloseUser(actor->GetNetId(), "GameEngine::OnCloseActorById", actor->GetActorId());
				}
				else
				{
					actor->CloseActor("GameEngine::OnCloseActorById");
				}
			}
		}
	}

	GetGameEngine()->GetGuildMgr()->Save(true);
	TianTiManger::GetInstance()->NewSave(true);

	if (globalFuncNpc_)
	{
		ScriptValueList arg;
		//GameScript& lua = globalFuncNpc_->GetScript();
		globalFuncNpc_->GetScript().Call("OnGameStop", &arg, NULL, 0);

		arg.clear();
		globalFuncNpc_->GetScript().Call("SaveOnGameStop", &arg, NULL, 0); // 程序退出时保存数据
	}

	ranking_system_->Destroy();
	entity_mgr_->CloseAllActor();
	guild_mgr_->Destroy();
	fuben_mgr_->Destroy();
	actor_asyn_mgr_->Destroy();
	actor_data_mgr_->Destroy();
	login_queue_->Destroy();

	if (globalFuncNpc_)
	{
		entity_mgr_->DestroyEntity(globalFuncNpc_->GetHandle());
		globalFuncNpc_ = NULL;
	}
	if (globalFuncNpc_rese_)
	{
		entity_mgr_->DestroyEntity(globalFuncNpc_rese_->GetHandle());
		globalFuncNpc_rese_ = NULL;
	}

	entity_mgr_->Destroy();
	//camp_mgr_.Destroy();
	//rankingMgr_.Destroy();
	//consignmentMgr_.Destroy();
	//fight_mgr_.Save();
	//fight_mgr_.Destroy();
	sysvar_mgr_.Destroy();
	//gamewar_mgr_.Destroy();

	if (filterWords_)
	{
		FreeMBCSFilter(filterWords_);
		filterWords_ = NULL;
	}

	//清除脚本数据
	dynamicVar_.clear();
	globalVarMgr_.Save();
	globalVarMgr_.Destroy();
	//miscMgr_.Save();

	SafeDelete(timeStatisticMgr_);
}

void GameEngine::LogicRun()
{
#ifdef _USE_TRY_CATCH

	__try
#endif
	{
		gate_mgr_->CollectGameData();
		ProcessSysMsg();
		entity_mgr_->RunOne();
		actor_asyn_mgr_->RunOne(game_tick_);
		fuben_mgr_->RunOne();
		guild_mgr_->RunOne();
		//camp_mgr_.RunOne(game_tick_);
		//consignmentMgr_.RunOne();//定期检查寄卖物品下架，每分钟检查一次
		globalVarMgr_.RunOne(game_tick_);
		ranking_system_->RunOne(game_tick_);
		//miscMgr_.RunOne(now_sec_);
		//fight_mgr_.RunOne(now_sec_);
		//gamewar_mgr_.RunOne();
		//teamMgr_.RunOne(now_sec_);
		TimeDomain::getInstance().RunOne(now_sec_);
		login_queue_->RunOne(now_sec_);
		TianTiManger::GetInstance()->NewSave();

		MiscRun();
	}

#ifdef _USE_TRY_CATCH

	__except (DefaultUnHandleExceptionFilter(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
	{
		OutputMsg(rmTip, ("catch exception!!!"));
	}

#endif
}

//检查全服事件刷新时间
void GameEngine::CheckRefreshTime()
{
	SecondTime curTime = getMiniDateTime();
	if (curTime.tv >= EventRefreshTime_.tv
		|| (curTime.tv >= EventRefreshTime_.rel_today() + GLOBAL_WEE_HOURS_TIME && curTime.tv < EventRefreshTime_.tv))
	{
		int rd = wrand(GLOBAL_TIME_FLUCTUATE);
		EventRefreshTime_.tv = now_sec_.tomorrow() + rd + GLOBAL_WEE_HOURS_TIME;
		static ScriptNpc* gn = GetGameEngine()->GetGlobalNpc();
		gn->GetScript().Call("OnGameRefreshEvent", NULL, NULL);
	}
}

bool GameEngine::InitReserveScene()
{
	return true;
	//bool ret = false;
	//SceneHandle handle;

	/*if (!reserveScene_)
	{
		//初始化生成一张8x8的地图数据
		reserveMapData_.initDefault(8, 8);

		FuBen* fb = fuBenMgr_.GetFbStaticDataPtr(0);

		static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
		Scene* scene = fbMgr->AllocSceneHandle(handle);
		scene->SetHandle(handle);
		scene->SetConfig(NULL, &reserveMapData_);
		ret = scene->Init(fb);
		fb->AddScene(scene);

		reserveScene_ = scene;
	}*/

}
bool GameEngine::InitStaticFuben()
{
	return fuben_mgr_->CreateStaticFuBen();
}

bool GameEngine::InitReserveNpc()
{
	EntityHandle hHandle;
	globalFuncNpc_ = (ScriptNpc*)entity_mgr_->CreateEntity(EntityType_Npc, hHandle);
	if (!globalFuncNpc_) return false;

	//globalFuncNpc_->SetInitProp(P_ID, 0);

	if (!globalFuncNpc_->Init(nullptr, 0))
	{
		entity_mgr_->DestroyEntity(hHandle);
		return false;
	}

	globalFuncNpc_->SetEntityName("SYS-FUNCTION");

	if (!(globalFuncNpc_)->LoadScript(GlobalScriptFile))
	{
		OutputMsg(rmError, ("unable to load GlobalFunction Script"));
		return false;
	}
	else
	{
		globalFuncNpc_->SetInitFlag(true);
	}
	return true;


	/*if (!reserveScene_)
		return false;

	if (!globalFuncNpc_)
	{
		//全局功能NPC，主要处理玩家事件回调
		globalFuncNpc_ = (ScriptNpc*)reserveScene_->CreateEntityAndEnter(0, EntityType_Npc, 0, 0);
		globalFuncNpc_->SetEntityName("SYS-FUNCTION");

		globalFuncNpc_rese_ = (ScriptNpc*)reserveScene_->CreateEntityAndEnter(0, EntityType_Npc, 0, 0);
		globalFuncNpc_rese_->SetEntityName("SYS-FUNCTION_RESE");
		globalFuncNpc_rese_->SetInitFlag(true);

		if (!globalFuncNpc_->LoadScript(GlobalScriptFile))
		{
			OutputMsg(rmError, ("unable to load GlobalFunction Script"));
			return false;
		}
		else
		{
			globalFuncNpc_->SetInitFlag(true);
		}
	}

	return true;
	*/
}

bool GameEngine::LoadActorBasicData()
{
	return actor_data_mgr_->Load();
}

//发送内部消息
void GameEngine::PostMsg(GameInterMsg& msg)
{
	inter_msg_.append(msg);
}

void GameEngine::ProcessSysMsg()
{
	inter_msg_.flush();

	int count = inter_msg_.count();

	for (int i = 0; i < count; ++i)
	{
		GameInterMsg& msg = inter_msg_[i];
		OnRecvSysMsg(msg);
	}

	inter_msg_.clear();
}

void GameEngine::OnRecvSysMsg(GameInterMsg& msg)
{
	switch (msg.msg_id_)
	{
	case SSM_ACTOR_LOGIN:
		{
			//OnActorLogin(msg); // 已改到登陆队列里了
			break;
		}
	case SSM_ADD_LOGIN:
		{
			OnAddLoginList(msg);
			break;
		}
	case SSM_ACTOR_LOGOUT:
		{
			OnActorLogout(msg);
			break;
		}
	case SSM_CREATE_ACTOR_IMAGE:
		{
		    OnCreateImageActor(msg);
		    break;
		}
	case SSM_DB_RET_DATA:
		{
			OnDbServerMsg(msg);
			break;
		}

	case SSM_GW_DUMP:
		{
			OnGatewayDump(msg);
			break;
		}

	case SSM_CLOSE_ACTOR_BY_ID:
		{
			OnCloseActorById(msg);
			break;
		}

	case SSM_GAMESESSION_REG:
		{
			OnGameSessionReg(msg);
			break;
		}

	case SSM_GAMECLIENT_REG:
		{
			OnGameClientResp(msg);
			break;
		}

	case SSM_GAMESESSION_GATEWAY:
		{
			//OnGameSessionGw(msg);
			break;
		}

	case SSM_CROSSWAR_KEY:
		{
			OnCrosswayKey(msg);
			break;
		}

	case SSM_CROSSWAR_MSG:
		{
			OnCrossWarMsg(msg);
			break;
		}

	case SSM_WORK_THREAD:
		{
			OnAsynWorkerMsg(msg);
			break;
		}

	case SSM_RELOAD_GLOBAL_NPC:
		{
			ReloadGlobalNpc(msg.data_.gm_actor_, msg.data_.type_);
			break;
		}

	case SSM_RELOAD_GLOBAL_NPC_MAIN:
		{
			PostReloadGlobaNpc();
			break;
		}

	case SSM_CENTER_DATA:
		{
			OnCenterServerMsg(msg);
			break;
		}

	case SSM_RUN_ALL_TESTS:
		{
			OnRunAllTests(msg);
			break;
		}
	case SSM_CROSSTTMSG_GAME:
		{
			OnCrossServerTtMsg(msg);
			break;
		}
	case SSM_USER_CHANGE_NAME:
		{
			OnChangeUserName(msg);
			break;
		}
	case SSM_CROSS_RELOGIN:
		{
			OnCrossRelogin(msg);
			break;
	}
	}

	FreeMsgPack(msg);
}


//做全局变量的初始化工作
void GameEngine::InitStaticVar()
{
	if (!global_var_) global_var_ = new GlobalVar();

	InitActMsgMemPool();

	luamemory::Initialize();

	EntityList::node_pool_ = new EntityList::LinkNodeMgr("EntityLinkNodeHdlMgr");
	GuildMemberList::node_pool_ = new GuildMemberList::LinkNodeMgr("GuildMemberNodeHdlMgr");

	//BuffSystem::allocator_ = new ObjPool<DynamicBuff>("DynamicBuff");

	//QuestSystem::item_op_list_ = new Vector<ItemOPParam>();

	TimeCaller::TimeList::node_pool_ = new TimeCaller::TimeList::LinkNodeMgr("TimeCaller::TimeList");
	//MonsterAction::TimeCallList::node_pool_ = new MonsterAction::TimeCallList::LinkNodeMgr("MonsterTimeCallPool");
	EntityPtrList::node_pool_ = new EntityPtrList::LinkNodeMgr("entity list");

	//AttrConfig::config_ = new AttrConfig();

	//RankingMgr::allocator_ = new RankAlloc("CRankingMgr", 1024, 8);
	//Animal::InitStateForbidMask();
}

//释放程序中的全局变量
void GameEngine::ReleaseStaticVar()
{
	SafeDelete(EntityList::node_pool_);
	SafeDelete(GuildMemberList::node_pool_);
	//SafeDelete(BuffSystem::allocator_);
	//SafeDelete(QuestSystem::item_op_list_);
	SafeDelete(EntityPtrList::node_pool_);
	SafeDelete(TimeCaller::TimeList::node_pool_);
	//SafeDelete(MonsterAction::TimeCallList::node_pool_);
	//SafeDeleteArray(Animal::s_stateForbidMask);
	//SafeDelete(AttrConfig::config_);
	luamemory::Realease();
	ReleaseActMsgMemPool();
	SafeDelete(global_var_);
}

void GameEngine::BroadCast(int channelId, int para, const char* buf, size_t len)
{
	// 给gatemanage发消息
	for (int i = 0; i < GateManager::MaxGateCount; ++i)
	{
		GameGate* gate = (GameGate*)gate_mgr_->gate_list_[i];

		if (gate && gate->connected())
		{
#pragma pack(push,1)
			static struct CmdHdr
			{
				DATAHEADER hdr;	// 这个也是4字节对齐
				uint16_t cmd;
				CmdHdr() : cmd(GW_CHANNEL)
				{
					hdr.tag = TAG_VALUE;
				}
			} cmdData;
#pragma pack(pop)
			static int data[4] = {ccBroadCast, 0, 0, 0};
			data[1] = channelId;
			data[2] = para;

			DataPacket* pack = gate->GetSendToGatePacket(GameGate::GameThread);
			cmdData.hdr.len = (/*uint16_t*/uint32_t)(sizeof(data) + len + 2);
			pack->writeBuf(&cmdData, sizeof(cmdData));
			pack->writeBuf(data, sizeof(data));
			pack->writeBuf(buf, len);
			//gate->Flush(*pack);
		}
	}
}

void GameEngine::ChannelUser(int channelId, int para, Actor* actor, int type)
{
	if (!actor) return;

	NetId& netid = actor->GetNetId();
	GameGate* gate = (GameGate*)gate_mgr_->GetGate(netid.gate_id_);

	if (!gate || !gate->connected()) return;

#pragma pack(push,1)
	static struct CmdHdr
	{
		DATAHEADER hdr;	// 这个也是4字节对齐
		uint16_t cmd;
		CmdHdr() : cmd(GW_CHANNEL)
		{
			hdr.tag = TAG_VALUE;
		}
	} cmdData;
#pragma pack(pop)
	static int data[4];
	data[0] = type == 0 ? ccAddUser : ccDelUser;
	data[1] = channelId;
	data[2] = para;
	data[3] = netid.index_;

	DataPacket* pack = gate->GetSendToGatePacket(GameGate::GameThread);
	cmdData.hdr.len = (/*uint16_t*/uint32_t)(sizeof(data) + 2);
	pack->writeBuf(&cmdData, sizeof(cmdData));
	pack->writeBuf(data, sizeof(data));
}


void GameEngine::BroadCast(const char* buff, size_t len)
{
	BroadCast(ciChannelWorld, 0, buff, len);
}

// 全服发布公告
void GameEngine::BroadcastTipmsg(const char* sTipmsg, int level, int tipType)
{
	//if (NULL == sTipmsg) return;

	//static uint8_t data_buff[512] = {enChatSystemID, sSendTipmsg, 0};
	//static DataPacket data(data_buff + 3, sizeof(data_buff) - 3);
	//data.setLength(0);

	//data_buff[2] = (uint8_t)level;
	//data << (int)tipType;
	//data.writeString(sTipmsg, __min(512, strlen(sTipmsg)));	// 256应该够了
	//BroadCast((char*)data_buff, data.getPosition() + 4); // 广播
}


int GameEngine::FormatTipmsg(char* buf, int size, const char* msg, int tipType)
{
	return 0;
	//if (buf == NULL || size <= 0 || msg == NULL) return 0;

	//buf[0] = enChatSystemID;
	//buf[1] = sSendTipmsg;
	//buf[2] = 0;
	//memcpy(buf + 3, &tipType, sizeof(int));
	//int len = DataPacket::writeString_s(buf + 7, size - 7, msg);
	//return len + 7;
}


void GameEngine::BroadcastGuildTipmsg(int guild, const char* sTipmsg)
{
	/*if (NULL == sTipmsg) return;

	DataPacket pack(broadcastBuff_, sizeof(broadcastBuff_));
	static uint8_t data[] = {enChatSystemID , sGuildTipMsg};
	pack.writeBuf(data, sizeof(data));
	pack.writeString(sTipmsg);
	BroadCastGuild(guild, broadcastBuff_, pack.getPosition()); //广播
	*/
}

void GameEngine::BroadcastCampTipmsg(int nCampId, const char* sTipmsg, int tipType)
{
	//if (NULL == sTipmsg) return;

	//DataPacket pack(broadcastBuff_, sizeof(broadcastBuff_));
	//static uint8_t data[] = { enChatSystemID, sSendTipmsg, 0 };
	//pack.writeBuf(data, sizeof(data));
	//pack << (int)tipType;
	//pack.writeString(sTipmsg);
	//BroadCastCamp(nCampId, broadcastBuff_, pack.getPosition()); //广播
}

//通过ID广播tipmsg
void GameEngine::BroadcastTipmsgWithID(int nTipmsgID, int nTipmsgType)
{
	static TIPMSGCONFIG& msgMgr = *TIPMSGCONFIG::config_;
	BroadcastTipmsg(msgMgr.GetTip(nTipmsgID), nTipmsgType);
}

void GameEngine::BroadCampTipmsgWithParams(int camp, int tip, int type, ...)
{
	va_list args;
	va_start(args, type);
	int len = FormatTipmsg(tip, args, type);
	va_end(args);
	BroadCastCamp(camp, broadcastBuff_, len);
}

void GameEngine::BroadGuildTipmsgWithParams(int gid, int tip, int type /*=ttTipmsgWindow*/, ...)
{
	/*va_list args;
	va_start(args, type);
	int len = FormatTipmsg(tip, args, type);
	va_end(args);
	BroadCastGuild(gid, broadcastBuff_, len);
	*/
}

// 带参数全服广播
void GameEngine::BroadTipmsgWithParams(int tip, int type, ...)
{
	va_list args;
	va_start(args, type);
	int len = FormatTipmsg(tip, args, type);
	va_end(args);
	BroadCast(broadcastBuff_, len);
}

//格式化广播字符串
int GameEngine::FormatTipmsg(int msgId, va_list& args, int msgType)
{
	return 0;
	//static TIPMSGCONFIG& msgMgr = *TIPMSGCONFIG::config_;

	//broadcastBuff_[0] = enChatSystemID;
	//broadcastBuff_[1] = sSendTipmsg;

	//memcpy(broadcastBuff_ + 3, &msgType, sizeof(msgType));

	////保留字符串长度成员
	//uint16_t* msg_len = (uint16_t*)(broadcastBuff_ + 7);

	//int count = VSNPRINTFA(broadcastBuff_ + 9,
	//                       sizeof(broadcastBuff_) - 9,
	//                       msgMgr.GetTip(msgId), args);

	//if (count < 0)
	//{
	//	// 格式化不成功
	//	count = 0;
	//}

	//int ret = 9 + count;	// 3字节+sizeof(uint16_t)+count+'\0'
	//*msg_len = (uint16_t)count;
	//broadcastBuff_[ret] = 0;
	//return ret + 1;
}

void GameEngine::GC()
{
	gate_mgr_->GC();
	luamemory::GC();

	//GetFuBenMgr()->GC();

	LogSender* log = ServerInstance()->GetLogClient();

	if (log)
	{
		log->GC();
	}

	DBClient* db = ServerInstance()->GetDbClient();

	if (db) db->GC();
}

//void GameEngine::UpdateCrossGateway(DataPacket& dp)
//{
//	int sid = 0;
//	int count = 0;
//	dp >> sid;
//	dp >> count;
//
//	GameRoute* r = GetGameRoute(sid);
//
//	if (!r)
//	{
//		int newCnt = gateway_routes_.count();
//		gateway_routes_.reserve(newCnt + 1);
//		gateway_routes_.trunc(newCnt + 1);
//		r = &(gateway_routes_[newCnt]);
//		r->sid_ = sid;
//	}
//
//	const int MAXROUTE = sizeof(r->t) / sizeof(r->t[0]);
//	count = __min(count, MAXROUTE);
//
//	r->count_ = count;
//
//	for (int i = 0; i < count; ++i)
//	{
//		dp.readString(r->t[i].host_, sizeof(r->t[i].host_) - 1);
//		dp >> r->t[i].port_;
//	}
//}

void GameEngine::SendActorCrossKey(DataPacket& dp, int sid, int loginType)
{
	GameRoute* r = GetGameRoute(sid);

	if (r && r->count_ > 0)
	{
		// 发给玩家数据
		const char* key = NULL;
		ActorId aid = 0;
		dp >> key >> aid;

		// todo 复用到这里的时候,考虑是否需要获取镜像actor
		Actor* actor = this->entity_mgr_->GetActorPtrById(aid/*, getImage */);

		if (actor)
		{
			int idx = wrand(r->count_);
			static uint8_t hdr[] = { Protocol::CMD_Login, ActorMgr::sCrossKey };
			ActorSendData(actor, 6,
			              dtPointer, (int64_t)hdr, sizeof(hdr),
			              dtInt, sid,
			              dtString, (int64_t)(r->t[idx].host_),
			              dtInt, r->t[idx].port_,
				dtString, (int64_t)key,
				dtInt, loginType);

			// 下线前要马上保存一次数据
			// 如果是从战斗服回到普通服，因为数据基本没什么变化，所以这个倒不用马上保存，因为下线后也会保存的
			// 但是从普通服到战斗服，还是保存一次比较安全
			if (!ServerInstance()->IsBattleSrv())
				actor->SaveDb(false);

			OutputMsg(rmError, "send crosswar key");
		}
		else
		{
			OutputMsg(rmError, "%s:cann't find the actor:%d", __FUNCTION__, aid);
		}
	}
	else
	{
		OutputMsg(rmError, "can not find server: %d gateway route", sid);
	}
}

int GameEngine::Filter(char* pInput)
{
	if (pInput == NULL) return 0;

	int nTotalFilterCount = 0; //共有多少个屏蔽字符

	char* pInputPtr = pInput;
	char* pFilterWord;
	int nFilteWordLen;

	while ((pFilterWord = MatchMBCSFilterWord(filterWords_, pInputPtr, &nFilteWordLen)))
	{
		memset(pFilterWord, '*', nFilteWordLen);
		nTotalFilterCount ++;
		pInputPtr = pFilterWord + nFilteWordLen;
	}

	return nTotalFilterCount;
}

/*
* Comments: 一个字符串是否和谐
* Param char * pInput:字符串指针
* @Return bool:和谐返回true，否则返回false
*/
bool GameEngine::IsStrInvalid(char* pInput)
{
	int nFilteWordLen;

	if (MatchMBCSFilterWord(filterWords_, pInput, &nFilteWordLen))
	{
		return false;
	}

	return true;
}

bool GameEngine::ReloadFilterDb()
{
	if (!FDOP::FileExists((const char*)("data/fw.txt")))
	{
		OutputMsg(rmError, ("No Fw table")); //找不到防沉迷的表
		return false;
	}

	if (filterWords_)
	{
		FreeMBCSFilter(filterWords_);
		filterWords_ = NULL;
	}

	filterWords_ = CreateMBCSFilter(NULL);
	int nCount = LoadMBCSFilterWords(filterWords_, "data/fw.txt");

	OutputMsg(rmError, "ChatManager::ReloadFilterDb:%d loaded FilterWords", nCount);

	return nCount >= 1;
}

GameRoute* GameEngine::GetGameRoute(int sid, bool create)
{
	if (sid <= 0 || sid > MAX_SERVER_ID) return NULL;

	GameRoute* r = gateway_routes_[sid - 1];
	
	if (r == NULL && create) {
		r = (GameRoute*)global_var_->ge_alloc_.AllocBuffer(sizeof(GameRoute));
		gateway_routes_[sid - 1] = r;
		memset(r, 0, sizeof(*r));
	}
	return r;
}


void GameEngine::ActorLogin(GateUser* user, int serverId, const char* pf, const char* pfid, const char* appid)
{
	if (!user || user->closed_) return;

	OutputMsg(rmTip, "actor login actorid=%d, gateuser=%lld",
		user->actor_id_, (long long int)user);

	Actor* actor = entity_mgr_->GetActorPtrById(user->actor_id_);
	if (actor) return;

	EntityHandle handle;
	actor = (Actor*)entity_mgr_->CreateEntity(EntityType_Actor, handle);

	if (actor)
	{
		user->handle_ = handle;

		// 设置玩家所在服务器
		if (!ServerInstance()->IsBattleSrv())
		{
			// 如果玩家回到普通服，serverid就是本服的serverid
			serverId = ServerInstance()->GetServerIndex();
		}
		actor->SetGmLevel(user->gm_);
		actor->SetServerId(serverId);

		actor->Onlogin(user->netid_, user->actor_id_, user->account_id_, user->gm_);
		actor->SetLastLoginIp(user->remote_addr_);
		//static GLOBALCONFIG& gc = GetConfData()->GetGlobalConfig();

		if (pf)
			actor->SetPf(pf);
		if (pfid)
			actor->SetPfid(pfid);
		if (appid)
			actor->SetAppid(appid);

		static ActorMgr* mgr = ServerInstance()->GetActorMgr();
		GameInterMsg msg1;
		msg1.msg_id_ = ActorMgr::imUserChange;
		msg1.data_.cmd_ = gpUserLogin;
		msg1.data_.dbsid_ = user->actor_id_;
		mgr->PostMsg(msg1);
	}
	else
	{
		OutputMsg(rmError, "create actor entity failed, actorid=%d", user->actor_id_);
	}
}

/*void GameEngine::OnActorLogin(GameInterMsg& msg)
{
	GateUser* user = msg.data_.user_;

	if (!user || user->closed_) return;

	OutputMsg(rmTip, "recv actor login msg, actorid=%d, ptr=%lld",
	          user->actor_id_, (long long int)user);

	Actor* actor = entity_mgr_->GetActorPtrById(user->actor_id_);

	if (actor)
	{
		OutputMsg(rmError, "repeat login！actorId=%d,accountid=%d",
		          user->actor_id_, user->account_id_);
		static uint8_t data[3] = { Protocol::CMD_Login, 1,3};
		actor->SendData(data, 3);
		actor->CloseActor("repeat login");

#ifdef OPENLOGTLOG
		static TlogMgr& tlog = GetGameEngine()->GetTlogMgr();
		tlog.LogOffline(*actor, OlServerKill);
#endif
		actor = NULL;
	}

	EntityHandle handle;
	actor = (Actor*)entity_mgr_->CreateEntity(EntityType_Actor, handle);

	if (actor)
	{
		user->handle_ = handle;

		// 设置玩家所在服务器
		if (!ServerInstance()->IsBattleSrv())
		{
			// 如果玩家回到普通服，serverid就是本服的serverid
			msg.data_.serverId_ = ServerInstance()->GetServerIndex();
		}

		actor->SetServerId(msg.data_.serverId_);

		actor->Onlogin(user->netid_, user->actor_id_, user->account_id_, user->gm_);
		actor->SetLastLoginIp(user->remote_addr_);
		//static GLOBALCONFIG& gc = GetConfData()->GetGlobalConfig();

		//if (msg.data_.pf_)
		//{
		//	actor->SetPf(msg.data_.pf_);
		//	ServerInstance()->GetActorMgr()->GetPfAlloc().FreeBuffer(msg.data_.pf_);
		//}

		static ActorMgr* mgr = ServerInstance()->GetActorMgr();
		GameInterMsg msg1;
		msg1.msg_id_ = ActorMgr::imUserChange;
		msg1.data_.cmd_ = gpUserLogin;
		msg1.data_.dbsid_ = user->actor_id_;
		mgr->PostMsg(msg1);
	}
	else
	{
		OutputMsg(rmError, "create actor entity failed, actorid=%d", user->actor_id_);
	}
}
*/

void GameEngine::OnCreateImageActor(GameInterMsg& msg)
{
	int aid = msg.data_.actor_id;
	int sid = msg.data_.sId_;
	Actor* actor = entity_mgr_->GetActorPtrById(aid);
	//if (actor && !actor->IsImage())
	if (actor) return;

	EntityHandle handle;
	actor = (Actor*)entity_mgr_->CreateEntity(EntityType_Actor, handle);

	if (actor)
	{
		DBClient *db = ServerInstance()->GetDbClient(sid);
		if (!db) {
			entity_mgr_->DestroyEntity(handle);
			OutputMsg(rmError, "not dbclient,sid=%d,aid=%d", sid, aid);
			return;
		}

		actor->SetServerId(ServerInstance()->GetServerIndex());
		actor->SetActorId(aid);
		actor->SetImage(true);
		actor->SetImageEndTime(getMiniDateTime() + IMAGE_ACTOR_CACHE_TIME);

#pragma pack(push, 1)
		static struct HDR_DATA {
			ActorId id;
			bool isImage;
		} hdr_data;
#pragma pack(pop)
		hdr_data.id = aid;
		hdr_data.isImage = true;

		db->SendDbServerData(MAKEINT16(siActor, dcQuery), hdr_data);
		GetEntityMgr()->OnActorLogin(actor);
		//OutputMsg(rmTip, "create image actor %d!!!!!", aid);
	}
	else
	{
		OutputMsg(rmError, "create image actor failed, actorid=%d", aid);
	}
}

void GameEngine::OnActorLogout(GameInterMsg& msg)
{
	if (((EntityHandle)msg.data_.handle_).GetType() != EntityType_Actor) {
		OutputMsg(rmTip, "GameEngine::OnActorLogout handle is not actor, account_id:%d", msg.data_.account_id_);
		return;
	}

	Actor* actor = (Actor*) entity_mgr_->GetEntity(msg.data_.handle_);

	if (actor && actor->GetAccountId() == msg.data_.account_id_) {
		actor->CloseActor(msg.data_.fn_, false);
	} else {
		OutputMsg(rmTip, "GameEngine::OnActorLogout not actor or account_id(%d) neq", msg.data_.account_id_);
	}
}

void GameEngine::OnCenterServerMsg(GameInterMsg& msg)
{
	/*DataPacket* packet = (DataPacket*)msg.data_.packet_;
	int cmd = msg.data_.cmd_; 

	if (!packet) return;

	CenterClient* cli = ServerInstance()->GetCenterClient();
	switch (cmd)
	{
		case cwComm:
		{
			ScriptValueList plist;
			static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
			plist << packet;

			if (!lua.Call("OnCenterMsg", &plist, NULL))
			{
				OutputMsg(rmError, "OnCenterMsg error in cmd = %d", cmd);
			}
			break;
		}
		case cwActorServerInfo:
		{
			static GameEngine* engine = GetGameEngine();
			engine->ChangeToOnlineList(*packet);
			break;
		}
	default:
		break;
	}

	cli->FreeBackUserDataPacket(packet);
	*/
}

void GameEngine::OnDbServerMsg(GameInterMsg& msg)
{
	DataPacket* packet = (DataPacket*)msg.data_.packet_;
	int cmd = msg.data_.cmd_;

	if (packet)
	{
		DBClient* db = ServerInstance()->GetDbClient(msg.data_.dbsid_);

		if (!db) return;

		uint8_t cmd_id = HIINT8(cmd);
		uint8_t sys_id = LOINT8(cmd);
		static GameEngine* ge = GetGameEngine();
		int route = ge->db_ret_route[sys_id][cmd_id];

		//route != 0 则由lua处理
		if (route != 0)
		{
			ScriptValueList plist;
			static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
			plist << packet;
			plist << sys_id;
			plist << cmd_id ;


			if (!lua.Call("OnDbRetDispatcher", &plist, NULL))
			{
				OutputMsg(rmError, "OnDbRetDispatcher error in sysid = %d, cmd = %d", sys_id, cmd);
			}

			//处理完数据指针要还回
			db->FreeBackUserDataPacket(packet);
			return;
		}

		if (sys_id == siActor)
		{
			entity_mgr_->OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siGuild)
		{
			//guildMgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siConsignment)
		{
			//consignmentMgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siRank)
		{
			//db_rank_mgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siMsg)
		{
			msgMgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siGlobal)
		{
			//miscMgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siFight)
		{
			//fight_mgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siCommon)
		{
			sysvar_mgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siWarTeam)
		{
			//gamewar_mgr_.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siConfig)
		{
			//dym_item_conf.OnDbReturnData(cmd_id, *packet);
		}
		else if (sys_id == siTxApi)
		{
			entity_mgr_->OnSsReturnData(cmd_id, *packet);
		}

		//处理完数据指针要还回
		db->FreeBackUserDataPacket(packet);
	}
}

void GameEngine::OnGatewayDump(GameInterMsg& msg)
{
	OutputMsg(rmError, "========================recv SSM_GW_DUMP msg!!");

	int gate_idx = msg.data_.account_id_;	// 网关的索引
	entity_mgr_->CloseAllActor(gate_idx);

	OutputMsg(rmError, "=========================gateway disconnect==================");
}

void GameEngine::OnCloseActorById(GameInterMsg& msg)
{
	ActorId aid = (ActorId)msg.data_.handle_;
	Actor* actor = entity_mgr_->GetActorPtrById(aid);

	if (actor) {
		if (!actor->IsImage()) {
			actor->SetKickRelogin(true);
			gate_mgr_->PostCloseUser(actor->GetNetId(), "GameEngine::OnCloseActorById", aid);
		} else {
			actor->CloseActor("GameEngine::OnCloseActorById");
	}
}
}

void GameEngine::OnGameSessionReg(GameInterMsg& msg)
{
	if (!msg.data_.packet_) return;

	DataPacket* dp = msg.data_.packet_;
	dp->setPosition(0);

	int sid = msg.data_.dbsid_;

	int port = msg.data_.cmd_;
	// 连接指定dbserver
	const char* ip = NULL;
	(*dp) >> ip;
	ServerInstance()->AddDbClient(sid, ip, port, true);

	// 发送在线用户给gameclient
	GameConn* conn = (GameConn*)msg.data_.rev_;

	if (conn) {
		if (conn->GetBattleFlag() == bsLianFuSrv) {
			lianfu_mgr_.OnRegReq(sid);
		}

		static ScriptNpc* gn = GetGameEngine()->GetGlobalNpc();

		if (gn) {
		ScriptValueList paras;
		paras << sid;
		paras << conn->GetBattleFlag();	// 是否战斗服
			gn->GetScript().Call("onCrossSrvConnected", &paras, &paras);
}
	}
}

void GameEngine::OnGameClientResp(GameInterMsg& msg)
{
	//当普通服和连服建立连接后，普通服需要把自己的在线玩家信息发给连服,战斗服也发，不限制了
	if (msg.data_.cmd_ == bsLianFuSrv)
	{
		lianfu_mgr_.OnRegResp(msg.data_.dbsid_);
	}

	SetSrvType(msg.data_.dbsid_, msg.data_.cmd_);

	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList paras;
	paras << msg.data_.dbsid_;
	paras << msg.data_.cmd_;	// 是否战斗服
	lua.Call("onCrossSrvConnected", &paras, NULL);
}

//void GameEngine::OnGameSessionGw(GameInterMsg& msg)
//{
//	if (!msg.data_.packet_) return;
//
//	DataPacket* dp = msg.data_.packet_;
//	dp->setPosition(0);
//	UpdateCrossGateway(*dp);
//}

void GameEngine::OnCrosswayKey(GameInterMsg& msg)
{
	if (!msg.data_.packet_) return;

	DataPacket* dp = msg.data_.packet_;
	dp->setPosition(0);
	SendActorCrossKey(*dp, msg.data_.cmd_, msg.data_.param1_);
}

void GameEngine::OnCrossWarMsg(GameInterMsg& msg)
{
	if (!msg.data_.packet_) return;

	int sid = msg.data_.dbsid_;
	DataPacket* dp = msg.data_.packet_;
	dp->setPosition(0);

	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();

	ScriptValueList paras;
	paras << sid;
	paras << msg.data_.cmd_;	// 是否战斗服
	paras << dp;
	lua.Call("OnRecvCrossServerMsg", &paras, NULL);
}

void GameEngine::SetNetMsgRoute(int sysId, int pid, int val)
{
	STATIC_ASSERT(sizeof(net_msg_route[0]) == 256);
	STATIC_ASSERT(sizeof(net_msg_route) == 256 * 256);

	if (sysId >= 0 && sysId <= 255 &&
	        pid >= 0 && pid <= 255)
	{
		if (pid == 0)
		{
			for (size_t i = 0; i < sizeof(net_msg_route[sysId]); ++i)
			{
				net_msg_route[sysId][i] = val;
			}
		}
		else
		{
			net_msg_route[sysId][pid] = val;
		}
	}
}

void GameEngine::OnAsynWorkerMsg(GameInterMsg& msg)
{
	AsyncWorker::CBData* cb = (AsyncWorker::CBData*)msg.data_.ptr_;

	if (cb)
	{
		AsyncWorker::AsyncWorkerAlloc& alloc = cb->worker_->GetAlloc();

		if (cb->after_func_) cb->after_func_(cb);

		if (cb->params_ && cb->free_func_)
		{
			cb->free_func_(cb);
		}

		alloc.FreeBuffer(cb);
	}
}

void GameEngine::PostMsgToGE(void* cb)
{
	// 这个函数必须是线程安全的，因为是在另外的线程调用
	GameInterMsg msg;
	msg.msg_id_ = SSM_WORK_THREAD;
	msg.data_.ptr_ = cb;
	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

void GameEngine::AsyncWorkLuaCallback(void* ptr)
{
	AsyncWorker::CBData* cb = (AsyncWorker::CBData*)ptr;
	AsyncWorker::LuaParams* params = (AsyncWorker::LuaParams*)cb->params_;

	ScriptValueList* arg = NULL;

	if (params)
	{
		arg = &params->result_;
	}

	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	lua.Call("OnAsyncWorkFinish", arg, NULL, 0);
}

ScriptEvent* GameEngine::AllocScriptEvent(SEventHandle& handle)
{
	ScriptEvent* param = NULL;
	param = se_hdl_mgr_.AllocHandle(handle);
	return param;
}

void GameEngine::FreeScriptEvent(SEventHandle& handle)
{
	se_hdl_mgr_.Free(handle);
}

ScriptEvent* GameEngine::GetScriptEvent(const SEventHandle& handle)
{
	return se_hdl_mgr_.GetPtr(handle);
}

bool GameEngine::PostReloadGlobaNpc(EntityHandle hdl, int type)
{
	/*
#ifndef _MSC_VER
	EntityHandle hHandle;
	globalFuncNpc_rese_ = (ScriptNpc*)entity_mgr_->CreateEntity(EntityType_Npc, hHandle);
	globalFuncNpc_rese_->SetEntityName("SYS-FUNCTION_RESE");
	globalFuncNpc_rese_->SetInitFlag(true);

	ScriptNpc* gn = globalFuncNpc_rese_;
	
	bool ret = gn->LoadScript(GlobalScriptFile, true);

	if (!ret)
	{
		Actor* actor = (Actor*)entity_mgr_->GetEntity(hdl);

		if (actor && actor->GetType() == enActor)
		{
			actor->SendTipmsg("reload global npc script fail!!", ttTipmsgWindow);
		}
		return ret;
	}

	entity_mgr_->DestroyEntity(globalFuncNpc_rese_->GetHandle());
	globalFuncNpc_rese_ = NULL;
#endif
*/

	GameInterMsg msg;
	msg.msg_id_ = SSM_RELOAD_GLOBAL_NPC;
	msg.data_.gm_actor_ = hdl;
	msg.data_.type_ = type;
	PostMsg(msg);

	return true;
}

void GameEngine::RunAllTests()
{
	GameInterMsg msg;
	msg.msg_id_ = SSM_RUN_ALL_TESTS;
	PostMsg(msg);
}

bool GameEngine::ReloadGlobalNpc(EntityHandle hdl, int type)
{
	OutputMsg(rmError, "ReloadGlobalNpc Script!");
	bool ret = globalFuncNpc_->LoadScript(GlobalScriptFile, true);

	Actor* actor = (Actor*)entity_mgr_->GetEntity(hdl);

	if (actor && actor->GetType() == enActor)
	{
		const char* msg = ret ? "reload global npc script success!!" :
		                  "reload global npc script fail!!";
		actor->SendTipmsg(msg, ttTipmsgWindow);
	}

	return ret;
}

void GameEngine::SetDbRetRoute(int sysid, int cmd, int val)
{
	STATIC_ASSERT(sizeof(db_ret_route[0]) == 256);
	STATIC_ASSERT(sizeof(db_ret_route) == 256 * 256);

	if (sysid < 0 || sysid >= 256 || cmd < 0 || cmd >= 256)
		return;

	db_ret_route[sysid][cmd] = val ;
}

void GameEngine::OnRunAllTests(GameInterMsg&)
{
#ifdef _MSC_VER
	//RUN_ALL_TESTS();
#endif
}

bool GameEngine::StartOneGameClient(const char * ip, int port, int serverId, int serverType) {
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();

	static BaseAllocator alloc("startOneGameClient");
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()
		->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imAddGameClient;
	msg.data_.packet_ = dp;
	(*dp) << ip << port << serverId;
	mgr->PostMsg(msg);

	AddBattleSrv(serverId, serverType);

	return true;
}

void GameEngine::ResetGameRoute() {
	OutputMsg(rmError, "ResetGameRoute");
	memset(gateway_routes_, 0, sizeof(GameRoute*) * gateway_routes_.count());
}

void GameEngine::ResetSingleGameRoute(int sid) {
	OutputMsg(rmError, "ResetSingleGameRoute sid:%d", sid);
	if (sid <= 0 || sid > MAX_SERVER_ID) return;
	GameRoute* r = gateway_routes_[sid - 1];
	if (r) {
		memset(r, 0, sizeof(GameRoute));
	}
}

void GameEngine::MiscRun()
{
	// 用于检查主线程是否阻塞了
	if (engine_report_t_.CheckAndSet(game_tick_))
	{
		WatchThread* watch = ServerInstance()->GetWatch();

		if (watch) watch->Report(GameServer::wiGame);
	}

	if (gc_t_.CheckAndSet(game_tick_) &&
	        entity_mgr_->GetOnlineActorCount() < gc_actor_cnt_)
		GC();

	static ScriptNpc* gn = GetGameEngine()->GetGlobalNpc();
	if (engine_5s_t_.CheckAndSet(game_tick_))
	{
		// 每5s执行一次
		ScriptValueList vl;
		vl << (unsigned int)getMiniDateTime();
		gn->GetScript().Call("OnGamePrecisionTimer", &vl, &vl);

		CheckRefreshTime();

		//威望回收
		PrestigeHelper::LogicRun(game_tick_);
	}

	if (engine_60s_t_.Check(game_tick_))
	{
		engine_60s_t_.SetNextHitTimeFromNow(game_tick_, (60 - cur_sys_time_.sec_)*1000);//给保证整点
		ScriptValueList paras;
		gn->GetScript().Call("OnGameTimer", &paras, &paras);
	}
}

ActorIdPacket::ActorIdPacket()
: actor_(NULL)
, actor_id_(0)
, dp_(&allocActorIdPacket)
{
}

DataPacket& ActorIdPacket::AllocIdPacket(ActorId aid, Actor* actor /* = NULL */)
{
	actor_ = actor;
	actor_id_ = aid;

	dp_.setPosition(0);
	dp_ << (int)dtToActor;
	dp_ << (ActorId)actor_id_;

	return dp_;
}

void ActorIdPacket::flush()
{
	static GameEngine* engine = GetGameEngine();
	static EntityMgr* em = engine->GetEntityMgr();

	if (!actor_) actor_ = em->GetActorPtrById(actor_id_);

	// 如果在本服, 则直接发送
	if (actor_ && !actor_->IsImage())
	{
		actor_->SendData(dp_.getPositionPtr(HEAD_SIZE), dp_.getLength() - HEAD_SIZE);
		return;
	}

	// 不在连服状态
	static LianfuMgr& lfMgr = engine->GetLianfuMgr();
	if (!lfMgr.IsLianfu()) return;

	static GameServer* gs = ServerInstance();

	int sid = gs->IsLianFuSrv() ? lfMgr.GetOnlineServerId(actor_id_) : lfMgr.GetLianfuSid();

	if (sid <= 0) return;

	ServerInstance()->SendMsgToAllGameClient(dp_.getMemoryPtr(), (size_t)dp_.getLength(),
		InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
}

void GameEngine::OnCrossServerTtMsg(GameInterMsg& msg)
{
	static EntityMgr* em = GetEntityMgr();
	int cmd = msg.data_.param1_;

	static GameServer* gs = ServerInstance();

	DataPacket* packet = (DataPacket*)msg.data_.packet_;
	if (packet)
	{
		packet->setPosition(0);
	}

	int server_id_src = msg.data_.dbsid_;
	int server_id = gs->GetServerIndex();

	switch (cmd)
	{
	case gpTtData:
		if (packet)
		{
			int type = 0;
			*packet >> type;

			if (type == dtToActor)
			{
				ActorId aid = 0;
				*packet >> aid;

				uint8_t* buf = (uint8_t*)packet->getOffsetPtr();
				size_t len = packet->getAvaliableLength();

				Actor* actor = em->GetActorPtrById(aid);
				if (actor)
				{
					actor->SendData((const char*)buf, len);
				}
				else if (gs->IsLianFuSrv())
				{
					int sid = lianfu_mgr_.GetOnlineServerId(aid);
					if (sid != server_id)
					{
						gs->SendMsgToAllGameClient(packet->getMemoryPtr(), (size_t)packet->getLength(),
							InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
					}
				}
			}
			else if (type == dtServerDeal) // 发送给其它服务器处理
			{
				int sid = 0, aid = 0;
				*packet >> sid;
				*packet >> aid;
				if (sid != server_id)
				{
					if (gs->IsLianFuSrv())
					{
						gs->SendMsgToAllGameClient(packet->getMemoryPtr(), (size_t)packet->getLength(),
							InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
					}
					else
					{
						OutputMsg(rmError, "server deal msg error : %d", sid);
					}
				}
				else
				{
					uint8_t* buf = (uint8_t*)packet->getOffsetPtr();
					lf_netmsg_mgr_.ProcessActorNetmsg(aid, buf[0], buf[1], *packet, NULL);
				}
			}
			else if (type == dtActorDeal)
			{
				int tActorId = 0, sActorId = 0;
				*packet >> tActorId;
				*packet >> sActorId;

				bool process = false;
				if (gs->IsLianFuSrv())
				{
					int sid = lianfu_mgr_.GetOnlineServerId(tActorId);
					if (sid > 0 && sid != server_id)
					{
						gs->SendMsgToAllGameClient(packet->getMemoryPtr(), (size_t)packet->getLength(),
							InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
						process = true;
					}
				}

				if (!process)
				{
					uint8_t* buf = (uint8_t*)packet->getOffsetPtr();
					lf_netmsg_mgr_.ProcessActorNetmsg(sActorId, buf[0], buf[1], *packet, NULL);
				}
			}
			else if (type == dtBroadCast)
			{
				BroadCast(packet->getOffsetPtr(), packet->getAvaliableBufLen());

				if (gs->IsLianFuSrv())
				{
					// 广播给所有服
					gs->SendMsgToAllGameClient(packet->getMemoryPtr(), (size_t)packet->getLength(),
						InterSrvComm::GameWorldProto::gpTtData, 0, CROSSSERVER_LIANFU);
				}
			}
			else
			{
				OutputMsg(rmError, "data type error !!!! type %d!", type);
			}
		}
		break;
	case gpSsData:
		if (packet)
		{
			int* buf = (int*)packet->getOffsetPtr();
			packet->adjustOffset(sizeof(int));
			lianfu_mgr_.OnLianfuMsg(server_id_src, buf[0], *packet);
		}
		break;
	case gpLfData:
		if (packet)
		{
			uint8_t* buf = (uint8_t*)packet->getOffsetPtr();
			packet->adjustOffset(2);
			switch (buf[0])
			{
			case lsDefault:
				lianfu_mgr_.ProcessNetData(buf[1], *packet);
				break;
			case lsGuild:
				//lianfu_guild_.ProcessNetData(buf[1], *packet);
				break;
			case lsRank:
				lianfu_rank_.ProcessNetData(buf[1], *packet);
				break;
			}
		}
		break;
	}
}

void OnChangeNameEvent(Actor *actor, int res, const char* name, const char* rawName, int way)
{
	ScriptValueList param;
	actor->InitActorEventParams(param, aeChangeName);
	param << (int)res;
	param << name;
	param << rawName;
	param << way;
	actor->OnEvent(&param);
	actor->SaveDb(true);
}

void GameEngine::OnChangeUserName(GameInterMsg& msg)
{
	DataPacket* packet = (DataPacket*)msg.data_.packet_;

	if (packet)
	{
		packet->setPosition(0);
		int res = 0;
		ActorId rawAid = 0;
		const char* name = NULL;
		const char* rawName = NULL;
		int way = 0;
		*packet >> res;
		*packet >> rawAid;
		*packet >> name;
		*packet >> rawName;
		*packet >> way;

		ActorAsynFunc func = std::bind(OnChangeNameEvent, std::placeholders::_1, res, name, rawName, way);
		GetGameEngine()->GetActorAsynMgr()->RegActorEv(rawAid, func);

		delete packet;
	}

}

void GameEngine::OnCrossRelogin(GameInterMsg& msg) {
	ActorId actorId = msg.data_.actor_id;
	Actor* actor = entity_mgr_->GetActorPtrById(actorId);
	if (!actor) {
		OutputMsg(rmTip, "can not find actor for cross relogin, actorid = %d", actorId);
		return;
	}
	actor->NoticeRelogin();
}

void GameEngine::SendTipWithId(ActorId sActorId, int msgid, int type /* = ttTipmsgWindow */, ...)
{
	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	const char* fmt = mgr.GetTip(msgid);

	if (!fmt) return;

	va_list args;
	va_start(args, type);
	SendTipmsgWithArgs(sActorId, fmt, args, type);
	va_end(args);
}


void GameEngine::SendTipmsgWithArgs(ActorId sActorId, const char* fmt, va_list& args, int type)
{
	if (fmt == NULL) return;

	static char sTipmsg[256];
	VSNPRINTFA(sTipmsg, sizeof(sTipmsg)-1, fmt, args);

	SendTipmsg(sActorId, sTipmsg, type);
}

void GameEngine::SendTipmsg(ActorId sActorId, const char* msg, int type/* = ttTipmsgWindow*/)
{
	//if (msg == NULL) return;

	//static uint8_t data[] = { enChatSystemID, sSendTipmsg, 0};

	//ActorIdPacket ap;
	//DataPacket& pack = ap.AllocIdPacket(sActorId);
	//pack.writeBuf(data, sizeof(data));
	//pack << (int)type;
	//pack.writeString(msg);

	//ap.flush();
}

void GameEngine::SendEnableCheckValid(bool flag)
{
	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siActor, dcEnableCheckValid));
	packet << (uint8_t)(flag ? 1 : 0);

	db->flushProtoPacket(packet);
}


void GameEngine::ChangeToOnlineList(DataPacket& pack)
{
	uint8_t status;
	int actorid, sid;
	pack >> status >> actorid >> sid;
	if (status == 1)
	{
		int* serverid = actor_online_list_.get(actorid);
		if (serverid)
		{
			actor_online_list_.update(actorid, sid);
		}
		else
		{
			actor_online_list_.put(actorid, sid);
		}
	}
	else
	{
		actor_online_list_.remove(actorid);
	}
}

int GameEngine::GetActorInServerId(ActorId aid)
{
	int* serverid = actor_online_list_.get(aid);
	return serverid ? *serverid : 0;
}

void GameEngine::SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw)
{
	_STRNCPY_A(db_host_, host);
	db_port_ = port;
	_STRNCPY_A(db_name_, db_name);
	_STRNCPY_A(db_user_, user);
	_STRNCPY_A(db_pw_, pw);

	SetupSQLConnection(&global_sql_);
}

void GameEngine::SetupSQLConnection(SQLConnection* sql)
{
	sql->SetHost(db_host_);
	sql->SetPort(db_port_);
	sql->SetDbName(db_name_);
	sql->SetUserName(db_user_);
	sql->SetPassWord(db_pw_);
	sql->SetConnectionFlags(CLIENT_FOUND_ROWS | CLIENT_MULTI_RESULTS);
}

void GameEngine::GameInit()
{
	//static GameScript& lua = globalFuncNpc_->GetScript();
	//lua.Call("GameInit", NULL, NULL);

}

bool GameEngine::HasRoute(int serverId)
{
	if (serverId <= 0 || serverId > MAX_SERVER_ID)
	{
		return true;
	}

	GameRoute* route = GetGameRoute(serverId);
	return route && route->sid_ != 0;
}

bool GameEngine::AddRoutes(int serverid, const char* host, int port)
{
	//注意：这里只做增量的更新，不支持旧数据修改，否则有线程安全问题，先这样处理
	if (serverid <= 0 || serverid > MAX_SERVER_ID)
	{
		OutputMsg(rmError, "serverid %d routelist can not add !!!!!!!!!!!!!!!!!!!!!!!!!!!!!", serverid);
		return false;
	}

	GameRoute* route = GetGameRoute(serverid, true);

	const int MAXROUTE = sizeof(route->t) / sizeof(route->t[0]);

	route->sid_ = serverid;
	if (route->count_ < MAXROUTE)
	{
		if (host)
		{
			_STRNCPY_A(route->t[route->count_].host_, host);
		}
		else
		{
			_STRNCPY_A(route->t[route->count_].host_, "");
		}

		route->t[route->count_].port_ = port;

		OutputMsg(rmNormal, ("add route,Host=%s,port=%d,serverid=%d"),
			route->t[route->count_].host_, route->t[route->count_].port_, route->sid_);

		route->count_++;
	}

	return true;
}

void GameEngine::OnAddLoginList(GameInterMsg& msg)
{
	static LoginQueue *login_queue_ = GetGameEngine()->GetLoginQueue();
	login_queue_->AddToQueue(msg.data_.user_, msg.data_.serverId_, msg.data_.pf_, msg.data_.pf_id_, msg.data_.appid_);
}

void GameEngine::SetRedisCfg(const char * host, int port, int db_index, const char * pw)
{
	std::shared_ptr< tg_redis_param> redis_config_ = std::make_shared<tg_redis_param>();
	redis_config_->db_index = db_index;
	redis_config_->host = host;
	redis_config_->port = port;
	redis_config_->pwd = pw;
	redis_config_->timeout.tv_sec = 3;
	redis_config_->timeout.tv_usec = 0;

	if (global_redis_ == nullptr)
	{
		global_redis_ = std::make_shared<CRedisConnect>(redis_config_);
	}

	if (!global_redis_->connect())
	{
		OutputMsg(rmError, ("Redis Not Connected Successful , %s"), global_redis_->get_last_err().c_str());
		return;
	}
	else
	{
		std::cout << "[ Redis ] , Connected Successful ! " << std::endl;
	}
}


