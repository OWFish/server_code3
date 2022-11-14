#include <stdio.h>
#include "os_def.h"
#include <_ast.h>
#include "share_util.h"
#include <x_tick.h>
#include <container/vector.h>
#include <ref_class.hpp>
#include <ref_string.hpp>
#include <stream.h>
#include "share_util.h"
#include "luabase/clvariant.h"
#include "luabase/lua_pre_process.h"
#include <ctype.h>

using namespace container;
using namespace string;
using namespace stream;


LuaPreProcessor::LuaPreProcessor(BaseAllocator* alloc)
	: Inherited(alloc)
{
}

LuaPreProcessor::~LuaPreProcessor()
{
	clearIncludedFileList();
	clearIncludeDirectory();
	clearMacroList();
}

inline bool fileExists(const char* sFilePath)
{
#ifdef _MSC_VER
	DWORD dwAttr = GetFileAttributes(sFilePath);

	if (dwAttr == INVALID_FILE_ATTRIBUTES)
		return false;

	if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
		return false;

	return true;
#else
	if(!access(sFilePath, F_OK))  
	{  
		return true;
	}  
	else  
	{  
		return false;
	}  
#endif
}

const char* getFileNamePart(const char* sFullFilePath)
{
	const char* sRet = sFullFilePath;

	while (*sFullFilePath)
	{
		if (*sFullFilePath == '/' || *sFullFilePath == '\\')
			sRet = sFullFilePath + 1;

		sFullFilePath++;
	}

	return sRet;
}

const char* LuaPreProcessor::parse(const char* sSourceText, const char* sFilePath, const char cNewLine)
{
	seek(0, SEEK_SET);
	m_ConditionList.clear();//清空条件表
	m_LineRangeList.clear();//清空源文件行号表
	m_nLineNo = 1;
	m_NewLineChar = cNewLine;
	m_boErrorAbort = false;
	m_boCurrCondition = true;
	clearIncludedFileList();
	return SaveFileDirAndParse(sSourceText, sFilePath);
}

const char* LuaPreProcessor::ParseSource(const char* sSourceText)
{
	size_t dwPos = getPosition();
	char* sLine = NULL;
	size_t dwMaxLineLen = 0, dwLineLen;
#ifdef _MSC_VER
	__try
#endif
	{
		//跳过UTF-8 BOM
		if ((*(int*)sSourceText & 0x00FFFFFF) == 0xBFBBEF)
			sSourceText += 3;

		m_ParseEnvir.sParsePtr = sSourceText;
		m_ParseEnvir.nLineNo = 1;

		while (*m_ParseEnvir.sParsePtr && !m_boErrorAbort)
		{
			m_ParseEnvir.sNewLinePtr = strchr(m_ParseEnvir.sParsePtr, m_NewLineChar);

			//定位新行位置
			if (m_ParseEnvir.sNewLinePtr)
			{
				m_ParseEnvir.sLineEndPtr = m_ParseEnvir.sNewLinePtr - 1;
				m_ParseEnvir.sNewLinePtr++;//调过新行字符
			}
			else
			{
				m_ParseEnvir.sNewLinePtr = m_ParseEnvir.sParsePtr + strlen(m_ParseEnvir.sParsePtr);
				m_ParseEnvir.sLineEndPtr = m_ParseEnvir.sNewLinePtr - 1;
			}

			//定位当前行尾，调过\n\r以及制表符
			while (m_ParseEnvir.sLineEndPtr >= m_ParseEnvir.sParsePtr && (UINT_PTR)*m_ParseEnvir.sLineEndPtr < 0x20)
			{
				m_ParseEnvir.sLineEndPtr--;
			}

			if (m_ParseEnvir.sLineEndPtr >= m_ParseEnvir.sParsePtr)
			{
				//终止行尾有效字符之后的后一个字符
				m_ParseEnvir.sLineEndPtr++;
				dwLineLen = m_ParseEnvir.sLineEndPtr - m_ParseEnvir.sParsePtr;

				//分析并处理文本行，如果前3个字符预处理指令字符（--#）则进行预处理，否则直接写入文本内容
				if ((*(int*)m_ParseEnvir.sParsePtr & 0x00FFFFFF) == MAKEFOUR('-', '-', '#', 0))
				{
					//拷贝行内容
					if (dwLineLen > dwMaxLineLen)
					{
						sLine = (char*)realloc(sLine, sizeof(*sLine) * (dwLineLen + 1));
						dwMaxLineLen = dwLineLen;
					}

					memcpy(sLine, m_ParseEnvir.sParsePtr, dwLineLen * sizeof(*sLine));
					sLine[dwLineLen] = 0;
					//保存当前行索引
					int nLineNoBefore = m_nLineNo;
					//执行行预处理语句
					ProcessLine(sLine);

					//在预处理指令没有写入新内容的情况下，必须写入一个空行占据改预处理行，才能使得预处理后的行号能够与源文件匹配
					if (nLineNoBefore == m_nLineNo)
					{
						//在代码中写入换行符
						write(&m_NewLineChar, sizeof(char));
						//调整行号
						m_nLineNo++;
					}
				}
				else if (m_boCurrCondition)  //只能在预处理条件为true的情况下写入文本
				{
					write(m_ParseEnvir.sParsePtr, dwLineLen * sizeof(*m_ParseEnvir.sParsePtr));
					//在代码中写入换行符
					write(&m_NewLineChar, sizeof(char));
					//调整行号
					m_nLineNo++;
				}
			}
			else
			{
				//在代码中写入换行符
				write(&m_NewLineChar, sizeof(char));
				//调整行号
				m_nLineNo++;
			}

			//将输入处理指针调整到下一行
			m_ParseEnvir.sParsePtr = m_ParseEnvir.sNewLinePtr;
			m_ParseEnvir.nLineNo++;//调整原始文件行号
		}
	}
#ifdef _MSC_VER
	__finally
#endif
	{
		free(sLine);
	}

	if (m_boErrorAbort)
		return NULL;

	return (getSize() > 0) ? (const char*)getMemory() + dwPos : ("");
}

void LuaPreProcessor::clearIncludeDirectory()
{
	for (int i = m_IncludeDirList.count() - 1; i > -1; --i)
	{
		delete m_IncludeDirList[i];
	}

	m_IncludeDirList.clear();
}

void LuaPreProcessor::addMacro(const char* sName, const char* sValue /* = NULL */)
{
	//如果宏存在则替换，否则则添加新的宏对象
	PPREPROC_MACRO pMacro = getMacro(sName);

	if (pMacro)
	{
		showErrorFormat("Macro %s Redefine and replaced", sName);
		pMacro->sValue[0] = 0;

		if (sValue)
		{
			_STRNCPY_A(pMacro->sValue, sValue);
		}
	}
	else
	{
		PREPROC_MACRO macro;
		_STRNCPY_A(macro.sName, sName);
		macro.sValue[0] = 0;

		if (sValue)
		{
			_STRNCPY_A(macro.sValue, sValue);
		}

		m_MacroList.add(macro);
	}
}

void LuaPreProcessor::removeMacro(const char* sName)
{
	for (int i = m_MacroList.count() - 1; i > -1; --i)
	{
		if (strcmp(m_MacroList[i].sName, sName) == 0)
		{
			m_MacroList.remove(i);
		}
	}
}

void LuaPreProcessor::clearMacroList()
{
	m_MacroList.clear();
}

int LuaPreProcessor::getLineRangeData(LineRange* pLineRange, int nCount)
{
	if (!pLineRange)
		return m_LineRangeList.count();

	if (nCount >= m_LineRangeList.count())
		nCount = m_LineRangeList.count();

	memcpy(pLineRange, &m_LineRangeList[0], nCount * sizeof(m_LineRangeList[0]));
	return nCount;
}

const char* LuaPreProcessor::getSourceLineNumber(int nLineNo, int& nSrcLineNo)
{
	return m_LineRangeList.getSourceLineNumber(nLineNo, nSrcLineNo);
}

const LuaPreProcessor::PPREPROC_MACRO LuaPreProcessor::getMacro(const char* sName)
{
	for (int i = m_MacroList.count() - 1; i > -1; --i)
	{
		if (strcmp(m_MacroList[i].sName, sName) == 0)
		{
			return &m_MacroList[i];
		}
	}

	return NULL;
}

void LuaPreProcessor::ProcessLine(const char* sLineText)
{
	int nIdx = 0;
	char sDirective[128];

	//取得预处理指令以及指令内容
	sLineText += 3;//调过--#

	while (nIdx < (int)sizeof(sDirective) - 1)
	{
		if (*sLineText == 0 || (UINT_PTR)*sLineText <= 0x20)
		{
			break;
		}

		sDirective[nIdx] = *sLineText;
		sLineText++;
		nIdx++;
	}

	if (nIdx > 0)
	{
		sDirective[nIdx] = 0;

		//调过预处理指令数据部分开头的不可见字符
		while (*sLineText && (UINT_PTR)*sLineText <= 0x20)
			sLineText++;

		//执行预处理指令
		ProcessDirective(sDirective, sLineText);
	}
}

void LuaPreProcessor::ProcessDirective(const char* sDirective, const char* sData)
{
	//代码文件包含指令--#include
	if (STRNCASECMP(sDirective, ("include"), 7) == 0)
	{
		if (m_boCurrCondition == true)
			DirectiveOfInclude(sData);
	}
	//宏定义指令--#define
	else if (STRNCASECMP(sDirective, ("define"), 6) == 0)
	{
		if (m_boCurrCondition == true)
			DirectiveOfDefine(sData);
	}
	//取消宏定义指令--#undef
	else if (STRNCASECMP(sDirective, ("undef"), 5) == 0)
	{
		if (m_boCurrCondition == true)
			DirectiveOfUndef(sData);
	}
	//条件指令--#ifdef
	else if (STRNCASECMP(sDirective, ("ifdef"), 5) == 0)
	{
		DirectiveOfIfdef(sData);
	}
	//条件指令--#ifndef
	else if (STRNCASECMP(sDirective, ("ifndef"), 6) == 0)
	{
		DirectiveOfIfndef(sData);
	}
	//条件指令--#if
	else if (STRNCASECMP(sDirective, ("if"), 2) == 0)
	{
		DirectiveOfIf(sData);
	}
	//条件指令--#else
	else if (STRNCASECMP(sDirective, ("else"), 4) == 0)
	{
		DirectiveOfElse(sData);
	}
	//条件指令--#elif
	else if (STRNCASECMP(sDirective, ("elif"), 4) == 0)
	{
		DirectiveOfElif(sData);
	}
	//条件指令--#endif
	else if (STRNCASECMP(sDirective, ("endif"), 5) == 0)
	{
		DirectiveOfEndif(sData);
	}
	else
	{
		showErrorFormat(("invalid directive %s"), sData);
		abort();
	}
}

void LuaPreProcessor::DirectiveOfInclude(const char* data)
{
	char fn[1024];

	if (!m_boCurrCondition)
		return;

	//取出包含文件中引号之内的文件名称
	if (*data != '"')
		return;

	data++;

	if (*data == '"')
		return;

	const char* ptr = strchr(data, '"');

	if (!ptr) return;

	//将文件名拷贝到sFile缓冲区中
	size_t size = ptr - data;

	size = __min(sizeof(fn) - 1, size + 1);
	_STRNCPY_S(fn, data, size);
	fn[size] = 0;

	//定位到包含限定词的位置
	while (*ptr)
	{
		if (*ptr == 0x20 || *ptr == 0x09)
		{
			do
			{
				ptr++;
			}
			while (*ptr == 0x20 || *ptr == 0x09);

			break;
		}

		ptr++;
	}
	char* sPtr1 = fn;
	while (*sPtr1)
	{
		if (*sPtr1 == '\\')
		{
			*sPtr1 = '/';
		}
		*sPtr1 = (char)tolower(*sPtr1);
		sPtr1++;
	}
	SearchAndLoadIncludeFile(fn, STRNCASECMP(ptr, ("once"), 4) != 0);
}

void LuaPreProcessor::DirectiveOfDefine(const char* sData)
{
	if (!m_boCurrCondition)
		return;

	PPToken sTokens[2];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 2)
		addMacro(sTokens[0], sTokens[1]);
	else if (nCount >= 1)
		addMacro(sTokens[0]);
	else
	{
		showError(("missing macro name"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfUndef(const char* sData)
{
	if (!m_boCurrCondition)
		return;

	PPToken sTokens[1];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 1)
		removeMacro(sTokens[0]);
	else
	{
		showError(("missing macro name on #undef"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfIfdef(const char* sData)
{
	PPToken sTokens[1];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 1)
	{
		m_ConditionList.add(getMacro(sTokens[0]) != NULL);
		refreshCondition();
	}
	else
	{
		showError(("missing macro name on #ifdef"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfIfndef(const char* sData)
{
	PPToken sTokens[1];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 1)
	{
		m_ConditionList.add(getMacro(sTokens[0]) == NULL);
		refreshCondition();
	}
	else
	{
		showError(("missing macro name on #ifndef"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfIf(const char* sData)
{
	PPToken sTokens[3];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 3)
	{
		PPREPROC_MACRO pMacro = getMacro(sTokens[0]);

		if (pMacro)
		{
			if (strcmp(("=="), sTokens[1]) == 0)
			{
				m_ConditionList.add(strcmp(pMacro->sValue, sTokens[2]) == 0);
				refreshCondition();
			}
			else if (strcmp(("!="), sTokens[1]) == 0)
			{
				m_ConditionList.add(strcmp(pMacro->sValue, sTokens[2]) != 0);
				refreshCondition();
			}
			else
			{
				showErrorFormat(("invalid macro compare operator %s, default is false"), sTokens[1]);
				abort();
			}
		}
		else
		{
			showErrorFormat(("macro %s was not defined, default comparison is false"), sTokens[0]);
			m_ConditionList.add(false);
			refreshCondition();
		}
	}
	else
	{
		showError(("missing operator/operand on #if"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfElse(const char*)
{
	int nCount = m_ConditionList.count();

	if (nCount > 0)
	{
		m_ConditionList[nCount - 1] = !m_ConditionList.get(nCount - 1);
		refreshCondition();
	}
	else
	{
		showError(("illegal #else missing #if/#ifdef/#ifndef"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfElif(const char* sData)
{
	int nCondCount = m_ConditionList.count();

	if (nCondCount <= 0)
	{
		showError(("illegal #elif missing #if/#ifdef/#ifndef"));
		abort();
		return;
	}

	//如果当前条件为true则改变条件为false
	if (m_ConditionList[nCondCount - 1])
	{
		m_ConditionList[nCondCount - 1] = false;
		refreshCondition();
		return;
	}

	PPToken sTokens[3];
	int nCount = ArrayCount(sTokens);

	delimiteLine(sData, sTokens, nCount);

	if (nCount >= 3)
	{

		PPREPROC_MACRO pMacro = getMacro(sTokens[0]);

		if (pMacro)
		{
			if (strcmp(("=="), sTokens[1]) == 0)
			{
				if (strcmp(pMacro->sValue, sTokens[2]) == 0)
					m_ConditionList[nCondCount - 1] = true;

				refreshCondition();
			}
			else if (strcmp(("!="), sTokens[1]) == 0)
			{
				if (strcmp(pMacro->sValue, sTokens[2]) != 0)
					m_ConditionList[nCondCount - 1] = true;

				refreshCondition();
			}
			else
			{
				showErrorFormat(("invalid macro compare operator %s, default is still false"), sTokens[1]);
				abort();
			}
		}
		else
		{
			showErrorFormat(("macro %s was not defined, default comparison is false"), sTokens[0]);
		}
	}
	else
	{
		showError(("missing operator/operand on #elif"));
		abort();
	}
}

void LuaPreProcessor::DirectiveOfEndif(const char*)
{
	int nCount = m_ConditionList.count();

	if (nCount > 0)
	{
		m_ConditionList.trunc(nCount - 1);
		refreshCondition();
	}
	else
	{
		showError(("illegal #endif missing #if/#ifdef/#ifndef"));
		abort();
	}
}

const char* LuaPreProcessor::delimiteLine(const char* sLinePtr, PPToken* sTokens, int& nTokenCount)
{
	int nCount = 0;
	char* sPtr = (char*)sLinePtr;
	const char* sBegin;
	size_t nLen;

	while (*sPtr && nCount < nTokenCount)
	{
		//跳过行首的不可见字符
		while (*sPtr && (unsigned)*sPtr <= 0x20)
		{
			sPtr++;
		}

		sBegin = sPtr;

		//取得当前的词结束的位置
		while (*sPtr && (unsigned)*sPtr > 0x20)
		{
			sPtr++;
		}

		//如果成功的取到了词，则保存改词到sTokens中
		if (sPtr > sBegin)
		{
			nLen = sPtr - sBegin;

			if (nLen >= ArrayCount(sTokens[0]))
				nLen = ArrayCount(sTokens[0]) - 1;

			memcpy(sTokens[nCount], sBegin, nLen * sizeof(*sBegin));
			sTokens[nCount][nLen] = 0;

			nCount++;

			if (*sPtr)
			{
				*sPtr = 0;//在该词结束的位置写入终止符
				sPtr++;
			}
		}
	}

	nTokenCount = nCount;
	return sPtr;
}

void LuaPreProcessor::refreshCondition()
{
	m_boCurrCondition = true;
	int nCount = m_ConditionList.count();

	while (nCount > 0)
	{
		nCount--;

		if (!m_ConditionList[nCount])
		{
			m_boCurrCondition = false;
			break;
		}
	}
}

void LuaPreProcessor::clearIncludedFileList()
{
	for (int i = m_IncludedFileList.count() - 1; i > -1; --i)
	{
		free((void*)m_IncludedFileList[i]);
	}

	m_IncludedFileList.trunc(0);
}

void LuaPreProcessor::showError(const char* err)
{
	RefString txt;
	if (m_ParseEnvir.sFilePath)
		txt.format("%s  in:\n  %s:%d", err, m_ParseEnvir.sFilePath, m_ParseEnvir.nLineNo);
	else
		txt = err;

	char buf[1024] = {0};

	for (int i = m_ParseEnvirStack.count() - 1; i > 0; --i) //循环的终止条件是索引大于0，因为第0个环境是未初始化的自身数据
	{
		PREPROC_PARSERENVIR& ev = m_ParseEnvirStack[i];
		SNPRINTFA(buf, sizeof(buf) - 1, ("\n  %s:%d"), ev.sFilePath, ev.nLineNo);
		txt += buf;
	}

	printf("%s", txt.rawStr());
	throw txt;
}

void LuaPreProcessor::showErrorFormat(const char* sFmt, ...)
{
	char sBuf[1024];
	va_list	args;

	va_start(args, sFmt);
	VSNPRINTFA(sBuf, sizeof(sBuf) - 1, sFmt, args);
	va_end(args);

	showError(sBuf);
}

const char* LuaPreProcessor::SaveFileDirAndParse(const char* sSourceText, const char* sFullFilePath)
{
	//生成文件路径字符串并将路径压入预处理器包含文件分析栈
	String sDir = sFullFilePath;
	char* sDirPtr = (char*)sDir.rawStr();
	sDirPtr[getFileNamePart(sDirPtr) - sDirPtr] = 0;
	int nPathIdx = m_FilePathStack.add(&sDir);


	//保存原始文件行信息
	int nLineIdx = m_LineRangeList.count() + 1;
	m_LineRangeList.reserve((nLineIdx + 15) & ~(15));
	m_LineRangeList.trunc(nLineIdx);
	nLineIdx--;
	LineRange* pLn = &m_LineRangeList[nLineIdx];
	//GetShortPathName(sFullFilePath, pLn->sFileName, ArrayCount(pLn->sFileName) - 1);
	_STRNCPY_A(pLn->sFileName, sFullFilePath);
	pLn->nLineStart = m_nLineNo;

	//分析文件中的代码
	m_ParseEnvir.sFilePath = sFullFilePath;
	const char* sResult = ParseSource(sSourceText);

	//设置结束行索引
	/**
		必须重新取得ln的指针，因为ParseSource是个递归调用，
	    如果后续再次调用SaveFileDirAndParse而导致m_LineRangeList的内存空间被重新申请，
		那么本次调用ParseSource前取得的ln将不再有效！
		这个BUG调了数个小时！！！
	**/
	pLn = &m_LineRangeList[nLineIdx];
	pLn->nLineEnd = m_nLineNo - 1;

	//从预处理器包含文件分析栈从弹出文件路径
	m_FilePathStack.trunc(nPathIdx);

	return sResult;
}

bool LuaPreProcessor::SearchAndLoadIncludeFile(const char* fn, bool mul)
{
	char sPath[2048];
	//开始搜索文件，优先从当前文件的目录开始搜索
	int count = m_FilePathStack.count();
	if (count > 0)
	{
		count--;
		SNPRINTFA(sPath, sizeof(sPath) - 1, "%s%s", m_FilePathStack[count]->rawStr(), fn);

		if (fileExists(sPath))
		{
			return LoadIncludeFile(sPath, mul);
		}
	}

	//无法从当前文件的目录找到文件则从包含文件目录列表中降序循环搜索
	for (int i = m_IncludeDirList.count() - 1; i > -1; --i)
	{
		SNPRINTFA(sPath, sizeof(sPath) - 1, "%s%s", m_IncludeDirList[i]->rawStr(), fn);
		if (fileExists(sPath))
		{
			return LoadIncludeFile(sPath, mul);
		}
	}

	char tmp[1024];
	if (strncmp(fn, "./", 2) != 0)
	{
		SNPRINTFA(tmp, sizeof(tmp) - 1, "./%s", fn);
	}
	else
	{
		SNPRINTFA(tmp, sizeof(tmp) - 1, "%s", fn);
	}

	//最后将文件视为绝对路径中的文件
	if (fileExists(fn))
	{
		return LoadIncludeFile(tmp, mul);
	}

	showErrorFormat(("include file \"%s\" can not be found"), fn);
	return false;
}

bool LuaPreProcessor::LoadIncludeFile(const char* sIncludeFilePath, bool mulInc)
{
	static const int dwBufLen = 1024;

	//整理文件完整路径
	char* sFilePath = (char*)malloc(dwBufLen);
	_STRNCPY_S(sFilePath, sIncludeFilePath, dwBufLen);
	sFilePath[strlen(sIncludeFilePath)] = 0;
	//如果不允许多次包含，则判断文件是否已经被加载过
	if (!mulInc)
	{
		for (int i = m_IncludedFileList.count() - 1; i > -1; --i)
		{
			//文件被加载过了，放弃再度包含
			if (strcmp(m_IncludedFileList[i], sFilePath) == 0)
			{
				free(sFilePath);
				return false;
			}
		}
	}

	//将文完整路径添加到已加载过的文件列表中
	m_IncludedFileList.add(sFilePath);

	//加载并分析文件
	MemoryStream ms(NULL);

	if (ms.loadFromFile(sFilePath) <= 0)
		return false;

	SaveParseEnvir();

	SaveFileDirAndParse((const char*)ms.getMemory(), sFilePath);

	RestorsParseEnvir();
	return true;
}

const char* LuaPreProcessor::LineRangeList::getSourceLineNumber(int nLineNo, int& nSrcLineNo)
{
	int nLineStart = 1, nLineCount = 0, nLineEnd = 0, nCount = count();
	const char* sSrcFile = NULL;

	for (int i = 0; i < nCount; ++i)
	{
		LineRange& ln = (*this)[i];

		if (ln.nLineStart > nLineNo)
			break;

		if (ln.nLineEnd >= nLineNo)
		{
			sSrcFile = ln.sFileName;
			nLineStart = ln.nLineStart;
			nLineCount = 0;
		}
		else if (nLineEnd < ln.nLineEnd)
		{
			nLineEnd = ln.nLineEnd;
			nLineCount += (nLineEnd - ln.nLineStart);
		}
	}

	if (sSrcFile)
	{
		nSrcLineNo = nLineNo - nLineStart - nLineCount + 1;//行号从1开始
		return sSrcFile;
	}
	else return NULL;
}


