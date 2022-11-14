#ifndef _AI_BACK_H_
#define _AI_BACK_H_


#include "../ai_state.h"


#define AI_FORCE_BACK_TIME 3000
class AIBack : public AIState
{
public:
	AIBack(AI*, Creature *mon, const AIEventConfigs *config, int frame_time);
	virtual ~AIBack();

	virtual void Update(int64_t now_t);
	virtual void Reset();
private:
	time_t stuck_time_;
};

#endif