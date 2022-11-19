#pragma once

#include "server_def.h"
#include "data_packet.hpp"


class Actor;
typedef void(*NetMsgDealFunc)(ActorId actor_id, DataPacketReader& pack, Actor* srcActor);

// �����Ϣ����

class LFNetmsgMgr
{
public:
	LFNetmsgMgr();
	~LFNetmsgMgr();

public:
	// ���������Ϣ
	bool ProcessActorNetmsg(ActorId actor_id, uint8_t sys_id, uint8_t cmd_id, DataPacket& pack, Actor* srcActor);
	// ע����Ϣ������
	static int RegistNetMsgDealFunc(int sys_id, int cmd_id, NetMsgDealFunc func);
	// ȡ��ע����Ϣ������
	static int UnregistNetMsgDealFunc(int sys_id, int cmd_id);
	// ע��ű��������Ϣ
	void RegisterScriptMsg(int sysId, int cmdId);
};
