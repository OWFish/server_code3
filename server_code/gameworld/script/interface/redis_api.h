#ifndef _REDIS_API_H_
#define _REDIS_API_H_
/*

*/

//tolua_begin
namespace LRedis
{
	void Zadd(char* rankname,int score,char* actordata);
}
//tolua_end

#endif