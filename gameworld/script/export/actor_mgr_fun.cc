#include "StdAfx.h"
#ifndef _MSC_VER
#include "../../StdAfx.h"
#endif

#include "../interface/actor_mgr_fun.h"


namespace LActorMgr
{
void* getDbConn()
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->GetDbConn();
}

void* getDataPacket()
{
	static BaseAllocator alloc("ActorMgr::alloc");
	static DataPacket packet(&alloc);
	packet.setLength(0);
	return &packet;
}

void SendToGate(void* netid, void* dp)
{
	if (!dp || !netid) return;

	DataPacket* senddp = (DataPacket*)dp;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	mgr->SendToGate(*((NetId*)netid), senddp->getMemoryPtr(), senddp->getPosition());
}

const char* lowerCaseNameStr(const char* name)
{
	if (!name) return "";

	static char ret[128];
	SNPRINTFA(ret, sizeof(ret), "%s", name);
	ActorMgr::LowerCaseNameStr(ret);
	return ret;
}

bool checkNameStr(const char* name)
{
	if (!name) return false;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->CheckNameStr(name);
}

bool nameHasUser(const char* name)
{
	if (!name) return false;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->NameHasUser(name);
}

int createActor(int accountid, const char* accountname,  const char* name, int sex, int job, int headimage, int& actor_id, const char* pfid, void* gateuser)
{
	if (!name) return false;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->CreateActor(accountid, accountname, name, sex, job, headimage,actor_id, pfid, (GateUser*)gateuser);
}

void enterGame(void* user, int actor_id, const char* pf, const char* pfid, const char* appid)
{
	if (!user) return;

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	mgr->EnterGame((GateUser*)user, actor_id, pf, pfid, appid, ServerInstance()->GetServerIndex());
}

const char* getRandomName(int sex)
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->GetRandomName(sex);
}

bool isLoginBattle(int aid)
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->IsLoginBattle(aid);
}

int isLogoutBattle(int aid)
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	return mgr->IsLogOutBattle(aid);
}

bool LoginOtherSrv(void* user, int srvId, int actorId)
{
	if (!user) return false;
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	int flag = mgr->LoginOtherSrv((GateUser*)user, srvId, actorId);
	return flag == 0;
}

bool LoginLianfuSrv(void* user, int actorId)
{
	if (!user) return false;
	static GameEngine* ge = GetGameEngine();

	int sid = ge->GetSrvByType(bsLianFuSrv);
	if (sid <= 0) return false;

	return LoginOtherSrv(user, sid, actorId);
}

};

