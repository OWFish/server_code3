#include "StdAfx.h"
#include "actor_ex_ring_system.h"
#include "role/role_system.h"
#include "monster/monster.h"
#include "ai/ai.h"


ActorExRingSystem::ActorExRingSystem(Actor* actor)
:actor_(actor)
{
	monster_attr.clear();
	monster_ex_attr.clear();
	battle_ring_.clear();
}


ActorExRingSystem::~ActorExRingSystem()
{
}

bool ActorExRingSystem::Init()
{
	ScriptValueList arg;
	arg << actor_;
	arg << true;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	if (!luaScript.Call("calcActorExRingAttr", &arg, &arg, 1))
		return false;
	return (bool)arg[0];
}

void ActorExRingSystem::OnExitScene()
{
	DestroyBattleRingAll();
}

void ActorExRingSystem::OnEnterScene()
{
	ReCreateAllRing();
}

void ActorExRingSystem::OnAllRoleDie() {
	DestroyBattleRingAll();
}

void ActorExRingSystem::OnRelive() {
	ReCreateAllRing();
}

void ActorExRingSystem::ReCreateAllRing() {
	DestroyBattleRingAll();
	if (actor_->GetFuBen()->GetFbId() == 0) {
		return;
	}
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	for (int rid = 0; rid < ActorExRingType_MAX; ++rid) {
		ScriptValueList arg;
		arg << actor_;
		arg << rid;
		luaScript.Call("createActorExRingMonster", &arg, &arg, 1);
	}
}

void ActorExRingSystem::CreateCloneExRingMonster(unsigned int scene, int x, int y, RoleClone* clone)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << actor_;
	arg << scene;
	arg << x;
	arg << y;
	arg << clone;
	luaScript.Call("createCloneActorExRingMonster", &arg, &arg, 1);
}

Monster* ActorExRingSystem::CreateExRingMonster(int rid, int id)
{
	if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
	if (!actor_) return NULL;
	if (!id) return NULL;
	BattleExRingMap::iterator it = battle_ring_.find(rid);
	if (it != battle_ring_.end()) {
		auto mon = it->second;
		battle_ring_.erase(it);
		if (mon) {
			GetGameEngine()->GetEntityMgr()->DestroyEntity(mon->GetHandle());
		}
	}

	EntityHandle hdl;
	Monster* br = (Monster*)GetGameEngine()->GetEntityMgr()->CreateEntity(EntityType_Monster, hdl);

	if (br != NULL)
	{
		if (!br->Init(id))
		{
			GetGameEngine()->GetEntityMgr()->DestroyEntity(hdl);
			OutputMsg(rmError, "Init battle_ring_[%d] error.id:%d",rid,id);
			br = NULL;
			return NULL;
		}
		br->SetMasterHandle(actor_->GetHandle());

		Grid pos = actor_->GetPosition();
		pos.x += short(wrand(2) - 1);
		pos.y += short(wrand(2) - 1);
		actor_->GetScene()->EnterScene(br, pos.x, pos.y);

		br->SetCamp(actor_->GetCamp());	//这个一定要放在进入场景后面,进入场景时会重置为默认的
	}
	battle_ring_[rid] = br;
	return br;
}

void ActorExRingSystem::DestroyBattleRing(int rid) {
	if (rid < 0 || rid >= ActorExRingType_MAX) return;
	BattleExRingMap::iterator it = battle_ring_.find(rid);
	if(it != battle_ring_.end()){
		auto mon = it->second;
		battle_ring_.erase(it);//先删后回收实体
		if (mon) {
			GetGameEngine()->GetEntityMgr()->DestroyEntity(mon->GetHandle());
		}
	}
}

void ActorExRingSystem::stopAllExringAi() {
	for (BattleExRingMap::iterator it = battle_ring_.begin(); it != battle_ring_.end(); ++it) {
		if (it->second) {
			if ((it->second)->GetAI()) {
				(it->second)->GetAI()->setPassivity(true);
			}
			(it->second)->SetTarget(NULL);
		}
	}
}

void ActorExRingSystem::SetCamp(int camp) {
	for (BattleExRingMap::iterator it = battle_ring_.begin(); it != battle_ring_.end(); ++it) {
		if (it->second) {
			(it->second)->SetCamp(camp);
		}
	}
}

void ActorExRingSystem::setCanChangeCamp(bool canChg) {
	for (BattleExRingMap::iterator it = battle_ring_.begin(); it != battle_ring_.end(); ++it) {
		if (it->second) {
			(it->second)->setCanChangeCamp(canChg);
		}
	}
}

void ActorExRingSystem::DestroyBattleRingAll() {
	//std::vector<Monster*> destroy_list; destroy_list.clear();
	//destroy_list.insert(battle_ring_.begin(), battle_ring_.end());
	for (BattleExRingMap::iterator it = battle_ring_.begin(); it != battle_ring_.end();) {
		auto mon = it->second;
		it = battle_ring_.erase(it);
		if (mon) {
			GetGameEngine()->GetEntityMgr()->DestroyEntity(mon->GetHandle());
			//destroy_list.push_back();
		}
	}
	//battle_ring_.clear();
}

Attribute* ActorExRingSystem::GetMonsterAttr(int rid) {
	if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
	return &(monster_attr[rid]);
}
ExAttribute* ActorExRingSystem::GetMonsterExAttr(int rid) {
	if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
	return &(monster_ex_attr[rid]);
}

