#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include "_ast.h"
#include "share_util.h"
#include "stream.h"

using namespace stream;

FileStream::FileStream(const char* lpFileName, unsigned int dwAccessType, BaseAllocator* alloc) : BaseStream(alloc)
{
	unsigned int dwWin32CreationDisposition = 0;
#ifndef _MSC_VER
	fp_ = NULL;
#else
	if (dwAccessType & faCreate)
		dwWin32CreationDisposition = CREATE_ALWAYS;
	else dwWin32CreationDisposition = OPEN_EXISTING;
#endif

	construct(lpFileName, dwAccessType, dwWin32CreationDisposition);
}

FileStream::FileStream(const char* lpFileName, unsigned int dwAccessType, OpenDisposition eWin32CreateionDisposition, BaseAllocator* alloc) : BaseStream(alloc)
{
	construct(lpFileName, dwAccessType, eWin32CreateionDisposition);
}

FileStream::~FileStream()
{
#ifdef _MSC_VER

	if (hdl_ != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hdl_);
	}

#else

	if (fp_) fclose(fp_);

#endif
}

void FileStream::setFileName(const char* lpFileName)
{
	_STRNCPY_A(fn_, lpFileName);
}

void FileStream::construct(const char* lpFileName, unsigned int dwAccessType, unsigned int dwWin32CreationDisposition)
{
	setFileName(lpFileName);

#ifdef _MSC_VER
	unsigned int dwDesiredAccess, dwShareMode ;

	dwDesiredAccess = dwShareMode = 0;

	if (dwAccessType & faCreate)
	{
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
	}
	else
	{
		if (dwAccessType & faRead) dwDesiredAccess |= GENERIC_READ;

		if (dwAccessType & faWrite) dwDesiredAccess |= GENERIC_WRITE;

		if (dwAccessType & faShareRead)
		{
			dwShareMode |= FILE_SHARE_READ;
			dwDesiredAccess |= GENERIC_READ;
		}

		if (dwAccessType & faShareWrite)
		{
			dwShareMode |= FILE_SHARE_WRITE;
			dwDesiredAccess |= GENERIC_WRITE;
		}

		if (dwAccessType & faShareDelete) dwShareMode |= FILE_SHARE_DELETE;
	}

	setHandle(CreateFile(fn_, dwDesiredAccess, dwShareMode, NULL, dwWin32CreationDisposition, 0, NULL));
#else
	const char* mode = "r";

	if (dwAccessType & faRead)
		mode = "r";
	else
		mode = "w";

	fp_ = fopen(fn_, mode);
#endif
}


int FileStream::seek(const int tOffset, const int Origin)
{
#ifdef _MSC_VER
	LARGE_INTEGER li, nNewPointer;
	li.QuadPart = tOffset;

	if (SetFilePointerEx(hdl_, li, &nNewPointer, Origin))
		return (int)nNewPointer.QuadPart;
	else return -1;

#else

	if (fp_)
	{
		if (!fseek(fp_, tOffset, Origin))
		{
			return ftell(fp_);
		}
		else
		{
			return -1;
		}
	}
	return 0;
#endif
}

int FileStream::read(void* lpBuffer, const int tSizeToRead)
{
#ifdef _MSC_VER
	DWORD dwBytesReaded;

	if (ReadFile(hdl_, lpBuffer, (unsigned int)tSizeToRead, &dwBytesReaded, NULL))
		return dwBytesReaded;
	else return -1;
#else
	if (fp_)
	{
		return fread(lpBuffer, 1, tSizeToRead, fp_);
	}
	return 0;
#endif
}

int FileStream::write(const void* lpBuffer, const size_t tSizeToWrite)
{
	if (!lpBuffer) return 0;

#ifdef _MSC_VER
	DWORD dwBytesWriten;

	if (WriteFile(hdl_, lpBuffer, (unsigned int)tSizeToWrite, &dwBytesWriten, NULL))
		return dwBytesWriten;
	else return -1;
#else
	if (fp_ && lpBuffer)
	{
		return fwrite(lpBuffer, 1, tSizeToWrite, fp_);
	}
	return 0;
#endif
}
#ifdef _MSC_VER
void FileStream::setHandle(HANDLE Handle)
{
	hdl_ = Handle;
}
#endif

