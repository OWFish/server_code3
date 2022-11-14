#pragma  once
#include "proto_common.h"
#include "system_cmd_def.h"

#define ProtoCMD(name,cmd) ProtoDef(name, CMD_ZhanLing, cmd)
#pragma pack (push, 1)

StartNameSpace

ProtoCMD(ShowZhanLingProto, sZhanLingCmd_ShowZhanLing)
int64_t handle;
int level;
char id;
};

ProtoCMD(ShowTalentProto, sZhanLingCmd_ShowTalent)
};

EndNamespace
#pragma pack(pop)


#undef ProtoCMD
