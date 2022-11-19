#ifndef _GAME_CLIENT_H_
#define	_GAME_CLIENT_H_

/***
	本类主要用于连接其他gameworld，并发送信息，主要用与跨服站
*/

class GameServer;

class GameClient:
	public NetClient
{
public:
	GameClient(GameServer* game);
	~GameClient();
public:
	// 以下函数用于逻辑服务器向数据服务器发送查询信息

	/*
	* Comments: 向db服务器发送简单的数据
		如果是复杂数据使用 allocProtoPacket，然后写入数据，再flushProtoPacket
	* Param int nCmd: 命令码,如dcLoadQuest
	* Param T data: 数据，可以是任何类型的
	* @Return void:
	*/
	template<class T>
	inline void SendDbServerData(int cmd, T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}

	// 回收空闲的CDataPacket类
	void FreeBackUserDataPacket(DataPacket* pack);

	// 重载下父类的函数，加些测试用的代码
	DataPacket& allocProtoPacket(uint16_t cmd);

	// 输出内存占用情况
	void printStat();

	void SetTargetSid(int sid)
	{
		target_sid_ = sid;
	}

	bool IsLianfuClient();

	int GetTargetSid()
	{
		return target_sid_;
	}
	//void SetGateMgr(GameGateMgr* mgr)
	//{
	//	gate_mgr_ = mgr;
	//}
protected:
	// 以下是实现基类的虚函数
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	virtual int GetLocalServerType();

	/* ★查询本地服务器的名称，以便正确的发送注册数据 */
	virtual const char* GetLocalServerName();
	/* ★查询本地服务器ID，以便正确的发送注册数据，默认的返回值是0 */
	virtual int GetLocalServerIndex();

	//提供向最外层逻辑通知连接建立的事件
	virtual void OnConnected();
	virtual void OnDisconnected();
private:
	// 分配一个包，这个包传递给游戏主逻辑处理
	DataPacket* AllocPostPacket();
	void OnGatewayInfo(DataPacketReader& reader);
	void OnRegResp(DataPacketReader& reader);
	void OnUserLogin(DataPacketReader& reader);
	void OnUserExit(DataPacketReader& reader);
	void OnBatchLogin(DataPacketReader& reader);
	void OnCloseUser(DataPacketReader& reader);
	void OnKeyReq(DataPacketReader& reader);
	void OnKeyResp(DataPacketReader& reader);
	void OnCommonMsg(DataPacketReader& reader);
	void OnTtDataToGame(DataPacketReader& reader, uint16_t cmd);
private:
	QueueList<DataPacket*>			free_;	//用来存放空闲的数据包
	Mutex							lock_;
	int								target_sid_;	// 连接的对方的gameworld的serverid
	int								is_battle_;		// 对方是否战斗服
	GameServer* game_server_;
	//GameGateMgr*			    gate_mgr_;
};
#endif

