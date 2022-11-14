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

	//���÷�����ID��������ID��������Ʒϵ�кŵ�����
	inline void SetServerId(const int sid) { server_id_ = sid; }
private:
	MailPool();
	~MailPool();

	Mail* NewMail();
private:
	int			series_;	//�ʼ�ϵ��ֵ
	int			server_id_;	//������ID
};
