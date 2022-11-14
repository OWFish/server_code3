#ifndef _ACTOR_MGR_H_
#define _ACTOR_MGR_H_

#include <map>
#include <string>
#include "actor/tianti_mgr.h"

//�����Ƕ��巵�ظ��ͻ��˵Ĵ����룬��ҪС��0,1�ֽ�
#define	NOERR					0		//��ȷ
#define	ERR_SQL					-1		//sql����
#define	ERR_SESS				-2		//�û�û��½
#define ERR_GAMESER				-3		//��Ϸ����û׼����
#define	ERR_DATASAVE			-4		//��ɫ��һ�α��������Ƿ�����쳣
#define ERR_SELACTOR			-5		//�ͻ���ѡ���ɫ�ĳ������
#define ERR_SAMENAME			-6		//��ɫ�����ظ�
#define ERR_NOUSER				-7		//��ɫ������
#define ERR_SEX					-8		//������Ա�
#define ERR_NORANDOMNAME		-9		//������ɵ������Ѿ�������
#define ERR_ZY					-10		//�ͻ����ϴ��Ľ�ɫ��Ӫ��������
#define ERR_JOB					-11		//�ͻ����ϴ��Ľ�ɫְҵ��������
#define ERR_NAME				-12		//������Ч�������а����Ƿ��ַ��򳤶Ȳ��Ϸ�
#define ERR_GUID				-13		//�������ǰ���������ɾ���ý�ɫ����Ҫ����˰�
#define ERR_CROSSWAR			-14		//�Ѿ���½������������
#define ERR_MAXACTOR			-15		//�Ѿ��������ɽ���ɫ����

/** Session��������������ֵ���� **/
typedef enum tagSessionServerOPError
{
	enSuccess = 0,	     //�����ɹ�
	enPasswdError = 1,   //�������
	enNoAccount = 2,     //û������˺�
	enIsOnline = 3,      //�Ѿ�����
	enServerBusy = 4,    //������æ
	enServerClose = 5,   //������û�п���
	enSessionServerError = 6 , //session�����������⣬����dbû�����Ӻ�
	enServerNotExisting = 7, //���������������
	enFcmLimited = 8 ,     //�˻����������
	enBanTime = 9,     //���ʱ��
} SESSION_SERVER_OPERROR;


using namespace thread;


//#define MAX_ACTOR_CREATE (1 << 19)
#define MAX_ACTOR_CREATE ((1 << 16) - 1) //Ϊ����չ������id,������󴴽���
#define MAX_SERVER_ID ((1 << 16) -1) //������id���ֵ 

class ActorMgr: public thread::BaseThread
{
public:
	typedef BaseThread Inherited;

	typedef struct tagGameServerRoute
	{
		int		nServerIndex;	//������ID
		int		nRouteCount;	//·�ɵ�ַ����
		struct
		{
			char	sHost[124];	//��������ַ��֧��������
			int		nPort;		//�������˿�
		}	RouteTable[16];		//·�ɵ�ַ��
	} GAMESERVERROUTE, *PGAMESERVERROUTE;

	enum
	{
	    imReloadScript = 1,	// ���¶���ű�
	    imReloadFilterName = 2,	// �������ֿ�
		imCloseUser = 3,		// ��gameengine������˳�
		imAddKey,		// ���ӿ����½��key
		imGetKeyResp,	// �յ������¼key��Ӧ��

		imAddOnline,		// �������ߵ��������
		imBatchOnline,		// ����ͬ�������������
		imRemoveOnline,		// ɾ�����ߵ����

		imAddGameClient,
		imBroadCast,
		imUserChange,

		imDelGameClient,	//�Ͽ�һ�����ӵ�gameclient

		imCloseUserInActorMgr, //��actormgr������˳�
		imChangeUserName, //����
	};
	// ������ʽ
	enum
	{
		cnwNormal = 0, // ָ������
		cnwRandom = 1, // �������, �����޸�������ֺ������ַ�����
	};

	struct NameSortItem
	{
		SrvDef::ACTORNAME name_;

		inline bool operator != (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) != 0;
		}
		inline bool operator > (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) > 0;
		}
		inline bool operator < (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) < 0;
		}
	};
	struct ActorSortItem
	{
		int	accountId_;
		NetId netId_;

		inline bool operator !=(const ActorSortItem& data) const
		{
			return accountId_ != data.accountId_;
		}
		inline bool operator >(const ActorSortItem& data) const
		{
			return accountId_ > data.accountId_;
		}
		inline bool operator <(const ActorSortItem& data) const
		{
			return accountId_ < data.accountId_;
		}
	};

	struct CrossUserData
	{
		int serverId_;
		ActorId actorId_;
		int accountId_;
		char account_name_[128];
		int fcm_;			// �Ѿ�����
		bool gm_;
		char key_[64];
		int target_sid_;	// ������ת��serverid���������������֤��
		time_t time_out_;
		//int cross_type_;	// ��ת������������

		CrossUserData() : serverId_(0), actorId_(0), accountId_(0),
			fcm_(0), gm_(false), target_sid_(0),time_out_(0)
		{
			account_name_[0] = 0;
			key_[0] = 0;
		}
		inline bool operator != (const CrossUserData& data) const
		{
			return actorId_ != data.actorId_;
		}
		inline bool operator > (const CrossUserData& data) const
		{
			return actorId_ > data.actorId_;
		}
		inline bool operator < (const CrossUserData& data) const
		{
			return actorId_ < data.actorId_;
		}
	};

	typedef container::BinaryList<CrossUserData> KeyList;

	struct OnlineUserData
	{
		int serverId_;
		ActorId actorId_;

		OnlineUserData() : serverId_(0), actorId_(0)
		{
		}
		inline bool operator != (const OnlineUserData& data) const
		{
			return actorId_ != data.actorId_;
		}
		inline bool operator > (const OnlineUserData& data) const
		{
			return actorId_ > data.actorId_;
		}
		inline bool operator < (const OnlineUserData& data) const
		{
			return actorId_ < data.actorId_;
		}
	};

	typedef container::BinaryList<OnlineUserData> OnLineList;

	enum
	{
		cUserPw = 1,
		sUserPw = 1,

	    cCreateActor = 2,
	    sCreateActor = 2,

	    cDelete = 3,
	    sDelete = 3,

	    cQueryList = 4,
	    sQueryList = 4,

	    cEnterGame = 5,
	    sEnterGame = 5,

	    cRandName = 6,	//�Զ���������
	    sRandName = 6,

	    cLessJob = 7,		//��ѯ������ʹ�õ�ְҵ
	    sLessJob = 7,

	    cLessCamp = 8,		//��ѯ������ʹ�õ���Ӫ
	    sLessCamp = 8,

		cCrossKey = 9,		// �����½��֤key
		sCrossKey = 9,		


	};

public:
	bool StartActorMgr();
	virtual void Stop();


	static int GetStrLenUtf8(const char* sName);

	static const char* LowerCaseNameStr(char* sNameStr);
	void PostMsg(GameInterMsg& msg)
	{
		inter_msg_.append(msg);
	}
public:
	ActorMgr(GameGateMgr* gate_mgr);
	virtual ~ActorMgr();

	void ProcessNetMsg(DataPacket& packet, int gate_idx);
	//void FlustFree();

	// ����
	void SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw);

	// ������ֵĺϷ���
	bool CheckNameStr(const char* sNameStr);

	SQLConnection* GetDbConn()
	{
		return &sql_;
	}

	void SendToGate(NetId& netid, const char* buf, size_t size);
	bool NameHasUser(const char* name);
	int CreateActor(int accountid, const char* accountname, const char* name, int sex, int job,int headid, ActorId& actor_id, const char* pfid, GateUser* gateuser);
	const char* GetRandomName(int nSex);
	void EnterGame(GateUser* user, ActorId actor_id, const char* pf, const char* pfid, const char* appid, int serverId);

	int ChangeActorName(ActorId actor_id, const char* name, const char* rawName);

	// kicknow��ʾ������������ս�������Ƿ����ھ�������
	bool IsLoginBattle(ActorId actorid, bool kickNow = true);

	int IsLogOutBattle(ActorId actorid);

	ActorMgrAlloc& GetAlloc()
	{
		return key_data_alloc_;
	}

	/*AlignAllocator& GetPfAlloc()
	{
		return pf_str_alloc_;
	}*/

	static void GenerateKey(char* buf, int size);

	int LoginOtherSrv(GateUser* user, int sid, ActorId aid, bool newpos = false, unsigned int fbhdl = 0, int sceneid = 0, int x = 0, int y = 0, const char* reason = "");

	bool HasGameClient(int sid);
	void SetupSQLConnection(SQLConnection* sql);
protected:
	void OnRoutine();
	//�����߼�����
	void Run();
	void OnStart();
	void OnStop();

	bool ConnectSQL();

private:
	void CheckUserPw(GateUser* user, DataPacket& packet);

	void SendPwResult( int ret, GateUser* user );

	int NameHasUserFromLasts(const char* name);

	bool LoadFilterNames();

	void FreeFilterWords();

	bool LoadNameData();
	bool LoadOldActorNameData();

	

	// ��ȡ���ս��ս�������ֵ��б�
	bool LoadCrossWarTeamName();
	// �����̷߳�����Ϣ�ĺ���
	void ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);
	int GetOnlinePos(int accountid);

	// �������key
	void CheckCrossKey(GateUser* user, DataPacket& pack);
	bool GetCrossKeyData(ActorId aid, CrossUserData& data);
	void AddCrossKey(CrossUserData& data);
	void AddOnline(int serverid, ActorId aid);
	void RemoveOnline(ActorId aid);
	void AddBatchOnline(DataPacket& dp);
	void DealKeyResp(CrossUserData& data, int loginType);
	//void OnRecvGameMsg(int cmd, DataPack& pack, GameClient* gc);
	//void OnRegist(DataPack& pack, GameClient* gc);

	//// ����Ƿ��Ѿ������gameworld������
	//void HasGameWorld(int sid);

	void ClearGameClient();
	void DelGameClient(int sid);

	bool AddGameClient(const char* ip, int port, int serverId);
	void SendMsgToAllGameClient(int cmd, void* buf, size_t size, int sid);

	GateUser* GetGateUserByActor(ActorId id);

	// ���������ַ���Χ�б�
	bool LoadAllowWords();
	// ����Ƿ�Ϸ������֣����򷵻�true
	bool CheckAllowWord(const char* sName);
	// ���������ַ�
	bool ParseAllowWord(char* sText);
private:
	GameGateMgr*			gate_mgr_;

	SQLConnection			sql_;
	time_t					reconnect_t_;
	time_t					report_t_;
	PFT_MBCS_CHAR			filter_words_;
	Mutex					filter_lock_;	// �ֿ�Ҫ��������Ϊ�ж���̻߳����
	bool					allow_words_[0xffff]; // ����ʹ�õ��ַ�

	RandNameList			def_names_;
	RandNameList			char_names_;

	BinaryList<NameSortItem, 10240>	all_actor_name_;
	BinaryList<ActorSortItem, 4096>	online_list_;

	time_t					next_ping_t_;

	char			db_host_[128];			//���ݿ��ַ
	int				db_port_;				//���ݿ�˿�
	char			db_name_[128];			//���ݿ�����
	char			db_user_[128];			//���ݿ��û���
	char			db_pw_[128];			//���ݿ��û�����

	static int		actorid_series_;

	// ʹ��lua�ű�����
	CVSPDefinition	vsp_def_;
	BaseScript		script_;

	QueueList<GameInterMsg>	inter_msg_;		//�ڲ���Ϣ�б�
	Mutex				inter_msg_lock_;		//�ڲ���Ϣ�б���

	// ���
	KeyList				key_list_;
	time_t				check_key_t_;

	ActorMgrAlloc		key_data_alloc_;
	//StrAlloc			pf_str_alloc_;

	OnLineList					battle_online_list_;		// �Ѿ���½��������������б�
	Vector<GameClient*>			game_client_list_;	// ����ս����������
	//CustomHashTable<ActorId> old_actor_name_;		// ��������ù������Ƶ��б�
	std::map<std::string, int> old_actor_name_;

	struct ActorNetInfo
	{
		NetId netid;
		ActorNetInfo(){}
		ActorNetInfo(NetId& net_id)
		{
			netid = net_id;
		}
	};
	container::StaticHashTable<ActorNetInfo, 4096 * 2> actor_net_list_; //���ڴ����ҵ�������Ϣ���������ĸ���������
};

#endif



