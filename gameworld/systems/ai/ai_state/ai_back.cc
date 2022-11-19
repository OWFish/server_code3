#include "StdAfx.h"
#include "ai_back.h"
#include "move/move_system.h"
#include "creature.h"


AIBack::AIBack(AI* ai_mgr, Creature *mon, const AIEventConfigs *config, int frame_time)
:AIState(ai_mgr, mon, config, frame_time)
, stuck_time_(0)
{
}

AIBack::~AIBack()
{
}

void AIBack::Update(int64_t now_t)
{
	// 暂时没有移动系统
	// 检查当前位置是否到达目的地
	// 到达后切换状态
	if (!PathToTarget(ai_mgr_->GetBackPos()))
		stuck_time_ = stuck_time_ == 0 ? now_t : stuck_time_;
	else
		stuck_time_ = 0;

	if (stuck_time_ > 0 && now_t - stuck_time_ > AI_FORCE_BACK_TIME )
	{
		self_->GetMoveSystem()->InstantMove(ai_mgr_->GetBackPos());
	}
		
	Point cur_pos = self_->GetPosition();
	if (cur_pos == ai_mgr_->GetBackPos())
	{ // todo 取消无敌状态**************
		ai_mgr_->ToState(AI::asIdle);
		return;
	}

	AIState::Update(now_t);
}

void AIBack::Reset()
{
	stuck_time_ = 0;
	AIState::Reset();
	// todo 设置无敌**************
	// 回血
	if (ai_mgr_->CanRecover()) {
		self_->SetHp(self_->GetMaxHp());
		if (self_->GetType() ==EntityType_Monster && self_->IsBoss() && self_->GetFuBen()) {
			ScriptValueList arg;
			arg << self_->GetFuBen()->GetHandle();
			arg << self_;
			arg << self_->GetMaxHp();
			static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
			luaScript.Call("onBossRecover", &arg, &arg, 0);
		}
	}

	// 设置目标点，并开始移动
	if (ai_mgr_->ReturnHome())
		PathToTarget(ai_mgr_->GetBackPos());
	else
		ai_mgr_->ToState(AI::asIdle);
}
