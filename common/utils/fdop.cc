#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include "_ast.h"
#include "share_util.h"
#include "fdop.h"

#ifndef _MSC_VER
#include <sys/stat.h>
#endif

using namespace FDOP;

bool FDOP::FileExists(const char* sFilePath)
{
#ifdef _MSC_VER
	DWORD dwAttr = GetFileAttributes(sFilePath);

	if (dwAttr == (DWORD) - 1)
		return false;
	else return true;

#else

	if (!access(sFilePath, F_OK))
	{
		return true;
	}
	else
	{
		return false;
	}

#endif
}


bool FDOP::DeepCreateDirectory(const char* sDirPath)
{
#ifdef _MSC_VER
	char sPath[4096];
	LPTSTR sPathPtr = sPath;
	size_t dwNameLen, dwBufLen = ArrayCount(sPath) - 1;
	DWORD dwAttr;

	while (true)
	{
		dwNameLen = ExtractTopDirectoryName(sDirPath, &sDirPath, sPathPtr, dwBufLen);

		//如果目录名称长度超过目录缓冲区长度则放弃
		if (dwNameLen >= dwBufLen)
			return false;

		//如果目录名称长度为0则表示所有目录均已创建完成
		if (dwNameLen == 0)
			return true;

		sPathPtr += dwNameLen;

		//如果目录名称不是驱动器名称则检查和创建目录
		if (sPathPtr[-1] != ':')
		{
			//如果目录不存在则创建此目录
			dwAttr = GetFileAttributes(sPath);

			if ((dwAttr == (DWORD) - 1 && GetLastError() == ERROR_FILE_NOT_FOUND))
			{
				if (!CreateDirectory(sPath, NULL))
					return false;
			}
			//如果文件存在且文件不是目录则返回false
			else if (!(dwAttr & FILE_ATTRIBUTE_DIRECTORY))
			{
				return false;
			}
		}

		sPathPtr[0] = '\\';
		sPathPtr++;

		if (dwBufLen > dwNameLen)
			dwBufLen -= dwNameLen + 1;
		else dwBufLen = 0;
	}

	return false;
#else
	char dirName[256];
	_STRNCPY_A(dirName, sDirPath);
	int len = strlen(dirName);

	if (dirName[len - 1] != '/')
		_STRNCAT_A(dirName,   "/");

	len = strlen(dirName);

	for (int i = 1; i < len; i++)
	{
		if (dirName[i] == '/')
		{
			dirName[i] = 0;
			if (access(dirName, F_OK) != 0)
			{
				if (mkdir(dirName, 0755) == -1)
				{
					//OutputMsg(rmError, "mkdir error, %s", dirName);
					return false;
				}
			}

			dirName[i] = '/';
		}
	}

	return true;
#endif
}


size_t FDOP::ExtractFileDirectory(const char* sFilePath, char* sDirBuf, size_t dwBufLen)
{
	const char* sDirEnd = sFilePath + strlen(sFilePath) - 1;

	while (sDirEnd >= sFilePath && *sDirEnd != '/' && *sDirEnd != '\\')
	{
		sDirEnd--;
	}

	if (sDirEnd > sFilePath)
	{
		size_t dwNameLen = sDirEnd - sFilePath;

		if (dwBufLen > 0)
		{
			if (dwBufLen > dwNameLen)
				dwBufLen = dwNameLen;
			else dwBufLen--;

			memcpy(sDirBuf, sFilePath, sizeof(*sDirBuf) * dwBufLen);
			sDirBuf[dwBufLen] = 0;
		}

		return dwNameLen;
	}

	return 0;
}

size_t FDOP::ExtractTopDirectoryName(const char* sDirPath, const char* *ppChildDirPath, char* sDirName, size_t dwBufLen)
{
	const char* sNameEnd;

	//跳过目录名称前连续的'/'或'\'
	while (*sDirPath && (*sDirPath == '/' || *sDirPath == '\\'))
	{
		sDirPath++;
	}

	sNameEnd = sDirPath;

	//定位目录名称起始的位置
	while (*sNameEnd)
	{
		if (*sNameEnd == '/' || *sNameEnd == '\\')
			break;

		sNameEnd++;
	}

	//拷贝目录名称
	if (sNameEnd > sDirPath)
	{
		size_t dwNameLen = sNameEnd - sDirPath;

		if (dwBufLen > 0)
		{
			if (dwBufLen > dwNameLen)
				dwBufLen = dwNameLen;
			else dwBufLen--;

			memcpy(sDirName, sDirPath, sizeof(*sDirPath) * dwBufLen);
			sDirName[dwBufLen] = 0;

			if (ppChildDirPath)
				*ppChildDirPath = sNameEnd;
		}

		return dwNameLen;
	}

	return 0;
}

size_t FDOP::ExtractFileName(const char* sFilePath, char* sNameBuf, size_t dwBufLen)
{
	const char* sNameStart;
	const char* sNameEnd = sFilePath + strlen(sFilePath) - 1;

	//跳过目录名称后连续的'/'或'\'
	while (sNameEnd >= sFilePath && (*sNameEnd == '/' || *sNameEnd == '\\'))
	{
		sNameEnd--;
	}

	sNameStart = sNameEnd;
	sNameEnd++;

	//定位目录名称起始的位置
	while (sNameStart >= sFilePath)
	{
		if (*sNameStart == '/' || *sNameStart == '\\')
			break;

		sNameStart--;
	}

	sNameStart++;

	//拷贝目录名称
	if (sNameStart < sNameEnd)
	{
		size_t dwNameLen = sNameEnd - sNameStart;

		if (dwBufLen > 0)
		{
			if (dwBufLen > dwNameLen)
				dwBufLen = dwNameLen;
			else dwBufLen--;

			memcpy(sNameBuf, sNameStart, sizeof(*sNameStart) * dwBufLen);
			sNameBuf[dwBufLen] = 0;
		}

		return dwNameLen;
	}

	return 0;
}



