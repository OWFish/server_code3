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
		asBorn = 0,		// 初始状态
		asIdle,			// 非战斗状态
		asBattle,		// 战斗状态
		asBack,			// 回归
		asDead,			// 战斗不能状态
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

	int GetId() { return id; }	// 配置id
	void setPassivity(bool b);
	bool getPassivity();
	bool Aggressive();	// 是否主动怪
	bool CanRecover();	// 脱离战斗是否恢复
	int GetDeadStateTime();	// 死亡状态持续时间
	int GetVision();		// 视野
	bool ReturnHome();		// 是否回归
	int GetHomeRange();		// 活动范围

	const AiSkill* CheckNextSkill(int64_t now_t);  // 计算下一个技能时间
	const AiSkill* FindRoleNextSkill(int64_t now_t);
	//int GetNextSkillDist();
	int GetSkillMinDist();
	//const AiSkill* GetNextSkill();
	void OnUseSkill(int index, int64_t time);
	const Point& GetBackPos();
	void SetBackPos(const Point &pos);
	void ClearHatred();					
	void DeleteHatred(EntityHandle hd);//删除玩家仇恨列表
	bool UpdateHatred();	//更新玩家仇恨列表
	Entity* GetFirstDamage(void);   //获取仇恨列表的第一个玩家
	const HatredList& GetHatred();	 // 返回排序的
	const HatredList& GetHatredList() { return damage_list_; } // 不排序
	Entity* SetTargetByDamageList(void);
	void PathToTarget(int gx, int gy);	// 导出接口
	void ChangeTarget(int type); // 切换目标
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
	const AIConfig*	ai_conf_; // 文件的指针
	//Timer		skill_timer_;		// 检测技能可用定时器
	Timer       time_check_;
	bool		is_add_damage_list; //是否添加了仇恨列表数据 针对玩家  怪物无效
	int			next_skill_index_;
	int64_t		skill_cd_[MAX_SKILL];	
	Point		back_pos;   // 回归点
	HatredList	damage_list_;	// 暂时只做了一个伤害表，没做仇恨，攻击者死亡时没做清除,这里会出现玩家Actor
};


#endif

