#pragma once

class Guild;
class Actor;

typedef Vector<Guild*> GuildList;

// 公会管理
class GuildMgr
{
public:
	static const int MAX_GUILD = 8192;
	static const unsigned int update_interval = 300;

	struct NameSortItem
	{
		SrvDef::ACTORNAME name_;

		inline bool operator != (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) != 0;
		}
		inline bool operator > (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) > 0;
		}
		inline bool operator < (const NameSortItem& data) const
		{
			return strcmp(name_, data.name_) < 0;
		}
	};

public:
	GuildMgr();
	~GuildMgr();

public:
	// 从数据库加载所有公会数据
	bool LoadDbData();
	// 创建公会
	Guild* CreateGuild(const char* name, Actor* actor);
	bool DeleteGuild(Guild* guild, const char* reason);
	Guild* FindGuild(int guildId);
	Guild* FindGuildByName(const char* name);

	bool NameHasUsed(const char* name);

	void AdjustRank(Guild* guild);

	void RunOne();

	void Save(bool is_stop = false);

	void Initialize();
	void Destroy();

private:
	//通知数据库服务器增加一个帮派
	void SendDbAddGuild(int gid, const char* name);
	//通知数据库服务器删除一个帮派
	void SendDbMsgDeleteGuild(int id);
	Guild* AddGuildToList(int gid, const char* guildName);

	bool LoadGuildDetail(SQLConnection& sql, Guild& guild);
	bool LoadGuildLog(SQLConnection& sql, Guild& guild);
	bool LoadGuildChat(SQLConnection& sql, Guild& guild);
	bool LoadGuildStoreLog(SQLConnection& sql, Guild& guild);

	void LoadSeries();
	void SaveSeries();

public:
	GuildList				rank_;				//按排名，排名规则 1、所有建筑的总等级 2、先后次序

private:
	StaticHashTable<Guild*, MAX_GUILD>	guild_list_; //	帮派列表,以帮派id做哈希，应该不会有这么多的帮派
	BinaryList<NameSortItem, 4096>	all_guild_name_;	//所有公会名列表

	Timer					timer_;	//1分钟检查一次

	static int				guildid_series_;

};
