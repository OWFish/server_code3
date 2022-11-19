#ifndef TLOG_MGR_H
#define TLOG_MGR_H

#define TLOG_BUFFER_SIZE 4096

// 掉线类型
enum
{
	OlSockError = 0,
	OlTimeout = 1,
	OlServerKill = 2,
};


// 物品类型，暂时全部是0
enum TLogItemType
{
	ltAlays = 0, // 永久有效
	ltOnce = 1, // 立即消耗
};

// 奖励物品
struct TLogItem 
{
	int id_; // 物品ID，0表示是金钱
	int type_;
	int count_;
	int64_t guid_;
};

#define MAX_LOG_QUEST_ITEM 20 // 能记录的奖励的物品最大数量

// TLog日志中替换字符串中的分隔符
const char* TLogReplace(const char* instr, int idx = 0);

class TlogMgr
{
public:
	TlogMgr();
	~TlogMgr();

public:
	// 发送日志
	void Log(const char* fmt, ...);
	// 在线人数日志
	void LogOnlineCount(int cnt);
	// 创建帮派
	void LogPartyBuild(Guild& guild, Actor& actor);
	// 解散帮派
	void LogPartyDismiss(Guild& guild);
	// 升级帮派
	void LogPartyLevelUp(Guild& guild, Actor& actor);
	// 添加帮派成员
	void LogPartyAddMember(Guild& guild, Actor& actor, Actor* byactor);
	// 删除帮派成员
	void LogPartyDelMember(Guild& guild, Actor& byactor, const char* name);
	// 商城购买
	void LogShop(Actor& actor, int moneyType, int money, const ItemOPParam& item, ItemSeries& guid);
	// 玩家PK死亡日志
	void LogPlayerKill(Actor* actor, Actor* killer);
	// 怪物死亡,确认过这个先不记！！！
	void LogMonsterKilled(Monster& mon, TLogItem* pitem, int& nitem, int reason);
	// 丢弃道具
	void LogDiscardItem(Actor* actor, ItemData* item);
	// 金钱流向
	void LogMoneyFlow(Actor& actor, int moneyType, int amount, const char* phylum);
	// 充值日志
	void LogRecharge(Actor& actor, int amount);
	// 开启寄售代币
	//void LogStartPostToken(Actor& actor, ConsingmentData& data);
	// 结束寄售代币
	//void LogEndPostToken(Actor* actor, ConsingmentData& data);
	// 玩家交易寄售代币日志
	//void LogPostTokenTrade(Actor& actor, ConsingmentData& data);
	// 拾取道具日志
	void LogPickupItem(Actor& actor, ItemOPParam& item, int64_t guid);
	// 使用道具日志
	void LogUseItem(Actor& actor, ItemData& item);
	// 任务开始日志
	void LogTaskStart(Actor& actor, const QuestConfig& conf);
	// 完成任务日志
	void LogTaskFinished(Actor& actor, const QuestConfig& conf, TLogItem* qitems, int nitem, TLogItem* litems, int litem);
	// 取消任务日志
	void LogCancelTask(Actor& actor, const QuestConfig& conf);
	// 杀怪日志,确认过这个先不记！！！
	void LogKillMon(Actor& actor, Monster& monster, int teamflag, int getexp, MONSTERCONFIG& mconf);
	// 掉线日志
	void LogOffline(Actor& actor, int reason);

	// 获取当前时间对应的字符串
	const char* GetTime();
	// 获取事件ID
	const char* GetEventId();

public:
	// 创建角色, 这个不在主线程中调用，特殊处理
	static void LogCreateRole(const char* accountname, int accountid, const char* name, int job, int sex, int pfid, const char* addr);

public:
	// 是否发送数据
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
	// 发送数据
	char send_buf_[TLOG_BUFFER_SIZE];
	//当前时间字符串
	char time_text_[64];
	// 事件ID
	EventId event_id_;
};

#endif

