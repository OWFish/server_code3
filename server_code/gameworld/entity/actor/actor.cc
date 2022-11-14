#include "StdAfx.h"
#include "actor.h"
#include "actor_data_mgr.h"
#include "actor_asyn_mgr.h"
#include "role/role.h"
#include "role/role_system.h"
#include "protocol/system_cmd_def.h"
#include "protocol/protos/base_proto.h"
#include "scene/fuben.h"
#include "netmsg_dispatcher.h"

#include "item/container/item_bag.h"
#include "item/container/equip_bag.h"
#include "item/item_config.h"
#include "item/item.h"
#include "mail/mail_system.h"
#include "zhuansheng/zhuansheng_system.h"
#include "store/store_system.h"
#include "item/container/depot_system.h"
#include "item/container/bag_config.h"
#include "neigongsystem/neigong_config.h"
#include "title/title_system.h"
#include "systems/guild/guild_system.h"
#include "systems/guild/guild.h"
#include "protos/zhanling_proto.h"
#include "systems/offlinemsg/msg_system.h"
#include "systems/actorexring/actor_ex_ring_system.h"
#include "systems/togetherhit/together_hit_system.h"
#include "systems/imba/imbasystem.h"
#include "systems/godweapon/godweaponsystem.h"
#include "systems/cswar/war_system.h"
#include "ai/ai_mgr.h"
#include "ai/ai.h"
#include "../redis/RedisConnect.h"
#ifndef _MSC_VER
#include <sys/time.h>
#endif

using namespace InterSrvComm::DbServerProto;
using namespace InterSrvComm::GameWorldProto;

// 时间波动，用于每天24点定时分散用
#define TIME_FLUCTUATE	20
#define DEFAULT_ENTER_SCENE 11
#define DEFAULT_ENTER_POSX 63
#define DEFAULT_ENTER_POSY 47
#define WEE_HOURS_TIME (6 * 60 * 60)
#define SUPER_VIP 3
#define SAVE_DB_CACHE_INTERVAL 10000

//静态函数，用于初始化更新的指针
//那些属性需要发送到客户端
UpdateMask*					Actor::broadcastMask_ = NULL;

int	Actor::save_db_interval_ = SAVE_DB_CACHE_INTERVAL;

int Actor::show_zhanling_cd_ = 0;
int Actor::show_zhanling_delay_ = 0;


//这里是玩家需要更新的属性
void Actor::InitBroadcastMask()
{
	if (!broadcastMask_)
	{
		broadcastMask_ = new UpdateMask();
	}

	broadcastMask_->SetMask(P_LEVEL);
	broadcastMask_->SetMask(P_MAXHP);
	broadcastMask_->SetMask(P_MAXMP);
	broadcastMask_->SetMask(P_HP);
	broadcastMask_->SetMask(P_MP);
	broadcastMask_->SetMask(P_MOUNT);
	broadcastMask_->SetMask(P_WING);
	broadcastMask_->SetMask(P_WEAPON);
	broadcastMask_->SetMask(P_SPIRIT);
	broadcastMask_->SetMask(P_MODELID);
	broadcastMask_->SetMask(P_ICON);
	broadcastMask_->SetMask(P_STATE);//实体的状态
	broadcastMask_->SetMask(P_SOCIAL);//实体的社会关系状态
	broadcastMask_->SetMask(P_ATTACK_SPEED);
	broadcastMask_->SetMask(P_SPEED);

	broadcastMask_->SetMask(P_TEAM_ID);
	broadcastMask_->SetMask(P_PK_MOD);
	broadcastMask_->SetMask(P_QQ_VIP);

	broadcastMask_->SetMask(P_FOOT_EFFECT); // 足迹
	broadcastMask_->SetMask(P_BUBBLE);

	broadcastMask_->SetMask(P_HAIR_MODEL); //时装帽
	broadcastMask_->SetMask(P_ACTOR_STATE); //玩家状态
	broadcastMask_->SetMask(P_VOCATION);

	broadcastMask_->SetMask(P_STAND_POINT);	 //立场
	broadcastMask_->SetMask(P_CHANGE_MODEL); //变身模型

	broadcastMask_->SetMask(P_STRONG_EFFECT);	//强化特效
	broadcastMask_->SetMask(P_STAGE_EFFECT); //装备品阶特效
	broadcastMask_->SetMask(P_GUILD_ID);		//帮派id
	broadcastMask_->SetMask(P_RECHARGE);	//充值金额

	//这些属性不需要更新
	UpdateMask::SetForbid(P_DIR, true);
	UpdateMask::SetForbid(P_POS_X, true);
	UpdateMask::SetForbid(P_POS_Y, true);
}


Actor::Actor(): Inherited()
	, m_t1s(1000), m_t1minute(60000), db_timer_(SAVE_DB_CACHE_INTERVAL),
	clear_vest_timer_(1000)
	, last_battle_(0), last_pk_(0), last_attacker_(0)
	, init_flag_(0),is_image_(0), image_end_time_(0), net_pack_id_(0), err_net_pack_id_(0)
{
	SetType(EntityType_Actor);
	account_id_ = 0;    //帐户的ID
	enter_fb_sid_ = 0; //进入副本前的位置
	enter_fb_x_ = 0;    //进入副本前x的坐标
	enter_fb_y_ = 0;  //进入副本前的y的坐标
	unreload_map_sid_ = unreload_map_x_ = unreload_map_y_ = 0;
	new_pet_x_ = new_pet_y_ = -1;
	force_pet_pos_ = false;

	account_name_[0] = 0;
	first_login_ = false;
	logined_ = false;
	//property_.SetIntProp(PROP_ACTOR_VIPFLAG, 0);

	show_name_[0] = 0;
	static GameEngine* ge = GetGameEngine();
	net_packs_ = ge->global_var_->dp_list_alloc_.get();
	net_packs_->reserve(32);

	_STRNCPY_A(last_login_ip_, "0.0.0.0");
	pf_[0] = 0;

	attack_list_.clear();

	cw_serverid_ = 0;
	cw_fbhdl_ = 0;
	cw_sceneid_ = 0;
	cw_x_ = 0;
	cw_y_ = 0;
	cw_static_sceneid_ = 0;
	cw_static_x_ = 0;
	cw_static_y_ = 0;
	waitForCross_ = false;

	comm_fb_hdl_ = 0;
	comm_sceneid_ = 0;
	comm_x_ = 0;
	comm_y_ = 0;

	deny_see_actor_ = false;
	can_see_ = true;

	last_check_door_x_ = 0;
	last_check_door_y_ = 0;

	protect_skill_id_ = 0;
	protect_skill_level = 0;
	flamestamp_lv_ = 0;
	memset(flamestamp_skill_lv_, 0, sizeof(flamestamp_skill_lv_));
	
//新增
	//basic_data_ = new ActorBasicData();
	basic_data_ = NULL;
	title_sys_ = new TitleSystem(this);
	role_sys_ = new RoleSystem(this);
	var_sys_ = new LuaVarSystem(this);
	item_bag_ = new ItemBag(this);
	equip_bag_ = new EquipBag(this);
	mail_sys_ = new MailSystem(this);
	zhuansheng_sys_ = new ZhuanShengSystem(this);
	store_sys_ = new StoreSystem(this);
	depot_ = new Depot(this);
	guild_sys_ = new GuildSystem(this);
	msg_sys = new MsgSystem(this);
	actor_ex_ring_sys_ = new ActorExRingSystem(this);
	together_hit_sys_ = new TogetherHitSystem(this);
	imba_sys_ = new ImbaSystem(this);
	god_weapon_sys_ = new GodWeaponSystem(this);
	war_sys_ = new WarSystem(this);
	//ZeroMemory(basic_data_, sizeof(ActorBasicData));

	show_zhanling_t_ = 0;
	zhanling_id_ = 0;
	zhanling_lv_ = -1;
	zhanling_talent_effid_ = 0;
	gm_level_ = 0;
	toge_lv_ = 0;
	yupei_lv_ = 0;
	new_world_boss_attr_.Reset();
	kick_relogin_ = false;
	ClearPackHideSet();
}

Actor::~Actor()
{

}

void Actor::ClearPackHideSet() {
	need_hide_pack_ = false;
	need_pack_list_.clear();
}

void Actor::OnDestroy()
{
	static GameGateMgr* mgr = ServerInstance()->GetGateManager();
	GameGate* gate = (GameGate*)mgr->GetGate(netid_.gate_id_);

	if (gate) gate->AddFreeList(*net_packs_, 0, GameGate::GameThread);

	net_packs_->clear();

	//这里是玩家的一些内存的释放工作
	role_sys_->Destroy();
	//deal_sys_.Destroy();
	//team_sys_.Destroy();
	//guild_sys_.Destroy();
	//equip_sys_.Destroy();
	//bag_sys_.Destroy();
	//depot_mgr_sys_.Destroy();//[改]
	//pet_sys_.Destroy();
	//dress_sys_.Destroy();
	//war_sys_.Destroy();
	//pet_cross_sys_.Destroy();
	//marry_sys_.Destroy();

	Inherited::OnDestroy();

	net_packs_->clear();
	static GameEngine* ge = GetGameEngine();
	ge->global_var_->dp_list_alloc_.release(net_packs_);
	net_packs_ = NULL;
	// 新增
	//SafeDelete(basic_data_);
	SafeDelete(depot_);

	SafeDelete(role_sys_);
	SafeDelete(var_sys_);
	SafeDelete(item_bag_);
	SafeDelete(equip_bag_);
	SafeDelete(mail_sys_);
	SafeDelete(zhuansheng_sys_);
	SafeDelete(store_sys_);
	SafeDelete(title_sys_);
	SafeDelete(guild_sys_);
	SafeDelete(msg_sys);
	SafeDelete(actor_ex_ring_sys_);
	SafeDelete(together_hit_sys_);
	SafeDelete(imba_sys_);
	SafeDelete(god_weapon_sys_);
	SafeDelete(war_sys_);
}

void Actor::Onlogin(NetId netid, ActorId actorId, int accountId, int gm_level)
{
	STATIC_ASSERT(sizeof(ActorId) == sizeof(unsigned int));
	DBClient* db = ServerInstance()->GetDbClient(serverId_);

	if (!db) return;

	//SetUIntProp(P_ID, actorId);
	SetActorId(actorId);

	netid_ = netid;

	account_id_ = accountId;

	if (gm_level > 0) //玩家的GM等级
	{
		AddBitState(ebsGm);
	}
	else
	{
		RemoveBitState(ebsGm);
	}

	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList params;
	params << actorId;
	params << this;
	luaScript.Call("OnLogin", &params, &params);

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();

#pragma pack(push, 1)
	static struct HDR_DATA {
		ActorId id;
		bool isImage;
	} hdr_data;
#pragma pack(pop)
	hdr_data.id = actorId;
	hdr_data.isImage = IsImage();
	db->SendDbServerData(MAKEINT16(siActor, dcQuery), hdr_data);
	em->OnActorLogin(this);
	OutputMsg(rmTip, "user Login, actorid=%d,accountid=%d,serverid=%d",
	          actorId, account_id_, serverId_);
}

void Actor::OnFirst()
{
	// 默认是写在数据库的初始值里, 读取配置修改
	basic_data_->bag_grid = BagConfigPool::GetBaseSize();
	equip_bag_->SetCapacity(basic_data_->bag_grid);

	//int firstjob = role_sys_->GetRoleById(0)->GetJob();
	//GetEquipBag()->AppendItem(100001 + firstjob * 1000, 1, "create role equip");
	//GetEquipBag()->AppendItem(120001 + firstjob * 1000, 1, "create role equip");

	//初次进入游戏，在脚本中执行某些初始化操作
	ScriptValueList p;
	p << this;
	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	bool ret = lua.Call("MyOnFirstEnterGame", &p, NULL);
	if (!ret)
	{
		//脚本错误，将以模态对话框的形式呈现给客户端
		const RefString& s = lua.getLastErrorDesc();
		SendTipmsg((const char*)s, ttDialog);
	}

	ScriptValueList paramList;
	InitActorEventParams(paramList, aeUserFirstLogion);
	OnEvent(&paramList);
}

//成功击中
//void Actor::OnAttackOther(Animal* et)
//{
	//Inherited::OnAttackOther(et);

	////AddState(esStateBattle);

	//ScriptValueList args;
	////InitActorEventParams(args, aeStartBattle);
	//OnEvent(&args);

	//static GameEngine* ge = GetGameEngine();
	//last_battle_ = ge->getTickCount();

	//if (et && et->GetType() == enActor)
	//{
	//	last_pk_ = last_battle_;
	//	AddState(esPkState);

	//	ScriptValueList args1;
	//	//InitActorEventParams(args1, aeStartPkState);
	//	OnEvent(&args1);

	//	int count = attack_back_.count();
	//	for (int i = count - 1; i >= 0; i--)
	//	{
	//		if (attack_back_[i].handle_ == et->GetHandle())
	//		{
	//			attack_back_[i].time_ = 15+ge->getMiniDateTime();
	//			break;
	//		}
	//	}
	//}
	//
	//PostCheckPropertyMsg();
//}

//void Actor::OnAttacked(Animal* et)
//{
	/*
	Inherited::OnAttacked(et);

	AddState(esStateBattle);

	ScriptValueList args;
	//InitActorEventParams(args, aeStartBattle);
	OnEvent(&args);

	static GameEngine* ge = GetGameEngine();
	last_battle_ = ge->getTickCount();

	int etType = et->GetType();
	if (et && (etType == enActor || (etType== enMonster && ((Monster*)et)->is_pet_)))
	{
		last_pk_ = last_battle_;
		AddState(esPkState);

		ScriptValueList args1;
		//InitActorEventParams(args1, aeStartPkState);
		OnEvent(&args1);

		EntityHandle new_actor;
		if (etType == enActor)
			new_actor = et->GetHandle();
		else
			new_actor = ((Monster*)et)->GetOwner();

		// 更新攻击自己的玩家列表
		if (HasBitState(ebsAttackLog))
		{
			EntityHandle* eh = attack_list_;
			for (int i = attack_list_.count() - 1; i >= 0; i--)
			{
				if (eh[i] == new_actor)
				{
					attack_list_.remove(i);
					break;
				}
			}

			if (attack_list_.count() >= MAX_ATTACK)
				attack_list_.remove(0);

			attack_list_.add(new_actor);
		}

		//特殊场景中，和平模式，更新可以反击的目标
		Scene* scene = GetScene();
		if (!scene) return;

		SceneConfig* sceneConf = scene->GetSceneConf();
		if (sceneConf && sceneConf->special_peaceful_ && GetIntProp(P_PK_MOD) == fpSpecialPeaceful)
		{
			int count = attack_back_.count();
			bool find = false;
			for (int i = count - 1; i >= 0; i--)
			{
				if (attack_back_[i].handle_ == new_actor)
				{
					attack_back_[i].time_ = 15 + ge->getMiniDateTime();
					find = true;
					break;
				}
			}
			if (!find)
			{
				attack_back_.reserve(count + 1);
				attack_back_.trunc(count + 1);

				AttackBack& newAttackBack = attack_back_[count];
				newAttackBack.handle_ = new_actor;
				newAttackBack.time_ = 15 + ge->getMiniDateTime();

				UpdateNameClr_BeAttacked(GetHandle(), new_actor);
			}
		}
	}

	//先获取当前target
	EntityHandle target = GetTarget();
	//设置target
	SetTarget(et->GetHandle());
	GetWingSystem().OnUseBeAttack();
	GetArtifactSystem().OnUseSkill(0, 0, stBeAttackTouch);

	//技能结束后设置回来
	SetTarget(target);

	PostCheckPropertyMsg();
	*/
//}

void Actor::AddProtectSkill(int skillId, int level)
{
	protect_skill_id_ = skillId;
	protect_skill_level = level;
}
void Actor::ProtectSkillEffect()
{
	/*
	if (protect_skill_id_ == 0) return;

	static SkillConfPool* pool = SkillConfPool::config_;
	const SkillConf* conf = pool->GetSkillData(protect_skill_id_);

	if (!conf) return;
	const SkillLvlConf* lvlConf = pool->GetSkillLevelData(protect_skill_id_, protect_skill_level);

	if (!lvlConf) return;

	unsigned int random = wrand(10000);
	if (((unsigned int)(lvlConf->rateParam_ * 10000)) < random) return;

	this->GetSkillSystem().UseSkill(protect_skill_id_, 0, 0, false, protect_skill_level);
	*/
}

int Actor::ProtectSkillFightValue()
{
	/*
	if (protect_skill_id_ <= 0) return 0;

	static SkillConfPool* pool = SkillConfPool::config_;
	const SkillConf* conf = pool->GetSkillData(protect_skill_id_);

	if (!conf) return 0;
	const SkillLvlConf* lvlConf = pool->GetSkillLevelData(protect_skill_id_, protect_skill_level);

	if (!lvlConf) return 0;

	return lvlConf->fightValue_;
	*/
	return 0;
}

void Actor::SetImage(bool isImage)
{
	auto em = GetGameEngine()->GetEntityMgr();
	if (!is_image_ && isImage)
		em->AddImage();
	if (is_image_ && !isImage)
		em->DecImage();

	is_image_ = isImage; 
}

void Actor::NoticeRelogin() {
#pragma pack(push, 1)
	static uint8_t data[3] = { Protocol::CMD_Login, 1,3 };
#pragma pack(pop)
	SendData((const char*)data, sizeof(data));
}

void Actor::CloseImageActor()
{
	if (!IsImage())
		return;

	GetGameEngine()->GetEntityMgr()->DestroyEntity(entity_handle_);
	GetGameEngine()->GetEntityMgr()->DecImage();
}

void Actor::CloseActor(const char* reason, bool notic_gate)
{
	if (IsImage()) {
		OutputMsg(rmTip, "Actor::CloseActor aid:%d is image", GetActorId());
		CloseImageActor();
		return;
	}
	//首先要判断handle是否合法，防止网关发多个包来踢玩家下线引起问题
	static GameEngine* ge = GetGameEngine();
	static EntityMgr* em = ge->GetEntityMgr();

	PreCloseActor();

	logout_t_ = ge->getMiniDateTime();

	// 保存脚本数据,和其他的一些处理
	if (inited_)
	{
		ScriptValueList params;
		InitActorEventParams(params, aeUserLogout);
		params << actor_id_;
		params << int(logout_t_ - login_t_);
		OnEvent(&params);
	}

	//static FightMgr& fightMgr = GetGameEngine()->GetFightMgr();
	//int x, y;
	//GetPosition(x,y);
	//basic_data_->field_posX = entity_pos_.point_pos.x;
	//basic_data_->field_posY = entity_pos_.point_pos.y;
	//this->enter_fb_x_ = x;
	//this->enter_fb_y_ = y;
	// 只有创建好的实体才能够存盘，没有创建好的玩家不能存盘
	if (inited_)
	{
		guild_sys_->OnLogout();

		SaveDb(true);
	}
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList params;

	//清理玩家动态变量
	//params.clear();
	params << actor_id_;
	params << this;

	// 脚本回调
	luaScript.Call("OnLogout", &params, &params);

	// 给网关发送消息关闭连接
	if (notic_gate)
	{
		static GateManager* gatemgr = ServerInstance()->GetGateManager();
		gatemgr->GetGate(netid_.gate_id_)->PostCloseUser(netid_, GetAccountId(), 
									"Actor::CloseActor[notic_gate]", GetActorId());
	}

	em->SendActorOnline(actor_id_, 0, serverId_);

	OutputMsg(rmTip, ("[%s]Logout, actorID=%d, account=%d, reason=%s, notic=%s, gate=%d"),
		entity_name_, actor_id_, account_id_, reason ? reason : "", notic_gate ? "notice" : "no notice", netid_.gate_id_);

	//ge->ChannelUser(ciChannelCamp, GetIntProp(P_CAMP), this, 1);

	em->DestroyEntity(entity_handle_);
}

#if (defined _DEBUG) && (defined _MSC_VER)
LONG Actor::PacketAlloced = FALSE;
const char* Actor::PacketAllocFile = NULL;
int Actor::PacketAllocLine = 0;
#endif


void InitActorPack(ActorPacket& pack, DataPacket* dp, NetId netid)
{
	if (!dp) return;

	size_t len = dp->getLength();
	size_t needLen = dp->getPosition() + sizeof(DATAHEADER);

	if (needLen > len)
	{
		len = (size_t)(len * 1.33);	// 每次扩展多1/3
		dp->reserve(__max(len, needLen));
	}

	DATAHEADER* hdr = (DATAHEADER*)dp->getOffsetPtr();		// 保留协议头部分

	pack.pos_ = dp->getPosition();

	hdr->tag = TAG_VALUE;
	dp->adjustOffset(sizeof(DATAHEADER));
#pragma pack(push, 1)
	static struct HDR_DATA
	{
		const uint16_t type_;
		NetId	netid_;
		HDR_DATA() : type_(GW_DATA) {}
	} hdr_data;
#pragma pack(pop)
	hdr_data.netid_ = netid;
	dp->writeBuf(&hdr_data, sizeof(hdr_data));
}

#ifdef _DEBUG
DataPacket& Actor::_AllocPacket(ActorPacket& pack, const char* file, int line)
#else
DataPacket& Actor::AllocPacket(ActorPacket& pack)
#endif
{
#if (defined _DEBUG) && (defined _MSC_VER)

	if (InterlockedCompareExchange(&PacketAlloced, TRUE, FALSE))
	{
		OutputMsg(rmError, "_AllocPacket error: id:%d,%s,%d", actor_id_, file, line);
		OutputMsg(rmError, "last alloc: %s,%d", PacketAllocFile, PacketAllocLine);
		Assert(FALSE);
	}

	PacketAllocFile = file;
	PacketAllocLine = line;
#endif


	DataPacket *dp = NULL;

	static GameGateMgr* mgr = ServerInstance()->GetGateManager();
	if (!IsImage() && IsInited())
	{
		GameGate* logicgate = (GameGate*)mgr->GetGate(netid_.gate_id_);
		assert(logicgate);

		dp = pack.packet_ = logicgate->GetSendToGatePacket(GameGate::GameThread);
	}
	else
	{
		dp = pack.packet_ = NULL;
	}

	if (dp)
	{
		InitActorPack(pack, dp, netid_);
	}
	else
	{
		static BaseAllocator alloc("actorret");
		static DataPacket p(&alloc);
		p.setLength(0);
		return p;
	}

	return *dp;
}



void ActorPacket::flush()
{
#if (defined _DEBUG) && (defined _MSC_VER)

	if (!InterlockedCompareExchange(&Actor::PacketAlloced, TRUE, TRUE))
	{
		OutputMsg(rmError, "ActorPacket::flush error:%s, %d",
		          Actor::PacketAllocFile, Actor::PacketAllocLine);
		assert(false);
	}

	Actor::PacketAllocFile = NULL;
	Actor::PacketAllocLine = 0;
#endif

	if (packet_)
	{
		DATAHEADER* hdr = (DATAHEADER*)(packet_->getMemoryPtr() + pos_);
		int len = static_cast<int>( (packet_->getPosition() - pos_ - sizeof(*hdr)) ) ;
		assert(len <= 0xFFFF);
		hdr->len = (/*uint16_t*/uint32_t)(packet_->getPosition() - pos_ - sizeof(*hdr));
	}

#if (defined _DEBUG) && (defined _MSC_VER)
	InterlockedCompareExchange(&Actor::PacketAlloced, FALSE, TRUE);
#endif
}

void ActorPacket::rollBack()
{
#if (defined _DEBUG) && (defined _MSC_VER)

	if (!InterlockedCompareExchange(&Actor::PacketAlloced, TRUE, TRUE))
	{
		OutputMsg(rmError, "ActorPacket::rollBack error:%s, %d",
		          Actor::PacketAllocFile, Actor::PacketAllocLine);
		assert(false);
	}

	Actor::PacketAllocFile = NULL;
	Actor::PacketAllocLine = 0;
#endif
	if (packet_)
		packet_->setPosition(pos_);
#if (defined _DEBUG) && (defined _MSC_VER)
	InterlockedCompareExchange(&Actor::PacketAlloced, FALSE, TRUE);
#endif
}

void Actor::PostNetMsg(DataPacket* data, int nid)
{
	net_packs_->add(data);

	if (nid <= net_pack_id_)
	{
		err_net_pack_id_++;

		if (err_net_pack_id_ % 10 == 0)
		{
			// 先输出，后续再做其他处理，比如踢人
			OutputMsg(rmError, "actor net packet id error %d, actorid=%d, actorname=%s",
			          err_net_pack_id_, GetActorId(), GetEntityName());
		}
	}

	net_pack_id_ = nid;
}


void Actor::AddExp(int addval, const char* log)
{
	ScriptValueList p;
	p << this;
	p << addval;
	p << log;
	ScriptValueList retList;
	CallFunc("MyAddExp", &p, &retList);
}

void Actor::ChangeGold(int value, const char* log)
{
	if (value < 0 && -value > basic_data_->gold)
		return;

	long long oldvalue = basic_data_->gold;
	basic_data_->gold += value;
	if (basic_data_->gold > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->gold = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->gold < 0)
	{
		OutputMsg(rmWarning, "aid:%d, gold not enough. v:%d, ret:%d", actor_id_, value, basic_data_->gold);
		basic_data_->gold = 0;
	}

	if (log == NULL) log = "";
	//OutputMsg(rmNormal, "change gold. v:%d, ret:%d, log:%s", value, basic_data_->gold, log);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_Gold;
	msg.current = basic_data_->gold;

	SendData(msg);

	static LogSender* logger = ServerInstance()->GetLogClient();
	char extra[256] = { 0 };
	char extra2[21] = { 0 };
	char account[21] = { 0 };
	sprintf(extra, "user_level:%d,ip:%lld", basic_data_->level, basic_data_->last_login_ip);
	sprintf(extra2, "%lld", oldvalue);
	sprintf(account, "%d", value);

	//logger->LogEnconomy(actor_id_, account_name_, "gold", account, "1", value > 0 ? "earning":"expenditure",log, "",
	//	"", "", extra, extra2, GetPf(), lfDB, false, "", GetAppid(), GetPfid());

	if (value < 0)
	{
		ScriptValueList paramList;
		InitActorEventParams(paramList, aeConsumeGold);
		paramList << -value;
		OnEvent(&paramList);
	}
}

void Actor::ChangeYuanBao(int value, const char* log, bool isIgnore)
{
	if (value < 0 && -value > basic_data_->yuanbao)
		return;

	long long oldvalue = basic_data_->yuanbao;
	basic_data_->yuanbao += value;

	if (value < 0)
		basic_data_->paid -= value;

	if (basic_data_->yuanbao > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->yuanbao = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->yuanbao < 0)
	{
		OutputMsg(rmWarning, "aid:%d, yb not enough. v:%d, ret:%d", actor_id_, value, basic_data_->yuanbao);
		basic_data_->yuanbao = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change yb. v:%d, ret:%d", actor_id_, value, basic_data_->yuanbao);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_YuanBao;
	msg.current = basic_data_->yuanbao;

	SendData(msg);

	static LogSender* logger = ServerInstance()->GetLogClient();
	char extra[256] = { 0 };
	char extra2[64] = { 0 };
	char account[64] = { 0 };
	sprintf(extra, "user_level:%d,ip:%lld", basic_data_->level, basic_data_->last_login_ip);
	sprintf(extra2, "%lld", oldvalue);
	sprintf(account, "%d", value);

	logger->LogEnconomy(actor_id_, account_name_, "yb", account, "1", value > 0 ? "earning" : "expenditure", log, "",
		"", "", extra, extra2, GetPf(), lfDB/*+lfBI*/, strcmp(log, "recharge")==0? true: false, "", GetAppid(), GetPfid());


#ifdef OPENLOGDKMLOG
	static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
	if (value > 0)
	{
		dkmLog.LogAddMoney(account_id_, actor_id_, entity_name_, GetLevel(), pf_id_, basic_data_->recharge, log, value, NumericType_YuanBao);
		//tlog.LogLogout(account_id_, actor_id_, entity_name_, GetLevel(), pf_, basic_data_->recharge, (int)(logout_t_ - login_t_));
	}
	else
	{
		//tlog.LogLogout(account_id_, actor_id_, entity_name_, GetLevel(), pf_, basic_data_->recharge, (int)(logout_t_ - login_t_));
		dkmLog.LogCostMoney(account_id_, actor_id_, entity_name_, GetLevel(), pf_id_, basic_data_->recharge, log, value * (-1));
	}
#endif

	if (value < 0 && !isIgnore)
	{
		ScriptValueList paramList;
		InitActorEventParams(paramList, aeConsumeYuanbao);
		paramList << -value;
		OnEvent(&paramList);
	}
}

void Actor::ChangeEssence(int value, const char* log)
{
	if (value < 0 && -value > basic_data_->essence)
		return;

	basic_data_->essence += value;
	if (basic_data_->essence > (int)MAX_32BIT_CURRENCY_COUNT)
		basic_data_->essence = (int)MAX_32BIT_CURRENCY_COUNT;

	if (basic_data_->essence < 0)
	{
		OutputMsg(rmWarning, "aid;%d, soul not enough. v:%d, ret:%d", actor_id_, value, basic_data_->essence);
		basic_data_->essence = 0;
	}
	//OutputMsg(rmNormal, "aid:%d, change soul. v:%d, ret:%d", actor_id_, value, basic_data_->essence);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_Essence;
	msg.current = basic_data_->essence;

	SendData(msg);

	//触发修改精魄事件
	ScriptValueList paramList;
	InitActorEventParams(paramList, aeAddEssence);
	paramList << value;

	OnEvent(&paramList);
}

void Actor::ChangeFeats(int value, const char* log)
{
	if (value < 0 && -value > basic_data_->feats)
		return;

	basic_data_->feats += value;
	if (basic_data_->feats > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->feats = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->feats < 0)
	{
		OutputMsg(rmWarning, "aid;%d, feats not enough. v:%d, ret:%d", actor_id_, value, basic_data_->feats);
		basic_data_->feats = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change feats. v:%d, ret:%d", actor_id_, value, basic_data_->feats);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_Feats;
	msg.current = basic_data_->feats;

	SendData(msg);
}

void Actor::ChangeShatter(int value, const char* log)
{
	if (value < 0 && -value > basic_data_->shatter)
		return;

	basic_data_->shatter += value;
	if (basic_data_->shatter > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->shatter = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->shatter < 0)
	{
		OutputMsg(rmWarning, "aid;%d, shatter not enough. v:%d, ret:%d", actor_id_, value, basic_data_->shatter);
		basic_data_->shatter = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change shatter. v:%d, ret:%d", actor_id_, value, basic_data_->shatter);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_Shatter;
	msg.current = basic_data_->shatter;

	SendData(msg);
}

void Actor::ChangeSpcShatter(int value, const char* log)
{

	if (value < 0 && -value > basic_data_->spcshatter)
		return;

	basic_data_->spcshatter += value;
	if (basic_data_->spcshatter > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->spcshatter = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->spcshatter < 0)
	{
		OutputMsg(rmWarning, "aid;%d, spcshatter not enough. v:%d, ret:%d", actor_id_, value, basic_data_->spcshatter);
		basic_data_->spcshatter = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change spcshatter. v:%d, ret:%d", actor_id_, value, basic_data_->spcshatter);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_SpeShatter;
	msg.current = basic_data_->spcshatter;

	SendData(msg);

}

void Actor::ChangeTogeatter(int value, const char* log)
{

	if (value < 0 && -value > basic_data_->togeatter)
		return;

	basic_data_->togeatter += value;
	if (basic_data_->togeatter > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->togeatter = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->togeatter < 0)
	{
		OutputMsg(rmWarning, "aid;%d, togeatter not enough. v:%d, ret:%d", actor_id_, value, basic_data_->togeatter);
		basic_data_->togeatter = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change togeatter. v:%d, ret:%d", actor_id_, value, basic_data_->togeatter);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_Togeatter;
	msg.current = basic_data_->togeatter;

	SendData(msg);

}

void Actor::ChangeTogeatterHigh(int value, const char* log)
{

	if (value < 0 && -value > basic_data_->togeatterhigh)
		return;

	basic_data_->togeatterhigh += value;
	if (basic_data_->togeatterhigh > MAX_64BIT_CURRENCY_COUNT)
		basic_data_->togeatterhigh = MAX_64BIT_CURRENCY_COUNT;

	if (basic_data_->togeatterhigh < 0)
	{
		OutputMsg(rmWarning, "aid;%d, togeatterhigh not enough. v:%d, ret:%d", actor_id_, value, basic_data_->togeatterhigh);
		basic_data_->togeatterhigh = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change togeatterhigh. v:%d, ret:%d", actor_id_, value, basic_data_->togeatterhigh);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_TogeatterHigh;
	msg.current = basic_data_->togeatterhigh;

	SendData(msg);

}

void Actor::ChangePrestigeExp(int value, const char* log)
{

	if (value < 0 && -value > basic_data_->prestige_exp)
		return;

	int curValue = basic_data_->prestige_exp;
	basic_data_->prestige_exp += value;
	if ((unsigned int)basic_data_->prestige_exp > MAX_32BIT_CURRENCY_COUNT)
		basic_data_->prestige_exp = MAX_32BIT_CURRENCY_COUNT;

	if (basic_data_->prestige_exp < 0)
	{
		OutputMsg(rmWarning, "aid;%d, prestige_exp not enough. v:%d, ret:%d", actor_id_, value, basic_data_->prestige_exp);
		basic_data_->prestige_exp = 0;
	}
	OutputMsg(rmNormal, "aid:%d, change prestige_exp. v:%d, ret:%d", actor_id_, value, basic_data_->prestige_exp);

	Protocol::UpdateMoneyProto msg;
	msg.type = NumericType_PrestigeExp;
	msg.current = basic_data_->prestige_exp;

	SendData(msg);

	ScriptValueList paramList;
	InitActorEventParams(paramList, aeChangePrestige);
	paramList << basic_data_->prestige_exp;
	OnEvent(&paramList);

	static LogSender* logger = ServerInstance()->GetLogClient();
	char extra[256] = { 0 };
	char extra2[64] = { 0 };
	char account[64] = { 0 };
	sprintf(extra, "user_level:%d,ip:%lld", basic_data_->level, basic_data_->last_login_ip);
	sprintf(extra2, "%d", basic_data_->prestige_exp);
	sprintf(account, "%d", value);

	//logger->LogEnconomy(actor_id_, account_name_, "prestige", account, "1", value > 0 ? "earning" : "expenditure", log, "",
	//	"", "", extra, extra2, GetPf(), lfDB, false, "", GetAppid(), GetPfid());
}

int Actor::GiveItem(int id, int count, const char* log,bool showTip)
{
	if (count <= 0) return 0;
	auto conf = ItemConfigPool::GetItemConfig(id);
	if (conf == NULL)
	{
		OutputMsg(rmError, "aid:%d, give item failed. config is null. id:%d", actor_id_, id);
		return 0;
	}
	if (conf->type == ItemType_Imba)
	{
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		ScriptValueList arg;
		arg << this << id;
		if (!luaScript.Call("imbaActiveItem", &arg, &arg, 1))
			return 0;
		return ((bool)arg[0])?count:0;
	}
	else
	{
		if (conf->isEquip()) {
			return equip_bag_->AppendItem(id, count, log, showTip);
		} else {
			item_bag_->AppendItem(id, count, log, showTip);
			return count;
		}
	}
	return 0;
}

void Actor::CostItem(int id, int count, const char* log)
{
	const ItemConfig *pconf = ItemConfigPool::GetItemConfig(id);
	if (!pconf) return;

	if (pconf->isEquip()) {//装备扣除
		for (int i = 0; i < count; ++i)
		{
			int64_t uid = equip_bag_->FindItemUid(id);
			if (uid == -1) return;
			equip_bag_->CostItem(uid, 1);
		}
	} else {//道具扣除
		int64_t uid = item_bag_->FindItemUid(id);
		if (uid == -1) return;
		item_bag_->CostItem(uid, count);
	}
	static LogSender* log_sender = ServerInstance()->GetLogClient();
	char id_str[64];
	char count_str[64];
	char level_str[64];
	int level = basic_data_->level;

	sprintf(id_str, "%d", id);
	sprintf(count_str, "%d", count);
	sprintf(level_str, "%d", level);
	log_sender->LogCounter(actor_id_,
		account_name_,
		level_str,
		"cost item",
		id_str,
		count_str,
		"", log, "itembag", "", ""
	);

#ifdef OPENLOGDKMLOG
	static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
	dkmLog.LogCostItem(account_id_, actor_id_, entity_name_, GetLevel(), pf_id_, id, count, 0, pconf->type, log);
#endif
}

bool Actor::CostItemByUid(int64_t uid, int count, const char* log)
{
	Item *item = equip_bag_->GetItem(uid);
	bool ret = false;
	int id = 0;
	int type = -1;
	int itemType = -1;
	if (item)
	{
		id = item->GetId();
		itemType = item->GetType();
		ret = equip_bag_->CostItem(uid, count);
		type = BagType_Equip;
	}
	else
	{
		item = item_bag_->GetItem(uid);
		if (item)
		{
			id = item->GetId();
			itemType = item->GetType();
			ret = item_bag_->CostItem(uid, count);
			type = BagType_Item;
		}
	}

	if (id > 0)
	{
		static LogSender* log_sender = ServerInstance()->GetLogClient();
		char id_str[64];
		char count_str[64];
		char level_str[64];
		char bag_type[64];
		char res[10];
		int level = basic_data_->level;

		sprintf(id_str, "%d", id);
		sprintf(count_str, "%d", count);
		sprintf(level_str, "%d", level);
		if (type == BagType_Equip)
			sprintf(bag_type, "equipbag");
		else if (type == BagType_Item)
			sprintf(bag_type, "itembag");
		else
			sprintf(bag_type, "bagtype:%d",type);
		if (ret)
			sprintf(res, "success");
		else
			sprintf(res, "failed");


		log_sender->LogCounter(actor_id_,
			account_name_,
			level_str,
			"cost item",
			id_str,
			count_str,
			res, log, bag_type, "", ""
		);
#ifdef OPENLOGDKMLOG
		static DKMLogMgr& dkmLog = GetGameEngine()->GetDKMlogMgr();
		dkmLog.LogCostItem(account_id_, actor_id_, entity_name_, GetLevel(), pf_id_, id, count, 0, itemType, log);
#endif
	}
	return ret;
}

void Actor::SendTipmsgWithId(int msgid, int type)
{
	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	SendTipmsg(mgr.GetTip(msgid), type);
}

void Actor::SendTipWithId(int msgid, int type/* = ttTipmsgWindow */, ...)
{
	static Protocol::ServerTipsProto proto;
	proto.tipId = msgid;

	SendData(proto);
}

void Actor::SendTipmsgWithArgs(const char* fmt, va_list& args, int type)
{
	//if (fmt == NULL) return;

	////_vsntprintf
	//static const int MAX_COUNT = 1024;
	//static uint8_t data[] = {enChatSystemID, sSendTipmsg, 0};


	//ActorPacket AP;
	//DataPacket& pack = AllocPacket(AP);
	//pack.reserve(pack.getPosition() + MAX_COUNT + 9);
	//pack.writeBuf(data, sizeof(data));
	//pack << (int)type;
	////保留字符串长度成员
	//uint16_t* len_pos = (uint16_t*)pack.getOffsetPtr();
	//int size = sizeof(*len_pos);
	//pack.adjustOffset(size);
	////格式化字符串
	//int fmt_count = VSNPRINTFA((char*)pack.getOffsetPtr(), MAX_COUNT - 1, fmt, args);

	//if (fmt_count < 0) fmt_count = 0;

	//*len_pos = (uint16_t)fmt_count;
	//pack.adjustOffset(fmt_count);
	//pack << (char)0;
	//AP.flush();
}

void Actor::InitTomorrowDateTime()
{
	int rd = wrand(TIME_FLUCTUATE);
	tomorrowDateTime_.tv = login_t_.tomorrow() + rd;
}

void Actor::InitTomorrowWeeHoursTime()
{
	int rd = wrand(TIME_FLUCTUATE);
	int64_t weehourstimelogin = login_t_.today() + WEE_HOURS_TIME;	//登录服务器日凌晨六点时间

	if (login_t_.tv >= weehourstimelogin)
	{
		tomorrowWeeHoursTime_.tv = login_t_.tomorrow() + rd + WEE_HOURS_TIME;
	}
	else
	{
		tomorrowWeeHoursTime_.tv = login_t_.today() + rd + WEE_HOURS_TIME;
	}
}

bool Actor::Init(void* pData, size_t size)
{
	if (size != sizeof(ActorBasicData))
	{
		OutputMsg(rmError, "aid %d, init actor data err. data len:%d, need:%d", actor_id_, size, sizeof(ActorBasicData));
		return false;
	}
	if (CheckInitStep(InitFlagType_Basic))
		return true;

	auto p_actor_data = GetGameEngine()->GetActorDataMgr()->GetData(GetActorId());
	basic_data_ = p_actor_data;
	memcpy(basic_data_, pData, size);

	static GameEngine* ge = GetGameEngine();
	logout_t_ = basic_data_->last_online_time;  //上次的登录时间
	create_t_ = basic_data_->create_time;
	login_t_ = ge->getMiniDateTime();
	OutputMsg(rmTip, "init actor %d, logout:%u:%lld", actor_id_, basic_data_->last_online_time, basic_data_->yuanbao);

	{
		// 之前时间记录有问题,把超出合理范围的记录修改一下.
		int now_t = GetGameEngine()->getMiniDateTime();
		int open_server_t = ServerInstance()->GetServerOpenTime();
		if (basic_data_->total_online > (unsigned int)(now_t - open_server_t))
			basic_data_->total_online = (unsigned int)(now_t - open_server_t);
	}

	InitTomorrowDateTime();
	InitTomorrowWeeHoursTime();

	if (Inherited::Init(pData, size) == false)
	{
		OutputMsg(rmWarning, "actor %d,Inherited::Init fail", actor_id_);
		return false;
	}

	SetEntityName(basic_data_->actor_name);
	_STRNCPY_A(account_name_, basic_data_->account_name);
	if (basic_data_->total_power == 0) // 有必要的话，另起一个字段
		first_login_ = true;

	OnFinishInitStep(InitFlagType_Basic);

	return true;
}

void Actor::OnFinishInitStep(int step)
{
	if (step < InitFlagType_Basic || step >= InitFlagType_Max) return;
//	printf("--------------OnFinishInitStep:%d\n", step);

	init_flag_ |= (1 << step);

	// 如果加载的数据不是指定的系统数据，也不能登陆
	const int Mask = (1 << InitFlagType_Max) - 1;

	if (init_flag_ != Mask) return;

	//首次登陆初始化处理
	if (first_login_)
		OnFirst();

	//脚本相关模块初始化
	{
		ScriptValueList paramList;
		InitActorEventParams(paramList, aeInit);
		paramList << (int)(login_t_ - logout_t_);					// 下线的累计时间
		paramList << (unsigned int)logout_t_;

		OnEvent(&paramList); 

		OnInit();
	}

	//离线奖励处理
	if (!first_login_ && !IsImage())
	{
		ScriptValueList paramList;
		InitActorEventParams(paramList, aeBeforeLogin);
		paramList << (int)(login_t_ - logout_t_);					// 下线的累计时间
		paramList << (unsigned int)logout_t_;

		OnEvent(&paramList); 
	}

	SetInitFlag(true); // 初始化好了

	//OutputMsg(rmTip, "User Init Finish, actorid=%d", actor_id_);

	 // 触发异步处理函数
	GetGameEngine()->GetActorAsynMgr()->TriggerAsynEv(this);
	if (IsImage())
	{
		//CloseImageActor(); // 统一由超时处理, 做缓存
		return;
	}
	static uint8_t data[3] = { Protocol::CMD_Login, ActorMgr::sEnterGame, 1 };
	SendData(data, sizeof(data));

	// 检查之前是否在跨服的时候断线，如果是，则跳到跨服
	ReturnToCrossWar();

	SendBasicData(!waitForCross_); // 下发创建的包

	//property_.clear(); //这里要清除属性改变
	// 只处理下发数据
	OnEnterGame();


	static LianfuMgr& lfMgr = GetGameEngine()->GetLianfuMgr();
	lfMgr.OnUserLogin(this);

	if (!logout_t_.isSameDay(login_t_))
	{
		OnNewDayArrive(true);
	}

	if (!logout_t_.isSameWeek(login_t_))
	{
		CheckNewWeek(true);
	}

	//以凌晨六点为分界线，判断是否是同一天
	if (((logout_t_.tv - WEE_HOURS_TIME) / SecondTime::SecOfDay) != ((login_t_.tv - WEE_HOURS_TIME) / SecondTime::SecOfDay))
	{
		OnNewDayHoursArrive(true);
	}

	int64_t offtime = login_t_ - logout_t_;
	basic_data_->last_online_time = GetGameEngine()->getMiniDateTime();

	if ((unsigned int)logout_t_ == 0 || login_t_ < logout_t_) offtime = 0;	// logout_t_ == 0 是新用户

	ScriptValueList paramList;
	InitActorEventParams(paramList, aeUserLogin);
	paramList << (int)(first_login_ ? 1 : 0); // 登录事件里添加一个参数，标明是不是第1次登录
	paramList << (int)offtime;					// 下线的累计时间
	paramList << (unsigned int)logout_t_;
	
	OnEvent(&paramList);

	//achieve_sys_.OnEvent(eAchieveEventLogin);
	// 触发重新登录副本事件
	/*FuBen* pfb = GetFuBen();

	if (pfb)
	{
		OnEnterFuben(pfb->GetFbId(), pfb->GetHandle(), efwRelogin);
	}

	Scene* scene = GetScene();
	if (scene)
	{
		scene->OnEnterScene(this);
	}
	*/

	AMCommon* msg = AMCommon::alloc();
	msg->msg_ = AMCommon::AMREFRESHFIGHTVAL;
	PostActMsg(msg, 5000);

	SendDataValid(serverId_, actor_id_, false, cw_serverid_);

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	em->SendActorOnline(actor_id_, 1, serverId_);
	logined_ = true;
	ReCalcAttr();
	ReCalcExAttr();
}

void Actor::ReturnToCrossWar()
{
	if (WillReturnToCrossWar())
	{
		LoginOtherSrv(cw_serverid_, false, 0, 0, 0, 0, __FUNCTION__);
	}
}

bool Actor::WillReturnToCrossWar()
{
	return false;	// 不让传回战斗服
}

void Actor::OnInit()
{
	guild_sys_->OnInit();
	zhuansheng_sys_->Init();
	actor_ex_ring_sys_->Init();
	// 统一最后算一次属性
	role_sys_->ReCalcAttr();
}

void Actor::OnEnterGame()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	//static DbRankMgr& rMgr = GetGameEngine()->GetDbRankMgr();

	em->AddToNameList(this);

	static GameEngine* ge = GetGameEngine();
	static Protocol::SyncTimeProto sysn_time_msg;
	sysn_time_msg.time = ge->getMiniDateTime();
	SendData(sysn_time_msg);

	ge->ChannelUser(ciChannelWorld, 0, this);
	//ge->ChannelUser(ciChannelCamp, GetIntProp(P_CAMP), this);
	//ge->ChannelUser(ciChannelTeam, 0, this);	 // 先加到求组频道中，后面如果加入队伍，则会从该频道删除

	role_sys_->OnEnterGame();
	item_bag_->OnEnterGame();
	equip_bag_->OnEnterGame();
	mail_sys_->OnEnterGame();
	store_sys_->OnEnterGame();
	depot_->OnEnterGame();
	msg_sys->OnEnterGame();
	guild_sys_->OnLogin();

	// 如果是排行榜的前3名，给称号
	//rMgr.OnLogin(this);

	// 第一次登陆欢迎界面
	if (first_login_)
	{
		static uint8_t data[2] = { Protocol::CMD_Base, Protocol::sBaseCmd_FirstLogin };
		SendData(data, 2);
	}

	//static FightMgr& fightMgr = GetGameEngine()->GetFightMgr();
	//fightMgr.OnActorLogin(this);
	static GameServer* srv = ServerInstance();
	FuBenMgr* fb_mgr = GetGameEngine()->GetFuBenMgr();

	if (srv->IsBattleSrv()) {
		if (!fb_mgr->EnterFuBen(this, fb_mgr->GetFubenPtr(cw_fbhdl_), cw_sceneid_, cw_x_, cw_y_)) {
			ReturnToStaticScene();
			return;
		}
	} else {
		if (!fb_mgr->EnterFuBen(this, fb_mgr->GetFubenFromID(basic_data_->field_last_fuben_id), basic_data_->fb_scene_id,basic_data_->field_last_pos_x,basic_data_->field_last_pos_y)) {
		//if (!fb_mgr->EnterFuBen(this, fb_mgr->GetFuben(basic_data_->fb_uid), basic_data_->fb_scene_id)) {
			if (!ReturnToStaticScene()) {
			OutputMsg(rmError, "Actor:%d enter fuben failed.", GetActorId());
			return;
		}
	}
	}

	static LogSender* log = ServerInstance()->GetLogClient();
	char buff[128];
	char levelstr[32];
	char bindmoney[32];
	char money[32];
	char total_online[32];
	char other[128];
	SNPRINTFA(buff, sizeof(buff), ("exp:%lld"), (long long)basic_data_->exp);
	SNPRINTFA(levelstr, sizeof(levelstr), "%d", basic_data_->level);
	SNPRINTFA(bindmoney, sizeof(bindmoney), "%d", basic_data_->recharge);
	SNPRINTFA(money, sizeof(money), "%d", basic_data_->yuanbao);
	SNPRINTFA(total_online, sizeof(total_online), "%d", basic_data_->total_online);
	SNPRINTFA(other, sizeof(other), "createtime:%d,pf:%s", GetCreateTime(), GetPf());


	//tlog.LogLogin(account_id_, actor_id_, entity_name_, GetLevel(), pf_, basic_data_->recharge, last_login_ip_);
	log->LogCounter(actor_id_, account_name_, levelstr, "login", buff, bindmoney, "", money, total_online, GetLastLoginIp(), other);
}

void Actor::SendBasicData(bool flag)
{
	// 在角色之前，提前下发服务器的时间下去
	//misc_sys_.SendServerTime();

	if (flag)
	{
		Protocol::ActorProto proto;

		proto.handle = entity_handle_;
		proto.actor_id = basic_data_->actor_id;
		proto.server_id = basic_data_->server_idnex;
		memcpy(&proto.name, &basic_data_->actor_name, sizeof(ACTORNAME));
		proto.level = basic_data_->level;
		proto.exp = basic_data_->exp;
		proto.gold = basic_data_->gold;
		proto.yb = basic_data_->yuanbao;
		proto.power = (double)basic_data_->total_power;
		proto.vip = basic_data_->vip_level;
		proto.soul = basic_data_->essence;
		proto.grid = basic_data_->bag_grid;
		proto.feats = basic_data_->feats;
		proto.shatter = basic_data_->shatter;
		proto.spcshatter = basic_data_->spcshatter;
		proto.togeatter = basic_data_->togeatter;
		proto.togeatterhigh = basic_data_->togeatterhigh;
		proto.prestigeexp = basic_data_->prestige_exp;
		proto.headID = basic_data_->headimage;

		OutputMsg(rmTip, "actor %d, senddata,handle:%lld", actor_id_, proto.handle);
		SendData(&proto, sizeof(proto));
	}

	//UpdateNameClr_OnActorLogin(entity_handle_);
}

void Actor::OnKilledByEntity(Entity* killer)
{
	/*
	if (!killer) return;

	if (killer == this) return; //被自己杀死了

	int kt = killer->GetType();

	if (kt == enActor)
	{
		ScriptValueList paramList;
		InitActorEventParams(paramList, aeKilledByActor); //
		paramList << (void*)killer;
		OnEvent(&paramList);

		Actor* killer_actor = (Actor*)killer;
		int killer_camp = killer_actor->GetCampId();
		int self_camp = GetCampId();

		//ActorId id = GetActorId();
		//ActorId killer_id = killer_actor->GetActorId();

		//killer_actor->GetAchieveSystem().OnEvent(aAchieveEventKillUser, self_camp == killer_camp);

		// 统计仇人的击杀数
		//friend_sys_.AddKillTime(killer_id, 1);
		//killer_actor->GetFriendSystem().AddKillTime(id, 0);

		// 敌对阵营玩家则增加怒气值
		if (killer_camp != self_camp)
		{
			static GLOBALCONFIG& globalConfig = GetConfData()->GetGlobalConfig();

			if (!killer_actor->HasBitState(ebsNoAnger))
			{
				killer_actor->ChangeAnger(globalConfig.enemy_zy_anger_);
			}

		}
	}
	*/
}

const char* Actor::GetMoneyTypeDesc(int nMoneyType)
{
	switch (nMoneyType)
	{
	case mtCoin:
		return "yl";

	case mtBindCoin:
		return "xb";

	case mtYuanbao:
		return "yb";

	case mtBindYuanbao:
		return "by";

	default:
		return "";
	}
}
void Actor::CreateAppearData(DataPacket& appearPack)
{
	Entity::CreateAppearData(appearPack);
	/*
	appearPack << (char)GetJob();
	appearPack << (char)GetSex();

	*/
}
void Actor::OnEntityDeath(EntityHandle killer)
{
	/*static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	Inherited::OnEntityDeath(killer);

	//SetIntProp(P_MP, 0);

	Entity* killerentity =  em->GetEntity(killer.GetHandle());

	pet_sys_.OnActorDie();

	ScriptValueList paramList;
	paramList << this;
	paramList << killerentity;
	CallFunc("onActorDieEvent", &paramList, NULL);

	last_attacker_ = 0; 	// 重设助攻玩家,要在调用aeOnActorDeath事件后，因为该事件会用到

	attack_list_.clear(); // 死亡后清空最近攻击列表

	if (HasState(esStateRide))
	{
		mount_sys_.ChangeStatus(0);
	}

	//群发通知队友
	Team* team = GetCurrentTeam();

	if (team)
	{
#pragma pack(push, 1)
		static struct Data
		{
			uint8_t sid_;
			uint8_t pid_;
			ActorId aid_;
			uint8_t ret_;
			Data(): sid_(enTeamSystemID), pid_(sMemberDieRelive), ret_(0) {}
		} data;
#pragma pack(pop)
		data.aid_ = actor_id_;
		team->BroadCast((char*)&data, sizeof(data), data.aid_);
	}

#ifdef OPENLOGTLOG

	if (killerentity && killerentity->GetType() == enActor)
	{
		static TlogMgr& log = GetGameEngine()->GetTlogMgr();
		log.LogPlayerKill(this, (Actor*)killerentity);
	}

#endif
	*/
}

void Actor::OnLevelUp()
{
	role_sys_->OnLevelUp();
}

bool Actor::IsDeath()
{
	return role_sys_->IsAllDie();
}

void Actor::OnMove(const Point &pos) {
	//获取场景
	Scene* scene = GetScene();
	if (!scene) return;
	//获取副本
	FuBen* fb = GetFuBen();
	if (!fb) return;
	Grid oldGrid(GetPosition());
	SetPosition(pos);
	if (scene->isLeapArea(oldGrid, Grid(pos))) {//夸了区域
		fb->OnActorLeapArea(this);
	}
	
	if (GetCurrGatherMonster())
	{
		GetCurrGatherMonster()->EndGather(false);
	}
}

void Actor::OnEnterScene()
{
	static BaseAllocator s_baseAlloc("enter scene packet");
	static DataPacket s_enter_packet(&s_baseAlloc);
	static Protocol::EnterSceneProto proto;
	proto.fb_id = GetFuBen()->GetFbId();
	proto.scene_id = GetScene()->GetId();
	Point pos = GetPosition();
	proto.x = pos.x;
	proto.y = pos.y;
	proto.fb_type = GetFuBen()->GetConfig()->type;

	s_enter_packet.setLength(0);
	s_enter_packet.writeBuf(&proto, sizeof(proto));

	s_enter_packet.writeString(GetFuBen()->GetConfig()->name.c_str());
	s_enter_packet.writeString(GetFuBen()->GetConfig()->desc.c_str());
	SendData(s_enter_packet);

	GetScene()->OnActorEnter(this);

	if (IsInited()) {
		role_sys_->OnEnterScene();
		actor_ex_ring_sys_->OnEnterScene();
	}
}

void Actor::OnExitScene()
{
	if (IsInited())
	{
		role_sys_->OnExitScene();
		actor_ex_ring_sys_->OnExitScene();
		ClearPackHideSet();
		//CollectOperate(EntityOPCollector::coTransport);
		//bag_sys_.OnEnterScene();
		//equip_sys_.OnEnterScene();
		//team_sys_.OnEnterScene();
	}
	/*
	Scene* scene = GetScene();

	if (!scene) return;

	FuBen* fb = GetFuBen();

	if (!fb) return;

	int x, y;
	GetPosition(x, y);

	if (!fb->IsFb()) //从普通场景里退出，要记录它进入普通场景的位置
	{
		if (!scene->HasMapAttribute(x, y, aaReloadMap))
		{
			enter_fb_x_ = x;
			enter_fb_y_ = y;
			enter_fb_sid_ = scene->GetSceneId();
		}
		else
		{
			enter_fb_x_ = unreload_map_x_;
			enter_fb_y_ = unreload_map_y_;
			enter_fb_sid_ = unreload_map_sid_;
		}
	}

	const FubenConf* conf = fb->GetConfig();

	if (!fb->IsFb() || (conf && conf->isUnique_))
	{
		static GameEngine* ge = GetGameEngine();
		ge->ChannelUser(ciChannelMap, scene->GetSceneId(), this, 1); // 场景频道删掉这个用户
	}

	//删除场景区域添加的buff
	SceneArea* area = scene->GetAreaAttri(x, y);
	RemoveAreaBuff(area);

	if (scene->HasMapAttribute(x, y, aaForcePkMode, area))//恢复上一次的pk模式
	{
		pk_sys_.SetPkMode(pk_sys_.m_bLastMode, true);
	}

	//如果设置了退出场景时触发脚本
	scene->OnExitScene(this);
	*/
	Role * roles[MAX_ROLE] = { NULL };
	GetRoleSystem()->GetRoles(roles);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		if (roles[i] != NULL)
		{
			roles[i]->ClearMoveLine();
		}
	}
}

void Actor::LogicRun(int64_t curr_t)
{
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	static GameEngine* ge = GetGameEngine();

	if (IsImage())
	{
		if (ge->getMiniDateTime() > (unsigned int)image_end_time_)
		{
			OutputMsg(rmError, "image actor timeout. id:%d, flag:%d", actor_id_, init_flag_);
			CloseImageActor();
		}
		return;
	}
	if (!inited_) return;

	Inherited::LogicRun(curr_t);

	int64_t start_t = _getTickCount();

	static int64_t limit_t = EntityMgr::one_entity_t_; //一个实体的处理时间

	static GameGateMgr* gate_mgr = (GameGateMgr*)ServerInstance()->GetGateManager();
	GameGate* gate = (GameGate*)gate_mgr->GetGate(netid_.gate_id_);

	bool ot = false; //已经超时了

	// 已经处理了的数据包的数量
	int proce_count = 0;
	int msgCount = net_packs_->count();
	if (msgCount > 100)
	{
		OutputMsg(rmError, "too many data packge!%d, actorId=%d", msgCount, actor_id_);
	}

	DataPacket** net_msg_list = *net_packs_;

	for (; proce_count < msgCount && !ot; ++proce_count)
	{
		DataPacket* packet = net_msg_list[proce_count];

		uint8_t* buf = (uint8_t*)packet->getOffsetPtr();
		if (!NetMsgDispatcher::ProcessNetMsg(this, buf[0], buf[1], *packet))
		{
			OutputMsg(rmWarning, "unknowning msg: %d %d", buf[0], buf[1]);
		}

		if (_getTickCount() - start_t > limit_t)
			ot = true;
	}

	//一次删除处理的消息
	if (proce_count > 0) gate->AddFreeList(*net_packs_, proce_count, GameGate::GameThread);

	//如果超时了就不处理后面的逻辑了
	if (ot) return;

	// pk，战斗等状态恢复判断 ...

	if (db_timer_.Check(curr_t))
	{
		db_timer_.SetNextHitTimeFromNow(ge->getTickCount(), save_db_interval_);
		SaveDb(false);
	}

	//subsystem runOne
	//...

	if (m_t1minute.CheckAndSet(curr_t)) {
		title_sys_->OnTimeCheck(curr_t);
		OnMonthCardCheck();

		// 检测特权月卡是否过期
		OnPrivilegeMonthCardCheck();
	}

	if (m_t1s.CheckAndSet(curr_t)) {
		ShowZhanLing(curr_t);
		role_sys_->On1sTick(curr_t);
		// 24点整点检测。
		CheckTomorrowTimePoint();
	}

	//如果是玩家要随时更新仇恨列表
	if ( GetRoleSystem()->GetRoleCount() > 0)
	{
		Creature* role = (Creature*)(GetRoleSystem()->GetRoleById(0));
		if (role)
		{
			//role->GetId();
			bool isUpdate = role->GetAI()->UpdateHatred();
			if (isUpdate)
			{
				AI::HatredList damege_list = role->GetAI()->GetHatredList();
				static BaseAllocator alloc("dbserver datapacket");
				static DataPacket s_enter_packet(&alloc);

				//(*(DataPacket*)&s_enter_packet) << (damege_list.size());
				//static Protocol::EnterSceneProto proto;
				static Protocol::BaseProto proto(Protocol::CMD_Field, Protocol::sField_UpdateHatredList);

				s_enter_packet.setLength(0);
				s_enter_packet.writeBuf(&proto, sizeof(proto));
				s_enter_packet.writeAtom((int)(damege_list.size()));
				for (int i = 0;i < (int)(damege_list.size());++i)
					s_enter_packet.writeAtom((int64_t)(damege_list[i].target));
				SendData(s_enter_packet);
			}
		}
			
	}
}


bool Actor::OnEvent(ScriptValueList* params, ScriptValueList* retval)
{
	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	bool ret = lua.Call("OnActorEvent", params, retval);

	if (!ret)
	{
		//脚本错误，将以模态对话框的形式呈现给客户端
		const RefString& s = lua.getLastErrorDesc();
		SendTipmsg((const char*)s, ttDialog);
	}

	return ret;
}

bool Actor::CallFunc(const char* func, ScriptValueList* params, ScriptValueList* retval)
{
	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	bool ret = lua.Call(func, params, retval);

	if (!ret)
	{
		//脚本错误，将以模态对话框的形式呈现给客户端
		const RefString& s = lua.getLastErrorDesc();
		SendTipmsg((const char*)s, ttDialog);
	}

	return ret;
}

void Actor::NpcTalk(const EntityHandle& handle, const char* fn)
{
	/*if (fn == NULL) return;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	static ScriptNpc* gn = GetGameEngine()->GetGlobalNpc();

	Entity* et = (handle == 0 ? gn : em->GetEntity(handle));

	if (!et) return;

	SetTarget(et->GetHandle());

	//只有npc才可以对话
	if (!et->isNPC()) return;

	if (handle != 0)
	{
		//检验数据和坐标，必须在规定范围以内
		if (et->GetFuBen() != GetFuBen() || et->GetScene() != GetScene())
		{
			return;
		}

		int actX, actY, npcX, npcY;
		GetPosition(actX, actY);
		et->GetPosition(npcX, npcY);

		if (!IsSameScreen(actX, actY, npcX, npcY))
		{
			SendTipmsgWithId(tpNpcTooFar, ttTipmsgWindow);
			return;
		}
	}

	//调用npc或者monster的脚本,如果有的话
	if (fn[0] == 0)
	{
		((Npc*)et)->Click(this);
	}
	else
	{
		((Npc*)et)->Talk(this, fn);
	}
	*/
}

void Actor::ExitFubenScene()
{
	//如果原来就是普通副本中，则不做处理
	FuBen* fb = GetFuBen();

	if (fb && !fb->IsFb()) return;

	if (fb)	OnExitFuben(fb->GetFbId(), fb->GetHandle(), xfwNormal);

	Scene* scene = GetScene();

	//正在副本中或者pFb为NULL
	if (scene != NULL)
	{
		scene->ExitScene(this);
	}
}

bool Actor::ReturnToStaticScene()
{
	static GameServer* srv = ServerInstance();
	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	if (srv->IsBattleSrv()) {
		//以防万一，在跨服也先跳到静态副本中先
		FuBen* sfb = mgr->GetStaticFuben();
		mgr->EnterFuBen(this, sfb, 0);
		//然后再跳回普通服
		LoginOtherSrv(serverId_, false, 0, 0, 0, 0, __FUNCTION__);
		DBClient* db = srv->GetDbClient(serverId_);
		if (db) {
			db->SendDbServerData(MAKEINT16(siActor, dcResetCrossPos), actor_id_);
		}
		OutputMsg(rmError, "cannot login battle server ,return to common server!actor's serverId=%d", serverId_);
		return true;
	}
	//如果原来就是普通副本中，则不做处理
	FuBen* fb = GetFuBen();
	if (fb && !fb->IsFb()) return true;
	//回到普通场景
	FuBen* sfb = mgr->GetStaticFuben();

	//回到之前保存的位置
	if (sfb && !srv->IsBattleSrv())	{
		if (fb)	OnExitFuben(fb->GetFbId(), fb->GetHandle(), xfwNormal);
		short x=0, y=0;
		int sid = GetChapterSceneId(x, y);
		return mgr->EnterFuBen(this, sfb, sid, x, y);
		//mgr->EnterFuBen(this, fb, enter_fb_sid_, enter_fb_x_, enter_fb_y_, -1, -1, false, true);
		//fb->Enter(this, enter_fb_sid_, enter_fb_x_, enter_fb_y_);
	}
	return false;
}

	/*
void Actor::ReturnToStaticScene(int sceneId, int posX, int posY)
{
	//如果原来就是普通副本中，则不做处理
	FuBen* fb = GetFuBen();

	if (fb && !fb->IsFb()) return;

	if (fb)	OnExitFuben(fb->GetFbId(), fb->GetHandle(), xfwNormal);

	Scene* scene = GetScene();

	//正在副本中或者pFb为NULL
	if (scene)
	{
		scene->ExitScene(this);
	}

	static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	//回到普通场景
	fb = mgr->GetFbStaticDataPtr(0);

	//回到之前保存的位置
	if (fb)	fb->Enter(this, sceneId, posX, posY);
}
	*/

void Actor::ReturnCity()
{
	//返回普通场景的城市
	/*static FuBenMgr* mgr = GetGameEngine()->GetFuBenMgr();
	FuBen* fb = mgr->GetFbStaticDataPtr(0);

	if (fb)
	{
		if (fb->IsFb())
		{
			OnExitFuben(fb->GetFbId(), fb->GetHandle(), xfwReturnCity);
		}

		mgr->EnterFuBen(this, fb, city_relive_sid_, city_relive_x_, city_relive_y_);
	}
	*/
}

void Actor::ReEnterScene(int x, int y)
{
	//如果原来就是普通副本中，则不做处理
	//FuBen* fb = GetFuBen();
	Scene* scene = GetScene();

	//正在副本中或者pFb为NULL
	if (scene != NULL)
	{
		scene->ExitScene(this);
		scene->EnterScene(this, x, y);
	}
}

void Actor::Relive(int x, int y) {
	//ReEnterScene(x, y);
	SetPosition(Grid(x, y));
	OnRelive();
}

void Actor::OnRelive() {
	role_sys_->OnRelive();
	actor_ex_ring_sys_->OnRelive();
}


void Actor::CheckTomorrowTimePoint()
{
	static GameEngine* ge = GetGameEngine();
	unsigned int tv = ge->getMiniDateTime();

	if (tv >= tomorrowDateTime_.tv) {
		// 更新Next New Day Timepoint
		tomorrowDateTime_.tv = tomorrowDateTime_.rel_tomorrow() + wrand(TIME_FLUCTUATE) ;	// 24点后TIME_FLUCTUATE秒分布 至少要在前半段内分布

		OnNewDayArrive();
		CheckNewWeek();
	}

	//新一天凌晨六点更新事件
	if (tv >= tomorrowWeeHoursTime_.tv) {
		// 更新Next New Wee Hours Timepoint
		tomorrowWeeHoursTime_.tv = tomorrowWeeHoursTime_.rel_tomorrow() + wrand(TIME_FLUCTUATE) + WEE_HOURS_TIME;	// 24点后TIME_FLUCTUATE秒分布

		OnNewDayHoursArrive();
	}
}

void Actor::CheckNewWeek(bool login)
{
	static GameEngine* ge = GetGameEngine();
	if (ge->getSysTime().wday_ == 1 || login)
	{
		// 脚本事件触发
		ScriptValueList params;
		InitActorEventParams(params, aeNewWeekArrive);
		OnEvent(&params);
	}
}

void Actor::PreCloseActor()
{
	if (!IsInited()) return;

	static GameEngine* ge = GetGameEngine();

	SecondTime curTime = ge->getMiniDateTime();

	if (curTime.tv >= tomorrowDateTime_.tv
	        || (curTime.tv >= tomorrowDateTime_.rel_today() && curTime.tv < tomorrowDateTime_.tv))
	{
		OnNewDayArrive();
		CheckNewWeek();
	}

	//凌晨六点更新时间
	if (curTime.tv >= tomorrowWeeHoursTime_.tv
	        || (curTime.tv >= tomorrowWeeHoursTime_.rel_today() + WEE_HOURS_TIME && curTime.tv < tomorrowWeeHoursTime_.tv))
	{
		OnNewDayHoursArrive();
	}

	/*
	//删除场景区域添加的buff
	Scene* scene = GetScene();
	int x , y;
	GetPosition(x, y);
	SceneArea* area = scene ? scene->GetAreaAttri(x, y) : NULL;
	RemoveAreaBuff(area);

	deal_sys_.CancelDeal();
	*/

	FuBen* pfb = GetFuBen();

	if (pfb && pfb->IsFb())
	{
		OnExitFuben(pfb->GetFbId(), pfb->GetHandle(), xfwLogout);
		pfb->OnOffline(this);
	}

	LimitItemCount();

	static LianfuMgr& lfMgr = ge->GetLianfuMgr();
	lfMgr.OnUserLogout(this);

	static ActorMgr* mgr = ServerInstance()->GetActorMgr();
	GameInterMsg msg;
	msg.msg_id_ = ActorMgr::imUserChange;
	msg.data_.cmd_ = gpUserExit;
	msg.data_.dbsid_ = GetActorId();
	mgr->PostMsg(msg);

	msg.msg_id_ = ActorMgr::imCloseUser;
	msg.data_.account_id_ = account_id_;
	mgr->PostMsg(msg);


	
}

#ifdef _MSC_VER
int gettimeofday(struct timeval *tp, void *tzp) {
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = static_cast<long>(clock);
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

void Actor::OnNewDayArrive(bool login/* = false*/)
{
	timeval t_start;
	gettimeofday(&t_start, NULL);
	if (!login)
	{
		ScriptValueList params;
		InitActorEventParams(params, aeDayEnd);
		OnEvent(&params);
	}

	// 脚本事件触发
	ScriptValueList params;
	InitActorEventParams(params, aeNewDayArrive);

	params << login;

	OnEvent(&params);

	//bag_sys_.OnNewDayArrived();
	//guild_sys_.OnNewDayArrived();
	//misc_sys_.OnNewDayArrived();
	basic_data_->daily_online = 0;

	timeval t_end;
	gettimeofday(&t_end, NULL);
	OutputMsg(rmTip, "OnNewDayArrive time: %ld us", 1000000 * (t_end.tv_sec - t_start.tv_sec) + t_end.tv_usec - t_start.tv_usec);
}

void Actor::OnNewDayHoursArrive(bool login/* = false*/)
{
	// 脚本事件触发
	ScriptValueList params;
	InitActorEventParams(params, aeNewDayHoursArrive);

	params << login;

	OnEvent(&params);
}


void Actor::GetEnterFbPos(int& sid, int& x, int& y)
{
	sid = enter_fb_sid_;
	x = enter_fb_x_;
	y = enter_fb_y_;
}

void Actor::SendOperateResult(bool flag, unsigned int send_t)
{
//#ifdef _MSC_VER
//#pragma message ("测试完后，这个发送时间要去掉")
//#endif
//
//#pragma pack(push,1)
//	static struct OpRet
//	{
//		uint8_t sid_;
//		uint8_t pid_;
//		uint8_t flag_;
//		uint8_t ack_;
//		unsigned int send_t_;
//		int r1_;
//		int r2_;
//		OpRet() : sid_(enDefaultEntitySystemID), pid_(sOperatorResult), r1_(0), r2_(0) {}
//	} op_ret;
//#pragma pack(pop)
//	op_ret.flag_ = flag;
//	op_ret.ack_ = send_t != 0 ? true : false;
//
//	if (op_ret.ack_) op_ret.send_t_ = send_t;
//
//	SendData(&op_ret, sizeof(op_ret));
}

//void Actor::SetOpNextTimeImpl(int next_t, bool send2cli,
//                              bool ret, unsigned int send_t)
//{
//	ops_timer_.SetNextHitTime(_getTickCount() + next_t);
//
//	if (send2cli)
//	{
//		SendOperateResult(ret, send_t);
//	}
//}


void Actor::SendTipmsg(const char* msg, int type /*= ttTipmsgWindow*/)
{
	if (msg == NULL) return;

	static uint8_t data[] = { Protocol::SystemCMD::CMD_Chat, Protocol::ChatCmd::sChatCmd_Tipmsg };
	// 如果是指针类型，要多传个长度
	ActorSendData(this, 4,
		dtPointer, (int64_t)&data, sizeof(data),
		dtInt, 0,
		dtInt, type, dtString, (int64_t)msg);
}

void Actor::SendTipmsgFormat(const char* fmt, int type /*=ttTipmsgWindow*/, ...)
{
	va_list args;
	va_start(args, type);
	SendTipmsgWithArgs(fmt, args, type);
	va_end(args);
}

void Actor::OpenSys(int sysId)
{
	ScriptValueList p;
	p << this;
	p << sysId;
	ScriptValueList retList;
	CallFunc("MyOpenSys", &p, &retList);
}


int Actor::GetVIPLevel()
{
	//return GetIntProp(P_VIP_LEVEL);
	return 0;
}

void Actor::OnExitFuben(int id, unsigned int hfb, int way)
{
	/*ScriptValueList params;
	params << id;
	params << this;
	params << hfb;
	params << way;

	static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();
	npc->GetScript().Call("OnActorExitFuben", &params, NULL);
	*/
}

void Actor::OnEnterFuben(int id, unsigned int hfb, int way)
{
	/*ScriptValueList params;
	params << id;
	params << this;
	params << hfb;
	params << way;
	static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();
	npc->GetScript().Call("OnActorEnterFuben", &params, NULL);
	*/
}



// 播放经验和物品特效两个协议脚本也用到，修改的话要一起修改
//void Actor::PlayExpEffect(int nexp)
//{
//	ScriptValueList p;
//	p << this;
//	p << nexp;
//	CallFunc("MyPlayExpEffect", &p, NULL);
//}
//
//void Actor::PlayItemEffect(const ITEM_EFFECT& effect)
//{
//	STATIC_ASSERT(sizeof(ITEM_EFFECT) == 8 + sizeof(ONE_ITEM_EFFECT) * MAX_ITEM_EFFECT);
//	static uint8_t hdr[] = { 139, 67 };
//	ActorPacket AP;
//	DataPacket& pack = AllocPacket(AP);
//	pack.writeBuf(hdr, sizeof(hdr));
//	pack.writeBuf(&effect, 8 + sizeof(ONE_ITEM_EFFECT) * __min(effect.count_, MAX_ITEM_EFFECT));
//	AP.flush();
//}
//用于处理数据上报（接口6.20）
void Actor::sendDcApiLog(int systemId, int protoId, int protoType, int protoResult)
{
//
//#ifdef NEED_LOG_DCAPI
//	static DcApiMgr& dcapi = GetGameEngine()->GetDcApiMgr();
//
//	if (dcapi.IsStopLog())
//	{
//		return;
//	}
//
//#endif
//
//	const char* openId = this->GetAccount();
//	int pf = this->GetPfId();
//	int serverId = ServerInstance()->GetServerIndex();
//	int roleId = this->GetActorId();
//	const char* svrip = (char*)ServerInstance()->getServerIP();
//	const char* userip = this->GetLastLoginIp();
//
//	static LogSender* log = ServerInstance()->GetLogClient();
//	log->LogDcApiProto(openId, pf, serverId, roleId, systemId, protoId, protoType, protoResult, svrip, userip);
}

void Actor::LimitItemCount()
{
	/*static GLOBALCONFIG& gc = GetConfData()->GetGlobalConfig();
	int level = GetIntProp(P_LEVEL);

	if (level < gc.item_warn_level_ && gc.item_limit_.count_ > 0)
	{
		return;
	}

	// 计算背包，装备，仓库等物品的总数量
	const int ArrSize = ArrayCount(gc.item_limit_.data_);

	int	result[ArrSize];
	int itemid = 0;
	ItemWarnList& list = gc.item_limit_;

	memset(&result, 0, sizeof(result[0]) * list.count_);

	bool warning = false;

	if (!warning) warning = consi_sys_.LimitItemCount(list, result, ArrSize, itemid);

	if (!warning) warning = pet_cross_sys_.LimitItemCount(list, result, ArrSize, itemid);

	if (!warning) warning = depot_mgr_sys_.LimitItemCount(list, result, ArrSize, itemid);

	if (warning)
	{
		// 发送报警
		static ScriptNpc* npc = GetGameEngine()->GetGlobalNpc();
		ScriptValueList paras;
		paras << this;
		paras << (int)GetActorId();
		paras << (int)ServerInstance()->GetServerIndex();
		paras << (int)level;
		paras << (int)itemid;
		paras << entity_name_;
		paras << account_name_;
		npc->GetScript().Call("OnItemWarning", &paras, &paras, 0);
	}*/
}

void Actor::putActorInfo2Pack(DataPacket& pack) {
	auto data = this->GetBasicData();
	pack << data->actor_id;
	pack << data->server_idnex;
	pack << data->actor_name;
	pack << (short)data->level;
	pack << (short)data->vip_level;
	pack << (short)data->zhuansheng_lv;
	pack << data->train_level;
	pack << data->total_power;
	pack << GetGuildId();
	pack << GetGuildSystem()->GetGuildName();
	pack << GetZhanLingId();
	pack << GetZhanLingLv();

	WriteRolesData(pack);

	//头像id
	int headID = 0;
	auto pActor = GetActor();
	if (pActor)
	{
		auto pBaseData = pActor->GetBasicData();
		if (pBaseData)
		{
			headID = pBaseData->headimage;
		}
	}

	pack << headID;
	
}

void Actor::LoginOtherSrv(int sid, bool newpos, unsigned int fbhdl, int sceneid, int x, int y, const char* reason)
{
	static GameServer* srv = ServerInstance();
	static GameEngine* ge = GetGameEngine();

	if (srv->IsCommonSrv())
	{
		if (!ge->HasBattleSrv(sid)) return;

		static ActorMgr* mgr = ServerInstance()->GetActorMgr();

		if (mgr && !mgr->HasGameClient(sid)) return;
	}

	ActorMgr::CrossUserData data;
	data.serverId_ = srv->GetServerIndex();

	if (data.serverId_ == sid) return;

	data.actorId_ = GetActorId();
	data.accountId_ = GetAccountId();
	_STRNCPY_A(data.account_name_, GetAccount());
	data.gm_ = HasBitState(ebsGm);

	ActorMgr::GenerateKey(data.key_, sizeof(data.key_));
	data.target_sid_ = sid;
	//data.cross_type_ = CROSSLOGINTYPE_ENTERGAME;
	srv->SendMsgToAllGameClient(&data, sizeof(data),
	                            gpKeyReq, sid);
#ifdef _MSC_VER
	assert(sid != 0);
#endif

	cw_serverid_ = sid;

	if (newpos)
	{
		if (srv->IsCommonSrv())
		{
			cw_fbhdl_ = fbhdl;
			cw_sceneid_ = sceneid;
			cw_x_ = x;
			cw_y_ = y;
		}
		else
		{
			//玩家从战斗服跳到普通服副本
			comm_fb_hdl_ = fbhdl;
			comm_sceneid_ = sceneid;
			comm_x_ = x;
			comm_y_ = y;
		}
	}

	if (fbhdl == 0)
	{
		cw_static_sceneid_ = sceneid;
		cw_static_x_ = x;
		cw_static_y_ = y;
	}

	waitForCross_ = true;

	OutputMsg(rmError, "LoginOtherSrv:%d,sceneid:%d,actorid:%d,reason=%s",
	          sid, sceneid, GetActorId(), reason ? reason : "");
}

void Actor::AddVestMonster(Monster* mon, unsigned int end_time, bool isVest)
{
	if (!mon) return;

	EntityHandle hdl = mon->GetHandle();
	int count = vest_monster_list_.count();
	VestMonster* vest = (VestMonster*)vest_monster_list_;

	for (int i = 0; i < count; i++)
	{
		if (hdl == vest->handle_)
		{
			vest->end_time_ = end_time;
			vest->vest_ = isVest;
			return;
		}

		vest ++;
	}

	if (vest_monster_list_.count() >= MAX_VEST_MONSTER)
		return;

	vest_monster_list_.trunc(count + 1);
	VestMonster& v = vest_monster_list_[count];
	v.handle_ = mon->GetHandle();
	v.end_time_ = end_time;
	v.vest_ = isVest;
}

//获取一个属性集的评分分数
//int Actor::GetFightValue(AttriCalc& attrCalc)
//{
//	/*int rate, dis;
//	int attack_type = SkillResult::GetAttackParam(this, rate, dis);
//	static AttrEval& attrEval = ItemConfPool::config_->GetEval();
//
//	int score = (int)attrEval.GetAttrSetScore(attrCalc, attack_type);
//	return score;
//	*/
//	return 0;
//}

//int Actor::GetFightValue(int type)
//{
	/*int fightValue = 0;

	switch (type)
	{
	case eEquipBase:
	case eEquipStone:
	case eEquipStrong:
	case eEquipsTage:
	case eEquipQuality:
	case eEquipBaptize:
		fightValue = GetEquipmentSystem().GetFightValue(type);
		break;

	case eMountHunger:
		fightValue = GetAttrSystem().CalcScore(acMountExtra);
		break;

	case eMountSkill:
		fightValue = GetMountsSystem().GetSkillScore();
		break;

	case eMountStage:
		fightValue = GetAttrSystem().CalcScore(acMountStage);
		break;

	case eMountAppearance:
		fightValue = GetAttrSystem().CalcScore(acMountAppearance);
		break;
	case eShenZhuangHead:
		fightValue = GetAttrSystem().CalcScore(acShenZhuangHead);
		break;
	case eShenZhuangHand:
		fightValue = GetAttrSystem().CalcScore(acShenZhuangHand);
		break;
	case eShenZhuangShoulder:
		fightValue = GetAttrSystem().CalcScore(acShenZhuangShoulder);
		break;
	case eShenZhuangKnee:
		fightValue = GetAttrSystem().CalcScore(acShenZhuangKnee);
		break;
	}

	return fightValue;
	*/
//	return 0;
//}

void Actor::SendData(const int64_t* params, size_t size, size_t plen)
{
	int pos = 0;
	ActorPacket AP;
	DataPacket& pack = AllocPacket(AP);

	for (int i = 0; i < (int)plen; i++)
	{
		int type = (int)params[pos++];

		switch (type)
		{
		case dtByte:
			pack << (unsigned char)params[pos++];
			break;

		case dtChar:
			pack << (char)params[pos++];
			break;

		case dtWord:
			pack << (unsigned short)params[pos++];
			break;

		case dtShort:
			pack << (short)params[pos++];
			break;

		case dtInt:
			pack << (int)params[pos++];
			break;

		case dtUint:
			pack << (unsigned int)params[pos++];
			break;

		case dtInt64:
			pack << (int64_t)params[pos++];
			break;

		case dtUint64:
			pack << (uint64_t)params[pos++];
			break;

		case dtString:
			pack.writeString((const char*)params[pos++]);
			break;

		case dtPointer:
			{
				const void* buf = (const void*)params[pos++];
				size_t len = params[pos++];
				pack.writeBuf(buf, len);
			}
			break;

		/*case dtItem:
			{
				const ItemData* item = (const ItemData*)params[pos++];
				ItemData::writeToPack(pack, item);
			}
			break;
			*/

		default:
			break;
		}
	}

	AP.flush();
	assert(pos == (int)size);
}

void Actor::SendData(const void* buf, size_t size)
{
	if (size <= 0) return;
	ActorPacket AP;
	DataPacket& pack = AllocPacket(AP);
	pack.writeBuf(buf, size);
	AP.flush();
//#ifdef _MSC_VER
//	if (!(((uint8_t*)buf)[0] == 0 && ((uint8_t*)buf)[1] == 9)  &&
//		!(((uint8_t*)buf)[0] == 2 && ((uint8_t*)buf)[1] ==1)
//		)
//		OutputMsg(rmTip, "======== send (%d,%d)", ((uint8_t*)buf)[0], ((uint8_t*)buf)[1]);
//#endif
}

void Actor::SendData(uint8_t sysid, uint8_t cmdid, const void* buf, size_t size)
{
	ActorPacket AP;
	DataPacket& pack = AllocPacket(AP);
	pack << sysid;
	pack << cmdid;
	pack.writeBuf(buf, size);
	AP.flush();
//#ifdef _MSC_VER
//	OutputMsg(rmTip, "======== send (%d,%d)", sysid, cmdid);
//#endif
}

void Actor::ChangeBabySpeed()
{
	/*static EntityMgr* em = GetGameEngine()->GetEntityMgr();

	int speed = property_.GetIntProp(P_SPEED);

	for (int i = baby_list_.count() - 1; i >= 0; i--)
	{
		Entity* et = em->GetEntity(baby_list_[i].handle_);

		if (et && et->GetType() == enMonster)
		{
			((Monster*)et)->SetIntProp(P_SPEED, speed);
		}
	}
	*/
}

void Actor::SendDataValid(int serverId, ActorId actorId, bool flag, int targetSid)
{
	//OutputMsg(rmTip, "Actor::SendDataValid start aid:%d,flag:%d", actorId, flag ? 1 : 0);
	DBClient* db = ServerInstance()->GetDbClient(serverId);
	if (!db) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siActor, dcSetDataValid));
	packet << (ActorId)actorId << (uint8_t)(flag ? 1 : 0) << (int)targetSid;

	db->flushProtoPacket(packet);
	//OutputMsg(rmTip, "Actor::SendDataValid send aid:%d,flag:%d", actorId, flag ? 1 : 0);
}

const char* Actor::GetServerName()
{
	//static GameWarMgr& warMgr = GetGameEngine()->GetGameWarMgr();
	//const char* sServer = warMgr.GetServerName(GetServerId());
	//return (sServer ? sServer : "");
	return "";
}

int Actor::GetOfflineTime()
{
	if (logout_t_ == (unsigned int)0)
		return 0;
	return login_t_ - logout_t_;
}

bool Actor::WriteRolesData(DataPacket &pack)
{
	return GetRoleSystem()->WriteRolesData(pack);
}

bool Actor::CreateCloneData(DataPacket &pack, int attrper)
{
	if (!GetRoleSystem()->CreateCloneData(pack, attrper)) {
		return false;
	}

	//暂时只发火焰戒指
	int hylv = GetActorExRingLevel(ActorExRingType_HuoYanRing);
	pack << hylv;//等级
	if(hylv > 0) {
		//技能书和道具能力等数据
		ScriptValueList arg;
		arg << this;
		arg << &pack;
		static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
		if (!luaScript.Call("CloneExRingData", &arg, &arg, 0))
			return false;
	}
	return true;
}

void Actor::SetCamp(int camp)
{
	Role* list[MAX_ROLE] = { NULL };
	GetRoleSystem()->GetRoles(list);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = list[i];
		if (!role) break;
		role->SetCamp(camp);
	}
	actor_ex_ring_sys_->SetCamp(camp);
}

void Actor::setCanChangeCamp(bool isChange)
{
	Role* list[MAX_ROLE] = { NULL };
	GetRoleSystem()->GetRoles(list);
	for (int i = 0; i < MAX_ROLE; ++i)
	{
		Role* role = list[i];
		if (!role) break;
		role->setCanChangeCamp(isChange);
	}
	actor_ex_ring_sys_->setCanChangeCamp(isChange);
}

int Actor::GetCamp()
{
	for (int i = 0; i < GetRoleSystem()->GetRoleCount(); ++i)
	{
		auto role = GetRoleSystem()->GetRoleById(i);
		return role->GetCamp();
	}
	return 1;
}

int64_t Actor::GetCurrency(int type)
{
	int64_t award = 0;
	switch (type)
	{
	case NumericType_Exp:
		award = GetExp();
		break;
	case NumericType_Gold:
		award = GetGold();
		break;
	case NumericType_YuanBao:
		award = GetYuanBao();
		break;
	case NumericType_Essence:
		award = GetSoul();
		break;
	case NumericType_Feats:
		award = GetFeats();
		break;
	case NumericType_Shatter:
		award = GetShatter();
		break;
	case NumericType_SpeShatter:
		award = GetSpcShatter();
		break;
	case NumericType_Togeatter:
		award = GetTogeatter();
		break;
	case NumericType_TogeatterHigh:
		award = GetTogeatterHigh();
		break;
	case NumericType_PrestigeExp:
		award = GetPrestigeExp();
		break;
	default:
	{
		ScriptValueList params;
		params << this;
		params << type;
		CallFunc("getCurrency", &params, &params);
		award = params[0];
	}
		break;
	}

	return award;
}

void Actor::ChangeCurrency(int type, int value, const char* log)
{
	switch (type)
	{
	case NumericType_Exp:
		AddExp(value, log);
		break;
	case NumericType_Gold:
		ChangeGold(value, log);
		break;
	case NumericType_YuanBao:
		ChangeYuanBao(value, log);
		break;
	case NumericType_Essence:
		ChangeEssence(value, log);
		break;
	case NumericType_Recharge:
		AddRecharge(value, value); //原先是带套餐的,现在去掉了,接口不想改回去了
		break;
	case NumericType_Feats:
		ChangeFeats(value, log);
		break;
	case NumericType_Shatter:
		ChangeShatter(value, log);
		break;
	case NumericType_SpeShatter:
		ChangeSpcShatter(value, log);
		break;
	case NumericType_Togeatter:
		ChangeTogeatter(value, log);
		break;
	case NumericType_TogeatterHigh:
		ChangeTogeatterHigh(value, log);
		break;
	case NumericType_PrestigeExp:
		ChangePrestigeExp(value, log);
		break;
	default:
	{
		ScriptValueList params;
		params << this;
		params << type;
		params << value;
		params << log;
		CallFunc("changeCurrency", &params, &params);
	}
	break;
	}
}
//战力对比
void Actor::battleComparison(int actorId)
{

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* targetActor = em->GetActorPtrById(actorId);

	if (targetActor == NULL)
		return;
	ActorPacket AP;
	DataPacket& pack = this->AllocPacket(AP);

	pack << (uint8_t)Protocol::CMD_Base;
	pack << (uint8_t)Protocol::sBaseCmd_BattleComparison;

	/*
	玩家id
	玩家区服id
	玩家名字
	玩家等级
	玩家转生等级
	玩家vip等级
	玩家工会id
	玩家工会名字
	玩家头像id
	*/

	//pack << this->GetBasicData()->actor_id;
	//pack << this->GetBasicData()->server_idnex;
	//pack << this->GetBasicData()->account_name;
	//pack << this->GetBasicData()->level;
	//pack << this->GetBasicData()->zhuansheng_lv;
	//pack << this->GetBasicData()->vip_level;
	//pack << this->GetBasicData()->guild_id_;
	//pack << this->GetBasicData()->guild_name_;
	//pack << this->GetBasicData()->headimage;
	//pack << this->GetTitleSystem()->getRoleTitle(0);
	//pack << this->GetBasicData()->job;
	//pack << this->GetBasicData()->sex;
	//this->GetRoleSystem()->WriteRoleBattleInfo(pack);


	pack << targetActor->GetBasicData()->actor_id;
	pack << targetActor->GetBasicData()->server_idnex;
	pack << targetActor->GetBasicData()->account_name;
	pack << targetActor->GetBasicData()->level;
	pack << targetActor->GetBasicData()->zhuansheng_lv;
	pack << targetActor->GetBasicData()->vip_level;
	pack << targetActor->GetBasicData()->guild_id_;
	pack << targetActor->GetBasicData()->guild_name_;
	pack << targetActor->GetBasicData()->headimage;
	pack << targetActor->GetTitleSystem()->getRoleTitle(0);
	pack << (int)targetActor->GetBasicData()->job;
	pack << (int)targetActor->GetBasicData()->sex;
	targetActor->GetRoleSystem()->WriteRoleBattleInfo(pack);

	AP.flush();
}

void Actor::ReCalcAttr()
{
	role_sys_->ReCalcAttr();
}

void Actor::ReCalcExAttr()
{
	role_sys_->ReCalcExAttr();
}

void Actor::ReCalcBattleAttr() {
	role_sys_->ReCalcBattleAttr();
}

void Actor::AddRecharge(int yb, int itemid, int back_yb, std::string orderNum)
{
	basic_data_->recharge += yb;

	ChangeYuanBao(yb, "recharge");
	if(back_yb > 0) ChangeYuanBao(back_yb, "recharge rebate");

	ScriptValueList paramList;
	InitActorEventParams(paramList, aeRecharge);
	paramList << yb;
	paramList << itemid;
	paramList << orderNum.c_str();
	OnEvent(&paramList);
}

int Actor::GetChapterSceneId(short &x, short &y)
{
	static std::map<int, EntityLocation> s_chapter_scenes;
	auto it = s_chapter_scenes.find(basic_data_->chapter_level);
	if (it != s_chapter_scenes.end())
	{
		x = it->second.x;
		y = it->second.y;
		return it->second.sid;
	}

	ScriptValueList p;
	p << basic_data_->chapter_level;
	ScriptValueList retList;
	static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
	if (!lua.Call("getChapterSceneId", &p, &retList, 3))
		return 0;
	ScriptValue& retSid = retList[0];
	if (retSid.getType() != ScriptValue::vNumber) return 0;
	int sceneId = (int)retSid;
	ScriptValue& retX = retList[1];
	if (retX.getType() == ScriptValue::vNumber) x = (int)retX;
	ScriptValue& retY = retList[2];
	if (retY.getType() == ScriptValue::vNumber) y = (int)retY;
	EntityLocation &loc = s_chapter_scenes[basic_data_->chapter_level];
	loc.sid = sceneId;
	loc.x = x;
	loc.y = y;
	return sceneId;
}

void Actor::SetChapterLevel(int level) {
	basic_data_->chapter_level = level;

	ScriptValueList paramList;
	InitActorEventParams(paramList, aeChapterLevelFinish);
	paramList << level;

	OnEvent(&paramList);
}

void Actor::SetVipLevel(int vip) 
{ 
	
	if (vip != (int)basic_data_->vip_level)
	{
		basic_data_->vip_level = vip;
		ScriptValueList paramList;

		InitActorEventParams(paramList, aeUpdateVipInfo);
		paramList << vip;
		OnEvent(&paramList);
		
		equip_bag_->OnVipLevelUpdate();
	}
	
}

Role* Actor::GetLiveByPower()
{
	//if (!IsDeath()) return nullptr;
	return role_sys_->GetLiveByPower();
}

Role* Actor::GetRandomLiveRole()
{
	return role_sys_->GetRandomLiveRole();
}

Role* Actor::GetLiveByJob()
{
	return role_sys_->GetLiveByJob();
}

int Actor::getDeathCount()
{
	return role_sys_->GetDeathCount();
}

double Actor::GetAtkSum(void) {
	int role_count = role_sys_->GetRoleCount();
	double atk_sum = 0.0;
	for (int i = 0; i < role_count; ++i) {
		Role* role = role_sys_->GetRoleById(i);
		if (role) atk_sum += role->GetAttr(Attribute::atAtk);
	}
	return atk_sum;
}

void Actor::ResetShowZhanLingT()
{
	static GameEngine* ge = GetGameEngine();
	show_zhanling_t_ = ge->getTickCount() - show_zhanling_cd_ + show_zhanling_delay_;
}

void Actor::ShowZhanLing(int64_t curr_t)
{
	if (zhanling_lv_ < 0) return;  //系统未开启或还没到指定等级
	if (curr_t - show_zhanling_t_ < show_zhanling_cd_) return;  //cd中
	Scene * scene = GetScene();
	if (nullptr == scene) return;  //不在副本里
	FuBen * fuben = scene->GetFuBen();
	if (nullptr == fuben) return;  //找不到副本
	if (!fuben->IsFb()) return;  //前端本不管

	Role *roles[MAX_ROLE] = { NULL };
	role_sys_->GetRoles(roles);
	for (auto it = zhanling_effids_.begin(); it != zhanling_effids_.end(); it++)
	{
		if (static_cast<int>(wrand(10000)) < it->second)
		{
			//触发战灵天赋
			for (int i = 0; i < MAX_ROLE; ++i)
			{
				if (roles[i] && !roles[i]->IsDeath()) {
					roles[i]->GetSkillEffectSystem()->AddEffect(roles[i], it->first);
				}
			}
			//客户端需求 屏蔽掉这个消息
			if (zhanling_talent_effid_ == it->first) {
				Protocol::ShowTalentProto proto;
				//SendData(proto);
			}
		}
	}
	
	show_zhanling_t_ = curr_t;

	// 广播
	Role *leader = GetLiveByJob();
	if (leader) {
		Protocol::ShowZhanLingProto proto;
		proto.handle = leader->GetHandle();
		proto.level = zhanling_lv_;
		proto.id = zhanling_id_;
		
		if (fuben->NeedShowZhanLing()) {
			scene->SendData(proto);
		}
		else {
			//有些副本为了不卡，屏蔽掉广播
			SendData(proto);
		}
	}
}

void Actor::OnMonthCardCheck(void)
{
	ScriptValueList arg;
	arg << this;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onMonthCardRun", &arg, &arg, 0);
}

// 检测特权月卡是否到期
void Actor::OnPrivilegeMonthCardCheck(void)
{
	ScriptValueList arg;
	arg << this;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("onCheckPrivilegeMonthCardValid", &arg, &arg, 0);
}

bool Actor::RoleHasTarget(void)
{

	for (int i = 0;i < MAX_ROLE; ++i)
	{
		auto role = role_sys_->GetRoleById(i);
		if (role)
		{
			if (role->GetTarget())
			{
				return true;
			}
		}
	}
	return false;
}

int Actor::GetActorExRingLevel(int id)
{
	if (id < 0 || id >= ActorExRingType_MAX) return 0;
	return basic_data_->ex_ring_lv[id] & (~(1 << 31));
}

void Actor::SetActorExRingLevel(int id, int level)
{
	if (id < 0 || id >= ActorExRingType_MAX) return;
	int val = (basic_data_->ex_ring_lv[id] >> 31) & 0x01;
	if (val == 1) { //把最高的标志位给拿回来
		level |= (1 << 31);
	}
	basic_data_->ex_ring_lv[id] = level;
}

bool Actor::GetActorExRingIsEff(int id)
{
	if (id < 0 || id >= ActorExRingType_MAX) return false;
	return (basic_data_->ex_ring_lv[id] & (1 << 31))?true:false;
}

void Actor::SetActorExRingIsEff(int id, bool eff)
{
	if (id < 0 || id >= ActorExRingType_MAX) return;
	unsigned int mask = (1 << 31);
	if (eff)
	{
		basic_data_->ex_ring_lv[id] |= mask;
	}
	else
	{
		// 变成0
		mask = ~mask;
		basic_data_->ex_ring_lv[id] &= mask;
	}
}
