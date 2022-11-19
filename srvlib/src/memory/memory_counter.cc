#include "memory/memory_counter.hpp"

#ifdef _MEMORY_TRACE_

void MemoryCounter::regist(AllocatorCounterItem* item)
{
	allocator_list.add(item);
}

void MemoryCounter::unregist(AllocatorCounterItem* item)
{
	for (int i = allocator_list.count() - 1; i >= 0; --i)
	{
		if (item == allocator_list[i])
		{
			allocator_list.remove(i);
			break;
		}
	}
}

void MemoryCounter::logToFile()
{
	FILE* fp = fopen("memory.txt", "w");

	if (!fp) return;

	size_t total = 0, used = 0;
	char buf[1024];

	for (int i = 0; i < allocator_list.count(); i++)
	{
		allocator_list[i]->Log(buf, sizeof(buf) - 1);
		//记录到文件中
		printf("%s\n", buf);
		fputs(buf, fp);
		fputs("\n", fp);

		total += allocator_list[i]->alloc_total_;
		used += allocator_list[i]->used_count_;
	}

	const char* fmt = "all: alloc total:%llu, used:%llu";
	SNPRINTFA(buf, sizeof(buf) - 1, fmt, total, used);
	printf("%s\n", buf);
	fputs(buf, fp);
	fputs("\n", fp);

	fclose(fp);
}

MemoryCounter::MemoryCounter()
{
	CheckDate();
}

MemoryCounter::~MemoryCounter()
{
	clear();
}

AllocatorCounterItem::~AllocatorCounterItem()
{
	MemoryCounter::getSingleton().unregist(this);
}

AllocatorCounterItem::AllocatorCounterItem(const char* namestr)
{
	alloc_total_ = 0;
	free_count_ = 0;
	used_count_ = 0;

	if (!namestr)
	{
		name_[0] = 0;
	}
	else
	{
		_STRNCPY_S(name_, namestr, sizeof(name_) - 1);
		name_[sizeof(name_) - 1] = 0;
	}

	MemoryCounter::getSingleton().regist(this);
}

#endif


