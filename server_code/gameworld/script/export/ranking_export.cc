#include "StdAfx.h"
#include "../interface/ranking_export.h"
#include "rank/ranking_system.h"
#include "rank/dynamic_ranking.h"
//#include "rank/ranking_system.h"

namespace Ranking
{

int getRankingItemList(lua_State* L)
{
	void* pRank = ((void*)tolua_touserdata(L, 1, 0));

	if (pRank == NULL) return 0;

	int nCount = (int)tolua_tonumber(L, 2, 0); //需要返回前N名

	Vector<RankingItem*>& itemList = ((DynamicRanking*)pRank)->GetList();
	Vector<void*>* pList = (Vector<void*>*)(&itemList);
	nCount = __min(nCount, (int)itemList.count());
	LuaHelp::PushDataPointerToTable(L, (void**)(*pList), nCount);

	return 1;
}

void* getRanking(char* sName)
{
	return GetGameEngine()->GetRankingSystem()->GetDynamicRankingMgr()->GetRanking(sName);
}

void* add(char* sName, int nMax, int boDisplay)
{
	return GetGameEngine()->GetRankingSystem()->GetDynamicRankingMgr()->Add(sName, nMax, boDisplay);
}

bool load(void* pRank, char* sFile)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->Load(sFile);
	}

	return false;
}

bool save(void* pRank, char* sFile)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->Save(sFile);
		return true;
	}

	return false;
}

void addColumn(void* pRank, char* sTitle, int nIndex /*= -1*/)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->AddColumn(sTitle, nIndex);
	}
}

int getColumnCount(void* pRank)
{
	if (!pRank) return 0;

	return ((DynamicRanking*)pRank)->ColumnCount();
}

void setColumnTitle(void* pRank, char* sTitle, int nIndex)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->SetColumnTitle(sTitle, nIndex);
	}
}

void* addItem(void* pRank, int nId, int nPoint)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->AddItem(nId, nPoint);
	}

	return NULL;
}

void* tryAddItem(void* pRank, int nId, int nPoint)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->TryAddItem(nId, nPoint);
	}

	return NULL;
}

int getItemIndexFromId(void* pRank, int nId)
{
	if (pRank)
	{
		int nTeamp = -1;
		return (int)(((DynamicRanking*)pRank)->GetIndexFromId(nId, nTeamp));
	}

	return -1;
}

void* getItemPtrFromId(void* pRank, int nId)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->GetPtrFromId(nId);
	}

	return NULL;
}

void* updateItem(void* pRank, int nId, int nPoint)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->Update(nId, nPoint);
	}

	return NULL;
}

void* setItem(void* pRank, int nId, int nPoint)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->Set(nId, nPoint);
	}

	return NULL;
}

void setSub(void* pRankItem, int nIndex, char* sData)
{
	if (pRankItem)
	{
		return ((RankingItem*)pRankItem)->SetSub(nIndex, sData);
	}
}

void setSubInt(void* pRankItem, int nIndex, int data)
{
	if (pRankItem)
	{
		char sData[20];
		itoa(data, sData, 10);
		return ((RankingItem*)pRankItem)->SetSub(nIndex, sData);
	}
}

int updateSubInt(void* rankItem, int nIndex, int val)
{
	if (!rankItem) return 0;

	RankingItem* pRankItem = (RankingItem*)rankItem;
	const char* sData = pRankItem->GetSubData(nIndex);
	/*int ndata = StrToInt(sData);
	ndata += val;*/
	int newVal = StrToInt(sData) + val;
	char newData[20];
	itoa(newVal, newData, 10);
	pRankItem->SetSub(nIndex, newData);
	return newVal;
}

void addRef(void* pRank)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->addRef();
	}
}

void release(void* pRank)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->release();
	}
}

int getRef(void* pRank)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->getRef();
	}

	return 0;
}

void removeRanking(char* sName)
{
	GetGameEngine()->GetRankingSystem()->GetDynamicRankingMgr()->Remove(sName);
}

int getRankItemCount(void* pRank)
{
	if (pRank)
	{
		return (int)(((DynamicRanking*)pRank)->GetList().count());
	}

	return 0;
}

int getPoint(void* pRankItem)
{
	if (pRankItem)
	{
		return ((RankingItem*)pRankItem)->GetPoint();
	}

	return 0;
}

int getId(void* pRankItem)
{
	if (pRankItem)
	{
		return ((RankingItem*)pRankItem)->GetId();
	}

	return 0;
}

const char* getSub(void* pRankItem, int nIndex)
{
	if (pRankItem)
	{
		return ((RankingItem*)pRankItem)->GetSubData(nIndex);
	}

	return "-";
}

int getSubInt(void* pRankItem, int nIndex)
{
	if (!pRankItem) return 0;

	const char* sData = ((RankingItem*)pRankItem)->GetSubData(nIndex);
	return sData ? StrToInt(sData) : 0;
}

void clearRanking(void* pRank)
{
	if (pRank)
	{
		return ((DynamicRanking*)pRank)->clear();
	}
}

void* getItemFromIndex(void* pRank, int nIndex)
{
	if (pRank)
	{
		Vector<RankingItem*>& itemList = ((DynamicRanking*)pRank)->GetList();

		if (nIndex >= 0 && nIndex < itemList.count())
		{
			return itemList[nIndex];
		}
	}

	return NULL;
}

void setColumnDisplay(void* pRank, int nIndex , int boDisplay)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->SetColDisplay(nIndex, boDisplay > 0 ? true : false);
	}
}

int getIndexFromPtr(void* pRankItem)
{
	if (pRankItem)
	{
		return ((RankingItem*)pRankItem)->GetIndex();
	}

	return -100000;//
}

void setDisplayName(void* pRank, const char* sName)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->SetDisplayName(sName);
	}
}

void setIdTitle(void* pRank, const char* sName)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->SetIdTitle(sName);
	}
}

void setPointTitle(void* pRank, const char* sName)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->SetPointTitle(sName);
	}
}

void removeId(void* pRank, int id)
{
	if (pRank)
	{
		((DynamicRanking*)pRank)->RemoveId(id);
	}
}

void setAutoSave(void* pRank, bool isAuto)
{
	if (!pRank) return;

	((DynamicRanking*)pRank)->SetAutoSave(isAuto);
}

void swapEqualItem(void* rank, void* item1, void* item2)
{
	if (!rank) return;

	((DynamicRanking*)rank)->SwapEqualItem((RankingItem*)item1, (RankingItem*)item2);
}

int getLianfuRankData(lua_State* L)
{
	return 0;

	//旧代码还没看
	int index = (int)tolua_tonumber(L, 1, -1);

	if (index < 0 || index > 99) return 0;

	static LianfuRank& lfRank = GetGameEngine()->GetLianfuRank();
	AllRankList* alllist = lfRank.GetTotalRank();

	RankList& list = alllist->data_[rtFightVal];
	if (list.count() <= index) return 0;

	int aid = list[index].actorId_;
	LianfuRankActor* info = lfRank.FindRankActor(aid);
	if (info == NULL) return 0;

	lua_newtable(L);

	lua_pushstring(L, "name");
	lua_pushstring(L, list[index].actorName_);
	lua_settable(L, -3);
	lua_pushstring(L, "actorid");
	lua_pushinteger(L, aid);
	lua_settable(L, -3);
	lua_pushstring(L, "job");
	lua_pushinteger(L, list[index].job_);
	lua_settable(L, -3);
	lua_pushstring(L, "sex");
	lua_pushinteger(L, list[index].sex_);
	lua_settable(L, -3);
	lua_pushstring(L, "fight");
	lua_pushinteger(L, list[index].fightVal_);
	lua_settable(L, -3);
	lua_pushstring(L, "guild");
	lua_pushstring(L, list[index].guild_);
	lua_settable(L, -3);
	lua_pushstring(L, "server");
	lua_pushinteger(L, info->sid_);
	lua_settable(L, -3);

	return 1;
}

void* getStaticRank(int rankId)
{
	if (rankId < RankingType_Power || rankId >= RankingType_Count)
	{
		return NULL;
	}
	return GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->GetRanking((RankingType)rankId);
}

int getSRIndexFromId(void* rank, int id)
{
	if (!rank)
	{
		return -1;
	}
	StaticRankBasic* pRank = (StaticRankBasic*)rank;
	return pRank->GetIndexFromId(id);
}

int getSRIdFromIdx(void* rank, int idx)
{
	if (!rank)
	{
		return -1;
	}
	StaticRankBasic* pRank = (StaticRankBasic*)rank;
	return pRank->GetActorIdByRanking((size_t)idx);
}

void updateStaticRank()
{
	GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->UpdateRank();
}

const char* getRankName(void* rank)
{
	if (rank)
	{
		return ((DynamicRanking*)rank)->GetFileName();
	}
	return NULL;
}

void setRankName(void* rank, const char* name)
{
	if (name == NULL)
		return;
	if (rank)
	{
		return ((DynamicRanking*)rank)->SetFileName(name);
	}
}

}

