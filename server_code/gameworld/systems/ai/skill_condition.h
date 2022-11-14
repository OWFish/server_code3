#ifndef _SKILL_CONDITION_H_
#define _SKILL_CONDITION_H_

enum SkillConditionType
{
	scNull,
	scMonsterCount,		 //自身周围怪数量
	scTargetMonCount,   //目标周围怪数量
	scConditionCount,
};

class Creature;
struct SkillConditionConfig;

namespace SkillCondition {
	bool Check(const SkillConditionConfig *config, Creature *self);
}; // end of namespace


#endif