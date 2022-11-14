extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "lundump.h"
#include "lstate.h"
}
#include <x_tick.h>
#include <stdarg.h>
#include <_ast.h>
#include <ref_string.hpp>
#include "share_util.h"
#include "luabase/base_lua.h"
#include "data_packet.hpp"

#include "luabase/lua_myload.h"

BaseLua::BaseLua()
{
	lua_ = NULL;
	errno_ = 0;
	last_fn_[0] = 0;
	err_desc_ = NULL;
}

BaseLua::~BaseLua()
{
	setScript(NULL);
	if (lua_)
	{
		lua_close(lua_);
		lua_ = NULL;
	}
	SafeFree(err_desc_);
}

bool BaseLua::FunctionExists(const char* fn)
{
	if (!lua_ || !fn || !fn[0])
		return false;

	lua_getglobal(lua_, fn);
	bool result = lua_isfunction(lua_, -1);
	lua_pop(lua_, 1);
	return result;
}
bool BaseLua::setScript(const char* txt)
{
	if (lua_)
	{
		//调用析构函数
		callFinal();
		//销毁虚拟机
		//lua_close(lua_);
		//lua_ = NULL;
	}

	if (txt)
	{
		//跳过UTF-8 BOM
		if ((*(int*)txt & 0x00FFFFFF) == 0xBFBBEF)
			txt += 3;
	}
	else if (lua_ != NULL)
	{
		//销毁虚拟机
		lua_close(lua_);
		lua_ = NULL;
	}

	if (txt && txt[0])
	{
		if (lua_ == NULL)
		{
			//创建虚拟机
			lua_ = createLuaVM();
			//打开基本函数库
			openBaseLibs();
			lua_initVersion(lua_);
			lua_registerMyRequire(lua_);
			//注册本地函数库
			registLocalLibs();
			//保存错误函数名称
			SetLastFunc("<LOADER>");
		}

		lua_incVersion(lua_);

		//加载脚本
		if (!lcCheck(luaL_loadstring(lua_, txt)))
			return false;

		//初始化脚本
		if (!pcall(0, 0, 0))
			return false;

		//调用初始化函数
		return callInit();
	}

	return true;
}

int BaseLua::StreamWriter(lua_State* L, const void* p, size_t size, void* u)
{
	UNUSED(L);
	DataPacket* packet = (DataPacket*)u;

	if (!packet)
		return 1;

	packet->writeBuf(p, size);
	return 0;
}

bool BaseLua::CompileLua(lua_State* L, const char* content, DataPacket& packet)
{
	if (!L || !content)
		return false;

	if (!lcCheck(luaL_loadstring(L, content)))
		return false;

	packet.setLength(0);
	const Proto* proto = clvalue(L->top - 1)->l.p;
	luaU_dump(L, proto, BaseLua::StreamWriter, &packet, 0);
	return true;
}

bool BaseLua::resetBinScript(DataPacket& packet)
{
	if (!lua_)
		return false;

	callFinal();

	if (!lcCheck(luaL_loadbuffer(lua_, packet.getMemoryPtr(), packet.getPosition(), "")))
		return false;

	lua_incVersion(lua_);

	if (!pcall(0, 0, 0))
		return false;

	return callInit();
}

bool BaseLua::setBinScript(const char* script, DataPacket& packet, const char* name, bool compile)
{
	if (lua_)
	{
		//调用析构函数
		callFinal();
		//销毁虚拟机
		//lua_close(lua_);
		//lua_ = NULL;
	}

	if ((compile && script) || (!compile && packet.getPosition() > 0))
	{
		if (lua_ == NULL)
		{
			//创建虚拟机
			lua_ = createLuaVM();
			//打开基本函数库
			openBaseLibs();
			lua_initVersion(lua_);
			lua_registerMyRequire(lua_);
			//注册本地函数库
			registLocalLibs();
			//保存错误函数名称
			SetLastFunc("<LOADER>");
		}

		lua_incVersion(lua_);
		
		//加载脚本
		if (compile)
		{
			if (!CompileLua(lua_, script, packet))
				return false;
		}

		if (!lcCheck(luaL_loadbuffer(lua_, packet.getMemoryPtr(), packet.getPosition(), name)))
			return false;

		//初始化脚本
		if (!pcall(0, 0, 0))
			return false;

		//调用初始化函数
		return callInit();
	}

	return true;
}

int BaseLua::getAvaliableMemorySize()
{
	if (!lua_) return 0;

	int n = lua_gc(lua_ , LUA_GCCOUNT, 0) * 1024;
	n |= lua_gc(lua_, LUA_GCCOUNTB, 0);
	return n;
}

int BaseLua::gc()
{
	if (!lua_) return 0;

	int n = getAvaliableMemorySize();
	lua_gc(lua_ , LUA_GCCOLLECT, 0);
	return n - getAvaliableMemorySize();
}

lua_State* BaseLua::createLuaVM()
{
	return luaL_newstate();
}

bool BaseLua::openBaseLibs()
{
	if (!lcCheck(lua_cpcall(lua_, luaopen_base, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_string, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_math, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_table, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_io, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_debug, NULL)))
		return false;

	if (!lcCheck(lua_cpcall(lua_, luaopen_package, NULL)))
		return false;

	return true;
}

bool BaseLua::registLocalLibs()
{
	return true;
}

bool BaseLua::callInit()
{
	return true;
}

bool BaseLua::callFinal()
{
	return true;
}

void BaseLua::showError(const char* err)
{
	SetErrDesc(err);
	printf("%s", err);
}

void BaseLua::showErrorFormat(const char* fmt, ...)
{
	char buf[1024];
	va_list	args;

	va_start(args, fmt);
	VSNPRINTFA(buf, ArrayCount(buf) - 1, fmt, args);
	va_end(args);

	showError(buf);
}

bool BaseLua::lcCheck(int err)
{
	if (!err) return true;

	errno_ = err;

	const char* errdesc = NULL;

	if (lua_gettop(lua_) > 0)
	{
		errdesc = lua_tostring(lua_, -1);
		lua_pop(lua_, 1);
	}
	else
	{
		errdesc = ("falt system error: lua_gettop <= 0");
	}

	if (!errdesc || !errdesc[0])
		errdesc = ("undefined error");

	showErrorFormat("function:%s,error:%s", last_fn_, errdesc);
	return false;
}

bool BaseLua::pcall(const int args, const int results, const int errfunc)
{
	bool result = true;

	int nTop = lua_gettop(lua_) - args - 1;  //-1是排除函数名称所占的栈空间
	result = lcCheck(lua_pcall(lua_, args, results, errfunc));
	int nTop2 = lua_gettop(lua_) - results;

	if (results != LUA_MULTRET && nTop != nTop2)
	{
		showErrorFormat("function:%s,the stack before call was:%d,the stack after call is:%d,stack difference value is:%d", last_fn_, nTop, nTop2, nTop2 - nTop);
	}

	return result;
}

void BaseLua::SetErrDesc(const char* err)
{
	SafeFree(err_desc_);
	size_t len = strlen(err);
	err_desc_ = (char*)malloc(len + 1);
	_STRNCPY_S(err_desc_, err, len + 1);
}

