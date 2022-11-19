#pragma once

#include "actor.h"


inline void AddRechargeEvent(Actor* tar, int yb, int itemid, int back_yb, std::string orderNum)
{
	if (tar == NULL) return;
	tar->AddRecharge(yb, itemid, back_yb, orderNum);

	//������Ҳ��ᱣ������,����ǿ�Ʊ���
	tar->SaveDb(true);
}
