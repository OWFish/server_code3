#ifndef _TIME_CALL_H_
#define _TIME_CALL_H_

/************************************************************************
*                             ��ʱ�ص�������
*                   ֧�ְ�����������Լ�ָ������ʱ�������ڻص���
* ʹ�õ�������������㷨��ִ�нڵ�ֻ��Ҫ����ǰ��ﵽʱ��Ľڵ㣬���ܱȽϸߣ���ʱ���Ӻ�ɾ������Ҫ����
* �������ܶ���O(n)
************************************************************************/
using namespace container;

class TimeCaller
{
public:
	/*
	* ��ʱ�ص��������Ͷ���
	* data �ص����ݣ�������ע��ʱ����
	* count ʣ����õĴ��������ú��Ϊ0���Ӷ�����ɾ��
	*/
	typedef void (*TimerCallBack)(void* data, int* count);
	typedef void (*TimerCallerFree)(void* data);
	typedef bool (*RemoveIf)(void* data);

	/**
	 * ����ص�����ע����Ϣ
	 ***********************/
	struct TIMECALLERNODE
	{
		int64_t guid_;
		TimerCallBack	callback_;	//�ص�����ָ��
		TimerCallerFree	free_;
		void*			data_;		//�ص����ݣ�������ע��ʱ����
		int				call_count_;	//���ô���
		uint64_t		next_t_;//�´ε��õ�ʱ��(TickCount)
		uint64_t		interval_;	//�ص�����
		bool			remove_f_;//�Ƿ���Ϊ�Ƴ�
		bool			call_detory_;	// ��������ʱ���Ƿ�Ҫ����
		TIMECALLERNODE(): guid_(0)
		{

		}
	} ;
	struct NEXTNODE
	{
		TimerCallBack	callback_;	//�ص�����ָ��
		TimerCallerFree	free_;
		void*			data_;		//�ص����ݣ�������ע��ʱ����
		bool			call_detory_;	// ��������ʱ���Ƿ�Ҫ����
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
	* Comments: ע�ᶨʱ�ص�����
	*/
	int64_t AddTimeCaller(TimerCallBack callerfunc, TimerCallerFree freef,
	                      void* data, uint64_t next_t, int count = 1, uint64_t interv = 0, bool call_destory = false);
	bool AddNext(TimerCallBack callerfunc, TimerCallerFree freef, void* data, bool call_destory = false);
	/*
	* Comments: �Ƴ��ص�����
	* Param HANDLE hTimedCall: �ص�������
	* @Return BOOL: ����ص���������ҳɹ��Ƴ���������TRUE���򷵻�FALSE
	*/
	bool RemoveTimeCaller(int64_t caller);

	/*
	* Comments: ��鲢�����Ѿ���������ʱ��Ļص�����
	* @Return int: ���ؼ���˶��ٸ��ص�����
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

	bool cleaning_;		// ������������ݵ�ʱ�򣬲����ټ��������caller
	bool runing_next_;		// �Ƿ�����run next����
	bool run_time_;		// �Ƿ���run time����
	bool run_time_clean_;	// �Ƿ���run time�ڼ�ִ����clean����

	ListIterator<TIMECALLERNODE> run_list_iter_;	//�������������
	ListIterator<TIMECALLERNODE> new_list_iter_;	//�½����������

	int precision_;	//���о���(����)
	uint64_t next_run_t_;
};

#endif

