#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "os_def.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "ltm.h"
}
#include "container/vector.h"
#include "ref_string.hpp"
#include "stream.h"
#include "share_util.h"
#include "second_time.h"
#include "container/str_hash_table.h"
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"
#include "luabase/lua_pre_process.h"
#include "luabase/clvariant.h"
#include "luabase/lua_clvariant.h"
#include "luabase/lua_profiler.h"
#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"
#include "luabase/vsp_def.h"
#include "luabase/base_script.h"

const char* BaseScript::ScriptInitFnName = "initialization";
const char* BaseScript::ScriptUninitFnName = "finalization";
const char* BaseScript::ScriptInstanceKeyName = "#LSKK#";

extern  int luaopen_server(lua_State* tolua_S);

BaseScript::BaseScript()
	: Inherited()
{
	vsp_ = NULL;
}

BaseScript::~BaseScript()
{
}

bool BaseScript::Call(const char* fn, ScriptValueList* args, ScriptValueList* results, int retCnt)
{
	bool ret = true;

	if (lua_ == NULL)
	{
		OutputMsg(rmError, ("调用了未初始化的脚本%s"), fn);
		return false;
	}

	/** 检查上次脚本调用所由脚本申请的数据包是否被回收 **/
	//DbgAssert(ScriptActorPacket == NULL);

	int argCnt = args ? (int)(args->count()) : 0;
	int top = lua_gettop(lua_);//获取当前的栈顶

	//压入错误处理函数
	lua_pushcfunction(lua_, ScriptCallErrorDispatcher);

	//压入函数以及参数
	SetLastFunc(fn);
	lua_getglobal(lua_, fn);

	if (argCnt > 0)
	{
		args->pushArgs(lua_, argCnt);
	}

	int err = lua_pcall(lua_, argCnt, retCnt, -argCnt - 2);

	//如果参数表和返回值表是同一个对象，则清空参数表。
	if (args && retCnt != 0 && args == results)
		args->clear();

	//如果脚本执行错误则进行错误处理
	if (err)
	{
		ScriptCallError(fn);
		ret = false;
	}
	//脚本执行成功则取出返回值
	else
	{
		//如果期望的返回值是不限个，则计算本次函数调用的返回值数量
		// 调用lua_pcall后，会在栈中清除参数，但是函数还在栈内，所以这里要再减1
		if (retCnt == LUA_MULTRET)
			retCnt = lua_gettop(lua_) - top - 1;		

		if (retCnt > 0 && results)
		{
			results->getResults(lua_, (int)retCnt);
		}
	}

	SetLastFunc(NULL);

	//恢复堆栈
	lua_settop(lua_, top);

	onCallEnd(ret);

	return ret;
}

bool BaseScript::setScript(const char* txt, SourceLineList* lr)
{
	src_ = *lr;
	return Inherited::setScript(txt);
}

bool BaseScript::LoadScript(const char* fn)
{
	if (!vsp_)
	{
		OutputMsg(rmError, "vsp is null");
		return false;
	}

	bool ret = true;
	stream::MemoryStream ms(NULL);
	if (ms.loadFromFile(fn) <= 0)
	{
		OutputMsg(rmError, ("unable to load Script file %s"), fn);
		return false;
	}

	//对脚本进行预处理
	LuaPreProcessor pp(NULL);
	vsp_->RegisteToPreprocessor(pp);

	const char* sScript = pp.parse((const char*)ms.getMemory(), fn);

	if (!sScript)
	{
		OutputMsg(rmError, ("script file pre-process fail"));
		return false;
	}

	misc::RefObject<LuaPreProcessor::LineRangeList> LRList;
	int nLRCount = pp.getLineRangeData(NULL, 0);

	if (nLRCount > 0)
	{
		LRList = new misc::RefObjectImpl<LuaPreProcessor::LineRangeList>();
		LRList.raw_ptr()->reserve(nLRCount);
		pp.getLineRangeData(*LRList.raw_ptr(), nLRCount);
		LRList.raw_ptr()->trunc(nLRCount);
	}

	//设置脚本
	ret = setScript(sScript, &LRList);
	return ret;
}


int BaseScript::ScriptCallErrorDispatcher(lua_State* L)
{
	lua_getglobal(L, ScriptInstanceKeyName);
	BaseScript* s = (BaseScript*)lua_touserdata(L, -1);
	lua_pop(L, 1);
	return s ? s->HandleCallError() : 0;
}

void BaseScript::ScriptCallError(const char* fn)
{
	const char* errDesc = NULL;

	int top = lua_gettop(lua_);

	if (top > 0)
		errDesc = lua_tostring(lua_, -1);

	if (!errDesc) errDesc = "Undefined Error";

	if (top > 0)
		lua_pop(lua_, 1);

	showError(errDesc);
}

int BaseScript::HandleCallError()
{
	char errBuf[1024];

	lua_Debug ar;
	int level = 0;
	const char* fn, *tag;
	LuaPreProcessor::LineRangeList* LR = src_;
#ifdef _MSC_VER
	WIN32_FIND_DATA fd;
#endif
	//定位到错误内容中只包含错误描述的部分，调过简单内容以及行号
	fn = lua_tostring(lua_, 1);
	tag = strrchr(fn, ':');

	if (tag) fn = tag + 2;

	int len = SNPRINTFA(errBuf, sizeof(errBuf), "%s\r\nthe stack trace is:\r\n", fn);

	while (lua_getstack(lua_, (int)level, &ar))
	{
		lua_getinfo(lua_, "Snl", &ar);
		//lua:field:name(file:line)
		len += SNPRINTFA(errBuf + len, ArrayCount(errBuf) - 1 - len, "  %s:%s:%s",
		                  ar.what, ar.namewhat, ar.name ? ar.name : "<NA>");
		//获取源代码位置
		fn = NULL;
		int line = 0;
		bool luaFile = false;
		const char* luaSrc = ar.source;
		// 如果是后缀名为lua的的文件，则不需要源代码行数转换了
		if (luaSrc)
		{
			static const char* fileExt = ".lua";
			static const size_t extLen = strlen(fileExt);
			size_t srcFileLen = strlen(luaSrc);
			if (srcFileLen > extLen && 
				strncmp(fileExt, luaSrc + srcFileLen - extLen, extLen) == 0)
			{
				luaFile = true;
				fn = luaSrc;
				line = ar.currentline;
			}
		}

		if (!luaFile && LR)
		{
			fn = LR->getSourceLineNumber(ar.currentline > -1 ? ar.currentline : ar.linedefined, line);
#ifdef _MSC_VER

			if (fn)
			{
				//由于文件名可能被缩短成短文件，因此做一次搜索以便确定更为完整的文件名。
				void* hd = FindFirstFile(fn, &fd);

				if (hd != INVALID_HANDLE_VALUE)
				{
					fn = fd.cFileName;
					FindClose(hd);
				}
				else
				{
					fn = strrchr(fn, '\\');

					if (fn) fn ++;
				}
			}
#endif
		}

		//格式化源代码位置
		if (fn)
			len += SNPRINTFA(errBuf + len, ArrayCount(errBuf) - 1 - len, "(%s:%d)\r\n", fn, line);
		else 
			len += SNPRINTFA(errBuf + len, ArrayCount(errBuf) - 1 - len, "\r\n");

		if (len >= (int)ArrayCount(errBuf) - 1)
			break;

		level++;
	}

	//没有格式化出调用栈则输出跟调用函数
	len += SNPRINTFA(errBuf + len, ArrayCount(errBuf) - 1 - len, "root call is : %s", last_fn_);
	lua_pushlstring(lua_, errBuf, len);
	return 1;
}

lua_State* BaseScript::createLuaVM()
{
	return luaL_newstate();
}

bool BaseScript::openBaseLibs()
{
	return Inherited::openBaseLibs();
}

bool BaseScript::registLocalLibs()
{
	//导出LuaHelp函数库
	//这里是tolua++导出的函数,所有的tolua++导出的只有一个入口
	luaopen_server(lua_);
	//导出CLVariant类
	LuaCLVariant::regist(lua_);
	return true;
}

bool BaseScript::callInit()
{
	gc();//先释放一遍内存
	//导出脚本自己的实例
	lua_pushlightuserdata(lua_, this);
	lua_setglobal(lua_, ScriptInstanceKeyName);

	bool result = onCallInit();

	return result;
}

bool BaseScript::onCallInit()
{
	bool result = true;

	if (FunctionExists(ScriptInitFnName))
	{
	}

	return result;
}

bool BaseScript::callFinal()
{
	bool result = onCallFinal();

	//移除向脚本导出脚本的自己的实例
	lua_pushnil(lua_);
	lua_setglobal(lua_, ScriptInstanceKeyName);

	return result;
}

bool BaseScript::onCallFinal()
{
	bool result = true;
	if (FunctionExists(ScriptUninitFnName))
	{
		result = Call(ScriptUninitFnName, NULL, NULL, 1);
	}
	return result;
}

void BaseScript::SetVspDef(CVSPDefinition* vsp)
{
	vsp_ = vsp;
}

void BaseScript::showError(const char* err)
{
	SetErrDesc(err);
	OutputMsg(rmError, err);
}

void BaseScript::onCallEnd(bool)
{

}
