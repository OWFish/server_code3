#ifndef _STORE_DATA_H_
#define _STORE_DATA_H_

#include "common.h"
#include "item_data.h"

struct StoreItemData
{
	int			id;					//��Ʒid
	int			currency_type;		//����Ļ�������
	int			currency;			//������Ҫ�Ļ�������
	int			discount;			//�ۿ����ͣ�1��8�ۣ�2��5��
	ItemData	itemData;			//��������

	StoreItemData()
	{
		memset(this, 0, sizeof(StoreItemData));
	}

public:
	//�޸�useritem ע����Ҫ�޸�����3������ writeToPack, writeDbPack, writeCrcPack
	//��װ���͸��ͻ��˵İ�
	void writeData(DataPacket& pack) {
		pack.writeBuf(this, sizeof(StoreItemData));
	}

	void readData(DataPacketReader& pack) {
		pack.readBuf(this, sizeof(StoreItemData));
	}
};


#endif