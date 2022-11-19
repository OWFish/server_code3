//#include <Windows.h>
#include <stdio.h>
#include "share_util.h"
#include "second_time.h"

const unsigned int SecondTime::SecOfYear[2] = { 365 * SecOfDay, 366 * SecOfDay };

const unsigned int SecondTime::SecOfMonth[2][13] =
{
	{0, 31 * SecOfDay, 28 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay},
	{0, 31 * SecOfDay, 29 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay, 30 * SecOfDay, 31 * SecOfDay}
};

const unsigned int SecondTime::MonthDays[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

SecondTime& SecondTime::encode(const unsigned int year, const unsigned int mon, const unsigned int day, const unsigned int hour, const unsigned int min, const unsigned int sec)
{
	int i;
	unsigned int v = 0;

	//计算年份经过的秒数
	for (i = year - 1; i >= YearBase; --i)
	{
		v += SecOfYear[isLeapYear(i)];
	}

	//计算当年1月到本月的秒数
	bool boLeepYear = isLeapYear(year);

	for (i = mon - 1; i >= 1; --i)
	{
		v += SecOfMonth[boLeepYear][i];
	}

	//计算当年1号到今天的秒数
	v += (day - 1) * SecOfDay;

	//计算今天0点到现在的秒数
	v += hour * SecOfHour;

	//计算当前小时的0分到现在的秒数
	v += min * SecOfMin;

	v += sec;

	tv = (tv & RecordFlag) | (v & (~RecordFlag));
	return *this;
}

void SecondTime::decode(tm& sysTime)
{
	unsigned int v = tv & (~RecordFlag);

	// 年
	int year = YearBase;

	for( ; ;)
	{
		unsigned int nSecOfCurrYear = SecOfYear[isLeapYear(year)];

		if (v >= nSecOfCurrYear)
		{
			v -= nSecOfCurrYear;
			year++;
		}
		else
			break;
	}

	// 月
	bool bIsLeepYear = isLeapYear(year);
	int month = 1;										// index based 1 <<<<

	for( ; ;)
	{
		unsigned int nSecOfCurrMonth = SecOfMonth[bIsLeepYear][month];

		if (v >= nSecOfCurrMonth)
		{
			v -= nSecOfCurrMonth;
			month++;
		}
		else
			break;
	}

	// 日
	int day = v / SecOfDay + 1;								// index based 1 <<<<

	//memset(&sysTime, 0, sizeof(sysTime));
	sysTime.tm_year	= year;
	sysTime.tm_mon	= month;
	sysTime.tm_mday	= day;
	//小时、分、秒
	unsigned int SecOfToday = v % (24 * 3600);
	sysTime.tm_hour = SecOfToday / 3600;
	sysTime.tm_min = (SecOfToday % 3600) / 60;
	sysTime.tm_sec = SecOfToday % 60;
}

void SecondTime::decode(SystemTime& sysTime)
{
	unsigned int v = tv & (~RecordFlag);

	// 年
	int year = YearBase;

	for( ; ;)
	{
		unsigned int nSecOfCurrYear = SecOfYear[isLeapYear(year)];

		if (v >= nSecOfCurrYear)
		{
			v -= nSecOfCurrYear;
			year++;
		}
		else
			break;
	}

	// 月
	bool bIsLeepYear = isLeapYear(year);
	int month = 1;										// index based 1 <<<<

	for( ; ;)
	{
		unsigned int nSecOfCurrMonth = SecOfMonth[bIsLeepYear][month];

		if (v >= nSecOfCurrMonth)
		{
			v -= nSecOfCurrMonth;
			month++;
		}
		else
			break;
	}

	// 日
	int day = v / SecOfDay + 1;								// index based 1 <<<<

	//memset(&sysTime, 0, sizeof(sysTime));
	sysTime.year_	= year;
	sysTime.mon_	= month;
	sysTime.mday_	= day;
	//小时、分、秒
	unsigned int SecOfToday = v % (24 * 3600);
	sysTime.hour_ = SecOfToday / 3600;
	sysTime.min_ = (SecOfToday % 3600) / 60;
	sysTime.sec_ = SecOfToday % 60;
}
