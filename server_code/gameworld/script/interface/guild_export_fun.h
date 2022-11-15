
//tolua_begin

namespace LGuild
{
	/*
	* Comments: 获取静态变量
	* Param void* 帮派指针
	* Param bool 是否会修改数据，默认是false，如果会修改里面的数据需要传个true
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
	// 获取公会成员信息，参数为公会指针，成员玩家ID
	int getMemberInfo(lua_State* L);
	bool isMember(void* guild, int actor_id);
	// 获取自动同意入会申请设置
	int  getAutoApprove(lua_State* L);
	void setAutoApprove(void * guild, unsigned char bauto, int need_fight);
	// 获取公会列表
	int getGuildList(lua_State* L);
	// 获取对应职位的人数
	int getGuildPosMemberCount(lua_State* L);
	int getMemberIdList(lua_State* L);
	//获取申请列表
	int getJoinMsgIdList(lua_State* L);

	bool postJoinMsg(void* guild, void* actor);
	bool removeJoinMsg(void* guild, int actorId);
	bool getJoinMsg(void* guild, int actorId);

	int getGuildPos(void* guild, int actorId);
	bool changeGuildPos(void* guild, int actorId, int pos);

	void updateGuildPos(void * guild);
	// 获取贡献最大的玩家的ID
	int getLargestContribution(void * guild);

	// 添加公会事件
	void addGuildLog(void* guild, unsigned char tp, const char* name1 = "", const char* name2 = "", int param1 = 0, int param2 = 0, int param3 = 0);

	void broadcastData(void* guild, void* dp);

	void setGuildLevel(void* guild, int level, int levelupTime);
	void setGuildAffairLevel(void* guild, int level);
	void updateGuildRank(void* guild);

	//获取公会等级
	int getGuildLevel(void* guild);

	// 添加一条聊天记录
	void addChatLog(void* guild, int type, const char* content, void* actor = 0,int time = 0);
	// 把聊天消息写入到消息包中
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
	int getOnlineActor(lua_State* l); //得到所有在线的actor

	const char* getLeaderName(void* guile);

	void* getOnlineLeaderActor(void* guile);

	//获取成员贡献
	int GetMemberTotalGx(void* guild, int actor_id);
	
	int getChangeNameCount(void* guile);
	void setChangeNameCount(void* guile, int num);
	bool changeName(void* guile, const char * name);
};

//tolua_end
