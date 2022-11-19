#ifndef _BZ_HASH_TABLE_H_
#define _BZ_HASH_TABLE_H_
/************************
 * 一个封装了暴雪hash算法的hashtable
 * 表长度是固定的，不能动态增长，同时不提供删除的接口
 * 为提供更快的性能
*************************/
#include "memory/base_allocator.hpp"
#include "bzhash.h"

template <typename T>
class BZHashTable
{
public:
	BZHashTable(size_t len)
	{
		assert(len > 0);

		max_size_ = len;
		data_ = NULL;
		size_ = 0;
	}
	
	virtual ~BZHashTable()
	{
		clear();
	}

	// 清空哈希表
	void clear()
	{
		if (size_ > 0)
		{
			for (int i = (int)(max_size_ - 1); i > -1; --i)
			{
				if (data_[i].exists)
				{
					data_[i].value.~T();
				}
			}
		}

		if (data_) realloc(data_, 0);
		data_ = NULL;
		size_ = 0;
	}

	inline size_t count() const { return size_; }
protected:
	template <typename TA>
	class HashNode
	{
	public:
		bool	exists;		// 是否保存有数据
		unsigned int hash1;	//哈希值1
		unsigned int hash2;	//哈希值2
		unsigned int hash3;	//哈希值3
		TA value;			//数据值
	};

	typedef HashNode<T> NodeType;
public:
	//通过键查找值
	inline T* get(const char* key)
	{
		int idx = getIndex(key);
		return (idx >= 0) ? &data_[idx].value : NULL;
	}
	//通过键查找值
	inline const T* get(const char* key) const
	{
		int idx = getIndex(key);
		return (idx >= 0) ? &data_[idx].value : NULL;
	}
	
	inline T* put(const char* key)
	{
		if (size_ >= max_size_)
		{
#ifdef _DEBUG
			DbgAssert(false);
#endif
			return NULL; // no free
		}
		if (!data_)
		{
			data_ = (HashNode<T> *)realloc(NULL, sizeof(HashNode<T>) * max_size_);
			for (size_t i = 0; i < max_size_; ++i)
			{
				data_[i].exists = false;
			}
		}

		unsigned int hash1, hash2, hash3, idx, start;
		hash1 = ::bzhashstr(key, 0);
		hash2 = ::bzhashstr(key, 1);
		hash3 = ::bzhashstr(key, 2);
		start = idx = hash1 % (unsigned int)max_size_;
		do 
		{
			NodeType *node = data_ + idx;
			//如果该位置没有值，则设置到该位置，否则向后找到一个空位置
			if (!node->exists)
			{
				node->exists = true;
				node->hash1 = hash1;
				node->hash2 = hash2;
				node->hash3 = hash3;
				size_++;
				new (&node->value)T();
				return &node->value;
			}
#ifdef _DEBUG
			else if (node->hash1 == hash1 && node->hash2 == hash2 && node->hash3 == hash3)
			{
				//调用者重复添加，或者确实出现错误！
				DebugBreak();
			}
#endif
			idx = (idx + 1) % (unsigned int)max_size_;
		} 
		while (start != idx);

		return NULL;
	}
	
	//获取键在表中的索引
	int getIndex(const char* sKey) const
	{
		if (!data_) return -1;

		unsigned int hash1, hash2, hash3;

		hash1 = ::bzhashstr(sKey, 0);
		hash2 = ::bzhashstr(sKey, 1);
		hash3 = ::bzhashstr(sKey, 2);

		size_t start = hash1 % max_size_, idx = start; 

		while (data_[idx].exists) 
		{ 
			if (data_[idx].hash2 == hash2 && data_[idx].hash3 == hash3) 
				return (int)idx; 
			else 
				idx = (idx + 1) % max_size_; 

			if (idx == start) 
				break; 
		} 

		return -1;
	}

protected:
	//内存申请函数，作用与c函数中的realloc实现相同，实现申请、扩展以及释放内存
	virtual void* realloc(void* p, size_t s)
	{
#ifdef _MSC_VER
		static BaseAllocator alloc("bzhashtable");
		if (s > 0)
		{
			return alloc.ReAllocBuffer(p, s);
		}
		else
		{
			if (p)
			{
				alloc.FreeBuffer(p);
			}
			return NULL;
		}
		return alloc.ReAllocBuffer(p, s);
#else
		return ::realloc(p, s);
#endif
	}
protected:
	size_t		max_size_;
	size_t		size_;
	HashNode<T>	*data_;	//哈希表
};

#endif
