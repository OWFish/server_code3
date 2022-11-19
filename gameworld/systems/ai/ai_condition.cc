#include "StdAfx.h"
#include "ai_condition.h"
#include "ai_state.h"
#include "config/ai_config.h"
#include "entity/creature.h"
#include "role/role_system.h"
#include "actor/actor.h"



typedef bool(*CheckConditionFunc)(const AIConditionConfig *config, Creature *self, AIState *ai_state);

static bool DefaultFunc(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	//log
	return false;
}

bool CheckTime(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	int time = ai_state->GetStateTime();
	if (time >= config->arg1 && ( config->arg2 == 0 || time <= config->arg2))	//arg1->min arg2->max
		return true;
	return false;
}
bool CheckSelfHp(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	int hp_percent = (int)(self->GetHp() * 100 / self->GetMaxHp());
	if (hp_percent >= config->arg1 && hp_percent <= config->arg2)
		return true;
	return false;
}
bool CheckTargetHp(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	Creature* target = (Creature*)self->GetTarget();
	if (!target)
		return false;
	int hp_percent = (int)(target->GetHp() * 100 / target->GetMaxHp());
	if (hp_percent >= config->arg1 && hp_percent <= config->arg2)
		return true;
	return false;
}

bool CheckSelfRoleHp(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	if (self->GetType() != EntityType_Role)
		return false;

	Creature* tar = ((Role*)self)->GetSelfMinRole();
	if (!tar) return false;

	int hp_percent = (int)(tar->GetHp() * 100 / tar->GetMaxHp());
	if (hp_percent >= config->arg1 && hp_percent <= config->arg2)
		return true;

	return false;
}

bool CheckSelfBuff(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	//todo
	return false;
}
bool CheckTargetBuff(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	Entity* target = self->GetTarget();
	if (!target)
		return false;
	//todo

	return false;
}
bool CheckTargetDistance(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	Entity* target = self->GetTarget();
	if (!target)
		return false;

	int x, y, tar_x, tar_y;
	self->GetPosition(x, y);
	target->GetPosition(tar_x, tar_y);

	x = abs(x - tar_x);
	y = abs(y - tar_y);

	int dis = __max(x, y);

	if (dis >= config->arg1 && dis <= config->arg2)
		return true;
	return false;
}
bool CheckMonsterDistance(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	Scene *scene = self->GetScene();
	if (!scene) return false;

	EntityList& list = scene->GetMonsterList();
	ListIterator<EntityHandle> it(list);

	for (LinkedNode<EntityHandle>* node = it.first(); node; node = it.next())
	{
		Monster* pe = (Monster*)em->GetEntity(node->data_);

		if (pe && pe->GetType() == enMonster && pe->GetId() == config->arg1)
		{	// 只找一个，这种需求只考虑针对某一个特殊怪
			int x, y, tar_x, tar_y;
			self->GetPosition(x, y);
			pe->GetPosition(tar_x, tar_y);

			x = abs(x - tar_x);
			y = abs(y - tar_y);

			int dis = __max(x, y);

			if (dis >= config->arg2 && dis <= config->arg3)
				return true;
			return false;;
		}
	}
	return false;
}
bool CheckPositionDistance(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	int x, y;
	self->GetPosition(x, y);

	x = abs(x - config->arg1);
	y = abs(y - config->arg2);

	int dis = __max(x, y);

	if (dis >= config->arg3 && dis <= config->arg4)
		return true;
	return false;
}
bool CheckPlayerCount(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	return false;
	//static VisiHandleList* visibleList = &GameEngine::global_var_->ai_visible_list_;
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	//visibleList->clear();

	//int self_x, self_y;
	//self->GetPosition(self_x, self_y);

	//// 视野
	//int vision = ai_state->GetVision();
	//if (vision <= 0) return false;

	//Scene *scene = self->GetScene();
	//if (!scene) return false;

	//// 视野内对象
	//scene->GetEntityList(self_x, self_y, *visibleList, vision);
	//int cnt = visibleList->count();
	//EntityHandle *list = *visibleList;

	//Creature* found = NULL;
	//int count = 0;
	//for (int i = 0; i < cnt; ++i)
	//{
	//	Entity *et = em->GetEntity(list[i]);
	//	if (!et || et->GetType() != enActor)
	//		continue;

	//	++count;
	//}

	//if (count >= config->arg1 && count <= config->arg2)
	//	return true;
	//return false;
}

bool CheckHasBattlePet(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	int pet = 0;
	if (self->GetBattlePet())
		pet = 1;
	if (pet == config->arg1)
		return true;
	return false;
}

bool CheckHatredDistanceCount(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	if (config->arg3 <= 0) return true; // 这么配置没什么意义

	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	auto &list = self->GetAI()->GetHatredList();
	int count = 0;
	for (std::size_t i = 0; i < list.size(); ++i)
	{
		auto &info = list[i];
		Creature* tar = (Creature*)em->GetEntity(info.target);
		if (tar)
		{
			int dis = GetGridDistance(tar->GetPosition(), self->GetPosition());
			if (dis >= config->arg1 && dis <= config->arg2)
			{
				++count;
				if (count >= config->arg3)
					return true;
			}
		}
	}

	return false;
}

bool CheckHatredMonDistanceCount(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	if (config->arg3 <= 0) return true; // 这么配置没什么意义

	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	auto &list = self->GetAI()->GetHatredList();
	int count = 0;
	for (std::size_t i = 0; i < list.size(); ++i)
	{
		auto &info = list[i];
		Creature* tar = (Creature*)em->GetEntity(info.target);
		if (tar && tar->IsMonster() && !tar->GetMaster())
		{
			int dis = GetGridDistance(tar->GetPosition(), self->GetPosition());
			if (dis >= config->arg1 && dis <= config->arg2)
			{
				++count;
				if (count >= config->arg3)
					return true;
			}
		}
	}

	return false;
}

bool CheckMonsterCount(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	if (config->arg3 <= 0) return true; // 这么配置没什么意义

	Scene *scene = self->GetScene();
	if (!scene) return false;

	//场景的所有怪物
	EntityList& list = scene->GetMonsterList();
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();

	int count = 0;
	ListIterator<EntityHandle> it(list);
	for (auto node = it.first(); node; node = it.next()) {
		Entity* tar = em->GetEntity(node->data_);
		if (tar && !tar->GetMaster()) {
			int dis = GetGridDistance(tar->GetPosition(), self->GetPosition());
			if (dis >= config->arg1 && dis <= config->arg2) {
				++count;
				if (count >= config->arg3)
					return true;
			}
		}
	}

	return false;
}

bool CheckTargetMonCount(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	if (config->arg3 <= 0) return true; // 这么配置没什么意义

	auto target = self->GetTarget();
	if (!target) return false;

	Scene *scene = self->GetScene();
	if (!scene) return false;

	//场景的所有怪物
	EntityList& list = scene->GetMonsterList();
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();

	int count = 0;
	ListIterator<EntityHandle> it(list);
	for (auto node = it.first(); node; node = it.next()) {
		Entity* tar = em->GetEntity(node->data_);
		if (tar && !tar->GetMaster()) {
			int dis = GetGridDistance(tar->GetPosition(), target->GetPosition());
			if (dis >= config->arg1 && dis <= config->arg2) {
				++count;
				if (count >= config->arg3)
					return true;
			}
		}
	}

	return false;
}

static CheckConditionFunc funcs[acConditionCount] = { NULL };
static bool is_init = false;
static void AIConditionInit()
{
	funcs[acNull] = DefaultFunc;

	funcs[acTime] = CheckTime;
	funcs[acSelfHp] = CheckSelfHp;
	funcs[acTargetHp] = CheckTargetHp;
	funcs[acTargetDistance] = CheckTargetDistance;
	funcs[acSelfBuff] = CheckSelfBuff;
	funcs[acTargetBuff] = CheckTargetBuff;
	funcs[acHasBattlePet] = CheckHasBattlePet;
	funcs[acRoleMinHp] = CheckSelfRoleHp;
	funcs[acHatredListDistanceCount] = CheckHatredDistanceCount;
	funcs[acHatreListMonDisCount] = CheckHatredMonDistanceCount;
	funcs[acMonsterCount] = CheckMonsterCount;
	funcs[acTargetMonCount] = CheckTargetMonCount;
	//funcs[acMonsterDistance] = CheckMonsterDistance;
	//funcs[acPostionDistance] = CheckPositionDistance;
	//funcs[acPlayerCount] = CheckPlayerCount;

	for (int i = 0; i < acConditionCount; ++i)
	{
		if (funcs[i] == NULL)
			OutputMsg(rmWarning, "condition check function undefined. type:%d", i);
	}

	is_init = true;
}

bool AICondition::Check(const AIConditionConfig *config, Creature *self, AIState *ai_state)
{
	if (!is_init)
		AIConditionInit();

	int type = config->type;
	if (type < 0 || type >= acConditionCount)
		return false;
	if (funcs[type] == NULL)
		return false;

	return (*funcs[type])(config, self, ai_state);
}
