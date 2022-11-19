#ifndef _CONFIG_LOADER_H_
#define _CONFIG_LOADER_H_

template<class SonClass>
class ConfigLoader
{
public:
	ConfigLoader() {};
	typedef bool (SonClass::*FileReaderFunc)(); //
	typedef bool (SonClass::*BFileReaderFunc)(bool flag);
	/*
	* Comments:读取文件，支持1个文件放多个table，最大支持4个处理函数
	* Param SonClass * pLuaConfig: 基类的指针
	* Param const char* sFilePath:文件的地址
	* Param FileReaderFunc reader:文件的读取函数
	* @Return bool:成功返回true，否则返回 false
	*/
	inline bool LoadFile(SonClass* config, const char* fn, FileReaderFunc reader)
	{
		bool ret = false;

		if (config == NULL)
		{
			OutputMsg(rmError, ("unable to load from %s,pLuaConfig == NULL"), fn);
			return false;
		}

		try
		{
			const char* txt = GameLuaConfig::LoadFromFile(fn, config);
			if (txt == NULL)
			{
				return false;
			}
			if (!config->setScript(txt))
				OutputMsg(rmError, ("syntax error on  %s"), fn);

			ret = (config->*reader)();

			if (ret)
			{
				char buf[256];
				FDOP::ExtractFileName(fn, buf, sizeof(buf) - 1);
				OutputMsg(rmError, ("load %s config finished!"), buf);
			}
		}
		catch (RefString& s)
		{
			OutputMsg(rmError, ("load %s config error: %s"), fn, s.rawStr());
		}
		catch (...)
		{
			OutputMsg(rmError, ("unexpected error on load %s"), fn);
		}

		//销毁脚本虚拟机
		config->setScript(NULL);

		return ret;
	}

	inline bool LoadFileB(SonClass* config, const char* fn, BFileReaderFunc reader, bool flag, int cachtype = 0)
	{
		bool ret = false;

		if (config == NULL)
		{
			OutputMsg(rmError, ("unable to load from %s,pLuaConfig == NULL"), fn);
			return false;
		}

		try
		{
			const char* txt = GameLuaConfig::LoadFromFile(fn, config);
			if (txt == NULL)
			{
				return false;
			}
			if (!config->setScript(txt))
			{
				OutputMsg(rmError, ("syntax error on  %s"), fn);
				return false;
			}

			ret = (config->*reader)(flag);
			if (ret)
			{
				char buf[256];
				FDOP::ExtractFileName(fn, buf, sizeof(buf) - 1);
				OutputMsg(rmError, ("load %s config finished!"), buf);
			}

/*
#ifdef _MSC_VER
			STATIC_ASSERT(FileUpCheck::ctNone == 0);

			if (cachtype != FileUpCheck::ctNone)
			{
				// 缓存到文件中，下次可以使用
				const char* cfn = GetConfData()->file_check_.getfn(cachtype);
				if (cfn && !FDOP::FileExists(cfn))
				{
					FILE* fp = fopen(cfn, "w");
					if (fp)
					{
						fputs(txt, fp);
						fclose(fp);
						fp = NULL;
					}
				}
			}
#endif
			*/
		}
		catch (RefString& s)
		{
			OutputMsg(rmError, ("load %s config error: %s"), fn, s.rawStr());
		}
		catch (...)
		{
			OutputMsg(rmError, ("unexpected error on load %s"), fn);
		}

		//销毁脚本虚拟机
		config->setScript(NULL);

		return ret;
	}
};

#endif

