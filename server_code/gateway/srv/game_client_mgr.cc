#include "StdAfx.h"
#include <map>
#include "client/client_obj_mgr.h"
#include "event/select_event.h"
#include "event/epoll_event.h"

GameClientMgr::GameClientMgr(const char *name, GateServer *srv) {
	srv_ = srv;
	gw_cli_ = new GameWorldClient(srv, this, name);
	cli_obj_mgr_ = new ClientObjMgr();
	inner_msg_list_.setLock(&inner_msg_lock_);
//#ifdef _MSC_VER
	event_ = new SelectEvent(this);
//#else
//	event_ = new EpollEvent(this);
//#endif
}

GameClientMgr::~GameClientMgr() {
	cli_obj_mgr_->flush();
	SafeDelete(cli_obj_mgr_);
	inner_msg_list_.flush();
	inner_msg_list_.clear();
	SafeDelete(gw_cli_);
}

void GameClientMgr::SetMaxSession(int max_session) {
	cli_obj_mgr_->SetMaxSession(max_session);
}

void GameClientMgr::InitGameWorldClient(const char * ip, int port) {
	gw_cli_ = new GameWorldClient(srv_, this, GetServiceName());
	gw_cli_->UseBaseAlloc(true);
	gw_cli_->SetHost(ip);
	gw_cli_->SetPort(port);
}

bool GameClientMgr::onConnect(SOCKET nSocket, sockaddr_in * pAddrIn) {
	if (!gw_cli_->connected()) return false;

	Client *cli = new Client(this, nSocket, pAddrIn);
	cli_obj_mgr_->setNewClient(cli);
	cli->SetBlockMode(false);
	GateInterMsg msg;
	msg.msg_id_ = gcAddClient;
	msg.data_.fd_ = nSocket;
	PostMsg(msg);
	MSG_TIP("new client connect fd:%d, sid:%d", cli->GetFd(), cli->GetSessionId());
	return true;
}

int GameClientMgr::Run() {
	inner_msg_list_.flush();
	int count = inner_msg_list_.count();
	for (int i = 0; i < count; ++i)
	{
		GateInterMsg& msg = inner_msg_list_[i];
		OnRecvSysMsg(msg);
	}
	inner_msg_list_.clear();
	event_->RunOne();
	return count;
}

void GameClientMgr::OnStart() {
	MSG_LOG("GameClientMgr::OnStart");
}

void GameClientMgr::OnStop() {
	MSG_LOG("GameClientMgr::OnStop");
}

void GameClientMgr::Stop() {
	MSG_LOG("%s, start", GetServiceName());
	while (gw_cli_->GetPacketCount()) {
		gw_cli_->SingleRun();
		Sleep(1);
	}
	gw_cli_->Stop();
	Inherited::Stop();
	MSG_LOG("%s, ok", GetServiceName());
}

void GameClientMgr::OnRecvSysMsg(GateInterMsg & msg) {
	switch (msg.msg_id_) {
	case gcAddClient: {
		event_->AddReadFd(msg.data_.fd_, cli_obj_mgr_->get(msg.data_.index_));
		break;
	}
	case gcGWData: {
		Client* cli = cli_obj_mgr_->get(msg.data_.index_);
		if (cli) {
			auto dp = msg.data_.packet_;
			cli->OnGameWorldRecv(dp->getOffsetPtr(), dp->getAvaliableLength());
		}
		gw_cli_->FreeBackUserDataPacket(msg.data_.packet_);
		break;
	}
	case gcGWClose: {
		Client* cli = cli_obj_mgr_->get(msg.data_.index_);
		if (cli) {
			cli->Close();
		}
		break;
	}
	case gcChAdd: {
		uint64_t key = MAKEINT64(msg.data_.channel_, msg.data_.para_);
		channel_indexs_map_[key].insert(msg.data_.idx_);
		break;
	}
	case gcChDel: {
		uint64_t key = MAKEINT64(msg.data_.channel_, msg.data_.para_);
		channel_indexs_map_[key].erase(msg.data_.idx_);
		break;
	}
	case gcChBro: {
		uint64_t key = MAKEINT64(msg.data_.b_channel_, msg.data_.b_para_);
		auto &list = channel_indexs_map_[key];
		for (auto idx:list) {
			Client* cli = cli_obj_mgr_->get(idx);
			if (cli) {
				auto dp = msg.data_.packet_;
				cli->OnGameWorldRecv(dp->getOffsetPtr(), dp->getAvaliableLength());
			}
		}
		gw_cli_->FreeBackUserDataPacket(msg.data_.dp_);
		break;
	}
	case gcGWDisconn: {
		CloseAllClient();
		break;
	}
	}
}

void GameClientMgr::ProssClient(void) {
	cli_obj_mgr_->flush();
	auto &list = cli_obj_mgr_->getClientMap();
	std::vector<uint16_t> remove_list;
	for (auto it:list)	{
		Client *cli = it.second;
		if (cli->IsClose()) {
			remove_list.push_back(cli->GetSessionId());
			continue;
		}
		cli->RecvData(); //尝试读
		//收到包之后;处理并包半包问题
		cli->PacketHandle();
		cli->WriteEvent();//尝试写
		cli->SendData();//发包
	}
	for (auto idx: remove_list) {
		Client *cli = cli_obj_mgr_->remove(idx);
		SafeDelete(cli);
	}
	remove_list.clear();
}

void GameClientMgr::HandleReadEvent(SOCKET fd, Client * cli) {
	if (cli) {
		cli->RecvData();
		cli->PacketHandle();
	}
}

void GameClientMgr::HandleWriteEvent(SOCKET fd, Client * cli) {
	event_->DelFd(fd);
	if (cli) {
		cli->WriteEvent();//尝试写
		if (!cli->SendData()) {//发包
			//还有包没发送完
			event_->AddWriteFd(fd, cli);
		}
	}
}

void GameClientMgr::CloseAllClient() {
	cli_obj_mgr_->flush();
	auto &list = cli_obj_mgr_->getClientMap();
	std::vector<uint16_t> remove_list;
	for (auto it : list) {
		Client *cli = it.second;
		cli->Close();
	}
}

void GameClientMgr::HaveData(Client * cli) {
	if(cli) {
		event_->AddWriteFd(cli->GetFd(), cli);
	}
}

void GameClientMgr::CloseClient(Client * cli) {
	event_->DelFd(cli->GetFd());
	closesocket(cli->GetFd());
}

bool GameClientMgr::Startup() {
	if (!Inherited::Startup()) {
		return false;
	}
	return gw_cli_->Startup();
}
