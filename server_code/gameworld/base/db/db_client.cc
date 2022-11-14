#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif
#include "db_client.h"

using namespace SrvDef;
using namespace InterSrvComm;
using namespace InterSrvComm::DbServerProto;


DBClient::DBClient(GameServer* game_srv) : NetClient("DBClient"), 
	select_time_out_(0)
{
	game_server_ = game_srv;
	SetClientName(("data server"));
	free_.setLock(&lock_);

	memset(dbg_list_, 0, sizeof(dbg_list_));
}

DBClient::~DBClient()
{
	free_.flush();

	for (int i = 0; i < free_.count(); i++)
	{
		DataPacket* dp = free_[i];
		dp->setPosition(0);
		Flush(*dp);
	}

	free_.clear();
}

bool DBClient::ConnectToServer()
{
	//如果已连接则直接返回
	if (connected())
	{
		return true;
	}

	time_t now_t = NOW_T;

	if (now_t < reconn_t_ && getSocket() == INVALID_SOCKET)
	{
		return false;
	}

	//创建套接字
	if (getSocket() == INVALID_SOCKET)
	{
		SOCKET sock;
		int err = createSocket(&sock);

		if (err)
		{
			OutputError(err, ("create socket fail! %s "), client_name_);
			return false;
		}

		socket_ = sock;
		last_msg_t_ = NOW_T;

		sockaddr_in addrin;

		memset(&addrin, 0, sizeof(addrin));
		addrin.sin_family = AF_INET;
		addrin.sin_addr.s_addr = addr_;
		addrin.sin_port = htons((u_short)port_);

		// 必须要非阻塞
		setBlockMode(false);

		err = ::connect(socket_, (sockaddr*)&addrin, sizeof(addrin));

		if (err == 0)
		{
			connected_ = true;
			Connected();
			reconn_t_ = now_t + 5;
			return true;
		}
		// select 5s，如果还是失败，表示connect不上
		select_time_out_ = now_t + 5; 
	}
	else
	{
		// select
		timeval		tm;
		fd_set		set;
		tm.tv_sec	= 0;
		tm.tv_usec	= 0;
		FD_ZERO(&set);
		FD_SET(socket_, &set);
		int selectRet = ::select((int)socket_ + 1, NULL, &set, NULL, &tm);

		bool ret = false;

		if (selectRet > 0)			// 检查连接
		{
			int err = 0;
			socklen_t len = sizeof(err);
			::getsockopt(socket_, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
			ret = err == 0;
		}
		if (ret)
		{
			connected_ = true;
			Connected();
			reconn_t_ = now_t + 5;
			return true;
		}
		else if (now_t >= select_time_out_)
		{
			OutputMsg(rmError, "connect server time out!");
			Close();
			reconn_t_ = now_t + 5;
		}
		// 下次继续select
	}

	return false;
}

void DBClient::OnRecv(const uint16_t cmd, char* buf, int size)
{
	if (cmd <= 0) return; //是心跳包

	DataPacket* pack = AllocPostPacket();

	pack->writeBuf(buf, size);

	GameInterMsg msg;
	msg.msg_id_ = SSM_DB_RET_DATA;
	msg.data_.cmd_ = cmd;
	msg.data_.packet_ = pack;
	msg.data_.dbsid_ = serverId_;
	pack->setPosition(0);

	static GameEngine* ge = GetGameEngine();
	ge->PostMsg(msg);
}

int DBClient::GetLocalServerType()
{
	return T_GameServer;
}

const char* DBClient::GetLocalServerName()
{
	return game_server_->getServerName();
}

int DBClient::GetLocalServerIndex()
{
	return serverId_;
}

void DBClient::OnConnected()
{
	setRecvBufSize(8 * 1024 * 1024);
	setSendBufSize(8 * 1024 * 1024);

	GameEngine* ge = GetGameEngine();
	int localSid = ServerInstance()->GetServerIndex();
	if (ge && localSid == serverId_)
	{
		{
			DataPacket& pack = allocProtoPacket(MAKEINT16(siGlobal, dcCheckVer));
			pack << (int)InterSrvComm::DBSER_VER;
			flushProtoPacket(pack);
		}
		{
			DataPacket& pack = allocProtoPacket(MAKEINT16(siDefault, dcInitDB));
			flushProtoPacket(pack);
		}
		ge->InitComponent();
	}

	DataPacket& pack1 = allocProtoPacket(MAKEINT16(siGlobal, dcBattleFlag));
	pack1 << (int)localSid;
	if (ServerInstance()->IsBattleSrv() && localSid != serverId_)
	{
		pack1 << (int)1;	// 由战斗服发起，并且不是访问本战斗服的数据库的连接，dbsrver对于这种连接，不处理部分的逻辑，比如读取gmcmd，不刷新排行榜等等
	}
	else
	{
		pack1 << (int)0;
	}
	flushProtoPacket(pack1);			
}

void DBClient::WaitFor()
{
	OutputMsg(rmTip, "WAITING FOR FLUSHING ACTOR DATA...");
	size_t count;
	int64_t print_t = 0;

	while ((count = GetPacketCount() > 0))
	{
		SingleRun();

		Sleep(1);

		if (print_t <= _getTickCount())
		{
			print_t = _getTickCount() + 2000;
			OutputMsg(rmNormal, "%d PACKET(S) REMAIN", count);
		}
	}

	OutputMsg(rmTip, "FLUSH ACTOR DATA COMPLETE!");
}

void DBClient::FreeBackUserDataPacket(DataPacket* pack)
{
	free_.append(pack);
}

DataPacket* DBClient::AllocPostPacket()
{
	if (free_.count() <= 0)
	{
		free_.flush();
	}

	if (free_.count() <= 0)
	{
		AllocSendPack(&free_, 512);
	}

	DataPacket* dp = free_.pop();//得到一个空闲的Datapacket
	dp->setLength(0);
	return dp;
}

DataPacket& DBClient::allocProtoPacket(uint16_t cmd)
{
	dbg_list_[cmd]++;

	return WorkSocket::allocProtoPacket(cmd);
}

void DBClient::printStat()
{
	FILE* fp = fopen("db_dbg.txt", "w");
	if (fp)
	{
		char buf[512];
		for (size_t i = 0; i < ArrayCount(dbg_list_); ++i)
		{
			if (dbg_list_[i] != 0)
			{
				SNPRINTFA(buf, sizeof(buf), "%d,%d,%d\n", HIINT8(i), LOINT8(i), dbg_list_[i]);
				fputs(buf, fp);
			}
		}
		fclose(fp);
	}
}

bool DBClient::Startup()
{
	return true;
}

void DBClient::Stop()
{

}



