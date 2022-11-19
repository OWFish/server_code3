#include "StdAfx.h"
#include "protos/base_proto.h"
#include "skill/skill.h"
#include "skill/skill_system.h"
#include "skill/effect/skill_effect_system.h"
#include "skill/status_system.h"
#include "move/move_system.h"
#include "ai/ai_mgr.h"
#include "ai/ai.h"
#include "skill/skill.h"
#include "actorexring/actor_ex_ring_system.h"
#include "neigongsystem/neigong_system.h"



Creature::Creature()
: destory_t_(0)
, ai_(NULL)
, camp_(0)
, battle_pet_(NULL)
, direction_(1,1)
, regeneration_timer_(1000)
,attack_times_(0)
,be_hit_times_(0)
,resist_death_cd_(0)
, is_invincible(false)
,mark_attr_(nullptr)
{
	can_change_camp_ = true;
	skill_sys_ = new SkillSystem(this);
	move_sys_ = new MoveSystem(this);
	skill_effect_sys_ = new SkillEffectSystem(this);
	status_sys_ = new StatusSystem(this);
	neigong_sys_ = new NeigongSystem(this);
}

Creature::~Creature() {
	SafeDelete(skill_sys_);
	SafeDelete(move_sys_);
	SafeDelete(skill_effect_sys_);
	SafeDelete(status_sys_);
	SafeDelete(neigong_sys_);
}

void Creature::OnDestroy()
{
	if (battle_pet_)
	{
		battle_pet_->ChangeHp(0 - battle_pet_->GetHp(), NULL);
		//SafeDelete(battle_pet_);
	}
}

void Creature::CreateAppearData(DataPacket& appearPack)
{
	Entity::CreateAppearData(appearPack);
	static double s_attrs[Attribute::atCount];
	GetAttrs().GetAttrData(s_attrs);
	static int s_ex_attrs[ExAttribute::eatCount];
	GetExAttr().GetValues(s_ex_attrs);

	appearPack << (short)Attribute::atCount;
	appearPack.writeBuf(s_attrs, sizeof(double)* Attribute::atCount);

	appearPack << (short)ExAttribute::eatCount;
	appearPack.writeBuf(s_ex_attrs, sizeof(int)* ExAttribute::eatCount);
}

void Creature::CalcExAttributes() 
{
	ex_attrs_.Reset();
	ex_attrs_ += GetSkillEffectSystem()->GetExAttr();
}

void Creature::SetDestoryTime(unsigned int t)
{
	static GameEngine* ge = GetGameEngine();
	destory_t_ = ge->getMiniDateTime() + t;//5秒后清除
}

void Creature::ChangeHp(double nValue, Creature* attacker)
{
	if (nValue < 0 && IsInvincible()) return;
	double curHp = GetHp();
	double maxHp = GetMaxHp();
	// 如果已经没血了，不能再扣了
	if (curHp <= 0 && nValue < 0) return;

	double ret = nValue + curHp;
	if (ret < 0) {
		ret = 0;
	} else {
		if (nValue > 0 && ret > maxHp)
			ret = maxHp;
	}

	OnChangeHp(ret - curHp, attacker, ret);

	if (ret <= 0)
	{
		//抵挡一次要死的伤害
		static auto ge = GetGameEngine();
		int64_t now_tick = ge->getTickCount();
		if (resist_death_cd_ < (uint64_t)now_tick && wrand(10000) < (unsigned int)(GetExAttr(ExAttribute::eatResistDeathPro))) {//判断cd概率
			resist_death_cd_ = now_tick + GetExAttr(ExAttribute::eatResistDeathCd);
			SendBubbleEffect(RESIST_BUBBLE_TEXT_ID);
			ret = floor(GetAttr(Attribute::atHpMax) * GetExAttr(ExAttribute::eatResistDeathRate) / 10000.0);
			OnChangeHp(ret, NULL, ret);
		} else if (wrand(10000) < (unsigned int)(GetExAttr(ExAttribute::eatGodBlessProbability)) && !status_sys_->CheckStatus(StatusType_DeathCurse)) {
			SendBubbleEffect(FUHUO_BUBBLE_TEXT_ID);
			ret = floor(GetAttr(Attribute::atHpMax) * GetExAttr(ExAttribute::eatGodBlessRate) / 10000.0);
			OnChangeHp(ret, NULL, ret);
		}
	}
	attrs_.SetHp(ret);
	if (ret <= 0) {
		OnKilled(attacker);
	}


	//if (ret != currVal && isAnimal() && ((Animal*)this)->HasBitState(ebsHpEvent))
	//{
	//	ScriptValueList arg;
	//	arg << this;
	//	arg << currVal;
	//	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	//	luaScript.Call("OnChangeHp", &arg, &arg, 0);
	//}
}

void Creature::ChangeMp(double nValue, Creature* attacker)
{
	if (nValue == 0) return;

	double cur_mp = GetMp();

	// 如果已经没血了，不能再扣了
	if (cur_mp <= 0 && nValue < 0) return;

	double ret = nValue + cur_mp;
	if (ret < 0) {
		ret = 0;
	}
	else {
		double maxmp = GetMaxMp();
		if (ret > maxmp)
			ret = maxmp;
	}

	attrs_.SetMp(ret);

	OnChangeMp(nValue, attacker);
}

void Creature::ChangeNp(double nValue, Creature* attacker)
{
	if (nValue == 0) return;

	double cur_np = GetNp();

	//如果已经没内功值了，不能再扣了
	if (cur_np <= 0 && nValue < 0) return;

	double ret = nValue + cur_np;
	if (ret < 0) {
		ret = 0;
	} else {
		double maxNp = GetMaxNp();
		if (ret > maxNp)
			ret = maxNp;
	}

	attrs_.SetNp(ret);

	OnChangeNp(nValue, attacker);
}

void Creature::OnEnterScene()
{
	// 重置默认阵营，特殊场景由外部处理
	int type = GetType();
	if (type == EntityType_Monster)
		camp_ = CampType_None;
	else if (type == EntityType_Role && getCanChangeCamp())
		camp_ = CampType_Player;
	ClearDestoryTime();
	SetTarget(NULL);
	if (ai_)
		ai_->OnEnterScene();
	ResetAttactAndBeHitTimes();//切换场景重置攻击与被攻击次数
}

void Creature::OnExitScene()
{
	if (ai_)
		ai_->ToState(AI::asIdle);
	move_sys_->OnExitScene();
	if (battle_pet_) {
		GetGameEngine()->GetEntityMgr()->DestroyEntity(battle_pet_->GetHandle());
		battle_pet_ = NULL;
	}
	if (skill_effect_sys_)
		skill_effect_sys_->OnExitScene();
	SetTarget(NULL);
	Inherited::OnExitScene();
}

void Creature::OnRelive() {
	if (ai_)
		ai_->ToState(AI::asIdle);
	move_sys_->ClearMoveData();
	if (battle_pet_) {
		GetGameEngine()->GetEntityMgr()->DestroyEntity(battle_pet_->GetHandle());
		battle_pet_ = NULL;
	}
	if (skill_effect_sys_)
		skill_effect_sys_->Clear();
	SetTarget(NULL);
}

/*
void Creature::NotifyHpChangeEx(Creature *caster, double change_hp)
{
	// 只发送给施法者和自己的飘血信息
	Protocol::UpdateHpProto msg;
	msg.handle = GetHandle();
	msg.hp = GetHp() + change_hp;
	msg.need_display = true; // 设置飘血显示

	Actor *actor = GetActor();
	if (actor)
		actor->SendData(msg);
	if (caster)
	{
		Actor *caster_actor = caster->GetActor();
		if (caster_actor && caster_actor != actor)
			caster_actor->SendData(msg);
	}
}
*/

void Creature::LogicRun(int64_t curr_t)
{
	if (!IsDeath() && ai_ && GetFuBen() && GetFuBen()->IsNeedAi() && (!GetFuBen()->IsEnd() || GetScene()->GetDropBagCount() > 0))
		ai_->Update(curr_t);
	if (move_sys_)
		move_sys_->OnTimeCheck(curr_t);
	if (skill_effect_sys_)
		skill_effect_sys_->OnRun(curr_t);
	if (status_sys_)
		status_sys_->OnRun(curr_t);
	if (!IsDeath() && neigong_sys_)
		neigong_sys_->LogicRun(curr_t);
	if (!IsDeath() && skill_sys_)
		skill_sys_->LogicRun(curr_t);
	if ((!IsDeath()) && (GetHp() < GetMaxHp()) && regeneration_timer_.CheckAndSet(curr_t) && GetAttr(Attribute::atRegeneration) > 0)
	{
		//notifyHpChangeEx(NULL, GetAttr(Attribute::atRegeneration));
		ChangeHp(GetAttr(Attribute::atRegeneration));
	}
	//求血量比例
	skill_sys_->OnPassiveEvent(PassiveSkillCond_HpPer);
	//下面这个其实可以整合到上面被动技能里，先这样吧
	int eff_id = GetExAttr(ExAttribute::eatHpLtAddBuffId);
	if (eff_id && !IsDeath() && curr_t > GetSkillSystem()->GetHpLtAddBuffCd() && (GetHp() / GetMaxHp()) * 10000.0 <= GetAttr(Attribute::atHpLtAddBuff) && !GetSkillEffectSystem()->HasEffect(eff_id)) {
		GetSkillSystem()->SetHpLtAddBuffCd(curr_t + GetExAttr(ExAttribute::eatHpLtAddBuffCd));
		GetSkillEffectSystem()->AddEffect(this, eff_id); //血量低于一定值,触发回血效果
		SendBubbleEffect(HP_LT_ADD_BUFF_TEXT_ID);
	}
	eff_id = GetExAttr(ExAttribute::eatMiJiBQBuffId);
	if (eff_id && !IsDeath() && curr_t > GetSkillSystem()->GetMiJiBqCd() && (GetHp() / GetMaxHp()) * 10000.0 <= GetExAttr(ExAttribute::eatMiJiBQHpPer) && !GetSkillEffectSystem()->HasEffect(eff_id)) {
		GetSkillEffectSystem()->AddEffect(this, eff_id); //不屈秘籍的效果
		GetSkillSystem()->SetMiJiBqCd(curr_t + GetExAttr(ExAttribute::eatMiJiBQHpTime));
		SendBubbleEffect(MJBQ_HP_LT_ADD_BUFF_TEXT_ID);
	}
}

void Creature::NotifyFlyHp(Creature* caster, double damage, uint32_t hit_type)
{
	if (GetType() == EntityType_Monster && ((Monster*)this)->GetMonType() == MonsterType_AexRing)
		return;
	static Protocol::NotifyFlyHpProto proto;
	proto.thandle = GetHandle();
	if (caster) proto.shandle = caster->GetHandle();
	else proto.shandle = 0;
	proto.damage = damage;
	proto.hit_type = hit_type;

	Scene *scene = GetScene();
	if (scene)
		scene->SendData(proto, GetActor());
}

bool Creature::IsEnemy(Creature *target)
{
	if (target->IsDeath()) return false;
	// todo 复杂的情况需要在场景中做配置
	if (target->GetCamp() == camp_)
		return false;
	
	if (target->GetType() == EntityType_Monster) {
		if (((Monster*)target)->GetMonType() == MonsterType_AexRing) {//特戒怪无敌
			return false;
		} else if (((Monster*)target)->GetMonType() == MonsterType_Pet) {//召唤兽无敌
			return false;
		}
	}
	if (GetActor() && target->GetActor() && GetActor() == target->GetActor()) return false;//不管怎么样;都不能打自己人
	{
		FuBen* fb = GetFuBen();
		if (!fb) return false;
		if (fb != target->GetFuBen()) return false;
		//在世界boss里面
		if (fb->IsBelong()) {
			if (IsMonster() && !GetMaster()) return true;//没有主人的怪物;例如boss可以打任何人
			if (target->IsMonster() && !target->GetMaster()) return true;//目标是没有主人的怪物;例如任何东西都可以打BOSS


			//屏蔽掉原有副本不能相互pk规则
			//if (GetCamp() == WorldBossCampType_Belong && target->GetCamp() == WorldBossCampType_Attack)
			//{//我是归属者,对方是打过我的人
			//	return true;
			//}
			//if (GetCamp() == WorldBossCampType_Attack && target->GetCamp() == WorldBossCampType_Belong)
			//{//我是打过归属的人, 对方是归属者
			//	return true;
			//}
			//return false;
		}
	}
	//在安全区不能打
	if (target->InSafeArea()) {
		return false;
	}
	return true;
}

void Creature::OnChangeHp(double nValue, Creature* attacker, double &ret)
{
	static Protocol::UpdateHpProto proto;
	proto.handle = GetHandle();
	proto.hp = floor(ret);
	Scene *scene = GetScene();
	if(scene && scene->GetFuBen() && scene->GetFuBen()->IsFb()) {
		scene->SendData(proto);
	} else {
		Actor *actor = GetActor();
		if (actor)
			actor->SendData(proto);
	}

	if (ai_ && attacker && (nValue < 0 || (nValue == 0 && IsEnemy(attacker))) 
		&& attacker->GetScene() == GetScene())
		OnAttack(attacker, 0 - nValue);
}

void Creature::OnChangeMp(double nValue, Creature* attacker)
{
	static Protocol::UpdateMpProto proto;
	proto.handle = GetHandle();
	proto.mp = GetMp();
	//proto.need_display = false; 

	//if (attacker)
	//{
	//	proto.need_display = true;
	//	Actor* attacker_actor = attacker->GetActor();
	//	if (attacker_actor)
	//		attacker_actor->SendData(proto);
	//	Actor* self_actor = GetActor();
	//	if (self_actor)
	//		self_actor->SendData(proto);
	//	proto.need_display = false;
	//}
	Scene *scene = GetScene();
	if (scene && scene->GetFuBen() && scene->GetFuBen()->IsFb()) {
		scene->SendData(proto, GetActor());
	} else {
		Actor *actor = GetActor();
		if (actor)
			actor->SendData(proto);
	}

	if (nValue <= 0 && attacker && ai_ && attacker->GetScene() == GetScene())
		OnAttack(attacker, 0 - nValue);
}

void Creature::OnChangeNp(double nValue, Creature* attacker)
{
	static Protocol::UpdateNpProto proto;
	proto.handle = GetHandle();
	proto.np = GetNp();
	//proto.need_display = false;

	//if (attacker)
	//{
	//	proto.need_display = true;
	//	Actor* attacker_actor = attacker->GetActor();
	//	if (attacker_actor)
	//		attacker_actor->SendData(proto);
	//	Actor* self_actor = GetActor();
	//	if (self_actor)
	//		self_actor->SendData(proto);
	//	proto.need_display = false;
	//}
	Scene *scene = GetScene();
	if (scene && scene->GetFuBen() && scene->GetFuBen()->IsFb()) {
		scene->SendData(proto,GetActor());
	} else {
		Actor *actor = GetActor();
		if (actor)
			actor->SendData(proto);
	}

	if (nValue <= 0 && attacker && ai_ && attacker->GetScene() == GetScene())
		OnAttack(attacker, 0 - nValue);
}

void Creature::OnAttack(Creature* enemy, double damage)
{
	ai_->OnAttacked(enemy, damage);

	if (battle_pet_ && battle_pet_->GetAI())
		battle_pet_->GetAI()->OnAttacked(enemy, 0);
}

void Creature::OnChangeTarget(Entity * target, EntityHandle old_target_handle)
{
	//发送正在攻击谁
	if (this->GetType() == EntityType_Role || this->GetType() == EntityType_CloneRole) {
		Protocol::SwitchTargetProto msg;
		msg.src_handle = GetHandle();
		msg.tar_handle = 0;//target?(target->GetHandle()):0;
		if (target) msg.tar_handle = target->GetHandle();
		if (GetScene())
			GetScene()->SendData(msg);
		//Actor* self_actor = GetActor();
		//if (self_actor) { self_actor->SendData(msg); }
	}

	if (target && target->GetType() == EntityType_Role) {
		//世界boss副本里面的处理
		if (this->GetType() == EntityType_Role && GetFuBen()->IsBelong()) {
			//如果目标是该副本的归属者
			if (((Creature *)target)->GetCamp() == WorldBossCampType_Belong) {
				//加入攻击归属者的里面当中
				//this->GetActor()->SetCamp(WorldBossCampType_Attack);
				//获取脚本
				static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
				ScriptValueList arg;
				arg << target->GetActor();
				luaScript.Call("sendAttackedListToBelong", &arg, &arg, 1);
			}
		}
	}
}

bool Creature::IsBattle()
{
	if (ai_)
	{
		return AI::State::asBattle == ai_->GetState();
	}

	return false;
}

void Creature::ChangeAi(int id)
{
	static AiMgr* aimgr = GetGameEngine()->GetAiMgr();
	if (ai_)
		aimgr->DestroyAi(ai_);
	ai_ = aimgr->CreateAi(id, this);
}

void Creature::OnKilled(Creature* killer)
{
	Scene *sc = GetScene();
	if (sc)
	{
		if (killer) killer->GetSkillSystem()->OnPassiveEvent(PassiveSkillCond_KillTar, this);
		skill_sys_->OnPassiveEvent(PassiveSkillCond_Death);
		if (GetType() != EntityType_Role) {
			sc->AddDeathEntity(this);
		}
		FuBen* fb = sc->GetFuBen();
		if (fb)
		{
			EntityHandle hdl = 0;
			if (killer) hdl = killer->GetHandle();
			fb->OnEntityDie(this, hdl);//放在前面获取不到场景怪物正确数量
		}
	}
	if (battle_pet_)
	{
		battle_pet_->ChangeHp(0 - battle_pet_->GetHp(), killer);
		battle_pet_ = NULL;
	}

	Entity* master = GetMaster();
	if (master)
	{
		if (master->IsCreature())
		{
			if (((Creature*)master)->GetBattlePet() == this)
				((Creature*)master)->OnBattlePetKilled(killer);
		}
		if (master->GetType() == EntityType_Actor && GetType() == EntityType_Monster)
		{//正常来说;不可能会被杀的
			int rid = ((Actor*)master)->GetActorExRingSystem()->FindActorExRingMonsterRid((Monster*)this);
			if (rid >= 0)
			{
				((Actor*)master)->GetActorExRingSystem()->ClearExRingMonster(rid);
				//((Actor*)master)->GetActorExRingSystem()->CreateExRingMonster(rid, this->GetId());
			}
		}
		if (master->GetType() == EntityType_CloneRole && GetType() == EntityType_Monster)
		{//正常来说;不可能会被杀的
			((RoleClone*)master)->DelAexringMon((Monster*)this);
		}
	}
}

bool Creature::CanMove()
{
	// 检查debuf
	// 检查是否正在施法
	if (skill_sys_->IsCasting())
		return false;
	if (!status_sys_->CanMove())
		return false;

	return true;
}

void Creature::OnCastSkill(int id, Creature* tar)
{	
	if (move_sys_->IsMoving())
		move_sys_->MovingTime(true, true);

	if (tar && tar != this)
	{
		const Point& tarpos = tar->GetPosition();
		const Point& selfpos = GetPosition();
		if (!(tarpos == selfpos))
			SetDirection(Point(tarpos.x - selfpos.x, tarpos.y - selfpos.y));
	}
}

void Creature::SetTarget(Entity* target)
{
	EntityHandle old_target_handle = target_handle_;
	if (!target) {
		target_handle_ = 0;
	} else {
		if (target->GetType() == EntityType_Role) {
			auto role = ((Role*)target)->GetActor()->GetLiveByJob();
			if (role != target) {
				SetTarget(role);
				return;
			}
		//} else if (target->GetType() == EntityType_CloneRole) {
		//	((RoleClone*)target)
		} else {
			Entity* master = target->GetMaster();
			if (master) {//如果有主人的怪
				if (target->GetType() == EntityType_Monster) {
					if (((Monster*)target)->GetMonType() == MonsterType_Pet) {//宠物
						if (master->IsCreature()) {
							SetTarget(master);
						}
						return;
					} else if (((Monster*)target)->GetMonType() == MonsterType_AexRing) {//特戒
						if (master->GetType() == EntityType_Actor ) {
							//auto role = ((Actor*)master)->GetLiveByJob();
							SetTarget(master);
						} else if(master->IsCreature()) {
							SetTarget(master);
						}
						return;
					}
				}
			}
		}
		target_handle_ = target->GetHandle();
	}
	OnChangeTarget(target, old_target_handle);
	if (IsBoss())
	{
		ScriptValueList arg;
		arg << GetFuBen()->GetHandle();
		double s,d;
		memcpy(&s, &entity_handle_, sizeof(s));
		memcpy(&d, &target_handle_, sizeof(d));
		arg << s;
		arg << d;
		
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		luaScript.Call("onBossChangeTarget", &arg, &arg, 0);
	}
#ifdef _MSC_VER 
	if (GetActor() && target && GetActor() == target->GetActor())
	{
		assert(false);
	}
#endif
}

Monster* Creature::SummonBattlePet(int id)
{
	if (battle_pet_)
	{
		GetGameEngine()->GetEntityMgr()->DestroyEntity(battle_pet_->GetHandle());
		battle_pet_ = NULL;
	}

	Grid pos = GetPosition();
	Grid dir = GetDirection();//获取玩家当前方向

	//pos.x += short(wrand(2) - 1);
	//pos.y += short(wrand(2) - 1);

	if (GetTarget())
	{
		if (dir.x > 0 && dir.y >= 0)
			pos.x += 2;
		else if (dir.x > 0 && dir.y < 0)
			pos.y += 2;
		else if (dir.x <= 0 && dir.y >= 0)
			pos.x -= 2;
		else if (dir.x <= 0 && dir.y < 0)
			pos.y -= 2;
	}
	else
		pos.y -= 2;



	EntityHandle hdl;
	battle_pet_ = (Monster*)GetGameEngine()->GetEntityMgr()->CreateEntity(EntityType_Monster, hdl);

	if (battle_pet_ != NULL)
	{
		battle_pet_->SetMasterHandle(GetHandle());
		if (!battle_pet_->Init(id) || !GetScene()->EnterScene(battle_pet_, pos.x, pos.y))
		{
			GetGameEngine()->GetEntityMgr()->DestroyEntity(hdl);
			OutputMsg(rmError, "Init battlepet error.id:%d", id);
			battle_pet_ = NULL;
			return NULL;
		}
		battle_pet_->SetCamp(GetCamp());	//这个一定要放在进入场景后面,进入场景时会重置为默认的
		battle_pet_->SetTarget(GetTarget());
	}

	return battle_pet_;
}

void Creature::OnBattlePetKilled(Creature* killer)
{
	// ...
	battle_pet_ = NULL;
}

void Creature::NotifyAttr(int type, double value)
{
	static Protocol::EntityUpdateAttrProto msg;
	msg.handle = GetHandle();
	msg.count = 1; // 等有多属性需求时再考虑怎么改接扣,或增加新接口
	msg.type = type;
	msg.value = value;

	GetScene()->SendData(msg, GetActor());
}

void Creature::SendBubbleEffect(int id)
{
	//通知客户端
	Protocol::BubbleTextProto msg;
	msg.target_handle = GetHandle();
	msg.id = id;
	if (GetScene())
		GetScene()->SendData(msg, GetActor());
}

void Creature::SetCamp(int camp) {
	camp_ = camp;
	if (battle_pet_) battle_pet_->SetCamp(camp);
}
