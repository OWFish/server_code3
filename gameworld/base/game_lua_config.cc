#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
using namespace stream;
extern  int luaopen_server(lua_State* tolua_S);

bool GameLuaConfig::registLocalLibs()
{
	GameServer* ge = ServerInstance();

	if (ge)
	{
		//导出语言包
		LuaLangSection::regist(lua_);
		LuaLangSection::setGlobalValue(lua_, ge->GetLang(), "Lang");
		luaopen_server(lua_);
	}

	return true;
}

void GameLuaConfig::RegisteToPreprocessor(LuaPreProcessor& pp)
{
	ServerInstance()->GetVSPDefine().RegisteToPreprocessor(pp);
	// 加这个宏是为了避免再加载语言包
	pp.addMacro("_LANGUAGE_INCLUDED_");
}

const char* GameLuaConfig::LoadFromFile(const char* fn, GameLuaConfig* config)
{
	static MemoryStream ms(NULL);
	static LuaPreProcessor pp(NULL);
	pp.clearMacro();
	pp.setSize(15 * 1024 * 1024);
	if (ms.loadFromFile(fn) <= 0)
	{
		config->showErrorFormat(("unable to load from %s"), fn);
		return NULL;
	}

	//对配置脚本进行预处理
	config->RegisteToPreprocessor(pp);
	const char* txt = pp.parse((const char*)ms.getMemory(), fn);
	return txt;
}


int GameLuaConfig::ReadIntArray(int* arr, int count, const char* field)
{
	int ret = 0;

	if (enumTableFirst())
	{
		do
		{
			arr[ret] = getFieldInt(field);
			ret++;
		}
		while (enumTableNext() && ret < count);
	}

	return ret;
}

int GameLuaConfig::ReadIntArray(int* arr, int count, const char** field, int fcount)
{
	int ret = 0;

	if (enumTableFirst())
	{
		do
		{
			for (int f = 0; f < fcount; ++f)
			{
				arr[ret] = getFieldInt(field[f]);
				ret++;
			}

		}
		while (enumTableNext() && ret < count);
	}

	return ret;
}

int GameLuaConfig::ReadDoubleArray(double* arr, int count, const char* field /*= NULL*/)
{
	int ret = 0;

	if (enumTableFirst())
	{
		do
		{
			arr[ret] = getFieldNumber(field);
			ret++;
		}
		while (enumTableNext() && ret < count);
	}

	return ret;
}

int GameLuaConfig::ReadFloatArray(float* arr, int count, const char* field /*= NULL*/)
{
	int ret = 0;

	if (enumTableFirst())
	{
		do
		{
			arr[ret] = (float)getFieldNumber(field);
			ret++;
		}
		while (enumTableNext() && ret < count);
	}

	return ret;
}

int GameLuaConfig::ReadIntArray(const char* table, int** arr, MemoryContainer<char>& alloc)
{
	if (!openFieldTable(table)) return -1;

	int cnt = (int)lua_objlen(lua_, -1);

	if (cnt > 0)
	{
		*arr =
		    (int*)alloc.AllocBuffer(cnt * sizeof(int));

		int ret = 0;

		if (enumTableFirst())
		{
			do
			{
				(*arr)[ret] = getFieldInt(NULL);
				ret++;
			}
			while (enumTableNext());
		}

	}

	closeTable();
	return cnt;
}

int GameLuaConfig::ReadIntArray(const char* table, int** arr, const char** field, int fcount, MemoryContainer<char>& alloc)
{
	if (!openFieldTable(table)) return -1;

	int cnt = (int)lua_objlen(lua_, -1);

	int ret = 0;

	if (cnt > 0)
	{
		*arr =
		    (int*)alloc.AllocBuffer(cnt * sizeof(int) * fcount);

		if (enumTableFirst())
		{
			do
			{
				for (int f = 0; f < fcount; ++f)
				{
					(*arr)[ret] = getFieldInt(field[f]);
					ret++;
				}

			}
			while (enumTableNext());
		}

	}

	closeTable();
	return ret;
}

int GameLuaConfig::ReadIntArray(const char* table, int* arr, int count)
{
	if (!openFieldTable(table)) return -1;

	int cnt = (int)lua_objlen(lua_, -1);
	int ret = 0;
	if (cnt > 0 && count > 0)
	{
		if (enumTableFirst())
		{
			do
			{
				(arr)[ret] = getFieldInt(NULL);
				ret++;
			}
			while (enumTableNext() && ret < count);
		}

	}
	//枚举还没结束
	if (ret != cnt)
	{
		endTableEnum();
	}
	closeTable();
	return ret;
}

//int GameLuaConfig::ReadGameAttrArray(const char* table, GAMEATTR** arr, MemoryContainer<char>& alloc)
//{
//	if (!openFieldTable(table)) return -1;
//
//	int cnt = (int)lua_objlen(lua_, -1);
//
//	if (cnt > 0)
//	{
//		*arr = (GAMEATTR*)alloc.AllocBuffer(cnt * sizeof(GAMEATTR));
//
//		int pos = 0;
//
//		if (enumTableFirst())
//		{
//			do
//			{
//				int type = getFieldInt("type");
//				(*arr)[pos].type_ = (uint8_t)type;
//
//				//判断物品属性类型是否有效
//				if (type < aUndefined || type >= GameAttributeCount)
//				{
//					showErrorFormat(("GameAttr config err nID=%d,type=%d"), pos, type);
//					return -1;
//				}
//
//				switch (AttrDataTypes[type])
//				{
//				case adInt:
//					(*arr)[pos].value_.nValue = getFieldInt("value");
//					break;
//
//				case adUInt:
//					(*arr)[pos].value_.uValue = (unsigned int)getFieldInt("value");
//					break;
//
//				case adFloat:
//					(*arr)[pos].value_.fValue = (float)getFieldNumber("value");
//					break;
//
//				default:
//					break;
//				}
//
//				pos++;
//			}
//			while (enumTableNext());
//		}
//
//	}
//
//	closeTable();
//	return cnt;
//}
//
//bool GameLuaConfig::ReadAttr(GAMEATTR& attr)
//{
//	int tmpType = getFieldInt("type");
//
//	if (tmpType < aUndefined || tmpType >= GameAttributeCount)
//	{
//		showErrorFormat(("dragon type config error %d"), tmpType);
//		return false;
//	}
//
//	attr.type_ = tmpType;
//
//	switch (AttrDataTypes[attr.type_])
//	{
//	case adInt:
//		attr.value_.nValue = getFieldInt("value");
//		break;
//
//	case adUInt:
//		attr.value_.uValue = (unsigned int)getFieldInt64("value");
//		break;
//
//	case adFloat:
//		attr.value_.fValue = (float)getFieldNumber("value");
//		break;
//
//	default:
//		break;
//	}
//
//	return true;
//}
//
//
