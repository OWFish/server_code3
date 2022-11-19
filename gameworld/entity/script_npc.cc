#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace stream;


ScriptNpc::ScriptNpc()
	: Inherited(), script_gc_timer_(60000), script_len_(0)
{
	script_.SetEntity(this);
}

void ScriptNpc::OnDestroy() {
	script_.setScript(NULL, NULL);
	Inherited::OnDestroy();
}

void ScriptNpc::LogicRun(int64_t curr_t)
{
	if (IsInited() == false) return;

	Inherited::LogicRun(curr_t);	// (NPC不执行怪物的这些逻辑检测)

	static GameEngine* ge = GetGameEngine();
	int64_t now_tick = ge->getTickCount();

	//检查脚本内存回收时间
	if (script_gc_timer_.Check(curr_t))
	{
		//设置下次进行脚本内存回收的时间为180秒到270秒之内。
		//在一个随机的时间范围内进行垃圾回收可以避免所有NPC在同一个主循环中进行脚本垃圾回收而导致的性能集中损失，
		//对脚本进行垃圾回收是十分低效的。
		script_gc_timer_.SetNextHitTimeFromNow(now_tick, 180000 + (curr_t % 90) * 1000);
		script_.gc();
	}
}

void ScriptNpc::ResetScript()
{
	/*
#ifdef USE_LUA_BIN_CODE
	// 采取先编译的方式
	script_.resetBinScript(conf_->packet);
#else
	script_.setScript(conf_->script_txt_, &conf_->LRList);
#endif

	Inherited::ResetScript();
	*/
}

#ifdef _MSC_VER
const char* ConvertCode(LPCSTR str, int sourceCodepage, int targetCodepage)
{
	int len = (int)strlen(str);
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, str, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));

	MultiByteToWideChar(sourceCodepage, 0, str, -1, (LPWSTR)pUnicode, unicodeLen);

	BYTE* pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char*)pTargetData, 0, NULL, NULL);

	pTargetData = new BYTE[targetLen + 1];
	memset(pTargetData, 0, targetLen + 1);

	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char*)pTargetData, targetLen, NULL, NULL);

	delete[] pUnicode;
	return (const char*)pTargetData;
}
#endif

bool ScriptNpc::LoadScript(const char* path, bool reload)
{
	bool result = false;
	const char* script_txt = NULL;

	if (path == NULL)
	{
		OutputMsg(rmError, ("unable to load Script file npc=%s"), GetEntityName());
		return false;
	}

	//从文件加载脚本
	MemoryStream ms(NULL);

	if (ms.loadFromFile(path) <= 0)
	{
		OutputMsg(rmError, ("unable to load Script file %s"), path);
		return false;
	}

	//对脚本进行预处理
	LuaPreProcessor pp(NULL);
	ServerInstance()->GetVSPDefine().RegisteToPreprocessor(pp);

	//增加语言包已被加载的标记，语言包已经作为独立的配置读取了，这里注册宏后可以加快脚本读取
	if (!pp.getMacro("_LANGUAGE_INCLUDED_"))
		pp.addMacro("_LANGUAGE_INCLUDED_");

	try
	{
		if (script_len_ > 0)
		{
			pp.setSize((int)script_len_);	// 一次扩展到足够的长度
		}
		else if (strcmp(GameEngine::GlobalScriptFile, path) == 0)
		{
			pp.setSize(30 * 1024 * 1024);
		}
		script_txt = pp.parse((const char*)ms.getMemory(), path);
	}
	catch (RefString& s)
	{
		OutputMsg(rmError, ("%s error: %s, scriptfile:%s"), __FUNCTION__, s.rawStr(), path);
	}
	catch (...)
	{
		OutputMsg(rmError, ("unexpected error on %s %s"), __FUNCTION__, path);
	}

	if (!script_txt)
	{
		OutputMsg(rmError, ("unable to pre-process Script file,npc %s"), GetEntityName());
		return false;
	}

	misc::RefObject<LuaPreProcessor::LineRangeList> LRList;
	int lrCount = pp.getLineRangeData(NULL, 0);

	if (lrCount > 0)
	{
		LRList = new misc::RefObjectImpl<LuaPreProcessor::LineRangeList>();
		LRList.raw_ptr()->reserve(lrCount);
		pp.getLineRangeData(*LRList.raw_ptr(), lrCount);
		LRList.raw_ptr()->trunc(lrCount);
	}

	size_t len = strlen(script_txt);
	script_len_ = len;
	if (len > 1024 * 1024)
	{
		OutputMsg(rmError, "********npc script too big:%s", path);
	}

	//设置脚本

	/* 采取先编译的方式的话，旧代码实际没有执行到，所以下面的也没初始化
	script_cache_.reserve(64 * 1024); 但是这里之前要初始化才行
	script_cache_.setAllocSize(10 * 1024);
	script_cache_.setLength(0);
	result = script_.setBinScript(script_txt, script_cache_, path, true);
	script_cache_ = LRList;
	*/
	result = script_.setScript(script_txt, &LRList);

#ifdef _MSC_VER

	if (!result)
	{
		// 输出脚本，用于调试
		FILE* fp = fopen("d:\\scripterror.txt", "wb");

		if (fp)
		{
			fputs(script_txt, fp);
			fclose(fp);
		}
	}
#else
	if (!result)
	{
		// 输出脚本，用于调试
		FILE* fp = fopen("scripterror.txt", "wb");

		if (fp)
		{
			fputs(script_txt, fp);
			fclose(fp);
		}
	}
#endif
	return result;
}

bool ScriptNpc::Call(const char* fn)
{
	if (fn == NULL || fn[0] == 0) return false;

	ScriptValueList va;

	char args[1024];
	args[0] = 0;

	FuncParamProcess(fn, args, sizeof(args), va);
	//调用脚本函数，期待返回1个值
	return (script_.Call(args, &va, &va, 1));
}