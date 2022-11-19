#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "os_def.h"
#include "_ast.h"

#include "x_tick.h"
#include "x_lock.h"
#include "container/queue_list.h"
#include "share_util.h"
#include "os_def.h"
#include "appitnmsg.h"
#include "server_def.h"
#include "watch_thread.h"


WatchThread::WatchThread()
{
#ifdef _MSC_VER
	handle_ = NULL;
#endif
	stoped_ = true;
	exit_ = true;

	msg_list_.setLock(&msg_lock_);

	Startup();
}

WatchThread::~WatchThread()
{
	Stop();

	msg_list_.flush();
	msg_list_.clear();
}

void WatchThread::SingleRun()
{
	ProcessSysMsg();

	//check
	time_t now_t = _getTickCount();
	for (int i = 0; i < list_.count(); ++i)
	{
		WatchData& data = list_[i];

		if (now_t - data.last_t_ >= data.timeout_)
		{
			printf("watch thread: %d block!time:%lld current = %d\n", 
				data.id_, (long long int)(now_t - data.last_t_), list_.count());
			
			if (data.func_)
				data.func_(data.params_);
			data.last_t_ = now_t; // 避免不断的输出
		}
	}
}

void WatchThread::PostMsg(UINT uMsg, size_t para1, size_t para2, BlockFunc func, void* params)
{
	InterMsg msg;
	msg.uMsg = uMsg;
	msg.uParam1 = para1;
	msg.uParam2 = para2;
	msg.func = func;
	msg.params = params;
	msg_list_.append(msg);
}

void WatchThread::OnRecvSysMsg(UINT msg, size_t p1, size_t p2, BlockFunc func, void* params)
{
	switch (msg)
	{
	case wmAddWatch:
		{
			int id = (int)p1;
			if (Find(id))
			{
				OutputMsg(rmError, "this id exist:%d", id);
			}
			WatchData data;
			data.id_ = id;
			data.last_t_ = _getTickCount();
			data.timeout_ = (int)p2;
			data.func_ = func;
			data.params_ = params;
			list_.add(data);

			break;
		}

	case wmReport:
		{
			WatchData* data = Find((int)p1);
			if (data)
			{
				data->last_t_ = _getTickCount();
			}
			else
			{
				printf("%d is not find. report error!!!!\n", (int)p1);
			}
			break;
		}
	case wmRemove:
		{
			int id = (int)p1;
			for (int i = 0; i < list_.count(); ++i)
			{
				WatchData& data = list_[i];

				if (data.id_ == id)
				{
					int count = list_.count();
					//查错
					//list_.remove(i);
					for (int j = i + 1, t = i; j < list_.count(); j++, t++)
					{
						WatchData& srcData = list_[j];
						WatchData& destData = list_[t];
						memcpy(&destData, &srcData, sizeof(WatchData));
					}
					list_.trunc(count-1); 
					return;
				}
			}
			break;
		}
	default:
		break;
	}
}

void WatchThread::ProcessSysMsg()
{
	msg_list_.flush();
	int count = msg_list_.count();

	for (int i = 0; i < count; ++i)
	{
		InterMsg& msg = msg_list_[i];
		OnRecvSysMsg(msg.uMsg, msg.uParam1, msg.uParam2, msg.func, msg.params);
	}

	msg_list_.clear();
}

void WatchThread::OnWorkThreadStart()
{
	OutputMsg(rmNormal, "watch thread start");
}

void WatchThread::OnWorkThreadStop()
{
	OutputMsg(rmNormal, "watch thread stop");
}

#ifdef _MSC_VER
void STDCALL WatchThread::Work_R(WatchThread* ptr)
#else
void* WatchThread::Work_R(void* ptr)
#endif
{
	WatchThread* watch = (WatchThread*)ptr;

	watch->OnWorkThreadStart();

	while (!watch->stoped_)
	{
		watch->SingleRun();

		Sleep(1);
	}

	watch->OnWorkThreadStop();

	watch->exit_ = true;

#ifdef _MSC_VER
	ExitThread(0);//设置线程退出返回值
#else
	return NULL;
#endif
}

bool WatchThread::Startup()
{
	bool ret = true;
	int err = 0;

	stoped_ = false;
#ifdef _MSC_VER
	handle_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Work_R, this, 0, &thread_id_);

	if (!handle_)
	{
		err = GetLastError();
		ret = false;
	}

#else

	if (pthread_create(&thread_id_, NULL, Work_R, this))
	{
		err = errno;
		ret = false;
	}

#endif

	if (!ret)
	{
		OutputError(err, ("创建监控线程失败"));
		return false;
	}

	exit_ = false;
	return true;
}

void WatchThread::Stop()
{
	stoped_ = true;

	while (!exit_)
	{
		Sleep(10);
	}

#ifdef _MSC_VER
	CloseThread(handle_);
#endif
}

WatchThread::WatchData* WatchThread::Find(int id)
{
	for (int i = 0; i < list_.count(); ++i)
	{
		WatchData& data = list_[i];

		if (data.id_ == id)
		{
			return &data;
		}
	}

	return NULL;
}
