#include "StdAfx.h"
#include "db_session.h"
#include "db/friend_data.h"
using namespace InterSrvComm::DbServerProto;


void DBSession::LoadFriends(DataPacketReader& inPacket)
{
	ActorId actorid;
	inPacket >> actorid;


	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadFriends));
	retPack << actorid;

	int err = sql_->Query(loadfriends, actorid);

	if (!err)
	{
		retPack << (uint8_t) err;
		MYSQL_ROW row = sql_->CurrentRow();
		int count = sql_->GetRowCount();
		retPack << (int)count;
		int val = 0;
		FriendInfo data;

		while (row)
		{
			memset(&data, 0, sizeof(data));
			sscanf(row[0], "%d", &val);
			data.actor_id_ = val;

			sscanf(row[1], "%d", &val);
			data.f_type_ = (uint8_t)val;

			sscanf(row[2], "%d", &val);
			data.add_friend_time_ = val;

			sscanf(row[3], "%d", &val);
			data.last_contact_time_ = val;

			retPack << data;

			row = sql_->NextRow();
		}

		sql_->ResetQuery(); 
	}
	else
	{
		retPack << (uint8_t) err;
	}

	flushProtoPacket(retPack);
}

void DBSession::UpdateFriend(DataPacketReader& inPacket)
{
	ActorId actorid, friendid;
	uint8_t ftype;
	int32_t addfriendtime;
	int32_t lastcontact;
	inPacket >> actorid >> friendid >> ftype >> addfriendtime >> lastcontact;

	int err = sql_->Exec(updatefriends, actorid, friendid, ftype, addfriendtime, lastcontact);

	if (!err)
	{
		sql_->ResetQuery();
	}
	
	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcUpdateFriend));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

void DBSession::DelFriend(DataPacketReader& inPacket)
{
	ActorId actorid, friendid;
	int friendType;

	inPacket >> actorid >> friendid >> friendType;

	int err = sql_->Exec(delfriend, actorid, friendid, friendType);

	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcDelFriend));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

//读取私聊数据
void DBSession::LoadPrivateChats(DataPacketReader & inPacket)
{
	ActorId Actorid;
	inPacket >> Actorid;

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadPrivateChat));
	retPack << Actorid;

	int err = sql_->Query(LoadPrivateChat, Actorid);

	if (!err)
	{
		retPack << (uint8_t)err;
		MYSQL_ROW row = sql_->CurrentRow();
		int count = sql_->GetRowCount();
		retPack << (int)count;
		int val = 0;

		const char* TestContent;

		while (row)
		{
			sscanf(row[1], "%d", &val);
			retPack << val;

			sscanf(row[2], "%d", &val);
			retPack << val;

			TestContent = row[3];
			retPack << TestContent;

			sscanf(row[4], "%d", &val);
			retPack << val;

			row = sql_->NextRow();
		}

		sql_->ResetQuery();
	}
	else
	{
		retPack << (uint8_t)err;
	}

	flushProtoPacket(retPack);
}

//新增聊天记录
void DBSession::AddPrivateChats(DataPacketReader & inPacket)
{
	int actorid = 0;
	int friendid = 0;
	int chat_tiem = 0;
	const char* chat_content;
	int isSelf = 0;

	inPacket >> actorid >> friendid >> chat_tiem >> chat_content >> isSelf;

	int err = sql_->Exec(AddPrivateChat, actorid, friendid, chat_tiem, chat_content, isSelf);

	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcAddPrivateChat));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

//删除聊天记录
void DBSession::DelPrivateChats(DataPacketReader & inPacket)
{
	int actorid = 0;
	int friendid = 0;
	int chat_time = 0;

	inPacket >> actorid >> friendid >> chat_time;

	int err = sql_->Exec(DelPrivateChat, actorid, friendid, chat_time);

	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcDelPrivateChat));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

void DBSession::BachDelPrivateChats(DataPacketReader & inPacket)
{
	ActorId actorid, friendid;

	inPacket >> actorid >> friendid;

	int err = sql_->Exec(BatchDelPrivateChat, actorid, friendid);

	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcBatchDelPrivateChat));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

