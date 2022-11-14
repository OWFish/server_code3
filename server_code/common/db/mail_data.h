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
	MailAwardStatusType_NoAward = -1,	//无附件
	MailAwardStatusType_CanAward = 0,	//可领取
	MailAwardStatusType_HaveAward = 1,	//已领取 
};

#pragma pack (push, 4)
union MailSeries
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

struct MailAwardData
{
	int type;		//附件类型
	int id;			//附件类型如果是物品的话，就用来存物品id，是货币的话就没用
	int count;		//数量

	MailAwardData() :type(0), id(0), count(0) {}
};

struct MailAwardList
{
	int awardCount;					//附件数量
	MailAwardData awardList[10];	//附件列表
};

struct MailData
{
	static const int HEAD_SIZE = 128;
	static const int CONTEXT_SIZE = 1024;

	int			uid;			//邮件唯一系列号 MailSeries
	int			readStatus;		//读取状态
	int			awardStatus;	//领奖状态
	int			sendtime;		//发送的时间
	char		head[128];		//邮件标题
	char		context[1024];	//邮件正文
	MailAwardList award_data;	// 大部分物品都是装备，且属性很少，不需要做优化

	MailData()
	{
		memset(this, 0, sizeof(MailData));
	}

public:
	//修改useritem 注意需要修改以下3个函数 writeToPack, writeDbPack, writeCrcPack
	//组装发送给客户端的包
	void writeData(DataPacket& pack) {
		pack.writeBuf(this, sizeof(MailData));
	}

	void readData(DataPacketReader& pack) {
		pack.readBuf(this, sizeof(MailData));
	}
};

#pragma pack(pop)

#endif