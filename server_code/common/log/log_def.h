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
	lmOnline = 9, // 统计在线人数
	lmDcApiData = 10, //QQ统一数据平台接口
	lmDcApiDataList = 11, //QQ统一数据平台接口
	lmDcApiProto = 12, //QQ统一数据平台接口(接口6.20)
	lmTLog = 13, // 发送到TLog数据
	lmChat = 14, // 统计聊天信息
	lmDKMLog = 15, //多可梦日志报送
};

enum LogFlagInter
{
	lfiDB = 1,	// 保存数据库
	lfiBI = 2,		// 保存到BI
	lfiText = 4,		// 保存到文本
	lfiIsPay = 8,		// 是否充值的数据
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
	short log_type_; // 见《DC_API_manual_C++_V2.1.pdf》中日志类型定义 : 0=经分数据上报；1=模调数据上报；4=反外挂数据上报
	char content_[2048];
};

struct LDcApiProtoLog
{
	//=====head=====
	char openId[128]; //即玩家帐号
	int domain; //平台ID
	int serverId;
	char svrip[32]; //服务器ip
	char userip[32]; //用户ip
	//=====end head=====

	//===body=====
	int roleId;
	int protoId;
	int gameFeatrueId; //直接填写系统ID
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
	bool save_db_;	// 是否保存到本地数据库，这个已经没用
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
	ctSecret = 1, // 私聊,密语
	ctMail = 3,
	ctWorld = 4, // 世界,喇叭频道
	ctCamp = 5,
	ctGuild = 6, // 工会，帮派
	ctTeam = 7, // 队伍频道,5人
	ctNear = 8,  // (取消）附近频道，同屏
	ctOther = 9,
};

#endif

