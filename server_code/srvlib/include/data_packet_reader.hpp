#ifndef _DATA_PACKET_READER_HPP_
#define _DATA_PACKET_READER_HPP_

class DataPacketReader
{
public:
	/* ��ȡ����������
	 * lpBuffer	Ϊ���ݶ�ȡ�Ļ������ڴ���ָ��
	 * dwSize	Ҫ��ȡ���ֽ���
	 * @return	����ʵ�ʶ�ȡ���ֽ���
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
	/* ��ȡԭ������
	 * bool,char,short,int,__int64,float,double,void*��Щ��������ԭ������
	 * ���ʣ�����ݵĳ���С��ԭ�����ݴ�С����ֻ����ж�ȡʣ��Ĳ��ֲ���ո�λ����λ��
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
	/* ��ȡANSI���ַ�������
	* �ַ��������ݸ�ʽΪ��[2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]
	 * str			 �ַ�����ȡ������ָ��
	 * dwCharsToRead ��ʾstr���ַ����������ֽڳ��ȣ��������Ϊ0�����������ݰ��ж��ַ����ĳ��ȣ��Ҳ����ȡ���ݵ�str��
	 * @return       �������dwCharsToReadֵΪ0�򷵻����ݰ��ж��ַ����ĳ��ȣ����򷵻�ʵ�ʶ�ȡ���ַ�������
	 * ��remaks		 ���dwCharsToRead�ַ����������ݰ��е��ַ�������Ҫ������Զ��ڶ�ȡ���str�������������ַ�����ֹ�ַ���
	 *               ���dwCharsToRead�ַ������������ݰ��е��ַ������ȣ����򲻻���str�������ֹ�ַ���
	 *               ���dwCharsToRead�ַ�����С�����ݰ��е��ַ������ȣ������ȡdwCharsToReadָ�����ַ���������������
	                 ���ݰ���������û�б���ȡ�Ĳ����Ա������������ȷ�Ĵ����ݰ��ж�ȡ���������ݡ�
	 */
	inline size_t readString(char* str, size_t read_len)
	{
		return rawReadStringLen<unsigned short>(str, read_len);
	}
	/* ��ȡUNICODE16���ַ�������
	* �ַ��������ݸ�ʽΪ��[2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]
	 * str			 �ַ�����ȡ������ָ��
	 * dwCharsToRead ��ʾstr���ַ����������ֽڳ��ȣ��������Ϊ0�����������ݰ��ж��ַ����ĳ��ȣ��Ҳ����ȡ���ݵ�str��
	 * @return       �������dwCharsToReadֵΪ0�򷵻����ݰ��ж��ַ����ĳ��ȣ����򷵻�ʵ�ʶ�ȡ���ַ�������
	 * ��remaks		 ���dwCharsToRead�ַ����������ݰ��е��ַ�������Ҫ������Զ��ڶ�ȡ���str�������������ַ�����ֹ�ַ���
	 *               ���dwCharsToRead�ַ������������ݰ��е��ַ������ȣ����򲻻���str�������ֹ�ַ���
	 *               ���dwCharsToRead�ַ�����С�����ݰ��е��ַ������ȣ������ȡdwCharsToReadָ�����ַ���������������
	                 ���ݰ���������û�б���ȡ�Ĳ����Ա������������ȷ�Ĵ����ݰ��ж�ȡ���������ݡ�
	 */

	// ��ȡ�ڴ�ռ�Ĵ�С
	inline size_t getSize()
	{
		return end_ptr_ - mem_ptr_;
	}

	/* ��ȡ��ȡ���ݰ��ĵ�ǰ��Ч���ݳ��� */
	inline size_t getLength()
	{
		return data_end_ - mem_ptr_;
	}
	/* ��ȡ���ݰ���ǰ��дλ���ֽ�ƫ���� */
	inline size_t getPosition()
	{
		return offset_ - mem_ptr_;
	}
	/* �������ݰ���ǰ��дλ���ֽ�ƫ������
	   ����µ�ƫ�����ȵ�ǰ�ڴ�鳤��Ҫ���������µ�ƫ��λ�ò�������ǰ�ڴ�鳤��
	 */
	inline size_t setPosition(size_t newPos)
	{
		size_t mem_size = end_ptr_ - mem_ptr_;

		if (newPos > mem_size)
			newPos = mem_size;

		offset_ = mem_ptr_ + newPos;
		return newPos;
	}
	/* ��ȡ�Ե�ǰ��дָ�뿪ʼ���������ȡ��ʣ���ֽ��� */
	inline size_t getAvaliableLength()
	{
		return data_end_ - offset_;
	}
	/* ���ڵ�ǰ��дָ��ƫ��λ�õ���ƫ����
	 * nOffsetToAdjust Ҫ������ƫ������С���������ʾ���ڴ濪ʼ������������ƫ�ƣ�
	 * �����ڻ����Ƶ������ƫ��λ������Ч���ڴ淶Χ��
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
	/* ��ȡ���ݰ������ڴ�ָ�� */
	inline char* getMemoryPtr()
	{
		return mem_ptr_;
	}
	/* ��ȡ���ݰ������ڴ�ĵ�ǰƫ��ָ�� */
	inline char* getOffsetPtr()
	{
		return offset_;
	}

	//��ȡָ��ƫ������ָ��
	inline char* getPositionPtr(size_t pos)
	{
		return mem_ptr_ + pos;
	}
public:
	/* ��ȡԭ�����ݵ���������� */
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
	/* ��ȡANSI/UNICODE16�ַ�������
	 * �ַ��������ݸ�ʽΪ��[2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]
	 * <TS>			 �����ַ����������ͣ���char*��wchar_t*
	 * <TL>			 �����ַ��������������ݵ��������ͣ����ڶ��ַ���Ӧ��Ϊunsigned char��������unsigned short
	 * str			 �ַ�����ȡ������ָ��
	 * lenType		 �������������Ͷ�����
	 * dwCharsToRead ��ʾstr���ַ����������ֽڳ��ȣ��������Ϊ0�����������ݰ��ж��ַ����ĳ��ȣ��Ҳ����ȡ���ݵ�str��
	 * @return       �������dwCharsToReadֵΪ0�򷵻����ݰ��ж��ַ����ĳ��ȣ����򷵻�ʵ�ʶ�ȡ���ַ�������
	 * ��remaks		 ���dwCharsToRead�ַ����������ݰ��е��ַ�������Ҫ������Զ��ڶ�ȡ���str�������������ַ�����ֹ�ַ���
	 *               ���dwCharsToRead�ַ������������ݰ��е��ַ������ȣ����򲻻���str�������ֹ�ַ���
	 *               ���dwCharsToRead�ַ�����С�����ݰ��е��ַ������ȣ������ȡdwCharsToReadָ�����ַ���������������
	                 ���ݰ���������û�б���ȡ�Ĳ����Ա������������ȷ�Ĵ����ݰ��ж�ȡ���������ݡ�
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
				//�����ַ�����������
				offset_ += 2;
				avaliable -= 2;

				//����ʵ�ʶ�ȡ���ȣ�����Խ��
				if (rlen > read_len)
					rlen = read_len;

				if (rlen > avaliable)
					rlen = avaliable;

				if (rlen > 0)
					readBuf(str, rlen);

				//�����ȡ���ַ�����������������ָ�����ַ������ȣ�����Ҫ����û�ж�ȡ�Ĳ��֣�
				//�Ա������������ȷ�Ĵ����ݰ��ж�ȡ���������ݡ�
				if (str_len > rlen)
					offset_ += (str_len - rlen);

				//������ֹ�ַ�0
				++offset_;

				if (offset_ > data_end_) offset_ = data_end_; // offset���ܳ���data_end�ķ�Χ
			}
		}
		else
		{
			rlen = 0;
		}

		//�����ȡ��������ʣ��Ŀռ��������ֹ�ַ�
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
	/* ��ȡANSI/UNICODE16�ַ�������
	 * �ַ��������ݸ�ʽΪ��[2�ֽ��ַ���������][�ַ����ֽ����ݣ��ַ���������65536����][�ַ�����ֹ�ַ�0]
	 * <TS>			 �����ַ��������ͣ���char��wchar_t
	 * <TL>			 �����ַ��������������ݵ��������ͣ����ڶ��ַ���Ӧ��Ϊunsigned char��������unsigned short
	 * str			 �ַ�����ȡ������ָ��
	 * lenType		 �������������Ͷ�����
	 * dwCharsToRead ��ʾstr���ַ����������ֽڳ��ȣ��������Ϊ0�����������ݰ��ж��ַ����ĳ��ȣ��Ҳ����ȡ���ݵ�str��
	 * @return       �������dwCharsToReadֵΪ0�򷵻����ݰ��ж��ַ����ĳ��ȣ����򷵻�ʵ�ʶ�ȡ���ַ�������
	 * ��remaks		 ���dwCharsToRead�ַ����������ݰ��е��ַ�������Ҫ������Զ��ڶ�ȡ���str�������������ַ�����ֹ�ַ���
	 *               ���dwCharsToRead�ַ������������ݰ��е��ַ������ȣ����򲻻���str�������ֹ�ַ���
	 *               ���dwCharsToRead�ַ�����С�����ݰ��е��ַ������ȣ������ȡdwCharsToReadָ�����ַ���������������
	                 ���ݰ���������û�б���ȡ�Ĳ����Ա������������ȷ�Ĵ����ݰ��ж�ȡ���������ݡ�
	 */
	template <typename TS, typename TL>
	const TS* rawReadStringPtr()
	{
		size_t avaliable = data_end_ - offset_;
		size_t str_len = 0;

		if (avaliable >= sizeof(TL) + sizeof(TS))
		{
			str_len = *((TL*)offset_);

			//������ݰ������㹻���ַ������ݿռ�
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
	char*				mem_ptr_;		//�ڴ���ʼ��ַ
	char*				end_ptr_;	//�ڴ������ַ��ָ���β�ֽڵĺ�һ���ֽ�
	char*				offset_;		//��ǰ��дƫ�Ƶ�ַ
	char*				data_end_;	//���ݳ��Ƚ���ƫ�Ƶ�ַ
};

#endif

