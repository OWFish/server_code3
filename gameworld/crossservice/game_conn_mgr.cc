#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "game_conn_mgr.h"

using namespace InterSrvComm::GameWorldProto;

static BaseAllocator alloc("GameConnMgr");

GameConnMgr::GameConnMgr(GameServer* srv) : ServerSocket("GameConnMgr")
{
	SetServiceName("battleworld");
	srv_ = srv;
}

GameConnMgr::~GameConnMgr()
{
	msg_list_.flush();

	for (int i = 0; i < msg_list_.count(); ++i)
	{
		APPINTERNALMSG& msg = msg_list_[i];

		if (msg.msg_ == gcBroadCast || msg.msg_ == gcReg)
		{
			DataPacket* dp = (DataPacket*)msg.p2_;
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
	}

	msg_list_.clear();
}

NetSession* GameConnMgr::NewSession(SOCKET nSocket, sockaddr_in* pAddrIn)
{
	NetSession* ret = new GameConn(this, nSocket, pAddrIn);
	ret->UseBaseAlloc(true);
	return ret;
}

void GameConnMgr::DestroyConnection(NetSession* client)
{
	// 断开连接后的处理

	// ServerSocket释放内存
	ServerSocket::DestroySession(client);
}

void GameConnMgr::ProcessClients()
{
	LOGTIME_BEGIN
	LOGTIME
	ServerSocket::ProcessClients();
	LOGTIME
	LOGTIME_END("GameConnMgr_ProcessClients", DEBUG_LOG_MAX_TIME)
}

void GameConnMgr::OnRecvSysMsg(UINT uMsg, size_t uParam1, size_t uParam2, size_t uParam3, size_t uParam4)
{
	switch (uMsg)
	{
	case gcReg:
		{
			int sid = (int)uParam1;
			int para = (int)uParam3;
			DataPacket* dp = (DataPacket*)uParam2;
			int isBattle = LOINT16(para);
			int port = HIINT16(para);

			GameConn* conn = (GameConn*)uParam4;

			// 检查是否有重复serverid的连接
			if (conn && !HasGameConnect(sid, conn))
			{
				// 给游戏主线程发个消息，连接到这个dbserver
				conn->SetTargetSid(sid);
				conn->SetBattleFlag(isBattle);

				static GameEngine* ge = GetGameEngine();
				GameInterMsg msg;
				msg.msg_id_ = SSM_GAMESESSION_REG;
				msg.data_.packet_ = dp;
				msg.data_.cmd_ = port;
				msg.data_.rev_ = (void*)conn;
				msg.data_.dbsid_ = sid;
				ge->PostMsg(msg);
			}
			else
			{
#ifndef TEST_CROSS_MEM
				delete dp;
#else
				dp->~DataPacket();
				ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
				OutputMsg(rmError, "GameConnMgr::OnRecvSysMsg err! uParam1=%d, hasGameConnect%s", uParam1, 
					conn ? (HasGameConnect(sid, conn) ? "hasAddConn":"notAddConns") : "notConn");
#endif
			}
		}
		break;

	case gcBroadCast:
		{
			DataPacket* dp = (DataPacket*)uParam2;
			int sid = (int)uParam3;
			PostMsgToAllGameWorld((int)uParam1, dp->getMemoryPtr(), dp->getPosition(), sid);
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
		break;

	case gcUserChange:
		{
			ActorId aid = (ActorId)uParam2;
			PostMsgToAllGameWorld((int)uParam1, &aid, sizeof(aid), 0);
		}
		break;

	}
}

bool GameConnMgr::HasGameConnect(int sid, GameConn* conn)
{
	for (int i = 0; i < session_list_.count(); ++i)
	{
		GameConn* client = (GameConn*)session_list_[i];

		if (client && conn != client && client->GetTargetSid() == sid)
		{
			return true;
		}
	}

	return false;
}

void GameConnMgr::OnServerStop()
{
	ServerSocket::OnServerStop();

	//强制释放所有客户端连接占用的内存（销毁连接对象）
	FreeAllClient();
}

void GameConnMgr::SingleRun()
{
	LOGTIME_BEGIN
	LOGTIME

	_M_DBGFUNC_BEGIN
	ServerSocket::SingleRun();
	_M_DBGFUNC_END

	LOGTIME
	LOGTIME_END("GameConnMgr_SingleRun", DEBUG_LOG_MAX_TIME)
}

void GameConnMgr::OnRun()
{

}


void GameConnMgr::FreeAllClient()
{
	//关闭所有客户端
	CloseAllClients();
}

void GameConnMgr::OnServerStart()
{

}

void GameConnMgr::PostMsgToAllGameWorld(int cmd, void* buff, size_t size, int sid)
{
	//bool send = false;
	for (int i = session_list_.count() - 1; i > -1; --i)
	{
		NetSession* cli = session_list_[i];

		// 删除断开的连接
		if (cli && cli->connected() && (sid <= 0 || sid == cli->getClientServerIndex()))
		{
			DataPacket& sendDp = cli->allocProtoPacket((uint16_t)cmd);
			sendDp.writeBuf(buff, size);
			cli->flushProtoPacket(sendDp);
			//send = true;

			if (sid != 0) break;
		}
	}
	//if (send) 
	//	OutputMsg(rmError, "GameConnMgr::PostMsgToAllGameWorld ok! cmd=%d", cmd);
}
