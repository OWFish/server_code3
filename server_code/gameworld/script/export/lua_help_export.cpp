#include "StdAfx.h"
#ifndef _MSC_VER
#include "../../StdAfx.h"
#endif
#include "../interface/lua_help_export_fun.h"
using namespace stream;


//Note向LuaHelp导出的一些辅助性的函数在这里要放一份
//不然脚本无法访问
const luaL_Reg  LuaHelpExpot[] =
{
	{"saveTable", LuaHelp::saveTable},
	{"getTestTable", LuaHelp::getTestTable},
	{"getTeamMemberList", LuaHelp::getTeamMemberList},
	{"getTeamMemberListByPtr", LuaHelp::getTeamMemberListByPtr},
	{"getFbFromId", LuaHelp::getFbFromId},
	{"getReloadMapPos", LuaHelp::getReloadMapPos},
	{"getNearEntityList", LuaHelp::getNearEntityList},
	{"getAllActorList", LuaHelp::getAllActorList},
	{"getSceneActorListById", LuaHelp::getSceneActorListById},
	{"getSceneNpcListById", LuaHelp::getSceneNpcListById},
	{"getSceneMonsterList", LuaHelp::getSceneMonsterList},
	{"getSceneActorList", LuaHelp::getSceneActorList},
	{"getNearEntityListFromXY", LuaHelp::getNearEntityListFromXY},
	{"getNearEntityListFromRange", LuaHelp::getNearEntityListFromRange},
	{"getRankingItemList", LuaHelp::getRankingItemList},
	{"getFbActorList", LuaHelp::getFbActorList},
	{"getVisiActorList", LuaHelp::getVisiActorList},
	{"getEntityListFromRange", LuaHelp::getEntityListFromRange},
	{"getSceneActorListByPtr", LuaHelp::getSceneActorListByPtr},
	{"getSceneMonsterListByScene", LuaHelp::getSceneMonsterListByScene},
	{ NULL, NULL }, //这行不要删除，删除服务器将无法启动
};


namespace LuaHelp
{
int getSceneEntityList(Scene* pScene, lua_State* L, int type)
{
	if (!pScene)
	{
		LuaHelp::PushDataPointerToTable(L, NULL, 0);
		return 0;
	}

	void* entityList[8192];
	int count = 0;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();


	if (type == enActor || type == enMonster)
	{
		EntityList* list = NULL;

		if (type == enActor)
		{
			list = &(pScene->GetPlayList());
		}

		else if (type == enMonster)
		{
			list = &(pScene->GetMonsterList());
		}

		LinkedNode<EntityHandle>* pNode;
		ListIterator<EntityHandle> it(*list);

		for (pNode = it.first(); pNode && count < 8192; pNode = it.next())
		{
			Entity* pe = em->GetEntity(pNode->data_);

			if (pe && pe->GetType() == type)
			{
				entityList[count++] = pe;
			}
		}
	}
	else if (type == enNpc)
	{
		Scene::NpcList* npclist = pScene->GetNpcList();

		for (int i = 0; i < npclist->count(); i++)
		{
			EntityHandle pe = npclist->get(i);
			if (pe && pe.GetType() == type)
			{
				entityList[count++] = em->GetEntity(pe);
			}
		}
	}

	LuaHelp::PushDataPointerToTable(L, entityList, count);

	return 1;
}

int getEntityFromRange(VisiHandleList& vec, lua_State* L)
{
	if (vec.count() > 0)
	{
		void* actorList[8192];
		int count = 0;
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();

		for (int i = 0; count < 8192 && i < vec.count(); i++)
		{
			Entity* pe = em->GetEntity(vec[i]);

			if (pe)
			{
				actorList[count++] = pe;
			}
		}

		LuaHelp::PushDataPointerToTable(L, actorList, count);
	}
	else
	{
		LuaHelp::PushDataPointerToTable(L, NULL, 0);
	}

	return 1;
}

int saveTable(lua_State* L)
{
	if (lua_istable(L, 1) == false)
	{
		OutputMsg(rmError, ("saveTable is parameter"));
		return 0;
	}

	const char* sFileName = lua_tostring(L, 2);

	if (sFileName == NULL)
	{
		OutputMsg(rmWaning, ("saveTable name is empty, save ./demo.txt"));
		sFileName = "./demo.txt";
	}

	const char* sTableName = lua_tostring(L, 3);
	FileStream stm(sFileName, FileStream::faWrite | FileStream::faCreate, FileStream::AlwaysCreate, NULL);

	if (NULL != sTableName)
	{
		stm.write(sTableName, strlen(sTableName));
		stm.write(" =\r\n", 4);
	}

	FormatTableA(L, 1, stm);
	return 0;

}

int getTestTable(lua_State* L)
{
	float a[10];

	for (int i = 0; i < 10; i++)
	{
		a[i] = (float)1221.3443;
	}

	PushNumberVector(L, (float*)(&a[0]), 10);
	return 1; //返回1个参数
}

int getTeamMemberList(lua_State* L)
{
	void* member[MAX_TEAM_MEMBER_COUNT];

	void* pEntity = ((void*)  tolua_touserdata(L, 1, 0));

	if (pEntity == NULL || ((Entity*)pEntity)->GetType() != enActor) return 0;

	Team* pTeam = ((Actor*)pEntity)->GetCurrentTeam();

	if (!pTeam) return 0;

	int nCount = 0;
	const TeamMember* pMember = pTeam->GetMemberList();

	for (int i = 0; i < MAX_TEAM_MEMBER_COUNT; i++)
	{
		if (pMember[i].actor_)
		{
			member[nCount++] = pMember[i].actor_;
		}
	}

	LuaHelp::PushDataPointerToTable(L, member, nCount);

	return 1;
}

int getTeamMemberListByPtr(lua_State* L)
{
	void* member[MAX_TEAM_MEMBER_COUNT];

	void* pTeam = ((void*)  tolua_touserdata(L, 1, 0));

	if (!pTeam) return 0;

	int nCount = 0;
	const TeamMember* pMember = ((Team*)pTeam)->GetMemberList();

	for (int i = 0; i < MAX_TEAM_MEMBER_COUNT; i++)
	{
		if (pMember[i].actor_)
		{
			member[nCount++] = pMember[i].actor_;
		}
	}

	LuaHelp::PushDataPointerToTable(L, member, nCount);

	return 1;
}



int getFbFromId(lua_State* L)
{
	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
	int nFbid = (int)tolua_tonumber(L, 1, 0);
	unsigned int Buf[256];//最多返回256个副本
	int nCount = fbMgr->GetFbCountFromId(nFbid, Buf, 256);
	LuaHelp::PushNumberVector(L, Buf, nCount);
	return 1;
}


int getReloadMapPos(lua_State* L)
{
	void* pEntity = ((void*)  tolua_touserdata(L, 1, 0));

	if (pEntity == NULL || ((Entity*)pEntity)->GetType() != enActor) return 0;

	int pos[3];
	((Actor*)pEntity)->GetNotReloadMapPos(pos[0], pos[1], pos[2]);
	LuaHelp::PushNumberVector(L, pos, 3);
	return 1;
}


int getNearEntityList(lua_State* L)
{
	void* et = ((void*)  tolua_touserdata(L, 1, 0));

	if (et == NULL) return 0;

	int nRadio = (int)tolua_tonumber(L, 2, 0);
	VisiHandleList& vec = GameEngine::global_var_->fb_visible_list_;
	vec.clear();
	Scene* pScene = ((Entity*)et)->GetScene();

	if (!pScene)
		LuaHelp::PushDataPointerToTable(L, NULL, 0);
	else
	{
		int x, y;
		((Entity*)et)->GetPosition(x, y);
		pScene->GetEntityList(x, y, vec, -nRadio, nRadio, -nRadio, nRadio);

		return getEntityFromRange(vec, L);
	}

	return 1;
}


int getNearEntityListFromXY(lua_State* L)
{
	void* scene = ((void*)  tolua_touserdata(L, 1, 0));

	if (scene == NULL) return 0;

	int x = (int)tolua_tonumber(L, 2, 0);
	int y = (int)tolua_tonumber(L, 3, 0);
	int nRadio = (int)tolua_tonumber(L, 4, 0);

	VisiHandleList& vec = GameEngine::global_var_->fb_visible_list_;
	vec.clear();

	((Scene*)scene)->GetEntityList(x, y, vec, -nRadio, nRadio, -nRadio, nRadio);

	return getEntityFromRange(vec, L);

}


int getNearEntityListFromRange(lua_State* L)
{
	void* pScene = ((void*)  tolua_touserdata(L, 1, 0));

	if (pScene == NULL) return 0;

	int x = (int)tolua_tonumber(L, 2, 0);
	int y = (int)tolua_tonumber(L, 3, 0);
	int width = (int)tolua_tonumber(L, 4, 0);
	int height = (int)tolua_tonumber(L, 5, 0);
	tolua_tonumber(L, 6, 0);

	VisiHandleList& vec = GameEngine::global_var_->fb_visible_list_;
	vec.clear();

	((Scene*)pScene)->GetEntityList(x, y, vec, -width, width, -height, height);

	return getEntityFromRange(vec, L);
}

int getEntityListFromRange(lua_State* L)
{
	void* pScene = ((void*)  tolua_touserdata(L, 1, 0));

	if (pScene == NULL) return 0;

	int luX = (int)tolua_tonumber(L, 2, 0);
	int luY = (int)tolua_tonumber(L, 3, 0);
	int rdX = (int)tolua_tonumber(L, 4, 0);
	int rdY = (int)tolua_tonumber(L, 5, 0);

	VisiHandleList& vec = GameEngine::global_var_->fb_visible_list_;
	vec.clear();

	((Scene*)pScene)->GetEntityList(luX, luY, vec, 0, rdX - luX, 0, rdY - luY);

	return getEntityFromRange(vec, L);
}



int getAllActorList(lua_State* L)
{
	void* actorList[8192];
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = em->GetOnlineActorPtrList(actorList, 8192);
	LuaHelp::PushDataPointerToTable(L, (void**)(actorList), count);
	return 1;
}


int getSceneActorListById(lua_State* L)
{
	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
	int sid = (int)tolua_tonumber(L, 1, 0);
	Scene* pScene = fbMgr->GetFbStaticDataPtr(0)->GetScene(sid);
	return getSceneEntityList(pScene, L, enActor);
}


int getSceneNpcListById(lua_State* L)
{
	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
	int sid = (int)tolua_tonumber(L, 1, 0);
	Scene* pScene = fbMgr->GetFbStaticDataPtr(0)->GetScene(sid);

	return getSceneEntityList(pScene, L, enNpc);
}

int getSceneMonsterListByScene(lua_State* L)
{
	Scene* pScene = (Scene*)tolua_touserdata(L, 1, 0);

	return getSceneEntityList(pScene, L, enMonster);
}

int getSceneMonsterList(lua_State* L)
{
	Entity* et = (Entity*)tolua_touserdata(L, 1, 0);

	if (!et) return 0;

	Scene* pScene = et->GetScene();

	return getSceneEntityList(pScene, L, enMonster);
}

int getSceneActorList(lua_State* L)
{
	Entity* et = (Entity*)tolua_touserdata(L, 1, 0);

	if (!et) return 0;

	Scene* pScene = et->GetScene();
	return getSceneEntityList(pScene, L, enActor);
}

int getRankingItemList(lua_State* L)
{
	void* pRank = ((void*)  tolua_touserdata(L, 1, 0));

	if (pRank == NULL) return 0;

	int nCount = (int)tolua_tonumber(L, 2, 0); //需要返回前N名

	Vector<RankingItem*>& itemList = ((CRanking*)pRank)->GetList();
	Vector<void*>* pList = (Vector<void*>*)(&itemList);
	nCount = __min(nCount, (int)itemList.count());
	LuaHelp::PushDataPointerToTable(L, (void**)(*pList), nCount);

	return 1;
}

int getFbActorList(lua_State* L)
{
	void* pFb = ((void*)  tolua_touserdata(L, 1, 0));

	if (pFb == NULL) return 0;

	void* actorList[8192];
	int count = 0;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	FuBen::SceneList& sl = ((FuBen*)pFb)->GetSceneList();

	for (int i = 0; i < sl.count(); i++)
	{
		Scene* pScene = sl[i];

		if (pScene)
		{
			EntityList& list = pScene->GetPlayList();
			LinkedNode<EntityHandle>* pNode;
			ListIterator<EntityHandle> it(list);

			for (pNode = it.first(); count < 8192 && pNode; pNode = it.next())
			{
				Entity* pe = em->GetEntity(pNode->data_);

				if (pe && pe->GetType() == enActor)
				{
					actorList[count++] = pe;
				}
			}
		}
	}

	LuaHelp::PushDataPointerToTable(L, actorList, count);

	return 1;
}

int getVisiActorList(lua_State* L)
{
	void* pEntity = ((void*)  tolua_touserdata(L, 1, 0));

	if (pEntity == NULL) return 0;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	StaticArrayList<void*, 8192> pEntityList;

	const VisiHandleList* entityList = ((Animal*)pEntity)->GetObserverSystem().GetVisibleList();

	if (!entityList) return 0;

	const EntityHandle* list = *entityList;
	int count = entityList->count();

	for (int i = 0; i < count; ++i)
	{
		Entity* pEntity = em->GetEntity(list[i]);

		if (pEntity && pEntity->GetType() == enActor)
		{
			pEntityList.add(pEntity);

			if (pEntityList.count() >= 8192) break;
		}
	}

	LuaHelp::PushDataPointerToTable(L, (void**)(pEntityList), pEntityList.count());
	return 1;
}

int getSceneActorListByPtr(lua_State* L)
{
	Scene* pScene = (Scene*)tolua_touserdata(L, 1, 0);

	return getSceneEntityList(pScene, L, enActor);
}

}


