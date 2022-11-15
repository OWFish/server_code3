#pragma once
#include "db/guild_data.h"
#include <vector>
#include <string>

typedef LinkedListEx<GuildMemberInfo, 4096 * 8>			GuildMemberList;
typedef LinkedNode<GuildMemberInfo>						GuildMemberNode;

struct GuildLog // �����¼�
{
	unsigned int time_;
	unsigned char type_;
	int param1_;
	int param2_;
	int param3_;
	ACTORNAME name1_;
	ACTORNAME name2_;
};

struct GuildChatLog // ����������Ϣ��¼
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

struct GuildStoreLog // �����̵��¼
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
	static const int POS_COUNT = smGuildLeader; // ���ְλ��
	static const int MAX_GUILD_LOG = 100;		//�������������¼���¼
	static const int GUILD_NAME_LEN = 32; //�������ֳ���
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
	// �Ƚ��������������
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

	//���빫���ڲ���Ϣ���
	bool PostJoinMsg(Actor* actor);
	bool RemoveJoinMsg(int actorId);
	bool GetJoinMsg(int actorId);

	int GetMemberTotalGx(int actorId);
	void ChangeMemberTotalGx(int actorId, int val);

	void Save();
	void SaveBase();

	void LoadVar(const char* ptr, size_t len);

	// ������ʷ���׸���ְλ
	void UpdateGuildPos();
	// ��ȡ������ߵ����ID
	ActorId GetLargestContribution();
	// ��ӹ����¼�
	void AddGuildLog(unsigned char type, const char* name1, const char* name2, int param1 = 0, int param2 = 0, int param3 = 0);
	// ��������¼
	void AddChatLog(uint8_t type, const char* content, Actor* actor,int time);
	//��ӹ����̵��¼
	void AddGuildStoreLog(ActorId actor_id, const char* name, int item_id);

	Vector<GuildLog>& GetGuildLogs() { return logs_; }

	std::vector<GuildChatLog>& GetChatLogs() { return chat_logs_; }

	Vector<GuildStoreLog>& GetGuildStoreLogs() { return store_logs_; }

	void BroadCast(const char* buf, size_t size);
	// ÿ���Ӷ�ʱ���
	void CheckTime(uint32_t now_sec,bool stopserver = false);
	// ���ݼ������
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
	// ������б����������
	void Sort(GuildMemberList& list, GuildMemberNode* node);
	// 
	void SaveVar();
	// ���������¼
	void SaveChatLog();
	// ���湫���̵��¼
	void SaveStoreLog();
	//
	void SaveMemberInfo(GuildMemberInfo& info);

public:
	int								id_;		//�����id
	int								rank_;		//���������
	char							name_[GUILD_NAME_LEN];//���������
	ActorId							leader_id_;	//�᳤�����ID
	ACTORNAME						leadername_; //�᳤������
	int								leader_vip_; //�᳤��VIP�ȼ�
	int								leader_monthcard_; //�᳤���¿�״̬
	int								level_;		// ����ȼ�
	int								affair_level_;		// �����õȼ�
	int								levelup_time_;	// ��������ʱ��
	bool							update_;	// �Ƿ���Ҫ���浽���ݿ���
	bool							update_base_; //���湫���������
	unsigned char                   auto_;       // �Ƿ��Զ�ͬ����빫������
	int                             need_fight_; // �Զ�ͬ����빫����Ҫ��ս����
	int								change_name_count; //�ɸ�������

	
	GuildMemberList					actor_list_;

	StaticHashTable<GuildMemberNode*, MAX_MEMBER> all_actor_;

	//�����ǰ����ڲ�����Ϣ���������롢��������
	BinaryList<JoinApply>			inter_msg_list_;

	friend class GuildMgr;
private:
	CLVariant						var_;
	Vector<GuildLog>				logs_;			// �����¼�
	std::vector<GuildChatLog>		chat_logs_;		// �����¼
	bool							chat_update_; // �Ƿ���Ҫ���������¼
	uint32_t						next_save_chat_; //�´α���������Ϣ��ʱ��
	bool							has_today_contrib_; // �����Ƿ��й���
	Vector<GuildStoreLog>				store_logs_;			// �����̵��¼
	bool							store_update_; // �Ƿ���Ҫ���湫���̵��¼
	uint32_t                   next_save_store_; //�´α��湫���̵��¼��ʱ��
};
