#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "os_def.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "ltm.h"
}
#include "container/vector.h"
#include "ref_string.hpp"
#include "stream.h"
#include "share_util.h"
#include "second_time.h"
#include "container/str_hash_table.h"
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"
#include "luabase/lua_pre_process.h"
#include "luabase/clvariant.h"
#include "luabase/lua_clvariant.h"
#include "luabase/lua_profiler.h"
#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"
#include "luabase/vsp_def.h"

CVSPDefinition::CVSPDefinition()
{

}

CVSPDefinition::~CVSPDefinition()
{
	ClearDefinitions();
}

const char* CVSPDefinition::GetDefinition(const char* sDefName) const
{
	int i, nCount = m_Defines.count();

	for (i = 0; i < nCount; ++i)
	{
		if (strcmp(m_Defines[i].sDefName, sDefName) == 0)
		{
			return m_Defines[i].sDefValue;
		}
	}

	return NULL;
}

void CVSPDefinition::RegisteToPreprocessor(LuaPreProcessor& pp)
{
	int nCount = m_Defines.count();

	for (int i = 0; i < nCount; ++i)
	{
		pp.addMacro(m_Defines[i].sDefName, m_Defines[i].sDefValue);
	}

#ifdef _MSC_VER
	const char* os = "WIN";
#else
	const char* os = "LINUX";
#endif

	if (!pp.getMacro("OSTYPE"))
		pp.addMacro("OSTYPE", os);
	
	if (!GetDefinition("OSTYPE"))
		SetDefinition("OSTYPE", os);
}

#define LN '\n'
bool CVSPDefinition::LoadDefinitions(const char* sFilePath)
{
	stream::MemoryStream ms(NULL);

	//加载定义文件
	if (ms.loadFromFile(sFilePath) <= 0)
	{
		OutputMsg(rmError, "unable to load Definitions from %s ", sFilePath);
		return false;
	}

	//清空当前所有定义
	ClearDefinitions();

	//读取定义文件
	char* sText = (char*)ms.getMemory();
	char* sLineEnd, *sNewLine, *sTag, *sPtr;

	//跳过UTF-8 BOM
	if ((*(int*)sText & 0x00FFFFFF) == 0xBFBBEF)
		sText += 3;

	while (true)
	{
		//跳过当前行中行首的空白字符
		while (*sText && (unsigned char)*sText <= 0x20 && *sText != LN)
		{
			sText++;
		}

		//字符串是否已经遍历结束
		if (!*sText)
			break;

		//该行如果是空行则换入下一行并继续
		if (*sText == LN)
		{
			sText++;
			continue;
		}

		//确定当前行结束的位置
		sLineEnd = strchr(sText, LN);

		if (!sLineEnd)
			sLineEnd = sText + strlen(sText) - 1;

		//跳过当前行中行尾的空白字符并在行尾写入终止符
		sNewLine = sLineEnd + 1;

		while (sText < sLineEnd && (unsigned char)*sLineEnd <= 0x20)
		{
			sLineEnd--;
		}

		if (sLineEnd > sText)
		{
			//在行尾写入终止符
			sLineEnd++;
			sLineEnd[0] = 0;

			//如果该行不是一个注释行，则按定义行分析
			if (sText[0] != '-' && sText[1] != '-')
			{
				sTag = strchr(sText, '=');

				if (sTag)
				{
					//跳过定义名称后面的空白字符
					sPtr = sTag - 1;

					while (sPtr > sText && *((uint8_t*)sPtr) <= 0x20)
					{
						sPtr--;
					}

					sPtr++;

					//如果定义名称有效则设置名称指针
					if (sPtr > sText)
					{
						sPtr[0] = 0;//在定义名称后面写入终止符
						//跳过定义值前面的空白字符
						sPtr = sTag + 1;

						while (sPtr < sLineEnd && (unsigned char)*sPtr <= 0x20)
						{
							sPtr++;
						}

						//添加此定义
						SetDefinition(sText, sPtr);
					}
				}
			}
		}

		sText = sNewLine;
	}

	return true;
}

void CVSPDefinition::SetDefinition(const char* sDefName, const char* sDefValue)
{
	int i, nCount = m_Defines.count();
	size_t nNameLen, nValueLen;
	Definition define;

	for (i = 0; i < nCount; ++i)
	{
		if (strcmp(m_Defines[i].sDefName, sDefName) == 0)
		{
			free(m_Defines[i].sDefName);
			m_Defines.remove(i);

			//如果定义值为空则表示删除定义，否则将终止循环并添加新的定义以实现修改定义值的目的
			if (!sDefValue)
				return;
			else break;
		}
	}

	nNameLen = strlen(sDefName);
	nValueLen = strlen(sDefValue);
	//申请定义数据内存
	define.sDefName = (char*)malloc(sizeof(*sDefName) * (nNameLen + nValueLen + 2));
	//拷贝定义名称
	memcpy(define.sDefName, sDefName, sizeof(*sDefName) * nNameLen);
	define.sDefName[nNameLen] = 0;
	//拷贝定义值
	define.sDefValue = define.sDefName + nNameLen + 1;
	memcpy(define.sDefValue, sDefValue, sizeof(*sDefName) * nValueLen);
	define.sDefValue[nValueLen] = 0;
	//添加为新定义
	m_Defines.add(define);
}

void CVSPDefinition::ClearDefinitions()
{
	int i, nCount = m_Defines.count();
	//__try
	{
		for (i = 0; i < nCount; ++i)
		{
			free(m_Defines[i].sDefName);
		}
	}
	//__except(CustomExceptHandler(GetExceptionInformation()))
	//{

	//}
	m_Defines.empty();
}

