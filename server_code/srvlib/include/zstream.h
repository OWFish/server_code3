#ifndef _WYL_ZLIB_STREAM_H_
#define _WYL_ZLIB_STREAM_H_


/******************************************************************
 *
 *	使用流的方式封装ZIP压缩和解压缩代码。
 *
 *****************************************************************/


namespace zstream
{

/*	ZLib流的基类
*/

class BaseZStream
	: public stream::BaseStream
{
public:
	typedef BaseStream Inherited;

protected:
	BaseStream*		strm_;			//zlib操作的目标流
	int				strm_pos_;			//目标流的指针位置
	z_stream		z_strm_;			//zlib操作的z_stream结构
	Bytef			buff_[0xffff];	//zlib操作缓冲区
	int				last_code_;		//上一次操作的返回码

private:
	static void* zlibAllocMem(BaseZStream& ZStream, uInt Items, uInt Size);
	static void zlibFreeMem(BaseZStream& ZStream, void* lpBlock);

protected:
	//zlib操作内存申请函数，如果关心内存的申请和释放，则可在继承类中覆盖此函数
	virtual void* AllocStream(int size);
	//zlib操作释放内存函数，如果关心内存的申请和释放，则可在继承类中覆盖此函数
	virtual void Free(void* ptr);
	//zlib操作进度通知函数，如果关心进度，则在子类中覆盖此函数即可
	virtual void DoProgress();
	//设置上当前操作的返回码
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

	//获取上一次操作的返回码
	inline int getLastCode()
	{
		return last_code_;
	}
	inline int succeeded()
	{
		return last_code_ >= 0;
	}
};


/*	ZLib压缩流
	可对数据进行压缩并写入到流中
*/
class ZCompressionStream
	: public BaseZStream
{
public:
	typedef BaseZStream Inherited;

	enum CompressionLevel
	{
	    clNone = 0,		//储存（未压缩）
	    clFastest,		//最快压缩（速度快，节省时间但压缩比不高）
	    clDefault,		//默认压缩等级（压缩速度和压缩比率均折中）
	    clMax,			//最高压缩比（压缩速度慢，但压缩比较高）
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
	//提交压缩缓冲中的数据到流中
	void finish();
	//获取压缩后的压缩比，返回的是一个浮点数
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

