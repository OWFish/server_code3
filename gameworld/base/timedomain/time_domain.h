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

/* 时间域结构
rule 规则 y.m.d-h:m ~/^ y.m.d-h:m [0,1,2,3..7]
~ 表示确定的两个时间点之间内，匹配星期
^ 表示前后两个时间域组成的时间段， 匹配星期
* 表示不限制
[]是星期几，不填或[*] 或 []表示不限

rule = "2015.10.1-10:0 ~ 2015.10.7-18:0 []"  10月1日10点开始，7日18点结束，不限星期几
= "2015.10.1-10:0 ~ 2015.10.7-18:0 [*]"  10月1日10点开始，7日18点结束，不限星期几
= "2015.10.1-10:0 ~ 2015.10.7-18:0 "  10月1日10点开始，7日18点结束，不限星期几

"*.8.1-*:* ^ *.9.15-*:* [0,6]"   每年8月9月的1-15号的周末

"*.*.*-20:0 ^ *.*.*-22:00 "   每天晚8点到10点
"*.*.*-20:0 ^ *.*.*-22:00 [3,6]"   周3周6 晚8点到10点
"*.*.*-22:0 ^ *.*.*-10:00 "   每天晚10点至次日早10点
!!!   "*.*.1-22:0 ^ *.*.2-10:00 "   1日晚10点至2日早10点 2日晚10点日3日早10点

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
	bool checkTime(const std::string &rule);//检查该范围是否处于活动状态
	time_t getStartTime(const std::string &rule);
	time_t getEndTime(const std::string &rule);
	bool regStart(const std::string &rule, TimerFunc func);
	bool regEnd(const std::string &rule, TimerFunc func);
	void RunOne(SecondTime now);

	static NowTimeFunc getNowTime; //默认是time(NULL)获取当前时间，可重载
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
