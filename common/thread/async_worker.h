#ifndef _ASYNC_WORKER_H_
#define _ASYNC_WORKER_H_

/*
* 单独运行的线程，用于非游戏主线程执行的操作
* 比如访问每个web接口。
* 增加新的功能，只需要定义线程的执行函数，以及执行完成后的回调函数
*/

using namespace thread;
using namespace container;

class AsyncWorker: public thread::BaseThread
{
public:
	typedef BufferAllocator AsyncWorkerAlloc;

	typedef BaseThread Inherited;
	typedef void (*WordFunc)(void* cb);
	typedef void (*WorkerCallBack)(void* cb);
	typedef void (*FreeFunc)(void* cb);

	struct LuaParams
	{
		ScriptValueList req_;	// 请求的参数列表
		ScriptValueList result_;	// 执行完后返回的值
	};

	struct CBData
	{
		unsigned int guid_;		// 序列号，每个执行的函数都会分配一个唯一的id，用于回调
		WordFunc work_func_;	// 在本线程里执行的工作函数，比如访问web
		WordFunc after_func_;	// 在游戏主线程要执行的函数指针,即回调函数
		FreeFunc free_func_;
		void* params_;
		AsyncWorker* worker_;
		CBData(AsyncWorker* worker,	unsigned int guid): 
				guid_(guid), work_func_(NULL), after_func_(NULL),
			free_func_(NULL), params_(NULL), worker_(worker)
		{
		}
	};
public:
	AsyncWorker(const char* lua_file = NULL);

	void LoadScript(const char* lua_file);

	virtual ~AsyncWorker();

	// 新增一个线程执行的操作
	void AppendWork(CBData* cb);

public:
	AsyncWorkerAlloc& GetAlloc()
	{
		return alloc_;
	}
	void SetWorkCallBack(WorkerCallBack wcb)
	{
		wcb_ = wcb;
	}
	void Reload()
	{
		reload_ = true;
	}

	// 发送执行lua的请求
	unsigned int SendLuaMessage(ScriptValueList& req, WordFunc func);
protected:
	void OnRoutine();
	//单次逻辑处理
	int Run();
	void OnStart();
	void OnStop();
private:
	static void FreeLuaParams(void* callback);
	static void ExecuteLua(void* cb);
private:
	QueueList<CBData*> cb_list_;
	Mutex				cb_list_lock_;

	AsyncWorkerAlloc alloc_;
	unsigned int	id_;
	WorkerCallBack	wcb_;
	BaseScript		script_;	// 用于执行lua的代码
	bool			reload_;	// 通知重新加载脚本
	char			lua_file_[128];	//文件名
};

#endif



