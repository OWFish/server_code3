#ifndef _AI_BORN_H_
#define _AI_BORN_H_


#include "../ai_state.h"


class AIBorn : public AIState
{
public:
	AIBorn(AI*, Creature *mon, const AIEventConfigs *config, int frame_time);
	virtual ~AIBorn();

	virtual void Update(int64_t now_t);
	virtual void OnEnterScene();
};

#endif