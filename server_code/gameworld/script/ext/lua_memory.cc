#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "lua_memory.h"
#include <stdlib.h>

//总计活动内存块数量
int64_t g_nMemBlockCount = 0;
//总计活动内存大小，以字节为单位
int64_t g_nTotalMemSize = 0;

#ifdef AAA

//全局脚本内存堆
void* g_hScriptMemHeap = NULL;

namespace luamemory
{
//初始化脚本内存管理器
void Initialize()
{
	if (!g_hScriptMemHeap)
	{
		g_hScriptMemHeap = HeapCreate(0, 16 * 1024 * 1024, 0);

		if (!g_hScriptMemHeap)
			OutputMsg(rmError, "Failed to create Script Alone Heap!");
		else g_nMemBlockCount = g_nTotalMemSize = 0;
	}
}


//析构脚本内存管理器
void Realease()
{
	if (g_hScriptMemHeap)
	{
		HeapDestroy(g_hScriptMemHeap);
		g_hScriptMemHeap = NULL;
		g_nMemBlockCount = g_nTotalMemSize = 0;
	}
}
void GC()
{

}
void printState()
{
	OutputMsg(rmError, "script memory:%I64d, %I64d", g_nTotalMemSize, g_nMemBlockCount);
}

void* luaAlloc(void* ud, void* ptr, size_t osize, size_t newsize)
{
	void* result;

	//内存堆尚未初始化
	if (!g_hScriptMemHeap)
		Initialize();

	//申请内存
	if (newsize > 0)
	{
		if (osize == 0)
		{
			result = HeapAlloc(g_hScriptMemHeap, 0, newsize);

			if (result)
			{
				g_nMemBlockCount++;
				g_nTotalMemSize += newsize;
			}
		}
		else
		{
			result = HeapReAlloc(g_hScriptMemHeap, 0, ptr, newsize);

			if (result)
			{
				g_nTotalMemSize += (int64_t)newsize - (int64_t)osize;
			}
		}
	}
	//释放内存
	else if (newsize <= 0)
	{
		if (ptr)
		{
			HeapFree(g_hScriptMemHeap, 0, ptr);
			g_nTotalMemSize -= osize;
			g_nMemBlockCount--;

			if (g_nMemBlockCount <= 0)
			{
				if (g_nTotalMemSize > 0)
				{
					OutputMsg(rmError, "Script Memroy Manager Detected Memory Leaks for %I64d bytes", g_nTotalMemSize);
				}

				Realease();
			}
		}

		result = NULL;
	}

	return result;
}

}
#else

namespace luamemory
{
	LuaAlloc* alloc = NULL;
	//BaseAllocator* alloc = NULL;
	size_t max_s = 0;
	void Initialize()
	{
		if (!alloc) alloc = new LuaAlloc("ScriptMemoryManager", 4096, 16);
	}
	void Realease()
	{
		if (alloc) delete alloc;
	}
	void GC()
	{
		alloc->GC();
	}
	void printState()
	{
		OutputMsg(rmError, "script memory:%lld, %lld,%d", (long long int)g_nTotalMemSize, (long long int)g_nMemBlockCount, max_s);
	}

	void* luaAlloc(void* ud, void* ptr, size_t osize, size_t newsize)
	{
		void* result = NULL;

		//申请内存
		if (newsize > 0)
		{
			if (osize == 0)
			{
				result = alloc->AllocBuffer(newsize);
				if (result)
				{
					g_nMemBlockCount++;
					if (newsize > max_s) max_s = newsize;
					g_nTotalMemSize += newsize;
				}
			}
			else
			{
				result = alloc->ReAllocBuffer(ptr, newsize);
				if (result)
				{
					g_nTotalMemSize += (int64_t)newsize - (int64_t)osize;
				}
				if (newsize > max_s) max_s = newsize;
			}
			
		}
		//释放内存
		else if (newsize <= 0)
		{
			if (ptr)
			{
				alloc->FreeBuffer(ptr);
				g_nTotalMemSize -= osize;
				g_nMemBlockCount--;
			}

			result = NULL;
		}

		return result;
	}

}

#endif
