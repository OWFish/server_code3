#ifndef _ACTOR_H_
#define _ACTOR_H_

/***************************************************************
*                     ��ҵ�ʵ��
***************************************************************/

//todo ����������
#include <cstdarg>
#include "lua_var_system.h"
//#include "offlinemsg/msg_system.h"


#define MAX_ATTACK	10	// ���湥���Լ�����������
#define MAX_VEST_MONSTER	5
#define IMAGE_ACTOR_CACHE_TIME 600
#define MAX_FLAMESTAMP_SKILL 7 //����ӡ�Ǽ��ܸ���

struct VestMonster
{
	EntityHandle handle_;
	unsigned int end_time_;
	bool vest_; // �Ƿ������
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
	//virtual void OnAttacked(Animal* pEntity);  //������

	//��ʼ��ʵ��Ĺ㲥��mask����Щ��������Ҫ�㲥��
	static void InitBroadcastMask();
	static void DestroyBroadcastMask() { SafeDelete(Actor::broadcastMask_); }


	bool IsImage() { return is_image_; }
	void SetImage(bool isImage);
	void SetImageEndTime(int endTime) { image_end_time_ = endTime; }
	int GetImageEndTime() { return image_end_time_; }
	void SetKickRelogin(bool iskick) { kick_relogin_ = iskick; }
	void NoticeRelogin();

	const ActorBasicData* GetBasicData() { return basic_data_; }

	//��ȡ��ɫID
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

	// ����
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

	// ��ֵ���
	int GetRecharge() { return basic_data_->recharge; }
	void AddRecharge(int yb, int itemid = -1, int back_yb = 0, std::string orderNum = "");

	unsigned int GetEssence() { return basic_data_->essence; }
	void SetEssence(unsigned int value) { basic_data_->essence = value; }

	//���ս���Ա�
	void battleComparison( int actorId);

	void ReCalcAttr();
	void ReCalcExAttr();
	void ReCalcBattleAttr();
	// ��������ս�������
	bool WriteRolesData(DataPacket &pack);
	bool CreateCloneData(DataPacket &pack, int attrper = 0); // ��������仯

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
	//inline MsgSystem& GetMsgSystem() { return msg_sys_; }  //��Ϣ��ϵͳ }
	inline int GetPropertySize() const { return sizeof(ActorProperty) - sizeof(PropertySet); }
	inline LuaVarSystem* GetActorVarSystem() { return var_sys_; }   //��ұ���ϵͳ }
	inline CLVariant& GetActorVar() { return var_sys_->GetVar(); }   //��ȡ��ұ��� }

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
	bool GetActorExRingIsEff(int id);//��ȡһ���ؽ��Ƿ��ս
	void SetActorExRingIsEff(int id, bool eff);//����һ���ؽ��Ƿ��ս
	void SetFlameStampLv(int lv) { flamestamp_lv_ = lv; }
	void SetFlameStampSkillLv(int index, int lv) { if (index >= 0 && index < MAX_FLAMESTAMP_SKILL) flamestamp_skill_lv_[index] = lv; }
	int *GetFlameStampData(int &level) { level = flamestamp_lv_; return flamestamp_skill_lv_; }

	/*
	* Comments: ��ȡ���ͻ���,����д�����ݷ����������ݰ���д���Ժ����һ��pack.flush()��д�뷢�ͻ���
	*            ���͵��÷��ο� SendData�ӿ�
	* Param CActorPacket & pack:�ֲ���CActorPacket
	* @Return DataPacket&: ����pack���datapack������ֱ��д������
	*/
#ifdef _DEBUG
	DataPacket& _AllocPacket(ActorPacket& pack, const char* file, int line);
#define AllocPacket(AP) _AllocPacket(AP, __FILE__, __LINE__)
#else
	DataPacket& AllocPacket(ActorPacket& pack);
#endif

	/*
	* Comments: ����ϵͳ��ʾID����ϵͳ��ʾ
	* Param int nTipmsgID:ϵͳ��ʾID
	* Param int nType: ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipmsgWithId(int msgid, int type = ttTipmsgWindow);

	/*
	* Comments: ����ϵͳ��ʾID���壬���и�ʽ������ϵͳ��ʾ
	* Param int nTipmsgID:ϵͳ��ʾID
	* Param int nType: ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipWithId(int msgid, int type = ttTipmsgWindow, ...);

	/*
	* Comments:����ϵͳ��ʾ��Ϣ,�Լ���װ���ˣ�����Ҫ��װ�͵�������ӿ�
	* Param const char* sTipmsg: ��װ�õ��ַ���
	* Param int nType:  ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipmsg(const char* msg, int type = ttTipmsgWindow);

	/*
	* Comments:���в�����ʽ�����ܵķ���ϵͳ��ʾ��Ϣ
	* Param const char* sTipmsg: ��װ�õ��ַ���
	* Param int nType:  ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipmsgFormat(const char* fmt, int type = ttTipmsgWindow, ...);

	//��ͻ��˷��͹��������Ľ��
	void SendOperateResult(bool flag, unsigned int nSendPkgTime = 0);

	/*
	* Comments:�ܹ�ʵ�ֲ�����ʽ�����ܵķ���ϵͳ��ʾ��Ϣ
	* Param const char* sFormat: ��Ϣ��ʽ
	* Param int nType:  ϵͳ��ʾ��ʾ������
	* @Return void:
	*/
	void SendTipmsgWithArgs(const char* fmt, va_list& args, int type);


	/*
	* Comments:����ҷ������ݣ�����ӿ�һ����㲥ʹ�ã����һ������ݰ���ʹ��AllocPacket����Ȼ����
	* Param char * pData: ����ָ��
	* Param size_t size: ���ݴ�С
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
	* Comments: ��ҵ�½
	* Param UINT_PTR nSocket: socketID
	* Param UINT_PTR nActorID: ��ҵĽ�ɫID
	* Param UINT_PTR nGateSessionID: �������ϵ�sessionID
	* Param UINT_PTR nGateIndex: ���ر��
	* Param UINT_PTR nServerSessionId: �ڷ������ϵ�sessionID
	* Param UINT_PTR nAccountID:��ҵ��ʻ�ID
	* Param int  nFcmTime: �����Ե�ʱ��
	* Param int  nGmLevel: ��ҵ�GM�ȼ�
	* Return void:
	*/
	void Onlogin(NetId netid, ActorId actorId, int accountId, int gm_level);

	//�Ƿ���Ҫ�����ط��͹رյ���Ϣ
	void CloseActor(const char* reason, bool notic_gate = true); // �ر�����

	void LogicRun(int64_t curr_t);

	void ChangeBabySpeed();

	// bLogout: Ϊtrue���������ߡ�����Ϊ��ʱ����
	void SaveDb(bool bLogout = false); //����
	void OnDbReturnData(int cmd, DataPacketReader& reader);

	inline int GetAccountId() { return account_id_; }
	inline const char* GetAccount() { return account_name_; }


	//�յ��������ݰ�
	void PostNetMsg(DataPacket* data, int nid);

	// �յ�������
	void OnRecvBeat(unsigned int send_beat_t);
	/*
	* Comments:��NPC��̸�Լ�ִ�нű�
	* Param EntityHandle & NpcHandle:
	* Param const char* sFunctionName:�ű�Ҫִ�еĺ������Ͳ�����Ϣ
	* @Return void:
	*/
	void NpcTalk(const EntityHandle& NpcHandle, const char* sFunctionName);

	/*
	* Comments:���������ڵ��¼�����ʱ���õĺ����������ڻ����ȫ�ֵĽű�ִ��
	* Param int CScriptValueList & paramList:�����б�
	* Param int CScriptValueList & retParamList:���ز����б�
	* @Return void:
	*/
	bool OnEvent(ScriptValueList* params = NULL, ScriptValueList* retval = NULL);

	bool CallFunc(const char* func, ScriptValueList* params, ScriptValueList* retval);

	/*
	* Comments: ��ʼ��һ���¼����õ�CScriptValueList����Ҫ
	  ���Լ���ָ����¼���ָ��ѹ��
	* Param CScriptValueList & paramList: �����б�
	* Param int nEventID: �¼�ID
	* @Return void:
	*/
	inline void InitActorEventParams(ScriptValueList& params, int eid)
	{
		params << this;
		params << eid;
	}
	/*
	* Comments: ��ȡһ������ϵ��λ
	* Param int nMaskID: maskID,������SystemParamDef.h���
		enum tagSocialMaskDef
		{
		smGuildCommon=0,    //�����ͨ��Ա
		smGuildTangzhu=1,    //����
		smGuildAssistLeader=2, //������
		smGuildLeader=3,     //����
		};
	* @Return bool: ��������˾ͷ���true,���򷵻�false
	*/
	//inline bool GetSocialMask(int nMaskID)
	//{
	//	return (GetUIntProp(P_SOCIAL) & (1 << nMaskID)) ? true : false;
	//}

	unsigned int GetLastLogoutTime() { return logout_t_; }
	unsigned int GetLoginTime() { return login_t_; }
	inline unsigned int GetCreateTime() { return create_t_; }
	//��ȡCActorPacket
	inline ActorPacket& GetFastPacket() { return fastPacket_; }

	/*
	* Comments:�ý�ɫ�˳��������ص����泡����λ���ǽ��븱��ǰ����ĳ��泡����λ�ã�
	* �����ɫ�Ѿ��ڳ��泡���У���������
	* @Return void:
	*/
	bool ReturnToStaticScene();
	void ExitFubenScene();
	void ReturnCity();
	void ReEnterScene(int x = 0, int y = 0);

	//���һ����ʼ�����裬�����Ҫ��������ݳ�ʼ����װ���ĳ�ʼ���ͼ��ܵĳ�ʼ�����·�����
	void OnFinishInitStep(int step);
	bool CheckInitStep(int step) { return (init_flag_ & (1 << step))> 0; }

	//װ�����������Ӽ���
	void AddProtectSkill(int skillId, int level);
	//����װ���ļ���Ч��
	void ProtectSkillEffect();
	//����װ���ļ���ս����
	int ProtectSkillFightValue();

	void OnFirst();
	void Relive(int x = 0, int y = 0);
	void OnRelive();

	void OnInit();
	//��ҽ�ɫ�������ˣ��Ѿ����ͻ��˷��˴��������ݰ���
	void OnEnterGame();

	//��ȡ���븱��ǰ��λ��
	void GetEnterFbPos(int& sid, int& x, int& y);

	//ɾ���������buff
	void RemoveReliveProtectState();

	/*
	* Comments: ��ȡ��Ǯ������
	* Param int nMoneyType:��Ǯ������
	* @Return char *:���ؽ�Ǯ�����֣�����Ԫ������yb,��Ԫ������byb,��������coin,�󶨷���bcoin
	*/
	static const char* GetMoneyTypeDesc(int nMoneyType);

	// �ж�ĳ��ϵͳ�Ƿ��Ѿ�����
	bool IsSysOpen(int sysId);
	// ����ĳ��ϵͳ
	void OpenSys(int sysId);

	// ��ȡ���VIP�ȼ�
	int GetVIPLevel();

	void OnExitFuben(int id, unsigned int hfb, int way);
	void OnEnterFuben(int id, unsigned int hfb, int way);

	// ���Ż�ȡ������Ч
	//void PlayExpEffect(int nexp);

	// ���Ż�ȡ��Ʒ��Ч
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

	// �����ɱ���Լ�����������һ�������Լ�����ҵ�id
	void SaveLastAttackId(ActorId aid) { last_attacker_ = aid; }
	ActorId GetLastAttackId() { return last_attacker_; }

	//���ڴ��������ϱ����ӿ�6.20��
	void sendDcApiLog(int systemId, int protoId, int protoType, int protoResult);

	void SetServerId(int sid) { serverId_ = sid; }
	int GetServerId() { return serverId_; }
	void putActorInfo2Pack(DataPacket& pack);
	void SetCurrGatherMonster(GatherMonster* m) { curr_gather_monster_ = m; }
	GatherMonster* GetCurrGatherMonster(void) {return curr_gather_monster_;}

	// ������
	void LoginOtherSrv(int sid, bool newpos, unsigned int fbhdl, int sceneid, int x, int y, const char* reason);
	// �������ͨ������λ�ã���ʵ�����������Ŀ����Ϊ���ڿ��ս�в�������ҽ�����ͨ����
	void ResetStaticFbPos()
	{
		enter_fb_sid_ = enter_fb_x_ = enter_fb_y_ = 0;
	}

	// ��ȡ���������б�
	void AddVestMonster(Monster* mon, unsigned int end_time, bool isVest);
	// ��ȡ������������
	int GetVestMonsterCount()
	{
		return vest_monster_list_.count();
	}
	// ��ȡ�����������ӳ�
	float GetVestExpRate();

	// ��ȡActor����role��ûdead����ս����ߵģ���dead�Ļ�����NULL
	Role* GetLiveByPower();
	Role* GetRandomLiveRole();
	Role* GetLiveByJob();
	int getDeathCount();
	double GetAtkSum();
private:

	void SendBasicData(bool flag); //�������Ǵ�������Ϣ���ͻ���
	void CloseImageActor();
	/*
	* Comments: �µ�һ�쵽����صĴ���
	* Param bool login: �Ƿ��¼�������
	* @Return void:
	*/
	void OnNewDayArrive(bool login = false);

	/*
	* Comments: �µ��賿���㵽����صĴ���
	* Param bool login: �Ƿ��¼�������
	* @Return void:
	*/
	void OnNewDayHoursArrive(bool login = false);

	/*
	* Comments: ��ҵ�½�ǳ�ʼ������ʱ��㣨����ڵ�ǰ��½ʱ�������죩
	* @Return void:
	*/
	void InitTomorrowDateTime();

	/*
	* Comments: ��ҵ�½ʱ��ʼ������ʱ��㣨����ڵ�ǰ��½ʱ�������죩
	* @Return void:
	*/
	void InitTomorrowWeeHoursTime();

	/*
	* Comments: �������ʱ����Ƿ�ʱ
	* @Return void:
	*/
	void CheckTomorrowTimePoint();

	void CheckNewWeek(bool login = false);

	/*
	* Comments: ���׼������
	* @Return void:
	* @Note: ��Ҫ����ʱ������صĲ��乤������ΪNextDayArrive 24������ˢ��ʵ����Ϊ�˷�ɢѹ������������׼�㣬
	* ���Ƿ��䵽����60sʱ����ִ�С��������и����⣬���������ˢ�µ��ǵڶ������50s�������ڵڶ������10s���ߣ�
	* �������޷����ˢ�£�Ȼ���������ߣ���Ϊdb������ϴ�����ʱ���ǵڶ���0��10s���������ߺ�Ҳ����ˢ�¡�Ϊ�˽�����
	* ���⣬��������ߵ�ʱ���ж����Ƿ����������12�㣬���һ�û���������������ˢ��ʱ�䣬����ǣ���ִ��һ��NewDayArrive��ˢ�¡�
	*/
	void PreCloseActor();

	// ������Ʒ�������������ں�̨����
	void LimitItemCount();

	/*
	* Comments:���ڼ��������ڵ��������ԣ�����Ӧ�Ĵ���
	* @Return void:
	*/
	void TimeCheckAreaAttri(int x, int y);

	void ReturnToCrossWar();
	bool WillReturnToCrossWar();

	void GetSpecialDataForPhp(ActorBasicData* data);

	void ShowZhanLing(int64_t curr_t);

	//����¿��Ƿ���
	void OnMonthCardCheck(void);

	// �����Ȩ�¿��Ƿ���
	void OnPrivilegeMonthCardCheck(void);
	
public:
	bool RoleHasTarget(void);
	const char* GetServerName();


	void setPkMode(int mode) { basic_data_->field_pk_mode = mode; };
	//int GetRealLevel();
public:
	// ����������Ч�Ա�ʶ
	static void SendDataValid(int serverId, ActorId actorId, bool flag, int targetSid = 0);
#if (defined _DEBUG) && (defined _MSC_VER)
public:
	static LONG PacketAlloced;
	static const char* PacketAllocFile;
	static int PacketAllocLine;
#endif
public:

	bool					first_login_; //�Ƿ��ǵ�һ�ε�¼
	bool					logined_;	//�Ƿ��½���

	unsigned int			enter_fb_sid_; //���븱��ǰ��λ��
	int						enter_fb_x_;    //���븱��ǰx������
	int						enter_fb_y_;  //���븱��ǰ��y������
	//������һЩ����Ҫ�ͻ���֪�������ԣ���������ÿ�μ�һ�����ԣ��ͻ��˶���Ҫ�޸�
	static int				save_db_interval_;	// ��Ҵ��̼��

	StaticArrayList<EntityHandle, MAX_ATTACK> attack_list_;	// ��������Լ�������б�
	StaticArrayList<VestMonster, MAX_VEST_MONSTER> vest_monster_list_; // �����Ĺ����б��ӵ�����б����о���ӳ�

	//�����³�����baby�����趨��λ�ý�ȥ
	int					new_pet_x_;
	int					new_pet_y_;
	bool					force_pet_pos_;

	// ������
	int					cw_serverid_;	// �ϴο��ʱ����ķ�����id,û����Ϊ0
	unsigned			cw_fbhdl_;		// ����ĸ���handle
	int					cw_sceneid_;	// �������id
	int					cw_x_;			// �����x��y
	int					cw_y_;

	int					cw_static_sceneid_;	// ������븱��ǰ�ĳ���id
	int					cw_static_x_;		// ������븱��ǰ�ĵ�x��y
	int					cw_static_y_;

	bool				waitForCross_;

	/**����ս����������ͨ������ʱʹ��**/
	unsigned			comm_fb_hdl_;	//��ͨ���ĸ���handl
	int					comm_sceneid_;	//��ͨ������id
	int					comm_x_;		//��ͨ����x��y
	int					comm_y_;

	bool				deny_see_actor_;	//�Ƿ񲻿��Կ����������(trueΪ�������������) ������������
	bool				can_see_;		//�Ƿ񲻿��Կ����������(trueΪ�������������) ��ɫ��������
	
	Vector<AttackBack> attack_back_;	//���ⳡ���� ��ƽģʽ�� �����Լ�������б�ͷ���ʱ��

	bool				hasChangePkMode;		//�л��������Ƿ��Ѿ��л���pkģʽ��

	int		protect_skill_id_;	//����װ�����ӵļ���id
	int		protect_skill_level;	//����װ�����ӵļ��ܵȼ�

	int64_t			show_zhanling_t_;		//�ϴ���ʾս���ʱ��
	static int		show_zhanling_cd_;		//��ʾս���CD
	static int		show_zhanling_delay_;		//�ӳ���ʾս��
	int				zhanling_id_;			//ս��Ƥ�����
	int				zhanling_lv_;			//ս��ȼ�
	int				zhanling_talent_effid_;	//ս����buff id
	std::map<int, int> zhanling_effids_;  //ս�����Դ�����buff�б�
	bool				need_hide_pack_;//�Ƿ���Ҫ�������ݰ�
	std::set<int64_t>	need_pack_list_;//���κ�,��Ҫ���ݰ���handle
	
private:
	static UpdateMask* broadcastMask_; //��Щ������Ҫ���͵��ͻ���
	DataPackList*			net_packs_;	// ������Ϣ����
	NetId					netid_;

	RoleSystem*				role_sys_; // ��ɫϵͳ
	ItemBag*				item_bag_; // ��Ʒ����
	EquipBag*				equip_bag_; // װ������
	LuaVarSystem*			var_sys_;//��ұ���ϵͳ
	MailSystem*				mail_sys_;//�ʼ�ϵͳ
	ZhuanShengSystem*		zhuansheng_sys_; // "������ɫ" ת��ϵͳ
	StoreSystem*			store_sys_;	//�̵�ϵͳ
	Depot*					depot_;		//�ֿ�
	TitleSystem*			title_sys_;	// �ƺ�ϵͳ
	GuildSystem*			guild_sys_; //����ϵͳ
	MsgSystem*              msg_sys;//��¼�����ݻص�����
	ActorExRingSystem*		actor_ex_ring_sys_;//��ɫ���ؽ�ϵͳ
	TogetherHitSystem*		together_hit_sys_;//�ϻ�ϵͳ
	ImbaSystem*	imba_sys_;//������
	GodWeaponSystem* god_weapon_sys_; //���ϵͳ
	WarSystem*				war_sys_;//���ϵͳ

//	MsgSystem				msg_sys_;
	Attribute				knighthood_attr_; //��λ����
	Attribute				artifacts_attr_; //��������
	Attribute				trainsystem_attr_; //��������
	Attribute				challengefbsystem_attr_;//��ս��������
	Attribute				ronglu_attr_;//��¯����
	Attribute				actorexring_attr_; //����ؽ�����
	Attribute               actor_attr_[attrMax];  // actorͳһ��������
	Attribute               mongthCard_attr_;  // �¿�����
	Attribute				privilege_attr_; //��������
	Attribute				vip_attr_; //vip����
	Attribute				new_world_boss_attr_;//������boss�ĸ���������
	Attribute				yupei_attr_;//���������
	Attribute				perstige_attr_;//��������
	Attribute				reincarnate_attr_;//�ֻ�����
	//Attribute				...
	//Attribute				...

	ExAttribute				knighthood_ex_attr_;//��λ��չ����
	ExAttribute				trainsystem_ex_attr_; //������չ����
	ExAttribute				god_weapon_ex_attr_; //�����չ����
	ExAttribute				yupei_ex_attr_;//�������չ����
	ExAttribute				reincarnate_ex_attr_;//�ֻ���չ����

	int						account_id_; //�˺ŵ�ID
	ACCOUNT					account_name_;	//����˺��ַ���
	ActorId					actor_id_;
	int						serverId_;	// ������ĸ����ģ���Ϊ�˿����

	SecondTime				login_t_;		//���εĵ�¼ʱ��
	SecondTime				logout_t_; //�ϴεĵǳ�ʱ��
	SecondTime				create_t_;	//��ɫ����ʱ��
	ActorPacket				fastPacket_;

	uint16_t				relive_sid_;//��ͨ���������ĳ���id
	uint16_t				relive_x_;//��ͨ����������x����
	uint16_t				relive_y_;//��ͨ����������y����

	uint16_t				city_relive_sid_;	//�سǵ㳡��id
	uint16_t				city_relive_x_;		//�سǵ�x����
	uint16_t				city_relive_y_;		//�سǵ�Y����

	uint16_t				fb_relive_sid_;	//�����ĸ���㳡��id
	uint16_t				fb_relive_x_;		//����������x����
	uint16_t				fb_relive_y_;		//����������y����

	uint16_t				unreload_map_sid_;	//��ͨ�����У��������ͼ�ĳ���id
	uint16_t				unreload_map_x_;	//��ͨ�����У��������ͼ�ĳ���x����
	uint16_t				unreload_map_y_;	//��ͨ�����У��������ͼ�ĳ���y����
	SecondTime				tomorrowDateTime_;			// ָʾ����Ŀ�ʼʱ�䣬Ҳ���ǽ���Ľ���ʱ�䣬����24���ˢ�´������������߼���
	SecondTime				tomorrowWeeHoursTime_;		// ָʾ�����賿����Ŀ�ʼʱ�䣬�賿�����ˢ�´������������߼���


	// �ϴμ�鴫����ʱ�����꣬���ڱ����ظ���鴫����
	int						last_check_door_x_;
	int						last_check_door_y_;

	Timer				m_t1s; //1�붨ʱ��
	Timer				m_t1minute; //1�ֶ�ʱ��

	Timer				db_timer_;//���̶�ʱ��,5���Ӵ���һ��
	Timer				clear_vest_timer_;		// ������������ʱ��

	int64_t				last_battle_;	// ������ս��״̬��ʱ��
	int64_t				last_pk_;		// ������pk״̬��ʱ��
	BabyList			baby_list_;			// ʵ��ӵ�е�BB�б�

	char				last_login_ip_[32];  //��ip�ǿͻ��˱������ģ�ֻ���������ϱ�������һ��׼ȷ
	char				pf_[PFSTR_MAX_LEN];//ƽ̨���,dkm
	char				pf_id_[PFID_MAX_LEN];//ƽ̨ID,dkm��Ӧ��ƽ̨ID,����
	char				appid_[APPID_MAX_LEN];//����ID, ͬһ��ƽ̨�µĶ������
	// ��ɱ���Լ�����������һ�������Լ������
	ActorId				last_attacker_;

	int					init_flag_;	// �����ж��û������Ƿ������ȫ
	bool				is_image_;	// �Ƿ��Ǿ���
	int					image_end_time_; // ����ĳ�ʱʱ��

	ActorBasicData*		basic_data_;	// ��������ݿ��ж�ȡ��ԭʼ���ݣ��������ݶ�ʧ

	// �û����������id�ţ��ͻ���ÿ��һ����������һ��id����һ������id�����ǰһ����������ڼ��ͻ�����û�з��ظ��İ�
	int					net_pack_id_;
	int					err_net_pack_id_;
	int					gm_level_;
	int					toge_lv_;//�ϻ����ܵȼ�
	int					yupei_lv_;	//����ȼ�
	int					flamestamp_lv_; //����ӡ�ǵȼ�
	int					flamestamp_skill_lv_[MAX_FLAMESTAMP_SKILL]; //����ӡ�Ǽ��ܵȼ�

	GatherMonster*		curr_gather_monster_ = nullptr; //��ǰ���ڲɼ��Ĺ���

	bool				kick_relogin_; // �߳�������¼���
};

#endif

