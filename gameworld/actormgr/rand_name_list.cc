#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

BaseAllocator RandNameList::alloc_("randnameAlloc");
BaseAllocator RandNameList::list_alloc_("namelist_Alloc");

int RandNameList::CompareFun(const void* i1, const void* i2)
{
	RandNameSortItem* item1 = ((RandNameSortItem*)i1);
	RandNameSortItem* item2 = ((RandNameSortItem*)i2);

	if (*item1 < *item2)
		return -1;
	else if (*item1 > *item2)
		return 1;

	return 0;
}

RandNameList::RandNameList() : name_stream_(&alloc_), user_count_(0),
name_list_(&list_alloc_), name_index_(&list_alloc_), index_(0), loaded_(false)
{
}

RandNameList::~RandNameList()
{

}

int RandNameList::LoadFromFile(const char* fn)
{
	if (name_stream_.loadFromFile(fn) <= 0)
		return 0;
	name_list_.clear();
	name_index_.clear();
	user_count_ = 0;

	const char* sPtr = (const char*)name_stream_.getMemory();
	const char* sTag;

	//跳过 UTF8 文件的头三个字节BOM
	uint8_t* pHead = (uint8_t*)sPtr;

	if (pHead[0] == 0xEF && pHead[1] == 0xBB && pHead[2] == 0xBF)
	{
		sPtr += 3;
	}

	while (*sPtr)
	{
		//跳过行首的空白字符
		while (*sPtr && (unsigned int)*sPtr <= 0x20)
			sPtr++;

		//将名字指针添加到名字列表中
		if (*sPtr)
		{
			if (name_list_.count() >= max_name)
			{
				break;
			}

			RandNameItem item;
			RandNameSortItem sort_item;
			item.name_ = sPtr;
			item.used_ = false;

			int item_idx = name_list_.add(item);
			RandNameItem* item_ptr = name_list_ + item_idx;
			item_ptr->index_ = item_idx;
			sort_item.item_ = item_ptr;
			name_index_.add(sort_item); // 后面统一排序
		}

		//搜索换行符
		sTag = strchr(sPtr, '\n');

		if (sTag)
		{
			if (*(sTag - 1) == '\r')
				*(char*)(sTag - 1) = 0; //把 '\r'也填充0
			*(char*)sTag = 0;
			sTag++;

			//跳过行尾的空白字符
			while (*sTag && (unsigned int)*sTag <= 0x20)
			{
				*(char*)sTag = 0;
				sTag++;
			}

			if (*sTag)
			{
				sPtr = sTag;
			}
		}

		if (NULL == sTag || !(*sTag))
		{
			break;
		}
	}

	index_ = wrand(name_list_.count());

	loaded_ = true;

	// name_index_ 要排序
	if(name_index_.count() > 0)
		qsort(name_index_, name_index_.count(), sizeof(RandNameSortItem), &RandNameList::CompareFun);

	return name_list_.count();
}

void RandNameList::SaveToFile(const char* fn)
{
	if (!loaded_) return;

	stream::MemoryStream ms(NULL);;

	for (int i = 0; i < name_list_.count(); i++)
	{
		if (!name_list_[i].used_)
		{
			ms.write(name_list_[i].name_, strlen(name_list_[i].name_));
			ms.write(("\r\n"), 2);
		}
	}

	ms.saveToFile(fn);

	OutputMsg(rmError, "save rand name file ok!%s", fn);
}

const char* RandNameList::GetName()
{
	const char* result = NULL;

	while (true)
	{
		//如果已经用完了列表的一轮,则看看是否还有未被使用的名字,有的话再继续一轮
		if (index_ >= name_list_.count())
		{
			if (name_list_.count() - user_count_ <= 0) //无名字可用
			{
				return NULL;
			}

			index_ = 0;
		}

		if (!name_list_[index_].used_)   //此名字没被使用
		{
			result = name_list_[index_].name_;
			index_++;
			break;
		}

		index_++;
	}

	return result;
}

void RandNameList::UseName(const char* name)
{
	RandNameSortItem sort_item;
	RandNameItem item;
	item.name_ = name;
	sort_item.item_ = &item;
	int idx = name_index_.find(sort_item);

	if (idx >= 0)
	{
		user_count_++;
		sort_item = name_index_[idx];
		sort_item.item_->used_ = true;
	}
}

