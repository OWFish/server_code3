#ifndef _STATIC_HASH_TABLE_H_
#define _STATIC_HASH_TABLE_H_

/************************
 * 一个封装了暴雪hash算法的hashtable
 * 表长度是固定的，不能动态增长，同时不提供删除的接口
 * 为提供更快的性能
*************************/

namespace container
{
template <typename T, int MAX_NODE_NUM>
class StaticHashTable
{
protected:
	class HashNode
	{
	public:
		bool exists_;		// 是否保存有数据
		uint64_t key_;			// key
		T value_;			// 数据值
	};

	size_t size_;
	size_t out_count_;
	static const size_t MAX_SIZE_ = MAX_NODE_NUM * 2;
	HashNode ptr_[MAX_SIZE_];
	//Vector<HashNode, MAX_NODE_NUM>	data_;
public:
	StaticHashTable() : size_(0), out_count_(0)
	{
		//data_.reserve(MAX_SIZE_);
		//ptr_ = data_;
		clear();
	}
	
	virtual ~StaticHashTable()
	{
		clear();
	}

	// 清空哈希表
	void clear()
	{
		size_ = 0;
		out_count_ = 0;
		memset(ptr_, 0, MAX_SIZE_ * sizeof(HashNode));
	}

	inline size_t count() const { return size_; }

public:
	//通过键查找值
	inline T* get(uint64_t key)
	{
		int idx = getIndex(key);
		return (idx >= 0) ? &ptr_[idx].value_ : NULL;
	}
	
	inline T* put(uint64_t key, T& data)
	{
		if (size_ >= MAX_NODE_NUM) return NULL;
		unsigned int start = key % MAX_NODE_NUM, idx = start;
		do 
		{
			HashNode *node = ptr_ + idx;
			//如果该位置没有值，则设置到该位置，否则向后找到一个空位置
			if (!node->exists_)
			{
				node->exists_ = true;
				node->key_ = key;
				size_++;
				node->value_ = data;

				if (idx >= MAX_NODE_NUM)
					++out_count_;
				return &(node->value_);
			}
#ifdef _DEBUG
			else if (node->key_ == key)
			{
				//调用者重复添加，或者确实出现错误！
				//DebugBreak();

			}
#endif
			++idx;
		}
		while (idx < MAX_SIZE_);

		return NULL;
	}
	
	inline bool remove(uint64_t key)
	{
		int idx = getIndex(key);

		if (idx < 0) 
			return false;

		ptr_[idx].exists_ = false;
		--size_;
		if (idx >= MAX_NODE_NUM)
			--out_count_;

		// 往后寻找一个移上来替换
		int start = idx;
		++idx;
		while (ptr_[idx].exists_ && idx < (int)MAX_SIZE_)
		{
			if (start >= MAX_NODE_NUM)
			{
				int cnt = (int)out_count_ - (start - MAX_NODE_NUM);
				if (cnt > 0)
				{
					memmove(ptr_ + start, ptr_ + idx, cnt * sizeof(HashNode));
					// 整块内存往前移动了一格,原来最后的那个格就可以设为false
					ptr_[MAX_NODE_NUM + out_count_].exists_ = false;	
				}
				break;
			}

			int key_idx = ptr_[idx].key_ % MAX_NODE_NUM;

			if (key_idx <= start)
			{
				ptr_[start] = ptr_[idx];				
				ptr_[idx].exists_ = false;
				start = idx;

				if (idx >= MAX_NODE_NUM) 
					-- out_count_;
			}
			++idx;
		}		
		return true;
	}

	// 获取键在表中的索引
	int getIndex(uint64_t key) const
	{
		size_t start = key % MAX_NODE_NUM, idx = start; 
		while (ptr_[idx].exists_ && idx < MAX_SIZE_) 
		{ 
			if (ptr_[idx].key_ == key) 
				return (int)idx; 
			else 
				++idx;
		}
		return -1;
	}

	void update(uint64_t key, const T& data)
	{
		int idx = getIndex(key);
		if (idx >= 0)
		{
			ptr_[idx].value_ = data;
		}
	}

};

}

#endif
