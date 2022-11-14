#pragma once
#include "proto_common.h"

#define ProtoCMD(name, cmd) ProtoDef(name, CMD_Equip, cmd)
#pragma  pack(push, 1)
namespace Protocol {
	ProtoCMD(EquipItemProto, sEquipCmd_EquipItem)
		int equiptype;
		short slot;
		ItemData equip_data;
	};

	ProtoCMD(EquipSmeltProto, sEquipCmd_EquipSmelt)
		int result;
		int goldNum;
		int itemCount;
	// {{itemId,num},...}
	};

	ProtoCMD(EquipLevelupProto, sEquipCmd_Levelup)
		short roleId;
		int result;
		int itemId;
	};

	ProtoCMD(EquipComposeProto, sEquipCmd_Compose)
		short roleId;
		int result;
		int itemId;
	};
};
#pragma  pack(pop)

#undef ProtoCMD