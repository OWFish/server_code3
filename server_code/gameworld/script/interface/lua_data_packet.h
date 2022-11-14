#ifndef _LUA_DATA_PACKET_H_
#define _LUA_DATA_PACKET_H_

//tolua_begin

namespace LDataPack
{
// 分配一个数据包，如果不带参数，则返回一个纯粹的datapacket，否则返回一个发送个Actor的packet
int allocPacket(lua_State* L);
// 分配一个数据包缓存，可以保存在lua里不立即发送，不用时需要释放
void* allocPacketCache();
void releasePacketCache(void* dpcache);

void* allocExtraPacket();

// 分配一个发送到centerserver的数据包
int allocPacketToCenter(lua_State* L);

// 数据包发送给Actor
void flush(void* ap);
// 发送连服
int flushLf(lua_State* L);

// 分配一个测试用的测试包
void* test_allocPack();

int getAvaliableLength(void* p);
int getLength(void* p);
int getPosition(void* p);
void setPosition(void* p, int pos);

//下面是读取数据的接口
const char* readString(void* p);
unsigned char readByte(void* p); //读取无符号的1字节
char readChar(void* p); //读取带符号的1字节
unsigned short readWord(void* p); //读取无符号的2字节
short readShort(void* p);  //读取带符号的2字节
int readInt(void* p); //读取带符号的4字节
unsigned int readUInt(void* p);	//读取无符号的4字节
double readUint64(void* p); //读取无符号的8字节
double readInt64(void* p);  //读取有符号的8字节

//读一系列的数据，避免多次调用c++接口造成性能问题
int readData(lua_State* L);

//下面是往数据包写数据的接口
void writeString(void* p, const char* str);
void writeByte(void* p, unsigned char v);  //写入无符号的1字节
void writeChar(void* p, char v); //写入带符号的1字节
void writeWord(void* p, unsigned short v); //写入无符号的2字节
void writeShort(void* p, short v); //写入带符号的2字节
void writeInt(void* p, int v); //写入带符号的4字节
void writeUInt(void* p, unsigned int  v);	//写入无符号的4字节
void writeUint64(void* p, double v); //写入无符号的64字节, 参数为lua中的中间变量
void writeInt64(void* p, double v); //写入有符号的64字节, 参数为lua中的中间变量
void writeInt64I(void* p, long long v);
void writeDouble(void* p, double v); //写入double, 参数为lua中的number
void writeUserItem(void* p, void* item);   //写入一个物品的数据
//发送一系列的数据，避免多次调用c++接口造成性能问题
int writeData(lua_State* L);
void writePacket(void* p, void* dp, bool reset = true);
void writeProto(void* p, void* proto);
};


//tolua_end

#endif

