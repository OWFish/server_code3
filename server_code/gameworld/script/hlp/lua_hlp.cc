#include "StdAfx.h"
#ifndef _MSC_VER
#include "../../StdAfx.h"
#endif

using namespace stream;

void LuaHelp::PushDataPointerToTable(lua_State* L, const void* lpData, size_t sizeElement, size_t elementCount)
{
	if (elementCount > 0)
	{
		BYTE* pBytes = (BYTE*)lpData;

		lua_createtable(L, (int)elementCount, 0);

		for (size_t i = 1; i <= elementCount; ++i)
		{
			lua_pushlightuserdata(L, (void*)pBytes);
			lua_rawseti(L, -2, (int)i);
			pBytes += sizeElement;
		}
	}
	else lua_pushnil(L);
}

void LuaHelp::PushDataPointerToTable(lua_State* L, void** lpData, size_t elementCount)
{
	if (elementCount > 0)
	{

		lua_createtable(L, (int)elementCount, 0);

		for (size_t i = 1; i <= elementCount; ++i)
		{
			lua_pushlightuserdata(L, (void*)(*lpData));
			lua_rawseti(L, -2, (int)i);
			lpData++;
		}
	}
	else lua_pushnil(L);
}



void LuaHelp::PushStringsToTable(lua_State* L, const char* *ppStrList, size_t strCount)
{
	if (strCount > 0)
	{
		lua_createtable(L, (int)strCount, 0);

		for (size_t i = 1; i <= strCount; ++i)
		{
			lua_pushstring(L, *ppStrList);
			lua_rawseti(L, -2, (int)i);
			ppStrList++;
		}
	}
	else lua_pushnil(L);
}

void LuaHelp::PushIntsToTable(lua_State* L, int* pIntList, size_t elementCount)
{
	if (elementCount > 0)
	{
		lua_createtable(L, (int)elementCount, 0);

		for (size_t i = 1; i <= elementCount; ++i)
		{
			lua_pushinteger(L, *pIntList);
			lua_rawseti(L, -2, (int)i);
			pIntList++;
		}
	}
	else lua_pushnil(L);
}

void WriteIdentChars(BaseStream& stm, int nIdent)
{
	static const char* sIdentStrs[] = { NULL,
	                                    "  ",
	                                    "    ",
	                                    "      ",
	                                    "        ",
	                                    "          ",
	                                    "            ",
	                                    "              ",
	                                    "                ",
	                                    "                  ",
	                                    "                    ",
	                                    "                      ",
	                                    "                        ",
	                                    "                          ",
	                                    "                            ",
	                                    "                              ",
	                                    "                                ",
	                                  };
	int nCount;

	while (nIdent > 0)
	{
		nCount = nIdent & 15;
		stm.write(sIdentStrs[nCount], nCount * 2);
		nIdent -= nCount;
	}
}

size_t WriteTableA(lua_State* L, int stackId, BaseStream& stm, int nIdent)
{
	int64_t dwPos = stm.getPosition();
	const char* sKey;
	const char* sValue;
	int nValueType, nFieldIndex = 1, nTableLen;

	WriteIdentChars(stm, nIdent);
	stm.write("{\r\n", 3);

	nTableLen = (int)lua_objlen(L, (int)stackId);

	if (stackId < 0) stackId--;

	lua_pushnil(L); /* first key */

	if (lua_next(L, (int)stackId))
	{
		nIdent++;

		do
		{
			nValueType = lua_type(L, -1);

			if (lua_type(L, -2) == LUA_TSTRING)
			{
				WriteIdentChars(stm, nIdent);
				sKey = lua_tostring(L, -2);
				stm.write(sKey, strlen(sKey));
				stm.write(" = ", 3);
			}
			else
			{
				sKey = NULL;

				//为纯数组中的bool、number以及string写缩进字符串
				if (nFieldIndex == 1)
				{
					switch (nValueType)
					{
					case LUA_TBOOLEAN:
					case LUA_TNUMBER:
					case LUA_TSTRING:
						if (!sKey)
							WriteIdentChars(stm, nIdent);

						break;
					}
				}
			}

			switch (nValueType)
			{
			case LUA_TBOOLEAN:
				if (lua_toboolean(L, -1))
					stm.write("true", 4);
				else stm.write("false", 5);

				break;

			case LUA_TNUMBER:
				sValue = lua_tostring(L, -1);
				stm.write(sValue, strlen(sValue));
				break;

			case LUA_TSTRING:
				sValue = lua_tostring(L, -1);
				stm.write("\"", 1);
				stm.write(sValue, strlen(sValue));
				stm.write("\"", 1);
				break;

			case LUA_TTABLE:
				if (sKey)
					stm.write("\r\n", 2);

				WriteTableA(L, -1, stm, nIdent);
				break;

			default:
				stm.write("nil", 3);
				break;
			}

			lua_pop(L, 1);
			nFieldIndex++;

			if (sKey || nValueType == LUA_TTABLE || nFieldIndex > nTableLen)
				stm.write(",\r\n", 3);
			else stm.write(", ", 2);
		}
		while (lua_next(L, (int)stackId));

		nIdent--;
	}

	WriteIdentChars(stm, nIdent);
	stm.write("}", 1);
	return (size_t)(stm.getPosition() - dwPos);
}

size_t LuaHelp::FormatTableA(lua_State* L, int stackId, BaseStream& stm)
{
	if (!lua_istable(L, (int)stackId))
		return 0;

	return WriteTableA(L, stackId, stm, 0);
}

