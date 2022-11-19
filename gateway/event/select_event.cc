#include "StdAfx.h"
#include "select_event.h"
SelectEvent::SelectEvent(GameClientMgr* cli_mgr) : BaseEvent(cli_mgr){

}

SelectEvent::~SelectEvent() {

}

void SelectEvent::RunOne(void) {
	cli_mgr_->ProssClient();
}
