#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
using namespace InterSrvComm::DbServerProto;

/*
void DBSession::QueryActorVariableData(ActorId actorId, const char* fieldName, int entityId)
{
	int err = reSucc;

	if (!sql_->Connected())
	{
		err = reDbErr;
	}
	else
	{
		err = sql_->Query(sql_loadvariable, fieldName, actorId);

		if (!err)
		{
			DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, entityId));
			retPack << actorId << (uint8_t) err;

			MYSQL_ROW row = sql_->CurrentRow();
			unsigned long* len = sql_->GetFieldsLength(); //获取数据的长度

			if (row && len && row[0])
			{
				size_t lLong = (len[0]);
				retPack.writeBuf((const void*)(row[0]), lLong);
			}

			flushProtoPacket(retPack);
			sql_->ResetQuery(); //函数调用里没有重置数据的
			return;
		}

	}

	if (err != reSucc)
	{
		DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, entityId));
		retPack << actorId << (uint8_t) err;
		flushProtoPacket(retPack);
	}
}
*/

bool DBSession::QueryActorVariableDataFromCache(ActorId actorId, int type, int cmd)
{
	client_mgr_->LockCache();

	DataPacket *pack = client_mgr_->GetCache()->GetReadableData(actorId, type);
	if (pack != NULL)
	{
		size_t pos = pack->getPosition();
		pack->setPosition(sizeof(ActorId));
	
		if (cmd == dcLoadVar || cmd == dcLoadCsWarVar) //分包脚本变量
		{
			if (pack->getAvaliableLength() == 0)
			{
				DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, cmd));
				retPack << actorId << (uint8_t)reSucc  << (uint32_t)0 << (uint32_t)0 << (uint32_t)0;
				flushProtoPacket(retPack);
			}
			else
			{
				for (uint32_t i = 0; i < pack->getAvaliableLength(); i += PACK_LEN)
				{
					DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, cmd));
					retPack << actorId << (uint8_t)reSucc  << (uint32_t)i;
					if ((i + PACK_LEN) > pack->getAvaliableLength())
					{
						retPack << (uint32_t)pack->getAvaliableLength() - i;
					}
					else
					{
						retPack << (uint32_t)PACK_LEN;
					}
					retPack << (uint32_t)pack->getAvaliableLength();
					if ((i + PACK_LEN) > pack->getAvaliableLength())
					{
						retPack.writeBuf(pack->getOffsetPtr() + i, pack->getAvaliableLength() - i);
					}
					else
					{
						retPack.writeBuf(pack->getOffsetPtr() + i, PACK_LEN);
					}

					flushProtoPacket(retPack);

				}
			}
		}
		else
		{
			DataPacket &retPack = allocProtoPacket(MAKEINT16(siActor, cmd));
			retPack << actorId<< (uint8_t)reSucc;
			if (pack->getAvaliableLength() < 65535)
				retPack.writeBuf(pack->getOffsetPtr(), pack->getAvaliableLength());
			flushProtoPacket(retPack);

			pack->setPosition(pos);
		}
	

		client_mgr_->UnLockCache();
		return true;
	}

	client_mgr_->UnLockCache();
	return false;
}

bool DBSession::SaveActorVariableData(DataPacketReader& packet, const char* fieldName, SQLConnection& sql, int entityId) {
	ActorId aid = 0;
	packet >> aid;
	size_t size = packet.getAvaliableLength();

	if (size > 0) {
		char* ptr = huge_buf_s;
		ptr += SNPRINTFA(huge_buf_s, HUNGSIZE, sql_updatevariable, fieldName);
		ptr[0] = '"';
		ptr++;
		ptr += mysql_escape_string(ptr, packet.getOffsetPtr(), (unsigned long)size);
		ptr[0] = '"';
		ptr++;
		ptr[0] = '\0';

		size_t rest = HUNGSIZE - (ptr - huge_buf_s);
		ptr += SNPRINTFA(ptr, (int)rest, " where actorid=%d", aid);

		assert((size_t)(ptr - huge_buf_s) <= HUNGSIZE);

		if (!sql.RealExec(huge_buf_s, ptr - huge_buf_s)) {
			sql.ResetQuery();
			return true;
		}
	}
	return false;
}


void DBSession::QueryActorVariableList(ActorId actorId, Vector<VariableDataFlag>& fieldList)
{
	huge_buf_[0] = 0;
	for (int i = 0; i < fieldList.count(); ++i)
	{
		VariableDataFlag& data = fieldList[i];
		_STRNCAT_S(huge_buf_, data.fieldName_, HUNGSIZE);
		if (i != (fieldList.count() - 1))
			_STRNCAT_S(huge_buf_, ",", HUNGSIZE);
	}

	int err = sql_->Query(sql_loadvariable, huge_buf_, actorId);

	if (!err)
	{
		MYSQL_ROW row = sql_->CurrentRow();
		unsigned long* len = sql_->GetFieldsLength(); //获取数据的长度

		for (int i = 0; i < fieldList.count(); ++i)
		{
			VariableDataFlag& data = fieldList[i];
			client_mgr_->LockCache();
			DataPacket* pack = 
				client_mgr_->GetCache()->UpdateCache(actorId, data.cache_type_, NULL, 0, false);
			if (pack)
			{
				pack->setPosition(0);
				(*pack) << (ActorId)actorId;

				if (row && len && row[i])
				{
					size_t lLong = (len[i]);
					pack->writeBuf((const void*)(row[i]), lLong);
				}
				
				pack->setPosition(0);
			}

			client_mgr_->UnLockCache();
			QueryActorVariableDataFromCache(actorId, data.cache_type_, data.protoId_);
		}

		sql_->ResetQuery(); //函数调用里没有重置数据的
	}
	else
	{
		for (int i = 0; i < fieldList.count(); ++i)
		{
			VariableDataFlag& data = fieldList[i];
			DataPacket& retPack = allocProtoPacket(MAKEINT16(siActor, data.protoId_));
			retPack << actorId << (uint8_t) err;
			flushProtoPacket(retPack);
		}
	}
}
