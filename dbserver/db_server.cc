
#include "StdAfx.h"

DBServer* DBServer::Instance(NULL);

DBServer::DBServer()
{
	srv_name_[0] = 0;
	client_mgr_ = new DBSessionMgr(this);
	tables_ = new DBTables();

	Instance = this;
}

DBServer::~DBServer()
{
	//Shutdown();
	SafeDelete(client_mgr_);
	SafeDelete(tables_);
}


void DBServer::SetDb(SQLConnection* con)
{
	con->SetHost(db_host_);
	con->SetPort(db_port_);
	con->SetDbName(db_name_);
	con->SetUserName(db_user_);
	con->SetPassWord(db_pw_);
	con->SetConnectionFlags(CLIENT_FOUND_ROWS | CLIENT_MULTI_RESULTS);
}

void DBServer::SetSrvName(const char* name)
{
	_STRNCPY_A(srv_name_, name);
}


void DBServer::SetDbConf(const char* host, const int port, const char* db_name, const char* db_usre, const char* db_pw)
{
	_STRNCPY_A(db_host_, host);
	db_port_ = port;
	_STRNCPY_A(db_name_, db_name);
	_STRNCPY_A(db_user_, db_usre);
	_STRNCPY_A(db_pw_, db_pw);
}

void DBServer::SetAddr(const char* host, const int port)
{
	client_mgr_->SetServiceHost(host);
	client_mgr_->SetServicePort(port);
}

bool DBServer::Startup()
{
#ifdef _MSC_VER
	TimeProfMgr::getSingleton();
#endif
	//启动数据服务器
	return (bool)client_mgr_->Startup();
}

void DBServer::Shutdown()
{
	//停止数据服务器
	client_mgr_->Stop();
#ifdef _MSC_VER
	TimeProfMgr::getSingleton().clear();
#endif
}


bool DBServer::GetGameReady(int srv_id)
{
	return client_mgr_->GetGameReady(srv_id);
}


