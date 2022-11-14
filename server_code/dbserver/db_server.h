#ifndef _DBENGINE_H_
#define _DBENGINE_H_

class DBSessionMgr;

class DBServer
{
public:
	DBServer();
	~DBServer();

	inline const char* GetServerName()
	{
		return srv_name_;
	}

	inline DBSessionMgr* GetClientMgr()
	{
		return client_mgr_;
	}

	bool GetGameReady(int srv_id);

	//配置数据库连接对象
	void SetDb(SQLConnection* conn);

	//设置服务器名称
	void SetSrvName(const char* name);
	//设置数据库连接配置
	void SetDbConf(const char* host, const int port, const char* db_name, const char* db_usre, const char* db_pw);
	//设置数据服务的绑定地址和端口
	void SetAddr(const char* host, const int port);

	//启动数据服务器的服务
	bool Startup();
	//停止数据服务器的服务
	void Shutdown();

	DBTables* getTables() { return tables_; }

	static DBServer* Instance;

private:
	char			srv_name_[128];			//服务器名称
	char			db_host_[128];			//数据库地址
	int				db_port_;				//数据库端口
	char			db_name_[128];			//数据库名称
	char			db_user_[128];			//数据库用户名
	char			db_pw_[128];		//数据库用户密码

	DBSessionMgr*		client_mgr_;		//数据服务器
	DBTables*			tables_;
};

#endif

