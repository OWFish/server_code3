#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "os_def.h"
#include "_ast.h"

extern "C"
{
#include "lua.h"
#include "ltm.h"
};

#include "share_util.h"
#include "luabase/clvariant.h"
#include <new>
#include "memory/memory_container.hpp"
#include "container/bz_hash_table.h"
#include "container/str_hash_table.h"
#include "lang/lang_section.h"
#include "lang/lua_lang_section.h"

namespace LangTextSectionExport
{
static const char* LangTextSectionName = "LangTextSection";
static const char* LangTextSectionRefName = "LangTextSectionRef";
static const unsigned int RegistedTypeId = hashstr(LangTextSectionName);
static const unsigned int RegistedRefTypeId = hashstr(LangTextSectionRefName);

static LangSection* getDataPtr(lua_State* L, int index = 1)
{
	if (lua_type(L, index) != LUA_TUSERDATA)
		return NULL;

	LangSection* result = NULL;

	/*
	int lua_getmetatable (lua_State *L, int index);
	把给定索引指向的值的元表压入堆栈。如果索引无效，或是这个值没有元表，函数将返回 0 并且不会向栈上压任何东西。
	*/
	if (lua_getmetatable(L, index))
	{
		lua_pushlstring(L, "_typeid", 7);
		lua_rawget(L, -2);

		if (lua_isnumber(L, -1))
		{
			unsigned int tpid = (unsigned int)lua_tonumber(L, -1);

			if (RegistedRefTypeId == tpid)
				result = *(LangSection**)lua_touserdata(L, (index > 0) ? index : index - 2);
			else if (RegistedTypeId == tpid)
				result = (LangSection*)lua_touserdata(L, (index > 0) ? index : index - 2);
		}

		//弹出_typeid以及metatable
		lua_pop(L, 2);
	}

	return result;
}
static void setType(lua_State* L, const char* classeName, int tidx = -1)
{
	lua_getglobal(L, classeName);

	if (lua_istable(L, -1))
		lua_setmetatable(L, (tidx > 0) ? tidx : tidx - 1);
	else lua_pop(L, 1);
}
static int newRef(lua_State* L, LangSection& section)
{
	LangSection** s = (LangSection**)lua_newuserdata(L, sizeof(*s));
	//设置类型表
	setType(L, LangTextSectionRefName);
	*s = &section;
	return 1;
}
static void setGlobal(lua_State* L, LangSection& section, const char* globalName)
{
	LangSection** s = (LangSection**)lua_newuserdata(L, sizeof(*s));
	//设置类型表
	setType(L, LangTextSectionRefName);
	*s = &section;
	//设为全局变量
	lua_setglobal(L, globalName);
}
static int get(lua_State* L)
{
	LangSection* sec = getDataPtr(L);

	if (!sec)
		return 0;

	const char* name = lua_tostring(L, 2);
	sec = sec->getSection(name);

	if (!sec)
		return 0;

	//返回字符串
	if (sec->getType() == LangSection::eText)
	{
		lua_pushstring(L, sec->getText());
		return 1;
	}

	//返回文字包引用
	return newRef(L, *sec);
}

static void setMetaNameClosure(lua_State* L, const char* metaName, const void* fn, int tidx = -1)
{
	lua_pushstring(L, metaName);
	lua_pushcfunction(L, (lua_CFunction)fn);
	lua_rawset(L, (tidx < 0) ? tidx - 2 : tidx);
}

static void registTo(lua_State* L, const char* className)
{
	lua_createtable(L, 0, 3);
	//typename
	lua_pushlstring(L, "_typename", 9);
	lua_pushstring(L, className);
	lua_rawset(L, -3);
	//typeid
	lua_pushlstring(L, "_typeid", 7);
	lua_pushnumber(L, hashstr(className));
	lua_rawset(L, -3);
	//__index
	setMetaNameClosure(L, "__index", (const void*)get);

	lua_setglobal(L, className);
}

void regist(lua_State* L)
{
	registTo(L, LangTextSectionRefName);
}
}

namespace LuaLangSection
{
void regist(lua_State* L)
{
	LangTextSectionExport::regist(L);
}

void registTo(lua_State* L, const char* className)
{
	LangTextSectionExport::registTo(L, className);
}

int returnValue(lua_State* L, LangSection& section)
{
	return LangTextSectionExport::newRef(L, section);
}

void setGlobalValue(lua_State* L, LangSection& section, const char* globalname)
{
	return LangTextSectionExport::setGlobal(L, section, globalname);
}
}
