#ifndef _ROLE_H_
#define _ROLE_H_

#include "entity/entity.h"
#include "entity/creature.h"
#include "db/role_data.h"

class EquipSystem;
class WingSystem;
class EnhanceSystem;
class StoneSystem;
class JingmaiSystem;
class ZhulingSystem;
class ExRingSystem;
class SoulshieldSystem;
class ChallengeFbSystem;
class BlessSystem;
class MiJiSystem;
class ZhuangBanSystem;
class SkillBreak;
class FuWenSystem;
class FulingSystem;
class SoulSystem;
class AttrsSystem;
class Role : public Creature
{
	typedef Creature Inherited;
public:
	Role();
	~Role();

	virtual void OnEnterScene();
	virtual void OnDestroy();

public:
	bool Init(Actor *actor, RoleData* data);
	// �������� reload ȫ�����¼��㣬����ֻ����
	/****************Entity*******************/
	virtual int GetId() { return data_->id; }
	virtual void LogicRun(int64_t curr_t);
	virtual void OnMove(const Point&);
	virtual Actor* GetActor() { return actor_; }
	virtual void CreateAppearData(DataPacket& appearPack);

	/****************Creature*****************/
	virtual void ChangeHp(double nValue, Creature* attacker = NULL);
	virtual void OnSetHp();
	virtual void OnSetMp();
	virtual void OnAddStatus(int status);
	//virtual void OnAttack(Creature* enemy, double damage);
	virtual void InitBasicAttribute();
	virtual void CalcAttributes(); // �����ϵͳ����
	virtual void CalcBattleAttributes(); // ֻ����ս��ϵͳ����
	virtual void CalcExAttributes(); // ������������
	void SendAttributes();
	void SendExAttributes();

	virtual float GetExtraCritDamage();
	virtual bool HasHuShenShield();
	virtual double GetAtkSum(void);//��ȡ�������ܺ�
	//virtual bool IsEnemy(Creature* target);
	/****************Creature*****************/
	void WriteData(DataPacket &pack, bool skirmishClone = false, int attrper = 0); // д���ɫ����
	Creature* GetSelfMinRole();
	virtual int getWeaponPeakLv(void);
	virtual int getDeathCount(void);
	virtual int GetYuPeiLv(void) { return actor_->GetYuPeiLv(); };
	virtual int64_t GetPrestigeExp(void) { return actor_->GetPrestigeExp(); };
	virtual int GetActorId(void) { if (actor_) return actor_->GetActorId(); return 0; };
	virtual uint64_t GetSummitHandle() { return actor_->GetSummitHandle(); }
	virtual int GetHeadID() { return GetActor()->GetBasicData()->headimage; }

	virtual char GetJob() { return data_->job; }
	int GetSex() { return data_->sex; }
	int GetZhuangshengLv() {
		return actor_->GetBasicData()->zhuansheng_lv;
	}
	int GetGuildID() {
		return actor_->GetBasicData()->guild_id_;
	}

	void pushBattleComparison(DataPacket& pack);

	Attribute* GetEquipPointAttrs(void){return &equip_point_attrs_;}
	Attribute* GetGuildSkillAttrs(void) { return &guild_skill_attrs_; }
	Attribute* GetHeirloomAttrs(void) { return &heirloom_attrs_; }
	ExAttribute* GetWeaponSoulExAttrs(void) { return &weaponsoul_exattrs_; }
	Attribute* GetWeaponSoulAttrs(void) { return &weaponsoul_attrs_; }
	ExAttribute* GetGodWingExAttrs(void) { return &godwing_exattrs_; }

	ExAttribute* GetWingExAttrs(void) { return &wing_exattrs_; }

	Attribute* GetGodWingAttrs(void) { return &godwing_attrs_; }
	Attribute* GetCampBattleAttrs(void) { return &camp_battle_attrs_; }
	Attribute* GetReincarnateEquipAttr(void) { return &reincarnate_equip_attrs_; }
	ExAttribute* GetReincarnateEquipExAttr(void) { return &reincarnate_equip_exattrs_; }
	Attribute* GetBasicAttrs(void) { return &basic_attrs_; }
	BattleAttribute* GetAttrsCache(void) { return &attrs_cache_; }
	Attribute* GetJadePlateAttrs(void) { return &jadeplate_attrs_; }
	ExAttribute* GetJadePlateExAttrs(void) { return &jadeplate_exattrs_; }
	Attribute* GetZhiZunAttrs(void) { return &zhizun_attrs_; }
	ExAttribute* GetZhiZunExAttrs(void) { return &zhizun_exattrs_; }
	Attribute* GetLeiTingEquipAttrs(void) { return &leitingequip_attrs_; }
	ExAttribute* GetLeiTingEquipExAttrs(void) {return &leitingequip_exattrs_;}
	// ���ǵ�������lua����������
	RoleData* GetData() { return data_; }
	void OnFirst();
	void OnLevelUp();
	void OnSave();
	int GetSkillLevel(int index);
	void SetSkillLevel(int index, int level);
	void SetCamp(int camp);

	EquipSystem* GetEquipSystem() { return equip_sys_; }
	WingSystem* GetWingSystem() { return wing_sys_; }
	EnhanceSystem* GetEnhanceSystem() { return enhance_sys_; }
	StoneSystem* GetStoneSystem(){ return stone_sys_; }
	JingmaiSystem* GetJingmaiSystem(){ return jingmai_sys_; }
	ZhulingSystem* GetZhulingSystem(){ return zhuling_sys_; }
	FulingSystem* GetFulingSystem() { return fuling_sys_; }
	SoulSystem* GetSoulSystem(){ return soul_sys_; }
	ExRingSystem* GetExRingSystem() { return ex_ring_sys_; }
	SoulshieldSystem* GetSoulshieldSystem(){ return soul_shield_sys_; }
	BlessSystem* GetBlessSystem(){ return bless_sys_; }
	MiJiSystem* GetMiJiSystem() { return miji_sys_; }
	ZhuangBanSystem* GetZhuangBanSystem() { return zhuangban_sys_; }	virtual bool CanMove();	// gm
	//SkillBreak* GetSkillBreakSystem() { return skillbreak_sys_; }
	FuWenSystem* GetFuWenSystem() { return fuwen_sys_; }
	AttrsSystem* GetAttrsSystem() { return attrs_sys_; }

	void GMSetAttr(int type, double value);
	bool GetSendEntity(void) { return send_entity_; }
	void SetSendEntity(bool b) { send_entity_ = b; }
	inline double GetRankPower(void) { return rank_power_; }

	int GetAILastUseSkill() { return last_use_skill; }
	void SetAILastUseSkill(int skill_index) { last_use_skill = skill_index; }

protected:
	virtual void OnChangeHp(double nValue, Creature* attacker, double &ret);
	virtual void OnKilled(Creature* killer);

private:
	Actor  *actor_;
	RoleData* data_;
	Attribute		level_attrs_;	// �ȼ�����
	Attribute		basic_attrs_;  // �������Ի��� ��ս��״̬ ��������
	Attribute		equip_point_attrs_; //װ��������
	Attribute		guild_skill_attrs_; //���ɼ�������
	BattleAttribute attrs_cache_; //�������ڷ��͸�ǰ�˵ķ�ս��״̬ ������
	Attribute       zhuangban_attrs_; // װ������
	Attribute		heirloom_attrs_;//����װ������
	Attribute		weaponsoul_attrs_;//��������
	ExAttribute		weaponsoul_exattrs_;//������չ����
	Attribute		godwing_attrs_;//��������
	ExAttribute		godwing_exattrs_;//������չ����

	ExAttribute		wing_exattrs_;//�����չ����

	Attribute		camp_battle_attrs_;//��Ӫս����
	Attribute		reincarnate_equip_attrs_;//�ֻ�װ����װ����
	ExAttribute		reincarnate_equip_exattrs_;//�ֻ�װ����װ��չ����
	Attribute		jadeplate_attrs_;//����������
	ExAttribute		jadeplate_exattrs_;//��������չ����
	Attribute		zhizun_attrs_;//����װ������
	ExAttribute		zhizun_exattrs_;//����װ����չ����
	Attribute		leitingequip_attrs_;//����װ������
	ExAttribute		leitingequip_exattrs_;//����װ����������

	EquipSystem*	equip_sys_;
	WingSystem*		wing_sys_;
	EnhanceSystem*	enhance_sys_;
	StoneSystem*	stone_sys_;
	JingmaiSystem*	jingmai_sys_;
	ZhulingSystem*	zhuling_sys_;
	FulingSystem*   fuling_sys_;
	SoulSystem*		soul_sys_;
	ExRingSystem*   ex_ring_sys_;
	SoulshieldSystem* soul_shield_sys_;
	BlessSystem*	bless_sys_;	// װ������ϵͳ
	MiJiSystem*		miji_sys_;	
	ZhuangBanSystem* zhuangban_sys_;
	//SkillBreak* skillbreak_sys_;
	FuWenSystem* fuwen_sys_;
	AttrsSystem* attrs_sys_;

	bool send_entity_ = false; //�Ƿ��·�ʵ��
	bool attr_change_; //�����Ƿ��б仯
	bool ex_attr_change_;//��չ�����Ƿ��б仯
	double rank_power_; //���а�ս��
	int last_use_skill; //ai��һ��ʹ�õļ����±�
};

#endif
