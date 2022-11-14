#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;

static BaseAllocator alloc_gameserver("alloc_gameserver");

LianfuMgr::LianfuMgr() : lianfu_conn_(false),
	lianfu_sid_(0),
	send_packet_(packet_buf_, sizeof(packet_buf_)),
	is_closed_(false)
{
}

LianfuMgr::~LianfuMgr()
{
}

void LianfuMgr::OnRegReq(int sid)
{
	SendBatchOnline(sid);
}

void LianfuMgr::OnRegResp(int sid)
{
	lianfu_conn_ = true;

	SendBatchOnline(sid);

	//连服排行榜数据(连接上了更新排行榜)
	static LianfuRank& rank = GetGameEngine()->GetLianfuRank();
	rank.OnUpdateRank();

	//连服仙宗数据(连接上了更新帮派列表)
	//static LianfuGuild& mgr = GetGameEngine()->GetLianfuGuild();
	//mgr.OnLoadGuild();
}

void LianfuMgr::SendBatchOnline(int sid)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp.setPosition(0);

	dp << (int)stBatchOnline;
	em->GetOnlineActorIdToPack(dp);

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, sid, CROSSSERVER_LIANFU);
}

void LianfuMgr::AddOnlineUser(ActorId aid, int curr_serverid, int comm_serverid)
{
	ActorOnlineInfo* actor_info = actor_id_online_.get(aid);

	if (actor_info)
	{
		OutputMsg(rmError, "add online user %d error : is exist", aid);
		actor_info->curr_server_id_ = curr_serverid;
		actor_info->comm_server_id_ = comm_serverid;
		return;
	}

	ActorOnlineInfo info;
	info.curr_server_id_ = curr_serverid;
	info.comm_server_id_ = comm_serverid;
	actor_id_online_.put(aid, info);
}

bool LianfuMgr::RemoveOnlineUser(ActorId aid)
{
	return actor_id_online_.remove(aid);
}

void LianfuMgr::OnUserLogin(Actor* actor)
{
	if (!actor || !IsLianfu()) return;

	static GameServer* gs = ServerInstance();

	ActorId aid = actor->GetActorId();
	AddOnlineUser(aid, gs->GetServerIndex(), actor->GetServerId());

	// 通知其他服玩家在线了
	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp.setPosition(0);
	dp << (int)stUserLogin;
	dp << (int)aid;
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, gs->IsCommonSrv() ? lianfu_sid_ : actor->GetServerId(), CROSSSERVER_LIANFU);
}

void LianfuMgr::OnUserLogout(Actor* actor)
{
	if (!actor || !IsLianfu()) return;

	static GameServer* gs = ServerInstance();

	ActorId aid = actor->GetActorId();
	RemoveOnlineUser(aid);

	// 通知其他服
	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp.setPosition(0);
	dp << (int)stUserLogout;
	dp << (int)aid;
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, gs->IsCommonSrv() ? lianfu_sid_ : actor->GetServerId(), CROSSSERVER_LIANFU);
}

bool LianfuMgr::IsOpenLianfu()
{
	static GameServer* gs = ServerInstance();
	if (gs->IsLianFuSrv()) return true;

	return lianfu_sid_ != 0;
}

bool LianfuMgr::IsLianfu()
{
	if (is_closed_) return false;

	static GameServer* gs = ServerInstance();
	if (gs->IsLianFuSrv()) return true;

	return lianfu_conn_;
}

void LianfuMgr::OnLianfuMsg(int sid, int cmd, DataPacket& packet)
{
	switch (cmd)
	{
	case stBroadCast:
		HandleBroadCast(packet);
		break;
	case stUserLogin:
		HandleUserLogin(sid, packet);
		break;
	case stUserLogout:
		HandleUserLogout(sid, packet);
		break;
	case stBatchOnline:
		HandleBatchLogin(sid, packet);
		break;
	case stKickUser:
		HandleKickUser(packet);
		break;
	default:
		if (cmd > stNormalMax)
		{
			HandleScriptPacket(cmd, packet);
		}
		break;
	}
}

void LianfuMgr::ProcessNetData(int cmd, DataPacketReader& packet)
{

}

void LianfuMgr::BroadCast(int channelId, int param, const char* data, size_t size, int sid/* = 0*/)
{
	static GameEngine* ge = GetGameEngine();
	ge->BroadCast(channelId, param, data, size);

	if (!IsLianfu()) return;

	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp << (int)stBroadCast;
	dp << (int)channelId;
	dp << (int)param;
	dp.writeBuf(data, size);

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, gs->IsCommonSrv() ? lianfu_sid_ : sid, CROSSSERVER_LIANFU);
}

void LianfuMgr::BroadCast(const char* data, size_t size, int sid/* = 0*/)
{
	BroadCast(ciChannelWorld, 0, data, size, sid);
}

int LianfuMgr::GetOnlineServerId(ActorId actor_id)
{
	ActorOnlineInfo* actor_info = actor_id_online_.get(actor_id);
	if (!actor_info)
	{
		return 0;
	}
	return actor_info->curr_server_id_;
}

int LianfuMgr::GetCommServerId(ActorId actor_id)
{
	ActorOnlineInfo* actor_info = actor_id_online_.get(actor_id);
	if (!actor_info)
	{
		return 0;
	}
	return actor_info->comm_server_id_;
}

bool LianfuMgr::IsOnlineOtherServer(ActorId actor_id)
{
	ActorOnlineInfo* actor_info = actor_id_online_.get(actor_id);
	if (!actor_info)
	{
		return false;
	}

	static GameServer* gs = ServerInstance();

	return (actor_info->curr_server_id_ != gs->GetServerIndex());
}

void LianfuMgr::SetServerList(int* list, int cnt)
{
	if (!list) return;

	for (int idx = 0; idx < cnt; idx++)
	{
		bool find = false;
		for (int i = 0; i < server_list_.count(); i++)
		{
			if (server_list_[i].sid_ == list[idx])
			{
				find = true;
				break;
			}
		}
		
		if (find) continue;

		if (server_list_.count() >= MAX_LIANFU_SERVER)
		{
			OutputMsg(rmError, "set server list error : max server count");
			return;
		}

		int list_cnt = server_list_.count();
		server_list_.trunc(list_cnt + 1);
		server_list_[list_cnt].sid_ = list[idx];
	}
}

CommServer* LianfuMgr::GetServerInfo(int sid)
{
	for (int i = 0; i < server_list_.count(); i++)
	{
		if (server_list_[i].sid_ == sid)
		{
			return &server_list_[i];
		}
	}
	return NULL;
}

DataPacket& LianfuMgr::AllocSendPacket(uint8_t sys_id, uint8_t cmd_id)
{
	uint8_t hdr[] = { sys_id, cmd_id };
	send_packet_.setPosition(0);
	send_packet_.writeBuf(hdr, sizeof(hdr));
	return send_packet_;
}

void LianfuMgr::SendToLianfuServer(const void* buf, size_t size)
{
	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(buf, size, gpLfData, lianfu_sid_, CROSSSERVER_LIANFU);
}

void LianfuMgr::KickUser(ActorId aid)
{
	static GameServer* gs = ServerInstance();
	if (!gs->IsCommonSrv())
	{
		return;
	}

	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp.setPosition(0);
	dp << (int)stKickUser;
	dp << (ActorId)aid;

	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, 0, CROSSSERVER_LIANFU);
}

void LianfuMgr::HandleUserLogin(int sid, DataPacket& packet)
{
	ActorId aid = 0;
	packet >> aid;

	static GameServer* gs = ServerInstance();
	int common_sid = gs->IsCommonSrv() ? gs->GetServerIndex() : sid;

	AddOnlineUser(aid, sid, common_sid);
}

void LianfuMgr::HandleUserLogout(int sid, DataPacket& packet)
{
	ActorId aid = 0;
	packet >> aid;
	RemoveOnlineUser(aid);
}

void LianfuMgr::HandleBatchLogin(int sid, DataPacket& packet)
{
	static GameServer* gs = ServerInstance();
	int common_sid = gs->IsCommonSrv() ? gs->GetServerIndex() : sid;

	int cnt = 0;
	packet >> cnt;

	//todo 这里还要处理连服的仙宗状态
	ActorId aid = 0;

	for (int i = 0; i < cnt; i++)
	{
		packet >> aid;
		AddOnlineUser(aid, sid, common_sid);
	}
}

void LianfuMgr::HandleKickUser(DataPacket& packet)
{
	ActorId aid;
	packet >> aid;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(aid);
	if (actor)
	{
		ServerInstance()->GetGateManager()->PostCloseUser(actor->GetNetId(), __FUNCTION__, aid);
	}
	else
	{
		OutputMsg(rmError, "LianfuMgr kick user(%d) error", aid);
	}
}

void LianfuMgr::HandleScriptPacket(int cmd, DataPacket& packet)
{
	ScriptValueList paramList;
	paramList << (int)cmd;
	paramList << &packet;

	static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();

	if (npc == NULL) return;

	if (!npc->GetScript().Call("OnLianfuServerPacket", &paramList, &paramList))
	{
		OutputMsg(rmError, "handle script msg error");
	}
}

void LianfuMgr::HandleBroadCast(DataPacket& packet)
{
	int channelId = 0;
	int param = 0;
	packet >> channelId >> param;
	static GameEngine* ge = GetGameEngine();
	ge->BroadCast(channelId, param, packet.getOffsetPtr(), packet.getAvaliableBufLen());
}

/* todo 邮件改为lua实现
void LianfuMgr::NotifyRecvMail(ActorId aid, int64_t msgId, int sid)
{
	DataPacket dp(packet_buf_, sizeof(packet_buf_));
	dp.setPosition(0);
	dp << (int)stRecvMail;
	dp << (ActorId)aid;
	dp << (int64_t)msgId;

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpSsData, sid, CROSSSERVER_LIANFU);
}

void LianfuMgr::HandleRecvMail(DataPacket& packet)
{
	static GameServer* gs = ServerInstance();

	// 不是普通服则跳过
	if (!gs->IsCommonSrv()) return;

	ActorId aid;
	int64_t msgId;

	packet >> aid;
	packet >> msgId;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	Actor* actor = em->GetActorPtrById(aid);
	if (actor)
	{
		actor->GetMailSystem().ReloadFromDb(msgId);
	}
}
*/

bool LianfuMgr::TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len, const void* extraData, size_t extraSize)
{
	if (!IsLianfu()) return false;

	//必须要有消息头(sysid, pid)
	if (!data || len < 2) return false;

	DataPacket dp(transfer_buf_, sizeof(transfer_buf_));
	dp << (int)dtActorDeal;
	dp << (ActorId)tActorId;
	dp << (ActorId)sActorId;
	dp.writeBuf(data, len);

	if (extraData && extraSize > 0)
	{
		dp.writeBuf(extraData, extraSize);
	}

	static GameServer* gs = ServerInstance();
	if (gs->IsCommonSrv())
	{
		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), (size_t)dp.getLength(),
			InterSrvComm::GameWorldProto::gpTtData, lianfu_sid_, CROSSSERVER_LIANFU);
	}
	else if (gs->IsLianFuSrv())
	{
		int sid = GetOnlineServerId(tActorId);
		if (sid <= 0) return false;

		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), (size_t)dp.getLength(),
			InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
	}
	else
	{
		OutputMsg(rmError, "server is not commonserver or lianfuserver ..");
		return false;
	}

	return true;
}

bool LianfuMgr::TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len)
{
	return TransferToActor(sActorId, tActorId, data, len, NULL, 0);
}

bool LianfuMgr::TransferToActor(ActorId sActorId, ActorId tActorId, DataPacketReader* packet)
{
	if (!packet) return false;
	return TransferToActor(sActorId, tActorId, packet->getMemoryPtr(), packet->getLength());
}

bool LianfuMgr::TransferToServer(ActorId sActorId, int sid, const char* data, size_t len, const void* extraData, size_t extraSize)
{
	if (!IsLianfu()) return false;

	//必须要有消息头(sysid, pid)
	if (!data || len < 2) return false;

	DataPacket dp(transfer_buf_, sizeof(transfer_buf_));
	dp << (int)dtServerDeal;
	dp << (int)sid;
	dp << (ActorId)sActorId;
	dp.writeBuf(data, len);

	if (extraData && extraSize > 0)
	{
		dp.writeBuf(extraData, extraSize);
	}

	static GameServer* gs = ServerInstance();
	if (gs->IsCommonSrv()) // 普通服发送到连服服务器,再由连服服务器发送到对应服务器
	{
		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), (size_t)dp.getLength(),
			InterSrvComm::GameWorldProto::gpTtData, lianfu_sid_, CROSSSERVER_LIANFU);
	}
	else if (gs->IsLianFuSrv()) // 连服服务器发送到对应服务器
	{
		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), (size_t)dp.getLength(),
			InterSrvComm::GameWorldProto::gpTtData, sid, CROSSSERVER_LIANFU);
	}

	return true;
}


bool LianfuMgr::TransferToServer(ActorId sActorId, int sid, const char* data, size_t len)
{
	return TransferToServer(sActorId, sid, data, len, NULL, 0);
}

bool LianfuMgr::TransferToServer(ActorId sActorId, int sid, DataPacketReader* packet)
{
	if (!packet) return false;

	return TransferToServer(sActorId, sid, packet->getMemoryPtr(), packet->getLength());
}

bool LianfuMgr::SendToActor(ActorId actorId, const char* data, size_t len, Actor* actor /* = NULL */)
{
	if (!data) return false;

	ActorIdPacket AP;
	DataPacket& dp = AP.AllocIdPacket(actorId, actor);
	dp.writeBuf(data, len);
	AP.flush();

	return true;
}

bool LianfuMgr::SendToActor(ActorId actorId, DataPacketReader* packet, Actor* actor /* = NULL */)
{
	if (!packet) return false;

	return SendToActor(actorId, packet->getMemoryPtr(), packet->getLength(), actor);
}

