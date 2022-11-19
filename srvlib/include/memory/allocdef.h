#ifndef _ALLOCDEF_H_
#define _ALLOCDEF_H_

#include "os_def.h"
/************************************************************************
* 内存分配的头文件定义
*
*
************************************************************************/
#ifdef _MEMORY_TRACE_
typedef struct
{
	size_t buff_size_;
	struct
	{
		const char* fn_;		//申请内存块的代码位置，用于调试
		int line_;
	} al_, fl_;
	bool using_flag_;
} AllocBuffHead;
#endif

#endif	//end _ALLOCDEF_H_
