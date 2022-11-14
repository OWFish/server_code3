#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

DcApiMgr::DcApiMgr()
	: stop_log_(false)
{
	// 
}

DcApiMgr::~DcApiMgr()
{
	// 
}

void DcApiMgr::SetStopLog(bool sp)
{
	stop_log_ = sp;
}

void DcApiMgr::LogChat(Actor* et, int cid, const char* content, Actor* receiver/* = NULL*/)
{
	if(stop_log_ || !et || !content) return;

	// 把聊天内容的&转换成#
	static char content2[2048];
	_STRNCPY_A(content2, content);
	int len = (int)strlen(content2);
	for (int i=0; i<len; i++)
	{
		if (content2[i]=='&')
			content2[i] = '#';
	}

	//static TIPMSGCONFIG& tipmsg = *TIPMSGCONFIG::config_;
	/*int headsize = DcApiLogHead(send_buf_, sizeof(send_buf_), et, AC_ROLECHAT);
	SNPRINTFA(send_buf_+headsize, sizeof(send_buf_)-headsize, "&RZN=&RLV=%d&RNA=%s&RID=%d&OOID=%s&ORID=%d&ORNA=%s&RTN=2&RTI=%s&RTP=%s&RTI=%s&RTP=%s&ORLV=%d&ORZN=&CCH=%d&CCD=%s&CCO=%s"
		, et->GetIntProp(PROP_LEVEL), et->GetEntityName(), et->GetActorId(), receiver ? receiver->GetAccount() : "0", receiver ? receiver->GetActorId() : 0, receiver ? receiver->GetEntityName() : "0"
		, tipmsg.GetTip(tpJobDesc), GetJobDesc(et->GetIntProp(PROP_VOCATION)), tipmsg.GetTip(tpCampDesc), GetCampDesc(et->GetIntProp(PROP_CAMP))
		, receiver ? receiver->GetIntProp(PROP_LEVEL) : 0, cid, GetChannelName(cid), content2);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);*/
}

void DcApiMgr::LogMail(Actor* et, const char* receiver, int64_t mailId, const char* content)
{
	if(stop_log_ || !et || !receiver || !content) return;

	static TIPMSGCONFIG& tipmsg = *TIPMSGCONFIG::config_;
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	Actor* actor = em->GetActorPtrByName(receiver); // actor有可能为空，要判断
	char midstr[32];
	SNPRINTFA(midstr, sizeof(midstr), I64FMT, mailId);
	int headsize = DcApiLogHead(send_buf_, sizeof(send_buf_), et, AC_ROLESENDMAIL);
	SNPRINTFA(send_buf_+headsize, sizeof(send_buf_)-headsize, "&RLV=%d&RNA=%s&RID=%d&MID=%d&MTP=%d&MTD=%s&MCO=%d&OOID=%s&ORID=%d&ORNA=%s&ORTN=2&ORTI=%s&ORTP=%s&ORTI=%s&ORTP=%s&OOLV=%d&MTL=%s&MCT=%s&IID=%d&ICT=%d"
		, et->GetIntProp(P_LEVEL), et->GetEntityName(), et->GetActorId(), midstr, MT_PRIVATE, GetMailTypeDesc(MT_PRIVATE), SEND_MAIL_COST, actor ? actor->GetAccount() : "0"
		, actor ? actor->GetActorId() : 0, receiver, tipmsg.GetTip(tpJobDesc), actor ? GetJobDesc(actor->GetIntProp(P_VOCATION)) : "0"
		, tipmsg.GetTip(tpCampDesc), actor ? GetCampDesc(actor->GetIntProp(P_CAMP)) : "0", actor ? actor->GetIntProp(P_LEVEL) : 0 ,"", content, 0, 0);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);
}

/*
 *func: 生成P2P交易信息，但是为简单起见，对同一种道具分成多份的，计算成多种道具
 *para: log_send发送日志方角色，corpt 交易另一方
 *return; 无
*/
void DcApiMgr::LogP2PTrade(Actor* log_send, Actor* corpt)
{
	if (stop_log_ || !log_send || !corpt)
	{
		return;
	}

	int sizedata = 0;
	int tmp = 0;
	Actor* lauch = NULL;
	Actor* accpt = NULL;

	//memset(send_buf_, 0, sizeof(send_buf_));

	if (log_send->GetDealSystem().is_deal_launchor)
	{
		lauch = log_send;
		accpt = corpt;
	}
	else
	{
		lauch = corpt;
		accpt = log_send;	
	}


	DealSystem& dealSys_lauch = lauch->GetDealSystem();
	UserBag& lauchBag = lauch->GetBagSystem();
	DealSystem::DealItemList& launchItems = dealSys_lauch.GetDealItemList();

	DealSystem& dealSys_accpt = accpt->GetDealSystem();
	UserBag& accptBag = accpt->GetBagSystem();	
	DealSystem::DealItemList& accptItems = dealSys_accpt.GetDealItemList();

	static TIPMSGCONFIG& tipConfig = *TIPMSGCONFIG::config_;
	
	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), log_send,AC_P2PTRADE)) < 0)
	{
		return;
	}
	sizedata += tmp;

	//角色A，交易发起人的信息
	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&RIDA=%lld&ITNA=%d", lauch->GetActorId(),launchItems.count() )) < 0 )
	{
		return;
	}
	sizedata += tmp;

	//A道具
	for (int i = 0; i < launchItems.count(); i++)
	{
		ItemData* item_ptr = lauchBag.FindItemByGuid(launchItems[i].guid_, NULL);
		if (!item_ptr)
		{
			continue;
		}
		if ((tmp =  SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&ITDA=%d&ICA=%d",item_ptr->wItemId, item_ptr->count_)) < 0)
		{
			return;
		}
		sizedata += tmp;	
	}

	const char* str_money_type_yuanbao = tipConfig.GetTip(tpMoneyTypeYuanbao);
	if(!str_money_type_yuanbao) return;
	const char* str_money_type_coin = tipConfig.GetTip(tpMoneyTypeCoin);
	if(!str_money_type_coin) return;

	//A货币
	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&CTNA=%d&CTDA=%s&CCA=%d&CBTA=%d&CTDA=%s&CCA=%d&CBTA=%d", COUNT_CHARGE_MONEY_TYPE, 
		str_money_type_yuanbao, dealSys_lauch.GetYuanBao(),lauch->GetMoneyCount(mtYuanbao),str_money_type_coin , dealSys_lauch.GetCoin(), lauch->GetMoneyCount(mtCoin))) < 0)
	{
		return;
	}
	sizedata += tmp;

	//角色B的信息
	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&OIDB=%s&RIDB=%lld&UIPB=%s&ITNB=%d",
		accpt->GetAccount(), accpt->GetActorId(), accpt->GetLastLoginIp(), accptItems.count())) < 0)
	{
		return;
	}
	sizedata += tmp;


	//B道具
	for (int i = 0; i < accptItems.count(); i++)
	{
		ItemData* item_ptr = accptBag.FindItemByGuid(accptItems[i].guid_, NULL);
		if (item_ptr)
		{
			continue;
		}
		if ((tmp =  SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&ITDB=%d&ICB=%d",item_ptr->wItemId, item_ptr->count_)) < 0)
		{
			return;
		}
		sizedata += tmp;	
	}



	//B货币
	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&CTNB=%d&CTDB=%s&CCB=%d&CBTB=%d&CTDB=%s&CCB=%d&CBTB=%d", COUNT_CHARGE_MONEY_TYPE,
		str_money_type_yuanbao, dealSys_accpt.GetYuanBao(),accpt->GetMoneyCount(mtYuanbao), str_money_type_coin, dealSys_accpt.GetCoin(), accpt->GetMoneyCount(mtCoin))) < 0)
	{
		return;
	}
	sizedata += tmp;

	

	//这个可以放到私有成员数据中吧
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);


}


/*
 *func: 发送道具变化信息
 *para: actor玩家信息，pUserItem 道具, nCountchg 道具变化数量 lpsender发送者，这里我们用来表示原因
 *return; 无
*/
void DcApiMgr::LogItemChange(Actor* actor, const ItemData* pUserItem,const StdItem* pStdItem, const int nCountChg, const char* lpSender, const int nTgtId, const char* sTargetName)
{
	if (stop_log_ || !actor || !pUserItem || !lpSender  )
	{
		return;
	}
	(void)pStdItem;
	(void)nTgtId;
	(void)sTargetName;

	int sizedata = 0;
	int tmp = 0;
//	memset(send_buf_, 0, sizeof(send_buf_));


	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor,AC_ITEMCHANGE)) < 0)
	{
		return;
	}
	sizedata += tmp;

	tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&RID=%lld&IID=%d&ICT=%d&RSN=%s&FID=%s&TPE=%d&QCC=%d",
		actor->GetActorId(), pUserItem->series, abs(nCountChg), lpSender, "", (nCountChg > 0)?1:0, 0);

	if (tmp < 0)
	{
		return;
	}

	//这个可以放到私有成员数据中吧
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);

}


/*
 *func: 
 *para: 
 *return; 无
*/
void DcApiMgr::LogGoldChange(Actor* actor, int moneyType,int amount, int value, 
	const char* phylum,
	const char* classfield,
	const char* family,
	const char* genus,
	const char* extra,
	bool ispay)
{
	if (stop_log_ || !actor || !phylum  )
	{
		return;
	}
	(void)classfield;
	(void)family;
	(void)genus;
	(void)extra;
	(void)ispay;

	int sizedata = 0;
	int tmp = 0;
	//memset(send_buf_, 0, sizeof(send_buf_));


	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor,AC_GOLDCHANGE)) < 0)
	{
		return;
	}
	sizedata += tmp;

	static TIPMSGCONFIG& tipConfig = *TIPMSGCONFIG::config_;

	const char* pstr_money_type = NULL;
	switch (moneyType)
	{
	case mtBindCoin:
		pstr_money_type = tipConfig.GetTip(tpMoneyTypeBindCoin);

		break;

	case mtCoin:
		pstr_money_type = tipConfig.GetTip(tpMoneyTypeCoin);

		break;

	case mtBindYuanbao:
		pstr_money_type = tipConfig.GetTip(tpMoneyTyeBindYuanbao);

		break;

	case mtYuanbao:

		return;

	default:
		return;
	}



	tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&RID=%lld&GID=%s&GOD=%d&RSN=%s&FID=%s&TPE=%d", 
		actor->GetActorId(),pstr_money_type, abs(amount)*value, phylum, "", (amount > 0)?1:0);

	if (tmp < 0)
	{
		return;
	}


	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);


}

/*
 *func: 
 *para: 
 *return; 无
*/
void DcApiMgr::LogCashCahnge(Actor* actor, int moneyType,int amount, int value, const char* phylum,const char* classfield, const char* family, const char* genus, const char* extra, bool)
{
	if (stop_log_ || !actor ||  !phylum)
	{
		return;
	}
	(void)classfield;
	(void)family;
	(void)genus;
	(void)extra;
	
	int sizedata = 0;
	int tmp = 0;
	//memset(send_buf_, 0, sizeof(send_buf_));

	if (moneyType != mtYuanbao)
	{
		return;
	}

	static TIPMSGCONFIG& tipConfig = *TIPMSGCONFIG::config_;
	const char* pstr_money_type = tipConfig.GetTip(tpMoneyTypeYuanbao);
	
	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor,AC_CASHCHANGE)) < 0)
	{
		return;
	}
	sizedata += tmp;


	tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata, "&RID=%lld&CID=%s&CAS=%d&RSN=%s&FID=%s&TPE=%d&QCC=%d", 
		actor->GetActorId(),pstr_money_type, abs(amount)*value, phylum, "", (amount > 0)?1:0, 0);

	if (tmp < 0)
	{
		return;
	}

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);

}

/*
 *func: 角色摆摊
 *para: evid 摆摊开关， guid 物品 money类型
 *return; 无
*/
void DcApiMgr::LogRoleVendor(Actor* actor, bool evid,  unsigned int handle)
{
	if (stop_log_ || !actor)
	{
		return;
	}

	int tmp = 0;
	int sizedata = 0;

	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor,AC_ROLEVENDOR)) < 0)
	{
		return;
	}
	sizedata += tmp;

	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&RID=%lld&EID=%d&SNA=%d", actor->GetActorId(), evid?1:2, handle)) < 0)
	{
		return;
	}

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);

}

/*
 *func: 角色组对
 *para: actor 发送信息的玩家, team所在队伍
 *return; 无
*/
void DcApiMgr::LogRoleTeam(Actor* actor, Team* team)
{
	if (stop_log_ || !actor || !team)
	{
		return;
	}

	int tmp = 0;
	int sizedata = 0;

	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor,AC_ROLETEAM)) < 0)
	{
		return;
	}
	sizedata += tmp;

	Actor* leader = team->GetCaptin();
	if (!leader) return;

	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&TID=%u&OID=%s&RNA=%s&RoleID=%d&MNU=%d&PNA=%d",
		   team->GetTeamID(), leader->GetAccount(), leader->GetEntityName(), leader->GetActorId(), team->GetOnlineUserCount(), team->GetFbId())) < 0)
	{
		return;
	}

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);
}

/*
 *func: 玩家通用信息
 *para: 
 *return; 无
*/
void DcApiMgr::LogGameMsgRP(Actor* actor,unsigned long long msgid, char* msg)
{
	if (stop_log_ || !actor || !msg)
	{
		return;
	}

	int tmp = 0;
	int sizedata = 0;

	if ((tmp = DcApiLogHead(send_buf_, sizeof(send_buf_), actor, AC_GAMEMSGRP)) < 0)
	{
		return;
	}
	sizedata += tmp;

	if ((tmp = SNPRINTFA(send_buf_ + sizedata, sizeof(send_buf_) - sizedata,"&MSID=%ull&RID=ull&UIC=%s", msgid, actor->GetActorId(), msg)) < 0)
	{
		return;
	}

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogDcApiLogByStr("appoperlog", send_buf_);

}

/*
const char* DcApiMgr::GetChannelName(int cid)
{
	if (cid < 0 || cid >= ciChannelMax)
		return "";

	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	return mgr.GetTip(tpChannelSecret+cid);
}
*/

int DcApiMgr::DcApiLogHead(char* buf, int len, Actor* actor, int aid)
{
	//if(!buf) return 0;

	//if (!actor)
	//{
	//	buf[0] = 0;
	//	return 0;
	//}

	//static GameServer* gs = ServerInstance();

	//static char timeStr[32];
	//SNPRINTFA(timeStr, sizeof(timeStr), I64FMT, ServerInstance()->getUnixTime());

	//// APPV=1.0&MSGV=1.1&VER=1.3&APPID=100634204&OID=efad1235t67d&WID=1&UIP=178.14.147.12&OKY=&SIP=172.25.14.14&MTM=1320056796032&DOM=1&MLV=0&AID=1
	//// APPV:应用程序版本号, MSGV:协议版本号, VER:DC API版本,OID:openid,wid:world id,uip:用户ip,oky:open key,可空,SIP:server ip,MTM:操作时间,DOM:平台,MLV:msg level,AID:action id
	//return SNPRINTFA(buf, len, "APPV=1.0&MSGV=1.1&VER=1.3&APPID=100634204&OID=%s&WID=%d&UIP=%s&OKY=&SIP=%s&MTM=%s&DOM=%d&MLV=0&AID=%d"
	//	, actor->GetAccount(), gs->GetServerIndex(), actor->GetLastLoginIp(), gs->getServerIP(), timeStr, actor->GetPfId(), aid);
	return 0;
}

const char* DcApiMgr::GetMailTypeDesc(int tp)
{
	if (tp < 0 || tp >= MT_COUNT) return "";

	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	return mgr.GetTip(tpMailTypeSystem+tp);
}

const char* DcApiMgr::GetJobDesc(int job)
{
	static int ids[] = { tpJob1, tpJob2, tpJob3, tpJob4 };

	// 1 - 4
	if (job < 1 || job > 4 ) return "";

	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	return mgr.GetTip(ids[job-1]);
}

const char* DcApiMgr::GetCampDesc(int camp)
{
	static int ids[] = { tpCamp1, tpCamp2, tpCamp3 };

	// 1 - 3
	if (camp < 1 || camp > 3 ) return "";

	static TIPMSGCONFIG& mgr = *TIPMSGCONFIG::config_;
	return mgr.GetTip(ids[camp-1]);
}

