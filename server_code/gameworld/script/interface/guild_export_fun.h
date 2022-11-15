
//tolua_begin

namespace LGuild
{
	/*
	* Comments: ��ȡ��̬����
	* Param void* ����ָ��
	* Param bool �Ƿ���޸����ݣ�Ĭ����false��������޸������������Ҫ����true
	* @Returns int:
	*/
	int getStaticVar(lua_State* L);
	bool nameHasUsed(const char* name);
	void* createGuild(const char* name, void* actor);
	void deleteGuild(void* guild, const char* reason = "");
	void deleteMember(void* guild, int actorId);
	void addMember(void* guild, void* actor, int pos);
	void* getGuildById(int guildId);
	void* getGuildByName(const char* name);
	const char* getGuildName(void* guild);
	int getGuildMemberCount(void* guild);
	int getGuildId(void* guild);
	void setUpdate(void* guild);
	int getLeaderId(void* guild);
	// ��ȡ�����Ա��Ϣ������Ϊ����ָ�룬��Ա���ID
	int getMemberInfo(lua_State* L);
	bool isMember(void* guild, int actor_id);
	// ��ȡ�Զ�ͬ�������������
	int  getAutoApprove(lua_State* L);
	void setAutoApprove(void * guild, unsigned char bauto, int need_fight);
	// ��ȡ�����б�
	int getGuildList(lua_State* L);
	// ��ȡ��Ӧְλ������
	int getGuildPosMemberCount(lua_State* L);
	int getMemberIdList(lua_State* L);
	//��ȡ�����б�
	int getJoinMsgIdList(lua_State* L);

	bool postJoinMsg(void* guild, void* actor);
	bool removeJoinMsg(void* guild, int actorId);
	bool getJoinMsg(void* guild, int actorId);

	int getGuildPos(void* guild, int actorId);
	bool changeGuildPos(void* guild, int actorId, int pos);

	void updateGuildPos(void * guild);
	// ��ȡ����������ҵ�ID
	int getLargestContribution(void * guild);

	// ��ӹ����¼�
	void addGuildLog(void* guild, unsigned char tp, const char* name1 = "", const char* name2 = "", int param1 = 0, int param2 = 0, int param3 = 0);

	void broadcastData(void* guild, void* dp);

	void setGuildLevel(void* guild, int level, int levelupTime);
	void setGuildAffairLevel(void* guild, int level);
	void updateGuildRank(void* guild);

	//��ȡ����ȼ�
	int getGuildLevel(void* guild);

	// ���һ�������¼
	void addChatLog(void* guild, int type, const char* content, void* actor = 0,int time = 0);
	// ��������Ϣд�뵽��Ϣ����
	void writeChatLog(void* guild, void* pack);

	void clearChatLog(void * guild);
	// 
	void resetTodayContrib(void* guild);
	//
	void addStoreLog(void * guild, void* actor,  int item_id);
	// 
	void writeStoreLog(void* guild, unsigned int last_time, void* pack);
	// 
	//
	int getOnlineActor(lua_State* l); //�õ��������ߵ�actor

	const char* getLeaderName(void* guile);

	void* getOnlineLeaderActor(void* guile);

	//��ȡ��Ա����
	int GetMemberTotalGx(void* guild, int actor_id);
	
	int getChangeNameCount(void* guile);
	void setChangeNameCount(void* guile, int num);
	bool changeName(void* guile, const char * name);
};

//tolua_end
