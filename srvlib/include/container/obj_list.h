#ifndef _OBJ_LIST_H_
#define _OBJ_LIST_H_

/************************************************************************
* ����Ļ���أ��ӳ���ȡ���ľ���һ�����õĶ��󣬷ŵ����еĶ���ִ������������
* �����ɱ���ִ�й��캯�������������Ŀ������ر�����Ҫ�����ڴ�Ķ��󣬿ɱ��������Ƭ
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
			assert(all_obj_count_ == free_obj_count_);	// �ڴ�й©?
			// �ͷ��ڴ�
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
				//ѭ�����ù��캯��
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


