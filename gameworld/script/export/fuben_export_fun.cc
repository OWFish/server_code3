#include "StdAfx.h"
#include "../interface/fuben_export_fun.h"
#include "monster/monster_config.h"


namespace Fuben
{

unsigned int createFuBen(int fbid)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->CreateFuBen(fbid);
	return fb ? (unsigned int)fb->GetHandle() : 0;
}

void closeFuben(unsigned int hFuben)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetFubenPtr(hFuben);

	if (fb)
	{
		mgr->ReleaseFuBen(fb);
	}
}

void setEnd(unsigned int hFuben)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetFubenPtr(hFuben);

	if (fb)
		fb->SetEnd();
}

void setBelong(unsigned int hFuben)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetFubenPtr(hFuben);

	if (fb)
		fb->SetBelong();
}

void setIsNeedAi(unsigned int hFuben, bool canRun)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetFubenPtr(hFuben);

	if (fb)
		fb->SetIsNeedAi(canRun);
}

unsigned int getFubenHandle(void* pFuben)
{
	return pFuben ? (unsigned int)(((FuBen*)pFuben)->GetHandle()) : 0;
}

void* getFubenPtr(unsigned int hFuben)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	return mgr->fb_hdl_mgr_.GetPtr(hFuben);
}

unsigned int getStaticFubenHandle()
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetStaticFuben();

	return fb ? (unsigned int)fb->GetHandle() : 0;
}

void* createMonster(unsigned int hScene, unsigned int nMonsterid, int posX, int posY, unsigned int nLiveTime, void* met)//, int tarX, int tarY)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	return mgr->CreateMonster(hScene, nMonsterid, Pos(posX, posY), nLiveTime, met);//, tarX, tarY);
}

void* createDropBag(unsigned int hScene, int type, int id, int count, int x, int y, int belong_id)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	return mgr->createDropBag(hScene, type, id, count, x, y, belong_id);
}

int RewardDropBag(lua_State* L)
{
	tolua_Error err;
	if (!tolua_isnumber(L, 1, 0, &err) || !tolua_isnumber(L, 2, 0, &err) || !tolua_isnumber(L, 3, 0, &err) || !tolua_istable(L, 5, 0, &err))
	{
		tolua_error(L, (char*)"#ferror in function 'DropBag'.", &err);
		return 0;
	}
	static int16_t s_matrix[][2] = {{ 0,0 },//原点
	{-1,+1},{0,+1},{+1,+1},{+1,0},{+1,-1},{0,-1},{-1,-1},{-1,0},//第一圈
	{-2,+2},{-1,+2},{0,+2},{+1,+2},{+2,+2},{+2,+1},{+2,0},{+2,-1},//第二圈
	{+2,-2},{+1,-2},{0,-2},{-1,-2},{-2,-2},{-2,-1},{-2,0},{-2,+1},
	{-3,+3},{-2,+3},{-1,+3},{0,+3},{+1,+3},{+2,+3},{+3,+3},{+3,+2},//第三圈
	{+3,+1},{+3,-0},{+3,-1},{+3,-2},{+3,-3},{+2,-3},{+1,-3},{0,-3},
	{-1,-3},{-2,-4},{-3,-3},{-3,-2},{-3,-1},{-3,0},{-3,+1},{-3,+2},
	{-4,+4},{-3,+4},{-2,+4},{-1,+4},{0,+4},{+1,+4},{+2,+4},{+3,+4},//第四圈
	{+4,+4},{+4,+3},{+4,+2},{+4,+1},{+4,-0},{+4,-1},{+4,-2},{+4,-3},
	{+4,-4},{+3,-4},{+2,-4},{+1,-4},{0,-4},{-1,-4},{-2,-5},{-3,-4},
	{-4,-4},{-4,-3},{-4,-2},{-4,-1},{-4,0},{-4,+1},{-4,+2},{-4,+3},
	{-5,+5},{-4,+5},{-3,+5},{-2,+5},{-1,+5},{0,+5},{+1,+5},{+2,+5},//第五圈
	{+3,+5},{+4,+5},{+5,+5},{+5,+4},{+5,+3},{+5,+2},{+5,+1},{+5,-0},
	{+5,-1},{+5,-2},{+5,-3},{+5,-4},{+5,-5},{+4,-5},{+3,-5},{+2,-5},
	{+1,-5},{0,-5},{-1,-5},{-2,-6},{-3,-5},{-4,-5},{-5,-5},{-5,-4},
	{-5,-3},{-5,-2},{-5,-1},{-5,0},{-5,+1},{-5,+2},{-5,+3},{-5,+4},
	{-6,+6},{-5,+6},{-4,+6},{-3,+6},{-2,+6},{-1,+6},{0,+6},{+1,+6},//第六圈
	{+2,+6},{+3,+6},{+4,+6},{+5,+6},{+6,+6},{+6,+5},{+6,+4},{+6,+3},
	{+6,+2},{+6,+1},{+6,0},{+6,-1},{+6,-2},{+6,-3},{+6,-4},{+6,-5},
	{+6,-6},{+5,-6},{+4,-6},{+3,-6},{+2,-6},{+1,-6},{0,-6},{-1,-6},
	{-2,-6},{-3,-6},{-4,-6},{-5,-6},{-6,-6},{-6,-5},{-6,-4},{-6,-3},
	{-6,-2},{-6,-1},{-6,0},{-6,+1},{-6,+2},{-6,+3},{-6,+4},{-6,+5}
	};
	static uint16_t s_matrix_count = ArrayCount(s_matrix);

	unsigned int hScene = static_cast<int>( lua_tonumber(L, 1) );
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	Scene *scene = mgr->GetScenePtr(hScene);
	if (!scene) return 0;
	int x = static_cast<int>( lua_tonumber(L, 2));
	int y = static_cast<int>( lua_tonumber(L, 3));
	if ((x == 0 && y == 0)) {
		x = scene->GetSceneConf()->enter_x;
		y = scene->GetSceneConf()->enter_y;
	}
	ActorId belong_id = static_cast<int>( lua_tonumber(L, 4));

	int index = 0;
	lua_pushnil(L);
	while (lua_next(L, 5)) {
		int it_idx = lua_gettop(L);
		lua_pushnil(L);
		int type = 0, id = 0, count = 0;
		while (lua_next(L, it_idx)) {
			const char* strkey = lua_tostring(L, -2);
			if (strcmp(strkey, "type") == 0) {
				type = (int)lua_tonumber(L, -1);
			}
			else if (strcmp(strkey, "id") == 0) {
				id = (int)lua_tonumber(L, -1);
			}
			else if (strcmp(strkey, "count") == 0) {
				count = (int)lua_tonumber(L, -1);
			}
			lua_pop(L, 1);
		}
		if (count) {
			if (index > s_matrix_count) index = 0;
			int nx = x, ny = y;
			do
			{
				nx = x + s_matrix[index][0];
				ny = y + s_matrix[index][1];
				++index;
			} while (!scene->CanMove(Grid(nx, ny)) && index < s_matrix_count);
			if (!scene->CanMove(Grid(nx, ny))) {
				nx = x;
				ny = y;
				OutputMsg(rmError, "DropBag(%d,%d) all grid is not CanMove", x, y);
			}
			mgr->createDropBag(hScene, type, id, count, nx, ny, belong_id);
		}
		lua_pop(L, 1);
	}



	return 0;
}

//void createMonsters(unsigned int hScene, unsigned int nMonsterid, int posX1, int posX2, int posY1, int posY2, int nCount, unsigned int nLiveTime,int tarX, int tarY)
//{
//	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
//	Scene* scene = mgr->GetScenePtr(hScene);
//
//	static MonsterConfPool& pool = *MonsterConfPool::config_;
//	PMONSTERCONFIG config = pool.GetMonsterData(nMonsterid);
//
//	if (!config || !scene) return;
//
//	if (posX2 < posX1)
//		posX2 = posX1;
//
//	if (posY2 < posY1)
//		posY2 = posY1;
//
//	int dx = posX2 - posX1;
//	int dy = posY2 - posY1;
//
//	for (int i = 0; i < nCount; i++)
//	{
//		unsigned long seed = posX2 - posX1;
//		seed = wrand(seed + 1);
//		int px = wrand(dx + 1);
//		int py = wrand(dy + 1);
//
//		int dir = -1;
//		if (tarX != -1 && tarY != -1)
//			dir = Entity::GetDir(posX1 + px, posY1 + py, tarX, tarY);
//
//		Entity* pMonster =
//		    scene->CreateEntityAndEnter(nMonsterid, config->btEntityType, posX1 + px, posY1 + py,"", -1, NULL, false, false, NULL, dir);
//
//		if (pMonster != NULL)
//		{
//			//pScene->SetMonsterConfig(pMonster, -1, nMonsterid);
//			((Monster*)pMonster)->SetLiveTIme(nLiveTime);
//		}
//	}
//}

void sendData(unsigned int hdl, void* dp)
{
	if (!dp) return;

	DataPacket* pack = (DataPacket*)dp;

	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);

	if (!fb) return;

	fb->SendData(pack->getMemoryPtr(), pack->getLength());
}
void sendDataNoActor(unsigned int hdl, void* dp,void* actor)
{
	if (!dp) return;

	DataPacket* pack = (DataPacket*)dp;

	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);

	if (!fb) return;

	fb->SendDataNoActor(pack->getMemoryPtr(), pack->getLength(), (Actor*)actor);
}

int getAllActor(lua_State* L)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	unsigned int hdl = (unsigned int)lua_tonumber(L, 1);
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb)
	{
		return 0;
	}
	auto ret = fb->GetAllActor();
	if (!ret.empty())
	{
		LuaHelp::PushDataPointerToTable(L, (void**)&ret[0], ret.size());
		return 1;
	}
	return 0;
}
int getAllMonster(lua_State* L)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	unsigned int hdl = (unsigned int)lua_tonumber(L, 1);
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb)
	{
		return 0;
	}
	auto ret = fb->GetAllMonster();
	if (!ret.empty())
	{
		LuaHelp::PushDataPointerToTable(L, (void**)&ret[0], ret.size());
		return 1;
	}
	return 0;
}
int getAllDropBag(lua_State* L)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	unsigned int hdl = (unsigned int)lua_tonumber(L, 1);
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb)
	{
		return 0;
	}
	auto ret = fb->GetAllDropBag();
	if (!ret.empty())
	{
		LuaHelp::PushDataPointerToTable(L, (void**)&ret[0], ret.size());
		return 1;
	}
	return 0;
}

int getAllCloneRole(lua_State* L) {
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	unsigned int hdl = (unsigned int)lua_tonumber(L, 1);
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb) {
		return 0;
	}
	std::vector<RoleClone*> ret;
	fb->GetAllCloneRole(ret);
	if (!ret.empty()) {
		LuaHelp::PushDataPointerToTable(L, (void**)&ret[0], ret.size());
		return 1;
	}
	return 0;
}

int getActorCount(unsigned int hdl) {
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb) {
		return 0;
	}
	return fb->getActorCount();
}

int GetResActorMirrorCount(unsigned int hdl)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb)
	{
		return 0;
	}
	return fb->GetResCloneRoleCount();
}

void * getCloneRole(unsigned int hdl,int ActorID)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	if (!fb)
	{
		return nullptr;
	}

	return fb->GetCloneRoleByID(ActorID);
}

void releaseInstance(void *fb)
{
	static FuBenMgr *fm = GetGameEngine()->GetFuBenMgr();
	fm->ReleaseFuBen((FuBen*)fb);
}

int getMonsterId(void *mon)
{
	if (!mon)
		return 0;
	if (((Entity*)mon)->GetType() != EntityType_Monster) return 0;
	return ((Monster*)mon)->GetId();
}

bool isKillAllMonster(unsigned int hScene, int monId)
{
	Scene* pScene = GetGameEngine()->GetFuBenMgr()->GetScenePtr(hScene);

	if (pScene)
	{
		return pScene->IsKillAllMonster(monId);
	}

	return false;
}

void killAllMonster(unsigned int hScene)
{
	Scene* pScene = GetGameEngine()->GetFuBenMgr()->GetScenePtr(hScene);

	if (pScene)
		pScene->KillFubenMonsters();
}

void clearAllMonster(unsigned int hScene)
{
	Scene* scene = GetGameEngine()->GetFuBenMgr()->GetScenePtr(hScene);
	if (!scene) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	EntityList& list = scene->GetMonsterList();
	ListIterator<EntityHandle> it(list);

	for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
	{
		Entity* et = em->GetEntity(node->data_);
		if (et)
			em->DestroyEntity(et->GetHandle(), true);
	}
}

void clearAllCloneRole(unsigned int hScene) {
	Scene* scene = GetGameEngine()->GetFuBenMgr()->GetScenePtr(hScene);
	if (!scene) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	EntityList& list = scene->GetCloneRoleList();
	ListIterator<EntityHandle> it(list);

	for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next()) {
		Entity* et = em->GetEntity(node->data_);
		if (et)
			em->DestroyEntity(et->GetHandle(), true);
	}
}

void clearCloneRoleById(unsigned int hScene, int actor_id) 	{
	Scene* scene = GetGameEngine()->GetFuBenMgr()->GetScenePtr(hScene);
	if (!scene) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	EntityList& list = scene->GetCloneRoleList();
	ListIterator<EntityHandle> it(list);

	for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next()) {
		Entity* et = em->GetEntity(node->data_);
		if (et && et->GetType() == EntityType_CloneRole) {
			if(((RoleClone *)et)->GetActorId() == actor_id) {
				for (int i = 0; i < MAX_ROLE; ++i) {
					EntityHandle hdl;
					if (((RoleClone*)et)->GetBuddy(i, hdl)) {
						auto roleClone = em->GetEntity(hdl);
						if (!roleClone) continue;
						em->DestroyEntity(roleClone->GetHandle(), true);
					}
				}
				break;
			}
		}
	}
}

double getMonsterMaxHp(int id)
{
	const MonsterConfig* conf = MonsterConfigPool::Get(id);
	if (conf == NULL) return 0;
	return conf->attrs.hp;
}

void setMonsterCamp(void *mon, int camp)
{
	if (!mon) return;
	if (((Entity*)mon)->GetType() != EntityType_Monster) return;
	((Creature*)mon)->SetCamp(camp);
}

void setBaseAttr(void *mon, float rate)
{
	if (!mon) return;
	if (rate == 0) return;
	if (((Entity*)mon)->GetType() != EntityType_Monster) return;

	((Monster*)mon)->ResetBasicAttr(rate);
}

void* getSceneMonsterById(void *pScene, int targetId)
{
	if (!pScene) return NULL;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	auto &monster_list = ((Scene*)pScene)->GetMonsterList();
	LinkedNode<EntityHandle>* node;
	ListIterator<EntityHandle> it(monster_list);

	for (node = it.first(); node; node = it.next())
	{
		Monster* mon = (Monster*)em->GetEntity(node->data_);
		int monId = mon->GetId();
		if (monId == targetId)
		{
			return mon;
		}
	}
	return NULL;
}

int Getscenelist(lua_State *L)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	unsigned int hdl = (unsigned int)lua_tonumber(L, 1);
	FuBen* fb = mgr->fb_hdl_mgr_.GetPtr(hdl);
	
	Scene** scenelist = fb->GetSceneList();
	
	if (!fb)
	{
		return 0;
	}
	
	LuaHelp::PushDataPointerToTable(L, (void**)scenelist, fb->scene_list_.size());
	return 1;	
}

unsigned int getSceneHandlebyPtr(void *pScene)
{
	if (!pScene) return 0;
	return ((Scene*)pScene)->GetHandle();
}

};
