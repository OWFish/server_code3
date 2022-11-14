#pragma once
#include <list>
#include "entity/actor/actor.h"
#include "timer.h"


class GateUser;

/*
	��Ҫ����ȷ�����߾�������첽��½�ɹ�������ʵ��Ҿ����ڴ�ʱ�ȴ�
	Ҳ�������Ŷӻ���
*/
class LoginQueue
{
	enum LoginStatusType
	{
		LST_Default			= 0,
		LST_KickingOldUser	= 1,
	};
	struct LoginUser
	{
		GateUser* user;
		int		server_id;

		int		status;	//״̬���
		int		time;
		char	pf[PFSTR_MAX_LEN];
		char	pfid[PFID_MAX_LEN];
		char	appid[APPID_MAX_LEN];
		LoginUser(GateUser* user, int server_id, const char* pf, const char* pfid, const char* appid) :user(user), server_id(server_id), status(0), time(0) {
			memset(this->pf, 0, PFSTR_MAX_LEN);
			_STRNCPY_A(this->pf, pf);
			memset(this->appid, 0, APPID_MAX_LEN);
			_STRNCPY_A(this->appid, appid);
			memset(this->pfid, 0, PFID_MAX_LEN);
			_STRNCPY_A(this->pfid, pfid);
		}
	};
public:
	LoginQueue();
	~LoginQueue();

	void Destroy();
	void RunOne(int now_t);
	void AddToQueue(GateUser* user, int serverId, const char* pf, const char* pfid, const char* appid);

private:
	std::list<LoginUser>  user_list_;
	Timer logic_timer_;
};

