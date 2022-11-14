#ifndef _X_LOCK_H_
#define	_X_LOCK_H_

/******************************************************************
 *	互斥锁类
 *  主要功能  *
 *		进程内部的互斥锁。Windows中提供临界区锁(CSLock)和原子锁(
 *		CAtomLock)两种互斥实现方式。另外提供一个可在函数内部安全
 *		使用的CSafeLock类。
 *
 *****************************************************************/
#ifndef _MSC_VER
#include <pthread.h>
#endif

namespace lock
{
class Mutex
{
private:
#ifdef _MSC_VER
	CRITICAL_SECTION lock_;
#else
	pthread_mutex_t lock_;
#endif
public:
	Mutex();
	virtual ~Mutex();
	void Lock();
	void Unlock();
};

};


#endif

