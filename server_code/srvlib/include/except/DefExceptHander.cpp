#ifdef _MSC_VER

#include <tchar.h>
#include <Windows.h>
#include <stdio.h>
#include <_ast.h>

#include <x_tick.h>
#include "share_util.h"
#include "DefExceptHander.h"

inline const char* GetAccessViolationOperationName(ULONG_PTR info)
{
	if ( info == 0 )
		return ("read");
	else if ( info == 1 )
		return ("write");
	else if ( info == 8 )
		return ("execute");
	else return ("unknown operation");
}

DWORD DefaultExceptHandler(const LPEXCEPTION_POINTERS lpPointers)
{
#define eprt(fmt, ...) sptr += _sntprintf(sptr, sErrBuf + ArrayCount(sErrBuf) - sptr - 1, fmt, __VA_ARGS__)
	
	TCHAR sErrBuf[1024], *sptr = sErrBuf;
	
	switch(lpPointers->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		eprt(("Access Violation at Address %0.16LX %s of Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress,
			GetAccessViolationOperationName(lpPointers->ExceptionRecord->ExceptionInformation[0]),
			lpPointers->ExceptionRecord->ExceptionInformation[1]);
		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		eprt(("Misaligment Address Access at Address %0.16LX Access of Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress,
			lpPointers->ExceptionRecord->ExceptionInformation[1]);
		break;
	case EXCEPTION_BREAKPOINT:
		eprt(("A BreakPoint was encountered at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_SINGLE_STEP:
		eprt(("A Single-Step instruction has been executed at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		eprt(("Array Access Bounds-Out at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_DENORMAL_OPERAND:
		eprt(("Denormaled floating-point operand at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		eprt(("Division by Zero at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_INEXACT_RESULT:
		eprt(("Cannot represent a decimal fraction of a floating-point operation at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_INVALID_OPERATION:
		eprt(("Invalid floating-point operation at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_OVERFLOW:
		eprt(("Floating-point operation Overflow at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_STACK_CHECK:
		eprt(("Floating-point stack Overflow or Underflow at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_FLT_UNDERFLOW:
		eprt(("Floating-point operation Underflow at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		eprt(("Integer Division By Zero at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_INT_OVERFLOW:
		eprt(("Integer operation Overflow at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_PRIV_INSTRUCTION:
		eprt(("Privileged Instuction at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_IN_PAGE_ERROR:
		eprt(("Page Error at Address %0.16LX %s of Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress,
			GetAccessViolationOperationName(lpPointers->ExceptionRecord->ExceptionInformation[0]),
			lpPointers->ExceptionRecord->ExceptionInformation[1]);
		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:
		eprt(("Illegal Instuction at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		eprt(("None-Continuable Exception at Address %0.16LX, Going to Abort"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_STACK_OVERFLOW:
		eprt(("Stack Overflow at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_INVALID_DISPOSITION:
		eprt(("Invalid Disposition at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case EXCEPTION_INVALID_HANDLE:
		eprt(("Invalid Handle at Address %0.16LX"),
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		break;
	case 0xe06d7363://C++ exception
		eprt(("Unhandled C++ Exception at Address %0.16LX"), (size_t)lpPointers->ExceptionRecord->ExceptionAddress);
		//ExceptionRecord->ExceptionInformation[1] = throw 的对象实例
		//ExceptionRecord->ExceptionInformation[2] = throw 的对象类型信息
		break;
	default:
		eprt(("Unexpected Exception Code %0.16LX at Address %0.16LX\r\n [0]=%0.16LX [1]=%0.16LX [2]=%0.16LX [3]=%0.16LX"),
			lpPointers->ExceptionRecord->ExceptionCode,
			(size_t)lpPointers->ExceptionRecord->ExceptionAddress,
			(size_t)lpPointers->ExceptionRecord->ExceptionInformation[0],
			(size_t)lpPointers->ExceptionRecord->ExceptionInformation[1],
			(size_t)lpPointers->ExceptionRecord->ExceptionInformation[2],
			(size_t)lpPointers->ExceptionRecord->ExceptionInformation[3]);
		break;
	}

#undef eprt
	TRACE(("%s\r\n"), sErrBuf);
	OutputMsg(rmError, sErrBuf);
	return EXCEPTION_EXECUTE_HANDLER;//继续从异常处理函数中恢复执行
}

#endif

