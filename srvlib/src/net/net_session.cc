#include <stdio.h>
#include <stdlib.h>
#include "os_def.h"
#include <_ast.h>

#include <net/base_socket.h>
#include <x_tick.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "server_def.h"
#include "net/net_session.h"


NetSession::NetSession(const char* name)
	: Inherited(name)
{
	ZeroMemory(&remote_addr_, sizeof(remote_addr_));
	keep_alive_ = TRUE;

	registed_ = false;
	client_srv_idx_ = 0;
	client_name_[0] = 0;
	client_type_ = SrvDef::InvalidServer;
}

NetSession::NetSession(SOCKET s, sockaddr_in* client_addr, const char* name) : Inherited(name)
{
	SetClientSocket(s, client_addr);
}

NetSession::~NetSession()
{

}

void NetSession::SetClientSocket(SOCKET sock, sockaddr_in* client_addr)
{
	setSocket(sock);

	if (client_addr)
	{
		remote_addr_ = *client_addr;
#ifdef _MSC_VER
		int len = SNPRINTFA(remote_host_, ArrayCount(remote_host_) - 1, ("%d.%d.%d.%d"),
		                      client_addr->sin_addr.S_un.S_un_b.s_b1, client_addr->sin_addr.S_un.S_un_b.s_b2,
		                      client_addr->sin_addr.S_un.S_un_b.s_b3, client_addr->sin_addr.S_un.S_un_b.s_b4);
#else
		int s[4];
		s[0] = client_addr->sin_addr.s_addr & 0xff;
		s[1] = (client_addr->sin_addr.s_addr >> 8) & 0xff;
		s[2] = (client_addr->sin_addr.s_addr >> 16) & 0xff;
		s[3] = (client_addr->sin_addr.s_addr >> 24) & 0xff;
		int len = SNPRINTFA(remote_host_, ArrayCount(remote_host_) - 1, ("%d.%d.%d.%d"),
			s[0], s[1],s[2], s[3]);
#endif
		remote_host_[len] = 0;
		remote_port_ = htons(client_addr->sin_port);
	}
	else
	{
		ZeroMemory(&remote_addr_, sizeof(remote_addr_));
		remote_host_[0] = 0;
		remote_port_ = 0;
	}
}

void NetSession::Disconnected()
{
	Inherited::Disconnected();
	registed_ = false;
	client_name_[0] = 0;
	client_srv_idx_ = 0;
	client_type_ = SrvDef::InvalidServer;
}

bool NetSession::PreProcess(DataPacketReader* data_buf)
{
	//如果客户端尚未注册则处理注册数据包
	if (!registed_)
	{
		if (data_buf->getAvaliableLength() >= sizeof(SrvDef::SERVER_REGDATA))
		{
			SrvDef::SERVER_REGDATA* regData = (SrvDef::SERVER_REGDATA*)data_buf->getOffsetPtr();

			if (!OnValidateRegData(regData))
			{
				Close();
				return false;
			}

			registed_ = true;
			client_type_ = (SrvDef::SERVERTYPE)regData->ServerType;
			client_srv_idx_ = regData->ServerIndex;
			_STRNCPY_A(client_name_, regData->ServerName);
			data_buf->adjustOffset(sizeof(*regData));
			OutputMsg(rmTip, ("%s client (%s:%d:%d) registe success (%s)"), SrvDef::getServerTypeName((SrvDef::SERVERTYPE)client_type_),
			          GetRemoteHost(), GetRemotePort(), client_srv_idx_, client_name_);
		}
		else
		{
			Close();
			return false;
		}
	}

	return true;
}

