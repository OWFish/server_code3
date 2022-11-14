#pragma once

/****************************************************************************************
* 服务端之间通信协议定义                                                   
* 命名规范：
* namespace 服务端名称Proto
* {
*    enum e目标服务端名称Code
*    {
*       //通信消息号注释，数据段格式（数据名称：数据类型【byte,short,int,shortString,string】）
*       c消息号别名 = 消息号值，其中c表示通信双方中的客户端方发送，从1开始
*       //通信消息号注释，数据段格式（数据名称：数据类型【byte,short,int,shortString,string】）
*       s消息号别名 = 消息号值，其中s表示通信双方中的服务端方发送，从1开始
*    };
* };
****************************************************************************************/

namespace InterSrvComm
{
	static const int DBSER_VER = 161122;

	namespace DbServerProto
	{		
		enum SystemId
		{
			siDefault = 0,	//特殊命令
			siActor = 1,
			siGuild = 2,
			siConsignment = 3,
			siMsg = 4,
			siRank = 5,
			siGlobal = 6,
			siFight = 7,
			siMail = 8,
			siCommon = 9,
			siConfig = 10,
			siWarTeam = 11,
			siTxApi = 12,
			siCommonDB = 13,
			siAuction = 14,
			siPvmDB = 15,
		};

		enum DefaultSysId
		{
			dcInitDB = 1,			//初始化数据库，特殊指令
			dcExecDB = 2,			//执行sql语句
		};


		/**数据服务器和逻辑服务器的命令码**/
		// 部分在脚本使用到了，所以不要任意修改
		// 注意：部分的数据在跨服战中不用读取，部分是读取但不用保存
		enum EntityMgrId
		{
			dcDefault,			//默认处理，0

			// g-d
			dcQuery = 1,		//查询数据
			dcSave = 2,			//保存数据 actors
			dcSaveRole,			// roles
			dcSaveVar,			//加载角色变量 actorvariable.variable
			dcSaveItem,			// items
			dcSaveMail,
			dcSaveStore,
			dcSaveTogHitEquip,	//保存合击装备
			dcLogout,			// 玩家下线

			// d-g
			dcLoad,
			dcLoadRole,
			dcLoadItem,
			dcLoadMail,
			dcLoadVar,			//加载角色变量
			dcLoadStore,		//加载商城
			dcLoadTogHitEquip, //加载合击装备

			dcLoadFriends = 35,		// 读取本人的好友相关列表
			dcUpdateFriend = 36,		// 更新好友的信息
			dcDelFriend = 37,		// 删除好友信息

			dcLoadMsg = 27,		//读取用户的消息数据
			dcDeleteMsg = 28,			//删除某条消息


			// todo下面是旧的，以后整理删掉
			//dcLoadQuest = 3,         //装置任务数据
			//dcSaveQuest = 4,		//保存用户的任务数据（跨服战不保存）
			//dcLoadSkill = 5,        //装置技能数据
			////dcSaveSkill = 6,        //保存技能数据（跨服战不保存）
			//dcLoadBagItem = 7,      //装载背包物品
			//dcSaveBagItem = 8,      //保存背包物品数据 （跨服战要保存，因为要消耗药品）
			//dcLoadEquipItem = 9,    //装载装备物品
			//dcSaveEquipItem = 10,    //保存装备物品（跨服战不保存）
			//dcLoadDepotItem = 11,    //装载仓库物品 （跨服战不读取）
			//dcSaveDepotItem = 12,    //保存仓库物品，13（跨服战不保存）

			dcLoadBuff = 15,			//加载角色buff的数据
			dcSaveBuff = 16,			//保存角色buff的数据（跨服战保存，有buff时间）



			dcAddMember = 23,		//增加帮派成员
			dcSaveActorGuild = 24,	//保存个人帮派信息
			dcDeleteMember = 25,		//删除某个成员


			dcLoadConsiTimeoutItem = 26,	//读取已经下架的个人物品		（跨服战不读取）



			dcLoadSpiritItemData = 29,				// 读取宝物数据
			dcSaveGemItemData = 30,				// 保存宝物数据		（跨服战不保存）

			dcLoadMountData = 31,        //装载坐骑的数据
			dcSaveMountData = 32,		 //保存坐骑的技能数据	（跨服战不保存）

			dcSaveDmkjItem = 33,		//保存抽奖的仓库物品	（跨服战不保存）
			dcLoadDmkjItem = 34,		//读取抽奖仓库的数据	（跨服战不读取）


			dcUpdateFriendInfo = 38,    //更新好友数据（下线时间）
			dcUpdateFriendContact = 39,	//更新最近联系时间（下线的时候）

			dcSaveCale = 40, //保存副本统计数据（跨服战不读取）
			dcLoadCale = 41, //读副本统计数据

			dcLoadFbCountData = 42, // 读取每天进入副本次数数据（跨服战不读取）
			dcSaveFbCountData = 43, // 保存每天进入副本次数数据

			// 剧情动画
			dcLoadPlotData = 48,	//（跨服战不读取）
			dcSavePlotData = 49,	// 这两个已无用

			//dcLoadMiscStruct = 50,	// 读取杂七杂八数据	（跨服战不读取）
			//dcSaveMiscStruct = 51,	// 保存杂七杂八数据

			// 竞技场
			dcLoadFightLog = 55,				// 读取PK记录	（跨服战不读取）
			dcAddFightLog = 56,				// 添加一条PK记录

			dcSlaveAll = 57,				// 苦工系统相关的数据保存，由脚本处理	(取消）

			dcDelFightLog = 58,				// 删除一条PK记录

//			dcLoadMail = 59,		//读取用户的邮件数据	（跨服战不读取）
			dcDeleteMail = 60,			//删除邮件
			dcUpdateMailStatus = 61,			//更新邮件状态
			dcDeleteMailFile = 62,		//删除邮件附件
			dcGetActorIdFromActroName = 63, //根据玩家名字获取玩家ID

			dcSaveEntrustItem = 64,		//保存副本委托的仓库物品	（跨服战不读取）
			dcLoadEntrustItem = 65,				//读取副本委托仓库的数据

			dcSaveActorMisc = 68,		// 保存杂七杂八的数据
			dcLoadActorMisc = 69,		// 读取杂七杂八的数据

			dcSavePetCrossItem = 70,		//保存宠物闯关仓库（珍宝囊）（跨服战不保存）
			dcLoadPetCrossItem = 71,		//读取宠物闯关仓库（珍宝囊）的数据（跨服战不读取）

			dcResetCrossPos = 80,		// 重置跨服位置
			dcLoadCrossVar = 81,		//加载角色跨服战变量
			dcSaveCrossVar = 82,		//保存角色跨服战变量
			dcLoadSkillMiji = 83,      //读取技能秘籍数据
			dcSaveSkillMiji = 84,     //保存秘籍数据（跨服战不保存）

			dcSaveTongTianTaStoreItem = 85, //保存通天塔仓库(跨服战不保存)
			dcLoadTongTianTaStoreItem = 86, //读取通天塔仓库(跨服战不读取)

			dcSaveWing = 87,		//保存翅膀
			dcLoadWing = 88,		//读取翅膀

			//宠物相关
			//dcLoadAllPet = 96, // 加载所有宠物
			//dcDeletePet	 = 97, // 删除宠物
			dcLoadPetBase = 98, // 加载宠物基础数据
			dcSavePetBase = 99, // 更新宠物

			dcPetSkill = 100,  // 宠物技能相关
			//dcLoadPetGotType    = 101,  // 读取宠物的历史记录（跨服战不读取）
			//dcAddPetGotType     = 102,  // 增加宠物的历史记录（跨服战不保存）
			dcPetLoadEquip = 103,  // 加载宠物装备
			dcPetSaveEquip = 104,  // 保存宠物装备

			dcClearActorDbCache = 105, //清空玩家的缓存

			//铭刻相关
			dcAddEqSign = 106,//新增铭刻信息
			dcInheritEqSign = 107,//继承替换铭刻信息
			dcGetEqSignList = 108,//获取某装备上的铭刻信息

			dcSaveOnceTime = 111, // 设置保存一次的时间

			dcSaveRankVar = 112, // 保存排行榜相关数据

			dcSetDataValid = 115, // 设置有效性标识
			dcEnableCheckValid = 116, // 是否启用检查数据有效性

			dcLoadActorGuild = 117, //读取角色帮派信息

			dcSaveMarryInfo = 118,		//保存结婚信息
			dcLoadMarryInfo = 119,		//加载结婚信息
			dcOfflineLogout = 120,	//下线时，对方不在线，写入相关数据
			dcOfflineDivorce = 121,	//离婚时，对方不在线，写入相关数据

			dcSaveCsWarVar = 122,			//保存角色跨服专用变量
			dcLoadCsWarVar = 123,			//加载角色跨服专用变量

			dcActorCacheSave = 124,
			dcActorCacheLoad = 125,

			dcLoadPrivateChat = 126,	// 读取聊天记录
			dcAddPrivateChat = 127,		// 新增聊天记录
			dcDelPrivateChat = 128,		// 删除聊天记录
			dcBatchDelPrivateChat = 129,// 批量删除聊天记录
		};

		enum ConsignmentSysId
		{
			dcLoadConsignment = 1,	//读取所有的寄卖物品信息
			dcSaveConsignmentItem,  //保存寄卖物品,包括删除和添加
			dcConsignmentCount,		// 寄卖物品总数
		};

		enum GuildMgrId
		{
			dcLoadGuildList = 1,	// 帮派组件读入所有帮派的数据
			dcLoadGuildDetail,	// 帮派的详细数据
			dcAddGuild,			// 增加帮派
			dcDeleteGuild,		// 解散帮派
			dcSaveGuild,		// 保存帮派的信息
			dcLoadGuildMgrData, // 读取帮派名称列表等
			dcLoadGuildDepot,	// 读取仙宗仓库物品信息
			dcSaveGuildDepot,	// 保存仙宗仓库物品信息
			dcLoadBeastLog,		// 读取帮派神兽记录
			dcAddBeastLog,		// 添加帮派神兽记录
			dcDeleteBeastLog,	// 删除帮派神兽记录
			dcLoadGuildLog,		// 读取仙宗事件
			dcAddGuildLog,		// 添加仙宗事件
			dcDelGuildLog,		// 删除仙宗事件
			dcLoadOneGuild,		// 加载一个帮派的数据
			dcGuildCount,		// 帮派数量
			dcSaveGuildVar,		// 保存帮派数据(静态变量)
			dcLoadGuildVar,		// 读取帮派数据(静态变量)
			dcSaveGuildChat,	// 保存公会聊天记录
			dcLoadGuildStore,		// 读取公会商店记录
			dcSaveGuildStore,	   // 保存公会商店记录
		};

		enum AuctionId
		{
			dcAuctionAdd = 1,
			dcAuctionDel,
			dcAuctionUpdate,
		};

		enum TopTitleId
		{
			dcLoadRank = 1,	//读取有关头衔的排行榜数据
			dcLoadRankUser = 2, // 用户详细数据
			dcLoadRankPet = 3,  //宠物详细数据
			dcRankUserCount,	// 用户详细数据的数量
		};
		enum MsgMgrId
		{
			dcAddMsg = 1,				//增加用户一条信息

			dcAddChat = 2,				//聊天监控的信息
		};
		enum MailMgrId
		{
			dcAddMail = 1,				//增加用户一条邮件
			dcAddMailByActorName,	// 增加用户一条信息（通过玩家名称）
			dcAddMailByAccountName,			// 增加用户一条信息（通过open id）
		};
		enum GlobalMgr
		{
			dcLoadBossKiller = 1,		// 保存世界boss的击杀者
			dcSaveBossKiller,
			dcLoadMaster,				// 读取天元之主装备信息
			dcSaveMaster,				// 保存天元之主装备信息
			dcGmCmd,					// 发送gm命令 暂时改到lua里注册，以后整理消息时要改
			//dcAllActorBI,				// 发送用户数据到BI系统（已无用）
			dcCheckVer,					// 检查gameworld的版本是否与dbserver一致
			dcLoadMarry,				// 读取全服仙侣数据
			dcAddMarry,					// 增加一个结婚记录

			dcBattleFlag,				// 表示这个连接是否从战斗服发起，如果是，则不读取gmcmd表的数据

			dcAddQuestion = 10,		//增加一条问题
			dcLoadQuestions, //读取玩家所有的问题
			dcLoadQuestion,	//读取某一条问题
			dcUpdateQuestion,	//更新问题 已阅读

			dcAddBug = 14,	//增加一条bug
			dcLoadGoldRank,	//读取神榜内容

			dcAddGameServerInfo, //添加一条gameworld相关信息
		};
		enum FightRankId
		{
			dcLoadFightRank = 1,		// 读取竞技场排行榜
			dcSaveFightRank,			// 保存竞技场排行榜
		};

		enum SysVarMgrId
		{
			dcAddSysVar = 1,
			dcLoadSysVar,
			dcUpdateSysVar,
			dcSysVarCount,
		};


		enum configType
		{
			ctLoadGiftItem = 1,  //读取礼包作为物品的数据
			ctLoadGiftConfig = 2,		//读取礼包奖励数据
		};
		

		// 通信的错误码定义
		enum tagResultError
		{
			reSucc = 0,
			reDbErr,		//数据库执行错误
			reNoActor,		//没有该角色的属性信息
			reSaveErr,		//保存属性失败
			reNoLoad,		//还没有读入数据
			reDbNotConnected,  //DB连接不上
			reParamError,      //参数错误
			reNameError,	//名字不合法
			reNameInUse,	//名字被使用
			reTimeOut,		//操作超时
			reInterErr,		//内部错误
		};

		// 战队消息ID
		enum WarTeamSysId
		{
			dcLoadWarTeam = 0,
			dcAddWarTeam,
			dcDelWarTeam,
			dcUpdateWarTeam,
			dcLoadWarTeamMember,
			dcAddWarTeamMember,
			dcDelWarTeamMember,
			dcUpdateWarTeamMember,
			dcLoadOneWarTeam, // 获取一个战队的信息
			dcWarTeamCount, // 本服需要加载的战队数量
		};

		enum TxApiMsg
		{
			// 充值返回
			sFeeCallBack = 1,
			// 腾讯api返回
			sTxApiMsg = 2,
			// 更新用户身份证号码
			sUpdateIdentity = 4,

			// 关闭或开启赌博系统
			sCloseGamble = 5,

			// 用户充值获取token
			sChargeToken = 6,
			// 开通黄钻等获取token
			sGetToken = 7,

			//增值序列号
			sAddValueCard = 8,
			// 查询增值卡
			sQueryAddValueCard = 9,
			// 查询元宝数量
			sQueryYuanbaoCount = 10,
			// 提取元宝
			sWithdrawYuanbao = 11,
			// 发送登陆的key
			sLoginKey = 12,
		};

		enum CommonDBMsg
		{
			dcDBExec = 1, // 执行预定义
		};

		enum PVMDBMsg
		{
			dcLoadPVMlayer = 133, //读取竞技场玩家
			dcUpdatePVMlayer = 134, //新增竞技场玩家
			dcUpdateChallengeRecord = 135,//更新竞技场挑战记录
			dcLoadChallengeRecord = 136,//更新竞技场挑战记录
		};

		enum AFKCmd
		{
			dcLoadAFKData = 139,    //加载挂机练功数据
			dcSaveAFKData = 140,    //保存挂机练功数据
		};
	}

	namespace AsyncOperatorCode
	{
		enum tagAsyncOpError
		{
			soeSucc = 0,			// 成功
			soeDBErr,				// db执行错误（或者db无法连接）
			soeNoCardInfo,			// 不存在此卡信息
			soeTimeExpired,			// 查询超时
		};
	}

	// gameworld之间通信的协议
	namespace GameWorldProto
	{
		enum GwP
		{
			gpRegReq = 1,		// 注册消息，发送最基本的信息，比如serverid
			gpRegResp = 2,

			gpKeyReq = 3,		// 发送key的请求和回复
			gpKeyResp = 4,

			gpUserLogin = 5,	// 广播玩家登陆的消息
			gpBatchOnline = 6,	// 同步在线玩家的信息
			gpUserExit = 7,		// 玩家下线消息
			gpCloseUser = 8,	// 踢玩家下线

			gpGateway = 9,		// 同步网关的信息
			gpTtData = 10,      // 转传协议
			gpSsData = 11,		// C++代码内，服务器之间的游戏逻辑消息
			gpLfData = 12,		// 连服相关系统信息
			// 除此之外的全是游戏逻辑相关的信息
			gpCommonMsg,	// 游戏逻辑相关的消息
			gpCrossRelogin,	// 通知跨服服务器玩家重复登录
		};

		enum LfSysType {
			lsDefault = 0,
			lsGuild,
			lsRank,
		};

		enum SSP
		{
			stBroadCast,	//广播
			stRankList,		//发送排行榜列表
			stUserLogin,    //玩家登录
			stUserLogout,	//玩家登出
			stBatchOnline,	//批量上线(同步玩家登录信息)

			//stRecvMail, //通知玩家收邮件 todo lua实现
			stKickUser, //踢掉连服的玩家
			//stRecvOfflineMsg, //通知玩家收离线消息 todo lua实现

			stNormalMax = 100, //后面开始是脚本处理的消息
		};

		enum LfGuildCmd {
			lcGuildList, // 更新仙宗列表
			lcGuildUnion, // 仙宗结盟
			lcGuildDelUnion, // 
			lcCreateGuild, // 创建仙宗
			lcDelGuild, // 删除仙宗
			lcUpdateGuild, // 更新仙宗信息
			lcDelGuildMem, // 
			lcAddGuildMem, // 
			lcGuildBroadCast, // 仙宗广播
			lcUpGuildMemInfo, // 
			lcGuildOnline, // 普通服通知仙宗在线状态
			lcGuildLeaderInfo, //发送帮主的一些信息
			lcAddItemToDepot,  //增加一个道具到仓库
			lcAddGuildLog, //增加一条帮派见闻
			lcSendFightVal, //发送帮派战力
			lcChangePos,	//改变玩家职位
			lcDepotAvailible,	//帮派仓库剩余位置
			lcImpeach,		//弹劾
		};

		enum LfRankCmd {
			lcRankList = 0, // 发送排行榜列表
			lcRankTitle = 1,	//发送通知修改排行榜称号
		};
	};
	// gameworld 和 centerserver 之间的通信协议
	namespace CenterProto
	{
		enum CWP
		{
			cwComm = 1, // 直接转发的的数据包
			cwActorOnline = 2, //在某服在线或不在线
			cwActorServer = 3, //根据actorid发送到actorid所在服务器
			cwActorServerInfo = 4,	//玩家在哪个服务器
		};

		struct ActorOnline
		{
			int actorid_;
			int sid_;

			inline bool operator != (const ActorOnline& data) const
			{
				return actorid_ != data.actorid_;
			}
			inline bool operator > (const ActorOnline& data) const
			{
				return actorid_ > data.actorid_;
			}
			inline bool operator < (const ActorOnline& data) const
			{
				return actorid_ < data.actorid_;
			}
		};
	}
}

