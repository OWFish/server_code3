#pragma once

#include "skill.h"
#include "skill_break.h"

struct DamageArg
{
	double damage;//�˺�
	const SkillConfig* skill_cfg;//��ɼ���Cd
	EntityHandle attacker_hdl;//�����ߵ�handle
	int64_t attack_time;//����ʱ��
	uint32_t hit_type;//��������
};

enum SkillUseResult {
	SkillUseResult_Err = -2,
	SkillUseResult_NotSkill = -1,
	SkillUseResult_Fail = 0,
	SkillUseResult_OK = 1,
};

class Creature;
class Entity;
struct RoleData;
class SkillSystem
{
public:
	SkillSystem(Creature*);
	~SkillSystem();

	const static int MAX_SKILL_INDEX = 8;
	/*************Role************/
	bool Init(RoleData *data);
	void Save(RoleData *data);
	int GetRoleSkillId(int job, int index, int level);
	bool OnUpgradeSkill(int index);
	bool OnCastSkill(int id, Entity *tar);
	bool CheckPublicCd();
	void LogicRun(int64_t curr_t);
	inline bool IsCasting() { return !CheckPublicCd(); }
	int64_t GetSkillLaveCD(int id);
	void SetSkillCdById(int id, int64_t cd_mtime_);
	void SetPassiveSkillCdById(int id, int64_t cd_mtime_, int cond);
	int UseSkill(int id, int index = -1);
	bool AutoUseAISkill(); //�Զ�ʹ�ö�̬���صļ���
	void AddDamageArg(DamageArg &darg);
	void AddSkillRevise(int skillId, ImbaSkillRevise &rev);
	void AddSkillReviseSelfBuff(int skillId, int buffId);
	void AddSkillReviseTarBuff(int skillId, int buffId);
	void DoDamageResult(Creature * attacker, double &damage, const SkillConfig* cfg, uint32_t hit_type);
	inline void clear_delay_damage(void) { delay_damage_.clear(); }
	bool AddSkill(int id);
	bool DelSkill(int id);
	bool AddAISkill(int id);
	bool DelAISkill(int id);
	bool DelAllAISkill();
	bool DelSkillById(int id);
	void DelAllSkill(void);
	bool AddPassiveSkill(int id);
	bool DelPassiveSkill(int id);
	bool DelPassiveSkillById(int id);
	void OnPassiveEvent(int cond, Creature *target = nullptr, double *val = nullptr, Skill *inSkill = nullptr);
	bool UpgradeSkill(int index, int level = 0);
	void UpdateSkillPower();
	const Attribute& GetBattleAttr(){ return skill_power_; }
	/*****************************/
	 std::vector<Skill*>& GetSkillList(void)  {return skill_list_;}
	 std::vector<Skill*>* GetPassiveSkillLists(void) { return passive_skill_list_; }
	 void GetSkillReviseCfg(int skill_id, ImbaSkillRevise &rev);
	 void GetImbaSkillReviseCfg(int skill_id, ImbaSkillRevise &rev);
	 void GetGWSkillReviseCfg(int skill_id, ImbaSkillRevise &rev);

	 inline bool GetLastTimeCrit() { return last_time_crit; }
	 inline void SetLastTimeCrit(bool b) { last_time_crit = b; }

	 inline int64_t GetMultipleCritCd() { return multiple_crit_cd_; }
	 inline void SetMultipleCritCd(int64_t cd) { multiple_crit_cd_ = cd; }
	 inline int64_t GetAttackAddHpCd() { return attack_add_hp_cd_; }
	 inline void SetAttackAddHpCd(int64_t cd) { attack_add_hp_cd_ = cd; }
	 void SyncAttackAddHpCd(int64_t cd);
	 inline int64_t GetStunCd() { return stun_cd_; }
	 inline void SetStunCd(int64_t cd) { stun_cd_ = cd; }
	 inline int64_t GetVampireCd() { return vampire_cd; }
	 inline void SetVampireCd(int64_t cd) { vampire_cd = cd; }
	 inline int64_t GetCurseCd() { return curse_cd; }
	 inline void SetCurseCd(int64_t cd) { curse_cd = cd; }
	 inline int64_t GetDeathCurseCd() { return death_curse_cd; }
	 inline void SetDeathCurseCd(int64_t cd) { death_curse_cd = cd; }
	 inline int64_t GetHpLtAddBuffCd() { return hp_lt_add_buff_cd; }
	 inline void SetHpLtAddBuffCd(int64_t cd) { hp_lt_add_buff_cd = cd; }
	 inline int64_t GetHunGuCd() { return hungu_cd; }
	 inline void SetHunGuCd(int64_t cd) { hungu_cd = cd; }
	 inline int64_t GetMiJiZhCd() { return mijizh_cd; }
	 inline void SetMiJiZhCd(int64_t cd) { mijizh_cd = cd; }
	 inline int64_t GetMiJiBqCd() { return mijibq_cd; }
	 inline void SetMiJiBqCd(int64_t cd) { mijibq_cd = cd; }

	 //���Ҽ����Ƿ��Ѽ���
	 bool FindSkillIsActive(int id);

private:
	Skill* FindSkill(int id);
	Skill* FindPassiveSkill(int id, int cond);

private:
	Creature*				self_;
	std::vector<Skill*> skill_list_;
	std::vector<Skill*> passive_skill_list_[PassiveSkillCond_Count];
	std::vector<int>	aiSkillList;
	std::map<int, ImbaSkillRevise> skill_rev_;  //��ʱ�����������������������������ݽṹ
	//Skill*			current_skill_;		// ��ǰʩ������
	int64_t				public_cd_;			// ����cd
	Attribute			skill_power_;		//����ϵͳս��
	std::list<DamageArg> delay_damage_; //�ӳ��˺��б�
	int64_t				max_delay_time_;//�ӳ����ʱ��,��������ȫ����
	uint64_t			multiple_crit_cd_;//����һ����CD
	uint64_t			attack_add_hp_cd_;//�����ؽ乥����Ѫ��CD
	uint64_t			stun_cd_;//���cd
	uint64_t			vampire_cd; //����װ����Ѫcd
	uint64_t			curse_cd;	//����װ������cd
	uint64_t			death_curse_cd;//���䴥��CD(��ȴʱ��)
	uint64_t			hp_lt_add_buff_cd;//��������(��ֱ���)ʱ,���������ָ�buff��CD
	uint64_t			hungu_cd;//��ǹ���������Ч��CD
	uint64_t			mijizh_cd;//�ؼ�׷��CD
	uint64_t			mijibq_cd;//�ؼ�������CD
	bool				last_time_crit;//��һ�ι����Ƿ񱩻�
};