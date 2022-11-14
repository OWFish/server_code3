#ifndef _CENTER_SERVER_H_
#define _CENTER_SERVER_H_

#include "InterServerComm.h"

using namespace container;
using namespace InterSrvComm::CenterProto;

class ServerSocket;
class SrvConfig;

class CenterServer:
	public ServerSocket
{
public:
	typedef ServerSocket Inherited;

	//重载父类的函数
	virtual NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);

	void RemoveClientId(int sid);
	GameSession* GetGameSession(int sid);
	void AddNewGameSession(int sid, GameSession* gs);
	void SendToGameworld(int src, const char* buf, int size);

	void SendToGameworld(GameSession* gs, int src, const char* buf, int size);

	void HandleActorOnline(int src, const char* buf, int size);

	void SendToActorServer(int src, const char* buf, int size);
public://构造函数和析构函数
	CenterServer(void);
	~CenterServer(void);

protected:
	//函数将在进入监听后，启动接受连接和连接处理线程前调用
	virtual bool DoStartup();
	//提供用于族类进行覆盖的停止服务的函数
	//函数将在停止接受连接以及处理数据线程并关闭监听套接字后调用
	virtual void DoStop();

#ifdef _MSC_VER
	static void STDCALL CenterThread(CenterServer* ptr);
#else
	static void* CenterThread(void* ptr);
#endif
public:
	SrvConfig		conf_;
protected:
	bool			pt_runing_;
	bool			pt_free_;
	BaseAllocator	alloc_;
#ifdef _MSC_VER
	HANDLE			pTThread_;
#else
	pthread_t		pTThread_;
#endif

	StaticHashTable<GameSession*, 1024> all_client_list_;
	BinaryList<ActorOnline> actor_online_list_;
};



#endif


