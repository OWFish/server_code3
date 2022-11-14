#ifndef TLOG_MGR_H
#define TLOG_MGR_H

#define TLOG_BUFFER_SIZE 4096

// ��������
enum
{
	OlSockError = 0,
	OlTimeout = 1,
	OlServerKill = 2,
};


// ��Ʒ���ͣ���ʱȫ����0
enum TLogItemType
{
	ltAlays = 0, // ������Ч
	ltOnce = 1, // ��������
};

// ������Ʒ
struct TLogItem 
{
	int id_; // ��ƷID��0��ʾ�ǽ�Ǯ
	int type_;
	int count_;
	int64_t guid_;
};

#define MAX_LOG_QUEST_ITEM 20 // �ܼ�¼�Ľ�������Ʒ�������

// TLog��־���滻�ַ����еķָ���
const char* TLogReplace(const char* instr, int idx = 0);

class TlogMgr
{
public:
	TlogMgr();
	~TlogMgr();

public:
	// ������־
	void Log(const char* fmt, ...);
	// ����������־
	void LogOnlineCount(int cnt);
	// ��������
	void LogPartyBuild(Guild& guild, Actor& actor);
	// ��ɢ����
	void LogPartyDismiss(Guild& guild);
	// ��������
	void LogPartyLevelUp(Guild& guild, Actor& actor);
	// ��Ӱ��ɳ�Ա
	void LogPartyAddMember(Guild& guild, Actor& actor, Actor* byactor);
	// ɾ�����ɳ�Ա
	void LogPartyDelMember(Guild& guild, Actor& byactor, const char* name);
	// �̳ǹ���
	void LogShop(Actor& actor, int moneyType, int money, const ItemOPParam& item, ItemSeries& guid);
	// ���PK������־
	void LogPlayerKill(Actor* actor, Actor* killer);
	// ��������,ȷ�Ϲ�����Ȳ��ǣ�����
	void LogMonsterKilled(Monster& mon, TLogItem* pitem, int& nitem, int reason);
	// ��������
	void LogDiscardItem(Actor* actor, ItemData* item);
	// ��Ǯ����
	void LogMoneyFlow(Actor& actor, int moneyType, int amount, const char* phylum);
	// ��ֵ��־
	void LogRecharge(Actor& actor, int amount);
	// �������۴���
	//void LogStartPostToken(Actor& actor, ConsingmentData& data);
	// �������۴���
	//void LogEndPostToken(Actor* actor, ConsingmentData& data);
	// ��ҽ��׼��۴�����־
	//void LogPostTokenTrade(Actor& actor, ConsingmentData& data);
	// ʰȡ������־
	void LogPickupItem(Actor& actor, ItemOPParam& item, int64_t guid);
	// ʹ�õ�����־
	void LogUseItem(Actor& actor, ItemData& item);
	// ����ʼ��־
	void LogTaskStart(Actor& actor, const QuestConfig& conf);
	// ���������־
	void LogTaskFinished(Actor& actor, const QuestConfig& conf, TLogItem* qitems, int nitem, TLogItem* litems, int litem);
	// ȡ��������־
	void LogCancelTask(Actor& actor, const QuestConfig& conf);
	// ɱ����־,ȷ�Ϲ�����Ȳ��ǣ�����
	void LogKillMon(Actor& actor, Monster& monster, int teamflag, int getexp, MONSTERCONFIG& mconf);
	// ������־
	void LogOffline(Actor& actor, int reason);

	// ��ȡ��ǰʱ���Ӧ���ַ���
	const char* GetTime();
	// ��ȡ�¼�ID
	const char* GetEventId();

public:
	// ������ɫ, ����������߳��е��ã����⴦��
	static void LogCreateRole(const char* accountname, int accountid, const char* name, int job, int sex, int pfid, const char* addr);

public:
	// �Ƿ�������
	static bool open_log_;

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

