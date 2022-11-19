#ifndef _ACTOR_H_
#define _ACTOR_H_

/***************************************************************
*                     玩家的实体
***************************************************************/

//todo 整理声明类
#include <cstdarg>
#include "lua_var_system.h"
//#include "offlinemsg/msg_system.h"


#define MAX_ATTACK	10	// 保存攻击自己的最大玩家数
#define MAX_VEST_MONSTER	5
#define IMAGE_ACTOR_CACHE_TIME 600
#define MAX_FLAMESTAMP_SKILL 7 //烈焰印记技能个数

struct VestMonster
{
	EntityHandle handle_;
	unsigned int end_time_;
	bool vest_; // 是否归属者
};

struct AttackBack
{
	EntityHandle handle_;
	unsigned int time_;
};

class Npc;
class Monster;
class Role;
class RoleSystem;
class ItemBag;
class EquipBag;
class MailSystem;
class ZhuanShengSystem;
class StoreSystem;
class Depot;
class TitleSystem;
class GuildSystem;
class GatherMonster;
class MsgSystem;
class ActorExRingSystem;
class TogetherHitSystem;
class ImbaSystem;
class GodWeaponSystem;
class WarSystem;
class Actor :
	public Entity
{
public:
	enum InitFlagType
	{
		InitFlagType_Basic = 0,
		InitFlagType_Role,

		InitFlagType_Lua,
		InitFlagType_ItemBag,
		InitFlagType_EquipBag,
		InitFlagType_Mail,
		InitFlagType_Store,
		InitFlagType_Depot,
		InitFlagType_TogetherHit,
		InitFlagType_CsWarLua,
		InitFlagType_ActorCsData,

		InitFlagType_Max,
	};

	typedef Entity Inherited;
	static const int MAX_OWNER = 4;
	static const int64_t MAX_64BIT_CURRENCY_COUNT = (int64_t)1 << 52;
	static const unsigned int MAX_32BIT_CURRENCY_COUNT = (unsigned int)1 << 30;

	typedef StaticArrayList<EntityHandle, MAX_OWNER>	OwnerMonList;

	typedef StaticArrayList<EntityHandle, 10>	QuestOwnerMonList;

	Actor();
	virtual ~Actor();
	bool Init(void* pData, size_t size);
	void OnDestroy();
	void ClearPackHideSet();

	virtual int GetId() { return basic_data_->actor_id; }
	virtual void OnKilledByEntity(Entity* killer);
	virtual void OnEnterScene();
	virtual void OnExitScene();
	virtual Actor* GetActor() { return this; }
	virtual void CreateAppearData(DataPacket& appearPack);
	virtual void OnEntityDeath(EntityHandle killer);
	virtual void OnLevelUp();
	virtual bool IsDeath();
	virtual void OnMove(const Point &pos);
	virtual int GetHeadID() { return basic_data_->headimage; }
	//virtual void OnAttackOther(Animal* pEntity);
	//virtual void OnAttacked(Animal* pEntity);  //被攻击

	//初始化实体的广播的mask，哪些属性是需要广播的
	static void InitBroadcastMask();
	static void DestroyBroadcastMask() { SafeDelete(Actor::broadcastMask_); }


	bool IsImage() { return is_image_; }
	void SetImage(bool isImage);
	void SetImageEndTime(int endTime) { image_end_time_ = endTime; }
	int GetImageEndTime() { return image_end_time_; }
	void SetKickRelogin(bool iskick) { kick_relogin_ = iskick; }
	void NoticeRelogin();

	const ActorBasicData* GetBasicData() { return basic_data_; }

	//获取角色ID
	virtual inline ActorId GetActorId() const { return actor_id_; }
	inline void SetActorId(ActorId id) { actor_id_ = id; }

	void AddExp(int addvalue, const char* log);
	int GetExp() { return basic_data_->exp; }
	void SetExp(int value) { basic_data_->exp = value; }
	int GetLevel() { return basic_data_->level; }
	void SetLevel(int value) { basic_data_->level = value; }
	void SetPower(double power) { basic_data_->total_power = (long long)power; }
	void SetRankPower(double power) { basic_data_->rank_power = (long long)power; }
	double GetPower() { return (double)basic_data_->total_power; }
	int getTujianPower() { return static_cast<int>(basic_data_->total_tujian_power); }
	int getEquipBasePower() { return static_cast<int>(basic_data_->total_equip_power); }
	int GetJob() { return basic_data_->job; }
	int GetSex() { return basic_data_->sex; }
	void SetCamp(int camp);
	void setCanChangeCamp(bool isChange);
	int GetCamp();
	void SetTogeLv(int lv) { toge_lv_ = lv; }
	int GetTogeLv() { return toge_lv_; }
	void SetYuPeiLv(int lv) { yupei_lv_ = lv; }
	int GetYuPeiLv() { return yupei_lv_; }

	// 货币
	int64_t GetCurrency(int type);
	void ChangeCurrency(int type, int value, const char* log);
	int64_t GetGold() { return basic_data_->gold; }
	int64_t GetYuanBao() { return basic_data_->yuanbao; }
	int64_t GetSoul() { return basic_data_->essence; }
	int64_t GetFeats() { return basic_data_->feats; }
	int64_t GetShatter() { return basic_data_->shatter; }
	int64_t GetSpcShatter() { return basic_data_->spcshatter; }
	int64_t GetTogeatter() { return basic_data_->togeatter; }
	int64_t GetTogeatterHigh() { return basic_data_->togeatterhigh; }
	int64_t GetPrestigeExp() { return basic_data_->prestige_exp; }
	void ChangeGold(int value, const char* log);
	void ChangeYuanBao(int value, const char* log, bool isIgnore = false);
	void ChangeEssence(int value, const char* log);
	void ChangeFeats(int value, const char* log);
	void ChangeShatter(int value, const char* log);
	void ChangeSpcShatter(int value, const char* log);
	void ChangeTogeatter(int value, const char* log);
	void ChangeTogeatterHigh(int value, const char* log);
	void ChangePrestigeExp(int value, const char* log);
	int GiveItem(int id, int count, const char* log, bool showTip = true);
	void CostItem(int id, int count, const char* log);
	bool CostItemByUid(int64_t uid, int count, const char* log);

	int GetChapterLevel() { return basic_data_->chapter_level; }
	void SetChapterLevel(int level);
	int GetChapterSceneId(short &x, short &y);

	int GetVipLevel() { return basic_data_->vip_level; }
	void SetVipLevel(int vip);

	void SetBagGrid(int value) { basic_data_->bag_grid = value; }
	const char* GetActorName() { return basic_data_->actor_name; }
	void SetActorName(const char* name)
	{
		if (name == NULL) return;
		memset(basic_data_->actor_name, 0, sizeof(basic_data_->actor_name));
		_STRNCPY_A(basic_data_->actor_name, name);
		SetEntityName(name);
	}

	void SetGuildId(int guildId) { basic_data_->guild_id_ = guildId; }
	int GetGuildId() const { return basic_data_->guild_id_; }
	void SetGuildName(const char* name) {	_STRNCPY_A(basic_data_->guild_name_, name ? name : ""); }
	const char* GetGuildName() const { return basic_data_->guild_name_; }

	uint8_t GetMonthCard() { return basic_data_->monthcard; }

	// 充值金额
	int GetRecharge() { return basic_data_->recharge; }
	void AddRecharge(int yb, int itemid = -1, int back_yb = 0, std::string orderNum = "");

	unsigned int GetEssence() { return basic_data_->essence; }
	void SetEssence(unsigned int value) { basic_data_->essence = value; }

	//玩家战力对比
	void battleComparison( int actorId);

	void ReCalcAttr();
	void ReCalcExAttr();
	void ReCalcBattleAttr();
	// 创建遭遇战玩家数据
	bool WriteRolesData(DataPacket &pack);
	bool CreateCloneData(DataPacket &pack, int attrper = 0); // 会有随机变化

	inline RoleSystem* GetRoleSystem() { return role_sys_; }
	inline TitleSystem* GetTitleSystem() { return title_sys_; }
	inline ItemBag* GetItemBag() { return item_bag_; }
	inline EquipBag* GetEquipBag() { return equip_bag_; }
	inline Depot* GetDepot() { return depot_; }
	inline MailSystem* GetMailSystem() { return mail_sys_; }
	inline ZhuanShengSystem* GetZhuanShengSystem() { return zhuansheng_sys_; }
	inline StoreSystem* GetStoreSystem() { return store_sys_; }
	inline GuildSystem* GetGuildSystem() { return guild_sys_; }
	inline MsgSystem* GetMsgSystem() { return msg_sys; }
	inline ActorExRingSystem* GetActorExRingSystem() { return actor_ex_ring_sys_; }
	inline TogetherHitSystem* GetTogetherHitSystem() { return together_hit_sys_; }
	inline ImbaSystem* GetImbaSystem() { return imba_sys_; }
	inline GodWeaponSystem* GetGodWeaponSystem() { return god_weapon_sys_; }
	inline WarSystem* GetWarSystem() { return war_sys_; }

	inline UpdateMask* GetBroadCastMask() { return broadcastMask_; }
	//inline MsgSystem& GetMsgSystem() { return msg_sys_; }  //消息子系统 }
	inline int GetPropertySize() const { return sizeof(ActorProperty) - sizeof(PropertySet); }
	inline LuaVarSystem* GetActorVarSystem() { return var_sys_; }   //玩家变量系统 }
	inline CLVariant& GetActorVar() { return var_sys_->GetVar(); }   //获取玩家变量 }

	inline Attribute* GetKnighthoodAttr() { return &knighthood_attr_; }
	inline Attribute* GetArtifactsAttr() { return &artifacts_attr_; }
	inline Attribute* GetTrainsystemAttr() { return &trainsystem_attr_; }
	inline Attribute* GetChallengefbsystem() { return &challengefbsystem_attr_; }
	inline Attribute* GetRongLuAttr() { return &ronglu_attr_; }
	inline Attribute* GetActorExRingAttr() { return &actorexring_attr_; }
	inline Attribute* GetActorsystemAttr(int32_t attrId) { if (attrId < 0 || attrId >= attrMax) { return nullptr; } return &actor_attr_[attrId]; }
	inline Attribute* GetMonthCardAttr() { return &mongthCard_attr_; }
	inline Attribute* GetPrivilegeAttr() { return &privilege_attr_; }
	inline Attribute* GetReincarnateAttr() { return &reincarnate_attr_; }
	inline Attribute* GetVipAttr() { return &vip_attr_; }
	inline Attribute* GetNewWorldBossAttr() { return &new_world_boss_attr_; }
	inline Attribute* getYuPeiAttr() { return &yupei_attr_; }
	inline Attribute* getPerstigeAttr() { return &perstige_attr_; }

	inline ExAttribute* GetKnighthoodExAttr() { return &knighthood_ex_attr_; }
	inline ExAttribute* GetTrainsystemExAttr() { return &trainsystem_ex_attr_; }
	inline ExAttribute* GetGodWeaponExAttr() { return &god_weapon_ex_attr_; }
	inline ExAttribute* getYuPeiExAttr() { return &yupei_ex_attr_; }
	inline ExAttribute* GetReincarnateExAttr() { return &reincarnate_ex_attr_; }

	int GetGateIdx() { return netid_.gate_id_; }
	NetId& GetNetId() { return netid_; }

	int GetGmLevel(void){ return gm_level_; }
	void SetGmLevel(int l){ gm_level_ = l; }

	void ResetShowZhanLingT();
	inline static void SetShowZhanLingCd(int cd, int delay) { show_zhanling_cd_ = cd; show_zhanling_delay_ = delay; }
	inline void SetZhanLingInfo(int id, int level, int effId) { zhanling_id_ = id;  zhanling_lv_ = level; zhanling_talent_effid_ = effId; }
	inline void GetZhanLingInfo(int &id, int &level, int &effId, std::map<int, int> &effids) { id = zhanling_id_; level = zhanling_lv_; effId = zhanling_talent_effid_; effids = zhanling_effids_; }
	inline int GetZhanLingId() { return zhanling_id_; }
	inline int GetZhanLingLv() { return zhanling_lv_; }
	inline void SetZhanLingId(int id) { zhanling_id_ = id; }
	inline void ClearZhanLingEffect() { zhanling_effids_.clear(); }
	inline void AddZhanLingEffect(int effId, int rate) { zhanling_effids_[effId] = rate;}
	
	int GetActorExRingLevel(int id);
	void SetActorExRingLevel(int id, int level);
	bool GetActorExRingIsEff(int id);//获取一个特戒是否出战
	void SetActorExRingIsEff(int id, bool eff);//设置一个特戒是否出战
	void SetFlameStampLv(int lv) { flamestamp_lv_ = lv; }
	void SetFlameStampSkillLv(int index, int lv) { if (index >= 0 && index < MAX_FLAMESTAMP_SKILL) flamestamp_skill_lv_[index] = lv; }
	int *GetFlameStampData(int &level) { level = flamestamp_lv_; return flamestamp_skill_lv_; }

	/*
	* Comments: 获取发送缓冲,用于写入数据发送网络数据包，写完以后调用一下pack.flush()就写入发送缓冲
	*            典型的用法参考 SendData接口
	* Param CActorPacket & pack:局部的CActorPacket
	* @Return DataPacket&: 返回pack里的datapack，可以直接写入数据
	*/
#ifdef _DEBUG
	DataPacket& _AllocPacket(ActorPacket& pack, const char* file, int line);
#define AllocPacket(AP) _AllocPacket(AP, __FILE__, __LINE__)
#else
	DataPacket& AllocPacket(ActorPacket& pack);
#endif

	/*
	* Comments: 根据系统提示ID发送系统提示
	* Param int nTipmsgID:系统提示ID
	* Param int nType: 系统提示显示的类型
	* @Return void:
	*/
	void SendTipmsgWithId(int msgid, int type = ttTipmsgWindow);

	/*
	* Comments: 根据系统提示ID定义，进行格式化后发送系统提示
	* Param int nTipmsgID:系统提示ID
	* Param int nType: 系统提示显示的类型
	* @Return void:
	*/
	void SendTipWithId(int msgid, int type = ttTipmsgWindow, ...);

	/*
	* Comments:发送系统提示消息,自己组装好了，不需要组装就调用这个接口
	* Param const char* sTipmsg: 组装好的字符串
	* Param int nType:  系统提示显示的类型
	* @Return void:
	*/
	void SendTipmsg(const char* msg, int type = ttTipmsgWindow);

	/*
	* Comments:具有参数格式化功能的发送系统提示消息
	* Param const char* sTipmsg: 组装好的字符串
	* Param int nType:  系统提示显示的类型
	* @Return void:
	*/
	void SendTipmsgFormat(const char* fmt, int type = ttTipmsgWindow, ...);

	//向客户端发送公共操作的结果
	void SendOperateResult(bool flag, unsigned int nSendPkgTime = 0);

	/*
	* Comments:能够实现参数格式化功能的发送系统提示消息
	* Param const char* sFormat: 消息格式
	* Param int nType:  系统提示显示的类型
	* @Return void:
	*/
	void SendTipmsgWithArgs(const char* fmt, va_list& args, int type);


	/*
	* Comments:向玩家发送数据，这个接口一般给广播使用，玩家一般的数据包请使用AllocPacket分配然后发送
	* Param char * pData: 数据指针
	* Param size_t size: 数据大小
	* @Return void:
	*/
	void SendData(const void* buf, size_t size);
	void SendData(uint8_t sysid, uint8_t cmdid, const void* buf, size_t size);
	template<class ProtoType>
	void SendData(ProtoType &proto) { SendData(&proto, sizeof(proto)); }
	void SendData(DataPacket &pack) { SendData(pack.getMemoryPtr(), pack.getLength()); }
#define ActorSendData(actor,pcount,...) const int64_t params[] = {__VA_ARGS__};\
	actor->SendData(params, sizeof(params)/sizeof(params[0]), pcount);

	void SendData(const int64_t* params, size_t size, size_t plen);

	/*
	* Comments: 玩家登陆
	* Param UINT_PTR nSocket: socketID
	* Param UINT_PTR nActorID: 玩家的角色ID
	* Param UINT_PTR nGateSessionID: 在网关上的sessionID
	* Param UINT_PTR nGateIndex: 网关编号
	* Param UINT_PTR nServerSessionId: 在服务器上的sessionID
	* Param UINT_PTR nAccountID:玩家的帐户ID
	* Param int  nFcmTime: 防沉迷的时间
	* Param int  nGmLevel: 玩家的GM等级
	* Return void:
	*/
	void Onlogin(NetId netid, ActorId actorId, int accountId, int gm_level);

	//是否需要向网关发送关闭的消息
	void CloseActor(const char* reason, bool notic_gate = true); // 关闭连接

	void LogicRun(int64_t curr_t);

	void ChangeBabySpeed();

	// bLogout: 为true表明是下线、否则为定时存盘
	void SaveDb(bool bLogout = false); //存盘
	void OnDbReturnData(int cmd, DataPacketReader& reader);

	inline int GetAccountId() { return account_id_; }
	inline const char* GetAccount() { return account_name_; }


	//收到网络数据包
	void PostNetMsg(DataPacket* data, int nid);

	// 收到心跳包
	void OnRecvBeat(unsigned int send_beat_t);
	/*
	* Comments:与NPC交谈以及执行脚本
	* Param EntityHandle & NpcHandle:
	* Param const char* sFunctionName:脚本要执行的函数名和参数信息
	* @Return void:
	*/
	void NpcTalk(const EntityHandle& NpcHandle, const char* sFunctionName);

	/*
	* Comments:本函数用于当事件发生时调用的函数，函数内会调用全局的脚本执行
	* Param int CScriptValueList & paramList:参数列表
	* Param int CScriptValueList & retParamList:返回参数列表
	* @Return void:
	*/
	bool OnEvent(ScriptValueList* params = NULL, ScriptValueList* retval = NULL);

	bool CallFunc(const char* func, ScriptValueList* params, ScriptValueList* retval);

	/*
	* Comments: 初始化一个事件调用的CScriptValueList，主要
	  把自己的指针和事件的指针压入
	* Param CScriptValueList & paramList: 参数列表
	* Param int nEventID: 事件ID
	* @Return void:
	*/
	inline void InitActorEventParams(ScriptValueList& params, int eid)
	{
		params << this;
		params << eid;
	}
	/*
	* Comments: 获取一个社会关系的位
	* Param int nMaskID: maskID,定义在SystemParamDef.h里，如
		enum tagSocialMaskDef
		{
		smGuildCommon=0,    //帮会普通成员
		smGuildTangzhu=1,    //堂主
		smGuildAssistLeader=2, //副帮主
		smGuildLeader=3,     //帮主
		};
	* @Return bool: 如果设置了就返回true,否则返回false
	*/
	//inline bool GetSocialMask(int nMaskID)
	//{
	//	return (GetUIntProp(P_SOCIAL) & (1 << nMaskID)) ? true : false;
	//}

	unsigned int GetLastLogoutTime() { return logout_t_; }
	unsigned int GetLoginTime() { return login_t_; }
	inline unsigned int GetCreateTime() { return create_t_; }
	//获取CActorPacket
	inline ActorPacket& GetFastPacket() { return fastPacket_; }

	/*
	* Comments:让角色退出副本，回到常规场景，位置是进入副本前保存的常规场景的位置，
	* 如果角色已经在常规场景中，则不做处理
	* @Return void:
	*/
	bool ReturnToStaticScene();
	void ExitFubenScene();
	void ReturnCity();
	void ReEnterScene(int x = 0, int y = 0);

	//完成一个初始化步骤，玩家需要自身的数据初始化，装备的初始化和技能的初始化才下发创建
	void OnFinishInitStep(int step);
	bool CheckInitStep(int step) { return (init_flag_ & (1 << step))> 0; }

	//装备护符，增加技能
	void AddProtectSkill(int skillId, int level);
	//护符装备的技能效果
	void ProtectSkillEffect();
	//护符装备的技能战斗力
	int ProtectSkillFightValue();

	void OnFirst();
	void Relive(int x = 0, int y = 0);
	void OnRelive();

	void OnInit();
	//玩家角色创建好了，已经给客户端发了创建的数据包了
	void OnEnterGame();

	//获取进入副本前的位置
	void GetEnterFbPos(int& sid, int& x, int& y);

	//删除复活保护的buff
	void RemoveReliveProtectState();

	/*
	* Comments: 获取金钱的描述
	* Param int nMoneyType:金钱的类型
	* @Return char *:返回金钱的名字，比如元宝返回yb,绑定元宝返回byb,银两返回coin,绑定返回bcoin
	*/
	static const char* GetMoneyTypeDesc(int nMoneyType);

	// 判断某个系统是否已经开放
	bool IsSysOpen(int sysId);
	// 开放某个系统
	void OpenSys(int sysId);

	// 获取玩家VIP等级
	int GetVIPLevel();

	void OnExitFuben(int id, unsigned int hfb, int way);
	void OnEnterFuben(int id, unsigned int hfb, int way);

	// 播放获取经验特效
	//void PlayExpEffect(int nexp);

	// 播放获取物品特效
	//void PlayItemEffect(const ITEM_EFFECT& effect);

	void SetPf(const char* pf) { _STRNCPY_A(pf_, pf); }
	const char* GetPf() { return pf_; }

	void SetAppid(const char* appid) { _STRNCPY_A(appid_, appid); }
	const char* GetAppid() { return appid_; }

	void SetPfid(const char* via) { _STRNCPY_A(pf_id_, via); }
	const char* GetPfid() { return pf_id_; }

	const char* GetLastLoginIp() { return last_login_ip_; }
	void SetLastLoginIp(const char* ip) { _STRNCPY_A(last_login_ip_, ip); }

	int GetOfflineTime();

	// 保存除杀死自己的玩家外最后一个攻击自己的玩家的id
	void SaveLastAttackId(ActorId aid) { last_attacker_ = aid; }
	ActorId GetLastAttackId() { return last_attacker_; }

	//用于处理数据上报（接口6.20）
	void sendDcApiLog(int systemId, int protoId, int protoType, int protoResult);

	void SetServerId(int sid) { serverId_ = sid; }
	int GetServerId() { return serverId_; }
	void putActorInfo2Pack(DataPacket& pack);
	void SetCurrGatherMonster(GatherMonster* m) { curr_gather_monster_ = m; }
	GatherMonster* GetCurrGatherMonster(void) {return curr_gather_monster_;}

	// 跨服相关
	void LoginOtherSrv(int sid, bool newpos, unsigned int fbhdl, int sceneid, int x, int y, const char* reason);
	// 清除在普通场景的位置，事实上这个函数的目的是为了在跨服战中不运行玩家进入普通场景
	void ResetStaticFbPos()
	{
		enter_fb_sid_ = enter_fb_x_ = enter_fb_y_ = 0;
	}

	// 获取归属怪物列表
	void AddVestMonster(Monster* mon, unsigned int end_time, bool isVest);
	// 获取归属怪物数量
	int GetVestMonsterCount()
	{
		return vest_monster_list_.count();
	}
	// 获取怪物归属经验加成
	float GetVestExpRate();

	// 获取Actor或者role中没dead并且战力最高的，都dead的话返回NULL
	Role* GetLiveByPower();
	Role* GetRandomLiveRole();
	Role* GetLiveByJob();
	int getDeathCount();
	double GetAtkSum();
private:

	void SendBasicData(bool flag); //发送主角创建的消息到客户端
	void CloseImageActor();
	/*
	* Comments: 新的一天到来相关的处理
	* Param bool login: 是否登录检查的情况
	* @Return void:
	*/
	void OnNewDayArrive(bool login = false);

	/*
	* Comments: 新的凌晨六点到来相关的处理
	* Param bool login: 是否登录检查的情况
	* @Return void:
	*/
	void OnNewDayHoursArrive(bool login = false);

	/*
	* Comments: 玩家登陆是初始化明天时间点（相对于当前登陆时间点的明天）
	* @Return void:
	*/
	void InitTomorrowDateTime();

	/*
	* Comments: 玩家登陆时初始化明天时间点（相对于当前登陆时间点的明天）
	* @Return void:
	*/
	void InitTomorrowWeeHoursTime();

	/*
	* Comments: 检测明天时间点是否到时
	* @Return void:
	*/
	void CheckTomorrowTimePoint();

	void CheckNewWeek(bool login = false);

	/*
	* Comments: 玩家准备下线
	* @Return void:
	* @Note: 主要做定时清理相关的补充工作。因为NextDayArrive 24点整点刷新实际上为了分散压力不是真正的准点，
	* 而是分配到随后的60s时间内执行。这样就有个问题，如果玩家随机刷新点是第二天零点50s，而他在第二天零点10s下线，
	* 这样就无法完成刷新，然后他再上线，因为db保存的上次下线时间是第二天0点10s，所以上线后也不会刷新。为了解决这个
	* 问题，在玩家下线的时候判断下是否过了真正的12点，并且还没到随机出来的整点刷新时间，如果是，就执行一次NewDayArrive的刷新。
	*/
	void PreCloseActor();

	// 计算物品的总数量，用于后台报警
	void LimitItemCount();

	/*
	* Comments:定期检查玩家所在的区域属性，做相应的处理
	* @Return void:
	*/
	void TimeCheckAreaAttri(int x, int y);

	void ReturnToCrossWar();
	bool WillReturnToCrossWar();

	void GetSpecialDataForPhp(ActorBasicData* data);

	void ShowZhanLing(int64_t curr_t);

	//检测月卡是否到期
	void OnMonthCardCheck(void);

	// 检测特权月卡是否到期
	void OnPrivilegeMonthCardCheck(void);
	
public:
	bool RoleHasTarget(void);
	const char* GetServerName();


	void setPkMode(int mode) { basic_data_->field_pk_mode = mode; };
	//int GetRealLevel();
public:
	// 发送数据有效性标识
	static void SendDataValid(int serverId, ActorId actorId, bool flag, int targetSid = 0);
#if (defined _DEBUG) && (defined _MSC_VER)
public:
	static LONG PacketAlloced;
	static const char* PacketAllocFile;
	static int PacketAllocLine;
#endif
public:

	bool					first_login_; //是否是第一次登录
	bool					logined_;	//是否登陆完成

	unsigned int			enter_fb_sid_; //进入副本前的位置
	int						enter_fb_x_;    //进入副本前x的坐标
	int						enter_fb_y_;  //进入副本前的y的坐标
	//这里是一些不需要客户端知道的属性，放这里，免得每次加一个属性，客户端都需要修改
	static int				save_db_interval_;	// 玩家存盘间隔

	StaticArrayList<EntityHandle, MAX_ATTACK> attack_list_;	// 最近攻击自己的玩家列表
	StaticArrayList<VestMonster, MAX_VEST_MONSTER> vest_monster_list_; // 归属的怪物列表，加到这个列表后会有经验加成

	//进入新场景，baby按新设定的位置进去
	int					new_pet_x_;
	int					new_pet_y_;
	bool					force_pet_pos_;

	// 跨服相关
	int					cw_serverid_;	// 上次跨服时进入的服务器id,没有则为0
	unsigned			cw_fbhdl_;		// 跨服的副本handle
	int					cw_sceneid_;	// 跨服场景id
	int					cw_x_;			// 跨服的x，y
	int					cw_y_;

	int					cw_static_sceneid_;	// 跨服进入副本前的场景id
	int					cw_static_x_;		// 跨服进入副本前的的x，y
	int					cw_static_y_;

	bool				waitForCross_;

	/**仅从战斗服跳到普通服副本时使用**/
	unsigned			comm_fb_hdl_;	//普通服的副本handl
	int					comm_sceneid_;	//普通服场景id
	int					comm_x_;		//普通服的x，y
	int					comm_y_;

	bool				deny_see_actor_;	//是否不可以看见其他玩家(true为看不见其他玩家) 场景属性设置
	bool				can_see_;		//是否不可以看见其他玩家(true为看不见其他玩家) 角色属性设置
	
	Vector<AttackBack> attack_back_;	//特殊场景中 和平模式下 攻击自己的玩家列表和反击时间

	bool				hasChangePkMode;		//切换场景后是否已经切换过pk模式了

	int		protect_skill_id_;	//护符装备附加的技能id
	int		protect_skill_level;	//护符装备附加的技能等级

	int64_t			show_zhanling_t_;		//上次显示战灵的时间
	static int		show_zhanling_cd_;		//显示战灵的CD
	static int		show_zhanling_delay_;		//延迟显示战灵
	int				zhanling_id_;			//战灵皮肤编号
	int				zhanling_lv_;			//战灵等级
	int				zhanling_talent_effid_;	//战神附体buff id
	std::map<int, int> zhanling_effids_;  //战灵外显触发的buff列表
	bool				need_hide_pack_;//是否需要屏蔽数据包
	std::set<int64_t>	need_pack_list_;//屏蔽后,需要数据包的handle
	
private:
	static UpdateMask* broadcastMask_; //那些属性需要发送到客户端
	DataPackList*			net_packs_;	// 网络消息缓冲
	NetId					netid_;

	RoleSystem*				role_sys_; // 角色系统
	ItemBag*				item_bag_; // 物品背包
	EquipBag*				equip_bag_; // 装备背包
	LuaVarSystem*			var_sys_;//玩家变量系统
	MailSystem*				mail_sys_;//邮件系统
	ZhuanShengSystem*		zhuansheng_sys_; // "传奇特色" 转生系统
	StoreSystem*			store_sys_;	//商店系统
	Depot*					depot_;		//仓库
	TitleSystem*			title_sys_;	// 称号系统
	GuildSystem*			guild_sys_; //公会系统
	MsgSystem*              msg_sys;//登录读数据回调处理
	ActorExRingSystem*		actor_ex_ring_sys_;//角色的特戒系统
	TogetherHitSystem*		together_hit_sys_;//合击系统
	ImbaSystem*	imba_sys_;//新神器
	GodWeaponSystem* god_weapon_sys_; //神兵系统
	WarSystem*				war_sys_;//跨服系统

//	MsgSystem				msg_sys_;
	Attribute				knighthood_attr_; //爵位属性
	Attribute				artifacts_attr_; //神器属性
	Attribute				trainsystem_attr_; //历练属性
	Attribute				challengefbsystem_attr_;//挑战副本属性
	Attribute				ronglu_attr_;//熔炉属性
	Attribute				actorexring_attr_; //玩家特戒属性
	Attribute               actor_attr_[attrMax];  // actor统一属性数组
	Attribute               mongthCard_attr_;  // 月卡属性
	Attribute				privilege_attr_; //贵族属性
	Attribute				vip_attr_; //vip属性
	Attribute				new_world_boss_attr_;//新世界boss的副本内属性
	Attribute				yupei_attr_;//玉佩的属性
	Attribute				perstige_attr_;//威望属性
	Attribute				reincarnate_attr_;//轮回属性
	//Attribute				...
	//Attribute				...

	ExAttribute				knighthood_ex_attr_;//爵位扩展属性
	ExAttribute				trainsystem_ex_attr_; //历练扩展属性
	ExAttribute				god_weapon_ex_attr_; //神兵扩展属性
	ExAttribute				yupei_ex_attr_;//玉佩的扩展属性
	ExAttribute				reincarnate_ex_attr_;//轮回扩展属性

	int						account_id_; //账号的ID
	ACCOUNT					account_name_;	//玩家账号字符串
	ActorId					actor_id_;
	int						serverId_;	// 玩家是哪个服的，（为了跨服）

	SecondTime				login_t_;		//本次的登录时间
	SecondTime				logout_t_; //上次的登出时间
	SecondTime				create_t_;	//角色创建时间
	ActorPacket				fastPacket_;

	uint16_t				relive_sid_;//普通场景复活点的场景id
	uint16_t				relive_x_;//普通场景复活点的x坐标
	uint16_t				relive_y_;//普通场景复活点的y坐标

	uint16_t				city_relive_sid_;	//回城点场景id
	uint16_t				city_relive_x_;		//回城点x坐标
	uint16_t				city_relive_y_;		//回城点Y坐标

	uint16_t				fb_relive_sid_;	//副本的复活点场景id
	uint16_t				fb_relive_x_;		//副本复活点的x坐标
	uint16_t				fb_relive_y_;		//副本复活点的y坐标

	uint16_t				unreload_map_sid_;	//普通场景中，非重配地图的场景id
	uint16_t				unreload_map_x_;	//普通场景中，非重配地图的场景x坐标
	uint16_t				unreload_map_y_;	//普通场景中，非重配地图的场景y坐标
	SecondTime				tomorrowDateTime_;			// 指示明天的开始时间，也就是今天的结束时间，用于24点的刷新处理（活动、任务等逻辑）
	SecondTime				tomorrowWeeHoursTime_;		// 指示明天凌晨六点的开始时间，凌晨六点的刷新处理（活动、任务等逻辑）


	// 上次检查传送门时的坐标，用于避免重复检查传送门
	int						last_check_door_x_;
	int						last_check_door_y_;

	Timer				m_t1s; //1秒定时器
	Timer				m_t1minute; //1分定时器

	Timer				db_timer_;//存盘定时器,5分钟存盘一次
	Timer				clear_vest_timer_;		// 清除怪物归属定时器

	int64_t				last_battle_;	// 最后添加战斗状态的时间
	int64_t				last_pk_;		// 最后添加pk状态的时间
	BabyList			baby_list_;			// 实体拥有的BB列表

	char				last_login_ip_[32];  //此ip是客户端报过来的，只用于数据上报，并不一定准确
	char				pf_[PFSTR_MAX_LEN];//平台简称,dkm
	char				pf_id_[PFID_MAX_LEN];//平台ID,dkm对应的平台ID,数字
	char				appid_[APPID_MAX_LEN];//渠道ID, 同一个平台下的多个渠道
	// 除杀死自己的玩家外最后一个攻击自己的玩家
	ActorId				last_attacker_;

	int					init_flag_;	// 用于判断用户数据是否加载完全
	bool				is_image_;	// 是否是镜像
	int					image_end_time_; // 镜像的超时时间

	ActorBasicData*		basic_data_;	// 保存从数据库中读取的原始数据，避免数据丢失

	// 用户的网络包的id号，客户端每发一个包上来带一个id，后一个包的id必须比前一个大，这个用于监测客户端有没有发重复的包
	int					net_pack_id_;
	int					err_net_pack_id_;
	int					gm_level_;
	int					toge_lv_;//合击技能等级
	int					yupei_lv_;	//玉佩等级
	int					flamestamp_lv_; //烈焰印记等级
	int					flamestamp_skill_lv_[MAX_FLAMESTAMP_SKILL]; //烈焰印记技能等级

	GatherMonster*		curr_gather_monster_ = nullptr; //当前正在采集的怪物

	bool				kick_relogin_; // 踢出他服登录玩家
};

#endif

