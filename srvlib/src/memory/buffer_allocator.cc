#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include <_ast.h>
#include "x_lock.h"
#include <x_tick.h>
#include <assert.h>
#include "memory/buffer_allocator.h"
#include "share_util.h"

#ifdef _MEMORY_TRACE_
#define _Free(x) /*alloc_total_ -= x->size_; */free(x);
#else
#define _Free(x) free(x)
#endif
static const int BufferFreeTick = 30 * 1000;//标记为释放的的内存块的延时销毁时间

BufferAllocator::BufferAllocator(const char* namestr): BaseAllocator(namestr)
{
	last_small_buffer_ = NULL;
	last_middle_buffer_ = NULL;
	last_large_buffer_ = NULL;
	last_super_buffer_ = NULL;
#ifdef _MEMORY_TRACE_
	last_alloced_buffer_ = NULL;
#endif
	alloced_small_size_ = 0;
	alloced_middle_size_ = 0;
	alloced_large_size_  = 0;
	alloced_super_size_ = 0;
	freed_small_size_ = 0;
	freed_middle_size_ = 0;
	freed_large_size_ = 0;
	freed_super_size_ = 0;
	//InitializeCriticalSection( &buffer_lock_ );

	mult_thread_ = true;
}

BufferAllocator::~BufferAllocator()
{
	PBUFFER pBuffer, pPrevBuffer;

	pBuffer = last_small_buffer_;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;
		_Free(pBuffer);
		pBuffer = pPrevBuffer;
	}

	pBuffer = last_middle_buffer_;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;
		_Free(pBuffer);
		pBuffer = pPrevBuffer;
	}

	pBuffer = last_large_buffer_;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;
		_Free(pBuffer);
		pBuffer = pPrevBuffer;
	}

	pBuffer = last_super_buffer_;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;
		_Free(pBuffer);
		pBuffer = pPrevBuffer;
	}

#ifdef _MEMORY_TRACE_
	pBuffer = last_alloced_buffer_;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;

		OutputMsg(rmError, ("%s(%d) : memory has not free！pointer Addr=%d\n"), 
			pBuffer->al.fn_, pBuffer->al.line_, (size_t)pBuffer);

		char err[1024];
		SNPRINTFA(err, sizeof(err) - 1, ("%s(%d) : memory has not free！pointer Addr=%d\n"), 
			pBuffer->al.fn_, pBuffer->al.line_, (size_t)pBuffer);
		OutputWatchFile(err, "err.log");

#ifdef _MSC_VER
		system("pause");
#endif
		assert(false);//有内存泄漏，提醒
		_Free(pBuffer);
		pBuffer = pPrevBuffer;
	}

#endif
	//DeleteCriticalSection( &buffer_lock_ );
}

#ifndef _MEMORY_TRACE_
void* BufferAllocator::AllocBuffer(size_t size)
#else
void* BufferAllocator::_AllocBuffer(size_t size, const char* fn, int line)
#endif
{
	PBUFFER pBuffer, pPrev, pResult = NULL;

	//EnterCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Lock();

	if (size <= SmallBufferSize)
	{
		if (last_small_buffer_)
		{
			pResult = last_small_buffer_;
			last_small_buffer_ = pResult->prev_buffer_;
			pResult->prev_buffer_ = NULL;
			freed_small_size_ -= SmallBufferSize;
		}
		else
		{
#ifdef _MEMORY_TRACE_
			pResult = (PBUFFER)malloc(SmallBufferSize + sizeof(*pResult) + sizeof(int));
#else
			pResult = (PBUFFER)malloc(SmallBufferSize + sizeof(*pResult));
#endif
			pResult->size_ = SmallBufferSize;
			pResult->prev_buffer_ = NULL;
#ifdef _MEMORY_TRACE_
			pResult->used_flag_ = false;
			pResult->next_buffer_ = NULL;
#endif
		}

		alloced_small_size_ += SmallBufferSize;
	}
	else if (size <= MiddleBufferSize)
	{
		if (last_middle_buffer_)
		{
			pResult = last_middle_buffer_;
			last_middle_buffer_ = pResult->prev_buffer_;
			pResult->prev_buffer_ = NULL;
			freed_middle_size_ -= MiddleBufferSize;
		}
		else
		{
#ifdef _MEMORY_TRACE_
			pResult = (PBUFFER)malloc(MiddleBufferSize + sizeof(*pResult) + sizeof(int));
#else
			pResult = (PBUFFER)malloc(MiddleBufferSize + sizeof(*pResult));
#endif
			pResult->size_ = MiddleBufferSize;
			pResult->prev_buffer_ = NULL;
#ifdef _MEMORY_TRACE_
			pResult->used_flag_ = false;
			pResult->next_buffer_ = NULL;
#endif
		}

		alloced_middle_size_ += MiddleBufferSize;
	}
	else if (size <= LargeBufferSize)
	{
		if (last_large_buffer_)
		{
			pResult = last_large_buffer_;
			last_large_buffer_ = pResult->prev_buffer_;
			pResult->prev_buffer_ = NULL;
			freed_large_size_ -= LargeBufferSize;
		}
		else
		{
#ifdef _MEMORY_TRACE_
			pResult = (PBUFFER)malloc(LargeBufferSize + sizeof(*pResult) + sizeof(int));
#else
			pResult = (PBUFFER)malloc(LargeBufferSize + sizeof(*pResult));
#endif
			pResult->size_ = LargeBufferSize;
			pResult->prev_buffer_ = NULL;
#ifdef _MEMORY_TRACE_
			pResult->used_flag_ = false;
			pResult->next_buffer_ = NULL;
#endif
		}

		alloced_large_size_ += LargeBufferSize;
	}
	else
	{
		pPrev = NULL;
		pBuffer = last_super_buffer_;

		while (pBuffer)
		{
			if (pBuffer->size_ >= size)
			{
				pResult = pBuffer;
#ifdef _MEMORY_TRACE_
				assert(!pResult->used_flag_);
#endif

				if (pResult == last_super_buffer_)
				{
					last_super_buffer_ = pResult->prev_buffer_;
					pResult->prev_buffer_ = NULL;
				}
				else  if (pPrev)
				{
					pPrev->prev_buffer_ = pResult->prev_buffer_;
					pResult->prev_buffer_ = NULL;
				}

				freed_super_size_ -= pResult->size_;
				break;
			}

			pPrev = pBuffer;
			pBuffer = pBuffer->prev_buffer_;
		}

		if (!pResult)
		{
			size = (size + 511) & (~511);
#ifdef _MEMORY_TRACE_
			pResult = (PBUFFER)malloc(size + sizeof(*pResult) + sizeof(int));
#else
			pResult = (PBUFFER)malloc(size + sizeof(*pResult));
#endif
			pResult->size_ = size;
			pResult->prev_buffer_ = NULL;
#ifdef _MEMORY_TRACE_
			pResult->used_flag_ = false;
			pResult->next_buffer_ = NULL;
#endif
		}

		alloced_super_size_ += pResult->size_;
	}

#ifdef _MEMORY_TRACE_

	if (pResult)
	{
		assert(!pResult->used_flag_);
		pResult->used_flag_ = true;
		pResult->al.fn_ = fn;
		pResult->al.line_ = line;
		pResult->fl.fn_ = NULL;
		pResult->fl.line_ = 0;
		pResult->free_tick_ = 0;

		*((int*)((char*)(pResult + 1) + pResult->size_)) = 0xCC55EE33;

		if (last_alloced_buffer_) last_alloced_buffer_->next_buffer_ = pResult;

		pResult->prev_buffer_ = last_alloced_buffer_;
		pResult->next_buffer_ = NULL;
		last_alloced_buffer_ = pResult;

		alloc_total_ += pResult->size_;
	}

#endif

	//LeaveCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Unlock();

	return pResult ? pResult + 1 : NULL;
}


#ifndef _MEMORY_TRACE_
void* BufferAllocator::ReAllocBuffer(void* ptr, size_t new_size)
#else
void* BufferAllocator::_ReAllocBuffer(void* ptr, size_t new_size, const char* fn, int)
#endif
{
	if (new_size == 0)
	{
		FreeBuffer(ptr);
		return NULL;
	}

	PBUFFER pBuffer = NULL;

	if (ptr)
	{
		pBuffer = ((PBUFFER)ptr) - 1;

		if (new_size <= pBuffer->size_)
			return ptr;
	}

	void* pResult;
#ifndef _MEMORY_TRACE_
	pResult = AllocBuffer(new_size);

	if (ptr)
	{
		memcpy(pResult, ptr, pBuffer->size_);
		FreeBuffer(ptr);
	}

#else
	pResult = _AllocBuffer(new_size, fn, 0);

	if (ptr)
	{
		memcpy(pResult, ptr, pBuffer->size_);
		_FreeBuffer(ptr, fn, 0);
	}

#endif
	return pResult;
}

#ifndef _MEMORY_TRACE_
void BufferAllocator::FreeBuffer(void* ptr)
#else
void BufferAllocator::_FreeBuffer(void* ptr, const char* fn, int line)
#endif
{
	PBUFFER pBuffer;

	if (!ptr) return;

	pBuffer = ((PBUFFER)ptr) - 1;

	//EnterCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Lock();

#ifdef _MEMORY_TRACE_

	if (!pBuffer->used_flag_)
	{
		//TRACE( (__FUNCTION__)(" 试图释放已经被标记为释放的内存块(%X,大小:%d)，申请位置：%s(%d)，释放位置：%s(%d)\n"),
		//	pBuffer, pBuffer->dwSize, pBuffer->al.lpFile, pBuffer->al.nLine,
		//	pBuffer->fl.lpFile, pBuffer->fl.nLine );
		OutputMsg(rmError, (" %s try to free the memory that had freed before(%X,size:%d)，alloc file：%s(%d)，free file：%s(%d)\n"),
		          __FUNCTION__, pBuffer, pBuffer->size_, pBuffer->al.fn_, pBuffer->al.line_,
		          pBuffer->fl.fn_, pBuffer->fl.line_);
	}

	alloc_total_ -= pBuffer->size_;
	assert(pBuffer->used_flag_);
	pBuffer->used_flag_ = false;
	assert(*((int*)((char*)(pBuffer + 1) + pBuffer->size_)) == (int)0xCC55EE33);

	if (pBuffer->prev_buffer_)
		pBuffer->prev_buffer_->next_buffer_ = pBuffer->next_buffer_;

	if (pBuffer->next_buffer_)
		pBuffer->next_buffer_->prev_buffer_ = pBuffer->prev_buffer_;

	if (pBuffer == last_alloced_buffer_)
		last_alloced_buffer_ = pBuffer->prev_buffer_;

	pBuffer->prev_buffer_ = NULL;
	pBuffer->next_buffer_ = NULL;
	pBuffer->fl.fn_ = fn;
	pBuffer->fl.line_ = line;
#endif

	pBuffer->free_tick_ = _getTickCount() + BufferFreeTick;

	if (pBuffer->size_ == SmallBufferSize)
	{
		pBuffer->prev_buffer_ = last_small_buffer_;
		last_small_buffer_ = pBuffer;
		alloced_small_size_ -= SmallBufferSize;
		freed_small_size_ += SmallBufferSize;
	}
	else if (pBuffer->size_ == MiddleBufferSize)
	{
		pBuffer->prev_buffer_ = last_middle_buffer_;
		last_middle_buffer_ = pBuffer;
		alloced_middle_size_ -= MiddleBufferSize;
		freed_middle_size_ += MiddleBufferSize;
	}
	else if (pBuffer->size_ == LargeBufferSize)
	{
		pBuffer->prev_buffer_ = last_large_buffer_;
		last_large_buffer_ = pBuffer;
		alloced_large_size_ -= LargeBufferSize;
		freed_large_size_ += LargeBufferSize;
	}
	else
	{
		pBuffer->prev_buffer_ = last_super_buffer_;
		last_super_buffer_ = pBuffer;
		alloced_super_size_ -= pBuffer->size_;
		freed_super_size_ += pBuffer->size_;
	}

	//LeaveCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Unlock();
}

void BufferAllocator::GetMemoryInfo(BufferAllocator::ALLOCATOR_MEMORY_INFO* pMemoryInfo)
{
	pMemoryInfo->SmallBuffer.alloc_size_ = alloced_small_size_;
	pMemoryInfo->SmallBuffer.free_size_ = freed_small_size_;
	pMemoryInfo->MiddleBuffer.alloc_size_ = alloced_middle_size_;
	pMemoryInfo->MiddleBuffer.free_size_ = freed_middle_size_;
	pMemoryInfo->LargeBuffer.alloc_size_ = alloced_large_size_;
	pMemoryInfo->LargeBuffer.free_size_ = freed_large_size_;
	pMemoryInfo->SuperBuffer.alloc_size_ = alloced_super_size_;
	pMemoryInfo->SuperBuffer.free_size_ = freed_super_size_;
}

void BufferAllocator::CheckFreeBuffers()
{
	PBUFFER pBuffer, pPrevBuffer, pLastBuffer;
	long long dwTick = _getTickCount();

	//EnterCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Lock();

	pBuffer = last_small_buffer_;
	pLastBuffer = NULL;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;

		if (dwTick >= pBuffer->free_tick_)
		{
			if (pBuffer == last_small_buffer_)
				last_small_buffer_ = pPrevBuffer;

			if (pLastBuffer)
				pLastBuffer->prev_buffer_ = pPrevBuffer;

			freed_small_size_ -= pBuffer->size_;
			_Free(pBuffer);
		}
		else pLastBuffer = pBuffer;

		pBuffer = pPrevBuffer;
	}

	pBuffer = last_middle_buffer_;
	pLastBuffer = NULL;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;

		if (dwTick >= pBuffer->free_tick_)
		{
			if (pBuffer == last_middle_buffer_)
				last_middle_buffer_ = pPrevBuffer;

			if (pLastBuffer)
				pLastBuffer->prev_buffer_ = pPrevBuffer;

			freed_middle_size_ -= pBuffer->size_;
			_Free(pBuffer);
		}
		else pLastBuffer = pBuffer;

		pBuffer = pPrevBuffer;
	}

	pBuffer = last_large_buffer_;
	pLastBuffer = NULL;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;

		if (dwTick >= pBuffer->free_tick_)
		{
			if (pBuffer == last_large_buffer_)
				last_large_buffer_ = pPrevBuffer;

			if (pLastBuffer)
				pLastBuffer->prev_buffer_ = pPrevBuffer;

			freed_large_size_ -= pBuffer->size_;
			_Free(pBuffer);
		}
		else pLastBuffer = pBuffer;

		pBuffer = pPrevBuffer;
	}

	pBuffer = last_super_buffer_;
	pLastBuffer = NULL;

	while (pBuffer)
	{
		pPrevBuffer = pBuffer->prev_buffer_;

		if (dwTick >= pBuffer->free_tick_)
		{
			if (pBuffer == last_super_buffer_)
				last_super_buffer_ = pPrevBuffer;

			if (pLastBuffer)
				pLastBuffer->prev_buffer_ = pPrevBuffer;

			freed_super_size_ -= pBuffer->size_;
			_Free(pBuffer);
		}
		else pLastBuffer = pBuffer;

		pBuffer = pPrevBuffer;
	}

	//LeaveCriticalSection( &buffer_lock_ );
	if (mult_thread_) buffer_lock_.Unlock();
}

void BufferAllocator::SetMultiThread(bool flag)
{
	mult_thread_ = flag;
}

void BufferAllocator::GC()
{
	CheckFreeBuffers();
}


