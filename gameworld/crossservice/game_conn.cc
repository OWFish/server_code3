#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::GameWorldProto;

static BaseAllocator alloc("GameConnAlloc");

GameConn::GameConn(GameConnMgr* mgr, SOCKET s, sockaddr_in* addr)
	: Inherited("GameConn"), target_sid_(0)
{
	SetClientSocket(s, addr);
	srv_name_[0] = 0;
	client_mgr_ = mgr;
}

GameConn::~GameConn()
{

}

void GameConn::OnDisconnected()
{
	OutputMsg(rmWarning, "client(%s:%d) disconnect", GetRemoteHost(), GetRemotePort());
}

void GameConn::OnRecvSysMsg(UINT, size_t, size_t, size_t, size_t)
{

}

void GameConn::OnRun()
{

}

void GameConn::OnRecv(const uint16_t cmd, char* buf, int size)
{
	DataPacketReader reader(buf, size);

	// OutputMsg(rmTip, "GameConn::OnRecv : %d", cmd);

	switch (cmd)
	{
	case gpRegReq:
		{
			OnRegReq(reader);
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

	case gpCloseUser:
		{
			OnCloseUser(reader);
		}
		break;

		// gameconn不会收到这个消息
	case gpBatchOnline:
		{
			OnBatchLogin(reader);
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
			OnCommonMssg(reader);
		}
		break;

	case gpTtData:
	case gpSsData:
	case gpLfData:
		{
			OnTtDataToGame(reader, cmd);
		}
		break;
	case gpCrossRelogin:
		{
			OnCrossRelogin(reader);
		}
		break;
	}
}

void GameConn::OnBatchLogin(DataPacketReader& reader)
{

}

void GameConn::OnTtDataToGame(DataPacketReader& reader, uint16_t cmd)
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

void GameConn::OnCrossRelogin(DataPacketReader &reader)
{
	ActorId actorId;
	reader >> actorId;

	GameInterMsg msg;
	msg.msg_id_ = SSM_CROSS_RELOGIN;
	msg.data_.actor_id = actorId;
	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

void GameConn::OnCommonMssg(DataPacketReader& reader)
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


void GameConn::OnKeyReq(DataPacketReader& reader)
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
	}

	// 返回结果
	DataPacket& packet = allocProtoPacket(gpKeyResp);
	packet << (int)err;
	packet << data;
	packet << ServerInstance()->GetBattleSrvFlag();
	flushProtoPacket(packet);

	//OutputMsg(rmError, "recv crosswar key:%s", data.key_);
}

void GameConn::OnKeyResp(DataPacketReader& reader)
{
	// 通知客户端
	int err = 0;
	int srvType = 0;
	ActorMgr::CrossUserData data;
	reader >> err;
	reader >> data;
	reader >> srvType;

	if (err !=  0)
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
		//msg.data_.param1_ = (ServerInstance()->IsLianFuSrv() ? CROSSLOGIN_LIANFU : CROSSLOGIN_CROSSWAR);
		static GameEngine* ge = GetGameEngine();
		ge->PostMsg(msg);
	//}
	//else
	//{
	//	//在非普通服，理论上不应该走到这里
	//	OutputMsg(rmError, " actorid %d, cross type %d, target id %d !", data.actorId_, data.cross_type_, target_sid_ );
	//}
	//OutputMsg(rmError, "recv crosswar key resp");
}

void GameConn::OnCloseUser(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static GameEngine* ge = GetGameEngine();
	GameInterMsg msg;
	msg.msg_id_ = SSM_CLOSE_ACTOR_BY_ID;
	msg.data_.handle_ = aid;
	ge->PostMsg(msg);
}

void GameConn::OnUserLogin(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imAddOnline;
	msg.data_.handle_ = MAKEINT64(target_sid_, aid);
	mgr->PostMsg(msg);
}

void GameConn::OnUserExit(DataPacketReader& reader)
{
	ActorId aid = 0;
	reader >> aid;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imRemoveOnline;
	msg.data_.handle_ = aid;
	mgr->PostMsg(msg);
}
void GameConn::OnGatewayInfo(DataPacketReader& reader)
{
	// 把网关的信息发给gameengine
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

void GameConn::OnRegReq(DataPacketReader& reader)
{
	int sid = 0;
	reader >> sid;
	reader >> is_battle_;
	const char* dbip = NULL;
	int port = 0;
	reader >> dbip >> port;

	// 发送信息到gameconnmgr
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif
	(*dp) << (dbip ? dbip : "");
	dp->setPosition(0);
	int para = MAKEINT32(is_battle_, port);

	if (ServerInstance()->IsBattleSrv())
		client_mgr_->PostMsg(GameConnMgr::gcReg, sid, (size_t)dp, para, (size_t)this);

	DataPacket& pack = allocProtoPacket(gpRegResp);
	pack << (int)ServerInstance()->GetBattleSrvFlag();
	flushProtoPacket(pack);
}

bool GameConn::OnValidateRegData(const SrvDef::PSERVER_REGDATA pRegData)
{
	return (pRegData->GameType == SERVER_REGDATA::GT_ID &&
	        (pRegData->ServerType == T_GameServer));
}

