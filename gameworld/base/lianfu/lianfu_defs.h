#ifndef _LIANFU_DEF_H_
#define _LIANFU_DEF_H_

#include "db/rank_data.h"

#define MAX_LIANFU_SERVER 10

// ������������¼����ͨ���������
struct CommServer
{
	int sid_;
	AllRankList rank_;
	AllLastRankList	last_rank_list_;
};

#endif
