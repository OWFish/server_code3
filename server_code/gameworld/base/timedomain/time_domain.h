#ifndef _TIME_DOMAIN_H_
#define _TIME_DOMAIN_H_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <map>
#include "timer.h"
#include "second_time.h"
#include "time_field.h"

/* ʱ����ṹ
rule ���� y.m.d-h:m ~/^ y.m.d-h:m [0,1,2,3..7]
~ ��ʾȷ��������ʱ���֮���ڣ�ƥ������
^ ��ʾǰ������ʱ������ɵ�ʱ��Σ� ƥ������
* ��ʾ������
[]�����ڼ��������[*] �� []��ʾ����

rule = "2015.10.1-10:0 ~ 2015.10.7-18:0 []"  10��1��10�㿪ʼ��7��18��������������ڼ�
= "2015.10.1-10:0 ~ 2015.10.7-18:0 [*]"  10��1��10�㿪ʼ��7��18��������������ڼ�
= "2015.10.1-10:0 ~ 2015.10.7-18:0 "  10��1��10�㿪ʼ��7��18��������������ڼ�

"*.8.1-*:* ^ *.9.15-*:* [0,6]"   ÿ��8��9�µ�1-15�ŵ���ĩ

"*.*.*-20:0 ^ *.*.*-22:00 "   ÿ����8�㵽10��
"*.*.*-20:0 ^ *.*.*-22:00 [3,6]"   ��3��6 ��8�㵽10��
"*.*.*-22:0 ^ *.*.*-10:00 "   ÿ����10����������10��
!!!   "*.*.1-22:0 ^ *.*.2-10:00 "   1����10����2����10�� 2����10����3����10��

*/

class TimeField :public BaseTimeField
{
public:
	void onStart();
	void onEnd();
	void regStart(TimerFunc func);
	void regEnd(TimerFunc func);
private:
	TimerFuncList start_callback_funcs;
	TimerFuncList end_callback_funcs;
};

typedef time_t(*NowTimeFunc)(time_t*);
class TimeDomain
{
	friend class TimeField;
public:
	static TimeDomain& getInstance();
	bool checkTime(const std::string &rule);//���÷�Χ�Ƿ��ڻ״̬
	time_t getStartTime(const std::string &rule);
	time_t getEndTime(const std::string &rule);
	bool regStart(const std::string &rule, TimerFunc func);
	bool regEnd(const std::string &rule, TimerFunc func);
	void RunOne(SecondTime now);

	static NowTimeFunc getNowTime; //Ĭ����time(NULL)��ȡ��ǰʱ�䣬������
private:
	TimeDomain();
	TimeField* getField(const std::string &rule);
	void onRun(time_t now);
private:
	typedef std::list<int> TimeFields;

	int index_;
	Timer check_t_;
	std::map<int, TimeField> fields_;
	std::map<std::string, int> field_index_;
	std::map<time_t, TimeFields> start_time_map_;
	std::map<time_t, TimeFields> end_time_map_;
};


#endif // !TIME_DOMAIN_H
