#ifndef _DB_CLIENT_MGR_H_
#define _DB_CLIENT_MGR_H_


/*
* �������е��̣߳����ڷ���Ϸ���߳�ִ�еĲ���
* �������ÿ��web�ӿڡ�
* �����µĹ��ܣ�ֻ��Ҫ�����̵߳�ִ�к������Լ�ִ����ɺ�Ļص�����
*/

using namespace thread;
using namespace container;

class DBClientMgr: public thread::BaseThread
{
public:
	typedef BaseThread Inherited;
	enum 
	{
		dbmAdd = 1,
	};
public:
	DBClientMgr();

	virtual ~DBClientMgr();

	void PostMsg(GameInterMsg& msg)
	{
		inter_msg_.append(msg);
	}
protected:
	void OnRoutine();
	//�����߼�����
	int Run();
	void OnStart();
	void OnStop();

	int ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);
private:
	QueueList<GameInterMsg>	inter_msg_;		//�ڲ���Ϣ�б�
	Mutex				inter_msg_lock_;		//�ڲ���Ϣ�б���
	Vector<DBClient*> db_list_;
};

#endif



