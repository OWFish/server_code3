#ifndef _ASYNC_WORKER_H_
#define _ASYNC_WORKER_H_

/*
* �������е��̣߳����ڷ���Ϸ���߳�ִ�еĲ���
* �������ÿ��web�ӿڡ�
* �����µĹ��ܣ�ֻ��Ҫ�����̵߳�ִ�к������Լ�ִ����ɺ�Ļص�����
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
		ScriptValueList req_;	// ����Ĳ����б�
		ScriptValueList result_;	// ִ����󷵻ص�ֵ
	};

	struct CBData
	{
		unsigned int guid_;		// ���кţ�ÿ��ִ�еĺ����������һ��Ψһ��id�����ڻص�
		WordFunc work_func_;	// �ڱ��߳���ִ�еĹ����������������web
		WordFunc after_func_;	// ����Ϸ���߳�Ҫִ�еĺ���ָ��,���ص�����
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

	// ����һ���߳�ִ�еĲ���
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

	// ����ִ��lua������
	unsigned int SendLuaMessage(ScriptValueList& req, WordFunc func);
protected:
	void OnRoutine();
	//�����߼�����
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
	BaseScript		script_;	// ����ִ��lua�Ĵ���
	bool			reload_;	// ֪ͨ���¼��ؽű�
	char			lua_file_[128];	//�ļ���
};

#endif



