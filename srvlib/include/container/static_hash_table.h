#ifndef _STATIC_HASH_TABLE_H_
#define _STATIC_HASH_TABLE_H_

/************************
 * һ����װ�˱�ѩhash�㷨��hashtable
 * �����ǹ̶��ģ����ܶ�̬������ͬʱ���ṩɾ���Ľӿ�
 * Ϊ�ṩ���������
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
		bool exists_;		// �Ƿ񱣴�������
		uint64_t key_;			// key
		T value_;			// ����ֵ
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

	// ��չ�ϣ��
	void clear()
	{
		size_ = 0;
		out_count_ = 0;
		memset(ptr_, 0, MAX_SIZE_ * sizeof(HashNode));
	}

	inline size_t count() const { return size_; }

public:
	//ͨ��������ֵ
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
			//�����λ��û��ֵ�������õ���λ�ã���������ҵ�һ����λ��
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
				//�������ظ���ӣ�����ȷʵ���ִ���
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

		// ����Ѱ��һ���������滻
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
					// �����ڴ���ǰ�ƶ���һ��,ԭ�������Ǹ���Ϳ�����Ϊfalse
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

	// ��ȡ���ڱ��е�����
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
