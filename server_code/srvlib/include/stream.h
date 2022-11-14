#ifndef __FILESTREAM_H_
#define __FILESTREAM_H_

#include <zlib.h>
#include "memory/base_allocator.hpp"

namespace stream
{
//����������	���Ļ����࣬�ṩ����������麯���ӿ�����
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

/*	�ļ�����
	���ļ�ϵͳ�е��ļ���д��������
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
	//�ļ��Ĵ򿪷�ʽ
	enum FileAccessType
	{
	    faRead		= 0x0001,		//��ȡ
	    faWrite		= 0x0002,		//д��
	    faCreate	= 0x1000,		//����

	    faShareRead		= 0x0100,		//������
	    faShareWrite	= 0x0200,		//д����
	    faShareDelete	= 0x0400,		//ɾ������
	};
	//win32�ļ�������ģʽ
	enum OpenDisposition
	{
	    CreateIfNotExists = 1,		//�ļ��������򴴽�
	    AlwaysCreate,				//���Ǵ����ļ�������ļ��������ļ��ض�Ϊ0�ֽ�
	    OpenExistsOnly,				//���򿪴��ڵ��ļ�
	    AlwaysOpen,					//���Ǵ��ļ������ļ�������ֱ�Ӵ򿪣������Դ����ļ�����
	    TruncExistsOnly,			//����ļ���������ļ����ض�Ϊ0�ֽ�
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


/*	�ڴ���
	ʹ���ڴ���Ϊ���ݴ洢������������
*/
class MemoryStream
	: public BaseStream
{
public:
	typedef BaseStream Inherited;

private:
	char*	mem_;		//�ڴ��ָ��
	char*	ptr_;	//��ָ��
	char*	end_ptr_;	//�ļ�βָ��
	char*	mem_end_;	//�ڴ�������ַָ��
	int		alloc_count_;	// ÿ����չ�������ӵ�����
protected:
	//�����Ҫ�����ڴ�������ͷ�������ˣ����ڼ̳����и��Ǵ˺�������
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
	//��ȡ�ڴ������ڴ��ָ��
	inline void* getMemory()
	{
		return mem_;
	}
	//���ļ��������ݵ��ڴ�
	int loadFromFile(const char* lpFileName);
	//�������ݱ��浽�ļ�
	int saveToFile(const char* lpFileName);
};

/*	ZLib��ѹ��
	�ɶ����ݽ��н�ѹ��д�뵽����
*/
class ZDecompressionStream
	: public BaseStream
{
public:
	typedef BaseStream Inherited;
protected:
	BaseStream*		strm_;			//zlib������Ŀ����
	int				strm_pos_;			//Ŀ������ָ��λ��
	z_stream		z_strm_;			//zlib������z_stream�ṹ
	Bytef			buff_[0xffff];	//zlib����������
	int				last_code_;		//��һ�β����ķ�����
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
	//zlib�����ڴ����뺯������������ڴ��������ͷţ�����ڼ̳����и��Ǵ˺���
	void* AllocStream(int size);
	//zlib�����ͷ��ڴ溯������������ڴ��������ͷţ�����ڼ̳����и��Ǵ˺���
	void SFree(void* ptr);
	//zlib��������֪ͨ������������Ľ��ȣ����������и��Ǵ˺�������
	void DoProgress();
	//�����ϵ�ǰ�����ķ�����
	inline void setLastCode(const int code)
	{
		last_code_ = code;
	}
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
};

#endif
