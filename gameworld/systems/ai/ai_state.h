#ifndef _AI_STATE_H_
#define _AI_STATE_H_

#include <vector>
#include "config/ai_config.h"
#include "ai_event.h"
#include "ai_mgr.h"
#include "ai.h"

class Creature;
class AI;
class AIEvent;

class AIState
{
public:
	static const int AI_MOVE_ESTIMATE_RANGE = 3;	// 移动预判位置范围
	AIState(AI* ai_msgr, Creature *mon, const AIEventConfigs *conf, int frame_time);
	virtual ~AIState();

	void SetCurrentEvent(AIEvent* e) { current_event_ = e; }
	AIEvent* GetCurrentEvent() { return current_event_; }
	int GetStateTime();
	int GetVision(){ return ai_mgr_->GetVision(); }
	bool PathToTarget(const Point& pos, int skill_dis = 0);
	bool PathToMaster(int size);
	int GetFrameTime() { return frame_time_; }
	bool CheckState();
	int GetId() { return ai_mgr_->GetId(); }

	virtual void OnAttacked(Creature*){}
	virtual void Update(int64_t now_t);
	virtual void Reset();
	virtual void OnEnterScene();

	bool IsExistFubenPathLine(Entity* et);
	//返回客户端进行a*寻路路线
	bool RequestFubenPathLine(Point &tar);


protected:
	int GetDistance(Entity *tar);
	Entity* FindOtherEnemy();

protected:
	typedef std::vector<AIEvent> AIEvents;
	static const int MAX_PATH_ERR = 10;

	AI			*ai_mgr_;
	Timer		frame_timer_;
	int			frame_time_;
	Creature		*self_;
	AIEvents	events_;
	AIEvent		*current_event_;	// 用以表示是否正在执行某个事件
	int			state_start_time_;	// 进入状态的时间

	int			path_step_;			// 每次寻路的基本单位，寻路多少格，当遇到道路不能走，这个值会减少，以增加寻路成功的几率
	EntityHandle last_attack_hdl_;
	Point last_path_point_; //
};

#endif