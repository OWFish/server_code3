#pragma  once

#include <map>
class Actor;
class MailSystem;


class GlobalMailMgr
{
public:
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

		int			uid;			//邮件唯一系列号 MailSeries
		int			sendtime;		//发送的时间
		char		head[128];		//邮件标题
		char		context[1024];	//邮件正文
		MailAwardList award_data;	// 大部分物品都是装备，且属性很少，不需要做优化

		MailData(void)
		{
			memset(this, 0, sizeof(*this));
		}
	};
public:
	GlobalMailMgr(void);
public:
	bool LoadDbData(void);
	int  GetMaxUid(void);
	void UpdataUserMailData(MailSystem* mail);
	void AddGlobalMail(const char* head, const char* context, const char* item_str);
	void UpdataAllMail(void);
private:
	std::map<int, GlobalMailMgr::MailData> mail_data_;
};

