#ifndef _LOG_DEF_H_
#define _LOG_DEF_H_

//Ϊ�˷�ֹ������Ⱦ������һ��GameLog��
namespace GameLog
{
	//��־����
	enum  taggGameLogType
	{
		//��Ʒid,����(�����Ǹ���),��ע
		clScriptGiveItem = 1,	//nPC�ű��и�����Ʒ
		clScriptDeleteItem=2,	//nPC�ű���ɾ����Ʒ
		clTakeOnItem=3,			//����װ��
		clTakeOffItem=4,		//ȡ��װ��
		clUserItem=5,			//�û�ʹ����Ʒ
		clUserDestroyItem=6,	//�û�������Ʒ
		clBuyItem=7,			//�û���NPC�̵깺����Ʒ
		clSellItem=8,			//�û�����Ʒ������NPC�̵�
		clRepairItem=9,			//�û�������Ʒ
		clBrokenItem=10,             //��Ʒ���;úĹ����
		clTimeupItem=11,             //��Ʒ�򵽴�ʹ��ʱ�޶���ʧ
		clGMAddItem=12,              //GM�������
		clShoppingCenterGiveItem=13, //�̳Ǹ���������һ����Ʒ
		clRankRewardItem=14,         //������������Ʒ
		clGuildDonateItem=15,        //�򹤻������Ʒ
		clWorldTalkItem=16,          //����㲥���ѵ���
		clMarriageItem=17,           //������ĵ���
		clInlayItem=18,              //��Ʒ��Ƕ������Ʒ
		clEquipStrengthItem=19,      //װ��ǿ��������Ʒ
		clEquipUpgradeItem=20,       //װ������������Ʒ
		clAchieveRewardItem=21,      //�ɾͽ�����Ʒ
		clQuestGiveItem=22,          //��������Ʒ
		clBuyStoreItem=23,			  //�����̳���Ʒ
		clDealTransferItem=24,		  //���׻����Ʒ
		clGuildClear=25,			  //�����Զ�������Ʒ��ָ���ټ��
		clGuildGive=26,				  //���ɵĸ�����Ʒ
		clGuildUpgrade=27,		      //�����������İ��ɷ�
		clGuildFr=28,				  //�������ɷ��ٶ������˰���
		clKillMonsterItem=29,         //ɱ�ֻ����Ʒ
		clSkillTrainItem=30,          //��������������Ʒ 
		clEquipRemoveGemItem= 31,          //װ��ժ����ʯ�����Ʒ
		clEquipRemoveLostItem =32,            //װ��ժ��������Ʒ
		clEquipSynthesizLostItem=33,         //װ���ϳ�ʧȥ��Ʒ
		clEQuipAssignStdItem  =34,            //װ���������һ����Ʒ
		clEQuipUpStageLostItem  =35,        //װ������������Ʒ
		clEQuipInjectLostItem  =36,           //װ��ע��������Ʒ
		clEQuipPourLostItem =37,              //װ���Ĺ�ע������Ʒ

		clEquipSplit =38,             //��Ʒ���
		clItemMerge =39,  //��Ʒ����
		clDealLostIteam =40, //����ʧȥ��Ʒ
		clDealGetItem =41,  //���׻����Ʒ
		clBag2Deport =42,  //��Ʒ�ӱ���ת�Ƶ��ֿ�
		clDeport2Bag =43,  //��Ʒ�Ӳֿ�ת�Ƶ�����
		clDeportRemoveItem =44, //�ֿ�ɾ����Ʒ
		
		clConsiRemoveItemFromBag = 45,		//��Ҽ�����Ʒ���ѱ�������Ʒɾ��
		clConsiAddItemToList = 46,		//��������Ʒ�ϼ�
		clConsiCancelItemRemoveFromList = 47,		//���ȡ����������Ʒ�¼�
		clConsiCancelItemToBag = 48,	//ȡ������Ʒת�뱳��
		clConsiBuyItemRemoveFromList = 49,		//����ڼ���ϵͳ������Ʒ,��Ʒ�¼�
		clConsiBuyItemAddToBag = 50,			//����ڼ���ϵͳ������Ʒ����Ʒת�뱳��
		clConsiTimeoutRemoveFromList = 51,		//��Ҽ�����Ʒ����,��Ʒ�¼�
		clConsiTimeoutAddToBag = 52,			//��Ҽ�����Ʒ����,��Ʒת�뱳��

		clEquipSynthesize=53,         //װ���ϳɵõ���Ʒ
		clEQuipBrokedown  =54,        //װ���ֽ�õ���Ʒ
		clItemFinishAwardItem = 55,	//����ͨ�ؽ�����Ʒ
		clNewPlayerAwardItem = 56,		//����������Ʒ
		clOnlineAwardItem = 57,			//���߽�����Ʒ
		clEQuipQualityLostItem = 58,		//װ����Ʒ������Ʒ

		clGmPresentItem = 59,			//gm����Ʒ
		clQuestLostItem = 60,			//��ɻ��߷�������ʧȥ������Ʒ
		clServerGiveItem = 61,			//�����̨����Ʒ��ͨ���Ǿٰ��͵Ķ���
		clLeftSceneRemoveItem = 62,		//�뿪����ɾ����Ʒ
		clRenownBuyItem =63,            //����������Ʒ
		clExchangeBadgeRemoveItem=64,	// �ռǶһ�ɾ���ϵĻռ���Ʒ
		clExchangeBadgeAddItem=65,		// �ռǶһ��������µĻռ���Ʒ
		clGotVIPFashionDress=66,		// VIP����һ�ʱװ
		clLearnSkillMiji=67,             //����miji��������Ʒ,(ȡ��)
		clGemRefineRemoveItem=68,		// ������������������Ʒ
		clGemUpgradeRemoveItem=69,		// ���ﵵ�ν���������Ʒ
		clGemAddSpriteStrenRemoveItem=70, // ʹ�ñ�����������������Ʒ
		clAddVIPTimeRemoveItem=71,		// �ӳ�VIPʱ�����ĵ���
		clGemRefineQualityRemoveItem=72, // ����Ʒ�ʾ���������Ʒ
		clGemOpenSlotRemoveItem=73,		// ��������������Ʒ
		clGemComposeRemoveItem=74,		// �ϳ�������Ʒ
		clGemComposeAddItem=75,			// ����ϳɳɹ���ӱ�����Ʒ
	    clPetLearnSkill =76,           //����ѧϰ����,���ļ�����
		clGemSmithRemoveItem=77,		// ���ﾫ��������Ʒ		
		clDmkjGiveItem = 78,			//�ڳ齱��õ���Ʒ
		clDmkjGiveToStore = 79,			//�齱�鵽��Ʒ���ֿ���
		clGuildBuyStoreItem = 80,		// ���ɹ�����Ʒ
		clActivityAwardItem = 81,			// ��ӻ�Ծ������Ʒ
		clVIPLoginAward = 82,			// VIP�û�ÿ���¼����
		clVIPUpdateAward = 83,			// VIP�ȼ���������
		clDmkjGiveForSY = 84,			// ʮһ�齱
		clTxApiGiveAward = 85,			// ��ѶAPI���ظ��轱��
		clUseVipCard = 86,				// ʹ��VIP���鿨
		clMailGetItem = 87,  			//�ʼ������Ʒ
		clEntrustGiveItem = 88,			//����ί�л����Ʒ
		clEntrustGiveToStore = 89,		//����ί����Ʒ�Ƴ�������
		clHonorBuyItem = 90,			//����ֵ������Ʒ
		clRingUpLostEquip = 91,			// ��ָ������ʧȥԭ�еĽ�ָ
		clRingUpAddEquip = 92,			// ��ָ����������µĽ�ָ
		clMarryGetRing = 93,			// ����ý�ָ
		clDivLostRing = 94,				// ���ʧȥ��ָ
		clUseRingQm = 95,				// ���Ľ�ָ��ȡ���ܶ�
		clDmkjStoreToBag = 96,			//�齱�鵽��Ʒ������
		clEntrustStoreToBag = 97,			// ����ί����Ʒ������
		clDenaturationMailEquip = 98,		//���Ժ󲻷���װ������
		clTeamBuyItem = 99,				//������һ�

		//��������,����, ��Դ�ı�ע(����skill ����)
		clNpcGiveMoney=100,				//nPC����Ǯ
		clNpcDelMoney=101,          //nPCɾ����Ǯ
		clGmAddMoney=102,              //GM�����˽�Ǯ
		clShopBuyMoney=103,            //���̵��ﹺ��ʧȥ��Ǯ
		clChatPosMoney = 104,             // ���췢���Լ��������Ľ�Ǯ
		clShopSellMoney=105,           //��NPC����������ý�Ǯ
		clShopoingCenterMoney=106,     //���̳�֧��
		clGuildDonateMoney=107,        //���������Ǯ
		clLearnSkillMoney=108,         //ѧϰ�������ѽ�Ǯ
		clChatMoney=109,               //�������Ľ�Ǯ�� ȫ��
		clMountXlMoney=110,           //����ϴ�����Ľ�Ǯ
		clDealTransferYB=111,            //���׻�ý�Ǯ��۳�Ԫ��
		clRankRewardMoney=112,         //����������Ǯ
		clAchieveRewardMoney=113,      //�ɾͽ�����Ǯ
	    clQuestGiveMoney=114,          //��������Ǯ
		clStoreBuyMoney=115,		   //�̳��й�����Ʒ֧��
		clEnlargeBag=116,              //���󱳰�
		clDealTransferMoney=117,	   //���׻�ý�Ǯ��۳���Ǯ
		clGuildGiveMoney=118,			//���ɸ����Ǯ�����ʣ��������ÿ�տ���ȡ��
		clCreateGuildLostMoney=119,		//��������ʱ���ɵ�Ǯ��
		clKillMonsterMoney=120,         //ɱ�ֻ�õĽ�Ǯ

		clConsiFee		= 121,			//������Ʒ��ȡ����
		clConsiBuyFee   = 122,			//����ϵͳ������Ʒ�۳�����
		clConsiSellFee = 123,			//������Ʒ�������ȡ����
		clRentFee = 124,				//�ֿ��������Ľ�Ǯ
		clEquipHoleMoney = 125,		//	װ��������ѽ�Ǯ	LongStr0:װ������
		clEquipRemoveMoney = 126,	//	װ��ժ�����ѽ�Ǯ	LongStr0:װ������
		clEquipSynthesizMoney =127,		//װ���ϳ����ѽ�Ǯ	LongStr0:װ������
		clEquipForgeMoney = 128,	//װ���������ѽ�Ǯ	LongStr0:װ������
		clEquipBrokedMoney = 129,	//װ���ֽ����ѽ�Ǯ	LongStr0:װ������
		clEquipInjectMoney = 130,	//װ��ע�����ѽ�Ǯ	LongStr0:װ������
		clEquipPourMoney = 131,		//	װ����ע���ѽ�Ǯ	LongStr0:װ������
		clEquipInlayMoney = 132,	//װ����Ƕ���ѽ�Ǯ	LongStr0:װ������
		clEquipUpQualityMoney = 133,//	װ����Ʒ���ѽ�Ǯ	LongStr0:װ������
		clEquipStrongMoney = 134,	//װ��ǿ�����ѽ�Ǯ
		clItemFinishAwardMoney = 135,//����ͨ�ؽ�����Ǯ
		clNewPlayerAwardMoney = 136,	//���ֽ�����Ǯ
		clOnlineAwardMoney = 137,		//���߽�����Ǯ
		clWithdrawYuanBao = 138,			// ��ȡԪ��	
		clServerGiveMoney = 139,		//��̨������Ǯ
		clActionAwardMoney=140,			// �������Ǯ
		clRenowBuyConsumeMoney =141,    //����������Ʒ��ʱ�����Ľ�Ǯ
		clPlantYB =142,           //��ֲԪ��
		clGainYB=143,                 //�ջ�Ԫ��
		clChangeIconMoney=144,                    //����ͷ��
		clUpgradeConsumeMoney=145,		// ���ﵵ�ν������Ľ�Ǯ
		clGemRefineQualityConsumeMoney=146, // ��������Ʒ�����Ľ�Ǯ
		clGemComposeConsumeMoney=147,	// ����ϳ����Ľ�Ǯ
		clGemUpSCConsumeMoney=148, // ���������������Ľ�Ǯ
		clGemSmithConsumeMoney=149, // ���￪�����Ľ�Ǯ
		clDmkjConsumeMoney = 150,		//��������Ԫ��
		clImpeachVoteConsumeMoney = 151, // ��������ͶƱ���Ľ�Ǯ
		clMountLevelUpYuanbao = 152,	// ������������cd����Ԫ��
		clMountStageUpYuanbao = 153,	// �����������Ԫ��
		clMountXlYuanbao = 154,			// ����ϴ������Ԫ��
		clMountJjBindCoin = 155,		// ���������ɱ�
		clMountLevelBindCoin = 156,		// ���������ɱ�
		clRootLevelCoin = 157,			// ����������Ľ�Ǯ 
		clGuildContribYb = 158,			// ��������Ԫ��
		clGuildStore = 159,				// �����̵깺��, ȡ�������������Ĺ���ֵ
		clConsignmentMoney = 160,		// ����ʧȥ��Ǯ
		clConsignmentCancelMoney = 161,	// �����Ľ�Ǯȡ����������
		clConsignmentBugMoney = 162,	// ��������Ľ�Ǯ
		clConsignmentTimeout = 163,		// �������ڣ���Ǯ��������
		clEquipInsertGem = 164,			// װ����Ƕ��ʯ���Ľ�Ǯ
		clEuqipRemoveGem = 165,			// װ���Ƴ���ʯ���Ľ�Ǯ
		clEuqipStrong = 166,			// װ��ǿ�����Ľ�Ǯ
		clEquipStrongFail = 167,		// װ��ǿ��ʧ�����Ľ�Ǯ
		clEquipItemMix = 168,			// ��Ʒ�ϳ����Ľ�Ǯ
		clEquipStrongChange = 169,		// ǿ��ת�����Ľ�Ǯ
		clEquipActiveRefresh = 170,		// ����ϴ���������Ľ�Ǯ
		clEquipRefreshAttr = 171,		// װ��ϴ�����Ľ�Ǯ
		clEquipRefreshInherit = 172,	// װ��ϴ���̳����Ľ�Ǯ
		clGemAdvance = 173,				// ʹ��Ԫ�������������������
		clGemHunt = 174,				// �������Ľ�Ǯ
		clGemHuntVIP = 175,				// VIP�û��������Ľ�Ǯ
		clGemOpenSlot = 176,			// �����ɻ��λ���Ľ�Ǯ
		clWorshipMoney = 177,			// �������Ľ�Ǯ
		clWorshipGain = 178,			// �����ý�Ǯ
		clEquipUpgrade = 179,			// װ�������۳����ɱ�
		clFinishRefreshStar = 180,		// �������ˢ������۳�Ԫ��
		clRefreshStar = 181,			// ����ˢ�ǿ۳�Ԫ��
		clQuickFinishQuestYB=183,		// ��������������ĵ�Ԫ��
		clAddItemCountYB=184,			// ���Ӹ����������ĵ�Ԫ��
		clSLFYAward=185,				// �����ӡ����������

		////////////////////////////
		clMountSkillLevelUp = 186,		//���＼������
		clMountStrengthen = 187,		//����ǿ��
		clMountFeed = 188,				//����ι��
		clPetFeed = 189,				//����ι��
		clPetJingjieUp = 190,			//�������ﾳ��
		clQuestTeleport = 191,			//������
		clSpiritFashion = 192,			//ʹ����Ʒ�����ʱװ
		clSpiritFashionStrong = 193,	//����ʱװǿ��
		clSpiritSkillLevelup = 194,		//���鼼������
		clAddItemCount = 195,			//��Ӹ�����ս����
		clWingLevelUp = 196,			//�������
		clWingEnhance = 197,			//���ģ��ǿ��
		clWingSkillLevelup = 198,		//���������
		clMountStageUp = 199,			//��������

		//���¾�����صĲ���¼��־
		clQuestGiveExp=200,				//����������
		clGmAddExp =201,               //GM��Ӿ��� 
		clKillMonsterExp=202,          //ɱ�������þ���
		clMeditationExp=203 ,			//�һ�����������þ���
		clItemAddExp = 204,				//������ͨ��Ʒ���
		clAwardBoxExp = 205,			// ������������
		clPracticeExp = 206,          //������þ���
		clLoopTaskExp = 207,          //�ܻ������þ���
		clEscortExp = 208,				//���������þ��齱��
		clMonsterDropLiLian = 209,		//������������
		clPeachExp = 210,				// ���ʢ���þ���
		clCampBattleExp = 211,			// ��Ӫս��þ���
		clOffLinePracticeExp = 212,    //���ߴ�����þ���

		//�����
		clFstEndAward = 213,	//����̳���㽱��
		clFishAward = 214,		//���㽱��
		clHolyBeastAward = 215,	//������ͨ�ؽ���
		clLoopTaskAward = 216,	//�ܻ�������
		clMicroDayAward = 217,	//΢�˿�������
		clMicroDownloadAward = 218, //΢�����ؽ���
		clPetSaveCrossAward = 219,	//���ȳ��︱��ͨ�ؽ���
		clQqshCrossAward = 220,		//�����黭ͨ�ؽ���
		clRoutineQuestLottery = 221, //�ճ�����齱
		clYellowVIPAward = 222,		//��������vip����
		clBlueVIPAward = 223,		//��������vip����
		clWYYJTaskAward = 224,		//�����ż�������
		clOnlineWingAward = 225,	//���߳����
		clWorldBossLottery = 226,   //����boss�齱
		clXiandaohuiLottery = 227,  //�ɵ����г齱
		clZmdHurtRankAward = 228,	//��ħ���˺����н���
		clDailySignAward = 229,		//ǩ������
		clFillCheckConsume = 230,	//��ǩ����
		clRoutineTaskFinish = 231,	//�ճ�����ʹ��˫����
		clBetaActivity = 232,		//��⽱����Ʒ
		clWeixinGift = 233,			//΢�Ź�ע���
		clCrossAward =234,			//������Ʒ����
		clQQMgrPrivAward = 235,		//qq�ܼ���Ȩ����
		clSpiteLevelUp = 236,		//��������
		cQQvipAward = 237,			//qq��Ա����


		//װ�������Է����仯����־
		clEQuipPropertyStrong = 301,				//װ���õ���ǿ��
		clEQuipPropertyHole = 302,					//װ������һ����,������ʾ���˵ڼ�����
		clEQuipPropertyRemove = 303,				//װ��ժ����ʯ
		clEQuipPropertyRandForge = 304,				//װ������������ľ���
		clEQuipPropertyInject = 305,			    //װ��ע�룬���ʹ��������˸ı�
		clEQuipPropertyInlay = 306,					//װ����Ƕ�˱�ʯ
		clEQuipPropertyQuality = 307,				//װ���õ���Ʒ������
		clEQuipProeprtyBind =308,                   //װ�����߱�ʯ�����Է����˸ı�
		clEquipPropertyDurChange =309,               //װ�����;÷����˸ı�
		clEquipPropertyMaxDurChange =310,            //װ��������;þͷ����˸ı�
		clEquipPropertyCountChange =311,              //��Ʒ�����������˸ı�(һ�㲻����)
		clEquipPropertyBindChange =312,              //װ���İ����Է����ı�
		clEquipPropertyBapize =313,                   //װ�������˾���

		clEquipAddProtect = 314,			//���һ������װ��
		clEquipDelProtect = 315,			//ɾ��һ������װ��
		clEquipActive = 316,				//����һ��ʱװ����һ��װ��
		clEquipBaptize = 317,				//װ��ϴ��������Ʒ

		//����
		clAddQuest = 400,			//����һ������
		clFinishQuest = 401,		//�������
		clGiveupQuest = 402,		//��������

		//����
		clCreateGuild = 450,		//��������
		clDeleteGuild = 451,		//��ɢ����
		clJoinGuild = 452,			//�������
		clExitGuild = 453,			//�˳�����
		clChangeGuildPos = 454,		//����ְ

		//�����Ϣ
		clLevelUp = 500,			//��ҵȼ���
		clLoginExp = 501,			//	���߼�¼����
		clLogOutExp = 502,			//���߼�¼����
		clPkActor = 503,			//pk���
		clKilledByMonster = 504,	//������ɱ��

		clZyCount = 510,		//��Ӫ����ֵ�仯
		clMap = 511,			//��¼��ҵĵ�ͼλ��
		clEnterFb = 512,		//���븱��
		clExitFb = 513,			//�˳�����

		//����ֵ������
		clRenowBuyItem = 601,		//������Ʒ��������
		clRenowQuestAward = 602,	//����������
		clRenownConsumeByUpgradeCamp=603, // ������Ӫ��λ��������
		clFbAwardRenown=604,		// ������������
		clItemGetRenown =605,		//��Ʒ�������
		clHonorBuyItemOther =606,  //������Ʒ��������ֵ
		clGmAddSW = 607,			//gm�������
		clWingConsumeSW = 608,		//���������������
		clGMAddHonor = 609,			//gm�����������
		clAwardBosAddSW = 610,			//����򿪻������
		clAwardBoxAddRenown = 610,	//������������
		clTournamentAddSW = 611,	//����̨ϵͳ�������
		clUseWingChangeSW = 612,	//ʹ�õ͵ȼ����ֱ��ת��Ϊ����
		clZysAddHonor = 613,		//��������������

		// ������صĲ�����־
		clAddGemItem=650,		// ���һ������
		clRemoveGemItem=651,	// ɾ��һ������
		clGemUpGrade=652,		// ���ﵵ������
		clGemUpQuality=653,		// ����Ʒ�ʾ���
		clGemGetExpFromActor=654, // ��Ҿ���ת����
		clGemUpLevel=655,		// ��������
		clGemGotWishWhenUpgradeFailed=656, // ���ﵵ�ν���ʧ�ܻ��ף��ֵ
		clGemDownLevelWhenUpgradeFailed=657, // ���ﵵ�ν���ʧ�ܵȼ�����
		clGemUpGradeSucc=658, // ���ﵵ�ν��׳ɹ����µ�Ʒ�ʱ仯		
		clGemRefineSpriteChar=659, // ������������		
		clGemRideConsumeEndure=660, // ��˱�����������
		clGemGotExpFromEquip=661, // ����װ����þ���
		clGemUpSSByUseItem=662,		// ����ʹ��������������������
		clGemGotExpFromUseItem=663, // ����ʹ�þ�����߻�ȡ����

		//�������
		clCongratulation = 671,		// ����ף��
		clMapAreaRoot = 672,		// ��ͼ���������ӳ�
		clGmAddRootExp = 673,		//gm������������
		clGuildFestRootExp = 674,  //����ʢ��ɼ��������
		clMailGetRootExp = 675,		//�ʼ������������
		clOilRootExp = 676,			//����ɳ̲���ͻ����������
		clStunRootExp =677,			//����ɳ̲���ζԷ���ȡ����
		clFlowerEggRootExp = 678,	//���������ʻ�������ȡ����
		clGetRootExp = 679,			// �����������
		clAwardBoxRootExp =680,		//���������������
		clFlowerRootExp = 681,		//�����ʻ������
		clRetrieveRootExp = 682,	//�һ�ϵͳ�һ�����
		clZbsRootExp	= 684,		//�������������


		///---------------
		clBag2GuildDeport = 700,	//��Ʒ�ӱ���ת�Ƶ����ڲֿ�
		clGuildDeport2Bag = 701,	//��Ʒ�����ڲֿ�ת�Ƶ�����
		clGuildDeportRemoveItem = 702, //�ֿ�ɾ����Ʒ
		clEnlargeDepot = 703,		// ��չ�����ķ���

		clArtifactRecallItem = 750, //��������������Ʒ

		clCrossHonour = 753, // ��������һ�
		

		clPetCrossStoreToBag = 754,	//ɾ�������䱦����Ʒ�����뵽����
		clPetCrossGiveItem = 755,		//�������䱦�һ�õ���Ʒ
		clPetCrossGiveToStore = 756,		//���ﴳ�ػ����Ʒ�����뵽�䱦����

		clGuildImpeach = 757,	//������������������

		clMiJiTakeOn = 758, //װ���ؼ�
		clMiJiTakeOff = 759, //�����ؼ�

		cdUseAdvFace = 760,	 //ʹ���������Ȩ�޵���

		clTongTianTaStoreToBag = 761, //ɾ����Ʒ��ͨ�����ֿ���Ʒ������
		clTongTianTaGiveItem = 762,  //������ͨ�����ֿ�����Ʒ
		clTongTianTaToStore = 763,   //ͨ������Ʒ���ֿ�

		clGMDelItem=764, //GMɾ����Ʒ

		clAddDepotItem = 765,
		clMoveItemFrom = 766,
		clMoveItemTo   = 767,

		clMjScore =  768,  //�ξ����ֶһ�

		clPetAddBlood = 769, //������ǶѪ��
		clPetRemoveBlood = 770, //�����Ƴ�Ѫ��

		clRankAddLike = 771, //���а����
		
		clGuildBattleAward = 772, //����ս����

		clPetUpdateSkill = 773,		//ʹ�ó��＼������������

		clFirstRecharge = 774,	//�׳影��

		clEquipInherit = 775,   //װ���̳�

		clOpenServerActivity = 776, //�����

		clGiftBoxConsumeItem = 777, //���������Ҫ������Ʒ

		clUseGuildItemGenerateItem = 778, //ʹ�ð�����Ʒ���ɵ���Ʒ,

		clCDkeyExchangeItem = 779, //cdkey�һ�

		cl3366LiBao = 780,	//3366���

		clLianfuQuestAward = 781,	//����������

		clMeltRemoveItem = 782, //����ɾ������

		clExchangeRemoveItem = 783,	//�һ�������Ʒ
		clExchangeAddItem = 784,	//�һ��������Ʒ
		clLimitBuyItem = 785,		//�޹������Ʒ
		clLoginAwardItem = 786,		//��¼������
		clSmashingEggsRemoveItem = 787,		//�ҽ�������Ʒ
		clSmahingAddItem = 788,		//�ҽ𵰻����Ʒ

		clSynthesizLostItem = 789,    //������Ʒ�ϳ�ʧȥ��Ʒ
		clAssignStdItem = 790,        //������Ʒ�������һ����Ʒ

		clCangBaoGeAwardItem = 791,	  //�ر�������Ʒ
		clFishRemoveItem = 792,		//�������
		clCostExchangeItem = 793,	//��Ӫ����ѻ��ֶһ�

		//���鲹�䣬����50��
		clWorshipExp = 800,				//Ĥ�ݻ�þ���
		clGuildUpStarExp = 801,			//�������ǻ�ý���
		clMailGetExp = 802,				//�ʼ���þ��齱��
		clQuestionExp = 803,			//�����þ��齱��
		clQuestRepulseExp = 804,		//ʹ�ô�����ɼ��ܻ�þ���
		clQuestStunExp = 805,			//ʹ�ô�����μ��ܻ�þ���
		clRankAddLikeExp = 806,			//���а���޻�þ���
		clWyyjAwardExp = 807,			//�����ż�������þ���
		clMapAreaExp = 808,				// ��ͼ������ӳ�
		clWorldBossLotteryExp = 809,	//����boss�齱��ý�������
		clSuperEliteExp = 810,			//������Ӣ��ý�������
		clZbsFlowerEggExp = 811,		//������͵�ʻ�������������
		clLevelItemAddExp = 812,		//ʹ��������Ʒ��þ���
		clRetrieveExp = 813,			//�һ�ϵͳ�һؾ���
		clZbsExp = 814,					//��������þ���
		clRingStageUpItem	= 815,			//�����׿۳�����
		clRingStageUpMoney = 816,			//�����׿۳�����
		clDevoiceMoney = 817,		//ǿ���������Ԫ��
		clUseRing = 818,					//ʹ�û��
		clXiaoyaoEquip = 819,		//��ң��װ��õľ��齱��
		clQQBrpwser = 820,		//qq����� ����
		clRingStageUpNewItem = 821,			//�����׻���»��
		clMarryBaiTang = 822,	//���û�Ľ���
		clMarryNaoXiExp = 823,	//��ϲ�����(����)
		clMarryNaoXiRootExp = 824, //��ϲ�����(����)
		clMarryXiyanExp = 825,	//ϲ������(����)
		clMarryXiyanRootExp = 826, //ϲ������(����)
		clMarryFbSkill = 827,	//ϲ�缼�ܽ���
		clRingCuiLianMoney = 828,	//�������۳�����
		clUseMoneyitem = 829,	//ʹ�ý�ש����
		clUseSoulItem = 830,	//ʹ�õ����������ֵ

		clMax,
	};

	void Init();
	const char* LogStr(int logid);
};


#endif

