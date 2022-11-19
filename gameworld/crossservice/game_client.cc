#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "game_client.h"

using namespace InterSrvComm::GameWorldProto;

static BaseAllocator alloc("GameClientAlloc");

GameClient::GameClient(GameServer* game_srv) : NetClient("GameClient"), target_sid_(0),
	is_battle_(1)	// gameclietn连接的肯定都是战斗服
{
	game_server_ = game_srv;
	SetClientName(("gameworld"));
	free_.setLock(&lock_);
}

GameClient::~GameClient()
{
	free_.flush();

	for (int i = 0; i < free_.count(); i++)
	{
		DataPacket* dp = free_[i];
		dp->setPosition(0);
		Flush(*dp);
	}

	free_.clear();
}


void GameClient::OnRecv(const uint16_t cmd, char* buf, int size)
{
	DataPacketReader reader(buf, size);
	// OutputMsg(rmTip, "GameClient::OnRecv : %d", cmd);

	switch (cmd)
	{
	case gpRegResp:
		{
			OnRegResp(reader);
		}
		break;

	case gpGateway:
		{
			OnGatewayInfo(reader);
		}
		break;

	case gpUserLogin:
		{
			OnUserLogin(reader);
		}
		break;

	case gpUserExit:
		{
			OnUserExit(reader);
		}
		break;

	case gpBatchOnline:
		{
			OnBatchLogin(reader);
		}
		break;

	case gpCloseUser:
		{
			OnCloseUser(reader);
		}
		break;

	case gpKeyReq:
		{
			OnKeyReq(reader);
		}
		break;

	case gpKeyResp:
		{
			OnKeyResp(reader);
		}
		break;

	case gpCommonMsg:
		{
			OnCommonMsg(reader);
		}
		break;

	case gpTtData:
	case gpSsData:
	case gpLfData:
		{
			OnTtDataToGame(reader, cmd);
		}
		break;

	}
}

void GameClient::OnTtDataToGame(DataPacketReader& reader, uint16_t cmd)
{
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif

	dp->writeBuf(reader.getOffsetPtr(), reader.getAvaliableLength());

	GameInterMsg msg;
	msg.msg_id_ = SSM_CROSSTTMSG_GAME;
	msg.data_.packet_ = dp;
	msg.data_.dbsid_ = target_sid_;
	msg.data_.cmd_ = is_battle_;
	msg.data_.param1_ = cmd;
	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);


}

void GameClient::OnRegResp(DataPacketReader& reader)
{
	reader >> is_battle_;

	static GameEngine* ge = GetGameEngine();
	GameInterMsg msg;
	msg.msg_id_ = SSM_GAMECLIENT_REG;
	msg.data_.dbsid_ = target_sid_;
	msg.data_.cmd_ = is_battle_;
	msg.data_.rev_ = (void*)this;
	ge->PostMsg(msg);
}

void GameClient::OnCommonMsg(DataPacketReader& reader)
{
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif

	dp->writeBuf(reader.getOffsetPtr(), reader.getAvaliableLength());

	GameInterMsg msg;
	msg.msg_id_ = SSM_CROSSWAR_MSG;
	msg.data_.packet_ = dp;
	msg.data_.dbsid_ = target_sid_;
	msg.data_.cmd_ = is_battle_;
	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

void GameClient::OnKeyReq(DataPacketReader& reader)
{
	// 生成一个key到actormgr，并返回结果
	ActorMgr::CrossUserData data;
	reader >> data;

	int err = 0;

	if (data.target_sid_ == ServerInstance()->GetServerIndex())
	{
		static ActorMgr* mgr = ServerInstance()->GetActorMgr();
		BufferAllocator& alloc = mgr->GetAlloc();
		ActorMgr::CrossUserData* cd =
		    (ActorMgr::CrossUserData*)alloc.AllocBuffer(sizeof(data));

		*cd = data;

		GameInterMsg msg;
		msg.msg_id_ = ActorMgr::imAddKey;
		msg.data_.buffdata_ = cd;
		mgr->PostMsg(msg);
	}
	else
	{
		err = 1;
		OutputMsg(rmError, "going to cross %d, but here is %d", data.target_sid_, 
			ServerInstance()->GetServerIndex());
	}

	// 返回结果
	DataPacket& packet = allocProtoPacket(gpKeyResp);
	packet << (int)err;
	packet << data;
	packet << ServerInstance()->GetBattleSrvFlag();
	flushProtoPacket(packet);

	OutputMsg(rmError, "recv crosswar key:%s,ActorID=%d", data.key_, data.actorId_);
}

void GameClient::OnKeyResp(DataPacketReader& reader)
{
	// 通知客户端
	int err = 0;
	int srvType = 0;
	ActorMgr::CrossUserData data;
	reader >> err;
	reader >> data;
	reader >> srvType;

	if (err != 0)
	{
		OutputMsg(rmError, "send crosswar key err:%d", err);
		return;
	}

	// serverid, ip, port, key
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif

	(*dp) << data.key_ << (ActorId)data.actorId_;

	//if (data.cross_type_ == CROSSLOGINTYPE_ENTERGAME)
	//{
		GameInterMsg msg;
		msg.msg_id_ = SSM_CROSSWAR_KEY;
		msg.data_.packet_ = dp;
		msg.data_.cmd_ = target_sid_;
		msg.data_.param1_ = srvType;
		//msg.data_.param1_ = (IsLianfuClient() ? CROSSLOGIN_LIANFU : CROSSLOGIN_CROSSWAR) ;
		static GameEngine* ge = GetGameEngine();
		ge->PostMsg(msg);
	//}
	//else if (data.cross_type_ == CROSSLOGINTYPE_NOTENTERGAME)
	//{
	//	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	//	BufferAllocator& alloc = mgr->GetAlloc();
	//	ActorMgr::CrossUserData* cd =
	//		(ActorMgr::CrossUserData*)alloc.AllocBuffer(sizeof(data));

	//	*cd = data;

	//	GameInterMsg msg;
	//	msg.msg_id_ = ActorMgr::imGetKeyResp;
	//	msg.data_.buffdata_ = cd;
	//	mgr->PostMsg(msg);
	//}
	//else
	//{
	//	OutputMsg(rmError, " actorid %d, cross type %d, target id %d !", data.actorId_, data.cross_type_, target_sid_ );
	//}

	OutputMsg(rmError, "recv crosswar key resp");
}

void GameClient::OnCloseUser(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static GameEngine* ge = GetGameEngine();
	GameInterMsg msg;
	msg.msg_id_ = SSM_CLOSE_ACTOR_BY_ID;
	msg.data_.handle_ = aid;
	ge->PostMsg(msg);
}

void GameClient::OnUserLogin(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imAddOnline;
	msg.data_.handle_ = MAKEINT64(target_sid_, aid);
	mgr->PostMsg(msg);
}

void GameClient::OnUserExit(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imRemoveOnline;
	msg.data_.handle_ = aid;
	mgr->PostMsg(msg);
}

void GameClient::OnBatchLogin(DataPacketReader& reader)
{
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif

	(*dp) << (int)target_sid_;
	dp->writeBuf(reader.getOffsetPtr(), reader.getAvaliableLength());

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imBatchOnline;
	msg.data_.packet_ = dp;
	mgr->PostMsg(msg);
}

void GameClient::OnGatewayInfo(DataPacketReader& reader)
{
	static GameEngine* ge = GetGameEngine();
#ifndef TEST_CROSS_MEM
	DataPacket* gp = new DataPacket(&alloc);
#else
	DataPacket* gp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(gp)DataPacket(&alloc);
#endif

	*gp << (int)target_sid_;

	int count = 0;
	reader >> count;
	count = __min(count, 4);
	*gp << (int)count;

	for (int i = 0; i < count; ++i)
	{
		const char* host = NULL;
		int port = 0;

		reader >> host >> port;
		*gp << (host ? host : "") << (int)port;
	}

	GameInterMsg msg;
	msg.msg_id_ = SSM_GAMESESSION_GATEWAY;
	msg.data_.packet_ = gp;
	ge->PostMsg(msg);
}

void GameClient::FreeBackUserDataPacket(DataPacket* pack)
{
	free_.append(pack);
}

int GameClient::GetLocalServerType()
{
	return T_GameServer;
}

const char* GameClient::GetLocalServerName()
{
	return game_server_->getServerName();
}

int GameClient::GetLocalServerIndex()
{
	return game_server_->GetServerIndex();
}

void GameClient::OnConnected()
{
	// 发送本服的数据
	DataPacket& pack = allocProtoPacket(gpRegReq);

	pack << (int)ServerInstance()->GetServerIndex();
	pack << (int)(ServerInstance()->GetBattleSrvFlag() ? 1 : 0);
	// 发送本服的dbserver的参数过去
	DBClient* db = ServerInstance()->GetDbClient();

	if (db)
	{
		const char* dbip = db->GetHost();
		int port = db->GetPort();

		pack << dbip << (int)port;
	}

	flushProtoPacket(pack);
}

void GameClient::OnDisconnected()
{
	OutputMsg(rmTip, "local client(%s:%d) disconnect", GetHost(), GetPort());
//	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
//	static BaseAllocator alloc("delOneGameClient");
//#ifndef TEST_CROSS_MEM
//	DataPacket* dp = new DataPacket(&alloc);
//#else
//	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
//	new(dp)DataPacket(&alloc);
//#endif
//	GameInterMsg msg;
//	msg.msg_id_ = ActorMgr::imDelGameClient;
//	msg.data_.packet_ = dp;
//	(*dp) << target_sid_;
//	mgr->PostMsg(msg);
}

DataPacket* GameClient::AllocPostPacket()
{
	if (free_.count() <= 0)
	{
		free_.flush();
	}

	if (free_.count() <= 0)
	{
		AllocSendPack(&free_, 512);
	}

	DataPacket* dp = free_.pop();
	dp->setLength(0);
	return dp;
}

DataPacket& GameClient::allocProtoPacket(uint16_t cmd)
{
	return WorkSocket::allocProtoPacket(cmd);
}

void GameClient::printStat()
{
}

bool GameClient::IsLianfuClient()
{
	//return is_battle_ == GameServer::bsLianFuSrv;
	return false;
}


