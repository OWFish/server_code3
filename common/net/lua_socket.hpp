#ifndef _LUA_SOCKET_HPP_
#define _LUA_SOCKET_HPP_

/******************************************************************
 *��װһ���򵥵�socket���lua����
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

	// ��������,��ʱֻ֧������ģʽ
	//ͨ��32λIP��ַ���ӵ��ƶ��Ķ˿ڣ�����ֵΪsocket����ţ�0��ʾ�ɹ������ڷ�����ģʽ����0������ʾ�Ѿ���������
	int connect(const double addr, const int port, bool block = true)
	{
		unsigned long long d;
		memcpy(&d, &addr, sizeof(addr));
		return BaseSocket::connect((u_long)d, port, block);
	}

	//���׽���д�����ݣ�����0��ʾ�����ѶϿ�������SOCKET_ERROR��ʾ��������
	//��ʱֻ֧��д���ַ�����������httpЭ��
	int send(char* buf)
	{
		if (!buf) return SOCKET_ERROR;

		return BaseSocket::send((void*)buf, (int)strlen(buf));
	}

	const char* readline(int& retval)
	{
		retval = 0;
		// ����SOCKET_ERROR != retval && 0 != retval ��ʾ�������ݿ��Զ�
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

