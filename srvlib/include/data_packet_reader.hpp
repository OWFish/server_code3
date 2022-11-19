#ifndef _DATA_PACKET_READER_HPP_
#define _DATA_PACKET_READER_HPP_

class DataPacketReader
{
public:
	/* 读取二进制数据
	 * lpBuffer	为数据读取的缓冲区内存子指针
	 * dwSize	要读取的字节数
	 * @return	返回实际读取的字节数
	 */
	inline size_t readBuf(void* buf, size_t size)
	{
		size_t avaliable = data_end_ - offset_;

		if (size > avaliable)
			size = avaliable;

		if (size > 0)
		{
			memcpy(buf, offset_, size);
			offset_ += size;
		}

		return size;
	}
	/* 读取原子数据
	 * bool,char,short,int,__int64,float,double,void*这些数据属于原子数据
	 * 如果剩余数据的长度小于原子数据大小，则只会进行读取剩余的部分并清空高位比特位！
	 */
	template <typename T>
	inline T readAtom()
	{
		T val;
		size_t avaliable = data_end_ - offset_;

		if (avaliable >= sizeof(T))
		{
			val = *(T*)offset_;
			offset_ += sizeof(T);
		}
		else if (avaliable > 0)
		{
			memset(&val, 0, sizeof(val));
			memcpy(&val, offset_, avaliable);
			offset_ += avaliable;
		}
		else memset(&val, 0, sizeof(val));

		return val;
	}
	/* 读取ANSI短字符串数据
	* 字符串的数据格式为：[2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]
	 * str			 字符串读取缓冲区指针
	 * dwCharsToRead 表示str的字符数量，非字节长度，如果参数为0则函数返回数据包中短字符串的长度，且不会读取数据到str中
	 * @return       如果参数dwCharsToRead值为0则返回数据包中短字符串的长度，否则返回实际读取的字符串长度
	 * ★remaks		 如果dwCharsToRead字符数量比数据包中的字符串长度要大，则会自动在读取后的str缓冲区中增加字符串终止字符。
	 *               如果dwCharsToRead字符数量等于数据包中的字符串长度，否则不会在str中添加终止字符。
	 *               如果dwCharsToRead字符数量小于数据包中的字符串长度，则仅读取dwCharsToRead指定的字符数量并丢弃（从
	                 数据包中跳过）没有被读取的部分以便接下来可以正确的从数据包中读取后续的数据。
	 */
	inline size_t readString(char* str, size_t read_len)
	{
		return rawReadStringLen<unsigned short>(str, read_len);
	}
	/* 读取UNICODE16短字符串数据
	* 字符串的数据格式为：[2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]
	 * str			 字符串读取缓冲区指针
	 * dwCharsToRead 表示str的字符数量，非字节长度，如果参数为0则函数返回数据包中短字符串的长度，且不会读取数据到str中
	 * @return       如果参数dwCharsToRead值为0则返回数据包中短字符串的长度，否则返回实际读取的字符串长度
	 * ★remaks		 如果dwCharsToRead字符数量比数据包中的字符串长度要大，则会自动在读取后的str缓冲区中增加字符串终止字符。
	 *               如果dwCharsToRead字符数量等于数据包中的字符串长度，否则不会在str中添加终止字符。
	 *               如果dwCharsToRead字符数量小于数据包中的字符串长度，则仅读取dwCharsToRead指定的字符数量并丢弃（从
	                 数据包中跳过）没有被读取的部分以便接下来可以正确的从数据包中读取后续的数据。
	 */

	// 获取内存空间的大小
	inline size_t getSize()
	{
		return end_ptr_ - mem_ptr_;
	}

	/* 获取获取数据包的当前有效数据长度 */
	inline size_t getLength()
	{
		return data_end_ - mem_ptr_;
	}
	/* 获取数据包当前读写位置字节偏移量 */
	inline size_t getPosition()
	{
		return offset_ - mem_ptr_;
	}
	/* 设置数据包当前读写位置字节偏移量，
	   如果新的偏移量比当前内存块长度要大，则限制新的偏移位置不超过当前内存块长度
	 */
	inline size_t setPosition(size_t newPos)
	{
		size_t mem_size = end_ptr_ - mem_ptr_;

		if (newPos > mem_size)
			newPos = mem_size;

		offset_ = mem_ptr_ + newPos;
		return newPos;
	}
	/* 获取自当前读写指针开始可以用与读取的剩余字节数 */
	inline size_t getAvaliableLength()
	{
		return data_end_ - offset_;
	}
	/* 基于当前读写指针偏移位置调整偏移量
	 * nOffsetToAdjust 要调整的偏移量大小，负数则表示向内存开始处调整（降低偏移）
	 * 函数内会限制调整后的偏移位置在有效的内存范围内
	 */
	inline size_t adjustOffset(int64_t adjust_offset)
	{
		offset_ += adjust_offset;

		if (offset_ < mem_ptr_)
			offset_ = mem_ptr_;
		else if (offset_ > end_ptr_)
			offset_ = end_ptr_;

		return offset_ - mem_ptr_;
	}
	/* 获取数据包数据内存指针 */
	inline char* getMemoryPtr()
	{
		return mem_ptr_;
	}
	/* 获取数据包数据内存的当前偏移指针 */
	inline char* getOffsetPtr()
	{
		return offset_;
	}

	//获取指定偏移量的指针
	inline char* getPositionPtr(size_t pos)
	{
		return mem_ptr_ + pos;
	}
public:
	/* 读取原子数据的运算符重载 */
	template <typename T>
	inline DataPacketReader& operator >> (T& val)
	{
		if (sizeof(val) <= sizeof(int))
			val = readAtom<T>();
		else readBuf(&val, sizeof(val));

		return *this;
	}

	inline DataPacketReader& operator >> (const char*& str)
	{
		str = rawReadStringPtr<char, unsigned short>();
		return *this;
	}
	inline const char* readStringBuf()
	{
		return rawReadStringPtr<char, unsigned int>();
	}
	//inline DataPacketReader& operator >> (const wchar_t* &str)
	//{
	//	str = rawReadStringPtr<wchar_t, unsigned short>();
	//	return *this;
	//}
public:
	DataPacketReader()
	{
		mem_ptr_ = end_ptr_ = offset_ = data_end_ = NULL;
	}
	DataPacketReader(void* buf, size_t size)
	{
		offset_ = mem_ptr_ = (char*)buf;
		end_ptr_ = data_end_ = mem_ptr_ + size;
	}

protected:
	/* 读取ANSI/UNICODE16字符串数据
	 * 字符串的数据格式为：[2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]
	 * <TS>			 定义字符串数据类型，是char*或wchar_t*
	 * <TL>			 定义字符串长度描述数据的数据类型，对于短字符串应当为unsigned char，否则即是unsigned short
	 * str			 字符串读取缓冲区指针
	 * lenType		 参数的数据类型定义了
	 * dwCharsToRead 表示str的字符数量，非字节长度，如果参数为0则函数返回数据包中短字符串的长度，且不会读取数据到str中
	 * @return       如果参数dwCharsToRead值为0则返回数据包中短字符串的长度，否则返回实际读取的字符串长度
	 * ★remaks		 如果dwCharsToRead字符数量比数据包中的字符串长度要大，则会自动在读取后的str缓冲区中增加字符串终止字符。
	 *               如果dwCharsToRead字符数量等于数据包中的字符串长度，否则不会在str中添加终止字符。
	 *               如果dwCharsToRead字符数量小于数据包中的字符串长度，则仅读取dwCharsToRead指定的字符数量并丢弃（从
	                 数据包中跳过）没有被读取的部分以便接下来可以正确的从数据包中读取后续的数据。
	 */
	template <typename TL>
	size_t rawReadStringLen(char* str, size_t read_len)
	{
		assert(read_len > 0);

		size_t avaliable = data_end_ - offset_;
		size_t rlen = 0;
		size_t str_len = 0;

		if (avaliable >= 2)
		{
			TL* temp = (TL*)offset_;
			rlen = str_len = (size_t)(*temp);

			if (read_len > 0)
			{
				//跳过字符串长度数据
				offset_ += 2;
				avaliable -= 2;

				//计算实际读取长度，避免越界
				if (rlen > read_len)
					rlen = read_len;

				if (rlen > avaliable)
					rlen = avaliable;

				if (rlen > 0)
					readBuf(str, rlen);

				//如果读取的字符串长度少于数据中指定的字符串长度，则需要调过没有读取的部分，
				//以便接下来可以正确的从数据包中读取后续的数据。
				if (str_len > rlen)
					offset_ += (str_len - rlen);

				//跳过终止字符0
				++offset_;

				if (offset_ > data_end_) offset_ = data_end_; // offset不能超过data_end的范围
			}
		}
		else
		{
			rlen = 0;
		}

		//如果读取缓冲区有剩余的空间则添加终止字符
		if (rlen < read_len)
		{
			str[rlen] = 0;
		}
		else if (read_len > 0)
		{
			str[read_len - 1] = 0;
		}

		return str_len;
	}
	/* 读取ANSI/UNICODE16字符串数据
	 * 字符串的数据格式为：[2字节字符长度数据][字符串字节数据，字符串长度在65536以内][字符串终止字符0]
	 * <TS>			 定义字符数据类型，是char或wchar_t
	 * <TL>			 定义字符串长度描述数据的数据类型，对于短字符串应当为unsigned char，否则即是unsigned short
	 * str			 字符串读取缓冲区指针
	 * lenType		 参数的数据类型定义了
	 * dwCharsToRead 表示str的字符数量，非字节长度，如果参数为0则函数返回数据包中短字符串的长度，且不会读取数据到str中
	 * @return       如果参数dwCharsToRead值为0则返回数据包中短字符串的长度，否则返回实际读取的字符串长度
	 * ★remaks		 如果dwCharsToRead字符数量比数据包中的字符串长度要大，则会自动在读取后的str缓冲区中增加字符串终止字符。
	 *               如果dwCharsToRead字符数量等于数据包中的字符串长度，否则不会在str中添加终止字符。
	 *               如果dwCharsToRead字符数量小于数据包中的字符串长度，则仅读取dwCharsToRead指定的字符数量并丢弃（从
	                 数据包中跳过）没有被读取的部分以便接下来可以正确的从数据包中读取后续的数据。
	 */
	template <typename TS, typename TL>
	const TS* rawReadStringPtr()
	{
		size_t avaliable = data_end_ - offset_;
		size_t str_len = 0;

		if (avaliable >= sizeof(TL) + sizeof(TS))
		{
			str_len = *((TL*)offset_);

			//如果数据包中有足够的字符串数据空间
			if (avaliable >= str_len + sizeof(TL) + sizeof(TS))
			{
				const TS* str = (TS*)(offset_ + sizeof(TL));
				offset_ += str_len * sizeof(TS) + sizeof(TL) + sizeof(TS);
				return str;
			}
		}

		return NULL;
	}
protected:
	char*				mem_ptr_;		//内存起始地址
	char*				end_ptr_;	//内存结束地址，指向结尾字节的后一个字节
	char*				offset_;		//当前读写偏移地址
	char*				data_end_;	//数据长度结束偏移地址
};

#endif

