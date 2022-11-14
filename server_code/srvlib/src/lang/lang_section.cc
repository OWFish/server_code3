#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include "_ast.h"
#include "bzhash.h"
#include "memory/base_allocator.hpp"
#include "memory/memory_container.hpp"
#include "container/bz_hash_table.h"
#include "container/str_hash_table.h"
#include "lang/lang_section.h"
#include <new>

static void* allocFromAllocator(MemoryContainer<char>* allocator, void* p, size_t s)
{
	if (s > 0)
	{
		size_t* block, *oldBlock = NULL;

		if (p)
		{
			oldBlock = (size_t*)p;
			oldBlock--;

			//内存块长度足够则直接返回
			if (*oldBlock >= s)
				return p;
		}

		block = (size_t*)allocator->AllocBuffer(s + sizeof(*block));
		*block = s;

		if (oldBlock)
		{
			memcpy(block + 1, oldBlock + 1, *oldBlock);
			//MemoryContainer<char> 没有提供释放内存的功能
		}

		return block + 1;
	}

	//MemoryContainer<char> 没有提供释放内存的功能
	return NULL;
}

LangSection::LangSection()
{
	alloctor_ptr_ = NULL;
	type_ = eInvalid;
	data_.str_ = NULL;
}

LangSection::LangSection(MemoryContainer<char>* alloc)
{
	alloctor_ptr_ = alloc;
	type_ = eInvalid;
	data_.str_ = NULL;
}

LangSection::~LangSection()
{
	clear();
}

LangSection* LangSection::getSection(const char* sName)
{
	if (type_ == ePacket)
	{
		return data_.pack_->get(sName);
	}

	return NULL;
}

void LangSection::setText(const char* str)
{
	clear();
	type_ = eText;
	size_t len = sizeof(*str) * (strlen(str) + 1);
	data_.str_ = (char*)Realloc(NULL, len);
	memcpy(data_.str_, str, len);
	data_.str_[len - 1] = 0;
}

void LangSection::setPacket(size_t len)
{
	clear();
	data_.pack_ = (LangSectionTable*)Realloc(NULL, sizeof(*data_.pack_));
	new(data_.pack_)LangSectionTable(len * 8);
	type_ = ePacket;
}

LangSection* LangSection::addSection(const char* name)
{
	if (type_ != ePacket)
		return NULL;

	LangSection* s = data_.pack_->get(name);

	if (!s)
	{
		s = data_.pack_->put(name);
		s->alloctor_ptr_ = alloctor_ptr_;
	}

	return s;
}

void LangSection::clear()
{
	if (type_ == eText)
	{
		Realloc(data_.str_, 0);
		data_.str_ = NULL;
	}
	else
	{
		if (data_.pack_)
		{
			data_.pack_->~LangSectionTable();
			Realloc(data_.pack_, 0);
			data_.pack_ = NULL;
		}
	}

	type_ = eInvalid;
}

void* LangSection::Realloc(void* p, size_t s)
{
	return allocFromAllocator(alloctor_ptr_, p, s);
}


LangSectionTable::LangSectionTable(size_t len)
	: Inherited(len)
{
}

LangSectionTable::~LangSectionTable()
{
	clear();
}



