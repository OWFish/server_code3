#include "StdAfx.h"
#include "mail_system.h"
#include "mail_pool.h"
#include "actor/actor_asyn_mgr.h"
#include "log/log_sender.h"

MailSystem::MailSystem(Actor* actor)
{
	actor_ = actor;
	need_save_ = false;
	init_finish_ = false;
}

MailSystem::~MailSystem()
{
	int count = static_cast<int>( mail_list_.size());
	for (int i = 0; i < count; ++i)
	{
		delete mail_list_[i];
	}
}


bool MailSystem::Init(DataPacketReader &data)
{
	if (!actor_)
		return false;

	if (!actor_->CheckInitStep(Actor::InitFlagType_Basic))
	{
		OutputMsg(rmError, "init order error. on init mail.");
		return false;
	}
	if (actor_->CheckInitStep(Actor::InitFlagType_Mail))
		return true;

	if (init_finish_) return true;

	int mail_count;
	data >> mail_count;
	if (data.getAvaliableLength() < mail_count * sizeof(MailData))
	{
		OutputMsg(rmError, "aid:%d, Init item bag failed. data length is wrong;%d, count:%d",
			actor_->GetActorId(), data.getAvaliableLength(), mail_count);
		return false;
	}

	MailData mail_data;
	for (int i = 0; i < mail_count; ++i)
	{
		data >> mail_data;
		Mail *pMail = MailPool::instance().CreateMail(&mail_data);
		AddMail(pMail);
	}
	MailSort();
	
	init_finish_ = true;
	actor_->OnFinishInitStep(Actor::InitFlagType_Mail);
	
	return true;
}

void MailSystem::Save(ActorBasicData* data, bool force)
{
	if (!actor_) return;

	DBClient* db = ServerInstance()->GetDbClient(actor_->GetServerId());
	if (!db) return;

	if (!force && !need_save_) return;

	DataPacket& pack = db->allocProtoPacket(MAKEINT16(siActor, dcSaveMail));
	pack << (ActorId)actor_->GetActorId();
	pack << (int)(mail_list_.size());

	for (std::size_t i = 0; i < mail_list_.size(); ++i)
	{
		Mail *pMail = mail_list_[i];
		pMail->WriteData(pack);
	}
	db->flushProtoPacket(pack);
	//OutputMsg(rmTip, "SaveMail:actor:%d.", actor_->GetActorId());

	need_save_ = false;
}

void MailSystem::OnEnterGame()
{
	UpdataGlobalMail();
}

Mail* MailSystem::GetMail(int uid)
{
	int count = static_cast<int>( mail_list_.size());
	for (int i = 0; i < count; ++i)
	{
		if (mail_list_[i]->GetUId() == uid)
		{
			return mail_list_[i];
		}
	}
	return NULL;
}

void MailSystem::MailSort()
{
	int count = static_cast<int>( mail_list_.size());
	for (int i = 0; i < count;++i)
	{
		for (int j = i + 1; j < count;++j)
		{
			if (mail_list_[i]->GetMailData().sendtime < mail_list_[j]->GetMailData().sendtime)
			{
				Mail *temp = mail_list_[i];
				mail_list_[i] = mail_list_[j];
				mail_list_[j] = temp;
			}
		}
	}
}

void MailSystem::AddMail(Mail *mail)
{
	if (mail) mail_list_.push_back(mail);
	need_save_ = true;
}

void MailSystem::GetMailId(Mail *mail)
{
	if (!mail)  return;

	ScriptValueList arg;
	arg << actor_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	if (!luaScript.Call("getNextMailId", &arg, &arg, 1))
		return;

	int mailId = (int)arg[0];
	mail->setUId(mailId);
}

void MailSystem::RevcMail(Mail *mail)
{
	if (!mail) return;

	GetMailId(mail);
	AddMail(mail);
	need_save_ = true; 
	MailSort();
	DeleteUseless();

	ScriptValueList arg;
	arg << actor_;
	arg << mail->GetUId();
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("recvMail", &arg, &arg, 0);

	static LogSender* log = ServerInstance()->GetLogClient();

	auto basic_data = actor_->GetBasicData();
	if (!basic_data) return;

	char level[100];
	char uid[100];
	sprintf(level, "%d", basic_data->level);
	sprintf(uid, "%d", mail->GetMailData().uid);
	log->LogCounter(basic_data->account_id
		, basic_data->account_name
		, level
		, "recv maile"
		, mail->GetMailData().head
		, mail->GetMailData().context
		, uid
		, "", "", "", ""
	);
}

void MailSystem::DeleteUseless()
{
	if (mail_list_.size() <= maxMailNum) return;

	int count = static_cast<int>( mail_list_.size());
	int more = count - maxMailNum;
	for (int i = 0; i < more; ++i)
	{
		DeleteMailSync(mail_list_[mail_list_.size() - 1]->GetUId());
		delete mail_list_[mail_list_.size() - 1];
		mail_list_.pop_back();
	}
}

void MailSystem::DeleteMail(int uid)
{
	int count = static_cast<int>( mail_list_.size());
	for (int i = 0; i < count; ++i)
	{
		if (mail_list_[i]->GetUId() == uid)
		{
			delete mail_list_[i];
			DeleteMailSync(uid);

			mail_list_[i] = mail_list_[count - 1];
			mail_list_.pop_back();
			break;
		}
	}
	MailSort();
}

void MailSystem::ChangeMailReadStatus(int uid)
{
	int count = static_cast<int>( mail_list_.size());
	for (int i = 0; i < count; ++i)
	{
		if (mail_list_[i]->GetUId() == uid)
		{
			mail_list_[i]->changeReadStatus(MailReadStatusType_HaveRead);
			need_save_ = true;
		}
	}
}

void MailSystem::ChangeMailAwardStatus(int uid)
{
	int count = static_cast<int>( mail_list_.size() );
	for (int i = 0; i < count; ++i)
	{
		if (mail_list_[i]->GetUId() == uid)
		{
			mail_list_[i]->changeAwardStatus(MailAwardStatusType_HaveAward);
			need_save_ = true;
		}
	}
}

void RecvOffLineMail(Actor* tar, Mail *pMail)
{
	MailSystem *mailSystem = tar->GetMailSystem();
	if (!mailSystem) return;

	mailSystem->GetMailId(pMail);
	mailSystem->AddMail(pMail);

	mailSystem->MailSort();
	mailSystem->DeleteUseless();
	//mailSystem->Save(NULL, true);
	tar->SaveDb(true);


	auto basic_data = tar->GetBasicData();
	char level[100];
	char uid[100];
	sprintf(level, "%d", basic_data->level);
	sprintf(uid, "%d", pMail->GetMailData().uid);
	static LogSender* log = ServerInstance()->GetLogClient();
	log->LogCounter(basic_data->account_id
		, basic_data->account_name
		, level
		, "recv offline mail"
		, pMail->GetMailData().head
		, pMail->GetMailData().context
		, uid
		, "", "", "", ""
	);
}

void RecvOffLineMailTimeOut(Mail *pMail) {
	if (pMail) {
		SafeDelete(pMail);
	}
}

void MailSystem::SendOffLineMail(ActorId actorId, MailData *data)
{
	if (actorId == 0) {
		OutputMsg(rmError, "%s actorId == 0", __FUNCTION__);
		return;
	}
	Mail *pMail = MailPool::instance().CreateMail(data);
	ActorAsynFunc func = std::bind(RecvOffLineMail, std::placeholders::_1, pMail);
	TimeOutAsynFunc timeout_func = std::bind(RecvOffLineMailTimeOut, pMail);
	GetGameEngine()->GetActorAsynMgr()->RegActorEv(actorId, func, 0, timeout_func);
}

void MailSystem::DeleteMailSync(int uid)
{
	ScriptValueList arg;
	arg << actor_;
	arg << uid;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("deleteMailSync", &arg, &arg, 0);
}


int MailSystem::GetGlobalMailMaxUid(void)
{
	ScriptValueList arg;
	arg << actor_;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("getGlobalMailMaxUid", &arg, &arg, 1);
	return (int)arg[0];
}

void MailSystem::setGlobalMailMaxUid(int uid)
{
	ScriptValueList arg;
	arg << actor_;
	arg << uid;
	static GameScript& luaScript = GetGameEngine()->GetGlobalNpc()->GetScript();
	luaScript.Call("setGlobalMailMaxUid", &arg, &arg, 0);
}

void MailSystem::UpdataGlobalMail(void)
{
	GetGameEngine()->GetGlobalMailMgr()->UpdataUserMailData(this);
}

