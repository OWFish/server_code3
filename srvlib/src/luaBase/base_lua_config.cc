extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "os_def.h"
#include <_ast.h>
#include <x_tick.h>
#include <container/vector.h>
#include <stdarg.h>
#include <string_ex.h>
#include <ref_class.hpp>
#include <ref_string.hpp>
#include "share_util.h"
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"

using namespace string;

BaseLuaConfig::BaseLuaConfig()
	: Inherited()
{
}

BaseLuaConfig::~BaseLuaConfig()
{
	for (int i = m_TableStacks.count() - 1; i > -1; --i)
	{
		m_TableStacks[i]->release();
	}

	m_TableStacks.clear();
}

void BaseLuaConfig::showError(const char* err)
{
	SetErrDesc(err);
	printf("%s[Configuration Error]", err);
}

void BaseLuaConfig::showTableNotExists(const char* sTableName)
{
	const char* sTableNamePtr;
	String s;
	getTablePath(s);

	sTableNamePtr = sTableName;

	const char* sFmt = (sTableName && !s.isEmpty())
	                   ? ("table \"%s.%s\" not exists")
	                   : ("table \"%s%s\" not exists");
	showErrorFormat(sFmt, (const char*)s, sTableNamePtr);
}

void BaseLuaConfig::showFieldDoesNotContainValue(const char* sFieldName, const char* sValueType)
{
	const char* sFieldNamePtr;
	String s;
	getTablePath(s);

	sFieldNamePtr = sFieldName;

	const char* sFmt = (sFieldName && !s.isEmpty())
	                   ? ("field \"%s.%s\" does not contain valid %s value")
	                   : ("field \"%s%s\" does not contain valid %s value");
	showErrorFormat(sFmt, (const char*)s, sFieldNamePtr, sValueType);
}

BaseLuaConfig::TableName* BaseLuaConfig::createTableName(const char* sName)
{
	TableName* tn = new TableName();
#ifdef UNICODE
	AnsiString as = sName;
	as.toWStr(tn);
#else
	*((String*)tn) = sName;
#endif
	tn->addRef();
	return tn;
}

bool BaseLuaConfig::openGlobalTable(const char* sTableName)
{
	lua_getglobal(lua_, sTableName);
	bool result = lua_istable(lua_, -1);

	if (!result)
	{
		lua_pop(lua_, 1);
		showTableNotExists(sTableName);
	}
	else
	{
		m_TableStacks.add(createTableName(sTableName));
	}

	return result;
}

bool BaseLuaConfig::openFieldTable(const char* sTableName)
{
	lua_getfield(lua_, -1, sTableName);
	bool result = lua_istable(lua_, -1);

	if (!result)
	{
		lua_pop(lua_, 1);
		showTableNotExists(sTableName);
	}
	else
	{
		m_TableStacks.add(createTableName(sTableName));
	}

	return result;
}

bool BaseLuaConfig::enumTableFirst()
{
	lua_pushnil(lua_);  /* first key */
	bool result = lua_next(lua_, -2) != 0;

	if (result)
	{
		m_TableStacks.add(createTableName("[1]"));
	}

	return result;
}

bool BaseLuaConfig::enumTableNext()
{
	lua_pop(lua_, 1);	/* remove value, reserve key for next iterate */
	bool result = lua_next(lua_, -2) != 0;
	int nListIndex = m_TableStacks.count() - 1;

	//如果表存在则改变表名称列表中的表名称，表不存在则完成遍历并从表名称列表中删除当前的枚举表名称
	if (result)
	{
		int nTableIndex;
		TableName* tn = m_TableStacks[nListIndex];
		sscanf((const char*) * ((String*)tn), ("[%d]"), &nTableIndex);
		nTableIndex++;
		tn->format(("[%d]"), nTableIndex);
	}
	else
	{
		m_TableStacks[nListIndex]->release();
		m_TableStacks.remove(nListIndex);
	}

	return result;
}

void BaseLuaConfig::endTableEnum()
{
	int nListIndex = m_TableStacks.count() - 1;

	if (nListIndex > -1)
	{
		TableName* tn = m_TableStacks[nListIndex];

		if (!tn->isEmpty() && tn->rawStr()[0] == '[')
		{
			m_TableStacks[nListIndex]->release();
			m_TableStacks.remove(nListIndex);
			lua_pop(lua_, 2);  /* remove value and key */
		}
		else
		{
			showErrorFormat(("table is not under enumeration"));
		}
	}
	else
	{
		showErrorFormat(("table stack was empty"));
	}
}

bool BaseLuaConfig::getFieldIndexTable(const int IndexStartFromOne)
{
	lua_pushinteger(lua_, IndexStartFromOne);
	lua_rawget(lua_, -2);
	bool result = lua_istable(lua_, -1);

	if (!result)
	{
		lua_pop(lua_, 1);

		String s;
		getTablePath(s);
		const char* sFmt = !s.isEmpty()
		                   ? ("table \"%s.[%d]\" does not exists")
		                   : ("table \"%s[%d]\" does not exists");
		showErrorFormat(sFmt, (const char*)s, IndexStartFromOne);
	}
	else
	{
		char s[64];
		sprintf(s, "[%d]", IndexStartFromOne);
		m_TableStacks.add(createTableName(s));
	}

	return result;
}

bool BaseLuaConfig::feildTableExists(const char* sTableName)
{
	lua_getfield(lua_, -1, sTableName);
	bool result = lua_istable(lua_, -1);
	lua_pop(lua_, 1);
	return result;
}

void BaseLuaConfig::closeTable()
{
	if (lua_gettop(lua_) > 0)
	{
		lua_pop(lua_, 1);
		int nIndex = m_TableStacks.count() - 1;
		m_TableStacks[nIndex]->release();
		m_TableStacks.remove(nIndex);
	}
	else
	{
		showErrorFormat(("table stack was empty"));
	}
}

String& BaseLuaConfig::getTablePath(String& Retval)
{
	int i, nCount;
	Retval = ("");

	nCount = m_TableStacks.count();

	if (nCount > 0)
	{
		for (i = 0; i < nCount - 1; ++i)
		{
			Retval += m_TableStacks[i]->rawStr();
			Retval += (".");
		}

		Retval += m_TableStacks[nCount - 1]->rawStr();
	}

	return Retval;
}

AnsiString& BaseLuaConfig::getKeyName(AnsiString& Retval)
{
	/*
		★attention★
			不得使用lua_tostring来直接获取键名称！
		因为在遍历数组表的时候，键的类型为number，这个时候
		使用lua_tostring会将键的数据类型修改为string，从而
		导致后续的遍历将无法进行！！！
	*/
	switch (lua_type(lua_, -2))
	{
	case LUA_TNUMBER:
		{
			lua_Integer n = lua_tointeger(lua_, -2) - 1;//LUA中数组索引是从1开始，基于CBP规范，数组索引应当从0开始。
			Retval.format("%d", (int)n);
		}
		break;

	case LUA_TSTRING:
		{
			const char* s = lua_tostring(lua_, -2);
			Retval = s;
		}
		break;

	default:
		Retval = NULL;
		break;
	}

	return Retval;
}

bool BaseLuaConfig::getFieldBoolean(const char* sFieldName, const bool* pDefValue, BOOL* pIsValid)
{
	if (sFieldName)
	{
		lua_getfield(lua_, -1, sFieldName);
	}

	bool result;
	BOOL isValid = lua_isboolean(lua_, -1);

	if (pIsValid) *pIsValid = isValid;

	if (isValid)
	{
		result = lua_toboolean(lua_, -1) != 0;
	}
	else if (pDefValue)
	{
		result = *pDefValue;
	}
	else
	{
		result = false;
		showFieldDoesNotContainValue(sFieldName, ("boolean"));
	}

	if (sFieldName)
	{
		lua_pop(lua_, 1);
	}

	return result;
}

double BaseLuaConfig::getFieldNumber(const char* sFieldName, const double* pDefValue, BOOL* pIsValid)
{
	if (sFieldName)
	{
		lua_getfield(lua_, -1, sFieldName);
	}

	double result;
	BOOL isValid = lua_isnumber(lua_, -1);

	if (pIsValid) *pIsValid = isValid;

	if (isValid)
	{
		result = lua_tonumber(lua_, -1);
	}
	else if (pDefValue)
	{
		result = *pDefValue;
	}
	else
	{
		result = 0;
		showFieldDoesNotContainValue(sFieldName, ("numeric"));
	}

	if (sFieldName)
	{
		lua_pop(lua_, 1);
	}

	return result;
}

int64_t BaseLuaConfig::getFieldInt64(const char* sFieldName, const int64_t* pDefValue, BOOL* pIsValid)
{
	if (pDefValue)
	{
		double defValue = (double) * pDefValue;
		return (int64_t)getFieldNumber(sFieldName, &defValue, pIsValid);
	}

	return (int64_t)getFieldNumber(sFieldName, NULL, pIsValid);
}

int BaseLuaConfig::getFieldInt(const char* sFieldName, const int* pDefValue, BOOL* pIsValid)
{
	if (pDefValue)
	{
		double defValue = *pDefValue;
		return (int)getFieldNumber(sFieldName, &defValue, pIsValid);
	}

	return (int)getFieldNumber(sFieldName, NULL, pIsValid);
}

const char* BaseLuaConfig::getFieldString(const char* sFieldName, const char* pDefValue, BOOL* pIsValid)
{
	if (sFieldName)
	{
		lua_getfield(lua_, -1, sFieldName);
	}

	const char* result;
	BOOL isValid = lua_isstring(lua_, -1);

	if (pIsValid) *pIsValid = isValid;

	if (isValid)
	{
		result = lua_tostring(lua_, -1);
	}
	else if (pDefValue)
	{
		result = pDefValue;
	}
	else
	{
		result = NULL;
		showFieldDoesNotContainValue(sFieldName, ("string"));
	}

	if (sFieldName)
	{
		lua_pop(lua_, 1);
	}

	return result;
}

int BaseLuaConfig::getFieldStringBuffer(const char* sFieldName, char* buf, size_t buflen)
{
	if (buflen <= 0)
		return -1;

	BOOL boIsValid;
	const char* s = getFieldString(sFieldName, NULL, &boIsValid);

	if (!boIsValid)
		return false;

	size_t len = strlen(s);
	len = __min(len, buflen - 1);

	memcpy(buf, s, len * sizeof(buf[0]));
	buf[len] = 0;
	return (int)len;
}

bool BaseLuaConfig::ExcuteCjson(const char* funcname, const char* p1, const char* p2, const char* p3)
{
	bool ret = true;
	int top = lua_gettop(lua_);//获取当前的栈顶

	lua_getglobal(lua_, funcname);
	if (p1) lua_pushlstring(lua_, p1, strlen(p1));
	if (p2) lua_pushlstring(lua_, p2, strlen(p2));
	if (p3) lua_pushlstring(lua_, p3, strlen(p3));

	int err = lua_pcall(lua_, 3, 0, 0);

	if (err)
	{
		const char* errDesc = NULL;
		int top = lua_gettop(lua_);

		if (top > 0)
		{
			errDesc = lua_tostring(lua_, -1);
		}

		if (!errDesc)
		{
			errDesc = "Undefined Error";
		}
		showError(errDesc);
		ret = false;
	}

	return ret;
}

