#ifndef _AI_BATTLE_H_
#define _AI_BATTLE_H_


#include "../ai_state.h"


const int BATTLE_RANDOM_WALK_INTERVAL = 800;
class AIBattle : public AIState
{
public:
	AIBattle(AI*, Creature *mon, const AIEventConfigs *config, int frame_time);
	virtual ~AIBattle();

	virtual void Update(int64_t now_t);
	virtual void Reset();
private:
	int Attack(Entity *tar, const AiSkill *skill);

private:
	int64_t	last_walk_time_;
	int skill_dis_; // 技能最小距离
	
};

#endif