extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "lundump.h"
#include "lstate.h"
}
#include "share_util.h"
#include "luabase/clvariant.h"

typedef int (*compfn)(const void*, const void*);

int compare(CLVariant** v1, CLVariant** v2)
{
	return (*v1)->compareName(*v2);
}

const char* CLVariant::loadFromMemory(const char* ptr, size_t& size, size_t* count)
{
	const int MIN_SIZE = 9;	// sizeof(char)+sizeof(name_id_);
	//内存长度小于MIN_SIZE字节，不能读取
	if (size < MIN_SIZE)
	{
		if (count) *count = 0;

		return ptr;
	}

	clear();
	//读取类型
	type_ = *(unsigned char*)ptr;
	ptr += sizeof(unsigned char);
	size -= sizeof(unsigned char);
	//读取名称
	name_id_ = *(int64_t*)ptr;
	ptr += sizeof(name_id_);
	size -= sizeof(name_id_);

	//依据类型读取数据
	switch (type_)
	{
	case vNumber:
		if (size >= sizeof(data_.n))
		{
			data_.n = *(double*)ptr;
			ptr += sizeof(double);
			size -= sizeof(double);
		}
		else
		{
			type_ = vNil;
		}

		break;

	case vStr:
		if (size >= sizeof(unsigned int))
		{
			unsigned int len = *(unsigned int*)ptr;
			ptr += sizeof(unsigned int);
			size -= sizeof(unsigned int);

			if (len > 0 && size >= len + 1)
			{
				operator = ((const char*)ptr);
				ptr += len + 1;
				size -= len + 1;
			}
		}
		else
		{
			type_ = vNil;
		}
		break;

	case vStruct:
		if (size >= sizeof(unsigned int))
		{
			unsigned int len = *(unsigned int*)ptr;
			ptr += sizeof(unsigned int);
			size -= sizeof(unsigned int);

			if (len > 0 && size >= MIN_SIZE)
			{
				data_.a.list = (CLVariant**)calloc(len, sizeof(*data_.a.list));

				for (int i = 0; i < (int)len; ++i)
				{
					size_t n = 0;
					data_.a.list[i] = new CLVariant();
					ptr = data_.a.list[i]->loadFromMemory(ptr, size, &n);

					if (n <= 0)
						break;

					data_.a.len++;

					if (count) *count += n;
				}

				qsort(data_.a.list, data_.a.len, sizeof(CLVariant*), (compfn)compare);
			}
		}
		else
		{
			type_ = vNil;
		}

		break;
	}

	//增加读取的变量数据量
	if (count && type_ != vNil)
		*count += 1;//不能用*pCount++，意义不一样的，*pCount++表示 *(pCount++)。

	return ptr;
}

size_t CLVariant::saveToMemory(char* ptr, size_t size, bool& memory)
{
	size_t reqSize = 0;

	//计算存储所需的空间
	switch (type_)
	{
	case vNil:
		break;

	case vNumber:
		reqSize = 1 + sizeof(name_id_) + sizeof(data_.n);
		break;

	case vStr:
		reqSize = 1 + sizeof(name_id_) + sizeof(data_.s.len) + ((data_.s.len > 0) ? data_.s.len + 1 : 0);
		break;

	case vStruct:
		reqSize = 1 + sizeof(name_id_) + sizeof(data_.a.len);

		if (size == 0 && data_.a.len > 0) //仅当参数size为0时用于计算保存变量所需的内存字节长度
		{
			for (int i = data_.a.len - 1; i > -1; --i)
			{
				reqSize += data_.a.list[i]->saveToMemory(NULL, 0, memory);
			}
		}

		break;
	}

	if (size <= 0) return reqSize;	// 只是计算大小

	//没有任何数据可以写入
	if (reqSize <= 0 || ptr == NULL)
	{
		memory = true;
		return 0;
	}

	if (reqSize > size)
	{
		memory = false;	// 由于空间不够而返回
		return 0;
	}

	//仅在剩余内存空间满足所需空间长度的时候才书写内容
	//写入类型
	*(unsigned char*)ptr = (unsigned char)type_;
	ptr += sizeof(unsigned char);
	size -= sizeof(unsigned char);
	//写入名称
	*(int64_t*)ptr = name_id_;
	ptr += sizeof(name_id_);
	size -= sizeof(name_id_);

	//写入数据
	switch (type_)
	{
	case vNumber:
		//写入值
		*(double*)ptr = data_.n;
		ptr += sizeof(double);
		size -= sizeof(double);
		break;

	case vStr:
		//写入字符串长度
		*(unsigned int*)ptr = data_.s.len;
		ptr += sizeof(unsigned int);
		size -= sizeof(unsigned int);

		//写入字符串内容
		if (data_.s.len > 0)
		{
			memcpy(ptr, data_.s.str, data_.s.len + 1);
			ptr += data_.s.len + 1;
			size -= data_.s.len + 1;
		}

		break;

	case vStruct:
		//写入成员数量
		{
			*(unsigned int*)ptr = (unsigned int)packedlen();
			ptr += sizeof(unsigned int);
			size -= sizeof(unsigned int);

			//循环写入成员内容
			if (data_.a.len > 0)
			{
				for (int i = data_.a.len - 1; i > -1; --i)
				{
					size_t nb = data_.a.list[i]->saveToMemory(ptr, size, memory);

					if (!memory)
					{
						return reqSize;	// 空间不够，结束了
					}

					reqSize += nb;
					ptr += nb;
					size -= nb;

					if (size == 0)
					{
						break;
					}
				}
			}
		}
		break;
	}

	return reqSize;
}
