#ifndef	_SRV_CONFIG_H_
#define	_SRV_CONFIG_H_


//服务器端口地址等相关配置
class SrvConfig:
	public BaseLuaConfig
{
public:
	void ReadConfig();
	SrvConfig(void);
	~SrvConfig(void);
public:
	char	szAddr[20];
	int		nPort;
	char	szServiceName[20];
protected:
	void showError(const char* err);
};

#endif

