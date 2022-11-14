#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::GameWorldProto;

GameGate::GameGate()
	: Inherited("GameGate"),/* send_gate_alloc_("send_gate_alloc_"),*/
	  recv_gate_alloc_("recv_gate_alloc_")
{
	login_srv_ = NULL;

	// 如果不调用这个，有可能导致内存占用比较大
	UseBaseAlloc(true);

	for (int i = 0; i < ThreadMax; ++i)
	{
		ThreadGateMsg& data = msg_thread_[i];
		data.free_list_.setLock(&data.free_lock_);
		data.big_packet_ = NULL;
	}
}

GameGate::~GameGate()
{
	// 释放datapacket
	FlushPackets();

	// 由于部分的datapacket是使用send_gate_alloc_分配内存
	// 所以这里显式删除内存，避免send_gate_alloc_先被删除了造成程序崩溃
	FreeAllPackets();
}


void GameGate::OnOpenUser(GateUser* user)
{
	user->account_id_ = 0;
	user->account_name_[0] = 0;
	user->handle_ = 0;
	user->actor_id_ = 0;
	user->gm_ = -1;

	OutputMsg(rmError, "openuser:%lld, reset all data", (long long int)user);
}

void GameGate::OnCloseUser(GateUser* user, const char* reason)
{
	int account_id = user->account_id_;

	OutputMsg(rmTip, "user closed.actorid=%d,accountId=%d,ptr=%lld",
	          user->actor_id_, account_id, (long long int)user);

	if (account_id != 0)
	{
		//hanlde_ != 0 证明已经登录到GameEgine
		//否则仍在actormgr上面
		if (user->handle_ != 0)
		{
			GameInterMsg msg;
			msg.msg_id_ = SSM_ACTOR_LOGOUT;
			msg.data_.handle_ = user->handle_;
			msg.data_.account_id_ = account_id;
			_STRNCPY_A(msg.data_.fn_, reason ? reason : "");

			static GameEngine* ge = GetGameEngine();
			ge->PostMsg(msg);

			OutputMsg(rmError, "post actor logout msg:actorid=%d, ptr=%lld,reason=%s",
			          user->actor_id_, (long long int)user, reason ? reason : "");
		}
		else
		{
			GameInterMsg msg;
			msg.msg_id_ = ActorMgr::imCloseUserInActorMgr;
			msg.data_.account_id_ = account_id;

			static ActorMgr* mgr = ServerInstance()->GetActorMgr();
			mgr->PostMsg(msg);

			OutputMsg(rmError, "post actor close in actormgr msg:actorid=%d, ptr=%lld, reason=%s", 
					 user->actor_id_, (long long int)user, reason ? reason : "");
		}
	}

	user->account_id_ = 0;
	user->account_name_[0] = 0;
	user->handle_ = 0;
	user->actor_id_ = 0;
	user->gm_ = -1;
}

void GameGate::OnRecv(NetId& netid, char* buf, int size)
{
	GateUser* gate_user = GetUser(netid);

	if (!gate_user) {OutputMsg(rmError, "GameGate::OnRecv size=%d   user null", size); return;}

	int thread_id = GameThread;

	if (gate_user->handle_ == 0) // 发送到角色管理线程的包
	{
		thread_id = ActorMgrThread;
	}

	ThreadGateMsg* thread_msg = &msg_thread_[thread_id];

	// 看是否需要释放内存
	if (thread_msg->gc_)
	{
		thread_msg->gc_ = false;
		// 目前的策略是留总数的1/3
		int rest = (int)(thread_msg->pack_total_ * 0.3);
		//OutputMsg(rmError, "GameGate::OnRecv thread_msg->gc_ rest=%d   pack_total_ =%d ", rest, thread_msg->pack_total_);
		if (thread_msg->free_list_.count() > rest)
		{
			int freeCnt = thread_msg->free_list_.count() - rest;

			for (int i = rest; i < thread_msg->free_list_.count(); ++i)
			{
				DataPacket* dp = thread_msg->free_list_[i];
				delete dp;
			}

			thread_msg->free_list_.trunc(rest);
			thread_msg->pack_total_ -= freeCnt;
		}


	}

	if (thread_msg->free_list_.count() <= 0)
	{
		//AllocSendPack(&(thread_msg->free_list_), 5 * 4096, NULL, &send_gate_alloc_);		// 这里分配足够多的数据包，避免后面再增加数据包
		DataPacket* newDp = new DataPacket(&recv_gate_alloc_);
		thread_msg->free_list_.add(newDp);
		thread_msg->pack_total_++;
	}

	DataPacket* temp = thread_msg->free_list_.pop();
	temp->setLength(0);

	if (thread_id == GameThread)
		(*temp) << gate_user->handle_;
	else
		(*temp) << netid;

	temp->writeBuf(buf, size);
	thread_msg->netmsg_list_.add(temp);
}

void GameGate::OnRun()
{
	Inherited::OnRun();

	// 把接收到的网络包传递给网关管理器,由网关管理器再传递给主线程
	for (int thread_id = 0; thread_id < GameGate::ThreadMax; ++thread_id)
	{
		gate_mgr_->PostUserDataList(gate_idx_, msg_thread_[thread_id].netmsg_list_, thread_id);
		ThreadGateMsg& thread_data = msg_thread_[thread_id];
		if (thread_data.free_list_.appendCount() > 0)
		{
			thread_data.free_list_.flush();
		}
	}
}

void GameGate::OnDisconnected()
{
	if (registed())
	{
		static GameEngine* ge = GetGameEngine();
		GameInterMsg msg;
		msg.msg_id_ = SSM_GW_DUMP;
		msg.data_.account_id_ = gate_idx_;

		OutputMsg(rmError, "gateway disconnect in GameGate::OnDisconnected!!gate=%d", gate_idx_);

		ge->PostMsg(msg);

		OutputMsg(rmError, "post SSM_GW_DUMP msg to GE");
	}
	else
	{
		OutputMsg(rmError, "==========no registe client disconnect!!=============");
	}
}

bool GameGate::CloseUserByAccount(int accountId)
{
	OutputMsg(rmError, "GameGate::CloseUserByAccount accountId=%d", accountId);

	for (int i = 0; i < MAX_GATE_USER; ++i)
	{
		GateUser& user = user_list_[i];

		if (user.account_id_ == accountId)
		{
			PostCloseUser(user.netid_, accountId, "GameGate::CloseUserByAccount");
			return true;
		}
	}

	return false;
}

void GameGate::GC()
{
	for (int thread_id = 0; thread_id < GameGate::ThreadMax; ++thread_id)
	{
		ThreadGateMsg& thread_data = msg_thread_[thread_id];
		thread_data.gc_ = true;
	}

	SendPacketPool::GC();
}

void GameGate::FlushPackets()
{
	for (int thread_id = 0; thread_id < ThreadMax; ++thread_id)
	{
		ThreadGateMsg& data = msg_thread_[thread_id];

		data.free_list_.appendList(data.netmsg_list_);
		data.netmsg_list_.clear();

		data.free_list_.flush();

		for (int i = 0; i < data.free_list_.count(); i++)
		{
			DataPacket* dp = data.free_list_[i];
			dp->setLength(0);
			//Flush(*dp);
			delete dp;
			data.pack_total_--;
		}

		data.free_list_.clear();

		if (data.free_back_list_.count() != 0)
		{
			//int c = data.free_back_list_.count();
			assert(false);
		}

		//最后的大包发向网关：），实际为了释放这个包的内存
		SendToGate(thread_id);
	}
}



