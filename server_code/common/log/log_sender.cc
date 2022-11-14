#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include "_ast.h"

#include "x_tick.h"
#include "x_lock.h"
#include "container/queue_list.h"
#include "net/base_socket.h"
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "appitnmsg.h"
#include "data_packet.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_client.h"
#include "server_def.h"
#include "log_def.h"
#include "encrypt/CRC.h"
#include "encrypt/Encrypt.h"
#include "log_sender.h"



using namespace SrvDef;

LogSender::LogSender(int ServerType, int ServerIndex, char* ServerName) : NetClient("LogSender")
{
	this->ServerType = ServerType;
	this->ServerIndex = ServerIndex;
	_STRNCPY_A(this->ServerName, ServerName);
	this->SetClientName(("logger server"));

	stop_log_ = false;
	stop_counter_log_ = false;
	stop_economy_log_ = false;
}

LogSender::LogSender() : NetClient("LogSender")
{
	this->SetClientName(("logger server"));

	stop_log_ = false;
	stop_counter_log_ = false;
	stop_economy_log_ = false;
}

LogSender::~LogSender(void)
{
}

void LogSender::SetServerName(const char* sServerName)
{
	_STRNCPY_S(ServerName, sServerName, ArrayCount(ServerName) - 1);
	ServerName[ArrayCount(ServerName) - 1] = 0;
}
int LogSender::GetLocalServerType()
{
	return ServerType;
}

const char* LogSender::GetLocalServerName()
{
	return ServerName;
}

int LogSender::GetLocalServerIndex()
{
	return ServerIndex;
}

void LogSender::OnConnected()
{
	setRecvBufSize(1024 * 1024);
	setSendBufSize(1024 * 1024);
}

void LogSender::LogCounter(ActorId actorId, const char* aid, const char* user_level /*= ""*/,
                           const char* counter /*= ""*/, const char* value /*= ""*/, const char* extra /*= ""*/,
                           const char* kingdom /*= ""*/, const char* phylum /*= ""*/, const char* classfield /*= ""*/,
                           const char* family /*= ""*/, const char* genus /*= ""*/, int flag)
{
	if (stop_log_ || stop_counter_log_) return;

	LCounter data;
	memset(&data, 0, sizeof(data));

	data.actorid_ = actorId;
	data.flag_ = flag;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (user_level)
	{
		_STRNCPY_A(data.user_level_, user_level);
	}

	if (counter)
	{
		_STRNCPY_A(data.counter_, counter);
	}

	if (value)
	{
		_STRNCPY_A(data.value_, value);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	if (kingdom)
	{
		_STRNCPY_A(data.kingdom_, kingdom);
	}

	if (phylum)
	{
		_STRNCPY_A(data.phylum_, phylum);
	}

	if (classfield)
	{
		_STRNCPY_A(data.classfield_, classfield);
	}

	if (family)
	{
		_STRNCPY_A(data.family_, family);
	}

	if (genus)
	{
		_STRNCPY_A(data.genus_, genus);
	}

	DataPacket& pdata = allocProtoPacket(lmCounter);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogDcApiLogByStr(const char* logName, const char* logContent)
{
	if (stop_log_) return;
	
	if(!logName || !logContent)	return;
	LDcApiData data;
	memset(&data, 0, sizeof(data));
	data.log_type_ = 4;
	_STRNCPY_A(data.log_name_, logName);
	_STRNCPY_A(data.content_ ,logContent);
	DataPacket& pdata = allocProtoPacket(lmDcApiData);
	pdata << data;
	flushProtoPacket(pdata);
}


void LogSender::LogDcApiProto(const char* openId, int pfId, int serverId, int roleId, int systemId, int protoId, int protoType, int protoResult, const char* svrip, const char* userip)
{
	//if (!et || ((Entity*)et)->GetType() != enActor)
	//	return;
	//Actor* pActor =(Entity*)et;
	if (stop_log_) return;

	if(!openId)	return;

	LDcApiProtoLog logData;
	memset(&logData, 0, sizeof(logData));

	//_STRNCPY_A(logData.openId, pActor->GetAccount());
	_STRNCPY_A(logData.openId, openId);
	logData.domain = pfId;
	//logData.serverId = ServerInstance()->GetServerIndex();
	logData.serverId = serverId;
	_STRNCPY_A(logData.svrip, svrip);
	_STRNCPY_A(logData.userip, userip);

	//logData.roleId = pActor->GetActorId();
	logData.roleId = roleId;
	logData.protoId = MAKEINT16(protoId, systemId);
	logData.gameFeatrueId = systemId;
	logData.protoType = protoType;
	logData.protoResult = protoResult;

	DataPacket& pdata = allocProtoPacket(lmDcApiProto);
	pdata << logData;
	flushProtoPacket(pdata);
}



void LogSender::LogInstall(const char* aid, const char* source /*= ""*/,
                           const char* affiliate /*= ""*/, const char* creative /*= ""*/,
                           const char* family /*= ""*/, const char* genus /*= ""*/,
                           const char* from_uid /*= ""*/ , const char* extra, int flag/* = 3*/)
{
	if (stop_log_) return;
	
	LInstall data;
	memset(&data, 0, sizeof(data));

	data.flag_ = flag;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (source)
	{
		_STRNCPY_A(data.source_, source);
	}

	if (affiliate)
	{
		_STRNCPY_A(data.affiliate_, affiliate);
	}

	if (creative)
	{
		_STRNCPY_A(data.creative_, creative);
	}

	if (family)
	{
		_STRNCPY_A(data.family_, family);
	}

	if (genus)
	{
		_STRNCPY_A(data.genus_, genus);
	}

	if (from_uid)
	{
		_STRNCPY_A(data.from_uid_, from_uid);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	DataPacket& pdata = allocProtoPacket(lmInstall);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogDau(const char* aid, const char* source /*= ""*/,
                       const char* affiliate /*= ""*/, const char* creative /*= ""*/,
                       const char* family /*= ""*/, const char* genus /*= ""*/,
                       const char* ip /*= ""*/, const char* from_uid /*= ""*/, const char* extra, int flag/* = 3*/)
{
	if (stop_log_) return;

	LDau data;
	memset(&data, 0, sizeof(data));

	data.flag_ = flag;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (source)
	{
		_STRNCPY_A(data.source_, source);
	}

	if (affiliate)
	{
		_STRNCPY_A(data.affiliate_, affiliate);
	}

	if (creative)
	{
		_STRNCPY_A(data.creative_, creative);
	}

	if (family)
	{
		_STRNCPY_A(data.family_, family);
	}

	if (genus)
	{
		_STRNCPY_A(data.genus_, genus);
	}

	if (ip)
	{
		_STRNCPY_A(data.ip_, ip);
	}

	if (from_uid)
	{
		_STRNCPY_A(data.from_uid_, from_uid);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	DataPacket& pdata = allocProtoPacket(lmDau);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogEnconomy(ActorId actorid, const char* aid, const char* currency /*= ""*/,
                            const char* amount /*= ""*/, const char* value /*= ""*/,
                            const char* kingdom /*= ""*/, const char* phylum /*= ""*/,
                            const char* classfield /*= ""*/, const char* family /*= ""*/,
                            const char* genus /*= ""*/ , const char* extra, const char* extra2, const char* pf, int flag/* = 3*/,
							bool isPay, const char* openkey, const char* pfkey, const char* pfid)
{
	if (stop_log_ || stop_economy_log_) return;

	LEconomy data;
	memset(&data, 0, sizeof(data));

	data.flag_ = flag;
	data.flag_ |= (isPay ? lfiIsPay : 0);

	data.actorid_ = actorid;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (currency)
	{
		_STRNCPY_A(data.currency_, currency);
	}

	if (amount)
	{
		_STRNCPY_A(data.amount_, amount);
	}

	if (value)
	{
		_STRNCPY_A(data.value_, value);
	}

	if (kingdom)
	{
		_STRNCPY_A(data.kingdom_, kingdom);
	}

	if (phylum)
	{
		_STRNCPY_A(data.phylum_, phylum);
	}

	if (classfield)
	{
		_STRNCPY_A(data.classfield_, classfield);
	}

	if (family)
	{
		_STRNCPY_A(data.family_, family);
	}

	if (genus)
	{
		_STRNCPY_A(data.genus_, genus);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	if (extra2)
	{
		_STRNCPY_A(data.extra2_, extra2);
	}

	if (pf)
	{
		_STRNCPY_A(data.pf_, pf);
	}

	if (openkey)
	{
		_STRNCPY_A(data.openkey_, openkey);
	}

	if (pfkey)
	{
		_STRNCPY_A(data.pfkey_, pfkey);
	}

	if (pfid) {
		_STRNCPY_A(data.pfid_, pfid);
	}

	DataPacket& pdata = allocProtoPacket(lmEconomy);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogMilestone(ActorId actorid, const char* aid, const char* milestone /*= ""*/, const char* value /*= ""*/, const char* extra, int flag/* = 3*/)
{
	if (stop_log_) return;

	LMilestone data;
	memset(&data, 0, sizeof(data));

	data.flag_ = flag;
	data.actorid_ = actorid;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (milestone)
	{
		_STRNCPY_A(data.milestone_, milestone);
	}

	if (value)
	{
		_STRNCPY_A(data.value_, value);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	DataPacket& pdata = allocProtoPacket(lmMilestone);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogPayment(int ret, ActorId actorId, const char* aid, int amount,
                           int mstType, int p1, int p2, int p3,
                           int value /*= 1*/, const char* kingdom /*= ""*/, const char* phylum /*= ""*/, const char* transactionid /*= ""*/,
                           const char* extra /*= ""*/, int p4 /*= 0*/, int p5 /*= 0*/, int flag/* = 3*/)
{
	if (stop_log_) return;

	LPayment data;
	memset(&data, 0, sizeof(data));
	data.ret_ = ret;
	data.actorId_ = actorId;
	data.amount_ = amount;
	data.value_ = value;
	data.mstType_ = mstType;
	data.p1_ = p1;
	data.p2_ = p2;
	data.p3_ = p3;
	data.p4_ = p4;
	data.p5_ = p5;
	data.flag_ = flag;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (kingdom)
	{
		_STRNCPY_A(data.kingdom_, kingdom);
	}

	if (phylum)
	{
		_STRNCPY_A(data.phylum_, phylum);
	}

	if (transactionid)
	{
		_STRNCPY_A(data.transactionid_, transactionid);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	DataPacket& pdata = allocProtoPacket(lmPayment);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogGameInfo(const char* aid, const char* user_level /*= ""*/, 
	const char* value /*= ""*/, const char* extra /*= ""*/, const char* kingdom /*= ""*/, 
	const char* phylum /*= ""*/, const char* classfield /*= ""*/, const char* family /*= ""*/, 
	const char* genus /*= ""*/,
	int flag/* = 3*/)
{
	if (stop_log_) return;

	LGameInfo data;
	memset(&data, 0, sizeof(data));

	data.flag_ = flag;

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (user_level)
	{
		_STRNCPY_A(data.user_level_, user_level);
	}

	if (value)
	{
		_STRNCPY_A(data.value_, value);
	}

	if (extra)
	{
		_STRNCPY_A(data.extra_, extra);
	}

	if (kingdom)
	{
		_STRNCPY_A(data.kingdom_, kingdom);
	}

	if (phylum)
	{
		_STRNCPY_A(data.phylum_, phylum);
	}

	if (classfield)
	{
		_STRNCPY_A(data.classfield_, classfield);
	}

	if (family)
	{
		_STRNCPY_A(data.family_, family);
	}

	if (genus)
	{
		_STRNCPY_A(data.genus_, genus);
	}

	DataPacket& pdata = allocProtoPacket(lmGameInfo);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogChat(const char* aid, const char* name, const char* ip, const char* pf, int actorid, int type, 
	const char* content, const char* toaid /* = "" */, const char* toname /* = "" */)
{
	if (stop_log_) return;

	LChat data;
	memset(&data, 0, sizeof(data));

	if (aid)
	{
		_STRNCPY_A(data.aid_, aid);
	}

	if (name)
	{
		_STRNCPY_A(data.name_, name);
	}

	if (pf)
	{
		_STRNCPY_A(data.pf_, pf);
	}

	if (ip)
	{
		_STRNCPY_A(data.ip_, ip);
	}

	data.type_ = type;

	data.actorid_ = actorid;

	if (content)
	{
		_STRNCPY_A(data.content_, content);
	}

	if (toaid)
	{
		_STRNCPY_A(data.toaid_, toaid);
	}

	if (toname)
	{
		_STRNCPY_A(data.toname_, toname);
	}

	DataPacket& pdata = allocProtoPacket(lmChat);
	pdata << data;
	flushProtoPacket(pdata);
}

void LogSender::LogOnline(int cnt, int extra)
{
	if (stop_log_) return;

	DataPacket& pdata = allocProtoPacket(lmOnline);
	pdata << (int)cnt;
	pdata << (int)extra;
	flushProtoPacket(pdata);
}

void LogSender::LogTLog(const char* logstr)
{
	if (stop_log_) return;

	DataPacket& pdata = allocProtoPacket(lmTLog);
	pdata.writeString(logstr);
	flushProtoPacket(pdata);
}

void LogSender::LogDKMLog(const char* logstr, const char* pf)
{
	if (!logstr || !pf) return;
	if (stop_log_) return;

	DataPacket& pdata = allocProtoPacket(lmDKMLog);
	pdata.writeString(logstr);
	pdata.writeString(pf);
	flushProtoPacket(pdata);
}

