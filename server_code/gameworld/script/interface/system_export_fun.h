#ifndef _SYSTEM_EXPORT_FUN_H_
#define _SYSTEM_EXPORT_FUN_H_

//tolua_begin
/*
	����ļ�����ϵͳ��һЩ���ã������ȡ���������ƣ�����ϵͳ��ʱ���
	��ʹ�ú���ǰ����System.xx�������ɻ�ȡ
	�����ȡ��ǰ��ʱ�����: nyear, nMonth,nDay= System.getDate()
*/

int print(lua_State* L);

namespace System
{
	// ����gameworld�İ汾��
	int version();

	// ˢ��ȫ��npc�Ľű���et����ҵ�ָ�룬��ˢ��npc�Ľű����֪ͨ�������ң�type��0��ʾȫ��npc��1��ʾ�����õ�ȫ��npc
	bool reloadGlobalNpc(void* et, int type);

	char* getServerName();
	int getServerId();
	// ��ȡweh��������ip��ַ�Ͷ˿ڣ�����lua�������web������
	int getWebServer(lua_State* L);
	bool isServerStarted();

	/*
	* Comments: ��ȡ��ǰ��������
	* Param int & nYear: ��
	* Param int & nMonth:��
	* Param int & nDay:��
	* @Return void:
	*/
	int getDate(lua_State* L);

	/*
	* Comments: ��ȡ��ǰ��Сʱ �����ӣ�����
	* Param int & nHour:Сʱ
	* Param int & nMinute:����
	* Param int & nSecond:��
	* @Return void:
	*/
	int getTime(lua_State* L);

	//����unixʱ�䣨�Ժ����㣩
	const char* getUnixTime();
	/*
	* Comments:��ȡ��ǰ��ʱ��δ𣨿���������
	* @Return Uint64:���ص�ǰ��ʱ��δ�
	*/
	unsigned long long getTick();
	/*
	* Comments:ͨ�����������ֻ�ȡ������id
	* Param char * sName:����������
	* @Return int:������ID,�������Ϊ�գ���ô����һ��-1
	*/
	//int getSceneIdByName(const char* sName);

	/*
	* Comments:��ȡ��ǰ��һ�ܵĵڼ���
	* @Return int:����һ�����ڵĵڼ���
	*/
	int getDayOfWeek();


	/*
	* Comments:��ȡһ��ȡģnModule�������
	* Param int nModule: ģ��
	* @Return int: ����ȡģ��������
	*/
	unsigned int getRandomNumber(int nModule);

	/*
	* Comments:��ȡ��ǰ��miniʱ�䣬��λ��
	* @Return UINT:
	*/
	unsigned int getNowTime();
	/*
	* Comments: ת��ϵͳʱ�䵽miniʱ��
	* Parameter: int systime:
	* Returns: unsigned int:
	*/
	unsigned int encodeTime(int systime);

	/*
	* Comments:��������ʱ�䵽�������ʱ���ʱ���
	* Param  unsigned int nHour: ��ͷ
	* Parma   unsigned int nMinute:����
	* @Return UINT:
	*/
	unsigned int getDiffendTime(int nHour, int nMinute);

	/*
	* Comments: ����ָ��ʱ�������ڼ�
	* Param
	*/
	unsigned int getWeekDataTime(int y, int m, int d);

	/*
	* Comments: �ж�����ʱ���Ƿ���ͬһ��,��һ������Ϊһ��
	* Param unsigned int t1: CMiniDateTime��ʽ
	* Param unsigned t2: CMiniDateTime��ʽ
	* @Return bool: ���t1��t2��ͬһ�ܣ�����true�����򷵻�false
	* @Remark:
	*/
	bool isSameWeek(unsigned int t1, unsigned int t2);

	/*
	* Comments: �����������ֺ�λ�ô���ʵ��
	* Param CEntity * pEntity:ʵ���ָ��
	* Param char * sSceneName:  ����������
	* Param int nPosX:����x
	* Param int nPosY:����y
	* @Return bool: �ɹ�����true�����򷵻�false
	*/
	//bool telportSceneByName(void* pEntity, char* sSceneName, int nPosX, int nPosY);

	/*
	* Comments:���͵�������һ����ȥ
	* Param void * pEntity:��ҵ�ָ��
	* Param int nSceneId:������id
	* Param int nPosX:λ��x
	* Param int nPosY:λ��y
	* @Return bool:�ɹ�����true�����򷵻�false
	*/
	//bool telportScene(void* pEntity, int nSceneId, int nPosX, int nPosY);

	// �ڱ������ڴ��ͣ�x��y���������꣬px��py���������꣬���Բ���
	//bool teleportInScene(void* et, int x, int y, int px = -1, int py = -1, bool teleport = false);

	// ���͵���������
	//bool telportFuBenScene(void* et, unsigned int fbHandle, int sceneId, int posX, int posY);

	/*
	* Comments: ���͵�������Ĭ�ϵ�
	* Param CEntity * pEntity: ʵ���ָ��
	* Param char * sSceneName:����������
	* Param int nPointID:Ĭ�ϵ��ID,���û�ж��Ĭ�ϵ�ֱ��ʹ��0
	* @Return bool: �ɹ�����true�����򷵻�false
	*/
	//bool telportSceneDefaultPoint(void* pEntity, char* sSceneName, int nPointID = 0);

	/*
	* Comments: ��ӡ������Ϣ
	* Param char * str: ������Ϣ
	* @Return void:
	*/
	void trace(char* str);

	/* ��㴴��Ŀ¼
	 * �������Ŀ¼C:\a\b\c\d������Ŀ¼�ĸ�Ŀ¼���������𼶴�����Ŀ¼����������Ŀ¼
	 * @���Ŀ¼��ȫ�����ɹ���������true�����򷵻�false��
	 * %����ڴ���ĳ����Ŀ¼�ɹ��󲢴�����Ŀ¼ʧ�ܣ���������false���Ѿ������ĸ�Ŀ¼���ᱻɾ����
	 * %Ŀ¼·���������ַ����ȣ�����Ҫ�������MAX_PATH���ַ���������
	 */
	bool deepCreateDirectory(const char* sDirName);


	/* �ж��ļ���Ŀ¼�Ƿ����
	* �ڲ���ϵͳ�У�Ŀ¼Ҳ��һ���ļ������Ҫ�ж�һ��Ŀ¼�Ƿ������Ӧ��ʹ��DirectoryExists��
	* Ҫ�ж�һ���ļ��Ƿ��������һ���鵵�ļ���Ӧ��ʹ��IsArchive��
	* @����ļ���Ŀ¼�����򷵻�true���򷵻�false
	* %�ļ�·���ַ����Ȳ��ó���MAX_PATH
	*/
	bool fileExists(const char* sFilePath);

	/*
	* Comments:������ҵ����ֻ�ȡ��ҵ�ָ��
	* Param char * sName:��ɫ����
	* @Return void*:
	*/
	void* getActorPtr(const char* sName);


	/*
	* Comments: ȫ������ϵͳ��ʾ
	* Param char * sTipmsg: tipmsg��ָ��
	* Param int nTipmsgType: �������ʾ���ͣ������������ǵ������
	* @Return void:
	*/
	void broadcastTipmsg(const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);

	// ��broadcastTipmsgһ����ֻ�Ƕ��level����
	void broadcastLevelTipmsg(const char* sTipmsg, int level, int nTipmsgType = ttTipmsgWindow);
	
	/*
	* Comments: ͨ��ID�㲥tipmsg
	* Param int nTipmsgID: ��ʾ��ID
	* Param int nTipmsgType: ��ʾ������
	* @Return void:
	*/
	void broadcastTipmsgWithID(int nTipmsgID, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:�㲥����������
	* Param void * dp: ����DataPacket*
	* @Returns void:
	*/
	void broadcastData(void* dp, bool isOffset = false);

	/*
	* Comments: ���ʵ���ָ�뷵������
	* Param void * pEntity: ʵ���ָ��
	* @Return int: ���ָ������ȷ�ķ���ʵ������(���,npc��)�����򷵻�-1
	*/
	int getEntityByPtr(void* pEntity);

	/*
	* Comments:��ȡ���е�������ҵ�ָ��
	* Param lua_State * L:
	* @Return int:����һ�����������е�ʵ��ָ��
	*/
	int getAllActorList(lua_State *L);

	/*
	* Comments:ͨ��ʵ���handle��������
	* Param unsigned long long entityHandle: ʵ���handle
	* @Return int: ���ָ������ȷ�ķ���ʵ������(���,npc��)�����򷵻�-1
	*/
	int getEntityTypeByHandle(double entityHandle);

	/*
	* Comments: ͨ����ҵ�actorID��ȡ��ҵ�ָ��
	* Param unsigned int nActorID:actorID
	* @Return void *:��ҵ�ָ��
	*/
	void* getEntityPtrByActorID(unsigned int nActorID);

	/*
	* Comments:�жϵ�ǰʱ���Ƿ������ʱ�����
	* Param int nStartHour:ʱ��ο�ʼ��Сʱ
	* Param int nStartMin:��
	* Param int nStartSec:��
	* Param int nEndHour:ʱ��ν�����Сʱ
	* Param int nEndMin:��
	* Param int nEndSec:��
	* @Return bool:��������ʱ����ڣ�����true������false
	*/
	bool isInTimeRange(int nStartHour, int nStartMin, int nStartSec, int nEndHour, int nEndMin, int nEndSec);

	/*
	* Comments:��ȡ�����賿����ʱ������
	* @Return unsigned int:
	*/
	unsigned int getToday();
	/*
	* Comments:��ȡ�����賿����ʱ������
	* @Return unsigned int:
	*/
	unsigned int getYesterday();
	/*
	* Comments:��ȡȫ��npc��ָ��
	* @Return void*:
	*/
	void* getGlobalNpc();

	// ��ȡtest�õ�ȫ��npc��ָ��
	void* getReserveNpc();

	/*
	* Comments: ��ȡ���ɵ�����
	* Param int nGuidID:���ɵ�����
	* @Return char*:���ɵ�����
	*/
	//const char* getGuildName(int nGuidID);

	/*
	* Comments:���ݰ���id��ȡ����ָ�룬��������ߣ�����NULL
	* Param int nGuildID:
	* @Return void*:
	*/
	//void* getGuildLeader(int nGuildID);

	/*
	* Comments:���ݰ���id���ذ����Ľ�ɫid
	* Param int nGuildID:
	* @Return int:
	*/
	//int getGuildLeaderId(int nGuildID);

	/*
	* Comments:��ȡ�����賿��ʱ��
	* @Return unsigned int:
	*/
	//unsigned int getTomorrow();

	//bool monUpdate();
	/*
	* Comments:ע������������Ƿ�Ҫ�����ű�
	* Param int mid:�����id
	* Param flag: �Ƿ����������ű�,�Ǳ�ʾҪ�����ű������򲻴����ű�
	* @Return void:
	*/
	//void regMonsterDie(int mid, bool flag = true);

	// ע��ɼ����Ƿ񴥷��ű�
	//void regGatherFinish(int mid, bool flag = true);

	// ע�ᱻ�����Ƿ񴥷��ű�
	//void regMonsterAttacked(int mid, bool flag = true);

	/*
	* Comments: ע�����ˢ�º��Ƿ���Ҫ���ýű�
	* Param int mid: �����id
	* Param bool flag:����Ǳ�ʾ
	* @Return void:
	*/
	//void regMonsterCreate(int mid, bool flag = true);

	// ������Ʒʱ�����ű�
	//void regMonsterDrop(int mid, bool flag = true);

	// hp�ı䴥���ű�
	//void regMonsterHpChange(int mid, bool flag = true);

	// ���������˺��ű�
	//void regMonsterDamage(int mid, bool flag = true);

	//��ȡȫ�ֶ�̬��������̬������������ʱ��Ч,��Ϸ����������ر�ʱ���ᱣ�浽db
	//int getDyanmicVar(lua_State* L);

	//��ȡȫ�־�̬��������̬�����ڻᱣ�浽���ݿ�
	int getStaticVar(lua_State* L);

	/*
	* Comments:��ȡϵͳ��һЩ����
	* Param char * pDefName:���õ��ַ����������ȡ��Ӫ�̵�id����������SPID
	* @Return char *:
	*/
	const char* getSystemDef(const char* name);

	/*
	* Comments:�������浽һ����Ӫ
	* Param int nCampId:��Ӫ��id
	* Param char * sTipmsg: ���������
	* Param int nTipmsgType: ��ʾ��λ��
	* @Return void:
	*/
	//void broadcastCampTipmsg(int nCampId, const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:�������浽һ������
	* Param int nGuild:����ID
	* Param char * sTipmsg:��������
	* Param int nTipmsgType:��ʾλ��
	* @Returns void:
	*/
	//void broadcastGuildTipmsg(int nGuild, const char* sTipmsg);

	/*
	* Comments:��ȡ�������Ŀ���ʱ��
	* @Return unsigned int:����ʱ�䣬minitime��ʽ��
	*/
	unsigned int getServerOpenTime();

	/*
	* Comments:ȫ������ȫ����Ч
	* Param int nEffId::��Чid
	* Param int nSec:����ʱ��
	* @Return void:
	*/
	//void playScrEffect(int nEffId, int nSec);

	/*
	* Comments:����ȫ����Ч������Ϣ18�������ǣ�����Ǵ���ʵ�ֵ���Ч
	* Param int nEffId:��Чid
	* Param int nSec:����ʱ��
	* @Return void:
	*/
	//void playScrEffectCode(int nEffId, int nSec);



	//const char* getMonsterNameById(int id);

	// �Ƿ�ͬһ��
	bool isSameDay(unsigned int t1, unsigned int t2);

	// ����ʵ����ʾ����
	void setEntityShowName(void* et, const char* name);

	// ��ȡ�����ǿ�����ĵڼ���
	int getOpenServerDay();

	// ��ȡָ��ʱ����������ǵڼ���
	int getTimeToNowDay(int optime);

	// ��ȡ���������0��ʱ��
	int getOpenServerStartDateTime();

	// ��ȡ����ʱ��
	unsigned int getOpenServerTime();

	// ���ÿ���ʱ��
	void setOpenServerTime(int year, int mon, int day, int hour, int m);

	// ������뿪����N��24���ʣ������
	int getRestTimeFromOpenServer(int day);

	// �ж����ֵ�ĳλ�Ƿ�Ϊ1��idx��0~31
	bool bitOPMask(int val, int idx);
	// ȡ��
	int bitOpNot(int val);

	// λ��
	int bitOpAnd(int val1, int val2);
	//λ��
	int bitOpOr(int val1, int val2);
	// λ����
	int bitOpRig(int val, int cnt);
	// λ����
	int bitOpLeft(int val, int cnt);

	// �����ֶ�Ӧ��λ���1
	int bitOpSetMask(int val, int idx, bool flag);

	//
	int makeInt16(int lo, int hi);
	int makeInt32(int lo, int hi);

	int makeHiInt16(int val);

	int makeLoInt16(int val);

	int makeHiInt8(int val);

	int makeLoInt8(int val);

	// ����4���ֽڵ����ֺϲ���һ��int32��b1��b4�ֱ��ǵ�λ-��λ,ע��ÿ�����ֲ��ܳ���256
	int int32Byte(int b1, int b2, int b3, int b4);
	// ��int32Byte�෴�Ĳ��������Եȵ�4�����֣��ֱ��ǵ�λ-��λ���ֽ�
	int byteInt32(lua_State* L);

	// ת��������
	unsigned int timeEncode(int year, int mon, int day, int hour, int m, int sec);
	//
	int timeDecode(lua_State* L);

	// save_db : ��־�Ƿ񱣴浽�������ݿ�
	void logCounter(int actorid, const char* aid,
		const char* user_level = "",
		const char* counter = "",
		const char* value = "",
		const char* extra = "",
		const char* kingdom = "",
		const char* phylum = "",
		const char* classfield = "",
		const char* family = "",
		const char* genus = "",
		int flag = lfDB);

	void logEnconomy(int actorid, const char* aid,
		const char* currency = "",
		const char* amount = "",
		const char* value = "",
		const char* kingdom = "",
		const char* phylum = "",
		const char* classfield = "",
		const char* family = "",
		const char* genus = "",
		const char* extra = "",
		const char* extra2 = "",
		const char* pf = "",
		int flag = lfNormal,
		bool isPay = true,
		const char* openkey = "",
		const char* pfkey = "",
		const char* pfid = "");

	void logMilestone(
		int actorid,
		const char* aid,
		const char* milestone = "",
		const char* value = "",
		const char* extra = "",
		int flag = lfNormal);

	void logPayment(int ret, int actorId, const char* aid, int amount,
		int mstType,
		int p1,
		int p2,
		int p3,
		int value = 1,
		const char* kingdom = "",
		const char* phylum = "",
		const char* transactionid = "",
		const char* extra = "",
		int p4 = 0,
		int p5 = 0,
		int flag = lfNormal);
	void logInstall(const char* actorId, const char* source = "",
		const char* affiliate = "",
		const char* creative = "",
		const char* family = "",
		const char* genus = "",
		const char* from_uid = "",
		const char* extra = "",
		int flag = lfNormal);

	void logDau(const char* aid,
		const char* source = "",
		const char* affiliate = "",
		const char* creative = "",
		const char* family = "",
		const char* genus = "",
		const char* ip = "",
		const char* from_uid = "",
		const char* extra = "",
		int flag = lfNormal);

	void logGameInfo(const char* aid,
		const char* user_level = "",
		const char* value = "",
		const char* extra = "",
		const char* kingdom = "",
		const char* phylum = "",
		const char* classfield = "",
		const char* family = "",
		const char* genus = "",
		int flag = lfNormal);

	void logChat(void* et,
		int type,
		const char* content,
		const char* toaid = "",
		const char* toname = "");

	void logTLog(const char* logstr);

	// ��¼��������
	void logOnline();

	// ��ȡ��������
	int getOnlineCount(bool includeCache = false);

	// ��ȡTLog�¼�ID
	//const char* getEventId();

	// ��ȡTLog�ĵ�ǰʱ��
	//const char* getTLogTime();

	// �滻TLog�ַ����ָ���
	//const char* tlogReplace(const char* instr, int idx = 0);

	// ���¶���actormgr�Ľű�
	void actorMgrReloadScript();
	// ���¶����ƵĹ����ֿ�
	void actorMgrLoadFilterNames();

	// ���ݿ�������

	void dbClose(void* db_conn);
	bool dbConnect(void* db_conn);
	void* getGameEngineGlobalDbConn();

	void* createActorsDbConn();
	void delActorsDbConn(void* db_conn);

	int dbQuery(void* db_conn, const char* sql);
	int dbExe(void* db_connection, const char* sql);

	void dbResetQuery(void* db_conn);

	void* dbCurrentRow(void* db_conn);

	const char* dbGetRow(void* row, int idx);

	int dbGetRowCount(void* db_conn);

	void* dbNextRow(void* db_conn);

	bool geAddRoutes(int serverid, const char* host, int port);

	bool geHasRoute(int serverid);

	int getStrLenUtf8(const char* str);

	// ��dbserverͨ�Ų��֣���Ҫ�������ݿ�洢
	// ���ܽӿڣ���
	/*
		ǰ�������������֣�����ϵͳid��Э��ţ�����siEntity, dcSaveGemItemData
		����������param3��ָ��������������
		����N�������� N = param3 * 2,�ֱ�Ϊ�������ͣ�����ֵ
		�������ͼ�tagDataType����
	*/
	int SendToDb(lua_State* L);

	// �������ݿ����ݰ�,���������ID������DBClient��DataPacketָ��
	int allocDBPacket(lua_State* L);
	// �ύ���ݿ����ݰ�
	int flushDBPacket(lua_State* L);

	// �ж�����ʱ��(minidate)��������
	int getDayDiff(unsigned int t1, unsigned int t2);

	// ���úϷ�״̬
	//void setHefuState(int state);

	// ��úϷ�״̬
	//int getHefuState();

	// �Ƿ���actorÿ5s�����ű���
	// �������������Ϊ�˽ű�����ʵ�ָ���Ĺ��ܣ�ͬʱ��֤һ��������
	void start5sScripte(bool flag);

	// ����������Ϣ
	void sendOffMsg(int aid, const char* actorname, const char* account, int srcid, void* dp);

	void saveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
		const char* account, const char* msg);

	// ������֤��0����ȷ��1�Ƿ����֤��2δ��18��
	int checkIdentity(const char* id);

	void setEngineGcActorCnt(int cnt);
	// ����ǿ��GC
	void engineGc();

	void stopLog(bool flag);
	void stopCounterLog(bool flag);
	void stopEconomyLog(bool flag);

	//void addMarryLog(int aid1, int aid2, const char* name1, const char* name2);
	//void sendMarryLog(void* et, int migid, int pid, int count, int page);

	//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, int camp = 0);
	//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, unsigned int hFuben, int camp = 0);

	int getSystemTime(lua_State* L);
	// ����������ݵı���ʱ��
	void setActorDbSaveTime(int sec);

	// �����
	void closeActor(void* et);

	// ���ü�������Ʒ����������
	// count��ʾ�ж�����Ʒ�Ǵ��ڼ��
	//void setLimitItemCount(int count, int itemId, int limitCnt, int idx, int level = 10);

	// ��ȡϵͳCLVariant����
	int getSysVar(lua_State* L);

	// ����ϵͳCLVariant����
	unsigned int createSysVar(int ownerId, const char* ownerName, int type);

	// ����ϵͳCLVariant����
	void saveSysVar(int ownerId, int type, unsigned int hdl);

	// ���¼���ϵͳCLVariant����
	void reloadSysVar();

	// ����ͨ��ϵͳ��ʱ������������һ��table����
	int saveSysTmpVar(lua_State* L);

	// ����ͨ��ϵͳ��ʱ����������һ��table����
	int loadSysTmpVar(lua_State* L);

	// �Ƿ�ֹͣDC API��־
	//void stopDcApiLog(bool sp);

	// �����Ƿ���tlog��־
	//void setOpenTlog(bool flag);
	// �Ƿ���tlog
	//bool openTlog();

	// ���
	//bool startGameSessionSrv(const char* ip, int port);

	bool startOneGameClient(const char* ip, int port, int serverId, int serverType);
	void resetGameRoute();
	void resetSingleGameRoute(int sid);

	void setBattleSrvFlag(int flag);
	// ��ȡ�����������
	// 0����ͨ����1��ս������ 2����ս����
	int getBattleSrvFlag();

	// �Ƿ�ս����
	bool isBattleSrv();

	// �Ƿ�����������
	bool isLianFuSrv();

	// �Ƿ���ͨ��
	bool isCommSrv();

	// �Ƿ���ս����
	bool isCrossWarSrv();

	// ������Ϣ��������ͨ����ս����, sidΪ0��ʾ�㲥��ȫ����������ֻ����ָ���ķ�
	void sendMsgToAllGameClient(const void* buff, int size, int sid = 0, int cross_method = CROSSSERVER_ALL);


	void sendPacketToAllGameClient(void* packet, int sid = 0, int cross_method = CROSSSERVER_ALL);

	// ���б���ɾ��һ��ս������������Ҿ�û�����뵽���ս������
	void removeBattleSrv(int sid);

	const char* loadStringFromFile(const char* filename);

	//��ˢ�����ַ���
	bool	reloadFilterDb();

	// �����ַ���
	const char* filterText(const char* text);

	//�ж��ַ��������д�����
	int filterTextCount(const char* text);

	void execute(const char* cmd);

	bool outputConfigFile(const char* fn, const char* output);

	// ����һ���첽�Ĺ����̣߳�ע�⣬gameserver����ʱ���Զ�����һ���߳�
	// ���Գ����Ǹ��߳���ΪĳЩԭ������ס�ˣ�����Ҫ�����������
	// ���Ϊ���ȵĴ�ʩ
	void startAsyncWorker();
	// ���¼���
	void reloadWorkerScript();
	// ����lua����Ϣ���첽�߳�
	int sendMessageToAsyncWorker(lua_State* L);
	//�ڳ���������һ����Ʒ
	//void dropPackage(void* et, int nItemID, int nCount, int nBind, int nStrong = 0);

	void regScriptNetMsg(int sysId, int cmdId);

	// ���¼��ع��������
	bool monUpdate();

	// ���¼���item������
	bool itemUpdate();

	// ������һؿ�����ֵ
	void changePrestigeExp();

	// ��Ʒ�����ȸ���
	//bool itemUpdate();
	// ���������ȸ���
	//bool skillUpdate();
	// �������� �ȸ���
	//bool envirUpdate();
	// �������� �ȸ���
	//bool questUpdate();
	// buff�б� �ȸ���
	//bool reloadBuffConfig();

	// ���¼������ƻ�ȡ���ܵ�id
	//int	getSkillIdByName(const char* skillName);

	//���¼������԰�
	bool reloadLang();

	//����db����������c++��������lua���� 0����c++����������lua����
	void setDbRetRoute(int sysid, int cmd, int val);

	//�������к�
	//double allocSeries();

	//���һ��attr����
	//void clearAttrConfig(int sysid);

	//����һ��attr��������
	//int createAttr(int sysid);

	//����һ��attr����
	//bool setAttr(int sysid, int index, int attrType, float attrValue);

	//����һ��attr����
	//int getAttrList(lua_State* L);

	// ����һ������������ķ�����
	void sendDataToCenter(void* pack);

	// ����c++�ĵ�Ԫ����
	void runGTest();

	// ȫ�����������
	//int getMonsterCount();

	// ���ù���������Ĳ������Ե���cpu��ռ��
	//void setMonsterMgrDiv(int num);

	//void broadcastToScene(void* scenePtr, void* packet);

	// ת����һ��int64λ������
	double getInt64(double num);

	// ��ȡ��������
	//const char* getSkillNameById(int skillId);

	// �㲥������Ϣ
	//void broadcastGuild(int guildid, void* packet, bool isAll);

	// ���Ͱ���������ڷ�
	void sendDataToActorServer(void* pack);

	// �����Ƿ���������Ч��
	void enableCheckDataValid(bool flag);

	// �������������Ч�Ա�ʶ
	void setActorDataValid(int serverId, int actorId, bool flag);

	// ����tips
	void sendTipmsg(int actorid, const char* msg, int type = ttTipmsgWindow);

	// ɾ��һ�����ӵ�gameclient
	void delOneGameClient(int serverId);

	int loadFileAsUserData(lua_State *L);
	int saveUserDataToFile(lua_State *L);

	// ����һ�����������е�ʵ��ָ��
	int getOnlineActorList(lua_State *L);
	// ����һ��������������ҵ�basicdataָ��,(ԭ���ϲ����޸�basicdata��������������޸���Ҳ���ܱ���)
	int getAllActorData(lua_State *L);
	int findSkirmish(lua_State* L);
	int FindFieldPlayer(lua_State* L);

	int sendMail(lua_State* L);
	void regInstanceMonsterDamage(int fid);
	void regInstanceActorDamage(int fid);

	// timedomain����
	bool regStartScript(const char* rule);
	bool regEndScript(const char* rule);
	bool checkRuleTime(const char* rule);
	double getRuleStartTime(const char* rule);
	double getRuleEndTime(const char* rule);


	// global mail 

	int getGlobalMailMaxUid(void);
	void addGlobalMail(const char* head, const char* context, const char* item_str);

	void buyMonthCard(int actorid);
	void buyPrivilege(int actorid);

	void buyPrivilegeCard(int actorid); // ������Ȩ

	void buyRechargeLimitPackage(int actorid, int money);
	void buyRechargeLimitPackageOffline(Actor* tar, int money);

	void buyFund(int actorid, int money);
	void buyFundOffline(Actor* tar, int money);

	int rand(int max);
	int getTimeZone(void);

	void shutup(int actor_id, int time);
	void releaseShutup(int actor_id);

	void offlineChangeTitle(int actor_id, int oper, int tId);
	
	// ���
	bool startGameConnSrv(const char* ip, int port);
	void stopGameConnSrv();
	//ֻ��activitysystem��
	int  time2String(lua_State* l);
	int getActorCountOfZhuanShengLv(int lv);
	double getGameTick();
	void logDKMLog(const char* logstr, const char* pf = "0");
	void printAllLua(void* et);
	int getClvariantSize(void* et, const char* str);
}

//tolua_end

#endif

