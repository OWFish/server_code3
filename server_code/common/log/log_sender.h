#ifndef	_LOG_SENDER_H_
#define	_LOG_SENDER_H_

class NetClient;

class LogSender:
	public NetClient
{
public:
	// DC API��־
	void LogDcApiLogByStr(const char* logName, const char* logContent);
	// DC API��ϷЭ����־ 
	void LogDcApiProto(const char* openId, int pf, int serverId, int roleId, int systemId, int protoId, int protoType, int protoResult, const char* svrip, const char* userip);

	void LogCounter(ActorId actorid, const char* aid,
	                const char* user_level = "",
	                const char* counter = "",
	                const char* value = "",
	                const char* extra = "",
	                const char* kingdom = "",
	                const char* phylum = "",
	                const char* classfield = "",
	                const char* family = "",
	                const char* genus = "",
					int flag = 1);

	void LogInstall(const char* actorId, const char* source = "",
	                const char* affiliate = "",
	                const char* creative = "",
	                const char* family = "",
	                const char* genus = "",
	                const char* from_uid = "",
	                const char* extra = "",
					int flag = 3);

	void LogDau(const char* aid,
	            const char* source = "",
	            const char* affiliate = "",
	            const char* creative = "",
	            const char* family = "",
	            const char* genus = "",
	            const char* ip = "",
	            const char* from_uid = "",
	            const char* extra = "",
				int flag = 3);

	void LogEnconomy(ActorId actorid, const char* aid,
	                 const char* currency = "",
	                 const char* amount = "",
	                 const char* value = "",
	                 const char* kingdom = "",
	                 const char* phylum = "",
	                 const char* classfield = "",
	                 const char* family = "",
	                 const char* genus = "",
	                 const char* extra = "",
					 const char* extra2 = "",
					 const char* pf = "",
					 int flag = 3,
					 bool isPay = true,
					 const char* openkey = "",
					 const char* pfkey = "", const char* pfid = "");	// ��ʾ�Ƿ��ֵ������

	void LogMilestone(
		ActorId actorid,
	    const char* aid,
	    const char* milestone = "",
	    const char* value = "",
	    const char* extra = "",
		int flag = 3);

	void LogPayment(int ret, ActorId actorId, const char* aid, int amount,
		int mstType,
		int p1,
		int p2,
		int p3,
		int value = 1,
		const char* kingdom = "", 
		const char* phylum = "",
		const char* transactionid = "",
		const char* extra = "",
		int p4 = 0,
		int p5 = 0,
		int flag = 3);

	void LogGameInfo(const char* aid,
		const char* user_level = "",
		const char* value = "",
		const char* extra = "",
		const char* kingdom = "",
		const char* phylum = "",
		const char* classfield = "",
		const char* family = "",
		const char* genus = "",
		int flag = 3);

	void LogChat(const char* aid,
		const char* name,
		const char* ip,
		const char* pf,
		ActorId actorid,
		int type,
		const char* content,
		const char* toaid = "",
		const char* toname = "");

	// ��¼��������
	void LogOnline(int cnt, int extra);

	void LogTLog(const char* logstr);

	void LogDKMLog(const char* logstr, const char* pf = "0");

	inline int GetServerIndex()
	{
		return ServerIndex;
	}
	inline int GetServerType()
	{
		return ServerType;
	}
	inline const char* GetServerName()
	{
		return ServerName;
	}

	void SetServerIndex(const int nSerIdx)
	{
		ServerIndex = nSerIdx;
	}
	void SetServerType(const int nSrvType)
	{
		ServerType = nSrvType;
	}
	void SetServerName(const char* sServerName);

	// �Ƿ�ֹͣ��¼��־
	inline void StopLog(bool flag = true)
	{
		stop_log_ = flag;
	}
	inline void StopCounterLog(bool flag = true)
	{
		stop_counter_log_ = flag;
	}
	inline void StopEconomyLog(bool flag = true)
	{
		stop_economy_log_ = flag;
	}

public:
	LogSender();
	LogSender(int ServerType, int ServerIndex, char* ServerName);
	~LogSender(void);
protected:
	//	/*** �����踲�ǵĺ����� ***/
	///* ������ͨ�����ݰ�
	// * nCmd		ͨ����Ϣ����
	// * inPacket	�Ѿ���ȡ��ͨ����������ݰ������ݰ��Ķ�ȡλ��ָ���������ݺ������
	// */
	//virtual void OnRecv(const uint16_t cmd, DataPacketReader &data);

	/*** ���к���Ϊ��������б�Ҫ���ǵĺ����� ***/
	/* ���ѯ���ط����������ͣ��Ա���ȷ�ķ���ע������ */
	virtual int GetLocalServerType();

	/* ���ѯ���ط����������ƣ��Ա���ȷ�ķ���ע������ */
	virtual const char* GetLocalServerName();
	/* ���ѯ���ط�����ID���Ա���ȷ�ķ���ע�����ݣ�Ĭ�ϵķ���ֵ��0 */
	virtual int GetLocalServerIndex();

	void OnConnected();
private:

	//����4��ֵ���ڷ���ע���
	int			ServerType;		//���������ͣ�ֵΪSERVERTYPEö�������е�ö��ֵ
	int			ServerIndex;	//������Ψһ��ţ���������Ž�����Ϸ�����������壩
	char		ServerName[128];	//���������ƣ������0��ֹ��

	bool		stop_log_;
	bool		stop_counter_log_;
	bool 		stop_economy_log_;
};

#endif


