#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

/************************************************************************
* 内存分配器，只分配固定大小的内存，适用于频繁创建实例的类，结构体之类
************************************************************************/
#include "os_def.h"
#include "container/vector.h"
#include "memory_counter.hpp"
#include "allocdef.h"

template <int BUFF_SIZE, int ONE_TIME_COUNT = 1024>
class MemPool :
	public AllocatorCounterItem
{
public:

	typedef AllocatorCounterItem Inherited;

private:
	struct DataBlock
	{
		DataBlock*	prev_;
	}*		data_block_;
public:

#ifndef _MEMORY_TRACE_
	void* Alloc()
#else
#define Alloc() _Alloc(__FILE__, __LINE__)
#define Free(ptr) _Free(ptr, __FILE__, __LINE__)
	void* _Alloc(const char* file_name, int line)
#endif
	{
		void* result;
		int count = free_list_.count();

		if (count <= 0)
		{
			count = all_size_ > 0 ? all_size_ * 2 : ONE_TIME_COUNT;	// 每次double
			all_size_ += count;
#ifndef _MEMORY_TRACE_
			size_t allocsize = sizeof(DataBlock) + BUFF_SIZE * count;
#else
			size_t allocsize = sizeof(DataBlock) + (BUFF_SIZE + sizeof(AllocBuffHead)) * count;
#endif
			DataBlock* block_ptr = (DataBlock*)malloc(allocsize);
#ifdef _MEMORY_TRACE_
			alloc_total_ += allocsize;
#endif
			//将对象指针全部添加到空闲列表中
			result = (void*)(block_ptr + 1);

			if (free_list_.max_size() < all_size_)
				free_list_.reserve(all_size_);

			void** list = free_list_;

			for (int i = 0; i < count; ++i)
			{
				list[i] = result;
#ifdef _MEMORY_TRACE_
				AllocBuffHead* hdr = (AllocBuffHead*)result;
				hdr->using_flag_ = false;
				hdr->buff_size_ = BUFF_SIZE;
				result = (void*)((char*)result + BUFF_SIZE + sizeof(AllocBuffHead));
#else
				result = (void*)((char*)result + BUFF_SIZE);
#endif
			}

#ifdef _MEMORY_TRACE_
			all_list_.addArray(free_list_, count);//已经分配的记录下
#endif
			//标记上内存块的上一个内存块
			block_ptr->prev_ = data_block_;
			data_block_ = block_ptr;
		}

		//返回列表中的最后一个对象
		count--;
		result = free_list_[count];
		free_list_.trunc(count);
#ifdef _MEMORY_TRACE_
		used_count_ += BUFF_SIZE;
#endif

#ifdef _MEMORY_TRACE_
		AllocBuffHead* hdr = (AllocBuffHead*)result;
#ifdef _MSC_VER
		assert(hdr->using_flag_ == false);	// 如果触发这个assert，这个是有严重的bug，这里先规避
#endif
		hdr->using_flag_ = true;
		hdr->al_.fn_ = file_name;
		hdr->al_.line_ = line;
		result =  hdr + 1;
#endif

		return result;
	}
#ifndef _MEMORY_TRACE_
	void Free(void* ptr)
#else
	void _Free(void* ptr, const char* file_name, int line)
#endif
	{
		if (ptr == NULL) return;

#ifdef _MEMORY_TRACE_
		AllocBuffHead* hdr = (AllocBuffHead*)ptr;
		hdr--;

		if (!hdr->using_flag_)
		{
			char err[1024];
			SNPRINTFA(err, sizeof(err) - 1, " %s Free the buff that had be release before(size:%d),alloc：%s(%d),free：%s(%d),now:%s(%d)\n",
				__FUNCTION__, (int)hdr->buff_size_, hdr->al_.fn_, hdr->al_.line_,
				hdr->fl_.fn_, hdr->fl_.line_, file_name, line);
			OutputWatchFile(err, "err.log");
#ifdef _MSC_VER
			// 这个是有严重的bug，这里先规避,直接return
			assert(false);
#endif
			return;
		}
#ifdef _MSC_VER
		assert(hdr->using_flag_);//检查有没有重复释放
#endif
		hdr->using_flag_ = false;
		hdr->fl_.fn_ = file_name;
		hdr->fl_.line_ = line;
		ptr =  hdr;
#endif
		free_list_.add(ptr);
#ifdef _MEMORY_TRACE_
		used_count_ -= BUFF_SIZE;
#endif
	}
	MemPool(const char* namestr)
		: Inherited(namestr)
	{
		data_block_ = NULL;
		all_size_ = 0;
	}

	~MemPool()
	{
#ifdef _MEMORY_TRACE_

		for (int i = 0; i < all_list_.size(); i++)
		{
			AllocBuffHead* hdr = (AllocBuffHead*)(all_list_[i]);

			if (hdr->using_flag_)
			{
				char err[1024];
				SNPRINTFA(err, sizeof(err) - 1, " %scheck memory leaks(size:%d),alloc：%s(%d)\n",
					__FUNCTION__, (int)hdr->buff_size_, hdr->al_.fn_, hdr->al_.line_);
				OutputWatchFile(err, "err.log");
			}
#ifdef _MSC_VER
			assert(hdr->using_flag_ == false);//内存泄露了
#endif
		}

#endif
		DataBlock* block_ptr, *prev;
		block_ptr = data_block_;
		int block_count = 0;

		while (block_ptr)
		{
			prev = block_ptr->prev_;
			free(block_ptr);
			block_ptr = prev;
			block_count++;
		}

		data_block_ = NULL;
#ifdef _MEMORY_TRACE_
		
		size_t free_size = free_list_.count() * (BUFF_SIZE + sizeof(AllocBuffHead)) + block_count * sizeof(DataBlock);
		if (free_size != alloc_total_)
		{
			char err[1024];
			SNPRINTFA(err, sizeof(err) - 1, "%s:%s:%d memory error,free size:%lld, alloc_size:%lld\n",
				__FUNCTION__, __FILE__, __LINE__, (long long int)free_size, (long long int)alloc_total_);
			OutputWatchFile(err, "err.log");
		}
#ifdef _MSC_VER
		assert(free_list_.count() * (BUFF_SIZE + sizeof(AllocBuffHead)) + block_count * sizeof(DataBlock) == alloc_total_); //简单的检查是否内存泄露
#endif

#else
		//assert(free_list_.count()*BUFF_SIZE+block_count*sizeof(DataBlock) == alloc_total_);//简单的检查是否内存泄露
#endif
	}

//public:
//#ifdef _MEMORY_TRACE_
//	virtual int Log(char* buf, int num){ return sprintf(buf,"alloc total:%d,used:%d",alloc_total_,used_count); }
//#endif

protected:
	container::Vector<void*> free_list_;
	int all_size_;

#ifdef _MEMORY_TRACE_
	container::Vector<void*> all_list_;//所有分配的内存都会在这里记录
#endif
};

#endif	//end _MEMPOOL_H_
