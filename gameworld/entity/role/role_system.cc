#include "StdAfx.h"
#include "role_system.h"
#include "entity/actor/actor.h"
#include "db/role_data.h"
#include "protocol/protos/base_proto.h"
#include "ai/ai.h"
#include "wing/wing_system.h"
#include "title/title_system.h"
#include "stone/stone_system.h"
#include "move/move_system.h"
#include "zhuling/zhuling_system.h"
#include "item/equip/equip_system.h"

RoleSystem::RoleSystem(Actor* actor)
:actor_(actor)

{
	isload_ = false;
	data_ = new RoleDatas();
	memset(roles_, 0, sizeof(Role*)*MAX_ROLE);
}

RoleSystem::~RoleSystem()
{
	SafeDelete(data_);
}

void RoleSystem::Destroy()
{
	EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < data_->role_count; ++i)
	{
		em->DestroyEntity(role_hdl_[i]);
		roles_[i] = NULL;
	}
}

void RoleSystem::Init(DataPacketReader& reader)
{
	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init rolesystem.");
		return;
	}
	if (reader.getAvaliableLength() != sizeof(RoleDatas))
	{
		OutputMsg(rmError, "rolesystem db data len err. actor:%d, %d,%d", actor_->GetActorId(), reader.getAvaliableLength(), sizeof(RoleDatas));
		return;
	}

	if (actor_->CheckInitStep(Actor::InitFlagType_Role))
		return;

	reader.readBuf(data_, sizeof(RoleDatas));
	OutputMsg(rmTip, "OnDbRetRole, rolecount:%d", data_->role_count);
	if (data_->role_count <= 0)
	{
		OutputMsg(rmError, "OnDbRetRole, error rolecount");
		return;
	}

	EntityMgr *em = GetGameEngine()->GetEntityMgr();

	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = (Role*)em->CreateEntity(EntityType_Role, role_hdl_[i]);
		if (!role)
		{
			OutputMsg(rmError, "create role error. actor:%d", actor_->GetActorId());
			return;
		}
		if (!role->Init(actor_, &data_->roles[i]))
		{
			em->DestroyEntity(role_hdl_[i]);
			OutputMsg(rmError, "init role error. actor:%d", actor_->GetActorId());
			return;
		}
		roles_[i] = role;
	}

	UpdateTotalPower();

	isload_ = true;
	actor_->OnFinishInitStep(Actor::InitFlagType_Role);
}

void RoleSystem::Save(ActorBasicData* basicData)
{
	if (!isload_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveRole));
	pack << (ActorId)actor_->GetActorId();

//	EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role)
		{
			OutputMsg(rmError, "onSave get role error. actor:%d", actor_->GetActorId());
			return;
		}

		role->OnSave();
	}
	//技能相关 todo

	//OutputMsg(rmTip, "SaveRole %d, role count:%d", basicData->actor_id, data_->role_count);
	pack.writeBuf(data_, sizeof(RoleDatas));
	db->flushProtoPacket(pack);
}

void RoleSystem::OnEnterGame()
{
	//下发数据
	UpdateInfo();

	OutputMsg(rmTip, "rolesystem onEnter roledata:%d %d %d %d %lf\n",
		data_->role_count,
		data_->roles[0].id,
		data_->roles[0].job,
		data_->roles[0].sex,
		data_->roles[0].power);
}

void RoleSystem::OnLevelUp()
{
//	EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role)
			return;

		role->OnLevelUp();
	}
}

void RoleSystem::OnEnterScene()
{
	Scene* scene = actor_->GetScene();
	Point point = actor_->GetPosition();
	Grid pos(point);

	Role* roles_job[JobType_Max] = {0};
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role) continue;
		int job = role->GetJob();
		if (job >= 0 && job < JobType_Max)
			roles_job[job] = role;
	}
	
	int last_dir = 0; bool find_leader = false;
	for (int i = 0; i < JobType_Max; ++i)
	{
		Role *role = roles_job[i];
		if (!role)
			continue;

		if (find_leader) {
			int rdir = wrand(8);
			while (rdir == last_dir) // 只随两次才可以这么写
				rdir = wrand(8);

			last_dir = rdir;

			int vx, vy;
			getDir(rdir, vx, vy);
			pos.x += vx;
			pos.y += vy;
			if (scene->CanMove(pos)) {
				point = pos.ToPoint();
			}
		} else {
			find_leader = true;
		}
		scene->EnterScene(role, point.x, point.y, true);//确保精度,用像素进入场景
	}
}

void RoleSystem::OnExitScene()
{
	Scene* scene = actor_->GetScene();
	//static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role)
			continue;

		scene->ExitScene(role);
	}
}

void RoleSystem::OnRelive() {
	Scene* scene = actor_->GetScene();
	Point point = actor_->GetPosition();
	Grid pos(point);

	Role* roles_job[JobType_Max] = { 0 };
	for (int i = 0; i < data_->role_count; ++i) {
		Role *role = roles_[i];
		if (!role) continue;
		int job = role->GetJob();
		if (job >= 0 && job < JobType_Max)
			roles_job[job] = role;
	}

	int last_dir = 0; bool find_leader = false;
	for (int i = 0; i < JobType_Max; ++i) {
		Role *role = roles_job[i];
		if (!role)
			continue;

		if (find_leader) {
			int rdir = wrand(8);
			while (rdir == last_dir) // 只随两次才可以这么写
				rdir = wrand(8);

			last_dir = rdir;

			int vx, vy;
			getDir(rdir, vx, vy);
			pos.x += vx;
			pos.y += vy;
			if (scene->CanMove(pos)) {
				point = pos.ToPoint();
			}
		} else {
			find_leader = true;
		}
		role->GetMoveSystem()->InstantMove(point);
	}
	Recover();
}

void RoleSystem::On1sTick(int64_t curr_t)
{
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role)
			continue;

		role->GetWingSystem()->On1sTick(curr_t);
	}
}

void RoleSystem::Recover()
{
	//static EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role)
			continue;
		bool last_death = role->IsDeath();
		
		role->ChangeHp(role->GetMaxHp());
		role->ChangeMp(role->GetMaxMp());
		role->OnRelive();
		if ( last_death && !role->GetSendEntity()) {
			Scene* scene = role->GetScene();
			if (scene) scene->BroadcastAppear(role);
		}
	}
}

Role* RoleSystem::GetRoleByJob(int job)
{
	EntityMgr *em = GetGameEngine()->GetEntityMgr();
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = (Role*)em->GetEntity(role_hdl_[i]);
		if (role && role->GetJob() == job)
			return role;
	}
	return NULL;
}

Role* RoleSystem::GetRoleById(int id)
{
	if (id < 0 || id >= MAX_ROLE) return NULL;
	EntityMgr *em = GetGameEngine()->GetEntityMgr();
	Role* role = (Role*)em->GetEntity(role_hdl_[id]);
	if (role)
		return role;

	return NULL;
}

RoleData* RoleSystem::GetRoleData(int roleid)
{
	if (roleid < 0 || roleid >= MAX_ROLE) return NULL;
	
	return &(data_->roles[roleid]);
}

void RoleSystem::CreateRole(int job, int sex)
{
	int count = data_->role_count;
	if (count >= MAX_ROLE)
		return;
	// 创建数据
	RoleData* data = &data_->roles[count];
	memset(data, 0, sizeof(RoleData));
	data->id = count;
	data->job = job;
	data->sex = sex;

	// 创建实体
	Role *role = (Role*)GetGameEngine()->GetEntityMgr()->CreateEntity(EntityType_Role, role_hdl_[count]);
	if (!role)
	{
		OutputMsg(rmError, "create role error. actor:%d", actor_->GetActorId());
		memset(data, 0, sizeof(RoleData));
		return;
	}
	if (!role->Init(actor_, &data_->roles[count]))
	{
		OutputMsg(rmError, "init role error. actor:%d", actor_->GetActorId());
		GetGameEngine()->GetEntityMgr()->DestroyEntity(role_hdl_[count]);
		memset(data, 0, sizeof(RoleData));
		return;
	}
	roles_[count] = role;
	data_->role_count = count + 1;
	// 更新信息
	UpdateInfo();
	// 保存数据
	actor_->SaveDb();
	// 进入场景
	role->setCanChangeCamp(false);
	role->SetCamp(roles_[0]->GetCamp());
	if (role->GetAI() && roles_[0]->GetAI()) {
		role->GetAI()->setPassivity(roles_[0]->GetAI()->getPassivity());
	}
	actor_->GetScene()->EnterScene(role);
	role->setCanChangeCamp(true);

	ScriptValueList paramList;
	actor_->InitActorEventParams(paramList, aeCreateRole);
	paramList << count;
	actor_->OnEvent(&paramList);
}

bool RoleSystem::WriteRolesData(DataPacket &pack)
{
	pack << short(data_->role_count);
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (!role)
			break;
		role->WriteData(pack);
	}
	return true;
}

bool RoleSystem::CreateCloneData(DataPacket &pack, int attrper)
{
	pack << short(data_->role_count);
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (!role)
			break;
		role->WriteData(pack, true, attrper);
	}
	return true;
}

bool RoleSystem::IsAllDie()
{
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (!role)
			break;
		if (!role->IsDeath()) return false;
	}
	return true;
}

void RoleSystem::UpdateTotalPower()
{
	//如果是初始化的时候，就不触发战斗力变化的事件了
	if (actor_->IsInited())
		OnPowerChangeEvent();
	
	//更新排行榜数据
	UpdateRank();
}

void RoleSystem::OnPowerChangeEvent()
{
	ScriptValueList params;
	params << actor_;
	params << aeFightPower;
	params << roles_[0]->GetRankPower();
	actor_->OnEvent(&params);
}


void RoleSystem::GetRoles(Role **list)
{
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = roles_[i];
		list[i] = role;
	}
}

void RoleSystem::ReCalcAttr()
{
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (!role)
		{
			OutputMsg(rmError, "get role error.");
			break;
		}
		role->CalcAttributes();
	}
}

void RoleSystem::ReCalcExAttr()
{
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (!role)
		{
			OutputMsg(rmError, "get role error.");
			break;
		}
		role->CalcExAttributes();
	}
}

void RoleSystem::ReCalcBattleAttr()
{
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role* role = roles_[i];
		if (role) {
			role->CalcBattleAttributes();
		}
	}
}
void RoleSystem::WriteRoleBattleInfo(DataPacket& pack)
{
	//for (int i = 0; i < data_->role_count; ++i)
	//{
		Role* role = roles_[0];
		if (role) {
			role->pushBattleComparison(pack);
		}
	//}
}
void RoleSystem::UpdateInfo()
{
	ActorPacket Ap;
	DataPacket& pack = actor_->AllocPacket(Ap);
	pack << (unsigned char)(Protocol::CMD_Base);
	pack << (unsigned char)(Protocol::sBaseCmd_RoleData);
	WriteRolesData(pack);
	Ap.flush();
}

void RoleSystem::UpdateRank(void)
{
	
	auto basic_data = const_cast<ActorBasicData*>(actor_->GetBasicData());
	//初始化累加数据
	basic_data->total_power = 0;
	basic_data->rank_power = 0;
	basic_data->total_wing_power = 0;
	basic_data->total_loongsoul_level = 0;
	basic_data->total_wing_lv = 0;
	basic_data->total_tujian_power = 0;
	basic_data->total_equip_power = 0;
	basic_data->total_stone_level = 0;
	basic_data->total_zhuling_level = 0;
	static BattleAttribute attrs;
	for (int i = 0; i < data_->role_count; ++i)	{
		Role* role = roles_[i];
		if (!role) break;
		//总战力
		basic_data->total_power += static_cast<int64_t>( role->GetAttrs().GetPower() );
		//排行榜总战力
		basic_data->rank_power += static_cast<int64_t> ( role->GetRankPower() );
		{//算翅膀总战力
			const Attribute& a = role->GetWingSystem()->GetBattleAttr();
			attrs.CalcBattleAttribute(a, role->GetJob());
			attrs.CalcPower();
			basic_data->total_wing_power += (long long int)attrs.GetPower();
		}
		//龙魂总等级
		basic_data->total_loongsoul_level += role->GetData()->loogsoul_data.level;
		//翅膀总等级
		auto wing_data = role->GetWingSystem()->GetWingData();
		if (wing_data->openStatus) {
			basic_data->total_wing_lv += (wing_data->level + 1);
		}
		//图鉴的战斗力
		attrs.CalcBattleAttribute(*(actor_->GetActorsystemAttr(attrTuJian)), role->GetJob());
		attrs.CalcPower();
		basic_data->total_tujian_power += static_cast<int64_t>( attrs.GetPower() ) ;
		{//算装备评分战力
			Attribute temp_attr; const Attribute& equip_attr = role->GetEquipSystem()->GetBattleAttr();
			temp_attr[Attribute::atHpMax] = equip_attr[Attribute::atHpMax];
			temp_attr[Attribute::atAtk] = equip_attr[Attribute::atAtk];
			temp_attr[Attribute::atDef] = equip_attr[Attribute::atDef];
			temp_attr[Attribute::atRes] = equip_attr[Attribute::atRes];
			temp_attr.SetExtraPower(equip_attr.GetExtraPower());
			attrs.SetBattleAttribute(temp_attr);
			attrs.CalcPower();
			basic_data->total_equip_power += static_cast<int64_t> ( attrs.GetPower() );
		}
		{//宝石(精炼)总等级
			auto ret = role->GetStoneSystem()->GetStoneData();
			for (size_t j = 0; j < ret.size(); ++j) {
				basic_data->total_stone_level += ret[j];
			}
		}
		{//铸造总等级
			auto ret = role->GetZhulingSystem()->GetZhulingData();
			for (size_t j = 0; j < ret.size(); ++j) {
				basic_data->total_zhuling_level += ret[j];
			}
		}
		//各职业的战力
		switch (role->GetJob()) {
			case JobType_Warrior: {//战士战力
				basic_data->warrior_power = (int64_t)role->GetAttrsCache()->GetPower();
				break;
			}
			case JobType_Mage: {//法师战力
				basic_data->mage_power = (int64_t)role->GetAttrsCache()->GetPower();
				break;
			}
			case JobType_Taoist: {//道士战力
				basic_data->taoistpriest_power = (int64_t)role->GetAttrsCache()->GetPower();
				break;
			}
		}
	}//end for

}

void RoleSystem::InstantMove(int x, int y)
{
	Point tar(Grid(x, y).ToPoint());
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (role && !role->IsDeath())
		{
			role->SetTarget(nullptr);
			role->GetMoveSystem()->InstantMove(tar);
			if (role->GetBattlePet() && role->GetBattlePet()->GetMoveSystem())
			{
				role->GetBattlePet()->SetTarget(nullptr);
				role->GetBattlePet()->GetMoveSystem()->InstantMove(tar);
			}
		}
	}
}

Role* RoleSystem::GetLiveByPower()
{
	Role* powerRole = NULL;
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role || role->IsDeath()) continue;

		if (powerRole == NULL || 
			role->GetAttrs().GetPower() > powerRole->GetAttrs().GetPower())
			powerRole = role;
	}
	return powerRole;
}

Role* RoleSystem::GetRandomLiveRole()
{
	int index = rand() % data_->role_count;
	for (int i = index; i < index + data_->role_count; ++i)
	{
		Role *role = roles_[i % data_->role_count];
		if (!role || role->IsDeath()) continue;
		return role;
	}
	return nullptr;
}

Role* RoleSystem::GetLiveByJob()
{
	Role *job_role[JobType_Max];
	memset(job_role, 0, sizeof(job_role));
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if (!role || role->IsDeath()) continue;
		int job = role->GetJob();
		if(job >= 0 && job < JobType_Max)
			job_role[job] = role;
	}
	if (job_role[JobType_Warrior]) return job_role[JobType_Warrior];
	if (job_role[JobType_Mage]) return job_role[JobType_Mage];
	if (job_role[JobType_Taoist]) return job_role[JobType_Taoist];
	if (job_role[JobType_None]) return job_role[JobType_None];
	return nullptr;
}

int RoleSystem::GetDeathCount()
{
	int count = 0;
	for (int i = 0; i < data_->role_count; ++i)
	{
		Role *role = roles_[i];
		if(!role) continue;
		if (role->IsDeath()) 
			count++;
	}

	return count;
}
