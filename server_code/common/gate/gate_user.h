#ifndef _GATE_USER_H_
#define _GATE_USER_H_

class GateUser
{
public:
	NetId					netid_;
	int						account_id_;		//网关用户的全局会话ID
	ActorId					actor_id_;			// 选择的角色id，在此之前是0
	bool					closed_;		//是否标记为主动关闭
	int64_t					handle_;
	int						gm_;			// gm等级
	char					remote_addr_[32];		//客户端地址
	SrvDef::ACCOUNT			account_name_;		//帐号字符串
public:
	GateUser(): account_id_(0), actor_id_(0), closed_(true), handle_(0), gm_(-1)
	{
		STATIC_ASSERT(sizeof(netid_.index_) == 2);
		netid_.index_ = 0xffff;
		remote_addr_[0] = 0;
		account_name_[0] = 0;
	}
};

#endif

