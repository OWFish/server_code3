#pragma once
#include "db/guild_data.h"
#include <vector>
#include <string>

typedef LinkedListEx<GuildMemberInfo, 4096 * 8>			GuildMemberList;
typedef LinkedNode<GuildMemberInfo>						GuildMemberNode;

struct GuildLog // 公会事件
{
	unsigned int time_;
	unsigned char type_;
	int param1_;
	int param2_;
	int param3_;
	ACTORNAME name1_;
	ACTORNAME name2_;
};

struct GuildChatLog // 公会聊天消息记录
{
	uint8_t type_;
	unsigned int time_;
	std::string content_;
	ActorId actor_id_;
	std::string actor_name_;
	uint8_t job_;
	uint8_t sex_;
	int vip_level_;
	uint8_t month_card_;
	uint8_t pos_;
	uint8_t zs_lv_;
	uint16_t level_;
	int status;
	int headID;
};

struct GuildStoreLog // 公会商店记录
{
	unsigned int time_;
	ActorId actor_id_;
	int item_id_;
	ACTORNAME actor_name_;
};

class Guild
{
public:
	static const int MAX_MEMBER = 256;
	static const unsigned int apply_keep_time = 24 * 3600;
	static const int POS_COUNT = smGuildLeader; // 最大职位数
	static const int MAX_GUILD_LOG = 100;		//最多多少条公会事件记录
	static const int GUILD_NAME_LEN = 32; //公会名字长度
	static const int MAX_CHAT_LOG = 50;
	static const int SAVE_CHAT_INTERVAL = 3600;
	static const int SAVE_RANDOM_SEC = 60 * 5;
	static const int MAX_JOIN_MSG = 100;
	static const int MAX_GUILD_STORE_LOG = 50;
	static const int SAVE_STORE_INTERVAL = 3600;
	static const int DEFAULT_AUTOAPPLY_FIGHT = 99999;

	struct JoinApply
	{
		ActorId			actorId_;
		int				vip_;
		uint8_t			sex_;
		int				level_;
		uint8_t 		job_;
		double			power_;
		unsigned int    jointime;
		char			name_[32];
		int				headid;
		inline bool operator != (const JoinApply& data) const
		{
			return actorId_ != data.actorId_;
		}
		inline bool operator > (const JoinApply& data) const
		{
			return actorId_ > data.actorId_;
		}
		inline bool operator < (const JoinApply& data) const
		{
			return actorId_ < data.actorId_;
		}
	};

	static const int MAX_VAR_SIZE = 61440;
	static const int MAX_VAR_COUNT = 3;

public:
	Guild();
	~Guild();

public:
	// 比较两个公会的排名
	int Compare(Guild* guild)
	{
		if (!guild) return 1;

		if (level_ > guild->level_) return 1;
		else if (level_ < guild->level_) return -1;

		else if(levelup_time_ < guild->levelup_time_) return 1;
		else if (levelup_time_ > guild->levelup_time_) return -1;

		else if (id_ < guild->id_) return 1;
		else if (id_ > guild->id_) return -1;

		else return 0;
	}

public:
	void AddMemberToList(Actor* actor, int pos = smGuildCommon);
	
	void DeleteMember(int actorId);

	GuildMemberNode* FindMember(ActorId actorId);

	inline int GetMemberCount()
	{
		return (int)all_actor_.count();
	}

	inline CLVariant& GetVar()
	{
		return var_;
	}

	void OnDestroy();
	void OnDelete();

	int GetGuildPos(int actorId);
	bool ChangeGuildPos(int actorId, int pos);

	//加入公会内部消息相关
	bool PostJoinMsg(Actor* actor);
	bool RemoveJoinMsg(int actorId);
	bool GetJoinMsg(int actorId);

	int GetMemberTotalGx(int actorId);
	void ChangeMemberTotalGx(int actorId, int val);

	void Save();
	void SaveBase();

	void LoadVar(const char* ptr, size_t len);

	// 根据历史贡献更新职位
	void UpdateGuildPos();
	// 获取贡献最高的玩家ID
	ActorId GetLargestContribution();
	// 添加公会事件
	void AddGuildLog(unsigned char type, const char* name1, const char* name2, int param1 = 0, int param2 = 0, int param3 = 0);
	// 添加聊天记录
	void AddChatLog(uint8_t type, const char* content, Actor* actor,int time);
	//添加公会商店记录
	void AddGuildStoreLog(ActorId actor_id, const char* name, int item_id);

	Vector<GuildLog>& GetGuildLogs() { return logs_; }

	std::vector<GuildChatLog>& GetChatLogs() { return chat_logs_; }

	Vector<GuildStoreLog>& GetGuildStoreLogs() { return store_logs_; }

	void BroadCast(const char* buf, size_t size);
	// 每分钟定时检查
	void CheckTime(uint32_t now_sec,bool stopserver = false);
	// 数据加载完成
	void OnLoadData();
	// 
	void ResetTodayContrib();

	void SetGuildLevel(int level) { level_ = level; }
	int GetGuildLevel() { return level_; }

	void SetGuildAffairLevel(int level) { affair_level_ = level; }
	void SetGuildLevelupTime(int levelupTime) { levelup_time_ = levelupTime; }

	Actor* GetActor(uint64_t handle);

	void LeaderNameUpdate();

	std::vector<Actor*> getOnlineActor(void);

	bool changeName(const char* name);

	void clearGuildChat();
public:
	static void UpdateActorData(Actor* actor, GuildMemberInfo* node);

private:
	// 
	void Reset();
	// 对玩家列表进行下排序
	void Sort(GuildMemberList& list, GuildMemberNode* node);
	// 
	void SaveVar();
	// 保存聊天记录
	void SaveChatLog();
	// 保存公会商店记录
	void SaveStoreLog();
	//
	void SaveMemberInfo(GuildMemberInfo& info);

public:
	int								id_;		//公会的id
	int								rank_;		//公会的排名
	char							name_[GUILD_NAME_LEN];//公会的名字
	ActorId							leader_id_;	//会长的玩家ID
	ACTORNAME						leadername_; //会长的名称
	int								leader_vip_; //会长的VIP等级
	int								leader_monthcard_; //会长的月卡状态
	int								level_;		// 公会等级
	int								affair_level_;		// 议事堂等级
	int								levelup_time_;	// 公会升级时间
	bool							update_;	// 是否需要保存到数据库中
	bool							update_base_; //保存公会基础数据
	unsigned char                   auto_;       // 是否自动同意加入公会申请
	int                             need_fight_; // 自动同意加入公会需要的战斗力
	int								change_name_count; //可改名次数

	
	GuildMemberList					actor_list_;

	StaticHashTable<GuildMemberNode*, MAX_MEMBER> all_actor_;

	//以下是帮派内部的消息，比如邀请、申请加入等
	BinaryList<JoinApply>			inter_msg_list_;

	friend class GuildMgr;
private:
	CLVariant						var_;
	Vector<GuildLog>				logs_;			// 公会事件
	std::vector<GuildChatLog>		chat_logs_;		// 聊天记录
	bool							chat_update_; // 是否需要保存聊天记录
	uint32_t						next_save_chat_; //下次保存聊天信息的时间
	bool							has_today_contrib_; // 今天是否有贡献
	Vector<GuildStoreLog>				store_logs_;			// 公会商店记录
	bool							store_update_; // 是否需要保存公会商店记录
	uint32_t                   next_save_store_; //下次保存公会商店记录的时间
};
