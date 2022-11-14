#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#include "ai_dead.h"

AIDead::AIDead(AI* ai_mgr, Creature *mon, const AIEventConfigs *config, int frame_time)
:AIState(ai_mgr, mon, config, frame_time)
{
}

AIDead::~AIDead()
{
}

void AIDead::Update(int64_t now_t)
{
	AIState::Update(now_t);
	if (now_t / 1000 > real_dead_time_){
		Scene* sc = self_->GetScene();
		if (sc)
			sc->AddDeathEntity(self_);
		return;
	}
}

void AIDead::Reset()
{
	AIState::Reset();
	static GameEngine *ge = GetGameEngine();
	real_dead_time_ = ge->getMiniDateTime() + ai_mgr_->GetDeadStateTime();
}
