#include "os_def.h"
#include "x_lock.h"

#ifdef _MSC_VER
#define InitMutex(x)			InitializeCriticalSection(x)
#define DestroyMutex(x)			DeleteCriticalSection(x)
#define MutexLock(x)			EnterCriticalSection(x)
#define MutexUnLock(x)			LeaveCriticalSection(x)
#else
#define InitMutex(x)			pthread_mutex_init(x,NULL)
#define DestroyMutex(x)			pthread_mutex_destroy(x)
#define MutexLock(x)			pthread_mutex_lock(x)
#define MutexUnLock(x)			pthread_mutex_unlock(x)
#endif

using namespace lock;

Mutex::Mutex()
{
	InitMutex(&lock_);
}

Mutex::~Mutex()
{
	DestroyMutex(&lock_);
}

void Mutex::Lock()
{
	MutexLock(&lock_);
}


void Mutex::Unlock()
{
	MutexUnLock(&lock_);
}


