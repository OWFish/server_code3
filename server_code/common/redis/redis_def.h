#ifndef REDES_DEF_H
#define REDES_DEF_H

//redis ≈‰÷√Ω·ππ
struct tg_redis_param
{
	std::string host;
	int port;
	int db_index;
	std::string pwd;
	struct timeval timeout;
};

#endif