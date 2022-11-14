#ifndef _AI_EVENT_H_
#define _AI_EVENT_H_

#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "config/ai_config.h"

class Creature;
class AIState;

/* 检查当前是否正在执行某种行为 moving, casting, doing action
* action执行后可能会额外产生moving和casting状态
* casting和moving中无法再次执行move和cast类型的action
* 即占用时间的行为执行中不应该执行其他占用时间的行为
*
* 所以每个event单独判断
*/

//怪物时间行为的定义
enum AIActionState {
	aasInActive = 0,	// 未执行
	aasDone,				// 执行完毕
	aasActive,				// 正在进行
};

class AIEvent
{
public:
	explicit AIEvent(const AIEventConfig *config);
	~AIEvent();

	void TryEvent(Creature *self, AIState *ai_state);
	void Reset(int64_t now_t, bool force = true);

private:
	bool TryFinishLastAction(Creature *self, AIState *ai_state);
	bool CheckTime();
	//bool CheckState(Creature *self, AIState *ai_state);
	bool CheckConditions(Creature *self, AIState *ai_state);
	int DoAction(Creature *self, AIState *ai_state);
	bool HasInstantAction();

private:
	const AIEventConfig			*config_;
	const AIConditionConfigs	*conditions_;
	const AIActionConfigs		*actions_;
	int				left_count_;
	int64_t			next_time_;

	int				current_action_;
	int				current_action_state_;
	int				current_action_left_time_;
	//int				action_data_; // 可能不需要了
};

#endif