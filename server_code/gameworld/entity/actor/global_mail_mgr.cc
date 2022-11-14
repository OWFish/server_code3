#include "StdAfx.h"
#include "actor/global_mail_mgr.h"

#include "actor/actor.h"
#include "mail/mail_system.h"
#include "mail/mail_pool.h"


GlobalMailMgr::GlobalMailMgr(void)
{

}

bool GlobalMailMgr::LoadDbData(void)
{

	SQLConnection sql;
#ifdef DB_UTF8
	sql.SetUtf8(true);
#endif
	ServerInstance()->GetActorMgr()->SetupSQLConnection(&sql);
	if (!sql.Connected())
	{
		if (sql.Connect()){
			mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
		}
		else {
			OutputMsg(rmError, ("can not load actordatas, sql connection error"));
			return false;
		}
	}
	
	int err = sql.Query("select * from globalmails;");
	if (err)
	{
		OutputMsg(rmError, "Load actor basic data failed.");
		return false;
	}
	MYSQL_ROW pRow = sql.CurrentRow();
	auto fieldLength = sql.GetFieldsLength();
//	int count = sql.GetRowCount();


	while (pRow != nullptr)
	{
	//	OutputMsg(rmTip, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

		GlobalMailMgr::MailData mail_data;
		if (pRow[0])
		{
			sscanf(pRow[0], "%d", &mail_data.uid);
		}
		if (pRow[1])
		{
			sscanf(pRow[1], "%d", &mail_data.sendtime);
		}
		if (pRow[2])
		{
			strcpy(mail_data.head,pRow[2]);
		}
		if (pRow[3])
		{
			strcpy(mail_data.context,pRow[3]);
		}

		if (pRow[4])
		{
			memcpy(&mail_data.award_data,pRow[4] , fieldLength[4]);
		}

		mail_data_[mail_data.uid] = mail_data;
		pRow = sql.NextRow();
		fieldLength = sql.GetFieldsLength();
	}
	
	
	sql.ResetQuery();
	return true;
}

int  GlobalMailMgr::GetMaxUid(void)
{

	if (mail_data_.empty())
	{
		return 0;
	}
	auto it = mail_data_.end();
	--it;
	return it->first;
}

void GlobalMailMgr::UpdataUserMailData(MailSystem* mail)
{
	if (mail == nullptr)
	{
		return;
	}
	auto last_max_uid = mail->GetGlobalMailMaxUid();
	if (last_max_uid == GetMaxUid())
	{
		return;
	}
	auto it = mail_data_.find(last_max_uid);
	auto end = mail_data_.end();
	if (last_max_uid == 0)
	{
		it = mail_data_.begin();
	}
	else
	{
		if (it != end)
		{
			++it;
		}
	}
	bool is_save = false;
	
	for (; it != end; ++it)
	{
		::MailData data;
		data.sendtime = it->second.sendtime;
		strcpy(data.head, it->second.head);
		strcpy(data.context, it->second.context);
		memcpy(&data.award_data, &it->second.award_data, sizeof(it->second.award_data));
		mail->RevcMail(MailPool::instance().CreateMail(&data));
		is_save = true;
	}
	mail->setGlobalMailMaxUid(GetMaxUid());
	if (is_save)
	{
		mail->GetActor()->SaveDb(true);
	}

	

}

void GlobalMailMgr::AddGlobalMail(const char* head, const char* context, const char* item_str)
{
	auto binary2hex = [](void* binary, int len)
	{

		std::string ret;
		if (!binary)
		{
			return ret;
		}
		ret.resize(len * 2);
		const char hex[] = "0123456789ABCDEF";
		const char* b = (const char*)binary;
		int j = 0;
		for (int i = 0; i < len; ++i)
		{
			ret[j++] = hex[(b[i] >> 4) & 0xf];
			ret[j++] = hex[b[i] & 0xf];
		}
		return ret;
	};
	auto split_string = [](const std::string& str, const std::string& pattern)
	{
		std::vector<std::string> ret;
		size_t i = 0;
		{
			i = str.find(pattern);
			if (i == std::string::npos) return ret;
			ret.push_back(str.substr(0, i));
			i += pattern.size();
		}
		for (;;)
		{
			auto p = i;
			i = str.find(pattern, i);
			if (i == std::string::npos)
			{
				if ((str.size() - p))
				{
					ret.push_back(str.substr(p, str.size() - p));
				}
				else if (str.substr(str.size() - pattern.size(), pattern.size()) == pattern)
				{
					ret.push_back("");
				}
				break;
			}
			ret.push_back(str.substr(p, i - p));
			i += pattern.size();
		}

		return ret;
	};


	GlobalMailMgr::MailData mail_data;
	mail_data.uid = GetMaxUid() + 1;
	mail_data.sendtime = (int)time(nullptr);
	strcpy(mail_data.head, head);
	strcpy(mail_data.context, context);

	auto vec1 = split_string(item_str, ";");
	if (vec1.empty())
	{
		vec1.push_back(item_str);
	}
	for (size_t i = 0; i < vec1.size(); ++i)
	{

		auto vec2 = split_string(vec1[i], ",");
		if (vec2.size() != 3)
		{
			continue;
		}
		
		int type = 0;
		int id = 0;
		int count = 0;
		sscanf(vec2[0].c_str(), "%d", &type);
		sscanf(vec2[1].c_str(), "%d", &id);
		sscanf(vec2[2].c_str(), "%d", &count);
		mail_data.award_data.awardList[mail_data.award_data.awardCount].type = type;
		mail_data.award_data.awardList[mail_data.award_data.awardCount].id = id;
		mail_data.award_data.awardList[mail_data.award_data.awardCount].count = count;


		mail_data.award_data.awardCount++;
	}
	mail_data_[mail_data.uid] = mail_data;



	{
		SQLConnection sql;
#ifdef DB_UTF8
		sql.SetUtf8(true);
#endif
		ServerInstance()->GetActorMgr()->SetupSQLConnection(&sql);
		if (!sql.Connected())
		{
			if (sql.Connect()){
				mysql_options(sql.GetMySql(), MYSQL_SET_CHARSET_NAME, "utf8");
			}
			else {
				OutputMsg(rmError, ("can not load actordatas, sql connection error"));
				return;
			}
		}

		char sql_buf[1000] = {};

		sprintf(sql_buf, "insert into globalmails(sendtime,head,context,award) values(%d,0x%s,0x%s,0x%s);",
			mail_data.sendtime,
			binary2hex(mail_data.head, static_cast<int>(strlen(mail_data.head) + 1) ).c_str(),
			binary2hex(mail_data.context, static_cast<int>(strlen(mail_data.context) + 1)).c_str(),
			binary2hex(&mail_data.award_data,sizeof(mail_data.award_data)).c_str()
			);

		int err = sql.Exec(sql_buf);
		if (err)
		{
			OutputMsg(rmError, "insert globalmails");
			return;
		}
		sql.ResetQuery();
	}
	UpdataAllMail();
}


void GlobalMailMgr::UpdataAllMail(void)
{
	void* actorList[8192];
	static EntityMgr* em = GetGameEngine()->GetEntityMgr();
	int count = em->GetOnlineActorPtrList(actorList, 8192);
	for (int i = 0; i < count; ++i)
	{
		Actor* actor = (Actor*)actorList[i];

		actor->GetMailSystem()->UpdataGlobalMail();
	}
}
