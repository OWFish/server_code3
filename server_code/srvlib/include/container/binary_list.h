#ifndef _BINARY_LIST_H_
#define _BINARY_LIST_H_

/******************************************************************
 *
 *	封装二分法，实现查找，插入，删除等操作
 *
 *****************************************************************/
#include <assert.h>
#include "container/vector.h"
#include "container/static_array_list.h"

namespace container
{
template <typename T, int ONE_TIME_NUM = 16>
class BinaryList: public Vector<T, ONE_TIME_NUM>
{
public:
	BinaryList(BaseAllocator* alloc = NULL): Vector<T, ONE_TIME_NUM>(alloc)
	{
	}

	virtual ~BinaryList()
	{
	}

	int add_item(const T& item)
	{
		//id加到列表中
		int low = 0;
		int high = this->count_ - 1;

		while (low <= high)
		{
			int mid = ((unsigned)(low + high)) >> 1;
			const T& mid_item = this->data_ptr_[mid];

			if (mid_item < item)
				low = mid + 1;
			else
				high = mid - 1;
		}

		this->insert(low, item);
		return low;
	}

	void remove_item(const T& item, bool del_repeat = false)
	{
		int idx = find(item);

		if (idx < 0) return;

		if (del_repeat)
		{
			this->remove(idx);
			return;
		}

		int endidx = idx;

		for (--idx; idx >= 0; idx--)
		{
			if (this->data_ptr_[idx] != item) break;
		}

		for (++endidx; endidx < this->count_; endidx++)
		{
			if (this->data_ptr_[endidx] != item) break;
		}

		this->remove(idx + 1, endidx - 1 - idx);
	}

	int find(const T& item)
	{
		int low = 0;
		int high = this->count_ - 1;

		while (low <= high)
		{
			int mid = ((unsigned int)(low + high)) >> 1;
			const T& mid_item = this->data_ptr_[mid];

			if (mid_item < item)
				low = mid + 1;
			else if (mid_item > item)
				high = mid - 1;
			else
				return mid; // key found
		}

		return -1;   // key not found.
	}
};
};


namespace container
{
template <typename T, int ONE_TIME_NUM = 16>
class StaticBinaryList : public StaticArrayList<T, ONE_TIME_NUM>
{
public:
	StaticBinaryList()
	{
	}

	virtual ~StaticBinaryList()
	{
	}

	int add_item(const T& item)
	{
		//id加到列表中
		int low = 0;
		int high = this->count_ - 1;

		while (low <= high)
		{
			int mid = ((unsigned)(low + high)) >> 1;
			const T& mid_item = this->data_ptr_[mid];

			if (mid_item < item)
				low = mid + 1;
			else
				high = mid - 1;
		}

		this->insert(low, item);
		return low;
	}

	void remove_item(const T& item, bool del_repeat = false)
	{
		int idx = find(item);

		if (idx < 0) return;

		if (del_repeat)
		{
			this->remove(idx);
			return;
		}

		int endidx = idx;

		for (--idx; idx >= 0; idx--)
		{
			if (this->data_ptr_[idx] != item) break;
		}

		for (++endidx; endidx < this->count_; endidx++)
		{
			if (this->data_ptr_[endidx] != item) break;
		}

		this->remove(idx + 1, endidx - 1 - idx);
	}

	int find(const T& item)
	{
		int low = 0;
		int high = this->count_ - 1;

		while (low <= high)
		{
			int mid = ((unsigned int)(low + high)) >> 1;
			const T& mid_item = this->data_ptr_[mid];

			if (mid_item < item)
				low = mid + 1;
			else if (mid_item > item)
				high = mid - 1;
			else
				return mid; // key found
		}

		return -1;   // key not found.
	}
};
};
#endif

