#include "StdAfx.h"
#include <signal.h>

void Exit() {
#ifdef	_MLIB_DUMP_MEMORY_LEAKS_
	_CrtDumpMemoryLeaks();
#endif
}
#ifdef _MSC_VER
const char szExceptionDumpFile[] = ".\\wsgate.dmp";
#endif
bool SetupLogicServerConfig(GateServer* gate_srv);
void ServerMain();

GateServer* GateServer::Instance = NULL;

void sighup_handler(int) {
	MSG_TIP("log the perfermance ");
	MemoryCounter::getSingleton().logToFile();
}

bool runing = false;
void sigterm_handler(int arg) {
	sighup_handler(arg);
	runing = false;
}

int main(int argc, char** argv) {
	winitseed((unsigned int)time(NULL));
#ifdef _MSC_VER
	//初始化网络库
	int err = WorkSocket::InitSocketLib();
	if (err) {
		MSG_ERR("initialize inet library failure");
		return 0;
	}
	SetMiniDumpFlag(MiniDumpWithFullMemory, szExceptionDumpFile);
	SetUnhandledExceptionFilter(DefaultUnHandleExceptionFilter);
#else
	//改为正确的启动目录
	const int MAX_PATH = 256;
	char startDir[MAX_PATH];
	FDOP::ExtractFileDirectory(argv[0], startDir, MAX_PATH - 1);
	//merge
	char dir[MAX_PATH];
	if (startDir[0] == '/')	{
		SNPRINTFA(dir, MAX_PATH - 1, "%s", startDir);
	} else {
		char p[MAX_PATH];
		getcwd(p, MAX_PATH - 1);
		SNPRINTFA(dir, MAX_PATH - 1, "%s/%s", p, startDir);
	}
	int err = chdir(dir);
	printf("chdir:%s, ret:%d\n", dir, err);

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


void ServerMain() {
	//设置窗口标题
#ifdef _MSC_VER
	SetConsoleTitle("gateway");
#endif
	char logpath[256] = "../log/";

	if (!FDOP::FileExists(logpath)) {
		FDOP::DeepCreateDirectory(logpath);
	}
	FileLogger flog(("../log/gateway"));

	GateServer::Instance = new GateServer();

	if (SetupLogicServerConfig(GateServer::Instance))	{
		if (GateServer::Instance->StartServer()) {
			MSG_TIP("===========================");
			MSG_TIP("gateway start ok");
			MSG_TIP("quit:stop server and exit");
			MSG_TIP("===========================");
#ifndef _MSC_VER		
			runing = true;
			signal(SIGTERM, sigterm_handler);
			signal(SIGPIPE, SIG_IGN);
			signal(SIGHUP, sighup_handler);
#endif
			while (true) {
#ifdef _MSC_VER
				char cmd_buf[512];
				//gets(cmd_buf);
				scanf("%s", cmd_buf);

				if (cmd_buf == NULL || *cmd_buf == 0) {
					Sleep(500);
					continue;
				}
				if (strncmp(cmd_buf, ("\\q"), 2) == 0
					|| strncmp(cmd_buf, ("exit"), 4) == 0
					|| strncmp(cmd_buf, ("quit"), 4) == 0) {
					sighup_handler(0);
					MSG_TIP("stop gate...");
					break;
				} else if (strncmp(cmd_buf, "spf", 3) == 0) {
					sighup_handler(0);
				} else if (strncmp(cmd_buf, "dmp", 3) == 0) {
					DebugBreak();
				}
#else
				if (!runing) break;
#endif
				Sleep(10);
			}

			GateServer::Instance->StopServer();
		} else {
			MSG_ERR("Press Any Key To Exit...\n");
			getc(stdin);
		}
	}

	delete GateServer::Instance;
	MSG_LOG("delete GateServer::Instance");
}

bool SetupLogicServerConfig(GateServer* gate_srv) {
	WsGateConfig config;
	return config.loadServerConfig(gate_srv);
}

