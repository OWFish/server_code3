#include "StdAfx.h"
#include "monster_config.h"
#include "actor/actor.h"
#include "gather_monster.h"
#include "flags_handle.h"
#include "role/role_system.h"
#include "skill/status_system.h"
#include "guild/guild_system.h"

FlagsHandle::FlagsHandle(void)
{

}

FlagsHandle::~FlagsHandle()
{

}
void FlagsHandle::ReSet(void)
{
	auto monster = GetGatherMonster();
	shield = monster->GetConfig()->shield;
	if (failure_)
	{
		failure_wait_tick_ = 10 * 1000;
		failure_wait_tick_ += ServerInstance()->Engine()->getTickCount();
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		ScriptValueList arg;

		arg.clear();
		arg << 0;
		luaScript.Call("setGuildBattleFlagsStatus", &arg, &arg, 0);

		arg.clear();
		arg << (double)failure_wait_tick_;
		luaScript.Call("setGuildBattleFlagsWaitTick", &arg, &arg, 0);

		arg.clear();
		luaScript.Call("broadcastGuildBattleFlagsData", &arg, &arg, 0);
	}
}

void FlagsHandle::Init(void)
{
	auto monster = GetGatherMonster();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;

	arg.clear();
	arg << 0;
	luaScript.Call("setGuildBattleFlagsStatus", &arg, &arg, 0);

	arg.clear();
	arg << (double)monster->GetWaitGatherTime();
	luaScript.Call("setGuildBattleFlagsWaitTick", &arg, &arg, 0);

	arg.clear();
	luaScript.Call("broadcastGuildBattleFlagsData", &arg, &arg, 0);
	ReSet();
}

bool FlagsHandle::BeginGather(Actor* actor)
{
	if (failure_)
	{
		return false;
	}
	auto monster = GetGatherMonster();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;

	arg.clear();
	arg << 2;
	luaScript.Call("setGuildBattleFlagsStatus", &arg, &arg, 0);

	arg.clear();
	arg << actor->GetActorName();
	luaScript.Call("setGuildBattleFlagsGatherersName", &arg, &arg, 0);

	arg.clear();
	arg << actor->GetGuildSystem()->GetGuildName();
	luaScript.Call("setGuildBattleFlagsGatherersGuild", &arg, &arg, 0);
	
	arg.clear();
	arg << actor->GetActorId();
	luaScript.Call("setGuildBattleFlagsGatherersActorId", &arg, &arg, 0);

	arg.clear();
	arg << (double)monster->GetGatherTime();
	luaScript.Call("setGuildBattleFlagsGatherTick", &arg, &arg, 0);

	arg.clear();
	luaScript.Call("broadcastGuildBattleFlagsData", &arg, &arg, 0);

	arg.clear();
	luaScript.Call("guildBattleCurrGatherFlagsNotice", &arg, &arg, 0);

	auto config = monster->GetConfig();
	arg.clear();
	arg << (int)shield;
	arg << (int)config->shield;
	luaScript.Call("broadcastGuildBattleShield", &arg, &arg, 0);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		auto role = actor->GetRoleSystem()->GetRoleById(i);
		if (!role)
		{
			continue;
		}
		Status status;
		status.param.highest_hurt = 2000;
		status.end_time = monster->GetGatherTime();
		status.type = StatusType_HighestHurt; 
		role->GetStatusSystem()->AddStatus(status);
		if (role->GetBattlePet())
		{
			role->GetBattlePet()->GetStatusSystem()->AddStatus(status);
		}

		status.param.highest_hurt = 0;
		status.end_time = monster->GetGatherTime();
		status.type = StatusType_Armor; // 不可被位移
		role->GetStatusSystem()->AddStatus(status);
		if (role->GetBattlePet())
		{
			role->GetBattlePet()->GetStatusSystem()->AddStatus(status);
		}
	}

	return true;
	
	
}

void FlagsHandle::EndGather( bool succeed)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	auto monster = GetGatherMonster();
	auto actor = monster->GetGatherActor();
	if(succeed)
	{
		arg.clear();
		arg <<(void*)actor;
		monster->ClearGatherActor(); //  警告          先清空actor不然会段错误
		luaScript.Call("setGuildBattleWinGuild", &arg, &arg, 0);
	}
	if (!succeed)
	{
		failure_ = true;
	}
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		auto role = actor->GetRoleSystem()->GetRoleById(i);
		if (!role)
		{
			continue;
		}
		role->GetStatusSystem()->DelStatus(StatusType_HighestHurt);
		if (role->GetBattlePet())
		{
			role->GetBattlePet()->GetStatusSystem()->DelStatus(StatusType_HighestHurt);
		}

		role->GetStatusSystem()->DelStatus(StatusType_Armor);
		if (role->GetBattlePet())
		{
			role->GetBattlePet()->GetStatusSystem()->DelStatus(StatusType_Armor);
		}
	}

	arg.clear();
	arg << 1;
	luaScript.Call("setGuildBattleFlagsStatus", &arg, &arg, 0);
	arg.clear();
	arg << "";
	luaScript.Call("setGuildBattleFlagsGatherersName", &arg, &arg, 0);

	arg.clear();
	arg << 0;
	luaScript.Call("setGuildBattleFlagsGatherersActorId", &arg, &arg, 0);
	arg.clear();
	luaScript.Call("broadcastGuildBattleFlagsData", &arg, &arg, 0);
}


void FlagsHandle::OnChangeHp(double& value, Role* role)
{
	if (value > 0 )
	{
		return;
	}
	value = abs(value);
	if (!role)
	{
		return;
	}
	auto monster = GetGatherMonster();
	auto actor = monster->GetGatherActor();
	auto config = monster->GetConfig();
	auto add_value = value;
	if (actor != role->GetActor())
	{
		return;
	}
	shield -= (int)value;
	if (shield <= 0)
	{
		add_value += shield;
		shield = 0;
		value = add_value;
		value = -value;
		
	}
	else
	{
		value = 0;
	}
	
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;

	arg.clear();
	arg << (int)shield;
	arg << (int)config->shield;
	luaScript.Call("broadcastGuildBattleShield", &arg, &arg, 0);
	if (shield == 0)
	{
		//护盾为0采集失败
		monster->EndGather(false);
	}
}


void FlagsHandle::OnWaitTimeTimeOut(void)
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList arg;
	arg << 1;
	luaScript.Call("setGuildBattleFlagsStatus", &arg, &arg, 0);
	arg.clear();
	luaScript.Call("broadcastGuildBattleFlagsData", &arg, &arg, 0);
	arg.clear();
	luaScript.Call("broadcastGuildBattleFlagsGather", &arg, &arg, 0);
}


void FlagsHandle::LogicRun(int64_t curr_t)
{
	if (failure_ && failure_wait_tick_ <= curr_t)
	{
		failure_ = false;
		OnWaitTimeTimeOut();
	}
}
