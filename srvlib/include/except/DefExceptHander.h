#ifndef _DEF_EXCEPT_HANDLE_H_
#define _DEF_EXCEPT_HANDLE_H_

/************************************************************************/
/* 
/*                    默认局部异常处理记录函数库
/*
/*   适用于在__try ... __except块中对异常进行记录并恢复程序的执行。DefaultExceptHandler
/* 函数会格式化各种常见的异常类型并在调试器中以及通过OutputMsg函数输出异常记录。
/*
/*   使用示范：
/*   __try
/*   {
/*      //进行任何可能产生异常的代码或函数调用
/*   }
/*   __except(DefaultExceptHandler(GetExceptionInformation()))
/*   {
/*      //当异常发生后的处理代码
/*   }
/*
/************************************************************************/
DWORD DefaultExceptHandler(const LPEXCEPTION_POINTERS lpPointers);

#endif

