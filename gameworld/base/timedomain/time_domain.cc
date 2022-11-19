#include "StdAfx.h"
#include "time_domain.h"


using namespace std;


time_t getNowTimeAdapter(time_t *m)
{
	SystemTime syt;
	GetSystemTime(syt);
	SecondTime sdt;
	sdt.encode(syt);
	return sdt.decode();
}
//nowTimeFunc TimeDomain::getNowTime = getNowTimeAdapter //既没有目标类型接口，又没有特殊功能，这个封装每次也就是从localtime里取值。用起来还麻烦
NowTimeFunc TimeDomain::getNowTime = time;

TimeDomain::TimeDomain()
: index_(0)
, check_t_(1)
{
	check_t_.SetNextHitTime(GameServer::Instance->Engine()->getMiniDateTime()+1);
}

TimeDomain& TimeDomain::getInstance()
{
	static TimeDomain td;
	return td;
}

void TimeDomain::RunOne(SecondTime now)
{
	if (check_t_.CheckAndSet(now))
	{
		onRun(now.decode());
	}
}

void TimeDomain::onRun(time_t now)
{
	map<time_t, TimeFields>::iterator it = start_time_map_.begin();
	while (it != start_time_map_.end())
	{
		if (it->first > now)
			break;

		std::list<int>::iterator fit;
		for (fit = it->second.begin(); fit != it->second.end(); ++fit)
		{
			TimeField& ts = fields_[*fit];
			ts.onStart();
		}

		start_time_map_.erase(it);
		it = start_time_map_.begin();
	}

	it = end_time_map_.begin();
	while (it != end_time_map_.end())
	{
		if (it->first > now)
			break;

		std::list<int>::iterator fit;
		for (fit = it->second.begin(); fit != it->second.end(); ++fit)
		{
			TimeField& ts = fields_[*fit];
			ts.onEnd();
		}

		end_time_map_.erase(it);
		it = end_time_map_.begin();
	}
}

bool TimeDomain::checkTime(const std::string &rule)
{
	TimeField* tf = getField(rule);
	if (tf == NULL) return false;
	return tf->active;
}

time_t TimeDomain::getStartTime(const std::string &rule)
{
	TimeField* tf = getField(rule);
	if (tf == NULL) return -1;
	return tf->start_time;
}

time_t TimeDomain::getEndTime(const std::string &rule)
{
	TimeField* tf = getField(rule);
	if (tf == NULL) return -1;
	return tf->end_time;
}

TimeField* TimeDomain::getField(const std::string &rule)
{
	std::map<std::string, int>::iterator it = field_index_.find(rule);
	if (it != field_index_.end())
		return &fields_[it->second];

	TimeField tf;
	if (!tf.readRule(rule)) // 规则错误
		return NULL;
	if (!tf.calcNext()) // 没有符合条件的时间
		return NULL;

	//return &tf;
	//默认全部注册，所有需要查询的rule都是会重复查询的
	field_index_[rule] = ++index_;
	tf.id = index_;
	fields_[index_] = tf;

	if (tf.start_time > getNowTime(NULL))
		start_time_map_[tf.start_time].push_back(index_);
	end_time_map_[tf.end_time].push_back(index_);

	return &fields_[index_];
}

bool TimeDomain::regStart(const std::string &rule, TimerFunc func)
{
	TimeField* tf = getField(rule);
	if (tf == NULL) return false;

	tf->regStart(func);
	return true;
}

bool TimeDomain::regEnd(const std::string &rule, TimerFunc func)
{
	TimeField* tf = getField(rule);
	if (tf == NULL) return false;

	tf->regEnd(func);
	return true;
}
