#include "StdAfx.h"

int DBTable::findField(const char* field_name)
{
	for (int i = 0; i < fields_.count(); i++)
	{
		if (!strcmp(fields_[i].name_, field_name))
		{
			return i;
		}
	}
	return -1;
}

DBExec::DBExec()
	: cache_type_(-1)
{
	// 
}

bool DBExec::Init()
{
	return true;
}

const DBTables::ReadExecFunc DBTables::read_funs_[]
{
	&DBTables::ReadError,
	&DBTables::ReadQueryConfig,
	&DBTables::ReadInsertConfig,
	&DBTables::ReadUpdateConfig,
	&DBTables::ReadDeleteConfig,
	&DBTables::ReadProcedureConfig,
};

DBTables::DBTables()
	: allocator_(("DBTables"))
{
	init_ = false;
}

DBTables::~DBTables()
{
	for (int i = 0; i < tables_.count(); i++)
	{
		delete tables_[i];
	}
	tables_.clear();

	for (int i = 0; i < execs_.count_; i++)
	{
		delete execs_.data_[i];
	}
}

bool DBTables::Init()
{
	if (init_) return true;

	if (!ReadConfig())
	{
		OutputMsg(rmError, "read db table config error");
		return false;
	}

	init_ = true;

	return true;
}

DBExec* DBTables::GetExec(int id)
{
	if (id < 0 || id >= execs_.count_) return NULL;

	return execs_.data_[id];
}

bool DBTables::ReadConfig()
{
	using namespace stream;

	bool result = false;
	MemoryStream ms(NULL);

	try
	{
		if (ms.loadFromFile("./data/tables.lua") <= 0)
		{
			ShowError(("unable to load config from file tables.lua"));
			return false;
		}
		 
		if (!setScript((const char*)ms.getMemory()))
		{
			ShowError(("parse tables config script failed"));
			return false;
		}

		if (openGlobalTable("Tables"))
		{
			int count = (int)lua_objlen(lua_, -1);
			if (enumTableFirst())
			{
				int index = 0;
				execs_.data_ = (DBExec**)allocator_.AllocBuffer(sizeof(DBExec*) * count);
				execs_.count_ = count;

				do
				{
					int etype = getFieldInt("etype");

					if (etype < 0 || etype >= (int)ArrayCount(read_funs_))
					{
						return false;
					}

					DBExec* db_exec = (this->*read_funs_[etype])();
					if (!db_exec)
					{
						return false;
					}

					int ndef = -1;
					db_exec->cache_type_ = getFieldInt("cache_type", &ndef);

					db_exec->Init();
					execs_.data_[index] = db_exec;

					index++;

				} while (enumTableNext());
			}

			closeTable();

			result = true;
		}
	}
	catch (RefString& s)
	{
		OutputMsg(rmNormal, s.rawStr());
	}
	catch (...)
	{
		OutputMsg(rmNormal, ("unexpected error on load config"));
	}

	return result;
}

DBTable* DBTables::ReadTable(MYSQL* mysql, const char* table_name)
{
	MYSQL_RES *tbl_cols = mysql_list_fields(mysql, table_name, "%");
	if (!tbl_cols)
		return NULL;

	DBTable* tbl = new DBTable();
	_STRNCPY_A(tbl->name_, table_name);

	unsigned int field_cnt = mysql_num_fields(tbl_cols);

	tbl->fields_.reserve(field_cnt);
	tbl->fields_.trunc(field_cnt);

	bool is_ok = true;
	for (unsigned int field_idx = 0; is_ok && field_idx < field_cnt; ++field_idx)
	{
		DBField& db_field = tbl->fields_[field_idx];
		MYSQL_FIELD *col = mysql_fetch_field_direct(tbl_cols, field_idx);
		_STRNCPY_A(db_field.name_, col->name);

		switch (col->type)
		{
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_INT24:
			db_field.type_ = ftInt;
			break;
		case MYSQL_TYPE_DOUBLE:
		case MYSQL_TYPE_FLOAT:
			db_field.type_ = ftDouble;
			break;
		case MYSQL_TYPE_VAR_STRING:
		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_DATETIME:
			db_field.type_ = ftString;
			break;
		case MYSQL_TYPE_LONGLONG:
			db_field.type_ = ftInt64;
			break;
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
			db_field.type_ = ftBlob;
			break;
		default:
			OutputMsg(rmError, "field type error : %d", col->type); // TODO:这种情况应该不让服务器启动了
			is_ok = false;
			break;
		}
	}
	mysql_free_result(tbl_cols);

	if (!is_ok)
	{
		delete tbl;
		return NULL;
	}

	tables_.add(tbl);

	return tbl;
}

void DBTables::ShowError(const char* err)
{
	SetErrDesc(err);
	RefString sErr = ("[Configuration Error]");
	sErr += err;
	throw sErr;
}

DBExec* DBTables::ReadError()
{
	return NULL;
}

DBExec* DBTables::ReadQueryConfig()
{
	DBQuery* db_exec = new DBQuery();

	getFieldStringBuffer("table_name", db_exec->table_name_, MAX_TABLE_NAME);

	if (!openFieldTable("columns"))
	{
		OutputMsg(rmError, "can not open columns table");
		return NULL;
	}
	int count = (int)lua_objlen(lua_, -1);

	db_exec->fields_.data_ = (DBField*)allocator_.AllocBuffer(sizeof(DBField) * count);
	db_exec->fields_.count_ = count;

	if (enumTableFirst())
	{
		int index = 0;
		do
		{
			DBField& db_field = db_exec->fields_.data_[index];
			getFieldStringBuffer("name", db_field.name_, sizeof(db_field.name_));
			db_field.type_ = getFieldInt("type", NULL);

			index++;

		} while (enumTableNext());
	}
	closeTable();

	return db_exec;
}

DBExec* DBTables::ReadInsertConfig()
{
	DBInsert* db_exec = new DBInsert();

	getFieldStringBuffer("table_name", db_exec->table_name_, MAX_TABLE_NAME);

	if (!openFieldTable("columns"))
	{
		OutputMsg(rmError, "can not open columns table");
		return NULL;
	}
	int count = (int)lua_objlen(lua_, -1);
	db_exec->fields_.data_ = (DBField*)allocator_.AllocBuffer(sizeof(DBField) * count);
	db_exec->fields_.count_ = count;

	if (enumTableFirst())
	{
		int index = 0;
		do
		{
			DBField& db_field = db_exec->fields_.data_[index];
			getFieldStringBuffer("name", db_field.name_, sizeof(db_field.name_));
			db_field.type_ = getFieldInt("type", NULL);

			index++;

		} while (enumTableNext());
	}
	closeTable();

	return db_exec;
}

DBExec* DBTables::ReadUpdateConfig()
{
	DBUpdate* db_exec = new DBUpdate();

	getFieldStringBuffer("table_name", db_exec->table_name_, MAX_TABLE_NAME);

	if (!openFieldTable("columns"))
	{
		OutputMsg(rmError, "can not open columns table");
		return NULL;
	}
	int count = (int)lua_objlen(lua_, -1);
	db_exec->fields_.data_ = (DBField*)allocator_.AllocBuffer(sizeof(DBField) * count);
	db_exec->fields_.count_ = count;

	if (enumTableFirst())
	{
		int index = 0;
		do
		{
			DBField& db_field = db_exec->fields_.data_[index];
			getFieldStringBuffer("name", db_field.name_, sizeof(db_field.name_));
			db_field.type_ = getFieldInt("type", NULL);

			index++;

		} while (enumTableNext());
	}
	closeTable();

	return db_exec;
}

DBExec* DBTables::ReadDeleteConfig()
{
	DBDelete* db_exec = new DBDelete();

	getFieldStringBuffer("table_name", db_exec->table_name_, sizeof(db_exec->table_name_));

	return db_exec;
}

DBExec* DBTables::ReadProcedureConfig()
{
	DBProcedure* db_exec = new DBProcedure();
	getFieldStringBuffer("name", db_exec->name_, DBProcedure::MAX_NAME);

	{
		if (!openFieldTable("paramlist"))
		{
			OutputMsg(rmError, "can not open paramlist table");
			delete db_exec;
			return NULL;
		}

		int count = (int)lua_objlen(lua_, -1);
		DataList<DB_FILED_TYPE>& params = db_exec->param_types_;
		params.data_ = (DB_FILED_TYPE*)allocator_.AllocBuffer(sizeof(DB_FILED_TYPE) * count);
		params.count_ = count;

		if (enumTableFirst())
		{
			int index = 0;
			do
			{
				params.data_[index] = (DB_FILED_TYPE)getFieldInt(NULL);

				index++;
			} while (enumTableNext());
		}
		closeTable();
	}

	{
		if(!openFieldTable("returns"))
		{
			OutputMsg(rmError, "can not open returns table");
			delete db_exec;
			return NULL;
		}

		int count = (int)lua_objlen(lua_, -1);

		DataList<DB_FILED_TYPE>& returns = db_exec->return_types_;
		returns.data_ = (DB_FILED_TYPE*)allocator_.AllocBuffer(sizeof(DB_FILED_TYPE) * count);
		returns.count_ = count;

		if (enumTableFirst())
		{
			int index = 0;
			do
			{
				returns.data_[index] = (DB_FILED_TYPE)getFieldInt(NULL);

				index++;
			} while (enumTableNext());
		}
		closeTable();
	}

	return db_exec;
}

