#ifndef _MAIL_DATA_H_
#define _MAIL_DATA_H_

#include "common.h"

enum MailAwardType
{
	MailAwardType_Currency,
	MailAwardType_Item,
};

enum MailReadStatusType
{
	MailReadStatusType_NotRead,
	MailReadStatusType_HaveRead,
};

enum MailAwardStatusType
{
	MailAwardStatusType_NoAward = -1,	//�޸���
	MailAwardStatusType_CanAward = 0,	//����ȡ
	MailAwardStatusType_HaveAward = 1,	//����ȡ 
};

#pragma pack (push, 4)
union MailSeries
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

struct MailAwardData
{
	int type;		//��������
	int id;			//���������������Ʒ�Ļ�������������Ʒid���ǻ��ҵĻ���û��
	int count;		//����

	MailAwardData() :type(0), id(0), count(0) {}
};

struct MailAwardList
{
	int awardCount;					//��������
	MailAwardData awardList[10];	//�����б�
};

struct MailData
{
	static const int HEAD_SIZE = 128;
	static const int CONTEXT_SIZE = 1024;

	int			uid;			//�ʼ�Ψһϵ�к� MailSeries
	int			readStatus;		//��ȡ״̬
	int			awardStatus;	//�콱״̬
	int			sendtime;		//���͵�ʱ��
	char		head[128];		//�ʼ�����
	char		context[1024];	//�ʼ�����
	MailAwardList award_data;	// �󲿷���Ʒ����װ���������Ժ��٣�����Ҫ���Ż�

	MailData()
	{
		memset(this, 0, sizeof(MailData));
	}

public:
	//�޸�useritem ע����Ҫ�޸�����3������ writeToPack, writeDbPack, writeCrcPack
	//��װ���͸��ͻ��˵İ�
	void writeData(DataPacket& pack) {
		pack.writeBuf(this, sizeof(MailData));
	}

	void readData(DataPacketReader& pack) {
		pack.readBuf(this, sizeof(MailData));
	}
};

#pragma pack(pop)

#endif