#ifndef _SYSTEM_PRARM_DEF_H_
#define _SYSTEM_PRARM_DEF_H_

using namespace InterSrvComm::DbServerProto;

//������һЩϵͳ�Ĳ����Ķ��壬����ְҵ��ID,���ɵ�id,ʵ�����͵ȵ�
//tolua_begin


//��ʵ�����Ͷ���
#define MAX_ROLE 3
#define MAX_ACTOR_LEVEL 200  //��ҵ����ȼ�
#define ZHUAN_SHENG_BASE_LEVEL 80	// ת�������ȼ�

#define PACK_LEN 50000 //�ְ�����
enum EntityType
{
	EntityType_Actor = 0,	//��ҳ���ʵ��
	EntityType_Role,		//��ҽ�ɫʵ��
	EntityType_Monster,
	EntityType_Npc,        // ��ʱ���script_npc�ļ��������⣬�Ժ��ٸ�
	EntityType_CloneRole , // ��¡�ӽ�ɫ
	EntityType_GatherMonster, //�ɼ���
	EntityType_DropBag,		//������

	EntityType_Count,
};

enum FuBenType
{
	FuBenType_Chapter = 1,
	FuBenType_PublicBoss = 7,
	FuBenType_Pata = 9, //ͨ����,����
	FuBenType_WorldBoss = 10,
	FuBenType_HomeBoss = 17,
	FuBenType_City = 20,//����
};

enum JobType
{
	JobType_None = 0,
	JobType_Warrior = 1,//սʿ
	JobType_Mage = 2,//��ʦ
	JobType_Taoist = 3,//��ʿ

	JobType_Max,
};

enum AwardType
{
	AwardType_Numeric  = 0, // ��������
	AwardType_Item	   = 1, // ����
};

enum CurrencyType
{
	NumericType_Exp				= 0, 
	NumericType_Gold			= 1, // ���
	NumericType_YuanBao			= 2, // Ԫ��
	NumericType_Fame			= 3, // ����
	NumericType_Essence			= 4, // ����
	NumericType_GuildContrib	= 5, // ���ṱ��
	NumericType_GuildFund		= 6, // �����ʽ�
	NumericType_Feats           = 7, // ��ѫ
	NumericType_Achieve			= 8, //�ɾͻ���
	NumericType_Shatter = 9, //������Ƭ
	NumericType_SpeShatter = 10,//���������Ƭ
	NumericType_Togeatter = 11, //�͵ȼ��ϻ�װ����Ƭ
	NumericType_TogeatterHigh = 12, //�ߵȼ��ϻ�װ����Ƭ
	NumericType_GodWeaponExp = 13,	//�������
	NumericType_PrestigeExp = 14,	//��������
	NumericType_Chips = 15,//����
	NumericType_ShenShouExp = 16,	//���޾���
	NumericType_VipExp	= 17,//vip����
	NumericType_SkillExp = 18, //����������
	NumericType_Recharge = 99, // ��ֵԪ��
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
	EquipType_Weapon = 0,//����
	EquipType_Helmet,//1.ͷ��
	EquipType_Coat,//2.�·�
	EquipType_Necklace,//3.����
	EquipType_Wrist,//4.����
	EquipType_Belt,//5.����
	EquipType_Ring,//6.��ָ
	EquipType_Shoes,//7.Ь��
	EquipType_Dzi,  //8.��ӡ
	EquipType_Hats,  //9.����
	EquipType_Mark,  //10.���
	EquipType_Cloak,  //11.����
	EquipType_Shield,  //12.����
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
	RankingType_Power = 0,//0.��ս�����а�
	RankingType_Arena,//1
	RankingType_Skirmish,//2
	RankingType_ChapterLevel,//3
	RankingType_ChallengeLevel,//4
	RankingType_Level,//5
	RankingType_Wing,//6
	RankingType_Warrior,//7 սʿ��
	RankingType_Mage,//8 ��ʦ��
	RankingType_Taoistpriest, //��ʿ��
	RankingType_Train,
	RankingType_TianTi,
	RankingType_Zhuling,//12.�����ܵȼ���
	RankingType_ZhanLing,
	RankingType_LoongSoul,//14.�����ܵȼ���
	RankingType_Knighthood,
	RankingType_WingLv,//16.����ܵȼ���
	RankingType_TuJianPower,//17.ͼ����ս��
	RankingType_ZhuanSheng,//18.ת����
	RankingType_EquipBasePower,//19.װ��������
	RankingType_Stone,//20.��ʯ(����)�ܵȼ���
	RankingType_ConsumeYB,
	RankingType_Prestige, //�������а�
	RankingType_TeamLike,//����ֵ���а�
	RankingType_Count,
	RankingType_Recharge,//��ֵ���а�
	//RankingType_subactivitytype4_16,
};


enum AttrSystemId
{
	asStart = 0,
	asEnhance = asStart,		//ǿ��
	asZhuling,			//ע��
	asStone,			//��ʯ
	asLongSoul,		//����
	asShield,			//����
	//asxueyu,          //Ѫ��
	asHeartMethod,  //�ķ�
	asHunGu,  //���
	asCount,
};

//actor
enum AttributeId
{
	attrStart = 0,
	attrTuJian = attrStart,//ͼ��ϵͳ����
	attrFlameStamp,  //����ӡ��
	attrZhanLing,  //ս��
	attrShenShou,  //����ϵͳ
	attrMax,
};

enum RoleMoveLineStatus
{
	MOVELINE_NORMAL,//��ʼ״̬
	MOVELINE_SEND_REQUEST,//��֪ͨ�ͻ��˼����ƶ���·
	MOVELINE_DATA_PREPARE,//�յ��ͻ��˼�����ƶ���·
};

/***********�����Ǿɶ���*********/
/*
enum ActorJobDef
{
	enVocNone = 0,    // ��ְҵ
	enVocTL = 1 ,   // սʿ
	enVocSS = 2,	// ����
	enVocYY = 3, // ��ʦ
	enMaxVocCount,  //����ְҵ����
	ActorJobCount = enMaxVocCount - 1,
};*/

// �������ֵ��ң�������Ϸ���������Ӫ
enum CampType
{
	CampType_None		= 0,	// û����Ӫ
	CampType_Player,
	CampType_Count,
};

enum CampBattleType
{
	CampType_CampBattle_Ice = 1,		//��Ӫս����Ӫ
	CampType_CampBattle_Fire = 2,		//��Ӫս����Ӫ
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

//������ؽ�����
enum ActorExRingType
{
//	ActorExRingType_MabiRing = 0,
//	ActorExRingType_HuShenRing = 1,
	ActorExRingType_HuoYanRing = 7,
	ActorExRingType_MAX = 8,
};

#define MALEACTOR  0 //���Խ�ɫ
#define FEMALEACTOR 1 //Ů�Խ�ɫ

#define MAX_FUBEN 512	// ��󸱱�����

#define MAX_REINCARNATION 4 //���ת����

#define INT_MAX_NUM 2147483647 //INT���ֵ

#define MAX_WING_SKILL_STORE 100



//ʵ�����Ͷ��� todo �Ժ�ɾ��
enum tagEntityType
{
	//��Щ�Ƕ���
	enActor = 0,     //���
	enMonster = 1,  //�������ս������
	enNpc = 2,	//NPC,�̳���Monster���лỰ����,ս������
	enMovingNPC = 3, //Ѱ·�Ĺ֣��̳���NPC,�������������лỰ,ս������,Ѱ·����
	enPet = 4,	//����
	//��Щ�������еķǶ���
	enTotom = 5, //ͼ��
	enDropBag = 6,  // �������
	enDefender = 7, //������ʩ,�ɼ�����
	enPlant = 8, //ֲ��,�ɼ�����

	//��������������ţ�����������Ч����
	enTransfer = 9 ,  //������
	enBuilding = 10, //����
	enEffects = 11,  //��Ч��������˺��Ե�һЩ��Ч

	enGatherMonster = 12, // �ɼ���
	//enDisplayMonster = 13, // ��ʾ�֣�

	enClonePet = 15, // ���Ƶĳ���
	enScriptNpc = 16,	// �ű�NPC
};

//��Ǯ�����͵Ķ��� todo delete
enum eMoneyType
{
	mtBindCoin = 0,       //���ɽ��׵Ľ�Ǯ������ϵͳ������һЩ��Ǯ
	mtCoin = 1,			 //�ɽ��׵Ľ�Ǯ��������ȷ��͵Ľ�Ǯ
	mtBindYuanbao = 2,    //���ɽ��׵�Ԫ����һ����ϵͳ������
	mtYuanbao = 3,		 //�ɽ��׵�Ԫ������ҳ�ֵ�һ���

	mtMoneyTypeCount,
	mtMoneyTypeStart = mtBindCoin,
};

enum eFubenType
{
	ftStatic = 0,			//��̬����
	ftChapterBoss = 1,		//�½�BOSS
	ftMaterial = 2,			//���ϸ���
	ftRetain1 = 3,			//������������1
	ftRetain2 = 4,			//������������2
	ftRetain3 = 5,			//������������3
	ftPersonalBoss = 6,		//����BOSS
	ftPublicBoss = 7,		//ȫ��BOSS
};

enum eSoulShieldType
{
	ssLoongSoul = 1,		//����
	//ssShield = 2,			//����
	//ssXueyu = 3,            //Ѫ��
};

//enum tagMonsterKind
//{
//    mk_Normal = 1,			// ��ͨ��
//    mk_Boss,				// ��Ӣ��
//    mk_GatherMonster,		// �ɼ���
//};


//����Ƶ����ID����, ����������йأ���Ҫ�޸�
enum tagChannelID
{
	ciChannelSecret = 0, // ˽��,����
	ciChannelNear = 1,  // (ȡ��������Ƶ����ͬ��
	ciChannelWorld = 2, // ����Ƶ��
	ciChannelGuild = 3, // ���ᣬ����
	ciChannelTeam = 4, // ����Ƶ��,5��
	ciChannelBigTeam = 5, // �Ŷ�,20��
	ciChannelMap = 6,  // ��ͼ������ͼ�ɼ�
	ciChannelAll = 7, // ȫ������(����)
	ciChannelCamp = 8, // ��ӪƵ��
	ciChannelSystem = 9,		// ϵͳƵ��
	ciChannelKuafu = 10,	//�������
	ciChannelSos = 11,	//���Ƶ������ʱû�õ���
	ciChannelCosign = 12,	//����Ƶ��
	ciChannelLianfu = 13,	//����Ƶ��
	ciChannelMax = 14,		// ���Ƶ����
};

//ϵͳ��ʾ������
enum tagTipmsgType
{
	ttInvalidTmType = -1, // ��Ч��Tipmsg����
	ttTipmsgWindow = 1, //���½���ʾ��
	ttScreenCenter = 2, //��Ļ����(2�Ź�����)
	ttDialog = 4,     //������
	ttHearsay = 8, // ��Ļ���룬����Ʈ��������ʾ
	ttMessage = 16,	//����Ʈ������������
	ttWarmTip  = 32,  //��ܰ��ʾ
	ttGmTip = 64,	// Gm��ʾ��Ϣ
	ttChatWindow = 128, //��������������һЩϵͳ��������������ʾ
	ttScreenMarquee = 256, //��Ļ����������(1�Ź�����)
	ttScreenCenterDown = 512,  //��Ļ�����·�������������Ч��
	//ttMaxTmType,		// ���Tipmsg����
};


//�򿪽�ɫ���Դ���ID����
enum tagOpenDialogID
{
	diItem = 0,	//��Ʒ����
	diActor = 1,	//��ɫ���Դ���
	diQuest = 2,	//����
	diSkill = 3,	//����
	diStrong = 4,	//ǿ��
	diGuild = 5,	//����
	diSell = 6,		//����
	diSystem = 7,	//ϵͳ
	diStore = 8,	//�̳�
	diNormalFuben = 9,//��ͨ������ڴ���
	diFubenList = 10,//�г����еĸ�������Ĵ���
	diBuyAnItem = 11,//��ʾĳ����Ʒ�Ĺ��򴰿�
	diFuncDia = 12,		//��ʾ�Զ��幦�ܴ��ڣ������Ĳ���Ϊ�ַ�����������ť����
	diMemoDia = 13,		//һ���ı����ݵĶԻ���"����,����"
	diRenown = 14,	//�����̵�
	diStartPlay = 15,//��ʼ��Ϸ��֪ͨ���ܵ�һ����������
	diRefreshTask = 16, // ����ˢ�Ǵ���
	diQuickTelport = 17, // �ٴ���ʾ��
	diDepot = 18,		// ��Ҳֿ�
	diProtection = 19,	// ��������
	diProtectionTips = 20,	// ����������ʾ
	diTianYuanInfo = 21, // ��Ԫ֮ս������ܽ���
	diFlower = 22,	// �����ʻ�����
	diLiudao = 23,	//�����������˴���
	diPayGuid = 24,	// ��������
	diAwardToDepot = 25, // ���������ŵ��ֿ���ʾ����
	diLotterySY = 26,	// �齱ϵͳ
	diPet = 27,			// ����������
	diMountTip = 28,	// ������ʾ����
	diGJGuid = 29,		// �һ�����
	diVipCard = 30,		// ʹ��VIP���鿨
	diWorldWar = 31, //����������
	diDigongchuansong = 32,//�򿪵ع�����
	diwyyjLead = 33, //�����ż�����ָ��
	diMarryMarch = 34,	// ���ϵͳ��Ѳ�ν���
	diNpcDialog = 35,   // npc�Ի���
	diZhuanShengTips = 36, //ת��tip
	diEqsign = 37, //���̽���
	diQualitySign = 38, //������Ʒ����
	diExclusiveSign = 39, //װ��ר������
	diZhuanZhi = 40,	//תְ����
	diMount = 41,		//����ι��
	diEscort = 44, //��Ů�o��
	diRoutineQuest = 45, //�ճ�����
	diZhengBa = 46, //������
	diJingjie = 47, //���縱��
	diQuestions = 49, //��������
	diBuyVip = 50,//�����𴰿�
	diPetJingJie = 51, //�򿪳��ﾳ��
	diInvestgate = 52,	//Ͷ��
	diBuyPetSkill = 53,	//�������Ⱥ������
	diZhuMoDian = 54, //��ħ���淨
	diFirstCharge = 55, //�׳�
	diRaiders = 57,	//��ң����	
	diTreasureofGold = 58, //�۱��ɽ�
	diFengQiangliBao = 59,//�������
	diCangbaoge = 60,	//�ر���
	diRabbit = 61,	//�����棬������ʾ�ĸ�С�
	diSmashingEggs = 62, //����ҵ�
	diAnHeiShendian = 63, //�������
	diAnHeiShendianMain = 64, //�������
	diMarry = 67, //��������
	diDivorce = 68, //��������
};

//��ҵĹ���ְλ
enum tagGuildPos
{
	smGuildCommon = 0,			//��ͨ��Ա
	//smGuildJy = 1,				//��Ӣ(��)
	//smGuildTz = 2,				//����(��)
	//smGuildHufa = 3,			//����(��)
	smGuildZl = 1,				//����
	smGuildAssistLeader = 2,	//������
	smGuildLeader = 3,			//����
};

//����������Ϣ����
enum tagGuildChatLogType
{
	enGuildChatSystem = 0,
	enGuildChatChat = 1,
	enGuildChatShow = 2,
};



// ���﷢�Թ㲥����
enum MonsterSayBCType
{
	mssInvalid,		// ��Ч�㲥����
	mssNear,		// �����㲥
	mssScene,		// �����㲥
	mssFuben,		// ����
	mssWorld,		// ����
	mssCamp,		// ��Ӫ�㲥
	mssNearScene,  //ͷ���ӳ���
	mssScreencenter, //��Ļ���м�

	mssSelf = 10,       //�����Լ�,�߻�������..
	mssMax,
};

enum MonsterSayPos
{
	mspLt = 0,		//����Ƶ��
	mspHead,			//����ͷ��
	mspCenter,		//��Ļ���м�
};

// VIP����
enum enVIPType
{
	enVIPRedDiamond,			// VIP ����
	enVIPBlueDiamond,			// VIP ����
	enVIPYellowDiamond,			// VIP ����
	enVIPTypeMax
};

// һЩ��������
enum enMiscDataType
{
	enMiscData_AddCampDailyTaskCount,	// ������Ӫ�ճ��������
	enMiscData_AddDailyTaskCount,		// �����ճ��������(����Ӫ)
	enMiscData_VIPXiuWeiAdd,			// VIP�޸�����ֵ
	enMiscDataMax
};

// ����״̬���Ͷ���
enum enGemStatus
{
	enGemStatusIdle,			// ���ﴦ����Ϣ״̬
	enGemStatusEquip,			// ���ﱻװ��
	enGemStatusRide,			// ���ﱻ���
	enGemMax
};

// �����������Ͷ���
enum enGemSpriteCharType
{
	enGemSpriteCharAttack,		// ��������  + ����
	enGemSpriteCharDefence,		// ��������	 + ����
	enGemSpriteCharAgility,		// ��������	 + ���ܡ�����
	enGemSpriteCharHP,			// ��������	 + ����������
	enGemSpriteCharMax
};


//�������Ͷ��壬����namespace DataPack
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
	dtPointer = 9,	// ָ������
	dtItem = 10,	// ��Ʒ��ָ��
	dtDouble = 11,
};

/*
*ʵ���״̬
*״̬�ǳ����Եģ������������������������̯
*Ҳ������һ�����̵�
*/
enum tagEntityState
{
	esStateStand = 0 , //��ֹ״̬
	esStateMove = 1,  //����״̬������Ծ״̬
	esStateRide = 2, //����״̬
	esStatePratice = 3, //����״̬
	esGather = 4,  //�ɼ�״̬
	esStateUnderSunshade = 5,//̫��ɡ��
	esStateBattle = 6, //ս��״̬
	esStateDeath = 7, //����״̬
	esStateMoveForbid = 8, //��ֹ�ƶ�״̬,buff���õ�
	esStateDizzy = 9,   //��ѣ״̬
	esStateAutoBattle = 10, //�һ�״̬
	esStateReturnHome = 11, //�ع�״̬(���ڹ���)
	esDisableSkillCD = 12, //���ü���CD��־�������Ͳ����ã�
	esChallenge = 13,		//��̨״̬
	esNewCreate = 14,	// �Ƿ��һ�γ��֣�����ĳЩ���ֵ���Ч��������������
	esStateDoubleSunBach = 15,	//�Ƿ�˫�ޣ�����ɳ̲��
	esStateAttackedForbid = 16,	// ��ֹ������
	esShowBossName = 17,		// ͷ����ʾbossͼƬ
	esNoTitle = 18,				// ����ʾ�ƺ�
	esJump = 19,				// ��Ծ״̬
	esMasterEquip = 20,			// װ������Ԫ����װ��
	esProtection = 21,			// ��������״̬
	esPkState = 22,				// �����pk״̬
	esPetState = 23,			// ����״̬�������г������Ϊ����
	esDenyRefreshModel = 24,	// ��ֹˢ�����
	esStateSunBath = 25,	//�չ�ԡ
	esStateHideForbid = 26, //��ֹ����
	esStateInSandBeach = 27, //������ɳ̲������
	esStateImprison = 28, //����״̬
	esStateHide = 29,    //����״̬
	esStateVest = 30,	//���������
	esStateJiuShiZhu = 31, //������״̬
	esReLive = 32, //����

	esMaxStateCount, //״̬������
};

enum EntityBitState
{
	ebsSuperman,		// �Ƿ�superman
	ebsNoAnger,			// �Ƿ񲻼�ŭ��ֵ
	ebsAttackLog,		// �Ƿ��¼�����б�
	ebsHpEvent,			// �Ƿ񴥷�Ѫ���ı�ű��¼�
	ebsTotem,			// �Ƿ�ͼ�ڹ�
	ebsGm,				// �Ƿ�gm
	ebsVestEvent,   //�Ƿ񴥷���������¼�

	ebsMaxStateCount,	// ����
};

enum spiritFashionType
{
	sftMin = 0,
	sftCount = sftMin,//�ռ�����
	sftStrong = 1,//ǿ������
	sftBless = 2,// ף��ֵ
	sftOutTime = 3,//����ʱ��

	sftMax,
};

//��ҵ�״̬
enum tagActorState
{
	esFishingNormal = 0, //��ͨ����
	esUsingOtherHp = 1, //����Ѫ��״̬
	esHaveSunshade = 2,//ӵ��ɡ
	esAvenger = 3, //������
	esGearsOfWar = 4,//ս������
	esChangeModel = 5, //����״̬

	esMaxActorStateCount, //״̬������
};

//����ͳ����
enum caletype
{
	caleExp = 0,   //����ֵ����
	caleCoin = 1, //��������
	caleBindCoin = 2, //�ɱ�
	calelingli = 3, //����ֵ,ֻ�ʺ����ⲿ����
	caleFubenTime = 4,//����ʱ��
	caleMonTime = 5,//ˢ��ʣ��ʱ��
	caleOther1 = 6, //���� ��ɼ��������ֵ
	caleOther2 = 7, //����
	caleOther3 = 8, //����
	caleRemainMonster = 9, //ʣ�������
	caleGameTime = 10,//������Ϸʱ��
	caleLiLiang = 11, // ����
	caleSceneExp = 12, // ��������õľ���
	caleHonor = 13, //����ֵ
	caleOther4 = 14, //����
	caleOther5 = 15, //����
	caleOther6 = 16, //����
	caleOther7 = 17, //����
	caleOther8 = 18, //����
	caleOther9 = 19, //����
	caleOther10 = 20, //����
	caleMax,
};

// �Ŀ������

enum ActivityTarget
{
	enRoutineQuest = 0,		// �ճ�����
	enGuildTask,		// ��������
	enGuildDice,		// ����ҡ����
	enGuildAnimal,			// ι����������
	enGiveFlower,			// �����ʻ�
	enExploreSecret,		// ̽���ز�
	enWushenTai,			// ��ս����̨
	enCorpse,		// ���б�ʬ
	enEscort,		// ������Ů
	enFish,			// ���е���

	enWanyaoyiji,			// �����ż�
	enBagua,		// ���Ը���
	enHolybeast,			// ��ʥ�޸���
	enLoveFuben,			// ���¸���
	enNirana,			// ���鸱��
	enMoneyFuben,			// ��Ҹ���
	enPetsave,		// ���︱��
	enQqshFuben,			// �����黭����
	//enATZaiXian, //����2Сʱ

	enATMax,			// ���ֵ
};

// �������ݱ���λ��
enum tagGuildValue
{
	gvLastCallSL = 0,	// ���һ���ٻ������ʱ��
	gvGuildMax,
};

// ÿ��ϵͳ��id���壬��Ҫ�����ж�ϵͳ�Ƿ񿪷�
// ����ͷ����Ķ��岻�ܸģ����ݿ�����а����õ�
enum tagSystemId
{
	siMount = 0,	// ����
	siGem = 1,		// ����(����)
	siGuildSys = 2,	// ����
	siEquipStrong = 3, // װ��ǿ��
	siSkillSystem = 4, //���ܼ�ϵͳ
	siWorship = 5,		// ����
	siSkill = 6,		// ��ɱ��
	siPractice = 7,    //����
	siRoot = 8,	// ���
	siDujie = 9,	// �ɽ�
	siOneKeyFriend = 10,	// һ������
	siExchange = 11,		// �һ�
	siWing = 12,  //���
	siPet = 13,		// ����ϵͳ
	siFightSys = 14,	// ������
	siZhuMoDian = 15,	// ��ħ��
	siMarry = 16,	// ���ϵͳ
	siMijiSys = 17,		//�ؼ�ϵͳ
	siArtifact = 18,	// ����
	siFashionDeal = 19,  //ʱװ����
	siWingShenTong = 20, //�����ͨ
	siWingSkill = 21, //�����
	siMountSkill = 22, //���＼��
	siMountStage = 23, //������� (������ֱ�ӿ���)
	siSpiritSoul = 24, //����Ԫ��
	siFriendSys = 25, //����ϵͳ
	siXunBao = 26,	  //Ѱ��ϵͳ
	siDayQuest = 27,  //�ճ�����ϵͳ
	siLoopTask = 28,  //�ܻ�����ϵͳ
	siDailySign = 29, //ǩ��
	siGemStone = 30, // ��ʯ����
	siShenZhuang = 31, //��װ
	siSysMAX,
};


// ��������id����
enum
{
	PI_ID		   = 0,	// id
	PI_MONSERID	   = 1,	// ����id������ʵ����Ҳ�Ǹ������
	PI_HP		   = 2,	// ����ֵ
	PI_LEVEL	   = 3,	// �ȼ�
	PI_FIGHT_TYPE  = 4,	// ս������
	PI_HP_STORE	   = 5,	// Ѫ��
	PI_EXP		   = 6,	// ����8�ֽڼ���64λΪPI_EXP��PI_EXP1
	PI_EXP1		   = 7,
	PI_AMBIT	   = 8,// ���� ��16λ�׼�, ��16λ����
	PI_QUALITY_LV  = 9,// ���ʵȼ�
	PI_QUALITY_EXP = 10,// ���ʾ���
	PI_TYPE		   = 11,// ��������, ��2�ֽڱ���ԭʼ�ĳ�������ֵ����2λ���滯�κ�ĳ�������ֵ
	PI_ATTACK_TYPE = 12,// ��������
	PI_TITLE_AMBIT = 13,// ����ƺ�
	PI_TITLE_QUALITY  = 14,// ���ʳƺ�
	PI_NATURE      = 15,// �����Ը� ��16λ�ĸ�8λ����8λ�洢��ˢ�³����Ը�A��B ��16λ�ĸ�8λ����8λ�洢��ǰ�Ը�A��B

	// �����ǳ����ս������, ע�����´���Ҫ�Ķ�
	PI_ATTACK		      = 16,// ����
	PI_MAGIC_DEFEN	      = 17,//����
	PI_PHY_DEFEN		  = 18,// ���
	PI_CRITICALSTRIKES    = 19,// ����
	PI_HITRATE			  = 20,// ����
	PI_DODGERATE		  = 21,// ����
	PI_DEFCRITICALSTRIKES = 22,// ������
	PI_HP_PRO			  = 23,// ����

	// ��������
	PI_AMBIT_ATTACK			 = 24,	// ����
	PI_AMBIT_MAG_DEFEN		 = 25,	// ����
	PI_AMBIT_PHY_DEFEN		 = 26,	// ���
	PI_AMBIT_CRITICALSTRIKES = 27,	// ����
	PI_AMBIT_HITRATE		 = 28,	// ����
	PI_AMBIT_DODGERATE		 = 29,	// ����
	PI_AMBIT_DEFCRITICALSTRIKES = 30,// ������
	PI_AMBIT_HP				 = 31,	// ����

	// �������ʣ�������ڳ����ʼ�͹̶�
	PI_QUA_BASE_ATTACK			= 32,	// ����
	PI_QUA_BASE_MAG_DEFEN		= 33,	// ����
	PI_QUA_BASE_PHY_DEFEN		= 34,	// ���
	PI_QUA_BASE_CRITICALSTRIKES = 35,	// ����
	PI_QUA_BASE_HITRATE			= 36,	// ����
	PI_QUA_BASE_DODGERATE		= 37,	// ����
	PI_QUA_BASE_DEFCRITICALSTRIKES = 38,// ������
	PI_QUA_BASE_HP				= 39,	// ����

	PI_FIGHT_VALUE  = 40,	// ս����
	PI_SKILL_SLOT   = 41,	// ���ܲ�
	PI_TOTAL_MAX_HP = 42,	// ����ʵ�ʵ����Ѫ����

	PI_PROP_MAX		= 43,

	//�������ﲻ��֪ͨ�ͻ���
	PI_REAL_QUA_ATTACK = PI_PROP_MAX, //���﹥��������
	PI_REAL_QUA_MAG_DEFEN		= 44,	// ����
	PI_REAL_QUA_PHY_DEFEN		= 45,	// ���
	PI_REAL_QUA_CRITICALSTRIKES = 46,	// ����
	PI_REAL_QUA_HITRATE			= 47,	// ����
	PI_REAL_QUA_DODGERATE		= 48,	// ����
	PI_REAL_QUA_DEFCRITICALSTRIKES = 49,// ������
	PI_REAL_QUA_HP				= 50,	// ����


	PI_MAX,
};

//���＼��λ��
enum PET_SKILL_DB_TYPE
{
	PET_SKILL_BAR	 = 1,// ����������
	PET_SKILL_STORE  = 2,// �ֿ⼼��
	PET_SKILL_SLOT = 3,// ˢ�²�
	PET_SKILL_BOOK = 4, // ������
};

// ��־�����־
enum tagLogFlag
{
	lfDB = lfiDB,	// �������ݿ�
	lfBI = lfiBI,				// ���浽BI
	lfText = lfiText,			// ���浽�ı�
	lfIsPay = lfiIsPay,			// �Ƿ��ֵ����
	lfNormal = lfDB + lfBI + lfIsPay, // Ĭ�ϱ��浽���ݿ��BI
};

enum itemPos
{
	ipStart = 0,
	ipBag = ipStart,
	ipDepot,      //��Ҳֿ�
	ipLottery,    //�齱�ֿ�
	ipEntrust,	  //ί�вֿ�
	ipTreasure,	  //�䱦��
	ipBabel,	  //ͨ�����ֿ�

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
	acSpiritFashion,//����ʱװ
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
	acSpiritFashionStrong,//����ʱװǿ��
	acEquipMelt, //װ������
	acXiaoyaoEquip,	//��ң��װ
	acRingStage, //������
	acRingCl,		//������
	acZsheng,		//ת������
	acShenZhuangHead,	//��װͷ��
	acShenZhuangHand,	//��װ�ֻ�
	acShenZhuangShoulder,	//��װ���
	acShenZhuangKnee,	//��װϥ��
	acArtifact,		//��������
	acEqRefine, //װ����������
	acMax,
};

enum DbSystemId
{
	dbDefault = siDefault,	//��������
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

// ʹ��Ԫ���۷Ѻ�Ļص�����
//enum tagYBPayType
//{
//    yptStore = 1,		// �̳ǹ���
//    yptAddFbCnt = 2,	// ���Ӹ����Ĵ���
//    yptLargeBag = 3,	// ��չ����
//    //ypt
//};

// ���븱����ʽ
enum tagEnterFbWay
{
	efwNone = 0,		// ������ʽ
	efwNormal = 1,		// ��������
	efwRelogin = 2,		// ��������
};

// �˳�������ʽ
enum tagExitFbWay
{
	xfwNone = 0,		// ������ʽ
	xfwNormal = 1,		// �����˳�
	xfwLogout = 2,		// ����
	xfwReturnCity = 3,	// �س�
	xfwTeleport = 4,	// ������
};

enum tagActivityEvent
{
	eaeUpgradeGuild = 1, //��������
	eaeUpgradeEquip = 2, //װ������
	eaeUpgradeCross = 3, //�ɽ�
};

enum tagPetSkillEff
{
	pseDizzy = 1, //.XX������
	pseThread = 2, //.XX����
	pseLj = 3,	//.XX����
	pseXx = 4,	//.XX��Ѫ
	pseTs = 5,	//.����
	pseGw = 6,	//.����
	pseTl = 7,	//.����
	pseFss = 8, // ������

	// 100����Ϊ����ļ���
	pseNgs = 100,	// Ů�ʯ
	pseKlj = 101,	// ���ؾ�
	pseDhz = 102,	// ������
	pseFty = 103,	// ����ӡ

	pseMiji = 200,	// �ؼ�
};

enum fightValueType
{
	eEquipBase = 1,		//װ����������ս����
	eEquipStone = 2,	//װ����ʯ����ս��
	eEquipStrong = 3,	//װ��ǿ������ս����
	eEquipsTage = 4, //װ������
	eEquipQuality = 5,//װ����Ʒ
	eEquipBaptize = 6, //װ��ϴ��
	eMountHunger = 7, //����ι��
	eMountSkill = 8,//���＼��
	eMountStage = 9, // �������
	eMountAppearance = 10, //����û�
	eShenZhuangHead = 11,	//��װͷ��ս��
	eShenZhuangHand = 12,	//��װ�ֻ�ս��
	eShenZhuangShoulder = 13, //��װ���ս��
	eShenZhuangKnee = 14, //��װϥ��ս��
};

/** ����buff�ķ������ **/
enum BuffGroup
{
	bgSystemBuff = 0,		//ϵͳĬ�ϵ�BUFF��
	bgSkillBuff = 1,		//����ϵͳĬ�ϵ�BUFF��
	bgDisplayBuff = 2, //��չʾʹ�ã����ߺ�ɾ��
	bgSceneBuff = 3, //����BUFF, ���л������󽫻�ɾ������BUFF
	bgFubenBuff = 4, // ����BUFF�����˳�������ɾ������BUFF
	bgManualBuff = 5, //BUFF��ɾ����Ҫ�Լ�д�߼����Ƶ�������
	bgGuildAnimal = 6,//��������buff(����Ҫ��)
	bgGearsOfWar = 7,//ս������BUFF��
	bgUserBuffMin = 32,		//�����ɿ������Զ����BUFF�����ʼֵ
	bgSkillBuffMin = bgUserBuffMin, //���ܵ���С��group
	bgHorseSkillBuff = 33,		  //������buff
	bgMountSkillBuff = 34,		  //���ﱻ������buff
	bgSpiritSkillBuff = 35,		  //���鱻������buff
	bgAgainstSkillBuff = 36,	  //�Կ���������buff
	bgPetSkillBuff = 37,		  //���ﱻ������buff
	bgHorseSkillBuff2 = 38,		  //�����ܼ���buff��2��
	bgHorseSkillBuff3 = 39,		  //�����ܼ���buff��3��
	bgSkillBuffMax = 80,          //���ܵ�����group

	bgItemBuffMin,       //��Ʒ����С����
	bgUserBuffMax = 127,	//�����ɿ������Զ����BUFF��Ľ���ֵ
	bgItemBuffMax = bgUserBuffMax,      //��Ʒ������ֵ

	/*�������µ�buff������AnyBuffGroupö��ֵǰ����*/
	AnyBuffGroup = -1,		//����ƥ���κ����е�buff
	MaxBuffGroup = 255,		//buff�������ֵ
};

//����˵��
enum MonsterSayType
{
	mstInvalid = 0,
	mstIdle,				//����
	mstFoundTarget,	//����Ŀ��
	mstAttack,			//����
	mstAttacked,		//������
	mstDead,				//����
	mstHpLow,			//Ѫ�����ڰٷ�֮��
	mstCreate,			//������ʱ��
	mstDisappear,		//��ʧ��ʱ��
	mstMax,
};

enum TeamType
{
	CommonTeam = 0,
	FbTeam = 1,
	LianfuTeam = 2,
	MaxTeamType,
};
/** ���а�洢���������� ����**/
enum rankDataType
{
	rankAllAttack = 0, //���й���
	rankOutDefence, //�������
	rankInDefence, //��������
	rankMaxHp, //�������ֵ
	rankCriticalStrikes, //����
	rankDefCriticalStrikes, //������
	rankHitrate, //����
	rankDodgerate, //����
	rankIntAttack,	//��������
	rankOutAttack,	//������

	rankMaxDataNum, //�������
};
/** ��ң����ս���� ����**/
enum rankCalcType
{
	rdEquipStrong = 1,	//װ��ǿ��
	rdEquipStone,		//װ����Ƕ
	rdEquipQuality,		//װ����Ʒ
	rdEquipStage,		//װ������
	rdEquipBaptize,		//װ��ϴ��
	rdEquipSign,			//װ������
	rdMountFeed,		//����ι��
	rdMountSkill,		//���＼��
	rdMountStage,		//�������
	rdWingLevel,			//�������
	rdWingStage,		//�������
	rdSpiritLevel,			//������ѵȼ�
	rdSpiritSoul,			//����Ԫ��
	rdSpiritFashion,		//����ʱװ
	rdMountModel,	//����û�
	rdWingSkill,			//�����
	rdWingShenTong,	//�����ͨ
	rdWingModel,		//���û�
	rdSpiritSkill,		//���鼼��
	rdTitle,		//�ƺ�
	rdRoot,		//��ͼ
	rdDress,	//װ��
	rdSkill,		//����
	rdPetSkill,	//��鼼��
	rdPetNature,		//����Ը�
	rdPetCross,		//��龳��
	rdPetStar,		//��齫��¼
	rdEquipBase, //װ������
	rdMountEquip,	//����װ��
	rdPetEquip,	//���װ��
	rdWingEquip, //���װ��
	rdEquipExclusive,	//װ��ר��
	rdAchieve, //�ɾ�
	rdJingjieCuiti, //�������
	rdGuildAnimal,	//��������
	rdGuildSkill,	//���ɼ���
	rdPetFeed, //����ι��
	rdShenZhuangHead, //��װ
	rdShenZhuangHand, 
	rdShenZhuangShoulder,
	rdShenZhuangKnee,
	rdEqRefine, //װ������

	rdMax,
};

enum BattleSrvType
{
	bsCommSrv = 0,	// ��ͨ��
	bsBattleSrv = 1,	// ս����
	bsMainBattleSrv = 2,	// ��ս����
	bsLianFuSrv = 3,	//����������
};

enum VestLockType
{
	vlStart = 0,
	vlActorId = 1, //����������ҹ���
	vlGuildId = 2,//�������ǰ��ɹ���

	vlMax,
};

enum crossServerMsgMethod
{
	CROSSSERVER_ALL, //ALL
	CROSSSERVER_CROSSBATTLE, //ս����
	CROSSSERVER_LIANFU,  //����
};


//enum crossServerLoginType
//{
//	CROSSLOGINTYPE_NOTENTERGAME, //��û�н�����Ϸ����,���п��
//	CROSSLOGINTYPE_ENTERGAME, //�Ѿ�������Ϸ���磬�ٽ��п��
//};

// �����½����
enum crossLoginType {
	CROSSLOGIN_CROSSWAR = 1, // ���
	CROSSLOGIN_LIANFU = 2, // ����
};

enum crossServerDataType
{
	dtActorDeal, // ���͸�������Ҵ���
	dtServerDeal, // ���͸�����������
	dtToActor,	// ���͸��������
	dtBroadCast, // �㲥
};

enum MonsterType {
	MonsterType_Normal = 0,//������
	MonsterType_Boss = 1,//boss��
	MonsterType_GatherMonster = 2,//�ɼ���
	MonsterType_Pet = 3,//�����
	MonsterType_AexRing = 4,//�ؽ��
};

//tolua_end

STATIC_ASSERT(siSysMAX <= 32);

#endif

