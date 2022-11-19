#include "StdAfx.h"
#include "role.h"
#include "db/role_data.h"
#include "role_config.h"
#include "protocol/protos/base_proto.h"
#include "item/equip/equip_system.h"
#include "item/container/equip_bag.h"
#include "skill/skill_system.h"
#include "skill/effect/skill_effect_system.h"
#include "role_system.h"
#include "wing/wing_system.h"
#include "enhance/enhance_system.h"
#include "fuling/fuling_system.h"
#include "ai/ai_mgr.h"
#include "stone/stone_system.h"
#include "jingmai/jingmai_system.h"
#include "zhuling/zhuling_system.h"
#include "zhuansheng/zhuansheng_system.h"
#include "soulsystem/soul_system.h"
#include "ex-ring/ex_ring_system.h"
#include "soulshield/soulshield_system.h"
#include "bless/bless_system.h"
#include "title/title_system.h"
#include "miji/mijisystem.h"
#include "guild/guild_system.h"
#include "zhuangban/zhuangban.h"
#include "skill/skill_break.h"
#include "neigongsystem/neigong_system.h"
#include "actorexring/actor_ex_ring_system.h"
#include "togetherhit/together_hit_system.h"
#include "fuwen/fuwensystem.h"
#include "imba/imbasystem.h"
#include "godweapon/godweaponsystem.h"
#include "attr/attrs_system.h"
#include "move/move_system.h"
#include <iostream>

Role::Role()
{
	SetType(EntityType_Role);
	data_ = NULL;
	equip_sys_ = new EquipSystem(this);
	wing_sys_ = new WingSystem(this);
	enhance_sys_ = new EnhanceSystem(this);
	stone_sys_ = new StoneSystem(this);
	jingmai_sys_ = new JingmaiSystem(this);
	zhuling_sys_ = new ZhulingSystem(this);
	fuling_sys_ = new FulingSystem(this);
	soul_sys_ = new SoulSystem(this);
	ex_ring_sys_ = new ExRingSystem(this);
	soul_shield_sys_ = new SoulshieldSystem(this);
	bless_sys_ = new BlessSystem(this);
	miji_sys_ = new MiJiSystem(this);
	zhuangban_sys_ = new ZhuangBanSystem(this);
	//skillbreak_sys_ = new SkillBreak(this);
	fuwen_sys_ = new FuWenSystem(this);
	attrs_sys_ = new AttrsSystem(this);
	attr_change_ = false;
	ex_attr_change_ = false;
	last_use_skill = 0;
}

Role::~Role()
{

}

// ����ò��Ҫд������ɴ����е��˳���������ͨ������ǰ����ڴ�й¶ʵ�ֵ�
void Role::OnDestroy()
{
	static AiMgr* aimgr = GetGameEngine()->GetAiMgr();
	if (ai_)
		aimgr->DestroyAi(ai_);
	SafeDelete(equip_sys_);
	SafeDelete(wing_sys_);
	SafeDelete(enhance_sys_);
	SafeDelete(stone_sys_);
	SafeDelete(jingmai_sys_);
	SafeDelete(zhuling_sys_);
	SafeDelete(fuling_sys_);
	SafeDelete(soul_sys_);
	SafeDelete(ex_ring_sys_);
	SafeDelete(soul_shield_sys_);
	SafeDelete(bless_sys_);
	SafeDelete(miji_sys_);
	SafeDelete(zhuangban_sys_);
	//SafeDelete(skillbreak_sys_);
	SafeDelete(fuwen_sys_);
	SafeDelete(attrs_sys_);

	Inherited::OnDestroy();
}

bool Role::Init(Actor *actor, RoleData* data)
{
	if (!actor || !data)
		return false;

	actor_ = actor;
	data_ = data;
	SetMasterHandle(actor_->GetHandle());

	if (data_->power == 0)
		OnFirst();

	InitBasicAttribute();
	//��ʼ��
	if (!equip_sys_->Init(data_))
		return false;
	if (!skill_sys_->Init(data_))
		return false;
	if (!wing_sys_->Init(data_))
		return false;
	if (!enhance_sys_->Init(data_))
		return false;
	if (!stone_sys_->Init(data_))
		return false;
	if (!jingmai_sys_->Init(data_))
		return false;
	if (!zhuling_sys_->Init(data_))
		return false;
	if (!fuling_sys_->Init(data_))
		return false;
	if (!soul_sys_->Init(data_))
		return false;
	if (!ex_ring_sys_->Init(data_))
		return false;
	if (!soul_shield_sys_->Init(data_))
		return false;
	if (!bless_sys_->Init(data_))
		return false;
	//if (!skillbreak_sys_->Init(data_))
	//	return false;
	if (!fuwen_sys_->Init(data_))
		return false;
	if (!neigong_sys_->Init(data_))
		return false;
	CalcAttributes();

	ai_ = GetGameEngine()->GetAiMgr()->CreateAi(data_->job, this);
	if (!ai_) OutputMsg(rmError, "create role ai failed.");

	is_init_ = true;

	return true;
}

void Role::InitBasicAttribute()
{
	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init role.");
		return;
	}
	int lv = actor_->GetLevel();
	int job = data_->job;

	level_attrs_.Reset();
	auto conf = RoleConfigPool::Get(lv, job);
	if (conf == nullptr)
	{
		OutputMsg(rmError, "Role::InitBasicAttribute error.");
		return;
	}

	level_attrs_[Attribute::atHp] = conf->hp;
	level_attrs_[Attribute::atHpMax] = conf->hp;
	level_attrs_[Attribute::atMp] = conf->mp;
	level_attrs_[Attribute::atMpMax] = conf->mp;
	level_attrs_[Attribute::atAtk] = conf->atk;
	level_attrs_[Attribute::atDef] = conf->def;
	level_attrs_[Attribute::atRes] = conf->res;
	level_attrs_[Attribute::atCrit] = conf->crit;
	level_attrs_[Attribute::atTough] = conf->tough;
	level_attrs_[Attribute::atMoveSpeed] = conf->ms;
	level_attrs_[Attribute::atAttackSpeed] = conf->as;
	level_attrs_[Attribute::atCritEnhance] = conf->acrit;

	auto Attrconf = RoleConfigPool::GetAttrDict(lv, job);
	if (Attrconf != nullptr)
	{
		for (auto ite : *Attrconf)
		{
			level_attrs_[ite.first] = ite.second;
		}
	}
}
void Role::pushBattleComparison(DataPacket& pack)
{
	//���ܵȼ���Ϣ
	for (int index = 0; index < MAX_SKILL_COUNT; ++index)
	{
		int cur_level = data_->skills.skill_level[index];
		pack << cur_level;
	}
	//װ����Ϣ
	for (int index = 0; index < EquipSlotType_Max; ++index)
	{
		/*
			װ�����ݽṹ
			װ��ǿ���ȼ�
			װ�������ȼ�
			װ���ı�id
			װ��������
		*/
		pack << data_->equips_data.slot_data[index].strength_lv; 
		pack << data_->equips_data.slot_data[index].gem_lv;
		data_->equips_data.slot_data[index].equip_data.writeData(pack);
	}

	//װ����Ϣ
	for (int index = 0; index < EquipSlotType_Dzi; ++index)
	{
		/*
		װ�����ݽṹ
		װ��ǿ���ȼ�
		װ�������ȼ�
		װ���ı�id
		װ��������
		*/
		pack << data_->equips_data.god_slot_data[index].strength_lv;
		pack << data_->equips_data.god_slot_data[index].gem_lv;
		data_->equips_data.god_slot_data[index].equip_data.writeData(pack);
	}

	//�ؽ����ݻ�ȡ
	for (int i = 0;i < 4 ;++i)
	{
		pack << data_->ex_rings.ring_level[i];
	}

	//�������
	{
		pack << data_->wings.level;	
		pack << data_->wings.exp;
		pack << data_->wings.openStatus;
		for (int i = 0; i < MAX_WING_PILL;++i)
		{
			pack << data_->wings.pill[i];
		}


		ScriptValueList params;
		params << actor_;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("getWingData", &params, &retList);
		for (int i =0;i < 4;++i)
		{
			int value = retList[i];
			pack << i+1;
			pack << value;
		}
	}
	//����
	{
		pack << data_->jingmai_data.level;
		pack << data_->jingmai_data.stage;
	}

	//����
	{
		pack << data_->loogsoul_data.stage;
		pack << data_->loogsoul_data.level;
		pack << data_->loogsoul_data.exp;
		pack << data_->loogsoul_data.act;
	}

	//ս��
	for (int i = 0;i < MAX_FUWEN;++i)
	{
		data_->fuwen_data.fuwen_slot[i].writeData(pack);
	}



	//�ƺŵ�����
	int titleId = 0;
	int titleEndTimeValue = 0;
	int titleLevelValue = 0;
	int titleCount = 0;
	int maxCount = 1;
	//�ƺŵ�����
	{

		ScriptValueList params;
		params << actor_;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("GetTitleCount", &params, &retList);
		if (retList.count() == 2)
		{
			titleCount = retList[0];
			maxCount = retList[1];
		}
		pack << titleCount;
	}
	//�ƺŵĵ���ʱ��͵ȼ�
	for (int i = 0; i < maxCount;++i)
	{
		ScriptValueList params;
		params << actor_;
		params << i;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("GetTitleInfo", &params, &retList);
		if (retList.count() == 3)
		{

			titleId = retList[0];
			titleEndTimeValue = retList[1];
			titleLevelValue = retList[2];

			pack << titleId;
			//params << titleEndTimeValue;
			pack << titleLevelValue;
		}
	}
	//��ȡװ������
	int zhuangbanCount = 0;
	ScriptValueList params;
	params << actor_;
	ScriptValueList retList;
	bool ret = actor_->CallFunc("getZhuangBanCount", &params, &retList);
	if (retList.count() > 0)
	{
		zhuangbanCount = retList[0];

	}
	pack << zhuangbanCount;

	int zhuangbanId = 0;
	int zhuangbanValue = 0;
	int zhuangbanLevel = 0;
	//װ����ӵ�е�
	for (int i = 0; i < zhuangbanCount; ++i)
	{
		ScriptValueList params;
		params << actor_;
		params << i;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("getZhuangBanGet", &params, &retList);
		if (retList.count() > 0)
		{

			zhuangbanId = retList[0];
			zhuangbanValue = retList[1];
			zhuangbanLevel = retList[2];

			pack << zhuangbanId;
			//params << zhuangbanValue;
			pack << zhuangbanLevel;
		}
	}

	//��ȡ��λ��Ϣ
	{
		int TrainLevel = 0;
		ScriptValueList params;
		params << actor_;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("getTrainInfo", &params, &retList);
		if (retList.count() > 0)
		{
			TrainLevel = retList[0];
		}
		pack << TrainLevel;
	}

	//��ȡ�ؽ���Ϣ
	{
		int ExRingId = 0;
		int ExRingLevel = 0;

		for (int i = 0;i< 6;++i)
		{
			ScriptValueList params;
			params << actor_;
			params << i;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getExRingInfo", &params, &retList);
			if (retList.count() == 2)
			{
				ExRingId = retList[0];
				ExRingLevel = retList[1];
			}
			pack << ExRingId;
			pack << ExRingLevel;
		}

	}

	//������Ϣ
	for (int i = 0; i < TogetherHitSlotType_Max; ++i)
	{
		//pack << actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].strength_lv;
		//pack << actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].gem_lv;
		actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].equip_data.writeData(pack);;
	}

	//������Ϣ
	{
		int neigongLevel = 0;
		int neigongOpen = 0;
		int neigongStage = 0;
		ScriptValueList params;
		params << actor_;
		ScriptValueList retList;
		bool ret = actor_->CallFunc("getNeiGongInfo", &params, &retList);
		if (retList.count() == 3)
		{
			neigongLevel = retList[0];
			neigongStage = retList[1];
			neigongOpen = retList[2];
		}
		pack << neigongLevel;
		pack << neigongStage;
		pack << neigongOpen;
	}

	//������Ϣ
	{
		int weaponType[3] = {1,2,3};
		int weaponCount[3];
		int uitemNum = 0;
		int neigongLevel = 0;
		int neigongOpen = 0;
		int neigongStage = 0;
		for (int i = 0;i < 3;++i)
		{
			ScriptValueList params;
			params << actor_;
			params << i+1;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getWeaponSoulCount", &params, &retList);
			weaponCount[i] = (int)retList[0];
			uitemNum = (int)retList[1];
		}
		for (int i = 0; i < 3; ++i)
		{
			int tempCount = weaponCount[i];
			pack << tempCount;
			for (int j = 0; j < weaponCount[i]; ++j)
			{
				ScriptValueList params;
				params << actor_;
				params << j;
				params << i + 1;
				ScriptValueList retList;
				bool ret = actor_->CallFunc("getWeaponSoulInfo", &params, &retList);
				//weaponType[i] = retList[0];
				if (weaponType[i] == 1)
				{
					int id = 0;
					int pos = 0;
					id = (int)retList[0];
					pos = retList[1];
					pack << id;
					pack << pos;
				}
				else if (weaponType[i] ==2)
				{
					int id = 0;
					id = (int)retList[0];
					pack << id;
				}else if (weaponType[i] == 3)
				{
					int id = 0;
					id = (int)retList[0];
					pack << id;
				}
			}
			
		}
		pack << uitemNum;

	}

	//����ս��
	{
		int ArtifactsCount = 0;
		int ArtifactsExp = 0;
		int ArtifactsPower = 0;
		{
			ScriptValueList params;
			params << actor_;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getArtifactsCount", &params, &retList);
			ArtifactsCount = (int)retList[0];
		}
		pack << ArtifactsCount;
		{
			int id = 0;
			int level = 0;
			char isActive = 0;
			for (int i = 0; i < ArtifactsCount; ++i)
			{
				ScriptValueList params;
				params << actor_;
				params << i ;
				ScriptValueList retList;
				bool ret = actor_->CallFunc("getArtifactsInfo", &params, &retList);
				id = (int)retList[0];
				level = (int)retList[1];
				isActive = (char)((int)(retList[2]));
				pack << id;
				pack << level;
				pack << isActive;
			}
		}
	}

	//ѫ����Ϣ
	{
		int level = 0;
		char isAct = 0;
		{
			ScriptValueList params;
			params << actor_;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getKnighthoodLv", &params, &retList);
			level = (int)retList[0];
			isAct = (int)retList[1];
		}
		pack << level;
		pack << isAct;
	}

	//ͼ����Ϣ
	{

		double tujianPower = 0;
		{
			tujianPower = (double)actor_->getTujianPower();
		}
		pack << tujianPower;
	}
	//���ս��
	{

		int godWeaponCount = 0;
		int skillCount = 0;
		int itemCount = 0;
		int id = 0;
		int level = 0;
		{
			ScriptValueList params;
			params << actor_;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getGodWeaponCount", &params, &retList);
			godWeaponCount= (int)retList[0];
			skillCount = (int)retList[1];
			itemCount = (int)retList[2];
			id = (int)retList[3];
			level = (int)retList[3];
		}

		pack << id;
		pack << level;
		pack << skillCount;
		pack << itemCount;
		for (int i = 0; i < godWeaponCount; ++i)
		{
			for (int j = 0; j < skillCount; ++j)
			{
				ScriptValueList params;
				params << actor_;
				params << i;
				params << j;
				params << 1;
				ScriptValueList retList;
				bool ret = actor_->CallFunc("getGodWeaponInfo", &params, &retList);
				//weaponType[i] = retList[0];
				int id = 0;
				int pos = 0;
				id = (int)retList[0];
				pos = retList[1];
				pack << id;
				pack << pos;
			}
			for (int j = 0; j < itemCount; ++j)
			{
				ScriptValueList params;
				params << actor_;
				params << i + 1;
				params << j;
				params << 2;
				ScriptValueList retList;
				bool ret = actor_->CallFunc("getGodWeaponInfo", &params, &retList);
				//weaponType[i] = retList[0];
				int id = 0;
				int pos = 0;
				id = (int)retList[0];
				pos = retList[1];
				//pack << id;
				pack << pos;
			}
		}
	}
	//������Ϣ
	{
		int JianPuCount = 0;
		{
			ScriptValueList params;
			params << actor_;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getJianPuCount", &params, &retList);
			JianPuCount = (int)retList[0];
		}
		pack << JianPuCount;
		for (int i = 0; i < JianPuCount; ++i)
		{
			ScriptValueList params;
			params << actor_;
			params << i;
			ScriptValueList retList;
			bool ret = actor_->CallFunc("getJianPuInfo", &params, &retList);
			//weaponType[i] = retList[0];
			int id = 0;
			int count = 0;
			int equipId1 = 0; 
			int equipId2 = 0;
			int equipId3 = 0;
			int equipId4 = 0;
			int equipId5 = 0;

			id = (int)retList[0];
			count = retList[1];
			equipId1 = retList[2];
			equipId2 = retList[3];
			equipId3 = retList[4];
			equipId4 = retList[5];
			equipId5 = retList[6];

			pack << id;
			pack << count;
			pack << equipId1;
			pack << equipId2;
			pack << equipId3;
			pack << equipId4;
			pack << equipId5;
		}
	}
}
void Role::CalcAttributes()
{
	static Attribute s_attrs;
	double hp_rate = 1.0;
	double old_hp = GetHp();
	double old_np = GetNp();
	double mp_rate = 1.0;
	double ng_rate = 1.0;
	if (GetMaxHp() > 0){
		hp_rate = 1.0 * GetHp() / GetMaxHp();
		if (GetMaxMp() > 0)
			mp_rate = 1.0 * GetMp() / GetMaxMp();
	}
	if (GetMaxNp() > 0)
	{
		ng_rate = 1.0 * GetNp() / GetMaxNp();
	}

	s_attrs.Reset();
	/**********��ϵͳ����**********/
	s_attrs += level_attrs_;
	s_attrs += equip_sys_->GetBattleAttr();
	s_attrs += wing_sys_->GetBattleAttr();
	s_attrs += enhance_sys_->GetBattleAttr();
	s_attrs += stone_sys_->GetBattleAttr();
	s_attrs += jingmai_sys_->GetBattleAttr();
	s_attrs += actor_->GetZhuanShengSystem()->GetBattleAttr();
	s_attrs += zhuling_sys_->GetBattleAttr();
	s_attrs += *fuling_sys_->GetAttr();
	s_attrs += *soul_sys_->GetAttr();
	s_attrs += ex_ring_sys_->GetBattleAttr();
	s_attrs += soul_shield_sys_->GetBattleAttr();
	s_attrs += miji_sys_->GetBattleAttr();
	s_attrs += *zhuangban_sys_->GetAttr();

	s_attrs += skill_sys_->GetBattleAttr();
	s_attrs += bless_sys_->GetBattleAttr();
	s_attrs += *actor_->GetKnighthoodAttr();
	s_attrs += *actor_->GetArtifactsAttr();
	s_attrs += *actor_->GetTrainsystemAttr();
	s_attrs += *actor_->GetChallengefbsystem();
	s_attrs += *actor_->GetRongLuAttr();
	s_attrs += equip_point_attrs_;
	s_attrs += actor_->GetTitleSystem()->GetBattleAttr();
	s_attrs += guild_skill_attrs_;
	//s_attrs += skillbreak_sys_->GetSkillBreakAttr();
	s_attrs += *actor_->GetActorExRingAttr();
	s_attrs += *actor_->GetMonthCardAttr();
	s_attrs += *actor_->GetPrivilegeAttr();
	s_attrs += *actor_->GetReincarnateAttr();
	s_attrs += *actor_->GetVipAttr();
	s_attrs += *actor_->GetGodWeaponSystem()->GetAttr();
	s_attrs += actor_->GetTogetherHitSystem()->GetAttr();
	s_attrs += actor_->GetTogetherHitSystem()->GetPunchAttr();
	s_attrs += *fuwen_sys_->GetAttr();
	s_attrs += *neigong_sys_->GetNeigongAttr();
	s_attrs += *actor_->GetImbaSystem()->GetAttr();
	s_attrs += heirloom_attrs_;
	s_attrs += reincarnate_equip_attrs_;
	s_attrs += jadeplate_attrs_;
	s_attrs += zhizun_attrs_;
	s_attrs += weaponsoul_attrs_;
	s_attrs += godwing_attrs_;
	s_attrs += *actor_->getPerstigeAttr();
	s_attrs += *actor_->getYuPeiAttr();
	s_attrs += leitingequip_attrs_;
	attrs_sys_->JoinAllBaseAttr(s_attrs);
	for (int32_t attrIdx = attrStart; attrIdx < attrMax; ++attrIdx)
	{
		s_attrs += *(actor_->GetActorsystemAttr(attrIdx));
	}

	//����ս��
	s_attrs.SetExtraPower(s_attrs.GetExtraPower() + actor_->GetGodWeaponSystem()->getPower(GetJob()));

	//attrs += .. ����ϵͳ����

	/***********�������а��ս����***********/
	//��ս��(û�г���)
	attrs_cache_.CalcBattleAttribute(s_attrs, GetJob()); // չʾ��������
	attrs_cache_.CalcPower();
	rank_power_ = attrs_cache_.GetPower();//���а�ר��ս����

	s_attrs += wing_sys_->GetTempAttr();
	//attrs += .. ����ϵͳ����

	/******************************/
	basic_attrs_ = s_attrs;
	attrs_cache_.CalcBattleAttribute(s_attrs,GetJob()); // չʾ��������
	attrs_cache_.CalcPower();

	s_attrs += *actor_->GetNewWorldBossAttr();//����boss��������ս��������
	s_attrs += skill_effect_sys_->GetAttr();	// ����buff��debuff�����������
	attrs_.CalcBattleAttribute(s_attrs, GetJob());		// ʵ������
	attrs_.SetPower(attrs_cache_.GetPower());	// һ��ͨ���������Ի�ȡ��ʵ��Ӧ���Ƿ�ս��״̬��ս��

	attrs_.SetHp(floor(GetMaxHp() * hp_rate));
	attrs_.SetMp(floor(GetMaxMp() * mp_rate));
	attrs_.SetNp(floor(GetMaxNp() * ng_rate));
	if (actor_ && is_init_ && actor_->logined_)
		attr_change_ = true;
	actor_->GetRoleSystem()->UpdateTotalPower();

	// ���ڷ����ͻ��˺��棬�Է��ͻ����������ʾѪ��
	attrs_cache_.SetHp(attrs_cache_.Get(Attribute::atHpMax)); //��ս������Ѫ��Ϊ��
	attrs_cache_.SetMp(attrs_cache_.Get(Attribute::atMpMax));
	double new_hp = GetHp();
	if (is_init_ && new_hp != old_hp) {
		// ����Ѫ��
		Creature::OnChangeHp(new_hp - old_hp, NULL, new_hp);
		NotifyAttr(Attribute::atHpMax, GetMaxHp());  //ÿ�ζ��������Ѫ��
		//Protocol::UpdateHpProto msg;
		//msg.handle = GetHandle();
		//msg.hp = GetHp();
		//msg.need_display = false;
		//actor_->SendData(msg);
		// todo �������Ѫ��
	}
	if (is_init_ && GetNp() != old_np)
	{
		// �����ڹ�ֵ
		Protocol::UpdateNpProto msg;
		msg.handle = GetHandle();
		msg.np = GetNp();
		//msg.need_display = false;
		actor_->SendData(msg);
	}
	data_->power = attrs_.GetPower();
}

void Role::CalcExAttributes()
{
	ex_attrs_.Reset();

	ex_attrs_ += equip_sys_->GetExAttr();
	ex_attrs_ += *miji_sys_->GetExAttr();
	ex_attrs_ += *(actor_->GetActorExRingSystem()->GetExAttr());
	ex_attrs_ += actor_->GetTogetherHitSystem()->GetExAttr();
	ex_attrs_ += actor_->GetTogetherHitSystem()->GetPunchExAttr();
	ex_attrs_ += actor_->GetTogetherHitSystem()->GetSkillExAttr();
	ex_attrs_ += fuwen_sys_->GetExAttr();
	ex_attrs_ += GetSkillEffectSystem()->GetExAttr();
	ex_attrs_ += *(actor_->GetTrainsystemExAttr());
	ex_attrs_ += *(ex_ring_sys_->GetExAttr());
	ex_attrs_ += *(actor_->GetKnighthoodExAttr());
	ex_attrs_ += actor_->GetImbaSystem()->GetExAttr();
	ex_attrs_ += weaponsoul_exattrs_;
	ex_attrs_ += godwing_exattrs_;
	ex_attrs_ += wing_exattrs_;
	ex_attrs_ += *fuling_sys_->GetExAttr();
	ex_attrs_ += reincarnate_equip_exattrs_;
	ex_attrs_ += jadeplate_exattrs_;
	ex_attrs_ += zhizun_exattrs_;
	ex_attrs_ += leitingequip_exattrs_;
	ex_attrs_ += *(actor_->GetGodWeaponExAttr());
	ex_attrs_ += *(actor_->getYuPeiExAttr());
	ex_attrs_ += *(actor_->GetReincarnateExAttr());

	if (actor_ && is_init_ && actor_->logined_)
		ex_attr_change_ = true;
}

void Role::CalcBattleAttributes()
{
	double old_hp = GetHp();
	double old_mp = GetMp();
	double old_np = GetNp();
	double old_maxHp = GetMaxHp();

	static Attribute s_attrs;
	s_attrs = basic_attrs_;

	// ����Ϊ��ǰѪ��
	s_attrs.Set(Attribute::atHp, old_hp);
	s_attrs.Set(Attribute::atMp, old_mp);
	s_attrs.Set(Attribute::atNeiGong, old_np);

	s_attrs += skill_effect_sys_->GetAttr();
	s_attrs += camp_battle_attrs_;				//��Ӫս����ս��������
	attrs_.CalcBattleAttribute(s_attrs, GetJob());		// ʵ������

	// ��skillEffectϵͳ���ӷ�����, �����漰����ǰѪ�����޸ĵģ�һ��Ҫ��skillEffect��ʱ�޸�
	double hp = GetHp();
	double maxHp = GetMaxHp();
	if (hp > maxHp)
		hp = maxHp;
	if (hp != old_hp) {
		SetHp(hp);
	}
	if (old_maxHp != maxHp)	{
		NotifyAttr(Attribute::atHpMax, maxHp);  //ÿ�ζ��������Ѫ��
	}
}

void Role::SendAttributes()
{
	if (!actor_->logined_) return;
	if (!is_init_) return;
	if (!attr_change_) return;
	attr_change_ = false;
	static Protocol::RoleAttributeProto proto;
	proto.role_id = data_->id;
	proto.count_ver = (short)Attribute::atCount;
	attrs_.GetAttrData(proto.attrs);	// ���ͻ������Լ�
	proto.power = attrs_.GetPower();
	
	actor_->SendData(proto);
}

void Role::SendExAttributes()
{
	if (!actor_->logined_) return;
	if (!is_init_) return;
	if (!ex_attr_change_) return;
	ex_attr_change_ = false;
	static Protocol::RoleExAttributeProto proto;
	proto.role_id = data_->id;
	proto.count_ver = (short)ExAttribute::eatCount;
	ex_attrs_.GetValues(proto.attrs);	// ���ͻ������Լ�

	actor_->SendData(proto);
}

float Role::GetExtraCritDamage()
{
	return 0;
}

bool Role::HasHuShenShield()
{
	return ex_ring_sys_->GetLevel(ExRingType_HuShenRing) > 0; //��ɫ���ϵĻ����ָ
		//|| (actor_->GetActorExRingIsEff(ActorExRingType_HuShenRing) 
		//	&& actor_->GetActorExRingLevel(ActorExRingType_HuShenRing) > 0);//������ϵĻ����ָ
}

double Role::GetAtkSum(void) {
	return actor_->GetAtkSum();
}

void Role::CreateAppearData(DataPacket& appearPack)
{

	Creature::CreateAppearData(appearPack);

	//appearPack << (unsigned char)actor_->GetJob();
	//appearPack << (unsigned char)actor_->GetSex();
	//��ɫ����
	appearPack << actor_->GetEntityName();
	appearPack << actor_->GetServerId();
	appearPack << (unsigned char)data_->job;
	appearPack << (unsigned char)data_->sex;
	appearPack << (int)actor_->GetLevel();
	appearPack << (int)(actor_->GetBasicData()->zhuansheng_lv);
	appearPack << (int)(actor_->GetBasicData()->prestige_exp);
	appearPack << GetEquipSystem()->GetEquipId(EquipSlotType_Coat);
	appearPack << GetEquipSystem()->GetEquipId(EquipSlotType_Weapon);
	appearPack << GetWingSystem()->GetWingData()->level;
	appearPack << GetWingSystem()->GetWingData()->openStatus;


	int tId = actor_->GetTitleSystem()->getRoleTitle(data_->id);
	appearPack << tId;
	appearPack << actor_->GetGuildId();
	appearPack << actor_->GetGuildSystem()->GetGuildName();
	appearPack << (int)(actor_->GetGuildSystem()->GetGuildPos());
	ZhuangBanData *p = zhuangban_sys_->GetZhuangBanData();
	appearPack << (int)p->pos1id;
	appearPack << (int)p->pos2id;
	appearPack << (int)p->pos3id;
	int trainLv = -1;
	if (actor_->GetActorVarSystem()->GetIntValue("trainVar.isAct", 0)) {
		trainLv = actor_->GetActorVarSystem()->GetIntValue("trainVar.level", 0);
	}
	appearPack << trainLv;
	appearPack << (short)data_->weapon_soul_id;
	for (short i = 0; i < HEIRLOOM_TYPE_MAX; ++i) {
		appearPack << (int)(data_->heirloom[i]);
	}
	appearPack << (short)actor_->GetCamp();

	//�ؽ���Ϣ
	int hylv = actor_->GetActorExRingLevel(ActorExRingType_HuoYanRing);
	int isEff = actor_->GetActorExRingIsEff(ActorExRingType_HuoYanRing);
	appearPack << (int)hylv;//�����ָ�ȼ�
	appearPack << (short)isEff;//�Ƿ��ս
	//appearPack << 0;// (BYTE)(actor_->GetActorExRingIsEff(ActorExRingType_MabiRing) ? 1 : 0);
	//appearPack << 0;// (BYTE)(actor_->GetActorExRingIsEff(ActorExRingType_HuShenRing) ? 1 : 0);
}

void Role::OnLevelUp()
{
	InitBasicAttribute();
	CalcAttributes();
}

void Role::OnEnterScene()
{
	Creature::OnEnterScene();
}

void Role::ChangeHp(double nValue, Creature* attacker /* = NULL */)
{
	if (actor_->GetCurrGatherMonster())
	{
		actor_->GetCurrGatherMonster()->OnChangeHp(nValue, this);
	}
	Creature::ChangeHp(nValue, attacker);
	
}

void Role::OnSetHp()
{
	double hp = GetHp();
	Creature::OnChangeHp(0, NULL, hp);
}

void Role::OnSetMp()
{
	static Protocol::UpdateMpProto proto;
	proto.handle = GetHandle();
	proto.mp = GetMp();
	//proto.need_display = false;

	Scene *scene = GetScene();
	if (scene)
		scene->SendData(proto);
	else
		actor_->SendData(proto);
	//OutputMsg(rmTip, "--------------------update mp:%d", proto.mp);
}
void Role::OnAddStatus(int status)
{
	if (actor_->GetCurrGatherMonster())
	{
		actor_->GetCurrGatherMonster()->OnAddStatus(status);
	}
	Creature::OnAddStatus(status);
}
/*
void Role::OnAttack(Creature* enemy, double damage)
{
	Creature::OnAttack(enemy,damage);
	auto scene = GetScene();
	if (!actor_->GetCurrGatherMonster() && scene && scene->GetDropBagCount() <= 0)
	{
		auto as = actor_->GetRoleSystem();
		for (int i = 0; i < MAX_ROLE; ++i)
		{
			auto role = as->GetRoleById(i);
			if ( role != nullptr  && !role->GetTarget() && !role->IsDeath())
			{
				//role->OnAttack(enemy, 0);
				role->SetTarget(enemy);
				if (role->GetAI())
				{
					role->GetAI()->ToState(AI::asBattle);
				}
				if (role->GetBattlePet())
				{
					//	role->GetBattlePet()->OnAttack(enemy, 0);
					role->GetBattlePet()->SetTarget(enemy);
					if (role->GetBattlePet()->GetAI())
					{
						role->GetBattlePet()->GetAI()->ToState(AI::asBattle);
					}
				}
			}
		}
	}
	
}
*/
void Role::OnSave()
{
	if (!data_) return;

	data_->power = attrs_.GetPower();
	equip_sys_->Save(data_);
	//wing_sys_->Save(data_);
	enhance_sys_->Save(data_);
	stone_sys_->Save(data_);
	jingmai_sys_->Save(data_);
	zhuling_sys_->Save(data_);
	fuling_sys_->Save(data_);
	soul_sys_->Save(data_);
	ex_ring_sys_->Save(data_);
	soul_shield_sys_->Save(data_);
	bless_sys_->Save(data_);
	neigong_sys_->Save(data_);
	//skillbreak_sys_->Save(data_);
}

int Role::GetSkillLevel(int index)
{
	if (index < 0 || index >= SkillSystem::MAX_SKILL_INDEX)
		return 0;
	return data_->skills.skill_level[index];
}

void Role::SetSkillLevel(int index, int level)
{
	if (index < 0 || index >= SkillSystem::MAX_SKILL_INDEX)
		return;

	data_->skills.skill_level[index] = level;
}

void Role::SetCamp(int camp) {
	Inherited::SetCamp(camp);
	Protocol::SwitchCampProto msg;
	msg.src_handle = GetHandle();
	msg.camp = camp;
	if (GetScene())
		GetScene()->SendData(msg);
}

void Role::OnFirst()
{
	//��ʼ������
	skill_sys_->UpgradeSkill(0);

	//��ʼ������
	//��ʼ��...
	if (actor_->IsInited()) //����actor�ı���Ҫ��actor��ʼ�����
	{
		//actor_->GetXXXSystem()->...
	}
}

/*bool Role::IsEnemy(Creature* target)
{
	
}*/


void Role::WriteData(DataPacket &pack, bool skirmishClone, int attrper)
{
	if (skirmishClone) // ����ս�������
	{
		pack << 0;	  // �ƺ�ID

		// �����������
		double old_power = data_->power;
		// ���һ��
		int r = 90 + wrand(20);
		if(attrper) {
			r = attrper;
		}
		data_->power = floor(data_->power * r / 100);
		pack.writeBuf(data_, sizeof(RoleData));
		data_->power = old_power;

		pack << (short)Attribute::atCount;	// ��������
		double attrs[Attribute::atCount];
		attrs_.GetAttrData(attrs);
		if(r != 100) {
			for (int i = 0; i < Attribute::atCount; ++i)
				attrs[i] = floor(attrs[i] * r / 100);
		}
		attrs[Attribute::atHp] = floor(attrs[Attribute::atHpMax]);

		pack.writeBuf(attrs, Attribute::atCount * sizeof(double));
	}
	else // ��������
	{
		int tId = actor_->GetTitleSystem()->getRoleTitle(data_->id);
		pack << tId;	  // �ƺ�ID

		// ��������
		pack.writeBuf(data_, sizeof(RoleData));
		pack << (short)Attribute::atCount;	  // ��������
		double attrs[Attribute::atCount];
		attrs_.GetAttrData(attrs);
		pack.writeBuf(attrs, Attribute::atCount * sizeof(double));
	}

	// ��������
	int ex_attrs[ExAttribute::eatCount];
	ex_attrs_.GetValues(ex_attrs);

	pack << (short)ExAttribute::eatCount;
	pack.writeBuf(ex_attrs, ExAttribute::eatCount * sizeof(int));
	// ����������
	ScriptValueList arg;
	arg << GetActor();
	arg << GetId();
	arg << (void*)&pack;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("packJadePlateData", &arg, &arg, 0);

	//װ������
	ZhuangBanData* p = zhuangban_sys_->GetZhuangBanData();
	pack << (int)p->pos1id;
	pack << (int)p->pos2id;
	pack << (int)p->pos3id;

	luaScript.Call("packLeiTingEquipData", &arg, &arg, 0);
}

Creature* Role::GetSelfMinRole()
{
	if (!actor_) return NULL;

	Role* list[MAX_ROLE] = { NULL };
	actor_->GetRoleSystem()->GetRoles(list);
	Role* ret = NULL;
	double hp_percent = 999999;
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = list[i];
		if (!role) break;
		if (role->IsDeath()) continue;
		double temp = role->GetHp() * 100 / role->GetMaxHp();
		if (temp < hp_percent)
		{
			hp_percent = temp;
			ret = role;
		}
	}
	return ret;
}

int Role::getWeaponPeakLv(void) {
	if (!actor_) return 0;
	auto gw_sys = actor_->GetGodWeaponSystem();
	if (!gw_sys || !gw_sys->getPeak()) return 0;
	return gw_sys->getLevel();
}

int Role::getDeathCount(void) {
	if (!actor_) return 0;
	auto role_sys = actor_->GetRoleSystem();
	if (!role_sys) return 0;
	return role_sys->GetDeathCount();
}

void Role::LogicRun(int64_t curr_t)
{
	Creature::LogicRun(curr_t);
	if (actor_ && is_init_ && actor_->logined_) SendAttributes();
	if (actor_ && is_init_ && actor_->logined_) SendExAttributes();


	if (this->GetBattlePet())
	{
		int dis = ::GetPixDistance(this->GetPosition(), this->GetBattlePet()->GetPosition(), 0);
		if (dis >= this->GetAI()->GetVision() * GRIDSIZE  &&  GetBattlePet()->GetMoveSystem())
		{
			Grid pos = GetPosition();
			Grid dir = GetDirection();//��ȡ��ҵ�ǰ����
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
			GetBattlePet()->SetTarget(nullptr);
			GetBattlePet()->GetMoveSystem()->InstantMove(pos.ToPoint());
		}
	}
}

void Role::OnChangeHp(double nValue, Creature* attacker, double &ret)
{
	if (actor_->GetCurrGatherMonster())
	{
		actor_->GetCurrGatherMonster()->OnChangeHp(nValue, this);
	}
	FuBen *fb = GetScene()->GetFuBen();
	if (fb)
		fb->OnRoleDamage(this, (int)(0 - nValue), attacker, ret);
	Creature::OnChangeHp(nValue, attacker, ret);
}

void Role::OnKilled(Creature* killer)
{
	if (actor_->GetRoleSystem()->IsAllDie())
	{
		FuBen *fb = GetFuBen();
		if (fb)
		{
			EntityHandle hdl = 0;
			if (killer) hdl = killer->GetHandle();
			fb->OnEntityDie(actor_, hdl);//����ǰ���ȡ��������������ȷ����
			Protocol::ActorDieProto msg;
			actor_->SendData(msg);
			//�Լ�����ʱ�������б�
			this->GetAI()->ClearHatred();
		}
		actor_->GetActorExRingSystem()->OnAllRoleDie();
	}
	Creature::OnKilled(killer);
}

void Role::OnMove(const Point& pos)
{
	if (this == actor_->GetLiveByJob()) {
		actor_->OnMove(pos);
	}
}

void Role::GMSetAttr(int type, double value)
{
	if (type < 0 || type >= Attribute::atCount) return;
	attrs_.GMSet(type, value);

	//����ı��Լ���Ѫ��Ϊ0 ���⴦��Ϊ��Ѫ������
	if(type == 0 && value < 100.f)
		this->ChangeHp(-10000000, NULL);
	if (is_init_) 
	{
		static Protocol::RoleAttributeProto proto;
		proto.role_id = data_->id;
		proto.count_ver = (short)Attribute::atCount;
		attrs_.GetAttrData(proto.attrs);	// ���ͻ������Լ�
		proto.power = attrs_.GetPower();
		actor_->SendData(proto);
	}

}


bool Role::CanMove()
{
	if (!Creature::CanMove())
	{
		return false;
	}
	if (actor_->GetCurrGatherMonster())
	{
		return actor_->GetCurrGatherMonster()->CanMove();
	}
	return true;
}




