#ifndef _AI_EVENT_H_
#define _AI_EVENT_H_

#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "config/ai_config.h"

class Creature;
class AIState;

/* ��鵱ǰ�Ƿ�����ִ��ĳ����Ϊ moving, casting, doing action
* actionִ�к���ܻ�������moving��casting״̬
* casting��moving���޷��ٴ�ִ��move��cast���͵�action
* ��ռ��ʱ�����Ϊִ���в�Ӧ��ִ������ռ��ʱ�����Ϊ
*
* ����ÿ��event�����ж�
*/

//����ʱ����Ϊ�Ķ���
enum AIActionState {
	aasInActive = 0,	// δִ��
	aasDone,				// ִ�����
	aasActive,				// ���ڽ���
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
	//int				action_data_; // ���ܲ���Ҫ��
};

#endif