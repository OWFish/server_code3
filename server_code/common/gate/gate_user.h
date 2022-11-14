#ifndef _GATE_USER_H_
#define _GATE_USER_H_

class GateUser
{
public:
	NetId					netid_;
	int						account_id_;		//�����û���ȫ�ֻỰID
	ActorId					actor_id_;			// ѡ��Ľ�ɫid���ڴ�֮ǰ��0
	bool					closed_;		//�Ƿ���Ϊ�����ر�
	int64_t					handle_;
	int						gm_;			// gm�ȼ�
	char					remote_addr_[32];		//�ͻ��˵�ַ
	SrvDef::ACCOUNT			account_name_;		//�ʺ��ַ���
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

