#include "StdAfx.h"
#include "guild.h"
#include "guild_mgr.h"
#include "guild_system.h"
#include "guild_config.h"
#include "actor/actor_asyn_mgr.h"

template<>
GuildMemberList::LinkNodeMgr* GuildMemberList::node_pool_ = NULL;

Guild::Guild()
	: update_(false)
	, update_base_(false)
	, chat_update_(false)
	, store_update_(false)
{
	Reset();

	static GameEngine* ge = GetGameEngine();
	next_save_chat_ = ge->getMiniDateTime() + SAVE_CHAT_INTERVAL + wrand(SAVE_RANDOM_SEC);
	next_save_store_ = ge->getMiniDateTime() + SAVE_STORE_INTERVAL + wrand(SAVE_RANDOM_SEC);
	change_name_count = 0;
}

Guild::~Guild()
{
	Reset();
}

void Guild::AddMemberToList(Actor * actor, int pos)
{
	if (!actor) return;

	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	ActorId aid = actor->GetActorId();

	if (all_actor_.getIndex(aid) >= 0)
	{
		OutputMsg(rmError, "guild(%d) AddMemberToList error, exist actorid(%d)", id_, aid);
		return;
	}

	GuildSystem* gs = actor->GetGuildSystem();
	gs->OnJoinGuild(this, pos);

	GuildMemberInfo node;
	UpdateActorData(actor, &node);
	node.handle_ = actor->IsImage() ? 0 : ((uint64_t)actor->GetHandle());
	node.pos_ = pos;

	GuildMemberNode* actor_node = actor_list_.linkAtLast(node);
	Sort(actor_list_, actor_node);
	all_actor_.put(aid, actor_node);

	if (pos == smGuildLeader)
	{
		leader_id_ = node.actorId_;
		_STRNCPY_A(leadername_, node.actor_name_);
		leader_vip_ = node.vip_;
		leader_monthcard_ = node.monthcard_;
	}

	static GameEngine* ge = GetGameEngine();
	ge->ChannelUser(ciChannelGuild, id_, actor);

	//发送消息到数据服务器
	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcAddMember));
	pack << (int)id_;
	pack << (ActorId)aid;
	pack << (int)pos;
	db->flushProtoPacket(pack);

	static GuildMgr* mgr = ge->GetGuildMgr();

	mgr->AdjustRank(this);

	char cId[32] = { 0 };
	SNPRINTFA(cId, sizeof(cId), "%d", id_);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(actor->GetActorId(), actor->GetAccount(), "", "guild", cId, "", "join", name_);

	OutputMsg(rmNormal, "AddMemberToList : guild(%d), actorId(%d)", id_, actor->GetActorId());
}

void Guild::DeleteMember(int actorId)
{
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	GuildMemberNode* actor_node = FindMember(actorId);

	if (!actor_node) return;

	GuildMemberInfo& node = actor_node->data_;
	//int guildpos = node.pos_;

	Actor* actor = GetActor(node.handle_);
	if (actor && !actor->IsImage() && actor->IsInited())
	{
		actor->GetGuildSystem()->OnLeftGuild();

		static GameEngine* ge = GetGameEngine();
		ge->ChannelUser(ciChannelGuild, id_, actor, 1);
	}
	else
	{
		GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorId, [](Actor* actor) {actor->GetGuildSystem()->OnLeftGuild(); actor->SaveDb(); });
	}
	
	actor_list_.remove(actor_node);
	all_actor_.remove(actorId);

	//向数据服务器发送信息
	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcDeleteMember));
	pack << (ActorId)actorId;
	db->flushProtoPacket(pack);

	char cId[32] = { 0 };
	SNPRINTFA(cId, sizeof(cId), "%d", id_);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(actorId, "", "", "guild", cId, "", "out", name_);

	OutputMsg(rmNormal, "DeleteMember : guild(%d), actorId(%d)", id_, actorId);
}

GuildMemberNode* Guild::FindMember(ActorId actorId)
{
	GuildMemberNode** node = all_actor_.get(actorId);

	if (node) return *node;
	else return NULL;
}

void Guild::OnDestroy()
{
	if (update_)
		Save();
	if (update_base_)
		SaveBase();
	if (chat_update_)
		SaveChatLog();
	if (store_update_)
		SaveStoreLog();
}

void Guild::OnDelete()
{
	//static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	ListIterator<GuildMemberInfo> it(actor_list_);
	for (LinkedNode<GuildMemberInfo>* node = it.first(); node; node = it.next())
	{
		if (node->data_.handle_ != 0)
		{
			Actor* actor = GetActor(node->data_.handle_);
			if (actor)
			{
				actor->GetGuildSystem()->OnLeftGuild();
			}
		}
	}

}

int Guild::GetGuildPos(int actorId)
{
	GuildMemberNode* actor_node = FindMember(actorId);
	if (!actor_node) return 0;

	GuildMemberInfo& node = actor_node->data_;
	return node.pos_;
}

bool Guild::ChangeGuildPos(int actorId, int pos)
{
	if (pos < smGuildCommon || pos > smGuildLeader) return false;

	GuildMemberNode* actor_node = FindMember(actorId);

	if (!actor_node)
	{
		OutputMsg(rmError, "guild(%d) ChangeGuildPos error, can not find member(%d)", id_, actorId);
		return false;
	}

	GuildMemberInfo& node = actor_node->data_;
	node.pos_ = pos;

	Actor* actor = GetActor(node.handle_);
	if (actor)
	{
		GuildSystem* gs = actor->GetGuildSystem();
		gs->SetGuildPos(pos, "ChangeGuildPos");
	}
	SaveMemberInfo(node);

	if (pos == smGuildLeader)
	{
		leader_id_ = actorId;
		_STRNCPY_A(leadername_, node.actor_name_);
		leader_vip_ = node.vip_;
		leader_monthcard_ = node.monthcard_;
	}

	char cId[32] = { 0 };
	SNPRINTFA(cId, sizeof(cId), "%d", id_);
	char cPos[32] = { 0 };
	SNPRINTFA(cPos, sizeof(cPos), "%d", pos);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(actorId, "", "", "guild", cId, "", "pos", name_, cPos);

	OutputMsg(rmNormal, "ChangeGuildPos : guild(%d), actorId(%d), pos(%d)", id_, actorId, pos);

	return true;
}

bool Guild::PostJoinMsg(Actor* actor)
{
	if (!actor) return false;

	if (inter_msg_list_.size() >= MAX_JOIN_MSG)
	{
		OutputMsg(rmError, "guild(%d) PostJoinMsg error, max join msg");
		return false;
	}

	const ActorBasicData* actorData = actor->GetBasicData();

	Guild::JoinApply Msg;
	Msg.actorId_ = actor->GetActorId();
	Msg.sex_ = actorData->sex;
	Msg.job_ = actorData->job;
	Msg.level_ = actorData->level;
	Msg.power_ = (double)actorData->total_power;
	Msg.vip_ = actorData->vip_level;
	Msg.headid = actorData->headimage;
	static GameEngine* ge = GetGameEngine();
	unsigned int now_sec = ge->getMiniDateTime();
	Msg.jointime = now_sec + apply_keep_time;
	_STRNCPY_A(Msg.name_, actor->GetEntityName());

	int idx = -1;
	idx = inter_msg_list_.find(Msg); //先在列表中寻找

	if (idx >= 0) return false;

	inter_msg_list_.add_item(Msg);

	return true;
}

bool Guild::RemoveJoinMsg(int actorId)
{
	//查看队列有没有这个消息
	Guild::JoinApply Msg;
	Msg.actorId_ = actorId;
	int idx = inter_msg_list_.find(Msg);

	if (idx < 0) return false;

	inter_msg_list_.remove(idx);

	return true;
}

bool Guild::GetJoinMsg(int actorId)
{
	//查看队列有没有这个消息
	Guild::JoinApply Msg;
	Msg.actorId_ = actorId;
	int idx = inter_msg_list_.find(Msg);

	if (idx < 0) return false;
	return true;
}

int Guild::GetMemberTotalGx(int actorId)
{
	GuildMemberNode* actor_node = FindMember(actorId);
	return actor_node ? actor_node->data_.total_contrib_ : 0;
}

void Guild::ChangeMemberTotalGx(int actorId, int val)
{
	GuildMemberNode* node = FindMember(actorId);
	if (!node) return;

	GuildMemberInfo& info = node->data_;

	info.total_contrib_ += val;
	if (val > 0)
	{
		info.today_contrib_ += val;
		has_today_contrib_ = true;
	}

	SaveMemberInfo(info);
	Sort(actor_list_, node);
}

void Guild::Save()
{
	update_ = false;

	SaveVar();
}

void Guild::SaveBase()
{
	update_base_ = false;

	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siGuild, dcSaveGuild));
	pack << id_;
	pack << change_name_count;
	pack << name_;

	db->flushProtoPacket(pack);
	OutputMsg(rmTip, "Guild::Save gid = %d, packet len = %d", id_, (int)pack.getLength());
}

void Guild::LoadVar(const char * ptr, size_t len)
{
	var_.loadFromMemory(ptr, len);

	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList args;
	args << this;
	luaScript.Call("onLoadGuildVar", &args, &args, 1);
}

void Guild::UpdateGuildPos()
{
	GuildPosConfig* levelConfig = GuildConfig::GetLevelConfig(level_);
	if (!levelConfig) return;

	int arraySize = (int)levelConfig->counts_.size();
	std::vector<int>& posCounts = levelConfig->counts_;

	if (arraySize != POS_COUNT)
	{
		return;
	}

	// 会长，副会长，长老，护法，堂主，精英
	static const int POS[] = { smGuildLeader, smGuildAssistLeader, smGuildZl //, smGuildHufa, smGuildTz, smGuildJy
	};
	int posIndex = 2;
	int posCount = posCounts[posIndex];
	ListIterator<GuildMemberInfo> it(actor_list_);
	bool all = false;
	for (LinkedNode<GuildMemberInfo>* node = it.first(); node; node = it.next())
	{
		GuildMemberInfo& actorData = node->data_;
		int old_pos = actorData.pos_;
		if (old_pos == smGuildLeader || old_pos == smGuildAssistLeader)
			continue;

		if (!all)
		{
			actorData.pos_ = POS[posIndex];
			--posCount;

			if (posCount <= 0)
			{
				if (posIndex < arraySize - 1)
				{
					++posIndex;
					posCount = posCounts[posIndex];
				}
				else
				{
					all = true;
				}
			}
		}
		else
		{
			actorData.pos_ = smGuildCommon;
		}

		if (actorData.pos_ != old_pos)
		{
			if (actorData.handle_ != 0)
			{
				Actor* actor = GetActor(node->data_.handle_);

				if (actor)
				{
					actor->GetGuildSystem()->SetGuildPos(actorData.pos_, "UpdateGuildPos");
				}
			}
			SaveMemberInfo(actorData);

			OutputMsg(rmNormal, "UpdateGuildPos : guild(%d), actorId(%d), pos(%d)", id_, actorData.actorId_, actorData.pos_);
		}
	}
}

ActorId Guild::GetLargestContribution()
{
	if (actor_list_.count() < 1)
	{
		return 0;
	}
	LinkedNode<GuildMemberInfo>* node = actor_list_.first();
	if (!node) return 0;

	return node->data_.actorId_;
}

void Guild::AddGuildLog(unsigned char type, const char* name1, const char* name2, int param1, int param2, int param3)
{
	static GameEngine* ge = GetGameEngine();
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	int count = logs_.count();

	if (count >= MAX_GUILD_LOG)
	{
		//从数据库中删除
		GuildLog& log = logs_[0];
		DataPacket& pack = db->allocProtoPacket(MAKEINT16(siGuild, dcDelGuildLog));

		pack << (int)id_;
		pack << (int)log.time_;
		db->flushProtoPacket(pack);

		logs_.remove(0);
		logs_.trunc(count);
	}
	else
	{
		count++;
		logs_.reserve(count);
		logs_.trunc(count);
	}

	GuildLog& log = logs_[count - 1];
	log.time_ = ge->getMiniDateTime();
	log.type_ = type;
	_STRNCPY_A(log.name1_, name1 ? name1 : "");
	_STRNCPY_A(log.name2_, name2 ? name2 : "");
	log.param1_ = param1;
	log.param2_ = param2;
	log.param3_ = param3;

	// 保存
	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siGuild, dcAddGuildLog));

	pack << (int)id_;
	pack << (int)log.time_;
	pack << (int)type;
	pack << (int)param1;
	pack << (int)param2;
	pack << (int)param3;
	pack.writeString(name1 ? name1 : "");
	pack.writeString(name2 ? name2 : "");
	db->flushProtoPacket(pack);
}

void Guild::AddChatLog(uint8_t type, const char* content, Actor* actor)
{
	if (!content) return;
	static GameEngine* ge = GetGameEngine();

	if (chat_logs_.size() >= MAX_CHAT_LOG)
	{
		chat_logs_.erase(chat_logs_.begin());
	}
	chat_logs_.resize(chat_logs_.size() + 1);
	GuildChatLog& log = chat_logs_[chat_logs_.size() - 1];
	log.type_ = type;
	log.time_ = ge->getMiniDateTime();
	log.content_ = content;
	if (actor)
	{
		log.actor_id_ = actor->GetActorId();
		log.actor_name_ = actor->GetActorName();
		log.job_ = actor->GetJob();
		log.sex_ = actor->GetSex();
		log.vip_level_ = actor->GetVipLevel();
		log.month_card_ = actor->GetMonthCard();
		log.pos_ = (uint8_t)actor->GetGuildSystem()->GetGuildPos();
		log.zs_lv_ = actor->GetBasicData()->zhuansheng_lv;
		log.level_ = actor->GetBasicData()->level;
	}
	chat_update_ = true;
}

void Guild::AddGuildStoreLog(ActorId actor_id, const char* name, int item_id)
{

	static GameEngine* ge = GetGameEngine();
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	int count = store_logs_.size();

	if (count >= MAX_GUILD_STORE_LOG)
	{
		store_logs_.remove(0);
		store_logs_.trunc(count);
	}
	else
	{
		count++;
		store_logs_.reserve(count);
		store_logs_.trunc(count);
	}

	GuildStoreLog& log = store_logs_[count - 1];
	log.time_ = ge->getMiniDateTime();
	log.actor_id_ = actor_id;
	log.item_id_ = item_id;
	_STRNCPY_A(log.actor_name_, name ? name : "");

	store_update_ = true;
}

// 广播
void Guild::BroadCast(const char* buf, size_t size)
{
	if (!buf || size == 0) return;

	static GameEngine* ge = GetGameEngine();
	ge->BroadCast(ciChannelGuild, id_, (const char*)buf, size);
}

void Guild::CheckTime(uint32_t now_sec, bool stopserver)
{
	if (update_ || stopserver)
	{
		Save();
		update_ = false;
	}

	if (update_base_ || stopserver)
	{
		SaveBase();
		update_base_ = false;
	}

	if (chat_update_ && (now_sec >= next_save_chat_ || stopserver))
	{
		static GameEngine* ge = GetGameEngine();
		SaveChatLog();
		chat_update_ = false;
		next_save_chat_ = ge->getMiniDateTime() + SAVE_CHAT_INTERVAL;
	}

	if (store_update_ && (now_sec >= next_save_store_ || stopserver))
	{
		static GameEngine* ge = GetGameEngine();
		SaveStoreLog();
		store_update_ = false;
		next_save_store_ = ge->getMiniDateTime() + SAVE_STORE_INTERVAL;
	}
}

void Guild::OnLoadData()
{
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	ScriptValueList args;
	args << this;
	luaScript.Call("onLoadGuild", &args, &args, 1);
}

void Guild::ResetTodayContrib()
{
	if (!has_today_contrib_) return;

	ListIterator<GuildMemberInfo> it(actor_list_);
	for (LinkedNode<GuildMemberInfo>* node = it.first(); node; node = it.next())
	{
		GuildMemberInfo& info = node->data_;
		int isChanged = (info.today_contrib_ != 0);
		info.today_contrib_ = 0;

		if (isChanged)
		{
			SaveMemberInfo(info);
		}
	}

	has_today_contrib_ = false;
}

Actor * Guild::GetActor(uint64_t handle)
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Entity* et = em->GetEntity(handle);
	if (et && et->GetType() == enActor)
	{
		Actor* actor = (Actor*)et;
		if (actor->IsInited())
		{
			return actor;
		}
	}

	return nullptr;
}

void Guild::LeaderNameUpdate()
{
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	if (em)
	{
		Actor* actor = em->GetActorPtrById(leader_id_);
		if (actor)
		{
			_STRNCPY_A(leadername_, actor->GetEntityName());
			return;
		}
	}

}

void Guild::UpdateActorData(Actor* actor, GuildMemberInfo* node)
{
	if (actor == NULL || node == NULL) return;

	ActorId actorid = actor->GetActorId();

	GuildSystem* gs = actor->GetGuildSystem();
	Guild* guild = gs->GetGuildPtr();

	if (!guild) return;

	node->actorId_ = actorid;
	node->sex_ = actor->GetSex();
	node->level_ = actor->GetLevel();
	node->zs_level_ = actor->GetBasicData()->zhuansheng_lv;
	node->job_ = actor->GetJob();
	node->fight_ = (double)actor->GetBasicData()->total_power;
	node->vip_ = actor->GetVipLevel();
	node->monthcard_ = actor->GetMonthCard();
	node->lastLogoutTime_ = actor->GetLastLogoutTime();
	node->icon_ = actor->GetBasicData()->headimage;

	_STRNCPY_A(node->actor_name_, actor->GetActorName());
}

void Guild::Reset()
{
	id_ = rank_ = 0;

	name_[0] = 0;
	leadername_[0] = 0;
	leader_id_ = 0;
	leader_vip_ = 0;
	leader_monthcard_ = 0;
	actor_list_.clear();
	all_actor_.clear();
	update_ = false;
	inter_msg_list_.clear();
	level_ = 1;
	levelup_time_ = 0;
	auto_ = 0;
	need_fight_ = 0;

	var_.clear();
	logs_.clear();
}

void Guild::Sort(GuildMemberList & list, GuildMemberNode * node)
{
	GuildMemberNode* link_pos = NULL;

	for (GuildMemberNode* pre = node->prev_; pre; pre = pre->prev_)
	{
		if (node->data_.compare(pre->data_) > 0)
			link_pos = pre;
		else
			break;
	}

	if (link_pos)
	{
		list.remove(node, false);
		list.linkBefore(node, link_pos);
		return;
	}

	for (GuildMemberNode* next = node->next_; next; next = next->next_)
	{
		if (node->data_.compare(next->data_) < 0)
			link_pos = next;
		else
			break;
	}

	if (link_pos)
	{
		list.remove(node, false);
		list.Transfer(node, link_pos);
	}
}

void Guild::SaveVar()
{
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	bool mem = true;
	size_t totalSize = var_.saveToMemory(NULL, 0, mem);

	if (totalSize >= MAX_VAR_SIZE * MAX_VAR_COUNT)
	{
		OutputMsg(rmError, "guild id = %d, the guild var data too large", id_);
		return;
	}

	static char buf[MAX_VAR_SIZE * MAX_VAR_COUNT];
	static DataPacket dp(buf, sizeof(buf));
	dp.setLength(0);

	size_t savesize = var_.saveToMemory(dp.getOffsetPtr(), dp.getAvaliableBufLen(), mem);

	if (savesize != totalSize)
	{
		OutputMsg(rmError, ("guild id=%d, the guild var data too large"), id_);
		return;
	}

	dp.setLength(savesize);
	for (int i = 0; i < MAX_VAR_COUNT && dp.getAvaliableLength() > 0; i++)
	{
		DataPacket& packet = db->allocProtoPacket(MAKEINT16(siGuild, dcSaveGuildVar));
		packet << (int)id_ << (int)i; //保存字段i
		size_t size = __min(MAX_VAR_SIZE, dp.getAvaliableLength());
		packet << (int)size;
		packet.writeBuf(dp.getOffsetPtr(), size);
		dp.adjustOffset(size);
		db->flushProtoPacket(packet);
	}
}

void Guild::SaveChatLog()
{
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siGuild, dcSaveGuildChat));
	packet << (int)id_;

	size_t size = chat_logs_.size();
	packet << (int)size;
	for (int i = 0; i < (int)size; i++)
	{
		GuildChatLog& log = chat_logs_[i];
		packet << (uint8_t)log.type_;
		packet << (int)log.time_;
		packet << (ActorId)log.actor_id_;
		packet << (const char*)log.content_.c_str();
	}
	db->flushProtoPacket(packet);
}

void Guild::SaveStoreLog()
{
	DBClient* db = ServerInstance()->GetDbClient();

	if (!db) return;

	int size = store_logs_.size();
	if (0 >= size) return;

	DataPacket& packet = db->allocProtoPacket(MAKEINT16(siGuild, dcSaveGuildStore));
	packet << id_;
	packet << size;
	for (int i = 0; i < size; i++)
	{
		GuildStoreLog& log = store_logs_[i];
		packet << log.time_;
		packet << log.actor_id_;
		packet << log.item_id_;
	}
	db->flushProtoPacket(packet);
}

void Guild::SaveMemberInfo(GuildMemberInfo& info)
{
	DBClient* db = ServerInstance()->GetDbClient(ServerInstance()->GetServerIndex());

	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveActorGuild));
	pack << (ActorId)info.actorId_;
	pack << (int)id_;
	pack << (int)info.total_contrib_;
	pack << (int)info.today_contrib_;
	pack << (int)info.pos_;
	db->flushProtoPacket(pack);
}


std::vector<Actor*> Guild::getOnlineActor(void)
{
	std::vector<Actor*> ret;

	ListIterator<GuildMemberInfo> it(actor_list_);
	for (LinkedNode<GuildMemberInfo>* node = it.first(); node; node = it.next())
	{
		GuildMemberInfo& info = node->data_;
		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		auto actor = em->GetActorPtrById(info.actorId_);
		if (actor  && actor->IsInited() && !actor->IsImage())
		{
			ret.push_back(actor);
		}
	}
	return ret;
}

bool Guild::changeName(const char* name)
{
	if (!name)
	{
		OutputMsg(rmError, "guild changeName error, guildName is null");
		return false;
	}
	if (change_name_count <= 0)
	{
		OutputMsg(rmError, "guild changeName count error, count:%d", change_name_count);
		return false;
	}

	change_name_count--;
	_STRNCPY_A(name_, name);

	update_base_ = true;
	return true;
}

void Guild::clearGuildChat()
{
	chat_logs_.clear();
	chat_update_ = false;
}