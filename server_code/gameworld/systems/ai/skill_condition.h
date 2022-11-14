#ifndef _SKILL_CONDITION_H_
#define _SKILL_CONDITION_H_

enum SkillConditionType
{
	scNull,
	scMonsterCount,		 //������Χ������
	scTargetMonCount,   //Ŀ����Χ������
	scConditionCount,
};

class Creature;
struct SkillConditionConfig;

namespace SkillCondition {
	bool Check(const SkillConditionConfig *config, Creature *self);
}; // end of namespace


#endif