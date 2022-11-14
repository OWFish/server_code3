#pragma once

/*********************************
*
* 本文件主要用于定于角色相关的事件，如升级、学习了某个技能，获得物品等
*
**********************************/


//tolua_begin
enum tagActorEventID
{
	aeNoEvent = 0,		//未定义事件
	aeStartBattle,	//进入战斗状态
	aeStartPkState, //进入和玩家pk状态
	aeLevel,			//角色升级
	aeSkillLevelup,		//技能升级F
	aeAddEquiment,	//穿上装备
	aeDelEquiment,	//脱掉装备

	/* Actor::Init流程*/
	aeInit,			//初始化事件, 处理子模块属性初始化之类 @不能发包,镜像玩家也会执行
	aeBeforeLogin,	//登陆前事件， 处理离线奖励之类，可操作玩家数据但不发送给客户端 不能发包,镜像玩家不执行
	aeUserLogin,   //玩家登陆 [是否是第1次登录] 主要用于发送客户端初始化信息 能发包,镜像玩家不执行
	aeUserFirstLogion, //玩家第一次登录的初始化
	/*******************/
	
	aeUserLogout,   //玩家登出

	aeEnterFuben,	//玩家进入副本[副本id]
	aeLeftTeam,	//玩家退出队伍（包括自己退出或队长踢的情况）,在这个事件中，脚本要把玩家退出副本，回到普通场景中[玩家指针，队伍指针]，注意：执行这个函数的时候，已退出队伍，所以无法通过玩家指针获取队伍指针，所以有个参数传了队伍指针
	//aeOnActorDeath = 19 , //玩家死亡
	aeReliveTimeOut,	//判断复活时间是否超时（用户超过5分钟没有选择回城复活还是原地复活），如果到达，脚本处理，送回主城复活.[玩家指针]
	aeRecharge,		//玩家充值
	aeNewDayArrive,				// 新的一天更新事件，玩家在线期间的24点整点更新事件
	aeUpdateVipInfo,				// 更新Vip信息
	aeKilledByActor,			//被玩家杀死 [自己指针][对方(杀人者)指针]


	aeStarQuest,				//刷星任务事件
	aeOpenSys,					//开启系统
	aeTeleportComfirm,			//传送门确认
	aeDayEnd, 					//今天结束
	aeConsumeYuanbao,			//消费元宝
	aeConsumeGold,				//消费金币
	aeChangePrestige,			//威望值改变
	aeRechargeOffline,			//离线充值
	aeJoinGuild,				//加入一个帮派
	aeLeftGuild,				//离开一个帮派
	aePetBattle,				//宠物出战

	aeCrossWar,				// 跨服战
	aeNewDayHoursArrive,	   // 新的凌晨六点更新事件

	aeStrongLevelChanged,//强化等级变化

	aeNewWeekArrive,//每周一 零点整触发事件
	aeNewDayHoursArriveInCommSrv, //新一天六点更新事件（在普通服触发）

	aeStoreCost,		//商城消耗货币事件
	aeDropItem,		//掉落物品触发()
	aeSmeltEquip,		//熔炼装备
	aeFightPower,		//战斗力变化
	aeSkirmish,		//遭遇战
	aeUpgradeSkillCount,	//技能升级次数
	aeWingLevelUp,		//翅膀升级
	aeWingStarUp,		//翅膀升星
	aeWingTrain,		//翅膀培养事件
	aeUpgradeJingmai,	//经脉升级事件
	aeUpgradeStone,	//宝石升级事件
	aeUpgradeZhuling,	//注灵升级事件
	aeUpgradeTupo,		//突破升级事件
	aeEnterPublicBoss,	//进入全民BOSS
	aeOpenRole,			//开启角色
	aeZhuansheng,			//转生事件
	aeUpgradeLoongSoul,	//龙魂提升事件
	aeUpgradeShield,	//护盾提升事件
	aeFieldBoss,	//野外boss击杀
	aeAddEssence,	//增加精华 
	aeAchievetaskFinish, // 成就任务完成
	aeChapterLevelFinish, // 完成关卡
	aeFinishFuben,	// 通关副本
	aeCreateRole, //创建子角色
	aeBlessLevelChanged, // 开光
	aeLearnMiJi, // 学习秘籍
	aeGuildDonate, //公会捐献
	aeChangeName, //改名
	aeTianTiChallenge, //天梯挑战

	aeMagicLevel,		//神功等级->历练(爵位)等级 c
	aeWarSpiritlevel,		//战灵等级
	aeWarSpiritstage,   //战灵阶级
	aeOrange,			//橙装数量
	aeLegend,			//传奇数量
	aeCasting,			//装备铸魂
	aeArtifact,			//装备神器
	aeArtifactstage,	//神器阶级
	aeParalysis,		//麻痹戒子升级
	aeProtective,		//护身戒子升级
	aePersonalBoss,		//击杀个人BOSS
	aeFullBoss,			//击杀全名BOSS
	aeTransferBoss,		//击杀转职BOSS
	aeHegemony,			//击杀转职BOSS
	aeloongLevelCount,	//龙魂提升次数
	aeShieldLevelCount,	//护盾提升次数
	aeXueyuLevelCount,	//血玉提升次数
	aeGuildSkill,		//工会技能修炼
	aeAtkWorldBoss,		//进入世界boss
	aeMorship,			//膜拜
	aeGetTreasureBoxType,	//获取指定类型宝箱
	aeChallengeFb,		//闯天关
	aeTuJian,			//图鉴
	aeFuWenLevel,		//战纹等级
	aeTreasureBoxReward,//获取宝箱奖励
	aeReqChapterReward,//领取章节奖励
	aeReqChapterWorldReward,//领取章节的世界奖励
	aeKillChapterMonster,//击杀关卡怪物
	aeXunBao,			//寻宝:寻宝次数
	aeGetWroldBossBelong,//获取了世界boss归属
	aeKnighthoodLv,	//勋章升级:当前等级
	aeNeiGongUp,	//内功升级升阶
	aeActTogetherhit,//激活(升级)合击技能
	aeUseTogetherhit,//使用合击技能
	aeActImba,		//激活神器
	aeActAExring,	//激活玩家特戒
	aeUpAExring,	//升级特戒
	aeOpenMonthCard,//开通月卡
	aeShareGame,//分享一次
	aeTianTiLevel,//王者争霸达到指定段位
	aeSkirmishRank,//达到遭遇战排行榜前几名
	aeDayLiLian,   //当天达到多少历练
	aeDayFuBenSweep,   //副本扫荡次数
	aeFinishLimitTask,   //完成限时任务
	aeGetItem,			//获取一个道具
	aeActImbaItem,	//激活神器碎片
	aeCaiKuang,		//挖矿
	aeDayFuBenWin,//每日副本胜利(只有个人boss)
	aeHolyBoss, //参与了一次神域boss(boss玩法)
	aeNewWorldBoss,//参与了世界boss
	aeCampBattleFb,//参与了阵营战
	aeGetWBossActScore,//获得了一次boss玩法积分
	aeMiJingBoss,//参与了一次秘境boss(boss玩法)
	aeLoseFuben,//副本失败
	aeJoinActivityId, //参与指定活动id
	aeRichManCircle, //大富翁圈数
	aeExpFubenAwardType, //经验副本奖励类型
	aeWorldBoss,	//参与一次boss玩法,boss配置ID,副本ID,参与类型
	aeZhuangBan,	//激活装扮
	aeChallengePVM, //挑战竞技场
	aeAchievemwntAward, //领取成就任务奖励
	aeSoulShieldAct,	//激活龙魂（龙心）
	aeNeiGongActive,	//内功激活
};	

/*
	这个文件保护副本相关的导出函数
*/
//副本类型的定义
enum tagFubenMode
{

    fmCommon = 0,	//普通场景
    fmSingle = 1,	//单人副本
    fmTeam = 2,		//普通队伍副本
    fmTeamHero = 3,	//英雄队伍副本
    fmGroup = 4,	//普通团队副本
    fmGroupHero = 5,	//英雄团队副本
    fmJd = 6,			//专门用于精锻的副本
    fmMaxCount,
};

enum tagTeamStatus
{
    tsCommon = 0,
    tsReady = 1,	//在创建队伍，等待进入副本的状态
    tsWar = 2,		//已经进入副本，战斗中
};

//这里定义副本的类型，比如结婚副本、擂台副本等
enum tagFubenType
{
    ftCommon = 0,	//普通副本，无特别意义的副本
    ftChallenge = 1,	//擂台副本
    ftWedding = 2,		//结婚副本
};

enum tagFreePkMode
{
    //和平模式
    fpPeaceful = 0,
    //团队模式
    fpTeam,
    //帮派模式
    fpGuild,
    //阵营模式
    fpZY,
    //杀戮模式
    fpPk,
	//盟友模式
	fpAlly,
    //联盟模式
    fpUnion,
	//区服模式
	fpServer,
	//特殊的和平模式
	fpSpecialPeaceful,

    fpCount,
};

//奖励类型
enum tagAwardType
{
    qatItem = 0,           //物品或者装备
    qatRootExp = 1,	            //灵气
    qatExp = 2,                	//角色经验值
    qatGuildContribution = 3,	//帮派贡献值
    qatZYContribution = 4,		//阵营贡献
    qatBindMoney = 5,           //绑定银两
    qatMoney = 6,	            //银两
    qatBindYuanBao = 7,	            //绑定元宝
    qatTitle = 8,	            //称谓
    qatSkill = 9,	            //技能
    qatShengWang = 10,	        //声望
    qatRenown = 12,              //历练
    qatPet = 13,                 //奖励宠物
    qatStone = 14,				// 帮派灵石
    qatYuanbao = 15,			// 元宝
    qatHonor = 16,				//荣誉值
	qatCrossHonor = 17,			// 跨服荣誉值
    qatCount ,					// 奖励个数

    qatCustomize = 127,		    //自定义奖励
};

//帮派的相关操作
enum tagGuildOP
{
    gUseCallItem = 1,		//使用召集令
    gUpLevel = 2,			//帮派升级
    gLeft = 3,				//离开帮派
};

enum StarEventType
{
    seGiveUp = 1,	// 放弃事件
    seFinish = 2,	// 完成事件
    seTimeout = 3, // 超时
    seAddQuest = 4, // 接受任务
	seCanFinish = 5, // 完成任务目标，可以完成任务
	seShowAccept = 6, // 显示可接任务
};

enum eRrchargeType
{
	eRrchargeType_NULL = 0,
	eRrchargeType_FIRST = 1, //首冲
	eRrchargeType_NORMAL = 2, //正常充值
	eRrchargeType_MONTHCARD = 3,//月卡充值
	eRrchargeType_PRIVIMONEY = 4,//特权充值
	eRrchargeType_LIMITPACKAGE = 5,//限时礼包充值
	eRrchargeType_ACTIVITY = 6,//活动礼包充值
};
//tolua_end

