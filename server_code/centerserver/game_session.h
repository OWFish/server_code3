#ifndef	_LOGGER_CLIENT_SOCKET_H_
#define	_LOGGER_CLIENT_SOCKET_H_

class NetSession;
class CenterServer;

class GameSession:
	public NetSession
{
public:
	GameSession(void);
	GameSession(CenterServer* pSrv, SOCKET nSocket, sockaddr_in* pClientAddr);
	~GameSession(void);
	virtual void OnRun();
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);
	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regData);
	void Disconnected();

private:
	CenterServer* srv_;
};

#endif

