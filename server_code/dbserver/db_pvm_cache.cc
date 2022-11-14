#include "StdAfx.h"
#include <sstream>

CDBPvmCache::CDBPvmCache()
{
	is_save = false;
	save_cd = 0;
}

CDBPvmCache::~CDBPvmCache()
{

}

void CDBPvmCache::RunOne(int64_t CurrTick, SQLConnection & sql)
{
	if (save_cd == 0)
	{
		save_cd = CurrTick + 1800000;
	}

	if (CurrTick >= save_cd)
	{
		UpdateChallengeToDB(sql);
		save_cd = CurrTick + 1800000;
	}
}

void CDBPvmCache::AddChallengeRecord(int32_t actorid, int32_t recordtime, std::string recorddata)
{
	StRecordData temp;
	temp.clear();
	auto ite = _mChallengeRecord.find(actorid);
	if (ite == _mChallengeRecord.end())
	{
		temp.m_record = recorddata;
		temp.is_save = true;
		_mChallengeRecord.emplace(actorid, temp);
	}
	else
	{
		ite->second.m_record = recorddata;
		ite->second.is_save = true;
	}
}

void CDBPvmCache::UpdateChallengeToDB(SQLConnection &sql)
{
	int i = 0;
	bool is_con = false;

	std::string sql_call = sql_replacechallengerecord;
	std::ostringstream oss;

	for (auto ite : _mChallengeRecord)
	{
		auto& st_ite = ite.second;
		if (st_ite.is_save)
		{
			sql.Exec(UpdateRecord, ite.first, st_ite.m_record.c_str());
			sql.ResetQuery();
			st_ite.is_save = false;
			oss.clear();

		}
	}
}