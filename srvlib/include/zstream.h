#ifndef _WYL_ZLIB_STREAM_H_
#define _WYL_ZLIB_STREAM_H_


/******************************************************************
 *
 *	ʹ�����ķ�ʽ��װZIPѹ���ͽ�ѹ�����롣
 *
 *****************************************************************/


namespace zstream
{

/*	ZLib���Ļ���
*/

class BaseZStream
	: public stream::BaseStream
{
public:
	typedef BaseStream Inherited;

protected:
	BaseStream*		strm_;			//zlib������Ŀ����
	int				strm_pos_;			//Ŀ������ָ��λ��
	z_stream		z_strm_;			//zlib������z_stream�ṹ
	Bytef			buff_[0xffff];	//zlib����������
	int				last_code_;		//��һ�β����ķ�����

private:
	static void* zlibAllocMem(BaseZStream& ZStream, uInt Items, uInt Size);
	static void zlibFreeMem(BaseZStream& ZStream, void* lpBlock);

protected:
	//zlib�����ڴ����뺯������������ڴ��������ͷţ�����ڼ̳����и��Ǵ˺���
	virtual void* AllocStream(int size);
	//zlib�����ͷ��ڴ溯������������ڴ��������ͷţ�����ڼ̳����и��Ǵ˺���
	virtual void Free(void* ptr);
	//zlib��������֪ͨ������������Ľ��ȣ����������и��Ǵ˺�������
	virtual void DoProgress();
	//�����ϵ�ǰ�����ķ�����
	inline void setLastCode(const int code)
	{
		last_code_ = code;
	}
public:
	BaseZStream(BaseStream& stream, BaseAllocator* alloc);
	virtual ~BaseZStream();

	//int seek(const int tOffset, const int Origin)
	//{
	//	return 0;
	//}
	//int read(void* lpBuffer, const int tSizeToRead)
	//{
	//	return 0;
	//}
	//int write(const void* lpBuffer, const size_t tSizeToWrite)
	//{
	//	return 0;
	//}
	//int copyFrom(BaseStream& stream, int tSizeToCopy = 0)
	//{
	//	return 0;
	//}

	//��ȡ��һ�β����ķ�����
	inline int getLastCode()
	{
		return last_code_;
	}
	inline int succeeded()
	{
		return last_code_ >= 0;
	}
};


/*	ZLibѹ����
	�ɶ����ݽ���ѹ����д�뵽����
*/
class ZCompressionStream
	: public BaseZStream
{
public:
	typedef BaseZStream Inherited;

	enum CompressionLevel
	{
	    clNone = 0,		//���棨δѹ����
	    clFastest,		//���ѹ�����ٶȿ죬��ʡʱ�䵫ѹ���Ȳ��ߣ�
	    clDefault,		//Ĭ��ѹ���ȼ���ѹ���ٶȺ�ѹ�����ʾ����У�
	    clMax,			//���ѹ���ȣ�ѹ���ٶ�������ѹ���Ƚϸߣ�
	};

public:
	ZCompressionStream(BaseStream& destStream, CompressionLevel CmprsLvl, BaseAllocator* alloc);
	~ZCompressionStream();

	int seek(const int tOffset, const int Origin);
	//int read(void* lpBuffer, const int tSizeToRead)
	//{
	//	return -1;
	//}
	int write(const void* lpBuffer, const size_t tSizeToWrite);
	//�ύѹ�������е����ݵ�����
	void finish();
	//��ȡѹ�����ѹ���ȣ����ص���һ��������
	inline float getCompressionRate()
	{
		if (z_strm_.total_in == 0)
			return 0;
		else return (1.0f - ((float)z_strm_.total_out / z_strm_.total_in)) * 100.0f;
	}
	virtual int read(void* lpBuffer, const int tSizeToRead)
	{
		return 0;
	}
};


};

#endif

