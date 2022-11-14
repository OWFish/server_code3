#pragma once

#include "actor.h"


inline void AddRechargeEvent(Actor* tar, int yb, int itemid, int back_yb, std::string orderNum)
{
	if (tar == NULL) return;
	tar->AddRecharge(yb, itemid, back_yb, orderNum);

	//离线玩家不会保存数据,所以强制保存
	tar->SaveDb(true);
}
