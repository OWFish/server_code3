#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "ai_born.h"

AIBorn::AIBorn(AI* ai_mgr, Creature *mon, const AIEventConfigs *config, int frame_time)
:AIState(ai_mgr, mon, config, frame_time)
{
}

AIBorn::~AIBorn()
{

}

void AIBorn::Update(int64_t now_t)
{
	ai_mgr_->ToState(AI::asIdle);
	/*FuBen *fb = self_->GetFuBen();
	if (fb && fb->IsFb())
		fb->OnMonsterBorn(self_);
		*/
}

void AIBorn::OnEnterScene()
{
	//执行一次事件
	AIState::Update(GetGameEngine()->getTickCount());
}
