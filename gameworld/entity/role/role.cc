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

// 析构貌似要写在这里，旧代码中的退出检测可能是通过析构前检查内存泄露实现的
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
	//初始化
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
	//技能等级信息
	for (int index = 0; index < MAX_SKILL_COUNT; ++index)
	{
		int cur_level = data_->skills.skill_level[index];
		pack << cur_level;
	}
	//装备信息
	for (int index = 0; index < EquipSlotType_Max; ++index)
	{
		/*
			装备数据结构
			装备强化等级
			装备精炼等级
			装备的表id
			装备的数量
		*/
		pack << data_->equips_data.slot_data[index].strength_lv; 
		pack << data_->equips_data.slot_data[index].gem_lv;
		data_->equips_data.slot_data[index].equip_data.writeData(pack);
	}

	//装备信息
	for (int index = 0; index < EquipSlotType_Dzi; ++index)
	{
		/*
		装备数据结构
		装备强化等级
		装备精炼等级
		装备的表id
		装备的数量
		*/
		pack << data_->equips_data.god_slot_data[index].strength_lv;
		pack << data_->equips_data.god_slot_data[index].gem_lv;
		data_->equips_data.god_slot_data[index].equip_data.writeData(pack);
	}

	//特戒数据获取
	for (int i = 0;i < 4 ;++i)
	{
		pack << data_->ex_rings.ring_level[i];
	}

	//翅膀数据
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
	//经脉
	{
		pack << data_->jingmai_data.level;
		pack << data_->jingmai_data.stage;
	}

	//龙魂
	{
		pack << data_->loogsoul_data.stage;
		pack << data_->loogsoul_data.level;
		pack << data_->loogsoul_data.exp;
		pack << data_->loogsoul_data.act;
	}

	//战纹
	for (int i = 0;i < MAX_FUWEN;++i)
	{
		data_->fuwen_data.fuwen_slot[i].writeData(pack);
	}



	//称号的数据
	int titleId = 0;
	int titleEndTimeValue = 0;
	int titleLevelValue = 0;
	int titleCount = 0;
	int maxCount = 1;
	//称号的数量
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
	//称号的到期时间和等级
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
	//获取装扮数量
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
	//装扮所拥有的
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

	//获取爵位信息
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

	//获取特戒信息
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

	//符文信息
	for (int i = 0; i < TogetherHitSlotType_Max; ++i)
	{
		//pack << actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].strength_lv;
		//pack << actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].gem_lv;
		actor_->GetTogetherHitSystem()->getTogetherHitEquip().together_hit_slot[i].equip_data.writeData(pack);;
	}

	//二脉信息
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

	//兵魂信息
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

	//神器战力
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

	//勋章信息
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

	//图鉴信息
	{

		double tujianPower = 0;
		{
			tujianPower = (double)actor_->getTujianPower();
		}
		pack << tujianPower;
	}
	//神兵战力
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
	//剑谱信息
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
	/**********各系统属性**********/
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

	//额外战力
	s_attrs.SetExtraPower(s_attrs.GetExtraPower() + actor_->GetGodWeaponSystem()->getPower(GetJob()));

	//attrs += .. 其他系统属性

	/***********计算排行榜的战斗力***********/
	//总战力(没有翅膀的)
	attrs_cache_.CalcBattleAttribute(s_attrs, GetJob()); // 展示交互属性
	attrs_cache_.CalcPower();
	rank_power_ = attrs_cache_.GetPower();//排行榜专用战斗力

	s_attrs += wing_sys_->GetTempAttr();
	//attrs += .. 其他系统属性

	/******************************/
	basic_attrs_ = s_attrs;
	attrs_cache_.CalcBattleAttribute(s_attrs,GetJob()); // 展示交互属性
	attrs_cache_.CalcPower();

	s_attrs += *actor_->GetNewWorldBossAttr();//世界boss副本不加战力的属性
	s_attrs += skill_effect_sys_->GetAttr();	// 加上buff和debuff获得最终属性
	attrs_.CalcBattleAttribute(s_attrs, GetJob());		// 实际属性
	attrs_.SetPower(attrs_cache_.GetPower());	// 一般通过最终属性获取，实际应该是非战斗状态的战力

	attrs_.SetHp(floor(GetMaxHp() * hp_rate));
	attrs_.SetMp(floor(GetMaxMp() * mp_rate));
	attrs_.SetNp(floor(GetMaxNp() * ng_rate));
	if (actor_ && is_init_ && actor_->logined_)
		attr_change_ = true;
	actor_->GetRoleSystem()->UpdateTotalPower();

	// 放在发给客户端后面，以防客户端用这个显示血量
	attrs_cache_.SetHp(attrs_cache_.Get(Attribute::atHpMax)); //非战斗数据血量为满
	attrs_cache_.SetMp(attrs_cache_.Get(Attribute::atMpMax));
	double new_hp = GetHp();
	if (is_init_ && new_hp != old_hp) {
		// 更新血量
		Creature::OnChangeHp(new_hp - old_hp, NULL, new_hp);
		NotifyAttr(Attribute::atHpMax, GetMaxHp());  //每次都更新最大血量
		//Protocol::UpdateHpProto msg;
		//msg.handle = GetHandle();
		//msg.hp = GetHp();
		//msg.need_display = false;
		//actor_->SendData(msg);
		// todo 加上最大血量
	}
	if (is_init_ && GetNp() != old_np)
	{
		// 更新内功值
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

	// 设置为当前血量
	s_attrs.Set(Attribute::atHp, old_hp);
	s_attrs.Set(Attribute::atMp, old_mp);
	s_attrs.Set(Attribute::atNeiGong, old_np);

	s_attrs += skill_effect_sys_->GetAttr();
	s_attrs += camp_battle_attrs_;				//阵营战不加战力的属性
	attrs_.CalcBattleAttribute(s_attrs, GetJob());		// 实际属性

	// 与skillEffect系统做加法运算, 但是涉及到当前血量的修改的，一定要在skillEffect即时修改
	double hp = GetHp();
	double maxHp = GetMaxHp();
	if (hp > maxHp)
		hp = maxHp;
	if (hp != old_hp) {
		SetHp(hp);
	}
	if (old_maxHp != maxHp)	{
		NotifyAttr(Attribute::atHpMax, maxHp);  //每次都更新最大血量
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
	attrs_.GetAttrData(proto.attrs);	// 发送基础属性集
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
	ex_attrs_.GetValues(proto.attrs);	// 发送基础属性集

	actor_->SendData(proto);
}

float Role::GetExtraCritDamage()
{
	return 0;
}

bool Role::HasHuShenShield()
{
	return ex_ring_sys_->GetLevel(ExRingType_HuShenRing) > 0; //角色身上的护身戒指
		//|| (actor_->GetActorExRingIsEff(ActorExRingType_HuShenRing) 
		//	&& actor_->GetActorExRingLevel(ActorExRingType_HuShenRing) > 0);//玩家身上的护身戒指
}

double Role::GetAtkSum(void) {
	return actor_->GetAtkSum();
}

void Role::CreateAppearData(DataPacket& appearPack)
{

	Creature::CreateAppearData(appearPack);

	//appearPack << (unsigned char)actor_->GetJob();
	//appearPack << (unsigned char)actor_->GetSex();
	//角色数据
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

	//特戒消息
	int hylv = actor_->GetActorExRingLevel(ActorExRingType_HuoYanRing);
	int isEff = actor_->GetActorExRingIsEff(ActorExRingType_HuoYanRing);
	appearPack << (int)hylv;//烈焰戒指等级
	appearPack << (short)isEff;//是否出战
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
	//初始化技能
	skill_sys_->UpgradeSkill(0);

	//初始化任务？
	//初始化...
	if (actor_->IsInited()) //调用actor的必须要等actor初始化完毕
	{
		//actor_->GetXXXSystem()->...
	}
}

/*bool Role::IsEnemy(Creature* target)
{
	
}*/


void Role::WriteData(DataPacket &pack, bool skirmishClone, int attrper)
{
	if (skirmishClone) // 遭遇战玩家数据
	{
		pack << 0;	  // 称号ID

		// 随机基础属性
		double old_power = data_->power;
		// 随机一下
		int r = 90 + wrand(20);
		if(attrper) {
			r = attrper;
		}
		data_->power = floor(data_->power * r / 100);
		pack.writeBuf(data_, sizeof(RoleData));
		data_->power = old_power;

		pack << (short)Attribute::atCount;	// 属性数量
		double attrs[Attribute::atCount];
		attrs_.GetAttrData(attrs);
		if(r != 100) {
			for (int i = 0; i < Attribute::atCount; ++i)
				attrs[i] = floor(attrs[i] * r / 100);
		}
		attrs[Attribute::atHp] = floor(attrs[Attribute::atHpMax]);

		pack.writeBuf(attrs, Attribute::atCount * sizeof(double));
	}
	else // 正常数据
	{
		int tId = actor_->GetTitleSystem()->getRoleTitle(data_->id);
		pack << tId;	  // 称号ID

		// 基础属性
		pack.writeBuf(data_, sizeof(RoleData));
		pack << (short)Attribute::atCount;	  // 属性数量
		double attrs[Attribute::atCount];
		attrs_.GetAttrData(attrs);
		pack.writeBuf(attrs, Attribute::atCount * sizeof(double));
	}

	// 特殊属性
	int ex_attrs[ExAttribute::eatCount];
	ex_attrs_.GetValues(ex_attrs);

	pack << (short)ExAttribute::eatCount;
	pack.writeBuf(ex_attrs, ExAttribute::eatCount * sizeof(int));
	// 新玉佩数据
	ScriptValueList arg;
	arg << GetActor();
	arg << GetId();
	arg << (void*)&pack;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("packJadePlateData", &arg, &arg, 0);

	//装扮数据
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
			Grid dir = GetDirection();//获取玩家当前方向
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
			fb->OnEntityDie(actor_, hdl);//放在前面获取不到场景怪物正确数量
			Protocol::ActorDieProto msg;
			actor_->SendData(msg);
			//自己死亡时清楚仇恨列表
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

	//如果改变自己的血量为0 特殊处理为扣血到死亡
	if(type == 0 && value < 100.f)
		this->ChangeHp(-10000000, NULL);
	if (is_init_) 
	{
		static Protocol::RoleAttributeProto proto;
		proto.role_id = data_->id;
		proto.count_ver = (short)Attribute::atCount;
		attrs_.GetAttrData(proto.attrs);	// 发送基础属性集
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




