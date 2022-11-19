#include "os_def.h"
#include "net/base_socket.h"

using namespace net;

BaseSocket::BaseSocket()
{
	socket_ = INVALID_SOCKET;
	local_addr_.sin_family = AF_INET;
	local_addr_.sin_addr.s_addr = 0;
	local_addr_.sin_port = 0;
	remote_addr_ = local_addr_;
	block_flag_ = true;
	connected_ = false;
}

BaseSocket::~BaseSocket()
{
	Close();
}

void BaseSocket::OnConnected()
{
}

void BaseSocket::OnDisconnected()
{
}

void BaseSocket::OnError(int)
{
}

void BaseSocket::Connected()
{
	OnConnected();
}

void BaseSocket::Disconnected()
{
	OnDisconnected();
}

void BaseSocket::SocketError(int errorCode)
{
	OnError(errorCode);
	Close();
}

void BaseSocket::setSocket(const SOCKET socket)
{
	socket_ = socket;

	//设置了套接字后变更为制定的阻塞模式
	if (socket_ != INVALID_SOCKET)
	{
		connected_ = true;
		block_flag_ = !block_flag_;
		setBlockMode(!block_flag_);
	}
	else connected_ = false;
}

int BaseSocket::setBlockMode(const bool block)
{
	//if (block == block_flag_)
	//	return 0;

	if (socket_ != INVALID_SOCKET)
	{
#ifdef _MSC_VER
		u_long ulock = block ? 0 : 1;

		if (ioctlsocket(socket_, FIONBIO, &ulock))
		{
			return WSAGetLastError();
		}

#else
		bool ret = true;
		int flags = fcntl(socket_, F_GETFL, 0);

		if (block)
		{
			fcntl(socket_, F_SETFL, flags & ~O_NONBLOCK);
		}
		else
		{
			if (fcntl(socket_, F_SETFL, flags | O_NONBLOCK) == -1)
				ret = false;
		}

		if (!ret)
		{
			return errno;
		}

#endif
	}

	block_flag_ = block;
	return 0;
}

void BaseSocket::Close()
{
	if (socket_ != INVALID_SOCKET)
	{
		if (connected_)
		{
			Disconnected();
		}

		closesocket(socket_);
		socket_ = INVALID_SOCKET;
	}

	connected_ = false;
	block_flag_ = true;
}

int BaseSocket::shutDown(const int sd)
{
	if (connected_ && socket_ != INVALID_SOCKET)
	{
		int err = shutdown(socket_, sd);

		if (err == 0)
		{
			connected_ = false;
			Disconnected();
		}
	}

	return 0;
}

int BaseSocket::bind(const u_long addr, const int port)
{
	sockaddr_in addrin;

	int on = 1;
	int err = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
	if (err != 0)
		return WSAGetLastError();

	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = addr;
	addrin.sin_port = htons((u_short)port);

	err = ::bind(socket_, (sockaddr*)&addrin, sizeof(addrin));

	if (err == 0)
	{
		local_addr_ = addrin;
	}

	return err ? WSAGetLastError() : 0;
}
//
//int BaseSocket::bind(const char* addr, const int port)
//{
//	hostent* host = gethostbyname(addr);
//
//	if (host)
//	{
//		in_addr addr;
//		addr.s_addr = *(u_long*)host->h_addr_list[0];
//		return bind(addr.s_addr, port);
//	}
//
//	return WSAGetLastError();
//}

int BaseSocket::getRecvBufSize(int* size)
{
	socklen_t oplen = sizeof(*size);
	int err = getsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)size, &oplen);
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::setRecvBufSize(int size)
{
	int err = setsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizeof(size));
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::getSendBufSize(int* size)
{
	socklen_t oplen = sizeof(*size);
	int err = getsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)size, &oplen);
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::setSendBufSize(int size)
{
	int err = setsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)&size, sizeof(size));
	return err ? WSAGetLastError() : 0;
}

int BaseSocket::listen(const int backlog)
{
	int err = ::listen(socket_, backlog);
	return err ? WSAGetLastError() : 0;
}
//
//int BaseSocket::connect(const char* addr, const int port, bool block)
//{
//	hostent* host = gethostbyname(addr);
//
//	if (host)
//	{
//		in_addr addr;
//		addr.s_addr = *(u_long*)host->h_addr_list[0];
//		return connect(addr.s_addr, port, block);
//	}
//
//	return WSAGetLastError();
//}

int BaseSocket::accept(SOCKET* socket, size_t wait_msec, sockaddr_in* addr)
{
	fd_set set;
	timeval tv;
	socklen_t addrsize;

	FD_ZERO(&set);
	FD_SET(socket_, &set);

	tv.tv_sec = long(wait_msec / 1000);
	tv.tv_usec = long(wait_msec * 1000);

	int err = select(int(socket_ + 1), &set, NULL, NULL, &tv);

	if (err < 0)
		return WSAGetLastError();

	if (err > 0)
	{
		addrsize = sizeof(*addr);
		*socket = ::accept(socket_, (sockaddr*)addr, &addrsize);

		if (*socket == INVALID_SOCKET)
		{
			return WSAGetLastError();
		}

		return 0;
	}

	return SOCKET_ERROR - 1;
}

int BaseSocket::connect(const u_long addr, const int port, bool block)
{
	sockaddr_in addrin;

	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = addr;
	addrin.sin_port = htons((u_short)port);

	int err = ::connect(socket_, (sockaddr*)&addrin, sizeof(addrin));

	if (err == 0)
	{
		// 设置是否阻塞模式
		setBlockMode(block);
		connected_ = true;
		Connected();
	}
	else
	{
		err = WSAGetLastError();

		if (err == WSAEWOULDBLOCK)
		{
			err = 0;
			connected_ = false;
		}
	}

	return err;
}

int BaseSocket::createSocket(SOCKET* socket, const int af, const int type, const int protocol)
{
	*socket = ::socket(af, type, protocol);

	if (*socket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	return 0;
}

int BaseSocket::recv(void* buf, int len, const int flags)
{
	int err = ::recv(socket_, (char*)buf, len, flags);

	if (err == 0)
	{
		Close();
	}
	else if (err < 0)
	{
		if (!block_flag_)
		{
			err = WSAGetLastError();

			if (err != WSAEWOULDBLOCK)
			{
				SocketError(err);
				err = -1;
			}
			else err = SOCKET_ERROR - 1;
		}
	}

	return err;
}

int BaseSocket::send(void* buf, int len, const int flags)
{
	char* ptr = (char*)buf;

	int ret = 0;

	while (len > 0)
	{
		int err = ::send(socket_, (char*)ptr, len, flags);

		if (err > 0)
		{
			ret += err;
			ptr += err;
			len -= err;
		}
		else if (err < 0)
		{
			if (!block_flag_)
			{
				err = WSAGetLastError();

				if (err != WSAEWOULDBLOCK)
				{
					ret = SOCKET_ERROR;
					SocketError(err);
				}
				else if (ret == 0)
				{
					ret = SOCKET_ERROR - 1;
				}
			}

			break;
		}
		else
		{
			ret = 0;
			Close();
			break;
		}
	}

	return ret;
}
