#ifndef _LIANFU_MGR_H_
#define _LIANFU_MGR_H_

using namespace container;

// 在线玩家信息
struct ActorOnlineInfo
{
	int comm_server_id_;   //玩家所在普通服服务器id
	int curr_server_id_;  //玩家现在所在服务器的服务器id

	ActorOnlineInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

typedef StaticArrayList<CommServer, MAX_LIANFU_SERVER> ServerList;

// 连服管理器
class LianfuMgr
{
public:
	static const int MAX_GUILD = 8192;
public:
	LianfuMgr();
	~LianfuMgr();

public:
	// 连服服务器收到普通服注册申请/回应
	void OnRegReq(int sid);
	void OnRegResp(int sid);
	//连服消息处理
	void OnLianfuMsg(int sid, int cmd, DataPacket& packet);
	void ProcessNetData(int cmd, DataPacketReader& packet);
public:
	// 是否处于连服状态
	bool IsLianfu();
	// 是否开启了连服功能
	bool IsOpenLianfu();
	// 关闭连服功能
	void Close(bool is_close) { is_closed_ = is_close; }
	// 设置连服sid
	void SetLianfuSid(int sid) { lianfu_sid_ = sid; }
	// 获取连服sid
	int GetLianfuSid(){ return lianfu_sid_; }
	// 获取serverlist
	ServerList& GetServerList() { return server_list_; }
	// 连服服务器 : 发送到当前服和sid对应的服(0表示全部), 普通服 : 发送到当前服和连服服务器
	void BroadCast(int channelId, int param, const char* data, size_t size, int sid = 0);
	// 世界频道广播
	void BroadCast(const char* data, size_t size, int sid = 0);

public:
	// 创建发送包
	DataPacket& AllocSendPacket(uint8_t sys_id, uint8_t cmd_id);
	// 发送到连服服务器,gpLfData类型
	void SendToLianfuServer(const void* buf, size_t size);
	// 把玩家的数据包转发给其它服的在线玩家处理
	bool TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len);
	bool TransferToActor(ActorId sActorId, ActorId tActorId, DataPacketReader* packet);
	bool TransferToActor(ActorId sActorId, ActorId tActorId, const char* data, size_t len, const void* extraData, size_t extraSize);
	// 把玩家的数据包转发给其它服务器处理,可以在消息内加入其它附加数据 
	bool TransferToServer(ActorId sActorId, int sid, const char* data, size_t len);
	bool TransferToServer(ActorId sActorId, int sid, DataPacketReader* packet);
	bool TransferToServer(ActorId sActorId, int sid, const char* data, size_t len, const void* extraData, size_t extraSize);

	// 发送数据包给某个玩家, actor : 目标玩家指针，有值就不用再查找
	bool SendToActor(ActorId actorId, const char* data, size_t len, Actor* actor = NULL);
	bool SendToActor(ActorId actorId, DataPacketReader* packet, Actor* actor = NULL);
public:
	// 在线玩家信息
	void AddOnlineUser(ActorId aid, int curr_serverid, int comm_serverid);
	bool RemoveOnlineUser(ActorId aid);
	// 获取当前在线sid
	int GetOnlineServerId(ActorId actor_id);
	// 获取玩家普通服sid
	int GetCommServerId(ActorId actor_id);
	// 是否在其他服online
	bool IsOnlineOtherServer(ActorId actor_id);
	// 设置普通服服务器列表
	void SetServerList(int* list, int cnt);
	// 获取服务器信息
	CommServer* GetServerInfo(int sid);

	/********* 游戏相关逻辑(连服操作) *********/
public:
	// 玩家登陆处理
	void OnUserLogin(Actor* actor);
	// 玩家登出处理
	void OnUserLogout(Actor* actor);
	// 批量发送玩家在线列表到目标服务器
	void SendBatchOnline(int sid);
	// 通知普通服务器踢掉玩家
	void KickUser(ActorId aid);

	/********* 游戏相关逻辑(普通服操作) *********/
public:
	// 普通服务器处理连服广播
	void HandleBroadCast(DataPacket& packet);
	// 普通服务器玩家登陆处理
	void HandleUserLogin(int sid, DataPacket& packet);
	// 普通服务器玩家登出处理
	void HandleUserLogout(int sid, DataPacket& packet);
	// 普通服接受批量在线列表处理
	void HandleBatchLogin(int sid, DataPacket& packet);
	// 普通服务器接受踢掉玩家处理
	void HandleKickUser(DataPacket& packet);
	// 普通服脚本处理
	void HandleScriptPacket(int cmd, DataPacket& packet);
private:
	// 用于存放玩家的在线信息，比如在哪个服务其上
	StaticHashTable<ActorOnlineInfo, 4096 * 4> actor_id_online_;

	bool lianfu_conn_; // 是否连接到连服服务器
	int lianfu_sid_; // 连服服务器ID

	char transfer_buf_[512 * 1024];

	char packet_buf_[512 * 1024];
	DataPacket send_packet_;

	ServerList server_list_; // 所有服的数据列表

	bool is_closed_; // 是否关闭连服功能,关闭和连服服务器的通讯
};

#endif