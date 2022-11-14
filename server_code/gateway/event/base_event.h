#pragma once
class BaseEvent
{
public:
	BaseEvent(GameClientMgr* cli_mgr);
	~BaseEvent();
	virtual bool init(void);
	virtual void RunOne(void);
	virtual void AddReadFd(SOCKET fd, void *ptr = NULL) {}
	virtual void DelFd(SOCKET fd, void *ptr = NULL) {}
	virtual void AddWriteFd(SOCKET fd, void *ptr = NULL) {}

protected:
	GameClientMgr* cli_mgr_;
};

