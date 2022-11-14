#include "StdAfx.h"
#include "script_npc.h"
#include "time_domain_helper.h"
#include "time_domain.h"


namespace TimeDomainHelper {

void scriptStartFunc(const char *rule)
{
	// 触发脚本
	ScriptValueList paramList;
	paramList << rule;

	static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();
	pNpc->GetScript().Call("onTimeRuleStart", &paramList, &paramList);
}

void scriptEndFunc(const char *rule)
{
	// 触发脚本
	ScriptValueList paramList;
	paramList << rule;

	static ScriptNpc* pNpc = GetGameEngine()->GetGlobalNpc();
	pNpc->GetScript().Call("onTimeRuleEnd", &paramList, &paramList);
}

bool regStartScript(const char* rule)
{
	return TimeDomain::getInstance().regStart(rule, scriptStartFunc);
}

bool regEndScript(const char* rule)
{
	return TimeDomain::getInstance().regEnd(rule, scriptEndFunc);
}

} // end of namespace