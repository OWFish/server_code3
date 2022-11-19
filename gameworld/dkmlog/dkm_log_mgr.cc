#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif


const char* TLogReplace(const char* instr, int idx /*= 0*/)
{
	static const int MAX_REPLACE_ITEM = 8;
	static const int MAX_REPLACE_LEN = 256;

	if (!instr || idx < 0 || idx >= MAX_REPLACE_ITEM)
		return "";

	int len = (int)strlen(instr);

	if (len > MAX_REPLACE_LEN)
		return "";

	static char retBuf[MAX_REPLACE_ITEM][MAX_REPLACE_LEN + 1];

	char* outstr = retBuf[idx];

	for (int i = 0; i < len; i++)
	{
		if (instr[i] == ':')
			outstr[i] = '#';
		else
			outstr[i] = instr[i];
	}

	outstr[len] = 0;
	return outstr;
}

const char* ReplaceString(const char* instr, char* outstr, int outlen)
{
	int len = (int)strlen(instr);
	if (len >= outlen)
		len = outlen - 1;

	for (int i = 0; i < len; i++)
	{
		if (instr[i] == ':')
			outstr[i] = '#';
		else
			outstr[i] = instr[i];
	}
	outstr[len] = 0;
	return outstr;
}

bool DKMLogMgr::open_log_(true);

DKMLogMgr::DKMLogMgr()
{
}

DKMLogMgr::~DKMLogMgr()
{

}

// void DKMLogMgr::LogLogin(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* addr)
// {
// 	if (!open_log_) return;
// 
// 	char buf[TLOG_BUFFER_SIZE];
// 	//2016-12-11 12:36:34 rolelogin:from=101:userid=323523:roleid=6b4715084:account=xx:lev=20:platform=wl91 : totalcash = 1000 : ip = 1.1.1.1
// 	SNPRINTFA(buf, sizeof(buf), "%s rolelogin:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:totalcash=%d:ip=%s"
// 		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, addr);
// 	static LogSender* log = ServerInstance()->GetLogClient();
// 	log->LogDKMLog(buf, pfid);
// 
// }
// 
// void DKMLogMgr::LogLogout(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int onlineTime)
// {
// 	if (!open_log_) return;
// 
// 	char buf[TLOG_BUFFER_SIZE];
// 	//2016-12-11 12:36:34 rolelogout:from=101:userid=323523:roleid=6b4715084:account=xx:lev=20:platform=wl91:totalcash=1000:time=12000:hint=xx
// 	SNPRINTFA(buf, sizeof(buf), "%s rolelogout:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:totalcash=%d:time=%d"
// 		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, onlineTime);
// 	static LogSender* log = ServerInstance()->GetLogClient();
// 	log->LogDKMLog(buf, pfid);
// 
// }

//void DKMLogMgr::LogUpgrade(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int vipLvl)
//{
//	if (!open_log_) return;
//	//2016-12-11 12:36:34 levelup:from=101:userid=323523:roleid=6b4715084:account=xx:lev=2:platform=25pp:totalcash=40000:viplev=5
//
//	char buf[TLOG_BUFFER_SIZE];
//	SNPRINTFA(buf, sizeof(buf), "%s levelup:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:totalcash=%d:viplev=%d"
//		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, vipLvl);
//}
//
//void DKMLogMgr::LogRecharge(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int cash, int yb, int id1, int id2, const char* addr)
//{
//	if (!open_log_) return;
//
//	//2016-12-11 12:36:34 addcash:from=101:userid=323523:roleid=6b4715084:account=xx:lev=20:platform=wl91:totalcash=1000:cash=200:yuanbao=100:id1=1213:id2=221:ip=1.1.1.1
//	char buf[TLOG_BUFFER_SIZE];
//	SNPRINTFA(buf, sizeof(buf), "%s addcash:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:totalcash=%d:cash=%d:yuanbao=%d:id1=%d:id2=%d:ip=%s"
//		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, cash, yb, id1, id2, addr);
//
//}
//
//void DKMLogMgr::LogChardata(int accountid, int actorid, const char* name, int lvl, const char* pfid, int createtime, int lastlogintime, int totalonlinetime, int dayonlinetime, int lev, int viplev, int exp, int fight, int totalcash, int  yuanbaoowned, int jinbiowned)
//{
//	if (!open_log_) return;
//
//	//2010-12-11 12:36:34 chardata:from=101:userid=154128:roleid=6b4715084:account=xx:platform=25pp:createtime=1483769092:lastlogintime=1483769093:totalonlinetime=3600:dayonlinetime=1800:lev=20:viplev=8:exp=1000:fight=1000:totalcash=2000:yuanbaoowned=110:jinbiowned=200
//
//	char buf[TLOG_BUFFER_SIZE];
//	SNPRINTFA(buf, sizeof(buf), "%s chardata:from=%d:userid=%d:roleid=%d:account=%s:platform=%s:createtime=%d:lastlogintime=%d:totalonlinetime=%d:dayonlinetime=%d:lev=%d:viplev=%d:exp=%d:fight=%d:totalcash=%d:yuanbaoowned=%d:jinbiowned=%d"
//		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, createtime, lastlogintime, totalonlinetime, dayonlinetime, lev, viplev, exp, fight, totalcash, yuanbaoowned, jinbiowned);
//}

void DKMLogMgr::LogAddMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* logStr, int yuanbao, int type)
{
		if (!open_log_) return;
		char format_log[64] = {0};
		FormatLog(format_log, logStr);

		//2010-12-11 12:36:34 addyuanbao:from=101:userid=323523:roleid=6b4715084:account=xx:lev=20:platform=25pp:mac=DC2B61739C2:os=1:totalcash=1000:typeinfo=2:yuanbao=100:type=1
		char buf[TLOG_BUFFER_SIZE];
		SNPRINTFA(buf, sizeof(buf), "%s addyuanbao:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:totalcash=%d:typeinfo=%s:yuanbao=%d:type=%d"
			, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, format_log, yuanbao, type);
		static LogSender* log = ServerInstance()->GetLogClient();
		log->LogDKMLog(buf, pfid);
}

void DKMLogMgr::LogCostMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* logStr, int yuanbao)
{
	if (!open_log_) return;
	char format_log[64] = { 0 };
	FormatLog(format_log, logStr);

	//2016-12-11 12:36:34 costyuanbao:from=101:userid=323523:roleid=6b4715084:account=xx:lev=20:platform=25pp:mac=DC2B61739C2:os=1:totalcash=1000:typeinfo=2:yuanbao=100:yuanbao1=100
	char buf[TLOG_BUFFER_SIZE];
	SNPRINTFA(buf, sizeof(buf), "%s costyuanbao:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:totalcash=%d:typeinfo=%s:itemcount=0:yuanbao=%d:yuanbao1=0"
		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, totalcash, format_log, yuanbao);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDKMLog(buf, pfid);
}


void DKMLogMgr::LogAddItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr)
{
	if (!open_log_) return;
	char format_log[64] = { 0 };
	FormatLog(format_log, logStr);

	//2010-12-11 12:36:34 gain_item:from=101:userid=154123:roleid=6b4715084:account=xx:lev=20:platform=25pp:mac=DC2B617396C2:os=1:itemid=10000:count=30:guid=0:reason=0:type=1:hint=xx
	char buf[TLOG_BUFFER_SIZE];
	SNPRINTFA(buf, sizeof(buf), "%s gain_item:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:itemid=%d:count=%d:guid=%d:reason=%s:type=%d:hint=xx"
		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, itemId, count, guid, format_log, itemType);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDKMLog(buf, pfid);
}

void DKMLogMgr::LogCostItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr)
{
	if (!open_log_) return;
	char format_log[64] = { 0 };
	FormatLog(format_log, logStr);

	//2010-12-11 12:36:34 lose_item:from=101:userid=154128:roleid=6b4715084:account=xx:lev=20:platform=25pp:mac=DC2B617396C2:os=1:itemid=10000:count=30:guid=0:reason=0:type=1:hint=xx
	char buf[TLOG_BUFFER_SIZE];
	SNPRINTFA(buf, sizeof(buf), "%s lose_item:from=%d:userid=%d:roleid=%d:account=%s:lev=%d:platform=%s:mac=null:os=null:itemid=%d:count=%d:guid=%d:reason=%s:type=%d:hint=xx"
		, GetTime(), ServerInstance()->GetServerIndex(), accountid, actorid, name, lvl, pfid, itemId, count, guid, format_log, itemType);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDKMLog(buf, pfid);
}

void DKMLogMgr::LogCreateRole(int accountid, int actorid, const char* name, const char* pfid, const char* addr)
{
	if(!open_log_) return;

	char timestr[64];
	SystemTime sys_t;
	GetSystemTime(sys_t);
	SNPRINTFA(timestr, ArrayCount(timestr),
		"%02d-%02d-%02d %02d:%02d:%02d",
		sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_, sys_t.min_, sys_t.sec_);

	ACTORNAME name2;
	ReplaceString(name, name2, ArrayCount(name2));
	//2016-12-11 12:36:34 createrole:from=101:userid=323523:roleid=6b4715084:account=xx:platform=wl91:ip=1.1.1.1
	char buf[TLOG_BUFFER_SIZE];
	SNPRINTFA(buf, sizeof(buf), "%s createrole:from=%d:userid=%d:roleid=%d:account=%s:platform=%s:os=null:ip=%s", timestr, ServerInstance()->GetServerIndex(), accountid, actorid, name2, pfid, addr);

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDKMLog(buf, pfid);
}


const char* DKMLogMgr::GetTime()
{
	SystemTime sys_t;
	GetSystemTime(sys_t);
	SNPRINTFA(time_text_, ArrayCount(time_text_),
	          "%02d-%02d-%02d %02d:%02d:%02d",
	          sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_, sys_t.min_, sys_t.sec_);
	return time_text_;
}

void DKMLogMgr::FormatLog(char *dstr, const char* str) {
	if (!str) return;
	uint16_t len = static_cast<uint16_t>( strlen(str));
	for (uint16_t i=0;i < len; ++i) {
		switch (str[i]) {
			case '=':
			case ' ':
			case ':':{
				dstr[i] = '_';
				break;
			}
			default:  {
				dstr[i] = str[i];
				break;
			}
		}
	}
}


