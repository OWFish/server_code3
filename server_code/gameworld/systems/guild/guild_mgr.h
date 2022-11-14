#pragma once

class Guild;
class Actor;

typedef Vector<Guild*> GuildList;

// �������
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
	// �����ݿ�������й�������
	bool LoadDbData();
	// ��������
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
	//֪ͨ���ݿ����������һ������
	void SendDbAddGuild(int gid, const char* name);
	//֪ͨ���ݿ������ɾ��һ������
	void SendDbMsgDeleteGuild(int id);
	Guild* AddGuildToList(int gid, const char* guildName);

	bool LoadGuildDetail(SQLConnection& sql, Guild& guild);
	bool LoadGuildLog(SQLConnection& sql, Guild& guild);
	bool LoadGuildChat(SQLConnection& sql, Guild& guild);
	bool LoadGuildStoreLog(SQLConnection& sql, Guild& guild);

	void LoadSeries();
	void SaveSeries();

public:
	GuildList				rank_;				//���������������� 1�����н������ܵȼ� 2���Ⱥ����

private:
	StaticHashTable<Guild*, MAX_GUILD>	guild_list_; //	�����б�,�԰���id����ϣ��Ӧ�ò�������ô��İ���
	BinaryList<NameSortItem, 4096>	all_guild_name_;	//���й������б�

	Timer					timer_;	//1���Ӽ��һ��

	static int				guildid_series_;

};
