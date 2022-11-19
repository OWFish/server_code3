#include "os_def.h"
#include "x_thread.h"
#include "share_util.h"

using namespace thread;

BaseThread::BaseThread()
{
#ifdef _MSC_VER
	thread_ = NULL;
#endif
	thread_id_ = 0;
	terminated_ = false;
}


BaseThread::~BaseThread()
{
	Stop();

#ifdef _MSC_VER
	if (thread_)
	{
		CloseHandle(thread_);
		thread_ = NULL;
	}
#endif
}

#ifdef _MSC_VER
void CALLBACK BaseThread::ThreadRoutine(BaseThread* thread_ptr)
{
	thread_ptr->OnRoutine();
	thread_ptr->OnTerminated();
	//ExitThread(0);
}
#else
void* BaseThread::ThreadRoutine(void* thread_ptr)
{
	BaseThread* ptr = (BaseThread*)thread_ptr;
	ptr->OnRoutine();
	ptr->OnTerminated();
	return NULL;
}
#endif
void BaseThread::OnRoutine()
{
}


void BaseThread::OnTerminated()
{
}


int BaseThread::Start()
{
	CheckDate();

#ifdef _MSC_VER
	thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRoutine, this, 0, &thread_id_);	
	return 0;
#else
	int ret = pthread_create(&thread_id_, NULL, ThreadRoutine, this);
	if (ret != 0)
	{
		thread_id_ = 0;
	}
	return ret;
#endif
}

#ifdef _MSC_VER
int BaseThread::getPriority()
{
	return GetThreadPriority(thread_);
}

bool BaseThread::setPriority(int priority)
{
	return SetThreadPriority(thread_, priority) != 0;
}
#endif

#ifdef _MSC_VER
int BaseThread::waitFor(unsigned int wait_time, bool wait_alert)
{
	return WaitForSingleObjectEx(thread_, wait_time, wait_alert);
}
#else
int BaseThread::waitFor()
{
	int ret = 0;
	if (thread_id_ != 0)
	{
		ret = pthread_join(thread_id_, NULL);
		thread_id_ = 0;
	}
	return ret;
}
#endif

void BaseThread::terminate()
{
	terminated_ = true;
}

void BaseThread::Stop()
{
	terminate();
	waitFor();
}
