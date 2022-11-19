#include "StdAfx.h"
#include "skill_condition.h"
#include "config/ai_config.h"
#include "entity/creature.h"
#include "role/role_system.h"
#include "actor/actor.h"

typedef bool(*CheckConditionFunc)(const SkillConditionConfig *config, Creature *self);

static bool DefaultFunc(const SkillConditionConfig *config, Creature *self)
{
	return true;
}

bool CheckMonsterCount(const SkillConditionConfig * config, Creature * self)
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

bool CheckTargetMonCount(const SkillConditionConfig * config, Creature * self)
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

static CheckConditionFunc funcs[scConditionCount] = { NULL };
static bool is_init = false;
static void AIConditionInit()
{
	funcs[scNull] = DefaultFunc;
	funcs[scMonsterCount] = CheckMonsterCount;
	funcs[scTargetMonCount] = CheckTargetMonCount;

	for (int i = 0; i < scConditionCount; ++i)
	{
		if (funcs[i] == NULL)
			OutputMsg(rmWarning, "skill condition check function undefined. type:%d", i);
	}

	is_init = true;
}

bool SkillCondition::Check(const SkillConditionConfig * config, Creature * self)
{
	int type = config->type;
	if (type == 0) return true;
	if (type < 0 || type >= scConditionCount) return false;
	if (!is_init)
		AIConditionInit();

	if (funcs[type] == NULL)
		return false;

	return (*funcs[type])(config, self);
}
