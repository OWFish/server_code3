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
	//覆盖创建连接对象的函数
	NetSession* NewSession(SOCKET nSocket, sockaddr_in* pAddrIn);
	//覆盖销毁一个已经建立的客户端对象
	void DestroyConnection(NetSession* client);
	//覆盖父类处理客户端连接的函数
	void ProcessClients();
	//覆盖分派内部消息处理的函数
	void OnRecvSysMsg(UINT uMsg, size_t uParam1, size_t uParam2, size_t uParam3, size_t uParam4);
	//覆盖当客户端连接处理线程停止前调用函数
	void OnServerStart();
	void OnServerStop();
	//覆盖父类例行执行函数
	void SingleRun();
	//覆盖父类调用例行RUN的函数
	void OnRun();

	virtual void OnClientConnect(NetSession* pClientSocke)
	{
	}
private:
	//强制释放所有客户端连接占用的内存（销毁连接对象）
	void FreeAllClient();

	bool HasGameConnect(int sid, GameConn* conn);
	void PostMsgToAllGameWorld(int cmd, void* buff, size_t size, int sid);
private:
	GameServer*					srv_;
};

#endif

