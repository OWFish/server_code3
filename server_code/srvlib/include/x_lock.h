#ifndef _X_LOCK_H_
#define	_X_LOCK_H_

/******************************************************************
 *	��������
 *  ��Ҫ����  *
 *		�����ڲ��Ļ�������Windows���ṩ�ٽ�����(CSLock)��ԭ����(
 *		CAtomLock)���ֻ���ʵ�ַ�ʽ�������ṩһ�����ں����ڲ���ȫ
 *		ʹ�õ�CSafeLock�ࡣ
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

