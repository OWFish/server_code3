#include "os_def.h"


#include "stream.h"
#include "zstream.h"

using namespace zstream;

BaseZStream::BaseZStream(BaseStream &stream, BaseAllocator* alloc)
:Inherited(alloc)
{
	strm_ = &stream;
	strm_pos_ = stream.getPosition();

	ZeroMemory( &z_strm_, sizeof(z_strm_) );

	z_strm_.zalloc = (alloc_func)zlibAllocMem;
	z_strm_.zfree = (free_func)zlibFreeMem;
	z_strm_.opaque = this;

	last_code_ = Z_OK;
}

BaseZStream::~BaseZStream()
{
}

void* BaseZStream::zlibAllocMem(BaseZStream &ZStream, uInt Items, uInt Size)
{
	return ZStream.AllocStream( Items * Size );
}

void BaseZStream::zlibFreeMem(BaseZStream &ZStream, void *lpBlock)
{
	ZStream.Free( lpBlock );
}

void* BaseZStream::AllocStream(int size)
{
	return alloc_ ? alloc_->AllocBuffer((int)size) : malloc(size);
}

void BaseZStream::Free(void* ptr)
{
	alloc_ ? alloc_->FreeBuffer(ptr) : free(ptr);
}

void BaseZStream::DoProgress()
{
}

