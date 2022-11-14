#ifndef _RAND_NAME_LIST_H_
#define _RAND_NAME_LIST_H_

#include <string.h>

using namespace container;

typedef struct
{
	const char* name_;
	bool used_;
	int index_;
} RandNameItem;

struct RandNameSortItem
{
	RandNameItem* item_;

	//重载不等判断的运算符
	inline bool operator != (const RandNameSortItem& data) const
	{
		return strcmp(item_->name_, data.item_->name_) != 0;
	}
	inline bool operator > (const RandNameSortItem& data) const
	{
		return strcmp(item_->name_, data.item_->name_) > 0;
	}
	inline bool operator < (const RandNameSortItem& data) const
	{
		return strcmp(item_->name_, data.item_->name_) < 0;
	}
};

class RandNameList
{
	const static int max_name = 20000;
public:
	RandNameList();
	~RandNameList();

	const char* GetName();

	int LoadFromFile(const char* fn);

	void SaveToFile(const char* fn);

	void UseName(const char* name);

	static int CompareFun(const void* i1, const void* i2);
protected:
	stream::MemoryStream		name_stream_;
	int							user_count_;	// 已经被使用的名字数量统计
	Vector<RandNameItem, max_name>			name_list_;
	BinaryList<RandNameSortItem, max_name>	name_index_;
	int							index_;
	bool						loaded_;

	static BaseAllocator		alloc_;
	static BaseAllocator		list_alloc_;
};

#endif


