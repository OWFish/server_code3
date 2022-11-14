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
#include "luabase/base_clv_class.h"
#include "luabase/lua_variant_class.h"
#include <new>

const LuaVariantClass::FuncCall LuaVariantClass::fnList[] =
{
	{"test", &LuaVariantClass::testCall},
};

LuaVariantClass::LuaVariantClass()
	: Inherited("CCLVariant")
{
	exportFunctions(fnList, ArrayCount(fnList));
}

CLVariant* LuaVariantClass::create(lua_State* L)
{
	CLVariant* pVar = (CLVariant*)lua_newuserdata(L, sizeof(*pVar));
	new(pVar)CLVariant();

	//如果给予了构造参数，则设置变量值
	if (lua_gettop(L) > 2)//LUA中传入meta表，且在栈顶创建了userdata所以这里要大于2
	{
		switch (lua_type(L, 2))
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
				CLVariant* pVar2 = getDataPtr(L, 2);

				if (pVar2)
					*pVar = *pVar2;
			}
			break;
		}
	}

	return pVar;
}

void LuaVariantClass::destroy(lua_State*, CLVariant* ptr)
{
	ptr->~CLVariant();
}

int LuaVariantClass::get(lua_State* L, CLVariant* pVar)
{
	const char* sName = lua_tostring(L, 1);

	CLVariant* pMemVar = pVar->get(sName);

	if (!pMemVar)
	{
		return Inherited::get(L, pVar);
	}

	pVar = pMemVar;

	switch (pVar->type())
	{
	case CLVariant::vNumber:
		lua_pushnumber(L, (double)*pVar);
		break;

	case CLVariant::vStr:
		lua_pushlstring(L, (const char*)*pVar, pVar->len());
		break;

	case CLVariant::vStruct:
		newReference(L, *pVar);
		break;

	default:
		lua_pushnil(L);
		break;
	}

	return 1;
}

int LuaVariantClass::set(lua_State* L, CLVariant* pVar)
{
	const char* sName = lua_tostring(L, 1);
	setVarMember(L, pVar, sName, 2);
	//return value
	lua_pushvalue(L, 2);
	return 1;
}

int LuaVariantClass::eq(lua_State* L, CLVariant* pVar)
{
	bool boResult = false;
	char numBuf[64];

	switch (lua_type(L, 1))
	{
	case LUA_TNIL:
		boResult = pVar->type() == CLVariant::vNil;
		break;

	case LUA_TBOOLEAN:
		switch (pVar->type())
		{
		case CLVariant::vNil:
			boResult = lua_toboolean(L, 1) == FALSE;
			break;

		case CLVariant::vNumber:
			boResult = ((double)(*pVar) != 0) == (lua_toboolean(L, 1) != FALSE);
			break;

		case CLVariant::vStr:
			boResult = (pVar->len() == 4) && (*((unsigned int*)(const char*)(*pVar)) == MAKEFOUR('t', 'r', 'u', 'e'))
			           == (lua_toboolean(L, 1) == TRUE);
			break;

		case CLVariant::vStruct:
			boResult = (pVar->len() > 0) == (lua_toboolean(L, 1) == TRUE);
			break;
		}

		break;

	case LUA_TNUMBER:
		switch (pVar->type())
		{
		case CLVariant::vNumber:
			boResult = (double) * pVar == lua_tonumber(L, 1);
			break;

		case CLVariant::vStr:
			lua_number2str(numBuf, lua_tonumber(L, 1));
			boResult = !strcmp((const char*)*pVar, numBuf);
			break;
		}

		break;

	case LUA_TSTRING:
		switch (pVar->type())
		{
		case CLVariant::vStr:
			boResult = !strcmp((const char*)*pVar, lua_tostring(L, 1));
			break;

		case CLVariant::vNumber:
			lua_number2str(numBuf, (double)*pVar);
			boResult = !strcmp(numBuf, lua_tostring(L, 1));
			break;
		}

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);
			boResult = pVar2 && *pVar == *pVar2;
		}
		break;
	}

	lua_pushboolean(L, boResult);
	return 1;
}

int LuaVariantClass::add(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	double n, d;

	switch (pVar->type())
	{
	case CLVariant::vNumber:
		e = NULL;
		n = *pVar;
		break;

	case CLVariant::vStr:
		n = lua_str2number((const char*)*pVar, &e);

		if (e && *e)
			return concat(L, pVar);

		break;

	default:
		return 0;
	}

	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
		lua_pushnumber(L, n + lua_tonumber(L, 1));
		break;

	case LUA_TSTRING:
		d = lua_str2number(lua_tostring(L, 1), &e);

		if (!e || !*e)
			lua_pushnumber(L, n + d);
		else return concat(L, pVar);

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

			if (pVar2)
			{
				if (pVar2->type() == CLVariant::vNumber)
					lua_pushnumber(L, n + (double)*pVar2);
				else if (pVar2->type() == CLVariant::vStr)
				{
					d = lua_str2number((const char*)*pVar2, &e);

					if (!e || !*e)
						lua_pushnumber(L, n + d);
					else return concat(L, pVar);
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

int LuaVariantClass::sub(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	double n, d;

	switch (pVar->type())
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
		lua_pushnil(L);
		return 1;
	}

	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
		lua_pushnumber(L, n - lua_tonumber(L, 1));
		break;

	case LUA_TSTRING:
		d = lua_str2number(lua_tostring(L, 1), &e);

		if (!e || !*e)
			lua_pushnumber(L, n - d);
		else lua_pushnumber(L, n);

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::mul(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	double n, d;

	switch (pVar->type())
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
		lua_pushnil(L);
		return 1;
	}

	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
		lua_pushnumber(L, n * lua_tonumber(L, 1));
		break;

	case LUA_TSTRING:
		d = lua_str2number(lua_tostring(L, 1), &e);

		if (!e || !*e)
			lua_pushnumber(L, n * d);
		else lua_pushnumber(L, 0);

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::div(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	double n, d;

	switch (pVar->type())
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
		lua_pushnil(L);
		return 1;
	}

	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
		d = lua_tonumber(L, 1);

		if (d != 0)
			lua_pushnumber(L, n / d);
		else lua_pushnumber(L, 0);

		break;

	case LUA_TSTRING:
		d = lua_str2number(lua_tostring(L, 1), &e);

		if ((!e || !*e) && d != 0)
			lua_pushnumber(L, n / d);
		else lua_pushnumber(L, 0);

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::mod(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	int64_t n, d;

	switch (pVar->type())
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
		lua_pushnil(L);
		return 1;
	}

	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
		d = (int64_t)lua_tonumber(L, 1);

		if (d != 0)
			lua_pushnumber(L, (lua_Number)(n % d));
		else lua_pushnumber(L, 0);

		break;

	case LUA_TSTRING:
		d = (int64_t)lua_str2number(lua_tostring(L, 1), &e);

		if ((!e || !*e) && d != 0)
			lua_pushnumber(L, (lua_Number)(n % d));
		else lua_pushnumber(L, 0);

		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::unm(lua_State* L, CLVariant* pVar)
{
	//尝试将参数1转换为整数
	char* e;
	double n;

	switch (pVar->type())
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
		lua_pushnil(L);
		break;
	}

	return 1;
}

int LuaVariantClass::len(lua_State* L, CLVariant* pVar)
{
	switch (pVar->type())
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

int LuaVariantClass::lt(lua_State* L, CLVariant* pVar)
{
	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
	case LUA_TSTRING:
		lua_pushboolean(L, (double)*pVar < lua_tonumber(L, 1));
		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::le(lua_State* L, CLVariant* pVar)
{
	switch (lua_type(L, 1))
	{
	case LUA_TNUMBER:
	case LUA_TSTRING:
		lua_pushboolean(L, (double)*pVar <= lua_tonumber(L, 1));
		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

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

int LuaVariantClass::concat(lua_State* L, CLVariant* pVar)
{
	int t = pVar->type();

	if (t != CLVariant::vNumber && t != CLVariant::vStr)
	{
		lua_pushnil(L);
		return 1;
	}

	//确定第二个字符串指针
	char Num2Buf[32];
	const char* s2 = NULL;
	int t2 = lua_type(L, 1);

	if (t2 != LUA_TNUMBER && t2 != LUA_TSTRING)
	{
		if (t2 == LUA_TUSERDATA)
		{
			CLVariant* pVar2 = getDataPtr(L, 1);

			if (pVar2)
			{
				switch (pVar2->type())
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
	else s2 = lua_tostring(L, 1);

	//第二个字符串指针无效则退出
	if (!s2)
	{
		lua_pushnil(L);
		return 1;
	}

	size_t len2 = strlen(s2);

	void* ud;
	lua_Alloc palloc = lua_getallocf(L, &ud);
	//确定第一个字符串并连接生成新字符串
	char* sRetPtr = NULL;
	size_t len1 = 0, newlen = 0;

	switch (pVar->type())
	{
	case CLVariant::vNumber:
		{
			char sNum1Buf[32];
			len1 = lua_number2str(sNum1Buf, (double) * pVar);
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

int LuaVariantClass::testCall(lua_State*, CLVariant* pInst)
{
	printf("script called this function\n");
	char buff[1024];
	bool mem = true;
	size_t size = pInst->saveToMemory(buff, sizeof(buff), mem);
	CLVariant var;
	size_t count = 0;
	var.loadFromMemory(buff, size, &count);
	return 0;
}

void LuaVariantClass::setVarFromTable(lua_State* L, CLVariant* pVar, int vidx)
{
	lua_pushnil(L);

	if (vidx < 0) vidx--;

	while (lua_next(L, vidx))
	{
		setVarMember(L, pVar, lua_tostring(L, -2));
		lua_pop(L, 1);//remove value
	}
}

void LuaVariantClass::setVarMember(lua_State* L, CLVariant* pVar, const char* sName, int vidx)
{
	switch (lua_type(L, vidx))
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
		setVarFromTable(L, pVar, vidx);
		break;

	case LUA_TUSERDATA:
		{
			CLVariant* pVar2 = getDataPtr(L, vidx);

			if (pVar2)
				*pVar = *pVar2;
		}
		break;
	}
}

