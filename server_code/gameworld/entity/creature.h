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

// �Ժ�������Ϊս����ʵ����࣬��Ҫanimal��
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
	// ��㲥��������Ʈ��
	virtual void ChangeHp(double nValue, Creature* attacker = NULL);
	virtual void ChangeMp(double nValue, Creature* attacker = NULL);
	virtual void ChangeNp(double nValue, Creature* attacker = NULL); //�ı��ڹ�ֵ
	virtual void OnSetHp() {}
	virtual void OnSetMp() {}
	virtual void InitBasicAttribute() = 0;
	virtual void CalcAttributes() = 0;	//��������ϵͳ������
	virtual void CalcBattleAttributes() = 0; //���¼���ս��ϵͳ����
	virtual void CalcExAttributes(); //���¼�����������
	virtual bool CanMove();
	virtual void OnCastSkill(int id, Creature* tar);
	virtual void OnAddStatus(int status) {};
	virtual bool IsBoss() { return false; }
	virtual void SetTarget(Entity* target);
	virtual void OnAttack(Creature* enemy, double damage);
	virtual void OnChangeTarget(Entity* target, EntityHandle old_target_handle);
	// ս�����
	virtual float GetExtraCritDamage() { return 0; }	// ���Ⱪ���˺��ӳ�, �ؼ�ϵͳ
	virtual bool HasHuShenShield() { return false; }	// ��������
	virtual bool IsBattle();							//�Ƿ���ս��״̬
	virtual double GetAtkSum(void) { return GetAttr(Attribute::atAtk); };//��ȡ�������ܺ�
	virtual int GetYuPeiLv(void) { return 0; };
	virtual int64_t GetPrestigeExp(void) { return 0; };

	//�л�AI
	void ChangeAi(int id);
	/*----------------------------------------*/

	void SetDestoryTime(unsigned int t = 5);
	inline void ClearDestoryTime() { destory_t_ = 0; }
	inline bool IsInDeathList() { return destory_t_ != 0; }
	inline unsigned int GetDeathTime() { return destory_t_; }
	inline bool IsInvincible() { return is_invincible; }
	inline void SetInvincible(bool res) { is_invincible = res; }

	// �������
	double GetAttr(int type) {
		double markVal = 0;
		if (mark_attr_ && mark_attr_->find(type) != mark_attr_->end()) markVal = (*mark_attr_)[type];
		return attrs_.Get(type) + markVal;
	}
	double GetHp() { return attrs_.Get(Attribute::atHp); }
	void NotifyAttr(int type, double value);
	// ����㲥����ĳЩʵ���Ʈ��
	void SetHp(double hp) { attrs_.SetHp(hp); OnSetHp(); }
	double GetMaxHp() { return attrs_.Get(Attribute::atHpMax); }
	double GetMp() { return attrs_.Get(Attribute::atMp); }
	void SetMp(double mp) { attrs_.SetMp(mp); }
	double GetMaxMp() { return attrs_.Get(Attribute::atMpMax); }
	double GetNp() { return attrs_.Get(Attribute::atNeiGong); }	//��ȡ�ڹ�ֵ
	void SetNp(double np) { attrs_.SetNp(np); }					//�����ڹ�ֵ
	double GetMaxNp() { return attrs_.Get(Attribute::atNeiGongMax); }//��ȡ����ڹ�ֵ
	int GetCamp() { return camp_; }	// ��Ӫ �������ֵ��ң���ʱ���������Ӫ
	void SetCamp(int camp);
	bool getCanChangeCamp() { return can_change_camp_; };
	void setCanChangeCamp(bool can) { can_change_camp_ = can; };

	virtual int getWeaponPeakLv(void) { return 0; }
	virtual int getDeathCount(void) { return 0; }
	// ��������
	int GetExAttr(int type) { if (type < 0 || type >= ExAttribute::eatCount) return 0; return ex_attrs_.Get((ExAttribute::ExAttributeType)type); }

	// ϵͳ
	ExAttribute& GetExAttr() { return ex_attrs_; }
	const BattleAttribute& GetAttrs() const { return attrs_; }
	BattleAttribute& GetAttrs() { return attrs_; }
	SkillSystem* GetSkillSystem() { return skill_sys_; }
	MoveSystem* GetMoveSystem() { return move_sys_; }
	SkillEffectSystem* GetSkillEffectSystem() { return skill_effect_sys_; }
	StatusSystem* GetStatusSystem() { return status_sys_; }
	NeigongSystem* GetNeigongSystem() { return neigong_sys_; }
	AI*	GetAI() { return ai_; }

	// ����
	Monster* GetBattlePet() { return battle_pet_; }
	void ClearBattlePet() { battle_pet_ = NULL; }
	Monster* SummonBattlePet(int id);
	void OnBattlePetKilled(Creature* killer);
	void SetDirection(Point dir) { direction_ = dir; }
	const Point& GetDirection() { return direction_; }

	uint32_t GetAttactTimes() { return attack_times_; }//��ȡ��������
	void SetAttactTimes(uint32_t times) { attack_times_ = times; }//���ù�������
	uint32_t GetBeHitTimes() { return be_hit_times_; }//��ȡ�ܹ�������
	void SetBeHitTimes(uint32_t times) { be_hit_times_ = times; }//�����ܹ�������
	void ResetAttactAndBeHitTimes() { attack_times_ = 0; be_hit_times_ = 0; } //���ù����ͱ���������
	void SendBubbleEffect(int id);

	MarkAttrs_Map & GetMarkAttrsMap() { return enemy_mark_attrs_; }
	void SetMarkAttr(std::map<int, double> *pma) { mark_attr_ = pma; }

	//��ȡ�ƶ���·
	const std::list<Point> & GetMoveLine()
	{
		return move_line_;
	}

	//����ƶ���·
	void AddMoveLine(const Point & point)
	{
		move_line_.push_back(point);
		move_line_status_ = MOVELINE_DATA_PREPARE;
	}

	//����ƶ���·
	void ClearMoveLine()
	{
		move_line_.clear();
		move_line_status_ = MOVELINE_NORMAL;
	}

	//����״̬
	void SetMoveLineStatus(int status)
	{
		if (status != move_line_status_)
		{
			move_line_status_ = status;
		}
	}

	//��ȡ״̬
	int GetMoveLineStatus()
	{
		return move_line_status_;
	}

	void MoveLinePopData()
	{
		move_line_.pop_back();
		if (move_line_.empty())
			move_line_status_ = MOVELINE_NORMAL;//����Ҫ��������, ����״̬
	}

protected:
	virtual void OnChangeHp(double nValue, Creature* attacker, double &ret);
	virtual void OnChangeMp(double nValue, Creature* attacker);
	virtual void OnChangeNp(double nValue, Creature* attacker);//�ڹ�ֵ�ı�ص�
	virtual void OnKilled(Creature* killer);

protected:
	BattleAttribute  attrs_;	// ս������ �������� (= ������buff��
	ExAttribute		ex_attrs_;	// ��������( û��ս��, �������⼼�ܵļ���)
	SkillSystem*	skill_sys_;	// ����ϵͳ
	SkillEffectSystem* skill_effect_sys_; // ����Ч��ϵͳ��buff��debuff)
	StatusSystem*	status_sys_;// ״̬ϵͳ
	MoveSystem*		move_sys_;	// �ƶ�ϵͳ
	NeigongSystem*  neigong_sys_;
	unsigned int	destory_t_;
	AI*				ai_;
	int				camp_;		// ��Ӫ ly:������ai�п����жϵ��ң�0Ϊ����Ӫ���������Ĭ��Ϊ1
								//����ͨ����������ˢ���ض���Ӫ�Ĺ֣�ʵ�ִ󲿷ֹ��ܣ����
								//Ҫ����ҵ���Ӫ���ٸ�������޸�����
	bool			can_change_camp_;//�Ƿ���Ըı䵱ǰ��Ӫ
	Monster*		battle_pet_;  // ֻ����һ�����������ж��ٻ��༼���ͷ�
	Point			direction_; // ������ʱ�ż���ʱ��Ҫ����Ȼ��Ŀ�����Լ��ص�
	Timer			regeneration_timer_; // �ָ����

	//�����ͱ���������
	uint32_t		attack_times_; //��������
	uint32_t		be_hit_times_; //�ܹ�������
	uint64_t		resist_death_cd_; //�ֵ�����cd

	bool			is_invincible;//�Ƿ��޵�

	std::list<Point> move_line_;

	int move_line_status_ = MOVELINE_NORMAL;

	MarkAttrs_Map enemy_mark_attrs_;
	std::map<int, double> *mark_attr_;
}; 