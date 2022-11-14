#include "StdAfx.h"
#include "net_handle_base.h"

#include "systems/guild/guild.h"
#include "systems/guild/guild_system.h"
#include "protocol/protos/guild_proto.h"
#include "actor/actor_data_mgr.h"
#include <iostream>

void OnGuildList(Actor* actor, DataPacketReader& reader)
{
	if (!actor) return;

	/*
#pragma pack(push, 1)
	struct CliData
	{
		int page_;
		int pcount_;
	} cliData;
#pragma pack(pop)

	reader.readBuf(&cliData, sizeof(cliData));	// 第几页，每页的数量

	if (cliData.pcount_ <= 0) cliData.pcount_ = 10; //每页默认显示数量
	if (cliData.page_ < 0) cliData.page_ = 0;
	*/

	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();

	ActorPacket AP;
	DataPacket& pack = actor->AllocPacket(AP);

	static uint8_t hdr[] = { Protocol::CMD_Guild, Protocol::sGuildCmd_GuildList };
	pack.writeBuf(hdr, sizeof(hdr));

	int total = mgr->rank_.count();

	/*
#pragma pack(push, 1)
	struct SendData
	{
		int count_;		// 本次下发的个数
		int page_;		// 当前第几页
		int pcount_;	// 一共多少页
	} sd;
#pragma pack(pop)

	sd.pcount_ = __max(1, (total % cliData.pcount_ == 0 ? (total / cliData.pcount_) : (total / cliData.pcount_ + 1)));
	sd.page_ = cliData.page_ >= sd.pcount_ ? sd.pcount_ - 1 : cliData.page_;
	int rest = total - cliData.pcount_ * sd.page_;
	sd.count_ = __min(rest, cliData.pcount_);

	pack.writeBuf(&sd, sizeof(sd));
	*/
	pack << (int)total;

	//if (sd.count_ > 0)
	if (total > 0)
	{
		int start = 0; //cliData.pcount_ * sd.page_;
		int end = total; //start + sd.count_;

		Guild** list = mgr->rank_;

		for (int i = start; i < end && i < total; ++i)
		{
			Guild* guild = list[i];
			pack << (int)guild->id_;
			pack << (unsigned char)guild->level_;
			pack << (unsigned char)guild->affair_level_;
			pack << (int)guild->GetMemberCount();
			pack.writeString(guild->name_);
			pack.writeString(guild->leadername_);
			pack << (int)guild->need_fight_;

			int headimage = 0;
			int leaderroleid = 0;
			static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
			if (data_mgr)
			{
				auto pActor = data_mgr->GetData(guild->leader_id_);
				if (pActor)
				{
					headimage = pActor->headimage;
					leaderroleid = pActor->actor_id;
				}
			}
			pack << headimage;
			pack << leaderroleid;
		}
	}

	AP.flush();
}

void OnGuildSearchList(Actor* actor, DataPacketReader& reader)
{
	if (!actor) return;

	std::string searchName;
	reader >> searchName;
	if (searchName.length() < 1)
		return;

	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();

	ActorPacket AP;
	DataPacket& pack = actor->AllocPacket(AP);

	static uint8_t hdr[] = { Protocol::CMD_Guild, Protocol::sGuildCmd_GuildSearchList };
	pack.writeBuf(hdr, sizeof(hdr));

#pragma pack(push, 1)
	struct SendData
	{
		int count_;		// 本次下发的个数
	} sd;
#pragma pack(pop)
	sd.count_ = 0;
	int total = mgr->rank_.count();
	Guild** list = mgr->rank_;
	Vector<Guild*> matchGuild;
	for (int i = 0; i < total; ++i)
	{
		Guild* guild = list[i];
		if (std::string(guild->name_).find(searchName) != std::string::npos)
		{
			sd.count_ += 1;
			matchGuild.push_back(guild);
		}
	}

	sd.count_ = matchGuild.size();
	pack.writeBuf(&sd, sizeof(sd));
	if (sd.count_ > 0)
	{
		for (int i = 0; i < sd.count_; ++i)
		{
			Guild* guild = matchGuild[i];
			pack << (int)guild->id_;
			pack << (unsigned char)guild->level_;
			pack << (int)guild->GetMemberCount();
			pack.writeString(guild->name_);
			pack.writeString(guild->leadername_);
			if (guild->auto_ == 1)
				pack << (int)guild->need_fight_;
			else
				pack << (int)0;
		}
	}

	AP.flush();
}

void OnMemberList(Actor* actor, DataPacketReader& reader)
{
	if (!actor) return;

	Guild* guild = actor->GetGuildSystem()->GetGuildPtr();
	if (!guild) return;

	ActorPacket AP;
	DataPacket& pack = actor->AllocPacket(AP);

	static uint8_t hdr[] = { Protocol::CMD_Guild, Protocol::sGuildCmd_MemberList };
	pack.writeBuf(hdr, sizeof(hdr));

	pack << (int)(guild->actor_list_.count());

	ListIterator<GuildMemberInfo> it(guild->actor_list_);

	for (LinkedNode<GuildMemberInfo>* node = it.first(); node; node = it.next())
	{
		GuildMemberInfo& actor = node->data_;

		pack << (int)actor.actorId_;
		pack.writeString(actor.actor_name_);
		pack << (uint8_t)actor.pos_;
		pack << (uint8_t)actor.job_;
		pack << (uint8_t)actor.sex_;
		pack << (int)actor.vip_;
		pack << (unsigned char)actor.monthcard_;
		pack << (int)actor.total_contrib_;
		pack << (int)actor.today_contrib_;
		pack << (double)actor.fight_;
		pack << (uint32_t)(actor.handle_ != 0 ? 0 : actor.lastLogoutTime_);
		pack << (int)actor.level_;
		pack << (int)actor.zs_level_;
		pack << actor.icon_;
	}

	AP.flush();
}

void OnApplyInfo(Actor* actor, DataPacketReader& reader)
{
	if (!actor) return;
	actor->GetGuildSystem()->OnApplyInfo();
}

void OnGuildLogList(Actor* actor, DataPacketReader& reader)
{
	if (!actor) return;

#pragma pack(push, 1)
	static struct GuildLogListProto
	{
		uint32_t time_;
		uint8_t type_;
		int param1_;
		int param2_;
		int param3_;
	} data;
#pragma pack(pop)

	Guild* guild = actor->GetGuildSystem()->GetGuildPtr();
	if (!guild) return;

	ActorPacket AP;
	DataPacket& pack = actor->AllocPacket(AP);

	static uint8_t hdr[] = { Protocol::CMD_Guild, Protocol::sGuildCmd_GuildLogList };
	pack.writeBuf(hdr, sizeof(hdr));

	Vector<GuildLog>& logs = guild->GetGuildLogs();
	int cnt = logs.count();

	if (cnt > Guild::MAX_GUILD_LOG)
		cnt = Guild::MAX_GUILD_LOG;

	pack << (int)cnt;

	for (int i = 0; i < cnt; i++)
	{
		GuildLog& log = logs[i];

		data.time_ = log.time_;
		data.type_ = log.type_;
		data.param1_ = log.param1_;
		data.param2_ = log.param2_;
		data.param3_ = log.param3_;

		pack.writeBuf(&data, sizeof(data));
		pack.writeString(log.name1_ ? log.name1_ : "");
		pack.writeString(log.name2_ ? log.name2_ : "");
	}

	AP.flush();
}


void NetHandle::RegGuildCmd()
{
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Guild, Protocol::cGuildCmd_GuildList, OnGuildList);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Guild, Protocol::cGuildCmd_MemberList, OnMemberList);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Guild, Protocol::cGuildCmd_ApplyInfo, OnApplyInfo);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Guild, Protocol::cGuildCmd_GuildLogList, OnGuildLogList);
	NetMsgDispatcher::RegistNetMsgHandle(Protocol::CMD_Guild, Protocol::cGuildCmd_GuildSearchList, OnGuildSearchList);
}
