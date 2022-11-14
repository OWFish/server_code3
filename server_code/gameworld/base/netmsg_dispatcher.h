#pragma once

#include "server_def.h"
#include "data_packet.hpp"


class Actor;
typedef void(*NetMsgHandle)(Actor* actor, DataPacketReader& pack);

// �����Ϣ����

class NetMsgDispatcher
{
private:
	NetMsgDispatcher(){};
	~NetMsgDispatcher(){};

public:
	// ���������Ϣ
	static bool ProcessNetMsg(Actor* actor, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack);
	// ע����Ϣ������
	static bool RegistNetMsgHandle(int sys_id, int cmd_id, NetMsgHandle func);
	// ע��ű��������Ϣ
	static bool RegisterScriptMsg(int sysId, int cmdId);
};
