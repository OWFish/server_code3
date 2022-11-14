#include "StdAfx.h"
#include "login_queue.h"



LoginQueue::LoginQueue()
	:logic_timer_(500)
{
}

LoginQueue::~LoginQueue()
{
}

void LoginQueue::Destroy()
{
}


inline bool operator==(const NetId& lhs, const NetId& rhs) {
	return lhs.socket_ == rhs.socket_ && lhs.index_ == rhs.index_ && lhs.gate_id_ == rhs.gate_id_;
}

void LoginQueue::RunOne(int now_t)
{
	
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	for (auto it(user_list_.begin()); it != user_list_.end();)
	{
		LoginUser &user = *it;
		if (user.user->closed_)
		{
			OutputMsg(rmError, "user is close, actorid:%d", user.user->actor_id_);
			it = user_list_.erase(it);
			continue;
		}
		
		Actor* actor = em->GetActorPtrById(user.user->actor_id_);

		if (actor)
		{
			if (actor->IsImage())
			{
				if (actor->GetImageEndTime() > (int)(GetGameEngine()->getMiniDateTime() + 2))
					actor->SetImageEndTime(GetGameEngine()->getMiniDateTime() + 2);// 不要立即关闭
				it++;
				if (now_t % 500 == 0)
				{
					OutputMsg(rmError, "actor is image and waiting for login,actorid:%d", user.user->actor_id_);
				}
				continue;
			}
			if (actor->GetLoginTime() == 0 || (actor->GetLoginTime() + 5 > (unsigned int)now_t))
			{
				OutputMsg(rmError, "user LoginTime error, actorid:%d", user.user->actor_id_);
				it = user_list_.erase(it);
				continue;
			}
			if (user.status == LST_Default)
			{
				if (!(actor->GetNetId() == user.user->netid_))
				{
					OutputMsg(rmError, "repeat login！actorId=%d,accountid=%d",
						user.user->actor_id_, user.user->account_id_);
					static uint8_t data[3] = { Protocol::CMD_Login, 1,3 };
					actor->SendData(data, 3);
					user.time = now_t;
					user.status = LST_KickingOldUser;
					it++;
					continue;
				}
			}
			else if (user.status == LST_KickingOldUser)
			{
				if (now_t - user.time > 1)
				{
					actor->CloseActor("repeat login");
#ifdef OPENLOGTLOG
					static TlogMgr& tlog = GetGameEngine()->GetTlogMgr();
					tlog.LogOffline(*actor, OlServerKill);
#endif
					actor = NULL;
				}
				else
				{
					it++;
					if (now_t % 500 == 0)
					{
						OutputMsg(rmError, "kick old user waiting,actorid:%d", user.user->actor_id_);
					}
					continue;
				}
			}
		}

		GetGameEngine()->ActorLogin(user.user, user.server_id, user.pf, user.pfid, user.appid);
		it = user_list_.erase(it);
	}
}

void LoginQueue::AddToQueue(GateUser * user, int serverId, const char* pf, const char* pfid, const char* appid)
{
	LoginUser temp(user, serverId, pf, pfid, appid);

	user_list_.push_back(temp);
}
