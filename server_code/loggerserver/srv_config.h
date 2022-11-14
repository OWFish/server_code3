#ifndef			_SRV_CONFIG_H_
#define			_SRV_CONFIG_H_


//�������˿ڵ�ַ���������
typedef	struct SrvConf
{
	char	szAddr[20];
	int		nPort;
	char	szServiceName[20];

	char	webHost_[256]; // �ύ��־��web�ĵ�ַ
	u_long	addr_;
	int		webPort_;
	char	webUrl_[256];
	bool	bi_;		// �Ƿ񷢵�bi

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
	char	szKey[100];//���ڽ��ܵ�key��16λ
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

