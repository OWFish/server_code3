#include "StdAfx.h"
#include "client_obj_mgr.h"
#include <map>

ClientObjMgr::ClientObjMgr() {
	cur_idx_ = 0;
	max_session_ = 0;
}


ClientObjMgr::~ClientObjMgr() {
	flush();
	for (auto cli:client_list_) {
		SafeDelete(cli.second);
	}
	client_list_.clear();
}

void ClientObjMgr::SetMaxSession(int max_session) {
	max_session_ = max_session;
}

bool ClientObjMgr::setNewClient(Client *cli) {
	client_lock_.Lock();
	if (max_session_ <= cur_idx_) return false;
	uint16_t index = 0;
	if (free_cli_idx_.empty()) {
		index = cur_idx_++;
	} else {
		index = free_cli_idx_.front();
		free_cli_idx_.pop_front();
	}
	cli->SetSessionId(index);
	client_append_list_.push_back(cli);
	client_lock_.Unlock();
	return true;
}

void ClientObjMgr::flush(void) {
	client_lock_.Lock();
	for (auto it:client_append_list_) {
		client_list_.insert(std::make_pair(it->GetSessionId(), it));
	}
	client_append_list_.clear();
	client_lock_.Unlock();
}

Client* ClientObjMgr::get(uint16_t index) {
	auto it = client_list_.find(index);
	if (it == client_list_.end()) return NULL;
	return it->second;
}

Client * ClientObjMgr::remove(uint16_t index) {
	auto it = client_list_.find(index);
	if (it == client_list_.end()) return NULL;
	Client *cli = it->second;
	client_list_.erase(it);
	client_lock_.Lock();
	if (index == cur_idx_ - 1) {
		--cur_idx_;
	} else {
		free_cli_idx_.push_back(index);
	}
	client_lock_.Unlock();
	return cli;
}
