#pragma once
//tolua_begin

enum tagDataType{
	dtByte = 0,
	dtChar = 1,
	dtWord = 2,
	dtShort = 3,
	dtInt = 4,
	dtUint = 5,
	dtInt64 = 6,
	dtUint64 = 7,
	dtString = 8,
};

namespace DataPack
{
	void * allocPacket();

	int getAvaliableLength(void* p);
	int getLength(void* p);

	// 向一个网络包里写字符串
	void writeString(void * p, const char *str);

	// 从网络包里读取字符串
	char* readString(void * p);

	//下面是读取数据的接口

	unsigned char readByte(void * p);//读取无符号的1字节
	char readChar(void * p);//读取带符号的1字节
	unsigned short  readWord(void * p);//读取无符号的2字节
	short readShort(void * p); //读取带符号的2字节
	int readInt(void * p);//读取带符号的4字节
	unsigned int readUInt(void * p);	//读取无符号的4字节
	double readUint64(void * p);//读取无符号的8字节
	double readInt64(void * p); //读取有符号的8字节

	//读一系列的数据，避免多次调用c++接口造成性能问题
	int readData(lua_State *L);

	//下面是往数据包写数据的接口
	void writeByte(void * p,  unsigned char btValue); //写入无符号的1字节
	void writeChar(void * p,   char cValue);//写入带符号的1字节
	void writeWord(void * p, unsigned short wValue);//写入无符号的2字节
	void writeShort(void * p,  short wValue);//写入带符号的2字节
	void writeInt(void * p, int  nValue);//写入带符号的4字节
	void writeUInt(void * p, unsigned int  uValue);	//写入无符号的4字节
	void writeUint64(void * p, double value);//写入无符号的8字节
	void writeInt64(void * p, double value);//写入有符号的8字节
	//发送一系列的数据，避免多次调用c++接口造成性能问题
	int writeData(lua_State *L);
};


//tolua_end

