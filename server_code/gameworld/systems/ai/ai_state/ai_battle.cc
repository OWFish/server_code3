#include "StdAfx.h"

#include "ai_battle.h"
#include "entity/monster/monster.h"
#include "skill/skill_system.h"
#include "script/interface/actor_export_fun.h"

#include "actor/actor.h"
#include "role/role_system.h"
#include "move/move_system.h"



AIBattle::AIBattle(AI* ai_mgr, Creature *mon, const AIEventConfigs *conf, int frame_time)
:AIState(ai_mgr, mon, conf, frame_time)
, last_walk_time_(0)
{
	skill_dis_ = ai_mgr->GetSkillMinDist();
}

AIBattle::~AIBattle()
{

}

void AIBattle::Update(int64_t now_t)
{
	// ����Ƿ���Ŀ��(Ŀ���Ƿ�����,��������)
	//		���û���ˣ���������ѡ��Ŀ��
	//		��Ȼû�еĻ��л�back״̬ ai_mgr_->ToState(AI::asBack);
	// ***���Ŀ������Ƿ񳬳���Ұ��ս������2�����᲻��õ㣿��
	// ***		��������ѡ��Ŀ�� or ֱ�ӷ���
	// ����Ƿ񳬳�׷����Χ
	//		���� ai_mgr_->ToState(AI::asBack);

	//����Լ��ڰ�ȫ����Ͳ���������� lxl
	if (self_->InSafeArea()) 
	{
		ai_mgr_->ToState(AI::asIdle);
		return;
	}

	Entity* et = self_->GetTarget();

	if (NULL == et) {
		if (ai_mgr_->ReturnHome())
			ai_mgr_->ToState(AI::asBack);
		else
			ai_mgr_->ToState(AI::asIdle);

		last_attack_hdl_ = EntityHandle();
		return;
	}

	if(et->GetType() != EntityType_DropBag) {
		//�������������ʱ��; ���зǵ�����ΪĿ��;ֱ�ӻص�����AIѰ�ҵ�����Ʒ����
		if (!self_->GetFuBen() || !self_->GetFuBen()->IsFb() || self_->GetFuBen()->IsEnd())	{
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asIdle);
			return;
		}
	} 

	//�Լ���Ŀ�궼����ҵ�ʱ��, Ŀ��������,ȥ��ڶ�����ɫ
	if (et->GetType() == EntityType_Role && self_->GetType() == EntityType_Role && et->IsDeath()) {
		auto acotr = et->GetActor();
		auto role = acotr->GetLiveByJob();
		auto rs = self_->GetActor()->GetRoleSystem();
		for (int i = 0;i < MAX_ROLE; ++i) {
			auto r = rs->GetRoleById(i);
			if (r && !r->IsDeath()) {
				r->SetTarget(role);
				r->GetAI()->ToState(AI::asBattle);
				if (r->GetBattlePet()) {
					r->GetBattlePet()->SetTarget(role);
					r->GetBattlePet()->GetAI()->ToState(AI::asBattle);
				}
			}
		}
		return;
	}
	
	////��������Ҫ��ʱ���³���б�
	//if(self_->GetType() == EntityType_Role)
	//	ai_mgr_->UpdateHatred();
	//Ŀ����Լ�����һ�������������Ŀ���Ѿ�����
	if (et->GetPosInfo().scene != self_->GetPosInfo().scene || et->IsDeath() || et->InSafeArea()) {
		if (self_->GetType() == EntityType_Role) {
			//ai_mgr_->ClearHatred();  //����Ŀ�겻��ճ��ֵ
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asIdle);
			return;
			//��ȡ��ҵĵ�һ������б����
			//et = ai_mgr_->GetFirstDamage();
			//self_->SetTarget(et);
			//if (et)
			//	ai_mgr_->ToState(AI::asBattle);
			//else 
			//{
			//	ai_mgr_->ToState(AI::asIdle);
			//	return;
			//}

		} else {
			et = FindOtherEnemy();
			if(!et) {
				self_->SetTarget(NULL);
				ai_mgr_->ToState(AI::asBack);
				return;
			}
		}
	}

	//��Ŀ��ľ���
	int et_dis = GetDistance(et);

	// ����лع�, ����Ŀ��̫Զ,�����ع�
	if (ai_mgr_->ReturnHome()) {
		//��ҵľ���
		int home_dis = ::GetPixDistance(self_->GetPosition(), ai_mgr_->GetBackPos(), 0);
		int home_range = ai_mgr_->GetHomeRange() * GRIDSIZE;
		if (home_dis > home_range || et_dis > home_range) {
			self_->SetTarget(NULL);
			ai_mgr_->ToState(AI::asBack);
			return;
		}
	}

	//Ŀ�����������͵������ﴦ��
	if (et->GetType() == EntityType_GatherMonster) {
		if (et_dis <= 1)
		{
			if (self_->GetType() == EntityType_Role)
			{
				GatherMonster* gather = (GatherMonster*)et;
				Role* role = (Role*)self_;
				if (role->GetActor() && role == role->GetActor()->GetLiveByJob()) {
					gather->BeginGather(role->GetActor());
				}
			}
			self_->SetTarget(nullptr);
			//ai_mgr_->ToState(AI::asIdle);
		}
		else if (self_->CanMove())
		{
			if (!IsExistFubenPathLine(et))
			{
				PathToTarget(et->GetPosition(), 1);
			}
		}
		return;
	} else if (et->GetType() == EntityType_DropBag) {
		if (et_dis <= 1)
		{
			if (self_->GetType() == EntityType_Role)
			{
				Role* role = (Role*)self_;
				((DropBag*)et)->GetDrop(role->GetActor());
			}
			self_->SetTarget(nullptr);
			ai_mgr_->ToState(AI::asIdle);
		}
		else if (self_->CanMove())
		{
			if (!IsExistFubenPathLine(et))
			{
				PathToTarget(et->GetPosition(), 1);
			}
		}
		return;
	}

	// ����ai��Ϊ�¼�
	AIState::Update(now_t);

	// ��⼼������Ƿ���Թ���Ŀ�ꡣ ���ܹ���ʱ�����Ҫ�ƶ���Ŀ�ĵظ��ƶ�ϵͳ
	if (self_->GetSkillSystem()->CheckPublicCd() && CheckState()) {
		// try attack
		const AiSkill *skill = ai_mgr_->CheckNextSkill(now_t);
		if (skill) { // �п��ü���

			if (skill->dis >= et_dis) {
				self_->ClearMoveLine();
				//�ڰ�ȫ�����ܴ�
				if (et->InSafeArea()) {
					if (self_->GetType() == EntityType_Role && self_->GetAI()) {
						self_->GetAI()->setPassivity(true);
						self_->SetTarget(NULL);
						ai_mgr_->ToState(AI::asIdle);
					} else {
						self_->SetTarget(NULL);
						ai_mgr_->ToState(AI::asBack);
					}
				} else {
					if (self_->GetSkillSystem()->AutoUseAISkill() == false)
					{
						int res = Attack(et, skill);
						if (res == SkillUseResult_Err) {
							self_->SetTarget(nullptr);
							ai_mgr_->ToState(AI::asIdle);
						}
					}

				}
			} else if (self_->CanMove()) {
				if (!IsExistFubenPathLine(et))
				{
					PathToTarget(et->GetPosition(), skill->dis-GRIDSIZE/4);
				}
			}
				
		} else {
			if (skill_dis_ < et_dis && self_->CanMove()) {
				if (!IsExistFubenPathLine(et)) {
					PathToTarget(et->GetPosition());
				}
			}
		}
	}
}

int AIBattle::Attack(Entity *tar, const AiSkill *skill) {
	if (!tar) { return SkillUseResult_Err; }
	auto skill_sys = self_->GetSkillSystem();
	if (!skill) { return SkillUseResult_Err;	}
	int res = skill_sys->UseSkill(skill->skill_id, skill->index);
	if (self_->GetType() == EntityType_Role && tar->GetType() == EntityType_Role) {
		auto master = tar->GetActor();
		auto actor = self_->GetActor();
		if (master && actor && last_attack_hdl_ != master->GetHandle()) {
			ActorPacket npack;
			actor->AllocPacket(npack);
			npack << (char)Protocol::CMD_GuildBattle;
			npack << (char)Protocol::sGuildBattleCmd_AttackInfo;
			npack << master->GetHandle();
			npack.flush();
			last_attack_hdl_ = master->GetHandle();
		}
	}

	if(res != SkillUseResult_OK) {
		static GameEngine* ge = GetGameEngine();
		ai_mgr_->OnUseSkill(skill->index, ge->getTickCount() + skill->cd);
	}
	return res;
}

void AIBattle::Reset()
{
	AIState::Reset();
	ai_mgr_->SetBackPos(self_->GetPosition());
}
