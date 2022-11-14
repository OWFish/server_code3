#ifndef _OBJ_LIST_H_
#define _OBJ_LIST_H_

/************************************************************************
* 对象的缓存池，从池中取出的就是一个可用的对象，放到池中的对象不执行析构函数，
* 这样可避免执行构造函数和析构函数的开销，特别是需要分配内存的对象，可避免产生碎片
************************************************************************/

#include <assert.h>
#include "container/vector.h"
#include "memory/buffer_allocator.h"

namespace container
{
	template <typename T, int ONE_TIME_COUNT=1024>
	class ObjList : public AllocatorCounterItem
	{
	public:
		ObjList(const char* namestr, const char* name2):AllocatorCounterItem(namestr), 
			all_obj_count_(0), free_obj_count_(0), allocator_(name2)
		{			
		}
		~ObjList()
		{
			assert(all_obj_count_ == free_obj_count_);	// 内存泄漏?
			// 释放内存
			int count = free_.count();
			T** list = free_;
			for (int i = 0; i < count; ++i)
			{
				list[i]->~T();
			}
			count = all_.count();
			list = all_;
			for (int i = 0; i < count; ++i)
			{
				allocator_.FreeBuffer(list[i]);
			}
			allocator_.CheckFreeBuffers();
		}
		T* get()
		{
			if (free_.count() <= 0)
			{
				T* news = (T*)allocator_.AllocBuffer(sizeof(T) * ONE_TIME_COUNT);
				all_.add(news);
				all_obj_count_ += ONE_TIME_COUNT;
				free_.reserve(all_obj_count_);
				//循环调用构造函数
				for (int i = 0; i < ONE_TIME_COUNT; ++i)
				{
					new(news)T();
					free_[i] = news;
					news++;
				}
				free_obj_count_ = ONE_TIME_COUNT;
				free_.trunc(free_obj_count_);
			}
			assert(free_obj_count_ == free_.count());
			--free_obj_count_;
			T* result = free_[free_obj_count_];
			free_.trunc(free_obj_count_);
			return result;
		}
		void release(T* p)
		{
			if (!p) return;
			free_.add(p);
			free_obj_count_++;
		}
	private:
		Vector<T*>	all_;
		Vector<T*>	free_;
		int			all_obj_count_;
		int			free_obj_count_;
		BufferAllocator	allocator_;
	};
};
#endif


