#ifndef _FRIEND_DATA_H_
#define _FRIEND_DATA_H_

#include "common.h"


#pragma  pack(push,1)

struct FriendInfo
{
	ActorId actor_id_;  //���ѽ�ɫid
	//int qq_vip_;
	//unsigned int friendly_;//��ú��ѵ��Ѻö�
	//uint8_t icon_;   //�ú��ѵ�ͷ��
	uint8_t f_type_;
	//int level_;
	//uint8_t camp_;
	//uint8_t job_;
	//uint8_t sex_;
	//uint32_t fight_;           //ս����
	//uint32_t last_logout_time_;//����ʱ��
	//uint32_t server_id_;       //������ID
	uint32_t add_friend_time_; //��Ӻ���ʱ��
	uint32_t last_contact_time_;	//�����ϵʱ��


	// ���رȽϲ����������б��л���ݽ�ɫid�����ַ�����
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

