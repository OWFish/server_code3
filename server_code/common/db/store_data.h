#ifndef _STORE_DATA_H_
#define _STORE_DATA_H_

#include "common.h"
#include "item_data.h"

struct StoreItemData
{
	int			id;					//商品id
	int			currency_type;		//购买的货币类型
	int			currency;			//购买需要的货币数量
	int			discount;			//折扣类型，1是8折，2是5折
	ItemData	itemData;			//道具数据

	StoreItemData()
	{
		memset(this, 0, sizeof(StoreItemData));
	}

public:
	//修改useritem 注意需要修改以下3个函数 writeToPack, writeDbPack, writeCrcPack
	//组装发送给客户端的包
	void writeData(DataPacket& pack) {
		pack.writeBuf(this, sizeof(StoreItemData));
	}

	void readData(DataPacketReader& pack) {
		pack.readBuf(this, sizeof(StoreItemData));
	}
};


#endif