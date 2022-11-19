#ifndef _GAME_CONN_MGR_H_
#define _GAME_CONN_MGR_H_
class GameServer;
class GameConn;
class GameClient;

using namespace container;

class GameConnMgr
	: public ServerSocket
{
public:
	enum GCMsg
	{
	    gcReg = 1,
	    gcBroadCast,
	    gcUserChange,
	};
public:
	GameConnMgr(GameServer* srv);
	~GameConnMgr();

	inline GameServer* GetGameServer()
	{
		return srv_;
	}

protected:
	//���Ǵ������Ӷ���ĺ���
	NetSession* NewSession(SOCKET nSocket, sockaddr_in* pAddrIn);
	//��������һ���Ѿ������Ŀͻ��˶���
	void DestroyConnection(NetSession* client);
	//���Ǹ��ദ��ͻ������ӵĺ���
	void ProcessClients();
	//���Ƿ����ڲ���Ϣ����ĺ���
	void OnRecvSysMsg(UINT uMsg, size_t uParam1, size_t uParam2, size_t uParam3, size_t uParam4);
	//���ǵ��ͻ������Ӵ����߳�ֹͣǰ���ú���
	void OnServerStart();
	void OnServerStop();
	//���Ǹ�������ִ�к���
	void SingleRun();
	//���Ǹ����������RUN�ĺ���
	void OnRun();

	virtual void OnClientConnect(NetSession* pClientSocke)
	{
	}
private:
	//ǿ���ͷ����пͻ�������ռ�õ��ڴ棨�������Ӷ���
	void FreeAllClient();

	bool HasGameConnect(int sid, GameConn* conn);
	void PostMsgToAllGameWorld(int cmd, void* buff, size_t size, int sid);
private:
	GameServer*					srv_;
};

#endif

