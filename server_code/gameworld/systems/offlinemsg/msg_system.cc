#include "StdAfx.h"
#include "msg_system.h"

using namespace InterSrvComm::DbServerProto;

MsgSystem::MsgSystem(Actor *actor)
{
	actor_ = actor;
}

MsgSystem::~MsgSystem()
{
	MsgData* list =	msg_list_;

	for (int i = msg_list_.count() - 1; i >= 0; --i)
	{
		MsgData& msg = list[i];
		msg.pack_.empty();
	}

	msg_list_.empty();
}

bool MsgSystem::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;

		int ncount = 0;
		data >> ncount;
		int total = ncount + msg_list_.count();

		if (msg_list_.max_size() < total)
		{
			msg_list_.reserve(total * 2);
		}

		int beg_msg_idx = msg_list_.count();

		for (int i = 0; i < ncount; i++)
		{
			// 读取MsgData的内容
			int now_cnt = msg_list_.count();
			msg_list_.trunc(now_cnt + 1);

			MsgData& msg = msg_list_[now_cnt];
			data >> msg.id_;
			static MsgSysAlloc alloc("msgsystem_alloc", 256, 8);
			new(&msg.pack_)DataPacket(&alloc);
			int psize = 0;
			data >> psize;

			if (psize > 0)
			{
				msg.pack_.writeBuf(data.getOffsetPtr(), psize);
				data.adjustOffset(psize);
				msg.pack_.setPosition(0);
			}
		}

		int end_msg_idx = msg_list_.count();

		//通知lua处理离线消息
		luaRecvMsg(beg_msg_idx, end_msg_idx);
		return true;
}

bool MsgSystem::Initialize(/*void* data, size_t size*/)
{
	msg_list_.reserve(12);
	return true;
}

void MsgSystem::OnEnterGame()
{
	SendDbLoadMsg();
}

void MsgSystem::ReloadFromDb(int64_t msg_id)
{
	//检查内存的列表中是否有这条消息，避免重复读入数据
	int ncount = msg_list_.count();

	for (int idx = 0; idx < ncount; ++idx)
	{
		MsgData& msg = msg_list_[idx];

		if (msg.id_ == msg_id)
		{
			return;
		}
	}

	//向数据库发送读入新消息
	SendDbLoadMsg(msg_id);
}

void MsgSystem::SendDbLoadMsg(int64_t msg_id /*= 0*/)
{
	if (actor_ == NULL)
	{
		return;
	}

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());

	if (db == NULL)
	{
		return;
	}

	//如果nMsgid == 0，读入所有消息，否则读入固定id的消息
	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcLoadMsg));
	pack << (ActorId)actor_->GetActorId();
	pack << (int64_t)msg_id;

	db->flushProtoPacket(pack);
}

void MsgSystem::OnDbRetData(int ncmd, int nerr,  DataPacketReader& reader)
{
	//switch (ncmd)
	//{
	//case dcLoadMsg://接收自己的消息
	//	{
	//		if (nerr != reSucc)
	//		{
	//			OutputMsg(rmError, ("load actor msg error!"));
	//		}
	//		else
	//		{
	//			int ncount = 0;
	//			reader >> ncount;
	//			int total = ncount + msg_list_.count();

	//			if (msg_list_.max_size() < total)
	//			{
	//				msg_list_.reserve(total * 2);
	//			}

	//			int beg_msg_idx = msg_list_.count();

	//			for (int i = 0; i < ncount; i++)
	//			{
	//				// 读取MsgData的内容
	//				int now_cnt = msg_list_.count();
	//				msg_list_.trunc(now_cnt + 1);

	//				MsgData& msg = msg_list_[now_cnt];
	//				reader >> msg.id_;
	//				static MsgSysAlloc alloc("msgsystem_alloc", 256, 8);
	//				new(&msg.pack_)DataPacket(&alloc);
	//				int psize = 0;
	//				reader >> psize;

	//				if (psize > 0)
	//				{
	//					msg.pack_.writeBuf(reader.getOffsetPtr(), psize);
	//					reader.adjustOffset(psize);
	//					msg.pack_.setPosition(0);
	//				}
	//			}

	//			int end_msg_idx = msg_list_.count();

	//			//通知lua处理离线消息
	//			luaRecvMsg(beg_msg_idx, end_msg_idx);
	//		}
	//	}
	//	break;

	//default:
	//	break;
	//}
}


void MsgSystem::luaRecvMsg(int beg_msg_idx, int end_msg_idx)
{
	if (beg_msg_idx >= end_msg_idx)
	{
		return;
	}

	ScriptValueList param_list;
	param_list << actor_;
	param_list << beg_msg_idx;
	param_list << end_msg_idx;

	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();

	lua.Call("recOffMsg", &param_list, &param_list);
	return;
}

bool MsgSystem::DeleteMsg(int idx)
{
	if (actor_ == NULL)
	{
		return false;
	}

	if (idx < 0 || idx >= msg_list_.count())
	{
		return false;
	}

	//内存中删除
	int64_t msg_id = msg_list_[idx].id_;
	msg_list_[idx].pack_.empty();
	msg_list_.remove(idx);

	//数据库删除
	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());

	if (db == NULL)
	{
		return false;
	}

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcDeleteMsg));
	pack << (int)actor_->GetActorId();
	pack << (int64_t)msg_id;
	db->flushProtoPacket(pack);

	return true;
}


