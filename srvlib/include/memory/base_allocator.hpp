#ifndef _BASE_ALLOCATOR_H_
#define _BASE_ALLOCATOR_H_

/************************************************************************
* 内存分配器的基类，其他分配器可继承其接口，实现不同的内存分配算法
* 这个基类实现的内存分配就是直接用crt分配内存
************************************************************************/

#include "os_def.h"

#include "memory_counter.hpp"

#ifdef _MEMORY_TRACE_
#define AllocBuffer(count_) _AllocBuffer(count_,__FILE__, __LINE__)
#define ReAllocBuffer(src,count_) _ReAllocBuffer(src,count_,__FILE__, __LINE__)
#define FreeBuffer(ptr) _FreeBuffer(ptr, __FILE__, __LINE__)
#endif

class BaseAllocator : public AllocatorCounterItem
{
public:
#ifndef _MEMORY_TRACE_
	virtual void* AllocBuffer(size_t count)
#else
	virtual void* _AllocBuffer(size_t count, const char*, int)
#endif
	{
		size_t* result = (size_t*)malloc(count + sizeof(size_t));
#ifdef _MEMORY_TRACE_

		if (result != NULL)
		{
			alloc_total_ += count;

			*result = count;
		}

#endif
		return (void*)(result + 1);
	}

#ifndef _MEMORY_TRACE_
	virtual void* ReAllocBuffer(void* src, size_t count)
#else
	virtual void* _ReAllocBuffer(void* src, size_t count, const char*, int)
#endif
	{
#ifdef _MEMORY_TRACE_
		if (src)
		{
			size_t old = *((size_t*)src - 1);
			alloc_total_ -= old; 
			src = (void*)((size_t*)src - 1);
		}
		alloc_total_ += count; // 注意是size_t类型
#endif

		size_t* result = (size_t*)realloc(src, count + sizeof(size_t));
		*result = count;
		return (void*)(result + 1);
	}
#ifndef _MEMORY_TRACE_
	virtual void FreeBuffer(void* ptr)
#else
	virtual void _FreeBuffer(void* ptr, const char*, int)
#endif
	{
		if (!ptr) return;

#ifdef _MEMORY_TRACE_
		size_t old = *((size_t*)ptr - 1);
		alloc_total_ -= old;
#endif
		free((size_t*)ptr - 1);
	}
	BaseAllocator(const char* namestr) : AllocatorCounterItem(namestr)
	{
	}
	virtual ~BaseAllocator()
	{
	}

	void SetMultiThread(bool){}
	void GC()
	{

	}
};

#endif	//end _BASE_ALLOCATOR_H_
