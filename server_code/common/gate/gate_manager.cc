#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include "_ast.h"

#include "x_thread.h"
#include "x_tick.h"
#include "x_lock.h"
#include "container/queue_list.h"
#include "net/base_socket.h"
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "gate_proto.h"
#include "server_def.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_session.h"
#include "net/server_socket.h"
#include "gate_user.h"
#include "gate_session.h"
#include "gate_manager.h"

GateManager::GateManager(const char* name) : Inherited(name)
{
	ZeroMemory(gate_list_, sizeof(gate_list_));
}

GateManager::~GateManager()
{
}

bool GateManager::Startup()
{
	for (int i = 0; i < MaxGateCount; ++i)
	{
		gate_list_[i]->gate_idx_ = i;
	}

	return Inherited::Startup();
}

NetSession* GateManager::NewSession(SOCKET s, sockaddr_in* addrIn)
{
	for (int i = 0; i < MaxGateCount; ++i)
	{
		if (!gate_list_[i]->connected())
		{
			gate_list_[i]->SetClientSocket(s, addrIn);
			gate_list_[i]->ClearSendBuffers();

			OutputMsg(rmWarning, "new gate connect,idx=%d", gate_list_[i]->gate_idx_);
			return gate_list_[i];
		}
	}

	return NULL;
}

void GateManager::DestroySession(NetSession*)
{
}


