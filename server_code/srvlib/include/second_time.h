#ifndef _MINI_DATE_TIME_H_
#define _MINI_DATE_TIME_H_

//һ���������������
#include <time.h>

class SecondTime
{
public:
	//�����ʱ�����Ϳ�ʼ�����
	static const int YearBase = 2010;
	static const int BaseYear = 1900;//Ϊ������ֲ�ԣ���������ʹ��tm�����ʱ������1900���1��1���賿��ʼ��
	//����ʱ���Ƿ��Ѿ���ʼ��ʱ�ı�־λ
	static const unsigned int RecordFlag = 0x80000000;
	//������ֵ�λ��ʱ�������
	static const unsigned int SecOfMin  = 60;
	static const unsigned int SecOfHour = SecOfMin * 60;
	static const unsigned int SecOfDay  = SecOfHour * 24;
	static const unsigned int SecOfYear[2];
	static const unsigned int SecOfMonth[2][13];//����Ϊ�ڶ�������±꣬��ȥ�·�-1�Ĳ�����
	static const unsigned int MonthDays[2][13];//����Ϊ�ڶ�������±꣬��ȥ�·�-1�Ĳ�����

public:

	SecondTime& encode(const unsigned int year, const unsigned int mon, const unsigned int day,
	                   const unsigned int hour, const unsigned int min, const unsigned int sec);

	// ��MiniDataTimeת����ϵͳʱ�䡣��ʱֻ��ȷ���졣
	void decode(tm& sysTime);
	void decode(SystemTime& sysTime);
	time_t decode()		//ע�⣺����tm��decode��װת���ӿڣ����tm���޸�Ϊ�������˽ӿ�ҲҪ�޸�
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
		// ������ͬ�� BaseTime.encode(2010,1,4,0,0,0);
		const unsigned int BaseTime = 3 * 24 * 3600;// 2010.1.4����һ�������Ϊ�ο���
		const unsigned int SecOfWeek = 7 * 24 * 3600;
		return (tv - BaseTime) / SecOfWeek == (rhs.tv - BaseTime) / SecOfWeek;
	}

	//��SystemTime�ṹ����������ʱ��ֵ
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
	//��ʼ��¼ʱ�䣬timeOfNow������ʾ��ǰʱ��Ķ�ʱ������ֵ
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

	//��ȡ��ǰ����ʱ��Ķ�ʱ��ֵ
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
	//��ȡ�����賿��ʱ��
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
	//���������賿ʱ��
	inline static unsigned int yesterday()
	{
		return today() - 3600 * 24;
	}

	//���������賿��ֵ
	inline static unsigned int tomorrow()
	{
		return today() + 3600 * 24;
	}

	// ��������ڵ�ǰMiniDateTime��ָʾ��ʱ��������
	inline unsigned int rel_tomorrow()
	{
		unsigned v = tv & (~RecordFlag);
		v = (v + SecOfDay) / SecOfDay * SecOfDay;
		return (tv & RecordFlag) | v;
	}

	// // ��������ڵ�ǰMiniDateTime��ָʾ��ʱ���ĵ�ǰ��ʼʱ���
	inline unsigned int rel_today()
	{
		unsigned v = tv & (~RecordFlag);
		v = v / SecOfDay * SecOfDay;
		return (tv & RecordFlag) | v;
	}

	//�ж��Ƿ�������ĺ���
	inline static bool isLeapYear(const unsigned int year)
	{
		return ((year % 4) == 0) && ((year % 100 != 0) || (year % 400 == 0));
	}


public:
	//ת��Ϊunsigned int������ת�������
	inline operator unsigned int()
	{
		return tv;
	}
	//��unsigned int���Ƶ����������
	inline SecondTime& operator = (const unsigned int time)
	{
		tv = time;
		return *this;
	}
	//��������жϵ������
	inline bool operator == (const unsigned int time)
	{
		return tv == time;
	}
	//���ز����жϵ������
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
	//����+�������������Ƿ�ʹ�õı�־λ��������
	inline unsigned int operator + (const unsigned int time)
	{
		return ((tv & (~RecordFlag)) + (time & (~RecordFlag))) & (~RecordFlag);
	}
	//����-�������������Ƿ�ʹ�õı�־λ��������
	inline unsigned int operator - (const unsigned int time)
	{
		return ((tv & (~RecordFlag)) - (time & (~RecordFlag))) & (~RecordFlag);
	}
	//����+=�������������Ƿ�ʹ�õı�־λ��������
	inline SecondTime& operator += (const unsigned int time)
	{
		tv = (tv & RecordFlag) | (((tv & (~RecordFlag)) + (time & (~RecordFlag))) & (~RecordFlag));
		return *this;
	}
	//����-=�������������Ƿ�ʹ�õı�־λ��������
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
