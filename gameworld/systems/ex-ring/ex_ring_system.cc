#include "StdAfx.h"
#include "ex_ring_system.h"
#include "db/role_data.h"


ExRingSystem::ExRingSystem(Role *role)
: role_(role)
{
	attribute_.Reset();
	ex_attr_.Reset();
}

ExRingSystem::~ExRingSystem()
{

}

void ExRingSystem::Destroy()
{
}

bool ExRingSystem::Init(RoleData *data)
{
	if (data == NULL)
		return false;
	data_ = &data->ex_rings;

	ScriptValueList arg;
	arg << role_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	if (!luaScript.Call("calcExRingAttr", &arg, &arg, 1))
		return false;
	return (bool)arg[0];
}

int ExRingSystem::GetLevel(int id)
{
	if (id < 0 || id >= ExRingType_MAX)
		return 0;

	return data_->ring_level[id];
}

void ExRingSystem::SetLevel(int id, int level)
{
	if (id < 0 || id >= ExRingType_MAX)
		return;
	data_->ring_level[id] = level;
}
