#include "StdAfx.h"
#include <time.h>
#include <ctype.h>

#include "../interface/system_export_fun.h"
#include "netmsg_dispatcher.h"
#include "actor/actor_data_mgr.h"

#include "mail/mail.h"
#include "mail/mail_system.h"
#include "mail/mail_pool.h"
#include "timedomain/time_domain_helper.h"
#include "timedomain/time_domain.h"
#include "skirmish/skirmish.h"
#include "prestige/prestige_helper.h"
#include "actor/actor_asyn_mgr.h"
#include "monster/monster_config.h"
#include "item/item_config.h"
#include "malloc.h"


using namespace stream;
using namespace InterSrvComm::CenterProto;

int print(lua_State* L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");

	for (i = 1; i <= n; i++)
	{
		const char* s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */

		if (s == NULL)
			return luaL_error(L, LUA_QL("tostring") " must return a string to " LUA_QL("print"));
	/*
#ifdef _MSC_VER
			//OutputMsg(rmError, "%s:%s:%s",
			//	ar.what, ar.namewhat, ar.name ? ar.name : "<NA>");

		lua_Debug ar;
		if (lua_getstack(L, (int)1, &ar)) {
			lua_getinfo(L, "Snl", &ar);
			OutputMsg(rmNormal, "%s[%d]:%s",ar.short_src, ar.currentline, s);
		} else {
			OutputMsg(rmNormal, s);
		}
#else
		OutputMsg(rmNormal, s);
#endif
*/
#ifdef _MSC_VER
		lua_Debug ar;
		if (strlen(s) < 10 && lua_getstack(L, (int)1, &ar)) {
			lua_getinfo(L, "Snl", &ar);
			OutputMsg(rmNormal, "%s[%d]:%s", ar.short_src, ar.currentline, s);
		} else {
			OutputMsg(rmNormal, s);
		}
#else
		OutputMsg(rmNormal, s);
#endif
		lua_pop(L, 1);  /* pop result */
	}

	return 0;
}

namespace System
{

int version()
{
	return GAMEWORLD_VERSION;
}

/*
* Comments: 获取服务器的名字
* @Return char *:返回服务器的名字
*/
char* getServerName()
{
	return (char*)ServerInstance()->getServerName();
}

/*
* Comments: 获取服务器的ID
* @Return int: 返回服务器的id
*/
int getServerId()
{
	return ServerInstance()->GetServerIndex();
}

int getWebServer(lua_State* L)
{
	int port = 0;
	const char* host = ServerInstance()->GetWebServer(port);
	lua_pushstring(L, host);
	lua_pushnumber(L, port);
	return 2;
}

bool isServerStarted()
{
	return ServerInstance()->Engine()->IsStarted();
}

/*
* Comments: 获取当前的年月日
  调用方法: nYear,nMonth,nDay = System.getTime( nYear,nMonth,nDay )
* Param int & nYear: 年
* Param int & nMonth:月
* Param int & nDay:日
* @Return void:
*/
int getDate(lua_State* L)
{
	SystemTime& sysTime = GetGameEngine()->getSysTime();
	lua_pushinteger(L, sysTime.year_);
	lua_pushinteger(L, sysTime.mon_);
	lua_pushinteger(L, sysTime.mday_);
	return 3;
}

/*
* Comments: 获取当前的小时 ，分钟，秒数
调用方法: nHour,nMinute,nSecond = System.getTime(nHour,nMinute,nSecond )
* Param int & nHour:小时
* Param int & nMinute:分钟
* Param int & nSecond:秒
* @Return void:
*/
int getTime(lua_State* L)
{
	SystemTime& sysTime = GetGameEngine()->getSysTime();
	lua_pushinteger(L, sysTime.hour_);
	lua_pushinteger(L, sysTime.min_);
	lua_pushinteger(L, sysTime.sec_);
	return 3;
}

const char* getUnixTime()
{
	unsigned long long ftime = ServerInstance()->getUnixTime();
	static char timeStr[32];
	SNPRINTFA(timeStr, sizeof(timeStr), I64FMT, ftime);
	return timeStr;
}

/*
* Comments:获取当前是一周的第几天
* @Return int:返回一个星期的第几天
*/
int getDayOfWeek()
{
	SystemTime& sysTime = GetGameEngine()->getSysTime();
	return sysTime.wday_;
}

/*
* Comments:获取当前的时间滴答（开机以来）
* @Return Uint64:返回当前的时间滴答
*/
unsigned long long getTick()
{
	return _getTickCount();
}

/*
* Comments:获取一个取模nModule的随机数
* Param int nModule: 模数
* @Return int: 返回取模后的随机数
*/
unsigned int getRandomNumber(int nModule)
{
	if (nModule <= 0)return 0;

	return ((unsigned int) wrandvalue() + (unsigned int)_getTickCount()) % (unsigned int) nModule;
}

/*
* Comments: 按场景的名字和位置传送实体
* Param CEntity * pEntity:实体的指针
* Param char * sSceneName:  场景的名字
* Param int nPosX:坐标x
* Param int nPosY:坐标y
* @Return bool: 成功返回true，否则返回false
*/
bool telportSceneByName(void* et, char* sceneName, int x, int y)
{
	//if (et == NULL || sceneName == NULL)return false;

	//return ((Entity*)et)->TelportSceneByName(sceneName, x, y);
	return false;
}

//int getSceneIdByName(const char* sName)
//{
//	if (sName == NULL) return -1;
//
//	FuBen* pRetFb = NULL;
//	Scene* pRetScene = NULL;
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//	mgr->GetFbPtrBySceneName(sName, pRetFb, pRetScene);
//
//	return pRetScene == NULL ? -1 : pRetScene->GetSceneId();
//}
//
//bool telportScene(void* pEntity, int nSceneId, int nPosX, int nPosY)
//{
//	if (pEntity == NULL || nSceneId < 0) return false;
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//	return mgr->EnterFuBen((Entity*)pEntity, NULL, nSceneId, nPosX, nPosY);
//}
//
//bool teleportInScene(void* et, int x, int y, int px, int py, bool teleport)
//{
//	if (!et) return false;
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//	Entity* entity = (Entity*)et;
//	return mgr->EnterFuBen(entity, entity->GetFuBen(), entity->GetSceneID(), x, y, px, py, teleport);
//}
//
//bool telportFuBenScene(void* et, unsigned int fbHandle, int sceneId, int posX, int posY)
//{
//	if (!et || sceneId < 0) return false;
//
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//	return mgr->EnterFuBen((Entity*)et, fbHandle, sceneId, posX, posY);
//}

/*
* Comments: 传送到场景的默认点
* Param CEntity * pEntity: 实体的指针
* Param char * sSceneName:场景的名字
* Param int nPointID:默认点的ID
* @Return bool: 成功返回true，否则返回false
*/
bool telportSceneDefaultPoint(void* pEntity, char* sSceneName, int nPointID)
{
//	if (pEntity == NULL || sSceneName == NULL) return false;

//	return ((Entity*)pEntity)->TelportSceneDefaultPoint(sSceneName, nPointID);
	return false;
}

/*
* Comments: 打印调试信息
* Param char * str: 调试信息
* @Return void:
*/
void trace(char* str)
{
	if (str == NULL) return;

	OutputMsg(rmTip, "[Script Trace]%s", str);
}

bool deepCreateDirectory(const char* sDirName)
{
	return FDOP::DeepCreateDirectory(sDirName);
}

bool fileExists(const char* sFilePath)
{
	return FDOP::FileExists(sFilePath);
}

unsigned int getNowTime()
{
	static GameEngine* ge = GetGameEngine();
	return ge->getMiniDateTime();
}

unsigned int encodeTime(int systime)
{
	SecondTime st;
	return st.encode(systime);
}

unsigned int getWeekDataTime(int y, int m, int d)
{
	struct tm tmResult;
	memset(&tmResult, 0, sizeof(tmResult));

	tmResult.tm_isdst = 0;
	tmResult.tm_year = y - 1900;
	tmResult.tm_mon = m - 1;
	tmResult.tm_mday = d;

	mktime(&tmResult);

	return tmResult.tm_wday;
}

unsigned int getDiffendTime(int nHour, int nMinute)
{
	SystemTime st;
	GetSystemTime(st);
	st.hour_ = nHour;
	st.min_ = nMinute;
	int ndifftime = 0;
	SecondTime nenttime;
	nenttime.encode(st);

	static GameEngine* ge = GetGameEngine();
	SecondTime curtime = ge->getMiniDateTime();

	if (nenttime > curtime)
		ndifftime = nenttime - curtime;

	return __max(ndifftime, 0);
}

bool isSameWeek(unsigned int t1, unsigned int t2)
{
	STATIC_ASSERT(SecondTime::YearBase == 2010);
	// 这代码等同于 BaseTime.encode(2010,1,4,0,0,0);
	const unsigned int BaseTime = 3 * 24 * 3600;// 2010.1.4是周一，以这个为参考点
	const unsigned int SecOfWeek = 7 * 24 * 3600;
	return (t1 - BaseTime) / SecOfWeek == (t2 - BaseTime) / SecOfWeek;
}

void* getActorPtr(const char* sName)
{
	if (sName == NULL || *sName == 0) return NULL;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor *actor = em->GetActorPtrByName(sName);

	if (actor && actor->IsInited() && !actor->IsImage())
		return actor;
	return NULL;
}

void broadcastTipmsg(const char* sTipmsg, int nTipmsgType)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadcastTipmsg(sTipmsg, 0, nTipmsgType);
}

void broadcastLevelTipmsg(const char* sTipmsg, int level, int nTipmsgType /*= ttTipmsgWindow*/)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadcastTipmsg(sTipmsg, level, nTipmsgType);
}

void broadcastTipmsgWithID(int nTipmsgID, int nTipmsgType)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadcastTipmsgWithID(nTipmsgID, nTipmsgType);
}

void broadcastData(void* dp, bool isOffset)
{
	if (!dp) return;

	DataPacket* pack = (DataPacket*)dp;

	static GameEngine* ge = GetGameEngine();
	if (isOffset)
		ge->BroadCast(((DataPacket*)pack)->getOffsetPtr(), ((DataPacket*)pack)->getAvaliableLength());
	else
		ge->BroadCast(pack->getMemoryPtr(), pack->getLength());
}

int getEntityByPtr(void* pEntity)
{
	Entity* ptr = (Entity*)pEntity;

	if (NULL == ptr) return -1;

	return ptr->GetType();
}

int getAllActorList(lua_State* L) {
	void* actorList[8192];
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = em->GetOnlineActorPtrList(actorList, 8192);
	LuaHelp::PushDataPointerToTable(L, (void**)(actorList), count);
	return 1;
}

int getEntityTypeByHandle(double entityHandle)
{
	unsigned long long tmp = 0;
	memcpy(&tmp, &entityHandle, sizeof(tmp));

	EntityHandle hdl = tmp;

	return hdl.GetType();
}
/*
* Comments: 通过玩家的actorID获取玩家的指针
* Param unsigned int nActorID:actorID
* @Return void *:玩家的指针
*/
void* getEntityPtrByActorID(unsigned int nActorID)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	Actor* actor = (Actor*)(em->GetActorPtrById(nActorID));
	if (actor && actor->IsInited() && !actor->IsImage())
		return actor;
	return NULL;
}

unsigned int getToday()
{
	return SecondTime::today();
}

unsigned int getYesterday()
{
	return SecondTime::yesterday();
}

bool isInTimeRange(int nStartHour, int nStartMin, int nStartSec, int nEndHour, int nEndMin, int nEndSec)
{
	static GameEngine* ge = GetGameEngine();
	SystemTime& sysTime = ge->getSysTime();
	int year = sysTime.year_;
	int month = sysTime.mon_;
	int day = sysTime.mday_;
	SecondTime start;
	start.encode(year, month, day, nStartHour, nStartMin, nStartSec);
	SecondTime end;
	end.encode(year, month, day, nEndHour, nEndMin, nEndSec);
	unsigned int now_t = ge->getMiniDateTime();

	return (now_t >= start && now_t <= end) || (now_t >= end && now_t <= start);
}

void* getGlobalNpc()
{
	static GameEngine* ge = GetGameEngine();
	return ge->GetGlobalNpc();
}

void* getReserveNpc()
{
	static GameEngine* ge = GetGameEngine();
	return ge->GetReserveNpc();
}

//const char* getGuildName(int gid)
//{
//	static GuildMgr& mgr = GetGameEngine()->GetGuildMgr();
//	Guild* guild = mgr.FindGuild(gid);
//	return guild ? guild->name_ : NULL;
//}
//
//void* getGuildLeader(int gid)
//{
//	static GuildMgr& mgr = GetGameEngine()->GetGuildMgr();
//	Guild* guild = mgr.FindGuild(gid);
//
//	if (NULL == guild)
//	{
//		return NULL;
//	}
//	else
//	{
//		if (guild->leader_id_ == 0) return NULL;
//
//		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
//		Entity* et = em->GetActorPtrById(guild->leader_id_);
//
//		if (et && et->GetType() == enActor)
//		{
//			return et;
//		}
//	}
//
//	return NULL;
//}
//
//int getGuildLeaderId(int gid)
//{
//	static GuildMgr& mgr = GetGameEngine()->GetGuildMgr();
//	Guild* guild = mgr.FindGuild(gid);
//
//	return guild ? guild->leader_id_ : 0;
//}
//
//unsigned int getTomorrow()
//{
//	return SecondTime::tomorrow();
//}
//
//bool monUpdate()
//{
//	MonsterConfPool& pool = *MonsterConfPool::config_;
//	return pool.LoadMonsters("data/config/monster/", true);
//}
//
//void regMonsterDie(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->bDeathTriggerScript = flag;
//	}
//}
//
//void regGatherFinish(int mid, bool flag /*= true*/)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->gather_script_ = flag;
//	}
//}
//
//void regMonsterAttacked(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->bAttackTriggerScript = flag;
//	}
//}
//
//void regMonsterCreate(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->bMobTriggerScript = flag;
//	}
//}
//
//void regMonsterDrop(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->bDropTrigger = flag;
//	}
//}
//
//void regMonsterHpChange(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->bHpChangedTriggerScript = flag;
//	}
//}
//
//void regMonsterDamage(int mid, bool flag)
//{
//	MONSTERCONFIG* conf = MonsterConfPool::config_->GetMonsterData(mid);
//
//	if (conf)
//	{
//		conf->trigger_damage = flag;
//	}
//}

//int getDyanmicVar(lua_State* L)
//{
//	return LuaCLVariant::returnValue(L, GetGameEngine()->GetDyanmicVar());
//}

int getStaticVar(lua_State* L)
{
	return LuaCLVariant::returnValue(L, GetGameEngine()->GetGlobalVarMgr().GetVar());
}

const char* getSystemDef(const char* name)
{
	if (name == NULL) return NULL;

	return ServerInstance()->GetVSPDefine().GetDefinition(name);
}

void broadcastCampTipmsg(int nCampId, const char* sTipmsg, int nTipmsgType)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadcastCampTipmsg(nCampId, sTipmsg, nTipmsgType);
}

void broadcastGuildTipmsg(int nGuild, const char* sTipmsg)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadcastGuildTipmsg(nGuild, sTipmsg);
}
//
//void broadcastGuild(int guildid, void* packet, bool isAll)
//{
//	if (!guildid || !packet) return;
//	static GameEngine* ge = GetGameEngine();
//
//	if (isAll)
//	{
//		ge->BroadCastGuild(guildid, ((DataPacket*)packet)->getMemoryPtr(), ((DataPacket*)packet)->getLength());
//	}
//	else
//	{
//		ge->BroadCastGuild(guildid, ((DataPacket*)packet)->getOffsetPtr(), ((DataPacket*)packet)->getAvaliableLength());
//	}
//}

unsigned int getServerOpenTime()
{
	return ServerInstance()->GetServerOpenTime();
}



//const char* getMonsterNameById(int id)
//{
//	static MonsterConfPool& pool = *MonsterConfPool::config_;
//	MONSTERCONFIG* conf = pool.GetMonsterData(id);
//	return conf ? conf->szName : "";
//}

bool isSameDay(unsigned int d1, unsigned int d2)
{
	SecondTime st1 = d1;
	SecondTime st2 = d2;

	return st1.isSameDay(st2);

	// 留着知道有个SystemTime
	//SystemTime sys_time1, sys_time2;
	//st1.decode(sys_time1);
	//st2.decode(sys_time2);

	//return (sys_time1.year_ == sys_time2.year_ && sys_time1.mon_ == sys_time2.mon_ && sys_time1.mday_ == sys_time2.mday_);
};

void setEntityShowName(void* et, const char* name)
{
	//if (!et) return;

	//Entity* entity = (Entity*)et;
	//entity->SetShowName(name);

	//if (entity->isAnimal())
	//{
	//	Animal* an = (Animal*)entity;
	//	an->ChangeName(name);
	//}
}
int getOpenServerDay()
{
	static GameEngine* ge = GetGameEngine();
	SecondTime openTime = ServerInstance()->GetServerOpenTime();
	SecondTime now_t = ge->getMiniDateTime();

	// 改成从0开始
	if (now_t.now() < openTime.rel_today())
	{
		return 0;
	}

	int day = (now_t.now() - openTime.rel_today()) / (3600 * 24);
	//if (day < 0) day = 0;
	return day;
}

int getTimeToNowDay(int optime)
{
	static GameEngine* ge = GetGameEngine();
	SecondTime openTime(optime);
	SecondTime now_t = ge->getMiniDateTime();

	// 改成从0开始
	int day = (now_t.now() - openTime.rel_today()) / (3600 * 24);
	if (day < 0) day = 0;
	return day;
}

int getOpenServerStartDateTime()
{
	return ServerInstance()->GetServerOpenTime().rel_today();
}

unsigned int getOpenServerTime()
{
	return ServerInstance()->GetServerOpenTime().tv;
}

int getRestTimeFromOpenServer(int day)
{
	static GameEngine* ge = GetGameEngine();
	SecondTime openTime = ServerInstance()->GetServerOpenTime();
	SecondTime now_t = ge->getMiniDateTime();
	unsigned int end_t = openTime.rel_today() + day * (3600 * 24);
	int ret = 0;

	if (now_t < end_t)
	{
		ret = (int)(end_t - now_t);
	}

	return ret;
}

bool bitOPMask(int val, int idx)
{
	if (idx < 0 || idx >= 32)
	{
		return false;
	}

	val = (val >> idx) & 0x01;
	return val == 1;
}

int bitOpSetMask(int val, int idx, bool flag)
{
	if (idx < 0 || idx >= 32)
	{
		return val;
	}

	unsigned int mask = (1 << idx);

	if (flag)
	{
		val |= mask;
	}
	else
	{
		// 变成0
		mask = ~mask;
		val &= mask;
	}

	return val;
}

unsigned int timeEncode(int year, int mon, int day, int hour, int m, int sec)
{
	SecondTime ret;
	return ret.encode(year, mon, day, hour, m, sec);
}

int timeDecode(lua_State* L)
{
	SecondTime ret = (unsigned int)lua_tointeger(L, 1);
	SystemTime sys_t;
	ret.decode(sys_t);
	lua_pushinteger(L, sys_t.year_);
	lua_pushinteger(L, sys_t.mon_);
	lua_pushinteger(L, sys_t.mday_);
	lua_pushinteger(L, sys_t.hour_);
	lua_pushinteger(L, sys_t.min_);
	lua_pushinteger(L, sys_t.sec_);
	return 6;
}

void logCounter(int actorid, const char* aid,
                const char* user_level /* = "" */,
                const char* counter /* = "" */,
                const char* value /* = "" */,
                const char* extra /* = "" */,
                const char* kingdom /* = "" */,
                const char* phylum /* = "" */,
                const char* classfield /* = "" */,
                const char* family /* = "" */,
                const char* genus /* = "" */,
                int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(actorid, aid, user_level, counter, value, extra, kingdom, phylum, classfield, family, genus, flag);
}

void logEnconomy(int actorid, const char* aid,
                 const char* currency /*= ""*/,
                 const char* amount /*= ""*/,
                 const char* value /*= ""*/,
                 const char* kingdom /*= ""*/,
                 const char* phylum /*= ""*/,
                 const char* classfield /*= ""*/,
                 const char* family /*= ""*/,
                 const char* genus /*= ""*/,
                 const char* extra /*= ""*/,
                 const char* extra2 /*= ""*/,
                 const char* pf/* = ""*/,
                 int flag,
                 bool isPay,
                 const char* openkey,
                 const char* pfkey,
				 const char* pfid)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogEnconomy(actorid, aid, currency, amount, value, kingdom, phylum, classfield, family, genus, extra, extra2, pf, flag, isPay, openkey, pfkey, pfid);
}

void logMilestone(
    int actorid,
    const char* aid,
    const char* milestone/* = ""*/,
    const char* value/* = ""*/,
    const char* extra/* = ""*/,
    int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogMilestone(actorid, aid, milestone, value, extra, flag);
}

void logPayment(int ret, int actorId, const char* aid, int amount,
                int mstType,
                int p1,
                int p2,
                int p3,
                int value/* = 1*/,
                const char* kingdom/* = ""*/,
                const char* phylum/* = ""*/,
                const char* transactionid/* = ""*/,
                const char* extra/* = ""*/,
                int p4/* = 0*/,
                int p5/* = 0*/,
                int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogPayment(ret, actorId, aid, amount, mstType, p1, p2, p3, value, kingdom, phylum, transactionid, extra, p4, p5, flag);
}

void logInstall(const char* actorId, const char* source /*= ""*/, const char* affiliate /*= ""*/, const char* creative /*= ""*/, const char* family /*= ""*/, const char* genus /*= ""*/, const char* from_uid /*= ""*/, const char* extra /*= ""*/, int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogInstall(actorId, source, affiliate, creative, family, genus, from_uid, extra, flag);
}

void logDau(const char* aid, const char* source /*= ""*/, const char* affiliate /*= ""*/, const char* creative /*= ""*/, const char* family /*= ""*/, const char* genus /*= ""*/, const char* ip /*= ""*/, const char* from_uid /*= ""*/, const char* extra /*= ""*/, int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDau(aid, source, affiliate, creative, family, genus, ip, from_uid, extra, flag);
}

void logGameInfo(const char* aid,
                 const char* user_level/* = ""*/,
                 const char* value/* = ""*/,
                 const char* extra/* = ""*/,
                 const char* kingdom/* = ""*/,
                 const char* phylum/* = ""*/,
                 const char* classfield/* = ""*/,
                 const char* family/* = ""*/,
                 const char* genus/* = ""*/,
                 int flag)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogGameInfo(aid, user_level, value, extra, kingdom, phylum, classfield, family, genus, flag);
}

void logOnline()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	static LogSender* log = ServerInstance()->GetLogClient();
	int nactor = em->GetOnlineActorCount();
	int extra = em->GetOnlineActorCount(true);
	log->LogOnline(nactor, extra);
#ifdef OPENLOGTLOG
	static TlogMgr& tlog = GetGameEngine()->GetTlogMgr();
	tlog.LogOnlineCount(nactor);
#endif
}

int getOnlineCount(bool includeCache)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	return em->GetOnlineActorCount(includeCache);
}

void logTLog(const char* logstr)
{
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(logstr);
}
//
//const char* getEventId()
//{
//	static TlogMgr& mgr = GetGameEngine()->GetTlogMgr();
//	return mgr.GetEventId();
//}
//
//const char* getTLogTime()
//{
//	static TlogMgr& mgr = GetGameEngine()->GetTlogMgr();
//	return mgr.GetTime();
//}
//
//const char* tlogReplace(const char* instr, int idx/* = 0*/)
//{
//	return TLogReplace(instr, idx);
//}


void actorMgrReloadScript()
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imReloadScript;
	mgr->PostMsg(msg);
}

void actorMgrLoadFilterNames()
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imReloadFilterName;
	mgr->PostMsg(msg);
}

int dbQuery(void* db_conn, const char* sql)
{
	if (!db_conn || !sql) return 1;

	SQLConnection* db = (SQLConnection*)db_conn;
	int ret = db->Query(sql);
	return ret;
}

bool dbConnect(void* db_conn)
{
	if (!db_conn) return false;

	SQLConnection* db = (SQLConnection*)db_conn;

	if (!db->Connected())
	{
		if (db->Connect())
		{
			mysql_options(db->GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

void dbClose(void* db_conn)
{
	if (!db_conn) return;

	SQLConnection* db = (SQLConnection*)db_conn;
	db->Disconnect();
}

void* getGameEngineGlobalDbConn()
{
	static GameEngine* ge = ServerInstance()->Engine();
	return ge->GetGlobalSqlConn();
}

void* createActorsDbConn()
{
	SQLConnection* conn = new SQLConnection;
#ifdef DB_UTF8
	conn->SetUtf8(true);
#endif
	ServerInstance()->GetActorMgr()->SetupSQLConnection(conn);
	if (!conn->Connected())
	{
		if (conn->Connect()) {
			mysql_options(conn->GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else {
			delete conn;
			OutputMsg(rmError, ("can not load actordatas, sql connection error"));
			return NULL;
		}
	}
	return conn;
}

void delActorsDbConn(void* db_conn)
{
	if (!db_conn)
	{
		return;
	}
	SQLConnection* db = (SQLConnection*)db_conn;
	if (db) {
		SafeDelete(db);
	}
}


int dbExe(void* db_connection, const char* sql)
{
	if (!db_connection || !sql) return 1;

	SQLConnection* db = (SQLConnection*)db_connection;
	int ret = db->Exec(sql);

	if (ret == 0)
		db->ResetQuery();

	return ret;
}


void dbResetQuery(void* db_conn)
{
	if (!db_conn) return;

	SQLConnection* db = (SQLConnection*)db_conn;
	db->ResetQuery();
}

void* dbCurrentRow(void* db_conn)
{
	if (!db_conn) return NULL;

	SQLConnection* db = (SQLConnection*)db_conn;
	return db->CurrentRow();
}

const char* dbGetRow(void* row, int idx)
{
	if (!row) return NULL;

	MYSQL_ROW data = (MYSQL_ROW)row;
	return data[idx];
}

int dbGetRowCount(void* db_conn)
{
	if (!db_conn) return 0;

	SQLConnection* db = (SQLConnection*)db_conn;
	return db->GetRowCount();
}

void* dbNextRow(void* db_conn)
{
	if (!db_conn) return NULL;

	SQLConnection* db = (SQLConnection*)db_conn;
	return db->NextRow();
}

bool geAddRoutes(int serverid, const char* host, int port)
{
	static GameEngine* ge = ServerInstance()->Engine();
	return ge->AddRoutes(serverid, host, port);
}

bool geHasRoute(int serverid)
{
	static GameEngine* ge = ServerInstance()->Engine();
	return ge->HasRoute(serverid);
}

int bitOpNot(int val)
{
	return ~val;
}

int bitOpAnd(int val1, int val2)
{
	return val1 & val2;
}

int bitOpOr(int val1, int val2)
{
	return val1 | val2;
}

int bitOpRig(int val, int cnt)
{
	return val >> cnt;
}

int bitOpLeft(int val, int cnt)
{
	return val << cnt;
}

int getStrLenUtf8(const char* str)
{
	return ActorMgr::GetStrLenUtf8(str);
}

int SendToDb(lua_State* L)
{
	int serverId = (int)lua_tointeger(L, 1);
	int sysid = (int)lua_tointeger(L, 2);
	int pid = (int)lua_tointeger(L, 3);

	DBClient* db = ServerInstance()->GetDbClient(serverId);

	if (!db) return 0;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(sysid, pid));

	int nParamCount = (int)lua_tointeger(L, 4);

	for (int i = 0, index = 5; i < nParamCount; i++, index += 2)
	{
		int dt = (int)lua_tointeger(L, index);

		switch (dt)
		{
		case dtByte:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (uint8_t)b;
				break;
			}

		case dtChar:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (char)b;
				break;
			}

		case dtWord:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (uint16_t)b;
				break;
			}

		case dtShort:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (short)b;
				break;
			}

		case dtInt:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (int)b;
				break;
			}

		case dtUint:
			{
				int b = (int)lua_tointeger(L, index + 1);
				packet << (unsigned int)b;
				break;
			}

		case dtString:
			{
				const char* b = lua_tostring(L, index + 1);
				packet.writeString(b);
				break;
			}

		case dtInt64:
			{
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				packet << (long long)b;
				break;
			}

		case dtUint64:
			{
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				packet << (unsigned long long)b;
				break;
			}
		}
	}

	db->flushProtoPacket(packet);
	return 0;
}

int allocDBPacket(lua_State* L)
{
	int server_id = (int)lua_tointeger(L, 1);
	int sys_id = (int)lua_tointeger(L, 2);
	int cmd_id = (int)lua_tointeger(L, 3);

	DBClient* db = ServerInstance()->GetDbClient(server_id);

	if (!db) return 0;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(sys_id, cmd_id));

	lua_pushlightuserdata(L, db);
	lua_pushlightuserdata(L, &packet);

	return 2;
}

// 
int flushDBPacket(lua_State* L)
{
	DBClient* db = (DBClient*)lua_topointer(L, 1);
	DataPacket* packet = (DataPacket*)lua_topointer(L, 2);
	if (!db || !packet) return 0;

	db->flushProtoPacket(*packet);

	return 0;
}

void setOpenServerTime(int year, int mon, int day, int hour, int m)
{
	SecondTime st;
	st.encode(year, mon, day, hour, m, 0);
	ServerInstance()->SetServerOpenTime(st);

	FILE* fp = fopen("./runtime/opentime.txt", "w");

	if (fp)
	{
		char content[256];
		memset(content, 0, sizeof(content));
		SNPRINTFA(content, sizeof(content), "%d-%d-%d %d:%d:%d", year, mon, day, hour, m, 0);
		OutputMsg(rmError, "open server time is : %d-%d-%d %d:%d:%d", year, mon, day, hour, m, 0);
		fputs(content, fp);
		fclose(fp);
	}
}

int makeInt16(int lo, int hi)
{
	return MAKEINT16(lo, hi);
}

int makeInt32(int lo, int hi)
{
	return MAKEINT32(lo, hi);
}

int makeHiInt16(int val)
{
	return HIINT16(val);
}

int makeLoInt16(int val)
{
	return LOINT16(val);
}

int makeHiInt8(int val)
{
	return HIINT8(val);
}

int makeLoInt8(int val)
{
	return LOINT8(val);
}

int int32Byte(int b1, int b2, int b3, int b4)
{
	return MAKEINT32(MAKEINT16(b1, b2), MAKEINT16(b3, b4));
}

int byteInt32(lua_State* L)
{
	int val = (int)lua_tointeger(L, 1);
	int lo = LOINT16(val);
	lua_pushinteger(L, LOINT8(lo));
	lua_pushinteger(L, HIINT8(lo));
	int hi = HIINT16(val);
	lua_pushinteger(L, LOINT8(hi));
	lua_pushinteger(L, HIINT8(hi));
	return 4;
}

int getDayDiff(unsigned int t1, unsigned int t2)
{
	return ((int)((SecondTime(t1)).rel_today() - (int)(SecondTime(t2)).rel_today()) / (3600 * 24));
}
//
//void setHefuState(int state)
//{
//	static MiscMgr& mgr = GetGameEngine()->GetMiscMgr();
//	mgr.SetHefuState(state);
//}
//
//int getHefuState()
//{
//	static MiscMgr& mgr = GetGameEngine()->GetMiscMgr();
//	return mgr.GetHefuState();
//}

void start5sScripte(bool flag)
{
	GetGameEngine()->script_5s_timer_ = flag;
}

void sendOffMsg(int aid, const char* actorname, const char* account, int srcid, void* dp)
{
	const char* buf = NULL;
	size_t size = 0;

	if (dp != NULL)
	{
		DataPacket* pack = (DataPacket*)dp;
		buf  = pack->getMemoryPtr();
		size = pack->getLength();
	}

	static MsgMgr& mgr = GetGameEngine()->GetMsgMgr();
	mgr.AddOffMsg(aid, actorname, account, srcid, buf, size);
}

void saveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
	const char* account, const char* msg)
{
	static MsgMgr& mgr = GetGameEngine()->GetMsgMgr();
	mgr.SaveChatMonitoring(aid, type, msgid, guild, actorname, account, msg);
}

int checkIdentity(const char* id)
{
	if (!id) return 1;

	bool enough18 = false;
	bool ret = CheckIdentity(id, &enough18);

	if (!ret)
	{
		return 1;
	}
	else
	{
		if (!enough18) return 2;
		else return 0;
	}
}

void setEngineGcActorCnt(int cnt)
{
	GetGameEngine()->gc_actor_cnt_ = cnt;
}

void engineGc()
{
	GetGameEngine()->GC();
#ifndef _MSC_VER
	malloc_trim(0);
#endif
}

void stopLog(bool flag)
{
	ServerInstance()->GetLogClient()->StopLog(flag);
}

void stopCounterLog(bool flag)
{
	ServerInstance()->GetLogClient()->StopCounterLog(flag);
}

void stopEconomyLog(bool flag)
{
	ServerInstance()->GetLogClient()->StopEconomyLog(flag);
}
//
//void addMarryLog(int aid1, int aid2, const char* name1, const char* name2)
//{
//	static MiscMgr& mgr = GetGameEngine()->GetMiscMgr();
//	mgr.AddMarryLog(aid1, aid2, name1, name2);
//}
//
//void sendMarryLog(void* et, int msgid, int pid, int count, int page)
//{
//	if (et == NULL || ((Entity*)et)->GetType() != enActor) return;
//
//	static MiscMgr& mgr = GetGameEngine()->GetMiscMgr();
//	mgr.SendMarryLog((Actor*)et, msgid, pid, count, page);
//}
//
//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, int camp)
//{
//	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
//	Scene* pScene = fbMgr->GetFbStaticDataPtr(0)->GetScene(scene_id);
//	double d;
//
//	if (pScene == NULL)
//	{
//		return 0;
//	}
//
//	Entity* et = pScene->CreateEntityAndEnter(model_id, enNpc, posX, posY, name);
//
//	if (et)
//	{
//		Npc* npc = (Npc*)et;
//
//		et->SetEntityName(name);
//		// TODO:还要传入NPC的ID
//		et->SetIntProp(P_MODELID, model_id);
//		et->SetIntProp(P_ICON, icon);
//		npc->SetCamp(camp); //设置NPC的阵营
//
//		et->SetUIntProp(P_MAXHP, 10000);
//		et->SetUIntProp(P_HP, 10000);
//		et->SetUIntProp(P_MAXMP, 10000);
//		et->SetUIntProp(P_MP, 10000);
//
//		et->SetInitFlag(true); // 如果是创建备用的，这个设置成false
//	}
//
//	memcpy(&d, &(((Entity*)et)->GetHandle()), sizeof(d));
//	return d;
//}
//
//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, unsigned int hFuben, int camp)
//{
//	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
//	double d;
//
//	if (fbMgr == NULL)
//		return 0;
//
//	FuBen* pFuBen = fbMgr->fb_hdl_mgr_.GetPtr(hFuben);
//
//	if (pFuBen == NULL)
//		return 0;
//
//	Scene* pScene = pFuBen->GetScene(scene_id);
//
//	if (pScene == NULL)
//	{
//		return 0;
//	}
//
//	Entity* et = pScene->CreateEntityAndEnter(model_id, enNpc, posX, posY, name);
//
//	if (et)
//	{
//		Npc* npc = (Npc*)et;
//
//		et->SetEntityName(name);
//		// TODO:设置NPC的ID
//		et->SetIntProp(P_MODELID, model_id);
//		et->SetIntProp(P_ICON, icon);
//		npc->SetCamp(camp); //设置NPC的阵营
//
//		et->SetUIntProp(P_MAXHP, 10000);
//		et->SetUIntProp(P_HP, 10000);
//		et->SetUIntProp(P_MAXMP, 10000);
//		et->SetUIntProp(P_MP, 10000);
//
//		et->SetInitFlag(true); // 如果是创建备用的，这个设置成false
//	}
//
//	memcpy(&d, &(((Entity*)et)->GetHandle()), sizeof(d));
//	return d;
//}

int getSystemTime(lua_State* L)
{
	static GameEngine* ge = GetGameEngine();
	SystemTime& sysTime = ge->getSysTime();

	lua_pushinteger(L, sysTime.year_);
	lua_pushinteger(L, sysTime.mon_);
	lua_pushinteger(L, sysTime.mday_);
	lua_pushinteger(L, sysTime.hour_);
	lua_pushinteger(L, sysTime.min_);
	lua_pushinteger(L, sysTime.sec_);

	return 6;
}
void setActorDbSaveTime(int sec)
{
	Actor::save_db_interval_ = sec * 1000;
	OutputMsg(rmError, "setActorDbSaveTime:%d", sec * 1000);
}

void closeActor(void* et)
{
	if (!et || ((Entity*)et)->GetType() != enActor) return;
	Actor* actor = (Actor*)et;
	actor->CloseActor("lua syscall", true);
	//ServerInstance()->GetGateManager()->PostCloseUser(actor->GetNetId(), "lua", actor->GetActorId());
}
//
//void setLimitItemCount(int count, int itemId, int limitCnt, int idx, int level)
//{
//	static GLOBALCONFIG& gc = GetConfData()->GetGlobalConfig();
//	ItemWarnList& list = gc.item_limit_;
//
//	list.count_ = count;
//
//	if (count == 0)
//	{
//		memset(&list.data_, 0, sizeof(list.data_));
//		return;
//	}
//
//	if (idx < 0 || idx >= count) return;
//
//	gc.item_warn_level_ = level;
//
//	if (itemId >= 0 && itemId < (int)ArrayCount(list.data_))
//	{
//		list.data_[itemId].cnt_ = limitCnt;
//		list.data_[itemId].idx_ = idx;
//	}
//}

int getSysVar(lua_State* L)
{
	static SysVarMgr& mgr = GetGameEngine()->GetSysVarMgr();

	SysVarMgr::SysVarHandle hdl = (unsigned int)lua_tonumber(L, 1);
	SysVar* pVar = mgr.getPtrByHandle(hdl);

	if (pVar != NULL)
		return LuaCLVariant::returnValue(L, pVar->var_);

	return 0;
}

unsigned int createSysVar(int ownerId, const char* ownerName, int type)
{
	static SysVarMgr& mgr = GetGameEngine()->GetSysVarMgr();

	SysVarMgr::SysVarHandle hdl = mgr.createSysVar(ownerId, ownerName, type);
	return (unsigned int)hdl;
}

void saveSysVar(int ownerId, int type, unsigned int hdl)
{
	static SysVarMgr& mgr = GetGameEngine()->GetSysVarMgr();

	mgr.saveSysVar(ownerId, type, hdl);
}

void reloadSysVar()
{
	static SysVarMgr& mgr = GetGameEngine()->GetSysVarMgr();
	mgr.reloadSysVar();
}

int saveSysTmpVar(lua_State* L)
{
	static container::Vector<CLVariant*>& list = GetGameEngine()->GetSysVarMgr().getTmpList();

	if (lua_istable(L, 1) == 0)
		return 0;

	int count = (int)lua_objlen(L, 1);
	list.reserve(list.count() + count);

	for (int i = 1; i <= count; ++i)
	{
		CLVariant* var = new CLVariant;
		list.push_back(var);

		char tmp[32];

		int index = 0;
		lua_rawgeti(L, 1, i);
		lua_pushnil(L);

		while (lua_next(L, -2) != 0)
		{
			const char* key = lua_tostring(L, -2);
			SNPRINTFA(tmp, sizeof(tmp), "%d", index++);
			var->set(tmp, key);

			const char* val = lua_tostring(L, -1);
			SNPRINTFA(tmp, sizeof(tmp), "%d", index++);
			var->set(tmp, val);

			lua_pop(L, 1);
		}

		lua_pop(L, 1);
	}

	return 0;
}

int loadSysTmpVar(lua_State* L)
{
	static container::Vector<CLVariant*>& list = GetGameEngine()->GetSysVarMgr().getTmpList();

	lua_createtable(L, list.count(), 0);
	int listPos = lua_gettop(L);

	int count = list.count();

	for (int i = 0; i < count; ++i)
	{
		lua_createtable(L, 0, 0);

		CLVariant* var = list[i];

		if (var == NULL)
			continue;

		int index = 0;
		int count = (int)var->len();
		const CLVariant** link = (const CLVariant**)(*var);

		while (index < count)
		{
			const char* key = (*link)->operator const char * ();
			++link;
			const char* val = (*link)->operator const char * ();
			++link;
			lua_pushlstring(L, val, strnlen(val, 32));
			lua_setfield(L, -2, key);

			index += 2;
		}

		lua_rawseti(L, listPos, i);

		delete var;
		list[i] = NULL;
	}

	list.clear();

	return 1;
}
//
//void stopDcApiLog(bool sp)
//{
//	static DcApiMgr& mgr = GetGameEngine()->GetDcApiMgr();
//	mgr.SetStopLog(sp);
//}
//
//void setOpenTlog(bool flag)
//{
//	static TlogMgr& mgr = GetGameEngine()->GetTlogMgr();
//	mgr.open_log_ = flag;
//}
//
//bool openTlog()
//{
//	static TlogMgr& mgr = GetGameEngine()->GetTlogMgr();
//	return mgr.open_log_;
//}
//
//bool startGameSessionSrv(const char* ip, int port)
//{
//	static GameSessionMgr* mgr = ServerInstance()->GetGameSessionMgr();
//
//	if (mgr->Started()) return true;
//
//	mgr->SetServiceHost(ip);
//	mgr->SetServicePort(port);
//
//	return mgr->Startup();
//}

bool startOneGameClient(const char* ip, int port, int serverId, int serverType)
{
	return GetGameEngine()->StartOneGameClient(ip, port, serverId, serverType);
}

void resetSingleGameRoute(int sid) {
	GetGameEngine()->ResetSingleGameRoute(sid);
}

void resetGameRoute() {
	GetGameEngine()->ResetGameRoute();
}

void setBattleSrvFlag(int flag)
{
	ServerInstance()->SetBattleSrvFlag(flag);
}
int getBattleSrvFlag()
{
	return ServerInstance()->GetBattleSrvFlag();
}

void sendMsgToAllGameClient(const void* buff, int size, int sid, int cross_method) {
	ServerInstance()->SendMsgToAllGameClient(buff, (size_t)size, InterSrvComm::GameWorldProto::gpCommonMsg, sid, cross_method);
}

void sendPacketToAllGameClient(void* packet, int sid /*= 0*/, int cross_method) {
	if (!packet) return;

	DataPacket* dp = (DataPacket*)packet;
	sendMsgToAllGameClient(dp->getMemoryPtr(), (int)dp->getLength(), sid, cross_method);
}

void removeBattleSrv(int sid)
{
	GetGameEngine()->RemoveBattleSrv(sid);
}

bool isBattleSrv()
{
	static GameServer* srv = ServerInstance();
	return srv->IsBattleSrv();
}

bool isLianFuSrv()
{
	static GameServer* srv = ServerInstance();
	return srv->IsLianFuSrv();
}

bool isCommSrv()
{
	static GameServer* srv = ServerInstance();
	return srv->IsCommonSrv();
}

bool isCrossWarSrv()
{
	static GameServer* srv = ServerInstance();
	return srv->IsCrossWarSrv();
}

const char* loadStringFromFile(const char* filename)
{
	static char str[1024];
	FILE* file = fopen(filename, "r");

	if (file)
	{
		char ch;
		uint32_t pos = 0;

		while (pos < (sizeof(str)-1) && 
				(ch = getc(file)) != EOF)
		{
			str[pos++] = ch;
		}

		str[pos] = 0;

		fclose(file);
		return str;
	}
	else
	{
		return "";
	}
}

bool reloadFilterDb()
{
	return GetGameEngine()->ReloadFilterDb();
}

const char* filterText(const char* text)
{
	if (!text) return "";

	static GameEngine* ge = GetGameEngine();

	static char str[1024];
	_STRNCPY_A(str, text);

	ge->Filter(str);
	return str;
}

int filterTextCount(const char* text)
{
	if (!text) return 0;

	static GameEngine* ge = GetGameEngine();

	static char str[1024];
	_STRNCPY_A(str, text);

	return ge->Filter(str);
}

void execute(const char* cmd)
{
#ifdef _UNIT_TEST_
	system(cmd);
#endif
}
//void dropPackage(void* et, int nItemID, int nCount, int nBind, int nStrong)
//{
//	Entity* entity = (Entity*)et;
//	Actor* actor = NULL;
//
//	if (entity->GetType() == enActor)
//		actor = (Actor*)entity;
//	else if (entity->GetType() == enMonster)
//	{
//		Entity* vester = NULL;
//		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
//		EntityHandle handle = ((Monster*)entity)->GetOwner();
//		vester = em->GetEntity(handle);
//
//		if (vester == NULL)
//		{
//			handle = ((Monster*)entity)->GetVestEntity();
//			vester = em->GetEntity(handle);
//		}
//
//		if (vester && vester->GetType() == enActor)
//		{
//			actor = (Actor*)vester;
//		}
//		else if (vester && vester->GetType() == enPet)
//		{
//			actor = ((Monster*)vester)->GetMaster();
//		}
//	}
//
//	if (!actor) return;
//
//
//	ActorId aid = actor->GetActorId();
//	unsigned int team_id = actor->GetUIntProp(P_TEAM_ID);
//
//	//添加上过期时间
//	static GameEngine* ge = GetGameEngine();
//	static GLOBALCONFIG& gc = GetConfData()->GetGlobalConfig();
//	static ItemConfPool& itemPool = *ItemConfPool::config_;
//
//	int64_t expired_t = ge->getMiniDateTime() + gc.nMonsterItemRefreshTime;
//	int64_t protect_t = ge->getMiniDateTime() + gc.monsterItemProtectTime;
//
//	StaticArrayList<DropBag, 25> bag_list;
//	DropBag& bag = bag_list[bag_list.count()];
//
//	bag.item_.itemid = nItemID;
//	bag.item_.count = nCount;
//
//	const StdItem* pItem = itemPool.GetStdItem(nItemID);
//
//	if (nItemID && pItem != NULL)
//	{
//		bag.item_.strong = (uint8_t)nStrong;
//		bag.item_.bindFlag = (uint8_t)nBind;
//		bag.broadcast_type_ = false; //拾取的时候是否需要广播
//		bag.need_trgger_ = false; //是否需要触发脚本
//	}
//	else
//	{
//		// strong 表示金钱类型
//		bag.money_type_ = nStrong;
//		bag.money_count_ = nCount;
//	}
//
//	bag.protect_t_ = protect_t;
//	bag.expired_t_ = expired_t;
//	bag.killer_id_ = aid;
//	bag.team_id_ = team_id;
//	bag.monster_id_ = 0;
//
//	bag_list.trunc(bag_list.count() + 1);
//
//
//	// 安排位置
//	Scene* scene = actor->GetScene();
//
//	if (!scene) return;
//
//	int posX = 0, posY = 0;
//	entity->GetPosition(posX, posY);
//
//	// 外围一圈八个位置
//	const int eight_count = 8;
//	const int c16 = 16;
//
//	static int eight [][2] = {{ -1, 0}, { -1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, { -1, 1}};
//
//	STATIC_ASSERT(sizeof(eight) / sizeof(eight[0]) == eight_count);
//
//	// 外围一圈16个位置
//	static int out_16[][2] = {{ -2, -2}, { -1, -2}, {0, -2}, {1, -2}, {2, -2},
//		{ -2, -1}, {2, -1},
//		{ -2, 0}, {2, 0},
//		{ -2, 1}, {2, 1},
//		{ -2, 2}, { -1, 2}, {0, 2}, {1, 2}, {2, 2}
//	};
//
//	STATIC_ASSERT(sizeof(out_16) / sizeof(out_16[0]) == c16);
//
//	static int eight_idx[] = {0, 1, 2, 3, 4, 5, 6, 7};
//	STATIC_ASSERT(sizeof(eight_idx) / sizeof(eight_idx[0]) == eight_count);
//
//	static int out16_idx[] = {0, 1,	2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
//	STATIC_ASSERT(sizeof(out16_idx) / sizeof(out16_idx[0]) == c16);
//
//	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
//	int bag_count = bag_list.count();
//	DropBag* list = bag_list;
//
//
//	int randpos = 0;
//	int loopCount = 0;	/// 限定循环的次数，因为如果所有位置都不能放，就死循环了
//
//	for (int i = 0; i < bag_count && loopCount < 100; ++loopCount)
//	{
//		int x = 0, y = 0;
//
//		if (randpos == 0)
//		{
//			x = posX;
//			y = posY;
//		}
//		else if (randpos <= eight_count)
//		{
//			int idx = randpos - 1;
//			idx = eight_idx[idx];
//			x = posX + eight[idx][0];
//			y = posY + eight[idx][1];
//		}
//		else
//		{
//			int idx = randpos - eight_count - 1;
//			idx = out16_idx[idx];
//			x = posX + out_16[idx][0];
//			y = posY + out_16[idx][1];
//		}
//
//		randpos ++;
//
//		if (randpos >= eight_count + c16)
//		{
//			randpos = 0;
//		}
//
//		//该位置不能放，就往回推一个位置
//		if (!scene->CanMove(x, y, true))
//		{
//			continue;
//		}
//
//		DropBag& bag = list[i];
//
//		// 放到场景中
//		EntityHandle handle;
//		DropBag* et_bag = (DropBag*)em->CreateEntity(enDropBag, handle);
//
//		if (et_bag)
//		{
//			et_bag->team_id_ = bag.team_id_;			//	所属的队伍，如果队伍id不为0，就是属于队伍的，如果队伍不存在，就看killer_id_字段
//			et_bag->money_count_ = bag.money_count_;   // 金钱的数量
//			et_bag->money_type_ = bag.money_type_;	// 金钱类型
//			et_bag->item_ = bag.item_;				// 背包物品
//			et_bag->monster_id_ = bag.monster_id_;    // 掉落这个物品的怪物的ID
//			et_bag->monster_posx = bag.monster_posx;
//			et_bag->monster_posy = bag.monster_posy; //怪物坐标
//			et_bag->killer_id_ = bag.killer_id_;		// 所属角色的
//			et_bag->broadcast_type_ = bag.broadcast_type_; // 是否需要广播
//			et_bag->need_trgger_ = bag.need_trgger_; // 是否需要触发脚本
//			et_bag->expired_t_ = bag.expired_t_;    // 过期时间
//			et_bag->protect_t_ = bag.protect_t_;		// 保护时间
//
//			bool flag = scene->EnterScene(et_bag, x, y);
//
//			if (!flag)
//			{
//				em->DestroyEntity(et_bag->GetHandle());	// 无法放到场景中删除掉
//			}
//		}
//
//		++i;
//	}
//}

bool outputConfigFile(const char* fn, const char* output)
{
	MemoryStream ms(NULL);
	LuaPreProcessor pp(NULL);

	if (ms.loadFromFile(fn) <= 0)
	{
		OutputMsg(rmError, "unable to load from %s", fn);
		return false;
	}

	ServerInstance()->GetVSPDefine().RegisteToPreprocessor(pp);
	pp.addMacro("_LANGUAGE_INCLUDED_");
	const char* txt = pp.parse((const char*)ms.getMemory(), fn);
	FILE* f = fopen(output, "w");

	if (f)
	{
		fwrite(txt, 1, strlen(txt), f);
		fclose(f);
	}

	return f != NULL;
}

void startAsyncWorker()
{
	AsyncWorker* worker = new AsyncWorker("data/functions/utils/thread/asyncworker.lua");
	worker->SetWorkCallBack(&GameEngine::PostMsgToGE);
	ServerInstance()->SetAsyncWorker(worker);
	worker->Start();
}

void reloadWorkerScript()
{
	ServerInstance()->GetAsyncWorker()->Reload();
}

int sendMessageToAsyncWorker(lua_State* L)
{
	if (!lua_istable(L, 1)) return 0;

	ScriptValueList args;
	int cnt = (int)lua_objlen(L, 1);
	cnt = __min(cnt, ScriptValueList::MaxValueCount);

	if (cnt > 0)
	{
		lua_pushnil(L);
		int qcnt = 0;

		while (lua_next(L, 1) && qcnt < cnt)
		{
			int type = lua_type(L, -1);

			// 只支持数字和字符串
			if (type == LUA_TNUMBER)
			{
				args << (int)(int)lua_tointeger(L, -1);
			}
			else if (type == LUA_TSTRING)
			{
				args << (const char*)lua_tostring(L, -1);
			}

			lua_pop(L, 1);

			qcnt++;
		}
	}

	unsigned int guid = ServerInstance()->GetAsyncWorker()->SendLuaMessage(args, &GameEngine::AsyncWorkLuaCallback);
	lua_pushnumber(L, guid);
	return 1;
}

void regScriptNetMsg(int sysId, int cmdId)
{
	//static GameEngine* ge = GetGameEngine();
	NetMsgDispatcher::RegisterScriptMsg(sysId, cmdId);
}

bool reloadGlobalNpc(void* et, int type)
{
	EntityHandle hdl = 0;

	if (et && ((Entity*)et)->GetType() == enActor)
		hdl = ((Entity*)et)->GetHandle();

	return GetGameEngine()->PostReloadGlobaNpc(hdl, type);
}

bool monUpdate()
{
	return MonsterConfigPool::Reload();
}

bool itemUpdate()
{
	return ItemConfigPool::Reload();
}

void changePrestigeExp()
{
	PrestigeHelper::setChangeExpTimeInfo();
}

//bool itemUpdate()
//{
//	ItemConfPool& pool = *ItemConfPool::config_;
//	return pool.LoadStdItems("data/config/item/", true);
//}
//
//bool skillUpdate()
//{
//	SkillConfPool* pool = SkillConfPool::config_;
//	return pool->LoadSkills("data/config/skill/", true);
//}
//
//bool envirUpdate()
//{
//	EnvirConfig* pool = EnvirConfig::config_;
//	bool ret = pool->LoadConfig("data/envir/", true);
//
//	if (!ret) return ret;
//
//	// 读取副本的相关配置
//	return pool->LoadSceneConfigEx("data/envir/fuben.txt");
//}
//
//bool questUpdate()
//{
//	QuestConfPool* pool = QuestConfPool::config_;
//	return pool->LoadQuest("data/config/quest/", true);
//}
//
//bool reloadBuffConfig()
//{
//	BuffConfigPool* pool = BuffConfigPool::config_;
//	return pool->LoadConfig("data/config/buff/buffconfig.lua", true);
//}
//
//int	getSkillIdByName(const char* skillName)
//{
//	int nSkillId = SkillConfPool::config_->GetSkillIdByName(skillName);
//	return nSkillId;
//}
//
//const char* getSkillNameById(int skillId)
//{
//	return SkillConfPool::config_->GetSkillNameById(skillId);
//}

bool reloadLang()
{
	return ServerInstance()->GetLang().LoadFromFile(("data/language/langcode.txt"));
}
void setDbRetRoute(int sysid, int cmd, int val)
{
	static GameEngine* ge = GetGameEngine();
	ge->SetDbRetRoute(sysid, cmd, val);
}
//
//double allocSeries()
//{
//	static GameEngine* ge = GetGameEngine();
//	int64_t lld = ge->AllocItemSeries();//.llId;
//	double sid = 0;
//	memcpy(&sid, &lld, sizeof(lld));
//	return sid;
//}

//void clearAttrConfig(int sysid)
//{
//	return AttrConfig::config_->clearAttrConfig(sysid);
//}

//int createAttr(int sysid)
//{
//	return AttrConfig::config_->createAttr(sysid);
//}

//bool setAttr(int sysid, int index, int attrType, float attrValue)
//{
//	return AttrConfig::config_->setAttrConf(sysid, index, attrType, attrValue);
//}

//int getAttrList(lua_State* L)
//{
//	int sysid = (int)lua_tointeger(L, 1);
//	int index = (int)lua_tointeger(L, 2);
//
//	AttriCalc* calc = AttrConfig::config_->getCalc(sysid, index);
//
//	lua_pushlightuserdata(L, calc);
//	return 1;
//}

void sendDataToCenter(void* pack)
{
	/*if (!pack) return;

	DataPacket* dp = (DataPacket*)pack;
	dp->setPosition(0);

	static CenterClient* cli = ServerInstance()->GetCenterClient();
	DataPacket& p = cli->allocProtoPacket(cwComm);
	p.writeBuf(dp->getMemoryPtr(), dp->getLength());
	cli->flushProtoPacket(p);
	*/
}

void sendDataToActorServer(void* pack)
{
	/*if (!pack) return;

	DataPacket* dp = (DataPacket*)pack;
	dp->setPosition(0);

	static CenterClient* cli = ServerInstance()->GetCenterClient();
	DataPacket& p = cli->allocProtoPacket(cwActorServer);
	p.writeBuf(dp->getMemoryPtr(), dp->getLength());
	cli->flushProtoPacket(p);
	*/
}

void runGTest()
{
	GetGameEngine()->RunAllTests();
}
//
//void broadcastToScene(void* scenePtr, void* packet)
//{
//	Scene* scene = (Scene*)scenePtr;
//
//	if (NULL == scene)
//	{
//		return;
//	}
//
//	size_t send_len = ((DataPacket*)packet)->getLength();
//
//	scene->Broadcast(((DataPacket*)packet)->getMemoryPtr(), send_len);
//	return;
//}

int getMonsterCount()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	return em->GetMonsterCount();
}

void setMonsterMgrDiv(int num)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	em->SetMonsterMgrDiv(num);
}

double getInt64(double num)
{
	int64_t result = (int64_t)num;
	double d;
	memcpy(&d, &result, sizeof(d));
	return d;
}

void enableCheckDataValid(bool flag)
{
	static GameEngine* ge = GetGameEngine();
	ge->SendEnableCheckValid(flag);
}

void setActorDataValid(int serverId, int actorId, bool flag)
{
	Actor::SendDataValid(serverId, actorId, flag);
}

void sendTipmsg(int actorid, const char* msg, int type /* = ttTipmsgWindow */)
{
	if (!msg) return;
	static GameEngine* ge = GetGameEngine();
	ge->SendTipmsg(actorid, msg, type);
}

void logChat(void* et, int type, const char* content,
	const char* toaid /* = "" */, const char* toname /* = "" */)
{
	if (!et || ((Entity*)et)->GetType() != enActor) return;

	static LogSender* log = ServerInstance()->GetLogClient();

	Actor* actor = (Actor*)et;

	log->LogChat(actor->GetAccount(), actor->GetEntityName(), actor->GetLastLoginIp(),
		"", actor->GetActorId(), type, content, toaid, toname);
}

void delOneGameClient(int serverId)
{
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();

	static BaseAllocator alloc("delOneGameClient");
#ifndef TEST_CROSS_MEM
	DataPacket* dp = new DataPacket(&alloc);
#else
	DataPacket* dp = (DataPacket*)ServerInstance()->GetActorMgr()->GetAlloc().AllocBuffer(sizeof(DataPacket));
	new(dp)DataPacket(&alloc);
#endif
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imDelGameClient;
	msg.data_.packet_ = dp;
	(*dp) << serverId;
	mgr->PostMsg(msg);

	static GameEngine* ge = GetGameEngine();
	ge->RemoveBattleSrv(serverId);
}

int loadFileAsUserData(lua_State *L)
{
	const char *path = lua_tostring(L, 1);
	if (NULL == path)
		return 0;

	stream::MemoryStream ms(NULL);
	if (ms.loadFromFile(path) > 0)
	{
		size_t size = ms.getSize();
		void *ud = lua_newuserdata(L, size);
		memcpy(ud, (char*)ms.getMemory(), size);

		return 1;
	}

	return 0;
}

int saveUserDataToFile(lua_State *L)
{
	void *ud = lua_touserdata(L, 1);
	const char *path = lua_tostring(L, 2);
	if (NULL == ud || NULL == path)
		return 0;

	size_t size = lua_objlen(L, 1);

	stream::MemoryStream ms(NULL);
	ms.write(ud, size);
	ms.saveToFile(path);

	return 0;
}

int getOnlineActorList(lua_State *L)
{
	void* actorList[8192];
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = em->GetOnlineActorPtrList(actorList, 8192);
	LuaHelp::PushDataPointerToTable(L, (void**)(actorList), count);
	return 1;
}

int getAllActorData(lua_State *L)
{
	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	const std::vector<ActorBasicData*>& datas = actor_data_mgr->GetDatas();
	LuaHelp::PushDataPointerToTable(L, ((void**)&datas[0]), datas.size());
	return 1;
}
int findSkirmish(lua_State* L)
{
	Actor* actor = (Actor*)lua_touserdata(L, 1);


	if (actor)
	{
		auto ret = SkirmishHelper::FindSkirmish(actor);
		if (ret.size() > 0)
		{
			LuaHelp::PushIntsToTable(L, &ret[0], ret.size());
			return 1;
		}
	}
	return 0;
}

int FindFieldPlayer(lua_State* L)
{
	Actor* actor = (Actor*)lua_touserdata(L, 1);
	if (actor)
	{
		int startlv = (int)lua_tointeger(L, 2);
		int endlv = (int)lua_tointeger(L, 3);
		int needNum = (int)lua_tointeger(L, 4);
		int flSize = (int)lua_tointeger(L, 5);
		auto ret = SkirmishHelper::FindFieldPlayer(actor, startlv, endlv, needNum, flSize);
		if (ret.size() > 0)
		{
			LuaHelp::PushIntsToTable(L, &ret[0], ret.size());
			return 1;
		}
	}
	return 0;
}

int sendMail(lua_State* L)
{
	ActorId actorId = (ActorId)lua_tonumber(L, 1);

	//从脚本读取邮件数据
	MailData mailData;

	//读取邮件标题
	const char *head = lua_tostring(L, 2);
	if (strlen(head) >= MailData::HEAD_SIZE)
		return 0;

	//读取邮件正文
	const char* context = lua_tostring(L, 3);
	if (strlen(context) >= MailData::CONTEXT_SIZE)
		return 0;

	strcpy(mailData.head, head);
	strcpy(mailData.context, context);

	//读取邮件发送时间
	int sendtime = (int)lua_tointeger(L, 4);
	mailData.sendtime = sendtime;

	//读取邮件状态
	mailData.readStatus = MailReadStatusType_NotRead;

	//读取邮件附件
	int j = 0;
	int paramCount = (int)lua_tointeger(L, 5);
	for (int i = 0; i < paramCount; i = i + 3)
	{
		mailData.award_data.awardList[j].type = (int)lua_tointeger(L, 6 + i);
		mailData.award_data.awardList[j].id = (int)lua_tointeger(L, 6 + i + 1);
		mailData.award_data.awardList[j].count = (int)lua_tointeger(L, 6 + i + 2);
		mailData.award_data.awardCount = j + 1;

		if (j + 1 == 10) break;

		++j;
	}

	GameEngine* engine = GetGameEngine();
	static EntityMgr* em = engine->GetEntityMgr();
	Actor *actor = em->GetActorPtrById(actorId);
	if (actor && actor->IsInited() && !actor->IsImage())
	{
		MailSystem *mailSystem = actor->GetMailSystem();
		if (!mailSystem) return 0;

		Mail *pMail = MailPool::instance().CreateMail(&mailData);

		mailSystem->RevcMail(pMail);
	}
	else
	{
		MailSystem::SendOffLineMail(actorId, &mailData);
	}
	return 0;
}

void regInstanceMonsterDamage(int fid)
{
	static FuBenMgr* fm = GetGameEngine()->GetFuBenMgr();
	fm->RegMonsterDamageEvent(fid);
}

void regInstanceActorDamage(int fid)
{
	static FuBenMgr* fm = GetGameEngine()->GetFuBenMgr();
	fm->RegActorDamageEvent(fid);
}

bool regStartScript(const char* rule)
{
	return TimeDomainHelper::regStartScript(rule);
}

bool regEndScript(const char* rule)
{
	return TimeDomainHelper::regEndScript(rule);
}

bool checkRuleTime(const char* rule)
{
	return TimeDomain::getInstance().checkTime(rule);
}

double getRuleStartTime(const char* rule)
{
	return static_cast<double>(TimeDomain::getInstance().getStartTime(rule));
}

double getRuleEndTime(const char* rule)
{
	return static_cast<double>(TimeDomain::getInstance().getEndTime(rule));
}

int getGlobalMailMaxUid(void)
{
	return GetGameEngine()->GetGlobalMailMgr()->GetMaxUid();
}

void addGlobalMail(const char* head, const char* context, const char* item_str)
{
	GetGameEngine()->GetGlobalMailMgr()->AddGlobalMail(head, context, item_str);
}


void buyMonthCardOffLine(Actor* tar)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	luaScript.Call("buyMonthCard", &arg, &arg,0);
	tar->SaveDb(true);
}

void buyMonthCard(int actorid)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actorid))
		return;

	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorid, buyMonthCardOffLine);
}

void buyPrivilegeCardOffLine(Actor* tar)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	luaScript.Call("buyPrivilegeMonthCard", &arg, &arg,0);
	tar->SaveDb(true);
}

void buyPrivilegeCard(int actorid) {
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actorid))
		return;

	ActorAsynFunc func = std::bind(buyPrivilegeCardOffLine, std::placeholders::_1);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorid, func);
}

void buyPrivilegeOffLine(Actor* tar)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	luaScript.Call("buyPrivilege", &arg, &arg, 0);
}

void buyPrivilege(int actorid)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actorid))
		return;
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorid, buyPrivilegeOffLine);
}

void buyRechargeLimitPackage(int actorid, int money)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actorid))
		return;
	ActorAsynFunc func = std::bind(buyRechargeLimitPackageOffline, std::placeholders::_1, money);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorid, func);

}

void buyRechargeLimitPackageOffline(Actor* tar, int money)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	arg << money;
	luaScript.Call("onBuyRechargeLimitPackage", &arg, &arg, 0);
}

void buyFund(int actorid, int money)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actorid))
		return;
	ActorAsynFunc func = std::bind(buyFundOffline, std::placeholders::_1, money);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorid, func);

}

void buyFundOffline(Actor* tar, int money)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	arg << money;
	luaScript.Call("onBuyFund", &arg, &arg, 0);
}

int rand(int max)
{
	return wrand(max);
}

int getTimeZone(void)
{
	return (60 * 60) * 8;
}

static void shutupOffLine(Actor* tar, int time)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	arg << time;
	luaScript.Call("shutup", &arg, &arg, 0);
	tar->SaveDb(true);
}

void shutup(int actor_id, int time)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actor_id))
		return;
	ActorAsynFunc func = std::bind(shutupOffLine, std::placeholders::_1, time);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, func);
}

static void releaseShutupOffLine(Actor* tar)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	luaScript.Call("releaseShutup", &arg, &arg, 0);
	tar->SaveDb(true);
}

void releaseShutup(int actor_id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actor_id))
		return;
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, releaseShutupOffLine);
}

static void cbChangeTitle(Actor* tar, int oper, int tId)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << tar;
	arg << oper;
	arg << tId;
	luaScript.Call("cbChangeTitle", &arg, &arg, 0);
	tar->SaveDb(true);
}

void offlineChangeTitle(int actor_id, int oper, int tId)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	if (!data_mgr->GetData(actor_id))
		return;
	ActorAsynFunc func = std::bind(cbChangeTitle, std::placeholders::_1, oper, tId);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, func);
}
bool startGameConnSrv(const char * ip, int port) {
	static GameConnMgr* mgr = ServerInstance()->GetGameConnMgr();

	if (mgr->Started()) return true;

	mgr->SetServiceHost(ip);
	mgr->SetServicePort(port);

	return mgr->Startup();
}

void stopGameConnSrv()
{
	static GameConnMgr* mgr = ServerInstance()->GetGameConnMgr();
	if (mgr->Started())
	{
		mgr->Close();
		mgr->Stop();
	}
}
int  time2String(lua_State* l)
{
	char ret[100] = {};
	SecondTime t = (unsigned int)lua_tonumber(l, 1);
	SystemTime sys_t;
	t.decode(sys_t);

	sprintf(ret,"%d.%d.%d-%d:%d",
		sys_t.year_,
		sys_t.mon_,
		sys_t.mday_,
		sys_t.hour_,
		sys_t.min_
	);
	lua_pushstring(l, ret);
	return 1;
}

int getActorCountOfZhuanShengLv(int lv)
{
	auto &datas = GetGameEngine()->GetActorDataMgr()->GetDatas();
	int count = 0;
	for (auto it : datas)
	{
		if (it->zhuansheng_lv >= lv)
			++count;
	}
	return count;
}

double getGameTick()
{
	 return (double)ServerInstance()->Engine()->getTickCount();
}

void logDKMLog(const char* logstr, const char* pf) {
	if (!logstr || !pf) return;
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDKMLog(logstr, pf);
}

void printAllLua(void* et)
{/*
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;
	Actor* actor = (Actor*)et;
	// 以下代码需要临时修改 CLVariant 的 var.data_ 为 public 对象  <----
	CLVariant& var = actor->GetActorVar();
	for (int i = var.data_.a.len - 1; i > -1; --i)
	{
		if (var.data_.a.list[i]->type_ == CLVariant::vStruct)
		{
			bool b = true;
			int size = var.data_.a.list[i]->saveToMemory(NULL, 0, b);
			OutputMsg(rmError, "lua data size:%d,id:%lld", size, var.data_.a.list[i]->name_id_);
		}
	}*/
}


int getClvariantSize(void* et, const char* str)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	Actor* actor = (Actor*)et;
	CLVariant& var = actor->GetActorVar();
	//CLVariant* subVar = var.get(str);
	CLVariant* subVar = &var;

	auto split_string = [](const std::string& str, const std::string& pattern)
	{
		std::vector<std::string> ret;
		size_t i = 0;
		{
			i = str.find(pattern);
			if (i == std::string::npos) return ret;
			ret.push_back(str.substr(0, i));
			i += pattern.size();
		}
		for (;;)
		{
			auto p = i;
			i = str.find(pattern, i);
			if (i == std::string::npos)
			{
				if ((str.size() - p))
				{
					ret.push_back(str.substr(p, str.size() - p));
				}
				else if (str.substr(str.size() - pattern.size(), pattern.size()) == pattern)
				{
					ret.push_back("");
				}
				break;
			}
			ret.push_back(str.substr(p, i - p));
			i += pattern.size();
		}

		return ret;
	};

	auto vec2 = split_string(str, ".");
	for (int i = 0; i < (int)vec2.size(); ++i)
	{
		auto str1 = vec2[i];
		subVar = subVar->get(str1.c_str());
		if (!subVar) break;
	}
	if (!subVar)
	{
		return -1;
	}

	bool bl = true;
	return static_cast<int>( subVar->saveToMemory(NULL, 0, bl));
}
}
