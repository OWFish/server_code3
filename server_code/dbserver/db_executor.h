#ifndef _DB_EXECUTOR_H_
#define _DB_EXECUTOR_H_

class DBSession;
class DBExec;

class DBExecutor
{
	static const int MAX_TEMP_STR = 65535;
public:
	typedef void(DBExecutor::*JoinPacketStringFunc)(DataPacketReader& reader, char* buf, int buf_size); // 从包读取数据拼到sql里
	typedef void(DBExecutor::*PacketFieldFunc)(const char* field, DataPacket& dp); // 打包返回结果的各个列

	DBExecutor(DBSession* sess)
		: field_index_(0),session_(sess)
	{
		// 
	}

	void ResetExec()
	{
		field_index_ = 0;
	}

public:
	bool HandleExec(DataPacketReader& reader);

private:
	bool HandleQuery(DataPacketReader& reader, DBExec* exec);
	bool HandleInsert(DataPacketReader& reader, DBExec* exec);
	bool HandleUpdate(DataPacketReader& reader, DBExec* exec);
	bool HandleDelete(DataPacketReader& reader, DBExec* exec);
	bool HandleProcedure(DataPacketReader& reader, DBExec* exec);

private:
	void ReadIntField(const char* field, DataPacket& dp);
	void ReadDoubleField(const char* field, DataPacket& dp);
	void ReadStringField(const char* field, DataPacket& dp);
	void ReadInt64Field(const char* field, DataPacket& dp);
	void ReadBlobField(const char* field, DataPacket& dp);

	void ReadPacketInt(DataPacketReader& reader, char* buf, int buf_size);
	void ReadPacketDouble(DataPacketReader& reader, char* buf, int buf_size);
	void ReadPacketString(DataPacketReader& reader, char* buf, int buf_size);
	void ReadPacketInt64(DataPacketReader& reader, char* buf, int buf_size);
	void ReadPacketBlob(DataPacketReader& reader, char* buf, int buf_size);

public:
	int field_index_; // 当前列索引
	DBSession* session_;

	char temp_str_[MAX_TEMP_STR];

private:
	static JoinPacketStringFunc packetFunc[];
	static PacketFieldFunc fieldFunc[];
};

#endif