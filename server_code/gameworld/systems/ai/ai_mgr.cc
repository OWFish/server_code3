#include "StdAfx.h"
#include "ai_mgr.h"
#include "ai.h"
#include "config/ai_config.h"
//AI管理器,用于创建各种AI实体



AiMgr::~AiMgr()
{
}

AI* AiMgr::CreateAi(int id, Creature* mon)
{
	if (mon == NULL) return NULL;

	const AIConfig* conf = AIConfigPool::Get(id);

	if (conf == NULL) return NULL;

	AI* p_ai = new AI();// ai_mgr_.Alloc();
	
	if (p_ai == NULL) return NULL;

	p_ai->Init(mon, conf);

	return p_ai;
}

void AiMgr::DestroyAi(AI*& p_ai)
{
	if (p_ai == NULL) return;

	SafeDelete(p_ai);
	//ai_mgr_.Free(p_ai);
}

