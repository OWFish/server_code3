#pragma once
#include "proto_common.h"
#include "togetherhit/together_hit_system.h"

#define ProtoCMD(name,cmd) ProtoDef(name, CMD_Skill, cmd)
#pragma pack(push, 1)
namespace Protocol {

ProtoCMD(CastSkillProto, sSkillCmd_CastSkill)
	int64_t caster_handle;
	int		id;
	int64_t target_handle;
	short count;
	/*struct {
		int64_t  affect_handle;
		uint8_t  hit_type;
		int		 damage;
	} *affect_info;
	*/
};

ProtoCMD(AppendSkillEffectProto, sSkillCmd_AppendSkillEffect)
	int64_t target_handle;
	int id;
};

ProtoCMD(RemoveSkillEffectProto, sSkillCmd_RemoveSkillEffect)
	int64_t target_handle;
	int id;
};

ProtoCMD(AddEffectProto, sSkillCmd_AddEffect)
int64_t target_handle;
int id;
};

ProtoCMD(DelEffectProto, sSkillCmd_DelEffect)
int64_t target_handle;
int id;
};

ProtoCMD(TogetherHitEquipProto, sSkillCmd_TogetherHitEquip)
ItemData equip[TogetherHitSlotType_Max];
};

ProtoCMD(TogetherHitEquipItemProto, sSkillCmd_TogetherHitEquipItem)
short slot;
ItemData equip;
};

};

#pragma pack(pop)

#undef ProtoCMD