#ifndef _DB_DATA_CLIENT_H_
#define _DB_DATA_CLIENT_H_

#define GetIntProp GetProperty<int>
#define SetIntProp SetProperty<int>
#define SetIntPropEx SetPropFromSet<int>

#define GetUIntProp GetProperty<unsigned int>
#define SetUIntProp SetProperty<unsigned int>

#define GetFloatProp GetProperty<float>
#define SetFloatProp SetProperty<float>

class DBSessionMgr;
class DataPacket;

struct VariableDataFlag{
	const char* fieldName_;
	int protoId_;
	int cache_type_;
};

class DBSession
	: public NetSession
{
	friend class DBSessionMgr;
	friend class DBDataCache;
	struct GMData
	{
		int id_;
		char cmd_[256];
		char param1_[256];
		char param2_[256];
		char param3_[256];
		char param4_[256];
		char param5_[256];
		int	 cmdid_;
	};
public:
	typedef NetSession Inherited;
public:
	DBSession(DBSessionMgr* mgr, SQLConnection* sql, SOCKET s, sockaddr_in* addr);
	~DBSession();

	inline const char* serverName()
	{
		return srv_name_;
	}
	SQLConnection* GetSQL()
	{
		return sql_;
	}
	bool IsBattleSrv()
	{
		return battleflag_ == 1;
	}

	char* getHugeBuf() { return huge_buf_; }

protected:
	//覆盖连接断开的函数
	void OnDisconnected();

	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);

	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	void processNetMsg(const uint16_t cmd, DataPacketReader& data);

	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regData);
public:
	//大型SQL查询语句缓冲长度
	static const size_t HUNGSIZE = 1024 * 1024 * 8;

protected:
	void OnDefaultSysRecv(int cmd, DataPacketReader& reader);
	bool OnEntitySysRecv(int cmd, DataPacketReader& reader);
	void OnGuildSysRecv(int cmd, DataPacketReader& reader);
	void OnConsignmentSysRecv(int cmd, DataPacketReader& reader);
	void OnMsgSysRecv(int cmd, DataPacketReader& reader);
	void OnMailSysRecv(int cmd, DataPacketReader& reader);
	void OnLoadRank(int cmd, DataPacketReader& reader);
	bool OnGlobalRecv(int cmd, DataPacketReader& reader);
	void OnFightRecv(int cmd, DataPacketReader& reader);
	void OnCommonRecv(int cmd, DataPacketReader& reader);
	void OnGiftItemConfigRecv(int cmd, DataPacketReader& reader);
	void OnRecvCommonDB(int cmd, DataPacketReader& reader);
	void OnRecvAuctionDB(int cmd, DataPacketReader& reader);
	void OnRecvPVMDB(int cmd, DataPacketReader& reader);

	void SaveCSScriptData(DataPacketReader& reader);
	void SaveScriptData(DataPacketReader& reader);
	void SaveItem(DataPacketReader& reader);
	void LoadGiftItem(DataPacketReader& reader);
	void LoadGiftConfig(DataPacketReader& reader);
	void OnWarTeamRecv(int cmd, DataPacketReader& reader);
	//玩家的主表
	void QueryActorFromDB(DataPacketReader& inPacket);
	void QueryActorFromDB(ActorId aid, bool isImage = false);
	static bool SaveActorToDB(DataPacketReader& inPacket, SQLConnection& sql);

	static bool SaveActorCacheToDB(DataPacketReader& inPacket, SQLConnection& sql);
	void QueryActorCacheData(ActorId actorId);

private:
	void QueryRoleData(ActorId actorid);
	static bool SaveRoleData(DataPacketReader& packet, SQLConnection& sql);

	void QueryBagData(ActorId actorid);
	void QueryBagData(ActorId actorid, int bagtype);
	static bool SaveBagData(DataPacketReader& packet, SQLConnection& sql);

	void QueryMailData(ActorId actorid);
	static bool SaveMailData(DataPacketReader& packet, SQLConnection& sql);

	bool QueryStoreData(ActorId actorid);
	static bool SaveStoreData(DataPacketReader& packet, SQLConnection& sql);

	bool QueryTogHitEquipData(ActorId actorid);
	static bool SaveTogHitEquipData(DataPacketReader& packet, SQLConnection& sql);
	//任务的
	//void QueryQuestFromDB(DataPacketReader& inPacket);
	//void QueryQuestFromDB(ActorId nActorId);
	//static void SaveQuestToDB(DataPacketReader& inPacket, SQLConnection& sql);
	//int GetMainQuest(int nActorId,DataPacket& out);
	//int SaveMainQuest(ActorId nActorId, char* pBuf, size_t nSize);
	//int GetGoingQuest(ActorId nActorid, DataPacket& out);
	//static int SaveGoingQuest(ActorId nActorid, int nTaskId, int id, int value, SQLConnection& sql);
	//int GetRepeatQuest(ActorId nActorid, DataPacket& out);
	//static int SaveRepeatQuest(int nActorid, int nTaskId, int qtime, SQLConnection& sql);
	//static int CleanQuestData(ActorId nActorId, SQLConnection& sql);


	//技能相关的
	//void QuerySkillFromDB(ActorId nActorID);  //装置玩家的技能数据
	//static void SaveSkillToDB(DataPacketReader& inPacket, SQLConnection& sql);  //保存技能数据

	bool QueryActorScriptData(ActorId nActorid);               //取脚本数据
	static bool SaveScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql);                //保存脚本数据

	bool QueryActorCsScriptData(ActorId nActorID);
	static bool SaveCsScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql);

	// 法宝系统
	//bool QueryActorGemItemData(ActorId nActorId);					// 获取角色宝物数据
	//static void SaveActorGemItemData(DataPacketReader& inPacket, SQLConnection& sql);		// 保存角色宝物数据

	// 每天今日副本次数数据
	//bool QueryActorFbCountData(ActorId actorId);
	//static void SaveActorFbCountData(DataPacketReader& inPacket, SQLConnection& sql);

	// 宠物技能
	//static void SavePetSkill(DataPacketReader& inPacket, SQLConnection& sql);
	//void QueryPetBaseFromDB(ActorId nActorID);
	//static void SavePetBase(DataPacketReader& inPacket, SQLConnection& sql);

	//void QueryMarryInfo(ActorId nActorID);
	//static void SaveMarryInfo(DataPacketReader& inPacket, SQLConnection& sql);
	//void offlineDivorce(DataPacketReader& inPacket, SQLConnection& sql);
	//void offlineSetLogouTime(DataPacketReader& inPacket, SQLConnection& sql);

	// 竞技场系统
	void QueryActorFightData(ActorId aid);

	void QueryPetSkillFromDB(ActorId nActorID);

	//秘籍相关
	//void QueryMijiItem(ActorId nActorID);

	//static void SaveMijiItem(DataPacketReader& inPacket, SQLConnection& sql);
	// 二进制数据
	/*
	* Comments:
	* Param int actorId:
	* Param const char * fieldName:数据库表中的字段名
	* Param int entityId:数据服务器和逻辑服务器通信的命令码EntityMgrId
	* @Returns void:
	*/
	//void QueryActorVariableData(ActorId actorId, const char* fieldName, int entityId);

	void QueryActorVariableList(ActorId actorId, Vector<VariableDataFlag>& fieldList);

	// 从cache中查询玩家二进制数据
	bool QueryActorVariableDataFromCache(ActorId actorId, int type, int cmd);
	/*
	* Comments:
	* Param DataPacketReader & packet:
	* Param const char * fieldName:字段名
	* Param bool bResp:
	* Param int entityId:要求响应时和逻辑服务器通信的命令码
	* @Returns void:
	*/
	static bool SaveActorVariableData(DataPacketReader& packet, const char* fieldName, SQLConnection& sql, int entityId = 0);

	// 查询全局的二进制数据
	//void QueryGlobalVariableData(const char* fieldName, int entityId);

	// 保存全局的二进制数
	//void SaveGlobalVariableData(DataPacketReader& packet, const char* fieldName, int entityId, bool bResp = true);

	void QueryActorSubSystemData(ActorId aid);    //装载各子系统的数据
	void QueryActoSubSystemData1(ActorId aid);    //装载各子系统的数据
	//物品相关的的
	/*
	* Comments:装置玩家的物品
	* Param unsigned int nActorID: 玩家的角色ID
	* Param unsigned int nItemStoreType: 物品的存储类型
		enum tagItemStorageType
		{
		itItemBag=1, //背包里的物品
		itItemEquip =2, //装备物品
		itItemDepot =3, //仓库物品
		};
	* @Return void:
	*/
	//void QueryItems(ActorId nActorID, unsigned int nItemStoreType);

	//仓库物品相关的
	/*
	* Comments:装置玩家的物品
	* Param unsigned int nActorID: 玩家的角色ID
	* Param unsigned int nDepotType: 仓库的类型
	enum itemPos
   {
	  ipStart = 0,
	  ipBag = ipStart,
	  ipDepot,      //玩家仓库
	  ipLottery,    //抽奖仓库
	  ipEntrust,	//委托仓库
	  ipTreasure,	//珍宝囊
	  ipBabel,	    //通天塔仓库

	  ipMax,
    };
	* @Return void:
	*/
	//void QueryDepotItems(ActorId nActorID);
	//void QueryDepotItem(ActorId nActorID, unsigned int nDepotType);


	/*
	* Comments: 保存物品的信息
	* Param DataPacketReader & inPacket: 读写器
	* @Return void:
	*/
	//static void SaveItems(DataPacketReader& inPacket, SQLConnection& sql);

    /*
	* Comments: 保存仓库物品的信息
	* Param DataPacketReader & inPacket: 读写器
	* @Return void:
	*/
	//static void SaveDepotItems(DataPacketReader& inPacket, SQLConnection& sql);

//	bool QueryCrossScriptData(ActorId nActorid);               //取跨服战脚本数据
//	static void SaveCrossScriptData(DataPacketReader& inPacket, SQLConnection& sql);                //保存跨服战脚本数据
	/*
	* Comments:  执行简单的存储过程，没有数据返回的
	* Param char * sSql:  存储过程语句
	* @Return int: 返回错误码
	*/
	//int ExecuteSimplyProcedure(const char* sSql,...);

	//处理帮派的数据消息
	//获取本服内所有的帮派列表
	//void LoadGuildList(DataPacketReader& inPacket);
	//读入这个帮派的详细数据，比如公告，成员列表等
	//void LoadGuildDetail(DataPacketReader& inPacket);
	//创建一个帮派
	void AddGuild(DataPacketReader& inPacket);
	//处理删除一个帮派
	void DeleteGuild(DataPacketReader& inPacket);
	//保存帮派信息
	void SaveGuild(DataPacketReader& inPacket);
	//保存帮派静态变量
	void SaveGuildVar(DataPacketReader& inPacket);
	//保存公会聊天信息
	void SaveGuildChat(DataPacketReader& inPacket);
	//保存公会商店记录
	void SaveGuildStore(DataPacketReader& inPacket);
	//增加一个帮派成员
	void AddGuildMember(DataPacketReader& inPacket);

	//保存个人的帮派信息
	static bool SaveActorGuild(DataPacketReader& inPacket, SQLConnection& sql);

	void DeleteMember(DataPacketReader& inPacket);

	/*// 读取帮派仓库物品信息
	//void LoadGuildDepot(DataPacketReader& inPacket);
	// 保存帮派仓库物品信息
	//void SaveGuildDepot(DataPacketReader& inPacket);
	//
	void LoadBeastLog(DataPacketReader& inPacket);
	//
	void AddBeastLog(DataPacketReader& inPacket);
	//
	void DeleteBeastLog(DataPacketReader& inPacket);
	//
	void LoadGuildLog(DataPacketReader& inPacket);
	*/
	//
	void AddGuildLog(DataPacketReader& inPacket);
	//
	void DeleteGuildLog(DataPacketReader& inPacket);
	/*
	// 读取一个帮派数据
	void LoadOneGuild(DataPacketReader& inPacket);
	// 读取一个帮派的静态数据
	void LoadGuildVar(DataPacketReader& inPacket);
	*/

	//副本相关
	void SaveFuben(DataPacketReader& inPacket);
	int SaveFubenData(ActorId nActorid, int Fbid, int Daycount, int Progress);
	void LoadFubenData(ActorId nActorId);
	void LoadFubenData(DataPacketReader& inPacket);
	int CleanFuben(ActorId nActorid);

	//寄卖系统相关
	//void LoadConsignmentItem(uint16_t totalCmd, uint16_t nCmd, DataPacketReader& inPacket);
	//void SaveConsignmentItem(DataPacketReader& inPacket);
	//void LoadConsiTimeoutItem(DataPacketReader& inPacket);
	//void LoadAllConsignmentItem(DataPacketReader& inPacket);
	//消息系统相关
	void LoadMsgListFromId(ActorId nActorId, int64_t nMsgId);
	void LoadMsgList(DataPacketReader& inPacket);
	void DeleteMsg(DataPacketReader& inPacket);
	void AddMsg(DataPacketReader& inPacket);

	void SaveChat(DataPacketReader& inPacket);

	//邮件系统相关
	//void LoadMailListFromId(ActorId nActorId, int64_t nMsgId, int32_t nLevel = 0);
	//void LoadMailList(DataPacketReader& inPacket);
	//void DeleteMail(DataPacketReader& inPacket);
	//void UpdateMailStatus(DataPacketReader& inPacket);
	//void DeleteMailFile(DataPacketReader& inPacket);
	//void GetActorIdFormActorName(DataPacketReader& inPacket);
	//void AddMail(DataPacketReader& inPacket);
	//void AddMailByName(DataPacketReader& inPacket);
	//void AddMailByAccountName(DataPacketReader& inPacket);
	//void LoadServerMail(ActorId actorid, int32_t nLevel = 0);
	//联系gm
	//void AddGmQuestion(DataPacketReader& inPacket);
	//void LoadGmQuestions(DataPacketReader& inPacket);
	//void LoadGmQuestion(DataPacketReader& inPacket);
	//void UpdateGmQuestion(DataPacketReader& inPacket);

	////宠物
	//bool QueryMountData(ActorId aid);
	//static void SaveMountToDB(DataPacketReader& inPacket, SQLConnection& sql);  //保存坐骑的数据

	//排行榜相关
	//void SaveTopTitleRank(DataPacketReader &inPacket); //保存排行榜
	//void LoadRank();	//读取排行榜入内存

	//void LoadFightRank();
	//void LoadFightRank2(int index = 0);
	//void SaveFightRank(DataPacketReader& reader);
	//void AddFightLog(DataPacketReader& reader);
	//void DelFightLog(DataPacketReader& reader);

	//void LoadGlobal(int cmd, DataPacketReader& reader);
	//void SaveGlobal(int cmd, DataPacketReader& reader);

	void LoadFriends(DataPacketReader& inPacket);	// 读取好友列表
	void UpdateFriend(DataPacketReader& inPacket);  //保存好友信息
	void DelFriend(DataPacketReader& inPacket);
	//void UpdateFriendInfo(DataPacketReader& inPacket);  //更新好友信息（下线时间）
	//void UpdateFriendContact(DataPacketReader& inPacket);	//下线时 更新最近联系时间

	
	void LoadPrivateChats(DataPacketReader& inPacket); //读取私聊数据
	void AddPrivateChats(DataPacketReader& inPacket);  //新增聊天记录
	void DelPrivateChats(DataPacketReader& inPacket);  //删除聊天记录
	void BachDelPrivateChats(DataPacketReader& inPacket);  //批量删除聊天记录

	void LoadPVMlayerData(DataPacketReader& inPacket);//加载竞技场玩家数据
	void SavePVMlayerData(DataPacketReader& inPacket); //保存竞技场玩家数据
	void UpdateChannengeRecord(DataPacketReader& inPacket);//更新竞技场挑战记录
	void LoadPlayerRecord(DataPacketReader& inPacket);//加载玩家挑战记录

	void LoadPlayerAFKData(DataPacketReader& inPacket); //加载玩家挂机练功数据
	void SavePlayerAFKData(DataPacketReader& inPacket); //保存玩家挂机练功数据

	//铭刻相关
	//void AddEqSign(DataPacketReader& inPacket);
	//void GetEqSignList(DataPacketReader& inPacket);
	//void InheritEqSign(DataPacketReader& inPacket);

	void AddSysVar(DataPacketReader& reader);		// 通用系统lua变量
	void LoadSysVar(DataPacketReader& reader);
	void UpdateSysVar(DataPacketReader& reader);



	//执行初始化数据库的存储过程
	//void ExecuInitDb();

	void OnResponseDbSessionData(DataPacketReader& inPacket);

	//bool QueryActorBuffData(ActorId nActorID);
	//static void SaveBuffDataToDB(DataPacketReader& inPacket, SQLConnection& sql);
	//bool QueryActorCaleData(ActorId nActorID);
	//static void SaveCaleDataToDB(DataPacketReader& inPacket, SQLConnection& sql);
	//bool QueryActorAchData(ActorId nActorID);
	//static void SaveAchDataToDB(DataPacketReader& inPacket, SQLConnection& sql);
	virtual void OnRun();

	/*void ReloadScript()
	{
		reload_script_ = true;
	}*/

	//wing 相关
	//bool QueryActorWingData(ActorId nActorID);
	//static void SaveWingDataToDB(DataPacketReader& inPacket, SQLConnection& sql);

	// 战队相关
	//加载战队列表
	//void LoadWarTeamList(DataPacketReader& inPacket);
	//创建一个战队
	//void AddWarTeam(DataPacketReader& inPacket);
	//处理删除一个战队
	//void DeleteWarTeam(DataPacketReader& inPacket);
	// 保存战队信息
	//void UpdateWarTeam(DataPacketReader& inPacket);
	//加载战队成员列表
	//void LoadWarTeamMember(DataPacketReader& inPacket);
	//创建一个战队成员
	//void AddWarTeamMember(DataPacketReader& inPacket);
	//处理删除一个战队成员
	//void DelWarTeamMember(DataPacketReader& inPacket);
	// 保存战队成员信息
	//void UpdateWarTeamMember(DataPacketReader& inPacket);
	// 加载一个战队的信息
	//void LoadOneWarTeam(DataPacketReader& inPacket);

	void ResetCrossPos(DataPacketReader& reader);
	void updateOnLogout(ActorId actorId, const char* name, long long int tPower, long long int rank_power);
	void updateOnLogin(ActorId actorId);

	void SaveActorMisc(DataPacketReader& reader);
	void LoadActorMisc(DataPacketReader& reader);

    void SaveDepotItemCache(DataPacketReader& inPacket);

	void SaveActorRankVar(DataPacketReader& reader);
	//执行从gameworld发送的sql
	void ExecFromGameWorld(DataPacketReader& reader);
	//初始化数据库
	void InitDB(DataPacketReader& reader);

	//global
	//增加一条bug
	//void AddBug(DataPacketReader& reader);
	//加载神榜内容
	//void LoadGoldRank(DataPacketReader& reader);

	//加载结婚记录
	//void LoadMarryRecord(DataPacketReader& inPacket);

	void OnSetValid(DataPacketReader& inPacket); // 设置数据有效性
	void OnEnableCheckValid(DataPacketReader& inPacket);	// 是否启用检查数据有效性

	void OnTxApiProcess();	//腾讯Api操作后处理

	bool HasWaitFor(ActorId actorid); //判断是否存在等待登陆的玩家
	void AddWaitFor(ActorId actorid); //增加等待登陆的玩家
	void RemoveWaitFor(ActorId actorid);//移除等待登陆的玩家

	void SetTargetId(int targetId){ target_sid_ = targetId; }
	int GetTargetId(){ return target_sid_; };

private:
	char						srv_name_[128];
	DBSessionMgr*				client_mgr_;			//所属数据服务器
	SQLConnection*				sql_;		//数据库连接对象
	time_t						close_t_;			//连接断开的时间
	char*						huge_buf_;		//大型SQL查询语句缓冲，长度为dwHugeSQLBufferSize
	static char*				huge_buf_s;		// sql查询语句缓冲，长度为dwHugeSQLBufferSize，用于静态方法中

	BaseAllocator				allocator_;

	// rank
	Vector<ActorRankDataEx, 2048> rank_actor_list_;
	StaticHashTable<ActorRankDataEx*, 2048* 4> rank_actor_hash_;
	AllLastRankList	last_rank_list_;

	time_t					check_gm_t_;
	Vector<GMData>			gm_list_;

	int						sentToBIDay_;
	//CVSPDefinition			vsp_def_;
	//BaseScript				script_;

	//bool					reload_script_;

	time_t					gc_t_;
	time_t					report_t_;
	int						watch_id_;

	int						battleflag_;

	Vector<DataPacket*>		netMsgList_;	// gameworld发过来的网络包
	BaseAllocator			netAlloc_;

	int						alloc_series_;

	//api返回相关
	time_t                  check_fee_t_;
	bool                    canOutputMsg_;
	Vector<FeeData>			fee_list_;
	Vector<TxApiMsgData>	tx_list_;

	int						target_sid_;
	StaticHashTable<ActorId, 4096>	wait_for_list_;	//等待查询列表

	DBExecutor* executor_;
};

#endif

