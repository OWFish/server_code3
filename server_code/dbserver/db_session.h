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
	//�������ӶϿ��ĺ���
	void OnDisconnected();

	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);

	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	void processNetMsg(const uint16_t cmd, DataPacketReader& data);

	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regData);
public:
	//����SQL��ѯ��仺�峤��
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
	//��ҵ�����
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
	//�����
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


	//������ص�
	//void QuerySkillFromDB(ActorId nActorID);  //װ����ҵļ�������
	//static void SaveSkillToDB(DataPacketReader& inPacket, SQLConnection& sql);  //���漼������

	bool QueryActorScriptData(ActorId nActorid);               //ȡ�ű�����
	static bool SaveScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql);                //����ű�����

	bool QueryActorCsScriptData(ActorId nActorID);
	static bool SaveCsScriptDataToDB(DataPacketReader& inPacket, SQLConnection& sql);

	// ����ϵͳ
	//bool QueryActorGemItemData(ActorId nActorId);					// ��ȡ��ɫ��������
	//static void SaveActorGemItemData(DataPacketReader& inPacket, SQLConnection& sql);		// �����ɫ��������

	// ÿ����ո�����������
	//bool QueryActorFbCountData(ActorId actorId);
	//static void SaveActorFbCountData(DataPacketReader& inPacket, SQLConnection& sql);

	// ���＼��
	//static void SavePetSkill(DataPacketReader& inPacket, SQLConnection& sql);
	//void QueryPetBaseFromDB(ActorId nActorID);
	//static void SavePetBase(DataPacketReader& inPacket, SQLConnection& sql);

	//void QueryMarryInfo(ActorId nActorID);
	//static void SaveMarryInfo(DataPacketReader& inPacket, SQLConnection& sql);
	//void offlineDivorce(DataPacketReader& inPacket, SQLConnection& sql);
	//void offlineSetLogouTime(DataPacketReader& inPacket, SQLConnection& sql);

	// ������ϵͳ
	void QueryActorFightData(ActorId aid);

	void QueryPetSkillFromDB(ActorId nActorID);

	//�ؼ����
	//void QueryMijiItem(ActorId nActorID);

	//static void SaveMijiItem(DataPacketReader& inPacket, SQLConnection& sql);
	// ����������
	/*
	* Comments:
	* Param int actorId:
	* Param const char * fieldName:���ݿ���е��ֶ���
	* Param int entityId:���ݷ��������߼�������ͨ�ŵ�������EntityMgrId
	* @Returns void:
	*/
	//void QueryActorVariableData(ActorId actorId, const char* fieldName, int entityId);

	void QueryActorVariableList(ActorId actorId, Vector<VariableDataFlag>& fieldList);

	// ��cache�в�ѯ��Ҷ���������
	bool QueryActorVariableDataFromCache(ActorId actorId, int type, int cmd);
	/*
	* Comments:
	* Param DataPacketReader & packet:
	* Param const char * fieldName:�ֶ���
	* Param bool bResp:
	* Param int entityId:Ҫ����Ӧʱ���߼�������ͨ�ŵ�������
	* @Returns void:
	*/
	static bool SaveActorVariableData(DataPacketReader& packet, const char* fieldName, SQLConnection& sql, int entityId = 0);

	// ��ѯȫ�ֵĶ���������
	//void QueryGlobalVariableData(const char* fieldName, int entityId);

	// ����ȫ�ֵĶ�������
	//void SaveGlobalVariableData(DataPacketReader& packet, const char* fieldName, int entityId, bool bResp = true);

	void QueryActorSubSystemData(ActorId aid);    //װ�ظ���ϵͳ������
	void QueryActoSubSystemData1(ActorId aid);    //װ�ظ���ϵͳ������
	//��Ʒ��صĵ�
	/*
	* Comments:װ����ҵ���Ʒ
	* Param unsigned int nActorID: ��ҵĽ�ɫID
	* Param unsigned int nItemStoreType: ��Ʒ�Ĵ洢����
		enum tagItemStorageType
		{
		itItemBag=1, //���������Ʒ
		itItemEquip =2, //װ����Ʒ
		itItemDepot =3, //�ֿ���Ʒ
		};
	* @Return void:
	*/
	//void QueryItems(ActorId nActorID, unsigned int nItemStoreType);

	//�ֿ���Ʒ��ص�
	/*
	* Comments:װ����ҵ���Ʒ
	* Param unsigned int nActorID: ��ҵĽ�ɫID
	* Param unsigned int nDepotType: �ֿ������
	enum itemPos
   {
	  ipStart = 0,
	  ipBag = ipStart,
	  ipDepot,      //��Ҳֿ�
	  ipLottery,    //�齱�ֿ�
	  ipEntrust,	//ί�вֿ�
	  ipTreasure,	//�䱦��
	  ipBabel,	    //ͨ�����ֿ�

	  ipMax,
    };
	* @Return void:
	*/
	//void QueryDepotItems(ActorId nActorID);
	//void QueryDepotItem(ActorId nActorID, unsigned int nDepotType);


	/*
	* Comments: ������Ʒ����Ϣ
	* Param DataPacketReader & inPacket: ��д��
	* @Return void:
	*/
	//static void SaveItems(DataPacketReader& inPacket, SQLConnection& sql);

    /*
	* Comments: ����ֿ���Ʒ����Ϣ
	* Param DataPacketReader & inPacket: ��д��
	* @Return void:
	*/
	//static void SaveDepotItems(DataPacketReader& inPacket, SQLConnection& sql);

//	bool QueryCrossScriptData(ActorId nActorid);               //ȡ���ս�ű�����
//	static void SaveCrossScriptData(DataPacketReader& inPacket, SQLConnection& sql);                //������ս�ű�����
	/*
	* Comments:  ִ�м򵥵Ĵ洢���̣�û�����ݷ��ص�
	* Param char * sSql:  �洢�������
	* @Return int: ���ش�����
	*/
	//int ExecuteSimplyProcedure(const char* sSql,...);

	//������ɵ�������Ϣ
	//��ȡ���������еİ����б�
	//void LoadGuildList(DataPacketReader& inPacket);
	//����������ɵ���ϸ���ݣ����繫�棬��Ա�б��
	//void LoadGuildDetail(DataPacketReader& inPacket);
	//����һ������
	void AddGuild(DataPacketReader& inPacket);
	//����ɾ��һ������
	void DeleteGuild(DataPacketReader& inPacket);
	//���������Ϣ
	void SaveGuild(DataPacketReader& inPacket);
	//������ɾ�̬����
	void SaveGuildVar(DataPacketReader& inPacket);
	//���湫��������Ϣ
	void SaveGuildChat(DataPacketReader& inPacket);
	//���湫���̵��¼
	void SaveGuildStore(DataPacketReader& inPacket);
	//����һ�����ɳ�Ա
	void AddGuildMember(DataPacketReader& inPacket);

	//������˵İ�����Ϣ
	static bool SaveActorGuild(DataPacketReader& inPacket, SQLConnection& sql);

	void DeleteMember(DataPacketReader& inPacket);

	/*// ��ȡ���ɲֿ���Ʒ��Ϣ
	//void LoadGuildDepot(DataPacketReader& inPacket);
	// ������ɲֿ���Ʒ��Ϣ
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
	// ��ȡһ����������
	void LoadOneGuild(DataPacketReader& inPacket);
	// ��ȡһ�����ɵľ�̬����
	void LoadGuildVar(DataPacketReader& inPacket);
	*/

	//�������
	void SaveFuben(DataPacketReader& inPacket);
	int SaveFubenData(ActorId nActorid, int Fbid, int Daycount, int Progress);
	void LoadFubenData(ActorId nActorId);
	void LoadFubenData(DataPacketReader& inPacket);
	int CleanFuben(ActorId nActorid);

	//����ϵͳ���
	//void LoadConsignmentItem(uint16_t totalCmd, uint16_t nCmd, DataPacketReader& inPacket);
	//void SaveConsignmentItem(DataPacketReader& inPacket);
	//void LoadConsiTimeoutItem(DataPacketReader& inPacket);
	//void LoadAllConsignmentItem(DataPacketReader& inPacket);
	//��Ϣϵͳ���
	void LoadMsgListFromId(ActorId nActorId, int64_t nMsgId);
	void LoadMsgList(DataPacketReader& inPacket);
	void DeleteMsg(DataPacketReader& inPacket);
	void AddMsg(DataPacketReader& inPacket);

	void SaveChat(DataPacketReader& inPacket);

	//�ʼ�ϵͳ���
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
	//��ϵgm
	//void AddGmQuestion(DataPacketReader& inPacket);
	//void LoadGmQuestions(DataPacketReader& inPacket);
	//void LoadGmQuestion(DataPacketReader& inPacket);
	//void UpdateGmQuestion(DataPacketReader& inPacket);

	////����
	//bool QueryMountData(ActorId aid);
	//static void SaveMountToDB(DataPacketReader& inPacket, SQLConnection& sql);  //�������������

	//���а����
	//void SaveTopTitleRank(DataPacketReader &inPacket); //�������а�
	//void LoadRank();	//��ȡ���а����ڴ�

	//void LoadFightRank();
	//void LoadFightRank2(int index = 0);
	//void SaveFightRank(DataPacketReader& reader);
	//void AddFightLog(DataPacketReader& reader);
	//void DelFightLog(DataPacketReader& reader);

	//void LoadGlobal(int cmd, DataPacketReader& reader);
	//void SaveGlobal(int cmd, DataPacketReader& reader);

	void LoadFriends(DataPacketReader& inPacket);	// ��ȡ�����б�
	void UpdateFriend(DataPacketReader& inPacket);  //���������Ϣ
	void DelFriend(DataPacketReader& inPacket);
	//void UpdateFriendInfo(DataPacketReader& inPacket);  //���º�����Ϣ������ʱ�䣩
	//void UpdateFriendContact(DataPacketReader& inPacket);	//����ʱ ���������ϵʱ��

	
	void LoadPrivateChats(DataPacketReader& inPacket); //��ȡ˽������
	void AddPrivateChats(DataPacketReader& inPacket);  //���������¼
	void DelPrivateChats(DataPacketReader& inPacket);  //ɾ�������¼
	void BachDelPrivateChats(DataPacketReader& inPacket);  //����ɾ�������¼

	void LoadPVMlayerData(DataPacketReader& inPacket);//���ؾ������������
	void SavePVMlayerData(DataPacketReader& inPacket); //���澺�����������
	void UpdateChannengeRecord(DataPacketReader& inPacket);//���¾�������ս��¼
	void LoadPlayerRecord(DataPacketReader& inPacket);//���������ս��¼

	void LoadPlayerAFKData(DataPacketReader& inPacket); //������ҹһ���������
	void SavePlayerAFKData(DataPacketReader& inPacket); //������ҹһ���������

	//�������
	//void AddEqSign(DataPacketReader& inPacket);
	//void GetEqSignList(DataPacketReader& inPacket);
	//void InheritEqSign(DataPacketReader& inPacket);

	void AddSysVar(DataPacketReader& reader);		// ͨ��ϵͳlua����
	void LoadSysVar(DataPacketReader& reader);
	void UpdateSysVar(DataPacketReader& reader);



	//ִ�г�ʼ�����ݿ�Ĵ洢����
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

	//wing ���
	//bool QueryActorWingData(ActorId nActorID);
	//static void SaveWingDataToDB(DataPacketReader& inPacket, SQLConnection& sql);

	// ս�����
	//����ս���б�
	//void LoadWarTeamList(DataPacketReader& inPacket);
	//����һ��ս��
	//void AddWarTeam(DataPacketReader& inPacket);
	//����ɾ��һ��ս��
	//void DeleteWarTeam(DataPacketReader& inPacket);
	// ����ս����Ϣ
	//void UpdateWarTeam(DataPacketReader& inPacket);
	//����ս�ӳ�Ա�б�
	//void LoadWarTeamMember(DataPacketReader& inPacket);
	//����һ��ս�ӳ�Ա
	//void AddWarTeamMember(DataPacketReader& inPacket);
	//����ɾ��һ��ս�ӳ�Ա
	//void DelWarTeamMember(DataPacketReader& inPacket);
	// ����ս�ӳ�Ա��Ϣ
	//void UpdateWarTeamMember(DataPacketReader& inPacket);
	// ����һ��ս�ӵ���Ϣ
	//void LoadOneWarTeam(DataPacketReader& inPacket);

	void ResetCrossPos(DataPacketReader& reader);
	void updateOnLogout(ActorId actorId, const char* name, long long int tPower, long long int rank_power);
	void updateOnLogin(ActorId actorId);

	void SaveActorMisc(DataPacketReader& reader);
	void LoadActorMisc(DataPacketReader& reader);

    void SaveDepotItemCache(DataPacketReader& inPacket);

	void SaveActorRankVar(DataPacketReader& reader);
	//ִ�д�gameworld���͵�sql
	void ExecFromGameWorld(DataPacketReader& reader);
	//��ʼ�����ݿ�
	void InitDB(DataPacketReader& reader);

	//global
	//����һ��bug
	//void AddBug(DataPacketReader& reader);
	//�����������
	//void LoadGoldRank(DataPacketReader& reader);

	//���ؽ���¼
	//void LoadMarryRecord(DataPacketReader& inPacket);

	void OnSetValid(DataPacketReader& inPacket); // ����������Ч��
	void OnEnableCheckValid(DataPacketReader& inPacket);	// �Ƿ����ü��������Ч��

	void OnTxApiProcess();	//��ѶApi��������

	bool HasWaitFor(ActorId actorid); //�ж��Ƿ���ڵȴ���½�����
	void AddWaitFor(ActorId actorid); //���ӵȴ���½�����
	void RemoveWaitFor(ActorId actorid);//�Ƴ��ȴ���½�����

	void SetTargetId(int targetId){ target_sid_ = targetId; }
	int GetTargetId(){ return target_sid_; };

private:
	char						srv_name_[128];
	DBSessionMgr*				client_mgr_;			//�������ݷ�����
	SQLConnection*				sql_;		//���ݿ����Ӷ���
	time_t						close_t_;			//���ӶϿ���ʱ��
	char*						huge_buf_;		//����SQL��ѯ��仺�壬����ΪdwHugeSQLBufferSize
	static char*				huge_buf_s;		// sql��ѯ��仺�壬����ΪdwHugeSQLBufferSize�����ھ�̬������

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

	Vector<DataPacket*>		netMsgList_;	// gameworld�������������
	BaseAllocator			netAlloc_;

	int						alloc_series_;

	//api�������
	time_t                  check_fee_t_;
	bool                    canOutputMsg_;
	Vector<FeeData>			fee_list_;
	Vector<TxApiMsgData>	tx_list_;

	int						target_sid_;
	StaticHashTable<ActorId, 4096>	wait_for_list_;	//�ȴ���ѯ�б�

	DBExecutor* executor_;
};

#endif

