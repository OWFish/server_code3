#pragma once

/*********************************
*
* ���ļ���Ҫ���ڶ��ڽ�ɫ��ص��¼�����������ѧϰ��ĳ�����ܣ������Ʒ��
*
**********************************/


//tolua_begin
enum tagActorEventID
{
	aeNoEvent = 0,		//δ�����¼�
	aeStartBattle,	//����ս��״̬
	aeStartPkState, //��������pk״̬
	aeLevel,			//��ɫ����
	aeSkillLevelup,		//��������F
	aeAddEquiment,	//����װ��
	aeDelEquiment,	//�ѵ�װ��

	/* Actor::Init����*/
	aeInit,			//��ʼ���¼�, ������ģ�����Գ�ʼ��֮�� @���ܷ���,�������Ҳ��ִ��
	aeBeforeLogin,	//��½ǰ�¼��� �������߽���֮�࣬�ɲ���������ݵ������͸��ͻ��� ���ܷ���,������Ҳ�ִ��
	aeUserLogin,   //��ҵ�½ [�Ƿ��ǵ�1�ε�¼] ��Ҫ���ڷ��Ϳͻ��˳�ʼ����Ϣ �ܷ���,������Ҳ�ִ��
	aeUserFirstLogion, //��ҵ�һ�ε�¼�ĳ�ʼ��
	/*******************/
	
	aeUserLogout,   //��ҵǳ�

	aeEnterFuben,	//��ҽ��븱��[����id]
	aeLeftTeam,	//����˳����飨�����Լ��˳���ӳ��ߵ������,������¼��У��ű�Ҫ������˳��������ص���ͨ������[���ָ�룬����ָ��]��ע�⣺ִ�����������ʱ�����˳����飬�����޷�ͨ�����ָ���ȡ����ָ�룬�����и��������˶���ָ��
	//aeOnActorDeath = 19 , //�������
	aeReliveTimeOut,	//�жϸ���ʱ���Ƿ�ʱ���û�����5����û��ѡ��سǸ����ԭ�ظ�����������ű������ͻ����Ǹ���.[���ָ��]
	aeRecharge,		//��ҳ�ֵ
	aeNewDayArrive,				// �µ�һ������¼�����������ڼ��24����������¼�
	aeUpdateVipInfo,				// ����Vip��Ϣ
	aeKilledByActor,			//�����ɱ�� [�Լ�ָ��][�Է�(ɱ����)ָ��]


	aeStarQuest,				//ˢ�������¼�
	aeOpenSys,					//����ϵͳ
	aeTeleportComfirm,			//������ȷ��
	aeDayEnd, 					//�������
	aeConsumeYuanbao,			//����Ԫ��
	aeConsumeGold,				//���ѽ��
	aeChangePrestige,			//����ֵ�ı�
	aeRechargeOffline,			//���߳�ֵ
	aeJoinGuild,				//����һ������
	aeLeftGuild,				//�뿪һ������
	aePetBattle,				//�����ս

	aeCrossWar,				// ���ս
	aeNewDayHoursArrive,	   // �µ��賿��������¼�

	aeStrongLevelChanged,//ǿ���ȼ��仯

	aeNewWeekArrive,//ÿ��һ ����������¼�
	aeNewDayHoursArriveInCommSrv, //��һ����������¼�������ͨ��������

	aeStoreCost,		//�̳����Ļ����¼�
	aeDropItem,		//������Ʒ����()
	aeSmeltEquip,		//����װ��
	aeFightPower,		//ս�����仯
	aeSkirmish,		//����ս
	aeUpgradeSkillCount,	//������������
	aeWingLevelUp,		//�������
	aeWingStarUp,		//�������
	aeWingTrain,		//��������¼�
	aeUpgradeJingmai,	//���������¼�
	aeUpgradeStone,	//��ʯ�����¼�
	aeUpgradeZhuling,	//ע�������¼�
	aeUpgradeTupo,		//ͻ�������¼�
	aeEnterPublicBoss,	//����ȫ��BOSS
	aeOpenRole,			//������ɫ
	aeZhuansheng,			//ת���¼�
	aeUpgradeLoongSoul,	//���������¼�
	aeUpgradeShield,	//���������¼�
	aeFieldBoss,	//Ұ��boss��ɱ
	aeAddEssence,	//���Ӿ��� 
	aeAchievetaskFinish, // �ɾ��������
	aeChapterLevelFinish, // ��ɹؿ�
	aeFinishFuben,	// ͨ�ظ���
	aeCreateRole, //�����ӽ�ɫ
	aeBlessLevelChanged, // ����
	aeLearnMiJi, // ѧϰ�ؼ�
	aeGuildDonate, //�������
	aeChangeName, //����
	aeTianTiChallenge, //������ս

	aeMagicLevel,		//�񹦵ȼ�->����(��λ)�ȼ� c
	aeWarSpiritlevel,		//ս��ȼ�
	aeWarSpiritstage,   //ս��׼�
	aeOrange,			//��װ����
	aeLegend,			//��������
	aeCasting,			//װ������
	aeArtifact,			//װ������
	aeArtifactstage,	//�����׼�
	aeParalysis,		//��Խ�������
	aeProtective,		//�����������
	aePersonalBoss,		//��ɱ����BOSS
	aeFullBoss,			//��ɱȫ��BOSS
	aeTransferBoss,		//��ɱתְBOSS
	aeHegemony,			//��ɱתְBOSS
	aeloongLevelCount,	//������������
	aeShieldLevelCount,	//������������
	aeXueyuLevelCount,	//Ѫ����������
	aeGuildSkill,		//���Ἴ������
	aeAtkWorldBoss,		//��������boss
	aeMorship,			//Ĥ��
	aeGetTreasureBoxType,	//��ȡָ�����ͱ���
	aeChallengeFb,		//�����
	aeTuJian,			//ͼ��
	aeFuWenLevel,		//ս�Ƶȼ�
	aeTreasureBoxReward,//��ȡ���佱��
	aeReqChapterReward,//��ȡ�½ڽ���
	aeReqChapterWorldReward,//��ȡ�½ڵ����罱��
	aeKillChapterMonster,//��ɱ�ؿ�����
	aeXunBao,			//Ѱ��:Ѱ������
	aeGetWroldBossBelong,//��ȡ������boss����
	aeKnighthoodLv,	//ѫ������:��ǰ�ȼ�
	aeNeiGongUp,	//�ڹ���������
	aeActTogetherhit,//����(����)�ϻ�����
	aeUseTogetherhit,//ʹ�úϻ�����
	aeActImba,		//��������
	aeActAExring,	//��������ؽ�
	aeUpAExring,	//�����ؽ�
	aeOpenMonthCard,//��ͨ�¿�
	aeShareGame,//����һ��
	aeTianTiLevel,//�������Դﵽָ����λ
	aeSkirmishRank,//�ﵽ����ս���а�ǰ����
	aeDayLiLian,   //����ﵽ��������
	aeDayFuBenSweep,   //����ɨ������
	aeFinishLimitTask,   //�����ʱ����
	aeGetItem,			//��ȡһ������
	aeActImbaItem,	//����������Ƭ
	aeCaiKuang,		//�ڿ�
	aeDayFuBenWin,//ÿ�ո���ʤ��(ֻ�и���boss)
	aeHolyBoss, //������һ������boss(boss�淨)
	aeNewWorldBoss,//����������boss
	aeCampBattleFb,//��������Ӫս
	aeGetWBossActScore,//�����һ��boss�淨����
	aeMiJingBoss,//������һ���ؾ�boss(boss�淨)
	aeLoseFuben,//����ʧ��
	aeJoinActivityId, //����ָ���id
	aeRichManCircle, //����Ȧ��
	aeExpFubenAwardType, //���鸱����������
	aeWorldBoss,	//����һ��boss�淨,boss����ID,����ID,��������
	aeZhuangBan,	//����װ��
	aeChallengePVM, //��ս������
	aeAchievemwntAward, //��ȡ�ɾ�������
	aeSoulShieldAct,	//�������꣨���ģ�
	aeNeiGongActive,	//�ڹ�����
};	

/*
	����ļ�����������صĵ�������
*/
//�������͵Ķ���
enum tagFubenMode
{

    fmCommon = 0,	//��ͨ����
    fmSingle = 1,	//���˸���
    fmTeam = 2,		//��ͨ���鸱��
    fmTeamHero = 3,	//Ӣ�۶��鸱��
    fmGroup = 4,	//��ͨ�ŶӸ���
    fmGroupHero = 5,	//Ӣ���ŶӸ���
    fmJd = 6,			//ר�����ھ��͵ĸ���
    fmMaxCount,
};

enum tagTeamStatus
{
    tsCommon = 0,
    tsReady = 1,	//�ڴ������飬�ȴ����븱����״̬
    tsWar = 2,		//�Ѿ����븱����ս����
};

//���ﶨ�帱�������ͣ������鸱������̨������
enum tagFubenType
{
    ftCommon = 0,	//��ͨ���������ر�����ĸ���
    ftChallenge = 1,	//��̨����
    ftWedding = 2,		//��鸱��
};

enum tagFreePkMode
{
    //��ƽģʽ
    fpPeaceful = 0,
    //�Ŷ�ģʽ
    fpTeam,
    //����ģʽ
    fpGuild,
    //��Ӫģʽ
    fpZY,
    //ɱ¾ģʽ
    fpPk,
	//����ģʽ
	fpAlly,
    //����ģʽ
    fpUnion,
	//����ģʽ
	fpServer,
	//����ĺ�ƽģʽ
	fpSpecialPeaceful,

    fpCount,
};

//��������
enum tagAwardType
{
    qatItem = 0,           //��Ʒ����װ��
    qatRootExp = 1,	            //����
    qatExp = 2,                	//��ɫ����ֵ
    qatGuildContribution = 3,	//���ɹ���ֵ
    qatZYContribution = 4,		//��Ӫ����
    qatBindMoney = 5,           //������
    qatMoney = 6,	            //����
    qatBindYuanBao = 7,	            //��Ԫ��
    qatTitle = 8,	            //��ν
    qatSkill = 9,	            //����
    qatShengWang = 10,	        //����
    qatRenown = 12,              //����
    qatPet = 13,                 //��������
    qatStone = 14,				// ������ʯ
    qatYuanbao = 15,			// Ԫ��
    qatHonor = 16,				//����ֵ
	qatCrossHonor = 17,			// �������ֵ
    qatCount ,					// ��������

    qatCustomize = 127,		    //�Զ��影��
};

//���ɵ���ز���
enum tagGuildOP
{
    gUseCallItem = 1,		//ʹ���ټ���
    gUpLevel = 2,			//��������
    gLeft = 3,				//�뿪����
};

enum StarEventType
{
    seGiveUp = 1,	// �����¼�
    seFinish = 2,	// ����¼�
    seTimeout = 3, // ��ʱ
    seAddQuest = 4, // ��������
	seCanFinish = 5, // �������Ŀ�꣬�����������
	seShowAccept = 6, // ��ʾ�ɽ�����
};

enum eRrchargeType
{
	eRrchargeType_NULL = 0,
	eRrchargeType_FIRST = 1, //�׳�
	eRrchargeType_NORMAL = 2, //������ֵ
	eRrchargeType_MONTHCARD = 3,//�¿���ֵ
	eRrchargeType_PRIVIMONEY = 4,//��Ȩ��ֵ
	eRrchargeType_LIMITPACKAGE = 5,//��ʱ�����ֵ
	eRrchargeType_ACTIVITY = 6,//������ֵ
};
//tolua_end

