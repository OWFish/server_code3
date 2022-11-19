#ifndef _ACTOR_MGR_FUN_H_
#define _ACTOR_MGR_FUN_H_

//tolua_begin
/*
	用于用户创建角色和选择角色那部分的功能
	!!!注意，这里的函数调用必须和ActorMgr是同一个线程!!!!
*/

namespace LActorMgr
{
// 获得数据库的操作类
void* getDbConn();

// 获得一个临时的datapacket
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

// actormgr 登陆到其他服务器
bool LoginOtherSrv(void* user, int srvId, int actorId);
bool LoginLianfuSrv(void* user, int actorId);

};


//tolua_end

#endif

