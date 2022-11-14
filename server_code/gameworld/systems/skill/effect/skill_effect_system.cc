#include "StdAfx.h"
#include "skill_effect_system.h"
#include "skill_effect.h"
#include "../skill.h"
#include "creature.h"
#include "protos/skill_proto.h"



SkillEffectSystem::SkillEffectSystem(Creature *self)
: self_(self)
, logic_timer_(100)
, add_bear_hurt_(0.0f)
{
	on_run_effect_ = false;
}

SkillEffectSystem::~SkillEffectSystem()
{
	Destroy();
}

void SkillEffectSystem::Destroy()
{
	for (std::size_t i = 0; i < effect_list_.size(); ++i)
		SafeDelete(effect_list_[i]);
	effect_list_.clear();
}

bool SkillEffectSystem::HasEffect(int id) {
	for (std::size_t i = 0; i < effect_list_.size(); ++i) {
		if (effect_list_[i]->GetId() == id) {
			return true;
		}
	}
	return false;
}

bool SkillEffectSystem::AddEffect(Creature *caster, int id, int64_t time, SKILLRESULTPARAM::buff* buf, Creature *enemy, bool isSubBuff, bool isDelay)
{
#ifdef _MSC_VER
	assert(on_run_effect_ == false);
#endif // _MSC_VER
	if (on_run_effect_) 
		return false;
	const EffectConfig* conf = SkillConfigPool::GetEffectConfig(id);
	if (!conf) return false;

	if (isDelay && conf->delay > 0)
	{
		EffectArg temp_arg;
		temp_arg.clear();
		if (buf)
		{
			temp_arg.buf = buf;
		}
		if (caster)
		{
			temp_arg.caster_hdl = caster->GetHandle();
		}
		if (enemy)
		{
			temp_arg.enemy_hdl = enemy->GetHandle();
		}
		temp_arg.bufid = id;
		temp_arg.attack_time = _getTickCount() + conf->delay;
		temp_arg.end_time = time;
		delay_buf_.emplace_back(temp_arg);
		return true;
	}

	bool needAdd = true;
	if (conf->probability) {
		if (wrand(10000) > (unsigned int)conf->probability)
			return false;
	}

	if (conf->overMaxCount) {
		if (effect_group_count_[conf->group] >= conf->overMaxCount) 
			return false;
	}

	SkillEffect *effect = new SkillEffect();
	if (!effect->Init(self_, caster, id, buf, enemy))
	{
		SafeDelete(effect);
		return false;
	}

	if (time > 0)
	{
		effect->SetEndTime(time);
	}

	int gid = effect->GetGroup();
	for (std::size_t i = 0; i < effect_list_.size(); ++i) {
		if (effect_list_[i]->GetGroup() == gid)
		{
			if (effect->GetOverlayType() == EffectOverlayType_Append)
			{
				uint64_t enemy_handle = 0;
				if (nullptr != enemy) {
					enemy_handle = enemy->GetSummitHandle();
				}
				if (enemy_handle == 0) {
					//无法区分敌人的话此类型无意义
					SafeDelete(effect);
					return false;
				}

				if (enemy && enemy_handle != 0 && enemy_handle == effect_list_[i]->GetEnemyHandle())
				{
					//策划要求buff来源是同一个玩家时效果叠加并刷新时间
					effect_list_[i]->SetEndTime(conf->duration);
					effect_list_[i]->AddCacheSnapshot(effect->GetSnapshot());
					effect_list_[i]->Refresh();
					SafeDelete(effect);
					needAdd = false;
					break;
				}
			}
			else if (effect->GetOverlayType() == EffectOverlayType_NoCover) {
				SafeDelete(effect);
				return false;
			}
			else if (effect->GetOverlayType() == EffectOverlayType_Over_Extend) {
				effect_list_[i]->SetEndTime(conf->duration);
			}
			else if (effect->GetOverlayType() == EffectOverlayType_Extend) {
				effect_list_[i]->SetEndTime(conf->duration);
				SafeDelete(effect);
				return false;
			}
			else {
				effect_list_[i]->SetInvalid();
			}
		}
	}

	if (needAdd) {
		effect_list_.push_back(effect);
		effect_group_count_[effect->GetGroup()] += 1;
	}

	//通知客户端？
	Protocol::AppendSkillEffectProto msg;
	msg.target_handle = self_->GetHandle();
	msg.id = id;
	if (self_->GetScene())
		self_->GetScene()->SendData(msg, self_->GetActor());

	if (!isSubBuff) {  //子buff不附加子buff的子buff，防止无止尽循环附加
		for (std::size_t i = 0; i < conf->otherBuffs.size(); ++i) {
			AddEffect(caster, conf->otherBuffs[i], -1, nullptr, enemy, true);
		}
	}

	return true;
}

bool SkillEffectSystem::DelEffect(int id)
{
	for (std::size_t i = 0; i < effect_list_.size(); ++i)
	{
		if (effect_list_[i]->GetId() == id)
		{
			effect_list_[i]->SetInvalid();
			return true;
		}
	}
	return false;
}

void SkillEffectSystem::OnRun(int64_t now_t)
{
	if (!logic_timer_.CheckAndSet(now_t))
		return;

	int size = static_cast<int> ( effect_list_.size());
	for (int i = size - 1; i >= 0;  --i)
	{
		if (effect_list_[i]->IsInvalid())
		{
			removeUnionBuff(effect_list_[i]->GetId());
			Remove(i);
		}
	}

	on_run_effect_ = true;
	for (auto effect:effect_list_)
	{
		effect->OnTimeCheck(now_t);
	}
	on_run_effect_ = false;

	if (!delay_buf_.empty())
	{
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		for (auto it = delay_buf_.begin(); it != delay_buf_.end();)
		{
			if (it->attack_time <= now_t) 
			{
				Creature *caster = NULL;
				Creature *enemy = NULL;
				if (it->caster_hdl) 
				{
					caster = (Creature*)em->GetEntity(it->caster_hdl);
				}
				if (it->enemy_hdl)
				{
					enemy = (Creature*)em->GetEntity(it->enemy_hdl);
				}

				int skill_id = 0;
				auto pEffCfg = SkillConfigPool::GetEffectConfig(it->bufid);
				if (pEffCfg)
				{
					skill_id = pEffCfg->skillid;
				}

				const SkillConfig *pSkillConf_ = SkillConfigPool::GetSkillConfig(skill_id);
				if (pSkillConf_)
				{
					if (pSkillConf_->tar_eff.size() > 0 || pSkillConf_->other_tar_eff.size() > 0)
					{
						if (enemy == nullptr)
						{
							it = delay_buf_.erase(it);
							continue;
						}
					}
					else if(pSkillConf_->self_eff.size() > 0)
					{
						if (caster == nullptr)
						{
							it = delay_buf_.erase(it);
							continue;
						}
					}
					AddEffect(caster, it->bufid, it->end_time, it->buf, enemy, false, false);
				}
				it = delay_buf_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

}

void SkillEffectSystem::Remove(int index)
{
	if (index >= (int)effect_list_.size() || index < 0)
		return;

	int groupId = effect_list_[index]->GetGroup();
	int id = effect_list_[index]->GetId();
	effect_list_[index]->OnRemove();
	SafeDelete(effect_list_[index]);

	effect_list_[index] = effect_list_[effect_list_.size() - 1];
	effect_list_.pop_back();

	effect_group_count_[groupId] -= 1;
	if (0 >= effect_group_count_[groupId])
		effect_group_count_.erase(groupId);

	// 通知客户端
	Protocol::RemoveSkillEffectProto msg;
	msg.target_handle = self_->GetHandle();
	msg.id = id;
	if (self_->GetScene())
		self_->GetScene()->SendData(msg, self_->GetActor());
}

void SkillEffectSystem::removeUnionBuff(int effectId)
{
	const EffectConfig* conf = SkillConfigPool::GetEffectConfig(effectId);
	if (!conf) return;

	for (auto& id : conf->unionBuff)
	{
		for (std::size_t i = 0; i < effect_list_.size(); ++i)
		{
			if (effect_list_[i]->GetGroup() == id)
				effect_list_[i]->SetInvalid();
		}
	}
}

void SkillEffectSystem::CalcAttributes()
{
	attribute_.Reset();
	for (std::size_t i = 0; i < effect_list_.size(); ++i)
	{
		auto effect = effect_list_[i];
		if (effect && effect->GetAttr())
			attribute_ += *(effect->GetAttr());
	}
	self_->CalcBattleAttributes();
}

void SkillEffectSystem::CalcExAttributes()
{
	ex_attribute_.Reset();
	for (std::size_t i = 0; i < effect_list_.size(); ++i)
	{
		auto effect = effect_list_[i];
		if (effect && effect->GetExAttr())
			ex_attribute_ += *(effect->GetExAttr());
	}
	self_->CalcExAttributes();
}

void SkillEffectSystem::CalcMarkAttrs(uint64_t enemy_handle)
{
	if (enemy_handle == 0) return;

	bool isEmpty = true;
	MarkAttrs_Map &tmap = self_->GetMarkAttrsMap();
	const EffectConfig *conf = nullptr;

	auto it = tmap.find(enemy_handle);	
	if (it != tmap.end()) {
		it->second.clear();
		for (std::size_t i = 0; i < effect_list_.size(); ++i)
		{
			auto effect = effect_list_[i];
			if (effect && effect->GetEnemyHandle() == enemy_handle && !effect->IsInvalid()) {
				conf = effect->GetConfig();
				if (conf && conf->type == SkillEffectType_EnemyMarkAttr) {
					(it->second)[(int)conf->args.d] += effect->GetAllSnapshot();
					effect->ResetCacheSnapshot();
					isEmpty = false;
				}
			}
		}
		if (isEmpty) {
			tmap.erase(enemy_handle);
		}
	}
}

void SkillEffectSystem::Clear() {
	for (std::size_t i = 0; i < effect_list_.size(); ++i) {
		effect_list_[i]->SetInvalid();
	}
}

void SkillEffectSystem::OnExitScene()
{
	// 暂时全清,没有特殊的buff
	Clear();
}
