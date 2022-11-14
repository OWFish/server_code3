#pragma once
#include "proto_common.h"

#define ProtoCMD(name, cmd) ProtoDef(name, CMD_Bag, cmd)
#pragma  pack(push, 1)
namespace Protocol {

	ProtoCMD(BagInitProto, sBagCmd_InitData)
		uint8_t init_index;
		uint8_t bag_type;
		int   item_count;
		/*ItemData items[item_count];*/
	};

	ProtoCMD(BagUpdateCapacityProto, sBagCmd_UpdateCapacity)
		int grid;
	};

	ProtoCMD(BagDeleteItemProto, sBagCmd_DeleteItem)
		uint8_t bag_type;
		int64_t uid;
	};

	ProtoCMD(BagAddItemProto, sBagCmd_AddItem)
		uint8_t bag_type;
		ItemData item;
		uint8_t show_tip;
	};

	ProtoCMD(BagUpdateItemProto, sBagCmd_UpdateItem)
		uint8_t bag_type;
		int64_t uid;
		int     count;
		uint8_t show_tip;
	};
};
#pragma  pack(pop)

#undef ProtoCMD