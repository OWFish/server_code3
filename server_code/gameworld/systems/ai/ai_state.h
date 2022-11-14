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
	static const int AI_MOVE_ESTIMATE_RANGE = 3;	// �ƶ�Ԥ��λ�÷�Χ
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
	//���ؿͻ��˽���a*Ѱ··��
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
	AIEvent		*current_event_;	// ���Ա�ʾ�Ƿ�����ִ��ĳ���¼�
	int			state_start_time_;	// ����״̬��ʱ��

	int			path_step_;			// ÿ��Ѱ·�Ļ�����λ��Ѱ·���ٸ񣬵�������·�����ߣ����ֵ����٣�������Ѱ·�ɹ��ļ���
	EntityHandle last_attack_hdl_;
	Point last_path_point_; //
};

#endif