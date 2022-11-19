#include "stdafx.h"
#include <ctype.h>
#include <time.h>
#include "utils/fdop.h"

using namespace InterSrvComm::CenterProto;

CenterServer::CenterServer(void) : ServerSocket("CenterServer"),
	alloc_("alloc_")
{
	conf_.ReadConfig();

	// 设置服务器的基本属性
	SetServiceName(conf_.szServiceName);
	SetServiceHost(conf_.szAddr);
	SetServicePort(conf_.nPort);
}

CenterServer::~CenterServer(void)
{

}

NetSession* CenterServer::NewSession(SOCKET socket, sockaddr_in* addrin)
{
	if (addrin == NULL)
	{
		return NULL;
	}

	GameSession* client = new GameSession(this, socket, addrin);
	client->setRecvBufSize(1024 * 1024);
	client->setSendBufSize(1024 * 1024);
	return client;
}

bool CenterServer::DoStartup()
{
//	int err = 0;
//
//	pt_runing_ = true;
//#ifdef _MSC_VER
//	pTThread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CenterThread, this, 0, NULL);
//
//	if (!pTThread_)
//	{
//		err = GetLastError();
//	}
//
//#else
//
//	if (pthread_create(&pTThread_, NULL, CenterThread, this))
//	{
//		err = errno;
//	}
//
//#endif
//
//	if (err)
//	{
//		OutputError(err, ("create thread fail！"));
//		return false;
//	}
//
//	OutputMsg(rmTip, ("create thread succ！"));
//	pt_free_ = false;
//
	return true;
}

void CenterServer::DoStop()
{
//	pt_runing_ = false;
//
//	while (!pt_free_)
//	{
//		Sleep(100);
//	}
//
//#ifdef _MSC_VER
//	CloseThread(pTThread_);
//#endif
}


#ifdef _MSC_VER
void CenterServer::CenterThread(CenterServer* ptr)
#else
void* CenterServer::CenterThread(void* ptr)
#endif
{
	//CenterServer* srv = (CenterServer*)ptr;

	//while (srv->pt_runing_)
	//{
	//}

	//srv->pt_runing_ = false;//标记接受连接的线程已经退出
	//srv->pt_free_ = true;
#ifdef _MSC_VER
	ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

void CenterServer::RemoveClientId(int sid)
{
	all_client_list_.remove(sid);
}

GameSession* CenterServer::GetGameSession(int sid)
{
	GameSession** gs = all_client_list_.get(sid);
	return gs ? *gs : NULL;
}

void CenterServer::AddNewGameSession(int sid, GameSession* gs)
{
	if (!gs) return;

	all_client_list_.put(sid, gs);
}

void CenterServer::SendToGameworld(int src, const char* buf, int size)
{
	if (size < (int)sizeof(int)) return;

	int sid = *(int*)buf;
	buf += sizeof(int);
	size -= sizeof(int);

	if (sid != 0)
	{
		GameSession* gs = GetGameSession(sid);

		SendToGameworld(gs, src, buf, size);
	}
	else
	{
		// 广播给所有的服务器
		for (int i = 0; i < session_list_.count(); ++i)
		{
			GameSession* gs = (GameSession*)session_list_[i];
			SendToGameworld(gs, src, buf, size);
		}
	}
}

void CenterServer::SendToGameworld(GameSession* gs, int src, const char* buf, int size)
{
	if (!gs) return;

	DataPacket& pack = gs->allocProtoPacket(cwComm);
	pack << (int)(src);	// 来源
	pack.writeBuf(buf, size);
	gs->flushProtoPacket(pack);
}

void CenterServer::HandleActorOnline(int src, const char* buf, int size)
{
	if (size < (int)sizeof(int)) return;

	int serverid = *(int*)buf;
	buf += sizeof(int);
	size -= sizeof(int);

	GameSession* gs = GetGameSession(serverid);
	if (gs)
	{
		DataPacket& pack = gs->allocProtoPacket(cwActorServerInfo);
		pack.writeBuf(buf, size);
		gs->flushProtoPacket(pack);
	}

	uint8_t status = *(uint8_t*)buf;
	buf += sizeof(uint8_t);
	int actorid = *(int*)buf;

	if (status == 1)
	{
		ActorOnline data;
		data.actorid_ = actorid;
		data.sid_ = src;
		int idx = actor_online_list_.find(data);

		if (idx >= 0)
		{
			actor_online_list_[idx] = data;
		}
		else
		{
			actor_online_list_.add_item(data);
		}
	}
	else
	{
		ActorOnline data;
		data.actorid_ = actorid;
		actor_online_list_.remove_item(data);
	}
}

void CenterServer::SendToActorServer(int src, const char* buf, int size)
{
	if (size < (int)sizeof(ActorId)) return;

	ActorId actorid = *(ActorId*)buf;
	buf += sizeof(ActorId);
	size -= sizeof(ActorId);

	ActorOnline data;
	data.actorid_ = actorid;

	int idx = actor_online_list_.find(data);

	if (idx < 0)
	{
		GameSession* gs = GetGameSession(src);
		SendToGameworld(gs, 0, buf, size);
		return;
	}
	int sid = actor_online_list_[idx].sid_;

	GameSession* gs = GetGameSession(sid);
	SendToGameworld(gs, src, buf, size);
}



