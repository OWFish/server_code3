#include "StdAfx.h"


#include <vector>
#include "time_domain.h"
using namespace std;

inline vector<std::string> split(const std::string &str, const std::string &pattern);
inline std::string& trim(std::string &str);
inline int recalcStart(int s, int c, int carry, int minUnit);
inline bool readField(TimeChunk &field, const std::string &rule);
inline bool readWeek(BaseTimeField *td, const std::string &rule);
//兼容旧版本
inline bool operator==(const std::string&, const std::string&);
inline bool operator==(const std::string&, const char*);

void TimeField::onStart()
{
	TimerFuncList::iterator it;
	for (it = start_callback_funcs.begin(); it != start_callback_funcs.end(); ++it)
	{
		(*it)(rule.c_str());
	}
	active = true;
}

void TimeField::onEnd()
{
	TimerFuncList::iterator it;
	for (it = end_callback_funcs.begin(); it != end_callback_funcs.end(); ++it)
	{
		(*it)(rule.c_str());
	}
	if (type == 1 && calcNext() == true)
	{
		TimeDomain::getInstance().start_time_map_[start_time].push_back(id);
		TimeDomain::getInstance().end_time_map_[end_time].push_back(id);
	}
	active = false;
}

void TimeField::regStart(TimerFunc func)
{
	TimerFuncList::iterator it;
	for (it = start_callback_funcs.begin(); it != start_callback_funcs.end(); ++it)
	{
		if (*it == func)
			return;
	}
	start_callback_funcs.push_back(func);
}

void TimeField::regEnd(TimerFunc func)
{
	TimerFuncList::iterator it;
	for (it = end_callback_funcs.begin(); it != end_callback_funcs.end(); ++it)
	{
		if (*it == func)
			return;
	}
	end_callback_funcs.push_back(func);
}


BaseTimeField::BaseTimeField()
	: type(0)
	, active(false)
	, start_time(-1)
	, end_time(-1)
{
	memset(week, 0, sizeof(week));
}

bool BaseTimeField::readRule(const std::string &rule)
{
	if (rule == "" || rule == "*")
	{
		type = 0;
		return false;
	}
	size_t p1 = rule.find("^");
	size_t p2 = rule.find("~");
	if (p1 != std::string::npos)
		type = 1;
	else if (p2 != std::string::npos)
		type = 2;
	else
		return false;

	size_t pw = rule.find('[');
	size_t p = type == 1 ? p1 : p2;
	if (!readField(start, rule.substr(0, p))
		|| (!readField(end, rule.substr(p + 1, pw == std::string::npos ? pw : pw - p - 1)))
		|| (!readWeek(this, rule))
		|| (!check())
		)
	{
		type = 0;
		return false;
	}
	this->rule = rule;

	return true;
}

bool BaseTimeField::check()
{
	if (type == 0)
		return false;

	if ((start.year == -1 && end.year != -1) || (start.year != -1 && end.year == -1))
		return false;
	if ((start.month == -1 && end.month != -1) || (start.month != -1 && end.month == -1))
		return false;
	if ((start.day == -1 && end.day != -1) || (start.day != -1 && end.day == -1))
		return false;
	if ((start.time == -1 && end.time != -1) || (start.time != -1 && end.time == -1))
		return false;

	if (type == 1)
	{
		// 不支持跨年，跨月, 否则规则非常非常非常乱
		if (start.year != -1 && start.year > end.year)
			return false;
		if (start.month != -1 && start.month > end.month)
			return false;
		if (start.day != -1 && start.day > end.day)
			return false;
	}
	else
	{
		bool ret = start.year != end.year ? start.year < end.year :
			start.month != end.month ? start.month < end.month :
			start.day != end.day ? start.day < end.day : false;

		return ret;
	}

	return true;
}

//rule = "2015.10.1-10:0 ~ 2015.10.7-18:0 []"  10月1日10点开始，7日18点结束，不限星期几
bool readField(TimeChunk &field, const std::string &rule)
{
	vector<std::string> r = split(rule, "-");
	if (r.size() == 1)
	{
		if (trim(r[0]) == "*") {
			field.year = -1;
			field.month = -1;
			field.day = -1;
			//field.time = -1;
			field.time = 0;// minimum unit is day
			return true;
		}
	}
	else if (r.size() == 2)
	{
		if (trim(r[1]) == "*") {
			field.time = -1;
		}
		vector<std::string> t = split(r[1], ":");
		if (t.size() != 2) {
			printf("readField  failed. time format error. %s", r[1].c_str());
			return false;
		}
		int h = atoi(t[0].c_str());
		int m = atoi(t[1].c_str());
		if (h < 0 || h > 23 || m < 0 || m > 59) {
			printf("readField failed. time format error. %s", r[1].c_str());
			return false;
		}
		field.time = h * 3600 + m * 60;
	}
	else {
		printf("readField failed: %s", rule.c_str());
		return false;
	}

	vector<std::string> date = split(trim(r[0]), ".");
	if (date.size() == 1 && trim(date[0]) == "*")
	{
		field.year = -1;
		field.month = -1;
		field.day = -1;
		return true;
	}
	if (date.size() != 3) {
		printf("readField failed, read date %s", r[0].c_str());
		return false;
	}
	if (date[0] == "*")
		field.year = -1;
	else
		field.year = atoi(date[0].c_str());

	if (date[1] == "*")
		field.month = -1;
	else
		field.month = atoi(date[1].c_str());

	if (date[2] == "*")
		field.day = -1;
	else
		field.day = atoi(date[2].c_str());

	if (field.month != -1 && (field.month < 1 || field.month > 12)) {
		printf("readField failed. %s", rule.c_str());
		return false;
	}
	if (field.day != -1 && (field.day < 1 || field.day > 31)) {
		printf("readField failed. %s", rule.c_str());
		return false;
	}
	return true;
}

bool readWeek(BaseTimeField *td, const std::string &rule)
{
	size_t p1 = rule.find("[");
	size_t p2 = rule.find("]");
	if (p1 == std::string::npos && p2 == std::string::npos) {
		for (int i = 0; i < 7; ++i) {
			td->week[i] = true;
		}
	}
	else if (p1 != std::string::npos && p2 != std::string::npos) {
		std::string weekrule = rule.substr(p1 + 1, p2 - p1 - 1);
		weekrule = trim(weekrule);
		if (weekrule == "*" || weekrule == "") {
			for (int i = 0; i < 7; ++i) {
				td->week[i] = true;
			}
		}
		else {
			vector<std::string> r = split(weekrule, ",");
			for (size_t i = 0; i < r.size(); ++i)
			{
				int w = atoi(r[i].c_str());
				if (w >= 0 && w < 7)
					td->week[w] = true;
				else {
					printf("readWeek failed");
					return false;
				}
			}
		}
	}
	else {
		printf("readWeek failed.");
		return false;
	}
	return true;
}

inline int mdays(int y, int m)
{
	static int md[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (m != 2)
		return md[m - 1];
	return 28 + ((y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)) ? 1 : 0);
}

inline int calcTime(int start, int end, tm* now, int &carry)
{
	if (start == -1) return 0;
	int nowtime = (now->tm_hour * 60 + now->tm_min) * 60;

	if (start < end) {
		if (nowtime >= end)
			carry = 1;
		return start;
	}
	else {
		if (nowtime < end)
			carry = -1;
		return start;
	}
}
inline int calcDay(int start, int end, tm* now, int last, int &carry, bool &future)
{
	int nowtime = now->tm_mday + last;
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	if (nowtime == 0) {
		carry = -1;
		month -= 1;
		if (month == 0) {
			month = 12;
			year -= 1;
		}
		nowtime = mdays(year, month);
	}
	else if (nowtime > mdays(year, month)) {
		nowtime = nowtime - mdays(year, month);
		carry += 1;
	}

	if (start == -1) return nowtime;

	if (nowtime < start) {
		future = true;
		return start;
	}
	else if (nowtime > end) {
		carry += 1;
		future = true;
		return start;
	}
	else {
		return nowtime;
	}
}
inline int calcMonth(int start, int end, tm* now, int last, int &carry, bool &future)
{
	int nowtime = now->tm_mon + 1 + last;
	if (nowtime == 0) {
		carry = -1;
		nowtime = 12;
	}
	else if (nowtime == 13) {
		carry = 1;
		nowtime = 1;
	}
	if (start == -1) return nowtime;

	if (nowtime < start) {
		future = true;
		return start;
	}
	else if (nowtime > end) {
		carry += 1;
		future = true;
		return start;
	}
	else {
		return nowtime;
	}
}
inline int calcYear(int start, int end, tm* now, int last, bool &future)
{
	int nowtime = now->tm_year + 1900 + last;

	if (start == -1) return nowtime;

	if (nowtime < start) {
		future = true;
		return start;
	}
	else if (nowtime > end) {
		return -1;
	}
	else {
		return nowtime;
	}
}

inline int recalcStart(int s, int c, bool future)
{
	if (future)
		return (s == -1) ? 1 : s;
	return c;
}

bool BaseTimeField::calcNext()
{
	time_t now_t = TimeDomain::getNowTime(NULL) + 1; //临界问题
	struct tm* now = localtime(&now_t);

	//"2012.12.21-0:0^2015.10.1-24:00[1]";
	// 2015.10.11 x:x:x
	if (type == 1)
	{
		//int nowtime = (now->tm_hour * 60 + now->tm_min) * 60;
		int y = 0, m = 0, d = 0, t = 0, cm = 0, cd = 0, ct = 0;
		bool fd = false, fm = false, fy = false;
		t = calcTime(start.time, end.time, now, ct);
		d = calcDay(start.day, end.day, now, ct, cd, fd);
		m = calcMonth(start.month, end.month, now, cd, cm, fm);
		y = calcYear(start.year, end.year, now, cm, fy);
		if (y == -1) return false;

		m = recalcStart(start.month, m, fy);
		d = recalcStart(start.day, d, fm);
		t = recalcStart(start.time, t, fd);

		if (checkWeekday(y, m, d))
		{
			start_time = mergeTime(y, m, d, start.time);
			end_time = mergeTime(y, m, d, end.time);
			if (start_time == end_time)
				end_time = start_time + 3600 * 24;
		}
		else
		{
			findNextDay(y, m, d);
			start_time = mergeTime(y, m, d, start.time);
			end_time = mergeTime(y, m, d, end.time);
			if (start_time >= end_time)
				end_time = end_time + 3600 * 24;
		}
		if (now_t > start_time)
			active = true;
		else
			active = false;
	}
	else if (type == 2)
	{
		end_time = mergeTime(end.year, end.month, end.day, end.time);
		start_time = mergeTime(start.year, start.month, start.day, start.time);

		if (end_time < now_t)
			return false;
		if (start_time < now_t)
			active = true;
		else
			active = false;
	}
	else
	{
		return false;
	}

	return true;
}

bool BaseTimeField::checkWeekday(int y, int m, int d, int *wk)
{
	tm t;
	t.tm_mday = d;                //day 为日
	t.tm_mon = m - 1;             // month为月
	t.tm_year = y - 1900;          // year 为年
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;

	time_t tm_t = mktime(&t);
	if (wk != NULL) *wk = t.tm_wday;
	return week[t.tm_wday];
}

time_t BaseTimeField::mergeTime(int y, int m, int d, int time)
{
	tm t;
	t.tm_mday = d;                //day 为日
	t.tm_mon = m - 1;             // month为月
	t.tm_year = y - 1900;          // year 为年

	if (time == -1) {
		t.tm_hour = 0;
		t.tm_min = 0;
		t.tm_sec = 0;
	}
	else
	{
		t.tm_hour = time % (3600 * 24) / 3600;
		t.tm_min = time / 60 % 60;
		t.tm_sec = time % 60;
	}

	time_t tm_t = mktime(&t);
	return tm_t;
}


bool BaseTimeField::findNextDay(int &y, int &m, int &d, int weekday)
{
	d = d + 1;
	if ((d > mdays(y, m))
		|| (start.day != -1 && d > start.day))
	{
		d = start.day;
		if (d == -1) d = 1;

		m = m + 1;
		if (m > 12 || (end.month != -1 && m > end.month))
		{
			m = start.month;
			if (m == -1) m = 1;

			y = y + 1;
			if (end.year != -1 && y > end.year)
				return false;
		}

		if (checkWeekday(y, m, d, &weekday))
			return true;
		else
			return findNextDay(y, m, d, weekday);
	}
	else
	{
		if (weekday != -1)
		{
			weekday = weekday + 1;
			if (week[weekday % 7])
				return true;
		}
		else
		{
			if (checkWeekday(y, m, d, &weekday))
				return true;
		}
		return findNextDay(y, m, d, weekday);
	}
}

vector<std::string> split(const std::string &str, const std::string &pattern)
{
	vector<std::string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

std::string& trim(std::string &str)
{
	size_t s = str.find_first_not_of(" \t");
	size_t e = str.find_last_not_of(" \t");
	if (s == std::string::npos) return str;
	str = str.substr(s, e - s + 1);
	return str;
}


bool operator==(const std::string& lhs, const std::string& rhs)
{
	return lhs.compare(rhs.c_str()) == 0;
}

bool operator==(const std::string& lhs, const char* str)
{
	return lhs.compare(str) == 0;
}
