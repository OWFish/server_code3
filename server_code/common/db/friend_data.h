#ifndef _FRIEND_DATA_H_
#define _FRIEND_DATA_H_

#include "common.h"


#pragma  pack(push,1)

struct FriendInfo
{
	ActorId actor_id_;  //好友角色id
	//int qq_vip_;
	//unsigned int friendly_;//与该好友的友好度
	//uint8_t icon_;   //该好友的头像
	uint8_t f_type_;
	//int level_;
	//uint8_t camp_;
	//uint8_t job_;
	//uint8_t sex_;
	//uint32_t fight_;           //战斗力
	//uint32_t last_logout_time_;//离线时间
	//uint32_t server_id_;       //服务器ID
	uint32_t add_friend_time_; //添加好友时间
	uint32_t last_contact_time_;	//最近联系时间


	// 重载比较操作符，在列表中会根据角色id作二分法查找
	inline bool operator != (const FriendInfo& data) const
	{
		return actor_id_ != data.actor_id_;
	}
	inline bool operator > (const FriendInfo& data) const
	{
		return actor_id_ > data.actor_id_;
	}
	inline bool operator < (const FriendInfo& data) const
	{
		return actor_id_ < data.actor_id_;
	}
};

#pragma  pack (pop)
#endif

