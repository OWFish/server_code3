#include "StdAfx.h"
#include "actor_data_mgr.h"



void ActorDataMgr::Destroy()
{
	for (auto p : data_list_)
		SafeDelete(p);
}

bool ActorDataMgr::Load()
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
	int err = sql.Query("select * from actors where serverindex=%d and (status & 2)=2", ServerInstance()->GetServerIndex());
	if (err)
	{
		OutputMsg(rmError, "Load actor basic data failed.");
		return false;
	}

	MYSQL_ROW row = sql.CurrentRow();
	int count = sql.GetRowCount();
	data_list_.reserve(count);
	int effective_time = GetGameEngine()->getMiniDateTime() - 7 * 24 * 3600;// 7天未登录

	int i = 0;
	while (row)
	{
		ActorBasicData *actor_data = new ActorBasicData();
		memset(actor_data, 0, sizeof(ActorBasicData));

		ReadActorBasicData(*actor_data, row, sql.GetFieldsLength());
		if (actor_data->level > 15 || actor_data->last_online_time > (unsigned int)effective_time){
			data_list_.push_back(actor_data);
			data_index_[actor_data->actor_id] = i;
			name_index_[actor_data->actor_name] = actor_data->actor_id;
			++i;
		}
		else
		{
			SafeDelete(actor_data);
		}
		row = sql.NextRow();
	}
	OutputMsg(rmTip, "load all actor completed. size:%d", i);

	sql.ResetQuery();
	return true;
}

const ActorBasicData* ActorDataMgr::GetData(int aid) const
{
	auto it = data_index_.find(aid);
	if (it == data_index_.end())
		return NULL;
	return data_list_[it->second];
}

ActorBasicData* ActorDataMgr::GetData(int aid)
{
	auto it = data_index_.find(aid);
	if (it != data_index_.end())
		return data_list_[it->second];

	ActorBasicData *actor_data = new ActorBasicData();
	data_list_.push_back(actor_data);
	data_index_[aid] = static_cast<int>(data_list_.size() - 1);
	name_index_[actor_data->actor_name] = actor_data->actor_id;
	return actor_data;
}

int ActorDataMgr::GetId(const char* name)
{
	if (nullptr == name) return 0;
	auto it = name_index_.find(name);
	if (it != name_index_.end())
		return it->second;
	return 0;
}

int ActorDataMgr::GetIdByAccountName(const char* name)
{
	if (nullptr == name) return 0;
	for (auto it : data_list_)
	{
		if (strcmp(it->account_name, name) == 0)
			return it->actor_id;
	}
	return 0;
}

int ActorDataMgr::getActorIdByName(const char* name)
{
	if (nullptr == name) return 0;
	for (auto it : data_list_)
	{
		if (strcmp(it->actor_name, name) == 0)
			return it->actor_id;
	}
	return 0;
}
