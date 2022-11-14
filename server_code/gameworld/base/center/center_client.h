#ifndef _CENTER_CLIENT_H_
#define	_CENTER_CLIENT_H_

/***
	本类主要用于逻辑服务器连接中心服务器，并发送信息
*/

class GameServer;

class CenterClient:
	public NetClient
{
public:
	CenterClient(GameServer* srv);
	~CenterClient();
public:
	/*
	* Comments: 向服务器发送简单的数据
		如果是复杂数据使用 allocProtoPacket，然后写入数据，再flushProtoPacket
	* Param int nCmd: 命令码,如dcLoadQuest
	* Param T data: 数据，可以是任何类型的
	* @Return void:
	*/
	template<class T>
	inline void SendServerData(int cmd, const T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}


	// 回收空闲的CDataPacket类
	void FreeBackUserDataPacket(DataPacket* pack);

	void SetServerId(int sid)
	{
		serverId_ = sid;
	}
	int GetServerId()
	{
		return serverId_;
	}
protected:
	// 以下是实现基类的虚函数
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	virtual int GetLocalServerType();

	/* ★查询本地服务器的名称，以便正确的发送注册数据 */
	virtual const char* GetLocalServerName();
	/* ★查询本地服务器ID，以便正确的发送注册数据，默认的返回值是0 */
	virtual int GetLocalServerIndex();

	GameServer* game_server_;

	//提供向最外层逻辑通知连接建立的事件
	virtual void OnConnected();
private:
	// 分配一个包，这个包传递给游戏主逻辑处理
	DataPacket* AllocPostPacket();

private:
	QueueList<DataPacket*>			free_;	//用来存放空闲的数据包
	Mutex							lock_;
	int								serverId_;
};
#endif

