#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace InterSrvComm::DbServerProto;

void DBSession::AddSysVar(DataPacketReader& reader)
{
	int err = reDbErr;

	if (sql_->Connected())
	{
		ActorId id;
		reader >> id;
		ACTORNAME name;
		reader.readString(name, sizeof(name));
		int sysId;
		reader >> sysId;

		size_t size = reader.getAvaliableLength();
		char* ptr = huge_buf_;
		ptr += SNPRINTFA(ptr, HUNGSIZE, "call addsysvar(%d, \"%s\", %d, \"", id, name, sysId);
		ptr += mysql_escape_string(ptr, reader.getOffsetPtr(), (unsigned long)size);
		*ptr = 0;
		strcat(ptr, "\")");
		ptr += 2;
		assert((size_t)(ptr - huge_buf_) <= HUNGSIZE);

		err = sql_->RealExec(huge_buf_, ptr - huge_buf_);

		if (err == reSucc)
			sql_->ResetQuery();
	}

	if (err != reSucc)
		OutputMsg(rmError, "update sysvar err occur");
}

void DBSession::LoadSysVar(DataPacketReader& reader)
{
	int err = reSucc;

	if (!sql_->Connected())
	{
		err = reDbErr;
	}
	else
	{
		err = sql_->Query("call loadsysvar()");

		if (!err)
		{
			int cnt = sql_->GetRowCount();

			DataPacket& retPack = allocProtoPacket(MAKEINT16(siCommon, dcSysVarCount));
			retPack << (int)reSucc
				<< (int)cnt;
			flushProtoPacket(retPack);

			if (cnt > 0)
			{
				MYSQL_ROW row = sql_->CurrentRow();

				int index = 0;
				int val;
				ACTORNAME name;

				const size_t szfixed = sizeof(ActorId) + sizeof(name) + sizeof(int);

				while (index < cnt)
				{
					int left = cnt - index;
					int cpt = __min(left, 50);

					DataPacket& retPack = allocProtoPacket(MAKEINT16(siCommon, dcLoadSysVar));
					retPack << (int)reSucc;
					int pos = (int)retPack.getPosition();
					retPack << (int)cpt;

					size_t totalLength = 0;
					for (int i = 0; i < cpt; ++i)
					{
						unsigned long* pLength = sql_->GetFieldsLength();
						size_t rowLength = pLength ? (szfixed + pLength[3]) : 0;
						if ((totalLength + rowLength) > 0xffff)
						{
							// 如果数据包超过长度0ffff
							int *ptr = (int*)retPack.getPositionPtr(pos);
							*ptr = i;
							break;
						}
						totalLength += rowLength;

						sscanf(row[0], "%d", &val);
						retPack << (ActorId)val;
						_STRNCPY_A(name, row[1] ? row[1] : "");
						retPack.writeString(name);
						sscanf(row[2], "%d", &val);
						retPack << (int)val;
						val = (pLength ? pLength[3] : 0);
						retPack << (int)val;
						retPack.writeBuf((const void*)(row[3] ? row[3] : ""), val);

						row = sql_->NextRow();
						++index;
					}

					flushProtoPacket(retPack);
				}
			}

			sql_->ResetQuery();
		}
	}

	if (err != reSucc)
	{
		OutputMsg(rmError, "loadSysVar error");
		DataPacket& retPack = allocProtoPacket(MAKEINT16(siCommon, dcLoadSysVar));
		retPack << (int)err;
		flushProtoPacket(retPack);
	}
}

void DBSession::UpdateSysVar(DataPacketReader& reader)
{
	int err = reDbErr;

	if (sql_->Connected())
	{
		ActorId id;
		reader >> id;
		int sysId;
		reader >> sysId;

		size_t size = reader.getAvaliableLength();
		char* ptr = huge_buf_;
		ptr += SNPRINTFA(ptr, HUNGSIZE, "call updatesysvar(%d, %d, \"", id, sysId);
		ptr += mysql_escape_string(ptr, reader.getOffsetPtr(), (unsigned long)size);
		*ptr = 0;
		
		strcat(ptr, "\")");
		ptr += 2;
		assert((size_t)(ptr - huge_buf_) <= HUNGSIZE);

		err = sql_->RealExec(huge_buf_, ptr - huge_buf_);

		if (err == reSucc)
			sql_->ResetQuery();
	}

	if (err != reSucc)
		OutputMsg(rmError, "update sysvar err occur");
}

