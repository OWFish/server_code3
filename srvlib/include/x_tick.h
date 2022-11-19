#ifndef _MTICK_H_
#define _MTICK_H_


/******************************************************************
 *
 *	$ 增强GetTickCount函数库 $
 *  
 *  - 主要功能 - 
 *
 *	可使用64位的TickCount。内部解决了TickCount在超过49天后重新开始的问题。
 *  同时，提供了一个在整个进程中使用同步的TickCount的机制，即通过SetTickCountEx
 *  函数来设置同步的时间值，从而避免在多处理器中不同处理器之间的频率差异带来的问题
 *
 *****************************************************************/
#include "os_def.h"

#define _getTickCount		tick64::GetTickCountEx
//#define _timeGetTime		tick64::GetTickCountEx

namespace tick64
{
	//取机器运行时间的函数，函数返回的是毫秒值，
	//如果硬件支持查询PerformanceCounter则可避免49天的整数溢出的问题
	/***
	  实际测试后此函数性能较差，因为查询CPU中断会导致进入内核并可能挂起
	  r3级的线程。此外在多处理器中如果各个处理器之间频率有误差，则可能
	  导致由不同线程的连续的两次调用，后者取得的时间值比前者要晚的问题。
	***/

	#ifdef _MTICK64
	typedef int64_t TICKCOUNT64;
	typedef TICKCOUNT64	TICKCOUNT;
	#	define GetTickCountEx		GetTickCount64
	TICKCOUNT64 GetTickCount64();
	#else
	typedef int64_t	TICKCOUNT;
	//typedef TICKCOUNT32	TICKCOUNT;	
	#	define GetTickCountEx		GetTickCount32
	TICKCOUNT GetTickCount32();
	#endif

};

#endif
