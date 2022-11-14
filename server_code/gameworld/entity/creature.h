#pragma once

#include "entity.h"
#include "attr/battle_attr.h"
#include "attr/ex_attr.h"
#include "skill/effect/skill_effect_system.h"

typedef std::map<uint64_t, std::map<int, double>> MarkAttrs_Map;

class MoveSystem;
class AI;
class SkillSystem;
class SkillEffectSystem;
class StatusSystem;
class Monster;
class NeigongSystem;

// 以后用来作为战斗类实体基类，不要animal了
class Creature :
	public Entity
{
public:
	typedef Entity Inherited;
	Creature();
	virtual ~Creature();

	inline bool Init() { return true; }

	/*-----------------entity---------------------*/
	virtual int GetId() = 0;
	virtual inline char GetJob() { return JobType_None; }
	virtual bool IsCreature() { return true; }
	virtual void OnEnterScene();
	virtual void OnExitScene();
	virtual void OnRelive();
	//void NotifyHpChangeEx(Creature * caster, double change_hp);
	void NotifyFlyHp(Creature* caster, double damage, uint32_t hit_type);
	virtual bool IsEnemy(Creature *target);
	virtual void LogicRun(int64_t curr_t);
	virtual bool IsDeath() { return GetHp() <= 0; }
	virtual void OnDestroy();
	virtual void CreateAppearData(DataPacket& appearPack);
	/*-----------------creatrue--------------------*/
	// 会广播，但不会飘字
	virtual void ChangeHp(double nValue, Creature* attacker = NULL);
	virtual void ChangeMp(double nValue, Creature* attacker = NULL);
	virtual void ChangeNp(double nValue, Creature* attacker = NULL); //改变内功值
	virtual void OnSetHp() {}
	virtual void OnSetMp() {}
	virtual void InitBasicAttribute() = 0;
	virtual void CalcAttributes() = 0;	//重新所有系统的属性
	virtual void CalcBattleAttributes() = 0; //重新计算战斗系统属性
	virtual void CalcExAttributes(); //重新计算特殊属性
	virtual bool CanMove();
	virtual void OnCastSkill(int id, Creature* tar);
	virtual void OnAddStatus(int status) {};
	virtual bool IsBoss() { return false; }
	virtual void SetTarget(Entity* target);
	virtual void OnAttack(Creature* enemy, double damage);
	virtual void OnChangeTarget(Entity* target, EntityHandle old_target_handle);
	// 战斗相关
	virtual float GetExtraCritDamage() { return 0; }	// 额外暴击伤害加成, 秘籍系统
	virtual bool HasHuShenShield() { return false; }	// 护身真气
	virtual bool IsBattle();							//是否处于战斗状态
	virtual double GetAtkSum(void) { return GetAttr(Attribute::atAtk); };//获取攻击力总和
	virtual int GetYuPeiLv(void) { return 0; };
	virtual int64_t GetPrestigeExp(void) { return 0; };

	//切换AI
	void ChangeAi(int id);
	/*----------------------------------------*/

	void SetDestoryTime(unsigned int t = 5);
	inline void ClearDestoryTime() { destory_t_ = 0; }
	inline bool IsInDeathList() { return destory_t_ != 0; }
	inline unsigned int GetDeathTime() { return destory_t_; }
	inline bool IsInvincible() { return is_invincible; }
	inline void SetInvincible(bool res) { is_invincible = res; }

	// 属性相关
	double GetAttr(int type) {
		double markVal = 0;
		if (mark_attr_ && mark_attr_->find(type) != mark_attr_->end()) markVal = (*mark_attr_)[type];
		return attrs_.Get(type) + markVal;
	}
	double GetHp() { return attrs_.Get(Attribute::atHp); }
	void NotifyAttr(int type, double value);
	// 不会广播，但某些实体会飘字
	void SetHp(double hp) { attrs_.SetHp(hp); OnSetHp(); }
	double GetMaxHp() { return attrs_.Get(Attribute::atHpMax); }
	double GetMp() { return attrs_.Get(Attribute::atMp); }
	void SetMp(double mp) { attrs_.SetMp(mp); }
	double GetMaxMp() { return attrs_.Get(Attribute::atMpMax); }
	double GetNp() { return attrs_.Get(Attribute::atNeiGong); }	//获取内功值
	void SetNp(double np) { attrs_.SetNp(np); }					//设置内功值
	double GetMaxNp() { return attrs_.Get(Attribute::atNeiGongMax); }//获取最大内功值
	int GetCamp() { return camp_; }	// 阵营 用于区分敌我，暂时不是真的阵营
	void SetCamp(int camp);
	bool getCanChangeCamp() { return can_change_camp_; };
	void setCanChangeCamp(bool can) { can_change_camp_ = can; };

	virtual int getWeaponPeakLv(void) { return 0; }
	virtual int getDeathCount(void) { return 0; }
	// 特殊属性
	int GetExAttr(int type) { if (type < 0 || type >= ExAttribute::eatCount) return 0; return ex_attrs_.Get((ExAttribute::ExAttributeType)type); }

	// 系统
	ExAttribute& GetExAttr() { return ex_attrs_; }
	const BattleAttribute& GetAttrs() const { return attrs_; }
	BattleAttribute& GetAttrs() { return attrs_; }
	SkillSystem* GetSkillSystem() { return skill_sys_; }
	MoveSystem* GetMoveSystem() { return move_sys_; }
	SkillEffectSystem* GetSkillEffectSystem() { return skill_effect_sys_; }
	StatusSystem* GetStatusSystem() { return status_sys_; }
	NeigongSystem* GetNeigongSystem() { return neigong_sys_; }
	AI*	GetAI() { return ai_; }

	// 其他
	Monster* GetBattlePet() { return battle_pet_; }
	void ClearBattlePet() { battle_pet_ = NULL; }
	Monster* SummonBattlePet(int id);
	void OnBattlePetKilled(Creature* killer);
	void SetDirection(Point dir) { direction_ = dir; }
	const Point& GetDirection() { return direction_; }

	uint32_t GetAttactTimes() { return attack_times_; }//获取攻击次数
	void SetAttactTimes(uint32_t times) { attack_times_ = times; }//设置攻击次数
	uint32_t GetBeHitTimes() { return be_hit_times_; }//获取受攻击次数
	void SetBeHitTimes(uint32_t times) { be_hit_times_ = times; }//设置受攻击次数
	void ResetAttactAndBeHitTimes() { attack_times_ = 0; be_hit_times_ = 0; } //重置攻击和被攻击次数
	void SendBubbleEffect(int id);

	MarkAttrs_Map & GetMarkAttrsMap() { return enemy_mark_attrs_; }
	void SetMarkAttr(std::map<int, double> *pma) { mark_attr_ = pma; }

	//获取移动线路
	const std::list<Point> & GetMoveLine()
	{
		return move_line_;
	}

	//添加移动线路
	void AddMoveLine(const Point & point)
	{
		move_line_.push_back(point);
		move_line_status_ = MOVELINE_DATA_PREPARE;
	}

	//清除移动线路
	void ClearMoveLine()
	{
		move_line_.clear();
		move_line_status_ = MOVELINE_NORMAL;
	}

	//设置状态
	void SetMoveLineStatus(int status)
	{
		if (status != move_line_status_)
		{
			move_line_status_ = status;
		}
	}

	//获取状态
	int GetMoveLineStatus()
	{
		return move_line_status_;
	}

	void MoveLinePopData()
	{
		move_line_.pop_back();
		if (move_line_.empty())
			move_line_status_ = MOVELINE_NORMAL;//按照要求走完了, 重置状态
	}

protected:
	virtual void OnChangeHp(double nValue, Creature* attacker, double &ret);
	virtual void OnChangeMp(double nValue, Creature* attacker);
	virtual void OnChangeNp(double nValue, Creature* attacker);//内功值改变回调
	virtual void OnKilled(Creature* killer);

protected:
	BattleAttribute  attrs_;	// 战斗属性 最终属性 (= 基础加buff）
	ExAttribute		ex_attrs_;	// 特殊属性( 没有战力, 用于特殊技能的计算)
	SkillSystem*	skill_sys_;	// 技能系统
	SkillEffectSystem* skill_effect_sys_; // 技能效果系统（buff和debuff)
	StatusSystem*	status_sys_;// 状态系统
	MoveSystem*		move_sys_;	// 移动系统
	NeigongSystem*  neigong_sys_;
	unsigned int	destory_t_;
	AI*				ai_;
	int				camp_;		// 阵营 ly:用于在ai中快速判断敌我，0为无阵营，所有玩家默认为1
								//可以通过副本配置刷出特定阵营的怪，实现大部分功能，如果
								//要做玩家的阵营，再根据情况修改这里
	bool			can_change_camp_;//是否可以改变当前阵营
	Monster*		battle_pet_;  // 只能有一个，可用于判断召唤类技能释放
	Point			direction_; // 朝向，有时放技能时需要方向，然而目标与自己重叠
	Timer			regeneration_timer_; // 恢复间隔

	//攻击和被攻击次数
	uint32_t		attack_times_; //攻击次数
	uint32_t		be_hit_times_; //受攻击次数
	uint64_t		resist_death_cd_; //抵挡死亡cd

	bool			is_invincible;//是否无敌

	std::list<Point> move_line_;

	int move_line_status_ = MOVELINE_NORMAL;

	MarkAttrs_Map enemy_mark_attrs_;
	std::map<int, double> *mark_attr_;
}; 