#ifndef _WATCH_THREAD_H_
#define _WATCH_THREAD_H_

using namespace tick64;
using namespace container;
using namespace lock;

typedef void (*BlockFunc)(void*);

class WatchThread
{
	// 可以考虑加个超时处理，外部传个函数指针进来
	struct WatchData
	{
		int id_;
		int64_t last_t_;
		int timeout_;
		BlockFunc func_;
		void* params_;
		WatchData() : id_(0), last_t_(0), timeout_(0), func_(NULL), params_(NULL)
		{

		}
	};
	enum WatchMsg 
	{
		wmAddWatch,
		wmReport,
		wmRemove,
	};

	typedef struct
	{
		unsigned int uMsg;	//消息号
		size_t	uParam1;//消息参数1
		size_t	uParam2;//消息参数2
		BlockFunc func;
		void* params;
	}InterMsg;
public:
	WatchThread();
	virtual ~WatchThread();

	bool Startup();
	void Stop();
#ifdef _MSC_VER
	unsigned long GetThreadId()
#else
	pthread_t GetThreadId()
#endif
	{
		return thread_id_;
	}

	void AddWatch(int id, int timeout, BlockFunc func = NULL, void* params = NULL)
	{
		PostMsg(wmAddWatch, id, timeout, func, params);
	}
	void RemoveWatch(int id)
	{
		PostMsg(wmRemove, id, 0, NULL, NULL);
	}
	void Report(int id)
	{
		PostMsg(wmReport, id, 0, NULL, NULL);
	}

protected:
	virtual void OnWorkThreadStart();
	virtual void OnWorkThreadStop();
protected:
	void SingleRun();
	void ProcessSysMsg();
	void OnRecvSysMsg(UINT msg, size_t p1, size_t p2, BlockFunc func, void* params);
	void PostMsg(UINT uMsg, size_t para1, size_t para2, BlockFunc func, void* params);

	WatchData* Find(int id);
private:
#ifdef _MSC_VER
	static void STDCALL Work_R(WatchThread* ptr);
#else
	static void* Work_R(void* ptr);
#endif
private:
#ifdef _MSC_VER
	HANDLE					handle_;		//工作线程句柄
	unsigned long			thread_id_;		//线程ID
#else
	pthread_t				thread_id_;
#endif
	bool					stoped_;				//是否标记为停止
	bool					exit_;

	QueueList<InterMsg> msg_list_;		//内部消息列表
	Mutex					msg_lock_;		//内部消息列表锁

	Vector<WatchData>		list_;
};


#endif

