#ifndef _DATA_PACKET_HPP_
#define _DATA_PACKET_HPP_
/***********************************************************************
                        �����ڴ�����ݰ���д��

  ʵ�ַ�ʽ��MemoryStream��ͬ��д�����ݵ�ʱ��д�뵽�ڴ��У����д�����ݵĿռ䳬������
  �ڴ�鳤������Զ������ڴ档

  ���ݰ����ڴ�����ʱͨ���ڴ�ض�����еģ���ʹ�ø���Ч�ʵ��ڴ����

  �����ݰ��е��ַ���
  ���ݰ�����һ���ַ�����д���ƣ�����ANSI�ַ����Լ�UNICODE16�ַ�������һ���ַ���д��
  �����ݰ������ڴ�ṹΪ��
    [2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]

***********************************************************************/
#include "os_def.h"
#include "data_packet_reader.hpp"

class DataPacket : public DataPacketReader
{
public:
	/* д�����������
	 * lpBuffer  ָ������������ڴ��ָ��
	 * dwSize    ���ݵ��ֽڳ���
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

		//�����дָ�볬������ָ���λ�ã����������ָ��Ϊ��дָ���λ��
		if (offset_ > data_end_)
			data_end_ = offset_;
	}
	/* д��ԭ����������
	 * bool,char,short,int,__int64,float,double,void*��Щ��������Ϊԭ������
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

		//�����дָ�볬������ָ���λ�ã����������ָ��Ϊ��дָ���λ��
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
	///* д��UNICODE16�ַ������ݣ��ַ������ȱ�����65536���ڣ�����65535�Ĳ��ֽ����ᱻд�룩
	// * ���ַ���֮ǰд�������ֽڵ��ַ������ȣ��һ����ַ���ĩβд����ֹ�ַ�
	// * len ���ֵΪ-1�����Զ�����str�ĳ���
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
	/* �������ݰ���ǰ��дλ���ֽ�ƫ������
	 * ����µ�ƫ�����ȵ�ǰ�ڴ�鳤��Ҫ����������setLengthһ�������ڴ�����չ����
	 */
	inline size_t setPosition(size_t newPos)
	{
		size_t mem_size = end_ptr_ - mem_ptr_;

		if (newPos > mem_size)
			setSize(newPos);

		offset_ = mem_ptr_ + newPos;

		//�����дָ�볬������ָ���λ�ã����������ָ��Ϊ��дָ���λ��
		if (offset_ > data_end_)
			data_end_ = offset_;

		return newPos;
	}
	/* ���ڵ�ǰ��дָ��ƫ��λ�õ���ƫ����
	 * nOffsetToAdjust Ҫ������ƫ������С���������ʾ���ڴ濪ʼ������������ƫ�ƣ�
	 * �����ڻ����Ƶ������ƫ��λ�ñ�����ڵ����ڴ濪ͷ��
	 * ���������ı��˳��������ڴ泤�ȣ�����Զ������ڴ浽���������λ��
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
	 * ��ȡ��ǰ���峤���µĿ����ֽ���
	 */
	inline size_t getAvaliableBufLen()
	{
		return end_ptr_ - offset_;
	}
public:
	/*
	* Comment: ��������ͨ������Ԥ�����_DPPACK_MEM_CHK_������£������ݰ������ڴ�Խ����
	* @Return void:
	*/
	inline void _Assert()
	{
#ifdef _DPPACK_MEM_CHK_
		DbgAssert(!end_ptr_ || *(int*)end_ptr_ == 0xCCDDCCEE);
#endif
	}
	/*
	 * ������ø�ֵ
	 */
	inline DataPacket& operator = (const DataPacket&)
	{
		//��ֹ���ø�ֵ��
		assert(false);
	}
public:
	/* д��ԭ�����ݵ���������� */
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
		//Ϊ�˷�ֹ�����ø�ֵ��һ�����󣬴˴���ֹ����һ�������й���
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

	// �ͷ��ڴ�
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
	// ���÷�����
	inline void setAllocator(BaseAllocator* allocator)
	{
		allocator_ = allocator;
	}

	// ���ڰ��ַ�����Ŀǰ�ĸ�ʽд�뵽һ��buff, �����������ݵĳ���
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
	/*  �����趨���ݰ��ڴ�ռ��С  */
	void setSize(size_t newSize)
	{
		char* old_mem = mem_ptr_;
		newSize += alloc_count_;
		//�ڴ泤�Ȱ�CDataPacket::MemoryAlginmentSize�ֽڶ���
		//���ݳ�������4�ֽڣ���������0��ֹ���Ա�����ַ����Ľ�β����
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

		//��������ָ��
		mem_ptr_ = new_mem;
		end_ptr_ = mem_ptr_ + newSize;
#ifdef _DPPACK_MEM_CHK_
		*(int*)end_ptr_ = 0xCCDDCCEE;
#endif
		offset_ = mem_ptr_ + offset;
		data_end_ = mem_ptr_ + length;

		//����ԭ�������ڴ�
		if (old_mem)
		{
			_Assert();
			allocator_->FreeBuffer(old_mem);
		}
	}

	/* д��ANSI���ַ����Լ��ַ�������
	 * �ַ��������ݸ�ʽΪ��[2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]���ַ����г�������65535��Ĳ��ֽ�������
	 * ���ַ���֮ǰд��sizeof(TL)�ֽڵĳ���ֵ���һ����ַ���ĩβд����ֹ�ַ�
	 * <TL> �����ַ��������������ݵ��������ͣ����ڶ��ַ���Ӧ��Ϊunsigned char��������unsigned short
	 * len	���ֵΪ-1�����Զ�����str�ĳ���
	 */
	template <typename TL>
	void rawWriteStringLen(const char* str, size_t len)
	{
		if (!str) str = "";

		if (len == ((size_t)-1))
			len = str ? (TL)strlen(str) : 0;
		else
			len = __min(len, strlen(str));

		writeAtom<TL>((TL)len);//д�볤��
		writeBuf(str, len * sizeof(*str));
		writeAtom<char>(0);//д����ֹ�ַ�
	}


	///* д��UNICODE16���ַ����Լ��ַ�������
	// * ������rawWriteLengthString��ͬ
	// */
	//template <typename TL>
	//void rawWriteWideStringLen(const char* str, size_t len)
	//{
	//	if ( len == -1 )
	//		len = str?(TL)wcslen(str):0;
	//	writeAtom<TL>((TL)len);//д�볤��
	//	writeBuf(str, len * sizeof(*str));
	//	writeAtom<char>(0);//д����ֹ�ַ�
	//}


protected:
	BaseAllocator*	allocator_;	//�ڴ�������
	int	alloc_count_;	// ÿ���ڴ�����������
//private:
//	static const size_t MemoryAlginmentSize = 256;	//���ݰ��ڴ泤�ȶ���߽�
};

#endif

