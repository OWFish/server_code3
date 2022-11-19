#pragma once

#include "skill_config.h"
#include "db/skill_data.h"
#include "skill_def.h"

#define MABI_SKILL_EFFECT_ID 51001  //���
#define DEATH_CURSE_EFFECT_ID 52001  //����
#define ALLCRIT_SKILL_EFFECT_ID 53001 //���鼼��
#define GOD_BLESS_EFFECT_ID 58001 //����
#define CURSE_SKILL_EFFECT_ID 80003 //����װ������,���ϵȼ�,����ռ�� 80004��80007

//ð��Ч��ID
#define MABI_BUBBLE_TEXT_ID 1 //��Խ�ָ
#define HUTI_BUBBLE_TEXT_ID 2 //�����ؽ�
#define SHENLI_BUBBLE_TEXT_ID 3 //�����ؽ�
#define SHANBI_BUBBLE_TEXT_ID 4 //�����ؽ�
#define ZHILIAO_BUBBLE_TEXT_ID 5 //�����ؽ�
#define KUANGBAO_BUBBLE_TEXT_ID 6 //���ؽ�
#define FUHUO_BUBBLE_TEXT_ID 7 //�����ؽ�
#define CURSE_BUBBLE_TEXT_ID 13 //����װ������
#define VAMIRE_BUBBLE_TEXT_ID 14 //����װ����Ѫ
#define ATT_ADD_DAM_TEXT_ID 15 //���깥�������˺�
#define BE_ATT_ADD_HP_TEXT_ID 16 //���걻������Ѫ
#define ATT_MB_ADD_DAM_TEXT_ID 17 //���깥������˺�����
#define HP_LT_ADD_BUFF_TEXT_ID 18 //���������ͼӻ�Ѫbuff
#define ATT_HP_LT_ADD_DAM_TEXT_ID 19 //���깥�������ͼ��˺�
#define ATT_PER_DAM_TEXT_ID 20 //���깥�������Ѫ+�����˺�
#define MULTIPLE_CRIT_BUBBLE_TEXT_ID 21 //���ر���
#define RESIST_BUBBLE_TEXT_ID 22 //�ؽ�ĸ���
#define MJBQ_HP_LT_ADD_BUFF_TEXT_ID 23 //�ؼ����������ͼ�buff
#define HUNGU_FLOAT_TEXT_ID 24  //���6������Ч
#define XINFA3_FLOAT_TEXT_ID 25  //�ķ�3��Ч

//�ض���Ѫ����
#define VamirePro_SKILL_ID 12 //�Ͽ�ն
#define Pet_Passive_Skill_ID      36000 //���ﱻ������

class Skill
{
public:
	enum HitType
	{
		HitType_None = 0,	// ����ʾ
		HitType_Hit = 1,	// ����
		HitType_Crit = 2,	// ����
		HitType_Dodge = 4,	// ����
		HitType_Lucky = 8,	// ����һ��
		HitType_Together = 16,//�ϻ�
		HitType_ExDam = 32,//�����˺�
		HitType_Deter = 64,//���������
		HitType_Multiple = 128,//����˺�
		HitType_ZhuiMing = 256,//׷���˺�
		HitType_Deadly = 512,//����һ��
		HitType_Rdamage = 1024,//����
		HitType_Penet = 2048,//�и�
		HitType_Poisoning = 4096,//�ж�
		HitType_Bleed = 8192 ,//��Ѫ
	};

public:
	friend SkillSystem;
	~Skill();

	bool Init(int id);
	int GetId() { return conf_->base.id; }
	const SkillConfig* GetConfig() { return conf_; }
	bool CheckCast(Creature* self, Creature* target, ImbaSkillRevise& rev);
	bool Cast(Creature* self, Creature* target);
	Creature* SelectTarget(Creature* caster);	// ѡ��ʩ��Ŀ��
	bool IsNoPublicCD() { return conf_->no_public_cd; };
	const SkillBase* GetRealConfig(Creature* caster);
private:
	Skill();
	typedef  double (Skill::*CalcSkillResultFunc)(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag);
	typedef  void (Skill::*CalcResultFunc)(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);

	double CalcSkillResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_NoDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_Damage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_Heal(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_TogetherHit(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_FixedDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_MultipleDamage(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);
	double CalcSkillResult_MultipleSkills(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev, bool critflag = false);

	void DoResult(SKILLRESULTPARAM & param, uint32_t& hitType, ImbaSkillRevise &rev);
	void Not(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddDamage(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void FormulaOne(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddDamageProportion(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void DisregardDef(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddStunPower(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void SetAddBearHurt(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void SetCurBuffInfo(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);
	void AddStunBuff(SKILLRESULTPARAM & param, uint32_t& hitType, const ImbaSkillRevise::arg* info);

	void GetAffectedTargets(Creature* self, Creature* target, std::vector<Creature*> &results, ImbaSkillRevise &rev);
	void DoRepel(Creature* self, Creature* target);
	void SyncAllRoleCDTick(Creature* self, int64_t tick);
	void SyncAllRoleAddEffect(Creature* self, int eff, SKILLRESULTPARAM::buff* buff);

	double getWeaponPeakPre(Creature * self, Creature * target);
	int getPerstigeDam(Creature * self);

private:
	const SkillConfig* conf_;
	int64_t cd_mtime_;
	static const CalcSkillResultFunc Handlers[];
	static const CalcResultFunc RevHandlers[];
};