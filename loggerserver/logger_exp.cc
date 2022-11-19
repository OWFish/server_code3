#include "stdafx.h"
#include "logger_exp.h"

extern LoggerServer* srv;

namespace logger
{
void getDate(int& year, int& month, int& day)
{
	SystemTime Systime;
	GetSystemTime(Systime);
	day = Systime.mday_;
	month = Systime.mon_;
	year = Systime.year_;
}

const char* getDateStr(void)
{
	SystemTime st;
	GetSystemTime(st);
	static char buf[512];
	sprintf(buf, "%d-%d-%d %d:%d:%d",
		st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_
		);
	return buf;
}


int exeSql(void* db_connection, const char* sql)
{
	if (!db_connection || !sql) return 1;

	SQLConnection* db = (SQLConnection*)db_connection;
	int ret = db->Exec(sql);

	if (ret == 0)
		db->ResetQuery();

	return ret;
}

const char* urlEncode(const char* msg)
{
	if(!msg) return "";

	static char buf[4096];
	return LoggerServer::UrlEncode(msg, buf);
}

void sendToScribe(int serverId, const char* para /*= ""*/,bool final,const char* key )
{
	if(!para) return;
	srv->SendToScribe(serverId, para,final,key);
}

}

