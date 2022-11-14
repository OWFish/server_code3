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
	gcAddClient = 1,	//����һ���µĿͻ�������
	gcGWData = 2, //��Ϸ�����ͻ��˷���Ϣ
	gcGWClose = 3,	//��Ϸ�������رտͻ���
	gcChBro = 4,//Ƶ���㲥��Ϣ
	gcChAdd = 5,//Ƶ����Ϣ����
	gcChDel = 6,//Ƶ����Ϣɾ��
	gcGWDisconn = 7,//��Ϸ���Ͽ�����
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
	
	//�����߼�����
	virtual int Run();
	virtual void OnStart();
	virtual void OnStop();
	virtual void Stop();

	void PostMsg(GateInterMsg& msg) {
		inner_msg_list_.append(msg);
	}

	void OnRecvSysMsg(GateInterMsg& msg);

	//selectģʽʹ��
	void ProssClient(void);
	//epollģʽʹ��
	void HandleReadEvent(SOCKET fd, Client* cli);
	void HandleWriteEvent(SOCKET fd, Client* cli);
	//�Ͽ����пͻ�������
	void CloseAllClient();
	void HaveData(Client* cli);
	
	void CloseClient(Client *cli);

protected:

	GateServer *srv_;
	GameWorldClient *gw_cli_;
	ClientObjMgr *cli_obj_mgr_;
	std::map<uint64_t, std::set<int> > channel_indexs_map_;

	QueueList<GateInterMsg> inner_msg_list_;//�ڲ���Ϣ�б�
	Mutex				 inner_msg_lock_;//�ڲ���Ϣ�б���
	BaseEvent			*event_;//�¼�����
};
