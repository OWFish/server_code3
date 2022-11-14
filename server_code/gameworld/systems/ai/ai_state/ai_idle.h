#ifndef _AI_IDLE_H_
#define _AI_IDLE_H_


#include "../ai_state.h"


class AIIdle : public AIState
{
public:
	AIIdle(AI*, Creature *mon, const AIEventConfigs *config, int frame_time);
	virtual ~AIIdle();

	virtual void Update(int64_t now_t);
	virtual void OnAttacked(Creature *enemy);
	virtual void Reset();
private:
	bool CheckEnemy();
	bool CheckPickUp(Entity *et);
private:
	Timer		aggressive_timer_;	// 主动攻击查找目标定时器
};

#endif