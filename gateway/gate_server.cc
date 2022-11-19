#include "StdAfx.h"

GateServer::GateServer() {
	GateServer::Instance = this;
	GetSystemTime(cur_sys_time_);
	now_sec_.encode(cur_sys_time_);
}

GateServer::~GateServer() {
	for (auto gcmgr : game_client_mgr_) {
		SafeDelete(gcmgr);
	}
	game_client_mgr_.clear();
}

bool GateServer::StartServer() {
	MSG_LOG("start server...................");
	for (auto gcmgr : game_client_mgr_) {
		gcmgr->Startup();
	}
	return true;
}

void GateServer::StopServer() {
	MSG_LOG("stop server................... start");
	for (auto gcmgr : game_client_mgr_) {
		gcmgr->Stop();
	}
	MSG_LOG("stop server................... ok");
}

GameClientMgr* GateServer::AddGameClientMgr(const char *name)
{
	GameClientMgr* gcmgr = new GameClientMgr(name, this);
	gcmgr->SetServiceName(name);
	game_client_mgr_.push_back(gcmgr);
	return gcmgr;
}
