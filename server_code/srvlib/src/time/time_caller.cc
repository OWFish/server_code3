#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include "_ast.h"

#include "x_tick.h"
#include "container/linked_list.h"
#include "container/linked_list_ex.h"
#include "share_util.h"
#include "time/time_caller.h"

template<>
TimeCaller::TimeList::LinkNodeMgr* TimeCaller::TimeList::node_pool_ = NULL;

using namespace container;
TimeCaller::TimeCaller(BaseAllocator* alloc):
	next_list1_(alloc), next_list2_(alloc), cleaning_(false),
	runing_next_(false), run_time_(false), run_time_clean_(false), precision_(0), next_run_t_(0)
{
	run_next_ = &next_list1_;
	run_list_iter_.setList(run_list_.list_);
	new_list_iter_.setList(new_list_.list_);
}

void TimeCaller::ClearAllCaller()
{
	// 某些caller可能在清除的时候执行函数，函数里面又调用了z这个函数，所以这里要避免这个情况
	if (cleaning_) return;

	// 禁止期间再添加新的
	cleaning_ = true;

	if (!runing_next_)
	{
		RunAllNext(run_next_, true);
	}
	NextList* list = (run_next_ == &next_list1_ ? &next_list2_ : &next_list1_);
	RunAllNext(list, true);

	run_time_clean_ = run_time_;
	if (!run_time_)
	{
		RunAllTime(&run_list_.list_);
		RunAllTime(&new_list_.list_);
	}

	cleaning_ = false;
}

int64_t TimeCaller::AddTimeCaller(TimerCallBack callerfunc, TimerCallerFree freef,
                                  void* data, uint64_t next_t, int count, uint64_t interv, bool call_destory)
{
	if (cleaning_) return 0;

	TIMECALLERNODE node;

	node.guid_ = id_++;

	if (node.guid_ == 0) node.guid_ = id_++;

	node.callback_ = callerfunc;
	node.free_ = freef;
	node.data_ = data;
	node.call_count_ = count;
	node.next_t_ = next_t;
	node.interval_ = interv;
	node.remove_f_ = false;
	node.call_detory_ = call_destory;
	new_list_.list_.linkAtLast(node);
	return node.guid_;
}

bool TimeCaller::AddNext(TimerCallBack callerfunc, TimerCallerFree freef, void* data, bool call_destory)
{
	if (cleaning_) return false;

	NEXTNODE node;

	node.callback_ = callerfunc;
	node.free_ = freef;
	node.data_ = data;
	node.call_detory_ = call_destory;
	node.remove_f_ = false;

	NextList* list = (run_next_ == &next_list1_ ? &next_list2_ : &next_list1_);
	list->add(node);
	return true;
}

bool TimeCaller::RemoveTimeCaller(int64_t caller)
{
	if (cleaning_) return false;

	if (RemoveTimeCaller(&run_list_.list_, caller))
	{
		run_list_.remove_count_++;
		return true;
	}
	else
	{
		return RemoveTimeCaller(&new_list_.list_, caller);
	}
}

bool TimeCaller::RemoveTimeCaller(TimeList* list, int64_t caller)
{
	LinkedNode<TIMECALLERNODE>* node;
	ListIterator<TIMECALLERNODE> it(*list);

	for (node = it.first(); node; node = it.next())
	{
		TIMECALLERNODE& tc = *node;

		if (caller == tc.guid_)
		{
			//标记为移除
			tc.remove_f_ = true;
			return true;
		}
	}

	return false;
}

int TimeCaller::Run(uint64_t now_t)
{
	if (now_t < next_run_t_) return 0;
	next_run_t_ = now_t + precision_;

	int result = 0;
	int count = run_next_->count();
	runing_next_ = true;
	RunAllNext(run_next_);
	runing_next_ = false;
	result += count;

	LinkedNode<TIMECALLERNODE>* node = NULL;
	//ListIterator<TIMECALLERNODE> it(run_list_.list_);
	run_time_ = true;
	for (node = run_list_iter_.first(); node; node = run_list_iter_.next())
	{
		TIMECALLERNODE& tc = *node;

		if (tc.remove_f_)
		{
			run_list_.remove_count_--;
			if (tc.free_) tc.free_(tc.data_);
			run_list_iter_.remove(node);
			continue;
		}

		if (now_t < tc.next_t_) break;	// 已排序，当前时间小于这个节点，则后面的都不用遍历了

		tc.call_count_--;
		tc.callback_(tc.data_, &tc.call_count_);

		tc.next_t_ += tc.interval_;

		if (tc.call_count_ <= 0)
		{
			if (tc.free_) tc.free_(tc.data_);
			run_list_iter_.remove(node);	// 可直接删除
		}
		else
		{
			run_list_iter_.remove(node, false);
			// 移到新增队列的后面去
			new_list_.list_.TransferAtLast(node);
		}

		result++;
	}
	//移除标记为移除的回调
	if (run_list_.remove_count_ > 0)
	{
		//ListIterator<TIMECALLERNODE> it(run_list_.list_);

		for (node = run_list_iter_.first(); node; node = run_list_iter_.next())
		{
			TIMECALLERNODE& tc = *node;

			if (tc.remove_f_)
			{
				if (tc.free_) tc.free_(tc.data_);

				run_list_iter_.remove(node);
				run_list_.remove_count_--;

				if (run_list_.remove_count_ <= 0)
					break;
			}

		}

		run_list_.remove_count_ = 0;
	}

	Swap();

	run_time_ = false;
	// 所有的节点移动到了run_list_
	if (run_time_clean_)
	{
		// 要清除所有
		ClearAllCaller();
	}

	return result;
}

void TimeCaller::Swap()
{
	run_next_ = (run_next_ == &next_list1_ ? &next_list2_ : &next_list1_);

	LinkedNode<TIMECALLERNODE>* nnode = NULL;
	//ListIterator<TIMECALLERNODE> nit(new_list_.list_);

	for (nnode = new_list_iter_.first(); nnode; nnode = new_list_iter_.next())
	{
		TIMECALLERNODE& tc = *nnode;

		if (!tc.remove_f_)
		{
			new_list_iter_.remove(nnode, false);

			LinkedNode<TIMECALLERNODE>* rnode = NULL;
			ListIterator<TIMECALLERNODE> rit(run_list_.list_);
			bool find = false;

			for (rnode = rit.first(); rnode; rnode = rit.next())
			{
				TIMECALLERNODE& rtc = *rnode;

				if (tc.next_t_ < rtc.next_t_)
				{
					run_list_.list_.linkBefore(nnode, rnode);
					find = true;
					break;
				}
			}

			if (!find) run_list_.list_.TransferAtLast(nnode);
		}
		else
		{
			if (tc.free_) tc.free_(tc.data_);

			new_list_iter_.remove(nnode);
		}
	}

	new_list_.list_.clear();
}

void TimeCaller::RunAllNext(NextList* list, bool destory)
{
	int count = list->count();
	NEXTNODE* nextList = *list;

	for (int i = 0; i < count; ++i)
	{
		NEXTNODE& node = nextList[i];

		if (!node.remove_f_ && (!destory || node.call_detory_))
			node.callback_(node.data_, NULL);

		if (node.free_)
			node.free_(node.data_);
	}

	list->clear();
}

void TimeCaller::RunAllTime(TimeList* list)
{
	LinkedNode<TIMECALLERNODE>* node = NULL;
	ListIterator<TIMECALLERNODE> it(*list);

	for (node = it.first(); node; node = it.next())
	{
		TIMECALLERNODE& tc = *node;

		if (!tc.remove_f_ && tc.call_detory_)
			tc.callback_(tc.data_, &tc.call_count_);

		if (tc.free_)
			tc.free_(tc.data_);
	}

	list->clear();
}

void TimeCaller::RemoveAllIf(RemoveIf func)
{
	RemoveNextIf(&next_list1_, func);
	RemoveNextIf(&next_list2_, func);

	RemoveTimeIf(&run_list_, func);
	RemoveTimeIf(&new_list_, func);
}

void TimeCaller::RemoveNextIf(NextList* list, RemoveIf func)
{
	int count = list->count();
	NEXTNODE* nextList = *list;

	for (int i = count - 1; i >= 0; --i)
	{
		NEXTNODE& node = nextList[i];

		if (func(node.data_))
		{
			node.remove_f_ = true;
		}
	}
}

void TimeCaller::RemoveTimeIf(BaseCallerList* list, RemoveIf func)
{
	LinkedNode<TIMECALLERNODE>* node = NULL;
	ListIterator<TIMECALLERNODE> it(list->list_);

	for (node = it.first(); node; node = it.next())
	{
		TIMECALLERNODE& tc = *node;

		if (!tc.remove_f_ && func(tc.data_))
		{
			list->remove_count_++;
			tc.remove_f_ = true;
		}
	}

}


