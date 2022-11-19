#include "../interface/redis_api.h"
#include "../../redis/RedisConnect.h"
namespace LRedis
{
	void Zadd(char* rankname, long long score, char* actordata)
	{
		if (score <= 0)
		{
			return;
		}
		auto ge = GetGameEngine();
		auto pRedis = ge->GetRedis();
		if (pRedis && !pRedis->zadd(rankname,score, actordata))
		{
			OutputMsg(rmError, ("Redis Not Connected Successful , Error Info : %s"), pRedis->get_last_err().c_str());
		}
		return;
	}
}

