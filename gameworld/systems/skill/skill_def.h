#pragma once
#include <map>

class Skill;
class Creature;
typedef struct tagSkillResultParam
{
	Creature* self;
	Creature* target;
	Skill* skill;
	float def_disregard;
	float stun_power;
	double stunTime;
	double damage;
	uint8_t index;
	struct buff
	{
		int buff_id;
		int buff_time;
		float a;
		float b;
		float c;
		buff()
		{
			memset(this, 0, sizeof(*this));
		}
	};
	std::map<int, buff> buffs;

	tagSkillResultParam()
	{

		self = NULL;
		target = NULL;
		skill = NULL;
		def_disregard = 0.0f;
		stun_power = 0.0f;
		stunTime = 0.0;
		damage = 0.0;
		buffs.clear();
	}

	buff* GetBuff(int id)
	{
		auto it = buffs.find(id);
		if (it == buffs.end())
			return nullptr;
		return &it->second;
	}
}SKILLRESULTPARAM;