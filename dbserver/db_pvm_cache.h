#pragma once

#include <unordered_map>
struct StRecordData
{
	std::string m_record;
	bool	is_save;

	void clear()
	{
		m_record = "";
		is_save = false;
	}
};
class CDBPvmCache
{
public:
	static CDBPvmCache* instance()
	{
		static CDBPvmCache ins;
		return &ins;
	}

	void RunOne(int64_t CurrTick, SQLConnection &sql);

	//�����ս��¼
	void AddChallengeRecord(int32_t actorid, int32_t recordtime, std::string recorddata);

	//������ս��¼
	void UpdateChallengeToDB(SQLConnection &sql);

private:
	CDBPvmCache();
public:
	~CDBPvmCache();

	bool is_save;
	int32_t save_cd;
	static CDBPvmCache* ins;
	//���а�����< ���� �� ���id >
	std::map<int32_t, int32_t > _PVMRank;
	//�����ս��¼
	std::unordered_map<int32_t, StRecordData > _mChallengeRecord;
};