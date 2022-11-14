#ifndef _CONSIGNMENT_H_
#define _CONSIGNMENT_H_

#include "common.h"
#include "item_data.h"
#include "common/datalist.h"


//禁止编译器对此结构进行字节对齐
#pragma pack (push, 1)
//
typedef struct tagConsingmentData
{
	ItemSeries	id_;	// 唯一的id
	ItemData*	item_;	//标准的物品结构
	int			sell_money_;	// 出售的是金钱
	int			sell_money_type_;	// 金钱类型，只能是非绑定的

	UINT		restTime_;	//寄卖的剩余时间
	UINT		price_;		//价钱
	ActorId		actorId_;	//所有者的id

	uint8_t		moneyType_;	//元宝或者银两
	uint8_t		bJob;		//适用的职业，0是通用，见职业定义
	uint8_t		bType;		//类型，
	uint8_t		bLevel;		//物品使用所需的等级
	uint8_t		timeOut_;	//是否过期，0表示没过期，否则表示过期
	unsigned int handle_;	//用于内存管理的handle
	ACTORNAME	actor_name_;		//所有者名字
	char		account_name_[64];	// 账户名称

	tagConsingmentData()
	{
		ZeroMemory(this, sizeof(*this));
	}
	static bool SortRule(tagConsingmentData* data1, tagConsingmentData* data2)
	{
		return (data1->moneyType_ == data2->moneyType_) ? (data1->price_ < data2->price_) : (data1->moneyType_ > data2->moneyType_);
	}
}ConsingmentData;
#pragma pack(pop)

#endif

