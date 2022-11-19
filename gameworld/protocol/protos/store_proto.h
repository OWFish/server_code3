#pragma once
#include "proto_common.h"


#define ProtoCMD(name,cmd) ProtoDef(name, CMD_Store, cmd)
#pragma pack(push, 1)
namespace Protocol {

	ProtoCMD(StoreDataProto, sStoreCmd_DataSync)
	int refresh_cd;
	int refresh_integra;
	int refreshCount;
	int data_num;
	/*
	struct StoreItemData *affect_info;
	*/
};

}
#pragma pack(pop)

#undef ProtoCMD