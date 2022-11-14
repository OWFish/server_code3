extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <ltm.h>
}

#include "os_def.h"
#include "stream.h"

#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"

void ScriptValueList::pushArgs(lua_State* L, int count)
{
	for (int i = 0; i < count; ++i)
	{
		ScriptValue& value = values_[i];

		switch (value.getType())
		{
		case ScriptValue::vBool:
			lua_pushboolean(L, value.operator bool());
			break;

		case ScriptValue::vLightData:
		case ScriptValue::vUserData:
			{
				const void* ptr = value;

				if (ptr)
					lua_pushlightuserdata(L, (void*)ptr);
				else lua_pushnil(L);
			}
			break;

		case ScriptValue::vNumber:
			lua_pushnumber(L, value.operator double());
			break;

		case ScriptValue::vString:
			lua_pushlstring(L, value.operator const char * (), value.getSize());
			break;

		case ScriptValue::vCFunction:
			{
				lua_CFunction pfn = value;

				if (pfn)
					lua_pushcfunction(L, pfn);
				else lua_pushnil(L);
			}
			break;

		default:
			lua_pushnil(L);
			break;
		}
	}
}

int ScriptValueList::getResults(lua_State* L, int count)
{
	int type, ret = 0;

	while (count > 0)
	{
		if (count_ >= MaxValueCount)
			break;

		type = lua_type(L, -count);

		switch (type)
		{
		case LUA_TBOOLEAN:
			values_[count_++] = lua_toboolean(L, -count) != FALSE;
			break;

		case LUA_TLIGHTUSERDATA:
			values_[count_++] = lua_touserdata(L, -count);
			break;

		case LUA_TNUMBER:
			values_[count_++] = lua_tonumber(L, -count);
			break;

		case LUA_TSTRING:
			values_[count_++] = lua_tostring(L, -count);
			break;

		case LUA_TUSERDATA:
			values_[count_++].SetUserData(lua_touserdata(L, -count), lua_objlen(L, -count));
			break;

		default:
			values_[count_++].clear();
			break;
		}

		count--;
		ret++;
	}

	lua_pop(L, (int)(ret + count));
	return ret;
}

int ScriptValueList::getArguments(lua_State* L, int idx)
{
	int type, ret = 0;
	int count = lua_gettop(L);

	clear();

	while (idx <= count)
	{
		if (count_ >= MaxValueCount)
			break;

		type = lua_type(L, (int)idx);

		switch (type)
		{
		case LUA_TBOOLEAN:
			values_[count_++] = lua_toboolean(L, (int)idx) != FALSE;
			break;

		case LUA_TLIGHTUSERDATA:
			values_[count_++] = lua_touserdata(L, (int)idx);
			break;

		case LUA_TNUMBER:
			values_[count_++] = lua_tonumber(L, (int)idx);
			break;

		case LUA_TSTRING:
			values_[count_++] = lua_tostring(L, (int)idx);
			break;

		case LUA_TUSERDATA:
			values_[count_++].SetUserData(lua_touserdata(L, (int)idx), lua_objlen(L, (int)idx));
			break;

		default:
			values_[count_++].clear();
			break;
		}

		idx++;
		ret++;
	}

	return ret;
}

