#ifndef _OJBPOOL_H_
#define _OJBPOOL_H_


/************************************************************************
* 内存分配器，只分配固定大小的类和结构体之类，
* 和mempool的区别是会自动执行构造函数和析构函数
************************************************************************/
#include "os_def.h"
#include "mempool.hpp"

template <typename T, int ONE_TIME_COUNT = 1024>

class ObjPool :	
	public MemPool<sizeof(T), ONE_TIME_COUNT>
{
	typedef MemPool<sizeof(T), ONE_TIME_COUNT> Inherited;
public:
	ObjPool(const char* namestr)
		:Inherited(namestr)
	{
	}

#ifndef _MEMORY_TRACE_
	T* Alloc()
	{
		T* result = (T*)Inherited::Alloc();
#else
	T* _Alloc(const char* fn, int line)
	{
		T* result = (T*)Inherited::_Alloc(fn, line);
#endif
		new(result)T();
		return result;
	}
#ifndef _MEMORY_TRACE_	
	void Free(T* ptr)
	{
		if (ptr == NULL) return;
		ptr->~T();
		Inherited::Free(ptr);
	}
#else
	void _Free(T* ptr, const char* fn, int line)
	{
		if (ptr == NULL) return;
		ptr->~T();
		Inherited::_Free(ptr, fn, line);
	}
#endif
};


#endif

