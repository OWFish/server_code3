#ifndef _LIANFU_GUILD_H_
#define _LIANFU_GUILD_H_

class LfGuild
{
public:
	LfGuild();

	int Compare(LfGuild* guild)
	{
		if (!guild) return 1;

		// 总等级的大小
		uint8_t* ptr = (uint8_t*)&level_;
		int t1 = ptr[0] + ptr[1] + ptr[2] + ptr[3];
		
		ptr = (uint8_t*)&(guild->level_);
		int t2 = ptr[0] + ptr[1] + ptr[2] + ptr[3];

		if (t1 > t2) return 1;
		else if (t1 < t2) return -1;

		if (all_actor_count_ > guild->all_actor_count_) return 1;
		else if (all_actor_count_ < guild->all_actor_count_) return -1;

		if (stone_ > guild->stone_) return 1;
		else if (stone_ < guild->stone_) return -1;
		else return 0;
	}

	inline int GetLevel(int idx=0)
	{
		return (level_ >> (8 * idx)) & 0xff;
	}

	void OnLogin(Actor* actor);
	void OnLogout(Actor* actor);
	void OnAddMember(ActorId aid);
	void OnDelMember(ActorId aid);
	void BroadCast(const char* data, size_t size); //仙宗内广播
	void UpdateOnlineStatus(ActorId aid, bool isOnline);
	void NotifyUpdateGuildInfo(uint8_t type);

public:
	int id_;  //帮派id
	int sid_; //所在的服务器ID
	char name_[32]; //帮派名字
	char leadername_[32]; //帮主名字
	char memo_[MAXMEMOCOUNT];		//外部公告信息
	int64_t	level_; // 等级4个字节，从低到高，分别代表4个建筑的等级
	int icon_;
	int rank_;	//排名
	int stone_;	//金钱
	int all_actor_count_; //宗里人数
	int depot_availible_; //帮派仓库剩余数量

	//GuildManagerInfo	leader_info_;

	int fight_val_;	//总战力

	BinaryList<int64_t> actor_list_; // 在这个服在线的玩家的handle列表
};


typedef Vector<LfGuild*> LfGuildList;

// 连服仙宗管理
class LianfuGuild
{
public:
	static const int MAX_GUILD = 8192;
	static const int MAX_SERVER = 10;

public:
	LianfuGuild();
	~LianfuGuild();

public:
	void ProcessNetData(int cmd, DataPacketReader& packet);
	
public:
	void OnLoadGuild();
	void NotifyUpdateGuildInfo(uint8_t type); //全服广播
	
	LfGuild* GetGuild(int gid); // 获取仙宗信息
	LfGuildList& GetGuildList() { return guild_list_; } // 获取仙宗列表
public:
	void UpdateGuildList(); //更新仙宗列表
	//void OnCreateGuild(Guild* guild); //创建帮派
	//void OnDeleteGuild(int gid);	//删除帮派
	//void OnUpdateGuild(Guild* guild); //帮派更新
	//void OnAddGuildMember(ActorId actorId, int guildId); // 添加帮派成员
	//void OnDelGuildMember(ActorId actorId, int gid); // 删除帮派成员
	//void GuildBroadCast(int sid, int gid, const void* data, size_t size, bool all = true); // 仙宗广播，在连服服务器调用
	//void BroadCastToLianfu(int gid, const void* data, size_t size);// 发送到连服服务器广播
	//void SendGuildOnlineStatus(int gid, ActorId aid, char status); // 成员上线状态
	//void SendGuildLeaderInfo(GuildManagerInfo& gmi, int gid);
	//void OnAddItemToDepot(int gid, int itemId, int count, int quality, int logId);
	//void OnAddGuildLog(int guildId, unsigned char tp, int aid, const char* name1, const char* name2, int param1, int param2, int param3);
	//void SendGuildFightVal(int fightVal, int gid);
	//void HandleGuildFightVal(DataPacketReader& packet);
	//void ChangePos(DataPacketReader& packet);	//改变玩家职位
	//void SendDepotAvailible(Guild* guild);	//帮派仓库剩余位置
public:
	void HandleGuildList(DataPacketReader& packet); //处理更新仙宗列表
	void HandleCreateGuild(DataPacketReader& packet); //处理创建帮派
	void HandleDeleteGuild(DataPacketReader& packet); //处理删除帮派
	void HandleUpdateGuild(DataPacketReader& packet); //处理帮派更新
	void HandleAddGuildMember(DataPacketReader& packet); //处理添加帮派成员
	void HandleDelGuildMember(DataPacketReader& packet); //处理删除帮派成员
	void HandleGuildBroadCast(DataPacketReader& packet); //处理帮派广播
	void HandleMemberStatus(DataPacketReader& packet); //处理帮派成员在线状态
	void HandleGuildOnlineStatus(DataPacketReader& packet); 
	void HandleGuildLeaderInfo(DataPacketReader& packet);
	void HandleAddItemToDepot(DataPacketReader& packet); //处理添加道具到帮派仓库
	void HandleAddGuildLog(DataPacketReader& packet);//处理在连服增加帮派日志
	void HandleDepotAvailible(DataPacketReader& packet); //处理帮派仓库剩余位置
	void HandleImpeach(DataPacketReader& packet); //处理弹劾职位变更
private:
	// 是否连服
	bool IsLianfu();
	// 添加仙宗
	LfGuild* AddGuild(int gid, int64_t level);
	// 删除仙宗
	void DeleteGuild(int gid);
	// 调整仙宗排行
	void AdjustRank(LfGuild* guild);
private:
	StaticHashTable<LfGuild*, MAX_GUILD> all_guild_; // 仙宗id : 仙宗信息(哈希表)
	LfGuildList guild_list_;
	ObjList<LfGuild>* guild_allocator_;

	bool guild_loaded_; // 是否已经加载仙宗数据
	bool guild_update_; // 是否已经发送仙宗信息
};

#endif