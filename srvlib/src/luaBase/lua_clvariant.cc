#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "os_def.h"
#include <_ast.h>

#include "share_util.h"

extern "C"
{
#include <lua.h>
#include <ltm.h>
};
#include "luabase/clvariant.h"
#include "luabase/lua_clvariant.h"
#include <new>



namespace CLVariantExport
{
	static const unsigned int RegistedTypeId = hashstr("CCLVariant");
	static const unsigned int RegistedRefTypeId = hashstr("CCLVariantRef");

	static CLVariant* getDataPtr(lua_State *L, int index = 1)
	{
		if (lua_type(L, index) != LUA_TUSERDATA)
			return NULL;
		CLVariant *result = NULL;
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
					result = *(CLVariant**)lua_touserdata(L, (index > 0) ? index : index - 2);
				else if (RegistedTypeId == tpid)
					result = (CLVariant*)lua_touserdata(L, (index > 0) ? index : index - 2);
			}
			//弹出_typeid以及metatable
			lua_pop(L, 2);
		}
		return result;
	}
	static void setType(lua_State *L, const char *classeName, int tidx = -1)
	{
		lua_getglobal(L, classeName);
		if (lua_istable(L, -1))
			lua_setmetatable(L, (tidx > 0) ? tidx : tidx - 1);
		else lua_pop(L, 1);
	}
	static int newRef(lua_State *L, CLVariant &var)
	{
		CLVariant **pVar = (CLVariant**)lua_newuserdata(L, sizeof(*pVar));
		//设置类型表
		setType(L, "CCLVariantRef");
		*pVar = &var;
		return 1;
	}
	static void setVarFromTable(lua_State *L, CLVariant *pVar, int vidx = -1);
	static void setVarMember(lua_State *L, CLVariant *pVar, const char* sName, int vidx = -1);
	static int newInst(lua_State *L)
	{
		CLVariant *pVar = (CLVariant*)lua_newuserdata(L, sizeof(CLVariant));
		//为userdata设置类型表
		setType(L, "CCLVariant");
		new (pVar)CLVariant();
		//如果给予了构造参数，则设置变量值
		if (lua_gettop(L) > 2)//LUA中传入meta表，且在栈顶创建了userdata所以这里要大于2
		{
			switch(lua_type(L, 2))
			{
			case LUA_TBOOLEAN:
				*pVar = lua_toboolean(L, 2);
				break;
			case LUA_TNUMBER:
				*pVar = lua_tonumber(L, 2);
				break;
			case LUA_TSTRING:
				*pVar = lua_tostring(L, 2);
				break;
			case LUA_TTABLE:
				setVarFromTable(L, pVar, 2);
				break;
			case LUA_TUSERDATA:
				{
					CLVariant *pVar2 = getDataPtr(L, 2);
					if (pVar2)
						*pVar = *pVar2;
				}
				break;
			}
		}
		return 1;
	}
	static int get(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			lua_pushnil(L);
			return 1;
		}

		const char* sName = lua_tostring(L, 2);

		pVar = pVar->get(sName);
		if (!pVar)
		{
			lua_pushnil(L);
			return 1;
		}

		switch(pVar->type())
		{
		case CLVariant::vNumber:
			lua_pushnumber(L, (double)*pVar);
			break;
		case CLVariant::vStr:
			lua_pushlstring(L, (const char*)*pVar, pVar->len());
			break;
		case CLVariant::vStruct:
			newRef(L, *pVar);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static void setVarFromTable(lua_State *L, CLVariant *pVar, int vidx)
	{
		lua_pushnil(L);
		if (vidx < 0) vidx--;
		while (lua_next(L, vidx))
		{
			setVarMember(L, pVar, lua_tostring(L, -2));
			lua_pop(L, 1);//remove value
		}
	}
	static void setVarMember(lua_State *L, CLVariant *pVar, const char* sName, int vidx)
	{
		switch(lua_type(L, vidx))
		{
		case LUA_TNIL:
			pVar = pVar->get(sName);
			if (pVar) pVar->clear();
			break;
		case LUA_TBOOLEAN:
			pVar->set(sName, lua_toboolean(L, vidx));
			break;
		case LUA_TNUMBER:
			pVar->set(sName, lua_tonumber(L, vidx));
			break;
		case LUA_TSTRING:
			pVar->set(sName, lua_tostring(L, vidx));
			break;
		case LUA_TTABLE:
			pVar = &pVar->set(sName);
			pVar->setToEmptyStruct();
			setVarFromTable(L, pVar, vidx);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, vidx);
				if (pVar2)
					*pVar = *pVar2;
			}
			break;
		}
	}
	static int set(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			lua_pushnil(L);
			return 1;
		}
		const char* sName = lua_tostring(L, 2);
		setVarMember(L, pVar, sName, 3);
		//return value
		lua_pushvalue(L, 3);
		return 1;
	}
	static int gc(lua_State *L)
	{
		/*
		int lua_getmetatable (lua_State *L, int index);
		把给定索引指向的值的元表压入堆栈。如果索引无效，或是这个值没有元表，函数将返回 0 并且不会向栈上压任何东西。
		*/
		if (lua_getmetatable(L, 1))
		{
			lua_pushlstring(L, "_typeid", 7);
			lua_rawget(L, -2);
			if (lua_isnumber(L, -1))
			{
				unsigned int tpid = (unsigned int)lua_tonumber(L, -1);
				if (RegistedRefTypeId == tpid)
					*(CLVariant**)lua_touserdata(L, 1) = NULL;
				else if (RegistedTypeId == tpid)
					((CLVariant*)lua_touserdata(L, 1))->~CLVariant();
			}
			//移除_typeid以及metatable
			lua_pop(L, 2);
		}
		return 0;
	}
	static int eq(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}
		bool boResult = false;
		char numBuf[64];

		switch(lua_type(L, 2))
		{
		case LUA_TNIL:
			boResult = pVar->type() == CLVariant::vNil;
			break;
		case LUA_TBOOLEAN:
			switch(pVar->type())
			{
			case CLVariant::vNil: 
				boResult = lua_toboolean(L, 2) == FALSE;
				break;
			case CLVariant::vNumber: 
				boResult = ((double)(*pVar) != 0) == (lua_toboolean(L, 2) != FALSE);
				break;
			case CLVariant::vStr: 
				boResult = (pVar->len() == 4) && (*((unsigned int *)(const char*)(*pVar)) == MAKEFOUR('t', 'r', 'u', 'e'))
					== (lua_toboolean(L, 2) == TRUE);
				break;
			case CLVariant::vStruct: 
				boResult = (pVar->len() > 0) == (lua_toboolean(L, 2) == TRUE);
				break;
			}
			break;
		case LUA_TNUMBER:
			switch(pVar->type())
			{
			case CLVariant::vNumber:
				boResult = (double)*pVar == lua_tonumber(L, 2);
				break;
			case CLVariant::vStr:
				lua_number2str(numBuf, lua_tonumber(L, 2));
				boResult = !strcmp((const char*)*pVar, numBuf);
				break;
			}
			break;
		case LUA_TSTRING:
			switch(pVar->type())
			{
			case CLVariant::vStr:
				boResult = !strcmp((const char*)*pVar, lua_tostring(L, 2));
				break;
			case CLVariant::vNumber:
				lua_number2str(numBuf, (double)*pVar);
				boResult = !strcmp(numBuf, lua_tostring(L, 2));
				break;
			}
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				boResult = pVar2 && *pVar == *pVar2;
			}
			break;
		}
		lua_pushboolean(L, boResult);
		return 1;
	}
	static int concat(lua_State *L);
	static int add(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		double n, d;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			break;
		case CLVariant::vStr:
			n = lua_str2number((const char*)*pVar, &e);
			if (e && *e)
				return concat(L);
			break;
		default:
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
			lua_pushnumber(L, n + lua_tonumber(L, 2));
			break;
		case LUA_TSTRING:
			d = lua_str2number(lua_tostring(L, 2), &e);
			if (!e || !*e)
				lua_pushnumber(L, n + d);
			else return concat(L);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					if (pVar2->type() == CLVariant::vNumber)
						lua_pushnumber(L, n + (double)*pVar2);
					else if (pVar2->type() == CLVariant::vStr)
					{
						d = lua_str2number((const char*)*pVar2, &e);
						if (!e || !*e)
							lua_pushnumber(L, n + d);
						else return concat(L);
					}
					else lua_pushnumber(L, n);
				}
				else lua_pushnil(L);
			}
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static int sub(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		double n, d;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			break;
		case CLVariant::vStr:
			n = lua_str2number((const char*)*pVar, &e);
			if (e && *e)
			{
				lua_pushnil(L);
				return 1;
			}
			break;
		default:
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
			lua_pushnumber(L, n - lua_tonumber(L, 2));
			break;
		case LUA_TSTRING:
			d = lua_str2number(lua_tostring(L, 2), &e);
			if (!e || !*e)
				lua_pushnumber(L, n - d);
			else lua_pushnumber(L, n);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					if (pVar2->type() == CLVariant::vNumber)
						lua_pushnumber(L, n - (double)*pVar2);
					else if (pVar2->type() == CLVariant::vStr)
					{
						d = lua_str2number((const char*)*pVar2, &e);
						if (!e || !*e)
							lua_pushnumber(L, n - d);
						else lua_pushnumber(L, n);
					}
					else lua_pushnumber(L, n);
				}
				else lua_pushnil(L);
			}
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static int mul(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		double n, d;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			break;
		case CLVariant::vStr:
			n = lua_str2number((const char*)*pVar, &e);
			if (e && *e)
			{
				lua_pushnil(L);
				return 1;
			}
			break;
		default:
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
			lua_pushnumber(L, n * lua_tonumber(L, 2));
			break;
		case LUA_TSTRING:
			d = lua_str2number(lua_tostring(L, 2), &e);
			if (!e || !*e)
				lua_pushnumber(L, n * d);
			else lua_pushnumber(L, 0);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					if (pVar2->type() == CLVariant::vNumber)
						lua_pushnumber(L, n * (double)*pVar2);
					else if (pVar2->type() == CLVariant::vStr)
					{
						d = lua_str2number((const char*)*pVar2, &e);
						if (!e || !*e)
							lua_pushnumber(L, n * d);
						else lua_pushnumber(L, 0);
					}
					else lua_pushnumber(L, 0);
				}
				else lua_pushnil(L);
			}
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static int div(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		double n, d;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			break;
		case CLVariant::vStr:
			n = lua_str2number((const char*)*pVar, &e);
			if (e && *e)
			{
				lua_pushnil(L);
				return 1;
			}
			break;
		default:
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
			d = lua_tonumber(L, 2);
			if (d != 0)
				lua_pushnumber(L, n / d);
			else lua_pushnumber(L, 0);
			break;
		case LUA_TSTRING:
			d = lua_str2number(lua_tostring(L, 2), &e);
			if ((!e || !*e) && d != 0)
				lua_pushnumber(L, n / d);
			else lua_pushnumber(L, 0);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					if (pVar2->type() == CLVariant::vNumber)
					{
						d = *pVar2;
						if (d != 0)
							lua_pushnumber(L, n / d);
						else lua_pushnumber(L, 0);
					}
					else if (pVar2->type() == CLVariant::vStr)
					{
						d = lua_str2number((const char*)*pVar2, &e);
						if ((!e || !*e) && d != 0)
							lua_pushnumber(L, n / d);
						else lua_pushnumber(L, 0);
					}
					else lua_pushnumber(L, 0);
				}
				else lua_pushnil(L);
			}
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static int mod(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		int64_t n, d;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			break;
		case CLVariant::vStr:
			n = (int64_t)lua_str2number((const char*)*pVar, &e);
			if (e && *e)
			{
				lua_pushnil(L);
				return 1;
			}
			break;
		default:
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
			d = (int64_t)lua_tonumber(L, 2);
			if (d != 0)
				lua_pushnumber(L, (lua_Number)(n % d));
			else lua_pushnumber(L, 0);
			break;
		case LUA_TSTRING:
			d = (int64_t)lua_str2number(lua_tostring(L, 2), &e);
			if ((!e || !*e) && d != 0)
				lua_pushnumber(L, (lua_Number)(n % d));
			else lua_pushnumber(L, 0);
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					if (pVar2->type() == CLVariant::vNumber)
					{
						d = *pVar2;
						if (d != 0)
							lua_pushnumber(L, (lua_Number)(n % d));
						else lua_pushnumber(L, 0);
					}
					else if (pVar2->type() == CLVariant::vStr)
					{
						d = (int64_t)lua_str2number((const char*)*pVar2, &e);
						if ((!e || !*e) && d != 0)
							lua_pushnumber(L, (lua_Number)(n % d));
						else lua_pushnumber(L, 0);
					}
					else lua_pushnumber(L, 0);
				}
				else lua_pushnil(L);
			}
			break;
		default:
			lua_pushnil(L);
			break;
		}
		return 1;
	}
	static int unm(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		//尝试将参数1转换为整数
		char *e;
		double n;
		switch(pVar->type())
		{
		case CLVariant::vNumber:
			e = NULL;
			n = *pVar;
			lua_pushnumber(L, -n);
			break;
		case CLVariant::vStr:
			n = lua_str2number((const char*)*pVar, &e);
			if (!e || !*e)
				lua_pushnumber(L, -n);
			else lua_pushnil(L);
			break;
		default:
			return 0;
		}

		return 1;
	}
	static int len(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		switch(pVar->type())
		{
		case CLVariant::vStr:
		case CLVariant::vStruct:
			lua_pushnumber(L, (lua_Number)pVar->len());
			break;
		default:
			lua_pushnumber(L, 0);
			break;
		}
		return 1;
	}
	static int lt(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)//不能在这里判断（pVar->type() != CCLVariant::vNumber），因为进行>运算的时候，lua会将第二个参数传递为第一个参数
		{
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
		case LUA_TSTRING:
			lua_pushboolean(L, (double)*pVar < lua_tonumber(L, 2));
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
					lua_pushboolean(L, *pVar < *pVar2);
				else lua_pushboolean(L, FALSE);
			}
			break;
		default:
			lua_pushboolean(L, FALSE);
			break;
		}
		return 1;
	}
	static int le(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)//不能在这里判断（pVar->type() != CCLVariant::vNumber），因为进行>运算的时候，lua会将第二个参数传递为第一个参数
		{
			return 0;
		}

		switch(lua_type(L, 2))
		{
		case LUA_TNUMBER:
		case LUA_TSTRING:
			lua_pushboolean(L, (double)*pVar <= lua_tonumber(L, 2));
			break;
		case LUA_TUSERDATA:
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
					lua_pushboolean(L, *pVar <= *pVar2);
				else lua_pushboolean(L, FALSE);
			}
			break;
		default:
			lua_pushboolean(L, FALSE);
			break;
		}
		return 1;
	}
	static int concat(lua_State *L)
	{
		CLVariant *pVar = getDataPtr(L);
		if (!pVar)
		{
			return 0;
		}

		int t = pVar->type();
		if ( t != CLVariant::vNumber && t != CLVariant::vStr )
		{
			lua_pushnil(L);
			return 1;
		}
		//确定第二个字符串指针
		char Num2Buf[32];
		const char *s2 = NULL;
		int t2 = lua_type(L, 2);
		if ( t2 != LUA_TNUMBER && t2 != LUA_TSTRING)
		{
			if (t2 == LUA_TUSERDATA)
			{
				CLVariant *pVar2 = getDataPtr(L, 2);
				if (pVar2)
				{
					switch(pVar2->type())
					{
					case CLVariant::vNumber:
						lua_number2str(Num2Buf, (double)*pVar2);
						s2 = Num2Buf;
						break;
					case CLVariant::vStr:
						s2 = *pVar2;
						break;
					}
				}
			}
		}
		else s2 = lua_tostring(L, 2);
		//第二个字符串指针无效则退出
		if (!s2)
		{
			return 0;
		}
		size_t len2 = strlen(s2);

		void* ud;
		lua_Alloc palloc = lua_getallocf(L, &ud);
		//确定第一个字符串并连接生成新字符串
		char *sRetPtr = NULL;
		size_t len1, newlen = 0;
		switch (pVar->type())
		{
		case CLVariant::vNumber:
			{
				char sNum1Buf[32];
				len1 = lua_number2str(sNum1Buf, (double)*pVar);
				newlen = len1 + len2;
				sRetPtr = (char*)palloc(ud, NULL, 0, newlen + 1);
				memcpy(sRetPtr, sNum1Buf, len1);
				memcpy(&sRetPtr[len1], s2, len2 + 1);
			}
			break;
		case CLVariant::vStr:
			{
				len1 = pVar->len();
				newlen = len1 + strlen(s2);
				sRetPtr = (char*)palloc(ud, NULL, 0, newlen + 1);
				memcpy(sRetPtr, (const char*)*pVar, len1);
				memcpy(&sRetPtr[len1], s2, len2 + 1);
			}
		}
		if (sRetPtr)
		{
			lua_pushlstring(L, sRetPtr, newlen);
			palloc(ud, sRetPtr, newlen + 1, 0);
		}
		else lua_pushnil(L);
		return 1;
	}






	static const char *const luaT_eventname[] = {  /* ORDER TM */
		"__index", "__newindex",
		"__gc", "__mode", "__eq",
		"__add", "__sub", "__mul", "__div", "__mod",
		"__pow", "__unm", "__len", "__lt", "__le",
		"__concat", "__call"
	};

	static void setMetaNameClosure(lua_State *L, const char* metaName, const void* fn, int tidx = -1)
	{  
		lua_pushstring(L, metaName);
		lua_pushcfunction(L, (lua_CFunction)fn);
		lua_rawset(L, (tidx < 0) ? tidx - 2 : tidx);
	}

	static void setMetaClosure(lua_State *L, TMS tm, const void* fn, int tidx = -1)
	{  
		if (tm < 0 || tm >= (int)ArrayCount(luaT_eventname) )
			return;
		setMetaNameClosure(L, luaT_eventname[tm], fn, tidx);
	}

	static void registTo(lua_State *L, const char *className)
	{
		lua_createtable(L, 0, 17);
		//typename
		lua_pushlstring(L, "_typename", 9);
		lua_pushstring(L, className);
		lua_rawset(L, -3);
		//typeid
		lua_pushlstring(L, "_typeid", 7);
		lua_pushnumber(L, hashstr(className));
		lua_rawset(L, -3);
		//constructor
		setMetaNameClosure(L, "new", (const void*)newInst);
		//__index
		setMetaClosure(L, TM_INDEX, (const void*)get);
		//__newindex
		setMetaClosure(L, TM_NEWINDEX, (const void*)set);
		//__gc
		setMetaClosure(L, TM_GC, (const void*)gc);
		//__eq
		setMetaClosure(L, TM_EQ, (const void*)eq);
		//__add
		setMetaClosure(L, TM_ADD, (const void*)add);
		//__sub
		setMetaClosure(L, TM_SUB, (const void*)sub);
		//__mul
		setMetaClosure(L, TM_MUL, (const void*)mul);
		//__div
		setMetaClosure(L, TM_DIV, (const void*)div);
		//__mod
		setMetaClosure(L, TM_MOD, (const void*)mod);
		//__unm
		setMetaClosure(L, TM_UNM, (const void*)unm);
		//__len
		setMetaClosure(L, TM_LEN, (const void*)len);
		//__lt
		setMetaClosure(L, TM_LT, (const void*)lt);
		//__le
		setMetaClosure(L, TM_LE, (const void*)le);
		//__concat
		setMetaClosure(L, TM_CONCAT, (const void*)concat);

		lua_setglobal(L, className);
	}

	void regist(lua_State *L)
	{
		registTo(L, "CCLVariant");
		registTo(L, "CCLVariantRef");
	}
}

namespace LuaCLVariant
{
	void regist(lua_State *L)
	{
		CLVariantExport::regist(L);
	}

	void registTo(lua_State *L, const char *className)
	{
		CLVariantExport::registTo(L, className);
	}

	int returnValue(lua_State *L, CLVariant &var)
	{
		return CLVariantExport::newRef(L, var);
	}
}
