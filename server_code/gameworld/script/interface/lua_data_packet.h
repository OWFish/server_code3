#ifndef _LUA_DATA_PACKET_H_
#define _LUA_DATA_PACKET_H_

//tolua_begin

namespace LDataPack
{
// ����һ�����ݰ�����������������򷵻�һ�������datapacket�����򷵻�һ�����͸�Actor��packet
int allocPacket(lua_State* L);
// ����һ�����ݰ����棬���Ա�����lua�ﲻ�������ͣ�����ʱ��Ҫ�ͷ�
void* allocPacketCache();
void releasePacketCache(void* dpcache);

void* allocExtraPacket();

// ����һ�����͵�centerserver�����ݰ�
int allocPacketToCenter(lua_State* L);

// ���ݰ����͸�Actor
void flush(void* ap);
// ��������
int flushLf(lua_State* L);

// ����һ�������õĲ��԰�
void* test_allocPack();

int getAvaliableLength(void* p);
int getLength(void* p);
int getPosition(void* p);
void setPosition(void* p, int pos);

//�����Ƕ�ȡ���ݵĽӿ�
const char* readString(void* p);
unsigned char readByte(void* p); //��ȡ�޷��ŵ�1�ֽ�
char readChar(void* p); //��ȡ�����ŵ�1�ֽ�
unsigned short readWord(void* p); //��ȡ�޷��ŵ�2�ֽ�
short readShort(void* p);  //��ȡ�����ŵ�2�ֽ�
int readInt(void* p); //��ȡ�����ŵ�4�ֽ�
unsigned int readUInt(void* p);	//��ȡ�޷��ŵ�4�ֽ�
double readUint64(void* p); //��ȡ�޷��ŵ�8�ֽ�
double readInt64(void* p);  //��ȡ�з��ŵ�8�ֽ�

//��һϵ�е����ݣ������ε���c++�ӿ������������
int readData(lua_State* L);

//�����������ݰ�д���ݵĽӿ�
void writeString(void* p, const char* str);
void writeByte(void* p, unsigned char v);  //д���޷��ŵ�1�ֽ�
void writeChar(void* p, char v); //д������ŵ�1�ֽ�
void writeWord(void* p, unsigned short v); //д���޷��ŵ�2�ֽ�
void writeShort(void* p, short v); //д������ŵ�2�ֽ�
void writeInt(void* p, int v); //д������ŵ�4�ֽ�
void writeUInt(void* p, unsigned int  v);	//д���޷��ŵ�4�ֽ�
void writeUint64(void* p, double v); //д���޷��ŵ�64�ֽ�, ����Ϊlua�е��м����
void writeInt64(void* p, double v); //д���з��ŵ�64�ֽ�, ����Ϊlua�е��м����
void writeInt64I(void* p, long long v);
void writeDouble(void* p, double v); //д��double, ����Ϊlua�е�number
void writeUserItem(void* p, void* item);   //д��һ����Ʒ������
//����һϵ�е����ݣ������ε���c++�ӿ������������
int writeData(lua_State* L);
void writePacket(void* p, void* dp, bool reset = true);
void writeProto(void* p, void* proto);
};


//tolua_end

#endif

