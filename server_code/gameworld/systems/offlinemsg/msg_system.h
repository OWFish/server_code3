#pragma once
#include "StdAfx.h"
#include "msg_system.h"


/*****************************************************************************

	 消息子系统，常用于用户离线后保存消息，等用户上线后再发消息通知

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
	* Comments:通知消息系统从数据库读入新加入的消息
	* @Return void:
	*/
	void ReloadFromDb(int64_t msgId);

	/*
	* Comments:返回玩家的消息列表
	* @Return void:
	*/
	void OnDbRetData(int nCmd, int nErrorCode,  DataPacketReader& reader);

	void luaRecvMsg(int beg_msg_list_cnt, int end_msg_list_cnt);

	/*
	* Comments:删除消息
	* @Return void:
	*/
	bool DeleteMsg(int idx);

	/*
	* Comments:玩家消息总数
	* @Return int:消息总数
	*/
	int GetMsgCnt()
	{
		return msg_list_.count();
	}

	/*
	* Comments:获取玩家消息
	* @Return MsgData*:玩家的消息指针
	*/
	MsgData* GetMsg(int idx)
	{
		if (idx < 0 || idx >= msg_list_.count()) return NULL;

		return &msg_list_[idx];
	}

	/*
	* Comments:获取玩家消息数组索引
	* @Return int:消息数组索引
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
	* Comments:向服务器发送获取自己的消息列表内容
	* Param int64_t nMsgId:如果nMsgid== 0，读入所有消息，否则读入固定id的消息
	* @Return void:
	*/
	void SendDbLoadMsg(int64_t nMsgId = 0);

private:
	Actor *actor_;

	Vector<MsgData>		msg_list_;
};



