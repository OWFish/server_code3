
#include "StdAfx.h"
DbConfig::DbConfig(void)
{
}


DbConfig::~DbConfig(void)
{
}

bool DbConfig::ReadConfig()
{
	using namespace stream;

	bool result = false;
	MemoryStream ms(NULL);

	try
	{
		if (ms.loadFromFile("DBServer.txt") <= 0)
		{
			showError(("unable to load config from file DBServer.txt"));
			return result;
		}

		if (!setScript((const char*)ms.getMemory()))
		{
			showError(("parse config script failed"));
			return false;
		}

		if (openGlobalTable("DBServer"))
		{
			getFieldStringBuffer(("ServerName"), srv_name_, sizeof(srv_name_));

			if (openFieldTable("DBService"))
			{
				getFieldStringBuffer(("Address"), addr_, sizeof(addr_));
				port_ = getFieldInt("Port");
				closeTable();//DBService
			}

			if (openFieldTable("SQL"))
			{
				//char szTemp[100];
				getFieldStringBuffer(("Host"), db_host_, sizeof(db_host_));
				db_port_ = getFieldInt("Port");
				getFieldStringBuffer(("DBName"), db_name_, sizeof(db_name_));
				getFieldStringBuffer(("DBUser"), db_user_, sizeof(db_user_));
				//getFieldStringBuffer(("DBPass"), szTemp, sizeof(szTemp));
				//DecryptPassword(db_pw_, sizeof(db_pw_), (unsigned char*)szTemp, (const unsigned char*)("This_AVC_GAME_fly"));
				getFieldStringBuffer(("DBPass"), db_pw_, sizeof(db_pw_));
				closeTable();//DB
				result = true;
			}

			closeTable();//¹Ø±ÕDBServer
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

	return result;
}

void DbConfig::showError(const char* err)
{
	SetErrDesc(err);
	RefString sErr = ("[Configuration Error]");
	sErr += err;
	throw sErr;
}

