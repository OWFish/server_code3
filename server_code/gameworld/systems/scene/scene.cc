#include "StdAfx.h"
#include "scene.h"
#include "entity/actor/actor.h"
#include "fuben.h"
#include "fuben_config.h"
#include "protocol/protos/base_proto.h"
#include "map_mgr.h"


using namespace container;

Scene::Scene()
	: death_list_timer_(500)
{
	map_ = NULL;
	scene_conf_ = NULL;
	scene_size_output_counter_ = 1;
	//grid_.SetScene(this);
}

Scene::~Scene()
{
	//释放所有的实体
	//ReleaseConfig();

	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int type = 0; type < EntityType_Count; ++type)
	{
		ListIterator<EntityHandle> it(entity_list_[type]);
		for (auto node = it.first(); node; node = it.next())
		{
			Entity* et = em->GetEntity(node->data_);
			if (et) {
				if (et->GetType() == EntityType_Actor)
					OutputMsg(rmError, ("destory scene error!!!!there is actor in this scene! %d,%d"), scene_conf_?scene_conf_->sid:0, et->GetActorId());
				em->DestroyEntity(node->data_);
			}
		}
	}
}

bool Scene::Init(FuBen* fuben, int id)
{
	fuben_ = fuben;
	scene_conf_ = SceneConfigPool::Get(id);
	if (!fuben_ || !scene_conf_)
		return false;
	map_ = MapMgr::instance().GetMap(scene_conf_->map_data.c_str());

	//grid_.Init();
	//grid_.SetScene(this);

	return true;
}

bool Scene::EnterScene(Entity* et, int x, int y, bool pix)
{
	if (!et) return false;

	Scene* last = et->GetScene(); //获取实体上一个的场景
	if (last == this) return true;

	if ((x == 0 && y == 0)/* || !CanMove(Grid(x,y))*/) {
		//既然指定了坐标,不可走就先直接卡住再说,不要修正到配置的进入点了
		//在特殊需求和复杂情况下,这个进入点也许没用,或者也是个不可走点
		x = scene_conf_->enter_x;
		y = scene_conf_->enter_y;
		pix = false;
	}
	//int nx = x, ny = y;
	//if (pix) {
	//	Grid grid(Point(x, y));
	//	nx = grid.x; ny = grid.y;
	//}
	//if (grid_.AddEntity(et, nx, ny))
	//{
		// 先退出之前的场景
		if (last) last->ExitScene(et);
	//}
	//else
	//{
	//	return false;
	//}

	et->SetScene(this);
	if (pix) {
		et->SetPosition(Point(x, y));
		et->SetOriginPosition(Point(x, y));
	} else {
		et->SetPosition(Grid(x, y));
		et->SetOriginPosition(Grid(x, y).ToPoint());
	}
	et->SetFuBen(fuben_);

	OnEntityEnter(et);

	return true;
}

void Scene::ExitScene(Entity* et)
{
	EntityHandle handle = et->GetHandle();

	BroadcastDisappear(et);
	RemoveEntity(handle);
	//grid_.DelEntity(et);
	OnEntityExit(et);

	et->SetScene(NULL);
	et->SetFuBen(NULL);
}

void Scene::OnEntityEnter(Entity* et)
{
	EntityHandle handle = et->GetHandle();
	int type = handle.GetType();
	entity_list_[type].linkAtLast(handle);

	et->OnEnterScene();

	BroadcastAppear(et);
	
	
	/*if (et->isAnimal())
	{
		AMCommon* msg = AMCommon::alloc();
		msg->msg_ = AMCommon::AMTRANSFER;
		msg->delOnDeath_ = true;
		msg->sender_ = handle;
		msg->val_ = new_flag ? 0 : 1;	// 进入新场景，不需要发瞬移的消息给自己
		((Animal*)et)->PostActMsg(msg); // 发送瞬间移动的数据包
	}*/
	if (et->IsCreature())
	{
		LinkedNode<EntityHandle>* node;

		ListIterator<EntityHandle> it(death_list_);
		for (node = it.first(); node; node = it.next())
		{
			if (handle == node->data_)
			{
				it.remove(node);
				break;
			}
		}
	}
}

void Scene::OnActorEnter(Actor* actor)
{
	if (GetFuBen()->GetFbId() == 0) return;	// 静态场景不发送
	
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	static BaseAllocator baseAlloc("appear_data");
	static DataPacket appear_pack(&baseAlloc);
	for (int type = 0; type < EntityType_Count; ++type)
	{
		ListIterator<EntityHandle> it(entity_list_[type]);
		for (auto node = it.first(); node; node = it.next())
		{
			Entity* et = em->GetEntity(node->data_);
			if (et) {
				if (type == EntityType_Role) {
					if (et->GetActor() == actor)
						continue;	//考虑客户端处理实体顺序
					else if(GetFuBen()->IsFb() && GetFuBen()->GetConfig()->type == 0 && et->GetId())
						continue;
				}
				et->CreateAppearData(appear_pack);
				actor->SendData(appear_pack);
				//OutputMsg(rmTip, "onActor:%d Enter type:%d, id:%d, hdl:%lld",
				//	actor->GetActorId(), et->GetType(), et->GetId(), et->GetHandle());
			}
		}
	}
}


void Scene::OnEntityExit(Entity *et)
{
	et->OnExitScene();
}

bool Scene::RunOne()
{
	int64_t now_t = _getTickCount(); //这里要使用当前的逻辑时间

	//清除掉死亡的怪物
	if (death_list_timer_.CheckAndSet(now_t))
	{
		//检查死亡的实体
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		if (entity_list_[EntityType_Role].count() > 5 && scene_size_output_counter_ % 5 == 0)
		{
			OutputMsg(rmTip, "%s scene id:%d, count:%d",__FUNCTION__, GetId(), entity_list_[EntityType_Role].count());
			++scene_size_output_counter_;
		}

		ListIterator<EntityHandle> it(death_list_);

		for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
		{
			Entity* et = em->GetEntity(node->data_);
			if (et) {
				// 玩家死亡只是告诉玩家退出场景
				if (et->GetType() == EntityType_Role)
				{
					ExitScene(et);
				}
				else
				{
					et->SetInitFlag(false);
					em->DestroyEntity(node->data_);
				}
				it.remove(node);
			}
			else
			{
				it.remove(node);
			}
		}
	}

	///刷怪逻辑结束
	return true;
}

void Scene::AddDeathEntity(Entity* et)
{
	if (!et) return;
	
	EntityHandle handle = et->GetHandle();
	//int type = handle.GetType();
	RemoveEntity(handle);

	Creature* creature = (Creature*)et;

	if (!creature->IsInDeathList()) {
		creature->SetDestoryTime();
		death_list_.linkAtLast(handle);
	}
}


void Scene::BroadcastAppear(Entity* et)
{
	if (!et) return;
	if (et->GetType() == EntityType_Role) {
		Role* role = (Role*)et;
		if(et->IsDeath() || (GetFuBen()->IsFb() && GetFuBen()->GetConfig()->type == 0 && role->GetId())) {
			role->SetSendEntity(false);
			return;
		}
	}
	static BaseAllocator baseAlloc("appear_data");
	static DataPacket appear_pack(&baseAlloc);
	et->CreateAppearData(appear_pack);

	//OutputMsg(rmTip, "broadcastAppear type:%d, id:%d, hdl:%lld",
	//	et->GetType(), et->GetId(), et->GetHandle());

	if (GetFuBen()->GetFbId() == 0) {
		Entity* master = et->GetMaster();
		if (master && master->GetType() == EntityType_Actor)
			((Actor*)master)->SendData(appear_pack);
	}
	else {
		SendData(appear_pack);
	}
	if (et->GetType() == EntityType_Role)
	{
		Role* role = (Role*)et;
		role->SetSendEntity(true);
		return;
	}
}


void Scene::ExitAllActor()
{
	if (!fuben_->IsFb()) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	ListIterator<EntityHandle> it(entity_list_[EntityType_Actor]);

	for (LinkedNode<EntityHandle>* pNode = it.first(); pNode; pNode = it.next())
	{
		Entity* pEntity = em->GetEntity(pNode->data_);

		if (pEntity && pEntity->GetType() == enActor)
		{
			((Actor*)pEntity)->ReturnToStaticScene();
		}

		entity_list_[EntityType_Actor].remove(pNode);
	}
}

void Scene::RemoveEntity(EntityHandle handle)
{
	LinkedNode<EntityHandle>* node;
	int type = handle.GetType();
	EntityList& list = entity_list_[type];

	ListIterator<EntityHandle> it(list);
	for (node = it.first(); node; node = it.next())
	{
		if (handle == node->data_)
		{
			it.remove(node);
		}
	}
}

bool Scene::CanMove(const Grid& pos)
{
	if (map_) {
		int pos_x = pos.x;
		if (scene_conf_->turn) pos_x = map_->getWidth() - pos.x - 1; //反转图
		return map_->canMove(pos_x, pos.y);
	}
	if (pos.x < 0 || (scene_conf_->size_x > 0 && scene_conf_->size_x < pos.x))
		return false;
	if (pos.y < 0 || (scene_conf_->size_y > 0 && scene_conf_->size_y < pos.y))
		return false;
	return true;
}

bool Scene::MoveTo(Entity* et, const Point& pos)
{
	if (!et) return false;

	if (fuben_ && fuben_->GetConfig() && fuben_->GetConfig()->findPath != 0) {
		if (!CanMove(pos))
			return false;
	}

	et->SetPosition(pos);
	et->OnMove(pos);

	return true;
}

void Scene::SendData(const void* buf, size_t size, Actor* except)
{
	if (this == NULL) return; // 防止广播消息的时候忘记判断scene为空
	//const FubenConf* conf = fuben_ ? fuben_->GetConfig() : NULL;

	//static GameEngine* ge = GetGameEngine();

	//if (fuben_ && (!fuben_->IsFb() || (conf && conf->isUnique_)))
	//{
	//	ge->BroadCast(ciChannelMap, GetId(), buf, size);
	//}
	//else
	//{
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();

		ListIterator<EntityHandle> it(entity_list_[EntityType_Actor]);

		for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
		{
			Actor* actor = (Actor*)(em->GetEntity(node->data_));
			if (!actor) continue;
			if (except != NULL && except != actor) {
				//屏蔽自己的不发
				if (actor->need_hide_pack_ &&
					actor->need_pack_list_.find(except->GetHandle()) == actor->need_pack_list_.end()) 
					continue;
			}
			actor->SendData(buf, size);
		}
	//}
}
void Scene::SendDataNoActor(const void* buf, size_t size, Actor* except)
{
	if (this == NULL) return; // 防止广播消息的时候忘记判断scene为空
	//const FubenConf* conf = fuben_ ? fuben_->GetConfig() : NULL;

	//static GameEngine* ge = GetGameEngine();

	//if (fuben_ && (!fuben_->IsFb() || (conf && conf->isUnique_)))
	//{
	//	ge->BroadCast(ciChannelMap, GetId(), buf, size);
	//}
	//else
	//{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	ListIterator<EntityHandle> it(entity_list_[EntityType_Actor]);

	for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
	{
		Actor* actor = (Actor*)(em->GetEntity(node->data_));
		if (!actor) continue;
		if (except != NULL && except == actor) {
			//屏蔽自己的不发
			continue;
		}
		actor->SendData(buf, size);
	}
	//}
}
void Scene::SendData(DataPacket& pack, Actor* except)
{
	SendData(pack.getMemoryPtr(), pack.getPosition(), except);
}

void Scene::SendPacket(DataPacket* pack, Actor* except)
{
	SendData(pack->getMemoryPtr(), pack->getPosition(), except);
}


void Scene::BroadcastDisappear(Entity* et)
{
	if (!et) return;

	static Protocol::EntityDisappearProto msg;
	msg.handle = et->GetHandle();

	SendData(msg);
}

bool Scene::IsKillAllMonster(int mid)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	if (mid)
	{
		ListIterator<EntityHandle> it(entity_list_[EntityType_Monster]);
		for (auto node = it.first(); node; node = it.next())
		{
			Entity* et = em->GetEntity(node->data_);
			if (et && et->GetId() == mid)
				return false;
		}
	}
	else
	{
		return !(entity_list_[EntityType_Monster].count() > 0);
	}

	return true;
}

void Scene::KillFubenMonsters()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	{
		ListIterator<EntityHandle> it(entity_list_[EntityType_Monster]);
		for (auto node = it.first(); node; node = it.next())
		{
			Monster* mon = (Monster*)em->GetEntity(node->data_);
			if (mon && mon->GetCamp() == CampType_None)
			{
				mon->ChangeHp(0 - mon->GetHp(), NULL);
			}
		}
	}
}

bool Scene::GetEntityList(VisiHandleList& list)
{
	if (!fuben_) return false;
	if(!fuben_->IsEnd()) {
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_Monster]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_Role]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_CloneRole]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
	}
	{
		ListIterator<EntityHandle> it(entity_list_[EntityType_DropBag]);
		for (auto node = it.first(); node; node = it.next())
		{
			list.add(node->data_);
		}
	}
	return true;
}

bool Scene::GetEntityListReDrop(VisiHandleList& list, Creature *et)
{
	if (!fuben_) return false;

	{
		ListIterator<EntityHandle> it(entity_list_[EntityType_DropBag]);
		for (auto node = it.first(); node; node = it.next())
		{
			list.add(node->data_);
		}
		if (list.count() > 0) {
			if (et->GetType() == EntityType_Role && et->GetActor()->GetLiveByJob() == et) {
				return true;
			}
		}
	}

	if (!fuben_->IsEnd()) {
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_Monster]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_Role]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
		{
			ListIterator<EntityHandle> it(entity_list_[EntityType_CloneRole]);
			for (auto node = it.first(); node; node = it.next())
			{
				list.add(node->data_);
			}
		}
	}
	return true;
}

bool Scene::GetMonsterList(VisiHandleList& list)
{
	{
		ListIterator<EntityHandle> it(entity_list_[EntityType_Monster]);
		for (auto node = it.first(); node; node = it.next())
		{
			list.add(node->data_);
		}
	}
	return true;
}

int Scene::GetDropBagCount()
{
	return entity_list_[EntityType_DropBag].count();
}

bool Scene::GetGridEntityList(int x, int y, VisiHandleList& list)
{
/*
	if (x >= 0 && y >= 0 && x < map_->getWidth() && y < map_->getHeight())
	{
		EntityGrid* g = grid_.GetList(x, y);
		if (g)
		{
			EntityHandle* entitys = g->entitys_;
			list.addArray(entitys, g->entitys_.count());
			return true;
		}
	}
	*/
	return false;
}

int Scene::GetGridEntityCount(int x, int y)
{
	/*
	if (x >= 0 && y >= 0 && x < map_->getWidth() && y < map_->getHeight())
	{
		EntityGrid* g = grid_.GetList(x, y);
		if (g)
		{
			return g->entitys_.count();
		}
	}
	*/
	return 0;
}

bool Scene::CloneRoleEmpyt(void)
{
	ListIterator<EntityHandle> it(entity_list_[EntityType_CloneRole]);

	return it.first() == nullptr;
}

bool Scene::HasAreaAttr(const SceneAreaAttrDef attr, const Point &point) {
	return HasAreaAttr(attr, Grid(point));
}

bool Scene::HasAreaAttr(const SceneAreaAttrDef attr, const Grid &grid) {
	auto sa = GetArea(grid);
	if (sa) {
		return sa->attri.find(attr) != sa->attri.end();
	}
	return false;
}

const std::vector<int>* Scene::GetAreaAttriparm(const SceneAreaAttrDef attr, const Grid &grid) {
	auto sa = GetArea(grid);
	if (sa) {
		auto it = sa->attri.find(attr);
		if (it != sa->attri.end()) {
			return &(it->second.iparm);
		}
	}
	return NULL;
}

uint32_t Scene::GetAreaMask(const Grid &grid) {
	auto sa = GetArea(grid);
	if (sa) {
		return sa->mark;
	}
	return 0;
}

const SceneArea* Scene::GetArea(const Grid &grid) {
	if (scene_conf_) {
		int idx = grid.y * scene_conf_->size_x + grid.x;
		if ((int)scene_conf_->areas.size() > idx) {
			auto sa = scene_conf_->areas[idx];
			if (sa) {
				return sa;
			}
		}
	}
	return 0;
}

bool Scene::isLeapArea(const Grid &old_grid, const Grid &new_grid) {
	auto osa = GetArea(old_grid);
	auto nsa = GetArea(new_grid);
	if (osa != nsa) return true;
	if (osa && nsa) {
		return osa->mark != nsa->mark;
	}
	return false;
}
