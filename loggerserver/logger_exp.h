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

namespace logger
{
	void getDate(int& year, int& month, int& day);
	const char* getDateStr(void);

	int exeSql(void* db_connection, const char* sql);

	const char* urlEncode(const char* msg);

	void sendToScribe(int serverId, const char* para = "",bool final = true,const char* key = "0948e5fa35a91677a2d8d8e7527ee461");
}

//tolua_end

#endif

