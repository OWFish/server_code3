#ifndef _BUFF_ALLOCATOR_H_
#define _BUFF_ALLOCATOR_H_

/************************************************************************
* һ���Ե��ڴ������
* ������һ�η����ڴ��ֱ������������ͷ��ڴ�ĵط����������ļ��Ķ�ȡ
* ������������ĺô��ǣ����ṩ�ͷ��ڴ�ĺ�������˲���Ҫһ�����ڴ��ֹ��ͷţ�
* �����ɷ�����һ���ͷ�
************************************************************************/


#include "os_def.h"
#include "memory_counter.hpp"

template <typename T, int ONE_TIME_COUNT = 1024>
class MemoryContainer : public AllocatorCounterItem
{
public:
	typedef AllocatorCounterItem Inherited;

	//�ڴ�������ṹ�����ڲ�ѯ�ڴ����Ϣ
	struct DataBlockDesc
	{
		const char* addr;//�ڴ��ָ���ַ
		size_t block_size;		  //�ڴ���С
	};

private:
	//�ڴ������ڵ�
	struct DataBlock
	{
		T*			free_ptr;	//ָ����еĶ���
		T*			end_ptr;	//ָ������ڴ��Ľ���
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
		//���Դӵ�ǰ�ڴ��������nCount�Ķ�������ڴ����û���㹻�Ķ�������֮ǰ���ڴ���в����Ƿ�����㹻�Ŀ��ж���
		if ( !block_ptr || size_t(block_ptr->end_ptr - block_ptr->free_ptr) < count )
		{
			//��֮ǰ���ڴ���в����Ƿ�����㹻�Ŀ��ж���
			while (block_ptr && (block_ptr = block_ptr->prev))
			{
				if ( size_t(block_ptr->end_ptr - block_ptr->free_ptr) >= count )
					break;
			}
			//��������ڴ���ж�û���㹻�Ķ������������ڴ��
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
		//���ض���ָ��
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

	//��ȡ�ڴ������
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
	* Comments: ö���ڴ��������Ϣ
	* Param LPCVOID lpEnumKey: �ϴ�ö�ٵķ���ֵ����Ϊö����һ�������ݣ���һ��ö�ٴ�ֵ����ΪNULL��
	* Param DataBlockDesc & desc: ���ڱ����ڴ�������Ķ���
	* @Return LPCVOID: ����һ���ڴ��ö��keyָ�룬���ڽ����´�ö�١��������ֵΪNULL���ʾö�ٽ���
	*
	* ���ע���ö���ڴ�������Ĳ����ǵ�����еģ���һ����ö�ٵ��ڴ������Ϊ���һ���ڴ���������
	*
	* ���ʾ�������-------------------------------------------------
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
