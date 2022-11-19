#include "StdAfx.h"
#include <signal.h>

#ifdef _MSC_VER
//#include "gtest/gtest.h"
#pragma init_seg(".CRT$XCB")
#endif

void Exit()
{
#ifdef	_MLIB_DUMP_MEMORY_LEAKS_
	assert(!_CrtDumpMemoryLeaks());
	//_CrtDumpMemoryLeaks();
#endif
}

//////////////////////////////
/* atexit 改到这里执行，原因是对于全局的static 变量，析构的顺序是先定义，后析构。这里TestStatic t 应该是整个
	程序中最先定义的static 类型的变量，所以应该会在程序最后的时候析构，然后就可以执行atexit来检查内存泄露的情况*/
class TesTStatic
{
public:
	TesTStatic()
	{
		atexit(Exit);
	}

};
static TesTStatic t;
////////////////////////////////

const char szExceptionDumpFile[] = (".\\gameworld.dmp");
bool SetupLogicServerConfig(GameServer* gameSrv);
void ServerMain();
void ServiceMain(int argc, char** argv);

GameServer* GameServer::Instance  = NULL;

void sighup_handler(int)
{
	OutputMsg(rmTip, ("log the perfermance "));
	if(GameEngine::timeStatisticMgr_) GameEngine::timeStatisticMgr_->LogTimeFile();
	MemoryCounter::getSingleton().logToFile();
#ifdef _MSC_VER
	TimeProfMgr::getSingleton().dump();
#endif
	luamemory::printState();
	DBClient* db = ServerInstance()->GetDbClient();
	if (db) db->printStat();
}

int runing = 0;
void sigterm_handler(int arg)  
{
	sighup_handler(arg);
	runing = 0;  
}

int main(int argc, char** argv)
{
	//atexit(Exit);

#ifdef _MSC_VER
	//testing::InitGoogleTest(&argc, argv);
#endif

	winitseed((unsigned int)time(NULL));
#ifdef _MSC_VER
	//初始化网络库
	int err = WorkSocket::InitSocketLib();
	if (err)
	{
		OutputError(err, ("initialize inet library failure"));
		return 0;
	}
	SetMiniDumpFlag(MiniDumpWithFullMemory, szExceptionDumpFile);
	SetUnhandledExceptionFilter(DefaultUnHandleExceptionFilter);
#else
	using namespace FDOP;
#ifdef _LINUX_DEBUG
	const char* WORKDIR = "Debug";
#else
	const char* WORKDIR = "Release";
#endif
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

	if (!FileExists("data"))
	{
		chdir(WORKDIR);
	}

	//Fork();
	daemon(1, 0);
#endif

	InitDefMsgOut();
#ifdef _MSC_VER
	TimeProfMgr::getSingleton().InitMgr();
#endif

	ServerMain();
	
	MemoryCounter::getSingleton().logToFile();

#ifdef _MSC_VER
	TimeProfMgr::getSingleton().clear();
	WorkSocket::UnintSocketLib();
#endif
	
	MemoryCounter::getSingleton().clear();
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

	FileLogger flog(("../log/gameworld"));
	GameServer::Instance  = new GameServer();

	// 统计内存
	//MEMCOUNTER(GameServer, 7);
	if (SetupLogicServerConfig(GameServer::Instance))
	{
		if (GameServer::Instance->StartServer())
		{
			OutputMsg(rmTip, ("================================================"));
			OutputMsg(rmTip, ("gameworld start ok,kernal:%d.%d"), (GAME_KN_VERSION >> 8) & 0xff, GAME_KN_VERSION & 0xff);
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
				char cmd_buf[512];
				//gets(cmd_buf);
				scanf("%s", cmd_buf);

				if (cmd_buf == NULL || *cmd_buf == 0)
				{
					Sleep(500);
					continue;
				}

				//退出命令
				if (strncmp(cmd_buf, ("\\q"), 2) == 0
				        || strncmp(cmd_buf, ("exit"), 4) == 0
				        || strncmp(cmd_buf, ("quit"), 4) == 0)
				{
					sighup_handler(0);
					OutputMsg(rmTip, ("stop gameworld..."));
					break;
				}
				else if (strncmp(cmd_buf, "spf", 3) == 0)
				{
					sighup_handler(0);
				}
				else if (strncmp(cmd_buf, "gc", 2) == 0)
				{
					luamemory::GC();
				}
				else if (strncmp(cmd_buf, "dmp", 3) == 0)
				{
					DebugBreak();
				}
				else if (strncmp(cmd_buf, "asi", 3) == 0)
				{
					const char* param = cmd_buf + 3;

					while (*param == ' ') param++;

					if (param)
					{
						int interval = atoi(param);

						if (interval > 0) Actor::save_db_interval_ = interval * 1000;
					}
				}
				else if (strncmp(cmd_buf, "pdb", 3) == 0)
				{
					ServerInstance()->printAllDbClient();
				}
				else if (strncmp(cmd_buf, "rsf", 3) == 0)
				{
					GameInterMsg msg;
					msg.msg_id_ = SSM_RELOAD_GLOBAL_NPC_MAIN;
					GetGameEngine()->PostMsg(msg);
				}
				else if (strncmp(cmd_buf, "test", 4) == 0)
				{
					GetGameEngine()->RunAllTests();
				}
#else
				if (!runing) break;
#endif
				Sleep(10);
			}

			GameServer::Instance->StopServer();
		}
		else
		{
			OutputMsg(rmError, "Press Any Key To Quit...\n");
			getc(stdin);
		}
	}

	delete GameServer::Instance;
	OutputMsg(rmError, "delete GameServer::Instance");
}

bool SetupLogicServerConfig(GameServer* gameSrv)
{
	GameServerConfig config;
	return config.loadServerConfig(gameSrv);
}

