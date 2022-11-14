#include "StdAfx.h"
#include "utils/fdop.h"
#include <signal.h>

using namespace FDOP;

//定义转储文件名称
const char szExceptionDumpFile[] = ("./DBServer.dmp");
bool SetDbConfig(DBServer* db_srv);
void ServerMain();

void Exit()
{
#ifdef	_MLIB_DUMP_MEMORY_LEAKS_
	assert(!_CrtDumpMemoryLeaks());
#endif
}

int runing = 0;
void sigterm_handler(int)  
{
	runing = 0;  
} 

DBServer* db_srv;

void sighup_handler(int)
{
	// 重读脚本
	//db_srv->GetClientMgr()->PostMsg(DBSessionMgr::rmReloadScript, 0, 0, 0, 0);

	MemoryCounter::getSingleton().logToFile();
}

int main(int argc, char** argv)
{
	atexit(Exit);

#ifdef _MSC_VER
	SetMiniDumpFlag(MiniDumpWithFullMemory, szExceptionDumpFile);
	//SetMiniDumpFlag(MiniDumpWithFullMemory);
	SetUnhandledExceptionFilter(DefaultUnHandleExceptionFilter);

	int err = WorkSocket::InitSocketLib();

	if (err)
	{
		OutputError(err, ("初始化网络库失败"));
		return 0;
	}
	CoInitialize(NULL);
#else
	// 从不同路径启动程序的时候，程序要chdir切换到程序所在的目录，不然无法读取配置文件等
	const int MAX_PATH = 256;
	char startDir[MAX_PATH];
	ExtractFileDirectory(argv[0], startDir, MAX_PATH - 1);

	printf("program is started from:%s\n", startDir);

	char p[MAX_PATH];
	printf("current dir:%s\n", getcwd(p, MAX_PATH - 1));

	//merge
	char dir[MAX_PATH];
	if (startDir[0] == '/')
	{
		// 从绝对路径启动的
		SNPRINTFA(dir, MAX_PATH - 1, "%s", startDir);
	}
	else
	{
		SNPRINTFA(dir, MAX_PATH - 1, "%s/%s", p, startDir);
	}
	int err = chdir(dir);
	printf("chdir:%s, ret:%d\n", dir, err);

	//Fork();
	daemon(1, 0);
#endif

	InitDefMsgOut();
	
	ServerMain();

#ifdef _MSC_VER
	CoUninitialize();
	WorkSocket::UnintSocketLib();
#endif
	UninitDefMsgOut();
	return 0;
}


void ServerMain()
{
	char logpath[256] = "../log/";

	if (!FDOP::FileExists(logpath))
	{
		FDOP::DeepCreateDirectory(logpath);
	}

	FileLogger flog(("../log/DBServer"));
	db_srv = new DBServer();

	if (!SetDbConfig(db_srv))
	{
		OutputMsg(rmError, ("load config fail, server stoped！"));
	}
	else if (db_srv->Startup())
	{
		//设置窗口标题
#ifdef _MSC_VER
		TimeProfMgr::getSingleton().InitMgr();
		SetConsoleTitle(db_srv->GetServerName());
#endif
		OutputMsg(rmTip, ("================================================"));
		OutputMsg(rmTip, ("dbserver start ok,kernal%d.%d"), (DB_KRN_VERSION >> 8) & 0xff, DB_KRN_VERSION & 0xff);
		OutputMsg(rmTip, ("quit:stop server and exit"));
		OutputMsg(rmTip, ("================================================"));
#ifndef _MSC_VER		
		runing = 1;
		signal(SIGTERM, sigterm_handler);  
		signal(SIGPIPE, SIG_IGN); 
		signal(SIGHUP, sighup_handler);
#endif

		while (true)
		{
#ifdef _MSC_VER
			char sCmdBuf[512];
			//gets(cmd_buf);
			scanf("%s", sCmdBuf);

			if (strncmp(sCmdBuf, ("\\q"), 2) == 0
			        || strncmp(sCmdBuf, ("exit"), 4) == 0
			        || strncmp(sCmdBuf, ("quit"), 4) == 0)
			{
				OutputMsg(rmTip, ("exiting..."));
				break;
			}
			else if (strncmp(sCmdBuf, ("spf"), 3) == 0)
			{
				TimeProfMgr::getSingleton().dump();
			}
			else if (strncmp(sCmdBuf, "reload", 6) == 0)
			{
				sighup_handler(0);
			}
			else if (strncmp(sCmdBuf, "refreshRank", 10) == 0)
			{
				if (db_srv)
				{
					DBSessionMgr* mgr = db_srv->GetClientMgr();
					if (mgr)
					{
						mgr->SetRankRefresh(true);
					}
				}
			}
#else
			if (!runing) break;
#endif
			Sleep(10);
		}

		db_srv->Shutdown();
	}
	else
	{
		OutputMsg(rmError, "start dbserver fail!");
	}
	delete db_srv;
}


bool SetDbConfig(DBServer* db_srv)
{
	DbConfig conf;

	if (!conf.ReadConfig())
		return false;

	db_srv->SetSrvName(conf.srv_name_);
	db_srv->SetAddr(conf.addr_, conf.port_);
	db_srv->SetDbConf(conf.db_host_, conf.db_port_, conf.db_name_, conf.db_user_, conf.db_pw_);

	db_srv->getTables()->Init();

	return true;
}

