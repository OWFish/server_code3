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

	//���ظ���ĺ���
	virtual NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);

	void RemoveClientId(int sid);
	GameSession* GetGameSession(int sid);
	void AddNewGameSession(int sid, GameSession* gs);
	void SendToGameworld(int src, const char* buf, int size);

	void SendToGameworld(GameSession* gs, int src, const char* buf, int size);

	void HandleActorOnline(int src, const char* buf, int size);

	void SendToActorServer(int src, const char* buf, int size);
public://���캯������������
	CenterServer(void);
	~CenterServer(void);

protected:
	//�������ڽ�������������������Ӻ����Ӵ����߳�ǰ����
	virtual bool DoStartup();
	//�ṩ����������и��ǵ�ֹͣ����ĺ���
	//��������ֹͣ���������Լ����������̲߳��رռ����׽��ֺ����
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


