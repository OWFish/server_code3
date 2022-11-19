#ifndef	_LOG_SENDER_H_
#define	_LOG_SENDER_H_

class NetClient;

class LogSender:
	public NetClient
{
public:
	// DC API日志
	void LogDcApiLogByStr(const char* logName, const char* logContent);
	// DC API游戏协议日志 
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
					 const char* pfkey = "", const char* pfid = "");	// 表示是否充值的数据

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

	// 记录在线人数
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

	// 是否停止记录日志
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
	//	/*** 子类需覆盖的函数集 ***/
	///* 处理单个通信数据包
	// * nCmd		通信消息命令
	// * inPacket	已经读取出通信命令的数据包，数据包的读取位置指向命令数据后的内容
	// */
	//virtual void OnRecv(const uint16_t cmd, DataPacketReader &data);

	/*** 下列函数为子类可能有必要覆盖的函数集 ***/
	/* ★查询本地服务器的类型，以便正确的发送注册数据 */
	virtual int GetLocalServerType();

	/* ★查询本地服务器的名称，以便正确的发送注册数据 */
	virtual const char* GetLocalServerName();
	/* ★查询本地服务器ID，以便正确的发送注册数据，默认的返回值是0 */
	virtual int GetLocalServerIndex();

	void OnConnected();
private:

	//以下4个值用于发送注册包
	int			ServerType;		//服务器类型，值为SERVERTYPE枚举类型中的枚举值
	int			ServerIndex;	//服务器唯一编号（服务器编号仅对游戏服务器有意义）
	char		ServerName[128];	//服务器名称，需包含0终止符

	bool		stop_log_;
	bool		stop_counter_log_;
	bool 		stop_economy_log_;
};

#endif


