#include "StdAfx.h"
#include "guild_system.h"
#include "db/actor_db_data.h"
#include "guild.h"
#include "game_engine.h"
#include "protocol/protos/base_proto.h"

GuildSystem::GuildSystem(Actor * actor)
	: actor_(actor)
	, guild_pos_(0)
{
	attribute_.Reset();
}

GuildSystem::~GuildSystem()
{
}

void GuildSystem::OnInit()
{
	if (!actor_) return;
	static GameServer* srv = ServerInstance();
	if (!srv->IsCommonSrv()) return;

	int guildId = GetGuildId();
	
	if (guildId != 0)
	{
		static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
		Guild* guild = mgr->FindGuild(guildId);

		if (guild)
		{
			GuildMemberNode* node = guild->FindMember(actor_->GetActorId());
			if (node)
			{
				SetGuildInfo(guildId, guild->name_);
				SetGuildPos(node->data_.pos_, "entergame");

				if (!actor_->IsImage())
				{
					node->data_.handle_ = actor_->GetHandle();
					static GameEngine* ge = GetGameEngine();
					ge->ChannelUser(ciChannelGuild, guildId, actor_);
				}
			}
			else //帮派成员没找到他，说明他没加入
			{
				OnLeftGuild();
				OutputMsg(rmTip, "actor(%d) is not guild(%d) member", actor_->GetActorId(), guildId);
			}
		}
		else
		{
			OnLeftGuild();
			OutputMsg(rmTip, "guild(%d) not exist, %d left guild", guildId, actor_->GetActorId());
		}
	}
}

void GuildSystem::OnLogout()
{
	if (!actor_) return;

	int guildid = GetGuildId();

	if (guildid != 0 && !actor_->IsImage())
	{
		static GameEngine* ge = GetGameEngine();
		ge->ChannelUser(ciChannelGuild, guildid, actor_, 1);

	//	static GameServer* gs = ServerInstance();

		static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
		Guild* guild = mgr->FindGuild(guildid);

		if (!guild) return;

		ActorId aid = actor_->GetActorId();

		GuildMemberNode* node = guild->FindMember(aid);
		if (!node) return;

		Guild::UpdateActorData(actor_, &node->data_);
		node->data_.handle_ = 0;
	}
}

int GuildSystem::GetGuildId()
{
	if (!actor_) return 0;

	const ActorBasicData* actorData = actor_->GetBasicData();
	if (!actorData) return 0;

	return actorData->guild_id_;
}

Guild * GuildSystem::GetGuildPtr()
{
	if (!actor_) return NULL;

	int guildId = GetGuildId();

	if (guildId == 0) return NULL;

	static GuildMgr* mgr = GetGameEngine()->GetGuildMgr();
	return mgr->FindGuild(guildId);
}

int GuildSystem::GetGuildPos()
{
	return guild_pos_;
}

void GuildSystem::SetGuildPos(int pos, const char* reson)
{
	if (actor_)
	{
		//OutputMsg(rmTip, "GuildSystem::SetGuildPos %d, %d, %s", actor_->GetActorId(), pos, reson ? reson : "");
	}
	guild_pos_ = pos;
}

const char * GuildSystem::GetGuildName() const
{
	return actor_->GetGuildName();
}

void GuildSystem::SetGuildInfo(int guildId, const char * name)
{
	if (!actor_) return;

	actor_->SetGuildId(guildId);
	actor_->SetGuildName(name);

	static Protocol::ActorGuildProto proto;
	proto.guildId = guildId;

	static char* buf[128];
	DataPacket pack(buf, sizeof(buf));
	pack.writeBuf(&proto, sizeof(proto));
	pack << GetGuildName();
	actor_->SendData(pack);
}

void GuildSystem::OnJoinGuild(Guild * guild, int pos)
{
	if (!actor_ || !guild) return;

	SetGuildInfo(guild->id_, guild->name_);
	SetGuildPos(pos, "join guild");
	actor_->SaveDb();

	ScriptValueList paramList;
	actor_->InitActorEventParams(paramList, aeJoinGuild);
	paramList << guild;

	actor_->OnEvent(&paramList);
}

void GuildSystem::OnLeftGuild()
{
	if (!actor_) return ;

	int guildId = GetGuildId();
	SetGuildInfo(0, "");
	actor_->SaveDb();

	ScriptValueList paramList;
	actor_->InitActorEventParams(paramList, aeLeftGuild);
	paramList << guildId;

	actor_->OnEvent(&paramList);
}

void GuildSystem::OnApplyInfo(void) {
	if (!actor_) return;

	Guild* guild = GetGuildPtr();
	if (!guild) return;

	ActorPacket AP;
	DataPacket& pack = actor_->AllocPacket(AP);

	static uint8_t hdr[] = { Protocol::CMD_Guild, Protocol::sGuildCmd_ApplyInfo };
	pack.writeBuf(hdr, sizeof(hdr));

	BinaryList<Guild::JoinApply>& applyList = guild->inter_msg_list_;
	int count = applyList.count();
	pack << (int)count;

	for (int i = 0; i < count; i++)
	{
		Guild::JoinApply& applyInfo = applyList[i];
		pack << (int)applyInfo.actorId_;
		pack << (int)applyInfo.vip_;
		pack << (uint8_t)applyInfo.job_;
		pack << (uint8_t)applyInfo.sex_;
		pack << (double)applyInfo.power_;
		pack << applyInfo.name_;
		pack << applyInfo.headid;
	}

	AP.flush();
}

void GuildSystem::OnLogin(void) {
	OnApplyInfo();
}
