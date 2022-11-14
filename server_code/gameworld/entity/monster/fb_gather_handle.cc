#include "StdAfx.h"
#include "monster_config.h"
#include "gather_monster.h"
#include "fb_gather_handle.h"
#include "role/role_system.h"
#include "actor/actor.h"

FbGatherHandle::FbGatherHandle(void) {
}

FbGatherHandle::~FbGatherHandle(){
}

void FbGatherHandle::ReSet(void) {
}

void FbGatherHandle::Init(void) {
}

bool FbGatherHandle::BeginGather(Actor* actor) {
	auto monster = GetGatherMonster();
	if (!monster) return false;
	auto fb = actor->GetFuBen();
	if (!fb || !fb->IsFb()) return false;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << fb->GetHandle();
	arg << monster;
	arg << actor;
	if (!luaScript.Call("onInstanceGatherStart", &arg, &arg, 1)) return false;
	return ((bool)arg[0]);
}

void FbGatherHandle::EndGather( bool succeed) {
	auto monster = GetGatherMonster();
	if (!monster) return;
	auto actor = monster->GetGatherActor();
	if (!actor) return;
	auto fb = actor->GetFuBen();
	if (!fb || !fb->IsFb()) return;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << fb->GetHandle();
	arg << monster;
	arg << actor;
	arg << succeed;
	luaScript.Call("onInstanceGatherFinished", &arg, &arg, 0);
}


void FbGatherHandle::OnChangeHp(double& value, Role* role) {
}


void FbGatherHandle::OnWaitTimeTimeOut(void) {
}


void FbGatherHandle::LogicRun(int64_t curr_t) {

}
