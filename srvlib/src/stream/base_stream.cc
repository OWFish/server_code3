#include "os_def.h"
#include "stream.h"

using namespace stream;

int BaseStream::getSize()
{
	int nPos = seek(0, SEEK_CUR);
	int nSize = seek(0, SEEK_END);
	seek(nPos, SEEK_SET);
	return nSize;
}

int BaseStream::setPosition(const int tPosition)
{
	return seek(tPosition, SEEK_SET);
}

int BaseStream::copyFrom(BaseStream& stream, int tSizeToCopy)
{
	static const int OnceReadBytes = 8192;
	//保存原始流当前的指针位置
	int nOldPosition = stream.seek(0, SEEK_CUR);

	if (tSizeToCopy == 0)
	{
		stream.seek(0, SEEK_SET);
		tSizeToCopy = stream.getSize();
	}

	if (tSizeToCopy <= 0)
		return tSizeToCopy;

	int nSizeCopyed = 0;
	void* pBuffer = alloc_ ? alloc_->AllocBuffer(OnceReadBytes) : malloc(OnceReadBytes);

	while (nSizeCopyed < tSizeToCopy)
	{
		int nSizeToRead = tSizeToCopy - nSizeCopyed;

		if (nSizeToRead > OnceReadBytes)
			nSizeToRead = OnceReadBytes;

		int nSizeReaded = stream.read(pBuffer, (unsigned int)nSizeToRead);

		if (nSizeReaded <= 0)
			break;

		write(pBuffer, (unsigned int)nSizeReaded);
		nSizeCopyed += nSizeReaded;
	}

	alloc_ ? alloc_->FreeBuffer(pBuffer) : free(pBuffer);

	//恢复原始流的指针位置
	stream.seek(nOldPosition, SEEK_SET);
	return nSizeCopyed;
}


ZDecompressionStream::ZDecompressionStream(BaseStream& source, BaseAllocator* alloc)
	: BaseStream(alloc)
{
	strm_ = &source;
	strm_pos_ = source.getPosition();

	ZeroMemory( &z_strm_, sizeof(z_strm_) );

	z_strm_.zalloc = (alloc_func)zlibAllocMem;
	z_strm_.zfree = (free_func)zlibFreeMem;
	z_strm_.opaque = this;

	last_code_ = Z_OK;

	z_strm_.next_in = buff_;
	z_strm_.avail_in = 0;
	last_code_ = inflateInit_(&z_strm_, zlib_version, sizeof(z_strm_));
}

ZDecompressionStream::~ZDecompressionStream()
{
	strm_->seek(-(signed)z_strm_.avail_in, SEEK_CUR);
	last_code_ = inflateEnd(&z_strm_);
}

int ZDecompressionStream::seek(const int Offset, const int Origin)
{
	char Buf[4096];
	int tOffset = Offset;

	if (!succeeded())
		return -1;

	if (tOffset == 0 && Origin == SEEK_SET)
	{
		last_code_ = inflateReset(&z_strm_);

		if (!succeeded())
			return -1;

		z_strm_.next_in = buff_;
		z_strm_.avail_in = 0;
		strm_->setPosition(0);
		strm_pos_ = 0;
	}
	else if ((tOffset >= 0 && Origin == SEEK_CUR) || (tOffset - z_strm_.total_out > 0 && Origin == SEEK_SET))
	{
		if (Origin == SEEK_SET)
			tOffset -= z_strm_.total_out;

		if (tOffset > 0)
		{
			for (int i = tOffset / sizeof(Buf) - 1; i > -1; --i)
			{
				read(Buf, sizeof(Buf));
			}

			read(Buf, tOffset % sizeof(Buf));
		}
	}

	return z_strm_.total_out;
}

int ZDecompressionStream::read(void* lpBuffer, const int tSizeToRead)
{
	z_strm_.next_out = (Bytef*)lpBuffer;
	z_strm_.avail_out = (uInt)tSizeToRead;

	if (!succeeded())
		return -1;

	if (strm_->getPosition() != strm_pos_)
		strm_->setPosition(strm_pos_);

	while (z_strm_.avail_out > 0)
	{
		if (z_strm_.avail_in == 0)
		{
			int nSizeReaded = strm_->read(buff_, sizeof(buff_));

			if (nSizeReaded <= 0)
			{
				return tSizeToRead - z_strm_.avail_out;
			}

			z_strm_.avail_in = (unsigned int)nSizeReaded;
			z_strm_.next_in = buff_;
			strm_pos_ = strm_->getPosition();
			DoProgress();
		}

		last_code_ = inflate(&z_strm_, 0);

		if (!succeeded())
		{
			return -1;
		}
	}

	return tSizeToRead;
}



void* ZDecompressionStream::zlibAllocMem(ZDecompressionStream &ZStream, uInt Items, uInt Size)
{
	return ZStream.AllocStream( Items * Size );
}

void ZDecompressionStream::zlibFreeMem(ZDecompressionStream &ZStream, void *lpBlock)
{
	ZStream.SFree( lpBlock );
}

void* ZDecompressionStream::AllocStream(int size)
{
	return alloc_ ? alloc_->AllocBuffer((int)size) : malloc(size);
}

void ZDecompressionStream::SFree(void* ptr)
{
	alloc_ ? alloc_->FreeBuffer(ptr) : free(ptr);
}

void ZDecompressionStream::DoProgress()
{
}
