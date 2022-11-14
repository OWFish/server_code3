#ifndef	_LOGGER_CLIENT_SOCKET_H_
#define	_LOGGER_CLIENT_SOCKET_H_

#if (defined(WIN32) || defined(WINDOWS))
#else
#include "dcapi_cpp.h"
using namespace DataCollector;
#endif

class NetSession;
class LoggerServer;

class LoggerSession:
	public NetSession
{
public:
	LoggerSession(void);
	LoggerSession(LoggerServer* pSrv, SOCKET nSocket, sockaddr_in* pClientAddr);
	~LoggerSession(void);
	virtual void OnRun();
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);
	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regData);
	void Disconnected();
	int GetWatchId()
	{
		return watch_id_;
	}

private:
	LoggerServer*		srv_;
	SQLConnection*		db_;
	int						watch_id_;
	time_t					report_t_;
};

#endif

