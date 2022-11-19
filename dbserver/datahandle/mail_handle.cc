#include "StdAfx.h"
#include "db/mail_data.h"


using namespace InterSrvComm::DbServerProto;


bool DBSession::SaveMailData(DataPacketReader& inPacket, SQLConnection& sql) {
	ActorId actor_id = 0;
	inPacket >> actor_id;

	if (!sql.Connected())
	{
		OutputMsg(rmError, "on save mail .db not connected");
		return false;
	}

	int err = reSucc;
	err = sql.Exec(sql_cleanmail, actor_id);
	if (!err) {
		sql.ResetQuery(); //函数调用里没有重置数据的
	} else {
		OutputMsg(rmError, "on save mail .db not connected");
		return false;
	}

	int mail_count = 0;
	MailData data;
	inPacket >> mail_count; //取邮件的数量

	strcpy(huge_buf_s, sql_savemail);
	//const int MaxMailSize = sizeof(MailData)* 200;
	char databuf[4096];
	char fieldbuf[2048];
	MailData mail_data;
	STATIC_ASSERT(sizeof(ItemData) < 2048);
//#define AddString(v) sprintf(fieldbuf, ",\"");strcat(fieldbuf, v);strcat(fieldbuf,"\"");strcat(databuf, fieldbuf)

	for (int i = 0; i < mail_count; ++i)
	{
		inPacket >> mail_data;

		//"(uid,actorid,bag_type,id, count, attrs)"
		strcpy(databuf, "(");
		FirstInt(mail_data.uid);
		AddInt(actor_id);
		AddInt(mail_data.readStatus);
		AddInt(mail_data.sendtime);
		AddData(mail_data.head, strlen(mail_data.head)+1);
		AddData(mail_data.context, strlen(mail_data.context)+1);
		AddData(mail_data.award_data, sizeof(mail_data.award_data));
		AddInt(mail_data.awardStatus);

		strcat(databuf, ")");
		if (i > 0)
			strcat(huge_buf_s, ",");
		strcat(huge_buf_s, databuf);
	}

	err = sql.RealExec(huge_buf_s, strlen(huge_buf_s));
	if (!err) {
		sql.ResetQuery();
		return true;
	}
	OutputMsg(rmError, "sql_save items failed; %s", huge_buf_s);
	return false;
}

void DBSession::QueryMailData(ActorId actorid)
{
	client_mgr_->LockCache();
	auto *pack = client_mgr_->GetCache()->GetReadableData(actorid, DBCacheType_Mail);
	if (pack != nullptr)
	{
		size_t pos = pack->getPosition();
		pack->setPosition(sizeof(ActorId));

		DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadMail));
		retPack << actorid << (uint8_t)reSucc;

		retPack.writeBuf(pack->getOffsetPtr(), pack->getAvaliableLength());
		flushProtoPacket(retPack);

		pack->setPosition(pos);

		client_mgr_->UnLockCache();
		return;
	}
	client_mgr_->UnLockCache();

	int errId = reSucc;
	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		errId = reDbErr;
	}
	else
	{
		errId = sql_->Query(sql_loadmail, actorid);

		if (!errId)
		{
			DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadMail));
			retPack << actorid << (uint8_t)reSucc;
			size_t headlen = retPack.getPosition();

			BEGIN_GET_ROW();
			retPack << rowCount;

			int i = 0;
			MailData mail_data;
			while (pRow)
			{
				memset(&mail_data, 0, sizeof(MailData));
				GetIntRow(0, mail_data.uid);
				//第一行是玩家id，邮件结构体里面不需要，就不读了，直接跳到第二行
				GetIntRow(2, mail_data.readStatus);
				GetIntRow(3, mail_data.sendtime);
				GetDataRow(4, mail_data.head);
				GetDataRow(5, mail_data.context);
				GetDataRow(6, mail_data.award_data);
				GetIntRow(7, mail_data.awardStatus);
				retPack << mail_data;

				pRow = sql_->NextRow();
				GET_NEXT_FIELD_LENGTH();
				++i;
			}

			flushProtoPacket(retPack);
			sql_->ResetQuery();

			client_mgr_->LockCache();
			DataPacket *pack = client_mgr_->GetCache()->UpdateCache(actorid, DBCacheType_Mail,
				NULL, 0, false);
			pack->setPosition(0);
			(*pack) << actorid;
			pack->writeBuf(retPack.getPositionPtr(0) + headlen, retPack.getLength() - headlen);
			pack->setPosition(0);
			client_mgr_->UnLockCache();

			return;
		}
		else
		{
			OutputMsg(rmError, ("%s load mail data failed,%d"), __FUNCTION__, actorid);
			errId = reDbErr;
		}
	}

	if (errId != reSucc)
	{
		OutputMsg(rmError, ("%s load mail data failed,%d"), __FUNCTION__, actorid);
		DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadMail));
		retPack << actorid << (uint8_t)errId;
		flushProtoPacket(retPack);
	}

	return;
}
