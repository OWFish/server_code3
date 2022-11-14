#ifndef _TIMER_H_
#define _TIMER_H_

//#include "../game_server.h"
#include <stdint.h>

class Timer
{
public:
	Timer(int i);


	//判断时间是否到达，如果到达则设置新的时间并返回true
	// Param bool bIgnore: 是否忽略中间累积的处理。
	inline bool CheckAndSet(uint64_t curr_t, bool ignore = true)
	{
		if (curr_t < next_t_)
		{
			return false;
		}
		else
		{
			if (ignore)
				next_t_ = curr_t + INTERVAL;
			else
				next_t_ += INTERVAL;

			return true;
		}
	}
	//判断时间是否到达
	inline bool Check(uint64_t curr_t)
	{
		return curr_t >= next_t_;
	}
	/*
		增加一个接口，设置现在到下一次触发的间隔时间，这个主要用于跨天等特殊场合
		* nNextTime 单位ms，表示下次触发是从现在开始的多少ms
	*/
	inline void SetNextHitTimeFromNow(uint64_t now_t, int nNextTime)
	{
		next_t_ = now_t + nNextTime;
	}
	inline void SetNextHitTime(uint64_t nNextTime)
	{
		next_t_ = nNextTime;
	}

//private:
public:
	uint64_t next_t_;
	int INTERVAL;
};

#endif

