#include "StdAfx.h"
#include "base_event.h"

BaseEvent::BaseEvent(GameClientMgr* cli_mgr)
:cli_mgr_(cli_mgr) {
}

BaseEvent::~BaseEvent()
{
}

bool BaseEvent::init(void) {
	return true;
}

void BaseEvent::RunOne(void) {
	
}
