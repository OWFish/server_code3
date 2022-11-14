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

	//�������ݿ����Ӷ���
	void SetDb(SQLConnection* conn);

	//���÷���������
	void SetSrvName(const char* name);
	//�������ݿ���������
	void SetDbConf(const char* host, const int port, const char* db_name, const char* db_usre, const char* db_pw);
	//�������ݷ���İ󶨵�ַ�Ͷ˿�
	void SetAddr(const char* host, const int port);

	//�������ݷ������ķ���
	bool Startup();
	//ֹͣ���ݷ������ķ���
	void Shutdown();

	DBTables* getTables() { return tables_; }

	static DBServer* Instance;

private:
	char			srv_name_[128];			//����������
	char			db_host_[128];			//���ݿ��ַ
	int				db_port_;				//���ݿ�˿�
	char			db_name_[128];			//���ݿ�����
	char			db_user_[128];			//���ݿ��û���
	char			db_pw_[128];		//���ݿ��û�����

	DBSessionMgr*		client_mgr_;		//���ݷ�����
	DBTables*			tables_;
};

#endif

