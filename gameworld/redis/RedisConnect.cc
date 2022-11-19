#include "RedisConnect.h"
//#include "redis/hiredis/hiredis.h"

CRedisConnect::CRedisConnect()
{
	_context_ptr = nullptr;
	_param_ptr = std::make_shared<tg_redis_param>();
	mLastTime = 0;
}

CRedisConnect::CRedisConnect(const std::shared_ptr<tg_redis_param>& param)
	:_context_ptr(nullptr)
	, _param_ptr(param)
	, mLastTime(0)
{
}

CRedisConnect::~CRedisConnect()
{
	close();
}

bool CRedisConnect::connect()
{
	close();

	_context_ptr = redisConnectWithTimeout(_param_ptr->host.c_str(), _param_ptr->port, _param_ptr->timeout);
	if (!_context_ptr || _context_ptr->err)
	{
		char buf[1024] = { 0 };
		if (_context_ptr)
		{
			sprintf(buf, "init redis is error: errcode=%d, errstr=%s", _context_ptr->err, _context_ptr->errstr);
			_last_error = buf;
		}
		else
		{
			sprintf(buf, "connect error: can't allocate redis context. host=%s, port=%d",
				_param_ptr->host.c_str(), _param_ptr->port);
			_last_error = buf;
		}

		return false;
	}

	if (!_param_ptr->pwd.empty() && !exec_cmd("auth %s", _param_ptr->pwd.c_str()))
	{
		return false;
	}

	if (!exec_cmd("SELECT %d", _param_ptr->db_index))
	{
		return false;
	}
	_db_no = _param_ptr->db_index;

	return true;
}

void CRedisConnect::close()
{
	if (_context_ptr)
	{
		redisFree(_context_ptr);
		_context_ptr = nullptr;
	}
}

void CRedisConnect::SetParam(const std::shared_ptr<tg_redis_param>& param)
{
	if (_param_ptr == nullptr)
	{
		return;
	}
	_param_ptr->db_index = param->db_index;
	_param_ptr->host = param->host;
	_param_ptr->port = param->port;
	_param_ptr->pwd = param->pwd;
	_param_ptr->timeout = param->timeout;
}

std::shared_ptr<CRedisResult> CRedisConnect::exec_cmd(const char * command, ...)
{
	va_list ap;
	va_start(ap, command);
	auto reply = std::make_shared<CRedisResult>(static_cast<redisReply*>(redisvCommand(_context_ptr, command, ap)));
	va_end(ap);
	if (reply->is_null())
	{
		_last_error = "Reply is null!";
		return nullptr;
	}
	if (reply->is_error())
	{
		_last_error = reply->get_str();
		return nullptr;
	}

	return reply;
}

std::shared_ptr<CRedisResult> CRedisConnect::testexec_cmd(const char * command, ...)
{
	auto reply = std::make_shared<CRedisResult>(static_cast<redisReply*>(redisCommand(_context_ptr, command)));
	if (reply->is_null())
	{
		_last_error = "Reply is null!";
		return nullptr;
	}
	if (reply->is_error())
	{
		_last_error = reply->get_str();
		return nullptr;
	}

	return reply;
}

std::string & CRedisConnect::get_last_err()
{
	return _last_error;
}

bool CRedisConnect::rpush(std::string key, std::vector<int>& value)
{
	int64_t len = 0;
	auto reply = exec_cmd("llen %s", key.c_str());
	if (!reply || reply->get_reply()->type != REDIS_REPLY_INTEGER)
	{
		return false;
	}
	len = reply->get_integer();

	for (int i = 0; i < value.size(); i++)
	{
		auto reply = exec_cmd("RPUSH %s %d", key.c_str(), value.at(i));
		if (!reply || reply->get_reply()->type != REDIS_REPLY_INTEGER)
		{
			return false;
		}
		if (++len != reply->get_integer())
		{
			return false;
		}
	}

	return true;
}

bool CRedisConnect::lrange_all(std::string key, std::vector<int>& out_data)
{
	int64_t len = 0;
	auto reply = exec_cmd("llen %s", key.c_str());
	if (!reply || reply->get_reply()->type != REDIS_REPLY_INTEGER)
	{
		return false;
	}
	len = reply->get_integer();

	reply = exec_cmd("LRANGE %s %d %d", key.c_str(), 0, len - 1);
	if (!reply || reply->get_reply()->type != REDIS_REPLY_ARRAY)
	{
		return false;
	}

	redisReply** replyVector = reply->get_reply()->element;//��ȡ����ָ��
	out_data.reserve(len);
	for (int i = 0; i < len; i++)
	{
		std::string temp = (*replyVector)->str;//����redisReply*����,����vector����
		int a = std::atoi(temp.c_str());
		out_data.push_back(a);
		replyVector++;
	}
	return true;
}

bool CRedisConnect::set(const char * key, const char * value, unsigned int expire)
{
	return (expire && exec_cmd("SETEX %s %d %s", key, expire, value))
		|| (expire == 0 && exec_cmd("SET %s %s", key, value));
}

bool CRedisConnect::hset(const char * hash_name, const char * key, const char * value)
{
	return nullptr != exec_cmd("HSET %s %s %s", hash_name, key, value);
}

bool CRedisConnect::rpush(const char * list_name, const char * value)
{
	return nullptr != exec_cmd("RPUSH %s %s", list_name, value);
}

bool CRedisConnect::lset(const char * list_name, int index, const char * value)
{
	return nullptr != exec_cmd("LSET %s %d %s", list_name, index, value);
}

int CRedisConnect::zcard(const char * set_name)
{
	auto tmp = exec_cmd("ZCARD %s", set_name);
	if (tmp)
	{
		return tmp->get_integer();
	}
}

bool CRedisConnect::zadd(const char * set_name, long long score, const char * value)
{
	char commond[1000];
	sprintf(commond, "ZADD %s %lld %s", set_name, score, value);
	//return nullptr != exec_cmd(commond);
	return nullptr != testexec_cmd(commond);
}

int64_t CRedisConnect::zrank(const char * set_name, const char * value)
{
	auto ptr = exec_cmd("ZRANK %s %s", set_name, value);
	if (ptr != nullptr && ptr->is_ok())
	{
		return ptr->get_integer();
	}
	return -1;
}

std::shared_ptr<CRedisResult> CRedisConnect::get(const char * key)
{
	return exec_cmd("GET %s", key);
}

std::shared_ptr<CRedisResult> CRedisConnect::hget(const char * hash_name, const char * key)
{
	return exec_cmd("HGET %s %s", hash_name, key);
}

std::shared_ptr<CRedisResult> CRedisConnect::zrange(const char * set_name, uint64_t start, uint64_t end)
{
	return exec_cmd("ZRANGE %s %d %d", set_name, start, end);
}

std::shared_ptr<CRedisResult> CRedisConnect::zrangebywithscores(const char * set_name, uint64_t start, uint64_t end)
{
	return exec_cmd("ZRANGE %s %d %d WITHSCORES", set_name, start, end);
}

std::shared_ptr<CRedisResult> CRedisConnect::zrevrange(const char * set_name, uint64_t start, uint64_t end)
{
	return exec_cmd("ZREVRANGE  %s %d %d", set_name, start, end);
}

std::shared_ptr<CRedisResult> CRedisConnect::zrevrangebywithscores(const char * set_name, uint64_t start, uint64_t end)
{
	return exec_cmd("ZREVRANGE  %s %d %d WITHSCORES", set_name, start, end);
}

bool CRedisConnect::zremrangebyrank(const char * set_name, uint64_t start, uint64_t end)
{
	return nullptr != exec_cmd("ZREMRANGEBYRANK %s %d %d", set_name, start, end);
}

std::shared_ptr<CRedisResult> CRedisConnect::lrange(const char * list_name, size_t start, size_t end)
{
	return exec_cmd("LRANGE %s %d %d", list_name, start, end);
}

uint64_t CRedisConnect::llen(const char * list_name)
{
	auto tmp = exec_cmd("LLEN %s", list_name);
	if (tmp)
	{
		return tmp->get_len();
	}

	return 0;
}

std::shared_ptr<CRedisResult> CRedisConnect::lpop(const char * list_name)
{
	return exec_cmd("LPOP %s %s", list_name);
}

std::shared_ptr<CRedisResult> CRedisConnect::rpop(const char * list_name)
{
	return exec_cmd("RPOP %s %s", list_name);
}

bool CRedisConnect::exists(const char * key)
{
	return nullptr != exec_cmd("exists %s", key);
}

bool CRedisConnect::del(const char * key)
{
	return nullptr != exec_cmd("DEL %s", key);
}

int CRedisConnect::get_data(std::shared_ptr<CRedisResult> result, const char *szcmd)
{
	if (result == nullptr)
	{
		return 0;
	}
	auto pReplay = result->get_reply();
	int ret = 0;
	int lrank = 0;
	switch (pReplay->type)
	{
	case REDIS_REPLY_STATUS:
		ret = -1;
		printf("[%s] status [%s]\n", szcmd, pReplay->str);
		break;
	case REDIS_REPLY_ERROR:
		ret = -1;
		printf("[%s] error [%s]\n", szcmd, pReplay->str);
		break;
	case REDIS_REPLY_STRING:
		ret = 0;
		printf("[%s] get string , value : %s\n", szcmd, pReplay->str);
		break;
	case REDIS_REPLY_INTEGER:
		ret = 0;
		printf("[%s] get integer , value : %d\n", szcmd, pReplay->integer);
		break;
	case REDIS_REPLY_ARRAY:
		ret = 0;
		for (int i = 0; i < pReplay->elements; i++)
		{
			if (i%2 == 0)
			{
				lrank++;

				printf("[%s] , Actor Rank [%d] , Actor ID : %s\n", szcmd, lrank, pReplay->element[i]->str);
			}
			else
			{
				printf(" Actor Score : %s\n", pReplay->element[i]->str);
			}
			
		}
		break;
	case REDIS_REPLY_NIL:
		ret = 0;
		printf("[%s] get null\n", szcmd);
		break;
	default:
		ret = -1;
		printf("[%s] get error\n", szcmd);
		break;
	}

	return ret;
}

int CRedisConnect::db_no()
{
	return _db_no;
}
