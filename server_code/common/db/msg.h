#ifndef _MSG_H_
#define _MSG_H_

#define MAX_MSG_COUNT 1024			//��������ݿⶨ��ĳ�����أ����ܸ�
#define MAX_MAIL_COUNT 1024			//��������ݿⶨ��ĳ�����أ����ܸ�
#define MAX_MAIL_FILE_COUNT 3
#define MAX_MAIL_NOTIFY	180
//��ֹ�������Դ˽ṹ�����ֽڶ���
#pragma pack (push, 1)
//���������ҵ��ʼ���Ϣ

struct MailFile
{
	uint8_t type_;  // 0 NULL 1 ��Ʒ 2 ��Ǯ
	int sort_;  // ��ƷID���Ǯ���ࣨ1 Ԫ���� 2 ��Ԫ���� 3 ������ 4 �ɱң�
	int num_;   // ����
	uint8_t bind_; // �Ƿ��
	int quality_; // Ʒ��

	MailFile()
	{
		ZeroMemory(this, sizeof(*this));
	}
	void reset()
	{
		ZeroMemory(this, sizeof(*this));
	}
};
	
// struct MailData
// {
// 	int64_t id_;
// 	int actor_id_;
// 	uint8_t type_;
// 	uint8_t status_;
// 	int sender_id_;
// 	int sender_level_;
// 	uint32_t send_tick_;
// 	char send_name_[33];
// 	char context_[MAX_MAIL_COUNT];
// 	MailFile attachment_[MAX_MAIL_FILE_COUNT];
// 
// 	MailData()
// 	{
// 		ZeroMemory(this, sizeof(*this));
// 	}
// 	void reset()
// 	{
// 		ZeroMemory(this, sizeof(*this));
// 	}
// };

struct GmQuestionData
{
	int64_t id_;
	int server_id_;
	int actor_id_;
	char name_[128];
	int status_;
	int hasread_;
	char title_[128];
	int type_;
	char question_[1024];
	char qq_[16];
	unsigned int question_time_;
	char answer_[1024];
	unsigned int answer_time_;

	GmQuestionData()
	{
		ZeroMemory(this, sizeof(*this));
	}
	void reset()
	{
		ZeroMemory(this, sizeof(*this));
	}
};

struct FeeData
{
	int id_;
	char openid_[128];
	int itemId_;
	int num_;
	int actor_id_;
	char order_num_[128];
};

struct TxApiMsgData
{
	int id_;
	char openid_[128];
	int type_;
	char para1_[64];
	char para2_[64];
	char para3_[64];
	char para4_[64];
	char para5_[64];
};

#pragma pack(pop)

#endif

