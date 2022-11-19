#ifdef _MSC_VER
#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include <_ast.h>

#include <x_thread.h>

#include <x_lock.h>
#include <x_tick.h>

#include <stream.h>
#include <wrand.h>
#include <time.h>

#include <container/vector.h>
#include <x_lock.h>
#include "second_time.h"



//#include <LinkedList.h>

#include "time_stat.h"
static const char s_szLogFileName[] = ("TimeStat.xml");
static const char* s_szTimeProfIndent[] = {
	(""),									// level_1
	("  "),								// level_2
	("    "),								// level_3
	("      "),							// level_4
	("        "),							// level_5
	("          "),						// level_6
	("            "),						// level_7
	("              "),					// level_8
	("                "),					// level_9
	("                  "),				// level_10
	("                    "),				// level_11
	("                      "),			// level_12
	("                        "),			// level_13
	("                          "),		// level_14
	("                            ")		// level_15
};
const char s_szSep[] = ("-------------------------------------------------------------------------------------------\r\n");
const char s_szStartRecordsLabel[] = ("<Records>\r\n");
const char s_szEndRecordsLabel[] = ("</Records>\r\n");
const char s_szStartProfRecord[] = ("<ProfRecord timeSpan=\"");
const char s_szEndProfRecord[] = ("</ProfRecord>\r\n");
const char s_szThreadLabel[] = (" threadId=%d");
const char szXmlEndLable[] = ("\">\r\n");
DWORD TimeProfMgr::s_dwTlsIdx = TLS_OUT_OF_INDEXES;

TimeProfDummy::TimeProfDummy(const char* szUnitName, unsigned int nHashCode)
{
	TimeProfMgr& profMgr = *TimeProfMgr::getSingleton().getThreadInst();
	TimeProfRecord *pCurRecord = profMgr.getCurrTimeProfRecord();
	if (pCurRecord)
	{
		TimeProfRecord* pChild = pCurRecord->getChildByHash(nHashCode);
		if (!pChild)
		{	
			pChild = profMgr.allocRecord();
			pChild->reInitBasicData(szUnitName, nHashCode);			
			pCurRecord->addChild(pChild);
		}
		pChild->startProf();
		profMgr.OnTimeProfRecordStart(pChild);
	}
}
TimeProfDummy::~TimeProfDummy()
{
	TimeProfMgr& mgr = *TimeProfMgr::getSingleton().getThreadInst();
	TimeProfRecord *pCurRecord = mgr.getCurrTimeProfRecord();
	pCurRecord->endProf();	
	mgr.OnTimeProfRecordEnd(pCurRecord);	
}

void TimeProfRecord::dump(stream::BaseStream& stream, int level)
{	
	level = level >= (int)(ArrayCount(s_szTimeProfIndent)) ? (int)(ArrayCount(s_szTimeProfIndent)-1) : level;
	stream.write(s_szTimeProfIndent[level], strlen(s_szTimeProfIndent[level])*sizeof(char));
	char szData[512] = {0};
	float nAvgTime = 0;	
	if (m_nTotalCount > 0)
		nAvgTime = (float)m_nTotalTime / m_nTotalCount;
	SNPRINTFA(szData, sizeof(szData), ("<%s ttime=\"%I64u\" tcount=\"%I64u\" atime=\"%f\" maxtime=\"%I64u\" mintime=\"%I64u\" ottime=\"%I64u\" otcount=\"%I64u\" omaxtime=\"%I64u\" omintime=\"%I64u\">\r\n"), 
		m_szExecUnitName,m_nTotalTime, m_nTotalCount, nAvgTime, m_nMaxTime, m_nMinTime, 
		m_nOccuTotalTime, m_nOccuTotalCount, m_nOccuMaxTime, m_nOccuMinTime);
	stream.write(szData, strlen(szData) * sizeof(szData[0]));
	reset();
	for (int i = 0; i < m_childrenNode.count(); i++)
		m_childrenNode[i]->dump(stream, level+1);	
	SNPRINTFA(szData, sizeof(szData), ("%s</%s>\r\n"), s_szTimeProfIndent[level], m_szExecUnitName);
	stream.write(szData, strlen(szData) * sizeof(szData[0]));
}

void TimeProfRecord::setName(const char* szName)
{
	_STRNCPY_A(m_szExecUnitName, szName);
}

TimeProfRecord::TimeProfRecord(const char*, unsigned int)
{	
}

TimeProfRecord::~TimeProfRecord(){
	clear();
}

void TimeProfRecord::clear()
{
	for (int i = 0; i < m_childrenNode.count(); i++)
	{
		TimeProfRecord *pRecord = m_childrenNode[i];
		
		pRecord->clear();
		TimeProfMgr::getSingleton().getThreadInst()->freeRecord(pRecord);
	}		
	m_childrenNode.empty();
}

TimeProfMgr::TimeProfMgr() : m_execUnitRoot("", 0), m_dwThreadId(0)
{
	//::timeBeginPeriod(1);
	m_execUnitRoot.setName("Root");
	m_execUnitRoot.reset(true);
	m_execUnitStack.reserve(500);
	getCurrentTm(m_lastDumpTime);	
	m_execUnitStack.push(&m_execUnitRoot);

	m_freeRecordList.reserve(500);
	allocTimeProfRecord();
}

TimeProfMgr::~TimeProfMgr()
{
	//::timeEndPeriod(1);	
	clear();
}

void TimeProfMgr::getCurrentTm(tm &t)
{
	time_t      szClock;	
	time(&szClock);
	struct tm   *curTime = localtime(&szClock);
	t = *curTime;
}

void TimeProfMgr::dumpImpl(stream::BaseStream& stream)
{
	dumpDateTimeHeader(stream);
	m_execUnitRoot.dump(stream);
	stream.write(s_szEndProfRecord, strlen(s_szEndProfRecord)*sizeof(char));
}

void TimeProfMgr::dump()
{	
	using namespace stream;
	FileStream fs(s_szLogFileName, FileStream::faWrite, FileStream::AlwaysOpen, NULL);
	int fileSize = fs.getSize();
	bool bFirstTime = true;
	if (fileSize > (LONGLONG)(strlen(s_szEndProfRecord)*sizeof(char)))
	{
		bFirstTime = false;
		fileSize -= (int)(strlen(s_szEndRecordsLabel)*sizeof(char));
		fs.setPosition(fileSize);
	}
	else
	{
		fs.setPosition(fileSize);
		fs.write(s_szStartRecordsLabel, strlen(s_szStartRecordsLabel)*sizeof(char));
	}
	for (int i = 0; i < m_vecTimeProfMgr.count(); i++)
	{
		m_vecTimeProfMgr[i]->dumpImpl(fs);
	}
	////dumpDateTimeSep(fs);
	//dumpDateTimeHeader(fs);
	//m_execUnitRoot.dump(fs);
	//fs.write(s_szEndProfRecord, strlen(s_szEndProfRecord)*sizeof(char));
	////dumpDateTimeSep(fs);	
	fs.write(s_szEndRecordsLabel, strlen(s_szEndRecordsLabel)*sizeof(char));	
}

void TimeProfMgr::dumpDateTimeHeader(stream::BaseStream& stream)
{	
	char szBeginDateTime[256] = {0};
	formatTimeStr(szBeginDateTime, ArrayCount(szBeginDateTime)-1, &m_lastDumpTime);
	szBeginDateTime[ArrayCount(szBeginDateTime)-1] = ('\0');		
	stream.write(s_szStartProfRecord, strlen(s_szStartProfRecord)*sizeof(char));
	stream.write(szBeginDateTime, strlen(szBeginDateTime) * sizeof(char));	
	stream.write("--", 2);

	char szDateTime[256] = {0};
	getCurrentTm(m_lastDumpTime);
	formatTimeStr(szDateTime, ArrayCount(szDateTime)-1, &m_lastDumpTime);
	szDateTime[ArrayCount(szDateTime)-1] = ('\0');
	stream.write(szDateTime, strlen(szDateTime) * sizeof(char));	

	// dump thread id	
	char szThreadInfo[64] = {0};
	SNPRINTFA(szThreadInfo, sizeof(szThreadInfo), s_szThreadLabel, m_dwThreadId);
	stream.write(szThreadInfo, strlen(szThreadInfo) * sizeof(char));	
	stream.write(szXmlEndLable, strlen(szXmlEndLable) * sizeof(char));
}

void TimeProfMgr::formatTimeStr(char* szDataBuff, size_t nLen, tm *t)
{
	//_tcsftime(szDataBuff, nLen-1, ("%Y-%m-%d_%H:%M:%S"), t);	
	SNPRINTFA(szDataBuff, (int)(nLen - 1), "%d-%d-%d_%d:%d:%d", t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

void TimeProfMgr::dumpDateTimeSep(stream::BaseStream& stream)
{
	stream.write(s_szSep, strlen(s_szSep) * sizeof(char));
}

#endif
