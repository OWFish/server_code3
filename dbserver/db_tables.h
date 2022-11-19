#ifndef _DB_TABLES_H_
#define _DB_TABLES_H_

static const int MAX_TABLE_NAME = 32;

enum DB_EXEC_TYPE
{
	dbExecQuery = 1,
	dbExecInsert,
	dbExecUpdate,
	dbExecDelete,
	dbExecProcedure,
};

struct DBField 
{
	char name_[32];
	uint8_t type_;
};

struct DBTable
{
	char name_[32];
	Vector<DBField> fields_;

	int findField(const char* field_name);
};

class DBExec
{
public:
	DBExec();
	virtual ~DBExec() {}

public:
	virtual bool Init();

public:
	int cache_type_; // 缓存数据类型,对应enActorCacheDataType,小于0表示不需要缓存
	int type_;
};

// 查询语句
class DBQuery : public DBExec
{
public:
	DBQuery()
	{
		type_ = dbExecQuery;
	}
public:
	char table_name_[MAX_TABLE_NAME];
	DataList<DBField> fields_;
};

// 插入语句
class DBInsert : public DBExec
{
public:
	DBInsert()
	{
		type_ = dbExecInsert;
	}
public:
	char table_name_[MAX_TABLE_NAME];
	DataList<DBField> fields_;
};

// 更新语句
class DBUpdate : public DBExec
{
public:
	DBUpdate()
	{
		type_ = dbExecUpdate;
	}
public:
	char table_name_[MAX_TABLE_NAME];
	DataList<DBField> fields_;
};

// 删除语句
class DBDelete : public DBExec
{
public:
	DBDelete()
	{
		type_ = dbExecDelete;
	}
public:
	char table_name_[MAX_TABLE_NAME];
};

// 执行存储过程
class DBProcedure : public DBExec
{
public:
	DBProcedure()
	{
		type_ = dbExecProcedure;
	}
public:
	static const int MAX_NAME = 64;
public:
	char name_[MAX_NAME];
	DataList<DB_FILED_TYPE> param_types_;
	DataList<DB_FILED_TYPE> return_types_;
};

class DBTables : public BaseLuaConfig
{
	typedef MemoryContainer<char>	DataAllocator;
	typedef DBExec* (DBTables::*ReadExecFunc)();
public:
	DBTables();
	~DBTables();

public:
	bool Init();

public:
	DBExec* GetExec(int id);

protected:
	bool ReadConfig();
	DBTable* ReadTable(MYSQL* mysql, const char* table_name);
	void ShowError(const char* err);

private:
	DBExec* ReadError();
	DBExec* ReadQueryConfig();
	DBExec* ReadInsertConfig();
	DBExec* ReadUpdateConfig();
	DBExec* ReadDeleteConfig();
	DBExec* ReadProcedureConfig();

public:
	bool init_;
	Vector<DBTable*> tables_;

private:
	DataList<DBExec*> execs_;
	static const ReadExecFunc read_funs_[];

	DataAllocator allocator_;	// 分配器
};

#endif
