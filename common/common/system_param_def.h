#ifndef _SYSTEM_PRARM_DEF_H_
#define _SYSTEM_PRARM_DEF_H_

using namespace InterSrvComm::DbServerProto;

//下面是一些系统的参数的定义，比如职业的ID,门派的id,实体类型等等
//tolua_begin


//新实体类型定义
#define MAX_ROLE 3
#define MAX_ACTOR_LEVEL 200  //玩家的最大等级
#define ZHUAN_SHENG_BASE_LEVEL 80	// 转生基础等级

#define PACK_LEN 50000 //分包长度
enum EntityType
{
	EntityType_Actor = 0,	//玩家抽象实体
	EntityType_Role,		//玩家角色实体
	EntityType_Monster,
	EntityType_Npc,        // 临时解决script_npc的兼容性问题，以后再改
	EntityType_CloneRole , // 克隆子角色
	EntityType_GatherMonster, //采集怪
	EntityType_DropBag,		//掉落物

	EntityType_Count,
};

enum FuBenType
{
	FuBenType_Chapter = 1,
	FuBenType_PublicBoss = 7,
	FuBenType_Pata = 9, //通天塔,爬塔
	FuBenType_WorldBoss = 10,
	FuBenType_HomeBoss = 17,
	FuBenType_City = 20,//主城
};

enum JobType
{
	JobType_None = 0,
	JobType_Warrior = 1,//战士
	JobType_Mage = 2,//法师
	JobType_Taoist = 3,//道士

	JobType_Max,
};

enum AwardType
{
	AwardType_Numeric  = 0, // 货币类型
	AwardType_Item	   = 1, // 道具
};

enum CurrencyType
{
	NumericType_Exp				= 0, 
	NumericType_Gold			= 1, // 金币
	NumericType_YuanBao			= 2, // 元宝
	NumericType_Fame			= 3, // 待定
	NumericType_Essence			= 4, // 精魄
	NumericType_GuildContrib	= 5, // 公会贡献
	NumericType_GuildFund		= 6, // 公会资金
	NumericType_Feats           = 7, // 功勋
	NumericType_Achieve			= 8, //成就积分
	NumericType_Shatter = 9, //符文碎片
	NumericType_SpeShatter = 10,//特殊符文碎片
	NumericType_Togeatter = 11, //低等级合击装备碎片
	NumericType_TogeatterHigh = 12, //高等级合击装备碎片
	NumericType_GodWeaponExp = 13,	//神兵经验
	NumericType_PrestigeExp = 14,	//威望经验
	NumericType_Chips = 15,//筹码
	NumericType_ShenShouExp = 16,	//神兽经验
	NumericType_VipExp	= 17,//vip经验
	NumericType_SkillExp = 18, //技能熟练度
	NumericType_Recharge = 99, // 充值元宝
};

enum ItemType
{
	ItemType_Equip = 0,
	ItemType_Gem,   
	ItemType_YuanShen,
	ItemType_Chest,
	ItemType_WingEquip,
	ItemType_TogetherHit,
	ItemType_FuWen,
	ItemType_Imba,
	ItemType_Holy = 15,
};

enum QualityType
{
	QualityType_White = 0,
	QualityType_Green,
	QualityType_Purple,
	QualityType_Orange,
	QualityType_Red,
	QualityType_Gold,
};

enum EquipType
{
	EquipType_Weapon = 0,//武器
	EquipType_Helmet,//1.头盔
	EquipType_Coat,//2.衣服
	EquipType_Necklace,//3.项链
	EquipType_Wrist,//4.护腕
	EquipType_Belt,//5.腰带
	EquipType_Ring,//6.戒指
	EquipType_Shoes,//7.鞋子
	EquipType_Dzi,  //8.官印
	EquipType_Hats,  //9.斗笠
	EquipType_Mark,  //10.面甲
	EquipType_Cloak,  //11.披风
	EquipType_Shield,  //12.盾牌
	EquipType_Max,
};

enum WingEquipType
{
	EquipType_Hub = 0,
	EquipType_Stone,
	EquipType_Feathers,
	EquipType_Colorplume,
};

enum RankingType
{
	RankingType_Power = 0,//0.总战力排行榜
	RankingType_Arena,//1
	RankingType_Skirmish,//2
	RankingType_ChapterLevel,//3
	RankingType_ChallengeLevel,//4
	RankingType_Level,//5
	RankingType_Wing,//6
	RankingType_Warrior,//7 战士榜
	RankingType_Mage,//8 法师榜
	RankingType_Taoistpriest, //道士榜
	RankingType_Train,
	RankingType_TianTi,
	RankingType_Zhuling,//12.铸造总等级榜单
	RankingType_ZhanLing,
	RankingType_LoongSoul,//14.龙魂总等级榜单
	RankingType_Knighthood,
	RankingType_WingLv,//16.翅膀总等级榜
	RankingType_TuJianPower,//17.图鉴总战力
	RankingType_ZhuanSheng,//18.转生榜
	RankingType_EquipBasePower,//19.装备总评分
	RankingType_Stone,//20.宝石(精炼)总等级榜单
	RankingType_ConsumeYB,
	RankingType_Prestige, //威望排行榜
	RankingType_TeamLike,//侠义值排行榜
	RankingType_Count,
	RankingType_Recharge,//充值排行榜
	//RankingType_subactivitytype4_16,
};


enum AttrSystemId
{
	asStart = 0,
	asEnhance = asStart,		//强化
	asZhuling,			//注灵
	asStone,			//宝石
	asLongSoul,		//龙魂
	asShield,			//护盾
	//asxueyu,          //血玉
	asHeartMethod,  //心法
	asHunGu,  //魂骨
	asCount,
};

//actor
enum AttributeId
{
	attrStart = 0,
	attrTuJian = attrStart,//图鉴系统属性
	attrFlameStamp,  //烈焰印记
	attrZhanLing,  //战灵
	attrShenShou,  //神兽系统
	attrMax,
};

enum RoleMoveLineStatus
{
	MOVELINE_NORMAL,//初始状态
	MOVELINE_SEND_REQUEST,//已通知客户端计算移动线路
	MOVELINE_DATA_PREPARE,//收到客户端计算的移动线路
};

/***********下面是旧定义*********/
/*
enum ActorJobDef
{
	enVocNone = 0,    // 无职业
	enVocTL = 1 ,   // 战士
	enVocSS = 2,	// 猎人
	enVocYY = 3, // 法师
	enMaxVocCount,  //最大的职业数量
	ActorJobCount = enMaxVocCount - 1,
};*/

// 用于区分敌我，不是游戏功能里的阵营
enum CampType
{
	CampType_None		= 0,	// 没有阵营
	CampType_Player,
	CampType_Count,
};

enum CampBattleType
{
	CampType_CampBattle_Ice = 1,		//阵营战冰阵营
	CampType_CampBattle_Fire = 2,		//阵营战火阵营
};

enum WorldBossCampType
{
	WorldBossCampType_Normal = 1,
	WorldBossCampType_Belong,
	WorldBossCampType_Attack,
};

enum ExRingType
{
	ExRingType_MabiRing = 0,
	ExRingType_HuShenRing = 1,

	ExRingType_MAX
};

//玩家新特戒类型
enum ActorExRingType
{
//	ActorExRingType_MabiRing = 0,
//	ActorExRingType_HuShenRing = 1,
	ActorExRingType_HuoYanRing = 7,
	ActorExRingType_MAX = 8,
};

#define MALEACTOR  0 //男性角色
#define FEMALEACTOR 1 //女性角色

#define MAX_FUBEN 512	// 最大副本个数

#define MAX_REINCARNATION 4 //最大转生数

#define INT_MAX_NUM 2147483647 //INT最大值

#define MAX_WING_SKILL_STORE 100



//实体类型定义 todo 以后删掉
enum tagEntityType
{
	//这些是动物
	enActor = 0,     //玩家
	enMonster = 1,  //怪物，具有战斗功能
	enNpc = 2,	//NPC,继承于Monster，有会话功能,战斗功能
	enMovingNPC = 3, //寻路的怪，继承于NPC,比如卫兵，具有会话,战斗功能,寻路功能
	enPet = 4,	//宠物
	//这些是生物中的非动物
	enTotom = 5, //图腾
	enDropBag = 6,  // 掉落包裹
	enDefender = 7, //防御设施,采集对象
	enPlant = 8, //植物,采集对象

	//非生物，包括传送门，建筑，技能效果等
	enTransfer = 9 ,  //传送门
	enBuilding = 10, //建筑
	enEffects = 11,  //特效，后面的伤害性的一些特效

	enGatherMonster = 12, // 采集怪
	//enDisplayMonster = 13, // 显示怪？

	enClonePet = 15, // 复制的宠物
	enScriptNpc = 16,	// 脚本NPC
};

//金钱的类型的定义 todo delete
enum eMoneyType
{
	mtBindCoin = 0,       //不可交易的金钱，比如系统奖励的一些金钱
	mtCoin = 1,			 //可交易的金钱，如任务等发送的金钱
	mtBindYuanbao = 2,    //不可交易的元宝，一般是系统奖励的
	mtYuanbao = 3,		 //可交易的元宝，玩家充值兑换的

	mtMoneyTypeCount,
	mtMoneyTypeStart = mtBindCoin,
};

enum eFubenType
{
	ftStatic = 0,			//静态场景
	ftChapterBoss = 1,		//章节BOSS
	ftMaterial = 2,			//材料副本
	ftRetain1 = 3,			//保留副本类型1
	ftRetain2 = 4,			//保留副本类型2
	ftRetain3 = 5,			//保留副本类型3
	ftPersonalBoss = 6,		//个人BOSS
	ftPublicBoss = 7,		//全民BOSS
};

enum eSoulShieldType
{
	ssLoongSoul = 1,		//龙魂
	//ssShield = 2,			//护盾
	//ssXueyu = 3,            //血玉
};

//enum tagMonsterKind
//{
//    mk_Normal = 1,			// 普通怪
//    mk_Boss,				// 精英怪
//    mk_GatherMonster,		// 采集怪
//};


//聊天频道的ID定义, 这个跟网关有关，不要修改
enum tagChannelID
{
	ciChannelSecret = 0, // 私聊,密语
	ciChannelNear = 1,  // (取消）附近频道，同屏
	ciChannelWorld = 2, // 喇叭频道
	ciChannelGuild = 3, // 工会，帮派
	ciChannelTeam = 4, // 队伍频道,5人
	ciChannelBigTeam = 5, // 团队,20人
	ciChannelMap = 6,  // 地图，本地图可见
	ciChannelAll = 7, // 全服聊天(世界)
	ciChannelCamp = 8, // 阵营频道
	ciChannelSystem = 9,		// 系统频道
	ciChannelKuafu = 10,	//跨服传音
	ciChannelSos = 11,	//求救频道（暂时没用到）
	ciChannelCosign = 12,	//交易频道
	ciChannelLianfu = 13,	//连服频道
	ciChannelMax = 14,		// 最大频道号
};

//系统提示的类型
enum tagTipmsgType
{
	ttInvalidTmType = -1, // 无效的Tipmsg类型
	ttTipmsgWindow = 1, //右下角提示板
	ttScreenCenter = 2, //屏幕中央(2号公告栏)
	ttDialog = 4,     //弹出框
	ttHearsay = 8, // 屏幕中央，向上飘的文字提示
	ttMessage = 16,	//向上飘的文字提升，
	ttWarmTip  = 32,  //温馨提示
	ttGmTip = 64,	// Gm提示信息
	ttChatWindow = 128, //左侧聊天栏里，用于一些系统公告在聊天栏显示
	ttScreenMarquee = 256, //屏幕中央的走马灯(1号公告栏)
	ttScreenCenterDown = 512,  //屏幕中央下方，像歌词那样的效果
	//ttMaxTmType,		// 最大Tipmsg类型
};


//打开角色属性窗口ID定义
enum tagOpenDialogID
{
	diItem = 0,	//物品窗口
	diActor = 1,	//角色属性窗口
	diQuest = 2,	//任务
	diSkill = 3,	//技能
	diStrong = 4,	//强化
	diGuild = 5,	//帮派
	diSell = 6,		//寄卖
	diSystem = 7,	//系统
	diStore = 8,	//商城
	diNormalFuben = 9,//普通副本入口窗口
	diFubenList = 10,//列出所有的副本队伍的窗口
	diBuyAnItem = 11,//显示某个物品的购买窗口
	diFuncDia = 12,		//显示自定义功能窗口，附带的参数为字符串，包含按钮连接
	diMemoDia = 13,		//一个文本内容的对话框，"标题,内容"
	diRenown = 14,	//声望商店
	diStartPlay = 15,//开始游戏，通知接受第一个主线任务
	diRefreshTask = 16, // 任务刷星窗口
	diQuickTelport = 17, // 速传提示框
	diDepot = 18,		// 玩家仓库
	diProtection = 19,	// 护送任务
	diProtectionTips = 20,	// 护送任务提示
	diTianYuanInfo = 21, // 天元之战规则介绍界面
	diFlower = 22,	// 赠送鲜花窗口
	diLiudao = 23,	//六道神秘商人窗口
	diPayGuid = 24,	// 消费引导
	diAwardToDepot = 25, // 把任务奖励放到仓库提示窗口
	diLotterySY = 26,	// 抽奖系统
	diPet = 27,			// 宠物主界面
	diMountTip = 28,	// 坐骑提示窗口
	diGJGuid = 29,		// 挂机引导
	diVipCard = 30,		// 使用VIP体验卡
	diWorldWar = 31, //打开世界争霸
	diDigongchuansong = 32,//打开地宫传送
	diwyyjLead = 33, //万妖遗迹任务指引
	diMarryMarch = 34,	// 结婚系统，巡游界面
	diNpcDialog = 35,   // npc对话框
	diZhuanShengTips = 36, //转生tip
	diEqsign = 37, //铭刻界面
	diQualitySign = 38, //铭刻提品界面
	diExclusiveSign = 39, //装备专属界面
	diZhuanZhi = 40,	//转职界面
	diMount = 41,		//坐骑喂养
	diEscort = 44, //美女護送
	diRoutineQuest = 45, //日常任务
	diZhengBa = 46, //争霸赛
	diJingjie = 47, //境界副本
	diQuestions = 49, //答题活动界面
	diBuyVip = 50,//打开仙尊窗口
	diPetJingJie = 51, //打开宠物境界
	diInvestgate = 52,	//投资
	diBuyPetSkill = 53,	//购买宠物群攻技能
	diZhuMoDian = 54, //诛魔殿玩法
	diFirstCharge = 55, //首充
	diRaiders = 57,	//逍遥攻略	
	diTreasureofGold = 58, //聚宝成金
	diFengQiangliBao = 59,//疯抢礼包
	diCangbaoge = 60,	//藏宝阁
	diRabbit = 61,	//大活动界面，参数表示哪个小活动
	diSmashingEggs = 62, //疯狂砸蛋
	diAnHeiShendian = 63, //暗黑神殿
	diAnHeiShendianMain = 64, //暗黑神殿
	diMarry = 67, //打开求婚界面
	diDivorce = 68, //打开离婚界面
};

//玩家的公会职位
enum tagGuildPos
{
	smGuildCommon = 0,			//普通成员
	//smGuildJy = 1,				//精英(无)
	//smGuildTz = 2,				//堂主(无)
	//smGuildHufa = 3,			//护法(无)
	smGuildZl = 1,				//长老
	smGuildAssistLeader = 2,	//副帮主
	smGuildLeader = 3,			//帮主
};

//公会聊天消息类型
enum tagGuildChatLogType
{
	enGuildChatSystem = 0,
	enGuildChatChat = 1,
	enGuildChatShow = 2,
};



// 怪物发言广播类型
enum MonsterSayBCType
{
	mssInvalid,		// 无效广播类型
	mssNear,		// 附近广播
	mssScene,		// 场景广播
	mssFuben,		// 副本
	mssWorld,		// 世界
	mssCamp,		// 阵营广播
	mssNearScene,  //头顶加场景
	mssScreencenter, //屏幕正中间

	mssSelf = 10,       //发给自己,策划的需求..
	mssMax,
};

enum MonsterSayPos
{
	mspLt = 0,		//聊天频道
	mspHead,			//怪物头顶
	mspCenter,		//屏幕正中间
};

// VIP类型
enum enVIPType
{
	enVIPRedDiamond,			// VIP 红钻
	enVIPBlueDiamond,			// VIP 蓝钻
	enVIPYellowDiamond,			// VIP 黄钻
	enVIPTypeMax
};

// 一些杂项数据
enum enMiscDataType
{
	enMiscData_AddCampDailyTaskCount,	// 增加阵营日常任务次数
	enMiscData_AddDailyTaskCount,		// 增加日常任务次数(非阵营)
	enMiscData_VIPXiuWeiAdd,			// VIP修改增加值
	enMiscDataMax
};

// 宝物状态类型定义
enum enGemStatus
{
	enGemStatusIdle,			// 宝物处于休息状态
	enGemStatusEquip,			// 宝物被装备
	enGemStatusRide,			// 宝物被骑乘
	enGemMax
};

// 宝物灵性类型定义
enum enGemSpriteCharType
{
	enGemSpriteCharAttack,		// 攻击灵性  + 攻击
	enGemSpriteCharDefence,		// 防御灵性	 + 防御
	enGemSpriteCharAgility,		// 敏捷灵性	 + 闪避、暴击
	enGemSpriteCharHP,			// 霸体灵性	 + 生命、内力
	enGemSpriteCharMax
};


//数据类型定义，用于namespace DataPack
enum tagDataType
{
	dtByte = 0,
	dtChar = 1,
	dtWord = 2,
	dtShort = 3,
	dtInt = 4,
	dtUint = 5,
	dtInt64 = 6,
	dtUint64 = 7,
	dtString = 8,
	dtPointer = 9,	// 指针类型
	dtItem = 10,	// 物品的指针
	dtDouble = 11,
};

/*
*实体的状态
*状态是持续性的，比如打坐，死亡，吟唱，摆摊
*也就是有一个过程的
*/
enum tagEntityState
{
	esStateStand = 0 , //静止状态
	esStateMove = 1,  //行走状态或者跳跃状态
	esStateRide = 2, //骑马状态
	esStatePratice = 3, //打坐状态
	esGather = 4,  //采集状态
	esStateUnderSunshade = 5,//太阳伞下
	esStateBattle = 6, //战斗状态
	esStateDeath = 7, //死亡状态
	esStateMoveForbid = 8, //禁止移动状态,buff设置的
	esStateDizzy = 9,   //晕眩状态
	esStateAutoBattle = 10, //挂机状态
	esStateReturnHome = 11, //回归状态(用于怪物)
	esDisableSkillCD = 12, //禁用技能CD标志（开发和测试用）
	esChallenge = 13,		//擂台状态
	esNewCreate = 14,	// 是否第一次出现（用于某些出现的特效，比如从天而降）
	esStateDoubleSunBach = 15,	//是否双修（浪漫沙滩）
	esStateAttackedForbid = 16,	// 禁止被攻击
	esShowBossName = 17,		// 头顶显示boss图片
	esNoTitle = 18,				// 不显示称号
	esJump = 19,				// 跳跃状态
	esMasterEquip = 20,			// 装备上天元城主装备
	esProtection = 21,			// 护送任务状态
	esPkState = 22,				// 和玩家pk状态
	esPetState = 23,			// 宠物状态，将具有宠物的行为特性
	esDenyRefreshModel = 24,	// 禁止刷新外观
	esStateSunBath = 25,	//日光浴
	esStateHideForbid = 26, //禁止隐身
	esStateInSandBeach = 27, //在浪漫沙滩场景内
	esStateImprison = 28, //禁锢状态
	esStateHide = 29,    //隐身状态
	esStateVest = 30,	//篝火归属者
	esStateJiuShiZhu = 31, //救世主状态
	esReLive = 32, //复活

	esMaxStateCount, //状态的数量
};

enum EntityBitState
{
	ebsSuperman,		// 是否superman
	ebsNoAnger,			// 是否不加怒气值
	ebsAttackLog,		// 是否记录攻击列表
	ebsHpEvent,			// 是否触发血量改变脚本事件
	ebsTotem,			// 是否图腾怪
	ebsGm,				// 是否gm
	ebsVestEvent,   //是否触发归属变更事件

	ebsMaxStateCount,	// 数量
};

enum spiritFashionType
{
	sftMin = 0,
	sftCount = sftMin,//收集次数
	sftStrong = 1,//强化次数
	sftBless = 2,// 祝福值
	sftOutTime = 3,//到期时间

	sftMax,
};

//玩家的状态
enum tagActorState
{
	esFishingNormal = 0, //普通钓鱼
	esUsingOtherHp = 1, //额外血槽状态
	esHaveSunshade = 2,//拥有伞
	esAvenger = 3, //复仇者
	esGearsOfWar = 4,//战争机器
	esChangeModel = 5, //变身状态

	esMaxActorStateCount, //状态的数量
};

//副本统计用
enum caletype
{
	caleExp = 0,   //经验值增加
	caleCoin = 1, //银两增加
	caleBindCoin = 2, //仙币
	calelingli = 3, //灵力值,只适合在外部增加
	caleFubenTime = 4,//副本时间
	caleMonTime = 5,//刷怪剩余时间
	caleOther1 = 6, //其它 如采集蟠桃上限值
	caleOther2 = 7, //其它
	caleOther3 = 8, //其它
	caleRemainMonster = 9, //剩余怪物数
	caleGameTime = 10,//副本游戏时间
	caleLiLiang = 11, // 历练
	caleSceneExp = 12, // 本场景获得的经验
	caleHonor = 13, //荣誉值
	caleOther4 = 14, //其它
	caleOther5 = 15, //其它
	caleOther6 = 16, //其它
	caleOther7 = 17, //其它
	caleOther8 = 18, //其它
	caleOther9 = 19, //其它
	caleOther10 = 20, //其它
	caleMax,
};

// 活动目标类型

enum ActivityTarget
{
	enRoutineQuest = 0,		// 日常任务
	enGuildTask,		// 帮派任务
	enGuildDice,		// 帮派摇骰子
	enGuildAnimal,			// 喂养帮派神兽
	enGiveFlower,			// 赠送鲜花
	enExploreSecret,		// 探索秘藏
	enWushenTai,			// 挑战武神台
	enCorpse,		// 进行鞭尸
	enEscort,		// 护送美女
	enFish,			// 进行钓鱼

	enWanyaoyiji,			// 万妖遗迹
	enBagua,		// 八卦副本
	enHolybeast,			// 四圣兽副本
	enLoveFuben,			// 情侣副本
	enNirana,			// 经验副本
	enMoneyFuben,			// 金币副本
	enPetsave,		// 宠物副本
	enQqshFuben,			// 琴棋书画副本
	//enATZaiXian, //在线2小时

	enATMax,			// 最大值
};

// 帮派数据保存位置
enum tagGuildValue
{
	gvLastCallSL = 0,	// 最后一次召唤兽灵的时间
	gvGuildMax,
};

// 每个系统的id定义，主要用于判断系统是否开放
// 坐骑和法宝的定义不能改，数据库的排行榜有用到
enum tagSystemId
{
	siMount = 0,	// 坐骑
	siGem = 1,		// 法宝(精灵)
	siGuildSys = 2,	// 帮派
	siEquipStrong = 3, // 装备强化
	siSkillSystem = 4, //技能及系统
	siWorship = 5,		// 拜神
	siSkill = 6,		// 必杀技
	siPractice = 7,    //打坐
	siRoot = 8,	// 灵根
	siDujie = 9,	// 渡劫
	siOneKeyFriend = 10,	// 一键征友
	siExchange = 11,		// 兑换
	siWing = 12,  //翅膀
	siPet = 13,		// 宠物系统
	siFightSys = 14,	// 竞技场
	siZhuMoDian = 15,	// 诛魔殿
	siMarry = 16,	// 结婚系统
	siMijiSys = 17,		//秘籍系统
	siArtifact = 18,	// 神器
	siFashionDeal = 19,  //时装处理
	siWingShenTong = 20, //翅膀神通
	siWingSkill = 21, //翅膀技能
	siMountSkill = 22, //坐骑技能
	siMountStage = 23, //坐骑进阶 (无用了直接开启)
	siSpiritSoul = 24, //精灵元素
	siFriendSys = 25, //好友系统
	siXunBao = 26,	  //寻宝系统
	siDayQuest = 27,  //日常任务系统
	siLoopTask = 28,  //跑环任务系统
	siDailySign = 29, //签到
	siGemStone = 30, // 宝石开启
	siShenZhuang = 31, //神装
	siSysMAX,
};


// 宠物属性id定义
enum
{
	PI_ID		   = 0,	// id
	PI_MONSERID	   = 1,	// 怪物id，宠物实际上也是个怪物：）
	PI_HP		   = 2,	// 生命值
	PI_LEVEL	   = 3,	// 等级
	PI_FIGHT_TYPE  = 4,	// 战斗类型
	PI_HP_STORE	   = 5,	// 血包
	PI_EXP		   = 6,	// 经验8字节即分64位为PI_EXP，PI_EXP1
	PI_EXP1		   = 7,
	PI_AMBIT	   = 8,// 境界 高16位阶级, 低16位重数
	PI_QUALITY_LV  = 9,// 资质等级
	PI_QUALITY_EXP = 10,// 资质经验
	PI_TYPE		   = 11,// 宠物类型, 低2字节保存原始的宠物类型值，高2位保存化形后的宠物类型值
	PI_ATTACK_TYPE = 12,// 攻击类型
	PI_TITLE_AMBIT = 13,// 境界称号
	PI_TITLE_QUALITY  = 14,// 资质称号
	PI_NATURE      = 15,// 宠物性格 高16位的高8位，低8位存储刚刷新出的性格A和B 低16位的高8位，低8位存储当前性格A和B

	// 以下是宠物的战斗属性, 注意以下次序不要改动
	PI_ATTACK		      = 16,// 攻击
	PI_MAGIC_DEFEN	      = 17,//法防
	PI_PHY_DEFEN		  = 18,// 物防
	PI_CRITICALSTRIKES    = 19,// 暴击
	PI_HITRATE			  = 20,// 命中
	PI_DODGERATE		  = 21,// 闪避
	PI_DEFCRITICALSTRIKES = 22,// 抗暴击
	PI_HP_PRO			  = 23,// 生命

	// 境界属性
	PI_AMBIT_ATTACK			 = 24,	// 攻击
	PI_AMBIT_MAG_DEFEN		 = 25,	// 法防
	PI_AMBIT_PHY_DEFEN		 = 26,	// 物防
	PI_AMBIT_CRITICALSTRIKES = 27,	// 暴击
	PI_AMBIT_HITRATE		 = 28,	// 命中
	PI_AMBIT_DODGERATE		 = 29,	// 闪避
	PI_AMBIT_DEFCRITICALSTRIKES = 30,// 抗暴击
	PI_AMBIT_HP				 = 31,	// 生命

	// 基础资质，这个是在宠物最开始就固定
	PI_QUA_BASE_ATTACK			= 32,	// 攻击
	PI_QUA_BASE_MAG_DEFEN		= 33,	// 法防
	PI_QUA_BASE_PHY_DEFEN		= 34,	// 物防
	PI_QUA_BASE_CRITICALSTRIKES = 35,	// 暴击
	PI_QUA_BASE_HITRATE			= 36,	// 命中
	PI_QUA_BASE_DODGERATE		= 37,	// 闪避
	PI_QUA_BASE_DEFCRITICALSTRIKES = 38,// 抗暴击
	PI_QUA_BASE_HP				= 39,	// 生命

	PI_FIGHT_VALUE  = 40,	// 战斗力
	PI_SKILL_SLOT   = 41,	// 技能槽
	PI_TOTAL_MAX_HP = 42,	// 宠物实际的最大血上限

	PI_PROP_MAX		= 43,

	//后面这里不用通知客户端
	PI_REAL_QUA_ATTACK = PI_PROP_MAX, //宠物攻击总资质
	PI_REAL_QUA_MAG_DEFEN		= 44,	// 法防
	PI_REAL_QUA_PHY_DEFEN		= 45,	// 物防
	PI_REAL_QUA_CRITICALSTRIKES = 46,	// 暴击
	PI_REAL_QUA_HITRATE			= 47,	// 命中
	PI_REAL_QUA_DODGERATE		= 48,	// 闪避
	PI_REAL_QUA_DEFCRITICALSTRIKES = 49,// 抗暴击
	PI_REAL_QUA_HP				= 50,	// 生命


	PI_MAX,
};

//宠物技能位置
enum PET_SKILL_DB_TYPE
{
	PET_SKILL_BAR	 = 1,// 技能栏技能
	PET_SKILL_STORE  = 2,// 仓库技能
	PET_SKILL_SLOT = 3,// 刷新槽
	PET_SKILL_BOOK = 4, // 技能书
};

// 日志保存标志
enum tagLogFlag
{
	lfDB = lfiDB,	// 保存数据库
	lfBI = lfiBI,				// 保存到BI
	lfText = lfiText,			// 保存到文本
	lfIsPay = lfiIsPay,			// 是否充值数据
	lfNormal = lfDB + lfBI + lfIsPay, // 默认保存到数据库和BI
};

enum itemPos
{
	ipStart = 0,
	ipBag = ipStart,
	ipDepot,      //玩家仓库
	ipLottery,    //抽奖仓库
	ipEntrust,	  //委托仓库
	ipTreasure,	  //珍宝囊
	ipBabel,	  //通天塔仓库

	ipMax,
};

enum AttrCalcId
{
	acStart = 0,
	acRoot = acStart,
	acTitle,
	acAchieveMedal,
	acSpirit,
	acSpiritLevel,
	acSpiritSoul,
	acSpiritFashion,//精灵时装
	acWingLevel,
	acWingStage,
	acWingShenTong,
	acWingModel,
	acMountExtra,
	acMountStage,
	acMountAppearance,
	acEqExclusive,
	acEqsign,
	acGuildSkill,
	acGuildAnimal,
	acVipBuff,
	acJingjieCuiti,
	acSpiritFashionStrong,//精灵时装强化
	acEquipMelt, //装备熔炼
	acXiaoyaoEquip,	//逍遥套装
	acRingStage, //婚戒进阶
	acRingCl,		//婚戒淬炼
	acZsheng,		//转生属性
	acShenZhuangHead,	//神装头箍
	acShenZhuangHand,	//神装手环
	acShenZhuangShoulder,	//神装肩甲
	acShenZhuangKnee,	//神装膝甲
	acArtifact,		//神器属性
	acEqRefine, //装备精炼属性
	acMax,
};

enum DbSystemId
{
	dbDefault = siDefault,	//特殊命令
	dbEntity = siActor,
	dbGuild = siGuild,
	dbConsignment = siConsignment,
	dbMsg = siMsg,
	dbRank = siRank,
	dbGlobal = siGlobal,
	dbFight = siFight,
	dbMail = siMail,
	dbCommon = siCommon,
	dbConfig = siConfig,
	dbWarTeam = siWarTeam,
	dbTxApi = siTxApi,
	dbCommonDB = siCommonDB,
	dbAuction = siAuction,
};

// 使用元宝扣费后的回调类型
//enum tagYBPayType
//{
//    yptStore = 1,		// 商城购买
//    yptAddFbCnt = 2,	// 增加副本的次数
//    yptLargeBag = 3,	// 扩展背包
//    //ypt
//};

// 进入副本方式
enum tagEnterFbWay
{
	efwNone = 0,		// 其他方式
	efwNormal = 1,		// 正常进入
	efwRelogin = 2,		// 重新上线
};

// 退出副本方式
enum tagExitFbWay
{
	xfwNone = 0,		// 其他方式
	xfwNormal = 1,		// 正常退出
	xfwLogout = 2,		// 下线
	xfwReturnCity = 3,	// 回城
	xfwTeleport = 4,	// 传送门
};

enum tagActivityEvent
{
	eaeUpgradeGuild = 1, //仙宗升级
	eaeUpgradeEquip = 2, //装备升级
	eaeUpgradeCross = 3, //渡劫
};

enum tagPetSkillEff
{
	pseDizzy = 1, //.XX击晕术
	pseThread = 2, //.XX恐吓
	pseLj = 3,	//.XX连击
	pseXx = 4,	//.XX吸血
	pseTs = 5,	//.提神
	pseGw = 6,	//.鼓舞
	pseTl = 7,	//.提灵
	pseFss = 8, // 分身术

	// 100以上为人物的技能
	pseNgs = 100,	// 女娲石
	pseKlj = 101,	// 昆仑镜
	pseDhz = 102,	// 东皇钟
	pseFty = 103,	// 翻天印

	pseMiji = 200,	// 秘籍
};

enum fightValueType
{
	eEquipBase = 1,		//装备基础属性战斗力
	eEquipStone = 2,	//装备宝石属性战斗
	eEquipStrong = 3,	//装备强化属性战斗力
	eEquipsTage = 4, //装备升阶
	eEquipQuality = 5,//装备提品
	eEquipBaptize = 6, //装备洗炼
	eMountHunger = 7, //坐骑喂养
	eMountSkill = 8,//坐骑技能
	eMountStage = 9, // 坐骑进阶
	eMountAppearance = 10, //坐骑幻化
	eShenZhuangHead = 11,	//神装头箍战力
	eShenZhuangHand = 12,	//神装手环战力
	eShenZhuangShoulder = 13, //神装肩甲战力
	eShenZhuangKnee = 14, //神装膝甲战力
};

/** 定义buff的分组归类 **/
enum BuffGroup
{
	bgSystemBuff = 0,		//系统默认的BUFF组
	bgSkillBuff = 1,		//技能系统默认的BUFF组
	bgDisplayBuff = 2, //仅展示使用，下线后删除
	bgSceneBuff = 3, //场景BUFF, 在切换场景后将会删除该组BUFF
	bgFubenBuff = 4, // 副本BUFF，在退出副本后将删除该组BUFF
	bgManualBuff = 5, //BUFF的删除需要自己写逻辑控制的扔这里
	bgGuildAnimal = 6,//帮派神兽buff(不需要了)
	bgGearsOfWar = 7,//战争机器BUFF组
	bgUserBuffMin = 32,		//可以由开发者自定义的BUFF组的起始值
	bgSkillBuffMin = bgUserBuffMin, //技能的最小的group
	bgHorseSkillBuff = 33,		  //赛马技能buff
	bgMountSkillBuff = 34,		  //坐骑被动技能buff
	bgSpiritSkillBuff = 35,		  //精灵被动技能buff
	bgAgainstSkillBuff = 36,	  //对抗被动技能buff
	bgPetSkillBuff = 37,		  //宠物被动技能buff
	bgHorseSkillBuff2 = 38,		  //赛马技能技能buff第2组
	bgHorseSkillBuff3 = 39,		  //赛马技能技能buff第3组
	bgSkillBuffMax = 80,          //技能的最大的group

	bgItemBuffMin,       //物品的最小的组
	bgUserBuffMax = 127,	//可以由开发者自定义的BUFF组的结束值
	bgItemBuffMax = bgUserBuffMax,      //物品组的最大值

	/*如果添加新的buff组请在AnyBuffGroup枚举值前增加*/
	AnyBuffGroup = -1,		//用于匹配任何组中的buff
	MaxBuffGroup = 255,		//buff分组最大值
};

//怪物说话
enum MonsterSayType
{
	mstInvalid = 0,
	mstIdle,				//空闲
	mstFoundTarget,	//发现目标
	mstAttack,			//攻击
	mstAttacked,		//被攻击
	mstDead,				//死亡
	mstHpLow,			//血量低于百分之几
	mstCreate,			//创建的时候
	mstDisappear,		//消失的时候
	mstMax,
};

enum TeamType
{
	CommonTeam = 0,
	FbTeam = 1,
	LianfuTeam = 2,
	MaxTeamType,
};
/** 排行榜存储的属性数据 类型**/
enum rankDataType
{
	rankAllAttack = 0, //所有攻击
	rankOutDefence, //物理防御
	rankInDefence, //法术防御
	rankMaxHp, //最大生命值
	rankCriticalStrikes, //暴击
	rankDefCriticalStrikes, //抗暴击
	rankHitrate, //命中
	rankDodgerate, //闪避
	rankIntAttack,	//法术攻击
	rankOutAttack,	//物理攻击

	rankMaxDataNum, //最大数量
};
/** 逍遥攻略战斗力 类型**/
enum rankCalcType
{
	rdEquipStrong = 1,	//装备强化
	rdEquipStone,		//装备镶嵌
	rdEquipQuality,		//装备提品
	rdEquipStage,		//装备升阶
	rdEquipBaptize,		//装备洗炼
	rdEquipSign,			//装备铭刻
	rdMountFeed,		//坐骑喂养
	rdMountSkill,		//坐骑技能
	rdMountStage,		//坐骑进阶
	rdWingLevel,			//翅膀升级
	rdWingStage,		//翅膀升阶
	rdSpiritLevel,			//精灵觉醒等级
	rdSpiritSoul,			//精灵元素
	rdSpiritFashion,		//精灵时装
	rdMountModel,	//坐骑幻化
	rdWingSkill,			//翅膀技能
	rdWingShenTong,	//翅膀神通
	rdWingModel,		//翅膀幻化
	rdSpiritSkill,		//精灵技能
	rdTitle,		//称号
	rdRoot,		//星图
	rdDress,	//装扮
	rdSkill,		//技能
	rdPetSkill,	//伙伴技能
	rdPetNature,		//伙伴性格
	rdPetCross,		//伙伴境界
	rdPetStar,		//伙伴将星录
	rdEquipBase, //装备基础
	rdMountEquip,	//坐骑装备
	rdPetEquip,	//伙伴装备
	rdWingEquip, //翅膀装备
	rdEquipExclusive,	//装备专属
	rdAchieve, //成就
	rdJingjieCuiti, //境界淬体
	rdGuildAnimal,	//帮派神兽
	rdGuildSkill,	//帮派技能
	rdPetFeed, //宠物喂养
	rdShenZhuangHead, //神装
	rdShenZhuangHand, 
	rdShenZhuangShoulder,
	rdShenZhuangKnee,
	rdEqRefine, //装备精炼

	rdMax,
};

enum BattleSrvType
{
	bsCommSrv = 0,	// 普通服
	bsBattleSrv = 1,	// 战斗服
	bsMainBattleSrv = 2,	// 主战斗服
	bsLianFuSrv = 3,	//连服服务器
};

enum VestLockType
{
	vlStart = 0,
	vlActorId = 1, //锁定的是玩家归属
	vlGuildId = 2,//锁定的是帮派归属

	vlMax,
};

enum crossServerMsgMethod
{
	CROSSSERVER_ALL, //ALL
	CROSSSERVER_CROSSBATTLE, //战斗服
	CROSSSERVER_LIANFU,  //连服
};


//enum crossServerLoginType
//{
//	CROSSLOGINTYPE_NOTENTERGAME, //还没有进入游戏世界,进行跨服
//	CROSSLOGINTYPE_ENTERGAME, //已经进入游戏世界，再进行跨服
//};

// 跨服登陆类型
enum crossLoginType {
	CROSSLOGIN_CROSSWAR = 1, // 跨服
	CROSSLOGIN_LIANFU = 2, // 连服
};

enum crossServerDataType
{
	dtActorDeal, // 发送给其它玩家处理
	dtServerDeal, // 发送给其它服处理
	dtToActor,	// 发送给其它玩家
	dtBroadCast, // 广播
};

enum MonsterType {
	MonsterType_Normal = 0,//正常怪
	MonsterType_Boss = 1,//boss怪
	MonsterType_GatherMonster = 2,//采集怪
	MonsterType_Pet = 3,//宠物怪
	MonsterType_AexRing = 4,//特戒怪
};

//tolua_end

STATIC_ASSERT(siSysMAX <= 32);

#endif

