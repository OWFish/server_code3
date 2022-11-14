#ifndef _LUA_MEMORY_H_
#define _LUA_MEMORY_H_

/************************************************************************
*						    脚本内存管理器
*                 目前的实现方式是采用单独的堆进行内存管理。
************************************************************************/

namespace luamemory
{
	void Initialize();
	void Realease();
	//LUA虚拟机内存申请函数
	void* luaAlloc(void *ud, void* ptr, size_t osize, size_t newsize);
	void GC();
	void printState();
}

#endif

