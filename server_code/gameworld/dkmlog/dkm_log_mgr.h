#ifndef TLOG_MGR_H
#define TLOG_MGR_H

#define TLOG_BUFFER_SIZE 4096


#define MAX_LOG_QUEST_ITEM 20 // 能记录的奖励的物品最大数量

// TLog日志中替换字符串中的分隔符
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

	// 获取当前时间对应的字符串
	const char* GetTime();
	void FormatLog(char *dstr, const char* str);


	//角色登录日志
	//void LogLogin(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* addr);
	//角色登出日志
	//void LogLogout(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int onlineTime);
	////角色升级日志
	//void LogUpgrade(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int vipLvl);
	////充值日志
	//void LogRecharge(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, int cash, int yb, int id1, int id2, const char* addr);
	////角色快照日志
	//void LogChardata(int accountid, int actorid, const char* name, int lvl, const char* pfid, int createtime, int lastlogintime, int totalonlinetime, int dayonlinetime, int lev, int viplev, int exp, int fight, int totalcash, int  yuanbaoowned, int jinbiowned);
	//加元宝
	void LogAddMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* typeinfo, int yuanbao, int type);
	//消耗元宝
	void LogCostMoney(int accountid, int actorid, const char* name, int lvl, const char* pfid, int totalcash, const char* typeinfo, int yuanbao);
	//道具产出
	void LogAddItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr = "");
	//道具消耗
	void LogCostItem(int accountid, int actorid, const char* name, int lvl, const char* pfid, int itemId, int count, int guid, int itemType, const char* logStr = "");

public:
	// 创建角色, 这个不在主线程中调用，特殊处理
	//创建角色日志
	static void LogCreateRole(int accountid, int actorid, const char* name, const char* pfid, const char* addr);

public:
	// 是否发送数据
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
	// 发送数据
	char send_buf_[TLOG_BUFFER_SIZE];
	//当前时间字符串
	char time_text_[64];
	// 事件ID
	EventId event_id_;
};

#endif

