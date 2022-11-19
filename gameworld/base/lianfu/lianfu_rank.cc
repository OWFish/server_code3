#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

LianfuRank::LianfuRank() : rank_update_(false)
{
	total_rank_ = new AllRankList();
}

LianfuRank::~LianfuRank()
{
	delete total_rank_;
}

int RankCompare(RankDbItem& item1, RankDbItem& item2)
{
	if (item1.point_ > item2.point_)
	{
		return 1;
	}
	else if (item1.point_ == item2.point_)
	{
		return (item1.actorId_ > item2.actorId_ ? 1 : -1);
	}
	return -1;
}

void LianfuRank::UpdateRank()
{
	////更新排行榜
	//rank_actor_list_.clear();
	//rank_actor_hash_.clear();

	//static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	//ServerList& srv_list = mgr.GetServerList();

	//int cnt = __min(srv_list.count(), MAX_LIANFU_SERVER);

	//for (int i = rtNone + 1; i < rtMax; i++)
	//{
	//	RankList& totalRank = total_rank_->data_[i];
	//	totalRank.clear();

	//	int pos[MAX_LIANFU_SERVER] = { 0 };
	//	while (totalRank.count() < RankDbItem::MAX_COUNT)
	//	{
	//		int serverId = -1;
	//		int nMax = -1; //找出最大的项
	//		RankDbItem* maxItem = NULL;
	//		for (int idx = 0; idx < cnt; idx++)
	//		{
	//			RankList& serverRank = srv_list[idx].rank_.data_[i];
	//			int curr_pos = pos[idx];
	//			if (curr_pos >= serverRank.count()) continue;

	//			RankDbItem* rankItem = &serverRank[curr_pos];
	//			if (nMax == -1 || RankCompare(*rankItem, *maxItem) > 0)
	//			{
	//				serverId = srv_list[idx].sid_;
	//				nMax = idx;
	//				maxItem = rankItem;
	//			}
	//		}

	//		if (nMax == -1) break;

	//		pos[nMax]++;
	//		totalRank.push_back(*maxItem);

	//		LianfuRankActor* actor = GetRankActor(maxItem->actorId_);
	//		if (actor)
	//		{
	//			actor->rankNum_[i] = totalRank.count();
	//			actor->sid_ = serverId;
	//		}
	//	}
	//}

	//// 通知排行榜已经更新
	//static uint8_t hdr[] = { enMiscSystemID, sRefreshRank, 1 };
	//mgr.BroadCast(ciChannelWorld, 0, (char*)(&hdr), sizeof(hdr));
}

void LianfuRank::OnUpdateRank()
{
	rank_update_ = true;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	if (!mgr.IsLianfu()) return;

	SendRankList();
}

void LianfuRank::SendRankList()
{
	/*if (!rank_update_) return;

	static LianfuMgr& lfMgr = GetGameEngine()->GetLianfuMgr();
	static GameServer* gs = ServerInstance();
	static DbRankMgr& mgr = GetGameEngine()->GetDbRankMgr();

	AllRankList* currRank = mgr.GetCurrRank();
	if (!currRank)
	{
		OutputMsg(rmError, "current rank is null");
		return;
	}

	int sid = gs->GetServerIndex();

	for (int rankIdx = rtNone + 1; rankIdx < rtMax; rankIdx++)
	{
		RankList& list = currRank->data_[rankIdx];

		DataPacket& dp = lfMgr.AllocSendPacket(lsRank, lcRankList);
		dp << (int)sid << (int)rankIdx << (int)list.count();

		for (int i = 0; i < list.count(); i++)
		{
			RankDbItem& item = list[i];
			DbRankMgr::WriteRankData(dp, item);
		}
		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, lfMgr.GetLianfuSid());
	}*/
}

LianfuRankActor* LianfuRank::FindRankActor(ActorId aid)
{
	LianfuRankActor** pp = rank_actor_hash_.get(aid);
	if (pp)
	{
		return *pp;
	}

	return NULL;
}

LianfuRankActor* LianfuRank::GetRankActor(ActorId aid)
{
	LianfuRankActor* actor = NULL;
	LianfuRankActor** pp = rank_actor_hash_.get(aid);
	if (pp)
	{
		actor = *pp;
	}
	else
	{
		int count = rank_actor_list_.count();
		if (count >= MAX_RANK_ACTOR)
		{
			// 正常情况是不会出现的
			return NULL;
		}
		actor = &rank_actor_list_[count];
		rank_actor_list_.trunc(count + 1);
		actor->reset(aid);

		rank_actor_hash_.put(aid, actor);
	}

	return actor;
}

void LianfuRank::ProcessNetData(int cmd, DataPacketReader& packet)
{
	switch (cmd)
	{
	case lcRankList:
		HandleRankList(packet);
		break;
	case lcRankTitle:
		GiveOrGiveupTitle(packet);
		break;
	}
}

void LianfuRank::HandleRankList(DataPacketReader& packet)
{
	/*int sid, rankIdx, itemCount;
	packet >> sid >> rankIdx >> itemCount;

	if (rankIdx <= rtNone || rankIdx >= rtMax)
	{
		OutputMsg(rmError, "rank index error:%d", rankIdx);
		return;
	}

	if (itemCount < 0 || itemCount > RankDbItem::MAX_COUNT)
	{
		OutputMsg(rmError, "rank item count error:%d", itemCount);
		return;
	}

	// 找到对应服的排行榜
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	CommServer* info = mgr.GetServerInfo(sid);
	if (!info)
	{
		OutputMsg(rmError, "handle rank list error:%d", sid);
		return;
	}

	RankList& rankList = info->rank_.data_[rankIdx];
	LastRankList& last_list = info->last_rank_list_.data_[rankIdx];
	rankList.trunc(itemCount);

	for (int itemIdx = 0; itemIdx < itemCount; itemIdx++)
	{
		RankDbItem& item = rankList[itemIdx];
		DbRankMgr::ReadRankData(packet, item);
		
		int* pos =last_list.get(item.actorId_);

		if (pos)
		{
			item.last_rank_ = (*pos);
		}
		else
		{
			item.last_rank_ = 0;
		}
	}

	// 最后一个，开始更新了
	if (rankIdx == rtMax - 1)
	{
		UpdateRank();

		for (int rankid = rtNone + 1; rankid < rtMax; rankid++)
		{
			LastRankList& last_list = info->last_rank_list_.data_[rankid];
			last_list.clear();

			RankList& list = total_rank_->data_[rankid];
			
			for (int i = 0; i < list.count(); i++)
			{
				RankDbItem& item = list[i];
				int pos = i + 1;
				last_list.put(item.actorId_, pos);
			}
		}
	}
	*/
}

void LianfuRank::GiveOrGiveupTitle(DataPacketReader& packet)
{
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	if (!mgr.IsLianfu()) return;

	ActorId aid;
	int titleId;
	int tmp;
	packet >> aid >> titleId >> tmp;
	
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(aid);
	if (!actor) return;

	/*if (tmp == 1)
		actor->GetAchieveSystem().GiveTitle(titleId);
	else
		actor->GetAchieveSystem().GiveupTitle(titleId);
	*/
}
