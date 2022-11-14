#include "StdAfx.h"
#include <string>
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;


void DBSession::LoadMsgList(DataPacketReader& inPacket)
{
	ActorId nActorid = 0;
	int64_t nMsgId = 0;
	inPacket >> nActorid;
	inPacket >> nMsgId;
	LoadMsgListFromId(nActorid, nMsgId);
}

void DBSession::LoadMsgListFromId(ActorId aid, int64_t msgid)
{
	//if (IsBattleSrv()) return;

	DataPacket& pack = allocProtoPacket(MAKEINT16(siActor, dcLoadMsg));
	pack << (ActorId)aid;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		pack << (uint8_t)reDbErr;
	}
	else
	{
		int err = sql_->Query(loadcharmsglist, aid, (long long int)msgid);

		if (!err)
		{
			pack << (uint8_t)reSucc;
			MYSQL_ROW row = sql_->CurrentRow();
			int count = sql_->GetRowCount();
			unsigned long* len = sql_->GetFieldsLength(); 

			pack << count;

			while (row)
			{

				int64_t id = StrToInt64(row[0]);

				pack << (int64_t)id;

				if (row[1] && len)
				{
					size_t lLong = (len[1]);
					pack << (int)lLong;

					if (lLong > 0) pack.writeBuf(row[1], lLong);
				}

				row = sql_->NextRow();

				len = sql_->GetFieldsLength();
			}

			sql_->ResetQuery();
		}
		else
		{
			pack << (uint8_t)reDbErr;
		}

	}

	flushProtoPacket(pack);
}

void DBSession::DeleteMsg(DataPacketReader& inPacket)
{
	//
	int64_t msgid = 0;
	ActorId nActorId = 0;
	inPacket >> nActorId;
	inPacket >> msgid;

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcDeleteMsg));
	retPack << nActorId;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		retPack << (uint8_t)reDbErr;
		retPack << msgid;//如果失败了，要告诉逻辑服务器那条失败了
	}
	else
	{
		int nError = sql_->Exec(szSQLSP_DeleteCharMsg, nActorId, (long long int)msgid);

		if (!nError)
		{
			sql_->ResetQuery();
			retPack << (uint8_t)reSucc;
			retPack << msgid;//如果失败了，要告诉逻辑服务器那条失败了
		}
		else
		{
			retPack << (uint8_t)reDbErr;
			retPack << msgid;//如果失败了，要告诉逻辑服务器那条失败了
		}

	}

	flushProtoPacket(retPack);
}

void DBSession::AddMsg(DataPacketReader& reader)
{
	ActorId aid = 0, srcid = 0;
	int serverid = 0;
	const char* actorname = NULL;
	const char* account = NULL;

	reader >> aid;
	reader >> srcid;

	reader >> serverid;

	reader >> actorname;
	reader >> account;

	DataPacket& pack = allocProtoPacket(MAKEINT16(siMsg, dcAddMsg));
	pack << aid;
	pack << srcid;
	pack.writeString(actorname);
	pack.writeString(account);

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		pack << (uint8_t)reDbErr;
	}
	else
	{
		char* ptr = huge_buf_;

		ptr += sprintf(ptr, addcharmsg, aid, serverid, strlen(actorname) > 0 ? actorname : "''", strlen(account) > 0 ? account : "''");
		ptr[0] = '"';
		ptr += 1;
		ptr += mysql_escape_string(ptr, reader.getOffsetPtr(), (unsigned long) reader.getAvaliableLength());
		ptr[0] = '"';
		ptr[1] = ')';
		ptr += 2;
		ptr[0] = 0;

		assert((size_t)(ptr - huge_buf_) <= HUNGSIZE);
		int err = sql_->RealQuery(huge_buf_, ptr - huge_buf_);

		if (!err)
		{
			pack << (uint8_t)reSucc;
			MYSQL_ROW row = sql_->CurrentRow();

			if (row)
			{
				int64_t Msgid = StrToInt64(row[0]);
				pack << (int64_t)Msgid;
			}

			sql_->ResetQuery();
		}
		else
		{
			pack << (uint8_t)reDbErr;
		}
	}

	flushProtoPacket(pack);
}

void DBSession::SaveChat(DataPacketReader& reader)
{
	ActorId aid = 0;
	int type = 0;
	int msgid = 0;
	int guildid = 0;
	int server = 0;
	const char* actorname = NULL;
	const char* account = NULL;
	const char* msg = NULL;

	reader >> aid;
	reader >> type;
	reader >> msgid;
	reader >> guildid;
	reader >> server;
	reader >> actorname;
	reader >> account;
	reader >> msg;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		return;
	}
	else
	{
		int err = sql_->Exec(addchatmonitoring, aid, type, msgid,guildid, actorname, account, msg, time(nullptr), server);
		if (!err)
		{
			sql_->ResetQuery();
		}
	}
}