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

	// ��һ���������д�ַ���
	void writeString(void * p, const char *str);

	// ����������ȡ�ַ���
	char* readString(void * p);

	//�����Ƕ�ȡ���ݵĽӿ�

	unsigned char readByte(void * p);//��ȡ�޷��ŵ�1�ֽ�
	char readChar(void * p);//��ȡ�����ŵ�1�ֽ�
	unsigned short  readWord(void * p);//��ȡ�޷��ŵ�2�ֽ�
	short readShort(void * p); //��ȡ�����ŵ�2�ֽ�
	int readInt(void * p);//��ȡ�����ŵ�4�ֽ�
	unsigned int readUInt(void * p);	//��ȡ�޷��ŵ�4�ֽ�
	double readUint64(void * p);//��ȡ�޷��ŵ�8�ֽ�
	double readInt64(void * p); //��ȡ�з��ŵ�8�ֽ�

	//��һϵ�е����ݣ������ε���c++�ӿ������������
	int readData(lua_State *L);

	//�����������ݰ�д���ݵĽӿ�
	void writeByte(void * p,  unsigned char btValue); //д���޷��ŵ�1�ֽ�
	void writeChar(void * p,   char cValue);//д������ŵ�1�ֽ�
	void writeWord(void * p, unsigned short wValue);//д���޷��ŵ�2�ֽ�
	void writeShort(void * p,  short wValue);//д������ŵ�2�ֽ�
	void writeInt(void * p, int  nValue);//д������ŵ�4�ֽ�
	void writeUInt(void * p, unsigned int  uValue);	//д���޷��ŵ�4�ֽ�
	void writeUint64(void * p, double value);//д���޷��ŵ�8�ֽ�
	void writeInt64(void * p, double value);//д���з��ŵ�8�ֽ�
	//����һϵ�е����ݣ������ε���c++�ӿ������������
	int writeData(lua_State *L);
};


//tolua_end

