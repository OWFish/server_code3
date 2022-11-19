#pragma once
#ifndef _MSC_VER
#include "base_event.h"
#include <sys/epoll.h>

#define EPOLLEVENTS 1024
class EpollEvent :
	public BaseEvent {
public:
	EpollEvent(GameClientMgr* cli_mgr);
	~EpollEvent();
	virtual bool init(void);
	virtual void RunOne(void);
	virtual void AddReadFd(SOCKET fd, void *ptr = NULL);
	virtual void DelFd(SOCKET fd, void *ptr = NULL);
	virtual void AddWriteFd(SOCKET fd, void *ptr = NULL);
private:
	SOCKET epollfd_;
	SOCKET listen_fd_;
	struct epoll_event events_[EPOLLEVENTS];
};
#endif
