#include "StdAfx.h"
#include "title_system.h"
#include "db/actor_db_data.h"
#include "role/role_system.h"


TitleSystem::TitleSystem(Actor *actor)
	: actor_(actor)
{
	attribute_.Reset();
	memset(roleTitle, 0, sizeof(int)*MAX_ROLE);
}

TitleSystem::~TitleSystem()
{

}

bool TitleSystem::Init()
{
	ScriptValueList arg;
	arg << actor_->GetActor();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("titleAttrInit", &arg, &arg, 0);

	return true;
}

void TitleSystem::Save()
{

}

void TitleSystem::Destroy()
{
}

//void TitleSystem::CalcAttribute()
//{
//	if (actor_ == NULL)
//	{
//		return;
//	}
//	Role* list[MAX_ROLE] = { NULL };
//	actor_->GetRoleSystem()->GetRoles(list);
//
//	for (int i = 0; i < MAX_ROLE; ++i)
//	{
//		Role* role = list[i];
//		if (!role) break;
//		role->CalcAttributes();
//	}
//
//}

void TitleSystem::OnTimeCheck(int64_t curr_t)
{
	ScriptValueList arg;
	arg << actor_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onTitleRun", &arg, &arg, 0);
}

void TitleSystem::setRoleTitle(int roleId, int tId)
{
	if (roleId < 0 || roleId >= MAX_ROLE)
	{
		return;
	}
	roleTitle[roleId] = tId;
}

int TitleSystem::getRoleTitle(int roleId)
{
	if (roleId < 0 || roleId >= MAX_ROLE)
	{
		return 0;
	}
	return roleTitle[roleId];
}


