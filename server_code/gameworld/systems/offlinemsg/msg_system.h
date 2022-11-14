#pragma once
#include "StdAfx.h"
#include "msg_system.h"


/*****************************************************************************

	 ��Ϣ��ϵͳ���������û����ߺ󱣴���Ϣ�����û����ߺ��ٷ���Ϣ֪ͨ

 *****************************************************************************/


class MsgSystem
{
public:
	struct MsgData
	{
		int64_t		 id_;
		DataPacket pack_;
	};

public:
	MsgSystem(Actor *actor);
	virtual ~MsgSystem();

public:
	bool Init(DataPacketReader &data);
	virtual bool Initialize(/*void* data, size_t size*/);

	virtual void OnEnterGame();

	/*
	* Comments:֪ͨ��Ϣϵͳ�����ݿ�����¼������Ϣ
	* @Return void:
	*/
	void ReloadFromDb(int64_t msgId);

	/*
	* Comments:������ҵ���Ϣ�б�
	* @Return void:
	*/
	void OnDbRetData(int nCmd, int nErrorCode,  DataPacketReader& reader);

	void luaRecvMsg(int beg_msg_list_cnt, int end_msg_list_cnt);

	/*
	* Comments:ɾ����Ϣ
	* @Return void:
	*/
	bool DeleteMsg(int idx);

	/*
	* Comments:�����Ϣ����
	* @Return int:��Ϣ����
	*/
	int GetMsgCnt()
	{
		return msg_list_.count();
	}

	/*
	* Comments:��ȡ�����Ϣ
	* @Return MsgData*:��ҵ���Ϣָ��
	*/
	MsgData* GetMsg(int idx)
	{
		if (idx < 0 || idx >= msg_list_.count()) return NULL;

		return &msg_list_[idx];
	}

	/*
	* Comments:��ȡ�����Ϣ��������
	* @Return int:��Ϣ��������
	*/
	int GetMsgIndex(int64_t msg_id)
	{
		if (msg_list_.count() <= 0)	 return -1;

		for (int idx = 0; idx < msg_list_.count(); ++idx)
		{
			if (msg_list_[idx].id_ == msg_id)
			{
				return idx;
			}
		}

		return -1;
	}

private:
	/*
	* Comments:����������ͻ�ȡ�Լ�����Ϣ�б�����
	* Param int64_t nMsgId:���nMsgid== 0������������Ϣ���������̶�id����Ϣ
	* @Return void:
	*/
	void SendDbLoadMsg(int64_t nMsgId = 0);

private:
	Actor *actor_;

	Vector<MsgData>		msg_list_;
};



