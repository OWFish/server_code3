#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include "_ast.h"

#include "container/queue_list.h"
#include "x_tick.h"
#include "x_lock.h"
#include "x_thread.h"
#include "net/base_socket.h"
#include "server_def.h"
#include "gate_proto.h"
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "data_packet_reader.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_session.h"
#include "net/server_socket.h"
#include "gate_user.h"
#include "gate_session.h"
#include "gate_manager.h"

GateSession::GateSession(const char* name) : Inherited(name)
{
	gate_idx_ = 0;
}

GateSession::~GateSession()
{
	CloseAllUser();
	FreeBuffers();
}

void GateSession::FreeBuffers()
{
	ClearSendList();
}

DataPacket& GateSession::AllocGateSendPacket(uint16_t cmd, NetId& netid)
{
	DataPacket& packet = Inherited::allocProtoPacket(cmd);
	packet << netid;
	return packet;
}

DataPacket& GateSession::AllocGateSendPacket(NetId& netid)
{
	DataPacket& packet = Inherited::allocProtoPacket(GW_DATA);
	packet << netid;
	return packet;
}

void GateSession::Disconnected()
{
	Inherited::Disconnected();
	FreeBuffers();
	CloseAllUser();
}

void GateSession::OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4)
{
	switch (msg)
	{
	case CLOSE_GATE_SESSION:
		// 这是由系统内部发出的关闭命令
		NetId netid;
		netid.socket_ = MAKEINT64(p1, p2);
		netid.index_ = LOINT16(p3);
		netid.gate_id_ = HIINT16(p3);
		CloseUser(netid, "OnRecvSysMsg");
		SendGateCloseUser(netid);
		break;
	}
}

void GateSession::OnRecv(const uint16_t cmd, char* buf, int size)
{
	if (size < (int)sizeof(NetId) || buf == NULL) return;

	NetId* netid = (NetId*)buf;
	buf += sizeof(NetId);
	size -= sizeof(NetId);

	if (netid->index_ >= MAX_GATE_USER) return;

	GateUser& user = user_list_[netid->index_];
	netid->gate_id_ = (uint16_t)gate_idx_;

	switch (cmd)
	{
	case GW_OPEN:
		{
			OpenNewUser(*netid, buf);
			break;
		}

	case GW_CLOSE:
		{
			CloseUser(*netid, "GW_CLOSE");
			break;
		}

	case GW_DATA:
		{
			if (!user.closed_ && user.netid_.socket_ == netid->socket_)
			{
				OnRecv(*netid, buf, size);
			}

			break;
		}

	case GW_TEST:
	case GW_CMD:
		{
			// 原样数据返回
			DataPacket& packet = AllocGateSendPacket(cmd, *netid);
			packet.writeBuf(buf, size);
			flushProtoPacket(packet);
			break;
		}
	}
}


NetId* GateSession::OpenNewUser(NetId& netid, const char* addr)
{
	if (netid.index_ >= MAX_GATE_USER) return NULL;

	GateUser& user = user_list_[netid.index_];

	user.netid_ = netid;
	user.netid_.gate_id_ = (uint16_t)gate_idx_;

	user.account_id_ = 0;
	_STRNCPY_A(user.remote_addr_, addr);
	user.closed_ = false;
	user.account_name_[0] = 0;
	user.gm_ = -1;

	OnOpenUser(&user);

	return &user.netid_;
}

void GateSession::OnOpenUser(GateUser*)
{

}

void GateSession::OnCloseUser(GateUser*, const char* reason)
{
}

bool GateSession::CloseUser(NetId& netid, const char* reason)
{
	if (netid.index_ >= MAX_GATE_USER) return false;

	if (netid.gate_id_ != gate_idx_) return false;

	GateUser& user = user_list_[netid.index_];

	if (user.closed_ == true) return true;
	if (user.netid_.socket_ != netid.socket_) return false;

	user.closed_ = true;

	OnCloseUser(&user, reason);
	return true;
}

void GateSession::CloseAllUser()
{
	for (int i = 0; i < MAX_GATE_USER; i++)
	{
		GateUser& user = user_list_[i];
		CloseUser(user.netid_, "CloseAllUser");
	}
}

void GateSession::SendGateCloseUser(NetId& netid)
{
	OutputMsg(rmNormal, ("close Socket=%d, GateSessionIdx=%d,reason=GW_CLOSE"), netid.socket_, netid.index_);
	DataPacket& packet = AllocGateSendPacket(GW_CLOSE, netid);
	flushProtoPacket(packet);
}


bool GateSession::OnValidateRegData(const SrvDef::PSERVER_REGDATA regData)
{
	return (regData && regData->GameType == SrvDef::SERVER_REGDATA::GT_ID && regData->ServerType == SrvDef::GateServer);
}

GateUser* GateSession::GetUser(NetId& netid)
{
	if (netid.index_ >= MAX_GATE_USER) return NULL;

	if (netid.gate_id_ != gate_idx_) return NULL;

	return &user_list_[netid.index_];
}



