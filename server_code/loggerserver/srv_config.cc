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
		const char* fn = "LoggerServer.txt";
		MemoryStream ms(NULL);

		//���������ļ�
		if (ms.loadFromFile(fn) <= 0)
		{
			showErrorFormat(("unabled to load config from %s"), fn);
			return;
		}

		setScript((const char*)ms.getMemory());

		if (openGlobalTable("LoggerServer"))
		{
			if (openFieldTable("SQL"))
			{
				getFieldStringBuffer(("Host"), DbConf.szHost, sizeof(DbConf.szHost));
				DbConf.nPort = getFieldInt("Port");
				getFieldStringBuffer(("DBName"), DbConf.szDbName, sizeof(DbConf.szDbName));
				getFieldStringBuffer(("DBUser"), DbConf.szUser, sizeof(DbConf.szUser));
				//char szTemp[100];
				//getFieldStringBuffer(("DBPass"), szTemp, sizeof(szTemp));
				//DecryptPassword(DbConf.szPassWord, sizeof(DbConf.szPassWord), (unsigned char*)szTemp, (const unsigned char*)("This_AVC_GAME_fly"));
				getFieldStringBuffer(("DBPass"), DbConf.szPassWord, sizeof(DbConf.szPassWord));
				closeTable();//DB
			}

			if (openFieldTable(("Server")))
			{
				getFieldStringBuffer(("BindAddress"), SrvConf.szAddr, sizeof(SrvConf.szAddr));
				SrvConf.nPort = getFieldInt("Port");
				getFieldStringBuffer(("ServiceName"), SrvConf.szServiceName, sizeof(SrvConf.szServiceName));
				getFieldStringBuffer(("WebHost"), SrvConf.webHost_, sizeof(SrvConf.webHost_));

				hostent* host = gethostbyname(SrvConf.webHost_);
				if (host)
				{
					SrvConf.addr_ = *(u_long*)host->h_addr_list[0];
				}

				int def = 8080;
				SrvConf.webPort_ = getFieldInt("WebPort", &def);
				getFieldStringBuffer(("WebUrl"), SrvConf.webUrl_, sizeof(SrvConf.webUrl_));

				bool bDef = true;
				SrvConf.bi_ = getFieldBoolean("sendtobi", &bDef);

				// TLog����������
				SrvConf.tlogAddr_ = 0;
				SrvConf.tlogPort_ = 0;
				memset(SrvConf.tlogHost_, 0, sizeof(SrvConf.tlogHost_));
				getFieldStringBuffer(("TLogHost"), SrvConf.tlogHost_, sizeof(SrvConf.tlogHost_));
				if(SrvConf.tlogHost_[0] != 0)
				{
					host = gethostbyname(SrvConf.tlogHost_);
					if (host)
					{
						SrvConf.tlogAddr_ = *(u_long*)host->h_addr_list[0];
					} 
				}
				SrvConf.tlogPort_ = getFieldInt("TLogPort", &def);

				closeTable();//DB
			}

			closeTable();//�ر�Config
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
	//���д������Ϊ�˼�������˴�ֱ���׳��쳣���쳣����readConfig�б�����Ӷ��������������õ�ѭ����ȡ��
	throw sErr;
}

