#ifndef _GAME_GATE_MGR_H_
#define _GAME_GATE_MGR_H_

class GameServer;
using namespace container;

class GameGateMgr :
	public GateManager
{
	friend class GameEngine;
public:
	enum InterMsg
	{
	    imCloseUser = 1,
	};
public:
	typedef GateManager Inherited;
	struct DataList
	{
		QueueList<DataPacket*>	list_;
		Mutex lock_;
	};

	struct GateList
	{
		GameGate gate_;
		DataList list_[GameGate::ThreadMax];
	};

public:
	GameGateMgr(GameServer* game_srv);
	virtual ~GameGateMgr();

	virtual void Initialize();
	virtual void Uninitialize();

	bool Startup();
	void Stop();
public:
	void PostUserDataList(const int gate_idx, Vector<DataPacket*>& data_list, int thread_id);
	void CollectGameData();
	int CollectActorMgrData();

	void GC();
protected:
	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);

	// 关闭指定的账户
	void CloseUserByAccount(int accountID);
private:
	GameServer*			game_srv_;
protected:
	GateList			gates_[MaxGateCount];
};

#endif

