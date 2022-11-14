#ifndef _USER_ITEM_H_
#define _USER_ITEM_H_

#include "common.h"


// ��ʱû�ã�������varchar64�������
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
		unsigned int time_;	//31-0λ��ʾ��Ʒ���������ں�ʱ�䣬ֵΪ���������ͣ���λ����
		uint16_t	series_;	//47-32λ��ʾ��һ���ڵ����У�ÿ����һ����Ʒ������ֵ+1��һ�������ֵ����
		uint16_t	sid_;	//55-48λ��ʾ������ID
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
		int attr[EQUIP_ATTR_COUNT][ITEM_ATTR_TYPEVALUE];	// ����+value
	};

// public:
	EquipAttr equip_attr;
};

struct ItemData
{
	int64_t		uid;	//��ƷΨһϵ�к� ItemSeries
	int			id;
	int			count;
	ItemAttrData attr_data; // �󲿷���Ʒ����װ���������Ժ��٣�����Ҫ���Ż�
	ItemAttrData ex_attr_data;

	ItemData()
	{
		memset(this, 0, sizeof(ItemData));
	}

public:
	//�޸�useritem ע����Ҫ�޸�����3������ writeToPack, writeDbPack, writeCrcPack
	//��װ���͸��ͻ��˵İ�
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


