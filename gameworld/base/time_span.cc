#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "time_span.h"
using namespace stream;
CTimeStatisticMgr * CTimeSpan::g_mgr = NULL;
void CTimeStatisticMgr::AddStatictic(unsigned int nKey,int nLine,const char* name, int64_t tick,int64_t nCurrentTick)
{
		
	CTimerElement * pElement = NULL;
	//查找的依据是函数名字的hash和行号一样，这样基本能保证100%唯一性了
	for (int i=0; i < m_elements.count(); i++)
	{
		if (m_elements[i].hKey ==nKey && nLine == m_elements[i].nLine ) //找到了
		{
			pElement = &m_elements[i];
			break;
		}
	}
	//如果是新加的元素的就初始化这些数据
	if (pElement == NULL)
	{
		CTimerElement element;
		//element.funcName = name;
		size_t nLen = __min(strlen(name), 32);
		memcpy(element.funcName, name, nLen * sizeof(char));
		element.funcName[nLen] = 0;
		element.hKey= nKey;
		element.nLine= nLine;
		element.nMaxTick=tick;
		element.nLastTick = tick;
		element.nLocalMaxTick =tick;
		element.nTotalTick = tick;
		element.nTimes = 1;
		element.nLocalMaxTick =tick;
		element.nLocalMinTick =tick;
		m_elements.add(element);
	}
	else
	{
		pElement->nTotalTick += tick; //总时间++
		if (tick > pElement->nMaxTick ) // 最大时间
		{
			pElement->nMaxTick = tick;
		}
		if (tick > pElement->nLocalMaxTick)
		{
			pElement->nLocalMaxTick = tick; 
		}
		if (tick && tick <  pElement->nLocalMinTick )
		{
			 pElement->nLocalMinTick = tick;
		}
		pElement->nLastTick = tick;
		pElement->nTimes ++; 
		//每个局部的统计周期为1分钟
		if (nCurrentTick -  pElement->nPeriodStartTick > 60000 ) //60分钟为一个统计周期
		{
			pElement->nPeriodStartTick =nCurrentTick;
			pElement->nLocalMinTick =tick; 
			pElement->nLocalMaxTick =tick;
		}
	}
	
}

bool CTimeStatisticMgr::LogTimeFile()
{
	SystemTime Systime;
	GetSystemTime(Systime);
	char sFileName[16];

	_STRNCPY_A(sFileName, ("perfermance.txt") );
	char buff[512];
	
	FileStream stm(sFileName, FileStream::faWrite | FileStream::faCreate,FileStream::AlwaysCreate, NULL);
	//sprintf( buff,"total	max	times	lMin	lMax	last	func");
	sprintf(buff, "%-13s%-13s%-13s%-13s%-13s%-13s%-20s\r\n","total", "max", "times", "lMin", "lMax", "last", "func");
	OutputMsg(rmTip,buff );
	stm.write(buff,strlen(buff));	
	for (int i=0; i< m_elements.count(); i++)
	{
		if (m_elements[i].nTimes <= 0 )
		{
			continue;
		}
#ifdef _MSC_VER
		sprintf( buff,"%-13I64d%-13I64d%-13I64d%-13I64d%-13I64d%-13I64d%-20s",
			(Uint64)m_elements[i].nTotalTick,(Uint64)m_elements[i].nMaxTick,
			(Uint64)m_elements[i].nTimes, (Uint64)m_elements[i].nLocalMinTick,
			(Uint64)m_elements[i].nLocalMaxTick,(Uint64)m_elements[i].nLastTick,
			m_elements[i].funcName);
#else
		sprintf( buff,"%-13lld%-13lld%-13lld%-13lld%-13lld%-13lld%-20s",
			(long long int)m_elements[i].nTotalTick,(long long int)m_elements[i].nMaxTick,
			(long long int)m_elements[i].nTimes, (long long int)m_elements[i].nLocalMinTick,
			(long long int)m_elements[i].nLocalMaxTick,(long long int)m_elements[i].nLastTick,
			m_elements[i].funcName);
#endif
		OutputMsg(rmTip,buff );
		stm.write(buff,strlen(buff));
		stm.write(" \r\n",4);
	}
	//OutputMsg(rmTip, (" log performance log %s"),sFileName );
	return true;
}

