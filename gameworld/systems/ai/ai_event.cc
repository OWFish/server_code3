#include "StdAfx.h"
#include "ai_event.h"
#include "ai_state.h"
#include "ai_condition.h"


AIEvent::AIEvent(const AIEventConfig* conf)
: config_(conf)
, conditions_(&(conf->conditions))
, actions_(&(conf->actions))
, left_count_(0)
, next_time_(0)
, current_action_(0)
, current_action_state_(0)
{
}

AIEvent::~AIEvent()
{

}

/*
* 先检查是否有上次进行中的action
* 
* 正式流程：
* 1检查时间
* 2获取进行中的状态  如果有状态则检查队首action是否需要为即时的
*   为了避免不同的event互相影响，可以给即时的action配置执行时间，实际以执行结果为准
*   另一方面，释放技能类的事件，最好配置执行时间，避免不必要的条件判断。
* 3检测condition
* 4执行action
* 5根据执行结果修改相应的状态，重复1步骤
*/
void AIEvent::TryEvent(Creature *self, AIState *ai_state)
{
	if (!TryFinishLastAction(self, ai_state))
		return;

	bool condition_checked = false;
	while (CheckTime())	// action可以设定间隔
	{
		if (!ai_state->CheckState() && !HasInstantAction())
			return;
		// 条件应该只需要检查一次    吧.....
		if (!condition_checked)
		{
			if (!CheckConditions(self, ai_state))
				return;
			condition_checked = true;
		}
		if (DoAction(self, ai_state) != aasDone)
			return;

		current_action_state_ = aasInActive;
		current_action_ += 1;
		current_action_left_time_ = 0;
		if (current_action_ >= (int)actions_->size()){
			current_action_ = 0;
			next_time_ += config_->interval;
			left_count_ -= 1;
			return;
		}
	}
}


bool AIEvent::CheckTime()
{
	if (left_count_ == 0) return false;
	static GameEngine *ge = GetGameEngine();
	return next_time_ <= ge->getTickCount();
}

bool AIEvent::HasInstantAction()
{
	return (*actions_)[current_action_].duration == 0;
}

bool AIEvent::CheckConditions(Creature *self, AIState *ai_state)
{
	for (std::size_t i = 0; i < conditions_->size(); ++i)
	{
		const AIConditionConfig &condition = (*conditions_)[i];
		if (!AICondition::Check(&condition, self, ai_state))
			return false;
	}
	return true;
}


bool AIEvent::TryFinishLastAction(Creature *self, AIState *ai_state)
{
	if (current_action_state_ != aasActive)
		return true;

	ScriptValueList arg;
	arg << self;
	arg << self->GetId();	// 怪物id
	arg << ai_state->GetId();
	arg << (*actions_)[current_action_].index;
//	arg << action_data_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();

	if (!luaScript.Call("OnMonsterAction", &arg, &arg, 1))
		return false;

	int ret = (int)arg[0];
	if (ret == aasActive) {
//		action_data_ = (int)arg[1];
		current_action_left_time_ -= ai_state->GetFrameTime();
	}	// 当前action执行超过了配置的持续时间，不再处理
	if (ret == aasDone || current_action_left_time_ <= 0) {
		static GameEngine *ge = GetGameEngine();
		next_time_ = ge->getTickCount() + (*actions_)[current_action_].interval;
//		action_data_ = 0;
		current_action_state_ = aasInActive;
		current_action_ += 1;
		if (current_action_ >= (int)actions_->size()){
			current_action_ = 0;
			next_time_ += config_->interval;
		}
		current_action_left_time_ = 0;

		ai_state->SetCurrentEvent(NULL);
		return true;
	}

	return false;
}

/* 
 * 执行成功返回aasDone
 * 失败返回aasInActive 
 * (巡逻类的返回aasActive ,执行时判断是否到达阶段性目标，当前目标达到后检查下一个目标，直到最终返回aasDone)
 * (如果将巡逻拆分成多个move action，则不需要过程性数据，每个action都不需要保存数据，且可以统一配置)
 * 技能类的可以先返回aasDone，通过技能的状态来判断以简化流程
 * 执行成功的action将left_time清零
*/ 
int AIEvent::DoAction(Creature *self, AIState *ai_state)
{
	ScriptValueList arg;
	arg << self;
	arg << self->GetId();	// 怪物id
	arg << ai_state->GetId();
	arg << (*actions_)[current_action_].index;
	//printf("******************\naction args: %s\n", (*actions_)[current_action_].args);
	//arg << action_data_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();

	// 执行action脚本 
	if (!luaScript.Call("OnMonsterAction", &arg, &arg, 1))
		return aasInActive;

	int ret = (int)arg[0];
	if (ret == aasActive) {	// 这里是第一次执行，继续上次的步骤在上一层
		//action_data_ = (int)arg[1];
		current_action_state_ = aasActive;
		current_action_left_time_ = (*actions_)[current_action_].duration;
		// 如果配置的duration是0，则可能会在其他event进行中进行，那么这种action只执行一次，不继续维持。
		if (current_action_left_time_ == 0)
			ret = aasDone;
		else 
			ai_state->SetCurrentEvent(this);
	}
	if (ret == aasDone){	// 不是else if 到期的进行中action也算完成
		static GameEngine *ge = GetGameEngine();
		next_time_ = ge->getTickCount() + (*actions_)[current_action_].interval;
		//action_data_ = 0;
	}

	return ret;
}

void AIEvent::Reset(int64_t now_t, bool force)
{
	next_time_ = config_->delay + now_t;
	left_count_ = config_->lcnt == 0 ? -1 : config_->lcnt;
	
	if (!force)	// 是否重置action状态，非战斗阶段的行为需要保存以继续，其他阶段的行为不需要保存
		return;

	current_action_ = 0;
	current_action_state_ = 0;
	current_action_left_time_ = 0;
	//action_data_ = 0;
}
