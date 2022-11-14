#ifndef _LIANFU_MGR_H_
#define _LIANFU_MGR_H_

using namespace container;

// ���������Ϣ
struct ActorOnlineInfo
{
	int comm_server_id_;   //���������ͨ��������id
	int curr_server_id_;  //����������ڷ������ķ�����id

	ActorOnlineInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

typedef StaticArrayList<CommServer, MAX_LIANFU_SERVER> ServerList;

// ����������
class LianfuMgr
{
public:
	static const int MAX_GUILD = 8192;
public:
	LianfuMgr();
	~LianfuMgr();

public:
	// �����������յ���ͨ��ע������/��Ӧ
	void OnRegReq(int sid);
	void OnRegResp(int sid);
	//������Ϣ����
	void OnLianfuMsg(int sid, int cmd, DataPacket& packet);
	void ProcessNetData(int cmd, DataPacketReader& packet);
public:
	// �Ƿ�������״̬
	bool IsLianfu();
	// �Ƿ�������������
	bool IsOpenLianfu();
	// �ر���������
	void Close(bool is_close) { is_closed_ = is_close; }
	// ��������sid
	void SetLianfuSid(int sid) { lianfu_sid_ = sid; }
	// ��ȡ����sid
	int GetLianfuSid(){ return lianfu_sid_; }
	// ��ȡserverlist
	ServerList& GetServerList() { return server_list_; }
	// ���������� : ���͵���ǰ����sid��Ӧ�ķ�(0��ʾȫ��), ��ͨ�� : ���͵���ǰ��������������
	void BroadCast(int channelId, int param, const char* data, size_t size, int sid = 0);
	// ����Ƶ���㲥
	void BroadCast(const char* data, size_t size, int sid = 0);

public:
	// �������Ͱ�
	DataPacket& AllocSendPacket(uint8_t sys_id, uint8_t cmd_id);
	// ���͵�����������,gpLfData����
	void SendToLianfuServer(const void* buf, size_t size);
	// ����ҵ����ݰ�ת������������������Ҵ���
	bool TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len);
	bool TransferToActor(ActorId sActorId, ActorId tActorId, DataPacketReader* packet);
	bool TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len, const void* extraData, size_t extraSize);
	// ����ҵ����ݰ�ת������������������,��������Ϣ�ڼ��������������� 
	bool TransferToServer(ActorId sActorId, int sid, const char* data, size_t len);
	bool TransferToServer(ActorId sActorId, int sid, DataPacketReader* packet);
	bool TransferToServer(ActorId sActorId, int sid, const char* data, size_t len, const void* extraData, size_t extraSize);

	// �������ݰ���ĳ�����, actor : Ŀ�����ָ�룬��ֵ�Ͳ����ٲ���
	bool SendToActor(ActorId actorId, const char* data, size_t len, Actor* actor = NULL);
	bool SendToActor(ActorId actorId, DataPacketReader* packet, Actor* actor = NULL);
public:
	// ���������Ϣ
	void AddOnlineUser(ActorId aid, int curr_serverid, int comm_serverid);
	bool RemoveOnlineUser(ActorId aid);
	// ��ȡ��ǰ����sid
	int GetOnlineServerId(ActorId actor_id);
	// ��ȡ�����ͨ��sid
	int GetCommServerId(ActorId actor_id);
	// �Ƿ���������online
	bool IsOnlineOtherServer(ActorId actor_id);
	// ������ͨ���������б�
	void SetServerList(int* list, int cnt);
	// ��ȡ��������Ϣ
	CommServer* GetServerInfo(int sid);

	/********* ��Ϸ����߼�(��������) *********/
public:
	// ��ҵ�½����
	void OnUserLogin(Actor* actor);
	// ��ҵǳ�����
	void OnUserLogout(Actor* actor);
	// ����������������б�Ŀ�������
	void SendBatchOnline(int sid);
	// ֪ͨ��ͨ�������ߵ����
	void KickUser(ActorId aid);

	/********* ��Ϸ����߼�(��ͨ������) *********/
public:
	// ��ͨ���������������㲥
	void HandleBroadCast(DataPacket& packet);
	// ��ͨ��������ҵ�½����
	void HandleUserLogin(int sid, DataPacket& packet);
	// ��ͨ��������ҵǳ�����
	void HandleUserLogout(int sid, DataPacket& packet);
	// ��ͨ���������������б���
	void HandleBatchLogin(int sid, DataPacket& packet);
	// ��ͨ�����������ߵ���Ҵ���
	void HandleKickUser(DataPacket& packet);
	// ��ͨ���ű�����
	void HandleScriptPacket(int cmd, DataPacket& packet);
private:
	// ���ڴ����ҵ�������Ϣ���������ĸ���������
	StaticHashTable<ActorOnlineInfo, 4096 * 4> actor_id_online_;

	bool lianfu_conn_; // �Ƿ����ӵ�����������
	int lianfu_sid_; // ����������ID

	char transfer_buf_[512 * 1024];

	char packet_buf_[512 * 1024];
	DataPacket send_packet_;

	ServerList server_list_; // ���з��������б�

	bool is_closed_; // �Ƿ�ر���������,�رպ�������������ͨѶ
};

#endif