#include "stdafx.h"
#include <ctype.h>
#include "luabase/base_script.h"
#include <time.h>
#include "second_time.h"
#include "utils/fdop.h"


#if (defined(WIN32) || defined(WINDOWS))
#elif DCAPI
#include "dcapi_cpp.h"
using namespace DataCollector;
#endif

int LoggerServer::swith_flag = 0;

//static const char* logCounter =
//    ("insert into log_counter_%d%02d%02d(logdate,actorid,user_level,counter,value,extra,kingdom,phylum,classfield,family,genus,serverid) "
//     "values(now(),%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%d');");
//static const char* logInstall =
//    ("insert into log_install_%d%02d%02d(logdate,actorid,source,affiliate,creative,family,genus,from_uid,extra,serverid) "
//     "values(now(),'%s','%s','%s','%s','%s','%s','%s','%s',%d);");
//
//static const char* logDau =
//    ("insert into log_dau_%d%02d%02d(logdate,actorid,source,affiliate,creative,family,genus,ip,from_uid,extra,serverid) "
//     "values(now(),'%s','%s','%s','%s','%s','%s','%s','%s','%s',%d);");
//static const char* logEconomy =
//    ("insert into log_economy_%d%02d%02d(logdate,actorid,currency,amount,value,kingdom,phylum,classfield,family,genus,extra,extra2,serverid)"
//     " values(now(),%d,'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d');");
//static const char* logMilestone =
//    ("insert into log_milestone_%d%02d%02d(logdate,actorid,milestone,value,extra,serverid)"
//     " values(now(),%d,'%s','%s','%s','%d');");


//#ifdef _MSC_VER
//const char* LoggerServer::dbLogDir_ = "f:/";
//#else
//const char* LoggerServer::dbLogDir_ = "/data/loggerserver/";
//#endif


void OnBlock(void* ptr)
{
	//if (ptr)
	//{
	//	LoggerServer* srv = (LoggerServer*)ptr;
	//	srv->GetSqlConnection()->Disconnect();
	//}
	//abort();
	printf("logger server on block.\n");
}

//获取当前时间到下个一号时间间隔
int GetMonsthIntervalFromNow()
{
	SystemTime st;
	GetSystemTime(st);

	SecondTime now;
	now = now.encode(st);

	SecondTime sc_st;
	st.mday_ = 1;
	st.hour_ = 0;
	st.min_ = 0;
	st.sec_ = 0;
	if (st.mon_ == 12)
	{
		st.mon_ = 1;
		st.year_ = st.year_ + 1;
	}
	else
	{
		st.mon_ = st.mon_ + 1;
	}

	sc_st = sc_st.encode(st);
	return sc_st - now;
}

LoggerServer::LoggerServer(void) : ServerSocket("LoggerServer"), /*ct_runing_(false), ct_free_(true), cTThread_(0),*/
	log_alloc_("log_alloc_"),
	next_conn_db_t_(0),
	next_ping_t_(0),
	next_conn_table_db_t_(0),
	next_table_ping_t_(0)
{
	conf_.ReadConfig();

	// 设置服务器的基本属性
	SetServiceName(conf_.SrvConf.szServiceName);
	SetServiceHost(conf_.SrvConf.szAddr);
	SetServicePort(conf_.SrvConf.nPort);

#ifdef DB_UTF8
	db_.SetUtf8(true);
	table_db_.SetUtf8(true);
#endif

	SetDbConnection(db_);

	table_db_.SetInfileFlag(true);
	SetDbConnection(table_db_);

	list_.setLock(&list_lock_);
	reload_createTable_script_ = false;
	reload_log_script_ = false;
	//vsp_def_.LoadDefinitions("./data/vspdef.txt");
	std::string fn = "./data/vspdef.txt";
	vsp_def_.LoadDefinitions(fn.c_str());


#if (defined(WIN32) || defined(WINDOWS))
#elif defined(DCAPI)
	std::string logName = "appoperlog";
	int ret = dclogger.init(logName, false);

	if (ret != 0)
	{
		OutputMsg(rmError, ".......... dclogger.init error! .....ret=%d\n", ret);
	}

#endif
	WatchThread* watch = GetWatch();

	if (watch) watch->AddWatch(1, 120000, &OnBlock, this);

	cli_sock_ = SOCKET_ERROR;
	cli_sock_start_time_ = 0;

	DKMLimit.clear();
	//DKMLimit.push_back("1060\n");
	//2, 5, 7, 8, 9, 10, 11, 12, 14, 15
	DKMLimit.push_back("2\n");
	DKMLimit.push_back("5\n");
	DKMLimit.push_back("7\n");
	DKMLimit.push_back("8\n");
	DKMLimit.push_back("9\n");
	DKMLimit.push_back("10\n");
	DKMLimit.push_back("11\n");
	DKMLimit.push_back("12\n");
	DKMLimit.push_back("14\n");
	DKMLimit.push_back("15\n");
}


LoggerServer::~LoggerServer(void)
{
	list_.flush();

	for (int i = 0; i < list_.count(); ++i)
	{
		LogData& data = list_[i];
		free_list_.add(data.dp_);
	}

	for (int i = 0; i < free_list_.count(); i++)
	{
		DataPacket* dp = free_list_[i];
		delete dp;
	}

	free_list_.empty();
}

NetSession* LoggerServer::NewSession(SOCKET socket, sockaddr_in* addrin)
{
	if (addrin == NULL)
	{
		return NULL;
	}

	LoggerSession* pClientSocket = new LoggerSession(this, socket, addrin);
	pClientSocket->setRecvBufSize(1024 * 1024);
	pClientSocket->setSendBufSize(1024 * 1024);
	return pClientSocket;
}

void LoggerServer::PrecessData(LogData& data, BaseScript& script, bool final)
{
	data.dp_->setPosition(0);

	switch (data.cmd_)
	{
	case 0:
		break;

	case lmCounter:
		{
			InsertCounter(data.serverId_, *data.dp_, final);
			break;
		}

	case lmInstall:
		{
			InsertInstall(data.serverId_, *data.dp_);
			break;
		}

	case lmDau:
		{
			InsertDau(data.serverId_, *data.dp_);
			break;
		}

	case lmEconomy:
		{
			InsertEconomy(data.serverId_, *data.dp_, final);
			break;
		}

	case lmChat:
		{
			InsertChat(data.serverId_, *data.dp_, final);
			break;
		}

	case lmMilestone:
		{
			InsertMilestone(data.serverId_, *data.dp_, final);
			break;
		}

	case lmCounterDB:
		{
			break;
		}

	case lmDcApiData:
		{
			doSendDcApiLog(*data.dp_);
			break;
		}

	case lmDcApiDataList:
		{
			doSendDcApiLogList(*data.dp_);
			break;
		}

	case lmDcApiProto:
		{
			doSendDcApiProtoLog(*data.dp_);
			break;
		}

	case lmTLog:
		{
			ProcessTLog(data.serverId_, *data.dp_);
			break;
		}
	case lmDKMLog:
	{
		WriteDKMLog(data.serverId_, *data.dp_);
		break;
	}

	default:
		ScriptValueList args;
		args << data.cmd_;
		args << data.serverId_;
		args << (void*)(data.dp_);
		args << (void*)(&db_);
		log_script_.Call("precessLog", &args, &args);
		break;
	}
}

void LoggerServer::SetDbConnection(SQLConnection& db)
{
	db.SetHost(conf_.DbConf.szHost);
	db.SetPort(conf_.DbConf.nPort);
	db.SetDbName(conf_.DbConf.szDbName);
	db.SetUserName(conf_.DbConf.szUser);
	db.SetPassWord(conf_.DbConf.szPassWord);//这个要解密
	//多个客户端连接，数据库操作类要加锁
	db.SetMultiThread(true);
	db.SetConnectionFlags(CLIENT_FOUND_ROWS | CLIENT_MULTI_RESULTS);
	BOOL boConnected = db.Connect();

	if (boConnected)
	{
		OutputMsg(rmTip, ("connect to db server succ"));
	}
	else
	{
		OutputMsg(rmError, ("connect to db server fail!"));
	}
}

bool LoggerServer::ConnectSQL(SQLConnection& db, time_t& conn_t, time_t& ping_t)
{
	time_t now_t = NOW_T;

	if (now_t >= conn_t)
	{
		if (!db.Connected())
		{
			SetDbConnection(db);

			if (db.Connect())
			{
				mysql_options(db.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
			}
		}

		conn_t = now_t + 5;
	}

	if (now_t >= ping_t)
	{
		int ret = 0;

		if (db.Connected())
		{
			ret = db.Ping();

			if (ret)
			{
				OutputMsg(rmError, "mysql ping error, errcode=%d", ret);
				db.Disconnect();
			}
		}

		ping_t = now_t + 20;
	}

	return true;
}

bool LoggerServer::DoStartup()
{
	int err = 0;

	ct_runing_ = true;
#ifdef _MSC_VER
	cTThread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateTablesThreadRoutine, this, 0, NULL);

	if (!cTThread_)
	{
		err = GetLastError();
	}

#else

	if (pthread_create(&cTThread_, NULL, CreateTablesThreadRoutine, this))
	{
		err = errno;
	}

#endif

	if (err)
	{
		OutputError(err, ("create thread fail！"));
		return false;
	}

	OutputMsg(rmTip, ("create thread succ！"));
	ct_free_ = false;

	pt_runing_ = true;
#ifdef _MSC_VER
	pTThread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoggThread, this, 0, NULL);

	if (!pTThread_)
	{
		err = GetLastError();
	}

#else

	if (pthread_create(&pTThread_, NULL, LoggThread, this))
	{
		err = errno;
	}

#endif

	if (err)
	{
		OutputError(err, ("create thread fail！"));
		return false;
	}

	OutputMsg(rmTip, ("create thread succ！"));
	pt_free_ = false;

	return true;
}

void LoggerServer::DoStop()
{
	ct_runing_ = false;

	while (!ct_free_)
	{
		Sleep(100);
	}

#ifdef _MSC_VER
	CloseThread(cTThread_);
#endif

	pt_runing_ = false;

	while (!pt_free_)
	{
		Sleep(100);
	}

#ifdef _MSC_VER
	CloseThread(pTThread_);
#endif
}

#ifdef _MSC_VER
void LoggerServer::CreateTablesThreadRoutine(LoggerServer* ptr)
#else
void* LoggerServer::CreateTablesThreadRoutine(void* ptr)
#endif
{
	LoggerServer* srv = (LoggerServer*)ptr;
	std::string fn = "./data/main.lua";

	// 使用lua脚本处理
	BaseScript& script = srv->create_script_;
	script.SetVspDef(&srv->vsp_def_);
	script.LoadScript(fn.c_str());

	srv->create_tbl_next_t_ = 0;
	srv->import_t_ = 0;

	while (srv->ct_runing_)
	{
		if (srv->reload_createTable_script_)
		{
			srv->reload_createTable_script_ = false;
			script.LoadScript(fn.c_str());
		}

		srv->ConnectSQL(srv->table_db_, srv->next_conn_table_db_t_, srv->next_table_ping_t_);

		time_t now_t = NOW_T;

		if (now_t >= srv->create_tbl_next_t_)
		{
			srv->create_tbl_next_t_ = now_t + GetMonsthIntervalFromNow();

			ScriptValueList args;
			args << (void*)(&(srv->table_db_));
			script.Call("createTable", &args, &args);
		}

		// 导入数据
		if (now_t >= srv->import_t_)
		{
			srv->import_t_ = now_t + 60;
			// 每分钟执行一次
			SystemTime st;
			GetSystemTime(st);
			SecondTime now;
			now = now.encode(st);

			SystemTime st_begin = st;
			SystemTime st_end = st;

			st_begin.hour_ = TIME_ST_H;
			st_begin.min_ = TIME_ST_M;
			st_begin.sec_ = 0;
			st_end.hour_ = TIME_END_H;
			st_end.min_ = TIME_END_M;
			st_end.sec_ = 0;

			SecondTime sc_st;
			sc_st = sc_st.encode(st_begin);
			SecondTime sc_end;
			sc_end = sc_end.encode(st_end);

			const int delay = 6;
			// 当天的时间倒退6天，看看有没有文件没导入数据库
			SecondTime start = now.today() - 24 * 3600 * delay;
			SecondTime end = now / 60 * 60 - 2 * 60;

			if (now > sc_st && now < sc_end)
			{
				swith_flag = 0; //暂时先不这么干
			}
			else
			{
				swith_flag = 0;
			}

			if (swith_flag == 0)
			{
				for (; start <= end; start += 60)
				{
					start.decode(st);

					srv->ImportData("log_counter_", st);
					srv->ImportData("log_install_", st);
					srv->ImportData("log_dau_", st);
					srv->ImportData("log_economy_", st);
					srv->ImportData("log_milestone_", st);
				}
			}

		}

		Sleep(1000);
	}

	srv->ct_runing_ = false;//标记接受连接的线程已经退出
	srv->ct_free_ = true;

	OutputMsg(rmError, "create table exit");
#ifdef _MSC_VER
	ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

#ifdef _MSC_VER
void LoggerServer::LoggThread(LoggerServer* ptr)
#else
void* LoggerServer::LoggThread(void* ptr)
#endif
{
	const char* fn = "./data/main.lua";

	LoggerServer* srv = (LoggerServer*)ptr;
	BaseScript& script = srv->log_script_;
	script.SetVspDef(&srv->vsp_def_);
	script.LoadScript(fn);
	uint32_t last_t = 0;
	while (srv->pt_runing_)
	{
		WatchThread* watch = srv->GetWatch();

		if (watch)
		{
			if ((uint32_t)NOW_T > last_t)
			{
				OutputMsg(rmTip, "report ... %u", (uint32_t)NOW_T);
				last_t = (uint32_t)NOW_T + 30;
			}
			watch->Report(1);
		}

		if (srv->reload_log_script_)
		{
			srv->reload_log_script_ = false;
			script.LoadScript(fn);
		}

		srv->ConnectSQL(srv->db_, srv->next_conn_db_t_, srv->next_ping_t_);

		if (srv->list_.appendCount() > 0)
		{
			srv->list_.flush();
		}
		
		if (srv->list_.count() <= 0)
		{
			Sleep(10);
			continue;
		}

		if (srv->list_.count() >= 100)
		{
			OutputMsg(rmError, "too many packet!%d", srv->list_.count());
		}

		time_t report_t = NOW_T;
		for (int i = 0; i < srv->list_.count(); ++i)
		{
			time_t now_t = NOW_T;
			if ((now_t - report_t) > 60)
			{
				if (watch)
				{
					watch->Report(1);
					OutputMsg(rmTip, "report ... %u", (uint32_t)NOW_T);
				}
				report_t = now_t;
			}

			LogData& data = srv->list_[i];
			srv->PrecessData(data, script, i % 50 == 0);		// 一次最多50条,实际测试发现一次超过96条会丢失数据。。。

			srv->free_lock_.Lock();
			srv->free_list_.add(data.dp_);
			srv->free_lock_.Unlock();

			now_t = NOW_T;
			if ((now_t - report_t) > 60)
			{
				OutputMsg(rmTip, "long time");
			}
		}

		srv->list_.clear();
	}

	srv->pt_runing_ = false;//标记接受连接的线程已经退出
	srv->pt_free_ = true;
#ifdef _MSC_VER
	ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

void LoggerServer::PostLogPacket(int serverId, int cmd, const char* buf, int size)
{
	if (!buf || size <= 0) return;

	DataPacket* dp = NULL;

	free_lock_.Lock();

	if (free_list_.count() > 0)
	{
		dp = free_list_.pop();
	}

	free_lock_.Unlock();

	if (!dp)
	{
		dp = new DataPacket(&log_alloc_);
	}

	dp->setLength(0);
	dp->writeBuf(buf, size);

	LogData data;
	data.serverId_ = serverId;
	data.cmd_ = cmd;
	data.dp_ = dp;
	list_.append(data);
}

const char* LoggerServer::UrlEncodeSize(const char* msg, char* out, int size)
{
	static const char* digits = "0123456789ABCDEF";
	const char* pInTmp   = msg;
	char* pOutTmp = out;

	while (*pInTmp && size-- > 0)
	{
		if (isalnum(*pInTmp))
			*pOutTmp++ = *pInTmp;
		else if (isspace(*pInTmp))
			*pOutTmp++ = '+';
		else
		{
			*pOutTmp++ = '%';
			*pOutTmp++ = digits[(*pInTmp >> 4) & 0x0F];
			*pOutTmp++ = digits[*pInTmp & 0x0F];
		}

		pInTmp++;
	}

	*pOutTmp = '\0';

	return out;
}

void LoggerServer::InsertCounter(int serverId, DataPacketReader& inPacket, bool final)
{
	LCounter data;
	inPacket >> data;

	if (data.flag_ & lfiDB)
	{
		SystemTime st;
		GetSystemTime(st);

		char buf[1024 * 4];
		long long int aid = (long long int)data.actorid_;
		SNPRINTFA(buf, sizeof(buf) - 1, "%d-%d-%d %d:%d:%d\t%lld\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",
		          st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
		          aid, data.user_level_, data.counter_, data.value_, data.extra_, data.kingdom_, data.phylum_,
		          data.classfield_, data.family_, data.genus_, serverId);
		char tableName[256];
		SNPRINTFA(tableName, sizeof(tableName) - 1, "log_counter_%d%02d%02d", st.year_, st.mon_, st.mday_);
		WriteFile(tableName, buf, st);
	}

	// openid 不为空才发送到bi
	if (data.flag_ & lfiBI)
	{
		char para[1024];
		char user_level[512];
		char counter[512];
		char value[512];
		char extra[512];
		char kingdom[512];
		char phylum[512];
		char classfield[512];
		char family[512];
		char genus[512];
		static uint64_t counterCount = 0;
		static SystemTime st_first;
		static int flag_print = 0;
		if (counterCount == 0)
		{
			GetSystemTime(st_first);
		}
		counterCount++;
		flag_print++;
		if (flag_print > 100)
		{
			OutputMsg(rmError, "InsertCounter begin record at: %d-%d-%d %d:%d:%d", st_first.year_, st_first.mon_, st_first.mday_, st_first.hour_, st_first.min_, st_first.sec_);
			OutputMsg(rmError, "InsertCounter send: %ulld", counterCount);
			flag_print = 0;
		}
		SNPRINTFA(para, sizeof(para), "metric=Counter&%s=%s&%s=%s&%s=%s&%s=%s&%s=%s&%s=%s&%s=%s&%s=%s&%s=%s&%s=%d&%s=%s",
		          "userid", data.aid_, "user_level", UrlEncode(data.user_level_, user_level), "counter", UrlEncode(data.counter_, counter),
		          "value", UrlEncode(data.value_, value), "extra", UrlEncode(data.extra_, extra), "kingdom", UrlEncode(data.kingdom_, kingdom),
		          "phylum", UrlEncode(data.phylum_, phylum), "classfield", UrlEncode(data.classfield_, classfield),
				  "family", UrlEncode(data.family_, family), "actorid", data.actorid_, "genus", UrlEncode(data.genus_, genus));
		SendToScribe(serverId, para, final);
	}

	//if (data.flag_ & lfiText)
	{
		OutputMsg(rmError, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", data.actorid_, data.aid_, data.user_level_, data.counter_, data.value_, data.extra_,
		          data.kingdom_, data.phylum_, data.classfield_, data.family_, data.genus_);
	}
}

void LoggerServer::doSendDcApiLog(DataPacketReader& inPacket)
{
	LDcApiData data;
	inPacket >> data;

#if (defined(WIN32) || defined(WINDOWS))
	OutputMsg(rmError, data.content_);
#elif defined(DCAPI)
	int ret = 0;
	logtype lType = 4;

	std::string content = data.content_;
	ret = dclogger.write_baselog(lType, content, false);
	OutputMsg(rmError, "\n..........Write_baselog data.........\n%s\n........................\n", content.c_str());

	if (ret != 0)
	{
		OutputMsg(rmError, ".....Write_baselog data error.....ret=%d\n", ret);
		//printf("Write_baselog data[%s] falied logtype[%d] ret[%d] err[%s]\n", content, lType,ret,dclogger.get_errmsg());
	}

#endif
}

void LoggerServer::doSendDcApiLogList(DataPacketReader& inPacket)
{
	/*
	#if (defined(WIN32) || defined(WINDOWS))
	#else
		LDcApiLogTableList list;
		inPacket >> list;
		int cnt = list.count();
		if(cnt <= 0 ) return;

		std::string strlog;

		for (int i=0; i<cnt; i++)
		{
			if (i!=0)
			{
				strlog += "&";
			}
			LDcApiLogTable* logItem = list.get(0);
			strlog += logItem->key_ ;
			if (logItem->mustUrlencode_){
				char* encodeStr;
				UrlEncode(logItem->value_, encodeStr);
				strlog += encodeStr;
			}else{
				strlog += logItem->value_;
			}
		}
	#endif
	*/
}

void LoggerServer::doSendDcApiProtoLog(DataPacketReader& inPacket)
{

#if (defined(WIN32) || defined(WINDOWS))
#elif __MACH__
#elif defined(DCAPI)
	LDcApiProtoLog data;
	inPacket >> data;

	int ret = 0;
	logtype lType = 4; //4=反外挂（见：DC_API_manual_C++_V2.1.pdf 第4）
	long long int nowTime = this->getUnixTime();

	std::string strlog = "";
	char msgHead[1024] = "";
	SNPRINTFA(msgHead, sizeof(msgHead),
	          "APPV=1.0&MSGV=1.1&VER=1.3.6&APPID=100634204&OID=%s&WID=%d&UIP=%s&OKY=&SIP=%s&MTM=%lld&DOM=%d&MLV=0&AID=%d",
	          data.openId, data.serverId, data.userip, data.svrip, nowTime, data.domain, 20); //协议上报的actionID为20
	strlog += msgHead;

	char msgBody[512] = "";
	SNPRINTFA(msgBody, sizeof(msgBody), "&RID=%d&PID=%d&FID=%d&PTP=%d&RST=%d",
	          data.roleId, data.protoId, data.gameFeatrueId, data.protoType, data.protoResult);
	strlog += msgBody;

	ret = dclogger.write_baselog(lType, strlog, false);
	/*OutputMsg(rmError, "\n..........Write_baselog data.....sendDcApiProtoLog....\n%s\n........................\n",
	          strlog.c_str());
	OutputMsg(rmError, "\n=======APPV=1.0&MSGV=1.1&VER=1.3.6&APPID=100634204&OID=%s&WID=%d&UIP=%s&OKY=&SIP=%s&MTM=%lld&DOM=%d&MLV=0&AID=%d&RID=%d&PID=%d&FID=%d&PTP=%d&RST=%d\n",
	          data.openId, data.serverId, data.userip, data.svrip, nowTime, data.domain, 20, data.roleId, data.protoId, data.gameFeatrueId, data.protoType, data.protoResult);
*/
	if (ret != 0)
	{
		OutputMsg(rmError, "\n..........Write_baselog data error! .....ret=%d\n", ret);
	}

#endif

}


void LoggerServer::InsertInstall(int serverId, DataPacketReader& inPacket)
{
	LInstall data;
	inPacket >> data;

	if ((data.flag_ & lfiDB) != 0)
	{
		SystemTime st;
		GetSystemTime(st);

		//if (db_.Exec(logInstall, st.year_, st.mon_, st.mday_,
		//             data.aid_,
		//             data.source_,
		//             data.affiliate_,
		//             data.creative_,
		//             data.family_,
		//             data.genus_,
		//             data.from_uid_,
		//             data.extra_,
		//             serverId))
		//{
		//	//执行插入操作出错，要记录文本日志
		//	OutputMsg(rmError, "InsertInstall error");
		//}
		//else
		//{
		//	//释放结果集
		//	db_.ResetQuery();
		//}

		char buf[1024 * 4];
		long long int aid = (long long int)data.aid_;
		SNPRINTFA(buf, sizeof(buf) - 1, "%d-%d-%d %d:%d:%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",
			st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
			aid, data.source_, data.affiliate_, data.creative_, data.family_, data.genus_, data.from_uid_,
			data.extra_, serverId);
		char tableName[256];
		SNPRINTFA(tableName, sizeof(tableName) - 1, "log_install_%d%02d%02d", st.year_, st.mon_, st.mday_);
		WriteFile(tableName, buf, st);
	}

	if ((data.flag_ & lfiText) != 0)
	{
		OutputMsg(rmError, "%s,%s,%s,%s,%s,%s,%s,%s", data.aid_, data.source_, data.affiliate_, data.creative_, data.family_, data.genus_, data.from_uid_, data.extra_);
	}
}

void LoggerServer::InsertDau(int serverId, DataPacketReader& inPacket)
{
	LDau data;
	inPacket >> data;

	if ((data.flag_ & lfiDB) != 0)
	{
		SystemTime st;
		GetSystemTime(st);

		//if (db_.Exec(logDau, st.year_, st.mon_, st.mday_,
		//             data.aid_,
		//             data.source_,
		//             data.affiliate_,
		//             data.creative_,
		//             data.family_,
		//             data.genus_,
		//             data.ip_,
		//             data.from_uid_,
		//             data.extra_,
		//             serverId))
		//{
		//	//执行插入操作出错，要记录文本日志
		//	OutputMsg(rmError, "InsertDau error");
		//}
		//else
		//{
		//	//释放结果集
		//	db_.ResetQuery();
		//}

		char buf[1024 * 4];
		long long int aid = (long long int)data.aid_;
		SNPRINTFA(buf, sizeof(buf) - 1, "%d-%d-%d %d:%d:%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",
			st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
			aid, data.source_, data.affiliate_, data.creative_, data.family_, data.genus_, data.ip_, data.from_uid_,
			data.extra_, serverId);
		char tableName[256];
		SNPRINTFA(tableName, sizeof(tableName) - 1, "log_dau_%d%02d%02d", st.year_, st.mon_, st.mday_);
		WriteFile(tableName, buf, st);
	}

	if ((data.flag_ & lfiText) != 0)
	{
		OutputMsg(rmError, "%s,%s,%s,%s,%s,%s,%s,%s,%s", data.aid_, data.source_, data.affiliate_, data.creative_, data.family_, data.genus_, data.ip_, data.from_uid_, data.extra_);
	}
}

void LoggerServer::InsertEconomy(int serverId, DataPacketReader& inPacket, bool final)
{
	LEconomy data;
	inPacket >> data;

	char buf_tmp[256] = {0};

	if ((data.flag_ & lfiDB) != 0)
	{
		SystemTime st;
		GetSystemTime(st);

		const char* pfamily_ = data.family_;
		if (strcmp(data.currency_, "yb") == 0)
		{
			if (strlen(data.family_) != 0)
			{
				SNPRINTFA(buf_tmp, sizeof(buf_tmp) -1, "%s#%s", ((data.flag_ & lfiIsPay) != 0) ? "1" : "0", data.family_);
				pfamily_ = buf_tmp;

			}
			else
			{
				pfamily_ = ((data.flag_ & lfiIsPay) != 0) ? "1" : "0";
			}
			
		}

		char buf[1024 * 4];
		long long int aid = (long long int)data.actorid_;
		SNPRINTFA(buf, sizeof(buf) - 1, "%d-%d-%d %d:%d:%d\t%lld\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",
			st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
			aid, data.currency_, data.amount_, data.value_, data.kingdom_, data.phylum_, data.classfield_,
			pfamily_, data.genus_, data.extra_, data.extra2_, serverId);
		char tableName[256];
		SNPRINTFA(tableName, sizeof(tableName) - 1, "log_economy_%d%02d%02d", st.year_, st.mon_, st.mday_);
		WriteFile(tableName, buf, st);
	}

	if ((data.flag_ & lfiBI) != 0)
	{
		char para[1024];
		char currency[512]; // currency type
		char amount[512]; //numerical amount
		char value[512]; // numerical value
		char kingdom[512];
		char phylum[512];
		char classfield[512];
		char family[512];
		char genus[512];
		char extra[512];
		char extra2[512];
		char pfkey[512];

		//char pf[512];

		static uint64_t counterCount = 0;
		static SystemTime st_first;
		static int flag_print = 0;
		static uint64_t createRoleCount = 0;
		if (counterCount == 0)
		{
			GetSystemTime(st_first);
		}
		counterCount++;
		flag_print++;
		if (flag_print > 100)
		{
			OutputMsg(rmError, "InsertEconomy begin record at: %d-%d-%d %d:%d:%d", st_first.year_, st_first.mon_, st_first.mday_, st_first.hour_, st_first.min_, st_first.sec_);
			OutputMsg(rmError, "InsertEconomy send: %ulld", counterCount);
			flag_print = 0;
		}
		if (strcmp(data.amount_, "tx_install_report") == 0)
		{
			createRoleCount++;
			OutputMsg(rmError, "createRoleCount begin record at: %d-%d-%d %d:%d:%d", st_first.year_, st_first.mon_, st_first.mday_, st_first.hour_, st_first.min_, st_first.sec_);
			OutputMsg(rmError, "createRoleCount send: %ulld", createRoleCount);
		}
		SystemTime st;
		GetSystemTime(st);

		SNPRINTFA(para, sizeof(para), "%s=%s&data=%s|%d-%d-%d %d:%d:%d|%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d|%s",
			"counter" ,"economy",
			data.pfid_,
			st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
			data.actorid_,
			UrlEncode(data.currency_,currency),
			UrlEncode(data.amount_, amount),
			UrlEncode(data.value_, value),
			UrlEncode(data.kingdom_, kingdom),
			UrlEncode(data.phylum_, phylum),
			UrlEncode(data.classfield_, classfield),
			UrlEncode(data.family_, family),
			UrlEncode(data.genus_, genus),
			UrlEncode(data.extra_, extra),
			UrlEncode(data.extra2_, extra2),
			serverId,
			UrlEncode(data.pfkey_, pfkey)
			);
		SendToScribe(serverId, para, final);
	}

	//if ((data.flag_ & lfiText) != 0)
	//{
	//	OutputMsg(rmError, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", data.actorid_, data.aid_, data.currency_, data.amount_, data.value_, data.kingdom_, data.phylum_,
	//	          data.classfield_, data.family_, data.genus_, data.extra_, data.extra2_, data.pf_);
	//}
}

void LoggerServer::InsertChat(int serverId, DataPacketReader& inPacket, bool final)
{
	LChat data;
	inPacket >> data;

	SystemTime st;
	GetSystemTime(st);

	char name[512];
	char aname[256];
//	char toname[512];
	char content[1024  * 3];
	char ip[32];
	char pf[32];

	char buf[1024 * 4];

	SNPRINTFA(buf, sizeof(buf), "counter=chat&data=%d|%s|%d|%s|%d|%s|%d-%02d-%02d %02d:%02d:%02d|%s|%s"
		, serverId
		, UrlEncode(data.aid_, aname)
		, data.actorid_
		, UrlEncode(data.name_, name)
		, data.type_
		, UrlEncode(data.content_, content)
		, st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_
		, UrlEncode(data.ip_, ip)
		, UrlEncode(data.pf_, pf)
	);
	SendToScribe(serverId, buf, final);
}

void LoggerServer::InsertMilestone(int serverId, DataPacketReader& inPacket, bool final)
{
	LMilestone data;
	inPacket >> data;

	if ((data.flag_ & lfiDB) != 0)
	{
		SystemTime st;
		GetSystemTime(st);

		//if (db_.Exec(logMilestone, st.year_, st.mon_, st.mday_,
		//             data.actorid_,
		//             data.milestone_,
		//             data.value_,
		//             data.extra_,
		//             serverId))
		//{
		//	//执行插入操作出错，要记录文本日志
		//	OutputMsg(rmError, "InsertMilestone error");
		//}
		//else
		//{
		//	//释放结果集
		//	db_.ResetQuery();
		//}

		char buf[1024 * 4];
		long long int aid = (long long int)data.actorid_;
		SNPRINTFA(buf, sizeof(buf) - 1, "%d-%d-%d %d:%d:%d\t%lld\t%s\t%s\t%s\t%d\n",
			st.year_, st.mon_, st.mday_, st.hour_, st.min_, st.sec_,
			aid, data.milestone_, data.value_, data.extra_, serverId);
		char tableName[256];
		SNPRINTFA(tableName, sizeof(tableName) - 1, "log_milestone_%d%02d%02d", st.year_, st.mon_, st.mday_);
		WriteFile(tableName, buf, st);
	}

	if ((data.flag_ & lfiBI) != 0)
	{
		char para[1024];
		char milestone[512];
		char value[512];
		char extra[512];

		static uint64_t counterCount = 0;
		static SystemTime st_first;
		static int flag_print = 0;
		if (counterCount == 0)
		{
			GetSystemTime(st_first);
		}
		counterCount++;
		flag_print++;
		if (flag_print > 100)
		{
			OutputMsg(rmError, "InsertMilestone begin record at: %d-%d-%d %d:%d:%d", st_first.year_, st_first.mon_, st_first.mday_, st_first.hour_, st_first.min_, st_first.sec_);
			OutputMsg(rmError, "InsertMilestone send: %ulld", counterCount);
			flag_print = 0;
		}

		SNPRINTFA(para, sizeof(para), "metric=Milestone&%s=%s&%s=%s&%s=%s&%s=%s",
		          "userid", data.aid_, "milestone", UrlEncode(data.milestone_, milestone),
		          "value", UrlEncode(data.value_, value), "extra", UrlEncode(data.extra_, extra));
		SendToScribe(serverId, para, final);
	}

	if ((data.flag_ & lfiText) != 0)
	{
		OutputMsg(rmError, "%d,%s,%s,%s,%s", data.actorid_, data.aid_, data.milestone_, data.value_, data.extra_);
	}
}

void LoggerServer::InsertOnline(int serverId, DataPacketReader& inPacket)
{
}

void LoggerServer::SendToScribe(int serverId, const char* para, bool final, const char* key)
{
	if (!conf_.SrvConf.bi_) return;

	OutputMsg(rmError, "SendToScribe data:%s", para);

	static int count_per_conn = 0;
	int send_counts = 0;
	int errn_num = 0;
	int64_t s = _getTickCount();
send_erro_deal:
	if (cli_sock_start_time_ > 0 && s - cli_sock_start_time_ > TIME_PER_CONN)
	{
		OutputMsg(rmError, "close socket,time out,%d", cli_sock_);
		CloseSock();
	}

	if (cli_sock_ == SOCKET_ERROR)
	{
		cli_sock_ = socket(PF_INET, SOCK_STREAM, 0);

		if (cli_sock_ == INVALID_SOCKET)
		{
			OutputMsg(rmError, "create socket error");
			cli_sock_ = INVALID_SOCKET;
			return;
		}

#if (defined(WIN32) || defined(WINDOWS))
#else
		struct timeval timeo = { 3, 0 };

		if (setsockopt(cli_sock_, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeo, sizeof(struct timeval)) == -1)
		{
			OutputMsg(rmError, "set send timeout error:%d", errno);
		}
		if (setsockopt(cli_sock_, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeo, sizeof(struct timeval)) == -1)
		{
			OutputMsg(rmError, "set send timeout error:%d", errno);
		}
#endif

		// connect to server
		struct sockaddr_in  srv_addr;
		srv_addr.sin_family = AF_INET;

		srv_addr.sin_addr.s_addr = conf_.SrvConf.addr_;

		srv_addr.sin_port = htons((u_short)conf_.SrvConf.webPort_);

		if (::connect(cli_sock_, (sockaddr*)&srv_addr, sizeof(srv_addr)) == SOCKET_ERROR)
		{
#ifdef _MSC_VER
			errn_num = GetLastError();
#else
			errn_num = errno;
#endif
			closesocket(cli_sock_);
			cli_sock_ = INVALID_SOCKET;
			send_counts++;
			OutputMsg(rmError, "can not connect to web server!error num: %d", errn_num);
			if (send_counts < 10)
			{
				goto send_erro_deal;
			}
			else
			{
				OutputMsg(rmError, "connect too many time ");
			}
			
			return;
		}
		count_per_conn = 0;
		cli_sock_start_time_ = _getTickCount();
	}
	char fmt[] = "GET %s?appv=1.0&key=%s&%s HTTP/1.1\r\nHost:%s\r\nContent-Length:0\r\nConnection:Keep-Alive\r\n\r\n";
	char sz[1024*4];
	SNPRINTFA(sz, sizeof(sz) - 1, fmt, conf_.SrvConf.webUrl_,key, para, conf_.SrvConf.webHost_);

	int sendlen = (int)strlen(sz);
	int retval = ::send(cli_sock_, sz, sendlen, 0);

	// 防止数据丢失，发送的长度不正确也算是失败
	if (retval <= 0 || sendlen != retval)
	{
		if (retval > 0 && sendlen != retval)
		{
			// 输出一下看看这个情况有多少
			OutputMsg(rmError, "sendlen is not equal retval,%d,%d", sendlen, retval);
		}
#ifdef _MSC_VER
		errn_num = GetLastError();
#else
		errn_num = errno;
#endif
		OutputMsg(rmError, "erro num: %d, cli_sock: %d", errn_num, cli_sock_);
		closesocket(cli_sock_);
		cli_sock_ = INVALID_SOCKET;
		count_per_conn = 0;
		send_counts++;
		if (send_counts < 10)
		{
			goto send_erro_deal;
		}
		else
		{
			OutputMsg(rmError, "too many send: send log fail:%s", sz);
		}

	}

	OutputMsg(rmError, "SendToScribe data ok:%s", para);

	count_per_conn++;

	if (sock_list_.count(cli_sock_) != 0)
	{
		OutputMsg(rmError, "sock error: sock=%d", cli_sock_);
	}
	std::map<SOCKET, time_t>::iterator piter;
	time_t curr_t = time(NULL);
	static time_t last_time = time(NULL);
	//1秒钟检测一次
	if ((curr_t - last_time) > 1)
	{
		last_time = curr_t;
		for (piter = sock_list_.begin(); piter != sock_list_.end(); )
		{
			if ((curr_t - piter->second) > TIME_CLOSE_SOCK)
			{
				closesocket(piter->first);
				sock_list_.erase(piter++);
			}
			else
			{
				piter++;
			}
		}
	}

	if (count_per_conn > NUM_REQUEST_PER_CONN)
	{
		OutputMsg(rmError, "close socket:count_per_conn=%d", count_per_conn);
		CloseSock();
	}

	int64_t e = _getTickCount();
#ifdef _MSC_VER
	OutputMsg(rmError, "execute time:%I64d\r\n", e - s);
#else
	OutputMsg(rmError, "execute time:%lld\r\n", (long long int)(e - s));
#endif
}

void LoggerServer::CloseSock()
{
	char buf[20480] = { 0 };
	OutputMsg(rmError, "to use new tcp connect, but recv current tcp data now: %d", cli_sock_);
#ifdef _MSC_VER
#else
	int flags = fcntl(cli_sock_, F_GETFL, 0);
	fcntl(cli_sock_, F_SETFL, flags | O_NONBLOCK);
#endif
	::recv(cli_sock_, buf, sizeof(buf) - 1, 0);
	sock_list_.insert(std::make_pair(cli_sock_, time(NULL)));
	//closesocket(cli_sock);
	cli_sock_ = INVALID_SOCKET;
	cli_sock_start_time_ = 0;
}

void LoggerServer::ProcessTLog(int serverId, DataPacketReader& reader)
{
	char logtext[4096];
	reader.readString(logtext, ArrayCount(logtext));
	_STRNCAT_A(logtext, "\n");
	SendToTLog(logtext);
	WriteTLog(logtext);
}

bool LoggerServer::IsCanDKMLog(const char* pf)
{
	for (int i = 0; i < (int)DKMLimit.size(); ++i)
		if (strcmp(DKMLimit[i], pf) == 0)
			return true;

	return false;
}

void LoggerServer::WriteDKMLog(int serverId, DataPacketReader& inPacket)
{
	char logtext[4096];
	inPacket.readString(logtext, ArrayCount(logtext));
	_STRNCAT_A(logtext, "\n");
	
	char pf[32];
	inPacket.readString(pf, ArrayCount(pf));
	_STRNCAT_A(pf, "\n");

	if (!IsCanDKMLog(pf))
		return;

	SystemTime st;
	GetSystemTime(st);
	WriteDKMLogFile(logtext, st);
}

void LoggerServer::SendToTLog(const char* logstr)
{
	if (!logstr) return;

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock == INVALID_SOCKET)
	{
		OutputMsg(rmError, "create socket error");
		return;
	}

	struct sockaddr_in  addr;

	addr.sin_family = AF_INET;

	addr.sin_addr.s_addr = conf_.SrvConf.tlogAddr_;

	addr.sin_port = htons((u_short)conf_.SrvConf.tlogPort_);

	int ret = ::sendto(sock, logstr, (int)strlen(logstr) + 1, 0, (sockaddr*)&addr, sizeof(addr));

	if (SOCKET_ERROR == ret)
	{
		OutputMsg(rmError, "sendto tlog error:%d", WSAGetLastError());
	}

	closesocket(sock);
}

void LoggerServer::WriteTLog(const char* logstr)
{
	char logpath[256];
	SystemTime sys_t;
	GetSystemTime(sys_t);
	SNPRINTFA(logpath, sizeof(logpath), "./tlog/65535_%d%d%d_%d00.log", sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_);

	FILE* fp = fopen(logpath, "a");

	if (fp == NULL)
	{
		OutputMsg(rmError, "write tlog error");
		return;
	}

	fputs(logstr, fp);

	fclose(fp);
}

unsigned long long LoggerServer::getUnixTime()
{
#if (defined(WIN32) || defined(WINDOWS))
	uint64_t ftime = NOW_T * 1000;
	return ftime;
#elif __MACH__
	return 0;
#else
	struct timespec unixTime;
	clock_gettime(CLOCK_REALTIME, &unixTime);
	uint64_t ftime = unixTime.tv_sec * 1000 + (uint64_t)unixTime.tv_nsec / 1000 / 1000;
	return ftime;
#endif
}

void LoggerServer::WriteFile(const char* tableName, const char* msg, SystemTime& st)
{
	if (!msg) return;

	char fn[256];

	SNPRINTFA(fn, sizeof(fn) - 1, "%s%s%d%d.txt", LoggerServer::dbLogDir_,
	          tableName, st.hour_, st.min_);
	FILE* fp = fopen(fn, "a+");

	if (fp)
	{
		fputs(msg, fp);
		fclose(fp);
	}
}

void LoggerServer::WriteDKMLogFile(const char* msg, SystemTime& st)
{
	if (!msg) return;

	char fn[256];

	SNPRINTFA(fn, sizeof(fn) - 1, "%s%s%d_%02d_%02d.txt", LoggerServer::dbLogDir_,
		"dkm_", st.year_, st.mon_, st.mday_);
	FILE* fp = fopen(fn, "a+");

	if (fp)
	{
		fputs(msg, fp);
		fclose(fp);
	}
}

void LoggerServer::ImportData(const char* tableName, SystemTime& st)
{
	// 检查有没有这个文件，如果有，则导入数据库中
	char fn[256];
	SNPRINTFA(fn, sizeof(fn) - 1, "%s%s%d%02d%02d%d%d.txt", LoggerServer::dbLogDir_,
		tableName, st.year_, st.mon_, st.mday_, st.hour_, st.min_);

	if (FDOP::FileExists(fn))
	{
		OutputMsg(rmError, "start Load Data Infile:%s", fn);
#ifndef _MSC_VER
		const char* cmd = "Load Data Local InFile '%s' Into Table %s%d%02d character set utf8;";
#else
		// win下多个local就会宕！！！不知道为什么
		const char* cmd = "Load Data InFile '%s' Into Table %s%d%02d character set utf8;";
#endif

		char sql[1024];
		SNPRINTFA(sql, sizeof(sql) - 1, cmd, fn, tableName, st.year_, st.mon_);
		SQLConnection con_;
		SetDbConnection(con_);
		con_.SetInfileFlag(true);
		if (con_.Connected()) {
			if (!con_.RealQuery(sql, strlen(sql)))
			{
				con_.ResetQuery();
				OutputMsg(rmError, "start Load Data Infile ok");
			}
			else
			{
				OutputMsg(rmError, "start Load Data Infile fail");
			}
			// 删除文件
			remove(fn);
			con_.Disconnect();
		}
		//if (!table_db_.RealExec(sql, strlen(sql)))
		//{
		//	table_db_.ResetQuery();
		//	OutputMsg(rmError, "start Load Data Infile ok");
		//}
		//else
		//{
		//	OutputMsg(rmError, "start Load Data Infile fail");
		//}
		//// 删除文件
		//remove(fn);
	}
}
