#ifndef _ALLOCDEF_H_
#define _ALLOCDEF_H_

#include "os_def.h"
/************************************************************************
* �ڴ�����ͷ�ļ�����
*
*
************************************************************************/
#ifdef _MEMORY_TRACE_
typedef struct
{
	size_t buff_size_;
	struct
	{
		const char* fn_;		//�����ڴ��Ĵ���λ�ã����ڵ���
		int line_;
	} al_, fl_;
	bool using_flag_;
} AllocBuffHead;
#endif

#endif	//end _ALLOCDEF_H_
