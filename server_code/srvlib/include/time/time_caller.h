#ifndef _TIME_CALL_H_
#define _TIME_CALL_H_

/************************************************************************
*                             定时回调函数类
*                   支持按间隔毫秒数以及指定日期时间点的周期回调。
* 使用的是排序的链表算法，执行节点只需要遍历前面达到时间的节点，性能比较高，到时增加和删除都需要遍历
* 链表，性能都是O(n)
************************************************************************/
using namespace container;

class TimeCaller
{
public:
	/*
	* 定时回调函数类型定义
	* data 回调数据，数据由注册时传递
	* count 剩余调用的次数，调用后变为0则会从队列中删除
	*/
	typedef void (*TimerCallBack)(void* data, int* count);
	typedef void (*TimerCallerFree)(void* data);
	typedef bool (*RemoveIf)(void* data);

	/**
	 * 定义回调函数注册信息
	 ***********************/
	struct TIMECALLERNODE
	{
		int64_t guid_;
		TimerCallBack	callback_;	//回调函数指针
		TimerCallerFree	free_;
		void*			data_;		//回调数据，数据由注册时传递
		int				call_count_;	//调用次数
		uint64_t		next_t_;//下次调用的时间(TickCount)
		uint64_t		interval_;	//回调周期
		bool			remove_f_;//是否标记为移除
		bool			call_detory_;	// 在析构的时候是否要调用
		TIMECALLERNODE(): guid_(0)
		{

		}
	} ;
	struct NEXTNODE
	{
		TimerCallBack	callback_;	//回调函数指针
		TimerCallerFree	free_;
		void*			data_;		//回调数据，数据由注册时传递
		bool			call_detory_;	// 在析构的时候是否要调用
		bool			remove_f_;
	};
public:
	typedef Vector<NEXTNODE> NextList;
	typedef LinkedListEx<TIMECALLERNODE> TimeList;

	struct BaseCallerList
	{
		TimeList list_;
		int remove_count_;
		BaseCallerList(): remove_count_(0)
		{

		}
	};
public:
	TimeCaller(BaseAllocator* alloc);
	virtual ~TimeCaller()
	{
		ClearAllCaller();
	}

	void ClearAllCaller();

	/*
	* Comments: 注册定时回调对象
	*/
	int64_t AddTimeCaller(TimerCallBack callerfunc, TimerCallerFree freef,
	                      void* data, uint64_t next_t, int count = 1, uint64_t interv = 0, bool call_destory = false);
	bool AddNext(TimerCallBack callerfunc, TimerCallerFree freef, void* data, bool call_destory = false);
	/*
	* Comments: 移除回调函数
	* Param HANDLE hTimedCall: 回调对象句柄
	* @Return BOOL: 如果回调对象存在且成功移除则函数返回TRUE否则返回FALSE
	*/
	bool RemoveTimeCaller(int64_t caller);

	/*
	* Comments: 检查并调用已经到达运行时间的回调对象
	* @Return int: 返回检查了多少个回调对象
	*/
	int Run(uint64_t now_t);

	void RemoveAllIf(RemoveIf func);

	void SetPrecision(int precision) { precision_ = precision; }
private:
	bool RemoveTimeCaller(TimeList* list, int64_t caller);
	void Swap();
	void RunAllNext(NextList* list, bool destory = false);
	void RunAllTime(TimeList* list);

	void RemoveNextIf(NextList* list, RemoveIf func);
	void RemoveTimeIf(BaseCallerList* list, RemoveIf func);
private:
	NextList	next_list1_;
	NextList	next_list2_;

	NextList*	run_next_;


	BaseCallerList new_list_;
	BaseCallerList run_list_;
	int64_t	id_;

	bool cleaning_;		// 在清除所有数据的时候，不能再继续添加新caller
	bool runing_next_;		// 是否正在run next队列
	bool run_time_;		// 是否在run time队列
	bool run_time_clean_;	// 是否在run time期间执行了clean操作

	ListIterator<TIMECALLERNODE> run_list_iter_;	//运行链表迭代器
	ListIterator<TIMECALLERNODE> new_list_iter_;	//新建链表迭代器

	int precision_;	//运行精度(毫秒)
	uint64_t next_run_t_;
};

#endif

