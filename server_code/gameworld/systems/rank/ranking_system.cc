#include "StdAfx.h"
#include "ranking_system.h"


RankingSystem::RankingSystem()
	:static_rank_mgr_(NULL)
	,dynamic_rank_mgr_(NULL)
{
	static_rank_mgr_ = new StaticRankingMgr();
	dynamic_rank_mgr_ = new DynamicRankingMgr();
}

RankingSystem::~RankingSystem()
{
	SafeDelete(static_rank_mgr_);
	SafeDelete(dynamic_rank_mgr_);
}

void RankingSystem::Destroy()
{
}

void RankingSystem::Initialize()
{
	static_rank_mgr_->Load();
	DynamicRankingMgr::allocator_ = new RankAlloc("DynamicRankingMgr");
}

void RankingSystem::RunOne(int64_t now_t)
{
	static_rank_mgr_->RunOne(now_t);
	dynamic_rank_mgr_->RunOne(now_t);
}

void RankingSystem::OnReqRankingData(Actor * actor, DataPacketReader & pack)
{
	short rank_type;
	pack >> rank_type;
	switch (rank_type) {
		case RankingType_Skirmish: {
			ScriptValueList arg;
			arg << actor;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onReqSkirmishRanking", &arg, NULL, 0);
			break;
		}
		case RankingType_ChapterLevel: {
			ScriptValueList arg;
			arg << actor;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onReqChapterLevelRanking", &arg, NULL, 0);
			break;
		}
		case RankingType_ChallengeLevel: {
			ScriptValueList arg;
			arg << actor;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onReqChallengeLevelRanking", &arg, NULL, 0);
			break;
		}
		case RankingType_TeamLike: {
			ScriptValueList arg;
			arg << actor;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onReqTeamLikeRanking", &arg, NULL, 0);
			break;
		}
		case RankingType_Stone: {
			ScriptValueList arg;
			arg << actor;
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onReqStoneLvRanking", &arg, NULL, 0);
			break;
		}
		default: {
			static_rank_mgr_->SendRankingDataByType(actor, (RankingType)rank_type);
		}
	}	
}
