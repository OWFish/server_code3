#include "os_def.h"

#include "stream.h"
#include <zlib.h>
#include "zstream.h"

using namespace zstream;

ZCompressionStream::ZCompressionStream(BaseStream& destStream, CompressionLevel CmprsLvl, BaseAllocator* alloc)
	: Inherited(destStream, alloc)
{
	static const int Levels[clMax + 1] = { Z_NO_COMPRESSION, Z_BEST_SPEED, Z_DEFAULT_COMPRESSION, Z_BEST_COMPRESSION };

	z_strm_.next_out = buff_;
	z_strm_.avail_out = sizeof(buff_);
	last_code_ = deflateInit_(&z_strm_, Levels[CmprsLvl], zlib_version, sizeof(z_strm_));
}

ZCompressionStream::~ZCompressionStream()
{
	finish();
	last_code_ = deflateEnd(&z_strm_);
}

int ZCompressionStream::seek(const int tOffset, const int Origin)
{
	if (tOffset == 0 && Origin == SEEK_CUR)
		return z_strm_.total_in;

	return 0;
}

int ZCompressionStream::write(const void* lpBuffer, const size_t tSizeToWrite)
{
	z_strm_.next_in = (Bytef*)lpBuffer;
	z_strm_.avail_in = (uInt)tSizeToWrite;

	if (strm_->getPosition() != strm_pos_)
	{
		strm_->setPosition(strm_pos_);
	}

	while (z_strm_.avail_in > 0)
	{
		last_code_ = deflate(&z_strm_, 0);

		if (!succeeded())
			break;

		if (z_strm_.avail_out == 0)
		{
			strm_->write(buff_, sizeof(buff_));
			z_strm_.next_out = buff_;
			z_strm_.avail_out = sizeof(buff_);
			strm_pos_ = strm_->getPosition();
			DoProgress();
		}
	}

	return (int)tSizeToWrite;
}

void ZCompressionStream::finish()
{
	if (!z_strm_.next_in)
		return;

	z_strm_.next_in = NULL;
	z_strm_.avail_in = 0;

	if (strm_->getPosition() != strm_pos_)
	{
		strm_->setPosition(strm_pos_);
	}

	for( ; ;)
	{
		last_code_ = deflate(&z_strm_, Z_FINISH);

		if (!succeeded())
			break;

		if (last_code_ == Z_STREAM_END || z_strm_.avail_out != 0)
			break;

		strm_->write(buff_, sizeof(buff_));
		z_strm_.next_out = buff_;
		z_strm_.avail_out = sizeof(buff_);
	}

	if (z_strm_.avail_out < sizeof(buff_))
	{
		strm_->write(buff_, sizeof(buff_) - z_strm_.avail_out);
	}
}
