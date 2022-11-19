#pragma once
#include "proto_common.h"
#include "system_cmd_def.h"

#define ProtoCMD(name, cmd) ProtoDef(name, CMD_Ranking, cmd)
#pragma pack(push, 1)
namespace Protocol 
{
	ProtoCMD(RankDataProto, sRankingCmd_ResRankingData)
		short	rank_type;
		short	rank_size;
	};
}
#pragma  pack(pop)

#undef ProtoCMD