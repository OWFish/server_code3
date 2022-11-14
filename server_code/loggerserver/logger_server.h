#ifndef _LOGGER_SERVER_H_
#define _LOGGER_SERVER_H_

// ����ʱ���η�����Ѷ����־
//#define DCAPI 1
//#define TLOG

class ServerSocket;
class SQLConnection;
class SrvConfig;

#define TIME_CLOSE_SOCK 2 //���������������Ժ��ùر�����
#define NUM_REQUEST_PER_CONN 15  //ÿ����������������
#define TIME_PER_CONN 5000  //ÿ�����ӱ���5��

#define TIME_ST_H 20
#define TIME_END_H 21
#define TIME_ST_M 30
#define TIME_END_M 30

class LoggerServer:
	public ServerSocket
{
public:
	typedef ServerSocket	Inherited;

	struct LogData
	{
		int cmd_;
		int serverId_;
		DataPacket* dp_;
	};

	//���ظ���ĺ���
	virtual NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);

	// ��ȡһ�����е����ݿ�����
	SQLConnection* GetSqlConnection()
	{
		return &db_;
	}

	void PostLogPacket(int serverId, int cmd, const char* buf, int size);
#define UrlEncode(msg, out) UrlEncodeSize(msg, out, sizeof(msg))
	static const char* UrlEncodeSize(const char* msg, char* out, int size);
	inline WatchThread* GetWatch()
	{
		return &watch_thread_;
	}
public://���캯������������
	LoggerServer(void);
	~LoggerServer(void);

	void SendToScribe(int serverId, const char* para = "", bool final = true,const char* key = "0948e5fa35a91677a2d8d8e7527ee461");
protected:
	//�������ڽ�������������������Ӻ����Ӵ����߳�ǰ����
	virtual bool DoStartup();
	//�ṩ����������и��ǵ�ֹͣ����ĺ���
	//��������ֹͣ���������Լ����������̲߳��رռ����׽��ֺ����
	virtual void DoStop();

	//������ݱ��Ƿ���ڵ��߳�
	static int swith_flag;
#ifdef _MSC_VER
	static void STDCALL CreateTablesThreadRoutine(LoggerServer* ptr);
	static void STDCALL LoggThread(LoggerServer* ptr);
#else
	static void* CreateTablesThreadRoutine(void* ptr);
	static void* LoggThread(void* ptr);
#endif
	void PrecessData(LogData& data, BaseScript& script, bool final);

private:
	//�������ݿ����ز���
	void SetDbConnection(SQLConnection& db);
	//������ݿ�����
	bool ConnectSQL(SQLConnection& db, time_t& conn_t, time_t& ping_t);

private:
	unsigned long long getUnixTime();
	void doSendDcApiLog(DataPacketReader& inPacket);
	void doSendDcApiLogList(DataPacketReader& inPacket);
	void doSendDcApiProtoLog(DataPacketReader& inPacket);
	void InsertCounter(int serverId, DataPacketReader& inPacket, bool final);
	void InsertInstall(int serverId, DataPacketReader& inPacket);
	void InsertDau(int serverId, DataPacketReader& inPacket);
	void InsertEconomy(int serverId, DataPacketReader& inPacket, bool final);
	void InsertChat(int serverId, DataPacketReader& inPacket, bool final);
	void InsertMilestone(int serverId, DataPacketReader& inPacket, bool final);
	void InsertOnline(int serverId, DataPacketReader& inPacket);

	void ProcessTLog(int serverId, DataPacketReader& reader);

	bool IsCanDKMLog(const char* pf);
	void WriteDKMLog(int serverId, DataPacketReader& inPacket);

	void SendToTLog(const char* logstr);
	void WriteTLog(const char* logstr);

	void WriteFile(const char* fn, const char* msg, SystemTime& st);
	void WriteDKMLogFile(const char* msg, SystemTime& st);
	void ImportData(const char* table, SystemTime& st);
	void CloseSock();	//�ر��ϱ�����
public:
	SrvConfig		conf_;

	bool			reload_createTable_script_;
	bool			reload_log_script_;
	BaseScript		create_script_;
	BaseScript		log_script_;
	time_t			create_tbl_next_t_;
	time_t			import_t_;
	char			dbLogDir_[256];
	std::vector<const char*> DKMLimit;
protected:

	CVSPDefinition	vsp_def_;

	bool			ct_runing_;				//�Ƿ�ֹͣ�����߳�
	bool			ct_free_;

	bool			pt_runing_;
	bool			pt_free_;

#ifdef _MSC_VER
	HANDLE			cTThread_;
	HANDLE			pTThread_;
#else
	pthread_t		cTThread_;
	pthread_t		pTThread_;
#endif
	QueueList<LogData> list_;
	Mutex			list_lock_;
	Vector<DataPacket*> free_list_;
	Mutex			free_lock_;
	BaseAllocator	log_alloc_;

	SQLConnection			db_;
	time_t					next_conn_db_t_;//�´������������ݵ�ʱ��
	time_t					next_ping_t_;

	SQLConnection			table_db_;	// �������ݿ�����
	time_t					next_conn_table_db_t_;
	time_t					next_table_ping_t_;
	WatchThread				watch_thread_;

	std::map<SOCKET, time_t> sock_list_; //��������Ҫ�ͷŵ�socket
	

	SOCKET					cli_sock_;	//�ϱ���web����
	time_t					cli_sock_start_time_; //�ϱ���web���ӽ���ʱ��
#if (defined(WIN32) || defined(WINDOWS))
#elif defined(DCAPI)
	CLogger dclogger;
#endif
};



#endif


