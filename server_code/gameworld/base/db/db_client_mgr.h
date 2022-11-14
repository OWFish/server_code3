#ifndef _DB_CLIENT_MGR_H_
#define _DB_CLIENT_MGR_H_


/*
* 单独运行的线程，用于非游戏主线程执行的操作
* 比如访问每个web接口。
* 增加新的功能，只需要定义线程的执行函数，以及执行完成后的回调函数
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
	//单次逻辑处理
	int Run();
	void OnStart();
	void OnStop();

	int ProcessSysMsg();
	void OnRecvSysMsg(GameInterMsg& msg);
private:
	QueueList<GameInterMsg>	inter_msg_;		//内部消息列表
	Mutex				inter_msg_lock_;		//内部消息列表锁
	Vector<DBClient*> db_list_;
};

#endif



