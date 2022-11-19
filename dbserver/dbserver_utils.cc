#include "StdAfx.h"

static int alloc_series_ = 0;

ItemSeries allocSeries(int serverid)
{
	ItemSeries series;
	series.t.time_ = getMiniDateTime();
	series.t.sid_ = (uint16_t)serverid;
	series.t.series_ = (uint16_t)alloc_series_;
	alloc_series_++;
	return series;
}

unsigned int getMiniDateTime()
{
	SecondTime sec;
	SystemTime sys_time;
	GetSystemTime(sys_time);
	sec = sec.encode(sys_time);
	return sec;
}

