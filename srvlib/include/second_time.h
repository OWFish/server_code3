#ifndef _MINI_DATE_TIME_H_
#define _MINI_DATE_TIME_H_

//一种以秒数定义的类
#include <time.h>

class SecondTime
{
public:
	//定义短时间类型开始的年份
	static const int YearBase = 2010;
	static const int BaseYear = 1900;//为方便移植性，日期类型使用tm，这个时间是以1900年的1月1日凌晨开始算
	//定义时间是否已经开始计时的标志位
	static const unsigned int RecordFlag = 0x80000000;
	//定义各种单位的时间的秒数
	static const unsigned int SecOfMin  = 60;
	static const unsigned int SecOfHour = SecOfMin * 60;
	static const unsigned int SecOfDay  = SecOfHour * 24;
	static const unsigned int SecOfYear[2];
	static const unsigned int SecOfMonth[2][13];//以月为第二数组的下标，免去月份-1的操作！
	static const unsigned int MonthDays[2][13];//以月为第二数组的下标，免去月份-1的操作！

public:

	SecondTime& encode(const unsigned int year, const unsigned int mon, const unsigned int day,
	                   const unsigned int hour, const unsigned int min, const unsigned int sec);

	// 从MiniDataTime转化到系统时间。暂时只精确到天。
	void decode(tm& sysTime);
	void decode(SystemTime& sysTime);
	time_t decode()		//注意：根据tm的decode封装转换接口，如果tm的修改为正常，此接口也要修改
	{
		tm hehe;
		decode(hehe);
		hehe.tm_year -= 1900;	//***
		hehe.tm_mon -= 1;		//***
		return mktime(&hehe);
	}

	inline bool isSameDay(const SecondTime& rhs)
	{
		return ((tv & (~RecordFlag)) / SecOfDay) == ((rhs.tv & (~RecordFlag)) / SecOfDay) ? true : false;
	}

	inline bool isSameWeek(const SecondTime& rhs)
	{
		STATIC_ASSERT(SecondTime::YearBase == 2010);
		// 这代码等同于 BaseTime.encode(2010,1,4,0,0,0);
		const unsigned int BaseTime = 3 * 24 * 3600;// 2010.1.4是周一，以这个为参考点
		const unsigned int SecOfWeek = 7 * 24 * 3600;
		return (tv - BaseTime) / SecOfWeek == (rhs.tv - BaseTime) / SecOfWeek;
	}

	//从SystemTime结构中设置日期时间值
	inline SecondTime& encode(time_t systime)
	{
		return encode(*localtime(&systime));
	}
	inline SecondTime& encode(const tm& sysTime)
	{
		return encode(1900 + sysTime.tm_year, sysTime.tm_mon + 1, sysTime.tm_mday, sysTime.tm_hour, sysTime.tm_min, sysTime.tm_sec);
	}
	inline SecondTime& encode(const SystemTime& sysTime)
	{
		return encode(sysTime.year_, sysTime.mon_, sysTime.mday_, sysTime.hour_, sysTime.min_, sysTime.sec_);
	}
	//开始记录时间，timeOfNow参数表示当前时间的短时间类型值
	inline SecondTime& startRecord(const unsigned int timeOfNow)
	{
		if (!(tv & RecordFlag))
			tv = RecordFlag | ((timeOfNow & (~RecordFlag)) + tv);

		return *this;
	}
	bool isStartRecord()
	{
		return (tv & RecordFlag) ? true : false;
	}

	//获取当前日期时间的短时间值
	inline static unsigned int now()
	{
		SecondTime tv;
		time_t timep;
		struct tm* sysTime;
		time(&timep);
		sysTime = localtime(&timep);
		tv.encode(1900 + sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_hour, sysTime->tm_min, sysTime->tm_sec);
		return tv.tv;
	}
	//获取今天凌晨的时间
	inline static unsigned int today()
	{
		SecondTime tv;
		time_t timep;
		struct tm* sysTime;
		time(&timep);
		sysTime = localtime(&timep);
		tv.encode(1900 + sysTime->tm_year, sysTime->tm_mon + 1, sysTime->tm_mday, 0, 0, 0);
		return tv.tv;
	}
	//计算昨天凌晨时间
	inline static unsigned int yesterday()
	{
		return today() - 3600 * 24;
	}

	//计算明日凌晨的值
	inline static unsigned int tomorrow()
	{
		return today() + 3600 * 24;
	}

	// 计算相对于当前MiniDateTime所指示的时间点的明天
	inline unsigned int rel_tomorrow()
	{
		unsigned v = tv & (~RecordFlag);
		v = (v + SecOfDay) / SecOfDay * SecOfDay;
		return (tv & RecordFlag) | v;
	}

	// // 计算相对于当前MiniDateTime所指示的时间点的当前开始时间点
	inline unsigned int rel_today()
	{
		unsigned v = tv & (~RecordFlag);
		v = v / SecOfDay * SecOfDay;
		return (tv & RecordFlag) | v;
	}

	//判断是否是闰年的函数
	inline static bool isLeapYear(const unsigned int year)
	{
		return ((year % 4) == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}


public:
	//转换为unsigned int的类型转换运算符
	inline operator unsigned int()
	{
		return tv;
	}
	//从unsigned int复制的运算符函数
	inline SecondTime& operator = (const unsigned int time)
	{
		tv = time;
		return *this;
	}
	//重载相等判断的运算符
	inline bool operator == (const unsigned int time)
	{
		return tv == time;
	}
	//重载不等判断的运算符
	inline bool operator != (const unsigned int time)
	{
		return tv != time;
	}
	inline bool operator > (const unsigned int time)
	{
		return (tv & (~RecordFlag)) > (time & (~RecordFlag));
	}
	inline bool operator >= (const unsigned int time)
	{
		return (tv & (~RecordFlag)) >= (time & (~RecordFlag));
	}
	inline bool operator < (const unsigned int time)
	{
		return (tv & (~RecordFlag)) < (time & (~RecordFlag));
	}
	inline bool operator <= (const unsigned int time)
	{
		return (tv & (~RecordFlag)) <= (time & (~RecordFlag));
	}
	//重载+运算符，避免对是否使用的标志位进行运算
	inline unsigned int operator + (const unsigned int time)
	{
		return ((tv & (~RecordFlag)) + (time & (~RecordFlag))) & (~RecordFlag);
	}
	//重载-运算符，避免对是否使用的标志位进行运算
	inline unsigned int operator - (const unsigned int time)
	{
		return ((tv & (~RecordFlag)) - (time & (~RecordFlag))) & (~RecordFlag);
	}
	//重载+=运算符，避免对是否使用的标志位进行运算
	inline SecondTime& operator += (const unsigned int time)
	{
		tv = (tv & RecordFlag) | (((tv & (~RecordFlag)) + (time & (~RecordFlag))) & (~RecordFlag));
		return *this;
	}
	//重载-=运算符，避免对是否使用的标志位进行运算
	inline SecondTime& operator -= (const unsigned int time)
	{
		tv = (tv & RecordFlag) | (((tv & (~RecordFlag)) - (time & (~RecordFlag))) & (~RecordFlag));
		return *this;
	}
public:
	SecondTime()
	{
		tv = 0;
	}
	SecondTime(const SecondTime& mt)
	{
		tv = mt.tv;
	}
	SecondTime(const unsigned int tva)
	{
		tv = tva;
	}
public:
	unsigned int tv;
};

#endif
