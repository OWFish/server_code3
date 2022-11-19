#ifndef _LOGGER_EXP_H_
#define _LOGGER_EXP_H_

//tolua_begin
static int print(lua_State* L)
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

		OutputMsg(rmNormal, s);
		lua_pop(L, 1);  /* pop result */
	}

	return 0;
}

namespace LDbserver
{
void getDate(int& year, int& month, int& day);

int exeSql(void* db_connection, const char* sql);

// ���ݿ�������
int dbQuery(void* db_conn, const char* sql);
int dbExe(void* db_connection, const char* sql);

void dbResetQuery(void* db_conn);

void* dbCurrentRow(void* db_conn);

const char* dbGetRow(void* row, int idx);

int dbGetRowCount(void* db_conn);

void* dbNextRow(void* db_conn);

// ���ܽӿڣ���
/*
	��һ��������dbclient��ָ�룬
	���������������֣�����ϵͳid��Э��ţ�����siEntity, dcSaveGemItemData
	��4������param3��ָ��������������
	����N�������� N = param3 * 2,�ֱ�Ϊ�������ͣ�����ֵ
	�������ͼ�tagDataType����
*/
int sendToGame(lua_State *L);

// �������ݰ��ͷ���
void* allocDp(void* dbclient, int sysid, int pid);

void flushDp(void* dbclient, void* dp);

int int64ToStr(lua_State* L);

double getInt64(const char* str);

bool isBattleSrv(void* dbclient);
}

//tolua_end

#endif

