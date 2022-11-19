#pragma once
#include "proto_common.h"

#define ProtoCMD(name, cmd) ProtoDef(name, CMD_Wing, cmd)
#pragma  pack(push, 1)
namespace Protocol {
	ProtoCMD(WingInfoProto, sWingCmd_InitData)
		short role_id;
		WingsData wing_data;
		//WingsEquip wing_equip;
	};
	ProtoCMD(WingItemProto, sWingCmd_EquipItem)
		short role_id;
		short slot;
		ItemData equip_data;
	};
};
#pragma  pack(pop)

#undef ProtoCMD
