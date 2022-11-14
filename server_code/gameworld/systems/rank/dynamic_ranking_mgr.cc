#include "StdAfx.h"

#include "dynamic_ranking_mgr.h"
#include "dynamic_ranking.h"


RankAlloc* DynamicRankingMgr::allocator_;

DynamicRankingMgr::DynamicRankingMgr() : saveTime_(3600000), ranking_array_(allocator_)
{
}

DynamicRankingMgr::~DynamicRankingMgr()
{
	Destroy();
	SafeDelete(DynamicRankingMgr::allocator_);
}

void DynamicRankingMgr::Destroy()
{
	//释放资源
	for (int i = 0; i < ranking_array_.count(); i++)
	{
		DynamicRanking* rank = ranking_array_[i];
		if (rank->IsModify())
			rank->Save(NULL);
		rank->~DynamicRanking();
		allocator_->FreeBuffer(rank);
	}

	ranking_array_.empty();
	ranking_table_.clear();
}

DynamicRanking* DynamicRankingMgr::GetRanking(const char* name)
{
	if (!name) return NULL;

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);
	DynamicRanking** ret = ranking_table_.get(key);
	return ret ? *ret : NULL;
}

void DynamicRankingMgr::Remove(const char* name)
{
	if (!name) return;

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);
	ranking_table_.remove(key);

	for (int i = 0; i < ranking_array_.count(); i++)
	{
		DynamicRanking* rank = ranking_array_[i];

		if (strcmp(name, rank->GetName()) == 0)
		{
			ranking_array_.remove(i);
			rank->~DynamicRanking();
			allocator_->FreeBuffer(rank);//销毁排行榜
			break;
		}
	}


}

DynamicRanking* DynamicRankingMgr::Add(const char* name, int maxitem, int display)
{
	if (!name) return NULL;

	if ((int)ranking_table_.count() >= MAX_RANKING) return NULL;

	DynamicRanking* rank = GetRanking(name);

	if (rank)
	{
		return NULL;
	}

	rank = (DynamicRanking*)allocator_->AllocBuffer(sizeof(DynamicRanking));
	new(rank)DynamicRanking(name, maxitem, display != 0 ? true : false);
	ranking_array_.add(rank);

	if (display)
	{
		NotifyUpdate();
	}

	unsigned int h1 = bzhashstr(name, 1);
	unsigned int h2 = bzhashstr(name, 2);
	int64_t key = MAKEINT64(h1, h2);

	if (ranking_table_.get(key) == NULL)
		ranking_table_.put(key, rank);

	return rank;
}

void DynamicRankingMgr::NotifyUpdate()
{
	//static char data[] = { enRankingSystemID, sRankingUpdate };
	//static GameEngine* ge = GetGameEngine();
	//ge->BroadCast(data, sizeof(data));
}

void DynamicRankingMgr::RunOne(int64_t now_t)
{
	if (saveTime_.CheckAndSet(now_t))
	{
		for (int i = 0; i < ranking_array_.count(); i++)
		{
			DynamicRanking* rank = ranking_array_[i];

			if (rank && rank->IsAutoSave() && rank->IsModify())
			{
				rank->Save(NULL);
			}
		}
	}
}

