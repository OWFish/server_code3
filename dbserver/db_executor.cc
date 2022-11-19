#include "StdAfx.h"
#include <string>

DBExecutor::PacketFieldFunc DBExecutor::fieldFunc[] =
{
	&DBExecutor::ReadIntField,
	&DBExecutor::ReadDoubleField,
	&DBExecutor::ReadStringField,
	&DBExecutor::ReadInt64Field,
	&DBExecutor::ReadBlobField,
};

DBExecutor::JoinPacketStringFunc DBExecutor::packetFunc[] =
{
	&DBExecutor::ReadPacketInt,
	&DBExecutor::ReadPacketDouble,
	&DBExecutor::ReadPacketString,
	&DBExecutor::ReadPacketInt64,
	&DBExecutor::ReadPacketBlob,
};

bool DBExecutor::HandleExec(DataPacketReader& reader)
{
	int id;
	reader >> id;

	static DBTables* db_tables = DBServer::Instance->getTables();

	DBExec* db_exec = db_tables->GetExec(id);
	if (!db_exec)
	{
		OutputMsg(rmError, "exec id error : %d", id);
		return false;
	}

	switch (db_exec->type_)
	{
	case dbExecQuery:
		HandleQuery(reader, db_exec);
		break;
	case dbExecInsert:
		HandleInsert(reader, db_exec);
		break;
	case dbExecUpdate:
		HandleUpdate(reader, db_exec);
		break;
	case dbExecDelete:
		HandleDelete(reader, db_exec);
		break;
	case dbExecProcedure:
		HandleProcedure(reader, db_exec);
		break;
	default:
		OutputMsg(rmError, "exec type error : %d", db_exec->type_);
		return false;
		break;
	}

	return true;
}

bool DBExecutor::HandleQuery(DataPacketReader& reader, DBExec* exec)
{
	uint8_t sys_id;
	uint8_t cmd_id;
	reader >> sys_id >> cmd_id;

	DBQuery* conf = (DBQuery*)exec;
	char* huge_buf = session_->getHugeBuf();
	SQLConnection* mysql = session_->GetSQL();

	int err = reSucc;

	if (!mysql->Connected())
	{
		err = reDbErr;
	}
	else
	{
		int field_cnt = conf->fields_.count_;
		const int max_field_cnt = 255;
		PacketFieldFunc funcs[max_field_cnt]; // TODO:这个可以初始化的时候已经确定好

		static const int max_conds = 1024;
		char conds[max_conds] = { 0 };
		reader.readString(conds, max_conds);

		_STRNCPY_A(huge_buf, "select ");

		if (field_cnt == 0)
		{
			strcat(huge_buf, "*");

			for (int i = 0; i < conf->fields_.count_; i++)
			{
				DBField& field_info = conf->fields_.data_[i];
				funcs[i] = fieldFunc[field_info.type_];
			}
		}
		else
		{
			for (uint8_t i = 0; i < field_cnt; i++)
			{
				DBField& field_info = conf->fields_.data_[i];
				strcat(huge_buf, field_info.name_);
				if (i != field_cnt - 1)
				{
					strcat(huge_buf, ",");
				}

				funcs[i] = fieldFunc[field_info.type_];
			}
		}

		strcat(huge_buf, " from ");
		strcat(huge_buf, conf->table_name_);

		// TODO:上面这部分其实在读配置的时候已经确定

		if (conds[0])
		{
			strcat(huge_buf, " where ");
			strcat(huge_buf, conds);
		}

		err = mysql->RealQuery(huge_buf, strlen(huge_buf));

		if (err == reSucc)
		{
			int cnt = mysql->GetRowCount();

			DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
			retPack << (uint8_t)reSucc;
			retPack << (int)cnt;

			for (int i = 0; i < cnt; i++)
			{
				MYSQL_ROW row = mysql->CurrentRow();

				for (int colIndex = 0; colIndex < field_cnt; colIndex++)
				{
					field_index_ = colIndex;
					(this->*funcs[colIndex])(row[colIndex], retPack);
				}

				row = mysql->NextRow();
			}
			session_->flushProtoPacket(retPack);

			mysql->ResetQuery();
		}
	}

	if (err != reSucc)
	{
		DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
		retPack << (uint8_t)err;
		session_->flushProtoPacket(retPack);
	}

	return true;
}

bool DBExecutor::HandleInsert(DataPacketReader& reader, DBExec* exec)
{
	uint8_t sys_id;
	uint8_t cmd_id;
	reader >> sys_id >> cmd_id;

	DBInsert* conf = (DBInsert*)exec;
	char* huge_buf = session_->getHugeBuf();
	SQLConnection* mysql = session_->GetSQL();

	int err = reSucc;

	if (!mysql->Connected())
	{
		err = reDbErr;
	}
	else
	{
		int field_cnt = conf->fields_.count_;
		const int max_field_cnt = 255;
		JoinPacketStringFunc funcs[max_field_cnt];

		int nCount;
		reader >> nCount;

		strcpy(huge_buf, "insert into  ");
		strcat(huge_buf, conf->table_name_);
		strcat(huge_buf, "(");

		if (field_cnt == 0)
		{
			strcat(huge_buf, "*");

			for (int i = 0; i < conf->fields_.count_; i++)
			{
				DBField& field_info = conf->fields_.data_[i];
				funcs[i] = packetFunc[field_info.type_];
			}
		}
		else
		{
			for (uint8_t i = 0; i < field_cnt; i++)
			{
				DBField& field_info = conf->fields_.data_[i];
				strcat(huge_buf, field_info.name_);
				if (i < field_cnt - 1)
				{
					strcat(huge_buf, ",");
				}

				funcs[i] = packetFunc[field_info.type_];
			}
		}

		strcat(huge_buf, ") values ");

		for (int i = 0; i < nCount; i++)
		{
			_STRNCAT_S(huge_buf, " (", DBSession::HUNGSIZE);

			for (int colIndex = 0; colIndex < field_cnt; colIndex++)
			{
				field_index_ = colIndex;

				(this->*funcs[colIndex])(reader, huge_buf, DBSession::HUNGSIZE); // 从包中读取数据拼接字符串

				if (colIndex < field_cnt - 1)
				{
					strcat(huge_buf, ",");
				}
			}

			_STRNCAT_S(huge_buf, " )", DBSession::HUNGSIZE);

			if (i < nCount - 1)
			{
				_STRNCAT_S(huge_buf, ",", DBSession::HUNGSIZE);
			}
		}

		err = mysql->RealExec(huge_buf, strlen(huge_buf));

		if (err == reSucc)
		{
			mysql->ResetQuery();
		}
	}

	DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
	retPack << (uint8_t)err;
	session_->flushProtoPacket(retPack);

	return true;
}

bool DBExecutor::HandleUpdate(DataPacketReader& reader, DBExec* exec)
{
	uint8_t sys_id;
	uint8_t cmd_id;
	reader >> sys_id >> cmd_id;

	DBUpdate* conf = (DBUpdate*)exec;
	char* huge_buf = session_->getHugeBuf();
	SQLConnection* mysql = session_->GetSQL();

	int err = reSucc;

	if (!mysql->Connected())
	{
		err = reDbErr;
	}
	else
	{
		int field_cnt = conf->fields_.count_;
		//const int max_field_cnt = 255;

		SNPRINTFA(huge_buf, DBSession::HUNGSIZE, "update %s set ", conf->table_name_);

		for (uint8_t i = 0; i < field_cnt; i++)
		{
			DBField& field_info = conf->fields_.data_[i];
			strcat(huge_buf, field_info.name_);

			strcat(huge_buf, " = ");

			field_index_ = i;
			JoinPacketStringFunc func = packetFunc[field_info.type_];
			(this->*func)(reader, huge_buf, DBSession::HUNGSIZE);

			if (i < field_cnt - 1)
			{
				strcat(huge_buf, ",");
			}
		}

		static const int max_conds = 1024;
		char conds[max_conds] = { 0 };
		reader.readString(conds, max_conds);
		if (conds[0])
		{
			strcat(huge_buf, " where ");
			strcat(huge_buf, conds);
		}

		err = mysql->RealExec(huge_buf, strlen(huge_buf));

		if (err == reSucc)
		{
			mysql->ResetQuery();
		}
	}

	DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
	retPack << (uint8_t)err;
	session_->flushProtoPacket(retPack);

	return true;
}

bool DBExecutor::HandleDelete(DataPacketReader& reader, DBExec* exec)
{
	uint8_t sys_id;
	uint8_t cmd_id;
	reader >> sys_id >> cmd_id;

	DBDelete* conf = (DBDelete*)exec;
	char* huge_buf = session_->getHugeBuf();
	SQLConnection* mysql = session_->GetSQL();

	int err = reSucc;

	if (!mysql->Connected())
	{
		err = reDbErr;
	}
	else
	{
		uint16_t table_id;
		reader >> table_id;

		strcpy(huge_buf, "delete from ");
		strcat(huge_buf, conf->table_name_);

		static const int max_conds = 1024;
		char conds[max_conds] = { 0 };
		reader.readString(conds, max_conds);

		if (conds[0])
		{
			strcat(huge_buf, " where ");
			strcat(huge_buf, conds);
		}

		err = mysql->RealExec(huge_buf, strlen(huge_buf));

		if (err == reSucc)
		{
			mysql->ResetQuery();
		}
	}

	DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
	retPack << (uint8_t)err;
	session_->flushProtoPacket(retPack);

	return true;
}

bool DBExecutor::HandleProcedure(DataPacketReader& reader, DBExec* exec)
{
	uint8_t sys_id;
	uint8_t cmd_id;
	reader >> sys_id >> cmd_id;

	DBProcedure* conf = (DBProcedure*)exec;
	char* huge_buf = session_->getHugeBuf();
	SQLConnection* mysql = session_->GetSQL();

	int err = reSucc;

	//数据库连接是否就绪
	if (!mysql->Connected())
	{
		err = reDbErr;
	}
	else
	{
		SNPRINTFA(huge_buf, DBSession::HUNGSIZE, "call %s ", conf->name_);
		strcat(huge_buf, "(");
		int param_count = conf->param_types_.count_;
		for (int i = 0; i < param_count; i++) // 读入参数
		{
			JoinPacketStringFunc func = packetFunc[conf->param_types_.data_[i]];
			(this->*func)(reader, huge_buf, DBSession::HUNGSIZE);
			if (i < param_count - 1)
			{
				strcat(huge_buf, ",");
			}
		}
		strcat(huge_buf, ")");

		err = mysql->RealQuery(huge_buf, strlen(huge_buf));

		if (!err)
		{
			int count = mysql->GetRowCount();

			DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
			retPack << (uint8_t)err << (int)count;

			MYSQL_ROW pRow = mysql->CurrentRow();
			if (pRow)
			{
				int ret_count = conf->return_types_.count_;
				for (int i = 0; i < ret_count; i++) // 写入查询结果
				{
					PacketFieldFunc func = fieldFunc[conf->return_types_.data_[i]];
					(this->*func)(pRow[i], retPack);
				}
			}

			session_->flushProtoPacket(retPack);
			mysql->ResetQuery();
		}
		else
		{
			OutputMsg(rmError, ("%s error"), __FUNCTION__);
		}
	}

	if (err != reSucc)
	{
		DataPacket& retPack = session_->allocProtoPacket(MAKEINT16(sys_id, cmd_id));
		retPack << (uint8_t)err;
		session_->flushProtoPacket(retPack);
	}

	return true;
}

void DBExecutor::ReadIntField(const char* field, DataPacket& dp)
{
	int val = 0;
	sscanf(field, "%d", &val);
	dp << (int)val;
}

void DBExecutor::ReadDoubleField(const char* field, DataPacket& dp)
{
	double val = 0;
	sscanf(field, "%lf", &val);
	dp << (double)val;
}

void DBExecutor::ReadStringField(const char* field, DataPacket& dp)
{
	const int MAX_STR_LEN = 1024 * 10;
	char str_data[MAX_STR_LEN];

	_STRNCPY_A(str_data, field ? field : "");
	dp.writeString(str_data);
}

void DBExecutor::ReadInt64Field(const char* field, DataPacket& dp)
{
	int64_t val = atoll(field);
	dp << val;
}

void DBExecutor::ReadBlobField(const char* field, DataPacket& dp)
{
	unsigned long* pLength = session_->GetSQL()->GetFieldsLength();
	size_t rowLength = pLength ? (pLength[field_index_]) : 0;
	dp << (uint16_t)rowLength;
	dp.writeBuf(field, rowLength);
}


void DBExecutor::ReadPacketInt(DataPacketReader& reader, char* buf, int buf_size)
{
	int value;
	reader >> value;
	sprintf(buf + strlen(buf), "%d", value);
}

void DBExecutor::ReadPacketDouble(DataPacketReader& reader, char* buf, int buf_size)
{
	double value;
	reader >> value;
	sprintf(buf + strlen(buf), "%f", value);
}

void DBExecutor::ReadPacketString(DataPacketReader& reader, char* buf, int buf_size)
{
	size_t str_len = reader.readString(temp_str_, DBExecutor::MAX_TEMP_STR);

	char* ptr = buf + strlen(buf);

	ptr[0] = '"';
	ptr++;

	ptr += mysql_escape_string(ptr, temp_str_, (unsigned long)str_len);

	ptr[0] = '"';
	ptr[2] = '\0';
}

void DBExecutor::ReadPacketInt64(DataPacketReader& reader, char* buf, int buf_size)
{
	int64_t value;
	reader >> value;
	auto data = std::to_string(value);
	_STRNCAT_S(buf, data.c_str(), buf_size);
}

void DBExecutor::ReadPacketBlob(DataPacketReader& reader, char* buf, int buf_size)
{
	uint16_t data_size;
	reader >> data_size;

	size_t str_len = strlen(buf);

	char* ptr = buf + str_len;
	ptr[0] = '"';
	ptr++;

	ptr += mysql_escape_string(ptr, reader.getOffsetPtr(), (unsigned long)data_size);

	ptr[0] = '"';
	ptr[1] = ',';
	ptr[2] = '\0';

	reader.adjustOffset(data_size);
}

