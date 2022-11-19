#ifndef _LIANFU_DEF_H_
#define _LIANFU_DEF_H_

#include "db/rank_data.h"

#define MAX_LIANFU_SERVER 10

// 连服服务器记录的普通服相关数据
struct CommServer
{
	int sid_;
	AllRankList rank_;
	AllLastRankList	last_rank_list_;
};

#endif
