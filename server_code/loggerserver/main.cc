#include "stdafx.h"
//#include <dbghelp.h>
//#include "utf8_output.h"
//#include "WinService.h"
#include "utils/fdop.h"
#include <signal.h>

#define LOGGER_KRN_VERSION 0x0102

const char szExceptionDumpFile[] = ".\\LoggerServer.dmp";
void ServiceMain(int argc, char** argv);
void ServerMain();

const char tlogpath[] = "./tlog";

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

LoggerServer* srv;

void sighup_handler(int)
{
	// 重读脚本
	srv->reload_createTable_script_ = true;
	srv->reload_log_script_ = true;
	srv->create_tbl_next_t_ = 0;
	srv->import_t_ = 0;
}
const int MAX_PATH1 = 512;
char exeDir[MAX_PATH1];
int main(int argc, char** argv)
{
	atexit(Exit);

	if (!FDOP::FileExists(tlogpath))
	{
		FDOP::DeepCreateDirectory(tlogpath);
	}

#ifdef _MSC_VER
	SetMiniDumpFlag(MiniDumpWithFullMemory, szExceptionDumpFile);
	//SetMiniDumpFlag(MiniDumpWithFullMemory);
	SetUnhandledExceptionFilter(DefaultUnHandleExceptionFilter);
#else
	//Fork();
	daemon(1, 0);
#endif
	InitDefMsgOut();

#ifdef _MSC_VER
	CoInitialize(NULL);
	WorkSocket::InitSocketLib();
#else
	// 从不同路径启动程序的时候，程序要chdir切换到程序所在的目录，不然无法读取配置文件等
	const int MAX_PATH = 256;
	char startDir[MAX_PATH];
	FDOP::ExtractFileDirectory(argv[0], startDir, MAX_PATH - 1);

	printf("program is started from:%s\n", startDir);

	char p[MAX_PATH];
	printf("current dir:%s\n", getcwd(p, MAX_PATH - 1));

	//merge
	if (startDir[0] == '/')
	{
		// 从绝对路径启动的
		SNPRINTFA(exeDir, MAX_PATH - 1, "%s", startDir);
	}
	else
	{
		SNPRINTFA(exeDir, MAX_PATH - 1, "%s/%s", p, startDir);
	}
	int err = chdir(exeDir);
	printf("chdir:%s, ret:%d\n", exeDir, err);
#endif

	ServerMain();

#ifdef _MSC_VER
	WorkSocket::UnintSocketLib();
	CoUninitialize();
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

	// 创建 套接字服务类
	FileLogger flog(("../log/LoggerServer"));
	srv = new LoggerServer();

OutputMsg(rmTip, ("start server……"));
#ifdef _MSC_VER
	SetConsoleTitle(srv->conf_.SrvConf.szServiceName);
	SNPRINTFA(srv->dbLogDir_, sizeof(srv->dbLogDir_), "%s", "d:/");
#else
	SNPRINTFA(srv->dbLogDir_, sizeof(srv->dbLogDir_), "%s/", exeDir);
#endif
	

	if (srv->Startup())
	{
		OutputMsg(rmTip, ("================================================"));
		OutputMsg(rmTip, ("loggerserver start ok,kernal%d.%d"), (LOGGER_KRN_VERSION >> 8) & 0xff, LOGGER_KRN_VERSION & 0xff);
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
			char cmd[128];
			scanf("%s", cmd);

			if (strcmp(cmd, ("exit")) == 0 || strcmp(cmd, ("quit")) == 0)
			{
				break;
			}
#else
			if (!runing) break;
#endif
			Sleep(100);
		}
		srv->Stop();
	}
	else	//启动服务失败
	{
		OutputMsg(rmTip, ("start service fail！"));
	}
	SafeDelete(srv);
}

