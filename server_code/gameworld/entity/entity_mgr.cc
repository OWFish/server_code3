#include "StdAfx.h"

#include "actor/actor.h"
#ifdef _MSC_VER
#pragma message("整理 entity_mgr.cc")
#endif
//todo delete row below
#include "role/role_system.h"
#include "role/role.h"
#include "role/role_clone.h"

using namespace InterSrvComm::DbServerProto;
using namespace InterSrvComm::CenterProto;

template<>
EntityPtrList::LinkNodeMgr* EntityPtrList::node_pool_ = NULL;

EntityMgr::EntityMgr() : SendPacketPool("EntityMgr")
, actor_mgr_(("ActorHdlMgr"), 4)
, role_mgr_(("RoleHdlMgr"), 4, 8)
, monster_mgr_(("MonsterHdlMgr"), 4, 8)
, npc_mgr_(("NpcHdlMgr"), 1, 8)
//, moving_npc_mgr_(("MovingNPcHdlMgr"), 1)
, script_npc_mgr_(("ScriptNPcHdlMgr"), 1)
, gather_mgr_(("GatherMonsterMgr"), 4, 8)
//, transfer_mgr_(("TransferHdlMgr"), 1)
//, gather_mgr_(("GatherHdlMgr"), 1, 10)
, dropbag_mgr_("DropBagMgr")
, role_clone_mgr_(("RoleCloneMgr"), 4, 8)
, image_actor_count_(0)
{
}

Entity* EntityMgr::GetEntity(const EntityHandle& handle)
{
	if (handle == NULL)
		return NULL;

	Entity* entity = NULL;

	switch (handle.GetType())
	{
	case EntityType_Actor:
		entity = (Entity*)actor_mgr_.entity_mgr_.GetPtr(handle);
		break;

	case EntityType_Monster:
		entity = (Entity*)monster_mgr_.entity_mgr_.GetPtr(handle);
		break;

	case EntityType_Role:
		entity = (Entity*)role_mgr_.entity_mgr_.GetPtr(handle);
		break;

	case EntityType_Npc:	//todo 整理npc 变成纯脚本
		//entity = (Entity*)npc_mgr_.entity_mgr_.GetPtr(handle);
		entity = (Entity*)script_npc_mgr_.entity_mgr_.GetPtr(handle);
		break;
	case  EntityType_CloneRole:
		entity = (Entity*)role_clone_mgr_.entity_mgr_.GetPtr(handle);
		break;
	case  EntityType_GatherMonster:
		entity = (Entity*)gather_mgr_.entity_mgr_.GetPtr(handle);
		break;

	//case enMovingNPC:
	//	//entity = (Entity*)moving_npc_mgr_.entity_mgr_.GetPtr(handle);
	//	break;

	//case EntityType_Npc:
	//	entity = (Entity*)script_npc_mgr_.entity_mgr_.GetPtr(handle);
	//	break;

	//case enTransfer:
	//	//entity = (Entity*)transfer_mgr_.entity_mgr_.GetPtr(handle);
	//	break;

	//case enGatherMonster:
	//	entity = (Entity*)gather_mgr_.entity_mgr_.GetPtr(handle);
	//	break;

	case EntityType_DropBag:
		entity = (Entity*)dropbag_mgr_.entity_mgr_.GetPtr(handle);
		break;
	default:
		OutputMsg(rmError, "GetEntity type error : %d", handle.GetType());
		break;
	}

	return entity;
}


void EntityMgr::RunOne()
{

#ifdef _USE_TRY_CATCH

	__try
#endif
	{
		int64_t now_tick = GameEngine::game_tick_;

		//加入临时列表, 删除实体时有可能操作wait_remove_list_
		int count = wait_remove_list_.count();

		for (int i = 0; i < count; i++)
		{
			DestroyEntity(wait_remove_list_[i]);
		}
		wait_remove_list_.remove(0, count);

		//超时就退出
		actor_mgr_.Run(now_tick);

		role_mgr_.Run(now_tick);

		monster_mgr_.Run(now_tick);

		//gather_mgr_.Run(now_tick);

		npc_mgr_.Run(now_tick);

		dropbag_mgr_.Run(now_tick);

		script_npc_mgr_.Run(now_tick);

		role_clone_mgr_.Run(now_tick);

		gather_mgr_.Run(now_tick);
	}

#ifdef _USE_TRY_CATCH

	__except (CustomExceptHandler(GetExceptionInformation()))
	{
	}

#endif
}

Entity* EntityMgr::CreateEntity(int entityType, EntityHandle& handle)
{
	STATIC_ASSERT(sizeof(EntityHandle) == 8);
	Entity* et = NULL;

	switch (entityType)
	{
	case EntityType_Actor:
		et = (Entity*)actor_mgr_.entity_mgr_.AllocHandle(handle);
		break;

	case EntityType_Monster:
		et = (Entity*)monster_mgr_.entity_mgr_.AllocHandle(handle);
		break;

	case EntityType_Role:
		et = (Entity*)role_mgr_.entity_mgr_.AllocHandle(handle);
		break;

	case EntityType_CloneRole:
		et = (Entity*)role_clone_mgr_.entity_mgr_.AllocHandle(handle);
		break;
	case EntityType_GatherMonster:
		et = (Entity*)gather_mgr_.entity_mgr_.AllocHandle(handle);
		break;
	//case EntityType_Npc:
	//	et = (Entity*)npc_mgr_.entity_mgr_.AllocHandle(handle);
	//	break;

	//case enMovingNPC:
	//	//et = (Entity*)moving_npc_mgr_.entity_mgr_.AllocHandle(handle);
	//	break;

	case EntityType_Npc:
		et = script_npc_mgr_.entity_mgr_.AllocHandle(handle);
		break;

	//case enTransfer: //传送门
	//	//et = (Entity*)transfer_mgr_.entity_mgr_.AllocHandle(handle);
	//	break;

	//case enGatherMonster://采集怪
	//	et = gather_mgr_.entity_mgr_.AllocHandle(handle);
	//	break;

	case EntityType_DropBag:
		et = dropbag_mgr_.entity_mgr_.AllocHandle(handle);
		break;
	}

	if (et)
	{
		handle.SetType(entityType);
		et->SetHandle(handle);

		switch (entityType)
		{
		case EntityType_Actor:
			actor_mgr_.Add(et);
			break;

		case EntityType_Monster:
			monster_mgr_.Add(et);
			break;

		case EntityType_Role:
			role_mgr_.Add(et);
			break;

		//case EntityType_Npc:
		//	npc_mgr_.Add(et);
		//	break;

		//case enMovingNPC:
		//	//moving_npc_mgr_.Add(et);
		//	break;

		case EntityType_Npc:
			script_npc_mgr_.Add(et);
			break;

		case EntityType_CloneRole:
			role_clone_mgr_.Add(et);
			break;
		case EntityType_GatherMonster:
			gather_mgr_.Add(et);
			break;

		//case enTransfer: //传送门
		//	//transfer_mgr_.Add(et);
		//	break;

		//case enGatherMonster://采集怪
		//	gather_mgr_.Add(et);
		//	break;

		case EntityType_DropBag:
			dropbag_mgr_.Add(et);
			break;
		}
	}

	return et;
}

bool EntityMgr::DestroyEntity(EntityHandle handle, bool delay)
{
	if (delay)
	{
		wait_remove_list_.add(handle);
		return true;
	}

	unsigned int type = handle.GetType();
	Entity* entity = GetEntity(handle);

	if (entity)
	{
		Scene* scene = entity->GetScene();
		if (scene != NULL)
			scene->ExitScene(entity);

		entity->OnDestroy();
		entity->SetInitFlag(false);

		switch (type)
		{
		case EntityType_Actor:
			OnActorClosed((Actor*)entity);
			actor_mgr_.Destroy(entity);
			actor_mgr_.entity_mgr_.Free(handle);
			break;

		case EntityType_Monster:
			monster_mgr_.Destroy(entity);
			monster_mgr_.entity_mgr_.Free(handle);
			break;

		case EntityType_Role:
			role_mgr_.Destroy(entity);
			role_mgr_.entity_mgr_.Free(handle);
			break;
		//case EntityType_Npc:
		//	npc_mgr_.Destroy(entity);
		//	npc_mgr_.entity_mgr_.Free(handle);
		//	break;

		//case enMovingNPC:
		//	//moving_npc_mgr_.Destroy(entity);
		//	//moving_npc_mgr_.entity_mgr_.Free(handle);
		//	break;

		case EntityType_Npc:
			script_npc_mgr_.Destroy(entity);
			script_npc_mgr_.entity_mgr_.Free(handle);
			break;


		case EntityType_CloneRole:
			role_clone_mgr_.Destroy(entity);
			role_clone_mgr_.entity_mgr_.Free(handle);
			break;
		case EntityType_GatherMonster:
			gather_mgr_.Destroy(entity);
			gather_mgr_.entity_mgr_.Free(handle);
			break;

		//case enTransfer:
		//	//transfer_mgr_.Destroy(entity);
		//	//transfer_mgr_.entity_mgr_.Free(handle);
		//	break;

		//case enGatherMonster:
		//	gather_mgr_.Destroy(entity);
		//	gather_mgr_.entity_mgr_.Free(handle);
		//	break;

		case EntityType_DropBag:
			dropbag_mgr_.Destroy(entity);
			dropbag_mgr_.entity_mgr_.Free(handle);
			break;
		}
	}

	return entity != NULL;
}

void EntityMgr::OnActorClosed(Actor* actor)
{
	int actor_id = actor->GetActorId();

	EntityHandle* handle = actor_id_table_.get(actor_id);

	if (handle)
		actor_id_table_.remove(actor_id);
	else
		OutputMsg(rmError, ("can't find actor[actorid=%d] in idlist"), actor_id);

	const char* name = actor->GetEntityName();

	if (!name) return;

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);
	handle = actor_name_table_.get(key);

	if (handle)
		actor_name_table_.remove(key);
	else
		OutputMsg(rmError, ("can't find actor[actorid=%d] in namelist"), actor_id);
}

void EntityMgr::OnActorLogin(Actor* actor)
{
	if (!actor) return;

	ActorId actorId = actor->GetActorId();
	EntityHandle handle = actor->GetHandle();

	EntityHandle* handle_ptr = actor_id_table_.get(actorId);

	if (handle_ptr)
	{
		OutputMsg(rmError, "error!! has actor data in hashtable:%d", actorId);
		actor_id_table_.remove(actorId);
	}

	actor_id_table_.put(actorId, handle);
}

void EntityMgr::OnDbReturnData(int cmd, DataPacketReader& reader)
{
	uint8_t err = 0;
	ActorId actorid = 0;
	const size_t minlen = sizeof(ActorId) + sizeof(err);

	if (reader.getAvaliableLength() < minlen) return;

	reader >> actorid >> err;

	Actor* actor = GetActorPtrById(actorid);
	if (!actor) {
		OutputMsg(rmError, "Query actor data Error!!ActorID = %d", actorid);
		return;
	}

	if (err != reSucc) {
		OutputMsg(rmError, "Data Error!!ActorID = %d,errorID=%d,serverid=%d",
		          actorid, err, actor->GetServerId());
		return;
	}

	actor->OnDbReturnData(cmd, reader);
}

bool EntityMgr::Initialize()
{
	UpdateMask::Init();
	//Actor::InitBroadcastMask();
	//Monster::InitBroadcastmask();

	return true;
}

void EntityMgr::Destroy()
{
	actor_mgr_.Empty();
	monster_mgr_.Empty();
	role_mgr_.Empty();
	npc_mgr_.Empty();
	//moving_npc_mgr_.Empty();
	script_npc_mgr_.Empty();
	//transfer_mgr_.Empty();
	//gather_mgr_.Empty();
	dropbag_mgr_.Empty();

	//Actor::DestroyBroadcastMask();
	//Monster::DestroyBroadcastMask();


	role_clone_mgr_.Empty();

	assert(actor_id_table_.count() == 0);
	assert(actor_name_table_.count() == 0);
}

void EntityMgr::CloseAllActor(int gate)
{
	OutputMsg(rmError, "EntityMgr::CloseAllActor, gate=%d", gate);
	EntityPtrList::Iterator it(actor_mgr_.entity_list_);

	for (EntityPtrList::NodeType* node = it.first(); node; node = it.next())
	{
		Entity* entity = *node;

		if (entity && entity->GetType() == EntityType_Actor)
		{
			Actor* actor = (Actor*)entity;

			if (gate == -1 || actor->GetGateIdx() == gate)
				actor->CloseActor("close all"); // 关闭用户
		}
	}
}

void EntityMgr::UpdateMonsterHandle(Entity* et)
{
	if (et && et->IsMonster())
	{
		Monster* monster = static_cast<Monster*>(et);
		int entityType = et->GetType();
		EntityHandle handle = monster->GetHandle();
		bool result = false;

		if (EntityType_Monster == entityType)
		{
			result = monster_mgr_.entity_mgr_.ReNew(handle);
		}
		//else if (enGatherMonster == entityType)
		//{
		//	result = gather_mgr_.entity_mgr_.ReNew(handle);
		//}

		if (!result)
		{
			OutputMsg(rmError, ("update monster handle fail!"));
			return;
		}

		//handle.init(handle.GetType(), index);
		et->SetHandle(handle);
	}
}

Actor* EntityMgr::GetActorPtrById(ActorId aid)
{
	EntityHandle* handle = actor_id_table_.get(aid);

	if (!handle || handle->GetType() != EntityType_Actor)
		return NULL;

	return (Actor*)GetEntity(*handle);
}

Actor* EntityMgr::GetActorPtrByName(const char* name)
{
	if (!name) return NULL;

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);
	EntityHandle* handle = actor_name_table_.get(key);

	if (!handle || handle->GetType() != EntityType_Actor)
		return NULL;

	Actor* actor = (Actor*)GetEntity(*handle);
	if (actor && actor->IsInited())
		return actor;
	return NULL;
}

void EntityMgr::AddToNameList(Actor* actor)
{
	if (!actor) return;

	const char* name = actor->GetEntityName();

	if (!name) return;

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);

	EntityHandle* handle_ptr = actor_name_table_.get(key);

	if (handle_ptr)
	{
		OutputMsg(rmError, "error!! has actor data in name hashtable:%d", actor->GetActorId());
		actor_name_table_.remove(key);
	}

	EntityHandle handle = actor->GetHandle();
	actor_name_table_.put(key, handle);
}

Actor* EntityMgr::GetActorPtrByAccount(const char* name)
{
	if (!name) return NULL;

	EntityPtrList::Iterator it(actor_mgr_.entity_list_);

	for (EntityPtrList::NodeType* node = it.first(); node; node = it.next())
	{
		Entity* entity = *node;
		Actor* actor = (Actor*)entity;

		if (actor && strcmp(actor->GetAccount(), name) == 0)
		{
			return actor;
		}
	}

	return NULL;
}

void EntityMgr::GetOnlineActorIdToPack(DataPacket& pack)
{
	pack << (int)GetOnlineActorCount();

	EntityPtrList::Iterator it(actor_mgr_.entity_list_);

	for (EntityPtrList::NodeType* node = it.first(); node; node = it.next())
	{
		Entity* entity = *node;
		Actor* actor = (Actor*)entity;
		if (actor && actor->IsInited() && !actor->IsImage())
			pack << (ActorId)(actor->GetActorId());
	}
}

int EntityMgr::GetOnlineActorPtrList(void** actorList, int max_count)
{
	int count = 0;
	EntityPtrList::Iterator it(actor_mgr_.entity_list_);

	for (EntityPtrList::NodeType* pNode = it.first(); pNode && count < max_count; pNode = it.next())
	{
		Entity* entity = *pNode;
		Actor* actor = (Actor*)entity;
		if (actor && actor->IsInited() && !actor->IsImage())
		actorList[count++] = actor;
	}

	return count;
}

void EntityMgr::SendActorOnline(int actorid, uint8_t status, int serverid)
{
	/*static CenterClient* cli = ServerInstance()->GetCenterClient();
	DataPacket& p = cli->allocProtoPacket(cwActorOnline);

	ActorOnline data;
	data.actorid_ = actorid;
	data.sid_ = ServerInstance()->GetServerIndex();

	p << (int)serverid;
	p << (uint8_t)status;
	p.writeBuf(&data, sizeof(data));
	cli->flushProtoPacket(p);
	*/
}


void EntityMgr::OnSsReturnData(int cmd, DataPacketReader& reader)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	uint8_t err = 0;
	ActorId actorid = 0;
	const size_t minlen = sizeof(ActorId) + sizeof(err);

	if (reader.getAvaliableLength() < minlen) return;

	const char* ptr = reader.getOffsetPtr();
	actorid = *((ActorId*)ptr);
	ptr += sizeof(ActorId);
	err = ptr[0];

	reader.adjustOffset(minlen);

	if (actorid == 0)
	{
		OutputMsg(rmError, "OnSsReturnData Error!!ActorID = %d", actorid);
		return; //数据格式错误
	}

	Actor* actor = em->GetActorPtrById(actorid);

	if (!actor) return;

	// 查询数据不成功
	if (err != reSucc)
	{
		OutputMsg(rmError, " session Data Error!!ActorID = %d,cmd=%d, errorID=%d", actorid, cmd, err);
	}

	//todo 暂时还没有的功能
	//switch (cmd)
	//{
	//case sAddValueCard:
	//case sQueryAddValueCard:
	//	{
	//		actor->GetBagSystem().OnSsRetData(cmd, err, reader);
	//		break;
	//	}

	//case sUpdateIdentity:
	//	{
	//		int update_ret = 0;
	//		reader >> update_ret;
	//		actor->GetMiscSystem().OnSaveIdentityRet(update_ret);
	//		break;
	//	}

	//case sChargeToken:
	//	{
	//		const char* token;
	//		const char* url_param;
	//		int ret = 0;
	//		reader >> ret >> token >> url_param;
	//		// 返回给客户端
	//		actor->GetChargeSys().SendChargeToken(ret, token, url_param);
	//		break;
	//	}

	//case sGetToken:
	//	{
	//		const char* token;
	//		int ret = 0;
	//		reader >> ret >> token;
	//		// 返回给客户端
	//		actor->GetChargeSys().SendToken(ret, token);
	//		break;
	//	}
	//}
}

void EntityMgr::OnActorChangeName(Actor* actor, const char* lastName)
{
	if (actor == NULL || lastName == NULL)
	{
		return;
	}
	int actor_id = actor->GetActorId();
	EntityHandle* handle_ptr = actor_id_table_.get(actor_id);

	if (handle_ptr == NULL)
		OutputMsg(rmError, ("can't find actor[actorid=%d] in idlist"), actor_id);

	const char* name = actor->GetEntityName();
	if (!name) return;

	unsigned int h1 = bzhashstr(lastName, 1);
	unsigned int h2 = bzhashstr(lastName, 2);
	int64_t key = MAKEINT64(h1, h2);
	handle_ptr = actor_name_table_.get(key);

	if (handle_ptr)
		actor_name_table_.remove(key);
	else
		OutputMsg(rmError, ("can't find actor[actorid=%d] in namelist"), actor_id);

	h1 = bzhashstr(name, 1);
	h2 = bzhashstr(name, 2);
	key = MAKEINT64(h1, h2);

	handle_ptr = actor_name_table_.get(key);

	if (handle_ptr)
	{
		OutputMsg(rmError, "error!! has actor data in name hashtable");
		actor_name_table_.remove(key);
	}

	EntityHandle handle = actor->GetHandle();
	actor_name_table_.put(key, handle);
}




