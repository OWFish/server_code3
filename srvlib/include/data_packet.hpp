#ifndef _DATA_PACKET_HPP_
#define _DATA_PACKET_HPP_
/***********************************************************************
                        基于内存的数据包读写类

  实现方式与MemoryStream相同，写入数据的时候写入到内存中，如果写入数据的空间超出现有
  内存块长度则会自动增长内存。

  数据包的内存申请时通过内存池对象进行的，以使用更有效率的内存管理。

  ★数据包中的字符串
  数据包含有一种字符串读写机制，包括ANSI字符串以及UNICODE16字符串。将一个字符串写入
  到数据包后其内存结构为：
    [2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]

***********************************************************************/
#include "os_def.h"
#include "data_packet_reader.hpp"

class DataPacket : public DataPacketReader
{
public:
	/* 写入二进制数据
	 * lpBuffer  指向二进制数据内存的指针
	 * dwSize    数据的字节长度
	 */
	inline void writeBuf(const void* buf, size_t size)
	{
		size_t mem_size = end_ptr_ - offset_;

		if (mem_size < size)
		{
			setSize(end_ptr_ - mem_ptr_ + size);
		}

		memcpy(offset_, buf, size);
		offset_ += size;

		//如果读写指针超过长度指针的位置，则调整长度指针为读写指针的位置
		if (offset_ > data_end_)
			data_end_ = offset_;
	}
	/* 写入原子类型数据
	 * bool,char,short,int,__int64,float,double,void*这些数据类型为原子类型
	 */
	template <typename T>
	inline void writeAtom(const T& data)
	{
		size_t mem_size = end_ptr_ - offset_;

		if (mem_size < sizeof(data))
		{
			setSize(end_ptr_ - mem_ptr_ + sizeof(data));
		}

		*(T*)offset_ = data;
		offset_ += sizeof(data);

		//如果读写指针超过长度指针的位置，则调整长度指针为读写指针的位置
		if (offset_ > data_end_)
			data_end_ = offset_;
	}
	inline void writeString(const char* str, size_t len = -1)
	{
		rawWriteStringLen<unsigned short>(str, len);
	}
	inline void writeStringBuf(const char* str, size_t len = -1)
	{
		rawWriteStringLen<unsigned int>(str, len);
	}
	///* 写入UNICODE16字符串数据（字符串长度必须在65536以内，超过65535的部分将不会被写入）
	// * 在字符串之前写入两个字节的字符串长度，且会再字符串末尾写入终止字符
	// * len 如果值为-1，则自动计算str的长度
	// */
	//inline void writeWideString(const char *str, size_t len = -1)
	//{
	//	rawWriteWideStringLen<unsigned short>(str, len);
	//}

public:
	inline void setLength(size_t newLength)
	{
		if (newLength > (size_t)(end_ptr_ - mem_ptr_))
			setSize(newLength);

		data_end_ = mem_ptr_ + newLength;

		if (offset_ > data_end_)
			offset_ = data_end_;
	}
	/* 设置数据包当前读写位置字节偏移量，
	 * 如果新的偏移量比当前内存块长度要大，则函数会与setLength一样进行内存块的扩展操作
	 */
	inline size_t setPosition(size_t newPos)
	{
		size_t mem_size = end_ptr_ - mem_ptr_;

		if (newPos > mem_size)
			setSize(newPos);

		offset_ = mem_ptr_ + newPos;

		//如果读写指针超过长度指针的位置，则调整长度指针为读写指针的位置
		if (offset_ > data_end_)
			data_end_ = offset_;

		return newPos;
	}
	/* 基于当前读写指针偏移位置调整偏移量
	 * nOffsetToAdjust 要调整的偏移量大小，负数则表示向内存开始处调整（降低偏移）
	 * 函数内会限制调整后的偏移位置必须大于等于内存开头，
	 * 如果调整后的便宜超过现有内存长度，则会自动增长内存到欲求调整的位置
	 */
	inline size_t adjustOffset(size_t adjust_offset)
	{
		offset_ += adjust_offset;

		if (offset_ < mem_ptr_)
			offset_ = mem_ptr_;
		else if (offset_ > end_ptr_)
			setSize(offset_ - mem_ptr_);

		if (offset_ > data_end_)
			data_end_ = offset_;

		return offset_ - mem_ptr_;
	}
	inline size_t reserve(size_t newSize)
	{
		size_t Result = end_ptr_ - mem_ptr_;

		if (Result < newSize)
			setSize(newSize);

		return Result;
	}
	/*
	 * 获取当前缓冲长度下的可用字节数
	 */
	inline size_t getAvaliableBufLen()
	{
		return end_ptr_ - offset_;
	}
public:
	/*
	* Comment: 适用于在通过开启预定义宏_DPPACK_MEM_CHK_的情况下，对数据包进行内存越界检查
	* @Return void:
	*/
	inline void _Assert()
	{
#ifdef _DPPACK_MEM_CHK_
		DbgAssert(!end_ptr_ || *(int*)end_ptr_ == 0xCCDDCCEE);
#endif
	}
	/*
	 * 检查引用赋值
	 */
	inline DataPacket& operator = (const DataPacket&)
	{
		//禁止引用赋值！
		assert(false);
	}
public:
	/* 写入原子数据的运算符重载 */
	template <typename T>
	inline DataPacket& operator << (const T& val)
	{
		if (sizeof(val) <= sizeof(int))
			writeAtom<T>(val);
		else writeBuf(&val, sizeof(val));

		return *this;
	}
	inline DataPacket& operator << (const char* val)
	{
		static const char* def = "";
		val ? writeString(val, strlen(val)) : writeString(def, strlen(def));
		return *this;
	}
	inline DataPacket& operator << (char* val)
	{
		static const char* def = "";
		val ? writeString(val, strlen(val)) : writeString(def, strlen(def));
		return *this;
	}

public:
	typedef DataPacketReader Inherited;

	DataPacket()
		: Inherited()
	{
		allocator_ = NULL;
		alloc_count_ = 0;
	}
	DataPacket(const DataPacket&)
	{
		//为了防止将引用赋值给一个对象，此处禁止从另一个对象中构造
		assert(false);
	}
	DataPacket(void* buf, size_t size)
		: Inherited(buf, size)
	{
		data_end_ = mem_ptr_;
		allocator_ = NULL;
		alloc_count_ = 0;
	}
	DataPacket(BaseAllocator* allocator)
		: Inherited()
	{
		allocator_ = allocator;
		alloc_count_ = 0;
	}
	~DataPacket()
	{
		empty();
	}

	// 释放内存
	void empty()
	{
		if (mem_ptr_ && allocator_)
		{
			allocator_->FreeBuffer(mem_ptr_);
			mem_ptr_ = end_ptr_ = offset_ = data_end_ = NULL;
		}
	}

	inline void setAllocSize(int size)
	{
		alloc_count_ = size;
	}
	// 设置分配器
	inline void setAllocator(BaseAllocator* allocator)
	{
		allocator_ = allocator;
	}

	// 用于把字符串按目前的格式写入到一个buff, 返回整个数据的长度
	static int writeString_s(char* buf, int maxLen, const char* str)
	{
		if (buf == NULL || maxLen < 3) return 0;

		if (str == NULL) str = "";

		int strLen = (int)strlen(str);

		int cpyLen = __min(maxLen - 3, strLen);
		unsigned short* tmp = (unsigned short*)buf;
		*tmp = (unsigned short)cpyLen;
		memcpy(buf + 2, str, cpyLen);
		buf[cpyLen + 2] = 0;
		return cpyLen + 3;
	}
protected:
	/*  重新设定数据包内存空间大小  */
	void setSize(size_t newSize)
	{
		char* old_mem = mem_ptr_;
		newSize += alloc_count_;
		//内存长度按CDataPacket::MemoryAlginmentSize字节对齐
		//数据长度增加4字节，用于增加0终止，以便进行字符串的结尾调试
		//newSize = (newSize + MemoryAlginmentSize) & (~(MemoryAlginmentSize - 1));
#ifdef _DPPACK_MEM_CHK_
		char* new_mem = (char*)allocator_->AllocBuffer(newSize + sizeof(int));
#else
		char* new_mem = (char*)allocator_->AllocBuffer(newSize);
#endif
		size_t offset = offset_ - mem_ptr_;
		size_t length = data_end_ - mem_ptr_;

		if (length > 0)
		{
			memcpy(new_mem, mem_ptr_, __min(newSize, length));
		}

		//重设数据指针
		mem_ptr_ = new_mem;
		end_ptr_ = mem_ptr_ + newSize;
#ifdef _DPPACK_MEM_CHK_
		*(int*)end_ptr_ = 0xCCDDCCEE;
#endif
		offset_ = mem_ptr_ + offset;
		data_end_ = mem_ptr_ + length;

		//销毁原有数据内存
		if (old_mem)
		{
			_Assert();
			allocator_->FreeBuffer(old_mem);
		}
	}

	/* 写入ANSI短字符串以及字符串数据
	 * 字符串的数据格式为：[2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]，字符串中超过索引65535后的部分将被忽略
	 * 在字符串之前写入sizeof(TL)字节的长度值，且会再字符串末尾写入终止字符
	 * <TL> 定义字符串长度描述数据的数据类型，对于短字符串应当为unsigned char，否则即是unsigned short
	 * len	如果值为-1，则自动计算str的长度
	 */
	template <typename TL>
	void rawWriteStringLen(const char* str, size_t len)
	{
		if (!str) str = "";

		if (len == ((size_t)-1))
			len = str ? (TL)strlen(str) : 0;
		else
			len = __min(len, strlen(str));

		writeAtom<TL>((TL)len);//写入长度
		writeBuf(str, len * sizeof(*str));
		writeAtom<char>(0);//写入终止字符
	}


	///* 写入UNICODE16短字符串以及字符串数据
	// * 规则与rawWriteLengthString相同
	// */
	//template <typename TL>
	//void rawWriteWideStringLen(const char* str, size_t len)
	//{
	//	if ( len == -1 )
	//		len = str?(TL)wcslen(str):0;
	//	writeAtom<TL>((TL)len);//写入长度
	//	writeBuf(str, len * sizeof(*str));
	//	writeAtom<char>(0);//写入终止字符
	//}


protected:
	BaseAllocator*	allocator_;	//内存申请器
	int	alloc_count_;	// 每次内存增长的数量
//private:
//	static const size_t MemoryAlginmentSize = 256;	//数据包内存长度对齐边界
};

#endif

