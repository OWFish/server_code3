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

// �ʼ�����
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
	// �Ƿ�ֹͣ����
	void SetStopLog(bool sp);

	bool IsStopLog(){return stop_log_;};
	// ��ɫ��Ϸ��¼
	void LogChat(Actor* et, int cid, const char* content, Actor* receiver = NULL);
	// ��ɫ�����ʼ�
	void LogMail(Actor* et, const char* receiver, int64_t mailId, const char* content);
	//������Ϣ
	void LogP2PTrade(Actor* lauch, Actor* accpt);
	//���������仯��Ϣ��ж����־���ͺ����������־���ͺ�����������������¶������ã���Ҫ����
	void LogItemChange(Actor* actor, const ItemData* pUserItem,const StdItem* pStdItem, 
		const int nCountChg, const char* lpSender, const int nTgtId, const char* sTargetName);
	//�ǳ�ֵ��Ϸ����Ϣ�仯
	void LogGoldChange(Actor* actor, int moneyType,int amount, int value, const char* phylum,const char* classfield,
		const char* family, const char* genus, const char* extra, bool ispay);
	//��ֵ��Ϸ�ұ仯
	void LogCashCahnge(Actor* actor, int moneyType,int amount, int value, const char* phylum,const char* classfield,
		const char* family, const char* genus, const char* extra, bool ispay);
	//������ɫ
//	void LogCreateRole(int accountid, const char* accountname, const char* name, int sex, int job, int icon, int camp, ActorId actor_id,int pfid);
	//���ͽ�ɫ��̯��־
	void LogRoleVendor(Actor* actor, bool evid, unsigned int handle);

	//���id
	//void LogRoleTeam(Actor* actor, Team* team);

	void LogGameMsgRP(Actor* actor,unsigned long long msgid, char* msg);

private:
	// ��ȡ����Ƶ������
	//const char* GetChannelName(int cid);
	// ��ȡDC API��Ϣͷ
	int DcApiLogHead(char* buf, int len, Actor* actor, int aid);
	// ��ȡ�ʼ���������
	const char* GetMailTypeDesc(int tp);
	// ��ȡְҵ����
	const char* GetJobDesc(int job);
	// ��ȡ��Ӫ����
	const char* GetCampDesc(int camp);

private:
	// ��������
	char send_buf_[DCAPI_SEND_BUF_SIZE];
	// �Ƿ�ֹͣ����log
	bool stop_log_;
};

#endif

