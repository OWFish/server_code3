#ifndef _MSG_ALLOCATOR_H_
#define	_MSG_ALLOCATOR_H_

#include "os_def.h"
#include "x_tick.h"
#include "base_allocator.hpp"
#include "x_lock.h"

class BaseAllocator;

using namespace tick64;
using namespace lock;

class BufferAllocator: public BaseAllocator
{

public:
	static const unsigned int SmallBufferSize	= 64;	//小块内存块大小
	static const unsigned int MiddleBufferSize	= 256;	//中等内存块大小
	static const unsigned int LargeBufferSize	= 1024;	//大块内存块大小

#pragma pack(push, 1)
	typedef struct tagBuffer
	{
		size_t		size_;		//内存数据段大小
		tagBuffer*	prev_buffer_;//指向上一个内存块的指针
		int64_t		free_tick_;	//即将被销毁的时间
#ifdef _MEMORY_TRACE_
		tagBuffer*	next_buffer_;//指向上下个内存块的指针，用于调试
		struct
		{
			const char* fn_;		//申请内存块的代码位置，用于调试
			int line_;
		} al, fl;
		bool		used_flag_;	//是否使用的标记
#endif
	} BUFFER, *PBUFFER;
#pragma pack(pop)

	struct BufferStatic
	{
		size_t		alloc_size_;
		size_t		free_size_;
	};

	typedef struct tagAllocatorMemoryInfo
	{
		BufferStatic	SmallBuffer;
		BufferStatic	MiddleBuffer;
		BufferStatic	LargeBuffer;
		BufferStatic	SuperBuffer;
	} ALLOCATOR_MEMORY_INFO;

private:
	Mutex				buffer_lock_;			//内存块申请锁
	PBUFFER				last_small_buffer_;		//指向最后一个空闲的小型内存块的指针
	PBUFFER				last_middle_buffer_;	//指向最后一个空闲的中型内存块的指针
	PBUFFER				last_large_buffer_;		//指向最后一个空闲的大型内存块的指针
	PBUFFER				last_super_buffer_;		//指向最后一个空闲的超级内存块的指针
#ifdef _MEMORY_TRACE_
	PBUFFER				last_alloced_buffer_;	//指向最后一个被申请的内存块
#endif
	size_t				alloced_small_size_;	//已被申请的小型内存块大小
	size_t				alloced_middle_size_;	//已被申请的中型内存块大小
	size_t				alloced_large_size_;	//已被申请的大型内存块大小
	size_t				alloced_super_size_;	//已被申请的超级内存块大小
	size_t				freed_small_size_;		//已被释放的小型内存块大小
	size_t				freed_middle_size_;	//已被释放的中型内存块大小
	size_t				freed_large_size_;		//已被释放的大型内存块大小
	size_t				freed_super_size_;		//已被释放的超级内存块大小

	bool				mult_thread_;
public:
	BufferAllocator(const char* namestr);
	~BufferAllocator();

#ifndef _MEMORY_TRACE_
	void* AllocBuffer(size_t size);
	void* ReAllocBuffer(void* ptr, size_t new_size);
	void FreeBuffer(void* ptr);
#else
	void* _AllocBuffer(size_t size, const char* fn, int line);
	void* _ReAllocBuffer(void* ptr, size_t new_size, const char* fn, int line);
	void _FreeBuffer(void* ptr, const char* fn, int line);
#endif

	void GetMemoryInfo(BufferAllocator::ALLOCATOR_MEMORY_INFO* pMemoryInfo);
	void CheckFreeBuffers();
	void SetMultiThread(bool flag);
	void GC();
};

#endif

