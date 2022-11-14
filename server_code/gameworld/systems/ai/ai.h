#ifndef _AI_H_
#define _AI_H_
#include <vector>

/*
* AI
*/

#include "config/ai_config.h"

class Creature;
class AIState;

class AI
{
public:
	static const int MAX_SKILL = 8;
	enum State
	{
		asBorn = 0,		// ��ʼ״̬
		asIdle,			// ��ս��״̬
		asBattle,		// ս��״̬
		asBack,			// �ع�
		asDead,			// ս������״̬
		asMax,
	};
	struct DamageInfo
	{
		EntityHandle target;
		double		damage;
		friend bool operator< (const DamageInfo& lhs, const DamageInfo& rhs)
		{
			return lhs.damage > rhs.damage;
		}
	};
	typedef std::vector<DamageInfo> HatredList;

public:
	AI();
	~AI();

	bool Init(Creature *self, const AIConfig *conf);

	void Update(int64_t now_t);
	void OnAttacked(Creature *enemy, double damage = 0);
	void OnDeath();
	void ToState(State s);
	void OnEnterScene();

	int GetId() { return id; }	// ����id
	void setPassivity(bool b);
	bool getPassivity();
	bool Aggressive();	// �Ƿ�������
	bool CanRecover();	// ����ս���Ƿ�ָ�
	int GetDeadStateTime();	// ����״̬����ʱ��
	int GetVision();		// ��Ұ
	bool ReturnHome();		// �Ƿ�ع�
	int GetHomeRange();		// ���Χ

	const AiSkill* CheckNextSkill(int64_t now_t);  // ������һ������ʱ��
	const AiSkill* FindRoleNextSkill(int64_t now_t);
	//int GetNextSkillDist();
	int GetSkillMinDist();
	//const AiSkill* GetNextSkill();
	void OnUseSkill(int index, int64_t time);
	const Point& GetBackPos();
	void SetBackPos(const Point &pos);
	void ClearHatred();					
	void DeleteHatred(EntityHandle hd);//ɾ����ҳ���б�
	bool UpdateHatred();	//������ҳ���б�
	Entity* GetFirstDamage(void);   //��ȡ����б�ĵ�һ�����
	const HatredList& GetHatred();	 // ���������
	const HatredList& GetHatredList() { return damage_list_; } // ������
	Entity* SetTargetByDamageList(void);
	void PathToTarget(int gx, int gy);	// �����ӿ�
	void ChangeTarget(int type); // �л�Ŀ��
	const AIConfig* GetConfig() { return ai_conf_; }
	State GetState() { return cur_state_; };

//private:
	//void RefreshNextSkill(int64_t now_t);

private:
	bool        passivity_ = false;
	int			id;
	Creature*	self_;
	AIState*	ai_[asMax];
	State		cur_state_;
	const AIConfig*	ai_conf_; // �ļ���ָ��
	//Timer		skill_timer_;		// ��⼼�ܿ��ö�ʱ��
	Timer       time_check_;
	bool		is_add_damage_list; //�Ƿ�����˳���б����� ������  ������Ч
	int			next_skill_index_;
	int64_t		skill_cd_[MAX_SKILL];	
	Point		back_pos;   // �ع��
	HatredList	damage_list_;	// ��ʱֻ����һ���˺���û����ޣ�����������ʱû�����,�����������Actor
};


#endif

