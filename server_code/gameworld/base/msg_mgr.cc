#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "msg_mgr.h"

using namespace InterSrvComm::DbServerProto;

bool MsgMgr::AddOffMsg(int aid, const char* actorname, const char* account, ActorId srcid,  const char* buf, size_t size)
{
	if (!actorname) actorname = "";

	if (!account) account = "";

	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return false;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siMsg, dcAddMsg));

	pack << (int)aid;
	pack << (int)srcid;//发出消息的角色ID
	pack << (int)(ServerInstance()->GetServerIndex());
	pack.writeString(actorname);
	pack.writeString(account);

	if (buf && size > 0) pack.writeBuf(buf, size);

	db->flushProtoPacket(pack);

	return true;
}

void MsgMgr::OnDbReturnData(int ncmd, DataPacketReader& reader)
{
	switch (ncmd)
	{
	case dcAddMsg:
		{
			OnAddOffMsgDbReturn(ncmd, reader);
		}
		break;

	default:
		break;
	}
}

void MsgMgr::OnAddOffMsgDbReturn(int nCmd, DataPacketReader& reader)
{
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	//const char* err_str = NULL;
	//int nmsg_type = ttTipmsgWindow;

	//int nactor_id = 0;
	//int src_actor_id = 0;
	//const char* actor_name = NULL;
	//const char* account_name = NULL;
	//uint8_t nerr_code = 0;

	//reader >> nactor_id;
	//reader >> src_actor_id;
	//reader >> actor_name;
	//reader >> account_name;
	//reader >> nerr_code;

	//if (nerr_code != reSucc)
	//{
	//	err_str = ("Error!!the msg send to %d fail!");
	//	nmsg_type = ttDialog;
	//	OutputMsg(rmError, err_str, nactor_id);
	//}
	//else
	//{
	//	err_str = ("the msg send to%d ok!");

	//	//如果用户在线，通知其从数据库中读出
	//	Actor* pactor = NULL;

	//	if (nactor_id != 0)
	//	{
	//		pactor = em->GetActorPtrById(nactor_id);
	//	}
	//	else if (actor_name != NULL && actor_name[0] != 0)
	//	{
	//		pactor = em->GetActorPtrByName(actor_name);
	//	}
	//	else
	//	{
	//		pactor = em->GetActorPtrByAccount(account_name);
	//	}

	//	if (pactor != NULL)
	//	{
	//		int64_t nmsg_id = 0;
	//		reader >> nmsg_id;
	//		pactor->GetMsgSystem().ReloadFromDb(nmsg_id);
	//	}
	//}

	////通知发送的原角色(一般是GM）错误消息
	//Actor* psrc_actor = em->GetActorPtrById(src_actor_id);

	//if (psrc_actor)
	//{
	//	psrc_actor->SendTipmsgFormat(err_str, nmsg_type, nactor_id);
	//}
}

void MsgMgr::SaveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
	const char* account, const char* msg)
{
	if (!actorname) actorname = "";

	if (!account) account = "";

	if (!msg) msg = "";

	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siMsg, dcAddChat));

	pack << (int)aid;
	pack << (int)type;
	pack << (int)msgid;
	pack << (int)guild;
	pack << (int)(ServerInstance()->GetServerIndex());
	pack.writeString(actorname);
	pack.writeString(account);
	pack.writeString(msg);

	db->flushProtoPacket(pack);
}