#include "StdAfx.h"
#include "guild_mgr.h"
#include "guild.h"
#include "entity/actor/actor.h"
#include "entity/actor/actor_data_mgr.h"
#include "guild_system.h"

int	GuildMgr::guildid_series_ = 0;
static const char guildid_series_file[] = ("./runtime/guildseries.txt");

GuildMgr::GuildMgr()
	:timer_(60)
{
}

GuildMgr::~GuildMgr()
{
	Destroy();
}

bool GuildMgr::LoadDbData()
{
	LoadSeries();

	int serverIdx = ServerInstance()->GetServerIndex();
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif
	ServerInstance()->GetActorMgr()->SetupSQLConnection(&sql);
	if (!sql.Connected())
	{
		if (sql.Connect()) {
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else {
			OutputMsg(rmError, ("can not load actordatas, sql connection error"));
			return false;
		}
	}

	int err = sql.Query("call loadguildbasicdata(%d);", ServerInstance()->GetServerIndex());
	if (err)
	{
		OutputMsg(rmError, "Load guild basic data failed.");
		return false;
	}

	MYSQL_ROW pRow = sql.CurrentRow();
	int total_count = sql.GetRowCount();
	std::vector<Guild*> temp_list;
	temp_list.reserve(total_count);

	static char var_buff_[Guild::MAX_VAR_SIZE * Guild::MAX_VAR_COUNT]; //静态变量读取内存

	while (pRow != nullptr)
	{
		int id;
		int changeNum;
		sscanf(pRow[0], "%d", &id);
		const char* name = (pRow[1] != NULL ? pRow[1] : "");
		sscanf(pRow[2], "%d", &changeNum);

		Guild* guild = new Guild();

		if (guild)
		{
			temp_list.push_back(guild);

			guild->id_ = id;
			guild->change_name_count = changeNum;
			_STRNCPY_A(guild->name_, name);

			NameSortItem item;
			_STRNCPY_A(item.name_, name);
			all_guild_name_.add_item(item);

			unsigned long* pLength = sql.GetFieldsLength();

			size_t totalSize = 0;
			//有三个字段要读的，variable、variable2、variable3
			for (int idx = 0; idx < 3; idx++)
			{
				//从第三个字段开启读
				size_t len = (pLength ? pLength[3 + idx] : 0);
				const char* ptr = pRow[3 + idx];

				if (!ptr || len <= 0) break;

				memcpy(var_buff_ + totalSize, ptr, len);
				totalSize += len;
			}
			if(totalSize > 0)
			{
				guild->LoadVar(var_buff_, totalSize);
			}
		}

		int serverId = HIINT16(id);
		if (serverId == serverIdx)
		{
			int series = LOINT16(id);
			if (series >= guildid_series_)
				guildid_series_ = series + 1;
		}

		pRow = sql.NextRow();
	}

	sql.ResetQuery();

	int count = static_cast<int>( temp_list.size() );
	for (int i = 0; i < count; i++)
	{
		Guild* guild = temp_list[i];
		if (!LoadGuildDetail(sql, *guild))
			return false;
		if (!LoadGuildLog(sql, *guild))
			return false;
		if (!LoadGuildChat(sql, *guild))
			return false;
		if (!LoadGuildStoreLog(sql, *guild))
			return false;
		guild->OnLoadData();

		//添加到列表
		guild_list_.put(guild->id_, guild);

		//加入排行榜，调整排名
		rank_.add(guild);
		guild->rank_ = rank_.count();

		AdjustRank(guild);
	}

	return true;
}

Guild * GuildMgr::CreateGuild(const char * name, Actor * actor)
{
	if (!name)
	{
		OutputMsg(rmError, "CreateGuild error, name is null");
		return NULL;
	}

	static int server_id = ServerInstance()->GetServerIndex();

	int gid = MAKEINT32(guildid_series_, server_id);
	guildid_series_ = guildid_series_ + 1;
	SaveSeries();
	
	Guild* guild = AddGuildToList(gid, name);
	if (!guild) return NULL;

	SendDbAddGuild(gid, name);

	ActorId actorId = (actor ? actor->GetActorId() : 0);

	char cId[32] = { 0 };
	SNPRINTFA(cId, sizeof(cId), "%d", gid);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(actorId, "", "", "guild", cId, "", guild->name_);

	OutputMsg(rmNormal, "CreateGuild : guild(%d), actorId(%d)", gid, actorId);

	return guild;
}

bool GuildMgr::DeleteGuild(Guild * guild, const char * reason)
{
	if (guild == NULL) return true;

	int guildId = guild->id_;

	guild->OnDelete();

	SendDbMsgDeleteGuild(guild->id_);

	guild_list_.remove(guild->id_);

	if (guild->rank_ <= rank_.count() && guild->rank_ > 0)
	{
		Guild* tmp = rank_[guild->rank_ - 1];

		if (tmp != guild)
		{
			OutputMsg(rmError, "delete guild error!!!");
		}
		else
		{
			// 后面的帮派的rank_要修改
			Guild** list = rank_;

			for (int i = guild->rank_; i < rank_.count(); ++i)
			{
				--(list[i]->rank_);
			}

			rank_.remove(guild->rank_ - 1);
		}

		char cId[32] = { 0 };
		SNPRINTFA(cId, sizeof(cId), "%d", guildId);
		static LogSender* log = ServerInstance()->GetLogClient();
		log->LogCounter(0, "", "", "guild", cId, "", guild->name_, reason ? reason : "");

		OutputMsg(rmNormal, "DeleteGuild : guild(%d), reason(%s)", guildId, reason ? reason : "");

		delete guild;
	}
	else
	{
		OutputMsg(rmError, "delete guild(%d) error!!", guild->id_);
	}

	return true;
}

Guild * GuildMgr::FindGuild(int guildId)
{
	Guild** ptr = guild_list_.get(guildId);
	return ptr ? *ptr : NULL;
}

Guild * GuildMgr::FindGuildByName(const char * name)
{
	if (!name) return nullptr;

	Guild** list = rank_;
	int cnt = rank_.count();

	for (int i = 0; i < cnt; i++)
	{
		Guild* guild = list[i];

		if (guild && strcmp(name, guild->name_) == 0)
			return guild;
	}

	return nullptr;
}

bool GuildMgr::NameHasUsed(const char* name)
{
	if (!name) return false;

	NameSortItem item;
	_STRNCPY_A(item.name_, name);
	return all_guild_name_.find(item) >= 0;
}

void GuildMgr::AdjustRank(Guild * guild)
{
	if (guild == NULL) return;

	int count = rank_.count();
	Guild** list = rank_;

	// 先在队列中找到自己，看是否需要调整位置
	int pos = guild->rank_ - 1;	// m_nrank是从1开始

	if (rank_[pos] != guild)
	{
		// 异常
		OutputMsg(rmError, "------guild rank error!!");
		pos = -1;

		for (int j = 0; j < count; ++j)
		{
			Guild* curr_guild = list[j];

			if (guild == curr_guild)
			{
				pos = j;
				break;
			}
		}
	}

	if (pos < 0) return;	// 异常

	bool move = false;	// 是否有移动位置

	for (int i = pos - 1; i >= 0; --i)
	{
		Guild* curr = list[i];

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
			Guild* curr = list[i];

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

void GuildMgr::RunOne()
{
	static GameEngine* ge = GetGameEngine();
	unsigned int now_sec = ge->getMiniDateTime();

	if (timer_.CheckAndSet(now_sec))
	{
		int count = rank_.count();
		Guild** list = rank_;

		for (int i = 0; i < count; ++i)
		{
			Guild* guild = list[i];
			guild->CheckTime(now_sec);
		}
	}
}

void GuildMgr::Save(bool is_stop)
{
	int count = rank_.count();
	Guild** list = rank_;

	for (int i = 0; i < count; ++i)
	{
		Guild* guild = list[i];
		guild->CheckTime(0, is_stop);
	}
}

void GuildMgr::Initialize()
{
	SecondTime now_t;
	now_t.encode(GetGameEngine()->getSysTime());

	// 保证x分0秒触发
	int64_t next_t = now_t / 60 * 60;
	timer_.SetNextHitTime(next_t + 60);
}

void GuildMgr::Destroy()
{
	// 全部save
	Guild** list = rank_;

	for (int i = rank_.count() - 1; i >= 0; --i)
	{
		Guild* guild = list[i];
		guild->OnDestroy();
		delete guild;
	}

	rank_.clear();
	guild_list_.clear();
}

void GuildMgr::SendDbAddGuild(int gid, const char* name)
{
	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siGuild, dcAddGuild));

	pack << (int)gid;
	pack.writeString(name);

	db->flushProtoPacket(pack);
}

void GuildMgr::SendDbMsgDeleteGuild(int id)
{
	DBClient* db = ServerInstance()->GetDbClient();
	if (!db) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siGuild, dcDeleteGuild));
	pack << (int)id;
	db->flushProtoPacket(pack);
}

Guild * GuildMgr::AddGuildToList(int gid, const char * guildName)
{
	if (!guildName)
	{
		OutputMsg(rmError, "AddGuildToList error, guildName is null");
		return NULL;
	}
	if (FindGuild(gid) != NULL)
	{
		OutputMsg(rmError, "AddGuildToList error, guild(%d) has exist", gid);
		return NULL;
	}

	if ((int)guild_list_.count() >= MAX_GUILD) return NULL;

	Guild* guild = new Guild();
	guild->id_ = gid;
	_STRNCPY_A(guild->name_, guildName);

	guild_list_.put(gid, guild);

	//加入排行榜，调整排名
	rank_.add(guild);
	guild->rank_ = rank_.count();

	AdjustRank(guild);

	NameSortItem item;
	_STRNCPY_A(item.name_, guildName);
	all_guild_name_.add_item(item);

	return guild;
}

bool GuildMgr::LoadGuildDetail(SQLConnection& sql, Guild& guild)
{
	int err = sql.Query("call loadguildmembers(%d);", guild.id_);
	if (err)
	{
		OutputMsg(rmError, "Load guild(%d) members data failed.", guild.id_);
		return false;
	}
	MYSQL_ROW pRow = sql.CurrentRow();

	// actors.actorid, actorname, pos, total_contrib, today_contrib, actors.sex, actors.level, actors.totalpower,actors.lastonlinetime

	while (pRow != nullptr)
	{
		GuildMemberInfo node;

		int temp = 0;
		double tempd = 0;
#define GET_INT(index, v) sscanf(pRow[index], "%d", &temp); v = temp; 
#define GET_LINT(index, v) sscanf(pRow[index], "%lf", &tempd); v = tempd; 

		GET_INT(0, node.actorId_);
		_STRNCPY_A(node.actor_name_, pRow[1]);
		GET_INT(2, node.pos_);
		GET_INT(3, node.total_contrib_);
		GET_INT(4, node.today_contrib_);
		GET_INT(5, node.sex_);
		GET_INT(6, node.job_);
		GET_INT(7, node.level_);
		GET_LINT(8, node.fight_);
		GET_INT(9, node.lastLogoutTime_);
		GET_INT(10, node.vip_);
		GET_INT(11, node.monthcard_);
		GET_INT(12, node.zs_level_);
		GET_INT(13, node.icon_);

		if (node.today_contrib_ > 0)
		{
			guild.has_today_contrib_ = true;
		}

		// 鍒濆鍖栫殑鏃跺�欙紝鎵�鏈変汉閮芥槸涓嶅湪绾跨殑
		node.handle_ = 0;
		GuildMemberNode* actorNode = guild.actor_list_.linkAtLast(node);
		guild.Sort(guild.actor_list_, actorNode);

		if (node.pos_ == smGuildLeader)
		{
			guild.leader_id_ = node.actorId_;
			_STRNCPY_A(guild.leadername_, node.actor_name_);
			guild.leader_vip_ = node.vip_;
			guild.leader_monthcard_ = node.monthcard_;
		}

		if ((int)guild.all_actor_.count() >= Guild::MAX_MEMBER) break;

		guild.all_actor_.put(node.actorId_, actorNode);

		pRow = sql.NextRow();
	}


	sql.ResetQuery();

	return true;
}

bool GuildMgr::LoadGuildLog(SQLConnection& sql, Guild& guild)
{
	int err = sql.Query("call loadguildlog(%d)", guild.id_);

	if (err) return false;

	Vector<GuildLog>& logs = guild.GetGuildLogs();
	int count = sql.GetRowCount();
	logs.reserve(count);
	logs.trunc(count);

	MYSQL_ROW pRow = sql.CurrentRow();
	int index = 0;
	while (pRow && index < count)
	{
		GuildLog& log = logs[index];
		int nValue;
		sscanf(pRow[1], "%u", &log.time_); //date
		sscanf(pRow[2], "%d", &nValue); //type
		log.type_ = (uint8_t)nValue;
		sscanf(pRow[3], "%d", &log.param1_); //param1
		sscanf(pRow[4], "%d", &log.param2_); //param2
		sscanf(pRow[5], "%d", &log.param3_); //param3
		_STRNCPY_A(log.name1_, pRow[6] ? pRow[6] : "");	// name1
		_STRNCPY_A(log.name2_, pRow[7] ? pRow[7] : "");	// name2

		pRow = sql.NextRow();

		++index;
	}

	sql.ResetQuery();

	return true;
}

bool GuildMgr::LoadGuildChat(SQLConnection & sql, Guild & guild)
{
	int err = sql.Query("select type, date, actorid, content from guildchat where guildid = %d order by date", guild.id_);
	if (err)
	{
		OutputMsg(rmError, "load guild(%d) chat error(%d)", guild.id_, err);
		return false;
	}

	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();

	std::vector<GuildChatLog>& logs = guild.chat_logs_;
	int count = sql.GetRowCount();
	if (count > Guild::MAX_CHAT_LOG)
		count = Guild::MAX_CHAT_LOG;
	logs.resize(count);

	MYSQL_ROW pRow = sql.CurrentRow();
	int index = 0;
	while (pRow && index < count)
	{
		GuildChatLog& log = logs[index];
		int nValue;
		sscanf(pRow[0], "%d", &nValue); //type
		log.type_ = (uint8_t)nValue;
		sscanf(pRow[1], "%u", &nValue); //time
		log.time_ = nValue;
		sscanf(pRow[2], "%u", &nValue); //actorid
		log.actor_id_ = nValue;
		log.content_ = pRow[3]; // content
		
		bool found = false;
		GuildMemberNode* node = guild.FindMember(log.actor_id_);
		if (node)
		{
			GuildMemberInfo& data = node->data_;
			log.actor_name_ = data.actor_name_;
			log.job_ = data.job_;
			log.month_card_ = data.monthcard_;
			log.pos_ = data.pos_;
			log.sex_ = data.sex_;
			log.vip_level_ = data.vip_;
			log.level_ = data.level_;
			const ActorBasicData* actor_data = data_mgr->GetData(log.actor_id_);
			if (actor_data)
			{
				log.zs_lv_ = actor_data->zhuansheng_lv;
				log.headID = actor_data->headimage;
			}

			found = true;
		}
		else // 鏈夊彲鑳借繖涓帺瀹跺凡缁忕寮�鍏細浜嗭紝灏变粠绯荤粺鐜╁鏁版嵁閲屽彇
		{
			const ActorBasicData* data = data_mgr->GetData(log.actor_id_);
			if (data)
			{
				log.actor_name_ = data->actor_name;
				log.job_ = data->job;
				log.month_card_ = data->monthcard;
				log.pos_ = 0;
				log.sex_ = data->sex;
				log.vip_level_ = data->vip_level;
				log.zs_lv_ = data->zhuansheng_lv;
				log.level_ = data->level;
				log.headID = data->headimage;
				found = true;
			}
		}

		if (!found)
		{
			log.actor_name_ = "";
			log.job_ = JobType_Warrior;
			log.month_card_ = 0;
			log.pos_ = 0;
			log.sex_ = 0;
			log.vip_level_ = 0;
			log.zs_lv_ = 0;
			log.level_ = 0;
			log.headID = 0;
		}

		pRow = sql.NextRow();

		++index;
	}

	sql.ResetQuery();

	return true;
}

bool GuildMgr::LoadGuildStoreLog(SQLConnection& sql, Guild& guild)
{
	int err = sql.Query("select logdate, actorid, itemid from guildstorelog where guildid = %d order by logdate desc limit 50", guild.id_);

	if (err)
	{
		OutputMsg(rmError, "load guild(%d) store log error(%d)", guild.id_, err);
		return false;
	}

	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();

	Vector<GuildStoreLog>& logs = guild.GetGuildStoreLogs();
	int count = sql.GetRowCount();
	logs.reserve(count);
	logs.trunc(count);

	MYSQL_ROW pRow = sql.CurrentRow();
	int index = count-1;
	while (pRow && index >= 0)
	{
		GuildStoreLog& log = logs[index];
		sscanf(pRow[0], "%d", &log.time_);
		sscanf(pRow[1], "%d", &log.actor_id_);
		sscanf(pRow[2], "%d", &log.item_id_); 
		
		bool found = false;
		GuildMemberNode* node = guild.FindMember(log.actor_id_);
		if (node)
		{
			GuildMemberInfo& data = node->data_;
			_STRNCPY_A(log.actor_name_, data.actor_name_ ? data.actor_name_ : "");
			found = true;
		}
		else
		{
			const ActorBasicData* data = data_mgr->GetData(log.actor_id_);
			if (data)
			{
				_STRNCPY_A(log.actor_name_, data->actor_name ? data->actor_name : "");
				found = true;
			}
		}
		if (!found)
		{
			_STRNCPY_A(log.actor_name_,  "");
		}

		pRow = sql.NextRow();

		--index;
	}

	sql.ResetQuery();

	return true;
}


void GuildMgr::LoadSeries()
{
	FILE* fp = fopen(guildid_series_file, "r");
	if (!fp) return;

	char data[256] = { 0 };
	fgets(data, 256, fp);
	fclose(fp);

	sscanf(data, "%d", &guildid_series_);
}

void GuildMgr::SaveSeries()
{
	FILE* fp = fopen(guildid_series_file, "w");

	if (fp)
	{
		char data[256] = { 0 };
		SNPRINTFA(data, sizeof(data), "%d", guildid_series_);
		fputs(data, fp);
		fclose(fp);
	}
}

