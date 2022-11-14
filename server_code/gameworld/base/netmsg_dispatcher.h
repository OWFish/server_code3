#pragma once

#include "server_def.h"
#include "data_packet.hpp"


class Actor;
typedef void(*NetMsgHandle)(Actor* actor, DataPacketReader& pack);

// 玩家消息处理

class NetMsgDispatcher
{
private:
	NetMsgDispatcher(){};
	~NetMsgDispatcher(){};

public:
	// 处理玩家消息
	static bool ProcessNetMsg(Actor* actor, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack);
	// 注册消息处理函数
	static bool RegistNetMsgHandle(int sys_id, int cmd_id, NetMsgHandle func);
	// 注册脚本处理的消息
	static bool RegisterScriptMsg(int sysId, int cmdId);
};
