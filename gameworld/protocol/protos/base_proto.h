#pragma  once
#include "proto_common.h"
#include "db/role_data.h"
#include "attr/attribute.h"


#define ProtoCMD(name,cmd) ProtoDef(name, CMD_Base, cmd)
#pragma pack (push, 1)

StartNameSpace

ProtoCMD(ActorProto, sBaseCmd_ActorBaseData)
int64_t handle;
int actor_id;
int server_id;
ACTORNAME name;
int level;
int exp;
double power;
int64_t gold;
int64_t yb;
int vip;
int64_t soul;
int grid;
int64_t feats;
int64_t shatter;
int64_t spcshatter;
int64_t togeatter;
int64_t togeatterhigh;
int prestigeexp;
int headID;
};

ProtoCMD(RoleProto, sBaseCmd_RoleData)
int role_count;
struct {
	RoleData roledata;
	int title;
	short attrs_count;
	int attrs[Attribute::atCount];
	int power;
} roles[3];
};

ProtoCMD(EnterSceneProto, sBaseCmd_EnterScene)
int fb_id;
int scene_id;
short x;
short y;
char fb_type;
//string name;
//string desc;
};

ProtoCMD(EntityAppearProto, sBaseCmd_OtherEntity)
short type;
int64_t hdl;
int id;
int64_t master_hdl;
int x;
int y;
int headimageid;
//int attrs[Attribute::atCount];(creature)
//DisplayData (role)
};

ProtoCMD(RoleAttributeProto, sBaseCmd_UpdateRoleAttribute)
int role_id;
short count_ver;
double attrs[Attribute::atCount];
double power;
};

ProtoCMD(RoleExAttributeProto, sBaseCmd_UpdateRoleExAttribute)
int role_id;
short count_ver;
int attrs[ExAttribute::eatCount];
};

ProtoCMD(UpdateHpProto, sBaseCmd_UpdateHp)
int64_t handle;
double hp;
};

ProtoCMD(NotifyFlyHpProto, sBaseCmd_NotifyFlyHp)
int64_t thandle;
int64_t shandle;
double damage;
uint32_t hit_type;
};

ProtoCMD(UpdateMoneyProto, sBaseCmd_UpdateMoney)
short type;
int64_t current;
};

ProtoCMD(EntityDisappearProto, sBaseCmd_EntityDisapear)
int64_t handle;
};

ProtoCMD(EntityMoveProto, sBaseCmd_EntityMove)
int64_t handle;
int tar_x;
int tar_y;
int cur_x;
int cur_y;
};
ProtoCMD(EntityStopProto, sBaseCmd_EntityStop)
int64_t handle;
int x;
int y;
};
ProtoCMD(EntitySpectialMoveProto, sBaseCmd_EntitySpecialMove)
int64_t handle;
short type;
int x;
int y;
int mtime;
};
ProtoCMD(SyncTimeProto, sBaseCmd_SyncTime)
unsigned int time;
};
ProtoCMD(UpdateMpProto, sBaseCmd_UpdateMp)
int64_t handle;
double mp;
//bool need_display;
};

ProtoCMD(UpdateNpProto, sBaseCmd_UpdateNp)
int64_t handle;
double np;
//bool need_display;
};

ProtoCMD(ServerTipsProto, sBaseCmd_ServerTips)
int tipId;
};

ProtoCMD(ActorDieProto, sBaseCmd_ActorDie)
};

ProtoCMD(ActorGuildProto, sBaseCmd_GuildInfo)
int guildId;
};

ProtoCMD(BubbleTextProto, sBaseCmd_BubbleText)
int64_t target_handle;
int id;
};

ProtoCMD(FloatTextProto, sBaseCmd_FloatText)
int id;
};

ProtoCMD(FubenMoveLineProto, sBaseCmd_GetFubenMoveLine)
int64_t handle;
int self_x;
int self_y;
int target_x;
int target_y;
};

ProtoCMD(SwitchTargetProto, sBaseCmd_SwitchTarget)
	int64_t src_handle;
	int64_t tar_handle;
};

ProtoCMD(SwitchCampProto, sBaseCmd_SwitchCamp)
int64_t src_handle;
int camp;
};

ProtoCMD(EntityUpdateAttrProto, sBaseCmd_UpdateAttr)
int64_t handle;
short count;
int type;
double value;
};

EndNamespace
#pragma pack(pop)


#undef ProtoCMD
