#pragma once
#include "base_event.h"
#include <map>

class SelectEvent :	public BaseEvent {
public:
	typedef std::map<SOCKET, void*> FdPtrMap;
	SelectEvent(GameClientMgr* cli_mgr);
	~SelectEvent();
	virtual void RunOne(void);
};
