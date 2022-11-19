#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

#ifndef _MSC_VER
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#include "login_queue.h"

using namespace InterSrvComm::GameWorldProto;

static const char* DEF_RANDNAME = "def_names.txt";
static const char* CHAR_RANDNAME = "chars_names.txt";

static const char* createnewactor = "call createnewactor(%d,\"%s\",%d, %d, \"%s\",%d,%d,%d)";//用户创建角色
static const char* loadfilternames = "call loadfilternames()";
static const char* loadcrosswarteamnames = "call loadcrosswarteamnames()";
static const char* loadallactorname = "call loadallactorname(%d)";
static const char* loadmaxactoridseries = "call loadmaxactoridseries(%d)";

static const char* loadoldnamelist = "select oldname, actorid from actoroldname;";
static const char* addoldnamelist = "call addoldnamelist(%d, \"%s\", %d);";

static const char* addpvmrecord = "call addpvmrecord(%d,%d,%d,%d,%d,%d,%d,'%s','%s');";
static const char* delpvmrecord = "call delpvmrecord(%d,%d);";

static const char* lua_fn = "./data/actormgr/actormgr.txt";


int ActorMgr::actorid_series_ = 0;

static BaseAllocator alloc("ActorMgr");

void OnBlock(void* mgr)
{
	if (mgr)
	{
		//ActorMgr* ag = (ActorMgr*)mgr;
		//ag->GetDbConn()->Disconnect();	//不同线程,并且断开连接也没有用
		//OutputWatchFile("actormgr block!");
		printf("actormgr block!\n");
	}
}

ActorMgr::ActorMgr(GameGateMgr* gate_mgr) : Inherited()
	, next_ping_t_(0), check_key_t_(0), key_data_alloc_("ActorMgrAlloc")/*, pf_str_alloc_("ActorMgrPfstrAlloc", 256, 8)*/
{
	gate_mgr_ = gate_mgr;
	sql_.SetMultiThread(true);
	sql_.SetLog(false);
	//pf_str_alloc_.SetMultiThread(true);

#ifdef DB_UTF8
	sql_.SetUtf8(true);
#endif
	reconnect_t_ = 0;
	report_t_ = 0;
	filter_words_ = NULL;

	db_host_[0] = 0;
	db_port_ = 0;

	vsp_def_.LoadDefinitions("./data/vspdef.txt");
	script_.SetVspDef(&vsp_def_);

	try
	{
		bool ret = script_.LoadScript(lua_fn);
		if (!ret)
			OutputMsg(rmError, "actormgr load script failed");
	}
	catch (RefString& s)
	{
		OutputMsg(rmError, "actormgr load script error:%s", (const char*)s);
	}

	inter_msg_.setLock(&inter_msg_lock_);

	old_actor_name_.clear();
}

ActorMgr::~ActorMgr()
{
	inter_msg_.flush();

	int count = inter_msg_.count();

	for (int i = 0; i < count; ++i)
	{
		GameInterMsg& msg = inter_msg_[i];

		if (msg.msg_id_ == imAddKey)
		{
			key_data_alloc_.FreeBuffer(msg.data_.buffdata_);
		}

		if (msg.msg_id_ == imBatchOnline || msg.msg_id_ == imAddGameClient
		        || msg.msg_id_ == imBroadCast || msg.msg_id_ == imDelGameClient)
		{
			DataPacket* dp = msg.data_.packet_;
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
	}

	inter_msg_.clear();
	old_actor_name_.clear();
}

void ActorMgr::Run()
{
	_M_DBGFUNC_BEGIN

	ConnectSQL();

	ProcessSysMsg();
	gate_mgr_->CollectActorMgrData();

	time_t now_t = NOW_T;

	if (abs(now_t - report_t_) > 10) // 10s 报告一次
	{
		WatchThread* watch = ServerInstance()->GetWatch();

		if (watch) watch->Report(GameServer::wiActorMgr);
		//OutputMsg(rmNormal, "actor_mgr report.");

		//report_t_ = now_t + 60;	// 5s报告一次
		report_t_ = now_t;	// 5s报告一次
	}

	if (now_t > check_key_t_)
	{
		check_key_t_ = now_t + 10;

		CrossUserData* list = key_list_;

		for (int i = key_list_.count() - 1; i >= 0; --i)
		{
			if (list[i].time_out_ < now_t)
			{
				OutputMsg(rmError, "cross key time out!%d,sid:%d,aid:%d", now_t - list[i].time_out_, list[i].serverId_, list[i].actorId_);
				key_list_.remove(i);
			}
		}
	}

	//PVMRun(now_t);

	_M_DBGFUNC_END
}

bool ActorMgr::StartActorMgr()
{
	if (!LoadNameData())
		return false;

	if (!LoadFilterNames())
		return false;

	//if (!LoadCrossWarTeamName())
	//	return false;

// 	if (!LoadRoutes())
// 		return false;

	if (!LoadOldActorNameData())
		return false;

	if (!LoadAllowWords())
		return false;

	Start();
	return true;
}

void ActorMgr::Stop()
{
	WatchThread* watch = ServerInstance()->GetWatch();

	if (watch) watch->RemoveWatch(GameServer::wiActorMgr);

	// 事实上不需要保存
#ifndef _MSC_VER
	def_names_.SaveToFile(DEF_RANDNAME);
	char_names_.SaveToFile(CHAR_RANDNAME);
#endif

	ClearGameClient();

	BaseThread::Stop();
}

void ActorMgr::OnRoutine()
{
	OnStart();

	while (!terminated())
	{
		Run();
		Sleep(1);
	}

	OnStop();
}

void ActorMgr::OnStart()
{
	OutputMsg(rmError, "actor mar thread start!");
	WatchThread* watch = ServerInstance()->GetWatch();

	//阻塞两分钟输出一次日志,如果需要处理,最好多等几分钟
	if (watch) watch->AddWatch(GameServer::wiActorMgr, 120000, &OnBlock, this);
}

void ActorMgr::OnStop()
{
	FreeFilterWords();

	OutputMsg(rmError, "actor mar thread stop!");
}

void ActorMgr::ProcessNetMsg(DataPacket& packet, int gate_idx)
{
	NetId netid;
	packet >> netid;
	GameGate* gate = (GameGate*)gate_mgr_->GetGate(netid.gate_id_);

	if (!gate)
	{
		OutputMsg(rmError, "recv a packet invalid source!")	;
		return;
	}

	GateUser* user = gate->GetUser(netid);

	if (!user)
	{
		OutputMsg(rmError, "recv a packet invalid user!");
		return;
	}

	// 用于检查重复包的id值，在这个线程不用检查，直接跳过
	packet.adjustOffset(sizeof(int));

	uint8_t cmd_str[2];
	packet.readBuf(cmd_str, sizeof(cmd_str));
	//OutputMsg(rmError, "netid:main=%d  sub=%d  %d,%d", cmd_str[0], cmd_str[1], netid.index_, netid.socket_);
	if (cmd_str[0] != Protocol::CMD_Login)
	{
		OutputMsg(rmError, "recv invalid systemid in actormgr,systemid=%d, protoid=%d,actorid=%d, hdl=%lld, ptr=%lld",
		          cmd_str[0], cmd_str[1], user->actor_id_,
		          (long long int)user->handle_, (long long int)user);
		OutputMsg(rmError, "netid:%d,%d", netid.index_, netid.gate_id_);
		return;
	}

	int cmd = cmd_str[1];

	switch (cmd)
	{
	case cUserPw:
		{
			CheckUserPw(user, packet);
			break;
		}

	case cCrossKey:
		{
			CheckCrossKey(user, packet);
			break;
		}

	default:
		ScriptValueList args;
		args << cmd;
		args << (void*)&packet;
		args << ServerInstance()->GetServerIndex();
		args << user->account_id_;
		args << (const char*)user->account_name_;
		args << user->actor_id_;
		args << (void*)&user->netid_;
		args << (void*)user;
		args << (const char*)user->remote_addr_;
		script_.Call("actorMgrEvent", &args, &args);
		break;
	}
}

int ActorMgr::CreateActor(int accountid, const char* accountname, const char* name, int sex, int job,int headid, ActorId& actor_id, const char* pfid, GateUser* gateuser)
{
	int ret = NOERR;

	// 生成全局唯一actorid
	static int server_id = ServerInstance()->GetServerIndex();

	if (actorid_series_ >= MAX_ACTOR_CREATE)
	{
		actor_id = 0;
		OutputMsg(rmNormal, "this CreateActor !, actorid_series_=%d  MAX_ACTOR_CREATE=%d", actorid_series_, MAX_ACTOR_CREATE);
		return ERR_MAXACTOR;
	}

	//检验数量
	int err = sql_.Query("select count(*) from actors where status<>0 and accountname='%s' and serverindex=%d", accountname, server_id);
	if (err)
	{
		OutputMsg(rmError, "create actor error sql:%d", err);
		return ERR_SQL;
	}

	MYSQL_ROW row = sql_.CurrentRow();
	if (!row || !row[0])
	{
		sql_.ResetQuery();
		return ERR_SQL;
	}

	int actorCount = 0;
	sscanf(row[0], "%d", &actorCount); //账户名字
	sql_.ResetQuery();

	if (actorCount > 0)
		return ERR_MAXACTOR;

	actor_id = (ActorId)((actorid_series_ << 16) | server_id);	// serverid不能超过2^(32-13)，即2048*4
	// 为了兼容旧版本, 保留后13位已存在的服务器id, 把新增的5位放在最前面
	//actor_id = (ActorId)((actorid_series_ << 13) | (server_id & ((1 << 13) - 1))) | ((server_id >> 13) << 27);
	actorid_series_++;

	char sql[512] = { 0 };
//"call createnewactor(%d,\"%s\",%d, %d, \"%s\",%d,%d,%d)";//用户创建角色
	sprintf(sql, createnewactor
		, accountid, accountname, ServerInstance()->GetServerIndex()
		, actor_id, name, job, sex, headid
		);
	err = sql_.Exec(sql);

	if (err != 0)
	{
		ret = ERR_SQL;
		actor_id = 0;
	}
	else
	{
		sql_.ResetQuery();
	}

	if (ret == NOERR)
	{
		//如果这个名字是随机生成的，要把这个名字设置成不可再用
		NameSortItem item;
		_STRNCPY_A(item.name_, name);

		all_actor_name_.add_item(item);
		def_names_.UseName(name);
		char_names_.UseName(name);
#ifdef OPENLOGDKMLOG
		DKMLogMgr::LogCreateRole(accountid, actor_id, name, pfid ? pfid : "", gateuser ? gateuser->remote_addr_ : "");
#endif
	}

	return ret;
}

int ActorMgr::ChangeActorName(ActorId actor_id, const char* name, const char* rawName)
{
	int ret = NOERR;
	bool isOld = false;
	//ActorId* pAid = old_actor_name_.get(rawName);
	//old_actor_name_[rawName] = actor_data->actor_id;
	auto it = old_actor_name_.find(rawName);
	if (it != old_actor_name_.end() && it->second == actor_id)
	//if (pAid && *pAid == actor_id)
	{
		// 用回旧名，不需要重复添加到数据库
		isOld = true;
	}
	else
	{
		char sql[512];
		static int server_id = ServerInstance()->GetServerIndex();
		SNPRINTFA(sql, sizeof(sql), addoldnamelist, actor_id, rawName, server_id);

		int err = sql_.Exec(sql);

		if (err != 0)
		{
			ret = ERR_SQL;
		}
		else
		{
			sql_.ResetQuery();
		}
	}

	if (ret == NOERR)
	{
		//如果这个名字是随机生成的，要把这个名字设置成不可再用
		NameSortItem item;
		_STRNCPY_A(item.name_, name);
		if (all_actor_name_.find(item) < 0)
		{
			all_actor_name_.add_item(item);

			def_names_.UseName(name);
			char_names_.UseName(name);
		}

		if (!isOld)
		{
			//ActorId* pAid = old_actor_name_.put(rawName);
			//if(pAid)
			//{
			//	*pAid = actor_id;
			//}
			old_actor_name_[rawName] = actor_id;
		}
	}

	return ret;
}
const char* ActorMgr::GetRandomName(int nSex)
{
	RandNameList* name_list = nSex == 0 ? &def_names_ : &char_names_;
	return name_list->GetName();
}
#include <ctime>
void ActorMgr::CheckUserPw(GateUser* user, DataPacket& packet)
{
	if (user->account_id_ != 0)
	{
		OutputMsg(rmError, "this account has logined!, accountid=%d", user->account_id_);
		return;
	}

	int accountId = 0;//userid

	int serverid = 0;
	const char* name = NULL;
	const char* cli_pw = NULL;
	packet >> serverid >> name >> cli_pw;

	if (!name || !cli_pw) { OutputMsg(rmError, "CheckUserPw account name or cli_pw null , accountid=%d", user->account_id_);  return; }

	if (serverid != ServerInstance()->GetServerIndex())
	{
		SendPwResult(enServerNotExisting, user);
		return;
	}

	int err = sql_.Query("call logingetglobaluser('%s')", name);

	if (err)
	{
		SendPwResult(enSessionServerError, user);
		return;
	}
	MYSQL_ROW row = sql_.CurrentRow();

	if (!row)
	{
		SendPwResult(enNoAccount, user);
		sql_.ResetQuery();
		return;
	}

	if (row[0])
	{
		sscanf(row[0], "%d", &accountId); //账户名字
	}

	char pwd[128] = "";

	if (row[1])
	{
		_STRNCPY_A(pwd, row[1]);
	}

	int gm_level = 0;

	if (row[4])
	{
		sscanf(row[4], "%d", &gm_level);
	}

	int pwtime = 0;
	if (row[5])
	{
		sscanf(row[5], "%d", &pwtime);
	}

	//处理封号问题
	char bantime[128] = "";
	if (row[6])
	{
		_STRNCPY_A(bantime, row[6]);
		struct tm tm;
		memset(&tm, 0, sizeof(tm));
		sscanf(bantime, "%d-%d-%d %d:%d:%d",
			&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
			&tm.tm_hour, &tm.tm_min, &tm.tm_sec);
		tm.tm_year -= 1900;
		tm.tm_mon--;
		time_t ban_t = mktime(&tm);
		//struct tm tm2;
		time_t  cur_t = time(0);
		if (ban_t > cur_t)
		{
			static DataPacket dp(&alloc);
			static uint8_t hdr[] = { Protocol::CMD_Login, sUserPw };
			dp.writeBuf(hdr, sizeof(hdr));
			dp << (uint8_t)enBanTime;
			dp << (int)ban_t;
			SendToGate(user->netid_, (const char*)dp.getMemoryPtr(), dp.getLength());
			dp.setPosition(0);
			//如果封号就打印日志 方便追查问题
			OutputMsg(rmError, "%s bantime enBanTime, db = %s,account pw:%s enBanTime:%s", name, pwd, cli_pw, bantime);
			return;
		}
	}
#ifndef _MSC_VER
	//if (gm_level != 10 && (row[1][0] == 0 || 0 != strcmp(pwd, cli_pw)))
	//int now_t = time(NULL);
	//if ((pwtime != 0 && now_t - pwtime > 20) || (0 != strcmp(pwd, cli_pw)))
	if (0 != strcmp(pwd, cli_pw))
	{
		OutputMsg(rmError, "%s diff password, db = %s,account pw:%s", name, pwd, cli_pw);
		SendPwResult(enPasswdError, user);
		sql_.ResetQuery();
		return;
	}
#endif

	//int pos = GetOnlinePos(accountId);

	//if (pos >= 0)
	//{
	//	static GameGateMgr* gm = ServerInstance()->GetGateManager();
	//	NetId netId = online_list_.get(pos).netId_;
	//	SendPwResult(enIsOnline, user);
	//	/*GameGate* gate = (GameGate*)gate_mgr_->GetGate(netId.gate_id_);
	//	if (gate) {
	//		GateUser* user = gate->GetUser(netId);
	//		if (user)
	//			SendPwResult(enIsLoginInOtherPlace, user);
	//	}*/

	//	//这个是异步，超级慢，玩家都已经登录了， 那边还没关闭
	//	gm->PostCloseUser(netId, "ActorMgr::CheckUserPw", accountId);

	//	ActorSortItem item;
	//	item.accountId_ = accountId;
	//	online_list_.remove_item(item, true);

	//	sql_.ResetQuery();
	//	return;
	//}

	OutputMsg(rmNormal, "%s password ok,accountID =%d", name, accountId);
	_STRNCPY_A(user->account_name_, name);
	user->account_id_ = accountId;

	sql_.ResetQuery();

	user->gm_ = gm_level;

	if (!sql_.Exec("call updateglobaluserlogin(%d,%lu)", accountId, 0))
	{
		sql_.ResetQuery();
	}

	//ActorSortItem item;
	//item.accountId_ = accountId;
	//item.netId_ = user->netid_;
	//online_list_.add_item(item);

	SendPwResult(enSuccess, user);
}

void ActorMgr::CheckCrossKey(GateUser* user, DataPacket& pack)
{
	if (user->account_id_ != 0)
	{
		OutputMsg(rmError, "this account has logined!, accountid=%d", user->account_id_);
		return;
	}

	bool ret = false;

	ActorId aid;
	const char* key = NULL;
	pack >> aid;

	CrossUserData data;

	if (GetCrossKeyData(aid, data))
	{
		pack >> key;

		if (strcmp(key, data.key_) == 0)
		{
			user->account_id_ = data.accountId_;
			user->actor_id_ = data.actorId_;
			_STRNCPY_A(user->account_name_, data.account_name_);

			user->gm_ = data.gm_;
			ret = true;
		}
		else
		{
			OutputMsg(rmError, "the cross key is error!,key=%s,realkey=%s",
			          key, data.key_);
		}
	}
	else
	{
		OutputMsg(rmError, "key data not found, key=%s", key);
	}

	if (!ret) {
		// 直接关闭连接
		gate_mgr_->PostCloseUser(user->netid_, "ActorMgr::CheckCrossKey", aid);
	} else {
		static uint8_t db[3] = { Protocol::CMD_Login, sEnterGame, 0 };
		SendToGate(user->netid_, (const char*)db, sizeof(db));
		const char *pf, *pfid, *appid;
		pack >> pf >> pfid >> appid;
		EnterGame(user, aid, pf, pfid, appid, data.serverId_);
		OutputMsg(rmTip, "actor login cross, actorid=%d, serverid=%d, pf=%s, pfid=%s, appid=%s", user->actor_id_, data.serverId_, pf ? pf : "", pfid ? pfid : "", appid ? appid : "");
	}
}


void ActorMgr::SendToGate(NetId& netid, const char* buf, size_t size)
{
	GameGate* gate = (GameGate*)gate_mgr_->GetGate(netid.gate_id_);

	if (gate)
	{
		DataPacket* packet = gate->GetSendToGatePacket(GameGate::ActorMgrThread);

		if (!packet) return;

		const size_t static_len = sizeof(uint16_t) + sizeof(netid);
		size_t total_size = packet->getPosition() + sizeof(DATAHEADER) + static_len + size;
		packet->reserve(total_size);

		DATAHEADER* hdr = (DATAHEADER*)packet->getOffsetPtr();
		hdr->len = (/*uint16_t*/uint32_t)(static_len + size);
		hdr->tag = TAG_VALUE;

		packet->adjustOffset(sizeof(DATAHEADER));
		(*packet) << (uint16_t)GW_DATA << netid;
		packet->writeBuf(buf, size);
	}
}

bool ActorMgr::ConnectSQL()
{
	time_t now_t = NOW_T;

	if (db_host_[0] != 0 && !sql_.Connected())
	{
		if (abs(now_t - reconnect_t_) > 5)
		{
			try
			{
				OutputMsg(rmTip, "%d before connect.", NOW_T);
				if (sql_.Connect())
				{
					OutputMsg(rmTip, "%d after connect.", NOW_T);
					mysql_options(sql_.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
					return true;
				}
			}
			catch (...)
			{ }

			OutputMsg(rmError, "DB will reconnect after 5s");
			// 如果连接SQL失败则将在5秒后重试
			reconnect_t_ = now_t;
			return false;
		}
	}

	if (abs(now_t - next_ping_t_)> 20)
	{
		int ret = 0;

		if (sql_.Connected())
		{
			ret = sql_.Ping();

			if (ret)
			{
				OutputMsg(rmError, "mysql ping error, errcode=%d", ret);
				sql_.Disconnect();
				reconnect_t_ = 0; // 马上重连
			}
		}

		next_ping_t_ = now_t;
	}

	return true;
}

bool ActorMgr::LoadNameData()
{
	if (def_names_.LoadFromFile(DEF_RANDNAME) <= 0)
	{
		OutputMsg(rmError, ("can not load boy rand names"));
		return false;
	}

	if (char_names_.LoadFromFile(CHAR_RANDNAME) <= 0)
	{
		OutputMsg(rmError, ("can not load girl rand names"));
		return false;
	}

	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif

	SetupSQLConnection(&sql);

	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load actor names"));
			return false;
		}

	}

	int server_id = ServerInstance()->GetServerIndex();
	int err = sql.Query(loadmaxactoridseries, server_id);

	if (err != 0)
	{
		// 严重错误，服务器不能启动
		OutputMsg(rmError, "********** loadmaxactoridseries error! server stop!**********");
		return false;
	}
	else
	{
		MYSQL_ROW pRow = sql.CurrentRow();

		if (pRow && pRow[0])
		{
			actorid_series_ = StrToInt(pRow[0]);
			actorid_series_++;
		}
		else
		{
			actorid_series_ = 0; // db no data
		}

		OutputMsg(rmError, "********** load max actorid series is:%d **********", actorid_series_);
		sql.ResetQuery();
	}

	if (sql.Query(loadallactorname, server_id))
	{
		OutputMsg(rmError, ("can not load actor names, database call error"));
		return FALSE;
	}

	int count = 0;
	MYSQL_ROW row = sql.CurrentRow();

	while (row)
	{
		if (row[0] && row[0][0])
		{
			NameSortItem item;
			_STRNCPY_A(item.name_, row[0]);

			all_actor_name_.add_item(item);

			def_names_.UseName(row[0]);
			char_names_.UseName(row[0]);

			count++;
		}

		row = sql.NextRow();
	}

	//释放查询结果集
	sql.ResetQuery();
	OutputMsg(rmTip, ("%d actor name loaded"), count);

	return true;
}

//读取玩家曾经改过的名称的列表
bool ActorMgr::LoadOldActorNameData()
{
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif

	//配置数据库连接
	SetupSQLConnection(&sql);

	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load old actor names"));
			return false;
		}
	}

	//从数据库加旧的名称列表
	if (sql.Query(loadoldnamelist))
	{
		OutputMsg(rmError, ("can not load old actor names, database call error"));
		return false;
	}

	int nCount = 0;
	MYSQL_ROW pRow = sql.CurrentRow();

	while (pRow)
	{
		if (pRow[0] && pRow[0][0])
		{
			NameSortItem item;
			_STRNCPY_A(item.name_, pRow[0]);
			if (all_actor_name_.find(item) < 0)
			{
				all_actor_name_.add_item(item);
				def_names_.UseName(pRow[0]);
				char_names_.UseName(pRow[0]);
			}
			//ActorId* pAid = old_actor_name_.put(item.name_);
			if(pRow[1] && pRow[1][0])
			{
				ActorId aid;
				sscanf(pRow[1], "%d", &aid);
				old_actor_name_[item.name_] = aid;
			}
			nCount++;
		}

		pRow = sql.NextRow();
	}

	//释放查询结果集
	sql.ResetQuery();
	OutputMsg(rmTip, ("%d actor old name loaded"), nCount);

	return true;
}

bool ActorMgr::LoadFilterNames()
{
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif
	//配置数据库连接
	SetupSQLConnection(&sql);

	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load filter names"));
			return false;
		}
	}

	//从数据库加载屏蔽文字列表  NSSQL_LoadFilterNames
	if (sql.Query(loadfilternames))
	{
		OutputMsg(rmError, ("can not load filter names, database call error"));
		return false;
	}

	FreeFilterWords();

	filter_lock_.Lock();
	//创建屏蔽词匹配工具
	filter_words_ = CreateMBCSFilter(NULL);
	int count = 0;
	MYSQL_ROW row = sql.CurrentRow();

	while (row)
	{
		if (row[0] && row[0][0])
		{
			AddMBCSFilterStrToTable(filter_words_, row[0]);
			count++;
		}

		row = sql.NextRow();
	}

	//释放查询结果集
	sql.ResetQuery();
	filter_lock_.Unlock();

	OutputMsg(rmTip, ("%d filter name loaded"), count);
	return true;
}


bool ActorMgr::NameHasUser(const char* name)
{
	NameSortItem item;
	_STRNCPY_A(item.name_, name);
	return all_actor_name_.find(item) >= 0;
}

void ActorMgr::SetupSQLConnection(SQLConnection* sql)
{
	sql->SetHost(db_host_);
	sql->SetPort(db_port_);
	sql->SetDbName(db_name_);
	sql->SetUserName(db_user_);
	sql->SetPassWord(db_pw_);
	sql->SetConnectionFlags(CLIENT_FOUND_ROWS | CLIENT_MULTI_RESULTS);
}

void ActorMgr::SetDbConfig(const char* host, int port, const char* db_name, const char* user, const char* pw)
{
	_STRNCPY_A(db_host_, host);
	db_port_ = port;
	_STRNCPY_A(db_name_, db_name);
	_STRNCPY_A(db_user_, user);
	_STRNCPY_A(db_pw_, pw);

	SetupSQLConnection(&sql_);
}

void ActorMgr::EnterGame(GateUser* user, ActorId actor_id, const char* pf, const char* pfid, const char* appid, int serverId)
{
	//通知逻辑有人登陆了
	user->actor_id_ = actor_id;

	//GameInterMsg msg;
	//msg.msg_id_ = SSM_ACTOR_LOGIN;
	//msg.data_.user_ = user;
	//msg.data_.serverId_ = ServerInstance()->GetServerIndex();

	/*if (pf && pf[0] != '\0')
	{
		size_t len = strlen(pf);
		len = len > PFSTR_MAX_LEN ? PFSTR_MAX_LEN : len;
		msg.data_.pf_ = (char*)pf_str_alloc_.AllocBuffer(len + 1);
		_STRNCPY_S(msg.data_.pf_, pf, len + 1);
	}
	else
	{
		msg.data_.pf_ = NULL;
	}
	*/

	//static GameEngine* ge = GetGameEngine();
	//ge->PostMsg(msg);
	//static LoginQueue *login_queue = GetGameEngine()->GetLoginQueue();
	//login_queue->AddToQueue(user, ServerInstance()->GetServerIndex(), pf);
	GameInterMsg msg;
	msg.msg_id_ = SSM_ADD_LOGIN;
	msg.data_.user_ = user;
	msg.data_.serverId_ = serverId;
	if(pf) {
		_STRNCPY_A(msg.data_.pf_,pf);
	} else {
		memset(msg.data_.pf_, 0, PFSTR_MAX_LEN);
	}

	if (pfid) {
		_STRNCPY_A(msg.data_.pf_id_, pfid);
	} else {
		memset(msg.data_.pf_id_, 0, PFID_MAX_LEN);
	}

	if (appid) {
		_STRNCPY_A(msg.data_.appid_, appid);
	} else {
		memset(msg.data_.appid_, 0, APPID_MAX_LEN);
	}

	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

int ActorMgr::GetStrLenUtf8(const char* sName)
{
	if (!sName) return 0;

	int len = (int)strlen(sName);
	int ret = 0;

	for (const char* sptr = sName; (sptr - sName) < len && *sptr;)
	{
		unsigned char ch = (unsigned char)(*sptr);

		if (ch < 0x80)
		{
			sptr++;	// ascii
			ret++;
		}
		else if (ch < 0xc0)
		{
			sptr++;	// invalid char
		}
		else if (ch < 0xe0)
		{
			sptr += 2;
			ret++;
		}
		else if (ch < 0xf0)
		{
			sptr += 3;
			ret++;
		}
		else
		{
			// 统一4个字节
			sptr += 4;
			ret++;
		}
	}

	return ret;
}

bool ActorMgr::CheckNameStr(const char* sName)
{
	if (!sName) return false;

	//检查是否包含控制字符以及英文标点符号，这些字符是不被允许的
	const char* sptr = NULL;
	int len = (int)strlen(sName);

	for (sptr = sName; (sptr - sName) < len && *sptr;)
	{
		unsigned char ch = (unsigned char)(*sptr);

		if (ch < 0x80)
		{
			sptr++;	// ascii
		}
		else if (ch < 0xc0)
		{
			return false;
		}
		else if (ch < 0xe0)
		{
			sptr += 2;
		}
		else if (ch < 0xf0)
		{
			sptr += 3;
		}
		else
		{
			// 统一4个字节
			sptr += 4;
		}
	}

	//从名称过滤表中进行屏蔽字检查
	filter_lock_.Lock();

	if (filter_words_)
		sptr = MatchMBCSFilterWord(filter_words_, sName, NULL);
	else sptr = NULL;

	if (sptr == NULL)
	{
		if (!CheckAllowWord(sName))
			sptr = "";
	}

	filter_lock_.Unlock();
	return sptr == NULL;
}

const char* ActorMgr::LowerCaseNameStr(char* sNameStr)
{
	const char* sResult = sNameStr;
	int len = (int)strlen(sResult);

	for (; (sNameStr - sResult) < len && *sNameStr;)
	{
		int ch = (unsigned int) * sNameStr;

		if (ch >= 0x7F)
		{
			if (ch < 0xc0)
			{
				sNameStr++;
			}
			else if (ch < 0xe0)
			{
				sNameStr += 2;
			}
			else if (ch < 0xf0)
			{
				sNameStr += 3;
			}
			else
			{
				// 统一4个字节
				sNameStr += 4;
			}

			continue;
		}

		if (*sNameStr >= 'A' && *sNameStr <= 'Z')
		{
			*sNameStr |= 0x20;
		}

		sNameStr++;
	}

	return sResult;
}

void ActorMgr::FreeFilterWords()
{
	filter_lock_.Lock();

	if (filter_words_)
	{
		FreeMBCSFilter(filter_words_);
		filter_words_ = NULL;
	}

	filter_lock_.Unlock();
}

void ActorMgr::ProcessSysMsg()
{
	inter_msg_.flush();

	int count = inter_msg_.count();

	for (int i = 0; i < count; ++i)
	{
		GameInterMsg& msg = inter_msg_[i];
		OnRecvSysMsg(msg);
	}

	inter_msg_.clear();
}

void ActorMgr::OnRecvSysMsg(GameInterMsg& msg)
{
	static GameConnMgr* mgr = ServerInstance()->GetGameConnMgr();

	switch (msg.msg_id_)
	{
	case imReloadScript:
		script_.LoadScript(lua_fn);
		break;

	case imReloadFilterName:
		LoadFilterNames();
		break;

	case imAddKey:
		{
			CrossUserData* keyData = (CrossUserData*)msg.data_.buffdata_;
			AddCrossKey(*keyData);
			key_data_alloc_.FreeBuffer(keyData);
		}
		break;

	case imAddOnline:
		{
			STATIC_ASSERT(sizeof(ActorId) == 4);
			int serverid = LOINT32(msg.data_.handle_);
			ActorId aid = HIINT32(msg.data_.handle_);
			AddOnline(serverid, aid);
		}
		break;

	case imRemoveOnline:
		{
			ActorId aid = (ActorId)msg.data_.handle_;
			RemoveOnline(aid);
		}
		break;

	case imBatchOnline:
		{
			DataPacket* dp = msg.data_.packet_;
			dp->setPosition(0);
			AddBatchOnline(*dp);
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
		break;

	case imAddGameClient:
		{
			DataPacket* dp = msg.data_.packet_;
			dp->setPosition(0);
			const char* ip = NULL;
			int port = 0;
			int sid = 0;
			(*dp) >> ip >> port >> sid;
			AddGameClient(ip, port, sid);
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
		break;

	case imDelGameClient:
		{
			DataPacket* dp = msg.data_.packet_;
			dp->setPosition(0);
			int sid = 0;
			(*dp) >> sid;
			DelGameClient(sid);
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
		break;

	case imBroadCast:
		{
			DataPacket* dp = (DataPacket*)msg.data_.packet_;
			int sid = msg.data_.dbsid_;
			SendMsgToAllGameClient(msg.data_.cmd_, dp->getMemoryPtr(), dp->getPosition(), sid);
#ifndef TEST_CROSS_MEM
			delete dp;
#else
			dp->~DataPacket();
			ServerInstance()->GetActorMgr()->GetAlloc().FreeBuffer(dp);
#endif
		}
		break;

	case imUserChange:
		{
			ActorId aid = (ActorId)msg.data_.dbsid_;
			SendMsgToAllGameClient((int)msg.data_.cmd_, &aid, sizeof(aid), 0);

			if (ServerInstance()->IsBattleSrv())
				mgr->PostMsg(GameConnMgr::gcUserChange, msg.data_.cmd_, aid, 0, 0);
		}
		break;

	case imCloseUser:
	case imCloseUserInActorMgr:
		ActorSortItem item;
		item.accountId_ = msg.data_.account_id_;
		online_list_.remove_item(item, true);
		break;

	case imGetKeyResp:
		{
			CrossUserData* keyData = (CrossUserData*)msg.data_.buffdata_;
			DealKeyResp(*keyData, msg.data_.param1_);
			key_data_alloc_.FreeBuffer(keyData);
		}
		break;
	case imChangeUserName:
	{
		DataPacket* dp = msg.data_.packet_;
		dp->setPosition(0);
		ActorId rawAid = 0;
		int sex = 0;
		int way = 0;
		const char* name = NULL;
		const char* rawName = NULL;
		(*dp) >> rawAid >> sex >> way >> name >> rawName;

		static EntityMgr* em = GetGameEngine()->GetEntityMgr();
		Actor* actor = em->GetActorPtrById(rawAid);
		if (actor == NULL)
		{
			delete dp;
			return;
		}
		int result = NOERR;

		if (way == cnwRandom) // 用个随机名
		{
			while (true)
			{
				const char* randName = GetRandomName(sex);
				if (!randName)
				{
					result = ERR_NORANDOMNAME;
					break;
				}
				if (!(NameHasUser(name) && NameHasUserFromLasts(name) == 0))
				{
					name = randName;
					if (ChangeActorName(rawAid, name, rawName) != NOERR)
					{
						result = ERR_SQL;
					}
					break;
				}
			}
		}
		else
		{
			bool isUse = NameHasUser(name); // 曾经用过和现在使用中的名称全部在里面
			if (!isUse)	// 未被使用
			{
				result = ERR_SQL;
				if (ChangeActorName(rawAid, name, rawName) == NOERR)
				{
					result = NOERR;
				}
			}
			else
			{
				result = ERR_SAMENAME;
				ActorId aId = NameHasUserFromLasts(name);
				if (aId == rawAid) // 曾经的使用者为本人，可以重复用
				{
					if (ChangeActorName(rawAid, name, rawName) == NOERR)
					{
						result = NOERR;
					}
				}
			}
		}

		static BaseAllocator alloc("GameClientAlloc");
		static GameEngine* ge = GetGameEngine();
		GameInterMsg sendMsg;
		sendMsg.msg_id_ = SSM_USER_CHANGE_NAME;
		sendMsg.data_.packet_ = new DataPacket(&alloc);
		(*sendMsg.data_.packet_) << result << rawAid << name << rawName << way;
		ge->PostMsg(sendMsg);

		delete dp;

	}
	break;

	default:
		break;
	}
}

int ActorMgr::GetOnlinePos(int accountid)
{
	ActorSortItem item;
	item.accountId_ = accountid;
	return online_list_.find(item);
}

bool ActorMgr::GetCrossKeyData(ActorId aid, CrossUserData& data)
{
	// 查找是否有这个key
	bool ret = true;

	data.actorId_ = aid;

	int it = key_list_.find(data);

	if (it < 0)
	{
		ret = false;
	}
	else
	{
		data = key_list_[it];
		key_list_.remove(it);
	}

	return ret;
}

void ActorMgr::AddCrossKey(CrossUserData& data)
{
	// 如果已有就直接替换
	data.time_out_ = NOW_T + 10; // 保留10s
	int idx = key_list_.find(data);

	if (idx >= 0)
	{
		key_list_[idx] = data;
	}
	else
	{
		key_list_.add_item(data);
	}
}

void ActorMgr::AddOnline(int serverid, ActorId aid)
{
	OnlineUserData data;
	data.actorId_ = aid;
	data.serverId_ = serverid;

	int idx = battle_online_list_.find(data);

	if (idx >= 0)
	{
		battle_online_list_[idx] = data;
	}
	else
	{
		battle_online_list_.add_item(data);
	}

	// 如果在本服登陆了，则踢下线
	static GameEngine* ge = GetGameEngine();
	GameInterMsg msg;
	msg.msg_id_ = SSM_CLOSE_ACTOR_BY_ID;
	msg.data_.handle_ = aid;
	ge->PostMsg(msg);
}

void ActorMgr::AddBatchOnline(DataPacket& dp)
{
	int serverid = 0;
	dp >> serverid;
	int count = 0;
	dp >> count;

	count = __min(count, 4096 * 2);

	for (int i = 0; i < count; ++i)
	{
		ActorId aid = 0;
		dp >> aid;
		AddOnline(serverid, aid);
	}
}

void ActorMgr::RemoveOnline(ActorId aid)
{
	OnlineUserData data;
	data.actorId_ = aid;

	battle_online_list_.remove_item(data, true);
}

bool ActorMgr::IsLoginBattle(ActorId actorid, bool kickNow)
{
	OnlineUserData data;
	data.actorId_ = actorid;

	int idx = battle_online_list_.find(data);
	bool ret = (idx >= 0);

	if (kickNow && ret)
	{
		static ActorMgr* mgr = ServerInstance()->GetActorMgr();
		GameInterMsg msg;
		msg.msg_id_ = ActorMgr::imUserChange;
		msg.data_.cmd_ = gpCloseUser;
		msg.data_.dbsid_ = actorid;
		mgr->PostMsg(msg);
	}

	return ret;
}

int ActorMgr::IsLogOutBattle(ActorId actorid)
{
	/*
	char sql[512];
	SNPRINTFA(sql, sizeof(sql), "select cw_fbhdl_sid from actors where actorid = %d", actorid);

	int err = sql_.Query(sql);

	if (err) return 0;

	MYSQL_ROW row = sql_.CurrentRow();

	int64_t cw_fbhdl_sid;
	int sid = 0;

	if (row)
	{
		sscanf(row[0], I64FMT, &cw_fbhdl_sid);

		sid = HIINT32(cw_fbhdl_sid);
	}

	sql_.ResetQuery();

	return sid;
	*/
	return 0;
}

bool ActorMgr::AddGameClient(const char* ip, int port, int serverId)
{
	// game_client_list_没有加锁，所以不支持多线程访问
	// 这么做的原因是 这个列表应该是在程序一启动的时候就初始化完成这些连接，不应该在游戏运行中动态增加
	GameClient** list = game_client_list_;
	int count = game_client_list_.count();
	for (int i = 0; i < count; ++i) {
		GameClient* conn = list[i];
		if (!conn) continue;

		if (conn->GetTargetSid() == serverId) {
			return true;
		}
	}

	GameClient* newClient = new GameClient(ServerInstance());
	newClient->SetHost(ip);
	newClient->SetPort(port);
	newClient->SetTargetSid(serverId);

	game_client_list_.add(newClient);

	return newClient->Startup();
}

void ActorMgr::ClearGameClient()
{
	GameClient** list = game_client_list_;
	int count = game_client_list_.count();
	for (int i = 0; i < count; ++i) {
		GameClient* conn = list[i];

		if (!conn) continue;

		conn->Stop();
		SafeDelete(conn);
	}

	game_client_list_.clear();
}

bool ActorMgr::HasGameClient(int sid)
{
	GameClient** list = game_client_list_;
	int count = game_client_list_.count();

	for (int i = 0; i < count; i++) {
		GameClient* conn = list[i];

		if (conn && conn->GetTargetSid() == sid && conn->connected()) return true;
	}


	return false;
}

void ActorMgr::DelGameClient(int sid)
{
	GameClient** list = game_client_list_;
	int count = game_client_list_.count();
	for (int i = 0; i < count; ++i) {
		GameClient* conn = list[i];

		if (!conn || conn->GetTargetSid() != sid) continue;

		conn->Stop();
		SafeDelete(conn);
		game_client_list_.remove(i);
		break;
	}
}

void ActorMgr::SendMsgToAllGameClient(int cmd, void* buf, size_t size, int sid)
{
	GameClient** list = game_client_list_;
	int count = game_client_list_.count();

	for (int i = 0; i < count; ++i) {
		GameClient* conn = list[i];
		if (!conn || (sid != 0 && sid != conn->GetTargetSid())) continue;

		DataPacket& pack = conn->allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(buf, size);
		conn->flushProtoPacket(pack);
		if (sid != 0) break;
	}
}

void ActorMgr::GenerateKey(char* buf, int size)
{
	// key:ascII 48- 90
	const char beg = 48;
	const int s = 90 - 48 + 1;
	int i = 0;

	for (; i < (size - 1); i++)
	{
		buf[i] = beg + (char)wrand(s);
	}

	buf[i] = 0;
}

bool ActorMgr::LoadCrossWarTeamName()
{
	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif
	//配置数据库连接
	SetupSQLConnection(&sql);

	if (!sql.Connected())
	{
		if (sql.Connect())
		{
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else
		{
			OutputMsg(rmError, ("can not load cross war team names"));
			return false;
		}
	}

	if (sql.Query(loadcrosswarteamnames))
	{
		OutputMsg(rmError, ("can not load cross war team names, database call error"));
		return false;
	}

	//static GameWarMgr& mgr = GetGameEngine()->GetGameWarMgr();
	//mgr.ClearUsedName();

	/*int count = 0;
	MYSQL_ROW row = sql.CurrentRow();

	while (row)
	{
		if (row[0] && row[0][0])
		{
			mgr.AddUsedName(row[0]);
			count++;
		}

		row = sql.NextRow();
	}*/

	//释放查询结果集
	sql.ResetQuery();

	return true;
}

void ActorMgr::SendPwResult(int ret, GateUser* user)
{
	static uint8_t data[3] = { Protocol::CMD_Login, sUserPw, 0 };
	data[2] = ret;
	SendToGate(user->netid_, (const char*)data, sizeof(data));
}

int ActorMgr::NameHasUserFromLasts(const char* name)
{
	//ActorId* pAid = old_actor_name_.get(name);
	//if (!pAid) return 0;

	//return *pAid;

	auto it = old_actor_name_.find(name);
	if (it != old_actor_name_.end())
	{
		return it->second;
	}
	return 0;
}

int ActorMgr::LoginOtherSrv(GateUser* user, int sid, ActorId aid, bool newpos /* = false */, unsigned int fbhdl /* = 0 */, int sceneid /* = 0 */, int x /* = 0 */, int y /* = 0 */, const char* reason /* = "" */)
{
	static GameServer* srv = ServerInstance();
	static GameEngine* ge = GetGameEngine();

	if (srv->GetBattleSrvFlag() == bsCommSrv)
	{
		if (!ge->HasBattleSrv(sid)) return -1;

		if (!HasGameClient(sid)) return -1;
	}

	ActorMgr::CrossUserData data;
	data.serverId_ = srv->GetServerIndex();

	if (data.serverId_ == sid) return -1;

	data.actorId_ = aid;
	data.accountId_ = user->account_id_;
	_STRNCPY_A(data.account_name_, user->account_name_);
	data.gm_ = (user->gm_ != 0);
	ActorMgr::GenerateKey(data.key_, sizeof(data.key_));
	data.target_sid_ = sid;
	//data.cross_type_ = CROSSLOGINTYPE_NOTENTERGAME;

	//这个用应该有现成安全问题
	srv->SendMsgToAllGameClient(&data, sizeof(data),
	                            gpKeyReq, sid);

	OutputMsg(rmError, "LoginOtherSrv:%d,sceneid:%d,actorid:%d,reason=%s",
	          sid, sceneid, aid, reason ? reason : "ActorMgr LoginOtherSrv");

	ActorNetInfo actor_net(user->netid_);
	actor_net_list_.put(aid, actor_net);

	return 0;
}

void ActorMgr::DealKeyResp(CrossUserData& data, int loginType)
{
	static GameEngine* ge = GetGameEngine();

	GameRoute* r = ge->GetGameRoute(data.target_sid_);

	if (r)
	{
		GateUser* user = GetGateUserByActor(data.actorId_);

		if (!user)
		{
			OutputMsg(rmError, "can not get user gate actorid %d!!!", data.actorId_);
			return;
		}

		int idx = wrand(r->count_);
		static DataPacket dp(&alloc);
		static uint8_t hdr[] = { Protocol::CMD_Login, sCrossKey };
		dp.writeBuf(hdr, sizeof(hdr));
		dp << (int)data.target_sid_ << r->t[idx].host_ << (int)r->t[idx].port_ << data.key_;
		SendToGate(user->netid_, (const char*)dp.getMemoryPtr(), dp.getLength());
		dp.setPosition(0);
	}

	actor_net_list_.remove(data.actorId_);
}

GateUser* ActorMgr::GetGateUserByActor(ActorId id)
{
	ActorNetInfo* actor_net = actor_net_list_.get(id);

	if (actor_net)
	{
		GameGate* gate = (GameGate*)gate_mgr_->GetGate(actor_net->netid.gate_id_);

		if (!gate)
		{
			OutputMsg(rmError, "recv a packet invalid source!");
			return NULL;
		}

		GateUser* user = gate->GetUser(actor_net->netid);

		if (!user)
		{
			OutputMsg(rmError, "recv a packet invalid user!");
			return NULL;
		}

		if (user->actor_id_ == id || !user->actor_id_)
		{
			return user;
		}
		else
		{
			actor_net_list_.remove(id);
			OutputMsg(rmError, "the actor net id info is wrong actorid %d!", id);
		}

	}

	return NULL;
}


static int ParseNumber(const char* sText)
{
	if (strlen(sText) > 2 && sText[0] == '0' && (sText[1] == 'x' || sText[1] == 'X'))
	{
		int val = 0;
		sscanf(sText, "%x", &val);
		return val;
	}

	return StrToInt(sText);
}

bool ActorMgr::LoadAllowWords()
{
	static const char* sNoticeFile = "data/allowword.txt";

	if (!FDOP::FileExists(sNoticeFile))
	{
		OutputMsg(rmError, ("no allowword.txt file"));
		return false;
	}

	OutputMsg(rmTip, "load allowword.txt");

	stream::MemoryStream ms(NULL);

	if (ms.loadFromFile(sNoticeFile) <= 0)
	{
		OutputMsg(rmError, "load allowword.txt error");
		return false;
	}

	ZeroMemory(allow_words_, sizeof(allow_words_));

	filter_lock_.Lock();

	char* sPtr = (char*)ms.getMemory();

	while (*sPtr)
	{
		char* sTag = strchr(sPtr, '\n');	//搜索换行符

		if (sTag)
		{
			if (*(sTag - 1) == '\r')
			{
				*((char*)(sTag - 1)) = 0;
			}

			*(char*)sTag = 0;
			sTag++;

			if (*sTag)
			{
				ParseAllowWord(sPtr);
				sPtr = sTag;
			}
		}

		if (NULL == sTag || !(*sTag))
		{
			ParseAllowWord(sPtr);
			break;
		}
	}

	filter_lock_.Unlock();

	return true;
}

bool ActorMgr::CheckAllowWord(const char* sName)
{
	if (!sName) return false;

	const char* sptr = NULL;
	int len = (int)strlen(sName);
	const char* endptr = sName + len;

	for (sptr = sName; (sptr - sName) < len && *sptr;)
	{
		unsigned char ch = (unsigned char)(*sptr);

		int e = 0;

		if (ch < 0x80)
		{
			e = sptr[0];

			sptr++;	// ascii
		}
		else if (ch < 0xc0)
		{
			return false;
		}
		else if (ch < 0xe0)
		{
			/*2:<11000000>*/
			if (sptr + 2 > endptr) return false;

			e = (sptr[0] & 0x1f) << 6;
			e |= (sptr[1] & 0x3f);

			sptr += 2;
		}
		else if (ch < 0xf0)
		{
			/*3:<11100000>*/
			if (sptr + 3 > endptr) return false;

			e = (sptr[0] & 0x0f) << 12;
			e |= (sptr[1] & 0x3f) << 6;
			e |= (sptr[2] & 0x3f);

			sptr += 3;
		}
		else if (ch < 0xf8)
		{
			if (sptr + 4 > endptr) return false;

			/*4:<11110000>*/
			e = (sptr[0] & 0x07) << 18;
			e |= (sptr[1] & 0x3f) << 12;
			e |= (sptr[2] & 0x3f) << 6;
			e |= (sptr[3] & 0x3f);

			// 统一4个字节
			sptr += 4;
		}
		else
		{
			// 不支持超过4个字节
			return false;
		}

		if (e < 0 || e >= 0xffff) return false;

		if (!allow_words_[e]) return false;
	}

	return true;
}

bool ActorMgr::ParseAllowWord(char* sText)
{
	if (!sText) return false;

	int st = 0, en = 0;

	char* sTag = strchr(sText, ',');

	if (sTag)
	{
		*sTag = 0;

		st = ParseNumber(sText);

		sText = sTag + 1;

		while (sText && (*sText == ' ')) sText++;

		if (!sText || *sText == 0) return false;

		en = ParseNumber(sText);
	}
	else
	{
		st = ParseNumber(sText);
		en = st;
	}

	if (st < 0 || st >= 0xffff || en < 0 || en >= 0xffff || st > en)
	{
		OutputMsg(rmError, "allow word range error : %d - %d", st, en);
		return false;
	}

	memset(&allow_words_[st], 1, sizeof(allow_words_[0]) * (en - st + 1));

	return true;
}

