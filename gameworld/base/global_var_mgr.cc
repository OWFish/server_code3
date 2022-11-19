#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;

const char sGlobalVarFile[] = "./runtime/globalVar_";

GlobalVarMgr::GlobalVarMgr() : inited_(false), timer_(30 * 60 * 1000)
{
}

GlobalVarMgr::~GlobalVarMgr()
{
	Destroy();
}

void GlobalVarMgr::Load()
{
	///改成读本地文件
	char fn[256];
	SNPRINTFA(fn, sizeof(fn), "%s%d.bin", sGlobalVarFile, ServerInstance()->GetServerIndex());
	stream::MemoryStream ms(NULL);;
	size_t fs = ms.loadFromFile(fn);
	if ((int)fs > 0)
	{
		var_.loadFromMemory((char*)ms.getMemory(), fs);
	}

	inited_ = true;
}

void GlobalVarMgr::RunOne(int64_t now_t)
{
	if (inited_ && timer_.CheckAndSet(now_t, true))
	{
		static GameEngine* ge = GetGameEngine();
		static ScriptNpc* gn = ge->GetGlobalNpc();
		ScriptValueList paras;
		gn->GetScript().Call("OnChangeStaticVar", &paras, &paras);

		Save();
	}
}

void GlobalVarMgr::Save()
{
	///改成保存到文件
	char fn[256];
	SNPRINTFA(fn, sizeof(fn), "%s%d.bin", sGlobalVarFile, ServerInstance()->GetServerIndex());
	stream::MemoryStream ms(NULL);
	bool mem = true;
	size_t totalSize = var_.saveToMemory(NULL, 0, mem);

	static BaseAllocator alloc("GlobalVarMgr::Save");
	static DataPacket dp(&alloc);

	dp.reserve(totalSize);
	dp.setLength(0);
	size_t savesize = var_.saveToMemory(dp.getMemoryPtr(), dp.getAvaliableBufLen(), mem);
	ms.write(dp.getMemoryPtr(), savesize);
	ms.saveToFile(fn);

	if (savesize != totalSize)
	{
		OutputMsg(rmError, "globalvar too big to save fail!");
	}
}


