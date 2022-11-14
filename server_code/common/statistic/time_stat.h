#ifndef _TIME_STAT_H_
#define _TIME_STAT_H_
#ifdef _MSC_VER
//////////////////////////////////////////////////////////////////////////
//							时间统计分析类
// 功	能：用于追踪程序中调用的函数执行时间消耗情况，定位出性能瓶颈
// 说	明：统计按照设定好的时间间隔来输出，例如2分钟输出一次，将所有函数调用
//			节点信息按照树形结果来呈现（序列化到文件）处理，可以快速的分析出
//			2分钟内，每个执行单元消耗了多久时间，找出瓶颈所在。
// 例如：在逻辑线程，在逻辑线程每次循环加一个追踪节点，在下面的网络处理、实体管理器、
//		 副本管理器等等都增加追踪节点，这样就能详细的跟踪到每个节点耗时占整个耗时的
//		 比例。
//			因为逻辑引擎本身采取分时，对每个子（子子）单元都限制了执行时间，这样就对
//		 统计分析有影响！比如正常情况下实体管理器刷新占据每次例行50%左右的时间，结果
//		 因为分时，就算实体刷新出问题，也检测不出来！！！
//			对于此问题，要么是暂时过滤分时；要么是在实体管理器内部设置分时追踪结点。
//////////////////////////////////////////////////////////////////////////

#include <new>
//#include "ObjectCounter.h"
class TimeProfDummy
{
public:
	TimeProfDummy(const char* szUnitName, unsigned int nHashCode);
	~TimeProfDummy();
};

// 执行时间记录节点
class TimeProfRecord
{
public:
	enum
	{
		MAX_EXEC_UNIT_NAME_LEN	= 64,								// 最大执行单元名称
	};
	TimeProfRecord(){}
	TimeProfRecord(const char* szUnitName, unsigned int nHashCode);
	~TimeProfRecord();
	//设置节点名称
	void setName(const char* szName);
	// 添加一个子执行结点
	inline void addChild(TimeProfRecord* record)
	{
		m_childrenNode.add(record);
	}
	// 查询节点
	//CTimeProfRecord* getChild(const char* szUnitName);
	inline TimeProfRecord* getChildByHash(int nHashCode)
	{
		for (int i = 0; i < m_childrenNode.count(); i++)
		{
			if ((unsigned int)nHashCode == m_childrenNode[i]->m_nNameHashCode)
				return m_childrenNode[i];
		}
		return NULL;
	}
	// 输出结点执行时间详细信息
	void dump(stream::BaseStream& stream, int level = 0);
	// 重置节点数据
	inline void reset(bool bIncOccuData = false)
	{
		m_nTotalCount	= 0;
		m_nMaxTime		= 0;
		m_nMinTime		= 0;
		m_nTotalTime	= 0;
		if (bIncOccuData)
		{
			m_nOccuTotalCount	= 0;
			m_nOccuTotalTime	= 0;
			m_nOccuMaxTime		= 0;
			m_nOccuMinTime		= 0;
		}
	}
	inline void reInitBasicData(const char* szUnitName, unsigned int nHashCode)
	{
		ZeroMemory(this, offsetof(TimeProfRecord, m_childrenNode));
		_STRNCPY_A(m_szExecUnitName, szUnitName);
		for (int i = 0; i < (int)strlen(m_szExecUnitName); i++)
		{
			if (m_szExecUnitName[i] == ('\"')		|| m_szExecUnitName[i] == (',') || m_szExecUnitName[i] == ('<') 
				|| m_szExecUnitName[i] == ('>')	|| m_szExecUnitName[i] == (':') || m_szExecUnitName[i] == (' '))
				m_szExecUnitName[i] = ('_');
		}
		m_nNameHashCode = nHashCode;			
	}
	inline void startProf()
	{
		m_nStartTime = _getTickCount();		
		m_nTotalCount++;	
		m_nOccuTotalCount++;
	}
	inline void endProf()
	{
		m_nEndTime = _getTickCount();		
		unsigned long long nTimeConsume = m_nEndTime - m_nStartTime;
		if (m_nMaxTime < nTimeConsume)
			m_nMaxTime = nTimeConsume;
		if (m_nMinTime > nTimeConsume)
			m_nMinTime = nTimeConsume;
		if (m_nOccuMaxTime < nTimeConsume)
			m_nOccuMaxTime = nTimeConsume;
		if (m_nOccuMinTime > nTimeConsume)
			m_nOccuMinTime = nTimeConsume;
		m_nTotalTime += nTimeConsume;
		m_nOccuTotalTime += nTimeConsume;	
	}

	void clear();

	//字符串hash函数，需要提供长度
	inline static unsigned int hashlstr(const char* str, size_t len)
	{
		unsigned int h = (unsigned int)len;
		size_t step = (len>>5)+1;  /* if string is too long, don't hash all its chars */
		size_t l1;
		for (l1=len; l1>=step; l1-=step)  /* compute hash */
			h = h ^ ((h<<5)+(h>>2)+(unsigned char)str[l1-1]);
		return h;
	}

protected:		
	unsigned int				m_nNameHashCode;							// 名字Hash码
	unsigned long long			m_nTotalCount;								// 执行次数
	unsigned long long			m_nOccuTotalCount;							// 累积执行次数
	unsigned long long			m_nMaxTime;									// 本次统计最大执行耗时
	unsigned long long			m_nMinTime;									// 本次统计最小执行耗时
	unsigned long long			m_nOccuMaxTime;								// 累积的最大执行耗时
	unsigned long long			m_nOccuMinTime;								// 累积的最小执行耗时
	unsigned long long			m_nTotalTime;								// 整体执行耗时（用于统计平均耗时）
	unsigned long long			m_nOccuTotalTime;							// 累积执行时间
	unsigned long long			m_nStartTime;								// 开始执行时间	
	unsigned long long			m_nEndTime;									// 结束执行时间
	char						m_szExecUnitName[MAX_EXEC_UNIT_NAME_LEN];	// 执行单位名称	
	container::Vector<TimeProfRecord*>		m_childrenNode;		// 所有子节点列表
};


// 执行时间管理器
class TimeProfMgr
{
public:
	TimeProfMgr();
	~TimeProfMgr();
	enum
	{
		ALLOC_RECORD_NUM = 200,
	};
	
	bool InitMgr()
	{
		if (TLS_OUT_OF_INDEXES == s_dwTlsIdx)
		{
			s_dwTlsIdx = TlsAlloc();
			return s_dwTlsIdx != TLS_OUT_OF_INDEXES ? true : false;
		}

		return false;		
	}

	static TimeProfMgr& getSingleton()
	{
		static TimeProfMgr mgr;
		return mgr;
	}

	TimeProfMgr* getThreadInst()
	{
		TimeProfMgr* profMgr = (TimeProfMgr *)TlsGetValue(s_dwTlsIdx);
		if (!profMgr)
		{
			profMgr = new TimeProfMgr();
			profMgr->setThreadId(GetCurrentThreadId());
			TlsSetValue(s_dwTlsIdx, profMgr);
			m_lock.Lock();
			m_vecTimeProfMgr.add(profMgr);
			m_lock.Unlock();
		}

		return profMgr;
	}

	// 开始执行计时
	inline void OnTimeProfRecordStart(TimeProfRecord *record)
	{
		m_execUnitStack.push(record);
	}
	// 结束执行计时
	inline void OnTimeProfRecordEnd(TimeProfRecord *)
	{
		m_execUnitStack.pop();		
	}

	// 获取当前执行单元结点
	inline TimeProfRecord* getCurrTimeProfRecord()
	{
		int count = m_execUnitStack.count();
		if (count > 0)
			return m_execUnitStack[count-1];

		return NULL;
	}

	// 输出结点执行时间详细信息
	void dump();

	inline TimeProfRecord* allocRecord()
	{
		if (m_freeRecordList.count() <= 0)
			allocTimeProfRecord();
		return m_freeRecordList.pop();
	}

	inline void freeRecord(TimeProfRecord *record)
	{
		m_freeRecordList.add(record);
	}
	inline void clear()
	{
		m_execUnitRoot.clear();

		for (int i = 0; i < m_freeRecordList.count(); i++)
		{
			TimeProfRecord *pRecord = m_freeRecordList[i];
			if (pRecord)
			{
				pRecord->~TimeProfRecord();
				free(pRecord);
			}
			
		}
		m_freeRecordList.empty();		
		m_execUnitStack.empty();

		if (s_dwTlsIdx != TLS_OUT_OF_INDEXES)
		{
			TlsFree(s_dwTlsIdx);
			s_dwTlsIdx = TLS_OUT_OF_INDEXES;
		}
		for (int i = 0; i < m_vecTimeProfMgr.count(); i++)
		{
			delete m_vecTimeProfMgr[i];
		}
		m_vecTimeProfMgr.empty();
	}
protected:
	// 输出时间头
	void dumpDateTimeHeader(stream::BaseStream& stream);
	// 输出分隔符
	void dumpDateTimeSep(stream::BaseStream& stream);
	// 获取当前时间
	void getCurrentTm(tm &t);
	// dump
	void dumpImpl(stream::BaseStream& stream);
	// 格式化时间
	void formatTimeStr(char* szDataBuff, size_t nLen, tm *t);
	// 执行一次分配（每次分配ALLOC_RECORD_NUM个）
	inline void allocTimeProfRecord()
	{		
		for (int i = 0; i < ALLOC_RECORD_NUM; i++)
		{
			TimeProfRecord* pRecords = (TimeProfRecord *)malloc(sizeof(TimeProfRecord));
			if (pRecords)
			{
				new (pRecords)TimeProfRecord();
				m_freeRecordList.add(pRecords);
			}
			
		}
	}
	// 设置线程Id
	inline void setThreadId(DWORD dwThreadId) { m_dwThreadId = dwThreadId; }

protected:
	container::Vector<TimeProfRecord *>	m_execUnitStack;	// 执行单元结点栈
	TimeProfRecord									m_execUnitRoot;		// 执行单元树的根节点	
	tm												m_lastDumpTime;		// 上次dump结束时间
	container::Vector<TimeProfRecord*>	m_freeRecordList;
	static DWORD									s_dwTlsIdx;			// Tls Slot Index
	lock::Mutex						m_lock;				// Sync for multithread create timeprofmgr object
	container::Vector<TimeProfMgr*>		m_vecTimeProfMgr;	// TimeProfMgr list
	DWORD											m_dwThreadId;		// Current ThreadId
};

#ifdef _TIME_STATE_CHECK_
#define DECLARE_TIME_PROF(name)   static unsigned int _STATIC_FUNCTION_HASH_VALUE_= TimeProfRecord::hashlstr(name,strlen(name)); \
	TimeProfDummy LocalTimeProfRecord(name, _STATIC_FUNCTION_HASH_VALUE_ );
#define DECLARE_FUN_TIME_PROF()  DECLARE_TIME_PROF(__FUNCTION__)
#else
#define DECLARE_TIME_PROF(name_)   
#define DECLARE_FUN_TIME_PROF()  DECLARE_TIME_PROF(__FUNCTION__)
#endif

#endif

#endif
