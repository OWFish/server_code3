#ifndef _ACTOR_MGR_FUN_H_
#define _ACTOR_MGR_FUN_H_

//tolua_begin
/*
	�����û�������ɫ��ѡ���ɫ�ǲ��ֵĹ���
	!!!ע�⣬����ĺ������ñ����ActorMgr��ͬһ���߳�!!!!
*/

namespace LActorMgr
{
// ������ݿ�Ĳ�����
void* getDbConn();

// ���һ����ʱ��datapacket
void* getDataPacket();

void SendToGate(void* netid, void* dp);

const char* lowerCaseNameStr(const char* name);

bool checkNameStr(const char* name);

bool nameHasUser(const char* name);

int createActor(int accountid, const char* accountname, const char* name, int sex, int job,int headimage, int& actor_id, const char* pfid, void* gateuser);

void enterGame(void* user, int actor_id, const char* pf, const char* pfid, const char* appid);
const char* getRandomName(int sex);
bool isLoginBattle(int aid);

int isLogoutBattle(int aid);

// actormgr ��½������������
bool LoginOtherSrv(void* user, int srvId, int actorId);
bool LoginLianfuSrv(void* user, int actorId);

};


//tolua_end

#endif

