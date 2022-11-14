#ifndef _TIME_STAT_H_
#define _TIME_STAT_H_
#ifdef _MSC_VER
//////////////////////////////////////////////////////////////////////////
//							ʱ��ͳ�Ʒ�����
// ��	�ܣ�����׷�ٳ����е��õĺ���ִ��ʱ�������������λ������ƿ��
// ˵	����ͳ�ư����趨�õ�ʱ���������������2�������һ�Σ������к�������
//			�ڵ���Ϣ�������ν�������֣����л����ļ����������Կ��ٵķ�����
//			2�����ڣ�ÿ��ִ�е�Ԫ�����˶��ʱ�䣬�ҳ�ƿ�����ڡ�
// ���磺���߼��̣߳����߼��߳�ÿ��ѭ����һ��׷�ٽڵ㣬����������紦��ʵ���������
//		 �����������ȵȶ�����׷�ٽڵ㣬����������ϸ�ĸ��ٵ�ÿ���ڵ��ʱռ������ʱ��
//		 ������
//			��Ϊ�߼����汾���ȡ��ʱ����ÿ���ӣ����ӣ���Ԫ��������ִ��ʱ�䣬�����Ͷ�
//		 ͳ�Ʒ�����Ӱ�죡�������������ʵ�������ˢ��ռ��ÿ������50%���ҵ�ʱ�䣬���
//		 ��Ϊ��ʱ������ʵ��ˢ�³����⣬Ҳ��ⲻ����������
//			���ڴ����⣬Ҫô����ʱ���˷�ʱ��Ҫô����ʵ��������ڲ����÷�ʱ׷�ٽ�㡣
//////////////////////////////////////////////////////////////////////////

#include <new>
//#include "ObjectCounter.h"
class TimeProfDummy
{
public:
	TimeProfDummy(const char* szUnitName, unsigned int nHashCode);
	~TimeProfDummy();
};

// ִ��ʱ���¼�ڵ�
class TimeProfRecord
{
public:
	enum
	{
		MAX_EXEC_UNIT_NAME_LEN	= 64,								// ���ִ�е�Ԫ����
	};
	TimeProfRecord(){}
	TimeProfRecord(const char* szUnitName, unsigned int nHashCode);
	~TimeProfRecord();
	//���ýڵ�����
	void setName(const char* szName);
	// ���һ����ִ�н��
	inline void addChild(TimeProfRecord* record)
	{
		m_childrenNode.add(record);
	}
	// ��ѯ�ڵ�
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
	// ������ִ��ʱ����ϸ��Ϣ
	void dump(stream::BaseStream& stream, int level = 0);
	// ���ýڵ�����
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

	//�ַ���hash��������Ҫ�ṩ����
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
	unsigned int				m_nNameHashCode;							// ����Hash��
	unsigned long long			m_nTotalCount;								// ִ�д���
	unsigned long long			m_nOccuTotalCount;							// �ۻ�ִ�д���
	unsigned long long			m_nMaxTime;									// ����ͳ�����ִ�к�ʱ
	unsigned long long			m_nMinTime;									// ����ͳ����Сִ�к�ʱ
	unsigned long long			m_nOccuMaxTime;								// �ۻ������ִ�к�ʱ
	unsigned long long			m_nOccuMinTime;								// �ۻ�����Сִ�к�ʱ
	unsigned long long			m_nTotalTime;								// ����ִ�к�ʱ������ͳ��ƽ����ʱ��
	unsigned long long			m_nOccuTotalTime;							// �ۻ�ִ��ʱ��
	unsigned long long			m_nStartTime;								// ��ʼִ��ʱ��	
	unsigned long long			m_nEndTime;									// ����ִ��ʱ��
	char						m_szExecUnitName[MAX_EXEC_UNIT_NAME_LEN];	// ִ�е�λ����	
	container::Vector<TimeProfRecord*>		m_childrenNode;		// �����ӽڵ��б�
};


// ִ��ʱ�������
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

	// ��ʼִ�м�ʱ
	inline void OnTimeProfRecordStart(TimeProfRecord *record)
	{
		m_execUnitStack.push(record);
	}
	// ����ִ�м�ʱ
	inline void OnTimeProfRecordEnd(TimeProfRecord *)
	{
		m_execUnitStack.pop();		
	}

	// ��ȡ��ǰִ�е�Ԫ���
	inline TimeProfRecord* getCurrTimeProfRecord()
	{
		int count = m_execUnitStack.count();
		if (count > 0)
			return m_execUnitStack[count-1];

		return NULL;
	}

	// ������ִ��ʱ����ϸ��Ϣ
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
	// ���ʱ��ͷ
	void dumpDateTimeHeader(stream::BaseStream& stream);
	// ����ָ���
	void dumpDateTimeSep(stream::BaseStream& stream);
	// ��ȡ��ǰʱ��
	void getCurrentTm(tm &t);
	// dump
	void dumpImpl(stream::BaseStream& stream);
	// ��ʽ��ʱ��
	void formatTimeStr(char* szDataBuff, size_t nLen, tm *t);
	// ִ��һ�η��䣨ÿ�η���ALLOC_RECORD_NUM����
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
	// �����߳�Id
	inline void setThreadId(DWORD dwThreadId) { m_dwThreadId = dwThreadId; }

protected:
	container::Vector<TimeProfRecord *>	m_execUnitStack;	// ִ�е�Ԫ���ջ
	TimeProfRecord									m_execUnitRoot;		// ִ�е�Ԫ���ĸ��ڵ�	
	tm												m_lastDumpTime;		// �ϴ�dump����ʱ��
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
