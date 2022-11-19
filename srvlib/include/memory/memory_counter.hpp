#ifndef _MEMORY_COUNTER_H_
#define _MEMORY_COUNTER_H_

/************************************************************************
*                          内存分配统计
* 每个用于内存分配的类最好都继承这个，并实现接口，好方便内存使用量的统计
* 可通过宏定义_MEMORY_TRACE_ 开关
***********************************************************************/
#include "os_def.h"
#include "share_util.h"
#include <vector>
#ifdef _MEMORY_TRACE_

template <typename T, int ONE_TIME_NUM = 16>
class MemoryItemList
{
protected:
	T*	data_ptr_;
	int	max_size_;
	int	count_;
public:
	MemoryItemList()
	{
		data_ptr_ = NULL;
		max_size_ = 0;
		count_ = 0;
	}

	virtual ~MemoryItemList()
	{
		empty();
	}

	inline int count() const
	{
		return count_;
	}

	int add(const T& data)
	{
		if (count_ >= max_size_)
			reserve((max_size_ > 0) ? max_size_ * 2 : ONE_TIME_NUM);

		memcpy(data_ptr_ + count_, &data, sizeof(data));
		count_++;
		return count_ - 1;
	}

	void remove(const int index)
	{
		assert(index > -1 && index < count_);
		remove(index, 1);
	}
	void remove(const int index, const int count)
	{
		assert(index + count <= count_);

		if (count > 0)
		{
			memmove(data_ptr_ + index, data_ptr_ + index + count, sizeof(data_ptr_[0]) * (count_ - index - count));
			count_ -= count;
		}
	}
	virtual void empty()
	{
		clear();
		max_size_ = 0;

		if (data_ptr_)
		{
			free(data_ptr_);
			data_ptr_ = NULL;
		}
	}
	inline void clear()
	{
		count_ = 0;
	}
	virtual void reserve(int count)
	{
		if (count > count_ && count != max_size_)
		{
			max_size_ = count;
			data_ptr_ = (T*)realloc(data_ptr_, sizeof(T) * count);
		}
	}
	inline operator T* () const
	{
		return data_ptr_;
	}
};

class MemoryCounter;
class AllocatorCounterItem
{
	friend class MemoryCounter;
public:
	enum
	{
	    MAX_NAME_LENGTH = 32,			// 最大描述字符串长度
	};

	AllocatorCounterItem(const char* namestr);


	virtual ~AllocatorCounterItem();


	const char* GetName()
	{
		return name_;
	}

	virtual int Log(char* buf, int num)
	{
		const char* fmt = "%s, alloc total:%llu, used:%llu %s";
		const char* tip  = GetTip(alloc_total_, used_count_);
		return SNPRINTFA(buf, num, fmt, name_, alloc_total_, used_count_, tip);
	}

	size_t GetAllocCount()
	{
		return alloc_total_;
	}

	const char* GetTip(size_t s1, size_t s2 = 0)
	{
		const char* tip  = "";

		if (s1 > largeCount || s2 > largeCount)
		{
			tip = "*****";
		}
		else if (s1 > midCount || s2 > midCount)
		{
			tip = "**";
		}

		return tip;
	}

public:
	static const size_t largeCount = 100 * 1024 * 1024;
	static const size_t midCount = 10 * 1024 * 1024;
protected:
	size_t				alloc_total_;	//分配的总数
	size_t				free_count_;	//空闲
	size_t				used_count_;	//正在使用的内存量
	char				name_[MAX_NAME_LENGTH];		//
};

class SimpleAllocCounter : public AllocatorCounterItem
{
	static const int MAX_COUNTER = 8;
public:
	SimpleAllocCounter(const char* name) : AllocatorCounterItem(name)
	{
		memset(counter_, 0, sizeof(counter_));
	}

	size_t counter(size_t s, int idx)
	{
		assert(idx >= 0 && idx < MAX_COUNTER);
		counter_[idx] += s;
		alloc_total_ += s;
		return counter_[idx];
	}

	virtual int Log(char* buf, int num)
	{
		const char* fmt = "%d, total:%llu %s\r\n";
		int ret = 0;

		for (int i = 0; i < MAX_COUNTER; i++)
		{
			size_t c = counter_[i];
			if (c <= 0) continue;

			const char* tip  = GetTip(c);

			ret += SNPRINTFA(buf + ret, num - ret, fmt, i, c, tip);
		}

		return ret;
	}
private:
	size_t counter_[MAX_COUNTER];
};

class MemoryCounter
{
public:
	MemoryCounter();

	static MemoryCounter& getSingleton()
	{
		static MemoryCounter mgr;
		return mgr;
	}

	~MemoryCounter();

	void clear()
	{
		allocator_list.clear();
		allocator_list.empty();
	}

	/*
	* Comments:添加一个统计项
	* @Return void:
	*/
	void regist(AllocatorCounterItem* item);

	/*
	* Comments: 移除一个统计项
	* Param CSingleObjectAllocatorStat * stat:
	* @Return void:
	*/
	void unregist(AllocatorCounterItem* item);

	/*
	* Comments: 统计信息到日志
	* @Return void:
	*/
	void logToFile();

private:
	MemoryItemList<AllocatorCounterItem*, 2048> allocator_list;
};

#else	//ifdef _MEMORY_TRACE_

class AllocatorCounterItem
{
public:
	AllocatorCounterItem(const char* namestr)
	{

	}
};

#endif	//ifdef _MEMORY_TRACE_

#endif	//end _ONCE_ALLOCATOR_H_
