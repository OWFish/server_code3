#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif


Timer::Timer(int i)
{
	INTERVAL = i;
	next_t_ = GameTickCount() + INTERVAL;
}
