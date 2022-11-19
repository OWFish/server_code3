#ifndef _BUFF_ALLOCATOR_H_
#define _BUFF_ALLOCATOR_H_

/************************************************************************
* 一次性的内存分配器
* 适用于一次分配内存后，直到程序结束才释放内存的地方，如配置文件的读取
* 用这个分配器的好处是：不提供释放内存的函数，因此不需要一个个内存手工释放，
* 而是由分配器一次释放
************************************************************************/


#include "os_def.h"
#include "memory_counter.hpp"

template <typename T, int ONE_TIME_COUNT = 1024>
class MemoryContainer : public AllocatorCounterItem
{
public:
	typedef AllocatorCounterItem Inherited;

	//内存块描述结构，用于查询内存块信息
	struct DataBlockDesc
	{
		const char* addr;//内存块指针地址
		size_t block_size;		  //内存块大小
	};

private:
	//内存块链表节点
	struct DataBlock
	{
		T*			free_ptr;	//指向空闲的对象
		T*			end_ptr;	//指向对象内存块的结束
		DataBlock*	prev;
	}		*data_block_;

public:

#ifndef _MEMORY_TRACE_
	T* AllocBuffer(size_t count)
#else
	T* _AllocBuffer(size_t count, const char*, int)
#endif
	{
		T* result;
		DataBlock *block_ptr = data_block_;
		//尝试从当前内存块中申请nCount的对象，如果内存块中没有足够的对象，则向之前的内存块中查找是否具有足够的空闲对象
		if ( !block_ptr || size_t(block_ptr->end_ptr - block_ptr->free_ptr) < count )
		{
			//向之前的内存块中查找是否具有足够的空闲对象
			while (block_ptr && (block_ptr = block_ptr->prev))
			{
				if ( size_t(block_ptr->end_ptr - block_ptr->free_ptr) >= count )
					break;
			}
			//如果所有内存块中都没有足够的对象则申请新内存块
			if ( block_ptr == NULL )
			{
				size_t alloc_count = __max(count, ONE_TIME_COUNT);
				block_ptr = (DataBlock*)malloc(sizeof(DataBlock) + sizeof(T) * alloc_count);
				memset(block_ptr, 0, sizeof(DataBlock) + sizeof(T) * alloc_count);
#ifdef _MEMORY_TRACE_
				alloc_total_ += alloc_count;
#endif
				block_ptr->free_ptr = (T*)(block_ptr + 1);
				block_ptr->end_ptr = block_ptr->free_ptr + alloc_count;
				block_ptr->prev = data_block_;
				data_block_ = block_ptr;
			}
		}
		//返回对象指针
		result = block_ptr->free_ptr;
		block_ptr->free_ptr += count;
#ifdef _MEMORY_TRACE_
		used_count_ += count;
#endif
		return result;
	}

	void _FreeBuffer()
	{
		DataBlock *block_ptr, *prev;
		block_ptr = data_block_;
		while (block_ptr)
		{
			prev = block_ptr->prev;
			free(block_ptr);
			block_ptr = prev;
		}
		data_block_ = NULL;
	}

	//获取内存块数量
	inline int blockCount() const
	{
		int result = 0;
		DataBlock *block_ptr = data_block_;

		while (block_ptr)
		{
			result++;
			block_ptr = block_ptr->prev;
		}
		return result;
	}
	/*
	* Comments: 枚举内存块描述信息
	* Param LPCVOID lpEnumKey: 上次枚举的返回值，作为枚举下一个的依据，第一次枚举此值必须为NULL。
	* Param DataBlockDesc & desc: 用于保存内存块描述的对象
	* @Return LPCVOID: 返回一个内存块枚举key指针，便于进行下次枚举。如果返回值为NULL则表示枚举结束
	*
	* ★★注意★★：枚举内存块描述的操作是倒叙进行的，第一个被枚举的内存块描述为左后一个内存块的描述！
	*
	* ★★示例代码★★：-------------------------------------------------
	*  LPCVOID lpEnumKey = NULL;
	*  BuffAllocator<T>::DataBlockDesc desc;
	*  while (lpEnumKey = allocator.enumBlockDesc(lpEnumKey, desc))
	*  {
	*     printf("Memory Block Info { Address = %X, Size = %u }", 
	*	    desc.lpBaseAddress, desc.dwBlockSize);
	*  }
	* --------------------------------------------------------------
	*/
	inline void* enumBlockDesc(void* enum_key, DataBlockDesc &desc) const 
	{
		DataBlock *block_ptr = (DataBlock*)enum_key;
		if (!block_ptr) 
			block_ptr = data_block_;
		else block_ptr = block_ptr->prev;

		if (block_ptr)
		{
			desc.addr = ((const char*)block_ptr) + sizeof(*block_ptr);
			desc.block_size = block_ptr->end_ptr - desc.addr;
			return block_ptr;
		}
		return NULL;
	}

	MemoryContainer(const char* namestr) : Inherited(namestr)
	{
		data_block_ = NULL;
	}
	virtual ~MemoryContainer()
	{
		DataBlock *block_ptr, *prev; 
		block_ptr = data_block_;
		while (block_ptr)
		{
			prev = block_ptr->prev;
			free(block_ptr);
			block_ptr = prev;
		}
		data_block_ = NULL;
		MemoryCounter::getSingleton().unregist((AllocatorCounterItem*)this);
	}

	inline MemoryContainer& operator = (const MemoryContainer &rhs)
	{
		Inherited::operator=(rhs);
		data_block_ = rhs.data_block_;	
		return *this;
	}
//public:
//#ifdef _MEMORY_TRACE_	
//	virtual int Log(char* buf, int num){ return sprintf(buf,"alloc total:%d,used:%d",alloc_total_,used_count); }
//#endif
private:
	MemoryContainer(const MemoryContainer &rhs);
};

#endif	//end _BUFF_ALLOCATOR_H_
