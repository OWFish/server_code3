#include "StdAfx.h"
#include "role.h"
#include "role_clone.h"
#include "wing/wing_system.h"
#include "item/equip/equip_system.h"
#include "ai/ai_mgr.h"
#include "skill/skill_system.h"
#include "skill/effect/skill_effect_system.h"
#include "ex-ring/ex_ring_system.h"
#include "guild/guild_system.h"
#include "title/title_system.h"
#include "zhuangban/zhuangban.h"
#include "systems/imba/imbasystem.h"
#include "systems/godweapon/godweaponsystem.h"
#include "protos/zhanling_proto.h"
#include "systems/guild/guild.h"

int RoleClone::show_zhanling_cd_ = 0;
int RoleClone::show_zhanling_delay_ = 0;

RoleClone::RoleClone() : m_t1s(1000)
{
	SetType(EntityType_CloneRole);
	SetCamp(CampType_None);
	aexring_mon.clear();
	actor_id = 0;
	isLeader = false;
	isPeak_ = false;
	zhanling_lv_ = -1;
	show_zhanling_t_ = 0;
	zhanling_talent_effid_ = 0;
	GodWeaponlevel_ = 0;
	perstige_exp_ = 0;
	zhuansheng_lv = 0;
	guildpos = 0;
	memset(heirloom, 0, sizeof(heirloom));
	flamestamp_lv_ = 0;
	memset(flamestamp_skill_lv_, 0, sizeof(flamestamp_skill_lv_));
	is_mirror = 0;
	//has_mabi_ring = false;
	//has_hushen_ring = false;
}

RoleClone::~RoleClone()
{
	OnDestroy();
}

void RoleClone::CreateAppearData(DataPacket& appearPack)
{
	Creature::CreateAppearData(appearPack);

	//appearPack << job1;
	//appearPack << sex1;

	//天梯这两个值没用
	appearPack << name.c_str();
	appearPack << job;
	appearPack << sex;
	appearPack << level;
	appearPack << zhuansheng_lv;
	appearPack << guildpos;
	appearPack << clothes_id;
	appearPack << weapon_id;
	appearPack << wing_level;
	appearPack << wing_open_state;
	appearPack << tid_;
	appearPack << guild_id_;
	appearPack << guild_name_.c_str();
	appearPack << 0;
	appearPack << zhuangban_pos1_;
	appearPack << zhuangban_pos2_;
	appearPack << zhuangban_pos3_;
	appearPack << train_lv_;
	appearPack << weapon_soul_id;
	for (short i = 0; i < HEIRLOOM_TYPE_MAX; ++i) {
		appearPack << (int)(heirloom[i]);
	}
	appearPack << (short)GetCamp();

	//特戒消息
	int hylv = 0;
	int isEff = 0;
	appearPack << (int)hylv;//烈焰戒指等级
	appearPack << (short)isEff;//是否出战
	//appearPack << 0;// (BYTE)(has_mabi_ring ? 1 : 0);
	//appearPack << 0;// (BYTE)(has_hushen_ring ? 1 : 0);
}

void RoleClone::LoadFromRobot(RobotData* data, unsigned int scene, int x, int y)
{
	if (!data)
	{
		return;
	}
	actor_id = data->actor_id;
	name = data->name;
	level = data->level;
	job = data->job;
	sex = data->sex;
	headid_ = data->headid;
	zhuangban_pos2_ = data->holaid;
	//job1 = job;
	//sex1 = sex1;
	clothes_id = data->clothesId;
	weapon_id = data->weaponId;
	wing_open_state = data->wingOpenState;
	wing_level = data->wingLevel;
	basic_attrs_cache_ = data->attrs;
	basic_attrs_cache_[Attribute::atHp] = (data->attrs)[Attribute::atHpMax];
	basic_attrs_cache_[Attribute::atMp] = (data->attrs)[Attribute::atMpMax];
	is_mirror = data->ismirror;
	if (data->camp > 0)
	{
		SetCamp(data->camp);
	}
	
	CalcAttributes();


	ai_ = GetGameEngine()->GetAiMgr()->CreateAi(job, this);

	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();

	Scene* s = mgr->GetScenePtr(scene);
	if (!s)
	{
		OutputMsg(rmError, "create clone role scen failed.scene:%d", scene);
		GetGameEngine()->GetEntityMgr()->DestroyEntity(GetHandle(), true);
		return;
	}

	auto& sk = data->skills;
	for (size_t i = 0; i < sizeof(sk) / sizeof(sk[0]); ++i)
	{
		if(sk[i])
			GetSkillSystem()->AddSkill(sk[i]);
	}
	s->EnterScene(this, x, y);
}

void RoleClone::LoadFromRole(Role* role, unsigned int scene, int x, int y)
{
	if (role == nullptr)
	{
		return;
	}
	auto actor = role->GetActor();
	guild_id_ = actor->GetGuildId();
	guild_name_ = actor->GetGuildSystem()->GetGuildName();
	tid_ = actor->GetTitleSystem()->getRoleTitle(role->GetId());
	/*
	appearPack << actor_->GetEntityName();
	appearPack << (unsigned char)data_->job;
	appearPack << (unsigned char)data_->sex;
	appearPack << (int)actor_->GetLevel();
	appearPack << GetEquipSystem()->GetEquipId(EquipSlotType_Coat);
	appearPack << GetEquipSystem()->GetEquipId(EquipSlotType_Weapon);
	appearPack << GetWingSystem()->GetWingData()->level;
	appearPack << GetWingSystem()->GetWingData()->openStatus;
	*/


	/*
	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
		Guild* guild = mgr->FindGuild(guildId);
	*/

	name = actor->GetEntityName();
	level = actor->GetLevel();
	auto data = role->GetData();
	job = data->job;
	sex = data->sex;

	actor_id = actor->GetActorId();
	if (actor->GetActorVarSystem()->GetIntValue("trainVar.isAct", 0)) {
		train_lv_ = actor->GetActorVarSystem()->GetIntValue("trainVar.level", 0);
	}
	else {
		train_lv_ = -1;
	}
	yupei_lv_ = actor->GetYuPeiLv();
	perstige_exp_ = actor->GetPrestigeExp();
	headid_ = actor->GetBasicData()->headimage;

	weapon_soul_id = data->weapon_soul_id;
	memcpy(heirloom, role->GetData()->heirloom, sizeof(heirloom));
	clothes_id = role->GetEquipSystem()->GetEquipId(EquipSlotType_Coat);
	weapon_id = role->GetEquipSystem()->GetEquipId(EquipSlotType_Weapon);
	wing_open_state = role->GetWingSystem()->GetWingData()->openStatus;
	wing_level = role->GetWingSystem()->GetWingData()->level;
	has_hushen_shield = role->HasHuShenShield();
	actor->GetZhanLingInfo(zhanling_id_, zhanling_lv_, zhanling_talent_effid_, zhanling_effids_);
	isPeak_ = actor->GetGodWeaponSystem()->getPeak();
	GodWeaponlevel_ = actor->GetGodWeaponSystem()->getLevel();
	actor->GetImbaSystem()->appendActId(imba_act_id_);
	actor->GetGodWeaponSystem()->appendActId(weapon_list_);
	ZhuangBanData *p = role->GetZhuangBanSystem()->GetZhuangBanData();
	zhuangban_pos1_ = p->pos1id;
	zhuangban_pos2_ = p->pos2id;
	zhuangban_pos3_ = p->pos3id;
	auto role_attr = role->GetAttrsCache();
	for (int i = 0; i < Attribute::atCount; ++i)
		basic_attrs_cache_[i] = role_attr->Get(i);
	basic_attrs_cache_[Attribute::atHp] = (*role_attr)[Attribute::atHpMax];
	basic_attrs_cache_[Attribute::atMp] = (*role_attr)[Attribute::atMpMax];
	ex_attrs_ = role->GetExAttr();
	zhuansheng_lv = role->GetZhuangshengLv();
	int guildid = role->GetGuildID();
	if (guildid > 0)
	{
		static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
		if (mgr)
		{
			Guild* guild = mgr->FindGuild(guildid);
			if (guild)
			{
				guildpos = guild->GetGuildPos(role->GetActorId());
			}
		}
	}

	CalcAttributes();

	ai_ = GetGameEngine()->GetAiMgr()->CreateAi(actor->GetJob()*10+job, this);
/*	if (!ai_) //没AI就先让他站着不动
	{
		OutputMsg(rmError, "create clone role ai failed.");
		return;
	}
*/
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();

	Scene* s = mgr->GetScenePtr(scene);
	if (!s)
	{
		OutputMsg(rmError, "create clone role scen failed.scene:%d", scene);
		GetGameEngine()->GetEntityMgr()->DestroyEntity(GetHandle(), true);
		return;
	}

	auto& sk = role->GetSkillSystem()->GetSkillList();
	for (size_t i = 0;i < sk.size(); ++i)
	{
		GetSkillSystem()->AddSkill(sk[i]->GetId());
	}

	std::vector<Skill*>* psk = role->GetSkillSystem()->GetPassiveSkillLists();
	for (int cond = 0; cond < PassiveSkillCond_Count; cond++) {
		for (size_t i = 0; i < psk[cond].size(); ++i)
		{
			GetSkillSystem()->AddPassiveSkill(psk[cond][i]->GetId());
		}
	}

	s->EnterScene(this, x, y);
	if (ai_) {
		const AIConfig* ai_conf = ai_->GetConfig();
		if (ai_conf && ai_conf->skills.size() > 0) {
			const AiSkill &skill = ai_conf->skills[0];
			double cd_sub = (double)GetExAttr(ExAttribute::eatTogetherHitCdSub) / 10000.0;
			int64_t cd_mtime = static_cast<int64_t>( GetGameEngine()->getTickCount() + ((skill.cd - skill.cd*cd_sub) / 10) );
			GetSkillSystem()->SetSkillCdById(skill.skill_id, cd_mtime+500);
		}
	}
}

void RoleClone::LogicRun(int64_t curr_t)
{
	Creature::LogicRun(curr_t);
	
	if (isLeader && m_t1s.CheckAndSet(curr_t)) {
		ShowZhanLing(curr_t);
	}
}

int RoleClone::GetId()
{
	return job;
}

void RoleClone::InitBasicAttribute()
{

}

void RoleClone::CalcAttributes()
{
	static Attribute s_attrs;
	double hp_rate = 1.0;
	double mp_rate = 1.0;

	if (GetMaxHp() > 0) {
		hp_rate = 1.0 * GetHp() / GetMaxHp();
	}
	if (GetMaxMp() > 0)
	{
		mp_rate = 1.0 * GetMp() / GetMaxMp();
	}

	s_attrs.Reset();
	s_attrs += basic_attrs_cache_;
	// ..
	s_attrs += skill_effect_sys_->GetAttr();
	attrs_.SetBattleAttribute(s_attrs);

	attrs_.SetHp(floor(GetMaxHp() * hp_rate));
	attrs_.SetMp(floor(GetMaxMp() * mp_rate));

}

void RoleClone::CalcBattleAttributes()
{
	double old_hp = GetHp();
	double old_mp = GetMp();
	static Attribute s_attrs;
	s_attrs.Reset();
	s_attrs += basic_attrs_cache_;
	// ..
	s_attrs += skill_effect_sys_->GetAttr();
	attrs_.SetBattleAttribute(s_attrs);

	SetHp(old_hp);
	SetMp(old_mp);
}

 void RoleClone::OnDestroy()
{
	 Creature::OnDestroy();

	 static AiMgr* aimgr = GetGameEngine()->GetAiMgr();
	 if (ai_)
		 aimgr->DestroyAi(ai_);
	 ai_ = nullptr;
	 DestroyAllAexringMon();
}

 void RoleClone::OnKilled(Creature* killer)
 {
	 Creature::OnKilled(killer);

	 if (isLeader)
	 {
		 //主角死了，按战法道顺序换主角
		 RoleClone *roleClone = GetLiveByJob();
		 if (roleClone)
		 {
			 //转移主角身份
			 roleClone->SetLeader();
			 isLeader = false;

			 //转移特戒怪
			 for (auto it = aexring_mon.begin(); it != aexring_mon.end(); ++it)
			 {
				 if (it->second) {
					 roleClone->SetAexringMon(it->first, it->second);
					 it->second->SetMasterHandle(roleClone->GetHandle());
				 }
			 }
			 aexring_mon.clear();
		 }
		 else {
			 //都死亡的时候,回收所有的特戒怪物
			 DestroyAllAexringMon();
		 }
	 }
 }

 void RoleClone::SetBuddy(int roleId, EntityHandle& hdl)
 {
	 if (roleId < 0 || roleId >= MAX_ROLE)
	 {
		 return;
	 }
	 cloneHdl[roleId] = hdl;
	// if (0 == roleId && GetHandle() == hdl) isLeader = true;
 }

 bool RoleClone::GetBuddy(int roleId, EntityHandle& hdl)
 {
	 if (roleId < 0 || roleId >= MAX_ROLE)
	 {
		 return false;
	 }
	 hdl = cloneHdl[roleId];
	 return true;
 }

 void RoleClone::SetAexringMon(int rid, Monster* mon)
 {
	 Monster *old = aexring_mon[rid];
	 if (old)
	 {
		 GetGameEngine()->GetEntityMgr()->DestroyEntity(old->GetHandle());
	 }
	 aexring_mon[rid] = mon;
 }

 void RoleClone::DelAexringMon(int rid)
 {
	 auto it = aexring_mon.find(rid);
	 if (it != aexring_mon.end())
	 {
		 aexring_mon.erase(it);
	 }
 }

 void RoleClone::DelAexringMon(Monster* mon)
 {
	 for (auto it = aexring_mon.begin();
		 it != aexring_mon.end(); ++it)
	 {
		 if (it->second == mon)
		 {
			 aexring_mon.erase(it);
			 break;
		 }
	 }
 }

 int RoleClone::HasAexringMon(Monster* mon)
 {
	  
	 for (auto it = aexring_mon.begin();
		 it != aexring_mon.end(); ++it)
	 {
		if (it->second == mon)
		{
			return it->first;
		}
	 }
	 return -1;
 }

 void RoleClone::DestroyAllAexringMon()
 {
	 if (aexring_mon.size() <= 0) return;
	 std::vector<Monster*> des_ent;
	 for (auto it = aexring_mon.begin(); it != aexring_mon.end(); ++it)
	 {
		 if (it->second)
			des_ent.push_back(it->second); //销毁实体时候会把迭代器删掉
	 }
	 aexring_mon.clear();
	 for (auto it = des_ent.begin(); it != des_ent.end(); ++it)
	 {
		 GetGameEngine()->GetEntityMgr()->DestroyEntity((*it)->GetHandle());
	 }
 }

 void RoleClone::SetAexringPassivity(bool b) {
	 if (aexring_mon.size() <= 0) return;
	 for (auto it = aexring_mon.begin(); it != aexring_mon.end(); ++it) {
		 if (it->second && it->second->GetAI())
			 it->second->GetAI()->setPassivity(b);
	 }
 }

 void RoleClone::SetAexringTargetNull() {
	 if (aexring_mon.size() <= 0) return;
	 for (auto it = aexring_mon.begin(); it != aexring_mon.end(); ++it) {
		 if (it->second)
			 it->second->SetTarget(NULL);
	 }
 }

 void RoleClone::AddAerMonAttr(int rid, Attribute::AttributeType type, double value)
 {
	 if (rid < 0 || rid >= ActorExRingType_MAX) return;
	 for (int i = 0; i < MAX_ROLE; ++i)
	 {
		 static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		 auto &hdl = cloneHdl[i];
		 if (!hdl) continue;
		 auto roleClone = em->GetEntity(hdl);
		 if (!roleClone) continue;
		 if (((RoleClone*)roleClone)->IsDeath()) continue;
		 auto attr = ((RoleClone*)roleClone)->GetAerMonAttr(rid);
		 if (attr)
		 {
			 attr->Add(type, value);
		 }
	 }
 }

 void RoleClone::AddAerMonExAttr(int rid, ExAttribute::ExAttributeType type, int value)
 {
	 if (rid < 0 || rid >= ActorExRingType_MAX) return;
	 for (int i = 0; i < MAX_ROLE; ++i)
	 {
		 static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		 auto &hdl = cloneHdl[i];
		 if (!hdl) continue;
		 auto roleClone = em->GetEntity(hdl);
		 if (!roleClone) continue;
		 if (((RoleClone*)roleClone)->IsDeath()) continue;
		 auto attr = ((RoleClone*)roleClone)->GetAerMonExAttr(rid);
		 if (attr)
		 {
			 attr->Add(type, value);
		 }
	 }
 }

 Attribute *RoleClone::GetAerMonAttr(int rid)
 {
	 if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
	 return &(aermon_attr[rid]);
 }

 ExAttribute *RoleClone::GetAerMonExAttr(int rid)
 {
	 if (rid < 0 || rid >= ActorExRingType_MAX) return NULL;
	 return &(aermon_ex_attr[rid]);
 }

 const std::set<int>* RoleClone::getWeaponIdList(int idx)
 {
	 auto it = weapon_list_.find(idx);
	 if (weapon_list_.end() != it) {
		 return &it->second;
	 }

	 return nullptr;
 }

 int RoleClone::getDeathCount(void)
 {
	 int count = 0;
	 for (int i = 0; i < MAX_ROLE; ++i)
	 {
		 static EntityMgr *em = GetGameEngine()->GetEntityMgr();
		 auto &hdl = cloneHdl[i];
		 if (!hdl) continue;
		 auto roleClone = em->GetEntity(hdl);
		 if (!roleClone || ((RoleClone*)roleClone)->IsDeath())
			 count++;
	 }
	 
	 return count;
 }

 double RoleClone::GetAtkSum(void) {
	return GetAllAttrs().Get(Attribute::atAtk);
 }

uint64_t RoleClone::GetSummitHandle() {
	 return (uint64_t)GetType() << 32 | actor_id;
}

//默认按战法道顺序
RoleClone *RoleClone::GetLiveByJob()
{
	static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	RoleClone *job_role[JobType_Max];
	memset(job_role, 0, sizeof(job_role));
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		auto &hdl = cloneHdl[i];
		if (!hdl) continue;
		auto roleClone = static_cast<RoleClone*>(em->GetEntity(hdl));
		if (!roleClone || roleClone->IsDeath()) continue;
		int job = roleClone->GetJob();
		if (job >= 0 && job < JobType_Max)
			job_role[job] = roleClone;
	}
	if (job_role[JobType_Warrior]) return job_role[JobType_Warrior];
	if (job_role[JobType_Mage]) return job_role[JobType_Mage];
	if (job_role[JobType_Taoist]) return job_role[JobType_Taoist];
	if (job_role[JobType_None]) return job_role[JobType_None];
	return nullptr;
}

void RoleClone::ShowZhanLing(int64_t curr_t)
{
	if (zhanling_lv_ < 0) return;  //系统未开启或还没到指定等级
	if (curr_t - show_zhanling_t_ < show_zhanling_cd_) return;  //cd中

	Scene *scene = GetScene();
	if (nullptr == scene) return;  //不在副本里
	FuBen *fuben = scene->GetFuBen();
	if (nullptr == fuben) return;  //找不到副本

	static EntityMgr *em = GetGameEngine()->GetEntityMgr();

	RoleClone *roleClones[MAX_ROLE] = {NULL};
	bool haveRoleClone = false;

	for (auto it = zhanling_effids_.begin(); it != zhanling_effids_.end(); it++)
	{
		if (static_cast<int>(wrand(10000)) < it->second)
		{
			//触发战灵天赋
			for (int i = 0; i < MAX_ROLE; ++i)
			{
				if (!haveRoleClone) {
					auto &hdl = cloneHdl[i];
					if (!hdl) continue;
					roleClones[i] = static_cast<RoleClone *>(em->GetEntity(hdl));
				}
				if (roleClones[i] && !roleClones[i]->IsDeath()) {
					roleClones[i]->GetSkillEffectSystem()->AddEffect(roleClones[i], it->first);
				}
			}
			haveRoleClone = true;
		}
	}

	show_zhanling_t_ = curr_t;

	if (!fuben->NeedShowZhanLing()) return; //有些副本为了不卡屏蔽掉广播

	// 广播
	Protocol::ShowZhanLingProto proto;
	proto.handle = GetHandle();
	proto.level = zhanling_lv_;
	proto.id = zhanling_id_;
	scene->SendData(proto);

	//OutputMsg(rmTip, "show zhanling %d %d %d", actor_id_, proto.handle, proto.stage);
}

void RoleClone::ResetShowZhanLingT()
{
	static GameEngine* ge = GetGameEngine();
	show_zhanling_t_ = ge->getTickCount() - show_zhanling_cd_ + show_zhanling_delay_;
}

