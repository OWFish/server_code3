#ifndef _DB_CLIENT_H_
#define	_DB_CLIENT_H_

/***
	本类主要用于逻辑服务器连接数据服务器，并发送信息
*/

class GameServer;

class DBClient:
	public NetClient
{
public:
	DBClient(GameServer* pLogicServer);
	~DBClient();
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
	inline void SendDbServerData(int cmd, const T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}

	virtual bool Startup();
	virtual void Stop();
	virtual bool ConnectToServer();

	//等待数据发送或转储完成
	void WaitFor();

	// 回收空闲的CDataPacket类
	void FreeBackUserDataPacket(DataPacket* pack);

	// 重载下父类的函数，加些测试用的代码
	DataPacket& allocProtoPacket(uint16_t cmd);

	// 输出内存占用情况
	void printStat();

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

	int dbg_list_[0xffff];

	int								serverId_;

	time_t	select_time_out_;
};
#endif

