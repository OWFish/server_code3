#ifndef _GUILD_DB_H_
#define _GUILD_DB_H_

#include "common.h"


#define		MAXMEMOCOUNT		1024

struct GuildMemberInfo
{
	ActorId				actorId_;
	int					total_contrib_;
	int					today_contrib_;
	uint8_t				job_; // 职业
	uint8_t				sex_;
	uint8_t				level_;//等级
	uint8_t				zs_level_;//转生等级
	uint8_t				pos_;	//地位
	double				fight_;	// 战力
	int					vip_; // vip等级
	int					monthcard_; // 月卡状态
	int					icon_;	//头像ID
	unsigned int		lastLogoutTime_;
	unsigned int        recharge_;
	ACTORNAME			actor_name_;
	uint64_t			handle_;
	GuildMemberInfo()
	{
		ZeroMemory(this, sizeof(*this));
	}

	int compare(GuildMemberInfo& node)
	{
		if (total_contrib_ > node.total_contrib_) return 1;
		else if (total_contrib_ < node.total_contrib_) return -1;
		else return 0;
	}
};



#endif
