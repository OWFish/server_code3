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
	* Comments:��ȡ�ļ���֧��1���ļ��Ŷ��table�����֧��4��������
	* Param SonClass * pLuaConfig: �����ָ��
	* Param const char* sFilePath:�ļ��ĵ�ַ
	* Param FileReaderFunc reader:�ļ��Ķ�ȡ����
	* @Return bool:�ɹ�����true�����򷵻� false
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

		//���ٽű������
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
				// ���浽�ļ��У��´ο���ʹ��
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

		//���ٽű������
		config->setScript(NULL);

		return ret;
	}
};

#endif

