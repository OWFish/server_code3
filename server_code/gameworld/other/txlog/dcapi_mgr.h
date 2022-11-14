#ifndef DCAPI_MGR_H
#define DCAPI_MGR_H

#ifndef SEND_DCAPI_PROTO_LOG
#define SEND_DCAPI_PROTO_LOG(entity, sid_, pid, tp, ret)// entity->sendDcApiLog(sid, pid, tp, ret)
#endif

#define DCAPI_SEND_BUF_SIZE		4096

#define COUNT_CHARGE_MONEY_TYPE 2
#define SEND_MAIL_COST 200
// DC API ActionID
enum {
	AC_LOGIN			= 1,
	AC_LOGOUT			= 2,
	AC_P2PTRADE			= 3,
	AC_ITEMCHANGE		= 4,
	AC_GOLDCHANGE		= 5,
	AC_CASHCHANGE		= 6,
	AC_PVPRESULT		= 7,
	AC_COPYRESULT		= 8,
	AC_USEROPRP			= 9,
	AC_FRIENDOPRP		= 10,
	AC_MOUSEDOWNRP		= 11,
	AC_APPHACKTYPERP	= 12,
	AC_PROTORP			= 13,
	AC_CREATEROLE		= 14,
	AC_ROLECHAT			= 15,
	AC_ROLESENDMAIL		= 16,
	AC_ROLEVENDOR		= 17,
	AC_ROLETEAM			= 18,
	AC_GAMEMSGRP		= 19,
	AC_RPGPROTORP		= 20,
};

// 邮件类型
enum {
	MT_SYSTEM		= 0,
	MT_PRIVATE		= 1,
	MT_ATTACHMENT	= 2,
	MT_COUNT		= 3,
};

//class Actor;

class DcApiMgr
{
public:
	DcApiMgr();
	~DcApiMgr();

public:
	// 是否停止发送
	void SetStopLog(bool sp);

	bool IsStopLog(){return stop_log_;};
	// 角色游戏记录
	void LogChat(Actor* et, int cid, const char* content, Actor* receiver = NULL);
	// 角色发送邮件
	void LogMail(Actor* et, const char* receiver, int64_t mailId, const char* content);
	//交易信息
	void LogP2PTrade(Actor* lauch, Actor* accpt);
	//道具数量变化信息，卸载日志发送函数里，但是日志发送函数并不是所有情况下都被调用，需要完善
	void LogItemChange(Actor* actor, const ItemData* pUserItem,const StdItem* pStdItem, 
		const int nCountChg, const char* lpSender, const int nTgtId, const char* sTargetName);
	//非充值游戏币信息变化
	void LogGoldChange(Actor* actor, int moneyType,int amount, int value, const char* phylum,const char* classfield,
		const char* family, const char* genus, const char* extra, bool ispay);
	//充值游戏币变化
	void LogCashCahnge(Actor* actor, int moneyType,int amount, int value, const char* phylum,const char* classfield,
		const char* family, const char* genus, const char* extra, bool ispay);
	//创建角色
//	void LogCreateRole(int accountid, const char* accountname, const char* name, int sex, int job, int icon, int camp, ActorId actor_id,int pfid);
	//发送角色摆摊日志
	void LogRoleVendor(Actor* actor, bool evid, unsigned int handle);

	//组队id
	//void LogRoleTeam(Actor* actor, Team* team);

	void LogGameMsgRP(Actor* actor,unsigned long long msgid, char* msg);

private:
	// 获取聊天频道名称
	//const char* GetChannelName(int cid);
	// 获取DC API消息头
	int DcApiLogHead(char* buf, int len, Actor* actor, int aid);
	// 获取邮件类型描述
	const char* GetMailTypeDesc(int tp);
	// 获取职业描述
	const char* GetJobDesc(int job);
	// 获取阵营描述
	const char* GetCampDesc(int camp);

private:
	// 发送数据
	char send_buf_[DCAPI_SEND_BUF_SIZE];
	// 是否停止发送log
	bool stop_log_;
};

#endif

