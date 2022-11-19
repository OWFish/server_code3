#include "StdAfx.h"
#include "dbserver_exp.h"


namespace LDbserver
{
void getDate(int& year, int& month, int& day)
{
	SystemTime Systime;
	GetSystemTime(Systime);
	day = Systime.mday_;
	month = Systime.mon_;
	year = Systime.year_;
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

int dbQuery(void* db_conn, const char* sql)
{
	if (!db_conn || !sql) return 1;

	SQLConnection* db = (SQLConnection*)db_conn;
	int ret = db->Query(sql);
	return ret;
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

int sendToGame(lua_State* L)
{
	DBSession* db = (DBSession*)lua_touserdata(L, 1);
	int sysid = (int)lua_tointeger(L, 2);
	int pid = (int)lua_tointeger(L, 3);

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

void* allocDp(void* dbclient, int sysid, int pid)
{
	if (!dbclient) return NULL;

	DataPacket& packet = ((DBSession*)dbclient)->allocProtoPacket(MAKEINT16(sysid, pid));
	return &packet;
}

void flushDp(void* dbclient, void* dp)
{
	if (!dbclient || !dp) return;

	((DBSession*)dbclient)->flushProtoPacket(*(DataPacket*)dp);
}

int int64ToStr(lua_State* L)
{
	double d = lua_tonumber(L, 1);
	int64_t dst;
	memcpy(&dst, &d, sizeof(d));
	char ret[128];
#ifdef _MSC_VER
	SNPRINTFA(ret, sizeof(ret) - 1, "%I64d", dst);
#else
	SNPRINTFA(ret, sizeof(ret) - 1, "%lld", dst);
#endif
	lua_pushstring(L, ret);
	return 1;
}

double getInt64(const char* str)
{
	if (!str) return 0.0;

	int64_t dst = StrToInt64(str);
	double ret;
	memcpy(&ret, &dst, sizeof(ret));
	return ret;
}

bool isBattleSrv(void* dbclient)
{
	if (!dbclient) return false;

	return ((DBSession*)dbclient)->IsBattleSrv();
}


}

