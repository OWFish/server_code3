#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

using namespace stream;
TIPMSGCONFIG* TIPMSGCONFIG::config_ = NULL;

LangPack::LangPack()
	: Inherited2(), Inherited(), allocator_(("LangDataAlloc"))
{
	alloctor_ptr_ = &allocator_;
	TIPMSGCONFIG::config_ = new TIPMSGCONFIG();

	// 统计内存
	MEMCOUNTER(TIPMSGCONFIG, 0);
}

LangPack::~LangPack()
{
	LangSection::clear();
	SafeDelete(TIPMSGCONFIG::config_);
}

bool LangPack::LoadFromFile(const char* fn)
{
	bool result = false;

	try
	{
		OutputMsg(rmTip, "Start Load Luaguage Config!");

		MemoryStream ms(NULL);

		if (ms.loadFromFile(fn) <= 0)
		{
			OutputMsg(rmError, ("unable to load file %s error code"), fn);
			return false;
		}

		LuaPreProcessor pp(NULL);
		ServerInstance()->GetVSPDefine().RegisteToPreprocessor(pp);

		const char* txt = pp.parse((const char*)ms.getMemory(), fn);

		if (!txt)
		{
			showErrorFormat(("unable to pre-precess Language config"));
			return false;
		}

		if (!setScript(txt))
		{
			showErrorFormat(("unable to set Language code-text"));
			return false;
		}

		if (openGlobalTable("Lang"))
		{
			clear();
			result = readLanguagePacket(*this);

			if (result)
			{
				LoadTipMsg("System");
			}

			closeTable();

			if (result)
			{
				OutputMsg(rmTip, ("[LANGUAGE]Luaguage Load Complete!"));
			}
		}
	}
	catch (RefString& s)
	{
		OutputMsg(rmError, ("load Language config error: %s"), s.rawStr());
	}
	catch (...)
	{
		OutputMsg(rmError, ("unexpected error on load Language config"));
	}

	//销毁脚本虚拟机
	setScript(NULL);
	return result;
}

bool LangPack::LoadTipMsg(const char* tn)
{
	TIPMSGCONFIG& dataConfig = *TIPMSGCONFIG::config_;
	if (tn == NULL) return false;

	if (!openGlobalTable("Lang"))
	{
		OutputMsg(rmError, ("load Lang table fail, not fing Global table system"));
		return false;
	}

	if (!openFieldTable(tn))
	{
		OutputMsg(rmError, ("open table %s fail, initlize fail"), tn);
		closeTable();
		return false;
	}

	if (dataConfig.count_ > 0)
	{
		dataConfig.count_ = 0;
	}

	const int count = (int)lua_objlen(lua_, -1);

	if (count <= 0)
	{
		OutputMsg(rmWarning, ("Lang table is empty"));
		return true;
	}

	if (count > TIPMSGCONFIG::MAX_COUNT)
	{
		OutputMsg(rmError, "tip over, MAX = %d", TIPMSGCONFIG::MAX_COUNT);
		return false;
	}

	int pos = 0;

	if (enumTableFirst())
	{
		do
		{
			getFieldStringBuffer(NULL, dataConfig.data_[pos], sizeof(dataConfig.data_[0]));
			pos ++;
		}
		while (enumTableNext());
	}

	dataConfig.count_ = pos;
	closeTable();
	return true;
};

void LangPack::showError(const char* err)
{
	SetErrDesc(err);
	RefString s = ("[Language Config Error]");
	s += err;
	throw s;
}

bool LangPack::readLanguagePacket(LangSection& section)
{
	//这里无法通过lua_objlen取得表内容数量，因为表可能只有None-Array value。所以可能取不到，应当遍历统计
	int len = 0;

	lua_pushnil(lua_);

	while (lua_next(lua_, -2))
	{
		len++;
		lua_pop(lua_, 1);//remove value
	}

	if (len <= 0)
		return true;

	bool result = true;

	section.setPacket(len);

	if (enumTableFirst())
	{
		char numKey[128];
		const char* key;
		int keyType, valType;
		LangSection* newSection;

		do
		{
			keyType = lua_type(lua_, -2);
			valType = lua_type(lua_, -1);

			//确定key
			if (keyType == LUA_TNUMBER)
			{
				SNPRINTFA(numKey, sizeof(numKey), "%lld", (long long int)lua_tointeger(lua_, -2));
				key = numKey;
			}
			else key = lua_tostring(lua_, -2);

			//读取和设置值
			if (valType == LUA_TSTRING || valType == LUA_TNUMBER)
			{
				newSection = section.addSection(key);
				newSection->setText(lua_tostring(lua_, -1));
			}
			else if (valType == LUA_TTABLE)
			{
				newSection = section.addSection(key);
				result = readLanguagePacket(*newSection);

				if (!result)
				{
					endTableEnum();
					break;
				}
			}
		}
		while (enumTableNext());
	}

	return result;
}



