#ifndef _AI_MGR_H_
#define _AI_MGR_H_

//AI管理器,用于创建各种AI实体
#include "ai.h"

class AiMgr
{
public:
	static const int ONE_TIME_ALLOC = 1024;

	AiMgr() : ai_mgr_(("AIHdlMgr"))
	{}
	~AiMgr();
	/*
	* Comments: 创建一个AI对象
	* Param int nAiId:  AI的ID
	* Param CAnimal * pAnimal: ai所有人的指针
	* @Return CAnimalAI *: ai的指针
	*/
	AI* CreateAi(int n_id, Creature* p_mon);

	/*
	* Comments: 删除一个ai
	* Param CAnimalAI * pAi: ai的指针
	* @Return void:
	*/
	void DestroyAi(AI*& p_ai);
private:
	ObjPool<AI, ONE_TIME_ALLOC> ai_mgr_;
};

#endif

