#include "StdAfx.h"
#include "zhuansheng_system.h"
#include "db/actor_db_data.h"


ZhuanShengSystem::ZhuanShengSystem(Actor *actor)
: actor_(actor)
{
	attribute_.Reset();
}

ZhuanShengSystem::~ZhuanShengSystem()
{

}

void ZhuanShengSystem::Destroy()
{
}

bool ZhuanShengSystem::Init()
{
	ScriptValueList arg;
	arg << actor_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	if (!luaScript.Call("calcZhuanShengAttr", &arg, &arg, 1))
		return false;
	return (bool)arg[0];
}

