#include "StdAfx.h"
#include "skirmish.h"
#include "actor/actor.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_data_mgr.h"
#include "rank/static_ranking_mgr.h"
#include "rank/static_rank_basic.h"
#include "rank/ranking_system.h"
#include <math.h>


void createSkirmishData(Actor* tar, int src_id, int index, int attrper)
{
	Actor* src = GetGameEngine()->GetEntityMgr()->GetActorPtrById(src_id);
	if (src == NULL || !src->IsInited() || src->IsImage()) return;

	ActorPacket AP;
	DataPacket& pack = src->AllocPacket(AP);
	pack << (uint8_t)Protocol::CMD_Skirmish;
	pack << (uint8_t)Protocol::sSkirmishCmd_UpdateActorData;

	pack << index;
	pack << (short)tar->GetLevel();
	pack << (short)tar->GetBasicData()->zhuansheng_lv;
	pack.writeString(tar->GetEntityName());
	//pack << (int)(tar->GetZhanLingStage());  遭遇战对方没有战灵数据，看策划需不需要加

	if (!tar->CreateCloneData(pack, attrper))
		AP.rollBack();
	else {
		pack << char(attrper ? 1 : 0);
		pack << int(tar->GetTogeLv());
		pack << int(tar->GetPrestigeExp());
		AP.flush();
	}
}

void SkirmishHelper::CreateSkirmishData(Actor* actor, int index, int id, int level, const char* name, int attrper)
{
	// 这个会产生连锁反应
	if (actor->IsImage())
		return;
	index = index - 1; // 后来改为从0开始
	OutputMsg(rmTip, "createSkirmishData index %d, level:%d, name:%s",
		index, level, name);

	if (id == actor->GetId())
	{
		ActorPacket AP;
		DataPacket& pack = actor->AllocPacket(AP);
		pack << (uint8_t)Protocol::CMD_Skirmish;
		pack << (uint8_t)Protocol::sSkirmishCmd_UpdateActorData;

		pack << index;
		pack << (short)(level % 1000);
		pack << (short)(level / 1000);
		pack.writeString(name);
		//pack << (int)(actor->GetZhanLingStage());  遭遇战没有战灵数据，看策划需不需要加

		if (!actor->CreateCloneData(pack, attrper))// 随机数据
			AP.rollBack();
		else {
			pack << char(attrper ? 1 : 0);
			pack << int(actor->GetTogeLv());
			pack << int(actor->GetPrestigeExp());
			AP.flush();
		}
	}
	else
	{
		ActorAsynFunc func = std::bind(createSkirmishData, std::placeholders::_1, actor->GetActorId(), index, attrper);
		GetGameEngine()->GetActorAsynMgr()->RegActorEv(id, func);
	}
}

void CreateFieldPlayerData(Actor* tar, int src_id, int index, int pos_x, int pos_y, int actionType, int isForay, int killNum, int ox, int oy)
{
	Actor* src = GetGameEngine()->GetEntityMgr()->GetActorPtrById(src_id);
	if (src == NULL || !src->IsInited() || src->IsImage()) return;

	ActorPacket AP;
	DataPacket& pack = src->AllocPacket(AP);
	pack << (uint8_t)Protocol::CMD_Skirmish;
	pack << (uint8_t)Protocol::sFiledPlayerCmd_UpdateActorData;

	pack << index;
	pack << (short)pos_x;
	pack << (short)pos_y;
	pack << (short)tar->GetLevel();
	pack << (short)tar->GetBasicData()->zhuansheng_lv;
	pack << (char)actionType;
	pack << (char)isForay;
	pack << (int)killNum;
	pack << (short)ox;
	pack << (short)oy;
	pack.writeString(tar->GetEntityName());
	pack << tar->GetBasicData()->headimage;

	if (!tar->CreateCloneData(pack, 100))
		AP.rollBack();
	else
		AP.flush();
}

void SkirmishHelper::createFieldPlayerData(Actor* actor, int index, int actor_id, int pos_x, int pos_y, int actionType, int isForay, int killNum, int ox, int oy)
{
	// 这个会产生连锁反应
	if (actor->IsImage())
		return;
	OutputMsg(rmTip, "%d createFieldPlayerData index %d, pos_x:%d, pos_y:%d, actionType:%d, isForay:%d", actor->GetActorId(),
		index, pos_x, pos_y, actionType, isForay);
	ActorAsynFunc func = std::bind(CreateFieldPlayerData, std::placeholders::_1, actor->GetActorId(), index, pos_x, pos_y, actionType, isForay, killNum, ox, oy);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, func);
}

inline bool FindInRet(ActorId id, std::vector<ActorId> &ret)
{
	for (auto it : ret)
	{
		if (it == id)
			return true;
	}
	return false;
}

// 4 + 1 // 列表为4, 多找1个, 在lua里排除最近匹配过的4个,
#define MAX_SKIRMISH_ACTORS 5
std::vector<ActorId>  SkirmishHelper::FindSkirmish(Actor* actor)
{
	std::vector<ActorId> ret;
	if (actor == nullptr)
		return ret;

	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	const std::vector<ActorBasicData*>& datas = actor_data_mgr->GetDatas();

	size_t size = datas.size();
	size_t index = wrand((unsigned long)size);
	int clevel = actor->GetChapterLevel();
	uint32_t aid = actor->GetActorId();

	// // 先从排行榜里找 前100, 前5-后50
	// 全部用排行榜
	static StaticRankBasic *power_rank = GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->GetRanking(RankingType_Power);
	int prank = power_rank->GetIndexFromId(actor->GetActorId());
	int rank_size =static_cast<int> ( power_rank->getRankDataSize() );
	if (prank >= 0)// && prank < 100)
	{
		int l = prank - MAX_SKIRMISH_ACTORS;
		int r = prank + 50;
		if (l < 0) l = 0;
		if (r > rank_size - 1) r = rank_size - 1;

		int rank_range = r - l;
		int need_size = rank_range >= MAX_SKIRMISH_ACTORS ? MAX_SKIRMISH_ACTORS : rank_range;

		int counter = 0;
		while (ret.size() < (uint32_t)need_size && counter < 100) //保险起见
		{
			++counter;
			int r = l + wrand(rank_range);
			if (r == prank) continue;
			ActorId a = power_rank->GetActorIdByRanking(r);
			if (!FindInRet(a, ret))
				ret.push_back(a);
		}

		if (counter >= 100)
			OutputMsg(rmError, "find skirmish counter > 100, aid:%d", actor->GetActorId());
	}

	//  需求改了,不用章节了
	/*for (size_t i = 0; i < size && ret.size() < MAX_SKIRMISH_ACTORS; ++i)
	{
		auto data = datas[(index + i) % size];
		if (aid != data->actor_id && 
			(data->chapter_level / 10) == (clevel / 10)) // 章节相同
			ret.push_back(data->actor_id);
	}*/

	if (ret.size() < MAX_SKIRMISH_ACTORS)
	{
		index = wrand((unsigned long)size);
		for (size_t i = 0; i < size && ret.size() < MAX_SKIRMISH_ACTORS; ++i)
		{
			auto data = datas[(index + i) % size];
			if (aid != (unsigned int)data->actor_id &&
				((unsigned int)clevel > data->chapter_level) && (((unsigned int)clevel - data->chapter_level) < 100) && // 100关以内
				!FindInRet(data->actor_id, ret))
			{
				ret.push_back(data->actor_id);
			}
		}
	}

	if (ret.size() < MAX_SKIRMISH_ACTORS)
	{
		index = wrand((unsigned int)size);
		for (size_t i = 0; i < size && ret.size() < MAX_SKIRMISH_ACTORS; ++i)
		{
			auto data = datas[(index + i) % size];
			if (aid != (unsigned int)data->actor_id && !FindInRet(data->actor_id, ret))
				ret.push_back(data->actor_id);
		}
	}
	return ret;
}

std::vector<ActorId> SkirmishHelper::FindFieldPlayer(Actor *actor, int startlv, int endlv, int needNum, int flSize)
{
	std::vector<ActorId> ret;
	if (actor == nullptr)
		return ret;
	startlv = __max(startlv, 0); endlv = __max(endlv, 0);
	auto actor_data_mgr = GetGameEngine()->GetActorDataMgr();
	const std::vector<ActorBasicData*>& datas = actor_data_mgr->GetDatas();
	uint32_t aid = actor->GetActorId();//自己的玩家ID
	std::vector<ActorBasicData*> leftDatas; leftDatas.clear();
	{//第一次找
		size_t size = datas.size();//数据大小
		size_t index = wrand((unsigned long)size);//随机出一个开始位置
		for (size_t i = 0; i < size && ret.size() < (size_t)needNum; ++i)
		{
			auto data = datas[(index + i) % size];
			if (aid != (uint32_t)data->actor_id &&
				data->chapter_level >= (unsigned int)startlv && data->chapter_level <= (unsigned int)endlv)
				ret.push_back(data->actor_id);
			else if (aid != (uint32_t)data->actor_id)
				leftDatas.push_back(data);
		}
	}
	while(ret.size() < (size_t)needNum && flSize > 0)//以后再递减往下找
	{
		startlv = startlv - flSize;
		endlv = endlv + flSize;
		startlv = __max(startlv, 0); endlv = __max(endlv, 0);
		if (leftDatas.empty()) break;
		size_t lsize = leftDatas.size();
		for (size_t i = 0; i < lsize && ret.size() < (size_t)needNum;)
		{
			auto data = datas[i];
			if (data->chapter_level >= (unsigned int)startlv && data->chapter_level <= (unsigned int)endlv)
			{
				ret.push_back(data->actor_id);
				leftDatas[i] = leftDatas[leftDatas.size() - 1];
				leftDatas.pop_back();
				lsize = leftDatas.size();
			}
			else 
			{
				++i;
			}
		}
	}
	return ret;
}