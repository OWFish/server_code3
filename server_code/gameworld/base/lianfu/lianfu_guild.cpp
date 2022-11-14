#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

int rank_;	//排名
int stone_;	//金钱
int all_actor_count_; //宗里人数
int depot_availible_; //帮派仓库剩余数量

LfGuild::LfGuild() : id_(0), sid_(0), level_(0), icon_(0), rank_(0), stone_(0), all_actor_count_(0), depot_availible_(0), fight_val_(0)
{
	ZeroMemory(name_, sizeof(name_));
	ZeroMemory(leadername_, sizeof(leadername_));
	ZeroMemory(memo_, sizeof(memo_));
}

void LfGuild::UpdateOnlineStatus(ActorId aid, bool isOnline)
{
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& pack = mgr.AllocSendPacket(lsGuild, lcUpGuildMemInfo);

#pragma pack(push, 1)
	static struct Data {
		int id_;
		int aid_;
		uint8_t status_;

		Data() {}
	} data;
#pragma pack(pop)

	data.id_ = id_;
	data.aid_ = aid;
	data.status_ = isOnline;

	pack.writeBuf(&data, sizeof(data));

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(pack.getMemoryPtr(), pack.getLength(), gpLfData, sid_, CROSSSERVER_LIANFU);

	// 通知连服玩家更新在线列表
	NotifyUpdateGuildInfo(Guild::dtGuildMem);
}

void LfGuild::NotifyUpdateGuildInfo(uint8_t type)
{
	static uint8_t hdr[] = { enGuildSystemID, sUpdateGuildInfo, type };
	BroadCast((char*)(&hdr), sizeof(hdr));
}

void LfGuild::BroadCast(const char* data, size_t size)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = actor_list_.count();
	int64_t* list = (int64_t*)actor_list_;
	for (int i = 0; i < count; i++)
	{
		Entity* et = em->GetEntity(list[i]);
		if (et && et->GetType() == enActor)
		{
			((Actor*)et)->SendData(data, size);
		}
	}
}

void LfGuild::OnLogin(Actor* actor)
{
	if (!actor) return;

	ActorId aid = actor->GetActorId();
	actor_list_.add(actor->GetHandle());

	UpdateOnlineStatus(aid, true);
}

void LfGuild::OnLogout(Actor* actor)
{
	if (!actor) return;

	ActorId aid = actor->GetActorId();
	int idx = actor_list_.find(actor->GetHandle());
	if (idx < 0) return;

	actor_list_.remove(idx);

	UpdateOnlineStatus(aid, false);
}

void LfGuild::OnAddMember(ActorId aid)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(aid);
	if (actor)
	{
		int64_t hdl = actor->GetHandle();
		int idx = actor_list_.find(hdl);
		if (idx < 0)
		{
			actor_list_.add(hdl);
		}
	}

	all_actor_count_++;
}

void LfGuild::OnDelMember(ActorId aid)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(aid);
	if (actor)
	{
		int idx = actor_list_.find(actor->GetHandle());
		if (idx >= 0)
		{
			actor_list_.remove(idx);
			((Entity*)actor)->SetIntProp(P_GUILD_ID, 0);
			actor->ResetShowName();
	
			GuildSystem& gs = actor->GetGuildSystem();
			gs.SetSave();
			gs.SetGuildPos(-1);

			actor->GetQuestSystem().ClearGuildQuest();
			ScriptValueList plist;
			static GameScript& lua = GetGameEngine()->GetGlobalNpc()->GetScript();
			plist << actor;
			plist << name_;
			lua.Call("onLfKick", &plist, &plist);
		}
	}

	all_actor_count_--;
}


/* ======================= LianfuGuild ======================= */
LianfuGuild::LianfuGuild() : guild_loaded_(false), guild_update_(false)
{
	guild_allocator_ = new ObjList<LfGuild>("lfguild pool", "lfguild mgr alloc");
}

LianfuGuild::~LianfuGuild()
{
	LfGuild** list = guild_list_;

	// 释放仙宗列表
	for (int i = guild_list_.count() - 1; i >= 0; i--)
	{
		LfGuild* guild = list[i];
		guild_allocator_->release(guild);
	}
	
	guild_list_.clear();

	if (guild_allocator_)
	{
		delete guild_allocator_;
		guild_allocator_ = NULL;
	}
}

bool LianfuGuild::IsLianfu()
{
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	return mgr.IsLianfu();
}

void LianfuGuild::OnLoadGuild()
{
	guild_loaded_ = true;

	if (!IsLianfu()) return;

	UpdateGuildList();
}

LfGuild* LianfuGuild::GetGuild(int gid)
{
	LfGuild** pp = all_guild_.get(gid);
	if (pp) return *pp;

	return NULL;
}

void LianfuGuild::ProcessNetData(int cmd, DataPacketReader& packet)
{
	switch (cmd)
	{
	case lcGuildList:
		HandleGuildList(packet);
		break;
	case lcCreateGuild:
		HandleCreateGuild(packet);
		break;
	case lcDelGuild:
		HandleDeleteGuild(packet);
		break;
	case lcUpdateGuild:
		HandleUpdateGuild(packet);
		break;
	case lcDelGuildMem:
		HandleDelGuildMember(packet);
		break;
	case lcAddGuildMem:
		HandleAddGuildMember(packet);
		break;
	case lcGuildBroadCast:
		HandleGuildBroadCast(packet);
		break;
	case lcUpGuildMemInfo:
		HandleGuildOnlineStatus(packet);
		break;
	case lcGuildOnline:
		HandleMemberStatus(packet);
		break;
	case lcGuildLeaderInfo:
		HandleGuildLeaderInfo(packet);
		break;
	case lcAddItemToDepot:
		HandleAddItemToDepot(packet);
		break;
	case lcAddGuildLog:
		HandleAddGuildLog(packet);
		break;
	case lcSendFightVal:
		HandleGuildFightVal(packet);
		break;
	case lcChangePos:
		ChangePos(packet);
		break;
	case lcDepotAvailible:
		HandleDepotAvailible(packet);
		break;
	case lcImpeach:
		HandleImpeach(packet);
		break;
	default:
		break;
	}
}

void LianfuGuild::NotifyUpdateGuildInfo(uint8_t type)
{
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	static uint8_t hdr[3] = { enGuildSystemID, sUpdateGuildInfo};
	hdr[2] = (uint8_t)type;
	mgr.BroadCast(ciChannelWorld, 0, (char*)(&hdr), sizeof(hdr));
}

void LianfuGuild::UpdateGuildList()
{
	if (!guild_loaded_)
	{
		OutputMsg(rmError, "update guild list error, guild is not loaded!");
		return;
	}

	static GuildMgr& guildMgr = GetGameEngine()->GetGuildMgr();
	static GameServer* gs = ServerInstance();
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	int sid = gs->GetServerIndex();

	if (!gs->IsCommonSrv())
	{
		OutputMsg(rmError, "update guild list error, is not common server!");
		return;
	}
	
	Guild** list = guildMgr.rank_;
	int total = guildMgr.rank_.count();
	const int max_send = 32;
	int pageCnt = total / max_send;
	if (total % max_send > 0) pageCnt++;

	int start = 0;
	for (int idx = 0; idx < pageCnt; idx++)
	{
		DataPacket& pack = mgr.AllocSendPacket(lsGuild, lcGuildList);
		pack << (int)sid << (int)pageCnt << (int)idx;

		int cnt = __min(max_send, total - start);

		pack << (int)cnt;

		for (int idx = start; idx < start + cnt; idx++)
		{
			Guild* guild = list[idx];

			pack << (int)guild->id_;
			pack << (int64_t)guild->GetLevelData();
			pack << (int)guild->GetStone();
			pack << (int)guild->GetMemberCount();
			pack << (int)guild->icon_;
			pack.writeString(guild->name_);
			pack.writeString(guild->leadername_);
			pack.writeString(guild->GetMemo());
			pack.writeBuf(&guild->leader_, sizeof(GuildManagerInfo));
			pack << (int)guild->fight_val_;
			pack << (int)guild->GetGuildDepotEmptyGridCount();
		}

		gs->SendMsgToAllGameClient(pack.getMemoryPtr(), pack.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);

		start += cnt;
	}

	guild_update_ = true;
}

void LianfuGuild::HandleGuildList(DataPacketReader& packet)
{
#pragma pack(push, 1)
	static struct PageInfo
	{
		int sid_;
		int page_cnt_;
		int page_idx_;
		int item_cnt_;
	} page;

	static struct Data
	{
		int id_;
		int64_t level_;
		int stone_;
		int count_;
		int icon_;
	} data;
#pragma pack(pop)

	packet.readBuf(&page, sizeof(page));

	for (int i = 0; i < page.item_cnt_; i++)
	{
		packet.readBuf(&data, sizeof(data));

		LfGuild* info = AddGuild(data.id_, data.level_);
		if (!info)
		{
			OutputMsg(rmError, "HandleGuildList error : unable add guild");
			return;
		}

		info->sid_ = page.sid_;
		info->stone_ = data.stone_;
		info->all_actor_count_ = data.count_;
		info->icon_ = data.icon_;
		packet.readString(info->name_, sizeof(info->name_));
		packet.readString(info->leadername_, sizeof(info->leadername_));
		packet.readString(info->memo_, sizeof(info->memo_));
		packet.readBuf(&info->leader_info_, sizeof(GuildManagerInfo));
		packet >> info->fight_val_;
		packet >> info->depot_availible_;
	}

	if (page.page_idx_ == page.page_cnt_ - 1)
	{
		OutputMsg(rmError, "receive guild list from server %d", page.sid_);

		ScriptValueList paramList;
		static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();
		pNpc->GetScript().Call("onMyLianFuGuildLoaded", &paramList, &paramList);
	}
}

LfGuild* LianfuGuild::AddGuild(int gid, int64_t level)
{
	LfGuild** pp = all_guild_.get(gid);
	if (pp) return (*pp);

	if ((int)all_guild_.count() >= MAX_GUILD)
	{
		OutputMsg(rmError, "add guild error:max");
		return NULL;
	}

	LfGuild* guild = guild_allocator_->get();
	if (!guild) return NULL;

	guild->id_ = gid;
	guild->level_ = level;
	guild_list_.add(guild);
	all_guild_.put(gid, guild);
	guild->rank_ = guild_list_.count();

	AdjustRank(guild);

	return guild;
}

void LianfuGuild::AdjustRank(LfGuild* guild)
{
	if (!guild) return;

	int count = guild_list_.count();
	LfGuild** list = guild_list_;

	int pos = guild->rank_ - 1;

	if (guild_list_[pos] != guild)
	{
		// 异常
		OutputMsg(rmError, "------guild rank error!!");
		pos = -1;

		for (int j = 0; j < count; ++j)
		{
			LfGuild* curr_guild = list[j];

			if (guild == curr_guild)
			{
				pos = j;
				break;
			}
		}
	}

	if (pos < 0) return; //异常

	bool move = false;	// 是否有移动位置

	for (int i = pos - 1; i >= 0; --i)
	{
		LfGuild* curr = list[i];

		if (guild->Compare(curr) > 0)
		{
			// 交换下位置
			move = true;
			list[i] = guild;
			list[i + 1] = curr;
			guild->rank_ = curr->rank_;
			curr->rank_ += 1;
		}
		else
		{
			break;
		}
	}

	// 没往前移，则看看有没有必要往后移
	if (!move)
	{
		for (int i = pos + 1; i < count; ++i)
		{
			LfGuild* curr = list[i];

			if (guild->Compare(curr) < 0)
			{
				// 交换下位置
				list[i] = guild;
				list[i - 1] = curr;
				guild->rank_ = curr->rank_;
				curr->rank_ -= 1;
			}
			else
			{
				break;
			}
		}
	}
}

void LianfuGuild::OnCreateGuild(Guild* guild)
{
	if (!guild || !IsLianfu()) return;

	static GameServer* gs = ServerInstance();

#pragma pack(push, 1)
	static struct Data
	{
		int sid_;
		int gid_;
		int64_t level_;
		int stone_;
		int count_;
		int icon_;
		int depot_availible_;
	}data;
#pragma pack(pop)

	data.sid_ = gs->GetServerIndex();
	data.gid_ = (int)guild->id_;
	data.level_ = (int64_t)guild->GetLevel(); 
	data.stone_ = (int)guild->GetStone();
	data.count_ = (int)guild->GetMemberCount();
	data.icon_ = (int)guild->icon_;
	data.depot_availible_ = (int)guild->GetGuildDepotEmptyGridCount();

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();

	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcCreateGuild);
	dp.writeBuf(&data, sizeof(data));
	dp.writeString(guild->name_);
	dp.writeString(guild->leadername_);
	dp.writeString(guild->GetMemo());
	dp << guild->fight_val_;

	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleCreateGuild(DataPacketReader& packet)
{
#pragma pack(push, 1)
	static struct Data
	{
		int sid_;
		int gid_;
		int64_t level_;
		int stone_;
		int count_;
		int icon_;
		int depot_availible_;
	}data;
#pragma pack(pop)

	packet.readBuf(&data, sizeof(data));

	LfGuild* guild = AddGuild(data.gid_, data.level_);
	if (!guild)
	{
		OutputMsg(rmError, "HandleCreateGuild error");
		return;
	}

	guild->sid_ = data.sid_;
	guild->stone_ = data.stone_;
	guild->icon_ = data.icon_;
	guild->all_actor_count_ = data.count_;
	guild->depot_availible_ = data.depot_availible_;

	packet.readString(guild->name_, sizeof(guild->name_));
	packet.readString(guild->leadername_, sizeof(guild->leadername_));
	packet.readString(guild->memo_, sizeof(guild->memo_));
	packet >> guild->fight_val_;

	NotifyUpdateGuildInfo(Guild::dtGuildList);
}

void LianfuGuild::DeleteGuild(int gid)
{
	LfGuild** pp = all_guild_.get(gid);
	if (!pp)
	{
		OutputMsg(rmError, "delete guild %d error:, not exist", gid);
		return;
	}

	LfGuild* guild = *pp;
	if (!guild)
	{
		OutputMsg(rmError, "delete guild(%d) error, ptr is null", gid);
		return;
	}
	
	all_guild_.remove(gid);

	int idx = guild->rank_ - 1;
	if (idx >= 0)
	{
		guild_list_.remove(idx);
		for (int i = idx; i < guild_list_.count(); i++) // 后面的排名减1
		{
			guild_list_[i]->rank_--;
		}
	}
	guild_allocator_->release(guild);
}

void LianfuGuild::OnDeleteGuild(int gid)
{
	if (!IsLianfu()) return;

	// 通知连服服务器
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcDelGuild);
	dp << (int)gid;

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleDeleteGuild(DataPacketReader& packet)
{
	int gid;
	packet >> gid;
	DeleteGuild(gid);
	
	NotifyUpdateGuildInfo(Guild::dtGuildListLf);
}

void LianfuGuild::OnUpdateGuild(Guild* guild)
{
	if (!guild) return;
	if (!IsLianfu()) return;

	// 通知连服服务器
	static GameServer* gs = ServerInstance();

#pragma pack(push, 1)
	static struct Data
	{
		int sid_;
		int gid_;
		int64_t level_;
		int stone_;
		int count_;
		int icon_;
	} data;
#pragma pack(pop)

	data.sid_ = gs->GetServerIndex();
	data.gid_ = (int)guild->id_;
	data.level_ = (int64_t)guild->GetLevelData();
	data.stone_ = (int)guild->GetStone();
	data.count_ = (int)guild->GetMemberCount();
	data.icon_ = (int)guild->icon_;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcUpdateGuild);
	dp.writeBuf(&data, sizeof(data));
	dp.writeString(guild->name_);
	dp.writeString(guild->leadername_);
	dp.writeString(guild->GetMemo());

	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleUpdateGuild(DataPacketReader& packet)
{
#pragma pack(push, 1)
	static struct Data
	{
		int sid_;
		int gid_;
		int64_t level_;
		int stone_;
		int count_;
		int icon_;
	} data;
#pragma pack(pop)

	packet.readBuf(&data, sizeof(data));

	LfGuild* guild = GetGuild(data.gid_);

	if (!guild)
	{
		OutputMsg(rmError, "HandleUpdateGuild error");
		return;
	}

	bool adjust = (data.level_ != guild->level_ || data.stone_ != guild->stone_);

	guild->sid_ = data.sid_;
	guild->level_ = data.level_;
	guild->stone_ = data.stone_;
	guild->icon_ = data.icon_;
	guild->all_actor_count_ = data.count_;

	packet.readString(guild->name_, sizeof(guild->name_));
	packet.readString(guild->leadername_, sizeof(guild->leadername_));
	packet.readString(guild->memo_, sizeof(guild->memo_));

	if (adjust)
	{
		AdjustRank(guild);
	}

	NotifyUpdateGuildInfo(Guild::dtGuildList);
}

void LianfuGuild::OnAddGuildMember(ActorId actorId, int guildId)
{
	if (!IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcAddGuildMem);
	dp << (int)actorId;
	dp << (int)guildId;

	mgr.SendToLianfuServer(dp.getMemoryPtr(), dp.getLength());
}

void LianfuGuild::HandleAddGuildMember(DataPacketReader& packet)
{
	int actorId, guildId;
	packet >> actorId;
	packet >> guildId;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(actorId);
	if (!actor) return;
	
	actor->GetGuildSystem().SetGuildId(guildId);

	LfGuild* guild = GetGuild(guildId);
	if (guild)
	{
		guild->OnAddMember(actorId);
	}
}

void LianfuGuild::OnDelGuildMember(ActorId actorId, int gid)
{
	if (!IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcDelGuildMem);
	dp << (int)actorId << (int)gid;

	mgr.SendToLianfuServer(dp.getMemoryPtr(), dp.getLength());
}

void LianfuGuild::HandleDelGuildMember(DataPacketReader& packet)
{
	int actorId, gid;
	packet >> actorId;
	packet >> gid;

	LfGuild* guild = GetGuild(gid);
	if (guild)
	{
		guild->OnDelMember(actorId);
	}
}

void LianfuGuild::GuildBroadCast(int sid, int gid, const void* data, size_t size, bool all /* = true */)
{
	LfGuild* guild = GetGuild(gid);
	if (guild)
	{
		guild->BroadCast((const char*)data, size);
	}

	if (all)
	{
		static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
		DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcGuildBroadCast);
		dp << (int)gid;
		dp.writeBuf(data, size);

		static GameServer* gs = ServerInstance();
		gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, sid);
	}
}

void LianfuGuild::BroadCastToLianfu(int gid, const void* data, size_t size)
{
	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcGuildBroadCast);
	dp << (int)gid;
	dp.writeBuf(data, size);

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid());
}

void LianfuGuild::HandleGuildBroadCast(DataPacketReader& packet)
{
	int gid;
	packet >> gid;

	static GameServer* gs = ServerInstance();
	if (gs->IsCommonSrv())
	{
		static char buf[1024 * 8];
		size_t len = packet.readBuf(buf, __min(sizeof(buf), packet.getAvaliableLength()));
		static GuildMgr& guildMgr = GetGameEngine()->GetGuildMgr();
		Guild* guild = guildMgr.FindGuild(gid);
		if (!guild)
		{
			OutputMsg(rmError, "guild not exist:%d", gid);
			return;
		}

		guild->BroadCast(buf, len);
	}
	else if (gs->IsLianFuSrv())
	{
		LfGuild* guild = GetGuild(gid);
		if (guild)
		{
			guild->BroadCast(packet.getOffsetPtr(), packet.getAvaliableLength());
		}
	}
}

void LianfuGuild::SendGuildOnlineStatus(int gid, ActorId aid, char status)
{
	if (!IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcGuildOnline);
	dp << (int)gid;
	dp << (ActorId)aid;
	dp << (char)status;

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleMemberStatus(DataPacketReader& packet)
{
	int gid;
	ActorId aid;
	char status;
	packet >> gid;
	packet >> aid;
	packet >> status;

	LfGuild* guild = GetGuild(gid);
	if (!guild) return;

	guild->NotifyUpdateGuildInfo(Guild::dtGuildMem);
}

void LianfuGuild::HandleGuildOnlineStatus(DataPacketReader& packet)
{
	int gid, aid;
	uint8_t status;
	packet >> gid;
	packet >> aid;
	packet >> status;

	static GuildMgr& guildMgr = GetGameEngine()->GetGuildMgr();
	Guild* guild = guildMgr.FindGuild(gid);

	if (!guild) return;

	if (status != 0)
	{
		ActorNode* actor = guild->FindMember(aid);
		if (actor)
		{
			actor->data_.lianfu_ = true;
			guild->NotifyUpdateGuildInfo(Guild::dtGuildMem);
		}
	}
	else
	{
		ActorNode* actor = guild->FindMember(aid);
		if (actor)
		{
			actor->data_.lianfu_ = false;
			guild->NotifyUpdateGuildInfo(Guild::dtGuildMem);
			static GameEngine* ge = GetGameEngine();
			if(ge)guild->SetLastOnlineTime(ge->getMiniDateTime());
		}
	}
}

void LianfuGuild::SendGuildLeaderInfo(GuildManagerInfo& gmi, int gid)
{
	if (!IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcGuildLeaderInfo);
	dp << gid;
	dp.writeBuf(&gmi, sizeof(GuildManagerInfo));

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleGuildLeaderInfo(DataPacketReader& packet)
{
	int gid;
	packet >> gid;

	LfGuild* guild = GetGuild(gid);
	if (!guild) return;

	packet.readBuf(&guild->leader_info_, sizeof(GuildManagerInfo));

	_STRNCPY_A(guild->leadername_, guild->leader_info_.name_);
}


void LianfuGuild::SendGuildFightVal(int fightVal, int gid)
{
	if (!IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcSendFightVal);
	dp << gid << fightVal;

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleGuildFightVal(DataPacketReader& packet)
{
	int gid, fight_val;
	packet >> gid >> fight_val;

	LfGuild* guild = GetGuild(gid);
	if (!guild) return;

	guild->fight_val_ = fight_val;
}

void LianfuGuild::ChangePos(DataPacketReader& packet)
{
	if (!IsLianfu()) return;

	int actorid, pos, tip;
	packet >> actorid >> pos >> tip;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(actorid);
	if (!actor) return;

	GuildSystem& gs = actor->GetGuildSystem();
	gs.SetGuildPos(pos);
	gs.SetSave();
	actor->SendTipWithId(tip, ttWarmTip);
}

void LianfuGuild::OnAddItemToDepot(int gid, int itemId, int count, int quality, int logId)
{
	if (!IsLianfu()) return;

	LfGuild* guild = GetGuild(gid);
	if (!guild) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();

	DataPacket& pack = mgr.AllocSendPacket(lsGuild, lcAddItemToDepot);
	pack << (int)gid << (int)itemId << (int)count << (int)quality << (int)logId;
	
	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(pack.getMemoryPtr(), pack.getLength(), gpLfData, guild->sid_, CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleAddItemToDepot(DataPacketReader& packet)
{
	int gid, itemId, count, quality, logId;
	packet >> gid >> itemId >> count >> quality >> logId;

	GuildMgr& gm = GetGameEngine()->GetGuildMgr();
	Guild* guild = gm.FindGuild(gid);
	if (!guild) return;

	guild->AddItemToGuildDepot(itemId, count, quality, logId);
}

void LianfuGuild::OnAddGuildLog(int guildId, unsigned char tp, int aid, const char* name1, const char* name2, int param1, int param2, int param3)
{
	if (!IsLianfu()) return;

	LfGuild* guild = GetGuild(guildId);
	if (!guild) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();

	DataPacket& pack = mgr.AllocSendPacket(lsGuild, lcAddGuildLog);
	pack << (int)guildId << (char)tp << (int)aid;
	pack.writeString(name1);
	pack.writeString(name2);
	pack << (int)param1 << (int)param2 << (int)param3;

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(pack.getMemoryPtr(), pack.getLength(), gpLfData, guild->sid_, CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleAddGuildLog(DataPacketReader& packet)
{
	int guildId, aid, param1, param2, param3;
	char tp;
	ACTORNAME name1, name2;
	packet >> guildId >> tp >> aid;
	packet.readString(name1, ArrayCount(name1));
	packet.readString(name2, ArrayCount(name2));
	packet >> param1 >> param2 >> param3;

	GuildMgr& gm = GetGameEngine()->GetGuildMgr();
	Guild* guild = gm.FindGuild(guildId);
	if (!guild) return;

	guild->AddGuildLog(tp, aid, name1, name2, param1, param2, param3);
}

void LianfuGuild::SendDepotAvailible(Guild* guild)
{
	if (!guild || !IsLianfu()) return;

	static LianfuMgr& mgr = GetGameEngine()->GetLianfuMgr();
	DataPacket& dp = mgr.AllocSendPacket(lsGuild, lcDepotAvailible);
	dp << (int)guild->id_;
	dp << (int)guild->GetDepot().availableCount();

	static GameServer* gs = ServerInstance();
	gs->SendMsgToAllGameClient(dp.getMemoryPtr(), dp.getLength(), gpLfData, mgr.GetLianfuSid(), CROSSSERVER_LIANFU);
}

void LianfuGuild::HandleDepotAvailible(DataPacketReader& packet)
{
	int gid, cnt;
	packet >> gid >> cnt;

	LfGuild* guild = GetGuild(gid);
	if (!guild) return;

	guild->depot_availible_ = cnt;
}

void LianfuGuild::HandleImpeach(DataPacketReader& packet)
{
	if (!IsLianfu()) return;

	int actorid, pos;
	packet >> actorid >> pos;

	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrById(actorid);
	if (!actor) return;

	GuildSystem& gs = actor->GetGuildSystem();
	gs.SetGuildPos(pos);
	gs.SetSave();
}
