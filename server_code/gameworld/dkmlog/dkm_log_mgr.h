#ifndef TLOG_MGR_H
#define TLOG_MGR_H

#define TLOG_BUFFER_SIZE 4096


#define MAX_LOG_QUEST_ITEM 20 // �ܼ�¼�Ľ�������Ʒ�������

// TLog��־���滻�ַ����еķָ���
const char* TLogReplace(const char* instr, int idx = 0);

//struct cmp_str
//{
//	bool operator()(const char *a, const char *b) const
//	{
//		return std::strcmp(a, b) == 0;
//	}
//};

class DKMLogMgr
{
public:
	DKMLogMgr();
	~DKMLogMgr();

public:

	// ��ȡ��ǰʱ���Ӧ���ַ���
	const char* GetTime();
	void FormatLog(char *dstr, const char* str);


	//��ɫ��¼��־
	//void LogLogin(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* addr);
	//��ɫ�ǳ���־
	//void LogLogout(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int onlineTime);
	////��ɫ������־
	//void LogUpgrade(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int vipLvl);
	////��ֵ��־
	//void LogRecharge(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int cash, int yb, int id1, int id2, const char* addr);
	////��ɫ������־
	//void LogChardata(int accountid, int actorid, const char* name, int lvl, const char* pfid, int createtime, int lastlogintime, int totalonlinetime, int dayonlinetime, int lev, int viplev, int exp, int fight, int totalcash, int  yuanbaoowned, int jinbiowned);
	//��Ԫ��
	void LogAddMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* typeinfo, int yuanbao, int type);
	//����Ԫ��
	void LogCostMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* typeinfo, int yuanbao);
	//���߲���
	void LogAddItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr = "");
	//��������
	void LogCostItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr = "");

public:
	// ������ɫ, ����������߳��е��ã����⴦��
	//������ɫ��־
	static void LogCreateRole(int accountid, int actorid, const char* name, const char* pfid, const char* addr);

public:
	// �Ƿ�������
	static bool open_log_;

	//std::map<const char*, int, cmp_str> dkmLogId;

private:
	union EventId
	{
		struct
		{
			unsigned int time_;
			unsigned int series_;
		} sval_;
		uint64_t ival_;
	};

private:
	// ��������
	char send_buf_[TLOG_BUFFER_SIZE];
	//��ǰʱ���ַ���
	char time_text_[64];
	// �¼�ID
	EventId event_id_;
};

#endif

