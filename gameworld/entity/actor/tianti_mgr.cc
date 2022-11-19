#include "tianti_mgr.h"
#include "actor_data_mgr.h"
#include "role/role_system.h"

static const char* updatarank = "call updatepvmrank(%d,%d);";

TianTiManger::TianTiManger()
{
	_mChallengeRecord.clear();
	_PVMRank.clear();
	_PlayerIndex.clear();
	_DataCache.clear();
	_SaveTime = 0;
	RecordMaxCount = 10;
	ChangeFlag = (int)time(0);
	oldFlag = 0;
	next_save_time_ = 0;
}

TianTiManger::~TianTiManger()
{
}

//添加记录
void TianTiManger::AddRecordByDB(int32_t actorid, ChallengeRecord recorddata)
{
	auto& challenge_map = _mChallengeRecord[actorid];
	challenge_map[recorddata.record_time] = recorddata;
}

void TianTiManger::AddRecordByScript(int32_t actorid, int32_t targetid, int32_t result, int32_t changerank, int32_t targetrank, int32_t recordtime)
{
	auto &challenge_map = _mChallengeRecord[actorid];

	if (challenge_map.size() >= RecordMaxCount)
	{
		//先删除再添加
		DelRecord(challenge_map);
	}

	ChallengeRecord& temp_data = challenge_map[recordtime];
	temp_data.clear();
	temp_data.actor_id = actorid;
	temp_data.record_time = recordtime;
	temp_data.result = result;
	temp_data.change_rank = changerank;
	temp_data.target_rank = targetrank;

	if (targetid > 0)
	{
		//目标为玩家
		static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
		const ActorBasicData* pActorData = data_mgr->GetData(targetid);
		if (pActorData != nullptr)
		{
			temp_data.headimage = pActorData->headimage;
			temp_data.total_power = pActorData->total_power;
			temp_data.actor_name = pActorData->actor_name;
			temp_data.guild_name = pActorData->guild_name_;
			temp_data.job = (int)pActorData->job;
		}
	}

	static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
	const ActorBasicData* pActorData = data_mgr->GetData(actorid);
	if (pActorData)
	{
		DBClient *db = ServerInstance()->GetDbClient(pActorData->server_idnex);
		if (db) {
			db->SendDbServerData(MAKEINT16(siActor, dcUpdateChallengeRecord), temp_data);
		}
	}
}

void TianTiManger::DelRecord(std::map<int32_t, ChallengeRecord>& recordmap)
{
	//找到时间最早的一条记录
	int last_time = 0;
	for (auto ite: recordmap)
	{
		if (last_time <= 0 || last_time > ite.first)
		{
			last_time = ite.first;
		}
	}

	auto find_ite = recordmap.find(last_time);
	if (find_ite != recordmap.end())
	{
		_DelDataCache[find_ite->second.actor_id] = find_ite->second.record_time;
		recordmap.erase(find_ite);
	}
}

//排行榜更新
void TianTiManger::UpdataRank(int32_t actorid, int32_t newrank)
{
	int old_rank = 0;
	auto rite = _PlayerIndex.find(actorid);
	if (rite != _PlayerIndex.end())
		old_rank = rite->second;

	auto ite = _PVMRank.find(old_rank);
	if (ite != _PVMRank.end() && ite->second == actorid) //删除自己的旧数据
	{
		_PVMRank.erase(old_rank);
	}
		

	_PVMRank[newrank] = actorid;
	_PlayerIndex[actorid] = newrank;
	//SaveRank(newrank,actorid);
	ChangeFlag = (int)time(0);
}
void TianTiManger::LoadOldData()
{
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif

	//配置数据库连接
	ServerInstance()->GetActorMgr()->SetupSQLConnection(&sql);

	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load old actor names"));
		}
	}

	if (sql.Query("select * from pvmrank;"))
	{
		OutputMsg(rmError, ("can not load pvm rank, database call error"));
	}

	int nCount = sql.GetRowCount();
	MYSQL_ROW pRow = sql.CurrentRow();
	auto pTianTiManager = TianTiManger::GetInstance();

	int IRank = 0;
	int IPlayerID = 0;

	while (pRow)
	{
		sscanf(pRow[0], "%d", &IRank);
		sscanf(pRow[1], "%d", &IPlayerID);

		LoadRankByDB(IPlayerID, IRank);
		pRow = sql.NextRow();
	}
	int err = sql.Exec("TRUNCATE table pvmrank");
	//释放查询结果集
	sql.ResetQuery();
	NewSave(true);
}
//从数据库加载排行榜
void TianTiManger::LoadRankByDB(int32_t actorid, int32_t irank)
{
	_PVMRank[irank] = actorid;
	_PlayerIndex[actorid] = irank;
}

const ChallengeRecord * TianTiManger::GetChallengeData(int32_t actorid, int32_t recordtime)
{
	auto acite = _mChallengeRecord.find(actorid);
	if (acite != _mChallengeRecord.end())
	{
		auto reite = acite->second.find(recordtime);
		if (reite != acite->second.end())
		{
			return &reite->second;
		}
	}
		
	return nullptr;
}

int32_t TianTiManger::GetPlayerRank(int32_t actor_id)
{
	auto rite = _PVMRank.find(actor_id);
	if (rite != _PVMRank.end())
	{
		return rite->second;
	}
	return 0;
}

void TianTiManger::SaveRank(int irank, int iactorid)
{
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif

	//配置数据库连接
	ServerInstance()->GetActorMgr()->SetupSQLConnection(&sql);
	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load old actor names"));
			return;
		}
	}

	int err = sql.Exec(updatarank,iactorid, irank);
	if (err != 0)
	{
		int ret = ERR_SQL;
	}
	sql.ResetQuery();
}

void TianTiManger::SendRankToClient(Actor * pActor, int Limit, int flag)
{
	ActorPacket AP;

	DataPacket& pack = pActor->AllocPacket(AP);
	int32_t actorid = pActor->GetActorId();

	int self_rank = 0;
	auto rite = _PlayerIndex.find(actorid);
	if (rite != _PlayerIndex.end())
	{
		self_rank = rite->second;
	}

	int pack_len = Limit;
	if (_PVMRank.size() < Limit)
	{
		pack_len = static_cast<int>(_PVMRank.size());
	}

	pack << (uint8_t)Protocol::CMD_Tianti;
	pack << (uint8_t)Protocol::sTiantiCmd_RankListData; 
	pack << self_rank << ChangeFlag;

	if (flag != ChangeFlag)
	{
		
		int pos1 = pack.getPosition();
		int for_count = 0;
		pack << 0;
		for (auto beginite = _PVMRank.begin(); beginite != _PVMRank.end(); ++beginite)
		{
			if (for_count >= pack_len)
			{
				break;
			}
			
			static const ActorDataMgr* data_mgr = GetGameEngine()->GetActorDataMgr();
			const ActorBasicData* data = data_mgr->GetData(beginite->second);
			if (data == nullptr)
			{
				continue;
			}

			pack << beginite->second;
			pack << data->actor_name;
			pack << beginite->first;
			pack << data->total_power;
			pack << data->guild_name_;
			for_count += 1;
		}
		int pos2 = pack.getPosition();
		pack.setPosition(pos1);
		pack << for_count;
		pack.setPosition(pos2);
		pActor->putActorInfo2Pack(pack);
	}
	
	AP.flush();
}

void TianTiManger::SendChallengeRecordToClient(Actor * pActor)
{
	int32_t actorid = pActor->GetActorId();
	auto rite = _mChallengeRecord.find(actorid);
	if (rite == _mChallengeRecord.end())
	{
		return;
	}

	std::map<int32_t, ChallengeRecord>& record_map = rite->second;

	ActorPacket AP;
	DataPacket& pack = pActor->AllocPacket(AP);
	pack << (uint8_t)Protocol::CMD_Tianti;
	pack << (uint8_t)Protocol::sTiantiCmd_ChallengesRecord;
	pack << (int)record_map.size();
	for (auto map_ite : record_map)
	{
		auto pRecord = map_ite.second;
		pack << pRecord.result;
		pack << pRecord.record_time;
		pack << pRecord.change_rank;
		pack << pRecord.target_rank;
		pack << pRecord.headimage;
		if (pRecord.headimage > 0)
		{
			pack << pRecord.job;
			pack << pRecord.total_power;
			pack << pRecord.actor_name;
			pack << pRecord.guild_name;
		}
	}
	pActor->putActorInfo2Pack(pack);
	AP.flush();
}

int TianTiManger::GetRankByPlayerID(int actorid)
{
	auto find_ite = _PlayerIndex.find((int32_t)actorid);
	if (find_ite == _PlayerIndex.end())
	{
		return 0;
	}

	return find_ite->second;
}

int TianTiManger::GetPlayerIDByRank(int rank)
{
	auto find_ite = _PVMRank.find((int32_t)rank);
	if (find_ite == _PVMRank.end())
	{
		return 0;
	}
	return find_ite->second;
}

void TianTiManger::NewSave(bool is_RightNow)
{
	if (_PVMRank.size() <= 0)
	{
		return;
	}
	int second_time = GetGameEngine()->getMiniDateTime();
	if (second_time > next_save_time_ || is_RightNow) //定时保存间隔
	{
		if (ChangeFlag == oldFlag && is_RightNow == false)
		{
			next_save_time_ = second_time + 1800;
			return;
		}
		oldFlag = ChangeFlag;
		const char* file = "PVMRank";
		const char* realFile = file;

		if (realFile == NULL || realFile[0] == 0)
		{
			OutputMsg(rmError, "PVM Rank Save Fail , /runtime/rank/PVMRank realFile is Nil !");
			return;
		}

		char path[256] = "./runtime/rank/";
		if (!FDOP::FileExists(path))
		{
			FDOP::DeepCreateDirectory(path);
		}

		_STRNCAT_A(path, realFile);
		FILE* fp = fopen(path, "w");

		if (!fp)
		{
			OutputMsg(rmError, "PVM Rank Save Fail , /runtime/rank/PVMRank File Can Not Open !");
			return;
		}

		int count = (int)_PVMRank.size();
		const char* data = "rank\tactorid ";
		fputs(data, fp);

		if (count > 0)
		{
			fputc('\n', fp);
		}

		for (auto ite : _PVMRank)
		{
			char buf[256];
			SNPRINTFA(buf, sizeof(buf), "%d\t%d", ite.first, ite.second);
			fputs(buf, fp);
			fputc('\n', fp);
		}
		fclose(fp);
		OutputMsg(rmNormal, "PVM Rank Save Successful !");
		next_save_time_ = second_time + 1800;
	}
}

void TianTiManger::NewLoad()
{
	const char* file = "PVMRank";
	char path[256] = "./runtime/rank/";

	if (!FDOP::FileExists(path))
	{
		FDOP::DeepCreateDirectory(path);
	}
	_STRNCAT_A(path, file);

	FILE* fp = fopen(path, "r");

	if (!fp)
	{
		OutputMsg(rmError, "PVM Rank Load Fail , /runtime/rank/PVMRank File Can Not Open !");
		return;
	}

	//纯文本，tab隔开各个字段，每行一个记录,第一行是标题
	int row = 0;
	const int size = 128;
	char buf[size];//缓冲区,保存每列的字符串，128应该够了
	int bufpos = 0;
	int col = 0;
	char ch = fgetc(fp);

	int rank = 0;
	while (!feof(fp))
	{
		if (ch == '\n')
		{
			buf[bufpos] = 0;
			if (col < 2)
			{
				//前两个是数字
				int value = atoi(buf);
				if (rank > 0 && value > 0)
				{
					_PVMRank[rank] = value;
					_PlayerIndex[value] = rank;
					rank = 0;
				}
			}
			bufpos = 0;
			col = 0;
			row++;
		}
		else if (ch == '\t')
		{
			buf[bufpos] = 0;

			if (col < 2)
			{
				//前两个是数字
				auto value = atoi(buf);
				rank = value;
			}

			bufpos = 0;
			col++;
		}
		else
		{
			if (bufpos < (size - 1))
			{
				buf[bufpos++] = ch;
			}
		}
		ch = fgetc(fp);
	}
	fclose(fp);
	OutputMsg(rmNormal, "PVM Rank Load Successful !");

	next_save_time_ = GetGameEngine()->getMiniDateTime();
	next_save_time_ = next_save_time_ / 1800 * 1800 + 1800;
}
