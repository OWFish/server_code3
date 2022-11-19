#ifndef _USER_ITEM_H_
#define _USER_ITEM_H_

#include "common.h"


// 暂时没用，可以用varchar64来做这个
//#define ITEM_DATA_RESERVED_SIZE 64
#define EQUIP_ATTR_COUNT 8
#define ITEM_ATTR_TYPEVALUE 2
#define ITEM_ATTR_TYPE 0
#define ITEM_ATTR_VALUE 1

enum BagType
{
	BagType_Item = 0,
	BagType_Equip,
	BagType_Depot,
};


#pragma pack (push, 1)
union ItemSeries
{
	int64_t	llId;

	struct
	{
		unsigned int time_;	//31-0位表示物品产生的日期和时间，值为短日期类型，单位是秒
		uint16_t	series_;	//47-32位表示在一秒内的序列，每产生一个物品则序列值+1，一秒后序列值归零
		uint16_t	sid_;	//55-48位表示服务器ID
	} t;
public:
	//inline operator int64_t () const { return llId; }
	//inline bool operator == (const ItemSeries& series) const { return llId == series.llId; }
	//inline bool operator != (const ItemSeries& series) const { return llId != series.llId; }
};

union ItemAttrData
{
// define: 
	struct EquipAttr
	{
		int attr[EQUIP_ATTR_COUNT][ITEM_ATTR_TYPEVALUE];	// 类型+value
	};

// public:
	EquipAttr equip_attr;
};

struct ItemData
{
	int64_t		uid;	//物品唯一系列号 ItemSeries
	int			id;
	int			count;
	ItemAttrData attr_data; // 大部分物品都是装备，且属性很少，不需要做优化
	ItemAttrData ex_attr_data;

	ItemData()
	{
		memset(this, 0, sizeof(ItemData));
	}

public:
	//修改useritem 注意需要修改以下3个函数 writeToPack, writeDbPack, writeCrcPack
	//组装发送给客户端的包
	void writeData(DataPacket& pack) {
		pack.writeBuf(this, sizeof(ItemData)); 
	}

	void readData(DataPacketReader& pack) {
		pack.readBuf(this, sizeof(ItemData));
	}

	static void copy(ItemData* dstItem, ItemData* srcItem)
	{
		if (!dstItem || !srcItem || dstItem == srcItem) return;

		memcpy(dstItem, srcItem, sizeof(ItemData));
	}
};

#pragma pack(pop)

//STATIC_ASSERT(sizeof(ItemData) < ITEM_DATA_RESERVED_SIZE);
typedef std::vector<ItemData*> ItemList ;

#endif


