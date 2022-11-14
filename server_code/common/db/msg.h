#ifndef _MSG_H_
#define _MSG_H_

#define MAX_MSG_COUNT 1024			//这个跟数据库定义的长度相关，不能改
#define MAX_MAIL_COUNT 1024			//这个跟数据库定义的长度相关，不能改
#define MAX_MAIL_FILE_COUNT 3
#define MAX_MAIL_NOTIFY	180
//禁止编译器对此结构进行字节对齐
#pragma pack (push, 1)
//保存这个玩家的邮件消息

struct MailFile
{
	uint8_t type_;  // 0 NULL 1 物品 2 金钱
	int sort_;  // 物品ID或金钱种类（1 元宝， 2 绑定元宝， 3 银两， 4 仙币）
	int num_;   // 数量
	uint8_t bind_; // 是否绑定
	int quality_; // 品质

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

