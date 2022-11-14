#include "StdAfx.h"
#include "db_session.h"
#include "db/role_data.h"
#include "db_pvm_cache.h"

using namespace InterSrvComm::DbServerProto;

void DBSession::QueryRoleData(ActorId actorid)
{
	client_mgr_->LockCache();

	auto *pack = client_mgr_->GetCache()->GetReadableData(actorid, DBCacheType_RoleData);
	if (pack != nullptr)
	{
		size_t pos = pack->getPosition();
		pack->setPosition(sizeof(ActorId));

		DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadRole));
		retPack << actorid << (uint8_t)reSucc;
#ifdef LYDEBUG
		RoleDatas role;
		memcpy(&role, pack->getOffsetPtr(), pack->getAvaliableLength());
		OutputMsg(rmTip, "--------------DB on queryRole: count:%d", role.role_count);
#endif
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
		errId = sql_->Query(sql_loadrole, actorid);

		if (!errId)
		{
			DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadRole));
			retPack << actorid << (uint8_t)reSucc;

			BEGIN_GET_ROW();
			RoleDatas roleDatas;
			memset(&roleDatas, 0, sizeof(RoleDatas));
			roleDatas.role_count = rowCount;

			int i = 0;
			while (pRow)
			{
				GetIntRow(1, i);
				if (i < 0 || i >= 3)
				{
					OutputMsg(rmError, "get role data error index:%d", i);
					break;
				}

				RoleData &data = roleDatas.roles[i];
				data.id = i;
				GetIntRow(2, data.job);
				GetIntRow(3, data.sex);
				GetDoubleRow(4, data.power);
				GetDataRow(5, data.skills);
				GetDataRow(6, data.wings);
				GetDataRow(8, data.equips_data);
				GetDataRow(9, data.ex_rings);
				GetDataRow(10, data.jingmai_data);
				GetDataRow(11, data.loogsoul_data);
				GetDataRow(12, data.fuwen_data);
				GetDataRow(13, data.heirloom);
				GetIntRow(14, data.weapon_soul_id);
				
				pRow = sql_->NextRow();
				GET_NEXT_FIELD_LENGTH();
				++i;
			}

			retPack.writeBuf(&roleDatas, sizeof(RoleDatas));
			flushProtoPacket(retPack);
			OutputMsg(rmTip, "size roledata:%d\n", (int)sizeof(RoleDatas));
			sql_->ResetQuery();

			client_mgr_->LockCache();
			DataPacket *pack = client_mgr_->GetCache()->UpdateCache(actorid, DBCacheType_RoleData, &roleDatas, sizeof(RoleDatas), false);
			pack->setPosition(0);
			(*pack) << actorid;
			pack->writeBuf(&roleDatas, sizeof(RoleDatas));
			pack->setPosition(0);
			client_mgr_->UnLockCache();

			return;
		}
		else
		{
			OutputMsg(rmError, ("%s load role data failed,%d"), __FUNCTION__, actorid);
			errId = reDbErr;
		}
	}

	if (errId != reSucc)
	{
		OutputMsg(rmError, ("%s load role data failed,%d"), __FUNCTION__, actorid);
		DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadRole));
		retPack << actorid << (uint8_t)errId;
		flushProtoPacket(retPack);
	}

	return;
}


bool DBSession::SaveRoleData(DataPacketReader& packet, SQLConnection& sql)
{
	if (packet.getAvaliableLength() != sizeof(int)+sizeof(RoleDatas)) {
		OutputMsg(rmError, ("%s Data size error"), __FUNCTION__);
		return false;
	}

	RoleDatas data;
	ActorId actorid;
	packet >> actorid;
	packet.readBuf(&data, sizeof(RoleDatas));

	int err = sql.Exec(sql_cleanrole, actorid);
	if (!err)
		sql.ResetQuery();
	else {
		OutputMsg(rmError, "#!! sql_cleanrole failed; actorid:%d", actorid);
		return false;
	}

	strcpy(huge_buf_s, sql_saverole);
	char databuf[29005];
	char fieldbuf[9000];
	//STATIC_ASSERT(sizeof(RoleData) < 4096);

	for (int i = 0; i < data.role_count; ++i)
	{
		memset(databuf, 0, sizeof(databuf));
		RoleData &role = data.roles[i];

		//"(x,x,x,x...)"
		strcat(databuf, "(");
		FirstInt(actorid);
		AddInt(role.id);
		AddInt(role.job);
		AddInt(role.sex);
		AddLInt((long long int)(role.power));
		AddData(role.skills, sizeof(SkillsData));
		AddData(role.wings, sizeof(WingsData));
		AddData(role.equips_data, sizeof(EquipsData));
		AddData(role.ex_rings, sizeof(ExRingsData));
		AddData(role.jingmai_data, sizeof(JingMaiData));
		AddData(role.loogsoul_data, sizeof(LoogsoulData));
		AddData(role.fuwen_data, sizeof(FuWenData));
		AddData(role.heirloom, sizeof(role.heirloom));
		AddInt(role.weapon_soul_id);
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
	OutputMsg(rmError, "sql_saveRole failed: %s", huge_buf_s);
	return false;
}


//加载竞技场玩家数据
void DBSession::LoadPVMlayerData(DataPacketReader & inPacket)
{
	ActorId Actorid;
	inPacket >> Actorid;

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadPVMlayer));
	retPack << Actorid;

	int err = sql_->Query(LoadLoadPVMlayer, Actorid);

	if (!err)
	{
		retPack << (uint8_t)err;
		MYSQL_ROW row = sql_->CurrentRow();
		int count = sql_->GetRowCount();
		retPack << (int)count;
		int val = 0;

		while (row)
		{
			sscanf(row[1], "%d", &val);
			retPack << val;

			sscanf(row[2], "%d", &val);
			retPack << val;

			sscanf(row[3], "%d", &val);
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

//保存竞技场玩家数据
void DBSession::SavePVMlayerData(DataPacketReader & inPacket)
{
	int actorid = 0;
	int recovertime = 0;
	int challengecount = 0;
	int buycount = 0;

	inPacket >> actorid >> recovertime >> challengecount >> buycount;

	int err = sql_->Exec(UpdatePVMlayer, actorid, recovertime, challengecount, buycount);

	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcUpdatePVMlayer));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}

void DBSession::UpdateChannengeRecord(DataPacketReader & inPacket)
{
	int actorid = 0;
	int recovertime = 0;
	const char* record_data;

	inPacket >> actorid >> recovertime >> record_data;

	CDBPvmCache::instance()->AddChallengeRecord((int32_t)actorid, (int32_t)recovertime, record_data);
}

//加载玩家挑战记录
void DBSession::LoadPlayerRecord(DataPacketReader& inPacket)
{
	ActorId Actorid;
	inPacket >> Actorid;

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadChallengeRecord));
	retPack << Actorid;

	int err = sql_->Query(LoadChallengeRecord, Actorid);

	if (!err)
	{
		retPack << (uint8_t)err;
		MYSQL_ROW row = sql_->CurrentRow();
		int count = sql_->GetRowCount();
		if (count > 1)
		{
			OutputMsg(rmError, "[DB - Error ] LoadPlayerRecord failed , actorid : %d", Actorid);
			return;
		}
		else if (count <= 0)
		{
			sql_->ResetQuery();
			return;
		}

		const char* TestContent;
		TestContent = row[1];
		retPack << TestContent;

		sql_->ResetQuery();
	}
	else
	{
		retPack << (uint8_t)err;
	}

	flushProtoPacket(retPack);
}

//加载玩家挂机练功数据
void DBSession::LoadPlayerAFKData(DataPacketReader & inPacket)
{
	ActorId Actorid;
	inPacket >> Actorid;

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcLoadAFKData));
	retPack << Actorid;

	int err = sql_->Query(loadplayerafkdata, Actorid);
	if (!err)
	{
		retPack << (uint8_t)err;
		MYSQL_ROW row = sql_->CurrentRow();
		if (row != nullptr)
		{
			int count = sql_->GetRowCount();
			retPack << (int)count;
			int val = 0;

			const char* TestContent = nullptr;
			while (row)
			{
				TestContent = nullptr;
				sscanf(row[0], "%d", &val);
				retPack << val;

				TestContent = row[1];
				retPack << TestContent;

				row = sql_->NextRow();
			}
		}
	}
	else
	{
		retPack << (uint8_t)err;
	}
	sql_->ResetQuery();
	flushProtoPacket(retPack);
}

//保存玩家挂机练功数据
void DBSession::SavePlayerAFKData(DataPacketReader & inPacket)
{
	int actorid = 0;
	int starttime = 0;
	const char * monsterlist = nullptr;

	inPacket >> actorid >> starttime >> monsterlist;

	int err = sql_->Exec(saveplayerafkdata, actorid, starttime, monsterlist);
	if (!err)
	{
		sql_->ResetQuery();
	}

	DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, dcSaveAFKData));
	retPack << (ActorId)actorid << char(err);
	flushProtoPacket(retPack);
}