#ifndef _MSG_MGR_H_
#define _MSG_MGR_H_

class MsgMgr
{
public:
	MsgMgr() {}
	~MsgMgr() {}

public:
	/*
	* Comments:���Ѿ����ߵ��û�����һ����Ϣ�����û��´ε�¼��ʱ�򣬻��յ�������Ϣ.
	* Param int nActorId:Ŀ���ɫid
	* Param int nSrcActorId:����������Ϣ�Ľ�ɫid������GM���������Ϣ���ɹ��������ɫ���ƴ�����Ҫ֪ͨGM,�����0����ʾϵͳ����
	* @Return bool: ����true����ʾ���ݳ���û���⣬������insert��db�ɹ�
	*/
	bool AddOffMsg(ActorId aid, const char* actorname, const char* account, ActorId srcid, const char* buf, size_t size);

	/*
	* Comments:���ݿⷵ��
	* @Return void:
	*/
	void OnDbReturnData(int nCmd, DataPacketReader& reader);

	/*
	* Comments:����һ����Ϣ�����ݿ�ķ��ؽ��
	* Param int nCmd:
	* Param int nErrorCode:�������
	* Param DataPacketReader & reader:
	* @Return void:
	*/
	void OnAddOffMsgDbReturn(int nCmd, DataPacketReader& reader);

	void SaveChatMonitoring(int aid, int type, int msgid, int guild, const char* actorname,
		const char* account, const char* msg);
};

#endif

