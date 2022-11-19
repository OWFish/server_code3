#include "StdAfx.h"
#include "../interface/guild_export_fun.h"
#include "systems/guild/guild.h"
#include "../interface/actor_export_fun.h"

namespace LGuild
{

int getStaticVar(lua_State * L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);
	bool modify = (tolua_toboolean(L, 2, false) != 0);

	if (!guild)
		return 0;

	if (modify)
		guild->update_ = true;

	return LuaCLVariant::returnValue(L, guild->GetVar());
}

bool nameHasUsed(const char * name)
{
	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();

	return mgr->NameHasUsed(name);
}

void * createGuild(const char * name, void* actor)
{
	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
	return mgr->CreateGuild(name, (Actor*)actor);
}

void deleteGuild(void* guild, const char* reason/* = NULL*/)
{
	if (!guild) return;

	static GuildMgr* gm = GetGameEngine()->GetGuildMgr();
	gm->DeleteGuild((Guild*)guild, reason);
}

void deleteMember(void* guild, int actorId)
{
	if (!guild) return;

	((Guild*)guild)->DeleteMember(actorId);
}

void addMember(void * guild, void * actor, int pos)
{
	if (!guild || !actor || ((Entity*)actor)->GetType() != EntityType_Actor) return ;

	((Guild*)guild)->AddMemberToList((Actor*)actor, pos);
}

void* getGuildById(int guildId)
{
	static GuildMgr* gm = GetGameEngine()->GetGuildMgr();
	return gm->FindGuild(guildId);
}

void * getGuildByName(const char * name)
{
	static GuildMgr* gm = GetGameEngine()->GetGuildMgr();
	return gm->FindGuildByName(name);
}

const char * getGuildName(void * guild)
{
	if (!guild) return "";

	return ((Guild*)guild)->name_;
}

int getGuildMemberCount(void * guild)
{
	if (!guild) return 0;

	return ((Guild*)guild)->GetMemberCount();
}

int getGuildId(void * guild)
{
	if (!guild) return 0;

	return ((Guild*)guild)->id_;
}

void setUpdate(void * guild)
{
	if (!guild) return ;

	((Guild*)guild)->update_ = true;
}

int getLeaderId(void* guild)
{
	if (!guild) return 0;

	return ((Guild*)guild)->leader_id_;
}

int getMemberInfo(lua_State* L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);

	if (!guild) return 0;

	int aid = (int)lua_tointeger(L, 2);

	GuildMemberNode* node = ((Guild*)guild)->FindMember(aid);

	if (!node) return 0;

	lua_pushstring(L, node->data_.actor_name_);
	lua_pushinteger(L, node->data_.level_);
	lua_pushinteger(L, node->data_.job_);
	lua_pushnumber(L, node->data_.fight_);
	lua_pushnumber(L, node->data_.lastLogoutTime_);
	lua_pushnumber(L, node->data_.sex_);
	return 6;
}

bool isMember(void* guild, int actor_id)
{
	if (!guild)
	{
		return false;
	}
	auto* node = ((Guild*)guild)->FindMember(actor_id);
	if (!node)
	{
		return false;
	}
	return true;
}

int getAutoApprove(lua_State* L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);
	if (!guild) return 0;

	lua_pushinteger(L, guild->auto_);
	lua_pushinteger(L, guild->need_fight_);
	return 2;
}

void setAutoApprove(void * guild, unsigned char bauto, int need_fight)
{
	if (!guild) return;

	((Guild*)guild)->auto_ = bauto;
	((Guild*)guild)->need_fight_ = need_fight;
}

int getGuildList(lua_State* L)
{
	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
	Guild** list = mgr->rank_;
	LuaHelp::PushDataPointerToTable(L, (void**)list, mgr->rank_.count());

	return 1;
}

int getGuildPosMemberCount(lua_State* L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);
	if (!guild) return 0;
	int pos = (int)lua_tonumber(L, 2);
	if (pos < smGuildCommon || pos >= smGuildLeader)
	{
		return -1;
	}

	int count = 0;
	ListIterator<GuildMemberInfo> it(guild->actor_list_);
	for (LinkedNode<GuildMemberInfo>* node = it.first(); node && count < Guild::MAX_MEMBER; node = it.next())
	{
		GuildMemberInfo& actor = node->data_;
		if(actor.pos_ == pos)
			count++;
	}
	lua_pushnumber(L, count);
	return 1;
}

int getMemberIdList(lua_State* L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);
	if (!guild) return 0;

	ActorId ret[Guild::MAX_MEMBER];
	int count = 0;

	ListIterator<GuildMemberInfo> it(guild->actor_list_);

	for (LinkedNode<GuildMemberInfo>* node = it.first(); node && count < Guild::MAX_MEMBER; node = it.next())
	{
		GuildMemberInfo& actor = node->data_;
		ret[count++] = actor.actorId_;
	}

	LuaHelp::PushNumberVector(L, ret, count);
	return 1;
}

int getJoinMsgIdList(lua_State * L)
{
	Guild* guild = (Guild*)lua_touserdata(L, 1);
	if (!guild) return 0;

	int need_power = guild->need_fight_;

	ActorId ret[Guild::MAX_JOIN_MSG];
	BinaryList<Guild::JoinApply>& applyList = guild->inter_msg_list_;
	int count = applyList.count();

	for (int i = 0; i < count; i++)
	{
		Guild::JoinApply& applyInfo = applyList[i];
		auto pActorData = LActor::getActorDataById((int)applyInfo.actorId_);
		if (pActorData != nullptr && pActorData->total_power >= need_power)
			ret[i++] = (int)applyInfo.actorId_;
		else
			ret[i++] = 0;
	}

	LuaHelp::PushNumberVector(L, ret, count);
	return 1;
}

bool postJoinMsg(void * guild, void * actor)
{
	if (!guild || !actor || ((Entity*)actor)->GetType() != EntityType_Actor) return false;

	return ((Guild*)guild)->PostJoinMsg((Actor*)actor);
}

bool removeJoinMsg(void * guild, int actorId)
{
	if (!guild) return false;

	return ((Guild*)guild)->RemoveJoinMsg(actorId);
}

bool getJoinMsg(void * guild, int actorId)
{
	if (!guild) return false;

	return ((Guild*)guild)->GetJoinMsg(actorId);
}

int getGuildPos(void * guild, int actorId)
{
	if (!guild) return smGuildCommon;

	return ((Guild*)guild)->GetGuildPos(actorId);
}

bool changeGuildPos(void * guild, int actorId, int pos)
{
	if (!guild) return false;

	return ((Guild*)guild)->ChangeGuildPos(actorId, pos);
}

void updateGuildPos(void * guild)
{
	if (!guild) return;
	((Guild*)guild)->UpdateGuildPos();
}

int getLargestContribution(void * guild)
{
	if (!guild) return 0;
	return ((Guild*)guild)->GetLargestContribution();
}

void addGuildLog(void * guild, unsigned char tp, const char * name1, const char * name2, int param1, int param2, int param3)
{
	if (!guild) return;

	((Guild*)guild)->AddGuildLog(tp, name1, name2, param1, param2, param3);
}

void broadcastData(void * guild, void * dp)
{
	if (!dp || !guild) return;

	DataPacket* pack = (DataPacket*)dp;

	((Guild*)guild)->BroadCast(pack->getMemoryPtr(), pack->getLength());
}

void setGuildLevel(void * guild, int level, int levelupTime)
{
	if (!guild) return;

	((Guild*)guild)->SetGuildLevel(level);
	((Guild*)guild)->SetGuildLevelupTime(levelupTime);
}

void setGuildAffairLevel(void * guild, int level)
{
	if (!guild) return;

	((Guild*)guild)->SetGuildAffairLevel(level);
}

void updateGuildRank(void* guild)
{
	if (!guild) return;
	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
	mgr->AdjustRank((Guild*)guild);
}

int getGuildLevel(void * guild)
{
	if (!guild) return 0;

	return ((Guild*)guild)->GetGuildLevel();
}

void addChatLog(void * guild, int type, const char * content, void * actor,int time)
{
	if (!guild) return;

	((Guild*)guild)->AddChatLog((uint8_t)type, content, (Actor*)actor,time);
}

void writeChatLog(void * guild, void * pack)
{
	if (!guild || !pack) return;

	Guild* guild_ptr = (Guild*)guild;
	DataPacket& dp = *(DataPacket*)pack;

	const std::vector<GuildChatLog>& logs = guild_ptr->GetChatLogs();
	int count = (int)logs.size();
	dp << (int)count;
	for (int i = 0; i < count; i++)
	{
		const GuildChatLog& log = logs[i];
		dp << (uint8_t)log.type_;
		dp << (int)log.time_;
		dp << log.content_.c_str();
		if (log.type_ == enGuildChatChat)
		{
			dp << (int)log.actor_id_;
			dp << log.actor_name_.c_str();
			dp << (uint8_t)log.job_;
			dp << (uint8_t)log.sex_;
			dp << (int)log.vip_level_;
			dp << (uint8_t)log.month_card_;
			dp << (uint8_t)log.pos_;
			dp << (uint8_t)log.zs_lv_;
			dp << (uint16_t)log.level_;
			dp << guild_ptr->name_;
			dp << (int)log.headID;
		}
		//dp << (int)log.time_;
	}
}

void clearChatLog(void * guild)
{
	((Guild*)guild)->clearGuildChat();
}

void resetTodayContrib(void * guild)
{
	if (!guild) return;

	((Guild*)guild)->ResetTodayContrib();
}


void addStoreLog(void * guild, void* actor, int item_id)
{
	if (!guild) return;
	if (!actor) return;

	((Guild*)guild)->AddGuildStoreLog(((Actor*)actor)->GetActorId(), ((Actor*)actor)->GetActorName(), item_id);
}

void writeStoreLog(void * guild, unsigned int last_time, void * pack)
{
	if (!guild || !pack) return;

	Guild* guild_ptr = (Guild*)guild;
	DataPacket& dp = *(DataPacket*)pack;

	const Vector<GuildStoreLog>& logs = guild_ptr->GetGuildStoreLogs();
	uint8_t count = 0;
	int pos = static_cast<int>( dp.getPosition() );
	dp << (uint8_t)count;
	for (int i = logs.size()-1; i >= 0 ; --i)
	{
		const GuildStoreLog& log = logs[i];
		if (0 == last_time || log.time_ > last_time)
		{
			dp << log.time_;
			dp << log.actor_name_;
			dp << log.item_id_;
			count++;
		}
	}
	
	int newPos = static_cast<int>(dp.getPosition());
	dp.setPosition(pos);
	dp << (uint8_t)count;
	dp.setPosition(newPos);
}


int getOnlineActor(lua_State* l)
{
	int guild_id = (int)lua_tonumber(l, 1);
	if (guild_id == 0)
	{
		return 0;
	}
	Guild* guild = (Guild*)getGuildById(guild_id);
	if (guild == nullptr)
	{
		return 0;
	}
	auto ret = guild->getOnlineActor();
	if (!ret.empty())
	{
		LuaHelp::PushDataPointerToTable(l, (void**)&ret[0], ret.size());
		return 1;
	}
	return 0;
}
const char* getLeaderName(void* guile)
{
	if (guile == nullptr)
	{
		return nullptr;
	}

	return ((Guild*)guile)->leadername_;
}
void* getOnlineLeaderActor(void* guile)
{
	if (!guile)
	{
		return nullptr;
	}
	ActorId actor_id = getLeaderId(guile);
	return LActor::getActorById(actor_id);
}

int GetMemberTotalGx(void* guild, int actor_id)
{
	if (guild && actor_id)
	{
		return ((Guild*)guild)->GetMemberTotalGx(actor_id);
	}
	return 0;
}

int getChangeNameCount(void* guile) {
	if (!guile)
		return 0;
	return ((Guild*)guile)->change_name_count;
}

void setChangeNameCount(void* guile, int num) {
	if (!guile || num < 0)
		return;
	((Guild*)guile)->change_name_count = num;
	((Guild*)guile)->update_base_ = true;
}

bool changeName(void* guile, const char * name) {
	if (!guile)
		return false;
	return ((Guild*)guile)->changeName(name);
}

};

