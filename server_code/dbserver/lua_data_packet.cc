#include "StdAfx.h"
#include "lua_data_packet.h"

namespace DataPack
{
void* allocPacket()
{
	static BaseAllocator alloc("dbserver datapacket");
	static DataPacket p(&alloc);
	p.setLength(0);
	return &p;
}


int getAvaliableLength(void* p)
{
	if (p == NULL) return 0;

	return (int)(((DataPacketReader*)p)->getAvaliableLength());
}

int getLength(void* p)
{
	if (p == NULL) return 0;

	return (int)(((DataPacketReader*)p)->getLength());
}


void writeString(void* p, const char* str)
{
	if (p == NULL) return;

	const char* sResutl = str;

	if (str == NULL)
	{
		sResutl = "";
	}

	(*(DataPacket*)p) << sResutl;
}

char* readString(void* p)
{
	if (p == NULL) return NULL;

	const char* result;
	(*(DataPacketReader*)p) >> result;
	return (char*)result;
}
unsigned char readByte(void* p)
{
	unsigned char bResult = 0;

	if (p == NULL) return 0;

	(*(DataPacketReader*)p) >> (bResult);
	return bResult;
}


char readChar(void* p)
{
	char cResult = 0;

	if (p == NULL) return 0;

	(*(DataPacketReader*)p) >> (cResult);
	return cResult;
}

unsigned short  readWord(void* p)
{
	unsigned short wValue = 0;

	if (p == NULL) return wValue;

	(*(DataPacketReader*)p) >> (wValue);
	return wValue;
}
short readShort(void* p)
{
	short wValue = 0;

	if (p == NULL) return wValue;

	(*(DataPacketReader*)p) >> (wValue);
	return wValue;
}
int readInt(void* p)
{
	int nValue = 0;

	if (p == NULL) return nValue;

	(*(DataPacketReader*)p) >> (nValue);
	return nValue;
}
unsigned int readUInt(void* p)
{
	unsigned int uValue = 0;

	if (p == NULL) return uValue;

	(*(DataPacketReader*)p) >> (uValue);
	return uValue;
}
double readUint64(void* p)
{
	unsigned long long lValue = 0;
	double d = 0;

	if (p == NULL) return d;

	(*(DataPacketReader*)p) >> (lValue);

	memcpy(&d, &lValue, sizeof(lValue));
	return d;
}
double readInt64(void* p)
{
	long long lValue = 0;
	double d = 0;

	if (p == NULL) return d;

	(*(DataPacketReader*)p) >> (lValue);
	memcpy(&d, &lValue, sizeof(lValue));
	return d;
}

int readData(lua_State* L)
{
	DataPacketReader* pack = (DataPacketReader*)lua_touserdata(L, 1);

	if (!pack) return 0;

	int nParamCount = (int)lua_tointeger(L, 2);

	for (int i = 0, index = 3; i < nParamCount; i++, index++)
	{
		int dt = (int)lua_tointeger(L, index);

		switch (dt)
		{
		case dtByte:
			{
				BYTE b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtChar:
			{
				char b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtWord:
			{
				unsigned short b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtShort:
			{
				short b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtInt:
			{
				int b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtUint:
			{
				unsigned int b = 0;
				(*pack) >> b;
				lua_pushinteger(L, b);
				break;
			}

		case dtString:
			{
				const char* b = NULL;
				(*pack) >> b;
				lua_pushstring(L, b);
				break;
			}

		case dtInt64:
			{
				long long b = 0;
				(*pack) >> b;
				double d = 0;
				memcpy(&d, &b, sizeof(b));
				lua_pushnumber(L, d);
				break;
			}

		case dtUint64:
			{
				unsigned long long b = 0;
				(*pack) >> b;
				double d = 0;
				memcpy(&d, &b, sizeof(b));
				lua_pushnumber(L, d);
				break;
			}
		}
	}

	return nParamCount;
}

void writeByte(void* p, unsigned char btValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (btValue);
}
void writeChar(void* p , char cValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (cValue);
}
void writeWord(void* p, unsigned short wValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (wValue);
}
void writeShort(void* p, short wValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (wValue);
}
void writeInt(void* p, int  nValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (nValue);
}
void writeUInt(void* p, unsigned int  uValue)
{
	if (p == NULL) return;

	(*(DataPacket*)p) << (uValue);
}
void writeUint64(void* p, double d)
{
	if (p == NULL) return;

	unsigned long long lValue = 0;
	memcpy(&lValue, &d, sizeof(d));
	(*(DataPacket*)p) << (lValue);
}
void writeInt64(void* p, double d)
{
	if (p == NULL) return;

	long long lValue = 0;
	memcpy(&lValue, &d, sizeof(d));
	(*(DataPacket*)p) << (lValue);
}

int writeData(lua_State* L)
{
	DataPacket* packet = (DataPacket*)lua_touserdata(L, 1);

	if (!packet) return 0;

	int nParamCount = (int)lua_tointeger(L, 2);

	for (int i = 0, index = 3; i < nParamCount; i++, index += 2)
	{
		int dt = (int)lua_tointeger(L, index);

		switch (dt)
		{
		case dtByte:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (BYTE)b;
				break;
			}

		case dtChar:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (char)b;
				break;
			}

		case dtWord:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (unsigned short)b;
				break;
			}

		case dtShort:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (short)b;
				break;
			}

		case dtInt:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (int)b;
				break;
			}

		case dtUint:
			{
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (unsigned int)b;
				break;
			}

		case dtString:
			{
				const char* b = lua_tostring(L, index + 1);
				packet->writeString(b);
				break;
			}

		case dtInt64:
			{
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				(*packet) << (long long)b;
				break;
			}

		case dtUint64:
			{
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				(*packet) << (unsigned long long)b;
				break;
			}
		}
	}

	return 0;
}


};
