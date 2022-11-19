#ifndef _AI_DEAD_H_
#define _AI_DEAD_H_


#include "../ai_state.h"


class AIDead : public AIState
{
public:
	AIDead(AI*, Creature *mon, const AIEventConfigs *config, int frame_time);
	virtual ~AIDead();

	virtual void Update(int64_t now_t);
	virtual void Reset();
private:
	int real_dead_time_;
};

#endif