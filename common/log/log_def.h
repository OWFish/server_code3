#ifndef			_LOG_TYPE_H_
#define			_LOG_TYPE_H_

using namespace SrvDef;
// new 
enum LogMsgCmd
{
	lmCounter = 1,
	lmInstall = 2,
	lmDau = 3,
	lmEconomy = 4,
	lmMilestone = 5,
	lmCounterDB = 6,
	lmPayment = 7,
	lmGameInfo = 8,
	lmOnline = 9, // ͳ����������
	lmDcApiData = 10, //QQͳһ����ƽ̨�ӿ�
	lmDcApiDataList = 11, //QQͳһ����ƽ̨�ӿ�
	lmDcApiProto = 12, //QQͳһ����ƽ̨�ӿ�(�ӿ�6.20)
	lmTLog = 13, // ���͵�TLog����
	lmChat = 14, // ͳ��������Ϣ
	lmDKMLog = 15, //�������־����
};

enum LogFlagInter
{
	lfiDB = 1,	// �������ݿ�
	lfiBI = 2,		// ���浽BI
	lfiText = 4,		// ���浽�ı�
	lfiIsPay = 8,		// �Ƿ��ֵ������
};



struct LDcApiLogTable
{
	char key_[16];
	char value_[64];
	bool mustUrlencode_;
};
typedef Vector<LDcApiLogTable*, 128> LDcApiLogTableList;
struct LDcApiData 
{
	char log_name_[128];
	short log_type_; // ����DC_API_manual_C++_V2.1.pdf������־���Ͷ��� : 0=���������ϱ���1=ģ�������ϱ���4=����������ϱ�
	char content_[2048];
};

struct LDcApiProtoLog
{
	//=====head=====
	char openId[128]; //������ʺ�
	int domain; //ƽ̨ID
	int serverId;
	char svrip[32]; //������ip
	char userip[32]; //�û�ip
	//=====end head=====

	//===body=====
	int roleId;
	int protoId;
	int gameFeatrueId; //ֱ����дϵͳID
	int protoType;
	int protoResult;
	//===end body====
};

struct LCounter 
{
	ActorId actorid_;
	char aid_[64];
	char user_level_[32];
	char counter_[32];
	char value_[32];
	char extra_[128];
	char kingdom_[32];
	char phylum_[32];
	char classfield_[32];
	char family_[32];
	char genus_[128];
	bool save_db_;	// �Ƿ񱣴浽�������ݿ⣬����Ѿ�û��
	int flag_;
};

struct LInstall
{
	char aid_[64];
	char source_[32];
	char affiliate_[32];
	char creative_[32];
	char family_[32];
	char genus_[32];
	char from_uid_[32];
	char extra_[32];
	int flag_;
};

struct LDau
{
	char aid_[64];
	char source_[32]; 
	char affiliate_[32];
	char creative_[32];
	char family_[32];
	char genus_[32];
	char ip_[32];
	char from_uid_[32]; 
	char extra_[32];
	int flag_;
};

struct LEconomy 
{
	ActorId actorid_;
	char aid_[64];
	char currency_[32]; // currency type
	char amount_[32]; //numerical amount
	char value_[32]; // numerical value
	char kingdom_[32]; 
	char phylum_[32];
	char classfield_[32];
	char family_[32];
	char genus_[32];
	char extra_[128];
	char extra2_[32];
	char pf_[128];
	int flag_;
	char openkey_[512];
	char pfkey_[128];
	char pfid_[128];
};

struct LMilestone 
{
	ActorId actorid_;
	char aid_[64];
	char milestone_[32];
	char value_[32];
	char extra_[32];
	int flag_;
};

struct LPayment
{
	ActorId actorId_;
	char aid_[64];
	int amount_;
	int value_;
	char kingdom_[32]; 
	char phylum_[32];
	char transactionid_[32];
	char extra_[32];
	int mstType_;
	int p1_;
	int p2_;
	int p3_;
	int p4_;
	int p5_;
	int ret_;
	int flag_;
};

struct LGameInfo
{
	char aid_[64];
	char user_level_[32];
	char value_[32];
	char extra_[32];
	char kingdom_[32];
	char phylum_[32];
	char classfield_[32];
	char family_[32];
	char genus_[32];
	int flag_;
};

struct LChat
{
	ActorId actorid_;
	char aid_[64];
	char name_[32];
	char ip_[32];
	char pf_[32];
	int type_;
	char toaid_[64];
	char toname_[32];
	char content_[1024];
};

enum ChatType
{
	ctSecret = 1, // ˽��,����
	ctMail = 3,
	ctWorld = 4, // ����,����Ƶ��
	ctCamp = 5,
	ctGuild = 6, // ���ᣬ����
	ctTeam = 7, // ����Ƶ��,5��
	ctNear = 8,  // (ȡ��������Ƶ����ͬ��
	ctOther = 9,
};

#endif

