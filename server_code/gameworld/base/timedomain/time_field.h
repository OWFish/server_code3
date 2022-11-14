#pragma once
#include <string>
#include <list>


typedef void(*TimerFunc)(const char *rule);
typedef std::list<TimerFunc> TimerFuncList; // 回调函数保存在


struct TimeChunk
{
	int year;
	int month;
	int day;
	int time;
};

class BaseTimeField
{
public:
	int id;
	int type;
	TimeChunk start;
	TimeChunk end;
	bool week[7];
	std::string rule;

	bool active;
	time_t start_time;
	time_t end_time;

public:
	BaseTimeField();
	bool readRule(const std::string &rule);
	bool calcNext();

private:
	bool check();
	bool checkWeekday(int y, int m, int d, int *week = NULL);
	time_t mergeTime(int y, int m, int d, int time);
	bool findNextDay(int &y, int &m, int &d, int week = -1);
};

