#ifndef __FILESTREAM_H_
#define __FILESTREAM_H_

#include <zlib.h>
#include "memory/base_allocator.hpp"

namespace stream
{
//基础抽象流	流的基础类，提供流最基本的虚函数接口声明
class BaseStream
{
public:
	BaseStream(BaseAllocator* alloc)
	{
		alloc_ = alloc;
	};
	virtual ~BaseStream() {};

	virtual int getSize();
	virtual bool setSize(int)
	{
		return false;
	}
	inline int getPosition()
	{
		return seek(0, SEEK_CUR);
	}
	int setPosition(const int tPosition);
	virtual int seek(const int tOffset, const int Origin) = 0;
	virtual int read(void* lpBuffer, const int tSizeToRead) = 0;
	virtual int write(const void* lpBuffer, const size_t tSizeToWrite) = 0;
	virtual int copyFrom(BaseStream& stream, int tSizeToCopy = 0);
protected:
	BaseAllocator* alloc_;
};

/*	文件流，
	对文件系统中的文件读写操作的类
*/
class FileStream
	: public BaseStream
{
protected:
#ifdef _MSC_VER
	HANDLE	hdl_;
#else
	FILE* fp_;
#endif
public:
#ifdef _MSC_VER
	void setHandle(HANDLE Handle);
#endif
	//文件的打开方式
	enum FileAccessType
	{
	    faRead		= 0x0001,		//读取
	    faWrite		= 0x0002,		//写入
	    faCreate	= 0x1000,		//创建

	    faShareRead		= 0x0100,		//读共享
	    faShareWrite	= 0x0200,		//写共享
	    faShareDelete	= 0x0400,		//删除共享
	};
	//win32文件创建的模式
	enum OpenDisposition
	{
	    CreateIfNotExists = 1,		//文件不存在则创建
	    AlwaysCreate,				//总是创建文件，如果文件存在则将文件截断为0字节
	    OpenExistsOnly,				//仅打开存在的文件
	    AlwaysOpen,					//总是打开文件，若文件存在则直接打开，否则尝试创建文件并打开
	    TruncExistsOnly,			//如果文件存在则打开文件并截断为0字节
	};
private:
	char	fn_[256];
protected:
	void setFileName(const char* lpFileName);
	void construct(const char* lpFileName, unsigned int dwAccessType, unsigned int dwWin32CreationDisposition);
public:
	FileStream(const char* lpFileName, unsigned int dwAccessType, BaseAllocator* alloc);
	FileStream(const char* lpFileName, unsigned int dwAccessType, OpenDisposition eWin32CreateionDisposition, BaseAllocator* alloc);
	~FileStream();
	int seek(const int tOffset, const int Origin);
	int read(void* lpBuffer, const int tSizeToRead);
	int write(const void* lpBuffer, const size_t tSizeToWrite);
	inline const char* getFileName()
	{
		return fn_;
	}
};


/*	内存流
	使用内存作为数据存储区的流对象类
*/
class MemoryStream
	: public BaseStream
{
public:
	typedef BaseStream Inherited;

private:
	char*	mem_;		//内存块指针
	char*	ptr_;	//流指针
	char*	end_ptr_;	//文件尾指针
	char*	mem_end_;	//内存块结束地址指针
	int		alloc_count_;	// 每次扩展至少增加的数量
protected:
	//如果需要处理内存申请和释放相关事宜，则在继承类中覆盖此函数即可
	virtual char* AllocStream(char* ptr, const int size);

public:
	MemoryStream(BaseAllocator* alloc);
	~MemoryStream();

	bool setSize(int tSize);
	int seek(const int tOffset, const int Origin);
	int read(void* lpBuffer, const int tSizeToRead);
	int write(const void* lpBuffer, const size_t tSizeToWrite);
	void setAllocSize(int size)
	{
		alloc_count_ = size;
	}
	//获取内存流的内存块指针
	inline void* getMemory()
	{
		return mem_;
	}
	//从文件加流数据到内存
	int loadFromFile(const char* lpFileName);
	//将流数据保存到文件
	int saveToFile(const char* lpFileName);
};

/*	ZLib解压流
	可对数据进行解压并写入到流中
*/
class ZDecompressionStream
	: public BaseStream
{
public:
	typedef BaseStream Inherited;
protected:
	BaseStream*		strm_;			//zlib操作的目标流
	int				strm_pos_;			//目标流的指针位置
	z_stream		z_strm_;			//zlib操作的z_stream结构
	Bytef			buff_[0xffff];	//zlib操作缓冲区
	int				last_code_;		//上一次操作的返回码
public:
	ZDecompressionStream(BaseStream& source, BaseAllocator* alloc);
	~ZDecompressionStream();

	int seek(const int tOffset, const int Origin);
	int read(void* lpBuffer, const int tSizeToRead);
	int write(const void*, const size_t)
	{
		return -1;
	}
	int copyFrom(BaseStream&, int)
	{
		return 0;
	}
private:
	static void* zlibAllocMem(ZDecompressionStream& ZStream, uInt Items, uInt Size);
	static void zlibFreeMem(ZDecompressionStream& ZStream, void* lpBlock);

protected:
	//zlib操作内存申请函数，如果关心内存的申请和释放，则可在继承类中覆盖此函数
	void* AllocStream(int size);
	//zlib操作释放内存函数，如果关心内存的申请和释放，则可在继承类中覆盖此函数
	void SFree(void* ptr);
	//zlib操作进度通知函数，如果关心进度，则在子类中覆盖此函数即可
	void DoProgress();
	//设置上当前操作的返回码
	inline void setLastCode(const int code)
	{
		last_code_ = code;
	}
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
};

#endif
