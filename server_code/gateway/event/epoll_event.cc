#include "StdAfx.h"
#include "epoll_event.h"

#ifndef _MSC_VER
EpollEvent::EpollEvent(GameClientMgr* cli_mgr) : BaseEvent(cli_mgr) {
	epollfd_ = 0;
	listen_fd_ = 0;
}


EpollEvent::~EpollEvent() {
	if (epollfd_) {
		close(epollfd_);
	}
}
bool EpollEvent::init(void) {
	epollfd_ = epoll_create(EPOLLEVENTS);
	return true;
}
void EpollEvent::RunOne(void) {
	int ret = epoll_wait(epollfd_, events_, EPOLLEVENTS, 0);
	for (int i = 0; i < ret; i++) {
		Client *ptr = (Client*)events_[i].data.ptr;
		if (events_[i].events & EPOLLIN) {
			cli_mgr_->HandleReadEvent(ptr->GetFd(), ptr);
		} else if (events_[i].events & EPOLLOUT) {
			cli_mgr_->HandleWriteEvent(ptr->GetFd(), ptr);
		}
	}
}

void EpollEvent::AddReadFd(SOCKET fd, void *ptr) {
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = ptr;
	epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev);
}

void EpollEvent::DelFd(SOCKET fd, void *ptr) {
	epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, NULL);
}

void EpollEvent::AddWriteFd(SOCKET fd, void *ptr) {
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.ptr = ptr;
	epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &ev);
}

#endif
