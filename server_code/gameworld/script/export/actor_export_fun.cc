
#include "StdAfx.h"

#include "../interface/actor_export_fun.h"
#include "systems/move/move_system.h"
#include "db/actor_db_data.h"
#include "db/role_data.h"
#include "db/store_data.h"
#include "game_engine.h"
#include "entity/role/role.h"
#include "entity/role/role_system.h"
#include "skirmish/skirmish.h"
#include "actor/actor_data_mgr.h"
#include "actor/actor_asyn_mgr.h"
#include "actor/actor_asyn_event.h"
#include "actor/tianti_mgr.h"
#include "item/container/equip_bag.h"
#include "item/container/depot_system.h"
#include "wing/wing_system.h"
#include "item/item_config.h"
#include "enhance/enhance_system.h"
#include "skill/skill_system.h"
#include "mail/mail.h"
#include "mail/mail_system.h"
#include "mail/mail_pool.h"
#include "stone/stone_system.h"
#include "jingmai/jingmai_system.h"
#include "zhuling/zhuling_system.h"
#include "zhuansheng/zhuansheng_system.h"
#include "item/equip/equip_system.h"
#include "store/store_system.h"
#include "ex-ring/ex_ring_system.h"
#include "ai/ai.h"
#include "soulshield/soulshield_system.h"
#include "soulsystem/soul_system.h"
#include "bless/bless_system.h"
#include "item/container/item_bag.h"
#include "item/container/equip_bag.h"
#include "item/container/depot_system.h"
#include "miji/mijisystem.h"
#include "title/title_system.h"

#include "rank/ranking_system.h"
#include "systems/guild/guild_system.h"
#include "systems/guild/guild.h"
#include "zhuangban/zhuangban.h"
#include "systems/offlinemsg/msg_system.h"
#include "systems/skill/skill_break.h"
#include "systems/fuling/fuling_system.h"
#include "systems/actorexring/actor_ex_ring_system.h"
#include "systems/togetherhit/together_hit_system.h"
#include "systems/fuwen/fuwensystem.h"
#include "systems/neigongsystem/neigong_system.h"
#include "systems/imba/imbasystem.h"
#include "systems/godweapon/godweaponsystem.h"
#include "systems/kuangsystem/kuangsystem.h"
#include "systems/attr/attrs_system.h"

namespace LActor
{
int getServerId(void* actor)
{
	if (!actor) return ServerInstance()->GetServerIndex();

	if (((Entity*)actor)->GetType() != EntityType_Actor) return ServerInstance()->GetServerIndex();

	return ((Actor*)actor)->GetServerId();
}

int getServerIdById(const int actorid)
{
	if (!actorid) return 0;

	return GetGameEngine()->GetActorInServerId(actorid);
}

void* getEntity(double handle)
{
	unsigned long long d;
	memcpy(&d, &handle, sizeof(handle));

	EntityHandle hHandle(d);
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	return em->GetEntity(hHandle);
}

int getId(void* et)
{
	if (et == NULL) return 0;
	Entity* entity = (Entity*)et;
	return entity->GetId();
}

void* getActor(void* et)
{
	if (et == NULL) return NULL;
	Entity* entity = (Entity*)et;
	return entity->GetActor();
}

void* getActorById(const int actorId, bool ignoreInit, bool includeImage)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	auto actor = em->GetActorPtrById(actorId);

	if (actor && (ignoreInit || actor->IsInited()) && (includeImage || !actor->IsImage()))
		return actor;
	return NULL;
}

void* getActorByName(const char* name)
{
	if (nullptr == name) return NULL;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrByName(name);
	if (actor && actor->IsInited() && !actor->IsImage())
		return actor;
	return NULL;
}

void* getActorByAccountName(const char* accountName)
{
	if (nullptr == accountName) return NULL;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrByAccount(accountName);
	if (actor && actor->IsInited() && !actor->IsImage())
		return actor;
	return NULL;
}

int getActorIdByAccountName(const char* accountName)
{
	if (nullptr == accountName) return 0;
	static ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	return data_mgr->GetIdByAccountName(accountName);
}

int getActorIdByName(const char* actorName)
{
	if (nullptr == actorName) return 0;
	static ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	return data_mgr->getActorIdByName(actorName);
}

const ActorBasicData* getActorData(void* actor)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	
	return ((Actor*)actor)->GetBasicData();
}

const char* getName(void* et)
{
	if (et == NULL) return NULL;

	return ((Entity*)et)->GetEntityName();
}

const char* getShowName(void* et)
{
	if (et == NULL) return NULL;

	//return ((Entity*)et)->GetShowName();
	return NULL;
}
double getHandle(void* et)
{
	if (et == NULL) return 0;

	double d;
	memcpy(&d, &(((Entity*)et)->GetHandle()), sizeof(d));
	return d;
}

unsigned int getLevel(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)et)->GetLevel();
}

int getJob(void* et)
{
	if (et == NULL) return 0;
	int type = ((Entity*)et)->GetType();
	if (type == EntityType_Actor) return ((Actor*)et)->GetJob();
	if (type == EntityType_Role) return ((Role*)et)->GetJob();
	return 0;
}

int getSex(void* et)
{
	if (et == NULL) return 0;
	int type = ((Entity*)et)->GetType();
	if (type == EntityType_Actor) return ((Actor*)et)->GetSex();
	if (type == EntityType_Role) return ((Role*)et)->GetSex();
	return 0;
}
const char* getLastLoginIp(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return "";
	return ((Actor*)et)->GetLastLoginIp();
}

const ActorBasicData* getActorDataById(int actorId)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	return data_mgr->GetData(actorId);
}

unsigned int getActorLevel(int actor_id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(actor_id);
	if (data)
		return data->level;
	return 0;
}

unsigned int getActorZhuanShengLevel(int id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(id);
	if (data)
		return data->zhuansheng_lv;
	return 0;
}

const char* getActorName(int id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(id);
	if (data)
		return data->actor_name;
	return NULL;
}

double getActorPower(int id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(id);
	if (data)
		return (double)data->total_power;
	return 0;
}

int getActorJob(int id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(id);
	if (data)
		return data->job;
	return 0;
}

int getActorSex(int id)
{
	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* data = data_mgr->GetData(id);
	if (data)
		return data->sex;
	return 0;
}

void loginOtherSrv(void* et, int sid, unsigned int fbhdl, int sceneid, int x, int y, const char* reason) {
	if (!et || ((Entity*)et)->GetType() != enActor) return;

	Actor* actor = (Actor*)et;
	actor->LoginOtherSrv(sid, true, fbhdl, sceneid, x, y, reason);
}

void setLevel(void* et, int level)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;
	if (level < 0) return;
	return ((Actor*)et)->SetLevel(level);
}

void onLevelUp(void* actor)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->OnLevelUp();
}

unsigned int getExp(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)et)->GetExp();
}

void setExp(void* et, int exp)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;
	if (exp < 0) return;
	return ((Actor*)et)->SetExp(exp);
}

void* getRole(void* actor, int roleId)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleId);
}

void * GetRoleByJob(void * actor, int job)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetRoleSystem()->GetRoleByJob(job);
}

RoleData* getRoleData(void* actor, int roleId)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return ((Actor*)actor)->GetRoleSystem()->GetRoleData(roleId);
}

int getRoleCount(void* actor)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetRoleSystem()->GetRoleCount();
}

void createRole(void* actor, int job, int sex)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	
	((Actor*)actor)->GetRoleSystem()->CreateRole(job, sex);
}

void changeGold(void *actor, int value, const char* log)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->ChangeGold(value, log);
}

void changeYuanBao(void *actor, int value, const char* log, bool ignore)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->ChangeYuanBao(value, log, ignore);
}

void giveItem(void *actor, int id, int count, const char* log)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GiveItem(id, count, log);
}

void costItem(void* actor, int id, int count, char *log)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->CostItem(id, count, log);
}


int getEquipBagSpace(void *actor)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetEquipBag()->Spaces();
}

void gmClearBag(void* actor, int type)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	if (type == BagType_Item)
		((Actor*)actor)->GetItemBag()->GMClear();
	else if (type == BagType_Equip)
		((Actor*)actor)->GetEquipBag()->GMClear();
	else if (type == BagType_Depot)
		((Actor*)actor)->GetDepot()->GMClear();
}

int getActorOfflineTime(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return false;
	return ((Actor*)et)->GetOfflineTime();
}

unsigned int getFubenHandle(void* et)
{
	if (!et) return 0;

	FuBen* fb = ((Entity*)et)->GetFuBen();
	return fb ? (unsigned int)fb->GetHandle() : 0;
}

unsigned int getSceneHandle(void* et)
{
	if (!et) return 0;

	Scene* scene = ((Entity*)et)->GetScene();
	return scene ? (unsigned int)scene->GetHandle() : 0;
}

void* getFubenPrt(void* et)
{
	if (!et) return NULL;

	return ((Entity*)et)->GetFuBen();
}
void* getFubenPtr(void* et)
{
	if (!et) return NULL;

	return ((Entity*)et)->GetFuBen();
}

int getFubenId(void* et)
{
	if (!et) return 0;

	FuBen* fb = ((Entity*)et)->GetFuBen();
	if (fb == NULL) return 0;
	return fb->GetFbId();
}


void* getScenePtr(void* et)
{
	if (!et) return NULL;

	return ((Entity*)et)->GetScene();
}

bool isInFuben(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return false;

	FuBen* fb = ((Actor*)et)->GetFuBen();
	if (fb == NULL) return false;

	return fb->GetFbId() > 0 && fb->GetConfig()->type != FuBenType_City;
}

bool isBoss(void* creature)
{
	if (creature == NULL) return false;
	return ((Creature*)creature)->IsBoss();
}

void enterScene(void *et, unsigned int hScene, int x, int y)
{
	if (et == NULL) return;
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	if (!mgr) return;
	Scene* s = mgr->GetScenePtr(hScene);
	if (!s) return;
	s->EnterScene((Entity*)et, x, y);
}

void instantMove(void* actor, int x, int y)
{
	if (actor == nullptr || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetRoleSystem()->InstantMove(x, y);
}

int GetFuBenType(void * actor)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return false;

	FuBen* fb = ((Actor*)actor)->GetFuBen();
	if (fb == NULL) return 0;

	return fb->GetFbType();
}

void changeHp(void* et, double nValue, void* killer)
{
	if (et == NULL) return;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return;
	Creature *ct = (Creature*)et;
	ct->ChangeHp(nValue, (Creature*)killer);
}

void setHp(void* et, double hp)
{
	if (et == NULL) return;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return;

	((Creature*)et)->SetHp(hp);
}

void setMp(void* et, double mp)
{
	if (et == NULL) return;
	if (!((Entity*)et)->IsCreature()) return;

	((Creature*)et)->SetMp(mp);
}

void setNp(void* et, double np)
{
	if (et == NULL) return;
	if (!((Entity*)et)->IsCreature()) return;

	((Creature*)et)->SetNp(np);
}

double getHp(void* et)
{
	if (et == NULL) return 0;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return 0;

	return ((Creature*)et)->GetHp();
}

double getNp(void* et)
{
	if (et == NULL) return 0;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return 0;

	return ((Creature*)et)->GetNp();
}

double getHpMax(void* et)
{
	if (et == NULL) return 0;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return 0;

	return ((Creature*)et)->GetMaxHp();
}

double getMpMax(void* et)
{
	if (et == NULL) return 0;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return 0;

	return ((Creature*)et)->GetMaxMp();
}

double getAttr(void* et, int atype)
{
	if (et == NULL) return 0;
	Entity *tmp = (Entity*)et;

	if (!tmp->IsCreature()) return 0;;

	return ((Creature*)et)->GetAttr(atype);
}

double getAtkSum(void * et) {
	if(!et) return 0.0;
	if (((Entity*)et)->GetType() == EntityType_Actor) {
		return ((Actor*)et)->GetAtkSum();
	}else if (((Entity*)et)->IsCreature()) {
		return ((Creature*)et)->GetAtkSum();
	}
	return 0.0;
}

void gmSetAttr(void* actor, int type, double value)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;

	Role* roles[3];
	((Actor*)actor)->GetRoleSystem()->GetRoles(roles);
	roles[0]->GMSetAttr(type, value);
	if (roles[1]) roles[1]->GMSetAttr(type, value);
	if (roles[2]) roles[2]->GMSetAttr(type, value);
}

void recover(void* actor)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetRoleSystem()->Recover();
}

int getChapterLevel(void* actor)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetChapterLevel();
}

void setChapterLevel(void* actor, int level)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	return ((Actor*)actor)->SetChapterLevel(level);
}

int getVipLevel(void* actor)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetVipLevel();
}

int getMonthCard(void* actor)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetBasicData()->monthcard;
}

int getRecharge(void* actor)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetRecharge();
}

void addRecharge(void* actor, int yb, int itemid)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	return ((Actor*)actor)->AddRecharge(yb, itemid);
}


void addRechargeOffline(int actor_id, int yb, int itemid, int yb_back, std::string orderNum)
{
	ActorAsynFunc func = std::bind(AddRechargeEvent, std::placeholders::_1, yb, itemid, yb_back, orderNum);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actor_id, func);
}

void setVipLevel(void* actor, int vip)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetVipLevel(vip);
}

int getEssence(void* actor)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetEssence();
}

void setEssence(void* actor, int value)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetEssence(value);
}

int getExRingLevel(void* role, int id)
{
	if (role == NULL) return 0;
	if (((Entity*)role)->GetType() != EntityType_Role) return 0;

	return ((Role*)role)->GetExRingSystem()->GetLevel(id);
}

void setExRingLevel(void* role, int id, int level)
{
	if (role == NULL) return;
	if (((Entity*)role)->GetType() != EntityType_Role) return;

	return ((Role*)role)->GetExRingSystem()->SetLevel(id, level);
}

int getActorExRingLevel(void * actor, int id)
{
	if (actor == NULL) return 0;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetActorExRingLevel(id);
}

void setActorExRingLevel(void * actor, int id, int level)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetActorExRingLevel(id, level);
}

bool GetActorExRingIsEff(void* actor, int id)
{
	if (actor == NULL) return false;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return false;
	return ((Actor*)actor)->GetActorExRingIsEff(id);
}

void SetActorExRingIsEff(void* actor, int id, int eff)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetActorExRingIsEff(id, eff?true:false);
}

void SetAexringMon(void* clone, int id, void* mon)
{
	if (!clone || !mon) return;
	if (((Entity*)clone)->GetType() != EntityType_CloneRole) return;
	if (((Entity*)mon)->GetType() != EntityType_Monster) return;
	((RoleClone*)clone)->SetAexringMon(id, (Monster*)mon);
}

void ClearExRingMonster(void* actor, int id)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetActorExRingSystem()->ClearExRingMonster(id);
}

void AddAerMonAttr(void* clone, int id, int type, double value)
{
	if (!clone) return;
	if (((Entity*)clone)->GetType() != EntityType_CloneRole) return;
	((RoleClone*)clone)->AddAerMonAttr(id, (Attribute::AttributeType)type, value);
}

void AddAerMonExAttr(void* clone, int id, int type, int value)
{
	if (!clone) return;
	if (((Entity*)clone)->GetType() != EntityType_CloneRole) return;
	((RoleClone*)clone)->AddAerMonExAttr(id, (ExAttribute::ExAttributeType)type, value);
}

void createSkirmishData(void* actor, int index, int id, int level, const char* name, int attrper)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	SkirmishHelper::CreateSkirmishData((Actor*)actor, index, id, level, name, attrper);
}

void createKuangActorData(void* actor, int tactorId)
{
	if (actor == NULL) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	KuangHelper::CreateKuangActorData((Actor*)actor, tactorId);
}

void createFieldPlayerData(void* actor, int index, int actor_id, int pos_x, int pos_y, int actionType, int isForay, int killNum, int ox, int oy)
{
	if (actor == NULL) return;
	SkirmishHelper::createFieldPlayerData((Actor*)actor, index, actor_id, pos_x, pos_y, actionType, isForay, killNum, ox, oy);
}

bool isDeath(void* et)
{
	if (!et) return false;

	return ((Entity*)et)->IsDeath();
}

void relive(void* et, int x, int y)
{
	if (!et) return;

	unsigned int type = ((Entity*)et)->GetType();
	if (type == EntityType_Actor)
	{
		((Actor*)et)->Relive(x, y);
		Role *roles[MAX_ROLE] = { NULL };
		((Actor*)et)->GetRoleSystem()->GetRoles(roles);
		for (int i =0;i < MAX_ROLE;++i)
		{
			if(roles[i]) //添加一个复活buff 
				roles[i]->GetSkillEffectSystem()->AddEffect(roles[i], 101);
		}
	}
	else if (type == EntityType_Role)
	{
		Role* role = (Role*)et;
		Actor* actor = role->GetActor();
		bool isDeath = false;
		if (actor)
			isDeath = actor->IsDeath();

		bool last_death = role->IsDeath();
		role->ChangeHp(role->GetMaxHp());
		role->ChangeMp(role->GetMaxMp());
		role->OnRelive();
		//玩家复活无敌buff  不用配置
		role->GetSkillEffectSystem()->AddEffect(role, 101);
		if (isDeath)
		{
			actor->GetActorExRingSystem()->OnRelive();
		}
		if (last_death && !role->GetSendEntity())
		{
			Point point(x,y);
			role->GetMoveSystem()->InstantMove(point);
			Scene* scene = role->GetScene();
			if (scene) scene->BroadcastAppear(role);
		}
	}
}

int getMoneyCount(void* et, int type)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	//Actor* actor = (Actor*)et;
	return 0; // todo
}

bool enterFuBen(void* et, unsigned int hFb, int sceneId, int x, int y, bool pix)
{
	if (et == NULL) return false;
	if (((Entity*)et)->GetType() != EntityType_Actor) return false;

	static FuBenMgr* fbMgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = GetGameEngine()->GetFuBenMgr()->GetFubenPtr(hFb);
	bool result = fbMgr->EnterFuBen((Entity*)et, fb, sceneId, x, y, pix);

	return result;
}

void sendTipmsg(void* et , const char* sTipmsg, int nType)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;

	((Actor*)et)->SendTipmsg(sTipmsg, nType);
}

void sendTipWithId(void* actor, int tipId)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	((Actor*)actor)->SendTipWithId(tipId);
}

int getActorId(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)et)->GetActorId();
}



int getCloneRoleActorId(void *clone_role) 	{
	if (clone_role == NULL || ((Entity*)clone_role)->GetType() != EntityType_CloneRole) return 0;
	return ((RoleClone*)clone_role)->GetActorId();
}

const char* getAccountName(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return "";

	return ((Actor*)et)->GetAccount();
}

int getAccountId(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)et)->GetAccountId();
}

void* getActorPtrByName(char* name)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	if (name == NULL || name[0] == 0) return NULL;

	return em->GetActorPtrByName(name);
}

unsigned int getLoginTime(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)et)->GetLoginTime();
}

unsigned int getLastLogoutTime(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)et)->GetLastLogoutTime();
}

unsigned int getLastLogoutDate(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return SecondTime(((Actor*)et)->GetLastLogoutTime()).rel_today();
}

unsigned int getLoginDate(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return SecondTime(((Actor*)et)->GetLoginTime()).rel_today();
}

int getStaticVar(lua_State* L)
{
	Actor* actor = (Actor*)lua_touserdata(L, 1);

	if (!actor || actor->GetType() != EntityType_Actor)
		return 0;

	return LuaCLVariant::returnValue(L, actor->GetActorVar());
}

int getCrossVar(lua_State* L) {
	Actor* pActor = (Actor*)lua_touserdata(L, 1);

	if (!pActor || pActor->GetType() != EntityType_Actor)
		return 0;

	return LuaCLVariant::returnValue(L, pActor->GetWarSystem()->GetVar());
}

int postScriptEvent(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et)
	{
		static GameEngine* ge = GetGameEngine();
		et = ge->GetGlobalNpc();
	}

	int64_t delay = (int64_t)lua_tonumber(L, 2);
	const char* fn = lua_tostring(L, 3);
	int64_t interval = (int64_t)lua_tonumber(L, 4);
	int count = (int)lua_tointeger(L, 5);
	ScriptValueList args;
	args.getArguments(L, 6);
	int64_t evt_hdl = et->PostScriptEvent(delay, interval, count, fn, args);
	double d;
	memcpy(&d, &evt_hdl, sizeof(d));
	lua_pushnumber(L, d);
	return 1;
}

int nextScriptEvent(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et) return 0;

	const char* fn = lua_tostring(L, 2);
	ScriptValueList args;
	args.getArguments(L, 3);
	et->PostScriptEvent(0, 0, 0, fn, args);
	return 0;
}

void cancelScriptTimer(void* et, double handle)
{
	if (!et) return;

	int64_t d = 0;
	memcpy(&d, &handle, sizeof(d));
	return ((Entity*)et)->CancelScriptTimer(d);
}

bool isActor(void* et)
{
	if (et)
	{
		return ((Entity*)et)->GetType() == EntityType_Actor;
	}

	return false;
}

bool isPet(void* et)
{
	//if (et)
	//{
	//	return (((Entity*)et)->GetType() == enMonster && ((Monster*)et)->is_pet_);
	//}

	return false;
}

bool isMonster(void* et)
{
	return et ? ((Entity*)et)->IsMonster(): false;
}

int getEntityType(void* et)
{
	if (!et) return -1;

	return ((Entity*)et)->GetType();
}

const char* getPf(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return "";

	return ((Actor*)et)->GetPf();
}

const char* getAppid(void* et) {
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return "";
	return ((Actor*)et)->GetAppid();
}

const char* getPfId(void* et) {
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return "";
	return ((Actor*)et)->GetPfid();
}

//克隆实体是否为机器人
int getCloneRoleIsMirror(void * clone_role)
{
	if (clone_role == NULL || ((Entity*)clone_role)->GetType() != EntityType_CloneRole) return 0;
	return ((RoleClone*)clone_role)->IsMirror();
}

Attribute* GetCloneRoleAttr(void *clone_role)
{
	if (clone_role == NULL || ((Entity*)clone_role)->GetType() != EntityType_CloneRole) return 0;
	return ((RoleClone*)clone_role)->GetBasicAttrs();
}

void exitFuben(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;

	Actor* actor = (Actor*)et;
	actor->ReturnToStaticScene();
}

void reEnterScene(void* actor, int x, int y)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	((Actor*)actor)->ReEnterScene(x, y);
}

long long getCurrency(void* et, int type)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)et)->GetCurrency(type);
}

void changeCurrency(void* et, int type, int value, const char* log)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return;

	((Actor*)et)->ChangeCurrency(type, value, log);
}

int getItemCount(void* et, int itemId)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return 0;

	const ItemConfig *pconf = ItemConfigPool::GetItemConfig(itemId);
	if (!pconf)
		return 0;

	ItemBag *pBag;
	if (pconf->isEquip())
		pBag = ((Actor*)et)->GetEquipBag();
	else
		pBag = ((Actor*)et)->GetItemBag();

	if (pBag)
		return pBag->GetCountById(itemId);

	return 0;
}



void reCalcRoleAttr(void* et, int roleId)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor) {
		RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
		if (!roleSystem) return;

		Role *pRole = roleSystem->GetRoleById(roleId);
		if (!pRole) return;

		pRole->CalcAttributes();
	}
	else if (((Entity*)et)->GetType() == EntityType_Role) {
		((Role*)et)->CalcAttributes();
	}
}

void reCalcAttr(void* et)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
		((Actor*)et)->ReCalcAttr();
	else if (((Entity*)et)->GetType() == EntityType_Role)
		((Role*)et)->CalcAttributes();
	else if (((Entity*)et)->GetType() == EntityType_Monster)
		((Monster*)et)->CalcAttributes();
	else if (((Entity*)et)->GetType() == EntityType_CloneRole)
		((RoleClone*)et)->CalcAttributes();
}

void reCalcExAttr(void* et)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
		((Actor*)et)->ReCalcExAttr();
	else if (((Entity*)et)->GetType() == EntityType_Role)
		((Role*)et)->CalcExAttributes();
	else if (((Entity*)et)->GetType() == EntityType_Monster)
		((Monster*)et)->CalcExAttributes();
}

void reCalcBattleAttr(void * et) {
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
		((Actor*)et)->ReCalcBattleAttr();
	else if (((Entity*)et)->GetType() == EntityType_Role)
		((Role*)et)->CalcBattleAttributes();
	else if (((Entity*)et)->GetType() == EntityType_Monster)
		((Monster*)et)->CalcBattleAttributes();
}

static WingSystem *getWingSystem(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetWingSystem();
}

int getWingInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);
	int roleId = (int)lua_tonumber(L, 2);

	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return 0;

	const WingsData *pWingData = pWingSystem->GetWingData();
	lua_pushinteger(L, pWingData->level);
	lua_pushinteger(L, pWingData->exp);
	lua_pushinteger(L, pWingData->openStatus);
	lua_pushnumber(L, pWingData->ctime);
	lua_pushinteger(L, pWingData->pill[0]);
	lua_pushinteger(L, pWingData->pill[1]);

	return 6;
}
void battleComparison(void* actor, int actorId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	//RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	//if (!roleSystem) return ;

	((Actor *)actor)->battleComparison(actorId);

	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	//auto actor = em->GetActorPtrById(actorId);

	//if (actor ==NULL)
	//	return ;
}
void setWingLevel(void* et, int roleId, int level)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->SetLevel(level);
}

void setWingStar(void* et, int roleId, int star)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->SetStar(star);
}

void setWingExp(void* et, int roleId, int exp)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->SetExp(exp);
}

void setWingStatus(void* et, int roleId, int status)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->SetOpenStatus(status);
}

void setWingCTime(void* actor, int roleId, unsigned int ctime)
{
	WingSystem *pWingSystem = getWingSystem(actor, roleId);
	if (!pWingSystem) return;
	pWingSystem->setWingCTime(ctime);
}

void setWingPill(void* actor, int roleId, int idx, int count)
{
	WingSystem *pWingSystem = getWingSystem(actor, roleId);
	if (!pWingSystem) return;
	pWingSystem->setWingPill(idx, count);
}

void clearWingAttr(void* et, int roleId)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->ClearAttr();
}

void addWingAttr(void* et, int roleId, int type, int value)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->AddAttr(type, value);
}

void addWingTempAttr(void* et, int roleId, int type, int value)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->AddTempAttr(type, value);
}

void wingInfoSync(void* et, int roleId)
{
	WingSystem *pWingSystem = getWingSystem(et, roleId);
	if (!pWingSystem) return;
	pWingSystem->WingInfoSync();
}

int getEnhanceInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	EnhanceSystem *pEnhanceSystem = pRole->GetEnhanceSystem();
	if (!pEnhanceSystem) return 0;

	const EquipsData* pData = pEnhanceSystem->GetEquipsData();
	if (!pData) return 0;

	lua_newtable(L);

	for (int pos = 0; pos < EquipSlotType_Max; ++pos)
	{
		lua_pushinteger(L, pos);
		lua_pushinteger(L, pData->slot_data[pos].strength_lv);
		lua_settable(L, -3);
	}
	return 1;
}

void setEnhanceLevel(void *et, int roleId, int posId, int level)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	EnhanceSystem *pEnhanceSystem = pRole->GetEnhanceSystem();
	if (!pEnhanceSystem) return;

	pEnhanceSystem->SetLevel(posId, level);
}

void clearEnhanceAttr(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	EnhanceSystem *pEnhanceSystem = pRole->GetEnhanceSystem();
	if (!pEnhanceSystem) return;

	pEnhanceSystem->ClearAttr();
}

void addEnhanceAttr(void* et, int roleId, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	EnhanceSystem *pEnhanceSystem = pRole->GetEnhanceSystem();
	if (!pEnhanceSystem) return;

	pEnhanceSystem->AddAttr(type, value);
}

int getFulingInfo(lua_State * L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	FulingSystem *pFuling = pRole->GetFulingSystem();
	if (!pFuling) return 0;

	int posId = (int)lua_tonumber(L, 3);
	const EquipSlotData* data = pFuling->GetEquipData(posId);
	if (!data) return 0;

	lua_pushinteger(L, data->fuling_lv);
	lua_pushinteger(L, data->fuling_exp);

	return 2;
}

void setFulingInfo(void * actor, int roleId, int posId, int level, int exp)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	FulingSystem *pFuling = pRole->GetFulingSystem();
	if (!pFuling) return;

	pFuling->SetLevelInfo(posId, level, exp);
}

Attribute* getFulingAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	FulingSystem *pFuling = pRole->GetFulingSystem();
	if (!pFuling) return nullptr;

	return pFuling->GetAttr();
}

ExAttribute * getFulingExAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	FulingSystem *pFuling = pRole->GetFulingSystem();
	if (!pFuling) return nullptr;

	return pFuling->GetExAttr();
}

int getSoulLevel(void* actor, int roleId, int pos)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return 0;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	SoulSystem *pSoul = pRole->GetSoulSystem();
	if (!pSoul) return 0;

	const EquipSlotData* data = pSoul->GetEquipData(pos);
	if (!data) return 0;

	return data->soul_lv;
}

void setSoulLevel(void *actor, int roleId, int posId, int level)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulSystem *pSoul = pRole->GetSoulSystem();
	if (!pSoul) return;

	pSoul->SetLevel(posId, level);
}

Attribute* getSoulAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	SoulSystem *pSoul = pRole->GetSoulSystem();
	if (!pSoul) return nullptr;

	return pSoul->GetAttr();
}

ExAttribute* getSoulExAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	SoulSystem *pSoul = pRole->GetSoulSystem();
	if (!pSoul) return nullptr;

	return pSoul->GetExAttr();
}

Attribute* getJadePlateAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetJadePlateAttrs();
}

ExAttribute* getJadePlateExAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetJadePlateExAttrs();
}

Attribute* getZhiZunAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetZhiZunAttrs();
}

ExAttribute* getZhiZunExAttr(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetZhiZunExAttrs();
}

Attribute* getLeiTingEquipAttrs(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetLeiTingEquipAttrs();
}

ExAttribute* getLeiTingEquipExAttrs(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetLeiTingEquipExAttrs();
}

int useSkill(void* et, int skillId)
{
	if (!et || !((Entity*)et)->IsCreature()) return false;
	return ((Creature*)et)->GetSkillSystem()->UseSkill(skillId);
}

long long int GetSkillLaveCD(void* et, int skillId)
{
	if (!et || !((Entity*)et)->IsCreature()) return false;
	return ((Creature*)et)->GetSkillSystem()->GetSkillLaveCD(skillId);
}

void SetAllRoleSkillCdById(void *actor, int skillId, int cd_time, int mod)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	static auto ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	for (int id = 0; id < MAX_ROLE; ++id) {
		Role *role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(id);
		if (role)
		{
			double cd_sub = (double)role->GetExAttr(ExAttribute::eatTogetherHitCdSub) / 10000.0;
			int64_t cd_mtime_ = static_cast<int64_t>(now_t + ((cd_time - cd_time*cd_sub)/mod));
			role->GetSkillSystem()->SetSkillCdById(skillId, cd_mtime_);
		}
	}
}

void addSkillEffect(void* et, int effid)
{
	if (!et || !((Entity*)et)->IsCreature()) return;
	((Creature*)et)->GetSkillEffectSystem()->AddEffect((Creature*)et, effid);
}

int getTogetherPunchInfo(lua_State* L) {
	Entity* et = (Entity*)lua_touserdata(L, 1);
	if (!et || et->GetType() != EntityType_Actor) return 0;
	Actor *actor = (Actor*)et;
	TogetherHitEquip &pData = actor->GetTogetherHitSystem()->getTogetherHitEquip();

	lua_newtable(L);

	for (int pos = 0; pos < TogetherHitSlotType_Max; ++pos) {
		lua_pushinteger(L, pos);
		lua_pushinteger(L, pData.together_hit_slot[pos].strength_lv);
		lua_settable(L, -3);
	}
	return 1;
}

void setTogetHerEquipLevel(void* actor, int pos, int lv) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetTogetherHitSystem()->setTogetHerEquipLevel(pos, lv);
}

Attribute* getTogetherPunchAttr(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return &((Actor*)actor)->GetTogetherHitSystem()->GetPunchAttr();
}

ExAttribute* getTogetherPunchExAttr(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return &((Actor*)actor)->GetTogetherHitSystem()->GetPunchExAttr();
}

int getMailInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	MailSystem *mailSystem = ((Actor *)et)->GetMailSystem();
	if (!mailSystem) return 0;

	int id = (int)lua_tointeger(L, 2);
	Mail *mail = mailSystem->GetMail(id);
	if (!mail) return 0;

	//把邮件信息导到lua
	//没用userdata的方式是因为到lua里面要对奖励进行遍历
	//用了userdata的话就遍历不了了，所以~~
	const MailData& mailData = mail->GetMailData();
	lua_pushinteger(L, mailData.awardStatus);
	lua_pushinteger(L, mailData.readStatus);
	lua_pushinteger(L, mailData.sendtime);
	lua_pushstring(L, mailData.head);
	lua_pushstring(L, mailData.context);

	lua_newtable(L);
	for (int i = 0; i < mailData.award_data.awardCount; ++i)
	{
		lua_pushinteger(L, i+1);

		lua_newtable(L);
		lua_pushinteger(L, 1);
		lua_pushinteger(L, mailData.award_data.awardList[i].id);
		lua_settable(L, -3);
		lua_pushinteger(L, 2);
		lua_pushinteger(L, mailData.award_data.awardList[i].type);
		lua_settable(L, -3);
		lua_pushinteger(L, 3);
		lua_pushinteger(L, mailData.award_data.awardList[i].count);
		lua_settable(L, -3);
		
		lua_settable(L, -3);
	}

	return 6;
}

int getMailList(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	MailSystem *mailSystem = ((Actor *)et)->GetMailSystem();
	if (!mailSystem) return 0;

	MailSystem::MailList &mailList = mailSystem->GetMailList();

	int count = static_cast<int>(mailList.size());
	lua_newtable(L);
	for (int i = 0; i < count; ++i)
	{
		lua_pushinteger(L, i + 1);

		lua_newtable(L);
		lua_pushinteger(L, 1);
		lua_pushinteger(L, mailList[i]->GetUId());
		lua_settable(L, -3);
		lua_pushinteger(L, 2);
		lua_pushstring(L, mailList[i]->GetMailData().head);
		lua_settable(L, -3);
		lua_pushinteger(L, 3);
		lua_pushinteger(L, mailList[i]->GetMailData().sendtime);
		lua_settable(L, -3);
		lua_pushinteger(L, 4);
		lua_pushinteger(L, mailList[i]->GetMailData().readStatus);
		lua_settable(L, -3);
		lua_pushinteger(L, 5);
		lua_pushinteger(L, mailList[i]->GetMailData().awardStatus);
		lua_settable(L, -3);

		lua_settable(L, -3);
	}

	return 1;
}

int deleteMail(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	MailSystem *mailSystem = ((Actor *)et)->GetMailSystem();
	if (!mailSystem) return 0;

	//因为id是64位的，要做个特殊处理，不然会被截断
	int id = (int)lua_tointeger(L, 2);
	mailSystem->DeleteMail(id);
	return 0;
}

int changeMailReadStatus(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	MailSystem *mailSystem = ((Actor *)et)->GetMailSystem();
	if (!mailSystem) return 0;

	//因为id是64位的，要做个特殊处理，不然会被截断
	int id = (int)lua_tointeger(L, 2);
	mailSystem->ChangeMailReadStatus(id);
	return 0;
}

int changeMailAwardStatus(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	MailSystem *mailSystem = ((Actor *)et)->GetMailSystem();
	if (!mailSystem) return 0;

	//因为id是64位的，要做个特殊处理，不然会被截断
	int id = (int)lua_tointeger(L, 2);
	mailSystem->ChangeMailAwardStatus(id);
	return 0;
}

int getStoneInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	StoneSystem *pStone = pRole->GetStoneSystem();
	if (!pStone) return 0;

	std::vector<int> pStoneData = pStone->GetStoneData();

	lua_newtable(L);
	for (int pos = 0; pos < EquipSlotType_Max; ++pos)
	{
		lua_pushinteger(L, pos);
		lua_pushinteger(L, pStoneData[pos]);
		lua_settable(L, -3);
	}
	return 1;
}

void setStoneLevel(void *et, int roleId, int posId, int level)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	StoneSystem *pStone = pRole->GetStoneSystem();
	if (!pStone) return;

	pStone->SetLevel(posId, level);
}

void clearStoneAttr(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	StoneSystem *pStone = pRole->GetStoneSystem();
	if (!pStone) return;

	pStone->ClearAttr();
}

void addStoneAttr(void* et, int roleId, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	StoneSystem *pStone = pRole->GetStoneSystem();
	if (!pStone) return;

	pStone->AddAttr(type, value);
}

int getJingmaiInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	JingmaiSystem *pJingmai = pRole->GetJingmaiSystem();
	if (!pJingmai) return 0;

	const JingMaiData* pData = pJingmai->GetJingmaiData();

	lua_pushinteger(L, pData->stage);
	lua_pushinteger(L, pData->level);

	return 2;
}

void setJingmaiLevel(void* et, int roleId, int level)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	JingmaiSystem *pJingmai = pRole->GetJingmaiSystem();
	if (!pJingmai) return;

	pJingmai->SetLevel(level);
}

void setJingmaiStage(void* et, int roleId, int stage)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	JingmaiSystem *pJingmai = pRole->GetJingmaiSystem();
	if (!pJingmai) return;

	pJingmai->SetStage(stage);
}

void clearJingmaiAttr(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	JingmaiSystem *pJingmai = pRole->GetJingmaiSystem();
	if (!pJingmai) return;

	pJingmai->ClearAttr();
}

void addJingmaiAttr(void* et, int roleId, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	JingmaiSystem *pJingmai = pRole->GetJingmaiSystem();
	if (!pJingmai) return;

	pJingmai->AddAttr(type, value);
}

Attribute* getNeigongAttr(void* actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return NULL;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return NULL;

	return pRole->GetNeigongSystem()->GetNeigongAttr();
}

int getZhulingInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	ZhulingSystem *pZhuling = pRole->GetZhulingSystem();
	if (!pZhuling) return 0;

	std::vector<int> pZhulingData = pZhuling->GetZhulingData();

	lua_newtable(L);
	for (int pos = 0; pos < EquipSlotType_Max; ++pos)
	{
		lua_pushinteger(L, pos);
		lua_pushinteger(L, pZhulingData[pos]);
		lua_settable(L, -3);
	}
	return 1;
}

void setZhulingLevel(void* actor, int roleId, int posId, int level)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	ZhulingSystem *pZhuling = pRole->GetZhulingSystem();
	if (!pZhuling) return;

	pZhuling->SetLevel(posId, level);
}

void clearZhulingAttr(void* actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	ZhulingSystem *pZhuling = pRole->GetZhulingSystem();
	if (!pZhuling) return;

	pZhuling->ClearAttr();
}

void addZhulingAttr(void* actor, int roleId, int type, int value)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	ZhulingSystem *pZhuling = pRole->GetZhulingSystem();
	if (!pZhuling) return;

	pZhuling->AddAttr(type, value);
}

void takeOutEquip(void* actor, int roleId, int posId, int equiptype)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor*)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	EquipSystem *pEquip = pRole->GetEquipSystem();
	if (!pEquip) return;


	pEquip->TakeOutEquip(posId, equiptype);
}

Attribute getEquipAttr(void* actor, int roleId, int posId)
{
	Attribute attribute;
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return attribute;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return attribute;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return attribute;

	EquipSystem *pEquip = pRole->GetEquipSystem();
	if (!pEquip) return attribute;

	
	if (!pEquip->GetEquipAttrBySlot(posId, attribute))
		return attribute;

	return attribute;
}

ExAttribute getEquipExAttr(void* actor, int roleId, int posId)
{
	ExAttribute ex_attribute;
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return ex_attribute;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return ex_attribute;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return ex_attribute;

	EquipSystem *pEquip = pRole->GetEquipSystem();
	if (!pEquip) return ex_attribute;


	if (!pEquip->GetEquipExAttrBySlot(posId, ex_attribute))
		return ex_attribute;

	return ex_attribute;
}

Attribute* getZhuanShengAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return ((Actor*)actor)->GetZhuanShengSystem()->GetAttr();
}

Attribute* getExRingAttr(void* role)
{
	if (!role || ((Entity*)role)->GetType() != EntityType_Role) return NULL;

	return ((Role*)role)->GetExRingSystem()->GetAttr();
}

ExAttribute * getExRingExAttr(void * role)
{
	if (!role || ((Entity*)role)->GetType() != EntityType_Role) return NULL;

	return ((Role*)role)->GetExRingSystem()->GetExAttr();
}

Attribute * getActorExRingAttr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return ((Actor*)actor)->GetActorExRingAttr();
}

ExAttribute * getActorExRingExAttr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return ((Actor*)actor)->GetActorExRingSystem()->GetExAttr();
}

Attribute* getActorExRingMonsterAttr(void *actor, int rid)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetActorExRingSystem()->GetMonsterAttr(rid);
}

ExAttribute* getActorExRingMonsterExAttr(void *actor, int rid)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetActorExRingSystem()->GetMonsterExAttr(rid);
}

Monster* createActorExRingMonster(void *actor, int rid, int id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetActorExRingSystem()->CreateExRingMonster(rid, id);
}

void DestroyBattleRing(void *actor, int rid)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetActorExRingSystem()->DestroyBattleRing(rid);
}

Monster* getActorExRingMonster(void *actor, int rid)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetActorExRingSystem()->GetExRingMonster(rid);
}

void SetMasterHandle(void *et, void *met)
{
	if (!et || !met) return;
	((Entity*)et)->SetMasterHandle(((Entity*)met)->GetHandle());
}

void changeMonsterAi(void *et, int aid)
{
	if (!et || !((Entity*)et)->IsCreature()) return;
	((Creature*)et)->ChangeAi(aid);
}

Attribute* getTogetherHitAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return &((Actor*)actor)->GetTogetherHitSystem()->GetAttr();
}

ExAttribute* getTogetherHitExAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return &((Actor*)actor)->GetTogetherHitSystem()->GetExAttr();
}

ExAttribute* getTogetherHitSkillExAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return &((Actor*)actor)->GetTogetherHitSystem()->GetSkillExAttr();
}

Attribute* getActorsystemAttr(void* actor, int attrId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetActorsystemAttr(attrId);
}

int getZhuanShengLevel(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetBasicData()->zhuansheng_lv;
}

int getReincarnateLv(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetBasicData()->reincarnate_lv;
}

int getRoleSkillLevel(void* actor, int roleid, int index)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	RoleData* data = ((Actor*)actor)->GetRoleSystem()->GetRoleData(roleid);
	if (data)
		return data->skills.skill_level[index];
	return 0;
}

void upgradeSkill(void* actor, int roleid, int index, int level)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleid);
	if (role)
		role->GetSkillSystem()->UpgradeSkill(index, level);
}

int getRoleSkillBreakLevel(void* actor, int roleid, int index)
{
	//if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	//Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleid);
	//if (role)
	//	return role->GetSkillBreakSystem()->GetSkillBreakLevel(index);
	return 0;
}

void upgradeSkillBreak(void* actor, int roleid, int index)
{
	//if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	//Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleid);
	//if (role)
	//	role->GetSkillBreakSystem()->UpgradeSkillBreakLevel(index);
}

int getStoreItemData(lua_State* L)
{
	Entity* actor = (Entity*)lua_touserdata(L, 1);

	if (!actor || actor->GetType() != EntityType_Actor) return 0;
	StoreSystem *pStore = ((Actor *)actor)->GetStoreSystem();
	if (!pStore) return 0;

	int id = (int)lua_tointeger(L,2);
	const StoreItemData* pData = pStore->GetStoreItemData(id);
	if (!pData) return 0;

	lua_pushinteger(L, pData->currency_type);
	lua_pushinteger(L, pData->currency);
	return 2;
}

//int giveStoreItem(void* actor, int id)
int giveStoreItem(lua_State* L)
{
	Entity* actor = (Entity*)lua_touserdata(L, 1);

	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	StoreSystem *pStore = ((Actor *)actor)->GetStoreSystem();
	if (!pStore) return 0;
	int id = (int)lua_tointeger(L, 2);

	int itemid = 0;
	int count = 0;
	pStore->GiveStoreItem(id, itemid, count);
	lua_pushinteger(L, itemid);
	lua_pushinteger(L, count);
	return 2;
}

void addStoreItem(void* actor, int id, int itemId, int count, int currencyType, int currency, int discount)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	StoreSystem *pStore = ((Actor *)actor)->GetStoreSystem();
	if (!pStore) return;

	pStore->AddStoreItem(id, itemId, count, currencyType, currency, discount);
}

void StoreClearList(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	StoreSystem *pStore = ((Actor *)actor)->GetStoreSystem();
	if (!pStore) return;

	pStore->StoreClearList();
}

void StoreDataSync(void* actor, int refreshCount)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	StoreSystem *pStore = ((Actor *)actor)->GetStoreSystem();
	if (!pStore) return;

	pStore->StoreDataSync(refreshCount);
}

void* getAITarget(void* creature)
{
	if (!creature || !((Entity*)creature)->IsCreature()) return NULL;
	return ((Creature*)creature)->GetTarget();
}

void changeAITarget(void* creature, int type)
{
	if (!creature || !((Entity*)creature)->IsCreature()) return;
	if (((Creature*)creature)->GetAI() == NULL) return;
	((Creature*)creature)->GetAI()->ChangeTarget(type);
}


void setAITarget(void* creature, void* target)
{
	if (creature == target)
	{
		return;
	}

	if (creature && target && ((Entity*)creature)->GetType() == EntityType_Actor)
	{//玩家的特殊处理
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			auto role = ((Actor*)creature)->GetRoleSystem()->GetRoleById(i);
			if (role)
			{
				setAITarget(role, target);
			}
		}
		for (int i = 0; i < ActorExRingType_MAX; ++i)
		{
			auto monster = ((Actor*)creature)->GetActorExRingSystem()->GetExRingMonster(i);
			if (monster)
			{
				setAITarget(monster, target);
			}
		}
		return;
	}

	if (!creature || !((Entity*)creature)->IsCreature()) return;
	if (!target || !((Entity*)target)->IsCreature()) return;

	if (((Creature*)creature)->GetAI() == NULL) return;
	if (((Creature*)creature)->GetType() == EntityType_Role)
	{
		if (((Creature*)target)->GetType() != EntityType_GatherMonster)
		{
			Actor* actor = (((Role*)creature))->GetActor();
			if (actor->GetCurrGatherMonster())
			{
				actor->GetCurrGatherMonster()->EndGather(false);
			}
		}
		auto pet = (((Role*)creature))->GetBattlePet();
		if (pet)
		{
			setAITarget(pet, target);
		}
	}
	if (((Creature*)target)->GetType() == EntityType_GatherMonster)
	{
		GatherMonster* gather = (GatherMonster*)target;
		if (gather->GetGatherMonsterType() == FLAGS)
		{
			if (gather->GetGatherActor())
			{
				auto camp = ((Creature*)creature)->GetCamp();
				auto actor = gather->GetGatherActor();
				bool is_battle = false;
				for (int i = 0; i < getRoleCount(actor); ++i)
				{
					Role* role = (Role*)getRole(actor, i);
					if (role)
					{
						if (camp == role->GetCamp())
						{
							is_battle = false;
						}
						else
						{
							is_battle = true;
						}
						break;

					}
				}
				if (is_battle)
				{
					auto role = actor->GetLiveByJob();
					if (role)
					{
						((Creature*)creature)->GetAI()->ClearHatred();
						((Creature*)creature)->SetTarget((Creature*)role);
						((Creature*)creature)->GetAI()->ToState(AI::asBattle);
					}
					return;
				}
			}
		}
	}
	((Creature*)creature)->GetAI()->ClearHatred();
	((Creature*)creature)->GetAI()->setPassivity(false);
	((Creature*)creature)->SetTarget((Creature*)target);
	((Creature*)creature)->GetAI()->ToState(AI::asBattle);

}

void setAITargetNull(void *creature) {
	if (!creature || !((Entity*)creature)->IsCreature()) return;
	((Creature*)creature)->SetTarget(NULL);
	if (((Entity*)creature)->GetType() == EntityType_CloneRole) {
		((RoleClone*)creature)->SetAexringTargetNull();
	}
}

void setAIPassivity(void* creature, bool b)
{
	if (!creature || !((Entity*)creature)->IsCreature()) return;
	if (((Creature*)creature)->GetAI() == NULL) return;
	((Creature*)creature)->GetAI()->setPassivity(b);
	if (((Entity*)creature)->GetType() == EntityType_CloneRole) {
		((RoleClone*)creature)->SetAexringPassivity(b);
	}
}

bool getAIPassivity(void* creature) {
	if (!creature || !((Entity*)creature)->IsCreature()) return false;
	if (((Creature*)creature)->GetAI() == NULL) return false;
	return ((Creature*)creature)->GetAI()->getPassivity();
}

void setAIAttackMonster(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor)
	{
		return;
	}
	auto a = (Actor*)actor;
	auto s = a->GetScene();
	if (s == nullptr) return;
	auto live = a->GetLiveByJob();
	if (live == nullptr)
	{
		return;
	}
	static VisiHandleList* monster_list = &GameEngine::global_var_->ai_visible_list_;
	monster_list->clear();
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	s->GetMonsterList(*monster_list);
	int cnt = monster_list->count();
	EntityHandle *list = *monster_list;
	std::vector<Creature*> et_list;
	for (int i = 0; i < cnt; ++i)
	{
		Entity *et = em->GetEntity(list[i]);
		if (!et || !et->IsCreature()) continue;
		if (et->GetType() == EntityType_Monster) {
			if (((Monster*)et)->GetMonType() == MonsterType_Pet) {//不打宠物(召唤物)
				continue;
			} else if (((Monster*)et)->GetMonType() == MonsterType_AexRing) {//不打特戒
				continue;
			}
		}
		for (int j = 0; j < MAX_ROLE; ++j)
		{
			auto role = a->GetRoleSystem()->GetRoleById(j);
			if (role)
			{
				if (et == role)
				{
					break;
				}
				if (((Creature*)et)->GetCamp() == role->GetCamp())
				{
					break;
				}
				et_list.push_back((Creature*)et);
				break;
			}

		}

	}

	if (et_list.empty()) return;

	Creature* found = et_list[0];
	int min_dist = ::GetPixDistance(found->GetPosition(), live->GetPosition(), 0);
	for (size_t i = 1; i < et_list.size(); ++i)
	{
		auto et = et_list[i];
		int dist = ::GetPixDistance(et->GetPosition(), live->GetPosition(), 0);
		if (dist < min_dist)
		{
			found = (Creature*)et;
			min_dist = dist;
		}
	}
	setAITarget(a, found);
}


int getSoulShieldinfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	SoulshieldSystem *psoulshielSystem = pRole->GetSoulshieldSystem();
	if (!psoulshielSystem) return 0;
	int type = (int)lua_tonumber(L, 3);

	const LoogsoulData *loogdata = psoulshielSystem->GetsoulData();
// 	const ShieldData *shielddata = psoulshielSystem->GetshielData();
// 	const XueyuData *xueyudata = psoulshielSystem->GetxueyuData();

	switch (type)
	{
	case  ssLoongSoul:
		lua_pushinteger(L, loogdata->stage);
		lua_pushinteger(L, loogdata->level);
		lua_pushinteger(L, loogdata->exp);
		lua_pushinteger(L, loogdata->act);
		return 4;
		break;
// 	case  ssShield:
// 		lua_pushinteger(L, shielddata->stage);
// 		lua_pushinteger(L, shielddata->level);
// 		lua_pushinteger(L, shielddata->exp);
// 		return 3;
// 		break;
// 	case  ssXueyu:
// 		lua_pushinteger(L, xueyudata->stage);
// 		lua_pushinteger(L, xueyudata->level);
// 		lua_pushinteger(L, xueyudata->exp);
// 		return 3;
// 		break;
	default:
		return -1;
		break;
	}
	return -1;
}

void setSoulShieldLevel(void* et, int roleId, int type,int level)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *SoulshieldSystem = pRole->GetSoulshieldSystem();
	if (!SoulshieldSystem) return;

	SoulshieldSystem->SetLevel(type,level);
}

void setSoulShieldExp(void* et, int roleId, int type, int exp)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *SoulshieldSystem = pRole->GetSoulshieldSystem();
	if (!SoulshieldSystem) return;

	SoulshieldSystem->SetExp(type, exp);
}

void setSoulShieldAct(void* et, int roleId, int type, int act)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *SoulshieldSystem = pRole->GetSoulshieldSystem();
	if (!SoulshieldSystem) return;

	SoulshieldSystem->SetAct(type, act);
}

void setSoulShieldStage(void* et, int roleId, int type, int stage)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *SoulshieldSystem = pRole->GetSoulshieldSystem();
	if (!SoulshieldSystem) return;

	SoulshieldSystem->SetStage(type, stage);
}



/*
int getSoulShieldLevel(void* actor, int roleId, int type)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return -1;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return -1;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return -1;

	SoulshieldSystem *pSys = pRole->GetSoulshieldSystem();
	if (!pSys) return -1;

	return pSys->GetLevel(type);
}
*/
/*
void setSoulShieldLevel(void* actor, int roleId, int type, int level)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *pSys = pRole->GetSoulshieldSystem();
	if (!pSys) return;

	pSys->SetLevel(type, level);
}
*/
void clearSoulShieldAttr(void* actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *pSys = pRole->GetSoulshieldSystem();
	if (!pSys) return;

	pSys->ClearAttr();
}

void addSoulShieldAttr(void* actor, int roleId, int type, int value)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	SoulshieldSystem *pSys = pRole->GetSoulshieldSystem();
	if (!pSys) return;

	pSys->AddAttr(type, value);
}

void giveItemToDepot(void* actor, int itemId, int count, const char *log)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	Depot *pDepot = ((Actor *)actor)->GetDepot();
	if (!pDepot) return;

	pDepot->AppendItem(itemId, count, log);
}

int getDepotCount(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	Depot *pDepot = ((Actor *)actor)->GetDepot();
	if (!pDepot) return 0;
	return static_cast<int>(pDepot->GetCount());
}

Attribute* getRoleBasicAttr(void* actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return nullptr;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return nullptr;

	return pRole->GetBasicAttrs();
}

Attribute* getKnighthoodAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetKnighthoodAttr();
}

ExAttribute* getKnighthoodExAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetKnighthoodExAttr();
}

Attribute* getYuPeiAttr(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->getYuPeiAttr();
}

ExAttribute* getYuPeiExAttr(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->getYuPeiExAttr();
}

Attribute* getPerstigeAttr(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->getPerstigeAttr();
}

Attribute* getArtifactsAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetArtifactsAttr();
}

Attribute* getTrainsystemAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetTrainsystemAttr();
}

ExAttribute * getTrainsystemExAttr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	return ((Actor*)actor)->GetTrainsystemExAttr();
}

Attribute* getChallengefbsystemAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetChallengefbsystem();
}

Attribute* getRongLuAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetRongLuAttr();
}

Attribute* getMonthCardAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetMonthCardAttr();
}

Attribute* GetReincarnateAttr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetReincarnateAttr();
}

ExAttribute* GetReincarnateExAttr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetReincarnateExAttr();
}

Attribute* getPrivilegeAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetPrivilegeAttr();
}

Attribute* getVipAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetVipAttr();
}

Attribute * getNewWorldBossAttr(void * actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetNewWorldBossAttr();
}

Attribute* getGodWeaponAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetGodWeaponSystem()->GetAttr();
}

ExAttribute* getGodWeaponExAttr(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetGodWeaponExAttr();
}

bool isImage(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return false;

	return ((Actor*)actor)->IsImage();
}

int getGmLevel(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)actor)->GetGmLevel();
}

unsigned int getCreateTime(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->GetCreateTime();
}

void updataEquipBagCapacity(void* actor,int add, int capacity)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	Actor* a = (Actor*)actor;
	a->GetEquipBag()->UpdataCapacity(add, capacity);
}

Attribute* getEquipPointAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	Actor* a = (Actor*)actor;
	auto r = a->GetRoleSystem()->GetRoleById(role_id);

	if (r == nullptr)
	{
		return nullptr;
	}
	return r->GetEquipPointAttrs();
}

void* getActorInfoPacket(void* et)
{
	if (et == nullptr || ((Entity*)et)->GetType() != EntityType_Actor) return nullptr;
	Actor* actor = (Actor*)et;

	static BaseAllocator actorcache_alloc("actorcache");
	static DataPacket actorcache_packet(&actorcache_alloc);
	actorcache_packet.setLength(0);
	actor->putActorInfo2Pack(actorcache_packet);
	return &actorcache_packet;
}

bool GetActorInfo(void * actor, int actor_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return false;

	ActorPacket AP;
	Actor *src = GetGameEngine()->GetEntityMgr()->GetActorPtrById(actor_id);
	if (!src || !src->IsInited() || src->IsImage())
		return false;

	DataPacket& pack = ((Actor *)actor)->AllocPacket(AP);

	pack << (uint8_t)Protocol::CMD_Base;
	pack << (uint8_t)Protocol::sBaseCmd_ResActorInfo;
	src->putActorInfo2Pack(pack);

	AP.flush();

	return true;
}

int findTiantiActor(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return 	GetGameEngine()->GetTianti().FindActor((Actor*)actor);
}

void createRoldClone(int actor_id, unsigned int scene,int x,int y, int sid, int camp)
{
	GetGameEngine()->GetTianti().CreateCloneRole(actor_id, scene,x,y, sid, camp);
}

void* createRobot(RobotData* data, unsigned int scene, int x, int y)
{
	return GetGameEngine()->GetTianti().CreateRobot(data, scene, x, y);
}
bool cloneRoleEmpty(unsigned int scene)
{
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();

	Scene* s = mgr->GetScenePtr(scene);
	if (!s)
	{
		OutputMsg(rmError, "create clone role scen failed.");
		return true;
	}

	return s->CloneRoleEmpyt();
}
void tiantiRefreshWeek(void)
{
	GetGameEngine()->GetTianti().refreshWeek();
}

Attribute* getEquipBlessAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	Actor* a = (Actor*)actor;
	auto r = a->GetRoleSystem()->GetRoleById(role_id);

	if (r == nullptr)
	{
		return nullptr;
	}
	return r->GetBlessSystem()->GetAttr();
}

void changeMiJi(void* actor, int roleid, int oldId, int id, bool refresh, int param1, int param2, int param3, int power)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleid);
	if (role == NULL) return;
	role->GetMiJiSystem()->ChangeMiJi(oldId, id, refresh, param1, param2, param3, power);
}

void refreshMiJi(void* actor, int roleid)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleid);
	if (role == NULL) return;
	role->GetMiJiSystem()->Refresh();
}


Attribute* getTitleAttrs(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return nullptr;
	Actor* actor = (Actor*)et;

	return actor->GetTitleSystem()->GetAttr();
}

void reCalcTitleAttr(void* et)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;
		TitleSystem* titleSys = actor->GetTitleSystem();
		if (!titleSys) return;

		Role* list[MAX_ROLE] = { NULL };
		actor->GetRoleSystem()->GetRoles(list);

		for (int i = 0; i < MAX_ROLE; ++i)
		{
			Role* role = list[i];
			if (!role) break;
			role->CalcAttributes();
		}
	}
}

void setRoleTitle(void* et, int roleId, int tId)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;
		actor->GetTitleSystem()->setRoleTitle(roleId, tId);
	}
}

void* getRainingFirstCacheByType(int type)
{
	return GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->GetFirstCacheByType((RankingType)type);
}

void updateDynamicFirstCache(int actor_id, int type)
{
	GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->UpdateDynamicFirstCache(actor_id,(RankingType) type);
}

void updateRanking(void)
{
	GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr()->UpdateRank();
}

int  getRankDataByType(lua_State* l)
{
	int type = (int)lua_tonumber(l, 1);
	static auto mgr = GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr();
	auto basic = mgr->GetRanking((RankingType)type);
	if (basic)
	{
		auto ret = basic->GetRankData();
		if (ret.size() > 0)
		{
			LuaHelp::PushDataPointerToTable(l, (void**)&ret[0], ret.size());
			return 1;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

int getRanking(int type, void * et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return 0;
	Actor* actor = (Actor*)et;
	static auto mgr = GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr();
	auto basic = mgr->GetRanking((RankingType)type);
	if (!basic)
	{
		return 0;
	}

	return basic->GetActorRanking(actor);
}

void* getRankCacheByType(int type, int min, int max)
{
	static auto mgr = GetGameEngine()->GetRankingSystem()->GetStaticRankingMgr();
	auto basic = mgr->GetRanking((RankingType)type);
	if (!basic)
	{
		return nullptr;
	}

	return basic->GetRankCache((size_t)min,(size_t)max);
}

void regAsynEvent(int actorid)
{
	GetGameEngine()->GetActorAsynMgr()->RegActorScriptEv(actorid);
}

Attribute * getGuildSkillAttrs(void * actor, int roleId)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	Actor* a = (Actor*)actor;
	Role* role = a->GetRoleSystem()->GetRoleById(roleId);
	if (!role) return nullptr;
	return role->GetGuildSkillAttrs();
}


int getGuildId(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)actor)->GetGuildSystem()->GetGuildId();
}

void * getGuildPtr(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;

	return ((Actor*)actor)->GetGuildSystem()->GetGuildPtr();
}

int getGuildPos(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	return ((Actor*)actor)->GetGuildSystem()->GetGuildPos();
}

const char * getGuildName(void * actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;
	return ((Actor*)actor)->GetGuildName();
}

int getTotalGx(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != enActor) return 0;

	Guild* guild = ((Actor*)actor)->GetGuildSystem()->GetGuildPtr();

	if (!guild) return 0;

	return guild->GetMemberTotalGx(((Actor*)actor)->GetActorId());
}

void changeTotalGx(void* actor, int val)
{
	if (!actor || ((Entity*)actor)->GetType() != enActor) return;

	Guild* guild = ((Actor*)actor)->GetGuildSystem()->GetGuildPtr();

	if (!guild) return;

	guild->ChangeMemberTotalGx(((Actor*)actor)->GetActorId(), val);
}

void saveDb(void* actorImage)
{
	if (!actorImage || ((Entity*)actorImage)->GetType() != enActor) return;
	// 导出给lua的接口只考虑镜像才需要
	if (!((Actor*)actorImage)->IsImage()) return;
	
	((Actor*)actorImage)->SaveDb();
}

void changeName(void* et, const char* name, int way/* = 0*/)
{
	if (name == NULL || et == NULL || ((Entity*)et)->GetType() != enActor)
		return;

	static BaseAllocator alloc("GameClientAlloc");
	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imChangeUserName;
	msg.data_.packet_ = new DataPacket(&alloc);
	(*msg.data_.packet_) << ((Actor*)et)->GetActorId() << (int)((Actor*)et)->GetSex() << (int)way << name << ((Entity*)et)->GetEntityName();

	mgr->PostMsg(msg);
}


void setEntityName(void* et, const char* name)
{
	if (name == NULL || et == NULL || ((Entity*)et)->GetType() != enActor)
		return;

	char lastName[ACTOR_NAME_BUFF_LENGTH] = { 0 };
	_STRNCPY_A(lastName, ((Entity*)et)->GetEntityName());
	//((Entity*)et)->SetEntityName(name);
	Actor* actor = (Actor*)et;
	actor->SetActorName(name);

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	em->OnActorChangeName(actor, lastName);

	if (actor->GetGuildSystem()->GetGuildPos() == smGuildLeader)
	{
		Guild* guild = actor->GetGuildSystem()->GetGuildPtr();

		if (guild != NULL)
		{
			guild->LeaderNameUpdate();
		}
	}

}
void addEffect(void* actor, int id)
{
	if (!actor) return;

	Role* roles[MAX_ROLE];
	((Actor*)actor)->GetRoleSystem()->GetRoles(roles);
	for (int i = 0; i < MAX_ROLE; i++)
	{
		Role* role = roles[i];
		if (role)
		{
			//role->GetSkillSystem()->OnCastSkill(id, role);
			role->GetSkillEffectSystem()->AddEffect(role, id);
		}
	}
}

int getItemData(lua_State* L)
{
	Actor* et = (Actor*)lua_touserdata(L, 1);
	double uId = (double)lua_tonumber(L, 2);

	if (!et || et->GetType() != EntityType_Actor) return 0;

	long long u_id;
	memcpy(&u_id, &uId, sizeof(u_id));

	Item* item = ((Actor*)et)->GetEquipBag()->GetItem(u_id);
	if (!item)
	{
		item = ((Actor*)et)->GetItemBag()->GetItem(u_id);
		if (!item)
			return 0;
	}

	auto itemdata = item->GetItemData();
	lua_newtable(L);
	for (int pos = 0; pos < EQUIP_ATTR_COUNT; ++pos)
	{
		lua_pushinteger(L, pos);

		lua_newtable(L);
		lua_pushinteger(L, ITEM_ATTR_TYPE);
		lua_pushinteger(L, itemdata.attr_data.equip_attr.attr[pos][ITEM_ATTR_TYPE]);
		lua_settable(L, -3);
		lua_pushinteger(L, ITEM_ATTR_VALUE);
		lua_pushinteger(L, itemdata.attr_data.equip_attr.attr[pos][ITEM_ATTR_VALUE]);
		lua_settable(L, -3);

		lua_settable(L, -3);
	}
	return 1;
}

int getItemIdByUid(void* actor, double uid)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	long long u_id;
	memcpy(&u_id, &uid, sizeof(uid));

	auto item = ((Actor*)actor)->GetEquipBag()->GetItem(u_id);
	if (item) return item->GetId();
	item = ((Actor*)actor)->GetItemBag()->GetItem(u_id);
	if (item) return item->GetId();

	return 0;
}

int getItemInfoByUid(lua_State* L)
{
	Actor* actor = (Actor*)lua_touserdata(L, 1);
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;

	double uid = (double)lua_tonumber(L, 2);
	long long u_id;
	memcpy(&u_id, &uid, sizeof(uid));

	int itemId = 0;
	int itemCount = 0;
	auto item = ((Actor*)actor)->GetEquipBag()->GetItem(u_id);
	if (item) {
		itemId = item->GetId();
		itemCount = item->GetCount();
	}
	else {
		item = ((Actor*)actor)->GetItemBag()->GetItem(u_id);
		if (item) {
			itemId = item->GetId();
			itemCount = item->GetCount();
		}
	}
	lua_pushinteger(L, itemId);
	lua_pushinteger(L, itemCount);
	return 2;
}

bool costItemByUid(void* actor, double uid, int count, const char* log)
{
	if (actor == NULL || ((Entity*)actor)->GetType() != EntityType_Actor) return NULL;

	long long u_id;
	memcpy(&u_id, &uid, sizeof(uid));

	return ((Actor*)actor)->CostItemByUid(u_id, count, log);
}

void setCamp(void* et, int camp)
{
	if (!et)
	{
		return;
	}
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		((Actor*)et)->SetCamp(camp);
	}
	else if (((Entity*)et)->IsCreature())
	{
		((Creature*)et)->SetCamp(camp);
	}
}

int getCamp(void* et)
{
	if (!et)
	{
		return 1;
	}
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		return ((Actor*)et)->GetCamp();
	}
	else if (((Entity*)et)->IsCreature())
	{
		return ((Creature*)et)->GetCamp();
	}
	return 1;
}

void setCanChangeCamp(void* et, bool canChange)
{
	if (!et)
	{
		return;
	}
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		((Actor*)et)->setCanChangeCamp(canChange);
	}
	else if (((Entity*)et)->IsCreature())
	{
		((Creature*)et)->setCanChangeCamp(canChange);
	}
}

void initZhanLingInfo(void* actor, int id, int level, int effId, int rate)
{
	if (!actor && ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetZhanLingInfo(id, level, effId);
	((Actor*)actor)->ClearZhanLingEffect();
	((Actor*)actor)->AddZhanLingEffect(effId, rate);
}

void setZhanLingId(void* actor, int id)
{
	if (!actor && ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetZhanLingId(id);
}

void addZhanLingEffect(void* actor, int id, int rate)
{
	if (!actor && ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->AddZhanLingEffect(id, rate);
}

void setZhanLingConfig(int cd, int delay)
{
	Actor::SetShowZhanLingCd(cd, delay);
	RoleClone::SetShowZhanLingCd(cd, delay);
}

void* getLiveByPower(void* actor)
{
	if (actor == nullptr)
	{
		return nullptr;
	}
	if (((Entity*)actor)->GetType() != EntityType_Actor)
	{
		return nullptr;
	}

	return ((Actor*)actor)->GetLiveByPower();
}

void* getLiveByJob(void* actor)
{
	if (actor == nullptr)
	{
		return nullptr;
	}
	if (((Entity*)actor)->GetType() != EntityType_Actor)
	{
		return nullptr;
	}

	return ((Actor*)actor)->GetLiveByJob();
}

int getEquipId(void* role, short pos)
{
	if (!role)
	{
		return 0;
	}
	if (((Entity*)role)->GetType() != EntityType_Role)
	{
		return 0;
	}
	return ((Role*)role)->GetEquipSystem()->GetEquipId(pos);
}

int getEquipQuality(void * role, short pos)
{
	if (!role)
	{
		return 0;
	}
	if (((Entity*)role)->GetType() != EntityType_Role)
	{
		return 0;
	}
	return ((Role*)role)->GetEquipSystem()->GetEquipQuality(pos);
}

int getEquipLevel(void * role, short pos, int &zsLevel)
{
	if (!role)
	{
		return 0;
	}
	if (((Entity*)role)->GetType() != EntityType_Role)
	{
		return 0;
	}
	int level = 0;
	((Role*)role)->GetEquipSystem()->getEquipLevel(pos, level, zsLevel);
	return level;
}

void* getBattlePet(void* role)
{
	if (!role)
	{
		return nullptr;
	}
	if (!((Entity*)role)->IsCreature())
	{
		return nullptr;
	}
	return ((Creature*)role)->GetBattlePet();
}

void setZhuangBan(void* actor, int roleindex, int pos1id, int pos2id, int pos3id)
{
	if (!actor) return;
	Role* role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleindex);
	if (role)
	{
		ZhuangBanData* data = role->GetZhuangBanSystem()->GetZhuangBanData();
		data->pos1id = pos1id;
		data->pos2id = pos2id;
		data->pos3id = pos3id;
	}
}

int getZhuangBan(lua_State * L) {
	Entity* actor = (Entity*)lua_touserdata(L, 1);
	if (!actor || actor->GetType() != EntityType_Actor) return 0;
	int roleId = (int)lua_tonumber(L, 2);
	Role* pRole = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleId);
	if (!pRole) return 0;
	ZhuangBanData* data = pRole->GetZhuangBanSystem()->GetZhuangBanData();
	lua_pushinteger(L, data->pos1id);
	lua_pushinteger(L, data->pos2id);
	lua_pushinteger(L, data->pos3id);
	return 3;
}


Attribute* getRoleZhuangBanAttr(void* actor, int roleindex)
{
	if (!actor) return nullptr;
	Role * role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(roleindex);
	if (role)
		return role->GetZhuangBanSystem()->GetAttr();
	else
		return nullptr;
}

double getMasterHdl(void* et)
{
	if (!et)
	{
		return 0;
	}
	if (!((Entity*)et)->IsCreature())
	{
		return 0;
	}
	if (!((Entity*)et)->GetMaster())
	{
		return 0;
	}
	double ret = 0;
	memcpy(&ret, &((Entity*)et)->GetMaster()->GetHandle(), sizeof(ret));
	return ret;
}

void* getMaster(void* et)
{
	if (!et)
	{
		return nullptr;
	}
	if (!((Entity*)et)->IsCreature())
	{
		return nullptr;
	}
	if (!((Entity*)et)->GetMaster())
	{
		return nullptr;
	}
	return ((Entity*)et)->GetMaster();
}

void KillMonster(double hdl)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	auto et = (Entity*)getEntity(hdl);
	if (et && et->IsCreature() && et->GetType() == EntityType_Monster)
	{
		auto mon = (Monster*)et;
		mon->SetHp(0);
		mon->ChangeHp(0);
		mon->GetFuBen()->OnEntityDie(mon, 0);
		auto scene = mon->GetScene();
		if (scene)
		{
			scene->ExitScene(et);
			em->DestroyEntity((int64_t)hdl);
		}
	}
}

void DestroyEntity(void* et, bool delay)
{
	if (!et) return;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	em->DestroyEntity(((Entity*)et)->GetHandle(), delay);
}

int getOffMsg(lua_State* L)
{
	Actor* actor = (Actor*)lua_touserdata(L, 1);
	int idx = (int)lua_tointeger(L, 2);

	if (!actor || actor->GetType() != EntityType_Actor) return 0;

	MsgSystem::MsgData* msg = actor->GetMsgSystem()->GetMsg(idx);

	if (!msg) return 0;

	double id;
	memcpy(&id, &msg->id_, sizeof(id));
lua_pushnumber(L, id);
lua_pushlightuserdata(L, &msg->pack_);
return 2;
}

int getOffMsgCnt(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return -1;

	return ((Actor*)et)->GetMsgSystem()->GetMsgCnt();
}

int getOffMsgIndex(void* et, double msg_id)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return -1;

	int64_t real_msg_id;
	memcpy(&real_msg_id, &msg_id, sizeof(msg_id));
	return ((Actor*)et)->GetMsgSystem()->GetMsgIndex(real_msg_id);
}

bool deleteOffMsg(void* et, int idx)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return false;

	return ((Actor*)et)->GetMsgSystem()->DeleteMsg(idx);
}

void AddSkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->AddSkill(id);
			//role->GetAI()->GetConfig()->skills.push_back()
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->AddSkill(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->AddSkill(id);
	}
}
void AddAISkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->AddAISkill(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->AddAISkill(id);
	}
	else
		OutputMsg(rmError, "-----AddAISkill----- %d; %d", id, ((Entity*)et)->GetType());
}
void DelAISkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelAISkill(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelAISkill(id);
	}
	else
		OutputMsg(rmError, "-----DelAISkill----- %d; %d", id, ((Entity*)et)->GetType());
}
void DelAllAISkill(void* et)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelAllAISkill();
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelAllAISkill();
	}
	else
		OutputMsg(rmError, "-----DelAllAISkill-----  %d", ((Entity*)et)->GetType());
}
void DelSkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelSkill(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelSkill(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->DelSkill(id);
	}
}

void DelSkillById(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelSkillById(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelSkillById(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->DelSkillById(id);
	}
}

void DelAllSkill(void* et) {
	if (!et) return;
	if (((Entity*)et)->IsCreature()) {
		((Creature*)et)->GetSkillSystem()->DelAllSkill();
	}
}

void AddPassiveSkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->AddPassiveSkill(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->AddPassiveSkill(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->AddPassiveSkill(id);
	}
}

void DelPassiveSkill(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelPassiveSkill(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelPassiveSkill(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->DelPassiveSkill(id);
	}
}

void DelPassiveSkillById(void* et, int id)
{
	if (!et) return;
	if (((Entity*)et)->GetType() == EntityType_Actor)
	{
		Actor* actor = (Actor*)et;

		for (int i = 0; i < actor->GetRoleSystem()->GetRoleCount(); ++i)
		{
			auto role = actor->GetRoleSystem()->GetRoleById(i);
			if (!role) return;
			role->GetSkillSystem()->DelPassiveSkillById(id);
		}
	}
	else if (((Entity*)et)->GetType() == EntityType_Role)
	{
		Role *role = (Role *)et;
		role->GetSkillSystem()->DelPassiveSkillById(id);
	}
	else if (((Entity*)et)->GetType() == EntityType_Monster)
	{
		((Monster*)et)->GetSkillSystem()->DelPassiveSkillById(id);
	}
}

void TogetherHitInfoSync(void* actor)
{
	if (!actor) return;
	if (((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetTogetherHitSystem()->TogetherHitInfoSync();
}

int getFuWenuIdInfo(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);

	if (!et || et->GetType() != EntityType_Actor) return 0;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return 0;

	int roleId = (int)lua_tonumber(L, 2);
	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return 0;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return 0;

	const FuWenData* pData = pFuWenSystem->GetFuWenData();
	if (!pData) return 0;

	lua_newtable(L);

	for (int pos = 0; pos < MAX_FUWEN; ++pos)
	{
		lua_pushinteger(L, pos);
		lua_pushinteger(L, pData->fuwen_slot[pos].id);
		lua_settable(L, -3);
	}
	
	return 1;
}

bool CheckFuWenByPost(void* et,int posid)
{
	Actor* actor = (Actor*)et;
	if (!actor) return false;

	Role *pRole = actor->GetRoleSystem()->GetRoleById(0);
	if (!pRole) return false;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return false;

	const FuWenData* pData = pFuWenSystem->GetFuWenData();
	if (!pData) return false;

	auto it = pData->fuwen_slot[posid];
	if (it.uid == 0)
		return true;

	return false;
}

int getPosition(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);
	if (!et) return 0;
	const Point& pos = et->GetPosition();
	Grid gpos(pos);
	lua_pushinteger(L, gpos.x);
	lua_pushinteger(L, gpos.y);
	return 2;
}
int getOriginPosition(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);
	if (!et) return 0;
	const Point& pos = et->GetOriginPosition();
	Grid gpos(pos);
	lua_pushinteger(L, gpos.x);
	lua_pushinteger(L, gpos.y);
	return 2;
}
int getDropBagData(lua_State* L)
{
	Entity* et = (Entity*)lua_touserdata(L, 1);
	if (!et || et->GetType() != EntityType_DropBag) return 0;
	DropBag *drop = (DropBag*)et;
	lua_pushinteger(L, drop->GetBelongId());
	lua_pushinteger(L, drop->GetRewardType());
	lua_pushinteger(L, drop->GetRewardId());
	lua_pushinteger(L, drop->GetRewardCount());
	return 4;
}

void SetFuwen(void* et, int roleId, int posid, double uid)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return;
	int64_t uuid = 0;
	memcpy(&uuid, &uid, sizeof(uid));
	pFuWenSystem->SetEquipFuwen(posid, uuid);
}

void FuwenLevelup(void* et, int roleId, int posid, int itemId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return;

	pFuWenSystem->FuwenLevelup(posid, itemId);
}

void addFuWenExattr(void*et, int roleid, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleid);
	if (!pRole) return;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return;

	pFuWenSystem->AddExAttr(type, value);
}


void CalcExAttr(void*et, int roleid)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleid);
	if (!pRole) return;
	pRole->CalcExAttributes();
}


void clearFuWenAttr(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	FuWenSystem *pFuWenSystemm = pRole->GetFuWenSystem();
	if (!pFuWenSystemm) return;

	pFuWenSystemm->ClearAttr();
}

void addFuWenAttr(void* et, int roleId, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return;

	pFuWenSystem->AddAttr(type, value);
}

Attribute* getFuWenAttr(void* et, int roleId)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return NULL;
	RoleSystem *roleSystem = ((Actor *)et)->GetRoleSystem();
	if (!roleSystem) return NULL;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return NULL;

	FuWenSystem *pFuWenSystem = pRole->GetFuWenSystem();
	if (!pFuWenSystem) return NULL;

	return pFuWenSystem->GetAttr();
}

void addImbaExattr(void*et, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;

	ImbaSystem *pImbaSystem = ((Actor *)et)->GetImbaSystem();
	if (!pImbaSystem) return;

	pImbaSystem->AddExAttr(type, value);
}

void clearImbaAttr(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;

	ImbaSystem *pImbaSystem = ((Actor *)et)->GetImbaSystem();
	if (!pImbaSystem) return;

	pImbaSystem->ClearAttr();
}

void addImbaAttr(void* et, int type, int value)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return;

	ImbaSystem *pImbaSystem = ((Actor *)et)->GetImbaSystem();
	if (!pImbaSystem) return;

	pImbaSystem->AddAttr(type, value);
}

Attribute* getImbaAttr(void* et)
{
	if (!et || ((Entity*)et)->GetType() != EntityType_Actor) return nullptr;

	ImbaSystem *pImbaSystem = ((Actor *)et)->GetImbaSystem();
	if (!pImbaSystem) return nullptr;

	return pImbaSystem->GetAttr();
}

void SetInvincible(void* et, bool res)
{
	if (!et || !((Entity*)et)->IsCreature()) return;
	((Creature*)et)->SetInvincible(res);
}

void* getActorByEt(void* et)
{
	if (!et) return NULL;
	return ((Entity*)et)->GetActor();
}

void clearImbaActId(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetImbaSystem()->ClearActId();
}

void addImbaActId(void* actor, int id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetImbaSystem()->AddActId(id);
}

void clearGodWeaponActId(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetGodWeaponSystem()->ClearActId();
}

void addGodWeaponActId(void* actor, int idx, int id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	
	((Actor*)actor)->GetGodWeaponSystem()->AddActId(idx, id);
}

void setGodWeaponPeak(void* actor, int peak)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	((Actor*)actor)->GetGodWeaponSystem()->setPeak(peak);
}

void setGodWeaponLevel(void* actor, int level)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	((Actor*)actor)->GetGodWeaponSystem()->setLevel(level);
}

void setGodWeaponPower(void* actor, int job, int power)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;

	((Actor*)actor)->GetGodWeaponSystem()->setPower(job, power);
}

void clearGodWeaponPower(void* actor)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->GetGodWeaponSystem()->clearPower();
}

int getHeirloomLv(void* actor, int roleId, int slot)
{
	if (slot < 0 || slot >= EquipSlotType_Max) return -1;
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return -1;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return -1;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return -1;
	
	return pRole->GetData()->heirloom[slot];
}

void setHeirloomLv(void* actor, int roleId, int slot, int lv)
{
	if (slot < 0 || slot >= EquipSlotType_Max) return;
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	RoleSystem *roleSystem = ((Actor *)actor)->GetRoleSystem();
	if (!roleSystem) return;

	Role *pRole = roleSystem->GetRoleById(roleId);
	if (!pRole) return;

	pRole->GetData()->heirloom[slot] = lv;
}

Attribute* GetHeirloomAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetHeirloomAttrs();
}

Attribute* GetWeaponSoulAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetWeaponSoulAttrs();
}

ExAttribute* GetWeaponSoulExAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetWeaponSoulExAttrs();
}

Attribute* GetCampBattleAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetCampBattleAttrs();
}

Attribute* GetReincarnateEquipAttr(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetReincarnateEquipAttr();
}

ExAttribute * GetReincarnateEquipExAttr(void * actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetReincarnateEquipExAttr();
}

Attribute* GetGodWingAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetGodWingAttrs();
}

ExAttribute* GetGodWingExAttrs(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetGodWingExAttrs();
}

ExAttribute * GetWingExAttrs(void * actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return nullptr;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return nullptr;

	return r->GetWingExAttrs();
}

int getUseingWeaponSoulId(void* actor, int role_id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return 0;

	return r->GetData()->weapon_soul_id;
}

void setUseingWeaponSoulId(void* actor, int role_id, int id)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	auto r = ((Actor*)actor)->GetRoleSystem()->GetRoleById(role_id);
	if (r == nullptr) return;

	r->GetData()->weapon_soul_id = id;
}

int TuJianPower(void* actor) 
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->getTujianPower();
}

int getEquipBasePower(void* actor) 	
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return 0;
	return ((Actor*)actor)->getEquipBasePower();
}

bool hasJobRole(void* actor, int job)
{
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return false;
	for (int i = 0; i < ((Actor*)actor)->GetRoleSystem()->GetRoleCount(); ++i) {
		auto role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(i);
		if (job == role->GetJob()) return true;
	}
	return false;
}

void SetTogeLv(void* actor, int lv) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetTogeLv(lv);
}

void SetYuPeiLv(void* actor, int lv) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	((Actor*)actor)->SetYuPeiLv(lv);
}

bool InSafeArea(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return false;
	auto role = ((Actor*)actor)->GetLiveByJob();
	if (role) return role->InSafeArea();
	return false;
}

void stopAI(void* actor) {
	if (!actor || ((Entity*)actor)->GetType() != EntityType_Actor) return;
	for (int i = 0; i < ((Actor*)actor)->GetRoleSystem()->GetRoleCount(); ++i) {
		auto role = ((Actor*)actor)->GetRoleSystem()->GetRoleById(i);
		if (role) {
			if (role->GetAI()) {
				role->GetAI()->setPassivity(true);
			}
			role->SetTarget(NULL);
		}
	}
	((Actor*)actor)->GetActorExRingSystem()->stopAllExringAi();
}

int getSceneAreaIParm(lua_State* L) {
	Entity* et = (Entity*)lua_touserdata(L, 1);
	if (!et || et->GetType() != EntityType_Actor) return 0;
	int attr = (int)lua_tonumber(L, 2);
	auto scene = et->GetScene();
	if (!scene) return 0;
	auto vec = scene->GetAreaAttriparm(SceneAreaAttrDef(attr), Grid(et->GetPosition()));
	if (!vec) return 0;
	for (auto it : (*vec)) {
		lua_pushinteger(L, it);
	}
	return static_cast<int>(vec->size());
}

void RequestFubenPathLine(void* role, int x, int y)
{
	if (role == NULL) return;
	if (((Entity*)role)->GetType() != EntityType_Role) return;
	auto ai = ((Role*)role)->GetAI();
	if (ai) {
		Point point = Grid(x, y).ToPoint();
		ai->PathToTarget(point.x, point.y);
	}
}
void MonsterFubenPathLine(void* role, int x, int y)
{
	if (role == NULL) return;
	if (((Entity*)role)->GetType() != EntityType_Monster) return;
	auto ai = ((Monster*)role)->GetAI();
	if (ai) {
		Point point = Grid(x,y).ToPoint();
		ai->PathToTarget(point.x, point.y);
	}
}
int getSceneId(void* et)
{
	if (et == NULL || ((Entity*)et)->GetType() != EntityType_Actor) return false;

	Scene* scene = ((Entity*)et)->GetScene();
	if (scene == NULL) return 0;
	return scene->GetId();
}
// AttrsSystem
AttrsSystem *getAttrsSystem(void* actor, int roleId)
{
	if (nullptr == actor || static_cast<Entity *>(actor)->GetType() != EntityType_Actor)
		return nullptr;

	Role *pRole = static_cast<Actor *>(actor)->GetRoleSystem()->GetRoleById(roleId);
	if (nullptr == pRole) return nullptr;

	return pRole->GetAttrsSystem();
}

void AddSkillRevise(void* et, int skillId, int cd, double a, int b)
{
	if (et == nullptr || !((Entity*)et)->IsCreature()) return;
	//借用神器技能修正数据结构，如有需要可以重新定义新类型
	ImbaSkillRevise rev;
	rev.cd = cd;
	rev.a = static_cast<float>(a);
	rev.b = b;
	((Creature*)et)->GetSkillSystem()->AddSkillRevise(skillId, rev);
}
bool clearAttrs(void* actor, int roleId, int attrSysId)
{
	AttrsSystem *pAttrsSystem = getAttrsSystem(actor, roleId);
	if (nullptr == pAttrsSystem) return false;
	pAttrsSystem->ClearBaseAttr(attrSysId);
	//pAttrsSystem->ClearExaAttr(attrSysId);
	return true;
}

bool addAttrsBaseAttr(void* actor, int roleId, int attrSysId, int type, int value)
{
	AttrsSystem *pAttrsSystem = getAttrsSystem(actor, roleId);
	if (nullptr == pAttrsSystem) return false;
	pAttrsSystem->AddBaseAttr(attrSysId, type, value);
	return true;
}

bool addAttrsExaPower(void* actor, int roleId, int attrSysId, int power)
{
	AttrsSystem *pAttrsSystem = getAttrsSystem(actor, roleId);
	if (nullptr == pAttrsSystem) return false;
	pAttrsSystem->AddExaPower(attrSysId, power);
	return true;
}

Attribute* getAttrs(void* actor, int roleId, int attrSysId)
{
	AttrsSystem *pAttrsSystem = getAttrsSystem(actor, roleId);
	if (nullptr == pAttrsSystem) return nullptr;
	return pAttrsSystem->GetBaseAttr(attrSysId);
}

void AddSkillReviseSelfBuff(void* et, int skillId, int buffId)
{
	if (et == nullptr || !((Entity*)et)->IsCreature() || buffId <= 0) return;
	((Creature*)et)->GetSkillSystem()->AddSkillReviseSelfBuff(skillId, buffId);
}

void AddSkillReviseTarBuff(void* et, int skillId, int buffId)
{
	if (et == nullptr || !((Entity*)et)->IsCreature() || buffId <= 0) return;
	((Creature*)et)->GetSkillSystem()->AddSkillReviseTarBuff(skillId, buffId);
}

void SetFlameStampLv(void* et, int level)
{
	if (et == nullptr) return;

	if (((Entity*)et)->GetType() == EntityType_Actor) {
		((Actor*)et)->SetFlameStampLv(level);
	}
	else if (((Entity*)et)->GetType() == EntityType_CloneRole) {
		((RoleClone*)et)->SetFlameStampLv(level);
	}
}

void SetFlameStampSkillLv(void* et, int skillId, int level) {
	if (et == nullptr) return;

	if (((Entity*)et)->GetType() == EntityType_Actor) {
		((Actor*)et)->SetFlameStampSkillLv(skillId - 1, level);
	}
	else if (((Entity*)et)->GetType() == EntityType_CloneRole) {
		((RoleClone*)et)->SetFlameStampSkillLv(skillId - 1, level);
	}
}

void SetSkillCdById(void *et, int skillId, int cd_time)
{
	if (nullptr == et) return;

	static auto ge = GetGameEngine();
	int64_t now_t = ge->getTickCount();
	int64_t cd_mtime_ = now_t + cd_time;

	if (((Entity*)et)->GetType() == EntityType_Monster) {
		//暂时只有特戒怪使用，需要再加
		((Monster*)et)->GetSkillSystem()->SetSkillCdById(skillId, cd_mtime_);
		return;
	}
}

bool CIsEquip(int equipID)
{
	auto pItemConf = ItemConfigPool::GetItemConfig(equipID);
	if (pItemConf == nullptr)
	{
		return false;
	}
	return pItemConf->isEquip();
}

void AddPVMRecord(int actorid, int targetid, int result, int changerank, int targetrank, int recordtime)
{
	TianTiManger::GetInstance()->AddRecordByScript(actorid,  targetid,  result,  changerank,  targetrank, recordtime);
}

void UpdataRank(int actorid, int newrank)
{
	TianTiManger::GetInstance()->UpdataRank(actorid, newrank);
}

void SendPVMRank(void* actor, int Limit,int flag)
{
	if (nullptr == actor || static_cast<Entity *>(actor)->GetType() != EntityType_Actor)
		return;

	if (Limit <= 0)
	{
		Limit = 20;
	}

	TianTiManger::GetInstance()->SendRankToClient((Actor*)actor, Limit, flag);
}

void SendPVMRecord(void * actor)
{
	if (nullptr == actor || static_cast<Entity *>(actor)->GetType() != EntityType_Actor)
		return;

	TianTiManger::GetInstance()->SendChallengeRecordToClient((Actor*)actor);
}

void InitMaxRecordCount(int max_count)
{
	TianTiManger::GetInstance()->InitRecordMaxCount(max_count);
}

int GetPlayerIDByPVMRank(int irank)
{
	return TianTiManger::GetInstance()->GetPlayerIDByRank(irank);
}

int GetPVMRankByPlayerID(int actorid)
{
	return TianTiManger::GetInstance()->GetRankByPlayerID(actorid);
}

int GetPVMRankSize()
{
	return TianTiManger::GetInstance()->GetRankSize();
}

void UpdataPvmRankOldData()
{
	//TianTiManger::GetInstance()->LoadOldData();
}

}
