#ifndef _LUA_SOCKET_HPP_
#define _LUA_SOCKET_HPP_

/******************************************************************
 *封装一个简单的socket类给lua调用
 *
 *****************************************************************/
#include "net/base_socket.h"

using namespace net;

class LuaSocket : public BaseSocket
{
public:
	LuaSocket(): buff_(NULL)
	{
		//printf("LuaSocket():%lld \n", (long long int)this);
	}

	virtual ~LuaSocket()
	{
		//printf("~LuaSocket():%lld \n", (long long int)this);

		if (buff_)
		{
			free(buff_);
			buff_ = NULL;
		}
	}

	// 建立连接,暂时只支持阻塞模式
	//通过32位IP地址连接到制定的端口，返回值为socket错误号，0表示成功。对于非阻塞模式返回0并不表示已经建立连接
	int connect(const double addr, const int port, bool block = true)
	{
		unsigned long long d;
		memcpy(&d, &addr, sizeof(addr));
		return BaseSocket::connect((u_long)d, port, block);
	}

	//向套接字写入内容，返回0表示连接已断开，返回SOCKET_ERROR表示发生错误，
	//暂时只支持写入字符串，可用于http协议
	int send(char* buf)
	{
		if (!buf) return SOCKET_ERROR;

		return BaseSocket::send((void*)buf, (int)strlen(buf));
	}

	const char* readline(int& retval)
	{
		retval = 0;
		// 返回SOCKET_ERROR != retval && 0 != retval 表示还有数据可以读
		const int max_size = 1024;

		if (!buff_) buff_ = (char*)malloc(max_size);

		retval = recv(buff_, max_size - 1, 0);

		if (retval >= 0)
			buff_[retval] = 0;

		return buff_;
	}

	const char* readall(int& retval)
	{
		//printf("readall start:%lld \n", (long long int)this);
		const int max_size = 1024;
		int total = 0;
		retval = 0;

		for (;;)
		{
			total += max_size;
			buff_ = (char*)(buff_ ? realloc(buff_, total) : malloc(total));

			assert(buff_);

			int len = recv(buff_ + retval, total - retval - 1);

			if (len <= 0)
			{
				break;
			}
			else
			{
				retval += len;

				if (retval < (total - 1)) break;
			}
		}

		//printf("readall end:%lld \n", (long long int)this);
		buff_[retval] = 0;
		return buff_;
	}

public:
	static LuaSocket* NewSocket()
	{
		//printf("NewSocket threadid %d\n", (int)GetCurrentThreadId());
		LuaSocket* s = new LuaSocket();
		int err = createSocket(&s->socket_);

		if (err)
		{
			delete s;
			return NULL;
		}

		//printf("NewSocket:%lld \n", (long long int)s);
		return s;
	}
	static void Release(LuaSocket* s, int step)
	{
		if (!s) return;

		//printf("Release:%lld \n", (long long int)s);

		s->Close();
		delete s;
	}
	static double GetHostByName(const char* host)
	{
		hostent* hostn = gethostbyname(host);
		u_long addr = 0;

		if (hostn)
		{
			addr = *(u_long*)hostn->h_addr_list[0];
		}

		double d;
		memcpy(&d, &addr, sizeof(d));
		return d;
	}
private:
	char*	buff_;
};

#endif

