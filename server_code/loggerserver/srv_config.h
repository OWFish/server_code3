#ifndef			_SRV_CONFIG_H_
#define			_SRV_CONFIG_H_


//服务器端口地址等相关配置
typedef	struct SrvConf
{
	char	szAddr[20];
	int		nPort;
	char	szServiceName[20];

	char	webHost_[256]; // 提交日志到web的地址
	u_long	addr_;
	int		webPort_;
	char	webUrl_[256];
	bool	bi_;		// 是否发到bi

	char	tlogHost_[256];
	u_long	tlogAddr_;
	int		tlogPort_;
	SrvConf(void) {
		memset(this, 0, sizeof(*this));
	}
} SRVCONF,*PSRVCONF;

typedef	struct DbConf{
	char	szHost[100];
	int		nPort;
	char	szDbName[100];
	char	szUser[100];
	char	szPassWord[100];
	char	szKey[100];//用于解密的key，16位
}DBCONF,*PDBCONF;

class SrvConfig:
	public BaseLuaConfig
{
public:
	void ReadConfig();
	SrvConfig(void);
	~SrvConfig(void);
public:
	SRVCONF		SrvConf;
	DBCONF		DbConf;

protected:
	void showError(const char* err);
};

#endif

