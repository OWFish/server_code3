#include "StdAfx.h"
#include "fuben.h"
#include "scene.h"
#include "fuben_mgr.h"
#include "entity/entity.h"
#include "entity/actor/actor.h"
#include "role/role_system.h"


using namespace FDOP;

FuBen::FuBen()
:fb_id_(0)
, handle_(0)
, conf_(nullptr)
, is_end_(false)
, belong_(false)
, is_released_(false)
, has_mon_damage_event_(false)
, has_actor_damage_event_(false)
, run_ai_(false)
{
}

FuBen::~FuBen()
{
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* s = scene_list_[i];

		if (s)
		{
			static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
			fbMgr->FreeScene(s->GetHandle());//这里释放场景里面的npc等实体，角色应该在这之前传送出副本
		}
	}
}

bool FuBen::Init(int id)
{
	fb_id_ = id;
	conf_ = FubenConfigPool::Get(id);
	if (!conf_)
		return false;

	has_mon_damage_event_ = GetGameEngine()->GetFuBenMgr()->HasMonsterDamageEvent(id);
	has_actor_damage_event_ = GetGameEngine()->GetFuBenMgr()->HasActorDamageEvent(id);
	run_ai_ = (conf_->type != 0);
	return true;
}

int FuBen::RunOne()
{
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* s = scene_list_[i];

		if (!s->RunOne())
			OutputMsg(rmError, "Scene run error. fb: %d, scene:%d", fb_id_, i);
		//if (s->RunOne()) return 1;
		//FuBenMgr::refreshPara_.setScene(i + 1);
	}

	return 0;
}

bool FuBen::Enter(Entity* et, int sid, int x, int y, bool pix)
{
	if (et == NULL) return false;

	Scene* scene = GetScene(sid);

	if (scene == NULL) {
		OutputMsg(rmError, " Enter fb fail, fb scene is empty. fb=%d, sid=%d", fb_id_, sid);
		return false;
	}

	bool enter_call = false;
	bool is_login = false;
	if (et->GetType() == EntityType_Actor)
	{
		FuBen* old_fb = et->GetFuBen();
		if (old_fb != this)
			enter_call = true;
		if (old_fb == NULL)
			is_login = true;

		//要切换的为副本，才会判断
		if (old_fb && old_fb != this)
		{
			old_fb->OnExit((Actor*)et);
		}
	}
	if (((Actor*)et))
		((Actor*)et)->setPkMode(conf_->pkMode);

	bool ret = scene->EnterScene(et, x, y, pix);
	if (!ret)
		return false;

	if (enter_call)
		OnEnter((Actor*)et, is_login);
	else
		((Actor*)et)->GetRoleSystem()->InstantMove(x, y);
	if (et->GetType() == EntityType_Actor) {
		((Actor*)et)->ResetShowZhanLingT();
	}
	else if (et->GetType() == EntityType_CloneRole) {
		((RoleClone*)et)->ResetShowZhanLingT();
	}

	return ret;
}

//bool FuBen::AddStaticScene(SceneConfig* sc)
//{
//	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
//	SceneHandle handle;
//	Scene* newone = fbMgr->AllocSceneHandle(handle);
//	newone->SetHandle(handle);
//
//	if (newone->Init(this, sc->sid))
//		scene_list_.add(newone);
//	else
//		return false;
//
//	return true;
//}

void FuBen::ExitAllActor()
{
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			scene->ExitAllActor();
		}
	}
}

Scene* FuBen::GetScene(int sid)
{
	if (scene_list_.count() <= 0) return NULL;
	if (sid < 0) return scene_list_[0];

	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene != NULL && scene->GetId() == sid)
			return scene;
	}

	return scene_list_[0];
}

Scene* FuBen::GetSceneByIndex(int index)
{
	if (index < 0 || index >= scene_list_.count()) return NULL;
	return scene_list_[index];
}

bool FuBen::HasScene(int sid)
{
	if (fb_id_ == 0)
	{
		return !(sid < 0 || sid >= scene_list_.count());
	}
	else
	{
		for (int i = 0; i < scene_list_.count(); i++)
		{
			//找到所在的场景
			Scene* scene = scene_list_[i];

			if (scene && scene->GetId() == sid)
			{
				return true;
			}
		}
	}

	return false;
}

void FuBen::SendData(const char* buf, size_t size)
{
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			scene->SendData(buf, size);
		}
	}
}
void FuBen::SendDataNoActor(const char* buf, size_t size, Actor* except)
{
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			scene->SendDataNoActor(buf, size, except);
		}
	}
}
//只有进入新副本才会调用
void FuBen::OnEnter(Actor *actor, bool isLogin)
{
	ScriptValueList arg;
	arg << handle_;
	arg << actor;
	arg << isLogin;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceEnter", &arg, &arg, 0);


	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char fb_id_str[64];
	char count_str[64];
	char level_str[64];
	int level = actor->GetLevel();

	sprintf(fb_id_str, "%d", conf_->fbid);
	sprintf(count_str, "%d", 1);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor->GetActorId(),
		actor->GetAccount(),
		level_str,
		"enter fuben",
		fb_id_str,
		count_str,
		"", conf_->name.c_str(), conf_->desc.c_str(), "", ""
	);
	//FuBen::UpdateActorCountAndLevel(Entity* et, bool add)
}

void FuBen::OnExit(Actor *et)
{
	//et->GetBuffSystem().OnExitFuben();

	ScriptValueList arg;
	arg << handle_;
	arg << et;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceExit", &arg, &arg, 0);

	//FuBen::UpdateActorCountAndLevel(Entity* et, bool add)
	if (et->GetCurrGatherMonster())
	{
		et->GetCurrGatherMonster()->EndGather(false);
	}

}

void FuBen::OnOffline(Actor *et)
{
	ScriptValueList arg;
	arg << handle_;
	arg << et;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceOffline", &arg, &arg, 0);

	//FuBen::UpdateActorCountAndLevel(Entity* et, bool add)
}

void FuBen::OnActorLeapArea(Actor *actor) {
	ScriptValueList arg;
	arg << handle_;
	arg << actor;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceLeapArea", &arg, &arg, 0);
}

void FuBen::OnEntityDie(Entity *et, EntityHandle killer)
{
	double killerHdl;
	memcpy(&killerHdl, &killer.handle_, sizeof(double));
	ScriptValueList arg;
	arg << handle_;
	arg << et;
	arg << killerHdl;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceEntityDie", &arg, &arg, 0);
}

void FuBen::OnMonsterDamage(Monster *mon, int nValue, Entity* attacker, double &ret)
{
	//static FuBenMgr *fm = GetGameEngine()->GetFuBenMgr();
	if (has_mon_damage_event_ && mon->GetHp() > 0 && nValue > 0)
	{
		ScriptValueList arg;
		arg << handle_;
		arg << mon;
		arg << nValue;
		arg << attacker;
		arg << ret;
		ScriptValueList res;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("onInstanceMonsterDamage", &arg, &res, 1);
		ret = (double)res[0];
	}
	if (mon->IsBoss())
	{
		ScriptValueList arg;
		arg << handle_;
		arg << mon->GetId();
		arg << ret;
		arg << nValue;
		arg << attacker;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("onBossDamage", &arg, &arg, 0);
	}
}

void FuBen::OnRoleDamage(Role *role, int nValue, Entity* attacker, double &ret) {
	if (has_actor_damage_event_ && role->GetHp() > 0 && nValue > 0) {
		ScriptValueList arg;
		arg << handle_;
		arg << role->GetActor();
		arg << role;
		arg << nValue;
		arg << attacker;
		arg << ret;
		ScriptValueList res;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("onInstanceActorDamage", &arg, &res, 1);
		ret = (double)res[0];
	}
}

void FuBen::OnMonsterEnter(Monster *mon)
{
	// 在这处理动态属性还是放在lua做?
	ScriptValueList arg;
	arg << handle_;
	arg << mon;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onInstanceMonsterCreate", &arg, &arg, 0);
}

void FuBen::KillAllMonster()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < scene_list_.size(); ++i)
	{
		Scene* scene = scene_list_[i];
		auto& list = scene->GetMonsterList();

		ListIterator<EntityHandle> it(list);
		for (auto node = it.first(); node; node = it.next())
		{
			Entity* et = em->GetEntity(node->data_);
			if (et)
			{
				double hp = ((Monster*)et)->GetHp();
				((Creature*)et)->ChangeHp(-hp, NULL);
			}
		}
	}
}

std::vector<Actor*> FuBen::GetAllActor()
{
	std::vector<Actor*> ret;
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetActorList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
			{
				Actor* actor = (Actor*)(em->GetEntity(node->data_));
				if (actor)
				{
					ret.push_back(actor);
				}
			}
		}
	}
	return ret;
}
std::vector<Monster*> FuBen::GetAllMonster()
{
	std::vector<Monster*> ret;
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetMonsterList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
			{
				Monster* actor = (Monster*)(em->GetEntity(node->data_));
				if (actor)
				{
					ret.push_back(actor);
				}
			}
		}
	}
	return ret;
}

int FuBen::GetResCloneRoleCount()
{
	int ret = 0;
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetCloneRoleList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
			{
				RoleClone* actor = (RoleClone*)(em->GetEntity(node->data_));
				if (actor && actor->IsMirror() == 0 )
					ret++;
			}
		}
	}
	return ret;
}

std::vector<DropBag*> FuBen::GetAllDropBag()
{
	std::vector<DropBag*> ret;
	for (int i = 0; i < scene_list_.count(); i++)
	{
		Scene* scene = scene_list_[i];

		if (scene)
		{
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetDropBagList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
			{
				DropBag* actor = (DropBag*)(em->GetEntity(node->data_));
				if (actor)
				{
					ret.push_back(actor);
				}
			}
		}
	}
	return ret;
}

void FuBen::GetAllCloneRole(std::vector<RoleClone*> &ret) {
	ret.clear();
	for (int i = 0; i < scene_list_.count(); i++) {
		Scene* scene = scene_list_[i];

		if (scene) {
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetCloneRoleList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next()) {
				RoleClone* et = (RoleClone*)(em->GetEntity(node->data_));
				if (et) {
					ret.push_back(et);
				}
			}
		}
	}
}

RoleClone * FuBen::GetCloneRoleByID(int ID)
{
	for (int i = 0; i < scene_list_.count(); i++) {
		Scene* scene = scene_list_[i];

		if (scene) {
			static EntityMgr* em = GetGameEngine()->GetEntityMgr();

			ListIterator<EntityHandle> it(scene->GetCloneRoleList());

			for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next()) {
				RoleClone* et = (RoleClone*)(em->GetEntity(node->data_));
				if (et->GetActorId() == ID) {
					return et;
				}
			}
		}
	}
	
	return nullptr;
}

int FuBen::getActorCount() {
	int count = 0;
	for (int i = 0; i < scene_list_.count(); i++) {
		Scene* scene = scene_list_[i];
		if (scene) {
			EntityList& el = scene->GetActorList();
			count += el.count();
		}
	}
	return count;
}
