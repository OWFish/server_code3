#ifndef _BASE_ALLOCATOR_H_
#define _BASE_ALLOCATOR_H_

/************************************************************************
* 内存分配器的基类，其他分配器可继承其接口，实现不同的内存分配算法
* 
* 
/************************************************************************/


#include "memory_counter.hpp"

class BaseAllocator : public AllocatorCounterItem
{
public:
#ifndef _MEMORY_TRACE_
	virtual void* AllocBuff(size_t count)
#else
#define AllocBuff(count_) _AllocBuff(count_,__FILE__, __LINE__)
#define FreeBuff(ptr) _FreeBuff(ptr, __FILE__, __LINE__)
	virtual void* _AllocBuff(size_t count,const char* lpFile, int nLine)
#endif
	{
		void* result = malloc(count);
#ifdef _MEMORY_TRACE_
		if (result != NULL)
		{
			used_count_ += count;
		}
#endif
		return result;
	}
#ifndef _MEMORY_TRACE_
	virtual void FreeBuff(void* ptr)
#else
	virtual void _FreeBuff(void* ptr,const char* lpFile, int nLine)
#endif
	{
		if (ptr) free(ptr);
	}
	BaseAllocator(const char* namestr) : AllocatorCounterItem(namestr)
	{
	}
	virtual ~BaseAllocator()
	{
	}

//public:
//#ifdef _MEMORY_TRACE_	
//	virtual int Log(char* buf, int num){ return sprintf(buf,"alloc total:%d,used:%d",alloc_total_,used_count); }
//#endif
};

#endif	//end _BASE_ALLOCATOR_H_
