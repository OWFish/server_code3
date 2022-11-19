#ifndef _TIME_SPAN_H_
#define _TIME_SPAN_H_


//这个是一个管理器的模块
struct CTimerElement
{
	unsigned int hKey; //名字的hash值
	int      nLine;    //行号
	//const char*  funcName; //函数的名字
	char funcName[33];	// 函数名称
	int64_t nTimes;    //执行的总次数
	int64_t nTotalTick; //执行的总时间
	int64_t nMaxTick; //最大的执行时间
	int64_t nLastTick; //上一次的时间
	int64_t nLocalMaxTick; //本次统计周期的时间
	int64_t nLocalMinTick; //被周期执行的最小的时
	int64_t nPeriodStartTick;  //本周期开始的时间

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

//时间的管理器,用于管理各函数使用的时间的情况
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
	* Comments: 添加时间的统计器
	* Param unsigned int nKey: hash值
	* Param int nLine: 行号
	* Param const char* name: 函数的名字
	* Param int64_t tick: 消耗的时间
	* Param int64_t nCurrentTick: 当前的时间
	* @Return void:
	*/
	void AddStatictic(unsigned int nKey, int nLine, const char* name, int64_t tick, int64_t nCurrentTick);
	
	//获取时间数据
	TimeData & GetTimeStaticData()
	{
		return m_elements;
	}

	//将消耗的时间记录在日志里，便于分析
	bool LogTimeFile();
	

private:
	TimeData m_elements;
};

//时间统计的类,

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
	static CTimeStatisticMgr* g_mgr; //管理器
private:
	int64_t m_tick; //花费的时间
	
	char	 m_funName[33]; // 函数名称
	int       m_line;  //行数
	unsigned  int  m_key; //只算一次
	unsigned int m_nMinStatTime; // 最小统计记录时间	
	bool		m_bInnerHash; // 是否内部计算hash值
};

//这里定义一个静态变量，只计算一次，为了避免hash值每次都去计算
/*
#define SF_TIME_CHECK()  static unsigned int _STATIC_FUNCTION_HASH_VALUE_= CLVariant::hashstr(__FUNCTION__); \
	CTimeSpan CTimeSpanLoalInst##__FUNCTION__##__LINE__(__FUNCTION__, __LINE__,_STATIC_FUNCTION_HASH_VALUE_ ) 

#define SF_TIME_CHECK_NAME(fn, minStatTime) static unsigned int _STATIC_FUNCTION_HASH_VALUE_= CLVariant::hashstr(__FUNCTION__"_"#fn); \
	CTimeSpan CTimeSpanLoalInst##__FUNCTION__##__LINE__(fn, __LINE__,_STATIC_FUNCTION_HASH_VALUE_, minStatTime, true); 
*/
#define SF_TIME_CHECK() 
#define SF_TIME_CHECK_NAME(fn, minStatTime)

#endif

