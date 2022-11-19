#ifndef REDES_RESULT_H
#define REDES_RESULT_H

#include <stdint.h>
#include <stdlib.h>
#include <string>

#ifndef _WIN32
#include "/redis/hiredis/hiredis.h"
#else
#include "redis/src/Win32_Interop/Win32_APIs.h"
#include "redis/hiredis/hiredis.h"
#endif

class CRedisResult
{
public:
	CRedisResult(redisReply* reply);

	~CRedisResult();
public:
	bool is_null();

	bool is_error();

	bool is_ok();

	const redisReply* get_reply();

	bool try_get_value(int64_t& out_val);

	bool try_get_value(double& out_val);

	bool try_get_value(std::string& out_val);

	bool try_get_value(bool& out_val);

	uint64_t get_len();

	bool is_arr();

	uint64_t get_len_arr();

	int64_t get_integer();

	const char* get_str();

private:
	redisReply* _reply;
};
#endif 