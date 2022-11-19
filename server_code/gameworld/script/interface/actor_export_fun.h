/*
	玩家的一些脚本接口的定义，在脚本里使用前加Actor.xx函数，比如：
	Actor.hasQuest(entityPtr,任务id)来获取是否完成了这个任务
*/

//tolua_begin
namespace LActor
{

void* getEntity(double handle);
int getId(void* et);
void* getActor(void* et);	// 获取实体最终归属的actor
void* getActorById(const int actorId, bool ignoreinit = false, bool includeImage = false);
int getServerId(void* actor);
int getServerIdById(const int actorid);
void* getActorByName(const char* name);
void* getActorByAccountName(const char* accountName);
int getActorIdByAccountName(const char* accountName);
int getActorIdByName(const char* actorName);


const ActorBasicData* getActorData(void* actor);
const char* getName(void* et);
unsigned int getLevel(void* et);
int getJob(void* et);
int getSex(void* et);
const char* getLastLoginIp(void* et);


// 可以获取离线数据
const ActorBasicData* getActorDataById(int id);
unsigned int getActorLevel(int id);
unsigned int getActorZhuanShengLevel(int id);
const char* getActorName(int id);
double getActorPower(int id);
int getActorJob(int id);
int getActorSex(int id);

// 后面的位置参数是普通服跳到战斗服才有效，如果是从战斗服跳到普通服，全部写0就行
void loginOtherSrv(void* et, int sid, unsigned int fbhdl, int sceneid, int x, int y, const char* reason = "");

void setLevel(void* actor, int level); // 只负责修改
void onLevelUp(void* actor);		// 负责处理
unsigned int getExp(void* actor);
void setExp(void* actor, int exp);

void* getRole(void* actor, int roleId);
void* GetRoleByJob(void* actor, int job);
RoleData* getRoleData(void* actor, int roleId);
int getRoleCount(void* actor);
void createRole(void* actor, int job, int sex);

void changeGold(void *actor, int value, const char* log);
void changeYuanBao(void *actor, int value, const char* log, bool ignore = false);
// 货币值
long long getCurrency(void* actor, int type);
void changeCurrency(void* actor, int type, int value, const char* log);

void giveItem(void *actor, int id, int count, const char* log);
int getEquipBagSpace(void *actor);
void gmClearBag(void* actor, int type);

//实体显示的名字
const char* getShowName(void* et);
double getHandle(void* et);
// 获取离线总时间
int getActorOfflineTime(void* actor);
void exitFuben(void* et);
// 重新进入场景
void reEnterScene(void* actor, int x = 0, int y = 0);
unsigned int getFubenHandle(void* actor);
unsigned int getSceneHandle(void* actor);
void* getFubenPrt(void* actor);
void* getFubenPtr(void* et);
void* getScenePtr(void* et);
int getFubenId(void* actor);
bool isInFuben(void* actor);
bool isBoss(void* creature);
void enterScene(void *et, unsigned int hScene, int x, int y);
void instantMove(void* actor, int x = 0, int y = 0);
int GetFuBenType(void* actor);

int getChapterLevel(void* actor);
void setChapterLevel(void* actor, int level);

int getVipLevel(void* actor);
void setVipLevel(void* actor, int vip);

int getMonthCard(void* actor);
// 充值
int getRecharge(void* actor);
// 充值元宝数, 套餐id
void addRecharge(void* actor, int yb, int itemid = -1);
void addRechargeOffline(int actor_id, int yb, int itemid = -1, int yb_back = 0, std::string orderNum="");

int getEssence(void* actor);
void setEssence(void* actor, int value);

int getExRingLevel(void* role, int id);
void setExRingLevel(void* role, int id, int level);

int getActorExRingLevel(void* actor, int id);
void setActorExRingLevel(void* actor, int id, int level);
bool GetActorExRingIsEff(void* actor, int id);
void SetActorExRingIsEff(void* actor, int id, int eff);
void SetAexringMon(void* clone, int id, void* mon);
void ClearExRingMonster(void* actor, int id);
void AddAerMonAttr(void* clone, int id, int type, double value);
void AddAerMonExAttr(void* clone, int id, int type, int value);

void createSkirmishData(void* actor, int index, int id, int level, const char* name, int attrper);
void createKuangActorData(void* actor, int tactorId);
void createFieldPlayerData(void* actor, int index, int actor_id, int pos_x, int pos_y, int actionType, int isForay, int killNum, int ox, int oy);
bool isDeath(void* et);
void relive(void* et, int x = 0, int y = 0);
int useSkill(void* et, int skillId);
long long int GetSkillLaveCD(void* et, int skillId);
void SetAllRoleSkillCdById(void *actor, int skillId, int cd_time, int mod = 1);
void addSkillEffect(void* et, int effid);
int getMoneyCount(void* actor, int type);
bool enterFuBen(void* et, unsigned int hFb, int sceneId = -1, int x = 0, int y = 0, bool pix = false);

void changeHp(void* et, double nValue, void* killer = NULL);
void setHp(void* et, double hp);
void setMp(void* et, double mp);
void setNp(void* et, double np);
double getHp(void* et);
double getNp(void* et);
double getHpMax(void *et);
double getMpMax(void *et);
double getAttr(void *et, int atype);
double getAtkSum(void *et);
void gmSetAttr(void* actor, int type, double value);
void recover(void* actor);
void sendTipmsg(void* actor, const char* sTipmsg, int nType = ttMessage);
void sendTipWithId(void* actor, int tipId);
void* getActorPtrByName(char* sName);
unsigned int getLoginTime(void* actor);
unsigned int getLastLogoutTime(void* actor);
unsigned int getLastLogoutDate(void* actor);
//获取角色上线的0点时间
unsigned int getLoginDate(void* actor);
//获取静态变量，静态变量在玩家下线时会保存且在玩家上线时会加载
int getStaticVar(lua_State* L);
int getCrossVar(lua_State* L);
int postScriptEvent(lua_State* L);
// 在游戏主循环里下一帧里执行的脚本回调，跟postScriptEvent类似
// 这类函数会更高效！
// 这类型的不能取消！
int nextScriptEvent(lua_State* L);
/*
* Comments: 注销脚本回调函数
* Param void * et: 实体指针
* Param double: 脚本回调句柄
* @Return unsigned int:
*/
void cancelScriptTimer(void* et, double handle);
bool isMonster(void* et);
bool isActor(void* et);
bool isPet(void* et);
int getActorId(void* actor);
int getCloneRoleActorId(void *clone_role);
const char* getAccountName(void* actor);
int getAccountId(void* et);
int getEntityType(void* et);
const char* getPf(void* actor);
const char* getAppid(void* actor);
const char* getPfId(void* actor);
int getCloneRoleIsMirror(void *clone_role); //克隆实体是否为机器人
Attribute* GetCloneRoleAttr(void *clone_role);

int getItemCount(void* actor, int itemId);
void costItem(void* actor, int itemId, int count, char *log);
void reCalcRoleAttr(void* et, int roleId = 0);
void reCalcAttr(void* et);
void reCalcExAttr(void* et);
void reCalcBattleAttr(void* et);

//战力比较
void battleComparison(void* actor, int actorId);

int getWingInfo(lua_State* L);
void setWingLevel(void* actor, int roleId, int level);
void setWingStar(void* actor, int roleId, int star);
void setWingExp(void* actor, int roleId, int exp);
void setWingStatus(void* actor, int roleId, int status);
void setWingCTime(void* actor, int roleId, unsigned int ctime);
void setWingPill(void* actor, int roleId, int idx, int count);
void clearWingAttr(void* actor, int roleId);
void addWingAttr(void* actor, int roleId, int type, int value);
void addWingTempAttr(void* actor, int roleId, int type, int value);
void wingInfoSync(void* actor, int roleId);

int getEnhanceInfo(lua_State* L);
void setEnhanceLevel(void *actor, int roleId, int posId, int level);
void clearEnhanceAttr(void* actor, int roleId);
void addEnhanceAttr(void* actor, int roleId, int type, int value);

int getFulingInfo(lua_State* L);
void setFulingInfo(void *actor, int roleId, int posId, int level, int exp);
Attribute* getFulingAttr(void* actor, int roleId);
ExAttribute* getFulingExAttr(void* actor, int roleId);

int getSoulLevel(void* actor, int roleId, int pos);
void setSoulLevel(void *actor, int roleId, int posId, int level);
Attribute* getSoulAttr(void* actor, int roleId);
ExAttribute* getSoulExAttr(void* actor, int roleId);

Attribute* getJadePlateAttr(void* actor, int roleId);
ExAttribute* getJadePlateExAttr(void* actor, int roleId);

Attribute* getZhiZunAttr(void* actor, int roleId);
ExAttribute* getZhiZunExAttr(void* actor, int roleId);

Attribute* getLeiTingEquipAttrs(void* actor, int roleId);
ExAttribute* getLeiTingEquipExAttrs(void * actor, int roleId);

int getTogetherPunchInfo(lua_State* L);
void setTogetHerEquipLevel(void* actor, int pos, int lv);
Attribute* getTogetherPunchAttr(void* actor);
ExAttribute* getTogetherPunchExAttr(void* actor);

int getMailInfo(lua_State* L);
int getMailList(lua_State* L);
int deleteMail(lua_State* L);
int changeMailReadStatus(lua_State* L);
int changeMailAwardStatus(lua_State* L);

int getStoneInfo(lua_State* L);
void setStoneLevel(void *actor, int roleId, int posId, int level);
void clearStoneAttr(void* actor, int roleId);
void addStoneAttr(void* actor, int roleId, int type, int value);

int getJingmaiInfo(lua_State* L);
void setJingmaiLevel(void* actor, int roleId, int level);
void setJingmaiStage(void* actor, int roleId, int stage);
void clearJingmaiAttr(void* actor, int roleId);
void addJingmaiAttr(void* actor, int roleId, int type, int value);

int getZhulingInfo(lua_State* L);
void setZhulingLevel(void* actor, int roleId, int posId, int level);
void clearZhulingAttr(void* actor, int roleId);
void addZhulingAttr(void* actor, int roleId, int type, int value);

void takeOutEquip(void* actor, int roleId, int posId,int equiptype);
Attribute getEquipAttr(void* actor, int roleId, int posId);
ExAttribute getEquipExAttr(void* actor, int roleId, int posId);
Attribute* getZhuanShengAttr(void* actor);
Attribute* getNeigongAttr(void* actor, int roleId);
Attribute* getExRingAttr(void* role);
ExAttribute* getExRingExAttr(void* role);
Attribute* getActorExRingAttr(void* actor);
ExAttribute* getActorExRingExAttr(void* actor);

Attribute* getActorExRingMonsterAttr(void *actor, int rid);
ExAttribute* getActorExRingMonsterExAttr(void *actor, int rid);
Monster* createActorExRingMonster(void *actor, int rid, int id);
void DestroyBattleRing(void *actor, int rid);
Monster* getActorExRingMonster(void *actor, int rid);
void SetMasterHandle(void *et, void *met);

void changeMonsterAi(void *et, int aid);
Attribute* getTogetherHitAttr(void* actor);
ExAttribute* getTogetherHitExAttr(void* actor);
ExAttribute* getTogetherHitSkillExAttr(void* actor);
Attribute* getActorsystemAttr(void* actor, int attrId);

int getZhuanShengLevel(void* actor);
int getReincarnateLv(void* actor);
int getRoleSkillLevel(void* actor, int roleid, int index);
void upgradeSkill(void* actor, int roleid, int index, int level = 0);

int getRoleSkillBreakLevel(void* actor, int roleid, int index);
void upgradeSkillBreak(void* actor, int roleid, int index);

int getStoreItemData(lua_State* L);
//int giveStoreItem(void* actor, int id);
int giveStoreItem(lua_State* L);

void addStoreItem(void* actor, int id, int itemId, int count, int currencyType, int currency, int discount);
void StoreClearList(void* actor);
void StoreDataSync(void* actor, int refreshCount);

void* getAITarget(void* creature);
void changeAITarget(void* creature, int type = 0);
void setAITarget(void* creature, void* target);
void setAITargetNull(void *creature);
void setAIPassivity(void* creature,bool b);
bool getAIPassivity(void* creature);
void setAIAttackMonster(void* actor);

//int getSoulShieldLevel(void* actor, int roleId, int type);
int getSoulShieldinfo(lua_State* L);
void setSoulShieldLevel(void* actor, int roleId, int type, int level);
void setSoulShieldStage(void* et, int roleId, int type, int stage);
void setSoulShieldExp(void* et, int roleId, int type, int exp);
void setSoulShieldAct(void* et, int roleId, int type, int act);
void clearSoulShieldAttr(void* actor, int roleId);
void addSoulShieldAttr(void* actor, int roleId, int type, int value);

void giveItemToDepot(void* actor, int itemId, int count, const char *log);
int getDepotCount(void* actor);

Attribute* getRoleBasicAttr(void* actor, int roleId);
Attribute* getKnighthoodAttr(void* actor);
ExAttribute* getKnighthoodExAttr(void* actor);
Attribute* getYuPeiAttr(void* actor);
ExAttribute* getYuPeiExAttr(void* actor);
Attribute* getPerstigeAttr(void* actor);
Attribute* getArtifactsAttr(void* actor);
Attribute* getTrainsystemAttr(void* actor);
ExAttribute * getTrainsystemExAttr(void * actor);
Attribute* getChallengefbsystemAttr(void* actor);
Attribute* getRongLuAttr(void* actor);
Attribute* getMonthCardAttr(void* actor);
Attribute* GetReincarnateAttr(void* actor);
ExAttribute* GetReincarnateExAttr(void* actor);
Attribute* getPrivilegeAttr(void* actor);
Attribute* getVipAttr(void* actor);
Attribute* getNewWorldBossAttr(void *actor);
Attribute* getGodWeaponAttr(void* actor);
ExAttribute* getGodWeaponExAttr(void* actor);

unsigned int getCreateTime(void* actor);

void updataEquipBagCapacity(void* actor,int add = 0,int capacity = 0);

bool isImage(void* actor);
int getGmLevel(void* actor);

Attribute* getEquipPointAttrs(void* actor, int role_id);

void* getActorInfoPacket(void* et);
bool GetActorInfo(void* actor, int actor_id);
int findTiantiActor(void* actor);
void createRoldClone(int actor_id,unsigned int scene,int x,int y,int sid = 0,int camp = 0);
void* createRobot(RobotData* data, unsigned int scene, int x, int y);
bool cloneRoleEmpty(unsigned int scene);
void tiantiRefreshWeek(void);

Attribute* getEquipBlessAttrs(void* actor, int role_id);
Attribute* getTitleAttrs(void* et);
void reCalcTitleAttr(void* et);

void setRoleTitle(void* et, int roleId, int tId);

void changeMiJi(void* actor, int roleid, int oldId, int id, bool refresh, int param1, int param2, int param3, int power);
void refreshMiJi(void* actor, int roleid);

void* getRankCacheByType(int type,int min, int max);
void regAsynEvent(int actorid);
Attribute* getGuildSkillAttrs(void* actor, int roleId);
int getGuildId(void* actor);
void* getGuildPtr(void* actor);
int getGuildPos(void* actor);
const char* getGuildName(void* actor);
int getTotalGx(void* actor);
void changeTotalGx(void* actor, int val);
void saveDb(void* actorImage);
void changeName(void *et, const char* name, int way = 0);
void setEntityName(void* et, const char* name);
void addEffect(void* actor, int id);

int getItemData(lua_State* L);
int getItemIdByUid(void* actor, double uid);
int getItemInfoByUid(lua_State* L);
bool costItemByUid(void* actor, double uid, int count, const char* log);

void setCamp(void* et,int camp);
int getCamp(void* et);
void setCanChangeCamp(void* et, bool canChange);

void* getLiveByPower(void* actor);
void* getLiveByJob(void* actor);

int getEquipId(void* role, short pos);
int getEquipQuality(void* role, short pos);
int getEquipLevel(void* role, short pos, int &zsLevel);

void setZhanLingConfig(int cd, int delay);
void initZhanLingInfo(void* actor, int id, int level, int effId, int rate);
void setZhanLingId(void* actor, int id);
void addZhanLingEffect(void* actor, int id, int rate);

void* getBattlePet(void* role);
void setZhuangBan(void* actor, int roleindex, int pos1id, int pos2id, int pos3id);
int getZhuangBan(lua_State* L);
Attribute* getRoleZhuangBanAttr(void* actor, int roleindex);
double getMasterHdl(void* et);
void* getMaster(void* et);
void KillMonster(double hdl);
void DestroyEntity(void* et, bool delay = false);


int getOffMsg(lua_State* L);

int getOffMsgCnt(void* et);

int getOffMsgIndex(void* et, double msg_id);

bool deleteOffMsg(void* et, int idx);

void AddSkill(void* et, int id);
void DelSkill(void* et, int id);

void AddAISkill(void* et, int id);
void DelAISkill(void* et, int id);
void DelAllAISkill(void* et);
void DelSkillById(void* et, int id);
void DelAllSkill(void* et);
void AddPassiveSkill(void* et, int id);
void DelPassiveSkill(void* et, int id);
void DelPassiveSkillById(void* et, int id);

void TogetherHitInfoSync(void* actor);

int getFuWenuIdInfo(lua_State* L);
bool CheckFuWenByPost(void* et,int posid);
void SetFuwen(void* et, int roleId, int posid, double uid);
void FuwenLevelup(void* et, int roleId, int posid, int itemId);
void addFuWenExattr(void*et, int roleid, int type, int value);
void CalcExAttr(void*et, int roleid);
void clearFuWenAttr(void* et, int roleId);
void addFuWenAttr(void* et, int roleId, int type, int value);
Attribute* getFuWenAttr(void* et, int roleId);

void addImbaExattr(void*et, int type, int value);
void clearImbaAttr(void* et);
void addImbaAttr(void* et, int type, int value);
Attribute* getImbaAttr(void* et);

int getPosition(lua_State* L);
int getOriginPosition(lua_State* L);
int getDropBagData(lua_State* L);

void SetInvincible(void* et, bool res);

void* getActorByEt(void* et);

void clearImbaActId(void* actor);
void addImbaActId(void* actor, int id);

void clearGodWeaponActId(void* actor);
void addGodWeaponActId(void* actor, int idx, int id);
void setGodWeaponPeak(void* actor, int peak);
void setGodWeaponLevel(void* actor, int level);
void setGodWeaponPower(void* actor, int job, int power);
void clearGodWeaponPower(void* actor);

int getHeirloomLv(void* actor, int roleId, int slot);
void setHeirloomLv(void* actor, int roleId, int slot, int lv);
Attribute* GetHeirloomAttrs(void* actor, int role_id);
Attribute* GetWeaponSoulAttrs(void* actor, int role_id);
ExAttribute* GetWeaponSoulExAttrs(void* actor, int role_id);
Attribute* GetGodWingAttrs(void* actor, int role_id);
Attribute* GetCampBattleAttrs(void* actor, int role_id);
Attribute* GetReincarnateEquipAttr(void* actor, int role_id);
ExAttribute* GetReincarnateEquipExAttr(void* actor, int role_id);
ExAttribute* GetGodWingExAttrs(void* actor, int role_id);
ExAttribute* GetWingExAttrs(void* actor, int role_id);
int getUseingWeaponSoulId(void* actor, int role_id);
void setUseingWeaponSoulId(void* actor, int role_id, int id);
int TuJianPower(void* actor);
int getEquipBasePower(void* actor);
bool hasJobRole(void* actor, int job);
void SetTogeLv(void* actor, int lv);
void SetYuPeiLv(void* actor, int lv);
bool InSafeArea(void* actor);
void stopAI(void* actor);
int getSceneAreaIParm(lua_State* L);

void RequestFubenPathLine(void* role, int x, int y);
void MonsterFubenPathLine(void* role, int x, int y);
int getSceneId(void* actor);

bool clearAttrs(void* actor, int roleId, int attrSysId);
bool addAttrsBaseAttr(void* actor, int roleId, int attrSysId, int type, int value);
bool addAttrsExaPower(void* actor, int roleId, int attrSysId, int power);
Attribute* getAttrs(void* actor, int roleId, int asid);

void AddSkillRevise(void* et, int skillId, int cd = 0, double a = 0, int b = 0);
void AddSkillReviseSelfBuff(void* et, int skillId, int buffId);
void AddSkillReviseTarBuff(void* et, int skillId, int buffId);
void SetFlameStampLv(void* actor, int level);
void SetFlameStampSkillLv(void* actor, int skillId, int level);
void SetSkillCdById(void *et, int skillId, int cd_time);

bool CIsEquip(int equipID);

void AddPVMRecord(int actorid, int targetid, int result, int changerank, int targetrank, int recordtime);

void UpdataRank(int actorid, int newrank);

void SendPVMRank(void* actor, int Limit, int flag);

void SendPVMRecord(void* actor);

void InitMaxRecordCount(int max_count);

int GetPlayerIDByPVMRank(int irank);

int GetPVMRankByPlayerID(int actorid);

int GetPVMRankSize();

void UpdataPvmRankOldData();

int GetZhulingToitalLv(void* actor);

int GetStoneTotalLv(void* actor);

};
//tolua_end

