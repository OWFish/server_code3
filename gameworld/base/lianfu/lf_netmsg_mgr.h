#pragma once

#include "server_def.h"
#include "data_packet.hpp"


class Actor;
typedef void(*NetMsgDealFunc)(ActorId actor_id, DataPacketReader& pack, Actor* srcActor);

// 玩家消息处理

class LFNetmsgMgr
{
public:
	LFNetmsgMgr();
	~LFNetmsgMgr();

public:
	// 处理玩家消息
	bool ProcessActorNetmsg(ActorId actor_id, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack, Actor* srcActor);
	// 注册消息处理函数
	static int RegistNetMsgDealFunc(int sys_id, int cmd_id, NetMsgDealFunc func);
	// 取消注册消息处理函数
	static int UnregistNetMsgDealFunc(int sys_id, int cmd_id);
	// 注册脚本处理的消息
	void RegisterScriptMsg(int sysId, int cmdId);
};
