#pragma once

#include "skill_config.h"

#pragma pack(push,1)
struct Status
{
	bool enabled = false;
	int type;
	int64_t end_time = 0;
	int effect_id = 0;
	union {
		struct { // 护盾参数
			double shield_power;
			float decrease_percent;
			float highest_hurt;
		};
	} param;
	Status() { memset(this, 0, sizeof(Status)); }
};
#pragma pack(pop)

class StatusSystem
{
public:
	explicit StatusSystem(Creature *self);
	~StatusSystem();

	void AddStatus(Status &status);
	void DelStatus(int type);
	bool CanMove();
	bool CanAttack();
	bool CanControlled(); //可以被控制
	bool CanControll();   //可以控制
	bool CheckStatus(int type);

	void OnRun(int64_t now_t);
	void OnDamaged(double &damage,bool is_debuff = false);
private:
	void AddEffect(int id);
	void DelEffect(int id);
private:
	Creature*	self_;
	Status status_list_[StatusType_Count];
	Timer	frame_timer_;
};