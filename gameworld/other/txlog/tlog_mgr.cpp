#include "StdAfx.h"
#ifndef _MSC_VER
#include "../StdAfx.h"
#endif

const char* TLogReplace(const char* instr, int idx /*= 0*/)
{
	static const int MAX_REPLACE_ITEM = 8;
	static const int MAX_REPLACE_LEN = 256;

	if (!instr || idx < 0 || idx >= MAX_REPLACE_ITEM)
		return "";

	int len = (int)strlen(instr);

	if (len > MAX_REPLACE_LEN)
		return "";

	static char retBuf[MAX_REPLACE_ITEM][MAX_REPLACE_LEN + 1];

	char* outstr = retBuf[idx];

	for (int i = 0; i < len; i++)
	{
		if (instr[i] == '|')
			outstr[i] = '#';
		else
			outstr[i] = instr[i];
	}

	outstr[len] = 0;
	return outstr;
}

const char* ReplaceString(const char* instr, char* outstr, int outlen)
{
	int len = (int)strlen(instr);
	if (len >= outlen)
		len = outlen - 1;

	for (int i = 0; i < len; i++)
	{
		if (instr[i] == '|')
			outstr[i] = '#';
		else
			outstr[i] = instr[i];
	}
	outstr[len] = 0;
	return outstr;
}

bool TlogMgr::open_log_(true);

TlogMgr::TlogMgr()
{
	event_id_.ival_ = 0;
}

TlogMgr::~TlogMgr()
{

}

void TlogMgr::Log(const char* fmt, ...)
{
	if (!open_log_) return;

	va_list	args;
	va_start(args, fmt);
	INT_PTR ret = VSNPRINTFA(send_buf_, TLOG_BUFFER_SIZE - 1, fmt, args);
	va_end(args);

	if (ret <= 0) return;

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogOnlineCount(int cnt)
{
	if (!open_log_) return;

	// OnlineCount|iEventId|dtEventTime|iWorldId|iPlayerCount
	SNPRINTFA(send_buf_, sizeof(send_buf_), "OnlineCount|%s|%s|%d|%d", GetEventId(), GetTime(), ServerInstance()->GetServerIndex(), cnt);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogCreateRole(const char* accountname, int accountid, const char* name, int job, int sex, int pfid, const char* addr)
{
	if(!open_log_) return;

	char buf[TLOG_BUFFER_SIZE];

	char eidstr[64] = { 0 };
	static unsigned int series = 0;
	EventId eid;

	// 时间 + 序号
	eid.sval_.time_ = (unsigned int)NOW_T;
	eid.sval_.series_ = (series > (unsigned int) - 1 ? 0 : series + 1);

#ifdef _MSC_VER
	SNPRINTFA(eidstr, sizeof(eidstr), "%I64u", eid.ival_);
#else
	SNPRINTFA(eidstr, sizeof(eidstr), "%llu", eid.ival_);
#endif

	char timestr[64];
	SystemTime sys_t;
	GetSystemTime(sys_t);
	SNPRINTFA(timestr, ArrayCount(timestr),
		"%02d-%02d-%02d %02d:%02d:%02d",
		sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_, sys_t.min_, sys_t.sec_);

	ACTORNAME name2;
	ReplaceString(name, name2, ArrayCount(name2));

	// CreateRole|iEventId|dtEventTime|iWorldId|iUin|vClientIp|iRoleId|vRoleName|iJobId|iGrender|iLoginWay
	SNPRINTFA(buf, sizeof(buf), "CreateRole|%s|%s|%d|%s|%s|%d|%s|%d|%d|%d", eidstr, timestr, ServerInstance()->GetServerIndex()
	          , accountname, addr, accountid, name2, job, sex, pfid);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(buf);
}

void TlogMgr::LogPartyBuild(Guild& guild, Actor& actor)
{
	if (!open_log_) return;

	// iEventId|vUin|dtEventTime|iWorldId|vRoleName|iPartyId|vPartyName|iPartyLevel|iPartyMoney|iPartyPolity
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PartyBuild|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d", GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex()
	          , TLogReplace(actor.GetEntityName()), guild.id_, TLogReplace(guild.name_, 1), guild.GetLevel(), guild.GetStone(), guild.GetMemberCount());
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPartyDismiss(Guild& guild)
{
	if (!open_log_) return;

	// PartyDismiss|iEventId|vUin|dtEventTime|iWorldId|vRoleName|iPartyId|iPartyName|iPartyLevel|iPartyMoney|iPartyPolity
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PartyDismiss|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d", GetEventId(), "", GetTime(), ServerInstance()->GetServerIndex()
	          , "", guild.id_, TLogReplace(guild.name_, 1), guild.GetLevel(), guild.GetStone(), guild.GetMemberCount());
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPartyLevelUp(Guild& guild, Actor& actor)
{
	// PartyLevelUp|iEventId|vUin|dtEventTime|iWorldId|vRoleName|iPartyId|vPartyName|iPartyLevel|iPartyMoney|iPartyPolity
	if (!open_log_) return;

	SNPRINTFA(send_buf_, sizeof(send_buf_), "PartyLevelUp|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d"
	          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), TLogReplace(actor.GetEntityName()), guild.id_, guild.name_, guild.GetLevel(), guild.GetStone(), guild.GetMemberCount());
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPartyAddMember(Guild& guild, Actor& actor, Actor* byactor)
{
	if (!open_log_) return;

	// iEventId|vUin|dtEventTime|iWorldId|vRoleName|iPartyId|vPartyName|iPartyLevel|iPartyMoney|iPartyPolity|vAddMemberName
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PartyAddMember|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d|%s", GetEventId(), byactor ? byactor->GetAccount() : "", GetTime(), ServerInstance()->GetServerIndex()
	          , byactor ? TLogReplace(byactor->GetEntityName()) : "", guild.id_, TLogReplace(guild.name_, 1), guild.GetLevel(), guild.GetStone(), guild.GetMemberCount(), TLogReplace(actor.GetEntityName(), 2));
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPartyDelMember(Guild& guild, Actor& byactor, const char* name)
{
	if (!open_log_) return;

	// PartyDelMember|iEventId|vUin|dtEventTime|iWorldId|vRoleName|iPartyId|vPartyName|iPartyLevel|iPartyMoney|iPartyPolity|vDelMemberName
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PartyDelMember|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d|%s"
	          , GetEventId(), byactor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(),
	          TLogReplace(byactor.GetEntityName()), guild.id_, TLogReplace(guild.name_, 1), guild.GetLevel(), guild.GetStone(), guild.GetMemberCount(), TLogReplace(name, 2));
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogShop(Actor& actor, int moneyType, int money, const ItemOPParam& item, ItemSeries& guid)
{
	//if (!open_log_) return;

	//char guidstr[64];
	//SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, guid.llId);

	//// Shop|iEventId|vUin|dtEventTime|iWorldId|vClientIp|iRoleId|vRoleName|iRoleLevel|iCostType|iCost|iRemain|iGoodsType|iGoodsId|iGoodsNum|iItemGuild|vReMarks|iLoginWay
	//SNPRINTFA(send_buf_, sizeof(send_buf_), "Shop|%s|%s|%s|%d|%s|%d|%s|%d|%d|%d|%d|%d|%d|%d|%s|%s|%d"
	//	, GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetLastLoginIp(), actor.GetActorId()
	//	, TLogReplace(actor.GetEntityName()), actor.GetIntProp(PROP_LEVEL), moneyType, money, actor.GetMoneyCount(moneyType), ltAlays
	//	, item.wItemId, item.btCount, guidstr, "", actor.GetPfId());
	//static LogSender* log = ServerInstance()->GetLogClient();
	//log->LogTLog(send_buf_);
}

void TlogMgr::LogPlayerKill(Actor* actor, Actor* killer)
{
	// PlayerKill|iEventId|vKilledUin|dtEventTime|iWorldId|iKilledRoleId|vKilledName|iKillJobId|iKillGrender|iKilledLevel
	// vKillerUin|iKillerRoleId|vKillerName|iKillerJobId|iKillerGender|iKillerLevel|iMapId|iPosX|iPosY

	if (!open_log_) return;

	if (!actor || !killer) return;

	SNPRINTFA(send_buf_, sizeof(send_buf_), "PlayerKill|%s|%s|%s|%d|%d|%s|%d|%d|%d|%s|%d|%s|%d|%d|%d|%d|%d|%d"
	          , GetEventId(), actor->GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor->getId(), TLogReplace(actor->GetEntityName()), actor->GetIntProp(P_VOCATION), actor->GetIntProp(P_SEX)
	          , actor->GetIntProp(P_LEVEL), killer->GetAccount(), killer->getId(), TLogReplace(killer->GetEntityName(), 1), killer->GetIntProp(P_VOCATION), killer->GetIntProp(P_SEX)
	          , killer->GetIntProp(P_LEVEL), actor->GetSceneID(), actor->GetIntProp(P_POS_X), actor->GetIntProp(P_POS_Y));
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogMonsterKilled(Monster& mon, TLogItem* pitem, int& nitem, int reason)
{
	if (!open_log_) return;

	static LogSender* log = ServerInstance()->GetLogClient();
	if (nitem > 0)
	{
		char guidstr[64];
		const char* eid = GetEventId();
		for (int i=0; i<nitem; i++)
		{
			TLogItem& item = pitem[i];

			SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, item.guid_);

			// MonsterKilled|iEventId|iMonsterId|dtEventTime|iWorldId|iMapId|iPosX|iPosY|iDropItemId|iDropItemType|iDropItemNum|iGuid|iReason
			SNPRINTFA(send_buf_, sizeof(send_buf_), "MonsterKilled|%s|%d|%s|%d|%d|%d|%d|%d|%d|%d|%s|%d"
				, eid, mon.getId(), GetTime(), ServerInstance()->GetServerIndex(), mon.GetSceneID(), mon.GetIntProp(P_POS_X), mon.GetIntProp(P_POS_Y)
				, item.id_, ltAlays, item.count_, guidstr, 0);
			log->LogTLog(send_buf_); 
		}
	}
	else
	{
		// MonsterKilled|iEventId|iMonsterId|dtEventTime|iWorldId|iMapId|iPosX|iPosY|iDropItemId|iDropItemType|iDropItemNum|iGuid|iReason
		SNPRINTFA(send_buf_, sizeof(send_buf_), "MonsterKilled|%s|%d|%s|%d|%d|%d|%d|%d|%d|%d|%s|%d"
			, GetEventId(), mon.getId(), GetTime(), ServerInstance()->GetServerIndex(), mon.GetSceneID(), mon.GetIntProp(P_POS_X), mon.GetIntProp(P_POS_Y)
			, 0, 0, 0, "0", 0);
		log->LogTLog(send_buf_); 
	}
}

void TlogMgr::LogDiscardItem(Actor* actor, ItemData* item)
{
	if (!open_log_) return;

	if (!actor || !item) return;

	char strguid[64];
	SNPRINTFA(strguid, sizeof(strguid), I64FMT, item->series.llId);

	// DiscardItem|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vReoleName|iJobId|iGender|iRoleLevel|iItemId|iItemType|iItemNum|iItemGuid
	SNPRINTFA(send_buf_, sizeof(send_buf_), "DiscardItem|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%d|%d|%s"
	          , GetEventId(), actor->GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor->GetActorId(), TLogReplace(actor->GetEntityName()), actor->GetIntProp(P_VOCATION)
	          , actor->GetIntProp(P_SEX), actor->GetIntProp(P_LEVEL), item->wItemId, 0, item->count_, strguid);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogMoneyFlow(Actor& actor, int moneyType, int amount, const char* phylum)
{
	//if (!open_log_) return;

	//int money = actor.GetMoneyCount(moneyType);
	//int iAction = 0;
	//if (moneyType == mtYuanbao)
	//{
	//	if (amount < 0)
	//	{
	//		iAction = 2; // 消费
	//	}
	//	else if (strcmp("payment", phylum) == 0)
	//	{
	//		iAction = 1; // 充值
	//	}
	//}

	//// MoneyFlow|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iBeforeMoney|iAfterMoney|iMoneyType|iMoney|iAction|vDesc|iLoginWay
	//SNPRINTFA(send_buf_, sizeof(send_buf_), "MoneyFlow|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%d|%d|%d|%d|%s|%d"
	//          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(PROP_VOCATION)
	//          , actor.GetIntProp(PROP_SEX), actor.GetIntProp(PROP_LEVEL), money - amount, money, moneyType, amount>0 ? amount : -amount, iAction, phylum, actor.GetPfId());
	//static LogSender* log = ServerInstance()->GetLogClient();
	//log->LogTLog(send_buf_);
}

void TlogMgr::LogRecharge(Actor& actor, int amount)
{
	//if (!open_log_) return;

	//int money = actor.GetMoneyCount(mtYuanbao);

	//// ChongZhi|iEventId|dtEventTime|iWorldId|vSrcUin|vDstUin|iSourceWay|vClientIp|vReMarks|iPayBefore|iPayDelta|iPayAfter|vDesc|iLoginWay
	//SNPRINTFA(send_buf_, sizeof(send_buf_), "ChongZhi|%s|%s|%d|%s|%s|%d|%s|%s|%d|%d|%d|%s|%d"
	//          , GetEventId(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetAccount(), actor.GetAccount(), 0, actor.GetLastLoginIp(), "", money - amount, amount, money, "", actor.GetPfId());
	//static LogSender* log = ServerInstance()->GetLogClient();
	//log->LogTLog(send_buf_);
}

void TlogMgr::LogStartPostToken(Actor& actor, ConsingmentData& data)
{
	if (!open_log_) return;

	int money = actor.GetMoneyCount(data.sell_money_type_);

	// StartPostToken|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iRoleLevel|iPostId|iPostType|iPostNum|iPostPrice|iPostBeforNum|iPostAfterNum|iCostType|iCostMoney
	SNPRINTFA(send_buf_, sizeof(send_buf_), "StartPostToken|%s|%s|%s|%d|%d|%s|%d|%u|%d|%d|%d|%d|%d|%d|%d"
				, GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName())
				, actor.GetIntProp(P_LEVEL), data.handle_, data.sell_money_type_, data.sell_money_, data.price_, money+data.sell_money_, money
				, data.moneyType_, data.price_);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogEndPostToken(Actor* actor, ConsingmentData& data)
{
	if (!open_log_) return;

	// actor 可能为空

	int money = actor ? actor->GetMoneyCount(data.sell_money_type_) : 0;

	// EndPostToken|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iRoleLevel|iPostId|iPostType|iPostNum|iPostPrice|iPostBeforNum|iPostAfterNum|iCostType|iCostMoney
	SNPRINTFA(send_buf_, sizeof(send_buf_), "EndPostToken|%s|%s|%s|%d|%d|%s|%d|%u|%d|%d|%d|%d|%d|%d|%d"
		, GetEventId(), data.account_name_, GetTime(), ServerInstance()->GetServerIndex(), data.actorId_, data.actor_name_
		, actor ? actor->GetIntProp(P_LEVEL) : 0, data.handle_, data.sell_money_type_, data.sell_money_, data.price_, actor ? money+data.sell_money_ : 0, money
		, data.moneyType_, data.price_);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPostTokenTrade(Actor& actor, ConsingmentData& data)
{
	if (!open_log_) return;

	int nmoney = actor.GetMoneyCount(data.moneyType_);
	// PostTokenTrade|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iRoleLevel|vSellerUin|vSellerName|iPostId|iPostType|iPostNum|iPostMoneyType|iPostPrice|iBuyBeforMoney|iBuyAfterMOney
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PostTokenTrade|%d|%s|%s|%d|%d|%s|%d|%s|%s|%u|%d|%d|%d|%d|%d|%d"
		, GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_LEVEL), data.account_name_, data.actor_name_
		, data.handle_, data.sell_money_type_, data.sell_money_, data.moneyType_, data.price_, nmoney + data.price_, nmoney);

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogPickupItem(Actor& actor, ItemOPParam& item, int64_t guid)
{
	if (!open_log_) return;

	char guidstr[64];
	SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, guid);

	// PickupItem|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iRoleLevel|iMapId|iPosX|iPosY|iPickItemId|iPickItemType|iPickItemNum|iGuid
	SNPRINTFA(send_buf_, sizeof(send_buf_), "PickupItem|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%d|%d|%d|%s"
	          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_LEVEL)
	          , actor.GetSceneID(), actor.GetIntProp(P_POS_X), actor.GetIntProp(P_POS_Y), item.itemid, ltAlays, item.count, guidstr);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogUseItem(Actor& actor, ItemData& item)
{
	if (!open_log_) return;

	char guidstr[64];
	SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, item.series.llId);

	// UseItem|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iItemId|iItemType|iItemNum|iItemGuid
	SNPRINTFA(send_buf_, sizeof(send_buf_), "UseItem|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%d|%d|%s"
	          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_VOCATION), actor.GetIntProp(P_SEX)
	          , actor.GetIntProp(P_LEVEL), item.wItemId, ltAlays, item.count_, guidstr);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogTaskStart(Actor& actor, const QuestConfig& conf)
{
	if (!open_log_) return;

	// TaskStart|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iTaskId|vTaskName|iNpcId|vNPCName
	SNPRINTFA(send_buf_, sizeof(send_buf_), "TaskStart|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%s|%d|%s"
	          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_VOCATION), actor.GetIntProp(P_SEX)
	          , actor.GetIntProp(P_LEVEL), conf.qid_, conf.name_, conf.StartNpc.sid_, conf.StartNpc.sNpcName);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogTaskFinished(Actor& actor, const QuestConfig& conf, TLogItem* qitems, int nitem, TLogItem* litems, int litem)
{
	if (!open_log_ || !qitems || !litems) return;

	const char* eid = GetEventId();
	const char* etm = GetTime();
	int sid = ServerInstance()->GetServerIndex();

	char guidstr[32];

	// 获得
	for (int i=0; i<nitem; i++)
	{
		TLogItem& item = qitems[i];
		if (item.id_ > 0)
		{
			SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, item.guid_);

			// TaskFinished|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iTaskId|vTaskName|iNpcId|vNPCName|iGetOrLost|iItemId|iItemType|iItemNum|iItemGuid
			SNPRINTFA(send_buf_, sizeof(send_buf_), "TaskFinished|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%s|%d|%s|%d|%d|%d|%d|%s"
				, eid, actor.GetAccount(), etm, sid, actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_VOCATION), actor.GetIntProp(P_SEX), actor.GetIntProp(P_LEVEL)
				, conf.qid_, conf.name_, 0, conf.EndNpc.sNpcName, 1, item.id_, item.type_, item.count_, guidstr);

			static LogSender* log = ServerInstance()->GetLogClient();
			log->LogTLog(send_buf_);
		}
	}

	// 失去
	for (int i=0; i<litem; i++)
	{
		TLogItem& item = litems[i];
		SNPRINTFA(guidstr, sizeof(guidstr), I64FMT, item.guid_);

		// TaskFinished|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iTaskId|vTaskName|iNpcId|vNPCName|iGetOrLost|iItemId|iItemType|iItemNum|iItemGuid
		SNPRINTFA(send_buf_, sizeof(send_buf_), "TaskFinished|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%s|%d|%s|%d|%d|%d|%d|%s"
			, eid, actor.GetAccount(), etm, sid, actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_VOCATION), actor.GetIntProp(P_SEX), actor.GetIntProp(P_LEVEL)
			, conf.qid_, conf.name_, 0, conf.EndNpc.sNpcName, 1, item.id_, item.type_, item.count_, guidstr);

		static LogSender* log = ServerInstance()->GetLogClient();
		log->LogTLog(send_buf_);
	}
}

void TlogMgr::LogCancelTask(Actor& actor, const QuestConfig& conf)
{
	if (!open_log_) return;

	// CancelTask|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iTaskId|vTaskName|iNpcId|vNPCName
	SNPRINTFA(send_buf_, sizeof(send_buf_), "CancelTask|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%s|%d|%s"
	          , GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(P_VOCATION), actor.GetIntProp(P_SEX)
	          , actor.GetIntProp(P_LEVEL), conf.qid_, conf.name_, conf.StartNpc.sid_, conf.StartNpc.sNpcName);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

void TlogMgr::LogKillMon(Actor& actor, Monster& monster, int teamflag, int getexp, MONSTERCONFIG& mconf)
{
	// 腾讯表示先不做
#if 0
	if (!open_log_) return;

	SecondTime ret = monster.first_attack_t_;
	SystemTime sys_t;
	ret.decode(sys_t);

	char tstr[32];
	SNPRINTFA(tstr, ArrayCount(tstr), "%02d-%02d-%02d %02d:%02d:%02d",
	          sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_, sys_t.min_, sys_t.sec_);

	// KillMon|iEventId|vUin|dtEventTime|iWorldId|iRoleId|vRoleName|iJobId|iGender|iRoleLevel|iRolePosX|iRolePosY|iMonsterId|iMapId|iPosX|iPosY|iTeamFlag|iGetExp|iOrdinAttackNum|iSkillAttackNum|iOradinAttackInj|iSkillAttackInju|iStandardPH|iMonsterLevel|iMonsterExp|iMonsterType|dtFirstAttackTime
	SNPRINTFA(send_buf_, sizeof(send_buf_), "KillMon|%s|%s|%s|%d|%d|%s|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%s"
			, GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetActorId(), TLogReplace(actor.GetEntityName()), actor.GetIntProp(PROP_VOCATION)
			, actor.GetIntProp(PROP_SEX), actor.GetIntProp(PROP_LEVEL), actor.GetIntProp(PROP_ENTITY_POSX), actor.GetIntProp(PROP_ENTITY_POSY), monster.getId()
			, actor.GetSceneID(), monster.GetIntProp(PROP_ENTITY_POSX), actor.GetIntProp(PROP_ENTITY_POSY), teamflag, getexp
			, monster.common_attack_, monster.skill_attack_, monster.common_attack_injury_, monster.skill_attack_injury_, mconf.maxDropHp
			, monster.GetIntProp(PROP_LEVEL), mconf.exp_, mconf.type_, tstr);

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
#endif
}

void TlogMgr::LogOffline(Actor& actor, int reason)
{
	if (!open_log_) return;

	// Offline|iEventId|vUin|dtEventTime|iWorldId|vClientIp|iPort|iOfflineType
	SNPRINTFA(send_buf_, sizeof(send_buf_), "Offline|%s|%s|%s|%d|%s|%d|%d"
		, GetEventId(), actor.GetAccount(), GetTime(), ServerInstance()->GetServerIndex(), actor.GetLastLoginIp(), 0, reason);

	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogTLog(send_buf_);
}

const char* TlogMgr::GetTime()
{
	SystemTime sys_t;
	GetSystemTime(sys_t);
	SNPRINTFA(time_text_, ArrayCount(time_text_),
	          "%02d-%02d-%02d %02d:%02d:%02d",
	          sys_t.year_, sys_t.mon_, sys_t.mday_, sys_t.hour_, sys_t.min_, sys_t.sec_);
	return time_text_;
}

const char* TlogMgr::GetEventId()
{
	static char buf[64] = { 0 };

	// 时间 + 序号
	event_id_.sval_.time_ = (unsigned int)NOW_T;
	event_id_.sval_.series_ = (event_id_.sval_.series_ > (unsigned int) - 1 ? 0 : event_id_.sval_.series_ + 1);

#ifdef _MSC_VER
	SNPRINTFA(buf, sizeof(buf), "%I64u", event_id_.ival_);
#else
	SNPRINTFA(buf, sizeof(buf), "%llu", event_id_.ival_);
#endif
	return buf;
}


