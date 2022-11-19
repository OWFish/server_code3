#pragma once
#include "proto_common.h"

#define ProtoCMD(name, cmd) ProtoDef(name, CMD_Guild, cmd)

#pragma  pack(push, 1)
//namespace Protocol {
//	ProtoCMD(GuildLogListProto, sGuildCmd_GuildLogList)
//		uint8_t type_;
//		uint32_t time_;
//		int param1_;
//		int param2_;
//		int param3_;
//	};
//};

#pragma  pack(pop)

#undef ProtoCMD

