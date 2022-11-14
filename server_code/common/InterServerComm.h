#pragma once

/****************************************************************************************
* �����֮��ͨ��Э�鶨��                                                   
* �����淶��
* namespace ���������Proto
* {
*    enum eĿ����������Code
*    {
*       //ͨ����Ϣ��ע�ͣ����ݶθ�ʽ���������ƣ��������͡�byte,short,int,shortString,string����
*       c��Ϣ�ű��� = ��Ϣ��ֵ������c��ʾͨ��˫���еĿͻ��˷����ͣ���1��ʼ
*       //ͨ����Ϣ��ע�ͣ����ݶθ�ʽ���������ƣ��������͡�byte,short,int,shortString,string����
*       s��Ϣ�ű��� = ��Ϣ��ֵ������s��ʾͨ��˫���еķ���˷����ͣ���1��ʼ
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
			siDefault = 0,	//��������
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
			dcInitDB = 1,			//��ʼ�����ݿ⣬����ָ��
			dcExecDB = 2,			//ִ��sql���
		};


		/**���ݷ��������߼���������������**/
		// �����ڽű�ʹ�õ��ˣ����Բ�Ҫ�����޸�
		// ע�⣺���ֵ������ڿ��ս�в��ö�ȡ�������Ƕ�ȡ�����ñ���
		enum EntityMgrId
		{
			dcDefault,			//Ĭ�ϴ���0

			// g-d
			dcQuery = 1,		//��ѯ����
			dcSave = 2,			//�������� actors
			dcSaveRole,			// roles
			dcSaveVar,			//���ؽ�ɫ���� actorvariable.variable
			dcSaveItem,			// items
			dcSaveMail,
			dcSaveStore,
			dcSaveTogHitEquip,	//����ϻ�װ��
			dcLogout,			// �������

			// d-g
			dcLoad,
			dcLoadRole,
			dcLoadItem,
			dcLoadMail,
			dcLoadVar,			//���ؽ�ɫ����
			dcLoadStore,		//�����̳�
			dcLoadTogHitEquip, //���غϻ�װ��

			dcLoadFriends = 35,		// ��ȡ���˵ĺ�������б�
			dcUpdateFriend = 36,		// ���º��ѵ���Ϣ
			dcDelFriend = 37,		// ɾ��������Ϣ

			dcLoadMsg = 27,		//��ȡ�û�����Ϣ����
			dcDeleteMsg = 28,			//ɾ��ĳ����Ϣ


			// todo�����Ǿɵģ��Ժ�����ɾ��
			//dcLoadQuest = 3,         //װ����������
			//dcSaveQuest = 4,		//�����û����������ݣ����ս�����棩
			//dcLoadSkill = 5,        //װ�ü�������
			////dcSaveSkill = 6,        //���漼�����ݣ����ս�����棩
			//dcLoadBagItem = 7,      //װ�ر�����Ʒ
			//dcSaveBagItem = 8,      //���汳����Ʒ���� �����սҪ���棬��ΪҪ����ҩƷ��
			//dcLoadEquipItem = 9,    //װ��װ����Ʒ
			//dcSaveEquipItem = 10,    //����װ����Ʒ�����ս�����棩
			//dcLoadDepotItem = 11,    //װ�زֿ���Ʒ �����ս����ȡ��
			//dcSaveDepotItem = 12,    //����ֿ���Ʒ��13�����ս�����棩

			dcLoadBuff = 15,			//���ؽ�ɫbuff������
			dcSaveBuff = 16,			//�����ɫbuff�����ݣ����ս���棬��buffʱ�䣩



			dcAddMember = 23,		//���Ӱ��ɳ�Ա
			dcSaveActorGuild = 24,	//������˰�����Ϣ
			dcDeleteMember = 25,		//ɾ��ĳ����Ա


			dcLoadConsiTimeoutItem = 26,	//��ȡ�Ѿ��¼ܵĸ�����Ʒ		�����ս����ȡ��



			dcLoadSpiritItemData = 29,				// ��ȡ��������
			dcSaveGemItemData = 30,				// ���汦������		�����ս�����棩

			dcLoadMountData = 31,        //װ�����������
			dcSaveMountData = 32,		 //��������ļ�������	�����ս�����棩

			dcSaveDmkjItem = 33,		//����齱�Ĳֿ���Ʒ	�����ս�����棩
			dcLoadDmkjItem = 34,		//��ȡ�齱�ֿ������	�����ս����ȡ��


			dcUpdateFriendInfo = 38,    //���º������ݣ�����ʱ�䣩
			dcUpdateFriendContact = 39,	//���������ϵʱ�䣨���ߵ�ʱ��

			dcSaveCale = 40, //���渱��ͳ�����ݣ����ս����ȡ��
			dcLoadCale = 41, //������ͳ������

			dcLoadFbCountData = 42, // ��ȡÿ����븱���������ݣ����ս����ȡ��
			dcSaveFbCountData = 43, // ����ÿ����븱����������

			// ���鶯��
			dcLoadPlotData = 48,	//�����ս����ȡ��
			dcSavePlotData = 49,	// ������������

			//dcLoadMiscStruct = 50,	// ��ȡ�����Ӱ�����	�����ս����ȡ��
			//dcSaveMiscStruct = 51,	// ���������Ӱ�����

			// ������
			dcLoadFightLog = 55,				// ��ȡPK��¼	�����ս����ȡ��
			dcAddFightLog = 56,				// ���һ��PK��¼

			dcSlaveAll = 57,				// �๤ϵͳ��ص����ݱ��棬�ɽű�����	(ȡ����

			dcDelFightLog = 58,				// ɾ��һ��PK��¼

//			dcLoadMail = 59,		//��ȡ�û����ʼ�����	�����ս����ȡ��
			dcDeleteMail = 60,			//ɾ���ʼ�
			dcUpdateMailStatus = 61,			//�����ʼ�״̬
			dcDeleteMailFile = 62,		//ɾ���ʼ�����
			dcGetActorIdFromActroName = 63, //����������ֻ�ȡ���ID

			dcSaveEntrustItem = 64,		//���渱��ί�еĲֿ���Ʒ	�����ս����ȡ��
			dcLoadEntrustItem = 65,				//��ȡ����ί�вֿ������

			dcSaveActorMisc = 68,		// ���������Ӱ˵�����
			dcLoadActorMisc = 69,		// ��ȡ�����Ӱ˵�����

			dcSavePetCrossItem = 70,		//������ﴳ�زֿ⣨�䱦�ң������ս�����棩
			dcLoadPetCrossItem = 71,		//��ȡ���ﴳ�زֿ⣨�䱦�ң������ݣ����ս����ȡ��

			dcResetCrossPos = 80,		// ���ÿ��λ��
			dcLoadCrossVar = 81,		//���ؽ�ɫ���ս����
			dcSaveCrossVar = 82,		//�����ɫ���ս����
			dcLoadSkillMiji = 83,      //��ȡ�����ؼ�����
			dcSaveSkillMiji = 84,     //�����ؼ����ݣ����ս�����棩

			dcSaveTongTianTaStoreItem = 85, //����ͨ�����ֿ�(���ս������)
			dcLoadTongTianTaStoreItem = 86, //��ȡͨ�����ֿ�(���ս����ȡ)

			dcSaveWing = 87,		//������
			dcLoadWing = 88,		//��ȡ���

			//�������
			//dcLoadAllPet = 96, // �������г���
			//dcDeletePet	 = 97, // ɾ������
			dcLoadPetBase = 98, // ���س����������
			dcSavePetBase = 99, // ���³���

			dcPetSkill = 100,  // ���＼�����
			//dcLoadPetGotType    = 101,  // ��ȡ�������ʷ��¼�����ս����ȡ��
			//dcAddPetGotType     = 102,  // ���ӳ������ʷ��¼�����ս�����棩
			dcPetLoadEquip = 103,  // ���س���װ��
			dcPetSaveEquip = 104,  // �������װ��

			dcClearActorDbCache = 105, //�����ҵĻ���

			//�������
			dcAddEqSign = 106,//����������Ϣ
			dcInheritEqSign = 107,//�̳��滻������Ϣ
			dcGetEqSignList = 108,//��ȡĳװ���ϵ�������Ϣ

			dcSaveOnceTime = 111, // ���ñ���һ�ε�ʱ��

			dcSaveRankVar = 112, // �������а��������

			dcSetDataValid = 115, // ������Ч�Ա�ʶ
			dcEnableCheckValid = 116, // �Ƿ����ü��������Ч��

			dcLoadActorGuild = 117, //��ȡ��ɫ������Ϣ

			dcSaveMarryInfo = 118,		//��������Ϣ
			dcLoadMarryInfo = 119,		//���ؽ����Ϣ
			dcOfflineLogout = 120,	//����ʱ���Է������ߣ�д���������
			dcOfflineDivorce = 121,	//���ʱ���Է������ߣ�д���������

			dcSaveCsWarVar = 122,			//�����ɫ���ר�ñ���
			dcLoadCsWarVar = 123,			//���ؽ�ɫ���ר�ñ���

			dcActorCacheSave = 124,
			dcActorCacheLoad = 125,

			dcLoadPrivateChat = 126,	// ��ȡ�����¼
			dcAddPrivateChat = 127,		// ���������¼
			dcDelPrivateChat = 128,		// ɾ�������¼
			dcBatchDelPrivateChat = 129,// ����ɾ�������¼
		};

		enum ConsignmentSysId
		{
			dcLoadConsignment = 1,	//��ȡ���еļ�����Ʒ��Ϣ
			dcSaveConsignmentItem,  //���������Ʒ,����ɾ�������
			dcConsignmentCount,		// ������Ʒ����
		};

		enum GuildMgrId
		{
			dcLoadGuildList = 1,	// ��������������а��ɵ�����
			dcLoadGuildDetail,	// ���ɵ���ϸ����
			dcAddGuild,			// ���Ӱ���
			dcDeleteGuild,		// ��ɢ����
			dcSaveGuild,		// ������ɵ���Ϣ
			dcLoadGuildMgrData, // ��ȡ���������б��
			dcLoadGuildDepot,	// ��ȡ���ڲֿ���Ʒ��Ϣ
			dcSaveGuildDepot,	// �������ڲֿ���Ʒ��Ϣ
			dcLoadBeastLog,		// ��ȡ�������޼�¼
			dcAddBeastLog,		// ��Ӱ������޼�¼
			dcDeleteBeastLog,	// ɾ���������޼�¼
			dcLoadGuildLog,		// ��ȡ�����¼�
			dcAddGuildLog,		// ��������¼�
			dcDelGuildLog,		// ɾ�������¼�
			dcLoadOneGuild,		// ����һ�����ɵ�����
			dcGuildCount,		// ��������
			dcSaveGuildVar,		// �����������(��̬����)
			dcLoadGuildVar,		// ��ȡ��������(��̬����)
			dcSaveGuildChat,	// ���湫�������¼
			dcLoadGuildStore,		// ��ȡ�����̵��¼
			dcSaveGuildStore,	   // ���湫���̵��¼
		};

		enum AuctionId
		{
			dcAuctionAdd = 1,
			dcAuctionDel,
			dcAuctionUpdate,
		};

		enum TopTitleId
		{
			dcLoadRank = 1,	//��ȡ�й�ͷ�ε����а�����
			dcLoadRankUser = 2, // �û���ϸ����
			dcLoadRankPet = 3,  //������ϸ����
			dcRankUserCount,	// �û���ϸ���ݵ�����
		};
		enum MsgMgrId
		{
			dcAddMsg = 1,				//�����û�һ����Ϣ

			dcAddChat = 2,				//�����ص���Ϣ
		};
		enum MailMgrId
		{
			dcAddMail = 1,				//�����û�һ���ʼ�
			dcAddMailByActorName,	// �����û�һ����Ϣ��ͨ��������ƣ�
			dcAddMailByAccountName,			// �����û�һ����Ϣ��ͨ��open id��
		};
		enum GlobalMgr
		{
			dcLoadBossKiller = 1,		// ��������boss�Ļ�ɱ��
			dcSaveBossKiller,
			dcLoadMaster,				// ��ȡ��Ԫ֮��װ����Ϣ
			dcSaveMaster,				// ������Ԫ֮��װ����Ϣ
			dcGmCmd,					// ����gm���� ��ʱ�ĵ�lua��ע�ᣬ�Ժ�������ϢʱҪ��
			//dcAllActorBI,				// �����û����ݵ�BIϵͳ�������ã�
			dcCheckVer,					// ���gameworld�İ汾�Ƿ���dbserverһ��
			dcLoadMarry,				// ��ȡȫ����������
			dcAddMarry,					// ����һ������¼

			dcBattleFlag,				// ��ʾ��������Ƿ��ս������������ǣ��򲻶�ȡgmcmd�������

			dcAddQuestion = 10,		//����һ������
			dcLoadQuestions, //��ȡ������е�����
			dcLoadQuestion,	//��ȡĳһ������
			dcUpdateQuestion,	//�������� ���Ķ�

			dcAddBug = 14,	//����һ��bug
			dcLoadGoldRank,	//��ȡ�������

			dcAddGameServerInfo, //���һ��gameworld�����Ϣ
		};
		enum FightRankId
		{
			dcLoadFightRank = 1,		// ��ȡ���������а�
			dcSaveFightRank,			// ���澺�������а�
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
			ctLoadGiftItem = 1,  //��ȡ�����Ϊ��Ʒ������
			ctLoadGiftConfig = 2,		//��ȡ�����������
		};
		

		// ͨ�ŵĴ����붨��
		enum tagResultError
		{
			reSucc = 0,
			reDbErr,		//���ݿ�ִ�д���
			reNoActor,		//û�иý�ɫ��������Ϣ
			reSaveErr,		//��������ʧ��
			reNoLoad,		//��û�ж�������
			reDbNotConnected,  //DB���Ӳ���
			reParamError,      //��������
			reNameError,	//���ֲ��Ϸ�
			reNameInUse,	//���ֱ�ʹ��
			reTimeOut,		//������ʱ
			reInterErr,		//�ڲ�����
		};

		// ս����ϢID
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
			dcLoadOneWarTeam, // ��ȡһ��ս�ӵ���Ϣ
			dcWarTeamCount, // ������Ҫ���ص�ս������
		};

		enum TxApiMsg
		{
			// ��ֵ����
			sFeeCallBack = 1,
			// ��Ѷapi����
			sTxApiMsg = 2,
			// �����û����֤����
			sUpdateIdentity = 4,

			// �رջ����Ĳ�ϵͳ
			sCloseGamble = 5,

			// �û���ֵ��ȡtoken
			sChargeToken = 6,
			// ��ͨ����Ȼ�ȡtoken
			sGetToken = 7,

			//��ֵ���к�
			sAddValueCard = 8,
			// ��ѯ��ֵ��
			sQueryAddValueCard = 9,
			// ��ѯԪ������
			sQueryYuanbaoCount = 10,
			// ��ȡԪ��
			sWithdrawYuanbao = 11,
			// ���͵�½��key
			sLoginKey = 12,
		};

		enum CommonDBMsg
		{
			dcDBExec = 1, // ִ��Ԥ����
		};

		enum PVMDBMsg
		{
			dcLoadPVMlayer = 133, //��ȡ���������
			dcUpdatePVMlayer = 134, //�������������
			dcUpdateChallengeRecord = 135,//���¾�������ս��¼
			dcLoadChallengeRecord = 136,//���¾�������ս��¼
		};

		enum AFKCmd
		{
			dcLoadAFKData = 139,    //���عһ���������
			dcSaveAFKData = 140,    //����һ���������
		};
	}

	namespace AsyncOperatorCode
	{
		enum tagAsyncOpError
		{
			soeSucc = 0,			// �ɹ�
			soeDBErr,				// dbִ�д��󣨻���db�޷����ӣ�
			soeNoCardInfo,			// �����ڴ˿���Ϣ
			soeTimeExpired,			// ��ѯ��ʱ
		};
	}

	// gameworld֮��ͨ�ŵ�Э��
	namespace GameWorldProto
	{
		enum GwP
		{
			gpRegReq = 1,		// ע����Ϣ���������������Ϣ������serverid
			gpRegResp = 2,

			gpKeyReq = 3,		// ����key������ͻظ�
			gpKeyResp = 4,

			gpUserLogin = 5,	// �㲥��ҵ�½����Ϣ
			gpBatchOnline = 6,	// ͬ��������ҵ���Ϣ
			gpUserExit = 7,		// ���������Ϣ
			gpCloseUser = 8,	// ���������

			gpGateway = 9,		// ͬ�����ص���Ϣ
			gpTtData = 10,      // ת��Э��
			gpSsData = 11,		// C++�����ڣ�������֮�����Ϸ�߼���Ϣ
			gpLfData = 12,		// �������ϵͳ��Ϣ
			// ����֮���ȫ����Ϸ�߼���ص���Ϣ
			gpCommonMsg,	// ��Ϸ�߼���ص���Ϣ
			gpCrossRelogin,	// ֪ͨ�������������ظ���¼
		};

		enum LfSysType {
			lsDefault = 0,
			lsGuild,
			lsRank,
		};

		enum SSP
		{
			stBroadCast,	//�㲥
			stRankList,		//�������а��б�
			stUserLogin,    //��ҵ�¼
			stUserLogout,	//��ҵǳ�
			stBatchOnline,	//��������(ͬ����ҵ�¼��Ϣ)

			//stRecvMail, //֪ͨ������ʼ� todo luaʵ��
			stKickUser, //�ߵ����������
			//stRecvOfflineMsg, //֪ͨ�����������Ϣ todo luaʵ��

			stNormalMax = 100, //���濪ʼ�ǽű��������Ϣ
		};

		enum LfGuildCmd {
			lcGuildList, // ���������б�
			lcGuildUnion, // ���ڽ���
			lcGuildDelUnion, // 
			lcCreateGuild, // ��������
			lcDelGuild, // ɾ������
			lcUpdateGuild, // ����������Ϣ
			lcDelGuildMem, // 
			lcAddGuildMem, // 
			lcGuildBroadCast, // ���ڹ㲥
			lcUpGuildMemInfo, // 
			lcGuildOnline, // ��ͨ��֪ͨ��������״̬
			lcGuildLeaderInfo, //���Ͱ�����һЩ��Ϣ
			lcAddItemToDepot,  //����һ�����ߵ��ֿ�
			lcAddGuildLog, //����һ�����ɼ���
			lcSendFightVal, //���Ͱ���ս��
			lcChangePos,	//�ı����ְλ
			lcDepotAvailible,	//���ɲֿ�ʣ��λ��
			lcImpeach,		//����
		};

		enum LfRankCmd {
			lcRankList = 0, // �������а��б�
			lcRankTitle = 1,	//����֪ͨ�޸����а�ƺ�
		};
	};
	// gameworld �� centerserver ֮���ͨ��Э��
	namespace CenterProto
	{
		enum CWP
		{
			cwComm = 1, // ֱ��ת���ĵ����ݰ�
			cwActorOnline = 2, //��ĳ�����߻�����
			cwActorServer = 3, //����actorid���͵�actorid���ڷ�����
			cwActorServerInfo = 4,	//������ĸ�������
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

