#include "StdAfx.h"
#include "mail_pool.h"
#include "mail.h"
#include "db/mail_data.h"


MailPool::MailPool()
: series_(0)
, server_id_(0)
{

}

MailPool::~MailPool()
{

}


Mail* MailPool::CreateMail(MailData* data)
{
	if (data == NULL) return NULL;

	Mail *mail = NewMail();
	memcpy(&mail->data_, data, sizeof(MailData));
	if (!mail->Init())
	{
		OutputMsg(rmError, "create mail failed. init failed.");
		delete mail;
		return NULL;
	}
	if (mail->data_.award_data.awardCount == 0)
		mail->data_.awardStatus = MailAwardStatusType_NoAward;

	return mail;
}

Mail* MailPool::CreateMail(char* context, AwardList& pList)
{
	Mail *mail = NewMail();
	memset(mail->data_.context, 0, sizeof(mail->data_.context));
	strcpy(mail->data_.context, context);
	mail->data_.readStatus = MailReadStatusType_NotRead;

	int count = static_cast<int>( pList.size());
	mail->data_.award_data.awardCount = count;
	for (int i = 0; i < count; ++i)
	{
		mail->data_.award_data.awardList[i].id = pList[i].id;
		mail->data_.award_data.awardList[i].count = pList[i].count;
		mail->data_.award_data.awardList[i].type = pList[i].type;
	}

	static GameEngine* ge = GetGameEngine();
	mail->data_.sendtime = ge->getMiniDateTime();

	mail->data_.readStatus = MailReadStatusType_NotRead;
	if (mail->data_.award_data.awardCount == 0)
		mail->data_.awardStatus = MailAwardStatusType_NoAward;

	return mail;
}

Mail* MailPool::NewMail()
{
	return new Mail();
}


