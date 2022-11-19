#pragma once
#include <stdint.h>
#include <string>


#pragma pack(push,1)
namespace Protocol {
	struct BaseProto {
		uint8_t sid;
		uint8_t cmd;
		BaseProto(uint8_t sid, uint8_t cmd) :sid(sid), cmd(cmd){}
	};
#define ProtoDef(protoname, sid, cmd) struct protoname: public BaseProto { \
	protoname() :BaseProto(sid, cmd){ }\
	void Reset() { memset((char*)this + sizeof(BaseProto), 0, sizeof(protoname)-sizeof(BaseProto)); } \

// 用宏来解决上面的宏定义时代码格式化混乱的问题
#define StartNameSpace namespace Protocol {
#define EndNamespace }


} // end of namespace
#pragma pack(pop)
