#pragma once

#include <map>
#include <set>

typedef union GateInterMsgData {
	struct {
		uint32_t b_channel_;
		uint32_t b_para_;
		DataPacket* dp_;
	};
	struct {
		uint32_t index_;
		DataPacket* packet_;
	};
	struct {
		uint32_t idx_;
		uint32_t para_;
		uint32_t channel_;
	};
	struct {
		SOCKET fd_;
	};
} tagGateInterMsgData;

typedef struct GateInterMsg
{
	int	msg_id_;
	GateInterMsgData data_;
} tagGateInterMsg;

class GameWorldClient;
class BaseEvent;
class SocketSrv;
class ClientObjMgr;

enum {
	gcAddClient = 1,	//增加一个新的客户端连接
	gcGWData = 2, //游戏服给客户端发消息
	gcGWClose = 3,	//游戏服主动关闭客户端
	gcChBro = 4,//频道广播消息
	gcChAdd = 5,//频道信息增加
	gcChDel = 6,//频道信息删除
	gcGWDisconn = 7,//游戏服断开连接
};

class GameClientMgr : public SocketSrv {
public:
	typedef SocketSrv Inherited;
	GameClientMgr(const char *name, GateServer *srv);
	~GameClientMgr();

	void SetMaxSession(int max_session);

	bool Startup();
	void InitGameWorldClient(const char *ip, int port);
	GameWorldClient* GetGameWorldClient(void) { return gw_cli_; }
	virtual bool onConnect(SOCKET nSocket, sockaddr_in* pAddrIn);
	
	//单次逻辑处理
	virtual int Run();
	virtual void OnStart();
	virtual void OnStop();
	virtual void Stop();

	void PostMsg(GateInterMsg& msg) {
		inner_msg_list_.append(msg);
	}

	void OnRecvSysMsg(GateInterMsg& msg);

	//select模式使用
	void ProssClient(void);
	//epoll模式使用
	void HandleReadEvent(SOCKET fd, Client* cli);
	void HandleWriteEvent(SOCKET fd, Client* cli);
	//断开所有客户端连接
	void CloseAllClient();
	void HaveData(Client* cli);
	
	void CloseClient(Client *cli);

protected:

	GateServer *srv_;
	GameWorldClient *gw_cli_;
	ClientObjMgr *cli_obj_mgr_;
	std::map<uint64_t, std::set<int> > channel_indexs_map_;

	QueueList<GateInterMsg> inner_msg_list_;//内部消息列表
	Mutex				 inner_msg_lock_;//内部消息列表锁
	BaseEvent			*event_;//事件处理
};
