#include "StdAfx.h"
#ifndef _MSC_VER
#include "../../StdAfx.h"
#endif
namespace LDataPack
{
#define WRITE_P(p, v) {if (!p) return; else (*(DataPacket*)p) << (v);}
#define READ_P(p, v) {if (!p) return 0; else {(*(DataPacketReader*)p) >> v; return v;}}


int allocPacket(lua_State* L)
{
	tolua_Error err;

	if (tolua_isnoobj(L, 1, &err))
	{
		// static类型，非线程安全
		static BaseAllocator alloc("datapacket");
		static DataPacket p(&alloc);
		p.setLength(0);
		lua_pushlightuserdata(L, &p);
	}
	else
	{
		if (!tolua_isuserdata(L, 1, 0, &err) ||
		        !tolua_isnumber(L, 2, 0, &err) ||
		        !tolua_isnumber(L, 3, 0, &err) ||
		        !tolua_isnoobj(L, 4, &err))
		{
			tolua_error(L, (char*)"#ferror in function 'allocPacket'.", &err);
			return 0;
		}

		Actor* actor = (Actor*)lua_topointer(L, 1);

		if (actor == NULL || ((Entity*)actor)->GetType() != enActor) return 0;

		int sid = (int)lua_tointeger(L, 2);
		int cmd = (int)lua_tointeger(L, 3);

		ActorPacket& ap = ((Actor*)actor)->GetFastPacket();

		DataPacket& pack = ((Actor*)actor)->AllocPacket(ap);
		/*
		保存指针以便在角色申请数据包后出现脚本错误从而无法flush数据包的时候回收数据包，
		如果脚本出错且数据包没有被回收，则会导致整个游戏引擎就此不能正常工作
		*/
		assert(GameScript::ScriptActorPacket == NULL);
		if (GameScript::ScriptActorPacket != NULL)
		{
			lua_getglobal(L,"debug");
			lua_getfield(L, -1, "traceback");
			int err = lua_pcall(L, 0, 1, 0);
			const char* s = lua_tostring(L, -1);
			OutputMsg(rmError, s);

			GameScript::ScriptActorPacket->rollBack();
			GameScript::ScriptActorPacket->packet_ = NULL;
			GameScript::ScriptActorPacket = NULL;
			OutputMsg(rmError, ("allocPacket : collected an ActorPacket; actor id : %d"), actor->GetActorId());
		}

		GameScript::ScriptActorPacket = &ap;
		uint8_t hdr[] = {(uint8_t)sid, (uint8_t)cmd};
//#ifdef _MSC_VER
		//OutputMsg(rmTip, "========== send (%d,%d)", sid, cmd);
//#endif
		pack.writeBuf(hdr, sizeof(hdr));
		lua_pushlightuserdata(L, ap.packet_);
	}

	return 1;
}

void* allocPacketCache()
{
	static BaseAllocator alloc("datapacket cache");
	DataPacket* p = new DataPacket(&alloc);
	p->setLength(0);
	return p;
}

void releasePacketCache(void* dpcache)
{
	DataPacket* p = (DataPacket*)dpcache;
	if (p) {
		SafeDelete(p);
	}
}

int allocPacketToCenter(lua_State* L)
{
	tolua_Error err;

	if (!tolua_isnoobj(L, 1, &err)) return 0;
	
	// static类型，非线程安全
	static BaseAllocator alloc("CenterDataPacket");
	static DataPacket p(&alloc);
	p.setLength(0);
	lua_pushlightuserdata(L, &p);

	return 1;
}

void* allocExtraPacket()
{
	static BaseAllocator alloc("extradatapacket");
	static DataPacket p(&alloc);
	p.setLength(0);
	return &p;
}

int flushLf(lua_State* L)
{
	tolua_Error err;
	
	if (!tolua_isuserdata(L, 1, 0, &err) || !tolua_isnumber(L, 2, 0, &err)) 
		return 0;

	DataPacket* pack = (DataPacket*)lua_touserdata(L, 1);
	int actorid = (int)lua_tointeger(L, 2);
	Actor* actor = NULL;
	if (tolua_isuserdata(L, 3, 0, &err))
	{
		actor = (Actor*)lua_touserdata(L, 3);
	}
	// static类型，非线程安全
	static ActorIdPacket ap;
	DataPacket& packet = ap.AllocIdPacket(actorid, actor);
	packet.writeBuf(pack->getMemoryPtr(), pack->getLength());
	ap.flush();
	
	return 0;
}

void flush(void* pack)
{
	ActorPacket* ap = GameScript::ScriptActorPacket;
	// allocPacket和flush必须是一一匹配的
	assert(ap != NULL);
	assert(pack == ap->packet_);

	ap->flush();
	ap->packet_ = NULL;
	//标记逻辑脚本申请的数据包已回收！
	GameScript::ScriptActorPacket = NULL;
}

// 用于单元测试的包
void* test_allocPack()
{
	static BaseAllocator alloc("test_datapacket");
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

int getPosition(void* p)
{
	if (p == NULL) return 0;

	return (int)(((DataPacketReader*)p)->getPosition());
}

const char* readString(void* p)
{
	const char* v;
	READ_P(p, v);
}

unsigned char readByte(void* p)
{
	unsigned char v = 0;
	READ_P(p, v);
}

char readChar(void* p)
{
	char v = 0;
	READ_P(p, v);
}

unsigned short readWord(void* p)
{
	unsigned short v = 0;
	READ_P(p, v);
}

short readShort(void* p)
{
	short v = 0;
	READ_P(p, v);
}

int readInt(void* p)
{
	int v = 0;
	READ_P(p, v);
}

unsigned int readUInt(void* p)
{
	unsigned int v = 0;
	READ_P(p, v);
}

double readUint64(void* p)
{
	if (p == NULL) return 0;

	unsigned long long v = 0;
	double d = 0;
	(*(DataPacketReader*)p) >> (v);

	memcpy(&d, &v, sizeof(v));
	return d;
}

double readInt64(void* p)
{
	if (p == NULL) return 0;

	long long v = 0;
	double d = 0;
	(*(DataPacketReader*)p) >> (v);
	memcpy(&d, &v, sizeof(v));
	return d;
}

int readData(lua_State* L)
{
	DataPacketReader* pack = (DataPacketReader*)lua_touserdata(L, 1);

	if (!pack) return 0;

	int pcount = (int)lua_tointeger(L, 2);

	for (int i = 0, index = 3; i < pcount; i++, index++)
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
		case dtDouble:
			{
				double d = 0;
				(*pack) >> d;
				lua_pushnumber(L, d);
				break;
			}
		}
	}

	return pcount;
}

void writeString(void* p, const char* str)
{
	WRITE_P(p, (str ? str : ""));
}

void writeByte(void* p, unsigned char v)
{
	WRITE_P(p, v);
}
void writeChar(void* p , char v)
{
	WRITE_P(p, v);
}
void writeWord(void* p, unsigned short v)
{
	WRITE_P(p, v);
}
void writeShort(void* p, short v)
{
	WRITE_P(p, v);
}
void writeInt(void* p, int v)
{
	WRITE_P(p, v);
}
void writeUInt(void* p, unsigned int v)
{
	WRITE_P(p, v);
}
void writeUint64(void* p, double d)
{
	unsigned long long v = 0;
	memcpy(&v, &d, sizeof(d));
	WRITE_P(p, v);
}
void writeInt64(void* p, double d)
{
	long long v = 0;
	memcpy(&v, &d, sizeof(d));
	WRITE_P(p, v);
}

void writeInt64I(void* p, long long v) {
	WRITE_P(p, v);
}

void writeDouble(void* p, double v)
{
	WRITE_P(p, v);
}


int writeData(lua_State* L)
{
	tolua_Error err;
	DataPacket* packet = NULL;
	int paramCount = 0;
	if (!tolua_isuserdata(L, 1, 0, &err) || !tolua_isnumber(L, 2, 0, &err) )
	{
		goto DataError;
	}
	packet = (DataPacket*)lua_touserdata(L, 1);

	if (!packet) return 0;
	
	paramCount = (int)lua_tointeger(L, 2);

	for (int i = 0, index = 3; i < paramCount; i++, index += 2)
	{
		if (!tolua_isnumber(L, index, 0, &err))
		{
			goto DataError;
		}
		int dt = (int)lua_tointeger(L, index);

		switch (dt)
		{
		case dtByte:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (uint8_t)b;
				break;
			}

		case dtChar:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (char)b;
				break;
			}

		case dtWord:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (unsigned short)b;
				break;
			}

		case dtShort:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (short)b;
				break;
			}

		case dtInt:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (int)b;
				break;
			}

		case dtUint:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				int b = (int)lua_tointeger(L, index + 1);
				(*packet) << (unsigned int)b;
				break;
			}

		case dtString:
			{
				if (!tolua_isstring(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				const char* b = lua_tostring(L, index + 1);
				packet->writeString(b);
				break;
			}

		case dtInt64:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				(*packet) << (long long)b;
				break;
			}

		case dtUint64:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				double d = (double)lua_tonumber(L, index + 1);
				long long b = 0;
				memcpy(&b, &d, sizeof(d));
				(*packet) << (unsigned long long)b;
				break;
			}
		case dtDouble:
			{
				if (!tolua_isnumber(L, index + 1, 0, &err))
				{
					goto DataError;
				}
				double d = (double)lua_tonumber(L, index + 1);
				(*packet) << d;
				break;
			}
		default:
			{
				goto DataError;
			}
		}
	}
	return 0;

DataError:
	tolua_error(L,(char*)"#ferror in function 'writeData'.",&err);
	return 0;
}

void setPosition(void* p, int pos)
{
	if (!p) return;

	((DataPacket*)p)->setPosition(pos);
}

void writePacket(void* p, void* dp, bool reset)
{
	if (!p || !dp) return;

	DataPacketReader* reader = (DataPacketReader*)dp;

	if (reset) 
		((DataPacket*)p)->writeBuf(reader->getMemoryPtr(), reader->getLength());
	else
		((DataPacket*)p)->writeBuf(reader->getOffsetPtr(), reader->getAvaliableLength());
}

void writeUserItem(void* p, void* item)
{
	if (!item) return;

	WRITE_P(p, (*(ItemData*)item));
}

void writeProto(void* p, void* proto)
{

}

#undef WRITE_P
#undef READ_P
};


