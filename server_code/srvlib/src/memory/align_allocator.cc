#include "os_def.h"
#include "x_lock.h"
#include "memory/memory_counter.hpp"
#include "memory/base_allocator.hpp"
#include "memory/align_allocator.h"


AlignAllocator::AlignAllocator(const char* name, int max_size, int align) : 
		BaseAllocator(name)
{
	mult_thread_ = false;
	heads_ = NULL;

	Init(max_size, align);
}

AlignAllocator::~AlignAllocator()
{
	for (int i = 0; i < hdrCnt_; ++i)
	{
		Header& hdr = heads_[i];

		assert(hdr.total_ == hdr.free_);

		FreeNode* node = hdr.first_;

		while (node)
		{
#ifdef _MEMORY_TRACE_
			alloc_total_ -= ((i + 1) * align_);
#endif
			hdr.first_ = node->next_;
			free(node);
			node = hdr.first_;
		}

		heads_[i].total_ = 0;
	}

	delete[] heads_;
}


void AlignAllocator::Init(int max_size, int align)
{
	assert(max_size % 8 == 0 && align % 8 == 0);

	max_size_ = max_size;
	align_ = align;

	hdrCnt_ = max_size_ / align_;
	heads_ = new Header[hdrCnt_];
	rest_ = 0;
}

#ifndef _MEMORY_TRACE_
void* AlignAllocator::AllocBuffer(size_t count)
#else
void* AlignAllocator::_AllocBuffer(size_t count, const char*, int)
#endif
{
	assert(count >= 0);

	if (mult_thread_) buffer_lock_.Lock();

	FreeNode* node = NULL;

	if ((int)count <= max_size_)
	{
		int idx = GetAlignIdx((int)count);

		Header& hdr = heads_[idx];

		if (hdr.first_)
		{
			node = hdr.first_;
			hdr.first_ = node->next_;
			hdr.free_--;
		}
		else
		{
			int newSize = (idx + 1) * align_;
#ifdef _MEMORY_TRACE_
			alloc_total_ += newSize;
#endif
			Header& hdr = heads_[idx];
			hdr.total_++;

			node = (FreeNode*)malloc(newSize + sizeof(FreeNode));
		}
	}
	else
	{
#ifdef _MEMORY_TRACE_
		alloc_total_ += count;
#endif
		node = (FreeNode*)malloc(count + sizeof(FreeNode));
	}

	node->size_ = (int)count;

	if (mult_thread_) buffer_lock_.Unlock();

	return (void*)(node + 1);
}

#ifndef _MEMORY_TRACE_
void* AlignAllocator::ReAllocBuffer(void* src, size_t count)
#else
void* AlignAllocator::_ReAllocBuffer(void* src, size_t newsize, const char* fn, int line)
#endif
{
	if (newsize == 0)
	{
#ifndef _MEMORY_TRACE_
		FreeBuff(src);
#else
		_FreeBuffer(src, fn, line);
#endif
		return NULL;
	}

	if (!src)
	{
#ifndef _MEMORY_TRACE_
		return AllocBuffer(newsize);
#else
		return _AllocBuffer(newsize, fn, line);
#endif
	}

	FreeNode* node = (FreeNode*)((char*)src - sizeof(FreeNode));

	int oldsize = node->size_;

	if (oldsize >= (int)newsize) return src;

	if (oldsize > max_size_)
	{
		if ((int)newsize > max_size_)
		{
#ifdef _MEMORY_TRACE_
			alloc_total_ += (newsize - oldsize);
#endif
			node = (FreeNode*)realloc(node, newsize + sizeof(FreeNode));
			node->size_ = (int)newsize;
			return (void*)(node + 1);;
		}
		else
		{
			assert(false);
		}
	}

	// 这里不用考虑加锁的问题，allocbuffer和freebuffer里已经加锁
	void* retPtr = src;

	assert((int)newsize > oldsize);

	int idx = GetAlignIdx(oldsize);
	int newIdx = GetAlignIdx((int)newsize);

	if (idx == newIdx)
	{
		node->size_ = (int)newsize;
	}
	else
	{
		void* ret = _AllocBuffer(newsize, fn, line);

		if (src)
		{
			memcpy(ret, src, oldsize);
#ifndef _MEMORY_TRACE_
			FreeBuff(src);
#else
			_FreeBuffer(src, fn, line);
#endif
		}

		retPtr = ret;
	}

	return retPtr;
}

#ifndef _MEMORY_TRACE_
void AlignAllocator::FreeBuffer(void* ptr)
#else
void AlignAllocator::_FreeBuffer(void* ptr, const char*, int)
#endif
{
	if (!ptr) return;

	if (mult_thread_) buffer_lock_.Lock();

	FreeNode* node = (FreeNode*)ptr - 1;
	int size = node->size_;

	// 找到所在的列表
	if (size > max_size_)
	{
#ifdef _MEMORY_TRACE_
		alloc_total_ -= size;
#endif
		free(node);
	}
	else
	{
		int idx = GetAlignIdx(size);

		Header& hdr = heads_[idx];

		node->next_ = hdr.first_;

		hdr.first_ = node;

		hdr.free_++;
	}

	if (mult_thread_) buffer_lock_.Unlock();
}

void AlignAllocator::GC()
{
	if (mult_thread_) buffer_lock_.Lock();

	for (int i = 0; i < hdrCnt_; ++i)
	{
		Header& hdr = heads_[i];
		// 目前的策略是留总数的1%
		int rest = rest_ != 0 ? rest_ : (int)(hdr.total_ * 0.01);

		if (hdr.free_ > rest)
		{
			int freeCnt = hdr.free_ - rest;
			FreeNode* node = hdr.first_;
			int cnt = 0;

			while (node && cnt < freeCnt)
			{
#ifdef _MEMORY_TRACE_
				alloc_total_ -= ((i + 1) * align_);
#endif
				hdr.first_ = node->next_;
				free(node);
				node = hdr.first_;
				cnt++;
			}

			hdr.free_ = rest;
			hdr.total_ -= freeCnt;
		}
	}

	if (mult_thread_) buffer_lock_.Unlock();
}

