#ifndef _TIME_SPAN_H_
#define _TIME_SPAN_H_


//�����һ����������ģ��
struct CTimerElement
{
	unsigned int hKey; //���ֵ�hashֵ
	int      nLine;    //�к�
	//const char*  funcName; //����������
	char funcName[33];	// ��������
	int64_t nTimes;    //ִ�е��ܴ���
	int64_t nTotalTick; //ִ�е���ʱ��
	int64_t nMaxTick; //����ִ��ʱ��
	int64_t nLastTick; //��һ�ε�ʱ��
	int64_t nLocalMaxTick; //����ͳ�����ڵ�ʱ��
	int64_t nLocalMinTick; //������ִ�е���С��ʱ
	int64_t nPeriodStartTick;  //�����ڿ�ʼ��ʱ��

	CTimerElement()
	{
		funcName[0] = 0;
		nPeriodStartTick  = 0;
	}
	CTimerElement(const CTimerElement &rhs)
	{
		hKey = rhs.hKey;
		nLine = rhs.nLine;
		nTimes = rhs.nTimes;
		nTotalTick = rhs.nTotalTick;
		nMaxTick = rhs.nMaxTick;
		nLastTick = rhs.nLastTick;
		nLocalMaxTick = rhs.nLocalMaxTick;
		nLocalMinTick = rhs.nLocalMinTick;
		
		//nPeriodTimes = rhs.nPeriodTimes;		
		memcpy(funcName, rhs.funcName, sizeof(funcName));
	}
};

//ʱ��Ĺ�����,���ڹ��������ʹ�õ�ʱ������
class CTimeStatisticMgr
{
public:
	typedef Vector<CTimerElement, 4096> TimeData;
	CTimeStatisticMgr(){}
	~CTimeStatisticMgr()
	{
		m_elements.empty();
	}

	/*
	* Comments: ���ʱ���ͳ����
	* Param unsigned int nKey: hashֵ
	* Param int nLine: �к�
	* Param const char* name: ����������
	* Param int64_t tick: ���ĵ�ʱ��
	* Param int64_t nCurrentTick: ��ǰ��ʱ��
	* @Return void:
	*/
	void AddStatictic(unsigned int nKey, int nLine, const char* name, int64_t tick, int64_t nCurrentTick);
	
	//��ȡʱ������
	TimeData & GetTimeStaticData()
	{
		return m_elements;
	}

	//�����ĵ�ʱ���¼����־����ڷ���
	bool LogTimeFile();
	

private:
	TimeData m_elements;
};

//ʱ��ͳ�Ƶ���,

class CTimeSpan
{
public:
	CTimeSpan( const char* name,int nLine,unsigned int key, unsigned int nMinStatTime = 0, bool bInnerHash = false)
	{
		//m_func = name;
		size_t nLen = __min(strlen(name), 32);
		memcpy(m_funName, name, nLen * sizeof(char));
		m_funName[nLen] = 0;		
		m_line = nLine;
		m_tick = _getTickCount();
		m_key = key;		
		m_nMinStatTime = nMinStatTime;
		m_bInnerHash = bInnerHash;	
	}
	~CTimeSpan()
	{
		if (g_mgr)
		{
			int64_t nCurrentTick = _getTickCount();
			int64_t ellapse = nCurrentTick- m_tick;			
			if ( ellapse >= m_nMinStatTime)
			{
				if ( m_bInnerHash )
					m_key = hashstr(m_funName);
				g_mgr->AddStatictic(m_key,m_line,m_funName,ellapse,nCurrentTick); 
			}
		}
	}
public:
	static CTimeStatisticMgr* g_mgr; //������
private:
	int64_t m_tick; //���ѵ�ʱ��
	
	char	 m_funName[33]; // ��������
	int       m_line;  //����
	unsigned  int  m_key; //ֻ��һ��
	unsigned int m_nMinStatTime; // ��Сͳ�Ƽ�¼ʱ��	
	bool		m_bInnerHash; // �Ƿ��ڲ�����hashֵ
};

//���ﶨ��һ����̬������ֻ����һ�Σ�Ϊ�˱���hashֵÿ�ζ�ȥ����
/*
#define SF_TIME_CHECK()  static unsigned int _STATIC_FUNCTION_HASH_VALUE_= CLVariant::hashstr(__FUNCTION__); \
	CTimeSpan CTimeSpanLoalInst##__FUNCTION__##__LINE__(__FUNCTION__, __LINE__,_STATIC_FUNCTION_HASH_VALUE_ ) 

#define SF_TIME_CHECK_NAME(fn, minStatTime) static unsigned int _STATIC_FUNCTION_HASH_VALUE_= CLVariant::hashstr(__FUNCTION__"_"#fn); \
	CTimeSpan CTimeSpanLoalInst##__FUNCTION__##__LINE__(fn, __LINE__,_STATIC_FUNCTION_HASH_VALUE_, minStatTime, true); 
*/
#define SF_TIME_CHECK() 
#define SF_TIME_CHECK_NAME(fn, minStatTime)

#endif

