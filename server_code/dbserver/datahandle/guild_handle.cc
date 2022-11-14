#include "StdAfx.h"
#include "../db_proto.h"

void DBSession::AddGuild(DataPacketReader& inPacket)
{
	int gid;
	inPacket >> gid;
	const char* name;
	inPacket >> name;

	DataPacket& out = allocProtoPacket(MAKEINT16(siActor, dcAddGuild));

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		out << (uint8_t)reDbErr;
	}
	else
	{
		int err = sql_->Exec(createguild, gid, name, getClientServerIndex());

		if (!err)
		{
			sql_->ResetQuery();
			out << (uint8_t)reSucc;
		}
		else
		{
			out << (uint8_t)reDbErr;
		}
	}

	flushProtoPacket(out);
}

void DBSession::DeleteMember(DataPacketReader& inPacket)
{
	
	int nActorid = 0;
	int nOperActor = 0;//这个是操作的帮主的id
	//这个是脱离帮派的角色id
	inPacket >> nActorid;
	inPacket >> nOperActor;

	DataPacket& out = allocProtoPacket(MAKEINT16(siActor, dcDeleteMember));
	out << nOperActor;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		out << (uint8_t)reDbErr;
	}
	else
	{
		int nError = sql_->Exec(delguildmember, nActorid);

		if (!nError)
		{
			sql_->ResetQuery();
			out << (uint8_t)reSucc;
		}
		else
		{
			out << (uint8_t)reDbErr;
		}
	}

	flushProtoPacket(out);

	//// 同时也要在缓存中清除数据
	//client_mgr_->LockCache();
	//// 删除玩家的guildid数据，这个也是存储过程delguildmember做的事情
	//ActorBasicData* actorData = client_mgr_->GetCache()->GetActorBasicData(nActorid);
	//if (actorData)
	//{
	//	actorData->guild_id_ = 0;
	//}
	//client_mgr_->UnLockCache();
}

bool DBSession::SaveActorGuild(DataPacketReader& inPacket, SQLConnection& sql)
{
	int gid = 0;
	ActorId aid = 0;
	int pos = 0;
	int	total_contrib = 0;
	int today_contrib = 0;
	inPacket >> aid;
	inPacket >> gid;
	inPacket >> total_contrib;
	inPacket >> today_contrib;
	inPacket >> pos;

	OutputMsg(rmTip, "SaveActorGuild: %d,%d", aid, pos);

	//数据库连接是否就绪
	if (sql.Connected()) {
		int err = sql.Exec(updateguildmember, gid, aid, total_contrib, today_contrib, pos);
		if (!err) {
			sql.ResetQuery();
			return true;
		}
	}
	return false;
}

void DBSession::AddGuildMember(DataPacketReader& inPacket)
{
	int gid = 0;
	ActorId aid = 0;
	int pos = 0;
	inPacket >> gid;
	inPacket >> aid;
	inPacket >> pos;

	OutputMsg(rmTip, "###### AddGuildMember : %d, %d", aid, pos);

	DataPacket& out = allocProtoPacket(MAKEINT16(siActor, dcAddMember));
	out << aid;

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		out << (uint8_t)reDbErr;
		out << gid;
	}
	else
	{
		int nError = sql_->Exec(addguildmember, gid, aid, pos);

		if (!nError)
		{
			sql_->ResetQuery();
			out << (uint8_t)reSucc;
			out << gid;
		}
		else
		{
			out << (uint8_t)reDbErr;
			out << gid;
		}
	}

	flushProtoPacket(out);
}

void DBSession::SaveGuild(DataPacketReader& inPacket)
{
	int gid = 0, changeNameCount = 0;
	const char* name;
	inPacket >> gid;
	inPacket >> changeNameCount;
	inPacket >> name;

	DataPacket& out = allocProtoPacket(MAKEINT16(siGuild, dcSaveGuild));

	size_t pos = out.getPosition();
	out << (uint8_t)reSucc;
	out << (int)gid;
	
	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		uint8_t* ret = (uint8_t*)(out.getPositionPtr(pos));
		*ret = reDbErr;
	}
	else
	{
		int err = sql_->Exec(updateguildbasedata, gid, changeNameCount, name);

		if (!err)
		{
			sql_->ResetQuery();
		}
		else
		{
			uint8_t* ret = (uint8_t*)(out.getPositionPtr(pos));
			*ret = reDbErr;
		}
	}

	flushProtoPacket(out);
}

void DBSession::SaveGuildVar(DataPacketReader& inPacket)
{
	int gid = 0, var_id = 0;
	inPacket >> gid >> var_id;

	char* ptr = huge_buf_;
	ptr += SNPRINTFA(ptr, HUNGSIZE, updateguildvar, gid, var_id);

	int var_len = 0;
	inPacket >> var_len;
	if (var_len > 0)
	{
		ptr += mysql_escape_string(ptr, inPacket.getOffsetPtr(), (unsigned long)var_len);
		inPacket.adjustOffset(var_len);
	}
	strcat(ptr, "\")");
	ptr += 2;
	assert((size_t)(ptr - huge_buf_) <= HUNGSIZE);

	if (!sql_->Connected())
	{
		return;
	}
	else
	{
		int err = sql_->RealExec(huge_buf_, ptr - huge_buf_);

		if (!err)
		{
			sql_->ResetQuery();
		}
	}
}

void DBSession::SaveGuildChat(DataPacketReader& inPacket)
{
	int guildId, count;
	inPacket >> guildId >> count;

	if (!sql_->Connected())
	{
		OutputMsg(rmError, "on save guild chat .db not connected");
		return;
	}

	int err = sql_->Exec(sql_cleanguildchat, guildId);

	if (!err)
		sql_->ResetQuery();
	else {
		OutputMsg(rmError, "clean guild chat error %d", err);
		return;
	}

	if (count > 0)
	{
		uint8_t type;
		int time;
		ActorId actorId;
		char content[512];

		strcpy(huge_buf_s, sql_saveguildchat);
		char databuf[1024];

		for (int i = 0; i < count; i++)
		{
			if (i > 0)
				strcat(huge_buf_s, ",");

			inPacket >> type;
			inPacket >> time;
			inPacket >> actorId;
			inPacket.readString(content, ArrayCount(content));

			char* ptr = databuf;
			ptr += SNPRINTFA(databuf, ArrayCount(databuf), "(%d,%d,%d,%d,\"", guildId, type, time, actorId);
			ptr += mysql_escape_string(ptr, content, (unsigned long)strlen(content));
			*ptr = 0;
			strcat(ptr, "\")");
			strcat(huge_buf_s, databuf);
		}

		err = sql_->RealExec(huge_buf_s, strlen(huge_buf_s));
		if (!err) sql_->ResetQuery();
		else {
			OutputMsg(rmError, "#!! sql_save guild chat failed;");
		}
	}
}

void DBSession::SaveGuildStore(DataPacketReader& inPacket)
{
	int guildId, count;
	inPacket >> guildId >> count;

	if (!sql_->Connected())
	{
		OutputMsg(rmError, "on save guild store .db not connected");
		return;
	}

	if (count > 0)
	{
		UInt32 time;
		ActorId actor_id;
		Int32 item_id;

		strcpy(huge_buf_s, sql_saveguildstorelog);
		char databuf[1024];

		for (int i = 0; i < count; i++)
		{
			if (i > 0)
				strcat(huge_buf_s, ",");

			inPacket >> time;
			inPacket >> actor_id;
			inPacket >> item_id;

			SNPRINTFA(databuf, ArrayCount(databuf), "(%d,%d,%d,%d)", time, guildId, actor_id, item_id);
			strcat(huge_buf_s, databuf);
		}

		int err = sql_->RealExec(huge_buf_s, strlen(huge_buf_s));
		if (!err)
		{
			sql_->ResetQuery();
		}
		else 
		{
			OutputMsg(rmError, "#!! sql_save guild store failed;");
		}
	}
}

void DBSession::DeleteGuild(DataPacketReader& inPacket)
{
	int gid = 0;
	inPacket >> gid;

	DataPacket& out = allocProtoPacket(MAKEINT16(siGuild, dcDeleteGuild));

	//数据库连接是否就绪
	if (!sql_->Connected())
	{
		out << (uint8_t)reDbErr;
	}
	else
	{
		//向数据库查询进度任务数据
		int err = sql_->Exec(deleteguild, gid);

		if (!err)
		{
			sql_->ResetQuery();
			out << (uint8_t)reSucc;
		}
		else
		{
			out << (uint8_t)reDbErr;
			OutputMsg(rmError, ("delete Guild error!id=%d"),	gid);
		}
	}

	out << gid;
	flushProtoPacket(out);

	//// 同时也要在缓存中清除数据
	//client_mgr_->LockCache();
	//// 删除玩家的guildid数据，这个也是存储过程deleteguild做的事情
	//client_mgr_->GetCache()->DeleteGuild(gid);
	//client_mgr_->UnLockCache();
}

void DBSession::AddGuildLog(DataPacketReader& inPacket)
{
	int err = reSucc;
	if (!sql_->Connected())
	{
		err = reDbErr;
	}
	else
	{
		int iguild, itime, itype, iparam1, iparam2, iparam3;
		inPacket >> iguild >> itime >> itype >> iparam1 >> iparam2 >> iparam3;

		ACTORNAME sname1, sname2;
		inPacket.readString(sname1, ArrayCount(sname1));
		inPacket.readString(sname2, ArrayCount(sname2));

		err = sql_->Exec(addguildlog, iguild, itime, itype, iparam1, iparam2, iparam3, sname1, sname2);
		if (!err)
		{
			sql_->ResetQuery();
		}
	}
}

void DBSession::DeleteGuildLog(DataPacketReader& inPacket)
{
	int err = reSucc;
	if (!sql_->Connected())
	{
		err = reDbErr;
	}
	else
	{
		int itime, guildId;
		inPacket >> guildId >> itime;

		err = sql_->Exec(delguildlog, guildId, itime);
		if (!err)
		{
			sql_->ResetQuery();
		}
	}
}

