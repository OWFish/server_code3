#ifndef _MSG_MGR_H_
#define _MSG_MGR_H_

class MsgMgr
{
public:
	MsgMgr() {}
	~MsgMgr() {}

public:
	/*
	* Comments:给已经离线的用户发送一条信息，当用户下次登录的时候，会收到这条消息.
	* Param int nActorId:目标角色id
	* Param int nSrcActorId:发出这条消息的角色id，比如GM，当添加消息不成功，比如角色名称错误，需要通知GM,如果是0，表示系统发送
	* @Return bool: 返回true仅表示数据长度没问题，不代表insert到db成功
	*/
	bool AddOffMsg(ActorId aid, const char* actorname, const char* account, ActorId srcid, const char* buf, size_t size);

	/*
	* Comments:数据库返回
	* @Return void:
	*/
	void OnDbReturnData(int nCmd, DataPacketReader& reader);

	/*
	* Comments:增加一条消息后数据库的返回结果
	* Param int nCmd:
	* Param int nErrorCode:错误代码
	* Param DataPacketReader & reader:
	* @Return void:
	*/
	void OnAddOffMsgDbReturn(int nCmd, DataPacketReader& reader);

	void SaveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
		const char* account, const char* msg);
};

#endif

