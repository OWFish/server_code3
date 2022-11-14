#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "../script/interface/system_export_fun.h"

extern "C"
{
#include <lualib.h>
}

extern  int luaopen_server(lua_State* tolua_S);
extern int luaopen_bson(lua_State *L);

ActorPacket* GameScript::ScriptActorPacket = NULL;

GameScript::GameScript()
	: Inherited()
{
	npc_ptr_ = NULL;
}

GameScript::~GameScript()
{

}

#ifdef _DEBUG
void GameScript::SaveProfiler(const char* sFilePath)
{
	stream::MemoryStream ms(NULL);
	m_Profiler.Save(ms);
	ms.saveToFile(sFilePath);
}
#endif

lua_State* GameScript::createLuaVM()
{
	return lua_newstate(luamemory::luaAlloc, this);
	//return luaL_newstate();
}

bool GameScript::registLocalLibs()
{
	if (!lcCheck(lua_cpcall(lua_, luaopen_os, NULL)))
		return false;

	GameServer* gameWorld = ServerInstance();

	//导出LuaHelp函数库
	//luaL_register(lua_, "LuaHelp", LuaHelpExpot);
	//这里是tolua++导出的函数,所有的tolua++导出的只有一个入口
	luaopen_server(lua_);
	//导出CLVariant类
	LuaCLVariant::regist(lua_);
	luaopen_bson(lua_);

	if (gameWorld)
	{
		//导出LangTextSection类
		LuaLangSection::regist(lua_);
		//导出语言包实例
		LuaLangSection::setGlobalValue(lua_, gameWorld->GetLang(), "Lang");
	}

	return true;
}

bool GameScript::onCallInit()
{
	//安装函数调用性能统计
#ifdef _DEBUG
	m_Profiler.SetState(lua_, &src_);
#endif

	bool result = true;

	if (FunctionExists(ScriptInitFnName))
	{
		ScriptValueList args;
		args << npc_ptr_;
		result = Call(ScriptInitFnName, &args, &args, 1);
	}

	return result;
}

bool GameScript::onCallFinal()
{
	bool result = true;

	if (FunctionExists(ScriptUninitFnName))
	{
		ScriptValueList args;
		args << npc_ptr_;
		result = Call(ScriptUninitFnName, &args, &args, 1);
	}

	//卸载函数调用性能统计
#ifdef _DEBUG
	static bool pathExists = FDOP::DeepCreateDirectory("./runtime/SPS");

	if (pathExists && m_Profiler.GetMaxTotalTime() > 16)//最大栈消耗16毫秒以上的才记录
	{
		char path[256];
		wchar_t buf[256];
		const char* npc = "(null)";
		const char* s = "(null)";

		if (npc_ptr_)
		{
			npc = npc_ptr_->GetEntityName();
			//Scene* scene = npc_ptr_->GetScene();
			//s = scene ? scene->GetSceneName() : "";
			s = "SYS";
		}

		int nLen = SNPRINTFA(path, ArrayCount(path), ("./runtime/SPS/%s-%s.txt"), s, npc);
		nLen = MultiByteToWideChar(CP_UTF8, 0, path, nLen, buf, ArrayCount(buf) - 1);
		buf[nLen] = 0;
#ifdef UNICODE
		SaveProfiler(buf);
#else
		nLen = WideCharToMultiByte(CP_ACP, 0, buf, nLen, path, ArrayCount(path) - 1, "?", NULL);
		path[nLen] = 0;
		SaveProfiler(path);
#endif
	}

	m_Profiler.SetState(NULL);
#endif

	return result;
}

void GameScript::showError(const char* err)
{
	const char* npc_name = "(null)";
	const char* scene_name = "(null)";

	if (npc_ptr_)
	{
		npc_name = npc_ptr_->GetEntityName();//获取角色名称
		//Scene* s = npc_ptr_->GetScene();
		//scene_name = s ? s->GetSceneName() : "(null)";//获取所在场景名称
		scene_name = "SYS";
	}

	OutputMsg(rmError, "[Script]NPC(%s:%s) Error %s", scene_name, npc_name, err);

	logError(err);
	
	SetErrDesc(err);
}

void GameScript::onCallEnd(bool ret)
{
	/*
	   如果脚本出错且数据包没有被回收，则会导致整个游戏引擎就此不能正常工作。因此必须检测并回收脚本申请的数据包
	*/
	if (ScriptActorPacket)
	{
		ScriptActorPacket->rollBack();
		ScriptActorPacket->packet_ = NULL;
		ScriptActorPacket = NULL;
		OutputMsg(rmWarning, ("collected an ActorPacket that because script error occured and the packet can not be flushed"));
	}
}

void GameScript::logError(const char* sError)
{
	if(!sError) return;

	char file_name[256];
	tm *t = nullptr;
	{
		auto sec = time(nullptr);
		t = localtime(&sec);
	}
	sprintf(file_name, "../log/error_%d_%02d_%02d_%02d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour);
	FILE* fd = fopen(file_name, "a");
	if (!fd)
	{
		OutputMsg(rmWarning, "open error.log error!");
		return;
	}

	std::string str = "script error: \n";
	str += sError;
	str += "\n";
	fwrite(str.c_str(), str.size(), 1, fd);
	fclose(fd);

}
