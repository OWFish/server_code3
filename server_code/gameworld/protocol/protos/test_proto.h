#pragma  once
#include "proto_common.h"
#include "system_cmd_def.h"
#include <vector>

#define ProtoCMD(name,cmd) ProtoDef(name, CMD_Base, cmd)
#pragma pack (push, 1)


//tolua_begin
namespace Protocol {

struct TestProto :public BaseProto {
	TestProto() :BaseProto(255, 255){}
	int a;
};
	
struct Test{
	int a;
	int b;
};



}
#pragma pack(pop)
//tolua_end


#undef ProtoCMD
