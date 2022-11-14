#ifndef _LOG_DEF_H_
#define _LOG_DEF_H_

//为了防止名字污染，放在一个GameLog里
namespace GameLog
{
	//日志类型
	enum  taggGameLogType
	{
		//物品id,数量(可以是负数),备注
		clScriptGiveItem = 1,	//nPC脚本中给予物品
		clScriptDeleteItem=2,	//nPC脚本中删除物品
		clTakeOnItem=3,			//穿上装备
		clTakeOffItem=4,		//取下装备
		clUserItem=5,			//用户使用物品
		clUserDestroyItem=6,	//用户销毁物品
		clBuyItem=7,			//用户从NPC商店购买物品
		clSellItem=8,			//用户将物品卖出到NPC商店
		clRepairItem=9,			//用户修理物品
		clBrokenItem=10,             //物品因耐久耗光而损坏
		clTimeupItem=11,             //物品因到达使用时限而消失
		clGMAddItem=12,              //GM添加制造
		clShoppingCenterGiveItem=13, //商城给玩家添加了一个物品
		clRankRewardItem=14,         //排名奖励的物品
		clGuildDonateItem=15,        //向工会捐赠物品
		clWorldTalkItem=16,          //世界广播消费道具
		clMarriageItem=17,           //结婚消耗道具
		clInlayItem=18,              //物品镶嵌消耗物品
		clEquipStrengthItem=19,      //装备强化消耗物品
		clEquipUpgradeItem=20,       //装备升级消耗物品
		clAchieveRewardItem=21,      //成就奖励物品
		clQuestGiveItem=22,          //任务奖励物品
		clBuyStoreItem=23,			  //购买商城物品
		clDealTransferItem=24,		  //交易获得物品
		clGuildClear=25,			  //帮派自动清理物品，指“召集令”
		clGuildGive=26,				  //帮派的福利物品
		clGuildUpgrade=27,		      //帮派升级消耗帮派符
		clGuildFr=28,				  //升级帮派繁荣度消耗兴邦令
		clKillMonsterItem=29,         //杀怪获得物品
		clSkillTrainItem=30,          //技能升级消耗物品 
		clEquipRemoveGemItem= 31,          //装备摘除宝石获得物品
		clEquipRemoveLostItem =32,            //装备摘除消耗物品
		clEquipSynthesizLostItem=33,         //装备合成失去物品
		clEQuipAssignStdItem  =34,            //装备变成另外一个物品
		clEQuipUpStageLostItem  =35,        //装备进阶消耗物品
		clEQuipInjectLostItem  =36,           //装备注入消耗物品
		clEQuipPourLostItem =37,              //装备的灌注消耗物品

		clEquipSplit =38,             //物品拆分
		clItemMerge =39,  //物品叠加
		clDealLostIteam =40, //交易失去物品
		clDealGetItem =41,  //交易获得物品
		clBag2Deport =42,  //物品从背包转移到仓库
		clDeport2Bag =43,  //物品从仓库转移到背包
		clDeportRemoveItem =44, //仓库删除物品
		
		clConsiRemoveItemFromBag = 45,		//玩家寄卖物品，把背包的物品删除
		clConsiAddItemToList = 46,		//寄卖的物品上架
		clConsiCancelItemRemoveFromList = 47,		//玩家取消寄卖，物品下架
		clConsiCancelItemToBag = 48,	//取消的物品转入背包
		clConsiBuyItemRemoveFromList = 49,		//玩家在寄卖系统买入物品,物品下架
		clConsiBuyItemAddToBag = 50,			//玩家在寄卖系统买入物品，物品转入背包
		clConsiTimeoutRemoveFromList = 51,		//玩家寄卖物品到期,物品下架
		clConsiTimeoutAddToBag = 52,			//玩家寄卖物品到期,物品转入背包

		clEquipSynthesize=53,         //装备合成得到物品
		clEQuipBrokedown  =54,        //装备分解得到物品
		clItemFinishAwardItem = 55,	//副本通关奖励物品
		clNewPlayerAwardItem = 56,		//打开礼包获得物品
		clOnlineAwardItem = 57,			//在线奖励物品
		clEQuipQualityLostItem = 58,		//装备提品消耗物品

		clGmPresentItem = 59,			//gm送物品
		clQuestLostItem = 60,			//完成或者放弃任务失去任务物品
		clServerGiveItem = 61,			//服务后台送物品，通常是举办活动送的东西
		clLeftSceneRemoveItem = 62,		//离开场景删除物品
		clRenownBuyItem =63,            //历练购买物品
		clExchangeBadgeRemoveItem=64,	// 徽记兑换删除老的徽记物品
		clExchangeBadgeAddItem=65,		// 徽记兑换，给予新的徽记物品
		clGotVIPFashionDress=66,		// VIP黄钻兑换时装
		clLearnSkillMiji=67,             //技能miji的消耗物品,(取消)
		clGemRefineRemoveItem=68,		// 宝物灵性炼化消耗物品
		clGemUpgradeRemoveItem=69,		// 宝物档次进阶消耗物品
		clGemAddSpriteStrenRemoveItem=70, // 使用宝物灵力道具消耗物品
		clAddVIPTimeRemoveItem=71,		// 延迟VIP时间消耗道具
		clGemRefineQualityRemoveItem=72, // 宝物品质精粹消耗物品
		clGemOpenSlotRemoveItem=73,		// 开启宝箱消耗物品
		clGemComposeRemoveItem=74,		// 合成消耗物品
		clGemComposeAddItem=75,			// 宝物合成成功添加宝物物品
	    clPetLearnSkill =76,           //宠物学习技能,消耗技能书
		clGemSmithRemoveItem=77,		// 宝物精锻消耗物品		
		clDmkjGiveItem = 78,			//在抽奖获得的物品
		clDmkjGiveToStore = 79,			//抽奖抽到物品到仓库中
		clGuildBuyStoreItem = 80,		// 帮派购买物品
		clActivityAwardItem = 81,			// 添加活跃奖励物品
		clVIPLoginAward = 82,			// VIP用户每天登录奖励
		clVIPUpdateAward = 83,			// VIP等级上升奖励
		clDmkjGiveForSY = 84,			// 十一抽奖
		clTxApiGiveAward = 85,			// 腾讯API返回给予奖励
		clUseVipCard = 86,				// 使用VIP体验卡
		clMailGetItem = 87,  			//邮件获得物品
		clEntrustGiveItem = 88,			//副本委托获得物品
		clEntrustGiveToStore = 89,		//副本委托物品移除到背包
		clHonorBuyItem = 90,			//荣誉值购买物品
		clRingUpLostEquip = 91,			// 戒指升级，失去原有的戒指
		clRingUpAddEquip = 92,			// 戒指升级，获得新的戒指
		clMarryGetRing = 93,			// 结婚获得戒指
		clDivLostRing = 94,				// 离婚失去戒指
		clUseRingQm = 95,				// 消耗戒指获取亲密度
		clDmkjStoreToBag = 96,			//抽奖抽到物品到背包
		clEntrustStoreToBag = 97,			// 副本委托物品到背包
		clDenaturationMailEquip = 98,		//变性后不符合装备销毁
		clTeamBuyItem = 99,				//聚仙令兑换

		//货币类型,数量, 来源的备注(比如skill 名字)
		clNpcGiveMoney=100,				//nPC给金钱
		clNpcDelMoney=101,          //nPC删除金钱
		clGmAddMoney=102,              //GM增加了金钱
		clShopBuyMoney=103,            //在商店里购买失去金钱
		clChatPosMoney = 104,             // 聊天发送自己坐标消耗金钱
		clShopSellMoney=105,           //在NPC处卖东西获得金钱
		clShopoingCenterMoney=106,     //在商城支付
		clGuildDonateMoney=107,        //工会捐赠金钱
		clLearnSkillMoney=108,         //学习技能消费金钱
		clChatMoney=109,               //聊天消耗金钱， 全服
		clMountXlMoney=110,           //坐骑洗炼消耗金钱
		clDealTransferYB=111,            //交易获得金钱或扣除元宝
		clRankRewardMoney=112,         //排名奖励金钱
		clAchieveRewardMoney=113,      //成就奖励金钱
	    clQuestGiveMoney=114,          //任务奖励金钱
		clStoreBuyMoney=115,		   //商城中购买物品支付
		clEnlargeBag=116,              //扩大背包
		clDealTransferMoney=117,	   //交易获得金钱或扣除金钱
		clGuildGiveMoney=118,			//帮派给予金钱（工资），这个是每日可领取的
		clCreateGuildLostMoney=119,		//创建帮派时缴纳的钱币
		clKillMonsterMoney=120,         //杀怪获得的金钱

		clConsiFee		= 121,			//寄卖物品收取银两
		clConsiBuyFee   = 122,			//寄卖系统购买物品扣除银两
		clConsiSellFee = 123,			//寄卖物品卖出后获取银两
		clRentFee = 124,				//仓库租用消耗金钱
		clEquipHoleMoney = 125,		//	装备打孔消费金钱	LongStr0:装备名称
		clEquipRemoveMoney = 126,	//	装备摘除消费金钱	LongStr0:装备名称
		clEquipSynthesizMoney =127,		//装备合成消费金钱	LongStr0:装备名称
		clEquipForgeMoney = 128,	//装备精锻消费金钱	LongStr0:装备名称
		clEquipBrokedMoney = 129,	//装备分解消费金钱	LongStr0:装备名称
		clEquipInjectMoney = 130,	//装备注入消费金钱	LongStr0:装备名称
		clEquipPourMoney = 131,		//	装备灌注消费金钱	LongStr0:装备名称
		clEquipInlayMoney = 132,	//装备镶嵌消费金钱	LongStr0:装备名称
		clEquipUpQualityMoney = 133,//	装备提品消费金钱	LongStr0:装备名称
		clEquipStrongMoney = 134,	//装备强化消费金钱
		clItemFinishAwardMoney = 135,//副本通关奖励金钱
		clNewPlayerAwardMoney = 136,	//新手奖励金钱
		clOnlineAwardMoney = 137,		//在线奖励金钱
		clWithdrawYuanBao = 138,			// 提取元宝	
		clServerGiveMoney = 139,		//后台奖励金钱
		clActionAwardMoney=140,			// 活动奖励金钱
		clRenowBuyConsumeMoney =141,    //声望购买物品的时候消耗金钱
		clPlantYB =142,           //种植元宝
		clGainYB=143,                 //收获元宝
		clChangeIconMoney=144,                    //更改头像
		clUpgradeConsumeMoney=145,		// 宝物档次进阶消耗金钱
		clGemRefineQualityConsumeMoney=146, // 宝物提升品质消耗金钱
		clGemComposeConsumeMoney=147,	// 宝物合成消耗金钱
		clGemUpSCConsumeMoney=148, // 宝物灵性炼化消耗金钱
		clGemSmithConsumeMoney=149, // 宝物开光消耗金钱
		clDmkjConsumeMoney = 150,		//盗梦消耗元宝
		clImpeachVoteConsumeMoney = 151, // 弹劾盟主投票消耗金钱
		clMountLevelUpYuanbao = 152,	// 坐骑升级消除cd消耗元宝
		clMountStageUpYuanbao = 153,	// 坐骑进阶消耗元宝
		clMountXlYuanbao = 154,			// 坐骑洗炼消耗元宝
		clMountJjBindCoin = 155,		// 进阶消耗仙币
		clMountLevelBindCoin = 156,		// 升级消耗仙币
		clRootLevelCoin = 157,			// 灵根升级消耗金钱 
		clGuildContribYb = 158,			// 捐献消耗元宝
		clGuildStore = 159,				// 帮派商店购买, 取消，现在是消耗贡献值
		clConsignmentMoney = 160,		// 寄卖失去金钱
		clConsignmentCancelMoney = 161,	// 寄卖的金钱取消寄卖回收
		clConsignmentBugMoney = 162,	// 购买寄卖的金钱
		clConsignmentTimeout = 163,		// 寄卖到期，金钱还给卖家
		clEquipInsertGem = 164,			// 装备镶嵌宝石消耗金钱
		clEuqipRemoveGem = 165,			// 装备移除宝石消耗金钱
		clEuqipStrong = 166,			// 装备强化消耗金钱
		clEquipStrongFail = 167,		// 装备强化失败消耗金钱
		clEquipItemMix = 168,			// 物品合成消耗金钱
		clEquipStrongChange = 169,		// 强化转移消耗金钱
		clEquipActiveRefresh = 170,		// 激活洗炼属性消耗金钱
		clEquipRefreshAttr = 171,		// 装备洗炼消耗金钱
		clEquipRefreshInherit = 172,	// 装备洗炼继承消耗金钱
		clGemAdvance = 173,				// 使用元宝提升法宝经验的消耗
		clGemHunt = 174,				// 炼魂消耗金钱
		clGemHuntVIP = 175,				// VIP用户炼魂消耗金钱
		clGemOpenSlot = 176,			// 开启仙魂槽位消耗金钱
		clWorshipMoney = 177,			// 拜神消耗金钱
		clWorshipGain = 178,			// 拜神获得金钱
		clEquipUpgrade = 179,			// 装备升级扣除的仙币
		clFinishRefreshStar = 180,		// 立即完成刷星任务扣除元宝
		clRefreshStar = 181,			// 任务刷星扣除元宝
		clQuickFinishQuestYB=183,		// 快速完成任务消耗的元宝
		clAddItemCountYB=184,			// 增加副本次数消耗的元宝
		clSLFYAward=185,				// 兽灵封印奖励的银两

		////////////////////////////
		clMountSkillLevelUp = 186,		//坐骑技能升级
		clMountStrengthen = 187,		//坐骑强化
		clMountFeed = 188,				//坐骑喂养
		clPetFeed = 189,				//宠物喂养
		clPetJingjieUp = 190,			//提升宠物境界
		clQuestTeleport = 191,			//任务传送
		clSpiritFashion = 192,			//使用物品，添加时装
		clSpiritFashionStrong = 193,	//精灵时装强化
		clSpiritSkillLevelup = 194,		//精灵技能升级
		clAddItemCount = 195,			//添加副本挑战次数
		clWingLevelUp = 196,			//翅膀升级
		clWingEnhance = 197,			//翅膀模型强化
		clWingSkillLevelup = 198,		//翅膀技能升级
		clMountStageUp = 199,			//坐骑升阶

		//以下经验相关的不记录日志
		clQuestGiveExp=200,				//任务奖励经验
		clGmAddExp =201,               //GM添加经验 
		clKillMonsterExp=202,          //杀死怪物获得经验
		clMeditationExp=203 ,			//挂机（打坐）获得经验
		clItemAddExp = 204,				//经验流通物品获得
		clAwardBoxExp = 205,			// 打开礼包获得灵气
		clPracticeExp = 206,          //打坐获得经验
		clLoopTaskExp = 207,          //跑环任务获得经验
		clEscortExp = 208,				//护送任务获得经验奖励
		clMonsterDropLiLian = 209,		//怪物掉落的历练
		clPeachExp = 210,				// 蟠桃盛宴获得经验
		clCampBattleExp = 211,			// 阵营战获得经验
		clOffLinePracticeExp = 212,    //离线打坐获得经验

		//活动奖励
		clFstEndAward = 213,	//封神坛结算奖励
		clFishAward = 214,		//钓鱼奖励
		clHolyBeastAward = 215,	//四神兽通关奖励
		clLoopTaskAward = 216,	//跑环任务奖励
		clMicroDayAward = 217,	//微端开启福利
		clMicroDownloadAward = 218, //微端下载奖励
		clPetSaveCrossAward = 219,	//拯救宠物副本通关奖励
		clQqshCrossAward = 220,		//琴棋书画通关奖励
		clRoutineQuestLottery = 221, //日常任务抽奖
		clYellowVIPAward = 222,		//开启黄钻vip奖励
		clBlueVIPAward = 223,		//开启蓝钻vip奖励
		clWYYJTaskAward = 224,		//万妖遗迹任务奖励
		clOnlineWingAward = 225,	//在线翅膀奖励
		clWorldBossLottery = 226,   //世界boss抽奖
		clXiandaohuiLottery = 227,  //仙道宝盒抽奖
		clZmdHurtRankAward = 228,	//诛魔殿伤害排行奖励
		clDailySignAward = 229,		//签到奖励
		clFillCheckConsume = 230,	//补签奖励
		clRoutineTaskFinish = 231,	//日常任务使用双倍令
		clBetaActivity = 232,		//封测奖励物品
		clWeixinGift = 233,			//微信关注礼包
		clCrossAward =234,			//境界物品奖励
		clQQMgrPrivAward = 235,		//qq管家特权奖励
		clSpiteLevelUp = 236,		//精灵升级
		cQQvipAward = 237,			//qq会员奖励


		//装备的属性发生变化的日志
		clEQuipPropertyStrong = 301,				//装备得到了强化
		clEQuipPropertyHole = 302,					//装备打了一个孔,参数表示开了第几个空
		clEQuipPropertyRemove = 303,				//装备摘除宝石
		clEQuipPropertyRandForge = 304,				//装备发生了随机的精锻
		clEQuipPropertyInject = 305,			    //装备注入，精锻次数发生了改变
		clEQuipPropertyInlay = 306,					//装备镶嵌了宝石
		clEQuipPropertyQuality = 307,				//装备得到了品质提升
		clEQuipProeprtyBind =308,                   //装备或者宝石绑定属性发生了改变
		clEquipPropertyDurChange =309,               //装备的耐久发生了改变
		clEquipPropertyMaxDurChange =310,            //装备的最大耐久就发生了改变
		clEquipPropertyCountChange =311,              //物品的数量发生了改变(一般不会有)
		clEquipPropertyBindChange =312,              //装备的绑定属性发生改变
		clEquipPropertyBapize =313,                   //装备进行了精锻

		clEquipAddProtect = 314,			//获得一件令牌装备
		clEquipDelProtect = 315,			//删除一件令牌装备
		clEquipActive = 316,				//激活一个时装或者一个装备
		clEquipBaptize = 317,				//装备洗练消耗物品

		//任务
		clAddQuest = 400,			//接受一个任务
		clFinishQuest = 401,		//完成任务
		clGiveupQuest = 402,		//放弃任务

		//帮派
		clCreateGuild = 450,		//创建帮派
		clDeleteGuild = 451,		//解散帮派
		clJoinGuild = 452,			//加入帮派
		clExitGuild = 453,			//退出帮派
		clChangeGuildPos = 454,		//升降职

		//玩家信息
		clLevelUp = 500,			//玩家等级升
		clLoginExp = 501,			//	上线记录经验
		clLogOutExp = 502,			//下线记录经验
		clPkActor = 503,			//pk玩家
		clKilledByMonster = 504,	//给怪物杀死

		clZyCount = 510,		//阵营贡献值变化
		clMap = 511,			//记录玩家的地图位置
		clEnterFb = 512,		//进入副本
		clExitFb = 513,			//退出副本

		//荣誉值，声望
		clRenowBuyItem = 601,		//购买物品消耗历练
		clRenowQuestAward = 602,	//任务奖励历练
		clRenownConsumeByUpgradeCamp=603, // 升级阵营地位消耗历练
		clFbAwardRenown=604,		// 副本奖励历练
		clItemGetRenown =605,		//物品添加历练
		clHonorBuyItemOther =606,  //购买物品消耗荣誉值
		clGmAddSW = 607,			//gm添加声望
		clWingConsumeSW = 608,		//翅膀升级消耗声望
		clGMAddHonor = 609,			//gm命令添加荣誉
		clAwardBosAddSW = 610,			//礼包打开获得声望
		clAwardBoxAddRenown = 610,	//打开礼包获得历练
		clTournamentAddSW = 611,	//斗法台系统获得声望
		clUseWingChangeSW = 612,	//使用低等级翅膀直接转化为声望
		clZysAddHonor = 613,		//自由赛增加荣誉

		// 宝物相关的操作日志
		clAddGemItem=650,		// 添加一个宝物
		clRemoveGemItem=651,	// 删除一个宝物
		clGemUpGrade=652,		// 宝物档次提升
		clGemUpQuality=653,		// 宝物品质精粹
		clGemGetExpFromActor=654, // 玩家经验转宝物
		clGemUpLevel=655,		// 宝物升级
		clGemGotWishWhenUpgradeFailed=656, // 宝物档次进阶失败获得祝福值
		clGemDownLevelWhenUpgradeFailed=657, // 宝物档次进阶失败等级降低
		clGemUpGradeSucc=658, // 宝物档次进阶成功导致的品质变化		
		clGemRefineSpriteChar=659, // 宝物灵性炼化		
		clGemRideConsumeEndure=660, // 骑乘宝物消耗灵力
		clGemGotExpFromEquip=661, // 宝物装备获得经验
		clGemUpSSByUseItem=662,		// 宝物使用灵力丹道具提升灵力
		clGemGotExpFromUseItem=663, // 宝物使用经验道具获取经验

		//灵气相关
		clCongratulation = 671,		// 好友祝贺
		clMapAreaRoot = 672,		// 地图区域灵气加成
		clGmAddRootExp = 673,		//gm命令增加灵气
		clGuildFestRootExp = 674,  //帮派盛宴采集获得灵气
		clMailGetRootExp = 675,		//邮件获得灵气奖励
		clOilRootExp = 676,			//浪漫沙滩推油获得灵气奖励
		clStunRootExp =677,			//浪漫沙滩击晕对方获取灵气
		clFlowerEggRootExp = 678,	//争霸赛扔鲜花鸡蛋获取灵气
		clGetRootExp = 679,			// 打坐获得灵气
		clAwardBoxRootExp =680,		//打坐获得灵气奖励
		clFlowerRootExp = 681,		//赠送鲜获得灵气
		clRetrieveRootExp = 682,	//找回系统找回灵气
		clZbsRootExp	= 684,		//争霸赛获得灵气


		///---------------
		clBag2GuildDeport = 700,	//物品从背包转移到仙宗仓库
		clGuildDeport2Bag = 701,	//物品从仙宗仓库转移到背包
		clGuildDeportRemoveItem = 702, //仓库删除物品
		clEnlargeDepot = 703,		// 扩展背包的费用

		clArtifactRecallItem = 750, //神器回忆消耗物品

		clCrossHonour = 753, // 跨服荣誉兑换
		

		clPetCrossStoreToBag = 754,	//删除宠物珍宝囊物品，放入到背包
		clPetCrossGiveItem = 755,		//背包从珍宝囊获得的物品
		clPetCrossGiveToStore = 756,		//宠物闯关获得物品，放入到珍宝囊中

		clGuildImpeach = 757,	//弹劾消耗宗主弹劾令

		clMiJiTakeOn = 758, //装载秘籍
		clMiJiTakeOff = 759, //脱下秘籍

		cdUseAdvFace = 760,	 //使用至尊表情权限道具

		clTongTianTaStoreToBag = 761, //删除物品，通天塔仓库物品到背包
		clTongTianTaGiveItem = 762,  //背包从通天塔仓库获得物品
		clTongTianTaToStore = 763,   //通天塔物品到仓库

		clGMDelItem=764, //GM删除物品

		clAddDepotItem = 765,
		clMoveItemFrom = 766,
		clMoveItemTo   = 767,

		clMjScore =  768,  //梦境积分兑换

		clPetAddBlood = 769, //宠物镶嵌血脉
		clPetRemoveBlood = 770, //宠物移除血脉

		clRankAddLike = 771, //排行榜点赞
		
		clGuildBattleAward = 772, //帮派战奖励

		clPetUpdateSkill = 773,		//使用宠物技能书升级技能

		clFirstRecharge = 774,	//首冲奖励

		clEquipInherit = 775,   //装备继承

		clOpenServerActivity = 776, //开服活动

		clGiftBoxConsumeItem = 777, //礼包开启需要消耗物品

		clUseGuildItemGenerateItem = 778, //使用帮派物品生成的物品,

		clCDkeyExchangeItem = 779, //cdkey兑换

		cl3366LiBao = 780,	//3366礼包

		clLianfuQuestAward = 781,	//连服任务奖励

		clMeltRemoveItem = 782, //熔炼删除道具

		clExchangeRemoveItem = 783,	//兑换消耗物品
		clExchangeAddItem = 784,	//兑换获得新物品
		clLimitBuyItem = 785,		//限购获得物品
		clLoginAwardItem = 786,		//登录好礼奖励
		clSmashingEggsRemoveItem = 787,		//砸金蛋消耗物品
		clSmahingAddItem = 788,		//砸金蛋获得物品

		clSynthesizLostItem = 789,    //两个物品合成失去物品
		clAssignStdItem = 790,        //两个物品变成另外一个物品

		clCangBaoGeAwardItem = 791,	  //藏宝阁获得物品
		clFishRemoveItem = 792,		//消耗鱼饵
		clCostExchangeItem = 793,	//运营活动消费积分兑换

		//经验补充，保留50个
		clWorshipExp = 800,				//膜拜获得经验
		clGuildUpStarExp = 801,			//帮派提星获得奖励
		clMailGetExp = 802,				//邮件获得经验奖励
		clQuestionExp = 803,			//答题获得经验奖励
		clQuestRepulseExp = 804,		//使用答题击飞技能获得经验
		clQuestStunExp = 805,			//使用答题击晕技能获得经验
		clRankAddLikeExp = 806,			//排行榜点赞获得经验
		clWyyjAwardExp = 807,			//万妖遗迹奖励获得经验
		clMapAreaExp = 808,				// 地图区域经验加成
		clWorldBossLotteryExp = 809,	//世界boss抽奖获得奖励经验
		clSuperEliteExp = 810,			//超级精英获得奖励经验
		clZbsFlowerEggExp = 811,		//争霸赛偷鲜花鸡蛋奖励经验
		clLevelItemAddExp = 812,		//使用升级物品获得经验
		clRetrieveExp = 813,			//找回系统找回经验
		clZbsExp = 814,					//争霸赛获得经验
		clRingStageUpItem	= 815,			//婚戒进阶扣除道具
		clRingStageUpMoney = 816,			//婚戒进阶扣除货比
		clDevoiceMoney = 817,		//强制离婚消耗元宝
		clUseRing = 818,					//使用婚戒
		clXiaoyaoEquip = 819,		//逍遥套装获得的经验奖励
		clQQBrpwser = 820,		//qq浏览器 奖励
		clRingStageUpNewItem = 821,			//婚戒进阶获得新婚戒
		clMarryBaiTang = 822,	//拜堂活动的奖励
		clMarryNaoXiExp = 823,	//闹喜活动奖励(经验)
		clMarryNaoXiRootExp = 824, //闹喜活动奖励(灵气)
		clMarryXiyanExp = 825,	//喜宴活动奖励(经验)
		clMarryXiyanRootExp = 826, //喜宴活动奖励(灵气)
		clMarryFbSkill = 827,	//喜宴技能奖励
		clRingCuiLianMoney = 828,	//婚戒淬炼扣除货比
		clUseMoneyitem = 829,	//使用金砖道具
		clUseSoulItem = 830,	//使用道具增加灵魂值

		clMax,
	};

	void Init();
	const char* LogStr(int logid);
};


#endif

