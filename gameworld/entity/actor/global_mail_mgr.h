#pragma  once

#include <map>
class Actor;
class MailSystem;


class GlobalMailMgr
{
public:
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

		int			uid;			//�ʼ�Ψһϵ�к� MailSeries
		int			sendtime;		//���͵�ʱ��
		char		head[128];		//�ʼ�����
		char		context[1024];	//�ʼ�����
		MailAwardList award_data;	// �󲿷���Ʒ����װ���������Ժ��٣�����Ҫ���Ż�

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

