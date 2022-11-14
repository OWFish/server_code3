#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"

#include "_ast.h"
#include "stream.h"

using namespace stream;

MemoryStream::MemoryStream(BaseAllocator* alloc) : Inherited(alloc)
{
	mem_ = ptr_ = mem_end_ = end_ptr_ = NULL;
	alloc_count_ = 5 * 1024;
}

MemoryStream::~MemoryStream()
{
	if (mem_)
	{
		alloc_? alloc_->FreeBuffer(mem_) : free(mem_);
		mem_ = NULL;
	}
}

char* MemoryStream::AllocStream(char* ptr, const int size)
{
	if (size == 0 && ptr)
	{
		alloc_ ? alloc_->FreeBuffer(ptr) : free(ptr);
		return NULL;
	}

	return (char*)(alloc_? alloc_->ReAllocBuffer(ptr, size) : realloc(ptr, (int)size));
}

bool MemoryStream::setSize(int tSize)
{
	tSize += alloc_count_;
	size_t offset = ptr_ - mem_;
	size_t dataLen = end_ptr_ - mem_;

	mem_ = AllocStream(mem_, tSize + sizeof(size_t));
	mem_end_ = mem_ + tSize;
	assert(tSize > 0);
	
	ptr_ = mem_ + offset;
	end_ptr_ = mem_ + dataLen;
	return true;
}

int MemoryStream::seek(const int tOffset, const int Origin)
{
	if (Origin == SEEK_SET)
		ptr_ = mem_ + tOffset;
	else if (Origin == SEEK_CUR)
		ptr_ += tOffset;
	else if (Origin == SEEK_END)
		ptr_ = end_ptr_ + tOffset;
	if (ptr_ > end_ptr_)
	{
		ptr_ = end_ptr_;
	}

	return (int)(ptr_ - mem_);
}

int MemoryStream::read(void* lpBuffer, const int tSizeToRead)
{
	size_t nRemain = end_ptr_ - ptr_;
	size_t tReadBytes = tSizeToRead;

	if (nRemain <= 0 || !tReadBytes)
		return 0;

	if (tReadBytes > nRemain)
		tReadBytes = nRemain;

	memcpy(lpBuffer, ptr_, (int)tReadBytes);
	ptr_ += tReadBytes;
	return (int)tReadBytes;
}

int MemoryStream::write(const void* buf, const size_t sizeToWrite)
{
	char* streamend = ptr_ + sizeToWrite;

	if (streamend > mem_end_)
	{
		setSize((int)(streamend - mem_));
	}

	memcpy(ptr_, buf, (int)sizeToWrite);
	ptr_ += sizeToWrite;
	if (ptr_ > end_ptr_)
	{
		end_ptr_ = ptr_;
	}
	if (mem_end_ > ptr_)
	{
		*ptr_ = 0;
	}
	return (int)sizeToWrite;
}

int MemoryStream::loadFromFile(const char* lpFileName)
{
	FileStream stm(lpFileName, FileStream::faRead | FileStream::faShareRead, NULL);

	int filesize = stm.getSize();

	if (filesize > 0)
	{
		setSize(filesize);
		stm.read(mem_, filesize);
		end_ptr_ = mem_ + filesize;
		// 如果是字符串要补0
		if ((mem_end_ - mem_) > filesize)
		{
			mem_[filesize] = 0;
		}
	}

	return filesize;
}

int MemoryStream::saveToFile(const char* lpFileName)
{
	FileStream stm(lpFileName, FileStream::faCreate, NULL);

	return stm.write(mem_, getSize());
}

