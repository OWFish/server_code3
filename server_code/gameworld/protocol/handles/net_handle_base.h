#pragma once
#include "system_cmd_def.h"
#include "netmsg_dispatcher.h"
#include "game_engine.h"
#include "game_server.h"


namespace NetHandle
{
	void RegBaseCmd();
	void RegSkillCmd();
	void RegEquipCmd();
	void RegRankingCmd();
	void ReqDepotCmd();
	void ReqWingCmd();
	void RegGuildCmd();
	void ReqTogetherHitCmd();

	/*------------------------------*/
	inline void InitNetHandles(){
		RegBaseCmd();
		RegSkillCmd();
		RegEquipCmd();
		RegRankingCmd();
		ReqDepotCmd();
		ReqWingCmd();
		RegGuildCmd();
		ReqTogetherHitCmd();
	}
} // end of namespace