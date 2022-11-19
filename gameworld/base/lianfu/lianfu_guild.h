#ifndef _LIANFU_GUILD_H_
#define _LIANFU_GUILD_H_

class LfGuild
{
public:
	LfGuild();

	int Compare(LfGuild* guild)
	{
		if (!guild) return 1;

		// �ܵȼ��Ĵ�С
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
	void BroadCast(const char* data, size_t size); //�����ڹ㲥
	void UpdateOnlineStatus(ActorId aid, bool isOnline);
	void NotifyUpdateGuildInfo(uint8_t type);

public:
	int id_;  //����id
	int sid_; //���ڵķ�����ID
	char name_[32]; //��������
	char leadername_[32]; //��������
	char memo_[MAXMEMOCOUNT];		//�ⲿ������Ϣ
	int64_t	level_; // �ȼ�4���ֽڣ��ӵ͵��ߣ��ֱ����4�������ĵȼ�
	int icon_;
	int rank_;	//����
	int stone_;	//��Ǯ
	int all_actor_count_; //��������
	int depot_availible_; //���ɲֿ�ʣ������

	//GuildManagerInfo	leader_info_;

	int fight_val_;	//��ս��

	BinaryList<int64_t> actor_list_; // ����������ߵ���ҵ�handle�б�
};


typedef Vector<LfGuild*> LfGuildList;

// �������ڹ���
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
	void NotifyUpdateGuildInfo(uint8_t type); //ȫ���㲥
	
	LfGuild* GetGuild(int gid); // ��ȡ������Ϣ
	LfGuildList& GetGuildList() { return guild_list_; } // ��ȡ�����б�
public:
	void UpdateGuildList(); //���������б�
	//void OnCreateGuild(Guild* guild); //��������
	//void OnDeleteGuild(int gid);	//ɾ������
	//void OnUpdateGuild(Guild* guild); //���ɸ���
	//void OnAddGuildMember(ActorId actorId, int guildId); // ��Ӱ��ɳ�Ա
	//void OnDelGuildMember(ActorId actorId, int gid); // ɾ�����ɳ�Ա
	//void GuildBroadCast(int sid, int gid, const void* data, size_t size, bool all = true); // ���ڹ㲥������������������
	//void BroadCastToLianfu(int gid, const void* data, size_t size);// ���͵������������㲥
	//void SendGuildOnlineStatus(int gid, ActorId aid, char status); // ��Ա����״̬
	//void SendGuildLeaderInfo(GuildManagerInfo& gmi, int gid);
	//void OnAddItemToDepot(int gid, int itemId, int count, int quality, int logId);
	//void OnAddGuildLog(int guildId, unsigned char tp, int aid, const char* name1, const char* name2, int param1, int param2, int param3);
	//void SendGuildFightVal(int fightVal, int gid);
	//void HandleGuildFightVal(DataPacketReader& packet);
	//void ChangePos(DataPacketReader& packet);	//�ı����ְλ
	//void SendDepotAvailible(Guild* guild);	//���ɲֿ�ʣ��λ��
public:
	void HandleGuildList(DataPacketReader& packet); //������������б�
	void HandleCreateGuild(DataPacketReader& packet); //����������
	void HandleDeleteGuild(DataPacketReader& packet); //����ɾ������
	void HandleUpdateGuild(DataPacketReader& packet); //������ɸ���
	void HandleAddGuildMember(DataPacketReader& packet); //������Ӱ��ɳ�Ա
	void HandleDelGuildMember(DataPacketReader& packet); //����ɾ�����ɳ�Ա
	void HandleGuildBroadCast(DataPacketReader& packet); //������ɹ㲥
	void HandleMemberStatus(DataPacketReader& packet); //������ɳ�Ա����״̬
	void HandleGuildOnlineStatus(DataPacketReader& packet); 
	void HandleGuildLeaderInfo(DataPacketReader& packet);
	void HandleAddItemToDepot(DataPacketReader& packet); //������ӵ��ߵ����ɲֿ�
	void HandleAddGuildLog(DataPacketReader& packet);//�������������Ӱ�����־
	void HandleDepotAvailible(DataPacketReader& packet); //������ɲֿ�ʣ��λ��
	void HandleImpeach(DataPacketReader& packet); //������ְλ���
private:
	// �Ƿ�����
	bool IsLianfu();
	// �������
	LfGuild* AddGuild(int gid, int64_t level);
	// ɾ������
	void DeleteGuild(int gid);
	// ������������
	void AdjustRank(LfGuild* guild);
private:
	StaticHashTable<LfGuild*, MAX_GUILD> all_guild_; // ����id : ������Ϣ(��ϣ��)
	LfGuildList guild_list_;
	ObjList<LfGuild>* guild_allocator_;

	bool guild_loaded_; // �Ƿ��Ѿ�������������
	bool guild_update_; // �Ƿ��Ѿ�����������Ϣ
};

#endif