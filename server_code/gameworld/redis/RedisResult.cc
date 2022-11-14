#include "RedisResult.h"
#include "string.h"

CRedisResult::CRedisResult(redisReply * reply) :_reply(reply)
{
}

CRedisResult::~CRedisResult()
{
	if (_reply)
	{
		freeReplyObject(_reply);
		_reply = nullptr;
	}
}

bool CRedisResult::is_null()
{
	return !_reply || _reply->type == REDIS_REPLY_NIL;
}

bool CRedisResult::is_error()
{
	return _reply->type == REDIS_REPLY_ERROR;
}

bool CRedisResult::is_ok()
{
	return !is_null() && !is_error();
}

const redisReply * CRedisResult::get_reply()
{
	return _reply;
}

bool CRedisResult::try_get_value(int64_t & out_val)
{
	if (is_error())
	{
		return false;
	}

	out_val = atoll(_reply->str);
	return true;
}

bool CRedisResult::try_get_value(double & out_val)
{
	if (is_error())
	{
		return false;
	}

	out_val = atof(_reply->str);
	return true;
}

bool CRedisResult::try_get_value(std::string & out_val)
{
	if (is_error())
	{
		return false;
	}

	out_val = _reply->str;
	return true;
}

bool CRedisResult::try_get_value(bool & out_val)
{
	if (is_error())
	{
		return false;
	}

	out_val = strcasecmp("true", _reply->str) == 0;
	return true;
}

uint64_t CRedisResult::get_len()
{
	return _reply->len;
}

bool CRedisResult::is_arr()
{
	return _reply->type == REDIS_REPLY_ARRAY;
}

uint64_t CRedisResult::get_len_arr()
{
	return _reply->elements;
}

int64_t CRedisResult::get_integer()
{
	return _reply->integer;
}

const char * CRedisResult::get_str()
{
	return _reply->str;
}

