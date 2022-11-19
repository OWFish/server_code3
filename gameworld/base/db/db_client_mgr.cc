#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

DBClientMgr::DBClientMgr() : Inherited()
{
	inter_msg_.setLock(&inter_msg_lock_);
}

DBClientMgr::~DBClientMgr()
{
	ProcessSysMsg();

	for (int i = 0; i < db_list_.count();  ++i)
	{
		DBClient* db = db_list_[i];
		db->WaitFor();
		OutputMsg(rmError, "DBClient stop");
		db->Stop();

		SafeDelete(db);
	}
}

int DBClientMgr::Run()
{
	int count = ProcessSysMsg();

	for (int i = 0; i < db_list_.count();  ++i)
	{
		DBClient* client = db_list_[i];
		client->SingleRun();

		if (client->GetBusy())
		{
			count++;
		}
	}

	return count;
}

void DBClientMgr::OnRoutine()
{
	OnStart();

	while (!terminated())
	{
		if (Run() <= 0)
			Sleep(1);
	}

	OnStop();
}

void DBClientMgr::OnStart()
{
	OutputMsg(rmNormal, "DBClientMgr start!");
}

void DBClientMgr::OnStop()
{
	OutputMsg(rmNormal, "DBClientMgr stop!");
}

int DBClientMgr::ProcessSysMsg()
{
	inter_msg_.flush();

	int count = inter_msg_.count();

	for (int i = 0; i < count; ++i)
	{
		GameInterMsg& msg = inter_msg_[i];
		OnRecvSysMsg(msg);
	}

	inter_msg_.clear();

	return count;
}

void DBClientMgr::OnRecvSysMsg(GameInterMsg& msg)
{
	switch (msg.msg_id_)
	{
	case dbmAdd:
		{
			DBClient* db = (DBClient*)msg.data_.ptr_;
			if (db)
			{
				db_list_.add(db);
			}
			break;
		}
	}
}

