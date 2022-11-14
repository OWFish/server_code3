#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "os_def.h"
#include <_ast.h>
#include <bzhash.h>
#include <x_tick.h>
#include <container/vector.h>
#include <stream.h>
#include <stdarg.h>
#include <string_ex.h>
#include <ref_class.hpp>
#include <ref_string.hpp>
#include "share_util.h"
#include <new>
#include "container/str_hash_table.h"
#include "luabase/lua_pre_process.h"
#include "luabase/lua_profiler.h"

using namespace stream;
using namespace container;

const char LuaProfiler::PerStaticDebuggerName[] = "#PFD#";

LuaProfiler::LuaProfiler()
{
	lua_ = NULL;
	igoreRecordTime_ = 16;
}

LuaProfiler::~LuaProfiler()
{
	SetState(NULL);
}

void LuaProfiler::StaticCallTimeHook(lua_State* L, lua_Debug* ar)
{
	//读取性能统计对象
	lua_getglobal(L, PerStaticDebuggerName);
	LuaProfiler* profile = (LuaProfiler*)lua_touserdata(L, -1);
	lua_pop(L, 1);

	if (profile) profile->HandleDebugHook(L, ar);
	else DbgAssert(FALSE);
}

bool LuaProfiler::SetState(lua_State* L, SourceLineList* lr)
{
	if (lua_)
	{
		//移除调试器对象
		lua_pushnil(lua_);
		lua_setglobal(lua_, PerStaticDebuggerName);
		//清除调用记录表
		rootCallTable_.clear();
		//清除调用堆栈
		callStack_.clear();

		lua_sethook(lua_, NULL, 0, 0);
		lua_ = NULL;
		LRList_ = NULL;
	}

	if (L)
	{
		//已经安装了性能调试器，函数返回
		lua_getglobal(L, PerStaticDebuggerName);

		if (!lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}

		lua_pop(L, 1);
		//设置调试器对象
		lua_pushlightuserdata(L, this);
		lua_setglobal(L, PerStaticDebuggerName);
		//设置调试调用钩子
		lua_sethook(L, StaticCallTimeHook, LUA_MASKCALL | LUA_MASKRET, 0);
		lua_ = L;
		LRList_ = *lr;
	}

	return true;
}

void ExpandCallTable(Vector<LuaProfiler::LuaCallRcd*>& callList,
                     Vector<LuaProfiler::LuaCallRcd*>& callStack, LuaProfiler::LuaCallRcd& callRec, int64_t watchtime)
{
	if (!callRec.pSubCallList)
	{
		callList.addList(callStack);
		callList.add(NULL);//空对象作为一个分隔符
	}
	else
	{
		StrHashTableIterator<LuaProfiler::LuaCallRcd> it(*((LuaProfiler::SubCallTable*)callRec.pSubCallList));
		int count = callStack.count();
		LuaProfiler::LuaCallRcd* rec = it.first();

		while (rec)
		{
			//总时间小于一定时间的都不记录
			if (rec->dwTotalTime >= watchtime)
			{
				callStack.add(rec);
				ExpandCallTable(callList, callStack, *rec, 0);//为了保证记录完整的调用栈，后续的递归调用应当传递时间忽略参数为0
				callStack.trunc(count);
				rec = it.next();
			}
		}
	}
}

void WriteCallList(BaseStream& stm, Vector<LuaProfiler::LuaCallRcd*>& callList)
{
	char buf[1024];
	LuaProfiler::LuaCallRcd** recList = callList;
	//write header
	int len = SNPRINTFA(buf, sizeof(buf), "%-40s %-8s %-8s %-8s %-8s SOURCE\r\n",
	                    "FUNCTION", "MIN", "MAX", "COUNT", "AVG");
	stm.write(buf, len);

	//write call records
	for (int i = callList.count() - 1; i > -1; --i)
	{
		LuaProfiler::LuaCallRcd* rec = recList[i];

		if (rec)
		{
			len = SNPRINTFA(buf, sizeof(buf), "%-40s %-8I64d %-8I64d %-8I64d %-8I64d\r\n",
			                rec->sName, rec->dwMinTime, rec->dwMaxTime, rec->dwCallCount, rec->dwTotalTime / rec->dwCallCount);
		}
		else
		{
			len = 3;
			memcpy(buf, "\r\n\0", len);
		}

		stm.write(buf, len);
	}
}

void WriteCallNode(BaseStream& stm, LuaProfiler::LuaCallRcd* rec, int level,
                   LuaPreProcessor::LineRangeList* pLRList)
{
	char buf[512];

	/*
	aaaaa
	+--bbbbb
	|  +--ccccc
	+--ggggg
	*/
	if (level > 0)
	{
		if (level > 1)
		{
			for (int i = 1; i < level; ++i)
			{
				stm.write("|  ", 3);
			}
		}

		stm.write("+--", 3);
	}

	int len = (int)strlen(rec->sName);
	stm.write(rec->sName, len);
	len = 40 - len - ((level > 0) ? (level - 1) * 3 + 3 : 0);

	if (len > 0)
	{
		len = __min((size_t)len, sizeof(buf) - 1);
		memset(buf, ' ', len);
		buf[len] = 0;
		stm.write(buf, len);
	}

	len = SNPRINTFA(buf, sizeof(buf), " %-8I64d %-8I64d %-8I64d %-8I64d ",
	                rec->dwMinTime, rec->dwMaxTime, rec->dwCallCount, rec->dwTotalTime / rec->dwCallCount);
	stm.write(buf, len);

	//获取原始代码以及行号
	if (pLRList && rec->nLineNo >= 0)
	{
		int srcNo;
		const char* srcfile = pLRList->getSourceLineNumber(rec->nLineNo, srcNo);

		if (srcfile)
		{
			stm.write(srcfile, strlen(srcfile));
			len = SNPRINTFA(buf, sizeof(buf) - 1, ":%d", srcNo);
			stm.write(buf, len);
		}
	}

	stm.write("\r\n", 2);

	int childWriten = 0;

	//write child nodes
	if (rec->pSubCallList)
	{
		StrHashTableIterator<LuaProfiler::LuaCallRcd> it(*((LuaProfiler::SubCallTable*)rec->pSubCallList));
		rec = it.first();

		while (rec)
		{
			if (rec->dwTotalTime > 0)
			{
				WriteCallNode(stm, rec, level + 1, pLRList);
				childWriten++;
			}

			rec = it.next();
		}

		//调整流指针，以便接下来的写入中能够覆盖最后三个字符"|  "。
		stm.seek(-5, 1);
		stm.write("\r\n", 2);
	}

	if (childWriten <= 0)
	{
		if (level > 0)
		{
			for (int i = 0; i < level; ++i)
			{
				stm.write("|  ", 3);
			}
		}

		stm.write("\r\n", 2);
	}
}

void WriteCallTree(BaseStream& stm, LuaProfiler::LuaCallRcd* callrec, int64_t dwWatchTime, LuaPreProcessor::LineRangeList* pLRList)
{
	char buf[512];

	//write columns
	int nLen = SNPRINTFA(buf, sizeof(buf), "%-40s %-8s %-8s %-8s %-8s SOURCE\r\n",
	                     "FUNCTION", "MIN", "MAX", "COUNT", "AVG");
	stm.write(buf, nLen);

	//write tree
	StrHashTableIterator<LuaProfiler::LuaCallRcd> it(*((LuaProfiler::SubCallTable*)callrec->pSubCallList));
	callrec = it.first();

	while (callrec)
	{
		if (callrec->dwTotalTime >= dwWatchTime)
		{
			WriteCallNode(stm, callrec, 0, pLRList);
		}

		callrec = it.next();
	}
}

size_t LuaProfiler::Save(BaseStream& stm)
{
	LuaCallRcd callRec;
	ZeroMemory(&callRec, sizeof(callRec));
	callRec.pSubCallList = &rootCallTable_;

	int64_t pos = stm.getPosition();

	WriteCallTree(stm, &callRec, igoreRecordTime_, LRList_);

	callRec.pSubCallList = NULL;
	return (size_t)(stm.getPosition() - pos);
}

int64_t LuaProfiler::GetMaxTotalTime()
{
	StrHashTableIterator<LuaCallRcd> it(rootCallTable_);
	LuaCallRcd* pRec = it.first();
	int64_t result = 0;

	while (pRec)
	{
		if (pRec->dwTotalTime >= result)
			result = pRec->dwTotalTime;

		pRec = it.next();
	}

	return result;
}

LuaProfiler::LuaCallRcd::~LuaCallRcd()
{
	if (pSubCallList)
	{
		delete(SubCallTable*)pSubCallList;
		pSubCallList = NULL;
	}
}

void LuaProfiler::HandleDebugHook(lua_State* L, lua_Debug* ar)
{
	SubCallTable* callTable = NULL;
	LuaCallRcd* callRec = NULL;

	//获取当前的调用记录
	if (callStack_.count() > 0)
		callRec = callStack_[callStack_.count() - 1];

	if (ar->event == LUA_HOOKCALL)
	{
		char sName[512];
		//生成函数名称，格式为function:行号
		lua_getinfo(L, "Sn", ar);
		int nNameLen = SNPRINTFA(sName, sizeof(sName) - 1, "%s:%s:%s", ar->what, ar->namewhat, ar->name ? ar->name : "<NA>");

		if (nNameLen < 0 || nNameLen >= (int)sizeof(sName))
		{
			nNameLen = 0;
		}

		SNPRINTFA(sName + nNameLen, sizeof(sName) - 1 - nNameLen, ":%d", ar->linedefined);

		//取得新的调用记录
		if (callRec)
		{
			if (!callRec->pSubCallList)
				callRec->pSubCallList = new SubCallTable();

			callTable = (SubCallTable*)callRec->pSubCallList;
		}
		else
		{
			callTable = &rootCallTable_;
		}

		callRec = callTable->get(sName);

		//新函数被调用，没有调用记录则创建
		if (!callRec)
		{
			callRec = callTable->put(sName);
			callRec->dwMinTime = INT_MAX;
			//保存函数名称时只拷贝名字，不包含行号
			sName[nNameLen] = 0;
			_STRNCPY_A(callRec->sName, sName);
			callRec->nLineNo = ar->linedefined;
		}

		callRec->dwCallCount++;
		callRec->dwLastTime = _getTickCount();
		callStack_.add(callRec);
	}
	else if (ar->event == LUA_HOOKRET || ar->event == LUA_HOOKTAILRET)
	{
		if (callRec)
		{
			callRec->dwLastTime = _getTickCount() - callRec->dwLastTime;
			callRec->dwTotalTime += callRec->dwLastTime;

			if (callRec->dwLastTime > callRec->dwMaxTime)
				callRec->dwMaxTime = callRec->dwLastTime;

			if (callRec->dwLastTime < callRec->dwMinTime)
				callRec->dwMinTime = callRec->dwLastTime;

			callStack_.trunc(callStack_.count() - 1);
		}
	}
}


