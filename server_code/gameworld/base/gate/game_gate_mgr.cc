#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

GameGateMgr::GameGateMgr(GameServer* game_srv)
	: Inherited("GameGateMgr")
{
	game_srv_ = game_srv;

	for (int i = 0; i < MaxGateCount; i++)
	{
		GateList* gate = gates_ + i;

		for (int thread_id = 0; thread_id < GameGate::ThreadMax; ++thread_id)
		{
			DataList& list = gate->list_[thread_id];
			list.list_.setLock(&list.lock_);
		}
	}
}

GameGateMgr::~GameGateMgr()
{
	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* game_gate = &(gates_[gate_idx].gate_);

		for (int thread_id = 0; thread_id < GameGate::ThreadMax; ++thread_id)
		{
			QueueList<DataPacket*>* data_list = &(gates_[gate_idx].list_[thread_id].list_);

			if (data_list->appendCount() > 0)
				data_list->flush();

			if (data_list->count() > 0)
			{
				game_gate->msg_thread_[thread_id].free_list_.appendList(*data_list);	// 加到这里是为了释放内存

				data_list->trunc(0);
			}
		}
	}
}

void GameGateMgr::Initialize()
{
	for (int i = 0; i < MaxGateCount; ++i)
	{
		GameGate* gate = &(gates_[i].gate_);

		gate->login_srv_ = game_srv_;
		gate->gate_mgr_ = this;
		gate_list_[i] = gate;
	}
}

void GameGateMgr::Uninitialize()
{
	for (size_t i = 0; i < ArrayCount(gate_list_); ++i)
	{
		gate_list_[i] = NULL;
	}
}

bool GameGateMgr::Startup()
{
	return Inherited::Startup();
}

void GameGateMgr::Stop()
{
	// 没来得及处理的包要还回给gate
	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* gate = &(gates_[gate_idx].gate_);

		//先close连接，避免再接收新的数据包
		if (gate) gate->Close();

		for (int thread_id = 0; thread_id < GameGate::ThreadMax; ++thread_id)
		{
			QueueList<DataPacket*>& data_list = gates_[gate_idx].list_[thread_id].list_;

			if (data_list.appendCount() > 0)
				data_list.flush();

			if (data_list.count() > 0)
			{
				gate->AddFreeList(data_list, data_list.count(), thread_id);
				data_list.trunc(0);
			}

			// 回收已经处理过的数据包
			gate->FlushFreeList(thread_id);
		}
	}

	Inherited::Stop();
}

void GameGateMgr::PostUserDataList(const int gate_idx, Vector<DataPacket*>& data_list, int thread_id)
{
	QueueList<DataPacket*>& thread_data_list = gates_[gate_idx].list_[thread_id].list_;
	thread_data_list.appendList(data_list);
	data_list.trunc(0);
}

void GameGateMgr::CollectGameData()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* gate = &(gates_[gate_idx].gate_);

		// 回收已经处理过的数据包
		gate->FlushFreeList(GameGate::GameThread);

		QueueList<DataPacket*>& data_list = gates_[gate_idx].list_[GameGate::GameThread].list_;

		if (data_list.appendCount() > 0)
			data_list.flush();

		int data_count = data_list.count();

		if (data_count > 0)
		{
			DataPacket** list = data_list;

			for (int i = 0; i < data_count; ++i)
			{
				DataPacket* packet = (list[i]);
				packet->setPosition(0);

#pragma pack(push, 1)
				static struct Data
				{
					EntityHandle hdl_;
					int nid_;
				} data;
#pragma pack(pop)

				packet->readBuf(&data, sizeof(data));

				Actor* actor = (Actor*)em->GetEntity(data.hdl_);

				if (!actor || data.hdl_.GetType() != enActor)
				{
					OutputMsg(rmWarning, "recv data fail,entity has destroyed ");
					gates_[gate_idx].gate_.AddFreeList(packet, GameGate::GameThread);
					continue;
				}

				actor->PostNetMsg(packet, data.nid_);
			}

			data_list.trunc(0);
		}

		//这里发送给网关的数据
		gate->SendToGate(GameGate::GameThread);
	}
}

int GameGateMgr::CollectActorMgrData()
{
	ActorMgr* mgr = ServerInstance()->GetActorMgr();

	if (!mgr) {OutputMsg(rmError, "GameGateMgr::CollectActorMgrData null"); return 0;}
	int proce_count = 0;

	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* gate = &(gates_[gate_idx].gate_);

		// 回收已经处理过的数据包
		gate->FlushFreeList(GameGate::ActorMgrThread);

		QueueList<DataPacket*>& data_list = gates_[gate_idx].list_[GameGate::ActorMgrThread].list_;

		if (data_list.appendCount() > 0)
			data_list.flush();

		int data_count = data_list.count();
		//OutputMsg(rmWarning, "GameGateMgr::CollectActorMgrDat data_count = %d ", data_count);
		if (data_count > 0)
		{
			DataPacket** pack_list = data_list;
			for (int i = 0; i < data_count; ++i)
			{
				DataPacket* p = pack_list[i];
				p->setPosition(0);
				mgr->ProcessNetMsg(*p, gate_idx);
			}

			gate->AddFreeList(data_list, data_count, GameGate::ActorMgrThread);
			data_list.trunc(0);
			proce_count += data_count;
		}

		//这里发送给网关的数据
		gate->SendToGate(GameGate::ActorMgrThread);
	}

	return proce_count;
}

void GameGateMgr::OnRecvSysMsg(unsigned int msg, size_t p1, size_t, size_t, size_t)
{
	switch (msg)
	{
	case imCloseUser:
		{
			CloseUserByAccount((int)p1);
			break;
		}
	}
}

void GameGateMgr::CloseUserByAccount(int accountID)
{
	OutputMsg(rmError, "GameGateMgr::CloseUserByAccount accountId=%d", accountID);

	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* gate = &(gates_[gate_idx].gate_);

		if (gate->connected())
		{
			if (gate->CloseUserByAccount(accountID))
			{
				break;
			}
		}
	}
}

void GameGateMgr::GC()
{
	for (int gate_idx = 0; gate_idx < GateManager::MaxGateCount; ++gate_idx)
	{
		GameGate* gate = &(gates_[gate_idx].gate_);

		if (gate->connected())
		{
			gate->GC();
		}
	}
}

