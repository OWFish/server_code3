#include <stdio.h>
#include "os_def.h"
#include "_ast.h"

#include "share_util.h"
#include "ansi_string.hpp"

const char* string::AnsiString::EMPTY_STR = "\0";

size_t string::AnsiString::format(const char* fmt, ...)
{
	va_list	args;
	size_t Result = 0;

	va_start(args, fmt);
	Result = format_args(fmt, args);
	va_end(args);
	return Result;
}

size_t string::AnsiString::format_args(const char* fmt, va_list _Args)
{
	CharType buffer[4096 / sizeof(CharType)];
	size_t Result = 0;

	Result = VSNPRINTFA(buffer, ArrayCount(buffer), fmt, _Args);
	if (Result >= 0) buffer[Result] = 0;

	setData(buffer);
	return Result;
}




