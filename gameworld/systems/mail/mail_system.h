#pragma once

#include "db/mail_data.h"
#include "mail.h"

class MailSystem
{
public:
	MailSystem(Actor *actor);
	~MailSystem();

	const static int deleteTime = 3600 * 24 * 15;
	const static int maxMailNum = 50;	// 邮件上限, 不能太多,否则会超过65535
	STATIC_ASSERT(maxMailNum * sizeof(MailData) < 65535);

	typedef std::vector<Mail*> MailList;

	bool Init(DataPacketReader &data);
	void Save(ActorBasicData* data, bool force = false);
	void OnEnterGame();

	Mail* GetMail(int uid);
	MailList& GetMailList(){ return mail_list_; }

	void MailSort();
	Actor* GetActor(void) { return actor_; }
	void RevcMail(Mail *mail);
	void DeleteUseless();
	void DeleteMail(int uid);
	void ChangeMailReadStatus(int uid);
	void ChangeMailAwardStatus(int uid);
	void AddMail(Mail *mail);
	void GetMailId(Mail *mail);

	static void SendOffLineMail(ActorId actorId, MailData *data);
	int GetGlobalMailMaxUid(void);
	void setGlobalMailMaxUid(int uid);
	void UpdataGlobalMail(void);
private:
	void DeleteMailSync(int uid);

protected:
	Actor *actor_;

	MailList mail_list_;

	bool need_save_;
	bool init_finish_;
};