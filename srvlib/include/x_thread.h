#ifndef _LIB_THREAD_H_
#define _LIB_THREAD_H_

/******************************************************************
 *  - 主要功能 -
 *	实现线程的基本封装操作。支持暂停、恢复线程，等待线程以及设
 *	置线程优先级等基本操作。
 *****************************************************************/
#ifndef _MSC_VER
#include "pthread.h"
#endif

namespace thread
{
class BaseThread
{
private:
#ifdef _MSC_VER
	static void CALLBACK ThreadRoutine(BaseThread* thread_ptr);
#else
	static void* ThreadRoutine(void* thread_ptr);
#endif
protected:
	//terminated函数用于判断现成是否被设置了终止标记
	inline bool terminated()
	{
		return terminated_;
	}
	//线程事物处理例程函数，子类应当继承此函数
	virtual void OnRoutine();
	//线程例程终止后的通知函数
	virtual void OnTerminated();
public:
	BaseThread();
	virtual ~BaseThread();

#ifdef _MSC_VER
	//获取线程句柄
	inline void* getHandle()
	{
		return thread_;
	}
	//获取线程ID
	inline unsigned long getThreadId()
	{
		return thread_id_;
	}
#endif
	//恢复线程的执行，返回值表示线程到本次恢复操作后，线程仍需恢复多少次才能恢复执行。
	//若返回-1则表示恢复线程失败，返回0表示线程已经完全恢复执行。
	virtual int Start();
	virtual void Stop();
#ifdef _MSC_VER
	//获取线程优先级,失败会返回THREAD_PRIORITY_ERROR_RETURN，否则返回值表示线程优先级
	int getPriority();
	//设置线程优先级，成功则返回true
	bool setPriority(int priority);
#endif
	//等待线程执行完毕，wait_time参数表示等待的最大毫秒数，INFINITE表示无限等待。
	//注意，调用此函数的线程在此线程执行完毕后会一直处于阻塞状态
	//参数wait_alert表示调用线程在阻塞期间是否允许进入警告状态（仅对于windows有效)
#ifdef _MSC_VER
	int waitFor(unsigned int wait_time = INFINITE, bool wait_alert = true);
#else
	int waitFor();
#endif
	//标记线程的终止标记
	void terminate();
private:
#ifdef _MSC_VER
	void*			thread_;			//线程句柄
	unsigned long	thread_id_;			//线程ID
#else
	pthread_t		thread_id_;
#endif
	bool			terminated_;		//线程终止标记，子类在线程例程循环中应当通过调用terminated函数判断线程是否被设置了终止标记
};
};

#endif

