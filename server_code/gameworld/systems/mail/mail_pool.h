#pragma  once

#include "db/mail_data.h"

class Mail;


class MailPool : public Singleton<MailPool>
{
public:
	friend Singleton<MailPool>;

	typedef std::vector<MailAwardData> AwardList;

	Mail* CreateMail(MailData* data);
	Mail* CreateMail(char* context, AwardList& pList);

	//设置服务器ID，服务器ID将参与物品系列号的生成
	inline void SetServerId(const int sid) { server_id_ = sid; }
private:
	MailPool();
	~MailPool();

	Mail* NewMail();
private:
	int			series_;	//邮件系列值
	int			server_id_;	//服务器ID
};
