#ifndef TG_REDIS_H
#define TG_REDIS_H

#include <stdio.h>
#include <stdarg.h>
#include<memory>
#include<vector>
#include "RedisResult.h"
#include "../../common/redis/redis_def.h"

class CRedisConnect
{

public:
	CRedisConnect();
	CRedisConnect(const std::shared_ptr<tg_redis_param>& param);
	
	~CRedisConnect();

	bool connect();

	void close();

	void SetParam(const std::shared_ptr<tg_redis_param>& param);

	std::shared_ptr<CRedisResult> exec_cmd(const char* command, ...);

	std::string& get_last_err();

	bool rpush(std::string key, std::vector<int>& value);

	bool lrange_all(std::string key, std::vector<int>& out_data);

	///设置一个字符串到key
	bool set(const char* key, const char* value, unsigned int expire = 0);

	///设置一个字符串到hash
	bool hset(const char* hash_name, const char* key, const char* value);

	bool rpush(const char* list_name, const char* value);

	bool  lset(const char* list_name, int index, const char* value);

	///添加一个数据到有序集合中
	bool zadd(const char* set_name, int score, const char* value);

	///根据对应的数据得到一个排名
	int64_t  zrank(const char* set_name, const char* value);

	///根据key得到一个value
	std::shared_ptr<CRedisResult> get(const char* key);

	///获取hash内的value
	std::shared_ptr<CRedisResult> hget(const char* hash_name, const char* key);

	///从有序集合中得到数据
	std::shared_ptr<CRedisResult> zrange(const char* set_name, uint64_t start, uint64_t end);

	///从列表中获取数据
	std::shared_ptr<CRedisResult> lrange(const char* list_name, size_t start, size_t end);

	///列表长度
	uint64_t  llen(const char* list_name);

	std::shared_ptr<CRedisResult> lpop(const char* list_name);

	///移除list的尾部并且返回
	std::shared_ptr<CRedisResult> rpop(const char* list_name);

	bool exists(const char* key);

	bool del(const char* key);

	///当前使用中的DB
	int db_no();

private:
	redisContext* _context_ptr;
	int _db_no;
	std::shared_ptr<tg_redis_param> _param_ptr;
	std::string _last_error;
};
#endif // TG_REDIS_H
