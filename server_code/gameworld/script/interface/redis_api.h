#ifndef _REDIS_API_H_
#define _REDIS_API_H_
#include "StdAfx.h"
/*

*/
//tolua_begin
namespace LRedis
{
	void Zadd(char* rankname, long long score, char* actordata);
}
//tolua_end

#endif