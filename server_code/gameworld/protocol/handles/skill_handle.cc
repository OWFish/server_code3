#include "StdAfx.h"
#include "net_handle_base.h"

#include "entity/entity_mgr.h"
#include "entity/creature.h"
#include "protocol/protos/skill_proto.h"
#include "entity/actor/actor.h"
#include "data_packet.hpp"
#include "entity/role/role.h"
#include "skill/skill_system.h"


void OnCastSkill(Actor* actor, DataPacketReader& pack)
{
	int64_t src_hdl;
	int64_t tar_hdl;
	int id;
	pack >> src_hdl >> tar_hdl >> id;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Entity* et = em->GetEntity(src_hdl);
	if (!et) return;
	if (et->GetType() != EntityType_Role || et->GetMaster() != actor)
		return;

	((Role*)et)->GetSkillSystem()->OnCastSkill(id, em->GetEntity(tar_hdl));

	return;
}


void NetHandle::RegSkillCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Skill, Protocol::cSkillCmd_CastSkill, OnCastSkill);
}