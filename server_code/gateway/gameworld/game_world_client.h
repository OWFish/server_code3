#pragma once
struct Channel {
	int type;// == 0 ? ccAddUser : ccDelUser;
	int channelId;
	int para;
	int index_;
};

class GameWorldClient :
	public NetClient
{
public:
	GameWorldClient(GateServer* serv, GameClientMgr* gcmgr, const char* name);
	~GameWorldClient();
	// 回收空闲的CDataPacket类
	void FreeBackUserDataPacket(DataPacket* pack);
protected:
	// 以下是实现基类的虚函数
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);
	void OnChannelMsg(char* buf, int size);
	virtual int GetLocalServerType();
	/* 查询本地服务器的名称，以便正确的发送注册数据 */
	virtual const char* GetLocalServerName();
	virtual void OnDisconnected();
private:
	// 分配一个包，这个包传递给游戏主逻辑处理
	DataPacket* AllocPostPacket();
private:
	QueueList<DataPacket*>			free_;	//用来存放空闲的数据包
	Mutex							lock_;
	GateServer* serv_;
	GameClientMgr* gcmgr_;
};

