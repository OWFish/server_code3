#ifndef _AI_MGR_H_
#define _AI_MGR_H_

//AI������,���ڴ�������AIʵ��
#include "ai.h"

class AiMgr
{
public:
	static const int ONE_TIME_ALLOC = 1024;

	AiMgr() : ai_mgr_(("AIHdlMgr"))
	{}
	~AiMgr();
	/*
	* Comments: ����һ��AI����
	* Param int nAiId:  AI��ID
	* Param CAnimal * pAnimal: ai�����˵�ָ��
	* @Return CAnimalAI *: ai��ָ��
	*/
	AI* CreateAi(int n_id, Creature* p_mon);

	/*
	* Comments: ɾ��һ��ai
	* Param CAnimalAI * pAi: ai��ָ��
	* @Return void:
	*/
	void DestroyAi(AI*& p_ai);
private:
	ObjPool<AI, ONE_TIME_ALLOC> ai_mgr_;
};

#endif

