#include "stdafx.h"
#include "srv_config.h"

using namespace stream;

SrvConfig::SrvConfig(void)
{
}


SrvConfig::~SrvConfig(void)
{
}

void SrvConfig::ReadConfig()
{
	try
	{
		const char* fn = "CenterServer.txt";
		MemoryStream ms(NULL);

		//加载配置文件
		if (ms.loadFromFile(fn) <= 0)
		{
			showErrorFormat(("unabled to load config from %s"), fn);
			return;
		}

		setScript((const char*)ms.getMemory());

		if (openGlobalTable("CenterServer"))
		{
			if (openFieldTable(("Server")))
			{
				getFieldStringBuffer(("BindAddress"), szAddr, sizeof(szAddr));
				nPort = getFieldInt("Port");
				getFieldStringBuffer(("ServiceName"), szServiceName, sizeof(szServiceName));

				closeTable();
			}

			closeTable();//关闭Config
		}
	}
	catch (RefString& s)
	{
		OutputMsg(rmNormal, s.rawStr());
	}
	catch (...)
	{
		OutputMsg(rmNormal, ("unexpected error on load config"));
	}
}

void SrvConfig::showError(const char* err)
{
	SetErrDesc(err);
	RefString sErr = ("[Configuration Error]");
	sErr += err;
	throw sErr;
}

