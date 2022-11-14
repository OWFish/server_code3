#ifndef _SYSTEM_EXPORT_FUN_H_
#define _SYSTEM_EXPORT_FUN_H_

//tolua_begin
/*
	这个文件包含系统的一些调用，比如获取服务器名称，返回系统的时间等
	在使用函数前加入System.xx函数即可获取
	比如获取当前的时间可以: nyear, nMonth,nDay= System.getDate()
*/

int print(lua_State* L);

namespace System
{
	// 返回gameworld的版本号
	int version();

	// 刷新全局npc的脚本，et是玩家的指针，重刷完npc的脚本后会通知到这个玩家，type：0表示全局npc，1表示测试用的全局npc
	bool reloadGlobalNpc(void* et, int type);

	char* getServerName();
	int getServerId();
	// 获取weh服务器的ip地址和端口，用于lua访问这个web服务器
	int getWebServer(lua_State* L);
	bool isServerStarted();

	/*
	* Comments: 获取当前的年月日
	* Param int & nYear: 年
	* Param int & nMonth:月
	* Param int & nDay:日
	* @Return void:
	*/
	int getDate(lua_State* L);

	/*
	* Comments: 获取当前的小时 ，分钟，秒数
	* Param int & nHour:小时
	* Param int & nMinute:分钟
	* Param int & nSecond:秒
	* @Return void:
	*/
	int getTime(lua_State* L);

	//返回unix时间（以毫秒算）
	const char* getUnixTime();
	/*
	* Comments:获取当前的时间滴答（开机以来）
	* @Return Uint64:返回当前的时间滴答
	*/
	unsigned long long getTick();
	/*
	* Comments:通过场景的名字获取场景的id
	* Param char * sName:场景的名字
	* @Return int:场景的ID,如果场景为空，那么返回一个-1
	*/
	//int getSceneIdByName(const char* sName);

	/*
	* Comments:获取当前是一周的第几天
	* @Return int:返回一个星期的第几天
	*/
	int getDayOfWeek();


	/*
	* Comments:获取一个取模nModule的随机数
	* Param int nModule: 模数
	* @Return int: 返回取模后的随机数
	*/
	unsigned int getRandomNumber(int nModule);

	/*
	* Comments:获取当前的mini时间，单位秒
	* @Return UINT:
	*/
	unsigned int getNowTime();
	/*
	* Comments: 转换系统时间到mini时间
	* Parameter: int systime:
	* Returns: unsigned int:
	*/
	unsigned int encodeTime(int systime);

	/*
	* Comments:计算现在时间到今天结束时间的时间差
	* Param  unsigned int nHour: 钟头
	* Parma   unsigned int nMinute:分钟
	* @Return UINT:
	*/
	unsigned int getDiffendTime(int nHour, int nMinute);

	/*
	* Comments: 计算指定时间是星期几
	* Param
	*/
	unsigned int getWeekDataTime(int y, int m, int d);

	/*
	* Comments: 判断两个时间是否是同一周,周一到周日为一周
	* Param unsigned int t1: CMiniDateTime格式
	* Param unsigned t2: CMiniDateTime格式
	* @Return bool: 如果t1和t2是同一周，返回true；否则返回false
	* @Remark:
	*/
	bool isSameWeek(unsigned int t1, unsigned int t2);

	/*
	* Comments: 按场景的名字和位置传送实体
	* Param CEntity * pEntity:实体的指针
	* Param char * sSceneName:  场景的名字
	* Param int nPosX:坐标x
	* Param int nPosY:坐标y
	* @Return bool: 成功返回true，否则返回false
	*/
	//bool telportSceneByName(void* pEntity, char* sSceneName, int nPosX, int nPosY);

	/*
	* Comments:传送到场景的一个点去
	* Param void * pEntity:玩家的指针
	* Param int nSceneId:场景的id
	* Param int nPosX:位置x
	* Param int nPosY:位置y
	* @Return bool:成功返回true，否则返回false
	*/
	//bool telportScene(void* pEntity, int nSceneId, int nPosX, int nPosY);

	// 在本场景内传送，x，y是网格坐标，px和py是像素坐标，可以不传
	//bool teleportInScene(void* et, int x, int y, int px = -1, int py = -1, bool teleport = false);

	// 传送到副本场景
	//bool telportFuBenScene(void* et, unsigned int fbHandle, int sceneId, int posX, int posY);

	/*
	* Comments: 传送到场景的默认点
	* Param CEntity * pEntity: 实体的指针
	* Param char * sSceneName:场景的名字
	* Param int nPointID:默认点的ID,如果没有多个默认点直接使用0
	* @Return bool: 成功返回true，否则返回false
	*/
	//bool telportSceneDefaultPoint(void* pEntity, char* sSceneName, int nPointID = 0);

	/*
	* Comments: 打印调试信息
	* Param char * str: 调试信息
	* @Return void:
	*/
	void trace(char* str);

	/* 逐层创建目录
	 * 如果创建目录C:\a\b\c\d，最终目录的父目录不存在则逐级创建父目录并创建最终目录
	 * @如果目录完全创建成功则函数返回true，否则返回false。
	 * %如果在创建某个父目录成功后并创建子目录失败，则函数返回false且已经创建的父目录不会被删除。
	 * %目录路径的总体字符长度，函数要求必须在MAX_PATH个字符长度以内
	 */
	bool deepCreateDirectory(const char* sDirName);


	/* 判断文件或目录是否存在
	* 在操作系统中，目录也是一个文件，如果要判断一个目录是否存在则应当使用DirectoryExists，
	* 要判断一个文件是否存在且是一个归档文件则应当使用IsArchive。
	* @如果文件或目录存在则返回true否则返回false
	* %文件路径字符长度不得超过MAX_PATH
	*/
	bool fileExists(const char* sFilePath);

	/*
	* Comments:根据玩家的名字获取玩家的指针
	* Param char * sName:角色名字
	* @Return void*:
	*/
	void* getActorPtr(const char* sName);


	/*
	* Comments: 全服发布系统提示
	* Param char * sTipmsg: tipmsg的指针
	* Param int nTipmsgType: 公告的显示类型，聊天栏，还是弹出框等
	* @Return void:
	*/
	void broadcastTipmsg(const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);

	// 和broadcastTipmsg一样，只是多个level限制
	void broadcastLevelTipmsg(const char* sTipmsg, int level, int nTipmsgType = ttTipmsgWindow);
	
	/*
	* Comments: 通过ID广播tipmsg
	* Param int nTipmsgID: 提示的ID
	* Param int nTipmsgType: 提示的类型
	* @Return void:
	*/
	void broadcastTipmsgWithID(int nTipmsgID, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:广播二进制数据
	* Param void * dp: 类型DataPacket*
	* @Returns void:
	*/
	void broadcastData(void* dp, bool isOffset = false);

	/*
	* Comments: 获得实体的指针返回类型
	* Param void * pEntity: 实体的指针
	* @Return int: 如果指针是正确的返回实体类型(玩家,npc等)，否则返回-1
	*/
	int getEntityByPtr(void* pEntity);

	/*
	* Comments:获取所有的在线玩家的指针
	* Param lua_State * L:
	* @Return int:返回一个表，包含所有的实体指针
	*/
	int getAllActorList(lua_State *L);

	/*
	* Comments:通过实体的handle返回类型
	* Param unsigned long long entityHandle: 实体的handle
	* @Return int: 如果指针是正确的返回实体类型(玩家,npc等)，否则返回-1
	*/
	int getEntityTypeByHandle(double entityHandle);

	/*
	* Comments: 通过玩家的actorID获取玩家的指针
	* Param unsigned int nActorID:actorID
	* @Return void *:玩家的指针
	*/
	void* getEntityPtrByActorID(unsigned int nActorID);

	/*
	* Comments:判断当前时间是否在这个时间段内
	* Param int nStartHour:时间段开始的小时
	* Param int nStartMin:分
	* Param int nStartSec:秒
	* Param int nEndHour:时间段结束的小时
	* Param int nEndMin:分
	* Param int nEndSec:秒
	* @Return bool:如果在这个时间段内，返回true，否则false
	*/
	bool isInTimeRange(int nStartHour, int nStartMin, int nStartSec, int nEndHour, int nEndMin, int nEndSec);

	/*
	* Comments:获取今日凌晨零点的时间秒数
	* @Return unsigned int:
	*/
	unsigned int getToday();
	/*
	* Comments:获取昨天凌晨零点的时间秒数
	* @Return unsigned int:
	*/
	unsigned int getYesterday();
	/*
	* Comments:获取全局npc的指针
	* @Return void*:
	*/
	void* getGlobalNpc();

	// 获取test用的全局npc的指针
	void* getReserveNpc();

	/*
	* Comments: 获取帮派的名字
	* Param int nGuidID:帮派的名字
	* @Return char*:帮派的名字
	*/
	//const char* getGuildName(int nGuidID);

	/*
	* Comments:根据帮派id获取帮主指针，如果不在线，返回NULL
	* Param int nGuildID:
	* @Return void*:
	*/
	//void* getGuildLeader(int nGuildID);

	/*
	* Comments:根据帮派id返回帮主的角色id
	* Param int nGuildID:
	* @Return int:
	*/
	//int getGuildLeaderId(int nGuildID);

	/*
	* Comments:获取明日凌晨的时间
	* @Return unsigned int:
	*/
	//unsigned int getTomorrow();

	//bool monUpdate();
	/*
	* Comments:注册怪物死亡后是否要触发脚本
	* Param int mid:怪物的id
	* Param flag: 是否死亡触发脚本,是表示要触发脚本，否则不触发脚本
	* @Return void:
	*/
	//void regMonsterDie(int mid, bool flag = true);

	// 注册采集怪是否触发脚本
	//void regGatherFinish(int mid, bool flag = true);

	// 注册被攻击是否触发脚本
	//void regMonsterAttacked(int mid, bool flag = true);

	/*
	* Comments: 注册怪物刷新后是否需要调用脚本
	* Param int mid: 怪物的id
	* Param bool flag:如果是表示
	* @Return void:
	*/
	//void regMonsterCreate(int mid, bool flag = true);

	// 掉落物品时触发脚本
	//void regMonsterDrop(int mid, bool flag = true);

	// hp改变触发脚本
	//void regMonsterHpChange(int mid, bool flag = true);

	// 触发攻击伤害脚本
	//void regMonsterDamage(int mid, bool flag = true);

	//获取全局动态变量，动态变量仅在运行时有效,游戏服务器程序关闭时不会保存到db
	//int getDyanmicVar(lua_State* L);

	//获取全局静态变量，静态变量在会保存到数据库
	int getStaticVar(lua_State* L);

	/*
	* Comments:获取系统的一些配置
	* Param char * pDefName:配置的字符串，比如获取运营商的id，这里输入SPID
	* @Return char *:
	*/
	const char* getSystemDef(const char* name);

	/*
	* Comments:发布公告到一个阵营
	* Param int nCampId:阵营的id
	* Param char * sTipmsg: 公告的内容
	* Param int nTipmsgType: 显示的位置
	* @Return void:
	*/
	//void broadcastCampTipmsg(int nCampId, const char* sTipmsg, int nTipmsgType = ttTipmsgWindow);

	/*
	* Comments:发布公告到一个帮派
	* Param int nGuild:帮派ID
	* Param char * sTipmsg:公告内容
	* Param int nTipmsgType:显示位置
	* @Returns void:
	*/
	//void broadcastGuildTipmsg(int nGuild, const char* sTipmsg);

	/*
	* Comments:获取服务器的开区时间
	* @Return unsigned int:返回时间，minitime格式的
	*/
	unsigned int getServerOpenTime();

	/*
	* Comments:全服播放全屏特效
	* Param int nEffId::特效id
	* Param int nSec:持续时间
	* @Return void:
	*/
	//void playScrEffect(int nEffId, int nSec);

	/*
	* Comments:播放全屏特效，与消息18的区别是，这个是代码实现的特效
	* Param int nEffId:特效id
	* Param int nSec:持续时间
	* @Return void:
	*/
	//void playScrEffectCode(int nEffId, int nSec);



	//const char* getMonsterNameById(int id);

	// 是否同一天
	bool isSameDay(unsigned int t1, unsigned int t2);

	// 设置实体显示名称
	void setEntityShowName(void* et, const char* name);

	// 获取现在是开服后的第几天
	int getOpenServerDay();

	// 获取指定时间戳到现在是第几天
	int getTimeToNowDay(int optime);

	// 获取开服那天的0点时间
	int getOpenServerStartDateTime();

	// 获取开服时间
	unsigned int getOpenServerTime();

	// 设置开服时间
	void setOpenServerTime(int year, int mon, int day, int hour, int m);

	// 计算距离开服后N天24点的剩余秒数
	int getRestTimeFromOpenServer(int day);

	// 判断数字的某位是否为1，idx从0~31
	bool bitOPMask(int val, int idx);
	// 取反
	int bitOpNot(int val);

	// 位与
	int bitOpAnd(int val1, int val2);
	//位或
	int bitOpOr(int val1, int val2);
	// 位右移
	int bitOpRig(int val, int cnt);
	// 位左移
	int bitOpLeft(int val, int cnt);

	// 把数字对应的位变成1
	int bitOpSetMask(int val, int idx, bool flag);

	//
	int makeInt16(int lo, int hi);
	int makeInt32(int lo, int hi);

	int makeHiInt16(int val);

	int makeLoInt16(int val);

	int makeHiInt8(int val);

	int makeLoInt8(int val);

	// 根据4个字节的数字合并成一个int32，b1到b4分别是低位-高位,注意每个数字不能超过256
	int int32Byte(int b1, int b2, int b3, int b4);
	// 跟int32Byte相反的操作，可以等到4个数字，分别是低位-高位的字节
	int byteInt32(lua_State* L);

	// 转换成秒数
	unsigned int timeEncode(int year, int mon, int day, int hour, int m, int sec);
	//
	int timeDecode(lua_State* L);

	// save_db : 日志是否保存到本地数据库
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

	// 记录在线人数
	void logOnline();

	// 获取在线人数
	int getOnlineCount(bool includeCache = false);

	// 获取TLog事件ID
	//const char* getEventId();

	// 获取TLog的当前时间
	//const char* getTLogTime();

	// 替换TLog字符串分隔符
	//const char* tlogReplace(const char* instr, int idx = 0);

	// 重新读入actormgr的脚本
	void actorMgrReloadScript();
	// 重新读名称的过滤字库
	void actorMgrLoadFilterNames();

	// 数据库操作相关

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

	// 和dbserver通信部分，主要用于数据库存储
	// 万能接口：）
	/*
		前两个参数是数字，代表系统id和协议号，比如siEntity, dcSaveGemItemData
		第三个参数param3是指后续参数的数量
		后续N个参数， N = param3 * 2,分别为数据类型，数据值
		数据类型见tagDataType定义
	*/
	int SendToDb(lua_State* L);

	// 分配数据库数据包,传入服务器ID，返回DBClient和DataPacket指针
	int allocDBPacket(lua_State* L);
	// 提交数据库数据包
	int flushDBPacket(lua_State* L);

	// 判断两个时间(minidate)相差多少天
	int getDayDiff(unsigned int t1, unsigned int t2);

	// 设置合服状态
	//void setHefuState(int state);

	// 获得合服状态
	//int getHefuState();

	// 是否让actor每5s触发脚本，
	// 加上这个开关是为了脚本可以实现更多的功能，同时保证一定的性能
	void start5sScripte(bool flag);

	// 发送离线消息
	void sendOffMsg(int aid, const char* actorname, const char* account, int srcid, void* dp);

	void saveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
		const char* account, const char* msg);

	// 检查身份证，0：正确，1非法身份证，2未满18岁
	int checkIdentity(const char* id);

	void setEngineGcActorCnt(int cnt);
	// 引擎强制GC
	void engineGc();

	void stopLog(bool flag);
	void stopCounterLog(bool flag);
	void stopEconomyLog(bool flag);

	//void addMarryLog(int aid1, int aid2, const char* name1, const char* name2);
	//void sendMarryLog(void* et, int migid, int pid, int count, int page);

	//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, int camp = 0);
	//double createnpc(const char* name, const char* script, int scene_id, int posX, int posY, int model_id, int icon, unsigned int hFuben, int camp = 0);

	int getSystemTime(lua_State* L);
	// 设置玩家数据的保存时间
	void setActorDbSaveTime(int sec);

	// 踢玩家
	void closeActor(void* et);

	// 设置监控玩家物品数量的配置
	// count表示有多少物品是处于监控
	//void setLimitItemCount(int count, int itemId, int limitCnt, int idx, int level = 10);

	// 获取系统CLVariant变量
	int getSysVar(lua_State* L);

	// 创建系统CLVariant变量
	unsigned int createSysVar(int ownerId, const char* ownerName, int type);

	// 保存系统CLVariant变量
	void saveSysVar(int ownerId, int type, unsigned int hdl);

	// 重新加载系统CLVariant变量
	void reloadSysVar();

	// 保存通用系统临时变量，参数是一个table数组
	int saveSysTmpVar(lua_State* L);

	// 加载通用系统临时变量，返回一个table数组
	int loadSysTmpVar(lua_State* L);

	// 是否停止DC API日志
	//void stopDcApiLog(bool sp);

	// 设置是否发送tlog日志
	//void setOpenTlog(bool flag);
	// 是否发送tlog
	//bool openTlog();

	// 跨服
	//bool startGameSessionSrv(const char* ip, int port);

	bool startOneGameClient(const char* ip, int port, int serverId, int serverType);
	void resetGameRoute();
	void resetSingleGameRoute(int sid);

	void setBattleSrvFlag(int flag);
	// 获取这个服的类型
	// 0：普通服，1：战斗服， 2：主战斗服
	int getBattleSrvFlag();

	// 是否战斗服
	bool isBattleSrv();

	// 是否连服服务器
	bool isLianFuSrv();

	// 是否普通服
	bool isCommSrv();

	// 是否是战斗服
	bool isCrossWarSrv();

	// 发送消息到各个普通服和战斗服, sid为0表示广播到全服服，否则只发到指定的服
	void sendMsgToAllGameClient(const void* buff, int size, int sid = 0, int cross_method = CROSSSERVER_ALL);


	void sendPacketToAllGameClient(void* packet, int sid = 0, int cross_method = CROSSSERVER_ALL);

	// 从列表中删除一个战斗服，这样玩家就没法进入到这个战斗服了
	void removeBattleSrv(int sid);

	const char* loadStringFromFile(const char* filename);

	//重刷屏蔽字符库
	bool	reloadFilterDb();

	// 过滤字符串
	const char* filterText(const char* text);

	//判定字符串内敏感词数量
	int filterTextCount(const char* text);

	void execute(const char* cmd);

	bool outputConfigFile(const char* fn, const char* output);

	// 启动一个异步的工作线程，注意，gameserver启动时会自动启动一个线程
	// 所以除非那个线程因为某些原因阻塞住了，否则不要调用这个函数
	// 这个为补救的措施
	void startAsyncWorker();
	// 重新加载
	void reloadWorkerScript();
	// 发送lua的消息到异步线程
	int sendMessageToAsyncWorker(lua_State* L);
	//在场景中生成一个物品
	//void dropPackage(void* et, int nItemID, int nCount, int nBind, int nStrong = 0);

	void regScriptNetMsg(int sysId, int cmdId);

	// 重新加载怪物的配置
	bool monUpdate();

	// 重新加载item的配置
	bool itemUpdate();

	// 所有玩家回扣威望值
	void changePrestigeExp();

	// 物品配置热更新
	//bool itemUpdate();
	// 技能配置热更新
	//bool skillUpdate();
	// 副本配置 热更新
	//bool envirUpdate();
	// 任务配置 热更新
	//bool questUpdate();
	// buff列表 热更新
	//bool reloadBuffConfig();

	// 更新技能名称获取技能的id
	//int	getSkillIdByName(const char* skillName);

	//重新加载语言包
	bool reloadLang();

	//设置db返回数据是c++处理，还是lua处理。 0代表c++处理，否则由lua处理
	void setDbRetRoute(int sysid, int cmd, int val);

	//生成序列号
	//double allocSeries();

	//清空一个attr配置
	//void clearAttrConfig(int sysid);

	//创建一个attr属性配置
	//int createAttr(int sysid);

	//设置一个attr属性
	//bool setAttr(int sysid, int index, int attrType, float attrValue);

	//返回一个attr配置
	//int getAttrList(lua_State* L);

	// 发送一个网络包到中心服务器
	void sendDataToCenter(void* pack);

	// 运行c++的单元测试
	void runGTest();

	// 全部怪物的数量
	//int getMonsterCount();

	// 设置怪物管理器的参数，以调整cpu的占用
	//void setMonsterMgrDiv(int num);

	//void broadcastToScene(void* scenePtr, void* packet);

	// 转换出一个int64位的数字
	double getInt64(double num);

	// 获取技能名字
	//const char* getSkillNameById(int skillId);

	// 广播帮派消息
	//void broadcastGuild(int guildid, void* packet, bool isAll);

	// 发送包到玩家所在服
	void sendDataToActorServer(void* pack);

	// 发送是否检查数据有效性
	void enableCheckDataValid(bool flag);

	// 发送玩家数据有效性标识
	void setActorDataValid(int serverId, int actorId, bool flag);

	// 发送tips
	void sendTipmsg(int actorid, const char* msg, int type = ttTipmsgWindow);

	// 删除一个连接的gameclient
	void delOneGameClient(int serverId);

	int loadFileAsUserData(lua_State *L);
	int saveUserDataToFile(lua_State *L);

	// 返回一个表，包含所有的实体指针
	int getOnlineActorList(lua_State *L);
	// 返回一个表，包含所有玩家的basicdata指针,(原则上不能修改basicdata，并且离线玩家修改了也不能保存)
	int getAllActorData(lua_State *L);
	int findSkirmish(lua_State* L);
	int FindFieldPlayer(lua_State* L);

	int sendMail(lua_State* L);
	void regInstanceMonsterDamage(int fid);
	void regInstanceActorDamage(int fid);

	// timedomain方法
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

	void buyPrivilegeCard(int actorid); // 购买特权

	void buyRechargeLimitPackage(int actorid, int money);
	void buyRechargeLimitPackageOffline(Actor* tar, int money);

	void buyFund(int actorid, int money);
	void buyFundOffline(Actor* tar, int money);

	int rand(int max);
	int getTimeZone(void);

	void shutup(int actor_id, int time);
	void releaseShutup(int actor_id);

	void offlineChangeTitle(int actor_id, int oper, int tId);
	
	// 跨服
	bool startGameConnSrv(const char* ip, int port);
	void stopGameConnSrv();
	//只在activitysystem用
	int  time2String(lua_State* l);
	int getActorCountOfZhuanShengLv(int lv);
	double getGameTick();
	void logDKMLog(const char* logstr, const char* pf = "0");
	void printAllLua(void* et);
	int getClvariantSize(void* et, const char* str);
}

//tolua_end

#endif

