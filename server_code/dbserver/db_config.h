#ifndef _DB_CONFIG_H_
#define _DB_CONFIG_H_

class BaseLuaConfig;

class DbConfig:
	public BaseLuaConfig
{
public:
	DbConfig(void);
	~DbConfig(void);
	bool ReadConfig();
public:
	char			srv_name_[32];
	char			addr_[32];
	int				port_;
	char			db_host_[32];
	int				db_port_;
	char			db_name_[32];
	char			db_user_[32];
	char			db_pw_[128];
protected:
	void showError(const char* err);
};

#endif

