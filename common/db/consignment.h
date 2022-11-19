#ifndef _CONSIGNMENT_H_
#define _CONSIGNMENT_H_

#include "common.h"
#include "item_data.h"
#include "common/datalist.h"


//��ֹ�������Դ˽ṹ�����ֽڶ���
#pragma pack (push, 1)
//
typedef struct tagConsingmentData
{
	ItemSeries	id_;	// Ψһ��id
	ItemData*	item_;	//��׼����Ʒ�ṹ
	int			sell_money_;	// ���۵��ǽ�Ǯ
	int			sell_money_type_;	// ��Ǯ���ͣ�ֻ���Ƿǰ󶨵�

	UINT		restTime_;	//������ʣ��ʱ��
	UINT		price_;		//��Ǯ
	ActorId		actorId_;	//�����ߵ�id

	uint8_t		moneyType_;	//Ԫ����������
	uint8_t		bJob;		//���õ�ְҵ��0��ͨ�ã���ְҵ����
	uint8_t		bType;		//���ͣ�
	uint8_t		bLevel;		//��Ʒʹ������ĵȼ�
	uint8_t		timeOut_;	//�Ƿ���ڣ�0��ʾû���ڣ������ʾ����
	unsigned int handle_;	//�����ڴ�����handle
	ACTORNAME	actor_name_;		//����������
	char		account_name_[64];	// �˻�����

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

