#ifndef _TIMER_H_
#define _TIMER_H_

//#include "../game_server.h"
#include <stdint.h>

class Timer
{
public:
	Timer(int i);


	//�ж�ʱ���Ƿ񵽴��������������µ�ʱ�䲢����true
	// Param bool bIgnore: �Ƿ�����м��ۻ��Ĵ���
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
	//�ж�ʱ���Ƿ񵽴�
	inline bool Check(uint64_t curr_t)
	{
		return curr_t >= next_t_;
	}
	/*
		����һ���ӿڣ��������ڵ���һ�δ����ļ��ʱ�䣬�����Ҫ���ڿ�������ⳡ��
		* nNextTime ��λms����ʾ�´δ����Ǵ����ڿ�ʼ�Ķ���ms
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

