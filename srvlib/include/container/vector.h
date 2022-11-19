#ifndef _VECTOR_H_
#define _VECTOR_H_

/******************************************************************
 *
 *	类std::vector 的动态数组类，封装了部分接口，也尽量与std::vector
 * 接近.
 * 注意：可指定最小的内存数量，默认是16，每次扩展是翻倍
 *
 *****************************************************************/
#include <assert.h>
#include "memory/base_allocator.hpp"

namespace container
{
template <typename T, int ONE_TIME_NUM = 16>
class Vector
{
protected:
	T*	data_ptr_;
	int	max_size_;
	int	count_;
	BaseAllocator* alloc;
public:
	Vector(BaseAllocator* alloc = NULL)
	{
		data_ptr_ = NULL;
		max_size_ = 0;
		count_ = 0;
		this->alloc = alloc;
	}

	virtual ~Vector()
	{
		empty();
	}

	inline int count() const
	{
		return count_;
	}
	inline int size() const
	{
		return count_;
	}
	inline int max_size() const
	{
		return max_size_;
	}

	void insert(const int index, const T& data)
	{
		assert(index > -1 && index <= count_);

		if (count_ >= max_size_)
			reserve((max_size_ > 0) ? max_size_ * 2 : ONE_TIME_NUM);

		if (index < count_)
		{
			memmove(data_ptr_ + index + 1, data_ptr_ + index, sizeof(T) * (count_ - index));
		}

		data_ptr_[index] = data;
		count_++;
	}
	int add(const T& data)
	{
		if (count_ >= max_size_)
			reserve((max_size_ > 0) ? max_size_ * 2 : ONE_TIME_NUM);

		memcpy(data_ptr_ + count_, &data, sizeof(data));
		count_++;
		return count_ - 1;
	}

	int push_back(const T& data)
	{
		return add(data);
	}

	inline T& get(const int index) const
	{
		assert(index > -1 && index < count_);
		return data_ptr_[index];
	}

	inline void set(const int index, const T& item)
	{
		assert(index > -1 && index < count_);
		data_ptr_[index] = item;
	}
	int index(const T& data) const
	{
		int i;

		for (i = count_ - 1; i > -1; --i)
		{
			if (data_ptr_[i] == data)
			{
				return i;
			}
		}

		return -1;
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
			if (alloc) alloc->FreeBuffer(data_ptr_);
			else free(data_ptr_);

			data_ptr_ = NULL;
		}
	}
	inline void clear()
	{
		count_ = 0;
	}
	inline void trunc(const int count)
	{
		assert(count > -1 && count <= max_size_);
		count_ = count;
	}
	virtual void reserve(int count)
	{
		if (count > count_ && count != max_size_)
		{
			max_size_ = count;

			if (alloc)
			{
				data_ptr_ = (T*) alloc->ReAllocBuffer(data_ptr_, sizeof(T) * count);
			}
			else
			{
				data_ptr_ = (T*)realloc(data_ptr_, sizeof(T) * count);
			}
		}
	}
	inline void addList(const Vector<T>& list)
	{
		addArray((T*)list, list.count_);
	}
	inline void addArray(T* data, int length)
	{
		if (count_ + length > max_size_)
			reserve(count_ + length);

		memcpy(data_ptr_ + count_, data, length * sizeof(T));
		count_ += length;
	}
	inline int push(const T& data)
	{
		return add(data);
	}
	inline T pop()
	{
		if (count_ > 0)
		{
			count_--;
			return data_ptr_[count_];
		}

		throw "stack was empty";
	}
	inline operator T* () const
	{
		return data_ptr_;
	}
};
};


#endif

