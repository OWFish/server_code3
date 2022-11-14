#include "StdAfx.h"
#include "fuben_mgr.h"

#include "entity/monster/monster_config.h"
#include "entity/monster/gather_monster.h"

FuBenMgr::FuBenMgr(void) 
: ref_timer_(500)
, logic_script_timer_(1000)
, fb_hdl_mgr_("FubenHdlMgr")
, scene_hdl_mgr_("SceneHdlMgr")
{
}

void FuBenMgr::Destroy()
{

	for (int i = all_fb_list_.count() - 1; i >= 0; --i)
	{
		FuBen* fb = all_fb_list_[i];

		if (fb)
		{
			fb->ExitAllActor();
			fb_hdl_mgr_.Free(fb->GetHandle());
			fb_map_.erase(fb->GetFbUId());
		}
	}

	all_fb_list_.clear();

	//for (int i = 0; i < static_fb_list_.count(); i++)
	//{
	//	FuBen* fb = static_fb_list_[i];

	//	if (fb)
	//	{
	//		// 里面会执行副本的析构函数
	//		fb_hdl_mgr_.Free(fb->GetHandle());
	//	}
	//}

	//static_fb_list_.clear();

	//for (int i = 0; i < free_fb_list_.count(); i++)
	//{
	//	FubenList* list = free_fb_list_[i];

	//	if (list)
	//	{
	//		for (int j = 0; j < list->count(); j++)
	//		{
	//			FuBen* fb = (*list)[j];

	//			if (fb)
	//			{
	//				fb_hdl_mgr_.Free(fb->GetHandle());
	//			}
	//		}

	//		list->clear();
	//		delete list;
	//	}
	//}

	//free_fb_list_.clear();

/*	for (int i = 0; i < map_data_list.count(); i++)
	{
		MAPDATA* md = map_data_list[i];
		delete md->map_data_;
		delete md;
	}

	map_data_list.clear()*/;
}

FuBenMgr::~FuBenMgr(void)
{
	Destroy();
}


FuBen* FuBenMgr::AllocNewFb(int fbid, bool run)
{
	FuBen* newFb = NULL;
	//FuBen* fuben = static_fb_list_[fbid];

	//从内存管理中获取一个新的CFuBen
	FuBenHandle handle;
	newFb = fb_hdl_mgr_.AllocHandle(handle);
	if (newFb->Init(fbid))
	{
		newFb->SetHandle(handle);
		newFb->SetFbUId(AllocNewUId());
		all_fb_list_.add(newFb);
		fb_map_[newFb->GetFbUId()] = newFb;
	}
	else
	{
		fb_hdl_mgr_.Free(handle);
		newFb = nullptr;
	}
	return newFb;
}

Scene* FuBenMgr::AllocNewScene(FuBen *fb, int sid)
{
	Scene *newscene;
	SceneHandle handle;
	newscene = scene_hdl_mgr_.AllocHandle(handle);

	if (newscene->Init(fb, sid))
		newscene->SetHandle(handle);
	else
	{
		scene_hdl_mgr_.Free(handle);
		return nullptr;
	}
	return newscene;
}

FuBenUId FuBenMgr::AllocNewUId()
{
	auto now_t = GetGameEngine()->getMiniDateTime();
	if (fb_series_.time != now_t)
		fb_series_.series = 0;
	fb_series_.time = now_t;
	fb_series_.series++;

	return fb_series_.uid;
}

FuBen* FuBenMgr::CreateFuBen(int fbId)
{
	FuBen* newFb = AllocNewFb(fbId);

	if (!newFb) return nullptr;

	// OutputMsg(rmTip, "createFuben success %d", fbId);

	ScriptValueList arg;
	arg << fbId;
	arg << newFb->GetHandle();

	const FubenConfig* conf = newFb->GetConfig();
	
	for (std::size_t i = 0; i < conf->scenes.size(); ++i)
	{
		int id = conf->scenes[i];

		Scene *newScene = AllocNewScene(newFb, id);
		if (newScene == nullptr)
		{
			fb_hdl_mgr_.Free(newFb);
			return NULL;
		}
		newFb->scene_list_.add(newScene);
		//arg << newScene->GetHandle();
		
	}


	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("createInstance", &arg, &arg, 0);
	//OutputMsg(rmTip, "createInstance. hdl:%u", newFb->GetHandle());

	return newFb;
}

void FuBenMgr::ReleaseFuBen(FuBen* fb)
{
	if (!fb || !fb->IsFb()) return;		// 常规副本不能这里关闭

	fb->SetReleased();
	fb->ExitAllActor();
}

void FuBenMgr::RunOne()
{
	//执行每个副本的runone
	int64_t start_t = _getTickCount(); //自行开始

	if (!ref_timer_.CheckAndSet(start_t))
		return;

	if (logic_script_timer_.CheckAndSet(start_t))
	{
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("onInstanceRun", NULL, NULL, 0);
	}

	//int64_t loopLimit = GetLoopTickLimit();

	// 释放内存和执行逻辑分开两个循环，避免执行逻辑的时候删除副本造成宕机
	for (int i = 0; i < all_fb_list_.count(); ++i)
	{
		FuBen* fb = all_fb_list_[i];
		//int fbId = fb->GetFbId();

		if (fb->IsReleased())
		{
			fb_hdl_mgr_.Free(fb->GetHandle());
			all_fb_list_.remove(i);
			fb_map_.erase(fb->GetFbUId());
			--i;	// 因为是从头遍历，这里删除则必须--i;
		}
	}

	for (int i = 0; i < all_fb_list_.count(); ++i)
	{
		FuBen* fb = all_fb_list_[i];
		int fbId = fb->GetFbId();

		int ret = fb->RunOne();

			/*if (ret == 1 || _getTickCount() - start_t > loopLimit)
			{
				if (ret != 1)
				{
					// 副本正常结束，但是总的时间超时了
					refreshPara_.setFB((i < all_fb_list_.count()) ? list[i] : NULL);
				}

				SetLoopTickCount(_getTickCount() - start_t);
				return;
			}
			else */

		if (ret != 0)
		{
			OutputMsg(rmTip, ("release fuben!fubenid=%d"), fbId);
			fb->ExitAllActor();

			fb->SetReleased(); // 下一个循环再删除，以便做清理工作
		}
	}

	//refreshPara_.setFB(NULL);
}

bool FuBenMgr::EnterFuBen(Entity* et, FuBen* fb, int sid, int x, int y, bool pix)
{
	if (et == NULL) return false;
	if (fb == NULL) return false;

	return fb->Enter(et, sid, x, y, pix);
}


bool FuBenMgr::CreateStaticFuBen()
{
	static_fb_ = CreateFuBen(0);

	if (!static_fb_) return false;

	return true;
}

//
//void FuBenMgr::AddStaticFuBen(FuBen* newfb)
//{
//	if (!newfb) return;
//
//	for (int i = 0; i < static_fb_list_.count(); i++)
//	{
//		FuBen* fb = static_fb_list_[i];
//
//		if (fb && fb->GetFbId() == newfb->GetFbId())
//		{
//			// 里面会执行副本的析构函数
//			fb_hdl_mgr_.Free(fb->GetHandle());
//			// 释放掉原来的副本，替换上新的
//			static_fb_list_[i] = newfb;
//			return;
//		}
//	}
//
//	assert(static_fb_list_.count() == (newfb->GetFbId()));
//
//	// 全新的副本，就放到列表的最后面
//	static_fb_list_.add(newfb);
//}

//GameMap* FuBenMgr::GetMapData(const char* fn, bool newver)
//{
//	if (!fn) return NULL;
//
//	MAPDATA* data = NULL;
//
//	for (int i = 0; i < map_data_list.count(); i++)
//	{
//		data = map_data_list[i];
//
//		if (strcmp(fn, data->file_) == 0)
//		{
//			return data->map_data_;
//		}
//	}
//
//	//暂时没有数据，读入
//	data = new MAPDATA();
//	_STRNCPY_A(data->file_, fn);
//
//	data->map_data_ = new GameMap();
//
//	if (!data->map_data_->LoadFromFile(fn, newver))
//	{
//		delete data->map_data_;
//		delete data;
//		return false;
//	}
//
//	map_data_list.add(data);
//	return data->map_data_;
//}

//int FuBenMgr::GetFbCountFromId(int fbId, unsigned int* list, size_t size)
//{
//	int ret = 0;
//	int count = all_fb_list_.count();
//	FuBen** fbList = all_fb_list_;
//
//	for (int i = 0; i < count; ++i)
//	{
//		FuBen* fb = fbList[i];
//
//		if (fb && fb->GetConfig()->fb_id_ == fbId)
//		{
//			list[ret++] = fb->GetHandle();
//		}
//	}
//
//	return ret;
//}


//void FuBenMgr::RefreshMonster()
//{
//	for (int i = 0; i < static_fb_list_.count(); i++)
//	{
//		FuBen* fb = static_fb_list_[i];
//		fb->RefreshMonster();
//	}
//}

void* FuBenMgr::CreateMonster(unsigned int hScene, unsigned int nMonsterid, Pos pos, unsigned int nLiveTime, void* met)
{
	auto conf = MonsterConfigPool::Get(nMonsterid);
	if (!conf)
	{
		return nullptr;
	}
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	Scene* scene = GetScenePtr(hScene);

	if (!scene) return NULL;

	EntityHandle hdl;
	if (conf->type != MonsterType_GatherMonster)
	{
		Monster *monster = (Monster*)em->CreateEntity(EntityType_Monster, hdl);

		if (monster != NULL)
		{
			if (met) {
				monster->SetMasterHandle(((Entity*)met)->GetHandle());
			}
			if (!monster->Init(nMonsterid) || !scene->EnterScene(monster, pos.x, pos.y))
			{
				em->DestroyEntity(hdl);
				return NULL;
			}

			monster->SetLiveTIme(nLiveTime);
			FuBen* fb = scene->GetFuBen();
			if (fb)
			{
				int fbId = fb->GetFbId();
				if (fbId > 0)
				{
					fb->OnMonsterEnter(monster);
				}
			}
		}

		return monster;
	}
	else
	{

		//OutputMsg(rmError, " 创建采集怪");
		GatherMonster* monster = (GatherMonster*)em->CreateEntity(EntityType_GatherMonster, hdl);
		if (monster != nullptr)
		{
			if (!monster->Init(nMonsterid) || !scene->EnterScene(monster, pos.x, pos.y))
			{
				em->DestroyEntity(hdl);
				return nullptr;
			}
		}
		return monster;
	}
}

void* FuBenMgr::createDropBag(unsigned int hScene, int type, int id, int count, int x, int y, ActorId belong_id)
{
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	Scene* scene = GetScenePtr(hScene);
	if (!scene) return NULL;

	EntityHandle hdl;
	DropBag* drop = (DropBag*)em->CreateEntity(EntityType_DropBag, hdl);

	if (drop != NULL)
	{
		if (!drop->Init(type, id, count, belong_id) || !scene->EnterScene(drop, x, y))
		{
			em->DestroyEntity(hdl);
			return NULL;
		}
	}

	return drop;
}

void FuBenMgr::GC()
{
//#ifdef REUSEFB
//
//	for (int i = 1; i < free_fb_list_.count(); i++)
//	{
//		FubenList* list = free_fb_list_[i];
//
//		if (!list) continue;
//
//		FubenConf* conf = GetConfig(i);
//		int total = list->count();
//
//		if (conf && total > conf->cache_count_)
//		{
//			int freeCnt = total - conf->cache_count_;
//
//			for (int j = 1; j <= freeCnt; j++)
//			{
//				FuBen* fb = list->get(total - j);
//
//				if (fb)
//				{
//					fb_hdl_mgr_.Free(fb->GetHandle());//里面会执行副本的析构函数
//				}
//			}
//
//			list->trunc(conf->cache_count_);
//		}
//	}
//
//#endif
}

FuBen* FuBenMgr::GetFubenPtr(FuBenHandle handle)
{
	return fb_hdl_mgr_.GetPtr(handle);
}

FuBen* FuBenMgr::GetFuben(FuBenUId uid)
{
	auto it = fb_map_.find(uid);
	if (it == fb_map_.end())
		return NULL;
	return it->second;
}
FuBen* FuBenMgr::GetFubenFromID(int id)
{
	if (id == 0)
		return NULL;
	std::map<FuBenUId, FuBen*>::iterator it = fb_map_.begin();
	for (; it != fb_map_.end(); ++it)
	{
		if (it->second->fb_id_ == id)
		{
			return it->second;
		}
	}
	return NULL;


}
Scene* FuBenMgr::GetScenePtr(SceneHandle handle)
{
	return scene_hdl_mgr_.GetPtr(handle);
}

void FuBenMgr::FreeScene(SceneHandle handle)
{
	scene_hdl_mgr_.Free(handle);
}

void FuBenMgr::RegMonsterDamageEvent(int fid)
{
	fb_monster_damage_event_flags_[fid] = true;
}

bool FuBenMgr::HasMonsterDamageEvent(int fid)
{
	auto it = fb_monster_damage_event_flags_.find(fid);
	if (it == fb_monster_damage_event_flags_.end())
		return false;
	return it->second;
}

void FuBenMgr::RegActorDamageEvent(int fid) {
	fb_actor_damage_event_flags_[fid] = true;
}

bool FuBenMgr::HasActorDamageEvent(int fid) {
	auto it = fb_actor_damage_event_flags_.find(fid);
	if (it == fb_actor_damage_event_flags_.end())
		return false;
	return it->second;
}

//Scene* FuBenMgr::AllocSceneHandle(SceneHandle& handle)
//{
//	return scene_hdl_mgr_.AllocHandle(handle) ;
//}

//FuBen* FuBenMgr::AllocFubenHandle(FuBenHandle& handle)
//{
//	return fb_hdl_mgr_.AllocHandle(handle);
//}

//bool FuBenMgr::ReSceneNew(SceneHandle& handle)
//{
//	return  scene_hdl_mgr_.ReNew(handle);
//}
//
//bool FuBenMgr::ReFubenNew(FuBenHandle& handle)
//{
//	return fb_hdl_mgr_.ReNew(handle);
//}

FuBen* FBHandleMgr::GetPtr(FuBenHandle handle)
{
	FuBen* fb = Inherited::GetPtr(handle);

	return fb;
}

FBHandleMgr::FBHandleMgr(const char* desc): Inherited(desc)
{
}


