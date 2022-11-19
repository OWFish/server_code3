#include "StdAfx.h"
#include "ranking_system.h"
#include "protocol/protos/rank_proto.h"
#include "actor/actor_data_mgr.h"
#include "rank_config.h"

RankingSystem::RankingSystem()
	:static_rank_mgr_(NULL)
	, dynamic_rank_mgr_(NULL)
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
	
	std::string rank_name = RankConfigPool::GetRankName(rank_type);
	if (rank_name == "")
		return;

	int show_size = RankConfigPool::GetRankShowSize(rank_type);
	if (show_size <= 0)
		return;

	auto ge = GetGameEngine();
	auto pRedis = ge->GetRedis();
	static const ActorDataMgr*  actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	int64_t self_rank = -1;
	char sActorID[32];
	strcpy(sActorID, std::to_string(actor->GetId()).c_str());
	auto pResult = pRedis->zrevrangebywithscores(rank_name.c_str(), 0, -1);
	self_rank = pRedis->zrank(rank_name.c_str(), sActorID);
	int total_count = pRedis->zcard(rank_name.c_str());
	if (total_count > 0 && total_count > self_rank)
	{
		self_rank = total_count - self_rank;
	}
	else
		self_rank = 0;

	static Protocol::RankDataProto msg;
	msg.rank_type = rank_type;
	auto pReplay = pResult->get_reply();
	short lrank = 0;
	msg.rank_size = (short)(pReplay->elements / 2);
	ActorPacket AP;
	DataPacket& sp = actor->AllocPacket(AP);
	sp.writeBuf(&msg, sizeof(msg));

	if (pReplay->type == REDIS_REPLY_ARRAY)
	{
		const ActorBasicData* pActor = nullptr;
		for (int i = 0; i < pReplay->elements; i++)
		{
			if (i % 2 == 0)
				pActor = actor_data_mgr->GetData(atoi(pReplay->element[i]->str));
			else
			{
				if (pActor)
				{
					lrank++;
					sp << (int)lrank;
					sp << (int)pActor->actor_id;
					sp << pActor->actor_name;
					sp << pActor->guild_name_;
					sp << (double)(atoi(pReplay->element[i]->str));
				}
			}
		}
		sp << (int)self_rank + 1;
	}
	AP.flush();	
}

bool RankingSystem::GetRankList(int rank_type, std::vector<int>& ret, int retsize)
{
	std::string rank_name = RankConfigPool::GetRankName(rank_type);
	if (rank_name == "")
		return false;

	auto ge = GetGameEngine();
	auto pRedis = ge->GetRedis();
	auto pResult = pRedis->zrevrange(rank_name.c_str(), 0, -1);
	auto pReplay = pResult->get_reply();
	short lrank = 0;

	static const ActorDataMgr*  actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	if (actor_data_mgr && pReplay->type == REDIS_REPLY_ARRAY)
	{
		for (int i = 0; i < pReplay->elements; i++)
		{
			auto pActor = actor_data_mgr->GetData(atoi(pReplay->element[i]->str));
			if (pActor)
			{
				ret.emplace_back(pActor->actor_id);
				if (lrank >= retsize)
					break;
			}
			lrank++;
		}
	}
	return true;
}

bool RankingSystem::GetRankListWithScore(int rank_type, std::vector<int>& ret, int retsize)
{
	std::string rank_name = RankConfigPool::GetRankName(rank_type);
	if (rank_name == "")
		return false;

	auto ge = GetGameEngine();
	auto pRedis = ge->GetRedis();
	auto pResult = pRedis->zrevrangebywithscores(rank_name.c_str(), 0, -1);
	auto pReplay = pResult->get_reply();
	short lrank = 0;

	static const ActorDataMgr*  actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	if (actor_data_mgr && pReplay->type == REDIS_REPLY_ARRAY)
	{
		bool has = false;
		for (int i = 0; i < pReplay->elements; i++)
		{
			bool has = false;
			if (i%2 == 0)
			{
				auto pActor = actor_data_mgr->GetData(atoi(pReplay->element[i]->str));
				if (pActor)
				{
					ret.emplace_back(pActor->actor_id);
					has = true;
				}
					
			}
			else
			{
				if (has)
				{
					has = false;
					ret.emplace_back(atoi(pReplay->element[i]->str));
					if (lrank >= retsize)
						break;
				}
			}
			lrank++;
		}
	}
	return true;
}
